from flask import Flask,render_template,request,jsonify
from threading import Timer,Thread,Event
import webview
import time
import requests
from requests import utils
import json
from datetime import datetime,timedelta
from itertools import groupby
import pymysql

def data_logic_proccs():
    login_url = 'http://172.18.100.216/api/blade-auth/ext/api/api/oauth/token/'
    url = 'http://172.18.100.216/api/datacenter/dataapiCfg/dc/getDataByConfigApi'

    headers = {
        'User-Agent':'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/114.0.5735.289 Safari/537.36',
        'Connection':'keep-alive',
        'Authorization':'Basic c2FiZXI6c2FiZXJfc2VjcmV0',
        'Content-Type':'application/json;charset=UTF-8'
    }

    base_info_data = {
        'tenantId':'999999',
        'clientId':'3A3885B032A98A5415ABF4D9D286DB5F',
        'clientSecret':'62F45543C8BA2281582FDDAE0FC6D007',
        'grantType':'api'
    }

    base_workload_data = {
        'tenantId':'999999',
        'clientId':'9BA6D5BEF1215F455D676C8233002D4E',
        'clientSecret':'926B96F45F2EEB96DDEDC1C5B3A2191D',
        'grantType':'api'
    }

    api_base_data={
        'cfgName':'数字航道武汉测绘基本信息及成果资料to武汉局'
    }

    api_workload_data={
        'cfgName': '数字航道武汉测绘工作量数据to武汉局'
    }

    def api_res(login_url,url,headers,api_data,base_data): ##可以添加file_str参数
        res = requests.post(login_url, headers=headers, json=base_data)
        print(res.text)
        result = json.loads(res.text)
        access_token = result['data']['access_token']
        print(access_token)
        headers["Blade-Auth"] = access_token
        res_api = requests.post(url, headers=headers, json=api_data)
        rep = res_api.json()
        print(type(rep))
        headers["Blade-Auth"] = ''
        return rep

    rep1 = api_res(login_url=login_url,url=url,headers=headers,base_data=base_info_data,api_data=api_base_data)
    rep2 = api_res(login_url=login_url,url=url,headers=headers,base_data=base_workload_data,api_data=api_workload_data)


    try:
        data_list = rep1.get('data', {}).get('data', [])
    except json.JSONDecodeError as e:
        print("JSON 解析错误:", e)
        data_list = []

    filtered_data = []
    for row in data_list:
        if isinstance(row, dict) and row.get('XDDW_ID') == '0105' and row.get('CGTJSJ') is not None:
            filtered_data.append(row)

    
    classified_data = {'010512': [],'010513': [],'010514': [],'010511': [],'010515': [],
                       '010517': [],'010516': [],'010518': [],'01051107':[],'01051607':[]}

    
    for row in filtered_data:
        ZXDW_ID = row.get('ZXDW_ID')
        if ZXDW_ID in classified_data:
            classified_data[ZXDW_ID].append(row)


    try:
        data_list = rep2.get('data', {}).get('data', [])
    except json.JSONDecodeError as e:
        print("JSON 解析错误:", e)
        data_list = []

    # 遍历 classified_data 中的每个地区的数据列表
    for area_rows in classified_data.values():
        # 遍历每个地区的行数据
        for row in area_rows:
            # 获取当前行的 ID
            row_id = row.get('ID')

            #初始化匹配计数和hsmj值列表
            match_count = 0
            hsmj_values = []
            # 在 B.json 中查找与当前行 ID 匹配的数据
            for b_row in data_list:
                if b_row.get('CHRW_ID') == row_id:
                    # 匹配到了，增加匹配计数
                    match_count += 1

                    # 将 B.json 中的 HSMJ 值添加到当前行中
                    hsmj_value = b_row.get('HSMJ')
                    if hsmj_value is not None:
                        hsmj_values.append(hsmj_value)
            row['RWZJ'] = match_count

            #检查hsmj_values是否非空
            if hsmj_values:
                if 'HSMJ' in row:
                    row['HSMJ'].extend(hsmj_values)
                else:
                    row['HSMJ'] = hsmj_values
    #字符串转日期
    for area_rows in classified_data.values():
        for row in area_rows:
           
            date_fields = ["CJSJ", "GXSJ", "KGRQ", "CGTJRQ", "XDSJ", "CGTJSJ", "CGWYKS", "CGWYJS"]
            for field in date_fields:
                if field in row and row[field] is not None:
                    # 截取日期部分并转换为日期对象
                    row[field] = datetime.strptime(row[field][:10], "%Y-%m-%d").date()

            # 转浮点
            if "HSMJ" in row and row["HSMJ"] is not None:
                hsmj_values = row["HSMJ"]
                if isinstance(hsmj_values, list):
                    # 将字符串数组中的每个字符串转换为浮点数
                    hsmj_float_values = [float(value) for value in hsmj_values]
                    row["HSMJ"] = hsmj_float_values
                else:
                    # 如果是单个字符串，则直接转换为浮点数
                    row["HSMJ"] = float(hsmj_values)
    filtered_data_by_area = {'010512': [], '010513': [], '010514': [], '010511': [], '010515': [],
                             '010517': [], '010516': [], '010518': [], '01051107': [], '01051607': []}

    for area_rows in classified_data.values():
        for row in area_rows:
            if "XDSJ" in row and row["XDSJ"] is not None and row["XDSJ"].year >= 2023:
                area = row["SSJG_ID"]  # 获取地区信息
                if area in filtered_data_by_area:
                    filtered_data_by_area[area].append(row)

    # 在筛选后的数据中添加 "HSMJZJ" 字段
    for area, rows in filtered_data_by_area.items():
        for row in rows:
            hsmj_values = row["HSMJ"]
            if isinstance(hsmj_values, list):
                # 计算 "HSMJ" 数组中的数字总和
                hsmj_sum = sum(hsmj_values)
                # 如果总和小于等于 8，则将其值设为 8
                row["HSMJZJ"] = max(hsmj_sum, 8)
            else:
                # 如果 "HSMJ" 不是数组，则将其值转换为浮点数，并设为 "HSMJZJ"
                row["HSMJZJ"] = max(float(hsmj_values), 8)

            # 添加字段 "WY-DAYS" 和 "NY-DAYS"
            if "CGWYKS" in row and row["CGWYKS"] is not None and "CGWYJS" in row and row["CGWYJS"] is not None:
                row["WY-DAYS"] = (row["CGWYJS"] - row["CGWYKS"]).days + 1
            if "CGTJSJ" in row and row["CGTJSJ"] is not None and "CGWYJS" in row and row["CGWYJS"] is not None:
                row["NY-DAYS"] = (row["CGTJSJ"] - row["CGWYJS"]).days + 1

            # 添加字段 "WY-analysis" 和 "NY-analysis"
            if "HSMJZJ" in row and row["HSMJZJ"] is not None and "WY-DAYS" in row and row["WY-DAYS"] is not None:
                row["WY-analysis"] = row["HSMJZJ"] / row["WY-DAYS"]
            if "HSMJZJ" in row and row["HSMJZJ"] is not None and "NY-DAYS" in row and row["NY-DAYS"] is not None:
                row["NY-analysis"] = row["HSMJZJ"] / row["NY-DAYS"]

    # 数据库连接配置
    db_config = {
        'host': 'localhost',
        'user': 'root',
        'password': '123456',
        'database': '数字航道质量评估结果',
        'port': 3306
    }

    # 连接到数据库
    connection = pymysql.connect(**db_config)
    cursor = connection.cursor()  
    # 获取当前时间
    current_time = datetime.now().strftime('%Y-%m-%d %H:%M:%S')

    # 使用INFORMATION_SCHEMA.TABLES来检查表是否存在  
    sql_check = """  
    SELECT TABLE_NAME   
    FROM INFORMATION_SCHEMA.TABLES   
    WHERE TABLE_SCHEMA = %s AND TABLE_NAME = %s;  
    """  
    cursor.execute(sql_check, (db_config['database'], 'wy_analysis'))  
    result_wy = cursor.fetchone()  
          
    # 如果表存在，则删除它  
    if result_wy:  
        sql_drop = "DROP TABLE IF EXISTS wy_analysis;"  
        cursor.execute(sql_drop)  
        print("Table data_analysis existed and has been dropped.")  
          
        # 创建表  
    sql_create_wy = """  
        CREATE TABLE IF NOT EXISTS wy_analysis (  
        id INT AUTO_INCREMENT PRIMARY KEY,  
        area VARCHAR(50),  
        excellent_count INT,  
        good_count INT,  
        average_count INT,  
        poor_count INT,  
        updated_at DATETIME  
        );  
           """  
    cursor.execute(sql_create_wy)  
    print("Table wy_analysis has been created.")  
            
        # 提交事务  
    connection.commit()      
    
    # 初始化存储优质数据数量的数组
    i_excellent_data = []
    i_good_data = []
    i_average_data = []
    i_poor_data = []

    # 修改部分
    # 遍历 filtered_data_by_area 字典的键值对
    for area, rows in filtered_data_by_area.items():
        excellent_count = 0
        good_count = 0
        average_count = 0
        poor_count = 0
        for row in rows:
            # 在筛选后的数据中计算不同等级数据的数量
            wy_analysis = row["WY-analysis"]
            if wy_analysis >= 8:
                excellent_count += 1
            elif wy_analysis >= 4:
                good_count += 1
            elif wy_analysis >= 2:
                average_count += 1
            else:
                poor_count += 1
        # 将每个地区的数据数量添加到相应的数组中
        i_excellent_data.append(excellent_count)
        i_good_data.append(good_count)
        i_average_data.append(average_count)
        i_poor_data.append(poor_count)
        # 将数据插入数据库
        sql = """
        INSERT INTO wy_analysis (area, excellent_count, good_count, average_count, poor_count, updated_at)
        VALUES (%s, %s, %s, %s, %s, %s)
        """
        cursor.execute(sql, (area, excellent_count, good_count, average_count, poor_count, current_time))
    connection.commit()

    # 使用INFORMATION_SCHEMA.TABLES来检查表是否存在  
    sql_check = """  
    SELECT TABLE_NAME   
    FROM INFORMATION_SCHEMA.TABLES   
    WHERE TABLE_SCHEMA = %s AND TABLE_NAME = %s;  
    """  
    cursor.execute(sql_check, (db_config['database'], 'ny_analysis'))  
    result_ny = cursor.fetchone()  
          
    # 如果表存在，则删除它  
    if result_ny:  
        sql_drop = "DROP TABLE IF EXISTS ny_analysis;"  
        cursor.execute(sql_drop)  
        print("Table data_analysis existed and has been dropped.")  
          
        # 创建表  
    sql_create_ny = """  
        CREATE TABLE IF NOT EXISTS ny_analysis (  
        id INT AUTO_INCREMENT PRIMARY KEY,  
        area VARCHAR(50),  
        excellent_count INT,  
        good_count INT,  
        average_count INT,  
        poor_count INT,  
        updated_at DATETIME  
        );  
           """  
    cursor.execute(sql_create_ny)  
    print("Table ny_analysis has been created.")  
            
        # 提交事务  
    connection.commit()

    # 初始化存储优质数据数量的数组
    f_excellent_data = []
    f_good_data = []
    f_average_data = []
    f_poor_data = []


    # 遍历 filtered_data_by_area 字典的键值对
    for area, rows in filtered_data_by_area.items():
        excellent_count = 0
        good_count = 0
        average_count = 0
        poor_count = 0
        for row in rows:
            # 在筛选后的数据中计算不同等级数据的数量
            ny_analysis = row["NY-analysis"]
            if ny_analysis >= 8:
                excellent_count += 1
            elif ny_analysis >= 4:
                good_count += 1
            elif ny_analysis >= 2:
                average_count += 1
            else:
                poor_count += 1
        # 将每个地区的数据数量添加到相应的数组中
        f_excellent_data.append(excellent_count)
        f_good_data.append(good_count)
        f_average_data.append(average_count)
        f_poor_data.append(poor_count)
        # 将数据插入数据库
        sql = """
        INSERT INTO ny_analysis (area, excellent_count, good_count, average_count, poor_count, updated_at)
        VALUES (%s, %s, %s, %s, %s, %s)
        """
        cursor.execute(sql, (area, excellent_count, good_count, average_count, poor_count, current_time))
    connection.commit()
    cursor.close()
    connection.close()

    #@test
    # 打印 f_excellent_data 数组
    print("f_excellent_data 数组:", f_excellent_data)
    print("f_good_data 数组:", f_good_data)
    print("f_average_data 数组:", f_average_data)
    print("f_poor_data 数组:", f_poor_data)
    print("f_excellent_data 数组:", i_excellent_data)
    print("f_good_data 数组:", i_good_data)
    print("f_average_data 数组:", i_average_data)
    print("f_poor_data 数组:", i_poor_data)


app = Flask(__name__)

app_title = "数字航道质量分析"
host = "http://127.0.0.1"
port = 5000

stop_event = Event()

def run():
    while not stop_event.is_set():
        app.run(port=port)

@app.route("/")
def index():
    # 数据库连接配置
    db_config = {
        'host': 'localhost',
        'user': 'root',
        'password': '123456',
        'database': '数字航道质量评估结果',
        'port': 3306
    }

    # 连接到数据库
    connection = pymysql.connect(**db_config)
    
    # 初始化数据数组
    i_excellent_data = []
    i_good_data = []
    i_average_data = []
    i_poor_data = []
    
    f_excellent_data = []
    f_good_data = []
    f_average_data = []
    f_poor_data = []

    try:
        with connection.cursor() as cursor:
            # 从数据库中读取数据并填充到 i_* 数据数组中
            sql_select_wy = "SELECT excellent_count, good_count, average_count, poor_count FROM wy_analysis"
            cursor.execute(sql_select_wy)
            results = cursor.fetchall()

            for row in results:
                excellent_count, good_count, average_count, poor_count = row
                i_excellent_data.append(excellent_count)
                i_good_data.append(good_count)
                i_average_data.append(average_count)
                i_poor_data.append(poor_count)

            # 从数据库中读取数据并填充到 f_* 数据数组中
            sql_select_ny = "SELECT area, excellent_count, good_count, average_count, poor_count FROM ny_analysis"
            cursor.execute(sql_select_ny)
            results = cursor.fetchall()

            for row in results:
                area, excellent_count, good_count, average_count, poor_count = row
                f_excellent_data.append(excellent_count)
                f_good_data.append(good_count)
                f_average_data.append(average_count)
                f_poor_data.append(poor_count)

    finally:
        connection.close()

    # 打印从数据库中读取的数据
    print("从数据库中读取的 i_excellent_data 数组:", i_excellent_data)
    print("从数据库中读取的 i_good_data 数组:", i_good_data)
    print("从数据库中读取的 i_average_data 数组:", i_average_data)
    print("从数据库中读取的 i_poor_data 数组:", i_poor_data)
    print("从数据库中读取的 f_excellent_data 数组:", f_excellent_data)
    print("从数据库中读取的 f_good_data 数组:", f_good_data)
    print("从数据库中读取的 f_average_data 数组:", f_average_data)
    print("从数据库中读取的 f_poor_data 数组:", f_poor_data)

    return render_template("index.html",
                           f_excellent_data=f_excellent_data,
                           f_good_data=f_good_data,
                           f_average_data=f_average_data,
                           f_poor_data=f_poor_data,
                           i_excellent_data=i_excellent_data,
                           i_good_data=i_good_data,
                           i_average_data=i_average_data,
                           i_poor_data=i_poor_data)

if __name__ == '__main__':
    t = Thread(target=run)
    t.daemon = True
    t.start()

    webview.create_window(
        app_title,
        f"{host}:{port}",
        resizable=False,
        height=1000,
        width=1980
    )

    webview.start()
  
   
    