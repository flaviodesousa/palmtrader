// PartialPrecosSynchronization.h: interface for the CPartialPrecosSynchronization class.
//
//////////////////////////////////////////////////////////////////////
// $Archive: /QuickSell/Server/PartialPrecosSynchronization.h $
// $Author: Fl�vio $
// $Date: 9/07/98 21:37 $
/* $History: PartialPrecosSynchronization.h $
 * 
 * *****************  Version 1  *****************
 * User: Fl�vio       Date: 9/07/98    Time: 21:37
 * Created in $/QuickSell/Server
 * Primeira implementa��o
 * Inclu�do tratamento para atualiza��o autom�tica parcial de produtos,
 * pre�os e clientes.
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
