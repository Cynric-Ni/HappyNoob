#pragma once


// CTestBtn

class CTestBtn : public CButton
{
	DECLARE_DYNAMIC(CTestBtn)

public:
	CTestBtn();
	virtual ~CTestBtn();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
};


