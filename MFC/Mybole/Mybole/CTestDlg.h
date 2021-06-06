#pragma once


// CTestDlg 对话框

class CTestDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTestDlg)

public:
	CTestDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CTestDlg();
	virtual void PostNcDestroy();
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	
	DECLARE_MESSAGE_MAP()
//	virtual void OnOK();
//	virtual void OnCancel();
public:
	afx_msg void OnClickedBtnAdd();
	CButton m_btn;
	bool m_bIsCreated = FALSE;
	virtual void OnOK();
	afx_msg void OnClickedNumber1();
	int m_num1;
	int m_num2;
	int m_num3;
	afx_msg void OnClickedButton1();
	//virtual BOOL OnInitDialog();
//	afx_msg void OnMButtonDblClk(UINT nFlags, CPoint point);
//	afx_msg void OnBnClickedOk();
//	afx_msg void OnBnClickedButton2();
};
