@echo off
REM ����
cls
title �����人���������������������
color f0
echo ****************************************
echo write by ������ 
echo ****************************************
pause
cls
color 3f
echo ****************************************
echo ���ÿ���Ӷ�
echo ���������ϸ��Ӷ�Ҫ��
echo ���볤�����12λ
echo �����ʹ������30��
echo �������ʹ������5��
echo �������5������
echo ����ʱ��16����
echo .
echo [version] > 1.inf
echo signature="$CHICAGO$" >>1.inf
echo [System Access] >>1.inf
echo MinimumPasswordLength = 12 >> 1.inf
echo PasswordComplexity = 1 >> 1.inf
echo MinimumPasswordAge = 5 >> 1.inf
echo MaximumPasswordAge = 90 >> 1.inf
echo LockoutBadCount = 5 >> 1.inf
echo ResetLockoutCount = 16 >> 1.inf
echo LockoutDuration = 16 >>1.inf
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
echo �������
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
sc start MpsSvc
sc config MpsSvc start= auto
echo �������
pause
cls
echo ****************************************
echo �ر��Զ�����
echo ****************************************
echo .
echo �����޸Ķ�Ӧ��ע������
reg delete HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Policies\Explorer /v NoDriveTypeAutoRun /f > nul
reg add HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Policies\Explorer /v NoDriveTypeAutoRun /t reg_dword /d 0xff /f > nul
echo �޸ĳɹ�
echo .
echo �޸Ķ�Ӧ�������
net stop ShellHWDetection
sc config ShellHWDetecion start= disable
echo �������
puase
cls
echo ****************************************
echo ��ֹ����Ա�Զ���¼
echo ****************************************
echo .
reg add "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Winlogon" /v AutoAdminLogon /d 0 /f
echo �������
pause
cls
echo *****************************************
echo �رղ���Ҫ����
echo *****************************************
net stop TermService
sc config TermService start= disabled
net stop RemoteRegistry
sc config RemoteRegistry start= disabled
net stop TlntSvr
sc config TlntSvr start= disabled
net stop Messenger
sc config Messenger start= disabled
net stop ClipSrv
sc config ClipSrv start= disabled
net stop Alerter
sc config Alerter start= disabled
echo �������
pause
cls
echo ******************************************
echo ����ϵͳ���·���
echo ******************************************
echo .
net start wuauserv
sc config wuauserv start= auto
echo .
echo �������
pause
cls
echo ******************************************
echo ��Ļ������������
echo ******************************************
echo .
reg add "HKEY_CURRENT_USER\Control Panel\Desktop" /v ScreenSaveActive /t REG_SZ /d 1 /f
reg add "HKEY_CURRENT_USER\Control Panel\Desktop" /v ScreenSaverIsSecure /t REG_SZ /d 1 /f
reg add "HKEY_CURRENT_USER\Control Panel\Desktop" /v ScreenSaveTimeOut /t REG_SZ /d 300 /f
echo �������
echo.
pause