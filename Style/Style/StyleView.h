
// StyleView.h: CStyleView 类的接口
//

#pragma once


class CStyleView : public CView
{
protected: // 仅从序列化创建
	CStyleView() noexcept;
	DECLARE_DYNCREATE(CStyleView)

// 特性
public:
	CStyleDoc* GetDocument() const;

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
	virtual ~CStyleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

#ifndef _DEBUG  // StyleView.cpp 中的调试版本
inline CStyleDoc* CStyleView::GetDocument() const
   { return reinterpret_cast<CStyleDoc*>(m_pDocument); }
#endif

