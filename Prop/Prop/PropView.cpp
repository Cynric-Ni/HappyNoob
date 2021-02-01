
// PropView.cpp: CPropView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Prop.h"
#endif

#include "PropDoc.h"
#include "PropView.h"
#include "CPropSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPropView

IMPLEMENT_DYNCREATE(CPropView, CView)

BEGIN_MESSAGE_MAP(CPropView, CView)
	ON_COMMAND(IDM_PROPERTYSHEET, &CPropView::OnPropertysheet)
END_MESSAGE_MAP()

// CPropView 构造/析构

CPropView::CPropView() noexcept
{
	// TODO: 在此处添加构造代码

}

CPropView::~CPropView()
{
}

BOOL CPropView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CPropView 绘图

void CPropView::OnDraw(CDC* /*pDC*/)
{
	CPropDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CPropView 诊断

#ifdef _DEBUG
void CPropView::AssertValid() const
{
	CView::AssertValid();
}

void CPropView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPropDoc* CPropView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPropDoc)));
	return (CPropDoc*)m_pDocument;
}
#endif //_DEBUG


// CPropView 消息处理程序


void CPropView::OnPropertysheet()
{
	// TODO: 在此添加命令处理程序代码
	CPropSheet propSheet("属性表单");
	propSheet.DoModal();
}
