// FormEstatisticas.cpp : implementation file
//

#include "stdafx.h"
#include "Server.h"
#include "FormEstatisticas.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFormEstatisticas property page

IMPLEMENT_DYNCREATE(CFormEstatisticas, CPropertyPage)

CFormEstatisticas::CFormEstatisticas() : CPropertyPage(CFormEstatisticas::IDD)
{
	//{{AFX_DATA_INIT(CFormEstatisticas)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CFormEstatisticas::~CFormEstatisticas()
{
}

void CFormEstatisticas::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFormEstatisticas)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFormEstatisticas, CPropertyPage)
	//{{AFX_MSG_MAP(CFormEstatisticas)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFormEstatisticas message handlers
