// ServerView.cpp : implementation of the CServerView class
//

#include "stdafx.h"
#include "afxmt.h"
#include "afxtempl.h"

#include "Protocol.h"
#include "ConnectionThread.h"

#include "Server.h"
#include "ServerDoc.h"
#include "ServerView.h"
#include "SessionThread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CServerView

IMPLEMENT_DYNCREATE(CServerView, CFormView)

BEGIN_MESSAGE_MAP(CServerView, CFormView)
	//{{AFX_MSG_MAP(CServerView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CServerView construction/destruction

CServerView::CServerView()
	: CFormView(CServerView::IDD)
{
	//{{AFX_DATA_INIT(CServerView)
	m_server_status = _T("");
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CServerView::~CServerView()
{
}

void CServerView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CServerView)
	DDX_Control(pDX, IDC_CONEXOES, m_conexoes);
	DDX_Control(pDX, IDC_SERVER_STATUS, m_server_status_ctl);
	DDX_Text(pDX, IDC_SERVER_STATUS, m_server_status);
	//}}AFX_DATA_MAP
}

BOOL CServerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CServerView printing

BOOL CServerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CServerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CServerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CServerView::OnPrint(CDC* pDC, CPrintInfo*)
{
	// TODO: add code to print the controls
}

/////////////////////////////////////////////////////////////////////////////
// CServerView diagnostics

#ifdef _DEBUG
void CServerView::AssertValid() const
{
	CFormView::AssertValid();
}

void CServerView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CServerDoc* CServerView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CServerDoc)));
	return (CServerDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CServerView message handlers

void CServerView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();

	m_conexoes.InsertColumn(0, "Status", LVCFMT_LEFT, 50);
	m_conexoes.InsertColumn(1, "Origem", LVCFMT_LEFT, 100);
	m_conexoes.InsertColumn(2, "Vendedor", LVCFMT_LEFT, 150);
	m_conexoes.InsertColumn(3, "Recebendo", LVCFMT_LEFT, 200);
	m_conexoes.InsertColumn(4, "Enviando", LVCFMT_LEFT, 200);

	//ConnectionThread.SetHWND(this->m_hWnd);
}
