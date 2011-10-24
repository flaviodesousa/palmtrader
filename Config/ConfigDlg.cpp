// ConfigDlg.cpp : implementation file
//
// $Archive: /PalmTrader 1/Config/ConfigDlg.cpp $
// $Author: Flávio $
// $Date: 11/11/98 15:12 $
/* $History: ConfigDlg.cpp $
 * 
 * *****************  Version 6  *****************
 * User: Flávio       Date: 11/11/98   Time: 15:12
 * Updated in $/PalmTrader 1/Config
 * Implementado recurso de eliminação automática de pedidos em função da
 * data da última alteração
 * Eliminado parâmetro "Nome do Vendedor"
 * 
 * *****************  Version 5  *****************
 * User: Flávio       Date: 10/07/98   Time: 23:16
 * Updated in $/PalmTrader 1/Config
 * Implementado item de configuração que regula a permissão de venda de
 * itens não disponíveis
 * 
 * *****************  Version 4  *****************
 * User: Flávio       Date: 7/05/98    Time: 1:02p
 * Updated in $/QuickSell/QSConfig
 * Incluídas opções para exibição de preços unitários
 * 
 * *****************  Version 3  *****************
 * User: Flávio       Date: 4/13/98    Time: 1:34a
 * Updated in $/QuickSell/QSConfig
 * Incluída opção para se determinar o tempo em segundos em que a busca
 * automática limpa o texto de busca.
 */

#include "stdafx.h"
#include "Afdfunc.h"

#include "Config.h"
#include "ConfigDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAX_RAS_ENTRIES 16 // Enough? For a HPC! Of Course!!

/////////////////////////////////////////////////////////////////////////////
// CConfigDlg dialog

CConfigDlg::CConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfigDlg)
	m_porta = 0;
	m_senha = _T("");
	m_servidor = _T("");
	m_tentativas = 0;
	m_vendedor_numero = 0;
	m_conexao = _T("");
	m_exibir_nao_disponiveis = FALSE;
	m_autoclear = 0;
	m_arredondar = FALSE;
	m_exibir_unitarios = FALSE;
	m_vender_falta = FALSE;
	m_autodelete = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigDlg)
	DDX_Control(pDX, IDC_COMBO_CONEXOES, m_conexoes_ctrl);
	DDX_Text(pDX, IDC_EDIT_PORTA, m_porta);
	DDV_MinMaxUInt(pDX, m_porta, 1024, 65535);
	DDX_Text(pDX, IDC_EDIT_SENHA, m_senha);
	DDV_MaxChars(pDX, m_senha, 8);
	DDX_Text(pDX, IDC_EDIT_SERVIDOR, m_servidor);
	DDV_MaxChars(pDX, m_servidor, 128);
	DDX_Text(pDX, IDC_EDIT_TENTATIVAS, m_tentativas);
	DDV_MinMaxUInt(pDX, m_tentativas, 1, 16);
	DDX_Text(pDX, IDC_EDIT_VENDEDOR_NUMERO, m_vendedor_numero);
	DDV_MinMaxUInt(pDX, m_vendedor_numero, 1, 9999);
	DDX_CBString(pDX, IDC_COMBO_CONEXOES, m_conexao);
	DDX_Check(pDX, IDC_CHECK_NAO_DISPONIVEIS, m_exibir_nao_disponiveis);
	DDX_Text(pDX, IDC_EDIT_AUTOCLEAR, m_autoclear);
	DDV_MinMaxUInt(pDX, m_autoclear, 1, 15);
	DDX_Check(pDX, IDC_CHECK_ARREDONDAR, m_arredondar);
	DDX_Check(pDX, IDC_CHECK_EXIBIR_UNITARIOS, m_exibir_unitarios);
	DDX_Check(pDX, IDC_CHECK_VENDER_FALTA, m_vender_falta);
	DDX_Text(pDX, IDC_EDIT_AUTO_DELETE, m_autodelete);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CConfigDlg, CDialog)
	//{{AFX_MSG_MAP(CConfigDlg)
// MM not needed in wce dialogs:	ON_WM_PAINT()
// MM not needed in wce dialogs:	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigDlg message handlers

BOOL CConfigDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	CenterWindow(GetDesktopWindow());	// center to the hpc screen

	RASENTRYNAME RASEntries[MAX_RAS_ENTRIES];
	DWORD dwEntries, dwRetCode, dwBufSize = sizeof RASEntries;

	dwRetCode = RasEnumEntries(
		NULL, NULL, &RASEntries[0], &dwBufSize, &dwEntries);
	ASSERT(!dwRetCode);

	if (!dwRetCode)
	{
		CString sValue = m_conexao;
		m_conexoes_ctrl.ResetContent();
		for (UINT i=0; i < dwEntries; i++)
			m_conexoes_ctrl.AddString(RASEntries[i].szEntryName);
		m_conexao = sValue;
	}

	UpdateData(FALSE);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}
