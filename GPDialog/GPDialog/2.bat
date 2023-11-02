@echo off
%1 mshta vbscript:CreateObject("Shell.Application").ShellExecute("cmd.exe","/c %~s0 ::","","runas",1)(window.close)&&exit
cd /d "%~dp0"
mode con: cols=85 lines=30
:Ok
title  关闭SMB安全加固工具  
color 0A
cls
echo.                   
echo.                      
echo -----------------------  开启SMB服务安全加固工具  --------------------------
echo.                                                                         
echo.       
echo.                                                                     
echo    * 网络层面：建议边界防火墙阻断445端口的访问，可通过IPS、防火墙相关安全设备配
echo      置相关阻断策略。    
echo.
echo    * 终端层面：暂时关闭Server服务,使用命令"netstat -ano | findstr ":445""，确保
echo      关闭445端口，建议在微软官网下载MS17-010补丁,选择对应的版本进行补丁安装，补
echo      丁下载地址：http://www.catalog.update.microsoft.com/Search.aspx?q=KB4012598。        
echo.     
echo    * 必须以系统管理员身份运行，以下提供此工具所做的操作的介绍：
echo.
echo       0：WINXP加固 1：WIN7加固 2：WIN10加固 3：WIN2003加固 4：WIN2008加固 5：WIN2012加固
echo       6.WIN2016加固          
echo.  
echo       7: 退出                                                              
echo                                                          
echo ---------------------------------------------------------------------------------
echo.
set start=
set /p start=    输入(0 1 2 3 4 5 6)后按回车键:
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
echo    *  Windows XP系统加固命令执行完毕！
echo .
pause
goto Ok
:WIN7
%1 mshta vbscript:CreateObject("Shell.Application").ShellExecute("cmd.exe","/c %~s0 ::","","runas",1)(window.close)&&exit
cd /d "%~dp0"
::开启ipsec服务
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
echo    *  Windows 7系统加固命令执行完毕！
echo .
pause
goto Ok
:WIN10
%1 mshta vbscript:CreateObject("Shell.Application").ShellExecute("cmd.exe","/c %~s0 ::","","runas",1)(window.close)&&exit
cd /d "%~dp0"
::开启ipsec服务
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
echo    *  Windows 10系统加固命令执行完毕！
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
echo    *  Windows Server 2003系统加固命令执行完毕！
echo .
pause
goto Ok

:WIN2008
%1 mshta vbscript:CreateObject("Shell.Application").ShellExecute("cmd.exe","/c %~s0 ::","","runas",1)(window.close)&&exit
cd /d "%~dp0"
::开启ipsec服务
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
echo    *  Windows Server 2008系统加固命令执行完毕！
echo .
pause
goto Ok

:WIN2012
%1 mshta vbscript:CreateObject("Shell.Application").ShellExecute("cmd.exe","/c %~s0 ::","","runas",1)(window.close)&&exit
cd /d "%~dp0"
::开启ipsec服务
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
echo    *  Windows Server 2012系统加固命令执行完毕！
echo .
pause
goto Ok
:WIN2016
%1 mshta vbscript:CreateObject("Shell.Application").ShellExecute("cmd.exe","/c %~s0 ::","","runas",1)(window.close)&&exit
cd /d "%~dp0"
::开启ipsec服务
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
echo    *  Windows Server 2016系统加固命令执行完毕！
echo .
pause
goto Ok
