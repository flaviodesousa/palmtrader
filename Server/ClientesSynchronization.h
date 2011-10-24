// ClientesSynchronization.h: interface for the CClientesSynchronization class.
//
//////////////////////////////////////////////////////////////////////
// $Archive: /QuickSell/Server/ClientesSynchronization.h $
// $Author: Flávio $
// $Date: 9/07/98 21:33 $
/* $History: ClientesSynchronization.h $
 * 
 * *****************  Version 4  *****************
 * User: Flávio       Date: 9/07/98    Time: 21:33
 * Updated in $/QuickSell/Server
 * Métodos declarados explicitamente como virtuais
 * 
 * *****************  Version 3  *****************
 * User: Flávio       Date: 7/04/98    Time: 6:02p
 * Updated in $/QuickSell/Server
 * Acrescentado campo "cl_Tabela"
 */

#if !defined(AFX_CLIENTESSYNCHRONIZATION_H__A8522236_9F7B_11D1_9FEB_00004403E294__INCLUDED_)
#define AFX_CLIENTESSYNCHRONIZATION_H__A8522236_9F7B_11D1_9FEB_00004403E294__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "RSClientes.h"
#include "UserAppSynchronization.h"

class CClientesSynchronization : public CUserAppSynchronization  
{
	CString strRows[28];
	int nRowCount;
	CRSClientes cl;
public:
	CClientesSynchronization();
	virtual ~CClientesSynchronization();

protected:
	virtual void SendRequest(void);
	virtual BOOL Process(CString& strRow);
};

#endif // !defined(AFX_CLIENTESSYNCHRONIZATION_H__A8522236_9F7B_11D1_9FEB_00004403E294__INCLUDED_)
