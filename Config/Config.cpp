// Config.cpp : Defines the class behaviors for the application.
//
// $Archive: /PalmTrader 1/Config/Config.cpp $
// $Author: Fl�vio $
// $Date: 11/11/98 15:12 $
/* $History: Config.cpp $
 * 
 * *****************  Version 6  *****************
 * User: Fl�vio       Date: 11/11/98   Time: 15:12
 * Updated in $/PalmTrader 1/Config
 * Implementado recurso de elimina��o autom�tica de pedidos em fun��o da
 * data da �ltima altera��o
 * Eliminado par�metro "Nome do Vendedor"
 * 
 * *****************  Version 5  *****************
 * User: Fl�vio       Date: 10/07/98   Time: 23:16
 * Updated in $/PalmTrader 1/Config
 * Implementado item de configura��o que regula a permiss�o de venda de
 * itens n�o dispon�veis
 * 
 * *****************  Version 4  *****************
 * User: Fl�vio       Date: 7/05/98    Time: 1:01p
 * Updated in $/QuickSell/QSConfig
 * Inclu�das op��es para exibi��o de pre�os unit�rios
 * 
 * *****************  Version 3  *****************
 * User: Fl�vio       Date: 4/13/98    Time: 1:34a
 * Updated in $/QuickSell/QSConfig
 * Inclu�da op��o para se determinar o tempo em segundos em que a busca
 * autom�tica limpa o texto de busca.
 */

#include "stdafx.h"

#include "PedidosRegistry.h"
#include "Config.h"
#include "ConfigDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigApp

BEGIN_MESSAGE_MAP(CConfigApp, CWinApp)
	//{{AFX_MSG_MAP(CConfigApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigApp construction

CConfigApp::CConfigApp(LPCTSTR lpszAppName, LPCTSTR lpszHelpName)
	: CWinApp(lpszAppName, lpszHelpName)
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CConfigApp object

// WCE MFC apps require the application name to be specified in the CWinApp 
// constructor. A help contents filename may also be specified.

CConfigApp theApp(_T("Config"), _T("Config.htc"));

/////////////////////////////////////////////////////////////////////////////
// CConfigApp initialization

BOOL CConfigApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.
	CConfigDlg dlg;
	m_pMainWnd = &dlg;
	CPedidosRegistry Reg(FALSE);

	dlg.m_conexao = Reg.GetString(_T("Conexao"));
	dlg.m_servidor = Reg.GetString(_T("Servidor"));
	dlg.m_porta = Reg.GetDWord(_T("Porta"));
	dlg.m_tentativas = Reg.GetDWord(_T("Tentativas"), 3);
	dlg.m_vendedor_numero = Reg.GetDWord(_T("VendedorCodigo"));
	//dlg.m_vendedor_nome = Reg.GetString(_T("VendedorNome"));
	dlg.m_senha = Reg.GetString(_T("VendedorSenha"));
	dlg.m_exibir_nao_disponiveis = Reg.GetDWord(_T("ExibirProdutosNaoDisponiveis"), TRUE);
    dlg.m_exibir_unitarios = Reg.GetDWord(_T("ExibirUnitarios"), FALSE);
    dlg.m_arredondar = Reg.GetDWord(_T("ArredondarUnitarios"), TRUE);
	dlg.m_vender_falta = Reg.GetDWord(_T("PermitirVendaItensEmFalta"), FALSE);
    dlg.m_autoclear = Reg.GetDWord(_T("Autoclear"), 3);
	dlg.m_autodelete = Reg.GetDWord(_T("AutoDelete"), 30);

	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		Reg.SetString(_T("Conexao"), dlg.m_conexao);
		Reg.SetString(_T("Servidor"), dlg.m_servidor);
		Reg.SetDWord(_T("Porta"), dlg.m_porta);
		Reg.SetDWord(_T("Tentativas"), dlg.m_tentativas);

		Reg.SetDWord(_T("VendedorCodigo"), dlg.m_vendedor_numero);
		//Reg.SetString(_T("VendedorNome"), dlg.m_vendedor_nome);
		Reg.SetString(_T("VendedorSenha"), dlg.m_senha);
		Reg.SetDWord(_T("ExibirProdutosNaoDisponiveis"), dlg.m_exibir_nao_disponiveis);
        Reg.SetDWord(_T("ExibirUnitarios"), dlg.m_exibir_unitarios);
        Reg.SetDWord(_T("Arredondar"), dlg.m_arredondar);
		Reg.SetDWord(_T("PermitirVendaItensEmFalta"), dlg.m_vender_falta);
        Reg.SetDWord(_T("Autoclear"), dlg.m_autoclear);
		Reg.SetDWord(_T("AutoDelete"), dlg.m_autodelete);
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
