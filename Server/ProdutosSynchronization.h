// ProdutosSynchronization.h: interface for the CProdutosSynchronization class.
//
//////////////////////////////////////////////////////////////////////
// $Archive: /QuickSell/Server/ProdutosSynchronization.h $
// $Author: Flávio $
// $Date: 9/07/98 21:35 $
/* $History: ProdutosSynchronization.h $
 * 
 * *****************  Version 5  *****************
 * User: Flávio       Date: 9/07/98    Time: 21:35
 * Updated in $/QuickSell/Server
 * Métodos declarados explicitamente como virtuais
 * 
 * *****************  Version 4  *****************
 * User: Flávio       Date: 7/04/98    Time: 6:04p
 * Updated in $/QuickSell/Server
 * Acrescentada sincronização do campo pd_Disponibilidade
 */

#if !defined(AFX_PRODUTOSSYNCHRONIZATION_H__A855AC85_9EB5_11D1_9FEA_00004403E294__INCLUDED_)
#define AFX_PRODUTOSSYNCHRONIZATION_H__A855AC85_9EB5_11D1_9FEA_00004403E294__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "RSProdutos.h"
#include "UserAppSynchronization.h"

class CProdutosSynchronization : public CUserAppSynchronization  
{
	CString strRows[9];
	int nRowCount;
	CRSProdutos pd;

public:
	CProdutosSynchronization();
	virtual ~CProdutosSynchronization();

protected:
	virtual void SendRequest(void);
	virtual BOOL Process(CString& strRow);
};

#endif // !defined(AFX_PRODUTOSSYNCHRONIZATION_H__A855AC85_9EB5_11D1_9FEA_00004403E294__INCLUDED_)
