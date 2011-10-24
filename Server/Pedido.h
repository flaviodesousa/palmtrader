// Pedido.h: interface for the CPedido class.
//
//////////////////////////////////////////////////////////////////////
// $Archive: /PalmTrader 1/Server/Pedido.h $
// $Author: Flávio $
// $Date: 25/05/99 15:31 $
/* $History: Pedido.h $
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

#if !defined(AFX_PEDIDO_H__C0991966_4BD5_11D2_BBB0_0000216E2E31__INCLUDED_)
#define AFX_PEDIDO_H__C0991966_4BD5_11D2_BBB0_0000216E2E31__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "PedidoItem.h"

class CPedido  
{
public:
	DWORD GetDataAsNumber(void);
	CPedidoItem * GetItem(DWORD dwProduto);
	void SetQuantidadeAtendida(DWORD dwProduto, DWORD dwQuantidadeAtendida);
	void AddItem(DWORD dwProduto, DWORD dwQuantidade, DWORD dwPrecoUnitario);
	DWORD	m_Numero;
	DWORD	m_Cliente;
	BYTE	m_CondicaoVenda;
	BYTE	m_Plano;
	CString	m_Cobranca;
	WORD	m_Vendedor;
	CTime	m_Data;
	CTime	m_Recepcao;
	CTime	m_Processamento;
	CTime	m_Devolucao;
	CString	m_Diagnostico;
	BOOL	m_Reenviar;

	CMap<DWORD, DWORD&, CPedidoItem, CPedidoItem&> m_Itens;

	CPedido();
	virtual ~CPedido();

};

#endif // !defined(AFX_PEDIDO_H__C0991966_4BD5_11D2_BBB0_0000216E2E31__INCLUDED_)
