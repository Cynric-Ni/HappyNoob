#pragma once


// CTestDlg 对话框

class CTestDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTestDlg)

public:
	CTestDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CTestDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
public:
	afx_msg void OnClickedBtnAdd();
private:
	CButton m_btn;
	BOOL  m_bIsCreated = FALSE;
public:
	afx_msg void OnClickedNum1();

private:
	int m_Edit1;
	int m_Edit2;
	int m_Edit3;
};
