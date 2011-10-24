// ServerStatusSheet.cpp : implementation file
//

#include "stdafx.h"
#include "Server.h"
#include "ServerStatusSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CServerStatusSheet

IMPLEMENT_DYNAMIC(CServerStatusSheet, CPropertySheet)

CServerStatusSheet::CServerStatusSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CServerStatusSheet::CServerStatusSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

CServerStatusSheet::~CServerStatusSheet()
{
}


BEGIN_MESSAGE_MAP(CServerStatusSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CServerStatusSheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CServerStatusSheet message handlers
