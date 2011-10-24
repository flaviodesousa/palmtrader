// TitulosSynchronization.h: interface for the CTitulosSynchronization class.
//
//////////////////////////////////////////////////////////////////////
// $Archive: /QuickSell/Server/TitulosSynchronization.h $
// $Author: Flávio $
// $Date: 7/04/98 6:11p $
/* $History: TitulosSynchronization.h $
 * 
 * *****************  Version 2  *****************
 * User: Flávio       Date: 7/04/98    Time: 6:11p
 * Updated in $/QuickSell/Server
 * Colocado em source control
 */

#if !defined(AFX_TITULOSSYNCHRONIZATION_H__81EBA835_F29E_11D0_A107_00004403E294__INCLUDED_)
#define AFX_TITULOSSYNCHRONIZATION_H__81EBA835_F29E_11D0_A107_00004403E294__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "RSTitulos.h"
#include "UserAppSynchronization.h"

class CTitulosSynchronization : public CUserAppSynchronization  
{
	CString strRows[5];
	int nRowCount;
    CRSTitulos ti;

public:
	CTitulosSynchronization();
	virtual ~CTitulosSynchronization();

protected:
	virtual void SendRequest(void);
	virtual BOOL Process(CString & strRow);
};

#endif // !defined(AFX_TITULOSSYNCHRONIZATION_H__81EBA835_F29E_11D0_A107_00004403E294__INCLUDED_)
