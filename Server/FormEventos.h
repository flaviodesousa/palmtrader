#if !defined(AFX_FORMEVENTOS_H__26EA9708_68B9_11D1_9F77_204C4F4F5020__INCLUDED_)
#define AFX_FORMEVENTOS_H__26EA9708_68B9_11D1_9F77_204C4F4F5020__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// FormEventos.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFormEventos dialog

class CFormEventos : public CPropertyPage
{
	DECLARE_DYNCREATE(CFormEventos)

// Construction
public:
	CFormEventos();
	~CFormEventos();

// Dialog Data
	//{{AFX_DATA(CFormEventos)
	enum { IDD = IDD_PROPPAGE_EVENTOS };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CFormEventos)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CFormEventos)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FORMEVENTOS_H__26EA9708_68B9_11D1_9F77_204C4F4F5020__INCLUDED_)
