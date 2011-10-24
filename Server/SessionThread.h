// SessionThread.h : header file
//
// $Archive: /QuickSell/Server/SessionThread.h $
// $Author: Flávio $
// $Date: 25/09/98 10:45 $
/* $History: SessionThread.h $
 * 
 * *****************  Version 7  *****************
 * User: Flávio       Date: 25/09/98   Time: 10:45
 * Updated in $/QuickSell/Server
 * Re-gravado com data de check-in reduzida para o dia 25/09 (Para
 * corrigir uma mudança de data indevida no sistema)
 * 
 * *****************  Version 6  *****************
 * User: Flávio       Date: 24/10/98   Time: 17:54
 * Updated in $/QuickSell/Server
 * Incluídos controles de erros
 * Variáveis críticas registradas como voláteis (volatile)
 * 
 * *****************  Version 5  *****************
 * User: Flávio       Date: 15/09/98   Time: 12:35
 * Updated in $/QuickSell/Server
 * Pedidos não mais registrados no servidor SQL, armazenados agora em
 * memória para agilizar o processamento.
 * Simplificado o processo de localização de clientes alterados via
 * timestamp.
 * Removido suporte a gravação de pedidos.
 * Incluídas classes para registro temporário de pedidos na memória.
 * 
 * *****************  Version 4  *****************
 * User: Flávio       Date: 7/04/98    Time: 6:10p
 * Updated in $/QuickSell/Server
 * Colocado em source control
 */

#if !defined(AFX_SESSIONTHREAD_H__7A769248_6B30_11D1_9F7C_204C4F4F5020__INCLUDED_)
#define AFX_SESSIONTHREAD_H__7A769248_6B30_11D1_9F7C_204C4F4F5020__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Pedido.h"

/////////////////////////////////////////////////////////////////////////////
// CSessionThread thread

class CSessionThread // : public CWinThread
{

// Attributes
public:
	SOCKET m_socket;
	SOCKADDR_IN m_addr;
	volatile BOOL m_open;
// Statistics
	volatile DWORD	m_bytes_received;
	volatile DWORD	m_bytes_sent;
	CList<CString, CString&>
		m_events_received,
		m_events_sent;
	CCriticalSection
		m_ReceivedEventsGateKeeper,
		m_SentEventsGateKeeper;

protected:
	int m_slot;
	volatile BOOL m_logged;
	BOOL m_version;
	volatile BOOL m_stop; // General panic exit flag
	volatile WORD m_vendedor;
	volatile WORD m_tabela; // Tabela de preços associada ao vendedor
	CPedido *m_Pedido;
    CTime m_ultima_sessao_do_vendedor;
	CTime m_inicio_sessao;
	char *m_input_buffer; // Where the packet fragments will be placed
	int m_input_buffer_offset; // Where to put the next bytes
	CCriticalSection
		m_TasksPendingAccess, 
		m_AcknowledgementsPendingAccess,
		m_SendQueueAccess,
		m_ImmediateSendAccess,
		m_SenderGateKeeper,
		m_ReceiverGateKeeper,
		m_DispatcherGateKeeper,
		m_SessionCloserGateKeeper;
	CList<struct packet_s, struct packet_s &>
		m_TasksPending, // Pedidos do HPC ainda nao atendidos
		m_AcknowledgementsPending, // Solicitacoes do Server ainda nao confirmadas
		m_SendQueue; // The outbound queue itself
	volatile int m_sender_thread_instances;
	volatile int m_receiver_thread_instances;
	volatile int m_dispatcher_thread_instances;
	volatile unsigned long m_sent_packets, m_received_packets;

// Operations
public:
	CSessionThread(int slot);
	~CSessionThread();
	void Open(void);
	void Close(void);

protected:
	void SendABORTACK(void);
	void ForceClose(void);
	void CloseSession(void);
	void SendABORT(void);
	void SendEOJ();
	void EnqueueTask(struct packet_s& packet);
	void EmptyAllLists(void);
	void EnqueueMessage(struct packet_s& packet);
	void DispatchTask(struct packet_s& packet);
	void TriggerDispatcherThread(void);
	void TriggerReceiverThread(void);
	void TriggerSenderThread(void);
	int Receive(struct packet_s& packet);
	int Send(struct packet_s& packet);
	int BufferLength(struct packet_s& buf);
	void ClearBuffer(struct packet_s& buf);
	void DispatcherRun(void);
	void SetupRun(void);
	void ReceiverRun(void);
	void SenderRun(void);

// Implementation
public:
	friend UINT SessionSetupThreadStart(LPVOID pParam);
	friend UINT SessionReceiverThreadStart(LPVOID pParam);
	friend UINT SessionSenderThreadStart(LPVOID pParam);
	friend UINT SessionDispatcherThreadStart(LPVOID pParam);
	friend UINT CloserThreadStart(LPVOID pParam);

private:
	void ReportSocketError(int nWhere);
	void AtualizarProdutos(void);
};

#endif // !defined(AFX_SESSIONTHREAD_H__7A769248_6B30_11D1_9F7C_204C4F4F5020__INCLUDED_)
