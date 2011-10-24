#if !defined(AFX_SERVERSTATUSSHEET_H__26EA970C_68B9_11D1_9F77_204C4F4F5020__INCLUDED_)
#define AFX_SERVERSTATUSSHEET_H__26EA970C_68B9_11D1_9F77_204C4F4F5020__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ServerStatusSheet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CServerStatusSheet

class CServerStatusSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CServerStatusSheet)

// Construction
public:
	CServerStatusSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CServerStatusSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServerStatusSheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CServerStatusSheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(CServerStatusSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVERSTATUSSHEET_H__26EA970C_68B9_11D1_9F77_204C4F4F5020__INCLUDED_)
