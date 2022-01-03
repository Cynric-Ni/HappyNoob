
// GPDialogDlg.h: 头文件
//
#pragma once


// CGPDialogDlg 对话框
class CGPDialogDlg : public CDialogEx
{
// 构造
public:
	CGPDialogDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GPDIALOG_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_ch1;
	CString m_ch2;
	CString m_ch3;
	CString m_ch4;
	CString m_ch5;
	CString m_bat;
	afx_msg void OnBnClickedOk();
	BOOL m_OpenPlociy;
	BOOL m_NoGuest;
	BOOL m_OpenFireWall;
	BOOL m_SrceenPsw;
};
