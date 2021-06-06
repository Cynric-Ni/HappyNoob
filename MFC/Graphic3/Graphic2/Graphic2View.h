
// Graphic2View.h: CGraphic2View 类的接口
//

#pragma once

class CGraphic2View : public CScrollView
{
protected: // 仅从序列化创建
	CGraphic2View() noexcept;
	DECLARE_DYNCREATE(CGraphic2View)

// 特性
public:
	CGraphic2Doc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CGraphic2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
private:
	DECLARE_MESSAGE_MAP()
	UINT		m_nLineWidth;
	int			m_nLineStyle;
private:
	UINT		m_nDrawType;
	CPoint		m_ptOrigin;
	COLORREF    m_clr;
	CFont       m_Font;
	CString		m_strFontName;
	CPtrArray	m_ptrArray;
public:
	afx_msg void OnDot();
	afx_msg void OnLine();
	afx_msg void OnRectangle();
	afx_msg void OnEllipse();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSetting();
	afx_msg void OnColor();
	afx_msg void OnFont();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual void OnInitialUpdate();
	CObArray	m_obArray;
private:
	CMetaFileDC m_dcMetaFile;
public:
//	afx_msg void OnFileSave();
//	afx_msg void OnFileOpen();
	afx_msg void OnFileWrite();
	afx_msg void OnFileRead();
};

#ifndef _DEBUG  // Graphic2View.cpp 中的调试版本
inline CGraphic2Doc* CGraphic2View::GetDocument() const
   { return reinterpret_cast<CGraphic2Doc*>(m_pDocument); }
#endif

