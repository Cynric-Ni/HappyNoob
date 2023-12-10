# This is a sample Python script.

# Press Shift+F10 to execute it or replace it with your code.
# Press Double Shift to search everywhere for classes, files, tool windows, actions, and settings.

import requests
from requests import utils
from selenium.webdriver import Chrome
from selenium import webdriver
import json
from datetime import datetime,timedelta
from itertools import groupby

def print_hi(name):
    # Use a breakpoint in the code line below to debug your script.
    print(f'Hi, {name}')  # Press Ctrl+F8 to toggle the breakpoint.


# Press the green button in the gutter to run the script.
if __name__ == '__main__':

    login_url = 'https://172.18.128.153/vadmin/v_login/'
    url = 'https://172.18.128.153/vadmin/v_change_list/xt/xtlog/'
    session = requests.session()
    headers = {
        'User-Agent':'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/114.0.5735.289 Safari/537.36',
        'Connection':'keep-alive',
    }

    data = {
        'hide_data':'{"update_content":0}',
        'widget_data':'{"username":"倪忻亮","pwd":"19831022Nxl."}',
        'event_data':'{"name":""}'
    }
    data1 = {
        's--w':'1920',
        's--h':'936',
        'l-b':'操作日志',
        'v_search_v':'1',
        'xt--xtlog--search':'登陆',
        'czr_id':'18c7384239c64eadac8a72afb5a91337',
    }
    sessionResult =session.post(login_url,data=data,headers=headers,verify=False)
    print(sessionResult.cookies)
    cookie_dict = requests.utils.dict_from_cookiejar(sessionResult.cookies)
    print(cookie_dict)
    sessionGet = session.get(url=url,headers=headers,params=data1,verify=False)
    print(sessionGet.json())
    resultASdict=sessionGet.json()
    name = resultASdict['step'][0]['step_data']['widget'][3]['col_data'][1]['data'][0]['data'][5]['data'][0][2]
    print('姓名：'+name)

    login_times_str = []
    for i in range(0,20,1):
        dataTime = resultASdict['step'][0]['step_data']['widget'][3]['col_data'][1]['data'][0]['data'][5]['data'][i][4]
        login_times_str.append(dataTime)
    print(login_times_str)
    # 将日期时间字符串转换为 datetime 对象
    login_times = [datetime.strptime(time_str, "%Y-%m-%d %H:%M:%S") for time_str in login_times_str]
    print(type(login_times))
    # 初始化变量
    login_statistics = {}

    # 遍历登录时间
    for login_time in login_times:
        date_key = login_time.date()

        # 如果日期键不存在，初始化登录统计
        if date_key not in login_statistics:
            login_statistics[date_key] = {'count': 1, 'first_login_time': login_time}
        else:
            # 计算时间间隔
            time_diff = login_time - login_statistics[date_key]['first_login_time']

            # 如果时间间隔大于等于8小时，认为是新的一天的第一次登录
            if time_diff <= timedelta(hours=-8):
                login_statistics[date_key]['count'] += 1
                login_statistics[date_key]['first_login_time'] = login_time

    # 打印每一天的登录统计数
    for date, stats in login_statistics.items():
        print(f"日期 {date}: 有效登录次数 {stats['count']}")

#     grouped_login_times = {date: list(group) for date, group in groupby(login_times, key=lambda x: x.date())}
#
#     # 初始化变量
#     valid_logins = 0
#
#     # 遍历每一天的登录时间
#     for date, times in grouped_login_times.items():
#         times.sort()  # 排序每一天的登录时间
#         last_login_time = None
#
#     # 遍历每一天的登录时间
#     for login_time in times:
#         # 如果是第一次登录或者距离上次登录超过8小时，认为是有效登录
#         if last_login_time is None or (login_time - last_login_time) >= timedelta(hours=8):
#             valid_logins += 1
#             last_login_time = login_time
#
# # 打印有效登录次数
# print("有效登录次数:", valid_logins)

   # print(resultASpy)
    #options = webdriver.ChromeOptions()
    #options.add_experimental_option('detach',True) #禁止chrom浏览器自己关闭（解决闪退问题），不明白的话可以把这段代码复制百度。
    #web = Chrome(options=options)
    #web.get(test_url)

# See PyCharm help at https://www.jetbrains.com/help/pycharm/
