
// MyboleView.h: CMyboleView 类的接口
//

#pragma once


class CMyboleView : public CView
{
protected: // 仅从序列化创建
	CMyboleView() noexcept;
	DECLARE_DYNCREATE(CMyboleView)

// 特性
public:
	CMyboleDoc* GetDocument() const;

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
	virtual ~CMyboleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDialog();
};

#ifndef _DEBUG  // MyboleView.cpp 中的调试版本
inline CMyboleDoc* CMyboleView::GetDocument() const
   { return reinterpret_cast<CMyboleDoc*>(m_pDocument); }
#endif

