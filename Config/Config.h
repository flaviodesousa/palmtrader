// Config.h : main header file for the CONFIG application
//
// $Archive: /PalmTrader 1/Config/Config.h $
// $Author: Flávio $
// $Date: 30/09/98 15:40 $
/* $History: Config.h $
 * 
 * *****************  Version 2  *****************
 * User: Flávio       Date: 30/09/98   Time: 15:40
 * Updated in $/PalmTrader 1/Config
 * Incluídos comentários de controle de versão
 */

#if !defined(AFX_CONFIG_H__848B5397_6802_11D1_9F76_204C4F4F5020__INCLUDED_)
#define AFX_CONFIG_H__848B5397_6802_11D1_9F76_204C4F4F5020__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CConfigApp:
// See Config.cpp for the implementation of this class
//

class CConfigApp : public CWinApp
{
public:
	CConfigApp(LPCTSTR lpszAppName, LPCTSTR lpszHelpName);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CConfigApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIG_H__848B5397_6802_11D1_9F76_204C4F4F5020__INCLUDED_)
