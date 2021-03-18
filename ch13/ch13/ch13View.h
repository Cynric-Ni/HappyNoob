
// ch13View.h: Cch13View 类的接口
//

#pragma once


class Cch13View : public CView
{
protected: // 仅从序列化创建
	Cch13View() noexcept;
	DECLARE_DYNCREATE(Cch13View)

// 特性
public:
	Cch13Doc* GetDocument() const;

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
	virtual ~Cch13View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileWrite();
	afx_msg void OnFileRead();
};

#ifndef _DEBUG  // ch13View.cpp 中的调试版本
inline Cch13Doc* Cch13View::GetDocument() const
   { return reinterpret_cast<Cch13Doc*>(m_pDocument); }
#endif

