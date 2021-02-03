#pragma once


// CProp2 对话框

class CProp2 : public CPropertyPage
{
	DECLARE_DYNAMIC(CProp2)

public:
	CProp2();
	virtual ~CProp2();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROP2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
	BOOL m_football;
	BOOL m_basketball;
	BOOL m_volleyball;
	BOOL m_swim;
	virtual LRESULT OnWizardNext();
private:
	BOOL m_bLike[4];
};
