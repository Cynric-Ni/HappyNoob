#pragma once
#include <afxwin.h>
class CNewButton :
    public CButton
{
public:
    CNewButton* m_pbtn;
    DECLARE_MESSAGE_MAP()
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

