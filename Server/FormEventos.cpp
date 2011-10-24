// FormEventos.cpp : implementation file
//

#include "stdafx.h"
#include "Server.h"
#include "FormEventos.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFormEventos property page

IMPLEMENT_DYNCREATE(CFormEventos, CPropertyPage)

CFormEventos::CFormEventos() : CPropertyPage(CFormEventos::IDD)
{
	//{{AFX_DATA_INIT(CFormEventos)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CFormEventos::~CFormEventos()
{
}

void CFormEventos::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFormEventos)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFormEventos, CPropertyPage)
	//{{AFX_MSG_MAP(CFormEventos)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFormEventos message handlers
