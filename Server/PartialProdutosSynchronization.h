// PartialProdutosSynchronization.h: interface for the CPartialProdutosSynchronization class.
//
//////////////////////////////////////////////////////////////////////
// $Archive: /QuickSell/Server/PartialProdutosSynchronization.h $
// $Author: Fl�vio $
// $Date: 9/07/98 21:37 $
/* $History: PartialProdutosSynchronization.h $
 * 
 * *****************  Version 1  *****************
 * User: Fl�vio       Date: 9/07/98    Time: 21:37
 * Created in $/QuickSell/Server
 * Primeira implementa��o
 * Inclu�do tratamento para atualiza��o autom�tica parcial de produtos,
 * pre�os e clientes.
 */

#if !defined(AFX_PARTIALPRODUTOSSYNCHRONIZATION_H__7E727C03_177D_11D2_BB33_0000216E2E31__INCLUDED_)
#define AFX_PARTIALPRODUTOSSYNCHRONIZATION_H__7E727C03_177D_11D2_BB33_0000216E2E31__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "ProdutosSynchronization.h"

class CPartialProdutosSynchronization : public CProdutosSynchronization  
{
public:
	virtual void SendRequest(void);
	CPartialProdutosSynchronization();
	virtual ~CPartialProdutosSynchronization();

};

#endif // !defined(AFX_PARTIALPRODUTOSSYNCHRONIZATION_H__7E727C03_177D_11D2_BB33_0000216E2E31__INCLUDED_)
