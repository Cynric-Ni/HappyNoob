
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

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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
{
	m_ch1 = L"12";
	m_ch2 = L"90";
	m_ch3 = L"5";
	m_ch4 = L"6";
	m_ch5 = L"16";
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

void CGPDialogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_OPENPLOCIY, m_OpenPlociy);
	DDX_Check(pDX, IDC_NO_GUEST, m_NoGuest);
	DDX_Check(pDX, IDC_OPEN_FIREWALL, m_OpenFireWall);
	DDX_Check(pDX, IDC_SCREEN_PSW, m_SrceenPsw);
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
		m_bat += L"necho 密码输错";
		m_bat += m_ch4;
		m_bat += L"次锁定\necho 锁定时间";
		m_bat += m_ch5;
		m_bat += L"分钟\n";
	}

	m_bat += L"echo .\necho [version] > 1.inf\necho signature=\"$CHICAGO$\" >>1.inf\necho [System Access] >>1.inf\necho MinimumPasswordLength =";
	m_bat += m_ch1;
	m_bat += L" >> 1.inf\necho PasswordComplexity = 1 >> 1.inf\necho MinimumPasswordAge = ";
	m_bat += m_ch3;
	m_bat += L" >> 1.inf\necho MaximumPasswordAge = ";
	m_bat += m_ch2;
	m_bat += "  >> 1.inf\n";

	if (m_ch4 != "0") {
		m_bat += L"necho LockoutBadCount = ";
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
		m_bat += L"cls";
	}

	if (m_OpenFireWall) {
		m_bat += L"echo * ***************************************\n";
		m_bat += L"echo 打开防火墙\n";
		m_bat += L"echo****************************************\n";
		m_bat += L"echo .\n";
		m_bat += L"sc start MpsSvc\n";
		m_bat += L"sc config MpsSvc start = auto\n";
		m_bat += L"echo 设置完毕\n";
		m_bat += L"pause\n";
		m_bat += L"cls\n";
	}

	if (m_SrceenPsw) {
		m_bat += L"echo******************************************\n";
		m_bat += L"echo 屏幕保护口令设置\n";
		m_bat += L"echo******************************************\n";
		m_bat += L"echo .\n";
		m_bat += L"reg add \"HKEY_CURRENT_USER\\Control Panel\\Desktop\" /v ScreenSaveActive /t REG_SZ /d 1 /f\n";
		m_bat += L"reg add \"HKEY_CURRENT_USER\\Control Panel\\Desktop\" /v ScreenSaverIsSecure / t REG_SZ /d 1 /f\n";
		m_bat += L"reg add \"HKEY_CURRENT_USER\\Control Panel\\Desktop\" /v ScreenSaveTimeOut /t REG_SZ /d 300 /f\n";
		m_bat += L"echo 设置完毕\n";
		m_bat += L"echo.\n";
		m_bat += L"pause\n";
	}
	setlocale(LC_CTYPE, "chs");
	file.WriteString(m_bat);
	file.Close();
	HINSTANCE Hinst = ShellExecute(this->m_hWnd, _T("open"), _T("..\\1.bat"), NULL, NULL, SW_SHOWNORMAL);
	if ((int)Hinst <= 32)
	{
		MessageBox(_T("创建升级窗口失败！"));
	}

}

