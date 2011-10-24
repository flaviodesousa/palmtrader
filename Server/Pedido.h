// Pedido.h: interface for the CPedido class.
//
//////////////////////////////////////////////////////////////////////
// $Archive: /PalmTrader 1/Server/Pedido.h $
// $Author: Fl�vio $
// $Date: 25/05/99 15:31 $
/* $History: Pedido.h $
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
