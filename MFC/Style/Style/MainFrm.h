﻿
// MainFrm.h: CMainFrame 类的接口
//

#pragma once
#define UM_PROGRESS WM_USER+1

class CMainFrame : public CFrameWnd
{
	
protected: // 仅从序列化创建
	CMainFrame() noexcept;
	DECLARE_DYNCREATE(CMainFrame)

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CToolBar          m_wndToolBar;
	//CStatusBar        m_wndStatusBar;
	CToolBar          m_newToolBar;
	CProgressCtrl	  m_progress;

// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

//ICON图标存储
private:
	HICON m_hIcons[3];
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnViewNewtoolbar();
	afx_msg void OnUpdateViewNewtoolbar(CCmdUI* pCmdUI);
	afx_msg LRESULT OnProgress(WPARAM wParam, LPARAM lParam);
	afx_msg void OnPaint();
	CStatusBar        m_wndStatusBar;
};


