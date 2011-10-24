// Pedidos.cpp : Defines the class behaviors for the application.
//
// $Archive: /PalmTrader 1/Pedidos/Pedidos.cpp $
// $Author: Flávio $
// $Date: 11/11/98 15:10 $
/* $History: Pedidos.cpp $
 * 
 * *****************  Version 4  *****************
 * User: Flávio       Date: 11/11/98   Time: 15:10
 * Updated in $/PalmTrader 1/Pedidos
 * Implementado recurso de eliminação automática de pedidos em função da
 * data da última alteração
 * 
 * *****************  Version 3  *****************
 * User: Flávio       Date: 30/09/98   Time: 15:41
 * Updated in $/PalmTrader 1/Pedidos
 * Incluídos comentários de controle de versão
 */

#include "stdafx.h"
#include "Pedidos.h"
#include "QSDatabase.h"
#include "AutoDeletePedidos.h"

#include "MainFrm.h"
#include "PedidosDoc.h"
#include "PedidosView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPedidosApp

BEGIN_MESSAGE_MAP(CPedidosApp, CWinApp)
	//{{AFX_MSG_MAP(CPedidosApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	//ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	//ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPedidosApp construction

CPedidosApp::CPedidosApp(LPCTSTR lpszAppName, LPCTSTR lpszHelpName)
	: CWinApp(lpszAppName, lpszHelpName)
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CPedidosApp object

// WCE MFC apps require the application name to be specified in the CWinApp 
// constructor. A help contents filename may also be specified.

CPedidosApp theApp(_T("Pedidos"), _T("Pedidos.htc"));

/////////////////////////////////////////////////////////////////////////////
// CPedidosApp initialization

BOOL CPedidosApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	// Change the registry key under which our settings are stored.
	// You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Pedidos"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CPedidosDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CPedidosView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	CAutoDeletePedidos::Run(); // Apaga automaticamente os pedidos antigos

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();		// Added for WCE apps
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CPedidosApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CPedidosApp commands
// Added for WCE apps

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CenterWindow();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
