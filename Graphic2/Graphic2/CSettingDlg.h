#pragma once


// CSettingDlg 对话框

class CSettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSettingDlg)

public:
	CSettingDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CSettingDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_SETTING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
//	afx_msg void OnClickedRadio1();
public:
	UINT m_nLineWidth;
	int m_nLineStyle;

	afx_msg void OnClickedRadio1();
	afx_msg void OnPaint();
//	afx_msg void OnClickedRadio2();
//	afx_msg void OnClickedRadio3();
	afx_msg void OnRadio2();
	afx_msg void OnRadio3();
	COLORREF m_clr;
	CBrush   m_brush;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
