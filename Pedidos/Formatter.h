// Formatter.h: interface for the CFormatter class.
//
//////////////////////////////////////////////////////////////////////
// $Archive: /QuickSell/Pedidos/Formatter.h $
// $Author: Flávio $
// $Date: 7/05/98 2:28p $
/* $History: Formatter.h $
 * 
 * *****************  Version 1  *****************
 * User: Flávio       Date: 7/05/98    Time: 2:28p
 * Created in $/QuickSell/Pedidos
 * Primeira implementação
 */

#if !defined(AFX_FORMATTER_H__59E89615_F537_11D0_A10E_00004403E294__INCLUDED_)
#define AFX_FORMATTER_H__59E89615_F537_11D0_A10E_00004403E294__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CFormatter  
{
public:
	static CString DWordAsMoney(DWORD dwValue);
	CFormatter();
	virtual ~CFormatter();

};

#endif // !defined(AFX_FORMATTER_H__59E89615_F537_11D0_A10E_00004403E294__INCLUDED_)
