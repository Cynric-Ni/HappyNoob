
// ch13View.cpp: Cch13View 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "ch13.h"
#endif

#include "ch13Doc.h"
#include "ch13View.h"
#include<fstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
using  std::ifstream;
using  std::ofstream;

// Cch13View

IMPLEMENT_DYNCREATE(Cch13View, CView)

BEGIN_MESSAGE_MAP(Cch13View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(IDM_FILE_WRITE, &Cch13View::OnFileWrite)
	ON_COMMAND(IDM_FILE_READ, &Cch13View::OnFileRead)
	ON_COMMAND(IDM_REG_WRITE, &Cch13View::OnRegWrite)
	ON_COMMAND(IDM_REG_READ, &Cch13View::OnRegRead)
END_MESSAGE_MAP()

// Cch13View 构造/析构

Cch13View::Cch13View() noexcept
{
	// TODO: 在此处添加构造代码

}

Cch13View::~Cch13View()
{
}

BOOL Cch13View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// Cch13View 绘图

void Cch13View::OnDraw(CDC* /*pDC*/)
{
	Cch13Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// Cch13View 打印

BOOL Cch13View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void Cch13View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void Cch13View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// Cch13View 诊断

#ifdef _DEBUG
void Cch13View::AssertValid() const
{
	CView::AssertValid();
}

void Cch13View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Cch13Doc* Cch13View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cch13Doc)));
	return (Cch13Doc*)m_pDocument;
}
#endif //_DEBUG


// Cch13View 消息处理程序


void Cch13View::OnFileWrite()
{
	// TODO: 在此添加命令处理程序代码
	//FILE* pFile = fopen("1.txt", "w");	2
	//char buf[24] = "http://www.phei.com.cn/";
	//fwrite("http://www.phei.com.cn/", 1, strlen("http://www.phei.com.cn/"), pFile);  1
	//fseek(pFile, 0, SEEK_SET);	1
	//fwrite("ftp:", 1, strlen("ftp:"), pFile);	1
	//fwrite("欢迎访问", 1, strlen("欢迎访问"), pFile);	1
	//buf[23] = '\0';	2
	//fwrite(buf, 1, 24, pFile);	2
	//fclose(pFile);	2
	//3 ofstream ofs("4.txt");
	//3 ofs.write("http://wwww.phei.com.cn/", strlen("http://wwww.phei.com.cn"));
	//3 ofs.close();
	/*方法4HANDLE hFile;
	hFile = CreateFile(L"5.txt", GENERIC_WRITE, 0, NULL, CREATE_NEW,
		FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD dwWrites;
	WriteFile(hFile, "http://wwww.phei.com.cn/", strlen("http://www.phei.com.cn/"),
		&dwWrites, NULL);
	CloseHandle(hFile);*/
	CFile file(L"6.txt", CFile::modeCreate | CFile::modeWrite);
	file.Write("http://www.phei.com.cn/", strlen("http://www.phei.com.cn"));
	file.Close();
}


void Cch13View::OnFileRead()
{
	// TODO: 在此添加命令处理程序代码
	/*FILE* pFile = fopen("1.txt", "r");
	char* pBuf;
	fseek(pFile, 0, SEEK_END);
	int len = ftell(pFile);
	pBuf = new char[len + 1];
	rewind(pFile);
	fread(pBuf, 1, len, pFile);
	pBuf[len] = 0;
	//fread(ch, 1, 100, pFile);
	fclose(pFile);
	::MessageBoxA(NULL, pBuf, "文件", 0);*/
	/*方法2 ifstream ifs("4.txt");
	char ch[100];
	memset(ch, 0, 100);
	ifs.read(ch,100);
	ifs.close();
	::MessageBoxA(NULL, ch, "文件", 0); */
	/*方法3HANDLE hFile;
	hFile = CreateFile(L"5.txt", GENERIC_READ, 0, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	char ch[100];
	DWORD dwReads;
	ReadFile(hFile, ch, 100, &dwReads, NULL);
	ch[dwReads] = 0;
	CloseHandle(hFile);
	MessageBoxA(NULL, ch, "文件", 0);*/
	
	
}


void Cch13View::OnRegWrite()
{
	// TODO: 在此添加命令处理程序代码
	HKEY hKey;
	LONG lResult;
	lResult = RegCreateKeyEx(HKEY_LOCAL_MACHINE,
		L"Software\\wwww.cynric.me\\admin",
		0, NULL, REG_OPTION_NON_VOLATILE,
		KEY_WRITE | KEY_WOW64_64KEY, NULL, &hKey, NULL);
	if (lResult == ERROR_SUCCESS) {
		MessageBox(L"创建注册表项成功");
	} else {
		MessageBox(L"创建注册表项失败");
		return;;
	}
	RegSetValue(hKey, NULL, REG_SZ, L"zhangsan", _tcslen(L"zhangsan"));
	RegCloseKey(hKey);
}


void Cch13View::OnRegRead()
{
	// TODO: 在此添加命令处理程序代码
	HKEY hKey;
	LONG lValue;
	RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"Software", 0, KEY_READ | KEY_WOW64_64KEY, &hKey);
	LONG lResult;
	lResult = RegQueryValue(hKey, L"wwww.cynric.me\\admin", NULL, &lValue);
	if (lResult == ERROR_SUCCESS) {
		TCHAR* pBuf = new TCHAR[lValue];
		RegQueryValue(hKey, L"wwww.cynric.me\\admin", pBuf, &lValue);
		MessageBox(pBuf);
	}else {
		MessageBox(L"创建失败");
	}
}
