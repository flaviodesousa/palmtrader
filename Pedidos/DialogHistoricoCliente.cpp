// DialogHistoricoCliente.cpp : implementation file
//
// $Archive: /PalmTrader 1/Pedidos/DialogHistoricoCliente.cpp $
// $Author: Flávio $
// $Date: 11/07/98 20:15 $
/* $History: DialogHistoricoCliente.cpp $
 * 
 * *****************  Version 3  *****************
 * User: Flávio       Date: 11/07/98   Time: 20:15
 * Updated in $/PalmTrader 1/Pedidos
 * Implementada exibição dos títulos em aberto do cliente
 * 
 * *****************  Version 2  *****************
 * User: Flávio       Date: 7/07/98    Time: 7:52a
 * Updated in $/QuickSell/Pedidos
 * Primeira implementação.
 * Falta suporte a lista de títulos
 */

#include "stdafx.h"
#include "Pedidos.h"
#include "DialogHistoricoCliente.h"
#include "QSTitulos.h"
#include "Formatter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define M_TITULOS_COLUMNS 4
static const LV_COLUMN m_titulos_headings[] =
{
	{ LVCF_FMT|LVCF_SUBITEM|LVCF_TEXT|LVCF_WIDTH, LVCFMT_LEFT,  200, _T("Número"),     0, 0 },
	{ LVCF_FMT|LVCF_SUBITEM|LVCF_TEXT|LVCF_WIDTH, LVCFMT_RIGHT, 100, _T("Valor"),      0, 1 },
	{ LVCF_FMT|LVCF_SUBITEM|LVCF_TEXT|LVCF_WIDTH, LVCFMT_LEFT,  100, _T("Emissão"),    0, 2 },
	{ LVCF_FMT|LVCF_SUBITEM|LVCF_TEXT|LVCF_WIDTH, LVCFMT_LEFT,  100, _T("Vencimento"), 0, 3 }
};

/////////////////////////////////////////////////////////////////////////////
// CDialogHistoricoCliente dialog


CDialogHistoricoCliente::CDialogHistoricoCliente(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogHistoricoCliente::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogHistoricoCliente)
	m_disponivel = _T("");
	m_cliente = _T("");
	m_limite = _T("");
	//}}AFX_DATA_INIT
}


void CDialogHistoricoCliente::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogHistoricoCliente)
	DDX_Control(pDX, IDC_LIST_TITULOS, m_titulos);
	DDX_Text(pDX, IDC_EDIT_DISPONIVEL, m_disponivel);
	DDX_Text(pDX, IDC_EDIT_CLIENTE, m_cliente);
	DDX_Text(pDX, IDC_EDIT_LIMITE, m_limite);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogHistoricoCliente, CDialog)
	//{{AFX_MSG_MAP(CDialogHistoricoCliente)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogHistoricoCliente message handlers

BOOL CDialogHistoricoCliente::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CQSTitulos ti;
	CString str;
	for (int i = 0; i < M_TITULOS_COLUMNS; i++)
	{
		m_titulos.InsertColumn(i, &m_titulos_headings[i]);
	}

	i = 0;

	while (!ti.IsEOF())
	{
		ti.GetRecord();
		if (ti.m_record.cliente == m_cliente_codigo)
		{
			m_titulos.InsertItem(i, str = ti.m_record.numero);
			m_titulos.SetItemText(i, 1, str = CFormatter::DWordAsMoney(ti.m_record.valor));
			m_titulos.SetItemText(i, 2, str = ti.m_record.emissao);
			m_titulos.SetItemText(i, 3, str = ti.m_record.vencimento);
			i++;
		}
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
