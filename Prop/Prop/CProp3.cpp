// CProp3.cpp: 实现文件
//

#include "pch.h"
#include "Prop.h"
#include "CProp3.h"
#include "afxdialogex.h"


// CProp3 对话框

IMPLEMENT_DYNAMIC(CProp3, CPropertyPage)

CProp3::CProp3()
	: CPropertyPage(IDD_PROP3)
{

}

CProp3::~CProp3()
{
}

void CProp3::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CProp3, CPropertyPage)
END_MESSAGE_MAP()


// CProp3 消息处理程序


BOOL CProp3::OnSetActive()
{
	// TODO: 在此添加专用代码和/或调用基类
	((CPropertySheet*)GetParent())->SetWizardButtons(PSWIZB_BACK | PSWIZB_FINISH);
	return CPropertyPage::OnSetActive();
}


BOOL CProp3::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  在此添加额外的初始化

	((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString("1000元以下");
	((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString("1000-2000元");
	((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString("2000-3000元");
	((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString("3000元以上");
	((CComboBox*)GetDlgItem(IDC_COMBO1))->SetCurSel(0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


BOOL CProp3::OnWizardFinish()
{
	// TODO: 在此添加专用代码和/或调用基类
	int index;
	index = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();
	((CComboBox*)GetDlgItem(IDC_COMBO1))->GetLBText(index, m_strSalary);
	return CPropertyPage::OnWizardFinish();
}
