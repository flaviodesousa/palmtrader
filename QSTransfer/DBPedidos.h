// DBPedidos.h: interface for the CDBPedidos class.
//
//////////////////////////////////////////////////////////////////////
// $Archive: /PalmTrader 1/Pedidos/DBPedidos.h $
// $Author: Flávio $
// $Date: 23/09/98 16:48 $
/* $History: DBPedidos.h $
 * 
 * *****************  Version 1  *****************
 * User: Flávio       Date: 23/09/98   Time: 16:48
 * Created in $/PalmTrader 1/Pedidos
 * Primeira implementação. Primeira bateria de testes concluída.
 */

#if !defined(AFX_DBPEDIDOS_H__3EF3C516_4D8A_11D2_BBB5_0000216E2E31__INCLUDED_)
#define AFX_DBPEDIDOS_H__3EF3C516_4D8A_11D2_BBB5_0000216E2E31__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "DB.h"

#define DBPEDIDOS_BASEID 0x2200

class CDBPedidos : public CDB
{
public:
	enum // This enumerator is public just because some of its members can be used in the constructor
	{
		en_PedidoNumero = DBPEDIDOS_BASEID,
		en_ClienteCodigo,
		en_CondicaoVenda,
		en_Plano,
		en_Desconto,
		en_ReterPedido,
		en_Cobranca,
		en_Diagnostico,
		en_PedidoEnviado,
		en_Data
	};

private:
	CCeDBProp props[10];

public:
	BOOL Find(DWORD dwNumeroPedido);
	void SetDataPedido(DWORD DataPedido);
	void SetPedidoEnviado(BOOL bPedidoEnviado);
	void SetDiagnostico(CString strDiagnostico);
	void SetCodigoCobranca(CString strCobranca);
	void SetReterPedido(BOOL bReterPedido);
	void SetDesconto(WORD wDesconto);
	void SetPlano(WORD wPlano);
	void SetCondicaoVenda(WORD wCondicaoVenda);
	void SetCodigoCliente(DWORD dwCodigoCliente);
	void SetNumeroPedido(DWORD dwNumeroPedido);

	DWORD	GetDataPedido(void);
	BOOL	GetPedidoEnviado(void);
	CString	GetDiagnostico(void);
	CString	GetCodigoCobranca(void);
	BOOL	GetReterPedido(void);
	WORD	GetDesconto(void);
	WORD	GetPlano(void);
	WORD	GetCondicaoVenda(void);
	DWORD	GetCodigoCliente(void);
	DWORD	GetNumeroPedido(void);

	CDBPedidos(WORD wSortOrder = en_PedidoNumero);
	virtual ~CDBPedidos();

};

#endif // !defined(AFX_DBPEDIDOS_H__3EF3C516_4D8A_11D2_BBB5_0000216E2E31__INCLUDED_)
