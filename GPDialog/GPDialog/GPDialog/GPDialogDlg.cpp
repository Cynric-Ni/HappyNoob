
// GPDialogDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "GPDialog.h"
#include "GPDialogDlg.h"
#include "afxdialogex.h"
#include <locale>
#include <iostream>
#include <fstream>
#include <VersionHelpers.h>
#include <windows.h>
#include <winnt.h>
#include <stdio.h>
#include <atlbase.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//操作系统版本
#define WIN7					61
#define WIN77600				617600
#define WIN77601				617601

#define	WIN8					62
#define	WIN89200				629200

#define WIN81					63
#define	WIN819600				639600


#define WIN10					100
#define WIN101607				1001607
#define WIN1010586				10010586
#define WIN1014393				10014393



// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
	

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:

};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)

END_MESSAGE_MAP()


// CGPDialogDlg 对话框



CGPDialogDlg::CGPDialogDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GPDIALOG_DIALOG, pParent)
	, m_OpenPlociy(TRUE)
	, m_NoGuest(TRUE)
	, m_OpenFireWall(TRUE)
	, m_SrceenPsw(TRUE)
	, m_DisablePortRdp(TRUE)
{
	m_ch1 = L"8";
	m_ch2 = L"90";
	m_ch3 = L"5";
	m_ch4 = L"6";
	m_ch5 = L"16";
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	hRead = NULL;
	hWrite = NULL;

}

CGPDialogDlg::~CGPDialogDlg() {
	if (hRead) {
		CloseHandle(hRead);
	}
	if (hWrite) {
		CloseHandle(hWrite);
	}
}

void CGPDialogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_OPENPLOCIY, m_OpenPlociy);
	DDX_Check(pDX, IDC_NO_GUEST, m_NoGuest);
	DDX_Check(pDX, IDC_OPEN_FIREWALL, m_OpenFireWall);
	DDX_Check(pDX, IDC_SCREEN_PSW, m_SrceenPsw);
	DDX_Check(pDX, IDC_DisablePortRdp, m_DisablePortRdp);
}

BEGIN_MESSAGE_MAP(CGPDialogDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//ON_EN_CHANGE(IDC_PASSLEN, &CGPDialogDlg::OnEnChangeEdit1)
	//ON_STN_CLICKED(IDC_PasssLen, &CGPDialogDlg::OnStnClickedPassslen)
	//ON_EN_CHANGE(IDC_EDIT2, &CGPDialogDlg::OnEnChangeEdit2)
	//ON_EN_CHANGE(IDC_EDIT3, &CGPDialogDlg::OnEnChangeEdit3)
	ON_BN_CLICKED(IDOK, &CGPDialogDlg::OnBnClickedOk)
	ON_BN_CLICKED(checkUpdate, &CGPDialogDlg::OnBnClickedcheckupdate)
END_MESSAGE_MAP()


// CGPDialogDlg 消息处理程序

BOOL CGPDialogDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	GetDlgItem(IDC_PASSLEN)->SetWindowTextW(m_ch1);
	GetDlgItem(IDC_EDIT2)->SetWindowTextW(m_ch2);
	GetDlgItem(IDC_EDIT3)->SetWindowTextW(m_ch3);
	GetDlgItem(IDC_EDIT4)->SetWindowTextW(m_ch4);
	GetDlgItem(IDC_EDIT6)->SetWindowTextW(m_ch5);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CGPDialogDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CGPDialogDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CGPDialogDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CGPDialogDlg::OnBnClickedOk()
{

	UpdateData();
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
	CStdioFile file;
	file.Open(L"..\\1.bat", CFile::modeCreate | CFile::modeWrite);
	GetDlgItem(IDC_PASSLEN)->GetWindowTextW(m_ch1);
	GetDlgItem(IDC_EDIT2)->GetWindowTextW(m_ch2);
	GetDlgItem(IDC_EDIT3)->GetWindowTextW(m_ch3);
	GetDlgItem(IDC_EDIT4)->GetWindowTextW(m_ch4);
	GetDlgItem(IDC_EDIT6)->GetWindowTextW(m_ch5);
	m_bat = L"@echo off\nREM 清屏\ncls\ntitle 长江武汉航道局组策略设置批处理\ncolor f0\necho ****************************************\necho write by 倪忻亮\necho ****************************************\n";
	m_bat += L"pause\ncls\ncolor 3f\necho ****************************************\necho 设置口令复杂度\necho 密码必须符合复杂度要求\necho 密码长度最低";
	m_bat += m_ch1;
	m_bat += L"位\necho 密码最长使用期限";
	m_bat += m_ch2;
	m_bat += L"天\necho 密码最短使用期限";
	m_bat += m_ch3;
	m_bat += L"天\n";
	if (m_ch4 != "0") {
		m_bat += L"echo 密码输错";
		m_bat += m_ch4;
		m_bat += L"次锁定\necho 锁定时间";
		m_bat += m_ch5;
		m_bat += L"分钟\n";
	}

	m_bat += L"echo ****************************************\necho [version] > 1.inf\necho signature=\"$CHICAGO$\" >>1.inf\necho [System Access] >>1.inf\necho MinimumPasswordLength =";
	m_bat += m_ch1;
	m_bat += L" >> 1.inf\necho PasswordComplexity = 1 >> 1.inf\necho MinimumPasswordAge = ";
	m_bat += m_ch3;
	m_bat += L" >> 1.inf\necho MaximumPasswordAge = ";
	m_bat += m_ch2;
	m_bat += "  >> 1.inf\n";     //在配置安全策略时会创建已个1.inf文件进行执行

	if (m_ch4 != "0") {
		m_bat += L"\necho LockoutBadCount = ";
		m_bat += m_ch4;
		m_bat += L"  >> 1.inf\necho ResetLockoutCount = ";
		m_bat += m_ch5;
		m_bat += L"  >> 1.inf\necho LockoutDuration = ";
		m_bat += m_ch5;
		m_bat += L"  >>1.inf\n";
	}

	m_bat += L"echo PasswordHistorySize = 5 >>1.inf\necho DotDisplayLastUserName = enable >> 1.inf\nsecedit /configure /db gp.sdb /cfg 1.inf /quiet\n";
	m_bat += L"del gp.sdb\ndel 1.inf\necho 设置完成\npause\ncls\n";

	if (m_NoGuest)
		m_bat += L"echo ****************************************\necho 禁用GUEST账号\necho ****************************************\necho .\nnet user guest /active:no\npause\ncls\n";

	if (m_OpenPlociy) {
		m_bat += L"echo ****************************************\necho 打开所有日志审计（成功失败）\necho ****************************************\necho .\n";
		m_bat += L"echo [version] > 1.inf\n";
		m_bat += L"echo signature=\"$CHICAGO$\" >> 1.inf\necho [Event Audit] >> 1.inf\necho AuditSystemEvents = 3 >> 1.inf\necho AuditObjectAccess = 3 >> 1.inf\necho AuditPrivilegeUse = 3 >> 1.inf\n";
		m_bat += L"echo AuditPolicyChange = 3 >> 1.inf\n";
		m_bat += L"echo AuditAccountManage = 3 >> 1.inf\n";
		m_bat += L"echo AuditProcessTracking = 3 >> 1.inf\n";
		m_bat += L"echo AuditDSAccess = 3 >> 1.inf\n";
		m_bat += L"echo AuditAccountLogon = 3 >> 1.inf\n";
		m_bat += L"echo AuditLogonEvents = 3 >> 1.inf\n";
		m_bat += L"secedit /configure /db gp.sdb /cfg 1.inf /quiet\n";
		m_bat += L"del gp.sdb\n";
		m_bat += L"del 1.inf\n";
		m_bat += L"echo 设置完毕\n";
		m_bat += L"pause\n";
		m_bat += L"cls\n";
	}

	if (m_OpenFireWall) {
		m_bat += L"echo ****************************************\n";
		m_bat += L"echo 打开防火墙\n";
		m_bat += L"echo ****************************************\n";
		m_bat += L"echo .\n";
		m_bat += L"netsh advfirewall set allprofiles state on\n";
        //m_bat += L"sc start MpsSvc\n";
		//m_bat += L"sc config MpsSvc start = auto\n";
		m_bat += L"echo 设置完毕\n";
		m_bat += L"pause\n";
		m_bat += L"cls\n";
	}

	if (m_SrceenPsw) {
		m_bat += L"echo ******************************************\n";
		m_bat += L"echo 屏幕保护口令设置\n";
		m_bat += L"echo ******************************************\n";
		m_bat += L"echo .\n";
		m_bat += L"reg add \"HKEY_CURRENT_USER\\Control Panel\\Desktop\" /v ScreenSaveActive /t REG_SZ /d 1 /f\n";
		m_bat += L"reg add \"HKEY_CURRENT_USER\\Control Panel\\Desktop\" /v ScreenSaverIsSecure / t REG_SZ /d 1 /f\n";
		m_bat += L"reg add \"HKEY_CURRENT_USER\\Control Panel\\Desktop\" /v ScreenSaveTimeOut /t REG_SZ /d 300 /f\n";
		m_bat += L"echo 设置完毕\n";
		m_bat += L"echo.\n";
		m_bat += L"pause\n";
	}

	if (m_DisablePortRdp) {
		m_bat += L"@echo off\n";
		m_bat += L"%1 mshta vbscript:CreateObject(\"Shell.Application\").ShellExecute(\"cmd.exe\",\"/c %~s0 ::\",\",\"runas\",1)(window.close)&&exit\n";
		m_bat += L"cd /d \"%~dp0\"\n";
		m_bat += L"mode con : cols = 85 lines = 30\n";
		m_bat += L": Ok\n";
		m_bat += L"title  关闭SMB安全加固工具\n";
		m_bat += L"color 0A\n";
		m_bat += L"cls\n";
		m_bat += L"echo **********************************关闭高危端口**************************************\n";
		m_bat += L"echo * 必须以系统管理员身份运行，以下提供此工具所做的操作的介绍：\n";
		m_bat += L"echo.\n";
		m_bat += L"echo 0：WINXP加固 1：WIN7加固 2：WIN10加固 3：WIN2003加固 4：WIN2008加固 5：WIN2012加固\n";
		m_bat += L"echo       6.WIN2016加固\n";
		m_bat += L"echo.\n";
		m_bat += L"echo       7: 退出\n";
		m_bat += L"echo \n";
		m_bat += L"echo *************************************************************************************\n";
		m_bat += L"echo .\n";
		m_bat += L"set start=\n";
		m_bat += L"set /p start=  输入(0 1 2 3 4 5 6)后按回车键 :\n";
		m_bat += L"if \"%start%\"==\"0\" goto WINXP\n";
		m_bat += L"if \"%start%\"==\"1\" goto WIN7\n";
		m_bat += L"if \"%start%\"==\"2\" goto WIN10\n";
		m_bat += L"if \"%start%\"==\"3\" goto WIN2003\n";
		m_bat += L"if \"%start%\"==\"4\" goto WIN2008\n";
		m_bat += L"if \"%start%\"==\"5\" goto WIN2012\n";
		m_bat += L"if \"%start%\"==\"6\" goto WIN2016\n";
		m_bat += L"if \"%start%\"==\"7\" goto quit\n";
		m_bat += L"goto Ok\n";
		m_bat += L"\n";
		m_bat += L":WINXP\n";
		m_bat += L"netsh firewall set opmode mode =enable\n";
		m_bat += L"netsh firewall set portopening protocol=tcp port=135 mode=disable name=eny135\n";
		m_bat += L"netsh firewall set portopening protocol=tcp port=136 mode=disable name=deny136\n";
		m_bat += L"netsh firewall set portopening protocol=tcp port=137 mode=disable name=deny137\n";
		m_bat += L"netsh firewall set portopening protocol=tcp port=138 mode=disable name=deny138\n";
		m_bat += L"netsh firewall set portopening protocol=tcp port=139 mode=disable name=deny139\n";
		m_bat += L"netsh firewall set portopening protocol=tcp port=445 mode=disable name=deny445\n";
		m_bat += L"netsh firewall set portopening protocol=tcp port=3389 mode=disable name=deny3389\n";
		m_bat += L"echo **************************************************************************************\n";
		m_bat += L"echo * Windows XP系统加固命令执行完毕！\n";
		m_bat += L"echo .\n";
		m_bat += L"pause\n";
		m_bat += L"goto Ok\n";
		m_bat += L":WIN7\n";
		m_bat += L"%1 mshta vbscript:CreateObject(\"Shell.Application\").ShellExecute(\"cmd.exe\", \"/c %~s0 ::\",\"\",\"runas\",1)(window.close) && exit\n";
		m_bat += L"cd /d \"%~dp0\"\n";
		m_bat += L"::开启ipsec服务\n";
		m_bat += L"sc config \"PolicyAgent\" start=auto\n";
		m_bat += L"sc start PolicyAgent\n";
		m_bat += L"netsh ipsec static add policy name=deny445\n";
		m_bat += L"netsh ipsec static add filterlist name=block\n";
		m_bat += L"netsh ipsec static add filteraction name=block action=block\n";
		m_bat += L"netsh ipsec static add filter filterlist = block any srcmask = 32 srcport = 0 dstaddr = me dstport = 21 protocol = tcp description = 21\n";
		m_bat += L"netsh ipsec static add filter filterlist = block any srcmask = 32 srcport = 0 dstaddr = me dstport = 135 protocol = tcp description = 135\n";
		m_bat += L"netsh ipsec static add filter filterlist = block any srcmask = 32 srcport = 0 dstaddr = me dstport = 137 protocol = tcp description = 137\n";
		m_bat += L"netsh ipsec static add filter filterlist = block any srcmask = 32 srcport = 0 dstaddr = me dstport = 138 protocol = tcp description = 138\n";
		m_bat += L"netsh ipsec static add filter filterlist = block any srcmask = 32 srcport = 0 dstaddr = me dstport = 139 protocol = tcp description = 139\n";
		m_bat += L"netsh ipsec static add filter filterlist = block any srcmask = 32 srcport = 0 dstaddr = me dstport = 445 protocol = tcp description = 445\n";
		m_bat += L"netsh ipsec static add filter filterlist = block any srcmask = 32 srcport = 0 dstaddr = me dstport = 3389 protocol = tcp description = 3389\n";
		m_bat += L"netsh ipsec static add rule name = block policy = deny445 filterlist = block filteraction = block\n";
		m_bat += L"netsh ipsec static set policy name = deny445 assign = y\n";
		m_bat += L"echo **************************************************************************************\n";
		m_bat += L"echo * Windows 7系统加固命令执行完毕！\n";
		m_bat += L"echo .\n";
		m_bat += L"pause\n";
		m_bat += L"goto Ok\n";
		m_bat += L":WIN10\n";
		m_bat += L"%1 mshta vbscript:CreateObject(\"Shell.Application\").ShellExecute(\"cmd.exe\", \"/c %~s0 ::\",\"\",\"runas\",1)(window.close)&&exit\n";
		m_bat += L"cd /d \"%~dp0\"\n";
		m_bat += L"::开启ipsec服务\n";
		m_bat += L"sc config \"PolicyAgent\" start=auto\n";
		m_bat += L"sc start PolicyAgent\n";
		m_bat += L"netsh ipsec static add policy name=deny445\n";
		m_bat += L"netsh ipsec static add filterlist name = block\n";
		m_bat += L"netsh ipsec static add filteraction name=block action =block\n";
		m_bat += L"netsh ipsec static add filter filterlist=block any srcmask=32 srcport=0 dstaddr=me dstport=21 protocol=tcp description=21\n";
		m_bat += L"netsh ipsec static add filter filterlist=block any srcmask=32 srcport=0 dstaddr=me dstport=21 protocol=tcp description=135\n";
		m_bat += L"netsh ipsec static add filter filterlist=block any srcmask=32 srcport=0 dstaddr=me dstport=21 protocol=tcp description=137\n";
		m_bat += L"netsh ipsec static add filter filterlist=block any srcmask=32 srcport=0 dstaddr=me dstport=21 protocol=tcp description=138\n";
		m_bat += L"netsh ipsec static add filter filterlist=block any srcmask=32 srcport=0 dstaddr=me dstport=21 protocol=tcp description=139\n";
		m_bat += L"netsh ipsec static add filter filterlist=block any srcmask=32 srcport=0 dstaddr=me dstport=21 protocol=tcp description=445\n";
		m_bat += L"netsh ipsec static add filter filterlist=block any srcmask=32 srcport=0 dstaddr=me dstport=21 protocol=tcp description=3389\n";
		m_bat += L"netsh ipsec static add rule name = block policy = deny445 filterlist = block filteraction = block\n";
		m_bat += L"netsh ipsec static set policy name = deny445 assign = y\n";
		m_bat += L"echo *****************************************************************************************\n";
		m_bat += L"echo * Windows 10系统加固命令执行完毕！\n";
		m_bat += L"echo .\n";
		m_bat += L"pause\n";
		m_bat += L"goto Ok\n";
		m_bat += L":WIN2003\n";
		m_bat += L"net stop server > nul\n";
		m_bat += L"	net start sharedaccess > nul\n";
		m_bat += L"sc config lanmanserver start = disabled\n";
		m_bat += L"netsh firewall add portopening protocol = ALL port = 21 name = DenyEquationTCP mode = DISABLE scope = ALL profile = ALL > nul\n";
		m_bat += L"netsh firewall add portopening protocol = ALL port = 135 name = DenyEquationTCP mode = DISABLE scope = ALL profile = ALL > nul\n";
		m_bat += L"netsh firewall add portopening protocol = ALL port = 136 name = DenyEquationTCP mode = DISABLE scope = ALL profile = ALL > nul\n";
		m_bat += L"netsh firewall add portopening protocol = ALL port = 137 name = DenyEquationTCP mode = DISABLE scope = ALL profile = ALL > nul\n";
		m_bat += L"netsh firewall add portopening protocol = ALL port = 138 name = DenyEquationTCP mode = DISABLE scope = ALL profile = ALL > nul\n";
		m_bat += L"netsh firewall add portopening protocol = ALL port = 445 name = DenyEquationTCP mode = DISABLE scope = ALL profile = ALL > nul\n";
		m_bat += L"netsh firewall add portopening protocol = ALL port = 3389 name = DenyEquationTCP mode = DISABLE scope = ALL profile = ALL > nul\n";
		m_bat += L"echo ****************************************************************************\n";
		m_bat += L"echo * Windows Server 2003系统加固命令执行完毕！\n";
		m_bat += L"echo .\n";
		m_bat += L"pause\n";
		m_bat += L"goto Ok\n";
		m_bat += L":WIN2008\n";
		m_bat += L"%1 mshta vbscript : CreateObject(\"Shell.Application\").ShellExecute(\"cmd.exe\", \"/c %~s0 ::\", \"\", \"runas\", 1)(window.close) && exit\n";
		m_bat += L"cd /d \"%~dp\"\n";
		m_bat += L"::开启ipsec服务\n";
		m_bat += L"sc config \"PolicyAgent\" start = auto\n";
		m_bat += L"sc start PolicyAgent\n";
		m_bat += L"netsh ipsec static add policy name = deny445\n";
		m_bat += L"netsh ipsec static add filterlist name = block\n";
		m_bat += L"netsh ipsec static add filteraction name = block action = block\n";
		m_bat += L"netsh ipsec static add filter filterlist = block any srcmask = 32 srcport = 0 dstaddr = me dstport = 21 protocol = tcp description = 21\n";
		m_bat += L"netsh ipsec static add filter filterlist = block any srcmask = 32 srcport = 0 dstaddr = me dstport = 135 protocol = tcp description = 135\n";
		m_bat += L"netsh ipsec static add filter filterlist = block any srcmask = 32 srcport = 0 dstaddr = me dstport = 137 protocol = tcp description = 137\n";
		m_bat += L"netsh ipsec static add filter filterlist = block any srcmask = 32 srcport = 0 dstaddr = me dstport = 138 protocol = tcp description = 138\n";
		m_bat += L"netsh ipsec static add filter filterlist = block any srcmask = 32 srcport = 0 dstaddr = me dstport = 139 protocol = tcp description = 139\n";
		m_bat += L"netsh ipsec static add filter filterlist = block any srcmask = 32 srcport = 0 dstaddr = me dstport = 445 protocol = tcp description = 445\n";
		m_bat += L"netsh ipsec static add filter filterlist = block any srcmask = 32 srcport = 0 dstaddr = me dstport = 3389 protocol = tcp description = 3389\n";
		m_bat += L"netsh ipsec static add rule name = block policy = deny445 filterlist = block filteraction = block\n";
		m_bat += L"netsh ipsec static set policy name = deny445 assign = y\n";
		m_bat += L"echo *************************************************************************\n";
		m_bat += L"echo * Windows Server 2008系统加固命令执行完毕！\n";
		m_bat += L"echo .\n";
		m_bat += L"pause\n";
		m_bat += L"goto Ok\n";
		m_bat += L":WIN2012\n";
		m_bat += L"%1 mshta vbscript : CreateObject(\"Shell.Application\").ShellExecute(\"cmd.exe\", \"/c %~s0 ::\", \"\", \"runas\", 1)(window.close) && exit\n";
		m_bat += L"cd /d \"%~dp0\"\n";
		m_bat += L"::开启ipsec服务\n";
		m_bat += L"sc config \"PolicyAgent\" start = auto\n";
		m_bat += L"sc start PolicyAgent\n";
		m_bat += L"netsh ipsec static add policy name = deny445\n";
		m_bat += L"netsh ipsec static add filterlist name = block\n";
		m_bat += L"netsh ipsec static add filteraction name = block action = block\n";
		m_bat += L"netsh ipsec static add filter filterlist = block any srcmask = 32 srcport = 0 dstaddr = me dstport = 21 protocol = tcp description = 21\n";
		m_bat += L"netsh ipsec static add filter filterlist = block any srcmask = 32 srcport = 0 dstaddr = me dstport = 135 protocol = tcp description = 135\n";
		m_bat += L"netsh ipsec static add filter filterlist = block any srcmask = 32 srcport = 0 dstaddr = me dstport = 137 protocol = tcp description = 137\n";
		m_bat += L"netsh ipsec static add filter filterlist = block any srcmask = 32 srcport = 0 dstaddr = me dstport = 138 protocol = tcp description = 138\n";
		m_bat += L"netsh ipsec static add filter filterlist = block any srcmask = 32 srcport = 0 dstaddr = me dstport = 139 protocol = tcp description = 139\n";
		m_bat += L"netsh ipsec static add filter filterlist = block any srcmask = 32 srcport = 0 dstaddr = me dstport = 445 protocol = tcp description = 445\n";
		m_bat += L"netsh ipsec static add filter filterlist = block any srcmask = 32 srcport = 0 dstaddr = me dstport = 3389 protocol = tcp description = 3389\n";
		m_bat += L"netsh ipsec static add rule name = block policy = deny445 filterlist = block filteraction = block\n";
		m_bat += L"netsh ipsec static set policy name = deny445 assign = y\n";
		m_bat += L"echo **********************************************************************\n";
		m_bat += L"echo * Windows Server 2012系统加固命令执行完毕！\n";
		m_bat += L"echo .\n";
		m_bat += L"pause\n";
		m_bat += L"goto Ok\n";
		m_bat += L":WIN2016\n";
		m_bat += L"% 1 mshta vbscript : CreateObject(\"Shell.Application\").ShellExecute(\"cmd.exe\", \"/c %~s0 ::\", \"\", \"runas\", 1)(window.close) && exit\n";
		m_bat += L"cd /d \"%~dp0\"\n";
		m_bat += L"::开启ipsec服务\n";
		m_bat += L"sc config \"PolicyAgent\" start = auto\n";
		m_bat += L"sc start PolicyAgent\n";
		m_bat += L"netsh ipsec static add policy name = deny445\n";
		m_bat += L"netsh ipsec static add filterlist name = block\n";
		m_bat += L"netsh ipsec static add filteraction name = block action = block\n";
		m_bat += L"netsh ipsec static add filter filterlist = block any srcmask = 32 srcport = 0 dstaddr = me dstport = 21 protocol = tcp description = 21\n";
		m_bat += L"netsh ipsec static add filter filterlist = block any srcmask = 32 srcport = 0 dstaddr = me dstport = 135 protocol = tcp description = 135\n";
		m_bat += L"netsh ipsec static add filter filterlist = block any srcmask = 32 srcport = 0 dstaddr = me dstport = 137 protocol = tcp description = 137\n";
		m_bat += L"netsh ipsec static add filter filterlist = block any srcmask = 32 srcport = 0 dstaddr = me dstport = 138 protocol = tcp description = 138\n";
		m_bat += L"netsh ipsec static add filter filterlist = block any srcmask = 32 srcport = 0 dstaddr = me dstport = 139 protocol = tcp description = 139\n";
		m_bat += L"netsh ipsec static add filter filterlist = block any srcmask = 32 srcport = 0 dstaddr = me dstport = 445 protocol = tcp description = 445\n";
		m_bat += L"netsh ipsec static add filter filterlist = block any srcmask = 32 srcport = 0 dstaddr = me dstport = 3389 protocol = tcp description = 3389\n";
		m_bat += L"netsh ipsec static add rule name = block policy = deny445 filterlist = block filteraction = block\n";
		m_bat += L"netsh ipsec static set policy name = deny445 assign = y\n";
		m_bat += L"echo **************************************************************\n";
		m_bat += L"echo * Windows Server 2016系统加固命令执行完毕！\n";
		m_bat += L"echo .\n";
		m_bat += L"pause\n";
		m_bat += L"goto Ok\n";
	} 



	setlocale(LC_CTYPE, "chs");
	file.WriteString(m_bat);
	file.Close();
	HINSTANCE Hinst = ShellExecute(this->m_hWnd, _T("open"), _T("..\\1.bat"), NULL, NULL, SW_SHOWNORMAL);
	if ((int)Hinst <= 32)
	{
		MessageBox(_T("创建升级窗口失败！"));
	}
	/*HINSTANCE Hinst = ShellExecute(this->m_hWnd, _T("open"), _T("..\\2.bat"), NULL, NULL, SW_SHOWNORMAL);
	if ((int)Hinst <= 32)
	{
		MessageBox(_T("创建升级窗口失败！"));
	}*/
}

//以下代码用来获取版本build号
BOOL CGPDialogDlg::GetVersionEx2(LPOSVERSIONINFOW lpVersionInformation)
{
	HMODULE hNtDll = GetModuleHandleW(L"NTDLL"); // 获取ntdll.dll的句柄
	typedef long (NTAPI* tRtlGetVersion)(_Out_ PRTL_OSVERSIONINFOW povi); // RtlGetVersion的原型
	tRtlGetVersion pRtlGetVersion = NULL;
	if (hNtDll)
	{
		pRtlGetVersion = (tRtlGetVersion)GetProcAddress(hNtDll, "RtlGetVersion"); // 获取RtlGetVersion地址
	}
	if (pRtlGetVersion)
	{
		return pRtlGetVersion((PRTL_OSVERSIONINFOW)lpVersionInformation) >= 0; // 调用RtlGetVersion
	}
	return FALSE;
}

//下面代码测试是是32位还是64位程序
BOOL CGPDialogDlg:: IsAppProcessWOW64(void)
{
	typedef BOOL(WINAPI* LPFN_ISWOW64PROCESS)(HANDLE, PBOOL);
	HMODULE hKernel32 = GetModuleHandle(L"kernel32");
	if (hKernel32)
	{
		LPFN_ISWOW64PROCESS lpfnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress(hKernel32, "IsWow64Process");
		if (lpfnIsWow64Process)
		{
			BOOL bIsWow64 = FALSE;
			if (lpfnIsWow64Process(GetCurrentProcess(), &bIsWow64))
				return bIsWow64;
		}
	}
	return false;
}

DWORD CGPDialogDlg::getOSName()
{
	typedef LONG(__stdcall* fnRtlGetVersion)(PRTL_OSVERSIONINFOW lpVersionInformation);
	fnRtlGetVersion pRtlGetVersion;
	HMODULE hNtdll;
	LONG ntStatus;
	ULONG    dwMajorVersion = 0;
	ULONG    dwMinorVersion = 0;
	ULONG    dwBuildNumber = 0;
	RTL_OSVERSIONINFOW VersionInformation = { 0 };
	DWORD OsVersion = 0;
	do
	{
		hNtdll = GetModuleHandle(L"ntdll.dll");
		if (hNtdll == NULL)break;

		pRtlGetVersion = (fnRtlGetVersion)GetProcAddress(hNtdll, "RtlGetVersion");
		if (pRtlGetVersion == NULL)break;

		VersionInformation.dwOSVersionInfoSize = sizeof(RTL_OSVERSIONINFOW);
		ntStatus = pRtlGetVersion(&VersionInformation);

		if (ntStatus != 0)break;

		dwMajorVersion = VersionInformation.dwMajorVersion;
		dwMinorVersion = VersionInformation.dwMinorVersion;
		dwBuildNumber = VersionInformation.dwBuildNumber;

		if (dwMajorVersion == 6 && dwMinorVersion == 1) 
			OsVersion = WIN7;
		else if (dwMajorVersion == 6 && dwMinorVersion == 2 && dwBuildNumber == 9200)
			OsVersion = WIN89200;
		else if (dwMajorVersion == 6 && dwMinorVersion == 2)
			OsVersion = WIN8;

		else if (dwMajorVersion == 6 && dwMinorVersion == 3 && dwBuildNumber == 9600)
			OsVersion = WIN819600;
		else if (dwMajorVersion == 6 && dwMinorVersion == 3)
			OsVersion = WIN81;

		else if (dwMajorVersion == 10 && dwMinorVersion == 0 && dwBuildNumber == 10240)
			OsVersion = WIN101607;
		else if (dwMajorVersion == 10 && dwMinorVersion == 0 && dwBuildNumber == 10586)
			OsVersion = WIN1010586;
		else if (dwMajorVersion == 10 && dwMinorVersion == 0 && dwBuildNumber == 14393)
			OsVersion = WIN1014393;
		else if (dwMajorVersion == 10 && dwMinorVersion == 0)

		{
			OsVersion = WIN10;
			AfxMessageBox(L"确认系统是WIN10");
		}
		else
		{
			return FALSE;
		}


	} while (FALSE);
	return OsVersion;
	/*CString osName = _T("");
	int a = 0, b = 0, i = 0, j = 0, win = 0;
	_asm
	{
		pushad
		mov ebx, fs: [0x18] ; get self pointer from TEB
		mov eax, fs: [0x30] ; get pointer to PEB / database
		mov ebx, [eax + 0A8h]; get OSMinorVersion
		mov eax, [eax + 0A4h]; get OSMajorVersion
		mov j, ebx
		mov i, eax
		popad
	}

	if ((i == 6) && (j == 1))
	{
	osName = _T("当前系统版本为：Windows 7");
	win = 7;
	}

	else if ((i == 10) && (j == 0))
	{
		osName = _T("当前系统版本为：Windows 10");
		win = 10;
	}
	else
	{
		osName = _T("当前系统不属于WIN7或WIN10");
		win = 0;
	}
	return win;*/
}

ULONG CGPDialogDlg::getBuildNum()
{
	ULONG    dwBuildNumber = 0;
	OSVERSIONINFOEXW ovi = { sizeof ovi };
	GetVersionEx2((LPOSVERSIONINFOW)&ovi);
	dwBuildNumber = ovi.dwBuildNumber;
	CString temp_value = _T("");
	temp_value.Format(_T("你的系统版本是%d"), dwBuildNumber);
	AfxMessageBox(temp_value);
	return dwBuildNumber;
}

//它的功能把systeminfo信息和pathKB补丁进行对比
void CGPDialogDlg::strContrast(CString str1, CString str2) {

	if (_tcsstr(str1, str2))
	{
		AfxMessageBox(_T("兄弟，你按要求安装补丁~不扣你绩效了"));
	}
	else
		AfxMessageBox(_T("注意！！没有按要求安装安全补丁"));

}


void CGPDialogDlg::checkMSpack()
{

	//调用CreatePipe创建管道
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;  //使用系统默认的安全描述符	
	sa.bInheritHandle = TRUE;  //创建的进程继承句柄

	if (!CreatePipe(&hRead, &hWrite, &sa, 0))  //创建匿名管道
	{
		MessageBox(_T("CreatePipe Failed!"), _T("Tip"), MB_OK | MB_ICONWARNING);
		return;
	}

	//创建子进程
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	GetStartupInfo(&si);
	//si.hStdInput = hRead;
	si.hStdOutput = hWrite;	 //新创建进程的标准输出连在写管道一端
	si.hStdError = GetStdHandle(STD_ERROR_HANDLE);
	si.wShowWindow = SW_HIDE;  //隐藏窗口	
	


	TCHAR cmdline[256] = { _T("C:\\WINDOWS\\system32\\cmd.exe /C systeminfo") };
	//CString tmp,stredit2;
//	GetDlgItemText(IDC_EDIT2,stredit2);  //获取编辑框中输入的命令行
//	tmp.Format(_T("cmd /C %s"),stredit2);
//	_stprintf(cmdline,_T("%s"),tmp);
#ifdef _UNICODE
	//MessageBox(_T("UNICODE!"), _T("提示"), MB_OK | MB_ICONWARNING);
#else
	//MessageBox(_T("ANSI!"), _T("提示"), MB_OK | MB_ICONWARNING);
#endif
	if (!CreateProcess(0,cmdline, NULL, NULL,TRUE, 0, NULL, NULL, &si, &pi))  //创建子进程
	{
		CloseHandle(hRead);
		CloseHandle(hWrite);

		MessageBox(_T("CreateProcess Failed!"), _T("Tip"), MB_OK | MB_ICONWARNING);
		return;
	} else {
		CloseHandle(pi.hProcess);//关闭管道句柄   问题出在这里 注销就好了
		CloseHandle(pi.hThread);
		CloseHandle(hWrite);
	}
	char buffer[4096] = { 0 };
	CString strOutput;
	CString PatchKB = {_T("不用装")};
	DWORD bytesRead;
	bool is64app;
	is64app = IsAppProcessWOW64();
	DWORD i = getOSName();
	ULONG j = getBuildNum();

	while (true) {
		if (ReadFile(hRead, buffer, 4095, &bytesRead, NULL) == NULL)  //读取管道
			break;

		strOutput += buffer;
		//SetDlgItemText(IDC_EDIT1, strOutput);  //显示输出信息到编辑框,并刷新窗口
		AfxMessageBox(strOutput);
		//UpdateWindow();
		//Sleep(100);
	}
	if (i == WIN7 && is64app) {
		PatchKB = { _T("KB4012212") };
		strContrast(strOutput, PatchKB);
	}
	else if (i == WIN7 && is64app == 0) {
		PatchKB = { _T("KB4012215") };
		strContrast(strOutput, PatchKB);

	}else if (i == WIN101607){
		PatchKB = { _T("KB4013429") };
		strContrast(strOutput, PatchKB);
	}else
		{
			AfxMessageBox(_T("你的系统不需要安装补丁"));
		}
			
	CloseHandle(hRead);
	//CloseHandle(pi.hProcess);//关闭管道句柄   问题出在这里 注销就好了
    //CloseHandle(pi.hThread);
	//getOSName();

	//	CDialog::OnOK();

	/*以下使用IsWindows10OrGreater判断是否是WIN10 但是无效
	if (IsWindows7OrGreater()){
		AfxMessageBox(_T("确认过眼神是WIN10"));
	}else{
		AfxMessageBox(_T("你不是WIN10"));
	}*/



}



void CGPDialogDlg::OnBnClickedcheckupdate()
{
	// TODO: 在此添加控件通知处理程序代码


	checkMSpack();
	


}


