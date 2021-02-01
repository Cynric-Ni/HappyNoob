// CProp1.cpp: 实现文件
//

#include "pch.h"
#include "Prop.h"
#include "CProp1.h"
#include "afxdialogex.h"


// CProp1 对话框

IMPLEMENT_DYNAMIC(CProp1, CPropertyPage)

CProp1::CProp1()
	: CPropertyPage(IDD_PROP1)
{

}

CProp1::~CProp1()
{
}

void CProp1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CProp1, CPropertyPage)
END_MESSAGE_MAP()


// CProp1 消息处理程序
