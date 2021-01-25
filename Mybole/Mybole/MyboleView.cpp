
// MyboleView.cpp: CMyboleView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Mybole.h"
#endif

#include "MyboleDoc.h"
#include "MyboleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyboleView

IMPLEMENT_DYNCREATE(CMyboleView, CView)

BEGIN_MESSAGE_MAP(CMyboleView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMyboleView 构造/析构

CMyboleView::CMyboleView() noexcept
{
	// TODO: 在此处添加构造代码

}

CMyboleView::~CMyboleView()
{
}

BOOL CMyboleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMyboleView 绘图

void CMyboleView::OnDraw(CDC* /*pDC*/)
{
	CMyboleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMyboleView 打印

BOOL CMyboleView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMyboleView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMyboleView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMyboleView 诊断

#ifdef _DEBUG
void CMyboleView::AssertValid() const
{
	CView::AssertValid();
}

void CMyboleView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyboleDoc* CMyboleView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyboleDoc)));
	return (CMyboleDoc*)m_pDocument;
}
#endif //_DEBUG


// CMyboleView 消息处理程序
