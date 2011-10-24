// UserAppSynchronization.h: interface for the CUserAppSynchronization class.
//
//////////////////////////////////////////////////////////////////////
// $Archive: /QuickSell/Server/UserAppSynchronization.h $
// $Author: Flávio $
// $Date: 25/09/98 10:45 $
/* $History: UserAppSynchronization.h $
 * 
 * *****************  Version 8  *****************
 * User: Flávio       Date: 25/09/98   Time: 10:45
 * Updated in $/QuickSell/Server
 * Re-gravado com data de check-in reduzida para o dia 25/09 (Para
 * corrigir uma mudança de data indevida no sistema)
 * 
 * *****************  Version 7  *****************
 * User: Flávio       Date: 24/10/98   Time: 17:54
 * Updated in $/QuickSell/Server
 * Incluídos controles de erros
 * 
 * *****************  Version 6  *****************
 * User: Flávio       Date: 11/07/98   Time: 19:55
 * Updated in $/QuickSell/Server
 * Implementado método para registro de erros
 * 
 * *****************  Version 5  *****************
 * User: Flávio       Date: 7/04/98    Time: 6:11p
 * Updated in $/QuickSell/Server
 * Colocado em source control
 */

#if !defined(AFX_USERAPPSYNCHRONIZATION_H__3717A463_9E7C_11D1_9FE9_00004403E294__INCLUDED_)
#define AFX_USERAPPSYNCHRONIZATION_H__3717A463_9E7C_11D1_9FE9_00004403E294__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "afxtempl.h"

class CUserAppSynchronization  
{
protected:
	CSocket sock;
	CList<CString, CString&> listErros;
	CList<CString, CString&> m_listReadLines;
	CString m_strCurrentLine;
	BOOL m_transferring;
	BOOL m_abort;
public:
	CString GetErrorMessage(void);
	BOOL HasErrors(void);
	CUserAppSynchronization();
	virtual ~CUserAppSynchronization();
	void DoIt(void);
protected:
	void AddError(CString strError);
	virtual void SendRequest(void) = 0;
	virtual BOOL Process(CString& strRow) = 0;
	CString GetRow(void);
private:
	void ReportSocketError(int);
};

#endif // !defined(AFX_USERAPPSYNCHRONIZATION_H__3717A463_9E7C_11D1_9FE9_00004403E294__INCLUDED_)
