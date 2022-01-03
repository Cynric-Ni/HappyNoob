@echo off
REM 清屏
cls
title 长江武汉航道局组策略设置批处理
color f0
echo ****************************************
echo write by 倪忻亮 
echo ****************************************
pause
cls
color 3f
echo ****************************************
echo 设置口令复杂度
echo 密码必须符合复杂度要求
echo 密码长度最低12位
echo 密码最长使用期限30天
echo 密码最短使用期限5天
echo 密码输错5次锁定
echo 锁定时间16分钟
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
echo 设置完成
pause
cls
echo ****************************************
echo 禁用GUEST账号
echo ****************************************
echo .
net user guest /active:no
echo 设置完毕
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
sc start MpsSvc
sc config MpsSvc start= auto
echo 设置完毕
pause
cls
echo ****************************************
echo 关闭自动播放
echo ****************************************
echo .
echo 正在修改对应的注册表项……
reg delete HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Policies\Explorer /v NoDriveTypeAutoRun /f > nul
reg add HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Policies\Explorer /v NoDriveTypeAutoRun /t reg_dword /d 0xff /f > nul
echo 修改成功
echo .
echo 修改对应服务项……
net stop ShellHWDetection
sc config ShellHWDetecion start= disable
echo 设置完毕
puase
cls
echo ****************************************
echo 禁止管理员自动登录
echo ****************************************
echo .
reg add "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Winlogon" /v AutoAdminLogon /d 0 /f
echo 设置完毕
pause
cls
echo *****************************************
echo 关闭不必要服务
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
echo 设置完毕
pause
cls
echo ******************************************
echo 开启系统更新服务
echo ******************************************
echo .
net start wuauserv
sc config wuauserv start= auto
echo .
echo 设置完毕
pause
cls
echo ******************************************
echo 屏幕保护口令设置
echo ******************************************
echo .
reg add "HKEY_CURRENT_USER\Control Panel\Desktop" /v ScreenSaveActive /t REG_SZ /d 1 /f
reg add "HKEY_CURRENT_USER\Control Panel\Desktop" /v ScreenSaverIsSecure /t REG_SZ /d 1 /f
reg add "HKEY_CURRENT_USER\Control Panel\Desktop" /v ScreenSaveTimeOut /t REG_SZ /d 300 /f
echo 设置完毕
echo.
pause