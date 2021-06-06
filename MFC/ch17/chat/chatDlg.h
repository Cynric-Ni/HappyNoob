
// chatDlg.h: 头文件
//

#pragma once
#define UM_SOCK WM_USER+1

// CchatDlg 对话框
class CchatDlg : public CDialogEx
{
// 构造
public:
	CchatDlg(CWnd* pParent = nullptr);	// 标准构造函数
	~CchatDlg();
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHAT_DIALOG };
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
	afx_msg LRESULT OnSock(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()
private:
	SOCKET  m_socket;
	BOOL	InitSocket();
public:
	afx_msg void OnClickedBtnSend();
};
