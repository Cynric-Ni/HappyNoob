
// Graphic2Doc.cpp: CGraphic2Doc 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Graphic2.h"
#endif

#include "Graphic2Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CGraphic2Doc

IMPLEMENT_DYNCREATE(CGraphic2Doc, CDocument)

BEGIN_MESSAGE_MAP(CGraphic2Doc, CDocument)
END_MESSAGE_MAP()


// CGraphic2Doc 构造/析构

CGraphic2Doc::CGraphic2Doc() noexcept
{
	// TODO: 在此添加一次性构造代码

}

CGraphic2Doc::~CGraphic2Doc()
{
}

BOOL CGraphic2Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)
	SetTitle(L"http://www.cynric.me");
	return TRUE;
}




// CGraphic2Doc 序列化

void CGraphic2Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
		int i = 5;
		char ch = 'b';
		float f = 1.2f;
		CString str("http://bbs.cynric.me");
		ar << i << ch << f << str;
	}
	else
	{
		// TODO: 在此添加加载代码
		int i;
		char ch;
		float f;
		CString str;
		CString strResult;
		ar >> i >> ch >> f >> str;
		strResult.Format(L"%d,%c,%f", i, ch, f, str);
		AfxMessageBox(strResult);
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CGraphic2Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CGraphic2Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CGraphic2Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CGraphic2Doc 诊断

#ifdef _DEBUG
void CGraphic2Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGraphic2Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CGraphic2Doc 命令
