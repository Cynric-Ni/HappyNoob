﻿
// GPDialogDlg.h: 头文件
//
#pragma once


// CGPDialogDlg 对话框
class CGPDialogDlg : public CDialogEx
{
// 构造
public:
	CGPDialogDlg(CWnd* pParent = nullptr);	// 标准构造函数
	~CGPDialogDlg();

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
	DWORD getOSName();
	void checkMSpack();
	ULONG getBuildNum();
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
	BOOL m_DisablePortRdp;     //禁止端口变量

	BOOL GetVersionEx2(LPOSVERSIONINFOW lpVersionInformation);
	afx_msg void OnBnClickedcheckupdate();
	BOOL IsAppProcessWOW64(void);

private:
	CString executeCmd();
	BOOL executeCmdC(TCHAR* cmd_str, CString& outbuf);
	void  BatScript();
	BOOL strContrast(CString str1,CString str2);
	void PasswordPolicy();
};
