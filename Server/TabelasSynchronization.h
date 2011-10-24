// TabelasSynchronization.h: interface for the CTabelasSynchronization class.
//
//////////////////////////////////////////////////////////////////////
// $Archive: /QuickSell/Server/TabelasSynchronization.h $
// $Author: Flávio $
// $Date: 7/04/98 6:11p $
/* $History: TabelasSynchronization.h $
 * 
 * *****************  Version 3  *****************
 * User: Flávio       Date: 7/04/98    Time: 6:11p
 * Updated in $/QuickSell/Server
 * Colocado em source control
 */

#if !defined(AFX_TABELASSYNCHRONIZATION_H__E78D2EB3_A08F_11D1_9FEE_00004403E294__INCLUDED_)
#define AFX_TABELASSYNCHRONIZATION_H__E78D2EB3_A08F_11D1_9FEE_00004403E294__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "RSTabelasPrecos.h"
#include "UserAppSynchronization.h"

class CTabelasSynchronization : public CUserAppSynchronization  
{
	CRSTabelasPrecos tp;

public:
	CTabelasSynchronization();
	virtual ~CTabelasSynchronization();

protected:
	BOOL Process(CString & strRow);
	void SendRequest(void);
};

#endif // !defined(AFX_TABELASSYNCHRONIZATION_H__E78D2EB3_A08F_11D1_9FEE_00004403E294__INCLUDED_)
