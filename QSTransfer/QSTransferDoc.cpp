// QSTransferDoc.cpp : implementation of the CQSTransferDoc class
//

#include "stdafx.h"
#include "winsock.h"

#include "QSDatabase.h"

#include "QSTransfer.h"

#include "SessionThread.h"
#include "QSTransferDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQSTransferDoc

IMPLEMENT_DYNCREATE(CQSTransferDoc, CDocument)

BEGIN_MESSAGE_MAP(CQSTransferDoc, CDocument)
	//{{AFX_MSG_MAP(CQSTransferDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQSTransferDoc construction/destruction

CQSTransferDoc::CQSTransferDoc()
{
	// TODO: add one-time construction code here

}

CQSTransferDoc::~CQSTransferDoc()
{
}

BOOL CQSTransferDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CQSTransferDoc serialization

void CQSTransferDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CQSTransferDoc diagnostics

#ifdef _DEBUG
void CQSTransferDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CQSTransferDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CQSTransferDoc commands
