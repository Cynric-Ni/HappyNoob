
// chatDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "chat.h"
#include "chatDlg.h"
#include "afxdialogex.h"
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib,"ws2_32.lib")


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


// CchatDlg 对话框



CchatDlg::CchatDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHAT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CchatDlg::~CchatDlg()
{
	if (m_socket)
		closesocket(m_socket);
}

void CchatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CchatDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(UM_SOCK,OnSock)
	ON_BN_CLICKED(IDC_BTN_SEND, &CchatDlg::OnClickedBtnSend)
END_MESSAGE_MAP()


// CchatDlg 消息处理程序

BOOL CchatDlg::OnInitDialog()
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
	InitSocket();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CchatDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CchatDlg::OnPaint()
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
HCURSOR CchatDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CchatDlg::InitSocket()
{
	m_socket = WSASocket(AF_INET, SOCK_DGRAM, 0, NULL, 0, 0);
	if (INVALID_SOCKET == m_socket) {
		MessageBox(L"创建套接字失败！");
		return FALSE;
	}
	SOCKADDR_IN addrSock;
	addrSock.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSock.sin_family = AF_INET;
	addrSock.sin_port = htons(6000);
	if (SOCKET_ERROR == bind(m_socket, (SOCKADDR*)&addrSock, sizeof(SOCKADDR))) {
		MessageBox(L"绑定失败！");
		return FALSE;
	}
	if (SOCKET_ERROR == WSAAsyncSelect(m_socket, m_hWnd, UM_SOCK, FD_READ))
	{
		MessageBox(L"注册网络读取事件失败！");
		return FALSE;
	}
	return TRUE;
}

LRESULT CchatDlg::OnSock(WPARAM wParam, LPARAM lParam)
{
	switch(LOWORD(lParam)) {
		case FD_READ:
			WSABUF wsabuf;
			wsabuf.buf = new char[200]{ 0 };
			wsabuf.len = 200;
			DWORD dwRead;
			DWORD dwFlag = 0;
			SOCKADDR_IN addrFrom;
			int len = sizeof(SOCKADDR);
			CString str;
			CString strTemp;
			char tempBuf[300] = { 0 };
			char buf[INET_ADDRSTRLEN];
			if (SOCKET_ERROR == WSARecvFrom(m_socket, &wsabuf, 1, &dwRead,
				&dwFlag, (SOCKADDR*)&addrFrom, &len, NULL, NULL)) {
				MessageBox(L"接受数据失败！");
				delete[]wsabuf.buf;
				return -1;
			}
			HOSTENT* pHost;
			pHost = gethostbyaddr((char*)&addrFrom.sin_addr.S_un.S_addr, 4, AF_INET);
			sprintf_s(tempBuf, "%s 说: %s", pHost->h_name, wsabuf.buf);
			/*sprintf_s(tempBuf, "%s 说：%s", inet_ntop(AF_INET, &addrFrom.sin_addr, buf, sizeof(buf)),
				wsabuf.buf);*/  //因为这段被上面代替，上面是通过IP查找到计算机名。
			USES_CONVERSION;
			str = A2T((char*)tempBuf);
			str += "\r\n";
			GetDlgItemText(IDC_EDIT_RECV, strTemp);
			str += strTemp;

			SetDlgItemText(IDC_EDIT_RECV, str);
			delete[] wsabuf.buf;
			break;
	}
	return 0;
}

void CchatDlg::OnClickedBtnSend()
{
	// TODO: 在此添加控件通知处理程序代码
	DWORD dwIP;
	CString strSend;
	WSABUF wsabuf;
	DWORD dwSend;
	SOCKADDR_IN addrTo;
	CString strHostName;
	HOSTENT* pHost;

	USES_CONVERSION;

	if (GetDlgItemText(IDC_EDIT_HOSTNAME,strHostName), strHostName == "") {
		((CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS1))->GetAddress(dwIP);
		addrTo.sin_addr.S_un.S_addr = htonl(dwIP);
	}else {
		pHost = gethostbyname(T2A(strHostName));
		addrTo.sin_addr.S_un.S_addr = *((DWORD*)pHost->h_addr_list[0]);
	}
	
	addrTo.sin_family = AF_INET;
	addrTo.sin_port = htons(6000);

	GetDlgItemText(IDC_EDIT_SEND, strSend);

	wsabuf.buf = T2A(strSend);
	wsabuf.len = strlen(wsabuf.buf) + 1;

	SetDlgItemText(IDC_EDIT_SEND, L"");
	if (SOCKET_ERROR == WSASendTo(m_socket, &wsabuf, 1, &dwSend, 0,
		(SOCKADDR*)&addrTo, sizeof(SOCKADDR), NULL, NULL)) {
		MessageBox(L"发送数据失败！");
		return;
	}
}
