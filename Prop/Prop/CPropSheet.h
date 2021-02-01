#pragma once



// CPropSheet
#include"CProp1.h"
#include"CProp2.h"
#include"CProp3.h"
class CPropSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CPropSheet)

public:
	CPropSheet(UINT nIDCaption, CWnd* pParentWnd = nullptr, UINT iSelectPage = 0);
	CPropSheet(LPCTSTR pszCaption, CWnd* pParentWnd = nullptr, UINT iSelectPage = 0);
	virtual ~CPropSheet();

protected:
	DECLARE_MESSAGE_MAP()
public:
	CProp1 m_prop1;
	CProp2 m_prop2;
	CProp3 m_prop3;
};


