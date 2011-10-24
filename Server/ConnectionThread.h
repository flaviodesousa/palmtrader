// ConnectionThread.h : header file
//
// $Archive: /QuickSell/Server/ConnectionThread.h $
// $Author: Flávio $
// $Date: 25/09/98 10:49 $
/* $History: ConnectionThread.h $
 * 
 * *****************  Version 3  *****************
 * User: Flávio       Date: 25/09/98   Time: 10:49
 * Updated in $/QuickSell/Server
 * Re-gravado com data de check-in reduzida para o dia 25/09 (Para
 * corrigir uma mudança de data indevida no sistema)
 */

#include "SessionThread.h"

#if !defined(AFX_CONNECTIONTHREAD_H__7A769247_6B30_11D1_9F7C_204C4F4F5020__INCLUDED_)
#define AFX_CONNECTIONTHREAD_H__7A769247_6B30_11D1_9F7C_204C4F4F5020__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
#define MAX_CONNECTIONS 128

/////////////////////////////////////////////////////////////////////////////
// CConnectionThread thread

class CConnectionThread
{
//public:
protected:
	CWinThread *m_thread;
	SOCKET m_s; // Socket que fica na escuta (listen)
	SOCKADDR_IN m_addr;
	BOOL m_suspend; 
	BOOL m_cancel;
	HWND m_hWnd;
	BOOL m_hWnd_available;
	struct // Armazena as conexoes
	{
		CSessionThread *Session;
	} m_connections[MAX_CONNECTIONS];

// Attributes
public:

// Operations
public:
	CConnectionThread();
	~CConnectionThread();
	void Start(void);

protected:
	void Run(void);

// Implementation
public:

	friend UINT ConnectionThreadStart(LPVOID lParam);

private:
	void ReportSocketError(int nLine);
};

/////////////////////////////////////////////////////////////////////////////

#endif // !defined(AFX_CONNECTIONTHREAD_H__7A769247_6B30_11D1_9F7C_204C4F4F5020__INCLUDED_)
