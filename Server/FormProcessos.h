#if !defined(AFX_FORMPROCESSOS_H__26EA9709_68B9_11D1_9F77_204C4F4F5020__INCLUDED_)
#define AFX_FORMPROCESSOS_H__26EA9709_68B9_11D1_9F77_204C4F4F5020__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// FormProcessos.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFormProcessos dialog

class CFormProcessos : public CPropertyPage
{
	DECLARE_DYNCREATE(CFormProcessos)

// Construction
public:
	CFormProcessos();
	~CFormProcessos();

// Dialog Data
	//{{AFX_DATA(CFormProcessos)
	enum { IDD = IDD_PROPPAGE_PROCESSOS };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CFormProcessos)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CFormProcessos)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FORMPROCESSOS_H__26EA9709_68B9_11D1_9F77_204C4F4F5020__INCLUDED_)
