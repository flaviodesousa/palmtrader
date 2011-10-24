// DBItens.h: interface for the CDBItens class.
//
//////////////////////////////////////////////////////////////////////
// $Archive: /PalmTrader 1/Pedidos/DBItens.h $
// $Author: Flávio $
// $Date: 13/05/99 22:31 $
/* $History: DBItens.h $
 * 
 * *****************  Version 2  *****************
 * User: Flávio       Date: 13/05/99   Time: 22:31
 * Updated in $/PalmTrader 1/Pedidos
 * Incluído atributo Desconto
 * 
 * *****************  Version 1  *****************
 * User: Flávio       Date: 23/09/98   Time: 16:48
 * Created in $/PalmTrader 1/Pedidos
 * Primeira implementação. Primeira bateria de testes concluída.
 */

#if !defined(AFX_DBITENS_H__3EF3C517_4D8A_11D2_BBB5_0000216E2E31__INCLUDED_)
#define AFX_DBITENS_H__3EF3C517_4D8A_11D2_BBB5_0000216E2E31__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "DB.h"

#define DBITENS_BASEID 0x2300

class CDBItens : public CDB
{
private:
	enum
	{
		en_Pedido = DBITENS_BASEID,
		en_Produto,
		en_QuantidadePedida,
		en_QuantidadeAtendida,
		en_Preco,
		en_Desconto
	};

	CCeDBProp props[6];
	CCeDBProp propSearch; // Para recuperar os itens de um pedido

public:
	BOOL FindItem(DWORD dwPedido, DWORD dwProduto);
	DWORD GetPedido(void);
	void SetPedido(DWORD dwPedido);
	BOOL FindNextItem(void);
	BOOL FindFirstItem(DWORD dwPedido);
	DWORD GetDesconto(void);
	DWORD GetPreco(void);
	DWORD GetQuantidadeAtendida(void);
	DWORD GetQuantidadePedida(void);
	DWORD GetProduto(void);
	void SetDesconto(DWORD dwDesconto);
	void SetPreco(DWORD dwPreco);
	void SetQuantidadeAtendida(DWORD dwQuantidadeAtendida);
	void SetQuantidadePedida(DWORD dwQuantidadePedida);
	void SetProduto(DWORD dwProduto);
	CDBItens();
	virtual ~CDBItens();

};

#endif // !defined(AFX_DBITENS_H__3EF3C517_4D8A_11D2_BBB5_0000216E2E31__INCLUDED_)
