// TestDlg.cpp: 实现文件
//

#include "pch.h"
#include "Mybole.h"
#include "CTestDlg.h"
#include "afxdialogex.h"
#include "resource.h"


// CTestDlg 对话框

IMPLEMENT_DYNAMIC(CTestDlg, CDialogEx)

CTestDlg::CTestDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_Edit1(0)
	, m_Edit2(0)
	, m_Edit3(0)
{

}

CTestDlg::~CTestDlg()
{
}

void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Edit1);
	DDX_Text(pDX, IDC_EDIT2, m_Edit2);
	DDX_Text(pDX, IDC_EDIT3, m_Edit3);
}


BEGIN_MESSAGE_MAP(CTestDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_ADD, &CTestDlg::OnClickedBtnAdd)
	ON_STN_CLICKED(IDC_NUM1, &CTestDlg::OnClickedNum1)
//	ON_EN_CHANGE(IDC_EDIT1, &CTestDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CTestDlg 消息处理程序
