// ConnectionThread.cpp : implementation file
// 
// $Archive: /PalmTrader 1/Server/ConnectionThread.cpp $
// $Author: Fl�vio $
// $Date: 25/05/99 15:31 $
/* $History: ConnectionThread.cpp $
 * 
 * *****************  Version 8  *****************
 * User: Fl�vio       Date: 25/05/99   Time: 15:31
 * Updated in $/PalmTrader 1/Server
 * Altera��es feitas para o release 1.30
 * Inclu�da rotina gen�rica para convers�o de n�meros em strings
 * Corrigido bug na defini��o do tamanho do buffer de envio de pacotes TCP
 * nos m�dulos de sincroniza��o
 * Separada a porta TCP de conex�o com os clientes e servidores
 * Inclu�do m�todo em CPedido para retornar a data do pedido como DWORD,
 * que � usada no m�dulo de sincroniza��o de pedidos
 * Implementados novos atributos em pre�os
 * Inclu�do o script de cria��o da base SQL
 * 
 * *****************  Version 7  *****************
 * User: Fl�vio       Date: 25/09/98   Time: 10:45
 * Updated in $/QuickSell/Server
 * Re-gravado com data de check-in reduzida para o dia 25/09 (Para
 * corrigir uma mudan�a de data indevida no sistema)
 * 
 * *****************  Version 6  *****************
 * User: Fl�vio       Date: 24/10/98   Time: 17:53
 * Updated in $/QuickSell/Server
 * Inclu�dos controles de erros
 * 
 * *****************  Version 5  *****************
 * User: Fl�vio       Date: 3/31/98    Time: 11:44a
 * Updated in $/QuickSell/Server
 * Altera��o, possivelmente final, na estrutura dos coment�rios contendo
 * macros do Visual SourceSafe
 * 
 * *****************  Version 4  *****************
 * User: Fl�vio       Date: 3/31/98    Time: 11:42a
 * Updated in $/QuickSell/Server
 * Verificando expans�o de macros do SourceSafe
 */

#include "stdafx.h"
#include "afxmt.h"
#include "afxtempl.h"
#include "winsock.h"
#include "Protocol.h"
#include "Registry.h"

#include "Server.h"
#include "ConnectionThread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static UINT ConnectionThreadStart(LPVOID pParam)
{
	((CConnectionThread *)pParam)->Run();

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CConnectionThread

CConnectionThread::CConnectionThread()
{
	m_suspend = FALSE;
	m_cancel = FALSE;
	m_hWnd_available = FALSE;
	for (int i = 0; i < MAX_CONNECTIONS; i++)
	{
		TRY
		{
			m_connections[i].Session = new CSessionThread(i);
		}
		CATCH_ALL(e)
		{
			e->ReportError();
		}
		END_CATCH_ALL
	}
}

CConnectionThread::~CConnectionThread()
{
	for (int i = 0; i < MAX_CONNECTIONS; i++)
	{
		delete m_connections[i].Session;
	}
}

void CConnectionThread::Start(void)
{
	m_thread = AfxBeginThread(ConnectionThreadStart, this);
}

void CConnectionThread::Run(void)
{
	u_short usPorta;

	{
	CRegistry reg;
	usPorta = (u_short)reg.GetDWord(_T("Porta"), 47375);
	}

	{
		WSADATA wsadata;
		
		int nRc = WSAStartup(0x0101, &wsadata);
		if (nRc)
		{
			ReportSocketError(__LINE__);
			return;
		}
	}
	m_s = socket(AF_INET, SOCK_STREAM, 0);
	if (m_s == INVALID_SOCKET)
	{
		ReportSocketError(__LINE__);
		return;
	}
	m_addr.sin_family = AF_INET;
	m_addr.sin_port = htons(usPorta);
	m_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(m_s, (LPSOCKADDR)&m_addr, sizeof(m_addr)) == SOCKET_ERROR)
	{
		ReportSocketError(__LINE__);
		return;
	}
	else
	{
		if (listen(m_s, 5) == SOCKET_ERROR)
		{
			ReportSocketError(__LINE__);
			return;
		}

		while (1)
		{
			int slot = 0, addrlen = sizeof SOCKADDR;
			
			for (; m_connections[slot].Session->m_open && slot < MAX_CONNECTIONS; slot++);
			if (slot == MAX_CONNECTIONS) // No free slots
			{
				AfxMessageBox(_T("Limite de conex�es atingido!"), MB_ICONEXCLAMATION);
				Sleep(1000L); // One second delay
				continue; // Try again
			}

			m_connections[slot].Session->m_socket = 
				accept(m_s, 
					(SOCKADDR *)&m_connections[slot].Session->m_addr, 
					&addrlen);

			if (m_connections[slot].Session->m_socket == INVALID_SOCKET)
			{
				ReportSocketError(__LINE__);
				continue;
			}
			else
			{
				m_connections[slot].Session->Open();
			}
		}
	}
}

void CConnectionThread::ReportSocketError(int nLine)
{
	CString errmsg;

	errmsg.Format(_T("ConnectionThread got a socket error #%d in line %d"), WSAGetLastError(), nLine);

	AfxMessageBox(errmsg, MB_ICONERROR);
}
