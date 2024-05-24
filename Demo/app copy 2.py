from flask import Flask, render_template, jsonify
from threading import Thread, Event
import webview
import requests
import json
from datetime import datetime
import pymysql

app = Flask(__name__)

# 常量配置
APP_TITLE = "数字航道质量分析"
HOST = "http://127.0.0.1"
PORT = 5000
LOGIN_URL = 'http://172.18.100.216/api/blade-auth/ext/api/api/oauth/token/'
DATA_URL = 'http://172.18.100.216/api/datacenter/dataapiCfg/dc/getDataByConfigApi'
HEADERS = {
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/114.0.5735.289 Safari/537.36',
    'Connection': 'keep-alive',
    'Authorization': 'Basic c2FiZXI6c2FiZXJfc2VjcmV0',
    'Content-Type': 'application/json;charset=UTF-8'
}
DB_CONFIG = {
    'host': 'localhost',
    'user': 'root',
    'password': '123456',
    'database': '数字航道质量评估结果',
    'port': 3306
}

# 停止事件
stop_event = Event()

def get_access_token(base_data):
    try:
        res = requests.post(LOGIN_URL, headers=HEADERS, json=base_data)
        res.raise_for_status()
        result = res.json()
        return result['data']['access_token']
    except requests.RequestException as e:
        print(f"获取访问令牌时发生错误: {e}")
        return None

def fetch_api_data(api_data, base_data):
    access_token = get_access_token(base_data)
    if not access_token:
        return None
    HEADERS["Blade-Auth"] = access_token
    try:
        res = requests.post(DATA_URL, headers=HEADERS, json=api_data)
        res.raise_for_status()
        return res.json()
    except requests.RequestException as e:
        print(f"获取API数据时发生错误: {e}")
        return None
    finally:
        HEADERS["Blade-Auth"] = ''

def process_data():
    base_info_data = {
        'tenantId': '999999',
        'clientId': '3A3885B032A98A5415ABF4D9D286DB5F',
        'clientSecret': '62F45543C8BA2281582FDDAE0FC6D007',
        'grantType': 'api'
    }
    base_workload_data = {
        'tenantId': '999999',
        'clientId': '9BA6D5BEF1215F455D676C8233002D4E',
        'clientSecret': '926B96F45F2EEB96DDEDC1C5B3A2191D',
        'grantType': 'api'
    }
    api_base_data = {
        'cfgName': '数字航道武汉测绘基本信息及成果资料to武汉局'
    }
    api_workload_data = {
        'cfgName': '数字航道武汉测绘工作量数据to武汉局'
    }

    rep1 = fetch_api_data(api_base_data, base_info_data)
    rep2 = fetch_api_data(api_workload_data, base_workload_data)

    if not rep1 or not rep2:
        print("API数据获取失败")
        return

    data_list = rep1.get('data', {}).get('data', [])
    workload_data_list = rep2.get('data', {}).get('data', [])

    # 数据过滤与分类
    classified_data = classify_data(data_list)
    update_classified_data(classified_data, workload_data_list)
    filtered_data_by_area = filter_data_by_area(classified_data)
    insert_data_to_db(filtered_data_by_area)

def classify_data(data_list):
    filtered_data = [row for row in data_list if row.get('XDDW_ID') == '0105' and row.get('CGTJSJ') is not None]
    classified_data = {key: [] for key in ['010512', '010513', '010514', '010511', '010515', '010517', '010516', '010518', '01051107', '01051607']}

    for row in filtered_data:
        ZXDW_ID = row.get('ZXDW_ID')
        if ZXDW_ID in classified_data:
            classified_data[ZXDW_ID].append(row)
    
    return classified_data

def update_classified_data(classified_data, workload_data_list):
    for area_rows in classified_data.values():
        for row in area_rows:
            row_id = row.get('ID')
            match_count = 0
            hsmj_values = []

            for b_row in workload_data_list:
                if b_row.get('CHRW_ID') == row_id:
                    match_count += 1
                    hsmj_value = b_row.get('HSMJ')
                    if hsmj_value is not None:
                        hsmj_values.append(hsmj_value)

            row['RWZJ'] = match_count
            row['HSMJ'] = hsmj_values if hsmj_values else row.get('HSMJ', [])

def filter_data_by_area(classified_data):
    filtered_data_by_area = {key: [] for key in classified_data.keys()}

    for area, rows in classified_data.items():
        for row in rows:
            if "XDSJ" in row and row["XDSJ"] is not None and row["XDSJ"].year >= 2023:
                area = row["SSJG_ID"]
                if area in filtered_data_by_area:
                    filtered_data_by_area[area].append(row)
    
    add_computed_fields(filtered_data_by_area)
    return filtered_data_by_area

def add_computed_fields(filtered_data_by_area):
    for rows in filtered_data_by_area.values():
        for row in rows:
            date_fields = ["CJSJ", "GXSJ", "KGRQ", "CGTJRQ", "XDSJ", "CGTJSJ", "CGWYKS", "CGWYJS"]
            for field in date_fields:
                if field in row and row[field] is not None:
                    row[field] = datetime.strptime(row[field][:10], "%Y-%m-%d").date()

            if "HSMJ" in row:
                hsmj_values = row["HSMJ"]
                row["HSMJZJ"] = max(sum(hsmj_values), 8) if isinstance(hsmj_values, list) else max(float(hsmj_values), 8)

            if "CGWYKS" in row and "CGWYJS" in row:
                row["WY-DAYS"] = (row["CGWYJS"] - row["CGWYKS"]).days + 1
            if "CGTJSJ" in row and "CGWYJS" in row:
                row["NY-DAYS"] = (row["CGTJSJ"] - row["CGWYJS"]).days + 1

            if "HSMJZJ" in row:
                if "WY-DAYS" in row:
                    row["WY-analysis"] = row["HSMJZJ"] / row["WY-DAYS"]
                if "NY-DAYS" in row:
                    row["NY-analysis"] = row["HSMJZJ"] / row["NY-DAYS"]

def insert_data_to_db(filtered_data_by_area):
    current_time = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
    try:
        connection = pymysql.connect(**DB_CONFIG)
        with connection.cursor() as cursor:
            setup_database(cursor)
            insert_analysis_data(cursor, filtered_data_by_area, 'wy_analysis', 'WY-analysis', current_time)
            insert_analysis_data(cursor, filtered_data_by_area, 'ny_analysis', 'NY-analysis', current_time)
        connection.commit()
    except pymysql.MySQLError as e:
        print(f"数据库操作错误: {e}")
    finally:
        connection.close()

def setup_database(cursor):
    for table in ['wy_analysis', 'ny_analysis']:
        cursor.execute(f"DROP TABLE IF EXISTS {table};")
        cursor.execute(f"""
            CREATE TABLE IF NOT EXISTS {table} (
                id INT AUTO_INCREMENT PRIMARY KEY,
                area VARCHAR(50),
                excellent_count INT,
                good_count INT,
                average_count INT,
                poor_count INT,
                updated_at DATETIME
            );
        """)
        print(f"Table {table} has been created.")

def insert_analysis_data(cursor, data, table, analysis_field, current_time):
    for area, rows in data.items():
        excellent_count = sum(1 for row in rows if row.get(analysis_field, 0) > 50)
        good_count = sum(1 for row in rows if 30 < row.get(analysis_field, 0) <= 50)
        average_count = sum(1 for row in rows if 10 < row.get(analysis_field, 0) <= 30)
        poor_count = sum(1 for row in rows if row.get(analysis_field, 0) <= 10)

        cursor.execute(f"""
            INSERT INTO {table} (area, excellent_count, good_count, average_count, poor_count, updated_at)
            VALUES (%s, %s, %s, %s, %s, %s);
        """, (area, excellent_count, good_count, average_count, poor_count, current_time))
        print(f"Data inserted into {table} for area {area}.")

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/api/wy_analysis")
def wy_analysis():
    return jsonify(fetch_analysis_data('wy_analysis'))

@app.route("/api/ny_analysis")
def ny_analysis():
    return jsonify(fetch_analysis_data('ny_analysis'))

def fetch_analysis_data(table):
    try:
        connection = pymysql.connect(**DB_CONFIG)
        with connection.cursor() as cursor:
            cursor.execute(f"SELECT * FROM {table}")
            result = cursor.fetchall()
            return result
    except pymysql.MySQLError as e:
        print(f"数据库查询错误: {e}")
        return []
    finally:
        connection.close()

def run_flask():
    app.run(host=HOST, port=PORT)

def open_webview():
    webview.create_window(APP_TITLE, f"{HOST}:{PORT}")
    webview.start(func=lambda: stop_event.set())

if __name__ == "__main__":
    flask_thread = Thread(target=run_flask)
    flask_thread.daemon = True
    flask_thread.start()

    open_webview()
    stop_event.set()

  
   
    