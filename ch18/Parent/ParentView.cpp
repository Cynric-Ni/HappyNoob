﻿
// ParentView.cpp: CParentView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Parent.h"
#endif

#include "ParentDoc.h"
#include "ParentView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CParentView

IMPLEMENT_DYNCREATE(CParentView, CView)

BEGIN_MESSAGE_MAP(CParentView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(IDM_PIPE_CREATE, &CParentView::OnPipeCreate)
	ON_COMMAND(IDM_PIPE_READ, &CParentView::OnPipeRead)
	ON_COMMAND(IDM_PIPE_WRITE, &CParentView::OnPipeWrite)
END_MESSAGE_MAP()

// CParentView 构造/析构

CParentView::CParentView() noexcept
{
	// TODO: 在此处添加构造代码
	hWrite = NULL;
	hRead = NULL;

}

CParentView::~CParentView()
{
	if (hWrite)
		CloseHandle(hWrite);
	if (hRead)
		CloseHandle(hRead);
}

BOOL CParentView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CParentView 绘图

void CParentView::OnDraw(CDC* /*pDC*/)
{
	CParentDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CParentView 打印

BOOL CParentView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CParentView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CParentView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CParentView 诊断

#ifdef _DEBUG
void CParentView::AssertValid() const
{
	CView::AssertValid();
}

void CParentView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CParentDoc* CParentView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CParentDoc)));
	return (CParentDoc*)m_pDocument;
}
#endif //_DEBUG


// CParentView 消息处理程序


void CParentView::OnPipeCreate()
{
	// TODO: 在此添加命令处理程序代码
	SECURITY_ATTRIBUTES sa;
	sa.bInheritHandle = TRUE;
	sa.lpSecurityDescriptor = NULL;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	if (!CreatePipe(&hRead, &hWrite, &sa, 0))
	{
		MessageBox(L"创建匿名管道失败！");
		return;
	}
	STARTUPINFO sui;
	PROCESS_INFORMATION pi;
	ZeroMemory(&sui, sizeof(STARTUPINFO));
	sui.cb = sizeof(STARTUPINFO);
	sui.dwFlags = STARTF_USESTDHANDLES;
	sui.hStdInput = hRead;
	sui.hStdOutput = hWrite;
	sui.hStdError = GetStdHandle(STD_ERROR_HANDLE);
	if (!CreateProcess(L"..\\Debug\\Child.exe", NULL, NULL, NULL,
		TRUE, 0, NULL, NULL, &sui, &pi)) {
		CloseHandle(hRead);
		CloseHandle(hWrite);
		hRead = NULL;
		hWrite = NULL;
		MessageBox(L"创建子进程失败！");
		return;
	}else {
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
}


void CParentView::OnPipeRead()
{
	// TODO: 在此添加命令处理程序代码
	char buf[100];
	DWORD dwRead;
	if (!ReadFile(hRead, buf, 100, &dwRead, NULL)) {
		MessageBox(L"读取数据失败！");
		return;
	}
	USES_CONVERSION;
	MessageBox(A2T(buf));
}




void CParentView::OnPipeWrite()
{
	// TODO: 在此添加命令处理程序代码
	char buf[] = "http://www.cynric.me";
	DWORD dwWrite;
	if (!WriteFile(hWrite, buf, strlen(buf) + 1, &dwWrite, NULL)) {
		MessageBox(L"写入数据失败！");
		return;
	}
}
