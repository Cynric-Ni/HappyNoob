#pragma once


// CProp3 对话框

class CProp3 : public CPropertyPage
{
	DECLARE_DYNAMIC(CProp3)

public:
	CProp3();
	virtual ~CProp3();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROP3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnInitDialog();
	virtual BOOL OnWizardFinish();
	CString m_strSalary;
};
