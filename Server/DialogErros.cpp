// DialogErros.cpp : implementation file
//

#include "stdafx.h"
#include "Server.h"
#include "DialogErros.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogErros dialog


CDialogErros::CDialogErros(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogErros::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogErros)
	m_erros = _T("");
	//}}AFX_DATA_INIT
}


void CDialogErros::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogErros)
	DDX_Text(pDX, IDC_ERROS, m_erros);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogErros, CDialog)
	//{{AFX_MSG_MAP(CDialogErros)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogErros message handlers
