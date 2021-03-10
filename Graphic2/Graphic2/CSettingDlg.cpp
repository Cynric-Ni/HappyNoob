// CSettingDlg.cpp: 实现文件
//

#include "pch.h"
#include "Graphic2.h"
#include "CSettingDlg.h"
#include "afxdialogex.h"


// CSettingDlg 对话框

IMPLEMENT_DYNAMIC(CSettingDlg, CDialogEx)

CSettingDlg::CSettingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_SETTING, pParent)
	, m_nLineWidth(0)
	, m_nLineStyle(0)
{

}

CSettingDlg::~CSettingDlg()
{
}

void CSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_nLineWidth);
	DDX_Radio(pDX, IDC_RADIO1, m_nLineStyle);
}


BEGIN_MESSAGE_MAP(CSettingDlg, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &CSettingDlg::OnEnChangeEdit1)
//	ON_BN_CLICKED(IDC_RADIO1, &CSettingDlg::OnClickedRadio1)
ON_BN_CLICKED(IDC_RADIO1, &CSettingDlg::OnClickedRadio1)
END_MESSAGE_MAP()


// CSettingDlg 消息处理程序


void CSettingDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	Invalidate();
}

void CSettingDlg::OnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	Invalidate();
}
