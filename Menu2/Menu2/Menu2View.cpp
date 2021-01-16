
// Menu2View.cpp: CMenu2View 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Menu2.h"
#endif

#include "Menu2Doc.h"
#include "Menu2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMenu2View

IMPLEMENT_DYNCREATE(CMenu2View, CView)

BEGIN_MESSAGE_MAP(CMenu2View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CHAR()
	ON_COMMAND(IDM_PHONE1, OnPhone1)

END_MESSAGE_MAP()

// CMenu2View 构造/析构

CMenu2View::CMenu2View() noexcept
{
	// TODO: 在此处添加构造代码
	m_nIndex = -1;
	m_strLine = "";
}

CMenu2View::~CMenu2View()
{
}

BOOL CMenu2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMenu2View 绘图

void CMenu2View::OnDraw(CDC* /*pDC*/)
{
	CMenu2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMenu2View 打印

BOOL CMenu2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMenu2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMenu2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMenu2View 诊断

#ifdef _DEBUG
void CMenu2View::AssertValid() const
{
	CView::AssertValid();
}

void CMenu2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMenu2Doc* CMenu2View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMenu2Doc)));
	return (CMenu2Doc*)m_pDocument;
}
#endif //_DEBUG


// CMenu2View 消息处理程序


void CMenu2View::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CClientDC dc(this);
	if (0x0d == nChar)
	{
		if (0 == ++m_nIndex)
		{
			m_menu.CreatePopupMenu();
			GetParent()->GetMenu()->AppendMenuA(MF_POPUP, (UINT)m_menu.m_hMenu, "PhoneBook");
			GetParent()->DrawMenuBar();
		}
		m_menu.AppendMenuA(MF_STRING, 111, m_strLine.Left(m_strLine.Find(' ')));
		m_strLine.Empty();
		Invalidate();
	}
	else
	{
		m_strLine += (TCHAR)nChar;
		dc.TextOut(0, 0, m_strLine);
	}
	CView::OnChar(nChar, nRepCnt, nFlags);
}
