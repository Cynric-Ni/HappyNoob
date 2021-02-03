
// PropView.h: CPropView 类的接口
//

#pragma once


class CPropView : public CView
{
protected: // 仅从序列化创建
	CPropView() noexcept;
	DECLARE_DYNCREATE(CPropView)

// 特性
public:
	CPropDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CPropView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPropertysheet();
private:
	//第一页面处理变量
	int m_iOccupation;
	CString m_strWorkAddr;
	//第二页面处理变量
	BOOL m_bLike[4];
		//第三页面处理变量
	CString m_strSalary;
};

#ifndef _DEBUG  // PropView.cpp 中的调试版本
inline CPropDoc* CPropView::GetDocument() const
   { return reinterpret_cast<CPropDoc*>(m_pDocument); }
#endif

