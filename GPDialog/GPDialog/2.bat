@echo off
%1 mshta vbscript:CreateObject("Shell.Application").ShellExecute("cmd.exe","/c %~s0 ::","","runas",1)(window.close)&&exit
cd /d "%~dp0"
mode con: cols=85 lines=30
:Ok
title  �ر�SMB��ȫ�ӹ̹���  
color 0A
cls
echo.                   
echo.                      
echo -----------------------  ����SMB����ȫ�ӹ̹���  --------------------------
echo.                                                                         
echo.       
echo.                                                                     
echo    * ������棺����߽����ǽ���445�˿ڵķ��ʣ���ͨ��IPS������ǽ��ذ�ȫ�豸��
echo      �������ϲ��ԡ�    
echo.
echo    * �ն˲��棺��ʱ�ر�Server����,ʹ������"netstat -ano | findstr ":445""��ȷ��
echo      �ر�445�˿ڣ�������΢���������MS17-010����,ѡ���Ӧ�İ汾���в�����װ����
echo      �����ص�ַ��http://www.catalog.update.microsoft.com/Search.aspx?q=KB4012598��        
echo.     
echo    * ������ϵͳ����Ա������У������ṩ�˹��������Ĳ����Ľ��ܣ�
echo.
echo       0��WINXP�ӹ� 1��WIN7�ӹ� 2��WIN10�ӹ� 3��WIN2003�ӹ� 4��WIN2008�ӹ� 5��WIN2012�ӹ�
echo       6.WIN2016�ӹ�          
echo.  
echo       7: �˳�                                                              
echo                                                          
echo ---------------------------------------------------------------------------------
echo.
set start=
set /p start=    ����(0 1 2 3 4 5 6)�󰴻س���:
if "%start%"=="0" goto WINXP
if "%start%"=="1" goto WIN7
if "%start%"=="2" goto WIN10
if "%start%"=="3" goto WIN2003
if "%start%"=="4" goto WIN2008
if "%start%"=="5" goto WIN2012
if "%start%"=="6" goto WIN2016
if "%start%"=="7" goto quit
goto Ok

:WINXP
netsh firewall set opmode mode=enable
netsh firewall set portopening protocol=tcp port=135 mode=disable name=deny135
netsh firewall set portopening protocol=tcp port=136 mode=disable name=deny136
netsh firewall set portopening protocol=tcp port=137 mode=disable name=deny137
netsh firewall set portopening protocol=tcp port=138 mode=disable name=deny138
netsh firewall set portopening protocol=tcp port=139 mode=disable name=deny139
netsh firewall set portopening protocol=tcp port=445 mode=disable name=deny445
netsh firewall set portopening protocol=tcp port=3389 mode=disable name=deny3389
echo ---------------------------------------------------------------------------------
echo    *  Windows XPϵͳ�ӹ�����ִ����ϣ�
echo .
pause
goto Ok
:WIN7
%1 mshta vbscript:CreateObject("Shell.Application").ShellExecute("cmd.exe","/c %~s0 ::","","runas",1)(window.close)&&exit
cd /d "%~dp0"
::����ipsec����
sc config "PolicyAgent" start= auto
sc start PolicyAgent
netsh ipsec static add policy name=deny445
netsh ipsec static add filterlist name=block
netsh ipsec static add filteraction name=block action=block
netsh ipsec static add filter filterlist=block any srcmask=32 srcport=0 dstaddr=me dstport=21 protocol=tcp description=21
netsh ipsec static add filter filterlist=block any srcmask=32 srcport=0 dstaddr=me dstport=135 protocol=tcp description=135
netsh ipsec static add filter filterlist=block any srcmask=32 srcport=0 dstaddr=me dstport=137 protocol=tcp description=137
netsh ipsec static add filter filterlist=block any srcmask=32 srcport=0 dstaddr=me dstport=138 protocol=tcp description=138
netsh ipsec static add filter filterlist=block any srcmask=32 srcport=0 dstaddr=me dstport=139 protocol=tcp description=139
netsh ipsec static add filter filterlist=block any srcmask=32 srcport=0 dstaddr=me dstport=445 protocol=tcp description=445
netsh ipsec static add filter filterlist=block any srcmask=32 srcport=0 dstaddr=me dstport=3389 protocol=tcp description=3389
netsh ipsec static add rule name=block policy=deny445 filterlist=block filteraction=block
netsh ipsec static set policy name=deny445 assign=y
echo ---------------------------------------------------------------------------------
echo    *  Windows 7ϵͳ�ӹ�����ִ����ϣ�
echo .
pause
goto Ok
:WIN10
%1 mshta vbscript:CreateObject("Shell.Application").ShellExecute("cmd.exe","/c %~s0 ::","","runas",1)(window.close)&&exit
cd /d "%~dp0"
::����ipsec����
sc config "PolicyAgent" start= auto
sc start PolicyAgent
netsh ipsec static add policy name=deny445
netsh ipsec static add filterlist name=block
netsh ipsec static add filteraction name=block action=block
netsh ipsec static add filter filterlist=block any srcmask=32 srcport=0 dstaddr=me dstport=21 protocol=tcp description=21
netsh ipsec static add filter filterlist=block any srcmask=32 srcport=0 dstaddr=me dstport=135 protocol=tcp description=135
netsh ipsec static add filter filterlist=block any srcmask=32 srcport=0 dstaddr=me dstport=137 protocol=tcp description=137
netsh ipsec static add filter filterlist=block any srcmask=32 srcport=0 dstaddr=me dstport=138 protocol=tcp description=138
netsh ipsec static add filter filterlist=block any srcmask=32 srcport=0 dstaddr=me dstport=139 protocol=tcp description=139
netsh ipsec static add filter filterlist=block any srcmask=32 srcport=0 dstaddr=me dstport=445 protocol=tcp description=445
netsh ipsec static add filter filterlist=block any srcmask=32 srcport=0 dstaddr=me dstport=3389 protocol=tcp description=3389
netsh ipsec static add rule name=block policy=deny445 filterlist=block filteraction=block
netsh ipsec static set policy name=deny445 assign=y
echo ---------------------------------------------------------------------------------
echo    *  Windows 10ϵͳ�ӹ�����ִ����ϣ�
echo .
pause
goto Ok
:WIN2003
net stop server > nul
net start sharedaccess > nul
sc config lanmanserver start= disabled
netsh firewall add portopening protocol = ALL port = 21 name = DenyEquationTCP mode = DISABLE scope = ALL profile = ALL > nul
netsh firewall add portopening protocol = ALL port = 135 name = DenyEquationTCP mode = DISABLE scope = ALL profile = ALL > nul
netsh firewall add portopening protocol = ALL port = 136 name = DenyEquationTCP mode = DISABLE scope = ALL profile = ALL > nul
netsh firewall add portopening protocol = ALL port = 137 name = DenyEquationTCP mode = DISABLE scope = ALL profile = ALL > nul
netsh firewall add portopening protocol = ALL port = 138 name = DenyEquationTCP mode = DISABLE scope = ALL profile = ALL > nul
netsh firewall add portopening protocol = ALL port = 445 name = DenyEquationTCP mode = DISABLE scope = ALL profile = ALL > nul
netsh firewall add portopening protocol = ALL port = 3389 name = DenyEquationTCP mode = DISABLE scope = ALL profile = ALL > nul
echo ---------------------------------------------------------------------------------
echo    *  Windows Server 2003ϵͳ�ӹ�����ִ����ϣ�
echo .
pause
goto Ok

:WIN2008
%1 mshta vbscript:CreateObject("Shell.Application").ShellExecute("cmd.exe","/c %~s0 ::","","runas",1)(window.close)&&exit
cd /d "%~dp0"
::����ipsec����
sc config "PolicyAgent" start= auto
sc start PolicyAgent
netsh ipsec static add policy name=deny445
netsh ipsec static add filterlist name=block
netsh ipsec static add filteraction name=block action=block
netsh ipsec static add filter filterlist=block any srcmask=32 srcport=0 dstaddr=me dstport=21 protocol=tcp description=21
netsh ipsec static add filter filterlist=block any srcmask=32 srcport=0 dstaddr=me dstport=135 protocol=tcp description=135
netsh ipsec static add filter filterlist=block any srcmask=32 srcport=0 dstaddr=me dstport=137 protocol=tcp description=137
netsh ipsec static add filter filterlist=block any srcmask=32 srcport=0 dstaddr=me dstport=138 protocol=tcp description=138
netsh ipsec static add filter filterlist=block any srcmask=32 srcport=0 dstaddr=me dstport=139 protocol=tcp description=139
netsh ipsec static add filter filterlist=block any srcmask=32 srcport=0 dstaddr=me dstport=445 protocol=tcp description=445
netsh ipsec static add filter filterlist=block any srcmask=32 srcport=0 dstaddr=me dstport=3389 protocol=tcp description=3389
netsh ipsec static add rule name=block policy=deny445 filterlist=block filteraction=block
netsh ipsec static set policy name=deny445 assign=y
echo ---------------------------------------------------------------------------------
echo    *  Windows Server 2008ϵͳ�ӹ�����ִ����ϣ�
echo .
pause
goto Ok

:WIN2012
%1 mshta vbscript:CreateObject("Shell.Application").ShellExecute("cmd.exe","/c %~s0 ::","","runas",1)(window.close)&&exit
cd /d "%~dp0"
::����ipsec����
sc config "PolicyAgent" start= auto
sc start PolicyAgent
netsh ipsec static add policy name=deny445
netsh ipsec static add filterlist name=block
netsh ipsec static add filteraction name=block action=block
netsh ipsec static add filter filterlist=block any srcmask=32 srcport=0 dstaddr=me dstport=21 protocol=tcp description=21
netsh ipsec static add filter filterlist=block any srcmask=32 srcport=0 dstaddr=me dstport=135 protocol=tcp description=135
netsh ipsec static add filter filterlist=block any srcmask=32 srcport=0 dstaddr=me dstport=137 protocol=tcp description=137
netsh ipsec static add filter filterlist=block any srcmask=32 srcport=0 dstaddr=me dstport=138 protocol=tcp description=138
netsh ipsec static add filter filterlist=block any srcmask=32 srcport=0 dstaddr=me dstport=139 protocol=tcp description=139
netsh ipsec static add filter filterlist=block any srcmask=32 srcport=0 dstaddr=me dstport=445 protocol=tcp description=445
netsh ipsec static add filter filterlist=block any srcmask=32 srcport=0 dstaddr=me dstport=3389 protocol=tcp description=3389
netsh ipsec static add rule name=block policy=deny445 filterlist=block filteraction=block
netsh ipsec static set policy name=deny445 assign=y
echo ---------------------------------------------------------------------------------
echo    *  Windows Server 2012ϵͳ�ӹ�����ִ����ϣ�
echo .
pause
goto Ok
:WIN2016
%1 mshta vbscript:CreateObject("Shell.Application").ShellExecute("cmd.exe","/c %~s0 ::","","runas",1)(window.close)&&exit
cd /d "%~dp0"
::����ipsec����
sc config "PolicyAgent" start= auto
sc start PolicyAgent
netsh ipsec static add policy name=deny445
netsh ipsec static add filterlist name=block
netsh ipsec static add filteraction name=block action=block
netsh ipsec static add filter filterlist=block any srcmask=32 srcport=0 dstaddr=me dstport=21 protocol=tcp description=21
netsh ipsec static add filter filterlist=block any srcmask=32 srcport=0 dstaddr=me dstport=135 protocol=tcp description=135
netsh ipsec static add filter filterlist=block any srcmask=32 srcport=0 dstaddr=me dstport=137 protocol=tcp description=137
netsh ipsec static add filter filterlist=block any srcmask=32 srcport=0 dstaddr=me dstport=138 protocol=tcp description=138
netsh ipsec static add filter filterlist=block any srcmask=32 srcport=0 dstaddr=me dstport=139 protocol=tcp description=139
netsh ipsec static add filter filterlist=block any srcmask=32 srcport=0 dstaddr=me dstport=445 protocol=tcp description=445
netsh ipsec static add filter filterlist=block any srcmask=32 srcport=0 dstaddr=me dstport=3389 protocol=tcp description=3389
netsh ipsec static add rule name=block policy=deny445 filterlist=block filteraction=block
netsh ipsec static set policy name=deny445 assign=y
echo ---------------------------------------------------------------------------------
echo    *  Windows Server 2016ϵͳ�ӹ�����ִ����ϣ�
echo .
pause
goto Ok
