// PedidoItem.h: interface for the CPedidoItem class.
//
//////////////////////////////////////////////////////////////////////
// $Archive: /QuickSell/Server/PedidoItem.h $
// $Author: Flávio $
// $Date: 14/09/98 11:14 $
/* $History: PedidoItem.h $
 * 
 * *****************  Version 1  *****************
 * User: Flávio       Date: 14/09/98   Time: 11:14
 * Created in $/QuickSell/Server
 * Primeira implementação
 */

#if !defined(AFX_PEDIDOITEM_H__C0991965_4BD5_11D2_BBB0_0000216E2E31__INCLUDED_)
#define AFX_PEDIDOITEM_H__C0991965_4BD5_11D2_BBB0_0000216E2E31__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CPedidoItem  
{
public:
	DWORD	m_Produto;
	DWORD	m_QuantidadePedida;
	DWORD	m_QuantidadeAtendida;
	DWORD	m_PrecoUnitario;

	CPedidoItem();
	virtual ~CPedidoItem();

};

#endif // !defined(AFX_PEDIDOITEM_H__C0991965_4BD5_11D2_BBB0_0000216E2E31__INCLUDED_)
