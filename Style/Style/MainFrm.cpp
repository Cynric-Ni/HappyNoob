
// MainFrm.cpp: CMainFrame 类的实现
//

#include "pch.h"
#include "framework.h"
#include "Style.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_COMMAND(IDM_VIEW_NEWTOOLBAR, &CMainFrame::OnViewNewtoolbar)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_NEWTOOLBAR, &CMainFrame::OnUpdateViewNewtoolbar)
	ON_MESSAGE(UM_PROGRESS,&CMainFrame::OnProgress)
	ON_WM_PAINT()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	IDS_TIMER,
	IDS_PROGRESS,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame() noexcept
{
	// TODO: 在此添加成员初始化代码
	//m_hIcons{};
}

CMainFrame::~CMainFrame()
{
}
extern CStyleApp theApp;
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	//下面工具栏不是默认的 是自定义的对象newToolBar 加载的也是自定义IDR_MAINFRAME1   倪忻亮
	if (!m_newToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_RIGHT | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_newToolBar.LoadToolBar(IDR_TOOLBAR1))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: 如果不需要可停靠工具栏，则删除这三行
	m_newToolBar.EnableDocking(CBRS_ALIGN_ANY);
	//EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_newToolBar);

	//SetWindowLong(m_hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);
	//SetWindowLong(m_hWnd, GWL_STYLE, GetWindowLong(m_hWnd, GWL_STYLE) & ~WS_MAXIMIZEBOX);
	//memset(m_hIcons, 0, sizeof(m_hIcons));
	SetClassLongPtr(m_hWnd, GCLP_HICON, (LONG_PTR  )LoadIcon(NULL, IDI_ERROR));
	m_hIcons[0] = LoadIconW(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON1));
	m_hIcons[1] = LoadIconW(theApp.m_hInstance, MAKEINTRESOURCE(IDI_ICON2));
	m_hIcons[2] = LoadIconW(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON3));

	SetClassLongPtr(m_hWnd, GCLP_HICON, (LONG_PTR)m_hIcons[0]);
	SetTimer(1, 1000, NULL);
	
	CTime t = CTime::GetCurrentTime();//新版本MFC 改成GetTickCount() 倪忻亮
	CString str = t.Format("%H:%M:%S");
	m_wndStatusBar.SetPaneText(1, str);
	CClientDC dc(this);
	CSize sz = dc.GetTextExtent(str);
	int index = 0;
	index = m_wndStatusBar.CommandToIndex(IDS_TIMER);
	m_wndStatusBar.SetPaneInfo(index, IDS_TIMER, SBPS_NORMAL, sz.cx);
	m_wndStatusBar.SetPaneText(index, str);
    //进度条创建过程
	/*CRect rect;
	m_wndStatusBar.GetItemRect(2, &rect);
	m_progress.Create(WS_CHILD | WS_VISIBLE, rect,
					&m_wndStatusBar, 123);
	m_progress.SetPos(50);*/

	//SendMessageW(UM_PROGRESS);用下面的Post方式代替Send 可以在OnCreate()函数完毕之后在执行Post消息，因为Post是寄送形式
	//PostMessage(UM_PROGRESS);它把消息放在队列里等待get获取执行，不过他目前已经被OnPaint代替因为程序执行的第一次启用了OnPaint
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	/*cs.cx = 300;
	cs.cy = 200;
	cs.lpszName = "http://www.cynric.me";
	cs.style = cs.style & ~FWS_ADDTOTITLE;*/
	/*WNDCLASS  wndcls;
	wndcls.cbClsExtra = 0;
	wndcls.cbWndExtra = 0;
	wndcls.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndcls.hCursor = LoadCursor(NULL, IDC_HELP);
	wndcls.hIcon = LoadIcon(NULL, IDI_ERROR);
	wndcls.hInstance = AfxGetInstanceHandle();
	wndcls.lpfnWndProc = ::DefWindowProc;
	wndcls.lpszClassName = _T("cynric.me");
	wndcls.lpszMenuName = NULL;
	wndcls.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wndcls);
	cs.lpszClass = _T("cynric.me");*/
	//cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW, 0, 0, LoadIcon(NULL, IDI_WARNING));
	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序



void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	static int index = 0;
	SetClassLongPtr(m_hWnd, GCLP_HICON, (LONG_PTR)m_hIcons[index]);
	index = ++index % 3;

	CTime t = CTime::GetCurrentTime();
	CString str = t.Format("%H:%M:%S");
	CClientDC dc(this);
	CSize sz = dc.GetTextExtent(str);
	m_wndStatusBar.SetPaneInfo(1, IDS_TIMER, SBPS_NORMAL, sz.cx);
	m_wndStatusBar.SetPaneText(1, str);
	
	m_progress.StepIt();

	CFrameWnd::OnTimer(nIDEvent);
}


void CMainFrame::OnViewNewtoolbar()
{
	// TODO: 在此添加命令处理程序代码
	/*if (m_newToolBar.IsVisible()) {
		m_newToolBar.ShowWindow(SW_HIDE);
		}else{
		m_newToolBar.ShowWindow(SW_SHOW);
	}
	RecalcLayout();
	DockControlBar(&m_newToolBar);*/
	//用以下代码代替以上代码 倪忻亮
	ShowControlBar(&m_newToolBar, !m_newToolBar.IsWindowVisible(), FALSE);
}


void CMainFrame::OnUpdateViewNewtoolbar(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_newToolBar.IsWindowVisible());
}

LRESULT CMainFrame::OnProgress(WPARAM wparam, LPARAM lparam)
{
	CRect rect;
	m_wndStatusBar.GetItemRect(2, &rect);
	m_progress.Create(WS_CHILD | WS_VISIBLE, rect, &m_wndStatusBar, 123);
	m_progress.SetPos(50);
	return 0;
}

void CMainFrame::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CFrameWnd::OnPaint()
	CRect rect;
	m_wndStatusBar.GetItemRect(2, &rect);
	if (!m_progress.m_hWnd) {
		m_progress.Create(WS_CHILD | WS_VISIBLE, rect, &m_wndStatusBar, 123);
		
	}else{
		m_progress.MoveWindow(rect);
	}
	m_progress.SetPos(50);
}
