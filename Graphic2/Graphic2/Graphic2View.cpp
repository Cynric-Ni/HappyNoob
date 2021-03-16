
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
#include "Graph.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGraphic2View

IMPLEMENT_DYNCREATE(CGraphic2View, CScrollView)

BEGIN_MESSAGE_MAP(CGraphic2View, CScrollView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_COMMAND(IDM_DOT, &CGraphic2View::OnDot)
	ON_COMMAND(IDM_LINE, &CGraphic2View::OnLine)
	ON_COMMAND(IDM_RECTANGLE, &CGraphic2View::OnRectangle)
	ON_COMMAND(IDM_ELLIPSE, &CGraphic2View::OnEllipse)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(IDM_SETTING, &CGraphic2View::OnSetting)
	ON_COMMAND(IDM_Color, &CGraphic2View::OnColor)
	ON_COMMAND(IDM_FONT, &CGraphic2View::OnFont)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CGraphic2View 构造/析构

CGraphic2View::CGraphic2View() noexcept
{
	// TODO: 在此处添加构造代码
	m_nDrawType = 0;
	m_nLineWidth = 0;
	m_nLineStyle = 0;
	m_clr = RGB(0, 0, 0);
	m_strFontName = "";
}

CGraphic2View::~CGraphic2View()
{
	for (int i = 0; i < m_ptrArray.GetSize(); i++) {
		delete m_ptrArray.GetAt(i);
	}
}

BOOL CGraphic2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CScrollView::PreCreateWindow(cs);
}

// CGraphic2View 绘图

void CGraphic2View::OnDraw(CDC* pDC)
{
	CGraphic2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	CBrush* pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
	CBrush* pOldBrush = pDC->SelectObject(pBrush);
	CPen pen(m_nLineStyle, m_nLineWidth, m_clr);
	CPen* pOldPen = pDC->SelectObject(&pen);
	for (int i = 0; i < m_ptrArray.GetSize(); i++) {
		switch (((CGraph*)m_ptrArray.GetAt(i))->m_nDrawType)
		{
		case 1:
			pDC->SetPixel(((CGraph*)m_ptrArray.GetAt(i))->m_ptEnd, m_clr);
			break;
		case 2:
			pDC->MoveTo(((CGraph*)m_ptrArray.GetAt(i))->m_ptOrigin);
			pDC->LineTo(((CGraph*)m_ptrArray.GetAt(i))->m_ptEnd);
			break;
		case 3:
			pDC->Rectangle(CRect(((CGraph*)m_ptrArray.GetAt(i))->m_ptOrigin,
				((CGraph*)m_ptrArray.GetAt(i))->m_ptEnd));
			break;
		case 4:
			pDC->Ellipse(CRect(((CGraph*)m_ptrArray.GetAt(i))->m_ptOrigin,
				((CGraph*)m_ptrArray.GetAt(i))->m_ptEnd));
			break;
		default:
			break;
		}
	}
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
	CFont* pOldFont = pDC->SelectObject(&m_Font);
	pDC->TextOutW(0, 0, m_strFontName);
	pDC->SelectObject(pOldFont);
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
	CScrollView::AssertValid();
}

void CGraphic2View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
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
	CScrollView::OnLButtonDown(nFlags, point);
}


void CGraphic2View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CClientDC dc(this);
	CPen pen(m_nLineStyle, m_nLineWidth, m_clr);
	CPen* pOldPen = dc.SelectObject(&pen);
	CBrush* pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
	CBrush* pOldBrush = dc.SelectObject(pBrush);
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
	dc.SelectObject(pOldPen);
	dc.SelectObject(pOldBrush);

	//CGraph qraph(m_nDrawType, m_ptOrigin, point);
	//m_ptrArray.Add(&qraph);
	CGraph* pGraph = new CGraph(m_nDrawType, m_ptOrigin, point);
	m_ptrArray.Add(pGraph);
	CScrollView::OnLButtonUp(nFlags, point);
}



void CGraphic2View::OnSetting()
{
	// TODO: 在此添加命令处理程序代码
	CSettingDlg dlg;
	dlg.m_nLineWidth = m_nLineWidth;
	dlg.m_nLineStyle = m_nLineStyle;
	//UpdateData();
	dlg.m_clr = m_clr;
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
	dlg.m_cc.Flags |= CC_RGBINIT | CC_FULLOPEN;
	//test.Format(L"%x", dlg.m_cc.Flags);
	//MessageBox(test);
	dlg.m_cc.rgbResult = m_clr;
	if(IDOK == dlg.DoModal()) {
		m_clr = dlg.m_cc.rgbResult;
	}


}


void CGraphic2View::OnFont()
{
	// TODO: 在此添加命令处理程序代码
	CFontDialog dlg;
	if (IDOK == dlg.DoModal()) {
		if (m_Font.m_hObject) {
			m_Font.DeleteObject();
		}
		m_Font.CreateFontIndirectW(dlg.m_cf.lpLogFont);
		m_strFontName = dlg.m_cf.lpLogFont->lfFaceName;
		Invalidate();
	}
}




BOOL CGraphic2View::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	/*CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_BITMAP1);
	BITMAP bmp;
	bitmap.GetBitmap(&bmp);
	CDC dcCompatible;
	dcCompatible.CreateCompatibleDC(pDC);
	dcCompatible.SelectObject(&bitmap);
	CRect rect;
	GetClientRect(&rect);
	//pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &dcCompatible, 0, 0, SRCCOPY);
	pDC->StretchBlt(0, 0, rect.Width(), rect.Height(), &dcCompatible, 
					0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY); */
	return CScrollView::OnEraseBkgnd(pDC); 
	//return TRUE;
}


void CGraphic2View::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	SetScrollSizes(MM_TEXT, CSize(1600, 900));
	// TODO: 在此添加专用代码和/或调用基类
}
