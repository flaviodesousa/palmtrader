// Pedidos.h : main header file for the PEDIDOS application
//

#if !defined(AFX_PEDIDOS_H__33B20CC7_5FA4_11D1_9F58_204C4F4F5020__INCLUDED_)
#define AFX_PEDIDOS_H__33B20CC7_5FA4_11D1_9F58_204C4F4F5020__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPedidosApp:
// See Pedidos.cpp for the implementation of this class
//

class CPedidosApp : public CWinApp
{
public:
	CPedidosApp(LPCTSTR lpszAppName, LPCTSTR lpszHelpName);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPedidosApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPedidosApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PEDIDOS_H__33B20CC7_5FA4_11D1_9F58_204C4F4F5020__INCLUDED_)
