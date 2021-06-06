#include "pch.h"
#include "CNewButton.h"
BEGIN_MESSAGE_MAP(CNewButton, CButton)
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


void CNewButton::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	ShowWindow(SW_HIDE);
	m_pbtn->ShowWindow(SW_SHOW);
	CButton::OnMouseMove(nFlags, point);
}
