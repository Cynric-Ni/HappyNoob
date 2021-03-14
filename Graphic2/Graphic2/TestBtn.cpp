// TestBtn.cpp: 实现文件
//

#include "pch.h"
#include "Graphic2.h"
#include "TestBtn.h"


// CTestBtn

IMPLEMENT_DYNAMIC(CTestBtn, CButton)

CTestBtn::CTestBtn()
{

}

CTestBtn::~CTestBtn()
{
}


BEGIN_MESSAGE_MAP(CTestBtn, CButton)
END_MESSAGE_MAP()



// CTestBtn 消息处理程序




void CTestBtn::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{

	// TODO:  添加您的代码以绘制指定项
    UINT uStyle = DFCS_BUTTONPUSH;

    // This code only works with buttons.
    ASSERT(lpDrawItemStruct->CtlType == ODT_BUTTON);

    // If drawing selected, add the pushed style to DrawFrameControl.
    if (lpDrawItemStruct->itemState & ODS_SELECTED)
        uStyle |= DFCS_PUSHED;

    // Draw the button frame.
    ::DrawFrameControl(lpDrawItemStruct->hDC, &lpDrawItemStruct->rcItem,
        DFC_BUTTON, uStyle);
    //改变背景色 倪忻亮
    CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
    CBrush brush;
    CRect rect;
    CRect focusRect;
    focusRect.CopyRect(&lpDrawItemStruct->rcItem);
    DrawFocusRect(lpDrawItemStruct->hDC, (LPRECT)&focusRect);
    focusRect.left += 4;
    focusRect.right -= 4;
    focusRect.top += 4;
    focusRect.bottom -= 4;
    if (lpDrawItemStruct->itemState) {
        DrawFocusRect(lpDrawItemStruct->hDC, (LPRECT)&focusRect);
    }
    rect.CopyRect(&lpDrawItemStruct->rcItem);
    pDC->Draw3dRect(rect, ::GetSysColor(COLOR_BTNSHADOW), ::GetSysColor(COLOR_BTNHILIGHT));
    brush.CreateSolidBrush(RGB(0, 255, 0));
    ::FillRect(lpDrawItemStruct->hDC, &rect, (HBRUSH)brush.m_hObject);
    ::SetBkMode(lpDrawItemStruct->hDC, TRANSPARENT);
    // Get the button's text.
    CString strText;
    GetWindowText(strText);

    // Draw the button text using the text color red.
    COLORREF crOldColor = ::SetTextColor(lpDrawItemStruct->hDC, RGB(255, 0, 0));
    ::DrawText(lpDrawItemStruct->hDC, strText, strText.GetLength(),
        &lpDrawItemStruct->rcItem, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
    ::SetTextColor(lpDrawItemStruct->hDC, crOldColor);
}
