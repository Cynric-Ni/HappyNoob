#pragma once
class CGraph : public CObject
{
	DECLARE_SERIAL(CGraph);
	
public:
	CGraph();
	virtual ~CGraph();
	void Serialize(CArchive& ar);
	CGraph(UINT m_nDrawType,CPoint m_ptOrigin, CPoint m_ptEnd);
	void Draw(CDC* pDC);
public:
	UINT	m_nDrawType;
	CPoint	m_ptOrigin;
	CPoint	m_ptEnd;
};

