@echo off
%1 mshta vbscript:CreateObject("Shell.Application").ShellExecute("cmd.exe"," /c %~s0 ::","","runas",1)(window.close)&&exit
cd /d "%~dp0"
REM ����
cls
title �����人�����ֻ�������
color f0
echo ****************************************
echo write by cynric
echo ****************************************
pause
cls
color 3f
echo ****************************************
echo ���ÿ���Ӷ�
echo ���������ϸ��Ӷ�Ҫ��
echo ���볤�����8λ
echo �����ʹ������90��
echo �������ʹ������5��
echo �������6������
echo ����ʱ��16����
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
echo �������
pause
cls
echo ****************************************
echo ����GUEST�˺�
echo ****************************************
echo .
net user guest /active:no
pause
cls
echo ****************************************
echo ��������־��ƣ��ɹ�ʧ�ܣ�
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
echo �������
pause
cls
echo ****************************************
echo �򿪷���ǽ
echo ****************************************
echo .
netsh advfirewall set allprofiles state on
echo �������
pause
cls
echo ******************************************
echo ��Ļ������������
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
echo �������
echo.
pause
cd /d "%~dp0"
mode con : cols = 85 lines = 30
: Ok
title  �ر�SMB��ȫ�ӹ̹���
color 0A
cls
echo **********************************�رո�Σ�˿�**************************************
echo * ������ϵͳ����Ա������У������ṩ�˹��������Ĳ����Ľ��ܣ�
echo.
echo 0��WINXP�ӹ� 1��WIN7�ӹ� 2��WIN10�ӹ� 3��WIN2003�ӹ� 4��WIN2008�ӹ� 5��WIN2012�ӹ�
echo       6.WIN2016�ӹ�
echo.
echo       7: �˳�
echo 
echo *************************************************************************************
echo .
set start=
set /p start=  ����(0 1 2 3 4 5 6)�󰴻س���:
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
echo * Windows XPϵͳ�ӹ�����ִ����ϣ�
echo .
pause
goto Ok
:WIN7
cd /d "%~dp0"
::����ipsec����
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
echo * Windows 7ϵͳ�ӹ�����ִ����ϣ�
echo .
pause
goto Ok
:WIN10
cd /d "%~dp0"
::����ipsec����
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
echo * Windows 10ϵͳ�ӹ�����ִ����ϣ�
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
echo * Windows Server 2003ϵͳ�ӹ�����ִ����ϣ�
echo .
pause
goto Ok
:WIN2008
cd /d "%~dp"
::����ipsec����
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
echo * Windows Server 2008ϵͳ�ӹ�����ִ����ϣ�
echo .
pause
goto Ok
:WIN2012
cd /d "%~dp0"
::����ipsec����
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
echo * Windows Server 2012ϵͳ�ӹ�����ִ����ϣ�
echo .
pause
goto Ok
:WIN2016
%1 mshta vbscript:CreateObject("Shell.Application").ShellExecute("cmd.exe"," /c %~s0 ::","","runas",1)(window.close)&&exit
cd /d "%~dp0"
::����ipsec����
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
echo * Windows Server 2016ϵͳ�ӹ�����ִ����ϣ�
echo .
pause
goto Ok
