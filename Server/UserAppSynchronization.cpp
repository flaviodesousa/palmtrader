// UserAppSynchronization.cpp: implementation of the CUserAppSynchronization class.
//
//////////////////////////////////////////////////////////////////////
// $Archive: /PalmTrader 1/Server/UserAppSynchronization.cpp $
// $Author: Flávio $
// $Date: 11/05/99 15:56 $
/* $History: UserAppSynchronization.cpp $
 * 
 * *****************  Version 9  *****************
 * User: Flávio       Date: 11/05/99   Time: 15:56
 * Updated in $/PalmTrader 1/Server
 * 
 * *****************  Version 8  *****************
 * User: Flávio       Date: 25/09/98   Time: 10:49
 * Updated in $/QuickSell/Server
 * Re-gravado com data de check-in reduzida para o dia 25/09 (Para
 * corrigir uma mudança de data indevida no sistema)
 */

#include "stdafx.h"
#include "Server.h"
#include "UserAppSynchronization.h"

#include "Registry.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUserAppSynchronization::CUserAppSynchronization()
{
	CRegistry reg;

	m_abort =
	m_transferring = FALSE;

	if (!sock.Create())
	{
		ReportSocketError(__LINE__);
	}
	else if (!sock.Connect((LPCTSTR)(reg.GetString(_T("AppServidor"))), (UINT)(reg.GetDWord(_T("AppPorta")))))
	{
		ReportSocketError(__LINE__);
	}
}

CUserAppSynchronization::~CUserAppSynchronization()
{
	if (!sock.ShutDown())
	{
		ReportSocketError(__LINE__);
	}
	sock.Close();
}

CString CUserAppSynchronization::GetRow()
{
	while (m_listReadLines.IsEmpty() && !m_abort)
	{
		char cInBuf[1024];
		int nCharsRead = sock.Receive((void *)&cInBuf, sizeof cInBuf);

		if (nCharsRead > 0)
		{
			for (int i = 0; i < nCharsRead; i++)
			{
				char c = cInBuf[i];

				if (isprint(c))
				{
					m_strCurrentLine += c;
				}
				else if (c == '\012') // Ugly, but works
				{
					if (m_transferring)
					{
						m_listReadLines.AddTail(m_strCurrentLine);
					}
					else if (m_strCurrentLine == ">>")
					{
						m_transferring = TRUE;
					}
					m_strCurrentLine.Empty();
				}
			}
		}
		else // socket closed
		{
			if (nCharsRead == SOCKET_ERROR)
				{
					ReportSocketError(__LINE__);
				}
			CString s = "/*";
			m_listReadLines.AddTail(s);
		}
	}

	return m_listReadLines.RemoveHead();
}

void CUserAppSynchronization::DoIt()
{
	SendRequest();
	while (Process(GetRow()));
}

BOOL CUserAppSynchronization::HasErrors()
{
    return !listErros.IsEmpty();
}

CString CUserAppSynchronization::GetErrorMessage()
{
    return listErros.RemoveHead();
}

void CUserAppSynchronization::AddError(CString strError)
{
	listErros.AddTail(strError);
}

void CUserAppSynchronization::ReportSocketError(int nLine)
{
	CString errmsg;

	errmsg.Format(_T("Synchronization got a socket error #%d in line %d"), sock.GetLastError(), nLine);

	AfxMessageBox(errmsg, MB_ICONERROR);

	m_abort = TRUE;
}
