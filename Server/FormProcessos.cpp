// FormProcessos.cpp : implementation file
//

#include "stdafx.h"
#include "Server.h"
#include "FormProcessos.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFormProcessos property page

IMPLEMENT_DYNCREATE(CFormProcessos, CPropertyPage)

CFormProcessos::CFormProcessos() : CPropertyPage(CFormProcessos::IDD)
{
	//{{AFX_DATA_INIT(CFormProcessos)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CFormProcessos::~CFormProcessos()
{
}

void CFormProcessos::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFormProcessos)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFormProcessos, CPropertyPage)
	//{{AFX_MSG_MAP(CFormProcessos)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFormProcessos message handlers
