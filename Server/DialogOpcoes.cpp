// DialogOpcoes.cpp : implementation file
//

#include "stdafx.h"
#include "Server.h"
#include "DialogOpcoes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogOpcoes dialog


CDialogOpcoes::CDialogOpcoes(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogOpcoes::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogOpcoes)
	m_aplicacao_address = _T("");
	m_aplicacao_port = 0;
	m_db_dsn = _T("");
	m_db_senha = _T("");
	m_pedidos_ultimo_bloco = _T("");
	m_db_usuario = _T("");
	m_pedidos_tamanho_bloco = 0;
	m_pedidos_proximo_numero = 0;
	m_porta_vendedores = 0;
	//}}AFX_DATA_INIT
}


void CDialogOpcoes::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogOpcoes)
	DDX_Text(pDX, IDC_APLICACAO_ADDRESS, m_aplicacao_address);
	DDX_Text(pDX, IDC_APLICACAO_PORT, m_aplicacao_port);
	DDV_MinMaxUInt(pDX, m_aplicacao_port, 1, 65535);
	DDX_Text(pDX, IDC_DSN, m_db_dsn);
	DDX_Text(pDX, IDC_SENHA, m_db_senha);
	DDX_Text(pDX, IDC_ULTIMO_BLOCO_ENVIADO, m_pedidos_ultimo_bloco);
	DDX_Text(pDX, IDC_USUARIO, m_db_usuario);
	DDX_Text(pDX, IDC_TAMANHO_BLOCO, m_pedidos_tamanho_bloco);
	DDV_MinMaxDWord(pDX, m_pedidos_tamanho_bloco, 1, 1000);
	DDX_Text(pDX, IDC_PROXIMO_NUMERO_PEDIDO, m_pedidos_proximo_numero);
	DDV_MinMaxDWord(pDX, m_pedidos_proximo_numero, 1, 99999999);
	DDX_Text(pDX, IDC_PORTA_VENDEDORES, m_porta_vendedores);
	DDV_MinMaxUInt(pDX, m_porta_vendedores, 1, 65535);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogOpcoes, CDialog)
	//{{AFX_MSG_MAP(CDialogOpcoes)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogOpcoes message handlers
