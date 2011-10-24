// CodigosDeCobrancaSynchronization.h: interface for the CCodigosDeCobrancaSynchronization class.
//
//////////////////////////////////////////////////////////////////////
// $Archive: /QuickSell/Server/CodigosDeCobrancaSynchronization.h $
// $Author: Flávio $
// $Date: 7/04/98 6:02p $
/* $History: CodigosDeCobrancaSynchronization.h $
 * 
 * *****************  Version 3  *****************
 * User: Flávio       Date: 7/04/98    Time: 6:02p
 * Updated in $/QuickSell/Server
 * Colocado em source control
 */

#if !defined(AFX_CODIGOSDECOBRANCASYNCHRONIZATION_H__E78D2EB8_A08F_11D1_9FEE_00004403E294__INCLUDED_)
#define AFX_CODIGOSDECOBRANCASYNCHRONIZATION_H__E78D2EB8_A08F_11D1_9FEE_00004403E294__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "UserAppSynchronization.h"
#include "RSCobranca.h"

class CCodigosDeCobrancaSynchronization : public CUserAppSynchronization  
{
	CString strRows[2];
	int nRowCount;
	CRSCobranca cb;

public:
	CCodigosDeCobrancaSynchronization();
	virtual ~CCodigosDeCobrancaSynchronization();

protected:
	void SendRequest(void);
	BOOL Process(CString& strRow);
};

#endif // !defined(AFX_CODIGOSDECOBRANCASYNCHRONIZATION_H__E78D2EB8_A08F_11D1_9FEE_00004403E294__INCLUDED_)
