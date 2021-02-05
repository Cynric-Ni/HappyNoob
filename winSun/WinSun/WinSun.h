
// WinSun.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"		// 主符号


// CWinSunApp:
// 有关此类的实现，请参阅 WinSun.cpp
//

class CWinSunApp : public CWinApp
{
public:
	CWinSunApp();

// 重写
public:
	virtual BOOL InitInstance();
	HWND m_hwndDlg;

// 实现

	DECLARE_MESSAGE_MAP()
    virtual BOOL ProcessMessageFilter(int code, LPMSG lpMsg);
};

extern CWinSunApp theApp;
