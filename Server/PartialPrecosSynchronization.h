// PartialPrecosSynchronization.h: interface for the CPartialPrecosSynchronization class.
//
//////////////////////////////////////////////////////////////////////
// $Archive: /QuickSell/Server/PartialPrecosSynchronization.h $
// $Author: Flávio $
// $Date: 9/07/98 21:37 $
/* $History: PartialPrecosSynchronization.h $
 * 
 * *****************  Version 1  *****************
 * User: Flávio       Date: 9/07/98    Time: 21:37
 * Created in $/QuickSell/Server
 * Primeira implementação
 * Incluído tratamento para atualização automática parcial de produtos,
 * preços e clientes.
 */

#if !defined(AFX_PARTIALPRECOSSYNCHRONIZATION_H__7E727C05_177D_11D2_BB33_0000216E2E31__INCLUDED_)
#define AFX_PARTIALPRECOSSYNCHRONIZATION_H__7E727C05_177D_11D2_BB33_0000216E2E31__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "PrecosSynchronization.h"

class CPartialPrecosSynchronization : public CPrecosSynchronization  
{
public:
	virtual void SendRequest(void);
	CPartialPrecosSynchronization(int nTabela);
	virtual ~CPartialPrecosSynchronization();

};

#endif // !defined(AFX_PARTIALPRECOSSYNCHRONIZATION_H__7E727C05_177D_11D2_BB33_0000216E2E31__INCLUDED_)
