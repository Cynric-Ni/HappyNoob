
import urllib.request

import requests

from bs4 import BeautifulSoup

import urllib.parse

import smtplib

from email.mime.text import MIMEText

from email.header import Header

import json

import datetime

from time import strftime, localtime

import re

import xlwt

cookie_str=r'Hm_lvt_421a98029ee1737df6d51923f48767b0=1586613569,1587829077,1588784211; bdshare_firstime=1588784243754; Hm_lpvt_421a98029ee1737df6d51923f48767b0=1588785286'

cookies = {}

for line in cookie_str.split(';'):

    key, value = line.split('=', 1)

    cookies[key] = value


def get_one_page(url):

  headers = {

    'User-Agent':'Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/64.0.3282.140 Safari/537.36'

}

  response = requests.get(url,headers=headers,cookies = cookies)


  if response.status_code == 200:

     return response.text

  else:

     print('无数据')

def parse_one_page(html):

    soup = BeautifulSoup(html,'html.parser')

    i = 0

    for item in soup.select('tr')[1:8]:



      yield{

         'time':item.select('td')[i].text,

         'yiBin':item.select('td')[i+1].text,

         'jiangAn':item.select('td')[i+2].text,

         'luZhou':item.select('td')[i+3].text,

         'beiPei':item.select('td')[i+4].text,

         'chongQing':item.select('td')[i+5].text,

         'cunTan':item.select('td')[i+6].text,
 
         'qingXichang':item.select('td')[i+7].text,

         'wanXian':item.select('td')[i+8].text,

         'maoPin':item.select('td')[i+9].text,

         'yiChang':item.select('td')[i+10].text,

         'zhiJiang':item.select('td')[i+11].text,

         'shaShi':item.select('td')[i+12].text,

         'jianLi':item.select('td')[i+13].text,

         'chenLinJi':item.select('td')[i+14].text,

         'hanKou':item.select('td')[i+15].text,

         'huangShi':item.select('td')[i+16].text,

         'jiuJiang':item.select('td')[i+17].text,

         'anQin':item.select('td')[i+18].text,

         'wuHu':item.select('td')[i+19].text,

         'nanJin':item.select('td')[i+20].text,

         'zhengJiang':item.select('td')[i+21].text,

         'changSha':item.select('td')[i+22].text,

         'sanXia':item.select('td')[i+23].text,

         'sanXiaOut':item.select('td')[i+24].text,

         'geZhouBa':item.select('td')[i+25].text,

         'yiChangLiuLiang':item.select('td')[i+26].text,

         'XJB_In':item.select('td')[i+27].text,

         'XJB_Out':item.select('td')[i+28].text,

         'daTong':item.select('td')[i+29].text
    }

def write_to_excel():

    f = xlwt.Workbook()                             

    sheet1 = f.add_sheet('waterLevel',cell_overwrite_ok=True)

    row0 = ["日期","宜宾","江安","泸州：二郎滩","北碚","重庆","寸滩","涪陵：清溪场","万县","茅坪","宜昌","枝江","沙市","监理","城陵矶","汉口","黄石","九江","安庆","芜湖","南京","镇江","湘江：长沙","三峡入库","三峡出库","葛洲坝出库","宜昌流量","向家坝入库","向家坝出库","大通流量"]

#写入第一行

    for j in range(0,len(row0)):

       sheet1.write(0,j,row0[j])


   #依次爬取每一页内容的每一期信息，并将其依次写入Excel

       i=0

       for k in range(1,2):

           url = 'http://www.cjhdj.com.cn/CjhdjManage/water/allwaterList.jsp' 

           html = get_one_page(url)

           print('正在保存第%d页。'%k)

         #写入每一期的信息

           for item in parse_one_page(html):

               sheet1.write(i+1,0,item['time'])

               sheet1.write(i+1,1,item['yiBin'])

               sheet1.write(i+1,2,item['jiangAn'])

               sheet1.write(i+1,3,item['luZhou'])

               sheet1.write(i+1,4,item['beiPei'])

               sheet1.write(i+1,5,item['chongQing'])

               sheet1.write(i+1,6,item['cunTan'])

               sheet1.write(i+1,7,item['qingXichang'])

               sheet1.write(i+1,8,item['wanXian'])

               sheet1.write(i+1,9,item['maoPin'])

               sheet1.write(i+1,10,item['yiChang'])

               sheet1.write(i+1,11,item['zhiJiang'])

               sheet1.write(i+1,12,item['shaShi'])

               sheet1.write(i+1,13,item['jianLi'])

               sheet1.write(i+1,14,item['chenLinJi'])

               sheet1.write(i+1,15,item['hanKou'])

               sheet1.write(i+1,16,item['huangShi'])

               sheet1.write(i+1,17,item['jiuJiang'])

               sheet1.write(i+1,18,item['anQin'])

               sheet1.write(i+1,19,item['wuHu'])

               sheet1.write(i+1,20,item['nanJin'])

               sheet1.write(i+1,21,item['zhengJiang'])

               sheet1.write(i+1,22,item['changSha'])

               sheet1.write(i+1,23,item['sanXia'])

               sheet1.write(i+1,24,item['sanXiaOut'])

               sheet1.write(i+1,25,item['geZhouBa'])

               sheet1.write(i+1,26,item['yiChangLiuLiang'])

               sheet1.write(i+1,27,item['XJB_In'])

               sheet1.write(i+1,28,item['XJB_Out'])

               sheet1.write(i+1,29,item['daTong'])

               i+=1



           f.save('waterLevel.xls')



write_to_excel()

