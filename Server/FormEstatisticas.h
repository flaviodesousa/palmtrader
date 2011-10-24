#if !defined(AFX_FORMESTATISTICAS_H__26EA9707_68B9_11D1_9F77_204C4F4F5020__INCLUDED_)
#define AFX_FORMESTATISTICAS_H__26EA9707_68B9_11D1_9F77_204C4F4F5020__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// FormEstatisticas.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFormEstatisticas dialog

class CFormEstatisticas : public CPropertyPage
{
	DECLARE_DYNCREATE(CFormEstatisticas)

// Construction
public:
	CFormEstatisticas();
	~CFormEstatisticas();

// Dialog Data
	//{{AFX_DATA(CFormEstatisticas)
	enum { IDD = IDD_PROPPAGE_ESTATISTICAS };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CFormEstatisticas)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CFormEstatisticas)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FORMESTATISTICAS_H__26EA9707_68B9_11D1_9F77_204C4F4F5020__INCLUDED_)
