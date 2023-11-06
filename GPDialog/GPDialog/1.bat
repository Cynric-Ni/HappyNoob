@echo off
%1 mshta vbscript:CreateObject("Shell.Application").ShellExecute("cmd.exe"," /c %~s0 ::","","runas",1)(window.close)&&exit
cd /d "%~dp0"
REM 清屏
cls
title 长江武汉航道局基线设置
color f0
echo ****************************************
echo write by cynric
echo ****************************************
pause
cls
color 3f
echo ****************************************
echo 设置口令复杂度
echo 密码必须符合复杂度要求
echo 密码长度最低8位
echo 密码最长使用期限90天
echo 密码最短使用期限5天
echo 密码输错6次锁定
echo 锁定时间16分钟
echo ****************************************
echo [version] > 1.inf
echo signature="$CHICAGO$" >>1.inf
echo [System Access] >>1.inf
echo MinimumPasswordLength =8 >> 1.inf
echo PasswordComplexity = 1 >> 1.inf
echo MinimumPasswordAge = 5 >> 1.inf
echo MaximumPasswordAge = 90  >> 1.inf

echo LockoutBadCount = 6  >> 1.inf
echo ResetLockoutCount = 16  >> 1.inf
echo LockoutDuration = 16  >>1.inf
echo PasswordHistorySize = 5 >>1.inf
echo DotDisplayLastUserName = enable >> 1.inf
secedit /configure /db gp.sdb /cfg 1.inf /quiet
del gp.sdb
del 1.inf
echo 设置完成
pause
cls
echo ****************************************
echo 禁用GUEST账号
echo ****************************************
echo .
net user guest /active:no
pause
cls
echo ****************************************
echo 打开所有日志审计（成功失败）
echo ****************************************
echo .
echo [version] > 1.inf
echo signature="$CHICAGO$" >> 1.inf
echo [Event Audit] >> 1.inf
echo AuditSystemEvents = 3 >> 1.inf
echo AuditObjectAccess = 3 >> 1.inf
echo AuditPrivilegeUse = 3 >> 1.inf
echo AuditPolicyChange = 3 >> 1.inf
echo AuditAccountManage = 3 >> 1.inf
echo AuditProcessTracking = 3 >> 1.inf
echo AuditDSAccess = 3 >> 1.inf
echo AuditAccountLogon = 3 >> 1.inf
echo AuditLogonEvents = 3 >> 1.inf
secedit /configure /db gp.sdb /cfg 1.inf /quiet
del gp.sdb
del 1.inf
echo 设置完毕
pause
cls
echo ****************************************
echo 打开防火墙
echo ****************************************
echo .
netsh advfirewall set allprofiles state on
echo 设置完毕
pause
cls
echo ******************************************
echo 屏幕保护口令设置
echo ******************************************
echo .
set SCREENSAVER_FILE="C:\Windows\System32\screensaver.scr"
set SCREENSAVER_SETTINGS="/s"
reg add "HKEY_CURRENT_USER\Control Panel\Desktop" /v SCRNSAVE.EXE /t REG_SZ /d %SCREENSAVER_FILE% /f
reg add "HKEY_CURRENT_USER\Control Panel\Desktop" /v ScreenSaverStart /t REG_SZ /d %SCREENSAVER_SETTINGS% /f
reg add "HKEY_CURRENT_USER\Control Panel\Desktop" /v ScreenSaveActive /t REG_SZ /d 1 /f
reg add "HKEY_CURRENT_USER\Control Panel\Desktop" /v ScreenSaverIsSecure /t REG_SZ /d 1 /f
reg add "HKEY_CURRENT_USER\Control Panel\Desktop" /v ScreenSaveTimeOut /t REG_SZ /d 900 /f
rundll32.exe user32.dll, UpdatePerUserSystemParameters
echo 设置完毕
echo.
pause
cd /d "%~dp0"
mode con : cols = 85 lines = 30
: Ok
title  关闭SMB安全加固工具
color 0A
cls
echo **********************************关闭高危端口**************************************
echo * 必须以系统管理员身份运行，以下提供此工具所做的操作的介绍：
echo.
echo 0：WINXP加固 1：WIN7加固 2：WIN10加固 3：WIN2003加固 4：WIN2008加固 5：WIN2012加固
echo       6.WIN2016加固
echo.
echo       7: 退出
echo 
echo *************************************************************************************
echo .
set start=
set /p start=  输入(0 1 2 3 4 5 6)后按回车键:
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
netsh firewall set portopening protocol=tcp port=135 mode=disable name=eny135
netsh firewall set portopening protocol=tcp port=136 mode=disable name=deny136
netsh firewall set portopening protocol=tcp port=137 mode=disable name=deny137
netsh firewall set portopening protocol=tcp port=138 mode=disable name=deny138
netsh firewall set portopening protocol=tcp port=139 mode=disable name=deny139
netsh firewall set portopening protocol=tcp port=445 mode=disable name=deny445
netsh firewall set portopening protocol=tcp port=3389 mode=disable name=deny3389
echo **************************************************************************************
echo * Windows XP系统加固命令执行完毕！
echo .
pause
goto Ok
:WIN7
cd /d "%~dp0"
::开启ipsec服务
sc config "PolicyAgent" start=auto
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
echo **************************************************************************************
echo * Windows 7系统加固命令执行完毕！
echo .
pause
goto Ok
:WIN10
cd /d "%~dp0"
::开启ipsec服务
sc config "PolicyAgent" start=auto
sc start PolicyAgent
netsh ipsec static add policy name=deny445
netsh ipsec static add filterlist name = block
netsh ipsec static add filteraction name=block action =block
netsh ipsec static add filter filterlist=block any srcmask=32 srcport=0 dstaddr=me dstport=21 protocol=tcp description=21
netsh ipsec static add filter filterlist=block any srcmask=32 srcport=0 dstaddr=me dstport=135 protocol=tcp description=135
netsh ipsec static add filter filterlist=block any srcmask=32 srcport=0 dstaddr=me dstport=137 protocol=tcp description=137
netsh ipsec static add filter filterlist=block any srcmask=32 srcport=0 dstaddr=me dstport=138 protocol=tcp description=138
netsh ipsec static add filter filterlist=block any srcmask=32 srcport=0 dstaddr=me dstport=139 protocol=tcp description=139
netsh ipsec static add filter filterlist=block any srcmask=32 srcport=0 dstaddr=me dstport=445 protocol=tcp description=445
netsh ipsec static add filter filterlist=block any srcmask=32 srcport=0 dstaddr=me dstport=3389 protocol=tcp description=3389
netsh ipsec static add rule name = block policy = deny445 filterlist = block filteraction = block
netsh ipsec static set policy name = deny445 assign = y
echo *****************************************************************************************
echo * Windows 10系统加固命令执行完毕！
echo .
pause
goto Ok
:WIN2003
net stop server > nul
	net start sharedaccess > nul
sc config lanmanserver start=disabled
netsh firewall add portopening protocol=ALL port=21 name=DenyEquationTCP mode=DISABLE scope=ALL profile=ALL > nul
netsh firewall add portopening protocol=ALL port=135 name=DenyEquationTCP mode=DISABLE scope=ALL profile=ALL > nul
netsh firewall add portopening protocol=ALL port=136 name=DenyEquationTCP mode=DISABLE scope=ALL profile=ALL > nul
netsh firewall add portopening protocol=ALL port=137 name=DenyEquationTCP mode=DISABLE scope=ALL profile=ALL > nul
netsh firewall add portopening protocol=ALL port=138 name=DenyEquationTCP mode=DISABLE scope=ALL profile=ALL > nul
netsh firewall add portopening protocol=ALL port=445 name=DenyEquationTCP mode=DISABLE scope=ALL profile=ALL > nul
netsh firewall add portopening protocol=ALL port=3389 name=DenyEquationTCP mode=DISABLE scope=ALL profile=ALL > nul
echo ****************************************************************************
echo * Windows Server 2003系统加固命令执行完毕！
echo .
pause
goto Ok
:WIN2008
cd /d "%~dp"
::开启ipsec服务
sc config "PolicyAgent" start=auto
sc start PolicyAgent
netsh ipsec static add policy name=deny445
netsh ipsec static add filterlist name=block
netsh ipsec static add filteraction name=block action = block
netsh ipsec static add filter filterlist=block any srcmask=32 srcport=0 dstaddr=me dstport=21 protocol=tcp description=21
netsh ipsec static add filter filterlist=block any srcmask=32 srcport=0 dstaddr=me dstport=135 protocol=tcp description=135
netsh ipsec static add filter filterlist=block any srcmask=32 srcport=0 dstaddr=me dstport=137 protocol=tcp description=137
netsh ipsec static add filter filterlist=block any srcmask=32 srcport=0 dstaddr=me dstport=138 protocol=tcp description=138
netsh ipsec static add filter filterlist=block any srcmask=32 srcport=0 dstaddr=me dstport=139 protocol=tcp description=139
netsh ipsec static add filter filterlist=block any srcmask=32 srcport=0 dstaddr=me dstport=445 protocol=tcp description=445
netsh ipsec static add filter filterlist=block any srcmask=32 srcport=0 dstaddr=me dstport=3389 protocol=tcp description=3389
netsh ipsec static add rule name=block policy=deny445 filterlist=block filteraction=block
netsh ipsec static set policy name=deny445 assign=y
echo *************************************************************************
echo * Windows Server 2008系统加固命令执行完毕！
echo .
pause
goto Ok
:WIN2012
cd /d "%~dp0"
::开启ipsec服务
sc config "PolicyAgent" start=auto
sc start PolicyAgent
netsh ipsec static add policy name=deny445
netsh ipsec static add filterlist name=block
netsh ipsec static add filteraction name=block action=block
netsh ipsec static add filter filterlist=block any srcmask=32 srcport=0 dstaddr=me dstport=21 protocol=tcp description=21
netsh ipsec static add filter filterlist=block any srcmask=32 srcport=0 dstaddr=me dstport=135 protocol=tcp description=135
netsh ipsec static add filter filterlist=block any srcmask=32 srcport=0 dstaddr=me dstport=137 protocol=tcp description=137
netsh ipsec static add filter filterlist=block any srcmask=32 srcport=0 dstaddr=me dstport=138 protocol=tcp description=138
netsh ipsec static add filter filterlist=block any srcmask=32 srcport=0 dstaddr=me dstport=139 protocol=tcp description=139
netsh ipsec static add filter filterlist=block any srcmask=32 srcport=0 dstaddr=me dstport=455 protocol=tcp description=445
netsh ipsec static add filter filterlist=block any srcmask=32 srcport=0 dstaddr=me dstport=3389 protocol=tcp description=3389
netsh ipsec static add rule name=block policy=deny445 filterlist=block filteraction = block
netsh ipsec static set policy name=deny445 assign=y
echo **********************************************************************
echo * Windows Server 2012系统加固命令执行完毕！
echo .
pause
goto Ok
:WIN2016
%1 mshta vbscript:CreateObject("Shell.Application").ShellExecute("cmd.exe"," /c %~s0 ::","","runas",1)(window.close)&&exit
cd /d "%~dp0"
::开启ipsec服务
sc config "PolicyAgent" start=auto
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
echo **************************************************************
echo * Windows Server 2016系统加固命令执行完毕！
echo .
pause
goto Ok
