// Server.cpp : Defines the class behaviors for the application.
//
// $Archive: /PalmTrader 1/Server/Server.cpp $
// $Author: Flávio $
// $Date: 25/05/99 15:31 $
/* $History: Server.cpp $
 * 
 * *****************  Version 11  *****************
 * User: Flávio       Date: 25/05/99   Time: 15:31
 * Updated in $/PalmTrader 1/Server
 * Alterações feitas para o release 1.30
 * Incluída rotina genérica para conversão de números em strings
 * Corrigido bug na definição do tamanho do buffer de envio de pacotes TCP
 * nos módulos de sincronização
 * Separada a porta TCP de conexão com os clientes e servidores
 * Incluído método em CPedido para retornar a data do pedido como DWORD,
 * que é usada no módulo de sincronização de pedidos
 * Implementados novos atributos em preços
 * Incluído o script de criação da base SQL
 * 
 * *****************  Version 10  *****************
 * User: Flávio       Date: 21/07/98   Time: 17:40
 * Updated in $/QuickSell/Server
 * Atualizações reordenadas para se evitar violações de integridade no
 * banco de dados
 * 
 * *****************  Version 9  *****************
 * User: Flávio       Date: 9/07/98    Time: 21:32
 * Updated in $/QuickSell/Server
 * Incluído tratamento para atualização automática parcial de produtos,
 * preços e clientes.
 * 
 * *****************  Version 8  *****************
 * User: Flávio       Date: 7/02/98    Time: 4:38p
 * Updated in $/QuickSell/Server
 * Suporte para atualização da tabela de títulos
 * 
 * *****************  Version 7  *****************
 * User: Flávio       Date: 6/26/98    Time: 1:47p
 * Updated in $/QuickSell/Server
 * Incluído suporte a atualização automática da base de dados do server
 */

#include "stdafx.h"
#include "afxmt.h"
#include "afxtempl.h"
#include "Protocol.h"
#include "ConnectionThread.h"
#include "Server.h"
#include "MainFrm.h"
#include "ServerDoc.h"
#include "ServerView.h"
#include "DialogAtualizar.h"
#include "DialogOpcoes.h"
#include "Registry.h"

#include "TitulosSynchronization.h"
#include "ProdutosSynchronization.h"
#include "ClientesSynchronization.h"
#include "TabelasSynchronization.h"
#include "VendedoresSynchronization.h"
#include "PlanosSynchronization.h"
#include "CodigosDeCobrancaSynchronization.h"
#include "EstoqueSynchronization.h"
#include "PrecosSynchronization.h"
#include "PartialClientesSynchronization.h"
#include "PartialProdutosSynchronization.h"
#include "PartialPrecosSynchronization.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CServerApp

BEGIN_MESSAGE_MAP(CServerApp, CWinApp)
	//{{AFX_MSG_MAP(CServerApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_ATUALIZAR_BASE, OnAtualizarBase)
	ON_COMMAND(ID_OPCOES, OnOpcoes)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CServerApp construction

CServerApp::CServerApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CServerApp object

CServerApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CServerApp initialization

BOOL CServerApp::InitInstance()
{
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CServerDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CServerView));
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
		// No message handlers
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
void CServerApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CServerApp commands

void CServerApp::OnOpcoes() 
{
	CDialogOpcoes dlg;

	{ // Isolate to force the call to the destructor, closing it
	CRegistry reg;

	dlg.m_aplicacao_address = reg.GetString(_T("AppServidor"), _T("127.0.0.1"));
	dlg.m_aplicacao_port    = reg.GetDWord(_T("AppPorta"), 47375);

	dlg.m_porta_vendedores  = reg.GetDWord(_T("Porta"), 47375);

	dlg.m_db_dsn			= reg.GetString(_T("ODBCDSN"));
	dlg.m_db_usuario		= reg.GetString(_T("ODBCUID"));
	dlg.m_db_senha			= reg.GetString(_T("ODBCPWD"));

	DWORD ultimo_bloco = reg.GetDWord(_T("PDBlocoAnterior"));

	if (ultimo_bloco)
	{
		dlg.m_pedidos_ultimo_bloco.Format(_T("%06lu - %06lu"), ultimo_bloco, ultimo_bloco + reg.GetDWord(_T("PDTamanhoAnterior")) - 1);
	}
	else
	{
		dlg.m_pedidos_ultimo_bloco = _T("<Nenhum bloco enviado>");
	}

	dlg.m_pedidos_proximo_numero = reg.GetDWord(_T("PDBlocoAtual"), 1);
	dlg.m_pedidos_tamanho_bloco = reg.GetDWord(_T("PDTamanhoAtual"), 100);
	}

	//dlg.m_spin_bloco_ctrl.SetRange(1,999999);
	//dlg.m_spin_tamanho_ctrl.SetRange(1,1000);
	
	if (dlg.DoModal() == IDOK)
	{
		CRegistry reg;

		reg.SetString(_T("AppServidor"), dlg.m_aplicacao_address);
		reg.SetDWord(_T("AppPorta"), dlg.m_aplicacao_port);

		reg.SetDWord(_T("Porta"), dlg.m_porta_vendedores);

		reg.SetString(_T("ODBCDSN"), dlg.m_db_dsn);
		reg.SetString(_T("ODBCUID"), dlg.m_db_usuario);
		reg.SetString(_T("ODBCPWD"), dlg.m_db_senha);

		reg.SetDWord(_T("PDBlocoAtual"), dlg.m_pedidos_proximo_numero);
		reg.SetDWord(_T("PDTamanhoAtual"), dlg.m_pedidos_tamanho_bloco);
	}
}

void CServerApp::OnAtualizarBase() 
{
	CDialogAtualizar dlg;
	if (dlg.DoModal() == IDOK)
    {
	    if (dlg.m_atualizar_planos)
	    {
		    if (dlg.m_paralelo)
		    {
			    AfxBeginThread(CServerApp::threadAtualizarPlanos, this);
		    }
		    else
		    {
			    CServerApp::threadAtualizarPlanos(this);
		    }
	    }
		//-----
	    if (dlg.m_atualizar_codigos_de_cobranca)
	    {
		    if (dlg.m_paralelo)
		    {
			    AfxBeginThread(CServerApp::threadAtualizarCodigosDeCobranca, this);
		    }
		    else
		    {
			    CServerApp::threadAtualizarCodigosDeCobranca(this);
		    }
	    }
		//-----
	    if (dlg.m_atualizar_tabelas)
	    {
		    if (dlg.m_paralelo)
		    {
			    AfxBeginThread(CServerApp::threadAtualizarTabelas, this);
		    }
		    else
		    {
			    CServerApp::threadAtualizarTabelas(this);
		    }
	    }
		//-----
	    if (dlg.m_atualizar_vendedores)
	    {
		    if (dlg.m_paralelo)
		    {
			    AfxBeginThread(CServerApp::threadAtualizarVendedores, this);
		    }
		    else
		    {
			    CServerApp::threadAtualizarVendedores(this);
		    }
	    }
		//-----
	    if (dlg.m_atualizar_produtos)
	    {
		    if (dlg.m_paralelo)
		    {
			    AfxBeginThread(CServerApp::threadAtualizarProdutos, this); 
		    }
		    else
		    {
			    CServerApp::threadAtualizarProdutos(this); 
		    }
	    }
	    else if (dlg.m_atualizar_produtos_partial)
	    {
		    if (dlg.m_paralelo)
		    {
			    AfxBeginThread(CServerApp::threadAtualizarProdutosPartial, this); 
		    }
		    else
		    {
			    CServerApp::threadAtualizarProdutosPartial(this); 
		    }
	    }
		//-----
	    if (dlg.m_atualizar_precos)
	    {
		    CRSTabelasPrecos tp;
		    tp.Open();
		    while (!tp.IsEOF())
		    {
			    int *pnTabela = new int;
			    *pnTabela = tp.m_tp_Codigo;
			    if (dlg.m_paralelo)
			    {
				    AfxBeginThread(CServerApp::threadAtualizarPrecos, pnTabela);
			    }
			    else
			    {
				    CServerApp::threadAtualizarPrecos(pnTabela);
			    }
			    tp.MoveNext();
		    }
	    }
	    else if (dlg.m_atualizar_precos_partial)
	    {
		    CRSTabelasPrecos tp;
		    tp.Open();
		    while (!tp.IsEOF())
		    {
			    int *pnTabela = new int;
			    *pnTabela = tp.m_tp_Codigo;
			    if (dlg.m_paralelo)
			    {
				    AfxBeginThread(CServerApp::threadAtualizarPrecosPartial, pnTabela);
			    }
			    else
			    {
				    CServerApp::threadAtualizarPrecosPartial(pnTabela);
			    }
			    tp.MoveNext();
		    }
	    }
		//-----
	    if (dlg.m_atualizar_clientes)
	    {
		    if (dlg.m_paralelo)
		    {
			    AfxBeginThread(CServerApp::threadAtualizarClientes, this);
		    }
		    else
		    {
			    CServerApp::threadAtualizarClientes(this);
		    }
	    }
	    else if (dlg.m_atualizar_clientes_partial)
	    {
		    if (dlg.m_paralelo)
		    {
			    AfxBeginThread(CServerApp::threadAtualizarClientesPartial, this);
		    }
		    else
		    {
			    CServerApp::threadAtualizarClientesPartial(this);
		    }
	    }
		//-----
	    if (dlg.m_atualizar_estoque)
	    {
		    if (dlg.m_paralelo)
		    {
			    AfxBeginThread(CServerApp::threadAtualizarEstoque, this);
		    }
		    else
		    {
			    CServerApp::threadAtualizarEstoque(this);
		    }
	    }
		//-----
        if (dlg.m_atualizar_titulos)
        {
            if (dlg.m_paralelo)
            {
                AfxBeginThread(CServerApp::threadAtualizarTitulos, this);
            }
            else
            {
                CServerApp::threadAtualizarTitulos(this);
            }
        }
    }
}

UINT CServerApp::threadAtualizarProdutos(void * p)
{
	CProdutosSynchronization s;
	s.DoIt();
	return 0;
}

UINT CServerApp::threadAtualizarPrecos(void * p)
{
	TRY
	{
		CPrecosSynchronization s(*(int *)p);
		delete (int *)p; // Bad practice. poor encapsulation.
		s.DoIt();
	}
	CATCH_ALL(ex)
	{
		ex->ReportError();
	}
	END_CATCH_ALL;

	return 0;
}

UINT CServerApp::threadAtualizarEstoque(void * p)
{
	CEstoqueSynchronization s;
	s.DoIt();
	return 0;
}

UINT CServerApp::threadAtualizarClientes(void * p)
{
	CClientesSynchronization s;
	s.DoIt();
	return 0;
}

UINT CServerApp::threadAtualizarPlanos(void * p)
{
	CPlanosSynchronization s;
	s.DoIt();
	return 0;
}

UINT CServerApp::threadAtualizarCodigosDeCobranca(void * p)
{
	CCodigosDeCobrancaSynchronization s;
	s.DoIt();
	return 0;
}

UINT CServerApp::threadAtualizarTabelas(void * p)
{
	CTabelasSynchronization s;
	s.DoIt();
	return 0;
}

UINT CServerApp::threadAtualizarVendedores(void * p)
{
	CVendedoresSynchronization s;
	s.DoIt();
	return 0;
}

UINT CServerApp::threadAtualizarTitulos(void * p)
{
    CTitulosSynchronization s;
    s.DoIt();
    return 0;
}

UINT CServerApp::threadAtualizarClientesPartial(void * p)
{
	CPartialClientesSynchronization s;
	s.DoIt();
	return 0;
}

UINT CServerApp::threadAtualizarProdutosPartial(void * p)
{
	CPartialProdutosSynchronization s;
	s.DoIt();
	return 0;
}

UINT CServerApp::threadAtualizarPrecosPartial(void * p)
{
	TRY
	{
		CPartialPrecosSynchronization s(*(int *)p);
		delete (int *)p; // Bad practice. poor encapsulation.
		s.DoIt();
	}
	CATCH_ALL(ex)
	{
		ex->ReportError();
	}
	END_CATCH_ALL;

	return 0;
}
