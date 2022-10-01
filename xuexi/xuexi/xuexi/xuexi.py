import requests
import json
import re
from lxpy import copy_headers_dict
import time


url = 'https://xxt.cxfww.cn:9090/api/client/courseware/time'
headers = """
Host: xxt.cxfww.cn:9090
Connection: keep-alive
Content-Length: 25
sec-ch-ua: "Google Chrome";v="105", "Not)A;Brand";v="8", "Chromium";v="105"
Accept: application/json, text/plain, */*
User-Access-Token: 0p4peF6mTRP9NEaaLLdF03vug76Z0EqeP4eG
sec-ch-ua-mobile: ?0
Content-Type: application/json;charset=UTF-8
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/105.0.0.0 Safari/537.36
sec-ch-ua-platform: "Windows"
Origin: https://xxt.cxfww.cn:9090
Sec-Fetch-Site: same-origin
Sec-Fetch-Mode: cors
Sec-Fetch-Dest: empty
Referer: https://xxt.cxfww.cn:9090/home2?count&cover&createTime=1661577743000&dataFileName=2022%2F0827%2F7342417610.mp4&dir=2&dirId=rR6fwq3ZBkohGk1B&dirName=%E7%BD%91%E7%BB%9C%E5%AE%89%E5%85%A8%E6%84%8F%E8%AF%86%E5%AE%A3%E4%BC%A0%E8%A7%86%E9%A2%91&enable=true&id=r2BKrW3ZBkoIHL2f&length&name=10-%E7%BD%91%E7%BB%9C%E6%8A%95%E7%A5%A8%E4%B8%8E%E4%B8%AA%E4%BA%BA%E4%BF%A1%E6%81%AF%E4%BF%9D%E6%8A%A4&orgName&orgs&processFileName=2022%2F0827%2F7342417610%2F7342417610.m3u8&recordId=21884098&size=20131161&sourceFileName=10-%E7%BD%91%E7%BB%9C%E6%8A%95%E7%A5%A8%E4%B8%8E%E4%B8%AA%E4%BA%BA%E4%BF%A1%E6%81%AF%E4%BF%9D%E6%8A%A4.mp4&suffix=mp4&type=3
Accept-Encoding: gzip, deflate, br
Accept-Language: zh-CN,zh;q=0.9,en;q=0.8
"""
headers = copy_headers_dict(headers)
data = {"id":"r2BKrW3ZBkoIHL2f"}
data = json.dumps(data)
for x in range(1,100000):
    req = requests.post(url,headers=headers,data=data)
    print(req.text)
    time.sleep(1)
