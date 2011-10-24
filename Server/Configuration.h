// Configuration.h: interface for the CConfiguration class.
//
//////////////////////////////////////////////////////////////////////
// $Archive: /QuickSell/Server/Configuration.h $
// $Author: Flávio $
// $Date: 21/07/98 17:34 $
/* $History: Configuration.h $
 * 
 * *****************  Version 2  *****************
 * User: Flávio       Date: 21/07/98   Time: 17:34
 * Updated in $/QuickSell/Server
 * Primeira implementação
 */

#if !defined(AFX_CONFIGURATION_H__B79A4531_1BE8_11D2_BB49_0000216E2E31__INCLUDED_)
#define AFX_CONFIGURATION_H__B79A4531_1BE8_11D2_BB49_0000216E2E31__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CConfiguration  
{
public:
	CString GetDSN(void);
	CConfiguration();
	virtual ~CConfiguration();

};

#endif // !defined(AFX_CONFIGURATION_H__B79A4531_1BE8_11D2_BB49_0000216E2E31__INCLUDED_)
