#pragma once
class CGraph
{
public:
	CGraph(UINT m_nDrawType,CPoint m_ptOrigin, CPoint m_ptEnd);
public:
	UINT	m_nDrawType;
	CPoint	m_ptOrigin;
	CPoint	m_ptEnd;
};

