// DialogPesquisaClientes.cpp : implementation file
//
// $Archive: /PalmTrader 1/Pedidos/DialogPesquisaClientes.cpp $
// $Author: Flávio $
// $Date: 12/11/98 13:27 $
/* $History: DialogPesquisaClientes.cpp $
 * 
 * *****************  Version 7  *****************
 * User: Flávio       Date: 12/11/98   Time: 13:27
 * Updated in $/PalmTrader 1/Pedidos
 * Incluída coluna com o limite de crédito do cliente na lista de clientes
 * 
 * *****************  Version 6  *****************
 * User: Flávio       Date: 21/07/98   Time: 17:18
 * Updated in $/PalmTrader 1/Pedidos
 * Suporte a atribuição automática do código de cobrança do cliente
 * 
 * *****************  Version 5  *****************
 * User: Flávio       Date: 11/07/98   Time: 20:17
 * Updated in $/PalmTrader 1/Pedidos
 * Método de centralização do diálogo de localização de clientes movido
 * para o resource.
 * 
 * *****************  Version 4  *****************
 * User: Flávio       Date: 7/07/98    Time: 7:53a
 * Updated in $/QuickSell/Pedidos
 * Permitido o registro de pedidos para clientes bloqueados
 * 
 * *****************  Version 3  *****************
 * User: Flávio       Date: 4/22/98    Time: 2:00a
 * Updated in $/QuickSell/Pedidos
 * Incluído suporte a localização de clientes pelo código.
 * Incluído campo com opção para "não faturar" que, no caso, gera uma
 * condição de venda igual a '3'.
 * Alterado formato de gravação dos pedidos que passam agora a registrar o
 * código do produto e do cliente ao invés dos números de registro.
 * Aumentada detecção de alterações no pedido, evitando perda de dados.
 * 
 * *****************  Version 2  *****************
 * User: Flávio       Date: 4/03/98    Time: 3:04a
 * Updated in $/QuickSell/Pedidos
 * Acrescentado suporte a teclado.
 * Mudada a ordem das colunas, a coluna principal passa a ser o nome do
 * cliente.
 */

#include "stdafx.h"
#include "Pedidos.h"
#include "QSDatabase.h"
#include "DialogPesquisaClientes.h"
#include "Formatter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define M_CLIENTES_COLUMNS 3
static const LV_COLUMN m_clientes_headings[] =
{
	{ LVCF_FMT|LVCF_SUBITEM|LVCF_TEXT|LVCF_WIDTH, LVCFMT_LEFT, 285, _T("Nome"), 0, 0 },
	{ LVCF_FMT|LVCF_SUBITEM|LVCF_TEXT|LVCF_WIDTH, LVCFMT_RIGHT, 70, _T("Código"), 0, 1 },
	{ LVCF_FMT|LVCF_SUBITEM|LVCF_TEXT|LVCF_WIDTH, LVCFMT_RIGHT, 80, _T("Limite"), 0, 2 }
};

/////////////////////////////////////////////////////////////////////////////
// CDialogPesquisaClientes dialog


CDialogPesquisaClientes::CDialogPesquisaClientes(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogPesquisaClientes::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogPesquisaClientes)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDialogPesquisaClientes::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogPesquisaClientes)
	DDX_Control(pDX, IDC_LIST_CLIENTES, m_clientes);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogPesquisaClientes, CDialog)
	//{{AFX_MSG_MAP(CDialogPesquisaClientes)
	ON_NOTIFY(NM_CLICK, IDC_LIST_CLIENTES, OnClickListClientes)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogPesquisaClientes message handlers

BOOL CDialogPesquisaClientes::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	for (int i = 0; i < M_CLIENTES_COLUMNS; i++)
	{
		m_clientes.InsertColumn(i, &m_clientes_headings[i]);
	}
	
	m_clientes_db.SetRecord(1);
	i = 0;
	while (!m_clientes_db.IsEOF())
	{
		CString msg;

		m_clientes_db.GetRecord();

		if (m_clientes_db.m_record.bloqueado)
		{
			msg = _T("* ");
		}
		else
		{
			msg = _T("");
		}
		msg += m_clientes_db.m_record.razao_social;
		m_clientes.InsertItem(i, msg);

		msg.Format(_T("%06d-%d"), m_clientes_db.m_record.codigo, m_clientes_db.m_record.digito);
		m_clientes.SetItemText(i, 1, msg);

		msg = CFormatter::DWordAsMoney(m_clientes_db.m_record.limite - m_clientes_db.m_record.valor_disponivel);
		m_clientes.SetItemText(i, 2, msg);

		++i;
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogPesquisaClientes::OnClickListClientes(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;
	
	if (IdentificaCliente())
	{
		EndDialog(IDOK);
	}
}

BOOL CDialogPesquisaClientes::IdentificaCliente()
{
	int iItem = -1, iCurItem, iLastItem;

	iCurItem = m_clientes.GetTopIndex();
	iLastItem = min(iCurItem + m_clientes.GetCountPerPage() - 1, m_clientes.GetItemCount() - 1);
	for (; iCurItem <= iLastItem; iCurItem++)
	{
		if (m_clientes.GetItemState(iCurItem, LVIS_FOCUSED) == (UINT)(LVIS_FOCUSED))
		{
			iItem = iCurItem;
			m_clientes_db.GetRecord(iItem + 1);
			m_cliente_codigo = m_clientes_db.m_record.codigo;
			if (m_clientes_db.m_record.bloqueado)
			{
				if (AfxMessageBox(_T("Este cliente está bloqueado.\nDeseja fazer o pedido mesmo assim?"), MB_YESNO|MB_ICONQUESTION) == IDNO)
                {
                    iItem = -1; // Cliente bloqueado, não válido
                }
			}
			
            if (iItem != -1)
			{
				m_cliente_codigo_str.Format(_T("%06d-%d"), m_clientes_db.m_record.codigo, m_clientes_db.m_record.digito);
				m_cliente_nome = m_clientes_db.m_record.razao_social;
				m_cobranca_codigo = m_clientes_db.m_record.cod_cobranca;
			}
			break;
		}
	}

	if (iItem >= 0)
	{
		return TRUE;
	}
	else
	{
        m_cliente_codigo = 0;
		return FALSE;
	}
}

BOOL CDialogPesquisaClientes::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->hwnd == m_clientes.m_hWnd)
	{
		if (pMsg->message == WM_KEYDOWN)
		{
			if (pMsg->wParam == VK_RETURN)
			{
	            if (IdentificaCliente())
	            {
		            EndDialog(IDOK);
	            }
				return TRUE;
			}
		}
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}
