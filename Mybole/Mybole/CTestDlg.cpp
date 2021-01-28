// CTestDlg.cpp: 实现文件
//

#include "pch.h"
#include "Mybole.h"
#include "CTestDlg.h"
#include "afxdialogex.h"


// CTestDlg 对话框

IMPLEMENT_DYNAMIC(CTestDlg, CDialogEx)

CTestDlg::CTestDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_num1(0)
	, m_num2(0)
	, m_num3(0)
{

}

CTestDlg::~CTestDlg()
{
}

void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT1, m_num1);
	DDX_Text(pDX, IDC_EDIT2, m_num2);
	DDX_Text(pDX, IDC_EDIT3, m_num3);
}

void CTestDlg::PostNcDestroy()
{
	//delete this;
}

BEGIN_MESSAGE_MAP(CTestDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_ADD, &CTestDlg::OnClickedBtnAdd)
	ON_STN_CLICKED(IDC_NUMBER1, &CTestDlg::OnClickedNumber1)
	ON_BN_CLICKED(IDC_BUTTON1, &CTestDlg::OnClickedButton1)
//	ON_WM_MBUTTONDBLCLK()
END_MESSAGE_MAP()



// CTestDlg 消息处理程序



//void CTestDlg::OnOK()
//{
//	// TODO: 在此添加专用代码和/或调用基类
//	DestroyWindow();
//	//CDialogEx::OnOK();
//}


//void CTestDlg::OnCancel()
//{
//	// TODO: 在此添加专用代码和/或调用基类
//	DestroyWindow();
//	CDialogEx::OnCancel();
//}


void CTestDlg::OnClickedBtnAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	/*if (!m_btn.m_hWnd)
	{
		m_btn.Create("New", BS_DEFPUSHBUTTON | WS_VISIBLE | WS_CHILD,
			         CRect(0, 0, 100, 100), this, 123);

	}
	else
	{
		m_btn.DestroyWindow();
	}

	int num1, num2, num3;
	char ch1[10], ch2[10], ch3[10];
	GetDlgItem(IDC_EDIT1)->GetWindowTextA(ch1, 10);
	GetDlgItem(IDC_EDIT2)->GetWindowTextA(ch2, 10);

	num1 = atoi(ch1);
	num2 = atoi(ch2);
	num3 = num1 + num2;

	_itoa(num3, ch3, 10);
	GetDlgItem(IDC_EDIT3)->SetWindowTextA(ch3);*/
	UpdateData();
	m_num3 = m_num1 + m_num2;
	UpdateData(FALSE);
}


void CTestDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


void CTestDlg::OnClickedNumber1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	if (GetDlgItem(IDC_NUMBER1)->GetWindowTextA(str),str == "Number1:")
	{
		GetDlgItem(IDC_NUMBER1)->SetWindowTextA("数字1：");
	}
	else
	{
		GetDlgItem(IDC_NUMBER1)->SetWindowTextA("Number1:");
	}
	
	
}


void CTestDlg::OnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	if (GetDlgItem(IDC_BUTTON1)->GetWindowTextA(str), str == "收缩<<")
	{
		//if(GetDlgItem(IDC_BUTTON1))
		GetDlgItem(IDC_BUTTON1)->SetWindowTextA("扩展>>");
	}
	else
	{
		//if(GetDlgItem(IDC_BUTTON1))
		GetDlgItem(IDC_BUTTON1)->SetWindowTextA("收缩<<");
	}
	    static CRect rectLarge;
	    static CRect rectSmall;
	if (rectLarge.IsRectNull())
	{
		CRect rectSeparator;
		GetWindowRect(&rectLarge);
		//if(GetDlgItem(ID_SEPARATOR))
		GetDlgItem(IDC_SEPERATOR)->GetWindowRect(&rectSeparator);

		rectSmall.top = rectLarge.top;
		rectSmall.left = rectLarge.left;
		rectSmall.right = rectLarge.right;
		rectSmall.bottom = rectSeparator.bottom;

	}
	if (str == "收缩<<")
	{
		SetWindowPos(NULL, 0, 0, rectSmall.Width(), rectSmall.Height(), SWP_NOMOVE | SWP_NOZORDER);
	}
	else
	{
		SetWindowPos(NULL, 0, 0, rectLarge.Width(), rectLarge.Height(), SWP_NOMOVE | SWP_NOZORDER);
	}
}

WNDPROC prevProc;
static LRESULT CALLBACK NewEditProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// TODO: 在此处添加实现代码.


	{
		if (uMsg == WM_CHAR && wParam == 0x0d)
		{
			::SetFocus(::GetNextWindow(hwnd, GW_HWNDNEXT));
			return 1;
		}
		else
		{
			return prevProc(hwnd, uMsg, wParam, lParam);
		}
	}
	return 1;
}


BOOL CTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	

	// TODO:  在此添加额外的初始化
	prevProc = (WNDPROC)SetWindowLongPtr(GetDlgItem(IDC_EDIT1)->m_hWnd, GWLP_WNDPROC,(LONG_PTR)NewEditProc);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}



//void CTestDlg::OnMButtonDblClk(UINT nFlags, CPoint point)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//
//	CDialogEx::OnMButtonDblClk(nFlags, point);
//}
