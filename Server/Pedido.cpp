// Pedido.cpp: implementation of the CPedido class.
//
//////////////////////////////////////////////////////////////////////
// $Archive: /PalmTrader 1/Server/Pedido.cpp $
// $Author: Flávio $
// $Date: 25/05/99 15:31 $
/* $History: Pedido.cpp $
 * 
 * *****************  Version 3  *****************
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
 * *****************  Version 1  *****************
 * User: Flávio       Date: 15/09/98   Time: 12:27
 * Created in $/QuickSell/Server
 * Primeira implementação
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
