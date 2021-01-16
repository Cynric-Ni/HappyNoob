
// Menu2View.h: CMenu2View 类的接口
//

#pragma once


class CMenu2View : public CView
{
protected: // 仅从序列化创建
	CMenu2View() noexcept;
	DECLARE_DYNCREATE(CMenu2View)

// 特性
public:
	CMenu2Doc* GetDocument() const;

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
	virtual ~CMenu2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
	
public:
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//afx_msg void OnPhone1();
	CStringArray m_strArray;
private:
	int     m_nIndex;
	CMenu   m_menu;
	CString m_strLine;
public:
//	afx_msg void OnPhone5();
	afx_msg void OnPhone5();
};
#ifndef _DEBUG  // Menu2View.cpp 中的调试版本
inline CMenu2Doc* CMenu2View::GetDocument() const
   { return reinterpret_cast<CMenu2Doc*>(m_pDocument); }
#endif

