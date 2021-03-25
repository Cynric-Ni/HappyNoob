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
	, m_clr(RGB(255,0,0))
{
	m_brush.CreateSolidBrush(RGB(0, 0, 255));
	m_font.CreatePointFont(200, L"华文行楷");
}

CSettingDlg::~CSettingDlg()
{
}

void CSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_nLineWidth);
	DDX_Radio(pDX, IDC_RADIO1, m_nLineStyle);
	DDX_Control(pDX, IDOK, m_TestBtn);
	//  DDX_Control(pDX, IDCANCEL, m_testBtn2);
	DDX_Control(pDX, IDCANCEL, m_cancel);
}


BEGIN_MESSAGE_MAP(CSettingDlg, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &CSettingDlg::OnEnChangeEdit1)
//	ON_BN_CLICKED(IDC_RADIO1, &CSettingDlg::OnClickedRadio1)
ON_BN_CLICKED(IDC_RADIO1, &CSettingDlg::OnClickedRadio1)
ON_WM_PAINT()
//ON_BN_CLICKED(IDC_RADIO2, &CSettingDlg::OnClickedRadio2)
//ON_BN_CLICKED(IDC_RADIO3, &CSettingDlg::OnClickedRadio3)
ON_COMMAND(IDC_RADIO2, &CSettingDlg::OnRadio2)
ON_COMMAND(IDC_RADIO3, &CSettingDlg::OnRadio3)
ON_WM_CTLCOLOR()
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




void CSettingDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	UpdateData();
	CPen pen(m_nLineStyle, m_nLineWidth, m_clr);
	dc.SelectObject(&pen);

	CRect rect;
	GetDlgItem(IDC_SAMPLE)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	dc.MoveTo(rect.left + 20, rect.top + rect.Height() / 2);
	dc.LineTo(rect.right - 20, rect.top + rect.Height() / 2);
}




void CSettingDlg::OnRadio2()
{
	// TODO: 在此添加命令处理程序代码
	Invalidate();
}


void CSettingDlg::OnRadio3()
{
	// TODO: 在此添加命令处理程序代码
	Invalidate();
}


HBRUSH CSettingDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	//return hbr;
	if(pWnd->GetDlgCtrlID() == IDC_LINE_STYLE) {
		pDC->SetTextColor(RGB(255, 0, 0));
		pDC->SetBkMode(TRANSPARENT);
		return m_brush;
	}
	if(pWnd->GetDlgCtrlID() == IDC_STATIC) {
		pDC->SetTextColor(RGB(255, 0, 0));
		pDC->SetBkMode(TRANSPARENT);
		return m_brush;
	}
	if(pWnd->GetDlgCtrlID() == IDC_LINE_WIDTH) {
		pDC->SetTextColor(RGB(255, 0, 0));
		pDC->SetBkMode(TRANSPARENT);
		return m_brush;
	}
	if (pWnd->GetDlgCtrlID() == IDC_TEXT) {
		pDC->SelectObject(&m_font);
	}
	return hbr;
}
