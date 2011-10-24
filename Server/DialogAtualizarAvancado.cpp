// DialogAtualizarAvancado.cpp : implementation file
//
// $Archive: /QuickSell/Server/DialogAtualizarAvancado.cpp $
// $Author: Flávio $
// $Date: 9/07/98 21:31 $
/* $History: DialogAtualizarAvancado.cpp $
 * 
 * *****************  Version 4  *****************
 * User: Flávio       Date: 9/07/98    Time: 21:31
 * Updated in $/QuickSell/Server
 * Incluído tratamento para atualização automática parcial de produtos,
 * preços e clientes.
 * 
 * *****************  Version 3  *****************
 * User: Flávio       Date: 7/02/98    Time: 4:34p
 * Updated in $/QuickSell/Server
 * Incluído suporte para atualização automática de títulos.
 * 
 * *****************  Version 2  *****************
 * User: Flávio       Date: 6/26/98    Time: 1:47p
 * Updated in $/QuickSell/Server
 * Incluído suporte a atualização automática da base de dados do server
 */

#include "stdafx.h"
#include "Server.h"
#include "DialogAtualizarAvancado.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogAtualizarAvancado dialog


CDialogAtualizarAvancado::CDialogAtualizarAvancado(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogAtualizarAvancado::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogAtualizarAvancado)
	m_repeat_clientes = 0;
	m_repeat_cobranca = 0;
	m_repeat_estoque = 0;
	m_repeat_planos = 0;
	m_repeat_precos = 0;
	m_repeat_produtos = 0;
	m_repeat_tabelas = 0;
	m_repeat_vendedores = 0;
	m_start_clientes = 0;
	m_start_cobranca = 0;
	m_start_estoque = 0;
	m_start_planos = 0;
	m_start_precos = 0;
	m_start_produtos = 0;
	m_start_tabelas = 0;
	m_start_vendedores = 0;
	m_repeat_titulos = 0;
	m_start_titulos = 0;
	m_repeat_precos_partial = 0;
	m_repeat_produtos_partial = 0;
	m_repeat_clientes_partial = 0;
	m_start_clientes_partial = 0;
	m_start_precos_partial = 0;
	m_start_produtos_partial = 0;
	//}}AFX_DATA_INIT
}


void CDialogAtualizarAvancado::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogAtualizarAvancado)
	DDX_Text(pDX, IDC_EDIT_REPEAT_CLIENTES, m_repeat_clientes);
	DDX_Text(pDX, IDC_EDIT_REPEAT_COBRANCA, m_repeat_cobranca);
	DDX_Text(pDX, IDC_EDIT_REPEAT_ESTOQUE, m_repeat_estoque);
	DDX_Text(pDX, IDC_EDIT_REPEAT_PLANOS, m_repeat_planos);
	DDX_Text(pDX, IDC_EDIT_REPEAT_PRECOS, m_repeat_precos);
	DDX_Text(pDX, IDC_EDIT_REPEAT_PRODUTOS, m_repeat_produtos);
	DDX_Text(pDX, IDC_EDIT_REPEAT_TABELAS, m_repeat_tabelas);
	DDX_Text(pDX, IDC_EDIT_REPEAT_VENDEDORES, m_repeat_vendedores);
	DDX_Text(pDX, IDC_EDIT_START_CLIENTES, m_start_clientes);
	DDX_Text(pDX, IDC_EDIT_START_COBRANCA, m_start_cobranca);
	DDX_Text(pDX, IDC_EDIT_START_ESTOQUE, m_start_estoque);
	DDX_Text(pDX, IDC_EDIT_START_PLANOS, m_start_planos);
	DDX_Text(pDX, IDC_EDIT_START_PRECOS, m_start_precos);
	DDX_Text(pDX, IDC_EDIT_START_PRODUTOS, m_start_produtos);
	DDX_Text(pDX, IDC_EDIT_START_TABELAS, m_start_tabelas);
	DDX_Text(pDX, IDC_EDIT_START_VENDEDORES, m_start_vendedores);
	DDX_Text(pDX, IDC_EDIT_REPEAT_TITULOS, m_repeat_titulos);
	DDX_Text(pDX, IDC_EDIT_START_TITULOS, m_start_titulos);
	DDX_Text(pDX, IDC_EDIT_REPEAT_PRECOS2, m_repeat_precos_partial);
	DDX_Text(pDX, IDC_EDIT_REPEAT_PRODUTOS2, m_repeat_produtos_partial);
	DDX_Text(pDX, IDC_EDIT_REPEAT_CLIENTES2, m_repeat_clientes_partial);
	DDX_Text(pDX, IDC_EDIT_START_CLIENTES2, m_start_clientes_partial);
	DDX_Text(pDX, IDC_EDIT_START_PRECOS2, m_start_precos_partial);
	DDX_Text(pDX, IDC_EDIT_START_PRODUTOS2, m_start_produtos_partial);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogAtualizarAvancado, CDialog)
	//{{AFX_MSG_MAP(CDialogAtualizarAvancado)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogAtualizarAvancado message handlers
