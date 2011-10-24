// PartialClientesSynchronization.h: interface for the CPartialClientesSynchronization class.
//
//////////////////////////////////////////////////////////////////////
// $Archive: /QuickSell/Server/PartialClientesSynchronization.h $
// $Author: Fl�vio $
// $Date: 9/07/98 21:37 $
/* $History: PartialClientesSynchronization.h $
 * 
 * *****************  Version 1  *****************
 * User: Fl�vio       Date: 9/07/98    Time: 21:37
 * Created in $/QuickSell/Server
 * Primeira implementa��o
 * Inclu�do tratamento para atualiza��o autom�tica parcial de produtos,
 * pre�os e clientes.
 */

#if !defined(AFX_PARTIALCLIENTESSYNCHRONIZATION_H__7E727C04_177D_11D2_BB33_0000216E2E31__INCLUDED_)
#define AFX_PARTIALCLIENTESSYNCHRONIZATION_H__7E727C04_177D_11D2_BB33_0000216E2E31__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "ClientesSynchronization.h"

class CPartialClientesSynchronization : public CClientesSynchronization  
{
public:
	virtual void SendRequest(void);
	CPartialClientesSynchronization();
	virtual ~CPartialClientesSynchronization();

};

#endif // !defined(AFX_PARTIALCLIENTESSYNCHRONIZATION_H__7E727C04_177D_11D2_BB33_0000216E2E31__INCLUDED_)
