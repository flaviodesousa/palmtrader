// VendedoresSynchronization.h: interface for the CVendedoresSynchronization class.
//
//////////////////////////////////////////////////////////////////////
// $Archive: /QuickSell/Server/VendedoresSynchronization.h $
// $Author: Flávio $
// $Date: 7/04/98 6:11p $
/* $History: VendedoresSynchronization.h $
 * 
 * *****************  Version 3  *****************
 * User: Flávio       Date: 7/04/98    Time: 6:11p
 * Updated in $/QuickSell/Server
 * Colocado em source control
 */

#if !defined(AFX_VENDEDORESSYNCHRONIZATION_H__E78D2EB5_A08F_11D1_9FEE_00004403E294__INCLUDED_)
#define AFX_VENDEDORESSYNCHRONIZATION_H__E78D2EB5_A08F_11D1_9FEE_00004403E294__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "RSVendedores.h"

#include "UserAppSynchronization.h"

class CVendedoresSynchronization : public CUserAppSynchronization  
{
	CRSVendedores vd;
	CString strRows[4];
	int nRowCount;

public:
	CVendedoresSynchronization();
	virtual ~CVendedoresSynchronization();

protected:
	void SendRequest(void);
	BOOL Process(CString& strRow);
};

#endif // !defined(AFX_VENDEDORESSYNCHRONIZATION_H__E78D2EB5_A08F_11D1_9FEE_00004403E294__INCLUDED_)
