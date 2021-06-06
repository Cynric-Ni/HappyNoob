import requests

from bs4 import BeautifulSoup

import xlwt

import time,sched

import sys

import io

import itchat

import threading


itchat.auto_login()

#users = itchat.search_friends(name = U'鱼儿')
rooms = itchat.search_chatrooms(name = U'135vip')


#####################以下开始监视75秒时时彩############### 

cookie_str = r'm_200000055_pid=889; m_sid=250659-033ebff9cc4c92ad710ea84763b7; m_last_login=1549704953'


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

    soup = BeautifulSoup(html, 'lxml')

    i = 0

    for item in soup.select('tr')[1:-1]:

 
      yield{

        'issue':item.select('td')[i].text,

        'time':item.select('td')[i+1].text,

        'ww':item.select('td')[i+2].text,

        'qw':item.select('td')[i+3].text,

        'bw':item.select('td ')[i+4].text,

        'sw':item.select('td')[i+5].text,

        'gw':item.select('td')[i+6].text,

        'zh':item.select('td')[i+7].text,

        'dx':item.select('td')[i+8].text,

        'ds':item.select('td')[i+9].text

         }

def write_to_excel():

  f = xlwt.Workbook()                             

  sheet1 = f.add_sheet('超级时时彩',cell_overwrite_ok=True)

  row0 = ["期数","开奖时间","万位数","千位数","百位数","十位数","个位","总和","总和单双","总和大小"]

#写入第一行

  for j in range(0,len(row0)):

      sheet1.write(0,j,row0[j])



#依次爬取每一页内容的每一期信息，并将其依次写入Excel

  i = 0

  for k in range(1,2):

      url = 'http://qrcode.135vip.cc/pc.php?c=pc&a=dresult&lottery=cjssc'

      html = get_one_page(url)

      print('正在保存超级时时彩第%d页。'%k)

      #写入每一期的信息

      ww = [0]
      qw = [0]
      bw = [0]
      sw = [0]
      gw = [0]
      zh = [0]
   
      for item in parse_one_page(html):

          sheet1.write(i+1,0,item['issue'])

          sheet1.write(i+1,1,item['time'])

          sheet1.write(i+1,2,int(item['ww']))

          sheet1.write(i+1,3,int(item['qw']))

          sheet1.write(i+1,4,int(item['bw']))

          sheet1.write(i+1,5,int(item['sw']))

          sheet1.write(i+1,6,int(item['gw']))

          sheet1.write(i+1,7,int(item['zh']))

          sheet1.write(i+1,8,item['ds'])

          sheet1.write(i+1,9,item['dx'])

          ww.append(int(item['ww']))

          qw.append(int(item['qw']))

          bw.append(int(item['bw']))

          sw.append(int(item['sw']))

          gw.append(int(item['gw']))

          zh.append(int(item['zh']))

          i+=1

####总和判断大小########

  da=0

  xiao=0

  for dx_zh in zh[1:11]:

    if dx_zh>=23:

       da+=1

    else:

       break

  for dx_zh in zh[1:11]:

    if dx_zh<23:

       xiao+=1

    else:

        break
    

####总和判断单双########

  dan=0

  shuang=0

  for ds_zh in zh[1:11]:

    if ds_zh%2==0:

       shuang+=1

    else:

       break

  for ds_zh in zh[1:11]:

      if ds_zh%2==1:

         dan+=1

      else:

        break



#######判断万位单双#############

  ww_d=0

  ww_s=0

  for r_ww in ww[1:11]:

    if r_ww%2==0:

        ww_s+=1

    else:

     break

  for r_ww in ww[1:11]:

    if r_ww%2==1:

       ww_d+=1
    else:

     break

#######判断万位大小#############

  ww_da=0

  ww_xiao=0

  for r_ww in ww[1:11]:

    if r_ww>=5:

        ww_da+=1

    else:

     break

  for r_ww in ww[1:11]:

    if r_ww<5:

       ww_xiao+=1
    else:

     break
  
#######判断千位单双#############

  qw_d=0

  qw_s=0

  for r_qw in qw[1:11]:

    if r_qw%2==0:

        qw_s+=1

    else:

     break

  for r_qw in qw[1:11]:

    if r_qw%2==1:

       qw_d+=1
    else:

     break

#######判断千位大小#############

  qw_da=0

  qw_xiao=0

  for r_qw in qw[1:11]:

    if r_qw>=5:

        qw_da+=1

    else:

     break

  for r_qw in qw[1:11]:

    if r_qw<5:

       qw_xiao+=1
    else:

     break
  

#######判断百位单双#############

  bw_d=0

  bw_s=0

  for r_bw in bw[1:11]:

    if r_bw%2==0:

        bw_s+=1

    else:

     break

  for r_bw in bw[1:11]:

    if r_bw%2==1:

       bw_d+=1
    else:

     break

#######判断百位大小#############

  bw_da=0

  bw_xiao=0

  for r_bw in bw[1:11]:

    if r_bw>=5:

        bw_da+=1

    else:

     break

  for r_bw in bw[1:11]:

    if r_bw<5:

       bw_xiao+=1
    else:

     break


#######判断十位单双#############

  sw_d=0

  sw_s=0

  for r_sw in bw[1:11]:

    if r_sw%2==0:

        sw_s+=1

    else:

     break

  for r_sw in bw[1:11]:

    if r_sw%2==1:

       sw_d+=1
    else:

     break


#######判断十位大小#############

  sw_da=0

  sw_xiao=0

  for r_sw in sw[1:11]:

    if r_sw>=5:

        sw_da+=1

    else:

     break

  for r_sw in sw[1:11]:

    if r_sw<5:

       sw_xiao+=1
    else:

     break

#######判断个位单双#############

  gw_d=0

  gw_s=0

  for r_gw in bw[1:11]:

    if r_gw%2==0:

        sw_s+=1

    else:

     break

  for r_gw in gw[1:11]:

    if r_gw%2==1:

       gw_d+=1
    else:

     break

#######判断个位大小#############

  gw_da=0

  gw_xiao=0

  for r_gw in gw[1:11]:

    if r_gw>=5:

        gw_da+=1

    else:

     break

  for r_gw in gw[1:11]:

    if r_gw<5:

       gw_xiao+=1

    else:

     break


  ls = 4

  if da>=ls:

    #itchat.send('超级时时彩-总和-大-超过4连~',toUserName=users[0]['UserName'])

    itchat.send('超级时时彩-总和-大-超过4连~',toUserName=rooms[0]['UserName'])

  if xiao>=ls:

    #itchat.send('超级时时彩-总和-小-超过4连~',toUserName=users[0]['UserName'])

    itchat.send('超级时时彩-总和-小-超过4连~',toUserName=rooms[0]['UserName'])    

  if dan>=ls:
      
     #itchat.send('超级时时彩-总和-单-超过4连~',toUserName=users[0]['UserName'])
   
     itchat.send('超级时时彩-总和-单-超过4连~',toUserName=rooms[0]['UserName'])

  if shuang>=ls:
      
     #itchat.send('超级时时彩-总和-双-超过4连~',toUserName=users[0]['UserName'])

     itchat.send('超级时时彩-总和-双-超过4连~',toUserName=rooms[0]['UserName'])

  if ww_d>=ls:

    #itchat.send('超级时时彩-万位-单-超过4连~',toUserName=users[0]['UserName'])

    itchat.send('超级时时彩-万位-单-超过4连~',toUserName=rooms[0]['UserName'])

  if ww_s>=ls:

    #itchat.send('超级时时彩-万位-双-超过4连~',toUserName=users[0]['UserName'])

    itchat.send('超级时时彩-万位-双-超过4连~',toUserName=rooms[0]['UserName'])

  if ww_da>=ls:

    #itchat.send('超级时时彩-万位-大-超过4连~',toUserName=users[0]['UserName'])

    itchat.send('超级时时彩-万位-大-超过4连~',toUserName=rooms[0]['UserName'])

  if ww_xiao>=ls:

   #itchat.send('超级时时彩-万位-小-超过4连~',toUserName=users[0]['UserName'])

   itchat.send('超级时时彩-万位-小-超过4连~',toUserName=rooms[0]['UserName'])

  if qw_d>=ls:

    #itchat.send('超级时时彩-千位-单-超过4连~',toUserName=users[0]['UserName'])

    itchat.send('超级时时彩-千位-单-超过4连~',toUserName=rooms[0]['UserName'])

  if qw_s>=ls:

    #itchat.send('超级时时彩-千位-双-超过4连~',toUserName=users[0]['UserName'])

    itchat.send('超级时时彩-千位-双-超过4连~',toUserName=rooms[0]['UserName'])

  if qw_da>=ls:

    #itchat.send('超级时时彩-千位-大-超过4连~',toUserName=users[0]['UserName'])

    itchat.send('超级时时彩-千位-大-超过4连~',toUserName=rooms[0]['UserName'])

  if qw_xiao>=ls:

    #itchat.send('超级时时彩-千位-小-超过4连~',toUserName=users[0]['UserName'])

    itchat.send('超级时时彩-千位-小-超过4连~',toUserName=rooms[0]['UserName'])

  if bw_d>=ls:

    #itchat.send('超级时时彩-百位-单-超过4连~',toUserName=users[0]['UserName'])

    itchat.send('超级时时彩-百位-单-超过4连~',toUserName=rooms[0]['UserName'])

  if bw_s>=ls:

    #itchat.send('超级时时彩-百位-双-超过4连~',toUserName=users[0]['UserName'])

    itchat.send('超级时时彩-百位-双-超过4连~',toUserName=rooms[0]['UserName'])

  if bw_da>=ls:

    #itchat.send('超级时时彩-百位-大-超过4连~',toUserName=users[0]['UserName'])

    itchat.send('超级时时彩-百位-大-超过4连~',toUserName=rooms[0]['UserName'])

  if bw_xiao>=ls:

    #itchat.send('超级时时彩-百位-小-超过4连~',toUserName=users[0]['UserName'])

    itchat.send('超级时时彩-百位-小-超过4连~',toUserName=rooms[0]['UserName'])

  if gw_d>=ls:

    #itchat.send('超级时时彩-个位-单-超过4连~',toUserName=users[0]['UserName'])

    itchat.send('超级时时彩-个位-单-超过4连~',toUserName=rooms[0]['UserName'])

  if gw_s>=ls:

    #itchat.send('超级时时彩-个位-双-超过4连~',toUserName=users[0]['UserName'])

    itchat.send('超级时时彩-个位-双-超过4连~',toUserName=rooms[0]['UserName'])

  if gw_da>=ls:

    #itchat.send('超级时时彩-个位-大-超过4连~',toUserName=users[0]['UserName'])

    itchat.send('超级时时彩-个位-大-超过4连~',toUserName=rooms[0]['UserName'])

  if gw_xiao>=ls:

    #itchat.send('超级时时彩-个位-小-超过4连~',toUserName=users[0]['UserName'])

    itchat.send('超级时时彩-个位-小-超过4连~',toUserName=rooms[0]['UserName'])

 # S.enter(cjssc_cycle,1,write_to_excel,)
############################时时彩结束#################################
  f.save('3D.xls')

#############################重庆时时彩部分#############################

def get_cqssc_page(cqssc_url):

  headers = {

    'User-Agent':'Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/64.0.3282.140 Safari/537.36'

}

  response = requests.get(cqssc_url,headers=headers,cookies = cookies)


  if response.status_code == 200:

     return response.text

  else:

     print('无数据')


    
def parse_cqssc_page(cqssc_html):

    soup = BeautifulSoup(cqssc_html, 'lxml')

    i = 0

    for item in soup.select('tr')[1:-1]:

 
      yield{

        'issue':item.select('td')[i].text,

        'time':item.select('td')[i+1].text,

        'ww':item.select('td')[i+2].text,

        'qw':item.select('td')[i+3].text,

        'bw':item.select('td ')[i+4].text,

        'sw':item.select('td')[i+5].text,

        'gw':item.select('td')[i+6].text,

        'zh':item.select('td')[i+7].text,

        'ds':item.select('td')[i+8].text,

        'dx':item.select('td')[i+9].text

         }

def cqssc_write_to_excel():

  f = xlwt.Workbook()                             

  sheet1 = f.add_sheet('cqssc',cell_overwrite_ok=True)

  row0 = ["期数","开奖时间","万位数","千位数","百位数","十位数","个位","总和","总和单双","总和大小"]

#写入第一行

  for j in range(0,len(row0)):

      sheet1.write(0,j,row0[j])



#依次爬取每一页内容的每一期信息，并将其依次写入Excel

  i = 0

  for k in range(1,2):

      cqssc_url = 'http://qrcode.135vip.cc/pc.php?c=pc&a=dresult&lottery=cqssc'

      cqssc_html = get_cqssc_page(cqssc_url)

      print('正在保存重庆时时彩第%d页。'%k)

      #写入每一期的信息

      ww = [0]
      qw = [0]
      bw = [0]
      sw = [0]
      gw = [0]
      zh = [0]
   
      for item in parse_cqssc_page(cqssc_html):

          sheet1.write(i+1,0,item['issue'])

          sheet1.write(i+1,1,item['time'])

          sheet1.write(i+1,2,int(item['ww']))

          sheet1.write(i+1,3,int(item['qw']))

          sheet1.write(i+1,4,int(item['bw']))

          sheet1.write(i+1,5,int(item['sw']))

          sheet1.write(i+1,6,int(item['gw']))

          sheet1.write(i+1,7,int(item['zh']))

          sheet1.write(i+1,8,item['ds'])

          sheet1.write(i+1,9,item['dx'])

          ww.append(int(item['ww']))

          qw.append(int(item['qw']))

          bw.append(int(item['bw']))

          sw.append(int(item['sw']))

          gw.append(int(item['gw']))

          zh.append(int(item['zh']))

          zh.append(int(item['zh']))

          i+=1

  ####总和判断大小########

  da=0

  xiao=0

  for dx_zh in zh[1:11]:

    if dx_zh>=23:

       da+=1

    else:

       break

  for dx_zh in zh[1:11]:

    if dx_zh<23:

       xiao+=1

    else:

        break
    

####总和判断单双########

  dan=0

  shuang=0

  for ds_zh in zh[1:11]:

    if ds_zh%2==0:

       shuang+=1

    else:

       break

  for ds_zh in zh[1:11]:

      if ds_zh%2==1:

         dan+=1

      else:

        break



#######判断万位单双#############

  ww_d=0

  ww_s=0

  for r_ww in ww[1:11]:

    if r_ww%2==0:

        ww_s+=1

    else:

     break

  for r_ww in ww[1:11]:

    if r_ww%2==1:

       ww_d+=1
    else:

     break

#######判断万位大小#############

  ww_da=0

  ww_xiao=0

  for r_ww in ww[1:11]:

    if r_ww>=5:

        ww_da+=1

    else:

     break

  for r_ww in ww[1:11]:

    if r_ww<5:

       ww_xiao+=1
    else:

     break
  
#######判断千位单双#############

  qw_d=0

  qw_s=0

  for r_qw in ww[1:11]:

    if r_qw%2==0:

        qw_s+=1

    else:

     break

  for r_qw in qw[1:11]:

    if r_qw%2==1:

       qw_d+=1
    else:

     break

#######判断千位大小#############

  qw_da=0

  qw_xiao=0

  for r_qw in qw[1:11]:

    if r_qw>=5:

        qw_da+=1

    else:

     break

  for r_qw in qw[1:11]:

    if r_qw<5:

       qw_xiao+=1
    else:

     break
  

#######判断百位单双#############

  bw_d=0

  bw_s=0

  for r_bw in bw[1:11]:

    if r_bw%2==0:

        bw_s+=1

    else:

     break

  for r_bw in bw[1:11]:

    if r_bw%2==1:

       bw_d+=1
    else:

     break

#######判断百位大小#############

  bw_da=0

  bw_xiao=0

  for r_bw in bw[1:11]:

    if r_bw>=5:

        bw_da+=1

    else:

     break

  for r_bw in bw[1:11]:

    if r_bw<5:

       bw_xiao+=1
    else:

     break


#######判断十位单双#############

  sw_d=0

  sw_s=0

  for r_sw in bw[1:11]:

    if r_sw%2==0:

        sw_s+=1

    else:

     break

  for r_sw in bw[1:11]:

    if r_sw%2==1:

       sw_d+=1
    else:

     break


#######判断十位大小#############

  sw_da=0

  sw_xiao=0

  for r_sw in sw[1:11]:

    if r_sw>=5:

        sw_da+=1

    else:

     break

  for r_sw in sw[1:11]:

    if r_sw<5:

       sw_xiao+=1
    else:

     break

#######判断个位单双#############

  gw_d=0

  gw_s=0

  for r_gw in bw[1:11]:

    if r_gw%2==0:

        sw_s+=1

    else:

     break

  for r_gw in gw[1:11]:

    if r_gw%2==1:

       gw_d+=1
    else:

     break

#######判断个位大小#############

  gw_da=0

  gw_xiao=0

  for r_gw in gw[1:11]:

    if r_gw>=5:

        gw_da+=1

    else:

     break

  for r_gw in gw[1:11]:

    if r_gw<5:

       gw_xiao+=1

    else:

     break


  ls = 4

  if da>=ls:

    #itchat.send('重庆时时彩-总和-大-超过4连~',toUserName=users[0]['UserName'])

    itchat.send('重庆时时彩-总和-大-超过4连~',toUserName=rooms[0]['UserName'])

  if xiao>=ls:

    #itchat.send('重庆时时彩-总和-小-超过4连~',toUserName=users[0]['UserName'])

    itchat.send('重庆时时彩-总和-小-超过4连~',toUserName=rooms[0]['UserName'])    

  if dan>=ls:
      
     #itchat.send('重庆时时彩-总和-单-超过4连~',toUserName=users[0]['UserName'])
   
     itchat.send('重庆时时彩-总和-单-超过4连~',toUserName=rooms[0]['UserName'])

  if shuang>=ls:
      
     #itchat.send('重庆时时彩-总和-双-超过4连~',toUserName=users[0]['UserName'])

     itchat.send('重庆时时彩-总和-双-超过4连~',toUserName=rooms[0]['UserName'])

  if ww_d>=ls:

    #itchat.send('重庆时时彩-万位-单-超过4连~',toUserName=users[0]['UserName'])

    itchat.send('重庆时时彩-万位-单-超过4连~',toUserName=rooms[0]['UserName'])

  if ww_s>=ls:

    #itchat.send('重庆时时彩-万位-双-超过4连~',toUserName=users[0]['UserName'])

    itchat.send('重庆时时彩-万位-双-超过4连~',toUserName=rooms[0]['UserName'])

  if ww_da>=ls:

    #itchat.send('重庆时时彩-万位-大-超过4连~',toUserName=users[0]['UserName'])

    itchat.send('重庆时时彩-万位-大-超过4连~',toUserName=rooms[0]['UserName'])

  if ww_xiao>=ls:

   #itchat.send('重庆时时彩-万位-小-超过4连~',toUserName=users[0]['UserName'])

   itchat.send('重庆时时彩-万位-小-超过4连~',toUserName=rooms[0]['UserName'])

  if qw_d>=ls:

    #itchat.send('重庆时时彩-千位-单-超过4连~',toUserName=users[0]['UserName'])

    itchat.send('重庆时时彩-千位-单-超过4连~',toUserName=rooms[0]['UserName'])

  if qw_s>=ls:

    #itchat.send('重庆时时彩-千位-双-超过4连~',toUserName=users[0]['UserName'])

    itchat.send('重庆时时彩-千位-双-超过4连~',toUserName=rooms[0]['UserName'])

  if qw_da>=ls:

    #itchat.send('重庆时时彩-千位-大-超过4连~',toUserName=users[0]['UserName'])

    itchat.send('重庆时时彩-千位-大-超过4连~',toUserName=rooms[0]['UserName'])

  if qw_xiao>=ls:

    #itchat.send('重庆时时彩-千位-小-超过4连~',toUserName=users[0]['UserName'])

    itchat.send('重庆时时彩-千位-小-超过4连~',toUserName=rooms[0]['UserName'])

  if bw_d>=ls:

    #itchat.send('重庆时时彩-百位-单-超过4连~',toUserName=users[0]['UserName'])

    itchat.send('重庆时时彩-百位-单-超过4连~',toUserName=rooms[0]['UserName'])

  if bw_s>=ls:

    #itchat.send('重庆时时彩-百位-双-超过4连~',toUserName=users[0]['UserName'])

    itchat.send('重庆时时彩-百位-双-超过4连~',toUserName=rooms[0]['UserName'])

  if bw_da>=ls:

    #itchat.send('重庆时时彩-百位-大-超过4连~',toUserName=users[0]['UserName'])

    itchat.send('重庆时时彩-百位-大-超过4连~',toUserName=rooms[0]['UserName'])

  if bw_xiao>=ls:

    #itchat.send('重庆时时彩-百位-小-超过4连~',toUserName=users[0]['UserName'])

    itchat.send('重庆时时彩-百位-小-超过4连~',toUserName=rooms[0]['UserName'])

  if gw_d>=ls:

    #itchat.send('重庆时时彩-个位-单-超过4连~',toUserName=users[0]['UserName'])

    itchat.send('重庆时时彩-个位-单-超过4连~',toUserName=rooms[0]['UserName'])

  if gw_s>=ls:

    #itchat.send('重庆时时彩-个位-双-超过4连~',toUserName=users[0]['UserName'])

    itchat.send('重庆时时彩-个位-双-超过4连~',toUserName=rooms[0]['UserName'])

  if gw_da>=ls:

    #itchat.send('重庆时时彩-个位-大-超过4连~',toUserName=users[0]['UserName'])

    itchat.send('重庆时时彩-个位-大-超过4连~',toUserName=rooms[0]['UserName'])

  if gw_xiao>=ls:

    #itchat.send('重庆时时彩-个位-小-超过4连~',toUserName=users[0]['UserName'])

    itchat.send('重庆时时彩-个位-小-超过4连~',toUserName=rooms[0]['UserName'])

 # Cqssc.enter(cqssc_cycle,1,cqssc_write_to_excel,)
############################重庆时时彩结束#################################
  f.save('cqssc.xls')

#TODO:
#main
def cjssc():

    while True:

      write_to_excel()

      time.sleep(75)

def cqssc():

      while True:

       cqssc_write_to_excel()

       time.sleep(600)

threads = []

t1 = threading.Thread(target = cjssc)

threads.append(t1)

t2 = threading.Thread(target = cqssc)

threads.append(t2)

for t in threads:
    t.start()
for t in threads:
    t.join()

#cjssc_cycle = 75
#cqssc_cycle = 420
#Cqssc=sched.scheduler(time.time,time.sleep)
#Cqssc.enter(cqssc_cycle,1,cqssc_write_to_excel,)
#Cqssc.run()
#S=sched.scheduler(time.time,time.sleep)
#S.enter(cjssc_cycle,1,write_to_excel,)
#S.run()



