#include "pch.h"
#include "Graph.h"




CGraph::CGraph(UINT m_nDrawType, CPoint m_ptOrigin, CPoint m_ptEnd)
{
	this->m_nDrawType = m_nDrawType;
	this->m_ptOrigin = m_ptOrigin;
	this->m_ptEnd = m_ptEnd;
}