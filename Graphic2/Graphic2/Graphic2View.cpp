
// Graphic2View.cpp: CGraphic2View 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Graphic2.h"
#endif

#include "Graphic2Doc.h"
#include "Graphic2View.h"
#include "CSettingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGraphic2View

IMPLEMENT_DYNCREATE(CGraphic2View, CView)

BEGIN_MESSAGE_MAP(CGraphic2View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(IDM_DOT, &CGraphic2View::OnDot)
	ON_COMMAND(IDM_LINE, &CGraphic2View::OnLine)
	ON_COMMAND(IDM_RECTANGLE, &CGraphic2View::OnRectangle)
	ON_COMMAND(IDM_ELLIPSE, &CGraphic2View::OnEllipse)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(IDM_SETTING, &CGraphic2View::OnSetting)
	ON_COMMAND(IDM_Color, &CGraphic2View::OnColor)
END_MESSAGE_MAP()

// CGraphic2View 构造/析构

CGraphic2View::CGraphic2View() noexcept
{
	// TODO: 在此处添加构造代码
	m_nDrawType = 0;
	m_nLineWidth = 0;
	m_nLineStyle = 0;
}

CGraphic2View::~CGraphic2View()
{
}

BOOL CGraphic2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CGraphic2View 绘图

void CGraphic2View::OnDraw(CDC* pDC)
{
	CGraphic2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CGraphic2View 打印

BOOL CGraphic2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CGraphic2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CGraphic2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CGraphic2View 诊断

#ifdef _DEBUG
void CGraphic2View::AssertValid() const
{
	CView::AssertValid();
}

void CGraphic2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGraphic2Doc* CGraphic2View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGraphic2Doc)));
	return (CGraphic2Doc*)m_pDocument;
}
#endif //_DEBUG


// CGraphic2View 消息处理程序


void CGraphic2View::OnDot()
{
	// TODO: 在此添加命令处理程序代码
	m_nDrawType = 1;
}


void CGraphic2View::OnLine()
{
	// TODO: 在此添加命令处理程序代码
	m_nDrawType = 2;
}


void CGraphic2View::OnRectangle()
{
	// TODO: 在此添加命令处理程序代码
	m_nDrawType = 3;
}


void CGraphic2View::OnEllipse()
{
	// TODO: 在此添加命令处理程序代码
	m_nDrawType = 4;
}


void CGraphic2View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_ptOrigin = point;
	CView::OnLButtonDown(nFlags, point);
}


void CGraphic2View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CClientDC dc(this);
	CPen pen(m_nLineStyle, m_nLineWidth, m_clr);
	dc.SelectObject(&pen);
	CBrush* pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
	switch (m_nDrawType)
	{
	case 1:
		dc.SetPixel(point, m_clr);
		break;
	case 2:
		dc.MoveTo(m_ptOrigin);
		dc.LineTo(point);
		break;
	case 3:
		dc.Rectangle(CRect(m_ptOrigin, point));
		break;
	case 4:
		dc.Ellipse(CRect(m_ptOrigin, point));
		break;
	}
	CView::OnLButtonUp(nFlags, point);
}



void CGraphic2View::OnSetting()
{
	// TODO: 在此添加命令处理程序代码
	CSettingDlg dlg;
	dlg.m_nLineWidth = m_nLineWidth;
	dlg.m_nLineStyle = m_nLineStyle;
	//UpdateData();
	if (IDOK == dlg.DoModal()) {
		m_nLineWidth = dlg.m_nLineWidth;
		m_nLineStyle = dlg.m_nLineStyle;
	}
}


void CGraphic2View::OnColor()
{
	// TODO: 在此添加命令处理程序代码
	CColorDialog dlg;
	CString test;
	dlg.m_cc.Flags = CC_RGBINIT;
	test.Format(_T("%x"), dlg.m_cc.Flags);
	MessageBox(test);
	dlg.m_cc.rgbResult = m_clr;
	if(IDOK == dlg.DoModal()) {
		m_clr = dlg.m_cc.rgbResult;
	}


}
