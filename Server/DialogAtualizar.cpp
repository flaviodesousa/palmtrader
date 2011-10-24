// DialogAtualizar.cpp : implementation file
//
// $Archive: /QuickSell/Server/DialogAtualizar.cpp $
// $Author: Flávio $
// $Date: 9/07/98 21:30 $
/* $History: DialogAtualizar.cpp $
 * 
 * *****************  Version 8  *****************
 * User: Flávio       Date: 9/07/98    Time: 21:30
 * Updated in $/QuickSell/Server
 * Incluído tratamento para atualização automática parcial de produtos,
 * preços e clientes.
 * 
 * *****************  Version 7  *****************
 * User: Flávio       Date: 7/02/98    Time: 4:34p
 * Updated in $/QuickSell/Server
 * Incluído suporte para atualização manual de títulos
 * 
 * *****************  Version 6  *****************
 * User: Flávio       Date: 6/26/98    Time: 1:46p
 * Updated in $/QuickSell/Server
 * Incluído suporte a atualização automática da base de dados do server
 * 
 * *****************  Version 5  *****************
 * User: Flávio       Date: 6/25/98    Time: 8:02p
 * Updated in $/QuickSell/Server
 * Removido tratamento manual do botão "Iniciar...", este botão agora
 * retorna IDOK
 * Incluído cabeçalho padrão
 */

#include "stdafx.h"
#include "Server.h"
#include "DialogAtualizar.h"

#include "DialogAtualizarAvancado.h"
#include "RSTabelasPrecos.h"
#include "Registry.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogAtualizar dialog


CDialogAtualizar::CDialogAtualizar(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogAtualizar::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogAtualizar)
	m_atualizar_clientes = FALSE;
	m_atualizar_codigos_de_cobranca = FALSE;
	m_atualizar_planos = FALSE;
	m_atualizar_precos = FALSE;
	m_atualizar_produtos = FALSE;
	m_atualizar_estoque = FALSE;
	m_atualizar_tabelas = FALSE;
	m_atualizar_vendedores = FALSE;
	m_paralelo = FALSE;
	m_atualizar_titulos = FALSE;
	m_atualizar_clientes_partial = FALSE;
	m_atualizar_precos_partial = FALSE;
	m_atualizar_produtos_partial = FALSE;
	//}}AFX_DATA_INIT
}


void CDialogAtualizar::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogAtualizar)
	DDX_Check(pDX, IDC_CHECK_CLIENTES, m_atualizar_clientes);
	DDX_Check(pDX, IDC_CHECK_COBRANCA, m_atualizar_codigos_de_cobranca);
	DDX_Check(pDX, IDC_CHECK_PLANOS, m_atualizar_planos);
	DDX_Check(pDX, IDC_CHECK_PRECOS, m_atualizar_precos);
	DDX_Check(pDX, IDC_CHECK_PRODUTOS, m_atualizar_produtos);
	DDX_Check(pDX, IDC_CHECK_ESTOQUE, m_atualizar_estoque);
	DDX_Check(pDX, IDC_CHECK_TABELAS, m_atualizar_tabelas);
	DDX_Check(pDX, IDC_CHECK_VENDEDORES, m_atualizar_vendedores);
	DDX_Check(pDX, IDC_CHECK_PARALELO, m_paralelo);
	DDX_Check(pDX, IDC_CHECK_TITULOS, m_atualizar_titulos);
	DDX_Check(pDX, IDC_CHECK_CLIENTES_PARTIAL, m_atualizar_clientes_partial);
	DDX_Check(pDX, IDC_CHECK_PRECOS_PARTIAL, m_atualizar_precos_partial);
	DDX_Check(pDX, IDC_CHECK_PRODUTOS_PARTIAL, m_atualizar_produtos_partial);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogAtualizar, CDialog)
	//{{AFX_MSG_MAP(CDialogAtualizar)
	ON_BN_CLICKED(IDC_BUTTON_AVANCADO, OnButtonAvancado)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogAtualizar message handlers


void CDialogAtualizar::OnButtonAvancado() 
{
    CDialogAtualizarAvancado dlg;

    {
        CRegistry reg;

	    dlg.m_repeat_clientes   = (short)reg.GetDWord(_T("IntervaloClientes"), 0);
	    dlg.m_repeat_cobranca   = (short)reg.GetDWord(_T("IntervaloCobranca"), 0);
	    dlg.m_repeat_estoque    = (short)reg.GetDWord(_T("IntervaloEstoque"), 0);
	    dlg.m_repeat_planos     = (short)reg.GetDWord(_T("IntervaloPlanos"), 0);
	    dlg.m_repeat_precos     = (short)reg.GetDWord(_T("IntervaloPrecos"), 0);
	    dlg.m_repeat_produtos   = (short)reg.GetDWord(_T("IntervaloProdutos"), 0);
	    dlg.m_repeat_tabelas    = (short)reg.GetDWord(_T("IntervaloTabelas"), 0);
	    dlg.m_repeat_vendedores = (short)reg.GetDWord(_T("IntervaloVendedores"), 0);

	    dlg.m_start_clientes    = (short)reg.GetDWord(_T("InicioClientes"), 0);
	    dlg.m_start_cobranca    = (short)reg.GetDWord(_T("InicioCobranca"), 0);
	    dlg.m_start_estoque     = (short)reg.GetDWord(_T("InicioEstoque"), 0);
	    dlg.m_start_planos      = (short)reg.GetDWord(_T("InicioPlanos"), 0);
	    dlg.m_start_precos      = (short)reg.GetDWord(_T("InicioPrecos"), 0);
	    dlg.m_start_produtos    = (short)reg.GetDWord(_T("InicioProdutos"), 0);
	    dlg.m_start_tabelas     = (short)reg.GetDWord(_T("InicioTabelas"), 0);
	    dlg.m_start_vendedores  = (short)reg.GetDWord(_T("InicioVendedores"), 0);

		dlg.m_repeat_clientes_partial = (short)reg.GetDWord(_T("IntervaloClientesParcial"), 0);
		dlg.m_repeat_produtos_partial = (short)reg.GetDWord(_T("IntervaloProdutosParcial"), 0);
		dlg.m_repeat_precos_partial   = (short)reg.GetDWord(_T("IntervaloPrecosParcial"), 0);

		dlg.m_start_clientes_partial  = (short)reg.GetDWord(_T("InicioClientesParcial"), 0);
		dlg.m_start_produtos_partial  = (short)reg.GetDWord(_T("InicioProdutosParcial"), 0);
		dlg.m_start_precos_partial    = (short)reg.GetDWord(_T("InicioPrecosParcial"), 0);
    }

    if (dlg.DoModal() == IDOK)
    {
        CRegistry reg;

	    reg.SetDWord(_T("IntervaloClientes"), dlg.m_repeat_clientes);
	    reg.SetDWord(_T("IntervaloCobranca"), dlg.m_repeat_cobranca);
	    reg.SetDWord(_T("IntervaloEstoque"), dlg.m_repeat_estoque);
	    reg.SetDWord(_T("IntervaloPlanos"), dlg.m_repeat_planos);
	    reg.SetDWord(_T("IntervaloPrecos"), dlg.m_repeat_precos);
	    reg.SetDWord(_T("IntervaloProdutos"), dlg.m_repeat_produtos);
	    reg.SetDWord(_T("IntervaloTabelas"), dlg.m_repeat_tabelas);
	    reg.SetDWord(_T("IntervaloVendedores"), dlg.m_repeat_vendedores);

	    reg.SetDWord(_T("InicioClientes"), dlg.m_start_clientes);
	    reg.SetDWord(_T("InicioCobranca"), dlg.m_start_cobranca);
	    reg.SetDWord(_T("InicioEstoque"), dlg.m_start_estoque);
	    reg.SetDWord(_T("InicioPlanos"), dlg.m_start_planos);
	    reg.SetDWord(_T("InicioPrecos"), dlg.m_start_precos);
	    reg.SetDWord(_T("InicioProdutos"), dlg.m_start_produtos);
	    reg.SetDWord(_T("InicioTabelas"), dlg.m_start_tabelas);
	    reg.SetDWord(_T("InicioVendedores"), dlg.m_start_vendedores);

		reg.SetDWord(_T("IntervaloClientesParcial"), dlg.m_repeat_clientes_partial);
		reg.SetDWord(_T("IntervaloProdutosParcial"), dlg.m_repeat_produtos_partial);
		reg.SetDWord(_T("IntervaloPrecosParcial"), dlg.m_repeat_precos_partial);

		reg.SetDWord(_T("InicioClientesParcial"), dlg.m_start_clientes_partial);
		reg.SetDWord(_T("InicioProdutosParcial"), dlg.m_start_produtos_partial);
		reg.SetDWord(_T("InicioPrecosParcial"), dlg.m_start_precos_partial);
    }
}
