// SessionThread.h: interface for the CSessionThread class.
//
//////////////////////////////////////////////////////////////////////
// $Archive: /PalmTrader 1/QSTransfer/SessionThread.h $
// $Author: Flávio $
// $Date: 25/09/98 17:35 $
/* $History: SessionThread.h $
 * 
 * *****************  Version 7  *****************
 * User: Flávio       Date: 25/09/98   Time: 17:35
 * Updated in $/PalmTrader 1/QSTransfer
 * Bases de pedidos, itens e blocos movidos para bases WCE
 * 
 * *****************  Version 6  *****************
 * User: Flávio       Date: 4/08/98    Time: 11:31
 * Updated in $/PalmTrader 1/QSTransfer
 * Corrigidos comentários de versão
 * 
 * *****************  Version 5  *****************
 * User: Flávio       Date: 4/08/98    Time: 11:16
 * Updated in $/PalmTrader 1/QSTransfer
 * Mudada forma de armazenamento das variáveis compartilhadas entre threads para modo volatile.
 *
 * *****************  Version 4  *****************
 * User: Flávio       Date: 24/07/98   Time: 18:03
 * Updated in $/PalmTrader 1/QSTransfer
 * Implementada solicitação automática de bloco quando não houver bloco
 * reserva
 * 
 * *****************  Version 3  *****************
 * User: Flávio       Date: 10/07/98   Time: 22:47
 * Updated in $/PalmTrader 1/QSTransfer
 * Implementado suporte a reenvio de pedidos;
 * Implementada transferência de títulos
 * 
 * *****************  Version 2  *****************
 * User: Flávio       Date: 4/02/98    Time: 1:00a
 * Updated in $/QuickSell/QSTransfer
 * Incluídos comentários com keywords SS
 * Alterada a forma de acesso aos arquivos de pedidos e itens
 * Incluído tratamento de corte automático
 */

#if !defined(AFX_SESSIONTHREAD_H__9B872CAE_6CB0_11D1_9F82_204C4F4F5020__INCLUDED_)
#define AFX_SESSIONTHREAD_H__9B872CAE_6CB0_11D1_9F82_204C4F4F5020__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "afxmt.h"
#include "afxtempl.h"
#include "Winsock.h"
#include "Protocol.h"
#include "DBPedidos.h"
#include "DBItens.h"

#define EVENT_SENT		0x1
#define EVENT_RECEIVED	0x2

#define RECEIVE_BUFFER_SIZE (sizeof(struct packet_s)*3)

class CSessionThread  
{

// Attributes
public:
	BOOL	m_ask_cobranca;
	BOOL	m_ask_planos;
	BOOL	m_ask_refill_clientes;
	BOOL	m_ask_refill_produtos;
	BOOL	m_ask_refill_titulos;
	BOOL	m_ask_bloco;
	BOOL	m_snd_pedidos;
	BOOL	m_snd_clientes;
// Statistics
	volatile DWORD	m_bytes_received;
	volatile DWORD	m_bytes_sent;
	CList<CString, CString&>
		m_events_received,
		m_events_sent;
	CCriticalSection
		m_ReceivedEventsGateKeeper,
		m_SentEventsGateKeeper;
	CTime m_timeSessionStart,
		m_timeSessionEnd;

protected:
	// Databases
	CQSProdutos pd;
	CQSClientes cl;
	CDBPedidos	dbPedidos;
	CDBItens	dbItens;
	// Thread control
	volatile int m_sender_thread_instances;
	volatile int m_receiver_thread_instances;
	volatile int m_dispatcher_thread_instances;
	LONG m_generic_outbound_record_counter; // To help count outbound records
	LONG m_generic_inbound_record_counter; // as above to inbound records
	volatile BOOL m_open;
	SOCKET m_socket;
	volatile BOOL m_stop; // General panic exit flag
	char *m_input_buffer; // A buffer for receiving packet fragments
	int m_input_buffer_offset; // Where the next byte will be placed
	CWinThread 
		*m_SessionThread,
		*m_SenderThread, 
		*m_ReceiverThread,
		*m_DispatcherThread;
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

private:
	int m_last_sent_message;
	int m_last_received_message;
	unsigned long m_sent_packets, m_received_packets;

// Operations
public:
	CSessionThread();
	virtual ~CSessionThread();

// Implementation
public:
	BOOL IsOpen(void);
	BOOL Open(void);
	void Close(void);
	friend UINT SessionThreadStart(LPVOID pParam);
	friend UINT ReceiverThreadStart(LPVOID pParam);
	friend UINT SenderThreadStart(LPVOID pParam);
	friend UINT DispatcherThreadStart(LPVOID pParam);
	friend UINT CloserThreadStart(LPVOID pParam);

protected:
	void ReportSocketError(int nWhere);
	void SendABORTACK();
	void SendEOJ(void);
	void SendABORT(void);
	void ForceClose(void);
	void CloseSession(void);
	void AddEvent(int nType, WORD nCode, TCHAR *msg, LONG lValue1 = 0, LONG lValue2 = 0, LONG lValue3 = 0);
	void EnqueueTask(struct packet_s& packet);
	void EmptyAllLists(void);
	void EnqueueMessage(struct packet_s& packet);
	void DispatchTask(struct packet_s& packet);
	void TriggerDispatcherThread(void);
	void TriggerReceiverThread(void);
	void TriggerSenderThread(void);
	void TriggerCloserThread(void);
	int Receive(struct packet_s& packet);
	int Send(struct packet_s& packet);
	int BufferLength(struct packet_s& buf);
	void ClearBuffer(struct packet_s& buf);
	void DispatcherRun(void);
	void SessionRun(void);
	void ReceiverRun(void);
	void SenderRun(void);
};

#endif // !defined(AFX_SESSIONTHREAD_H__9B872CAE_6CB0_11D1_9F82_204C4F4F5020__INCLUDED_)
