// QSTransfer.h : main header file for the QSTRANSFER application
//

#if !defined(AFX_QSTRANSFER_H__9B872C9E_6CB0_11D1_9F82_204C4F4F5020__INCLUDED_)
#define AFX_QSTRANSFER_H__9B872C9E_6CB0_11D1_9F82_204C4F4F5020__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CQSTransferApp:
// See QSTransfer.cpp for the implementation of this class
//

class CQSTransferApp : public CWinApp
{
public:
	CQSTransferApp(LPCTSTR lpszAppName);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQSTransferApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CQSTransferApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QSTRANSFER_H__9B872C9E_6CB0_11D1_9F82_204C4F4F5020__INCLUDED_)
