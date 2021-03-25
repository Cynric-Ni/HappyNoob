#include "pch.h"
#include "Graph.h"



IMPLEMENT_SERIAL(CGraph, CObject, 1);

CGraph::CGraph()
{

}
CGraph::~CGraph()
{

}

CGraph::CGraph(UINT m_nDrawType, CPoint m_ptOrigin, CPoint m_ptEnd)
{
	this->m_nDrawType = m_nDrawType;
	this->m_ptOrigin = m_ptOrigin;
	this->m_ptEnd = m_ptEnd;
}

void CGraph::Serialize(CArchive& ar)
{
	if (ar.IsStoring()) {
		ar << m_nDrawType << m_ptOrigin << m_ptEnd;
	}else{
		ar >> m_nDrawType >> m_ptOrigin >> m_ptEnd;
	}
}

void CGraph::Draw(CDC* pDC)
{
	//创建透明画刷
	CBrush* pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
	CBrush* pOldBrush = pDC->SelectObject(pBrush);
	//根据选择类型绘画
	switch (m_nDrawType)
	{
	case 1:
		pDC->SetPixel(m_ptEnd, RGB(0,0,0));
		break;
	case 2:
		pDC->MoveTo(m_ptOrigin);
		pDC->LineTo(m_ptEnd);
		break;
	case 3:
		pDC->Rectangle(CRect(m_ptOrigin, m_ptEnd));
		break;
	case 4:
		pDC->Ellipse(CRect(m_ptOrigin, m_ptEnd));
		break;
	}
	pDC->SelectObject(pOldBrush);
}
