
// NamePipeSrvView.cpp: CNamePipeSrvView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "NamePipeSrv.h"
#endif

#include "NamePipeSrvDoc.h"
#include "NamePipeSrvView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNamePipeSrvView

IMPLEMENT_DYNCREATE(CNamePipeSrvView, CView)

BEGIN_MESSAGE_MAP(CNamePipeSrvView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(IDM_PIPE_CREATE, &CNamePipeSrvView::OnPipeCreate)
	ON_COMMAND(IDM_PIPE_READ, &CNamePipeSrvView::OnPipeRead)
	ON_COMMAND(IDM_PIPE_WRITE, &CNamePipeSrvView::OnPipeWrite)
END_MESSAGE_MAP()

// CNamePipeSrvView 构造/析构

CNamePipeSrvView::CNamePipeSrvView() noexcept
{
	// TODO: 在此处添加构造代码
	hPipe = NULL;

}

CNamePipeSrvView::~CNamePipeSrvView()
{
	if (hPipe)
		CloseHandle(hPipe);
}

BOOL CNamePipeSrvView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CNamePipeSrvView 绘图

void CNamePipeSrvView::OnDraw(CDC* /*pDC*/)
{
	CNamePipeSrvDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CNamePipeSrvView 打印

BOOL CNamePipeSrvView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CNamePipeSrvView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CNamePipeSrvView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CNamePipeSrvView 诊断

#ifdef _DEBUG
void CNamePipeSrvView::AssertValid() const
{
	CView::AssertValid();
}

void CNamePipeSrvView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CNamePipeSrvDoc* CNamePipeSrvView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNamePipeSrvDoc)));
	return (CNamePipeSrvDoc*)m_pDocument;
}
#endif //_DEBUG


// CNamePipeSrvView 消息处理程序


void CNamePipeSrvView::OnPipeCreate()
{
	// TODO: 在此添加命令处理程序代码
	hPipe = CreateNamedPipe(L"\\\\.\\pipe\\MyPipe",
		PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED,
		0, 1, 1024, 1024, 0, NULL);
	if (INVALID_HANDLE_VALUE == hPipe) {
		MessageBox(L"创建命名管道失败！");
		hPipe = NULL;
		return;
	}
	//创建匿名的人工重置事件对象
	HANDLE hEvent;
	hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	if (!hEvent) {
		MessageBox(L"创建事件对象失败！");
		CloseHandle(hPipe);
		hPipe = NULL;
		return;
	}
	OVERLAPPED ovlap;
	ZeroMemory(&ovlap, sizeof(OVERLAPPED));
	ovlap.hEvent = hEvent;
	//等待客户端请求的到来
	if(!ConnectNamedPipe(hPipe,&ovlap)){
		if (ERROR_IO_PENDING != GetLastError()) {
			MessageBox(L"等待客户端连接失败！");
			CloseHandle(hPipe);
			CloseHandle(hEvent);
			hPipe = NULL;
			return;
	    }
	}
	if (WAIT_FAILED == WaitForSingleObject(hEvent, INFINITE)) {
		MessageBox(L"等待对象失败！");
		CloseHandle(hPipe);
		CloseHandle(hEvent);
		hPipe = NULL;
		return;
	}
	CloseHandle(hEvent);
}


void CNamePipeSrvView::OnPipeRead()
{
	// TODO: 在此添加命令处理程序代码
	char buf[100];
	DWORD dwRead;
	if (!ReadFile(hPipe, buf, 100, &dwRead, NULL)) {
		MessageBox(L"读取数据失败！");
		return;
	}
	USES_CONVERSION;
	MessageBox(A2T(buf));
}


void CNamePipeSrvView::OnPipeWrite()
{
	// TODO: 在此添加命令处理程序代码
	char buf[] = "http://www.cynric.me";
	DWORD dwWrite;
	if (!WriteFile(hPipe, buf, strlen(buf) + 1, &dwWrite, NULL)) {
		MessageBox(L"写入数据失败！");
		return;
	}
}
