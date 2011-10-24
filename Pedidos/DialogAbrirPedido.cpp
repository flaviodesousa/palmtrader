// DialogAbrirPedido.cpp : implementation file
//
// $Archive: /PalmTrader 1/Pedidos/DialogAbrirPedido.cpp $
// $Author: Flávio $
// $Date: 1/06/99 22:33 $
/* $History: DialogAbrirPedido.cpp $
 * 
 * *****************  Version 10  *****************
 * User: Flávio       Date: 1/06/99    Time: 22:33
 * Updated in $/PalmTrader 1/Pedidos
 * Exibição do número de pedido ampliada de 6 para 8 dígitos
 * 
 * *****************  Version 9  *****************
 * User: Flávio       Date: 12/11/98   Time: 13:26
 * Updated in $/PalmTrader 1/Pedidos
 * Incluída coluna com a data do pedido na relação de pedidos
 * 
 * *****************  Version 8  *****************
 * User: Flávio       Date: 27/10/98   Time: 10:05
 * Updated in $/PalmTrader 1/Pedidos
 * Implementada seleção de pedido via teclado
 * 
 * *****************  Version 7  *****************
 * User: Flávio       Date: 30/09/98   Time: 16:39
 * Updated in $/PalmTrader 1/Pedidos
 * Mudada ordem de exibição dos pedidos - ao invés de ordem inversa de
 * dada passou a ser por ordem inversa de número
 * 
 * *****************  Version 6  *****************
 * User: Flávio       Date: 28/09/98   Time: 16:40
 * Updated in $/PalmTrader 1/Pedidos
 * Pedidos retidos marcados com um interrogação "?"
 * 
 * *****************  Version 5  *****************
 * User: Flávio       Date: 23/09/98   Time: 16:56
 * Updated in $/PalmTrader 1/Pedidos
 * Implementada classe basica para suporte a bases de dados do Windows CE.
 * Movidas as bases de dados de pedidos e de itens para a nova classe.
 * Controle de blocos removido do registry para as novas classes
 * Incluído ícone para futuro suporte a eliminação de produtos
 * 
 * *****************  Version 4  *****************
 * User: Flávio       Date: 11/07/98   Time: 20:14
 * Updated in $/PalmTrader 1/Pedidos
 * Incluído status do pedido na tela de abertura de pedidos
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
 * User: Flávio       Date: 4/14/98    Time: 10:03a
 * Updated in $/QuickSell/Pedidos
 * Pedidos já enviados marcados com um asterisco ('*')
 */

#include "stdafx.h"
#include "Pedidos.h"
#include "DialogAbrirPedido.h"
#include "QSDatabase.h"
#include "DBPedidos.h"
#include "DBItens.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogAbrirPedido dialog


CDialogAbrirPedido::CDialogAbrirPedido(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogAbrirPedido::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogAbrirPedido)
	//}}AFX_DATA_INIT
}


void CDialogAbrirPedido::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogAbrirPedido)
	DDX_Control(pDX, IDC_LIST_PEDIDOS, m_pedidos);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogAbrirPedido, CDialog)
	//{{AFX_MSG_MAP(CDialogAbrirPedido)
	ON_NOTIFY(NM_CLICK, IDC_LIST_PEDIDOS, OnClickListPedidos)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogAbrirPedido message handlers

void CDialogAbrirPedido::OnClickListPedidos(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;

	if (IdentificaPedido())
	{
		EndDialog(IDOK);
	}
}

BOOL CDialogAbrirPedido::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_pedidos.InsertColumn(0, _T("Número"), LVCFMT_LEFT, 60);
	m_pedidos.InsertColumn(1, _T("Cliente"), LVCFMT_LEFT, 250);
	m_pedidos.InsertColumn(2, _T("Situação"), LVCFMT_LEFT, 200);
	m_pedidos.InsertColumn(3, _T("Data"), LVCFMT_LEFT, 80);

	PopulateList();

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDialogAbrirPedido::IdentificaPedido()
{
	int iItem;

	iItem = m_pedidos.GetNextItem(-1, LVNI_FOCUSED);

	if (iItem >= 0)
	{
		m_pedido = m_pedidos.GetItemData(iItem);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void CDialogAbrirPedido::PopulateList()
{
	CDBPedidos pe;
	CQSClientes cl;
	CString str;
	int nItemCount = 0;

	m_pedidos.DeleteAllItems();

	if (pe.MoveLast())
	{
		do
		{
			DWORD dwDataPedido;

			pe.Read();
			cl.FindByCodigo(pe.GetCodigoCliente());
			str.Format(_T("%08d"), pe.GetNumeroPedido());
			if (pe.GetPedidoEnviado())
			{
				str += _T("*");
			}
			if (pe.GetReterPedido())
			{
				str += _T("?");
			}
			m_pedidos.InsertItem(nItemCount, str);
			m_pedidos.SetItemText(nItemCount, 1, str = cl.m_record.razao_social);
			m_pedidos.SetItemText(nItemCount, 2, pe.GetDiagnostico());

			dwDataPedido = pe.GetDataPedido();
			str.Format(_T("%02d/%02d/%04d"), dwDataPedido % 100, dwDataPedido / 100 % 100, dwDataPedido / 10000);
			m_pedidos.SetItemText(nItemCount, 3, str);

			m_pedidos.SetItemData(nItemCount, pe.GetNumeroPedido());

			nItemCount++;
		}
		while (pe.MovePrev());
	}
}

DWORD CDialogAbrirPedido::GetPedidoNumero()
{
	return m_pedido;
}

BOOL CDialogAbrirPedido::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->hwnd == m_pedidos.m_hWnd)
	{
		if (pMsg->message == WM_KEYDOWN)
		{
			if (pMsg->wParam == VK_RETURN)
			{
	            if (IdentificaPedido())
	            {
		            EndDialog(IDOK);
	            }
				return TRUE;
			}
		}
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}
