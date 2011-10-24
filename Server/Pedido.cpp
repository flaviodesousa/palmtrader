// Pedido.cpp: implementation of the CPedido class.
//
//////////////////////////////////////////////////////////////////////
// $Archive: /PalmTrader 1/Server/Pedido.cpp $
// $Author: Fl�vio $
// $Date: 25/05/99 15:31 $
/* $History: Pedido.cpp $
 * 
 * *****************  Version 3  *****************
 * User: Fl�vio       Date: 25/05/99   Time: 15:31
 * Updated in $/PalmTrader 1/Server
 * Altera��es feitas para o release 1.30
 * Inclu�da rotina gen�rica para convers�o de n�meros em strings
 * Corrigido bug na defini��o do tamanho do buffer de envio de pacotes TCP
 * nos m�dulos de sincroniza��o
 * Separada a porta TCP de conex�o com os clientes e servidores
 * Inclu�do m�todo em CPedido para retornar a data do pedido como DWORD,
 * que � usada no m�dulo de sincroniza��o de pedidos
 * Implementados novos atributos em pre�os
 * Inclu�do o script de cria��o da base SQL
 * 
 * *****************  Version 1  *****************
 * User: Fl�vio       Date: 15/09/98   Time: 12:27
 * Created in $/QuickSell/Server
 * Primeira implementa��o
 */

#include "stdafx.h"
#include "server.h"
#include "afxtempl.h"
#include "Pedido.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPedido::CPedido()
{

}

CPedido::~CPedido()
{
	m_Itens.RemoveAll();
}

void CPedido::AddItem(DWORD dwProduto, DWORD dwQuantidade, DWORD dwPrecoUnitario)
{
	CPedidoItem item;

	item.m_Produto = dwProduto;
	item.m_QuantidadePedida = dwQuantidade;
	item.m_QuantidadeAtendida = 0;
	item.m_PrecoUnitario = dwPrecoUnitario;

	m_Itens[dwProduto] = item;
}

void CPedido::SetQuantidadeAtendida(DWORD dwProduto, DWORD dwQuantidadeAtendida)
{
	m_Itens[dwProduto].m_QuantidadeAtendida = dwQuantidadeAtendida;
}

CPedidoItem * CPedido::GetItem(DWORD dwProduto)
{
	return &m_Itens[dwProduto];
}

DWORD CPedido::GetDataAsNumber()
{
	return m_Data.GetYear() * 10000L + m_Data.GetMonth() * 100L + m_Data.GetDay();
}
