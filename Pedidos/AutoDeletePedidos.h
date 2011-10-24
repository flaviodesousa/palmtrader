// AutoDeletePedidos.h: interface for the CAutoDeletePedidos class.
//
//////////////////////////////////////////////////////////////////////
// $Archive: /PalmTrader 1/Pedidos/AutoDeletePedidos.h $
// $Author: Fl�vio $
// $Date: 11/11/98 15:10 $
/* $History: AutoDeletePedidos.h $
 * 
 * *****************  Version 1  *****************
 * User: Fl�vio       Date: 11/11/98   Time: 15:10
 * Created in $/PalmTrader 1/Pedidos
 * Implementado recurso de elimina��o autom�tica de pedidos em fun��o da
 * data da �ltima altera��o
 */

#if !defined(AFX_AUTODELETEPEDIDOS_H__08353263_797F_11D2_BC04_0080AD426C46__INCLUDED_)
#define AFX_AUTODELETEPEDIDOS_H__08353263_797F_11D2_BC04_0080AD426C46__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CAutoDeletePedidos  
{
public:
	static void Run(void);
	CAutoDeletePedidos();
	virtual ~CAutoDeletePedidos();

};

#endif // !defined(AFX_AUTODELETEPEDIDOS_H__08353263_797F_11D2_BC04_0080AD426C46__INCLUDED_)
