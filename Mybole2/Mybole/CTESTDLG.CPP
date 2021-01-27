#include "pch.h"
#include "CTestDlg.h"
#include "resource.h"


void CTestDlg::PostNcDestroy()
{
	// TODO: 在此添加专用代码和/或调用基类
	//delete this;
	CDialogEx::PostNcDestroy();
}


void CTestDlg::OnClickedBtnAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	
	/*if (m_bIsCreated == FALSE)
	{
		m_btn.Create("New", BS_DEFPUSHBUTTON | WS_VISIBLE | WS_CHILD,
			CRect(0, 0, 100, 100), this, 123);
		m_bIsCreated = TRUE;
	}
	else
	{
		m_btn.DestroyWindow();
		m_bIsCreated = FALSE;
	}*/
	UpdateData();
	m_Edit3 = m_Edit1 + m_Edit2;
	UpdateData(FALSE);
}



void CTestDlg::OnClickedNum1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	if (GetDlgItem(IDC_NUM1)->GetWindowTextA(str), str == "Number1:")
	{
		GetDlgItem(IDC_NUM1)->SetWindowTextA("数值1：");
	}
	else
	{
		GetDlgItem(IDC_NUM1)->SetWindowTextA("Number1:");
	}
}


