#if !defined(AFX_DIALOGERROS_H__E78D2EB6_A08F_11D1_9FEE_00004403E294__INCLUDED_)
#define AFX_DIALOGERROS_H__E78D2EB6_A08F_11D1_9FEE_00004403E294__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DialogErros.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogErros dialog

class CDialogErros : public CDialog
{
// Construction
public:
	CDialogErros(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogErros)
	enum { IDD = IDD_ERROS };
	CString	m_erros;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogErros)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogErros)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGERROS_H__E78D2EB6_A08F_11D1_9FEE_00004403E294__INCLUDED_)
