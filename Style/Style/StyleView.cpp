
// StyleView.cpp: CStyleView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Style.h"
#endif

#include "StyleDoc.h"
#include "StyleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CStyleView

IMPLEMENT_DYNCREATE(CStyleView, CView)

BEGIN_MESSAGE_MAP(CStyleView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_COMMAND(IDM_TEST, &CStyleView::OnTest)
END_MESSAGE_MAP()

// CStyleView 构造/析构

CStyleView::CStyleView() noexcept
{
	// TODO: 在此处添加构造代码

}

CStyleView::~CStyleView()
{
}

BOOL CStyleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	//cs.lpszClass = _T("cynric.me");
	//cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW, LoadCursor(NULL, IDC_CROSS), (HBRUSH)GetStockObject(BLACK_BRUSH), 0);
	return CView::PreCreateWindow(cs);
}

// CStyleView 绘图

void CStyleView::OnDraw(CDC* /*pDC*/)
{
	CStyleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CStyleView 打印

BOOL CStyleView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CStyleView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CStyleView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CStyleView 诊断

#ifdef _DEBUG
void CStyleView::AssertValid() const
{
	CView::AssertValid();
}

void CStyleView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CStyleDoc* CStyleView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CStyleDoc)));
	return (CStyleDoc*)m_pDocument;
}
#endif //_DEBUG


// CStyleView 消息处理程序


int CStyleView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	//SetClassLongPtr(m_hWnd, GCLP_HBRBACKGROUND, (LONG_PTR)GetStockObject(BLACK_BRUSH));
	//SetClassLongPtr(m_hWnd, GCLP_HCURSOR, (LONG_PTR)LoadCursor(NULL, IDC_HELP));

	return 0;
}


void CStyleView::OnTest()
{
	// TODO: 在此添加命令处理程序代码
	MessageBox(_T("test!"));
}


