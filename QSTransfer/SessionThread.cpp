// SessionThread.cpp: implementation of the CSessionThread class.
//
//////////////////////////////////////////////////////////////////////
// $Archive: /PalmTrader 1/QSTransfer/SessionThread.cpp $
// $Author: Flávio $
// $Date: 25/05/99 15:34 $
/* $History: SessionThread.cpp $
 * 
 * *****************  Version 17  *****************
 * User: Flávio       Date: 25/05/99   Time: 15:34
 * Updated in $/PalmTrader 1/QSTransfer
 * Implementados novos atributos para produto
 * 
 * *****************  Version 16  *****************
 * User: Flávio       Date: 25/09/98   Time: 18:28
 * Updated in $/PalmTrader 1/QSTransfer
 * Implementado maior controle de erros
 * 
 * *****************  Version 15  *****************
 * User: Flávio       Date: 25/09/98   Time: 17:35
 * Updated in $/PalmTrader 1/QSTransfer
 * Bases de pedidos, itens e blocos movidos para bases WCE
 * 
 * *****************  Version 14  *****************
 * User: Flávio       Date: 24/07/98   Time: 18:03
 * Updated in $/PalmTrader 1/QSTransfer
 * Implementada solicitação automática de bloco quando não houver bloco
 * reserva
 * 
 * *****************  Version 13  *****************
 * User: Flávio       Date: 21/07/98   Time: 17:32
 * Updated in $/PalmTrader 1/QSTransfer
 * Incluído suporte básico à atualização automática
 * 
 * *****************  Version 12  *****************
 * User: Flávio       Date: 12/07/98   Time: 10:34
 * Updated in $/PalmTrader 1/QSTransfer
 * Implementada atualização automática do saldo do cliente na transmissão
 * do pedido.
 * 
 * *****************  Version 11  *****************
 * User: Flávio       Date: 10/07/98   Time: 22:47
 * Updated in $/PalmTrader 1/QSTransfer
 * Implementado suporte a reenvio de pedidos;
 * Implementada transferência de títulos
 * 
 * *****************  Version 10  *****************
 * User: Flávio       Date: 7/07/98    Time: 10:35a
 * Updated in $/QuickSell/QSTransfer
 * Os pedidos enviados não são mais automaticamente marcados como enviados
 * - é necessário implementar o processo de confirmação de recepção pelo
 * server.
 * A recepção de produtos inclui agora mais campos (embalagem, unidade,
 * número de itens na embalagem etc)
 * 
 * *****************  Version 9  *****************
 * User: Flávio       Date: 4/22/98    Time: 1:54a
 * Updated in $/QuickSell/QSTransfer
 * Adaptado código para utilizar índices no arquivo de produtos. Incluíndo
 * o pedido para reindexação
 * 
 * *****************  Version 8  *****************
 * User: Flávio       Date: 4/14/98    Time: 10:10a
 * Updated in $/QuickSell/QSTransfer
 * Incluído suporte a retenção de pedido
 * 
 * *****************  Version 7  *****************
 * User: Flávio       Date: 4/06/98    Time: 11:08a
 * Updated in $/QuickSell/QSTransfer
 * Incluído suporte a recepção de mensagens informativas
 * 
 * *****************  Version 6  *****************
 * User: Flávio       Date: 4/02/98    Time: 12:56a
 * Updated in $/QuickSell/QSTransfer
 * Incluídos comentários com keywords SS
 * Alterada a forma de acesso aos arquivos de pedidos e itens
 * Incluído tratamento de corte automático
 */

#include "stdafx.h"
#include "winbase.h"

#include "QSTools.h"

#include "QSDatabase.h"

#include "DBBlocos.h"
#include "DBPedidos.h"
#include "DBItens.h"

#include "QSTransfer.h"
#include "SessionThread.h"
#include "PedidosRegistry.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define XOUMSG(MSG) { CString x; x.Format(_T("%d - ") MSG, __LINE__); AddEvent(EVENT_SENT, 0, x); }
#define new DEBUG_NEW
#else
#define XOUMSG(MSG) /* Don't mind */
#endif

//////////////////////////////////////////////////////////////////////
// Friend functions
//////////////////////////////////////////////////////////////////////

static UINT SessionThreadStart(LPVOID pParam)
{
	((CSessionThread *)pParam)->SessionRun();

	return 0;
}

static UINT ReceiverThreadStart(LPVOID pParam)
{
	((CSessionThread *)pParam)->ReceiverRun();

	return 0;
}

static UINT SenderThreadStart(LPVOID pParam)
{
	((CSessionThread *)pParam)->SenderRun();

	return 0;
}

static UINT DispatcherThreadStart(LPVOID pParam)
{
	((CSessionThread *)pParam)->DispatcherRun();

	return 0;
}

static UINT CloserThreadStart(LPVOID pParam)
{
	((CSessionThread *)pParam)->ForceClose();

	return 0;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSessionThread::CSessionThread()
{
	m_stop = FALSE;

	TRY
	{
		m_input_buffer = new char[RECEIVE_BUFFER_SIZE];
	}
	CATCH_ALL(e)
	{
		e->ReportError();
	}
	END_CATCH_ALL;
	m_input_buffer_offset = 0;
}

CSessionThread::~CSessionThread()
{
	delete m_input_buffer;
}

//////////////////////////////////////////////////////////////////////
// Member functions
//////////////////////////////////////////////////////////////////////

BOOL CSessionThread::Open(void)
{
	m_sent_packets = m_received_packets = 0;
	m_bytes_received = m_bytes_sent = 0;

	m_sender_thread_instances =
	m_receiver_thread_instances =
	m_dispatcher_thread_instances = 0;

	m_ReceivedEventsGateKeeper.Lock();
		m_events_received.RemoveAll();
	m_ReceivedEventsGateKeeper.Unlock();
	
	m_SentEventsGateKeeper.Lock();
		m_events_sent.RemoveAll();
	m_SentEventsGateKeeper.Unlock();

	EmptyAllLists();

	{
		WSADATA wsadata;
		
		int nRc = WSAStartup(0x0101, &wsadata);
		if (nRc)
		{
			ReportSocketError(__LINE__);
			return FALSE;
		}
	}
	sockaddr_in addr;
	m_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_socket == INVALID_SOCKET)
	{
		ReportSocketError(__LINE__);
		return FALSE;
	}
	addr.sin_family = AF_INET;
	addr.sin_port = 0;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(m_socket, (LPSOCKADDR)&addr, sizeof(addr)) == SOCKET_ERROR)
	{
		ReportSocketError(__LINE__);
		CloseSession();
		return FALSE;
	}
	else
	{
		sockaddr_in saddr;
		CPedidosRegistry Reg;
		
		saddr.sin_family = AF_INET;
		saddr.sin_port = htons((unsigned short)Reg.GetDWord(_T("Porta")));
		{
			char sz[32];
			saddr.sin_addr.s_addr = 
				inet_addr(CString2sz(sz, Reg.GetString(_T("Servidor"))));
		}
		if (connect(m_socket, (LPSOCKADDR)&saddr, sizeof(saddr)) == SOCKET_ERROR)
		{
			ReportSocketError(__LINE__);
			CloseSession();
			return FALSE;
		}
		else
		{
			struct packet_s in_pkt, out_pkt;

			m_timeSessionStart = CTime::GetCurrentTime();

			// Aguarda solicitacao de versao
			do
			{
				if (!Receive(in_pkt)) return FALSE;
			}
			while (ntohs(in_pkt.header.type) != PKT_ASK_VERSION && !m_stop);

			// Envia versao
			ClearBuffer(out_pkt);
			out_pkt.header.type = htons(PKT_SND_VERSION);
			out_pkt.version.number = htons(PROTOCOL_VERSION);
			if (!Send(out_pkt))
			{
				CloseSession();
				return FALSE;
			}

			// Aguarda solicitacao de logon
			if (!Receive(in_pkt)) return FALSE;
			if (ntohs(in_pkt.header.type) != PKT_ASK_LOGON)
			{
				AddEvent(EVENT_RECEIVED, 0, _T("Falha de protocolo"));
				CloseSession();
				return FALSE;
			}

			// Envia logon
			ClearBuffer(out_pkt);
			out_pkt.header.type = htons(PKT_SND_LOGON);
			out_pkt.logon.codigo_vendedor = htons((WORD)Reg.GetDWord(_T("VendedorCodigo")));
			CString2sz(out_pkt.logon.senha, Reg.GetString(_T("VendedorSenha")));

			if (!Send(out_pkt))
			{
				CloseSession();
				return FALSE;
			}

			// Aguarda confirmacao da senha
			if (!Receive(in_pkt))
			{
				CloseSession();
				return FALSE;
			}
			if (ntohs(in_pkt.header.type) != PKT_ACK_LOGON)
			{
				AddEvent(EVENT_RECEIVED, 0, _T("Erro: Código ou senha inválidos!"));
				CloseSession();
				return FALSE;
			}

			// Debug sequence
			/*
			for (int i = 0; i < 10; i++)
			{
				ClearBuffer(out_pkt);
				strcpy(out_pkt.cliente.endereco_cobranca.cep, "98765-432");
				out_pkt.header.type = htons(PKT_ACK_VERSION);
				Send(out_pkt);
			}
			*/

			m_open = TRUE;

			m_SessionThread = AfxBeginThread(SessionThreadStart, this);

			AddEvent(EVENT_SENT|EVENT_RECEIVED, 0, _T("Sessão iniciada!"));
		}
	}

	return  TRUE;
}

void CSessionThread::Close()
{
	if (!m_stop)
	{
		TriggerCloserThread();
		AddEvent(EVENT_RECEIVED, 0, _T("Encerrando sessão..."));
	}
}

void CSessionThread::ForceClose()
{
	m_stop = TRUE;

	SendABORT();

	EmptyAllLists();

	CloseSession();
}

void CSessionThread::CloseSession()
{
	CSingleLock Closing(&m_SessionCloserGateKeeper, TRUE);

	AddEvent(EVENT_SENT, 0, _T("Encerrando fila de saída"));
	CSingleLock LockSender(&m_SenderGateKeeper, TRUE);

	AddEvent(EVENT_SENT, 0, _T("Encerrando processador de pedidos"));
	CSingleLock LockDispatcher(&m_DispatcherGateKeeper, TRUE);

	EmptyAllLists();

	if (m_open)
	{
		m_open = FALSE;
		if (closesocket(m_socket) == SOCKET_ERROR) // Any doubt dbItens will be closed?
		{
			ReportSocketError(__LINE__);
		}
		AddEvent(EVENT_SENT|EVENT_RECEIVED, 0, _T("Sessão encerrada!"));
		m_timeSessionEnd = CTime::GetCurrentTime();
	}
}



void CSessionThread::SessionRun()
{
	struct packet_s out_pkt;

	ClearBuffer(out_pkt);

	if (m_ask_cobranca)
	{
		out_pkt.header.type = htons(PKT_ASK_REFILL_COBRANCA);
		EnqueueMessage(out_pkt);
	}
	
	if (m_ask_planos)
	{
		out_pkt.header.type = htons(PKT_ASK_REFILL_PLANOS);
		EnqueueMessage(out_pkt);
	}

	CDBBlocos dbBlocos;
	if (m_ask_bloco || !dbBlocos.HaveBlocosReserva())
	{
		out_pkt.header.type = htons(PKT_ASK_BLOCO);
		EnqueueMessage(out_pkt);
	}
	
	if (m_ask_refill_clientes)
	{
		out_pkt.header.type = htons(PKT_ASK_REFILL_CLIENTES);
		EnqueueMessage(out_pkt);
	}
	else
	{
		out_pkt.header.type = htons(PKT_ASK_NOVOS_CLIENTES);
		EnqueueMessage(out_pkt);
	}

	if (m_ask_refill_produtos)
	{
		out_pkt.header.type = htons(PKT_ASK_REFILL_PRODUTOS);
		EnqueueMessage(out_pkt);
	}
	else
	{
		out_pkt.header.type = htons(PKT_ASK_NOVOS_PRODUTOS);
		EnqueueMessage(out_pkt);

		out_pkt.header.type = htons(PKT_ASK_NOVOS_PRECOS);
		EnqueueMessage(out_pkt);

		out_pkt.header.type = htons(PKT_ASK_NOVOS_SALDOS);
		EnqueueMessage(out_pkt);
	}
	
	if (m_ask_refill_titulos)
	{
		out_pkt.header.type = htons(PKT_ASK_REFILL_TITULOS);
		EnqueueMessage(out_pkt);
	}
	else
	{
		out_pkt.header.type = htons(PKT_ASK_NOVOS_TITULOS);
		EnqueueMessage(out_pkt);
	}

	//Solicitações locais
	if (m_snd_pedidos)
	{
		out_pkt.header.type = htons(PKT_SND_PEDIDO);
		EnqueueTask(out_pkt);
	}
	if (m_snd_clientes)
	{
		/*
		out_pkt.header.type = htons(PKT_SND_NOVO_CLIENTE);
		EnqueueTask(out_pkt);
		out_pkt.header.type = htons(PKT_SND_ATUALIZA_CLIENTE);
		EnqueueTask(out_pkt);
		*/
	}

	//Fim das solicitações
	out_pkt.header.type = htons(PKT_EOQ);
	EnqueueMessage(out_pkt);

	TriggerDispatcherThread();
	TriggerReceiverThread();
}

void CSessionThread::ReceiverRun(void)
{
	struct packet_s in_pkt;

	if (m_stop||!m_open) { CloseSession(); return; }

	++m_receiver_thread_instances;

	CSingleLock GateKeeper(&m_ReceiverGateKeeper, TRUE);

	//AddEvent(EVENT_SENT, 0, _T("Fila de entrada ativada"));

	while (TRUE)
	{
		if (m_stop||!m_open) break;

		int retcode = Receive(in_pkt);
		if (!retcode)
		{
			if (!m_stop) ForceClose();
			break;
		}
		WORD wType = ntohs(in_pkt.header.type);

		/////////// DEBUG STUFF
		/*
		{
			static WORD wPreviousType = 0;
			if (wPreviousType != wType)
			{
				wPreviousType = wType;
				AddEvent(EVENT_RECEIVED, 0, _T("[0x%04lx] Received"), (LONG)wType);
			}
		}
		*/

		if (wType == PKT_ABORT)
		{
			AddEvent(EVENT_RECEIVED, 0, _T("Sessão encerrada pelo servidor"));
			SendABORTACK();
			ForceClose();
			break;
		}
		else if (wType == PKT_ABORT_ACK)
		{
			AddEvent(EVENT_RECEIVED, 0, _T("Fim de sessão confirmado"));
			ForceClose();
			break;
		}
		else if (wType == PKT_EOJ)
		{
			AddEvent(EVENT_RECEIVED, 0, _T("Fim da recepção"));
			EnqueueTask(in_pkt);
			break;
		}
		else if (wType == PKT_EOJ_ACK)
		{
			AddEvent(EVENT_RECEIVED, 0, _T("Fim da transmissão confirmado"));
			CloseSession();
			break;
		}
		else
		{
			EnqueueTask(in_pkt);
		}
	}

	--m_receiver_thread_instances;
}

void CSessionThread::SenderRun(void)
{
	if (m_stop||!m_open) { CloseSession(); return; }

	++m_sender_thread_instances;

	CSingleLock
		GateKeeper(&m_SenderGateKeeper, TRUE),
		ToDo(&m_SendQueueAccess, TRUE);

	//AddEvent(EVENT_SENT, 0, _T("Fila de saida ativada"));

	while (!m_SendQueue.IsEmpty())
	{
		struct packet_s out_pkt;

		out_pkt = m_SendQueue.RemoveHead();
		ToDo.Unlock();
		//AddEvent(EVENT_SENT, 0, _T("[0x%x] Enviado"), ntohl(out_pkt.header.type));
		Send(out_pkt);
		ToDo.Lock();
	}

	--m_sender_thread_instances;
}

void CSessionThread::DispatcherRun()
{
	if (m_stop||!m_open) { CloseSession(); return; }

	++m_dispatcher_thread_instances;

	CSingleLock
		GateKeeper(&m_DispatcherGateKeeper, TRUE),
		ToDo(&m_TasksPendingAccess, TRUE);

	//AddEvent(EVENT_SENT, 0, _T("Processador de pedidos ativado"));

	while (!m_TasksPending.IsEmpty())
	{
		struct packet_s packet;
		packet = m_TasksPending.RemoveHead();
		ToDo.Unlock();
		DispatchTask(packet);
		ToDo.Lock();
	}

	--m_dispatcher_thread_instances;
}

void CSessionThread::TriggerCloserThread(void)
{
	m_SenderThread = AfxBeginThread(CloserThreadStart, this);
}

void CSessionThread::TriggerSenderThread(void)
{
	if (!m_sender_thread_instances)
		m_SenderThread = AfxBeginThread(SenderThreadStart, this);
}

void CSessionThread::TriggerReceiverThread(void)
{
	if (!m_receiver_thread_instances)
		m_ReceiverThread = AfxBeginThread(ReceiverThreadStart, this);
}

void CSessionThread::TriggerDispatcherThread()
{
	if (!m_dispatcher_thread_instances)
		m_DispatcherThread = AfxBeginThread(DispatcherThreadStart, this);
}

void CSessionThread::ClearBuffer(struct packet_s& buf)
{
	memset(&buf, 0x0, sizeof buf);
}

int CSessionThread::BufferLength(struct packet_s& buf)
{
	int Length = sizeof (struct packet_s);

	while (((BYTE *)&buf)[--Length] == 0);

	return ++Length; // The position is 0 based, right?
}

int CSessionThread::Send(struct packet_s& out_pkt)
{
	CSingleLock GateKeeper(&m_ImmediateSendAccess, TRUE);
	int retcode, len;

	len = BufferLength(out_pkt);
	if (len < sizeof(out_pkt.header))
		len = sizeof(out_pkt.header);

	out_pkt.header.magic = htonl(PKT_MAGIC_NUMBER);
	out_pkt.header.size = htons(len);
	out_pkt.header.sequence = htonl(++m_sent_packets);

	retcode = send(m_socket, (LPSTR)&out_pkt, len, 0);

	m_bytes_sent += len;

	if (retcode == SOCKET_ERROR)
	{
		retcode = 0;

		if (WSAGetLastError() == WSAECONNRESET) // Conexão abortada
		{
			m_stop = TRUE;
		}
		else
		{
			ReportSocketError(__LINE__);
		}
	}

	return retcode;
}

int CSessionThread::Receive(struct packet_s& pkt)
{
	int retcode;
	char *buffer = m_input_buffer;		// Yes, I'm lazy!
	int offset = m_input_buffer_offset;
	struct packet_s *pktx = (struct packet_s *)buffer; // to help debugging

	//AddEvent(EVENT_SENT, 0, _T("Offset = %ld"), (LONG)offset);

	while (offset < ntohs(pktx->header.size) /*- 1*/ || 
		ntohl(pktx->header.magic) != PKT_MAGIC_NUMBER)
	{
		//AddEvent(EVENT_SENT, 0, _T("recv - Offset = %ld"), (LONG)offset);
		retcode = recv(m_socket, buffer+offset, RECEIVE_BUFFER_SIZE - offset/*sizeof pkt*/, 0);
		if (retcode == SOCKET_ERROR)
		{
			retcode = 0;

			if (WSAGetLastError() == WSAECONNRESET) // Conexão abortada
			{
				m_stop = TRUE;
			}
			else
			{
				ReportSocketError(__LINE__);
				return 0;
			}
		}
		else
		{
			offset += retcode;

			while (offset >= sizeof(pkt.header.magic) /*- 1*/)
			{
				if (ntohl(pktx->header.magic) == PKT_MAGIC_NUMBER)
				{
					break;
				}
				else
				{
					char *source = buffer + 1;
					char *target = buffer;
					int move = --offset;
					while (move--) *(target++) = *(source++);
				}
			}
		}
	}

	// AddEvent(EVENT_SENT, 0, _T("recv - Size = %ld"), (LONG)ntohs(pktx->header.size));

	//if (retcode > 0)
	if (offset >= ntohs(pktx->header.size) /*- 1*/)
	{
		int size = ntohs(pktx->header.size);

		ClearBuffer(pkt);
		memcpy(&pkt, buffer, size);
		offset -= size;
		
		// move rest of buffer to its beggining
		if (offset >= 0)
		{
			int residue = offset;
			char *source = buffer + size;
			while (residue--) *(buffer++) = *(source++);
		}
		else
		{
			AddEvent(EVENT_RECEIVED, 0, _T("Offset < 0!!!"));
			offset = 0;
		}
		
		retcode = size;
	}
	
	if (retcode < 0)
	{
		retcode = 0;
	}
	else
	{
		m_bytes_received += retcode;

		if (++m_received_packets != ntohl(pkt.header.sequence))
		{
			AddEvent(EVENT_RECEIVED, 0, _T("ALERTA! RCV=%ld SEQ=%ld"), m_received_packets, ntohl(pkt.header.sequence));
			m_received_packets = ntohl(pkt.header.sequence);
		}
	}

	m_input_buffer_offset = offset; // give dbItens back
	return retcode;
}

void CSessionThread::DispatchTask(struct packet_s& pkt)
{
	switch (ntohs(pkt.header.type))
	{
	case PKT_SND_PEDIDO :
		{
			struct packet_s out_pkt;

			m_generic_outbound_record_counter = 0;
			dbPedidos.MoveFirst();

			while (!dbPedidos.IsEOF())
			{
				dbPedidos.Read();
				if (!dbPedidos.GetReterPedido() && !dbPedidos.GetPedidoEnviado())
				{
					ClearBuffer(out_pkt);
					out_pkt.header.type = htons(PKT_SND_PEDIDO);
					out_pkt.pedido.numero = htonl(dbPedidos.GetNumeroPedido());
					out_pkt.pedido.cliente_codigo = htonl(dbPedidos.GetCodigoCliente());
					out_pkt.pedido.condicao_venda = htons(dbPedidos.GetCondicaoVenda());
					out_pkt.pedido.plano = htons(dbPedidos.GetPlano());
					out_pkt.pedido.data_entrada = htonl(dbPedidos.GetDataPedido());
					CString2sz(out_pkt.pedido.cobranca, dbPedidos.GetCodigoCobranca());

					EnqueueMessage(out_pkt);

					if (dbItens.FindFirstItem(dbPedidos.GetNumeroPedido()))
					{
						do
						{
							dbItens.Read();

							ClearBuffer(out_pkt);
							out_pkt.header.type = htons(PKT_SND_PEDIDO_ITEM);
							out_pkt.pedido_item.pedido = htonl(dbPedidos.GetNumeroPedido());
							out_pkt.pedido_item.produto = htonl(dbItens.GetProduto());
							out_pkt.pedido_item.quantidade = htonl(dbItens.GetQuantidadePedida());
							out_pkt.pedido_item.preco = htonl(dbItens.GetPreco());
							EnqueueMessage(out_pkt);
						}
						while (dbItens.FindNextItem());
					}

					ClearBuffer(out_pkt);
					out_pkt.header.type = htons(PKT_SND_PEDIDO_FIM);
					out_pkt.pedido_fim.pedido = htonl(dbPedidos.GetNumeroPedido());
					EnqueueMessage(out_pkt);

					AddEvent(EVENT_SENT, PKT_SND_PEDIDO, _T("%d pedidos enviados"), ++m_generic_outbound_record_counter);
				}
				dbPedidos.MoveNext();
			}
		}
		break;
    case PKT_SND_PEDIDO_ITEM_CONF :
        {
            DWORD dwPedido      = ntohl(pkt.pedido_item_conf.pedido);
            DWORD dwProduto     = ntohl(pkt.pedido_item_conf.produto);
            DWORD dwQuantidade  = ntohl(pkt.pedido_item_conf.quantidade);

            if (dbItens.FindItem(dwPedido, dwProduto))
            {
				if (pd.FindByCodigo(dwProduto))
				{
					dbItens.Read();
                    dbItens.SetQuantidadeAtendida(dwQuantidade);
					dbItens.Write();
				}
            }
        }
        break;
	case PKT_SND_PEDIDO_STATUS :
		{
            DWORD dwPedido = ntohl(pkt.pedido_status.pedido);

            if (dbPedidos.Find(dwPedido))
            {
                dbPedidos.Read();
				dbPedidos.SetPedidoEnviado(ntohs(pkt.pedido_status.reenviar) == 0);
				dbPedidos.SetDiagnostico(pkt.pedido_status.diagnostico);
				dbPedidos.Write();

				if (cl.FindByCodigo(dbPedidos.GetCodigoCliente()))
				{
					WORD wRecord = cl.GetRecordNumber();
					cl.m_record.valor_disponivel = ntohl(pkt.pedido_status.novo_saldo_cliente);
					cl.SetRecord(wRecord);
					cl.WriteRecord();
				}
				AddEvent(EVENT_RECEIVED, 0, _T("Pedido %ld processado"), dwPedido);
            }
        }
		break;
	case PKT_ASK_CLEAR_TITULOS :
		{
			CQSTitulos ti;

			ti.Reset();

			AddEvent(EVENT_RECEIVED, 0, _T("Títulos apagados"));

			m_generic_inbound_record_counter = 0;
		}
		break;
	case PKT_SND_TITULO :
		{
			CQSTitulos ti;

			ti.ClearBuffer();
			strcpy(ti.m_record.emissao, pkt.titulo.emissao);
			strcpy(ti.m_record.vencimento, pkt.titulo.vencimento);
			strcpy(ti.m_record.numero, pkt.titulo.numero);
			ti.m_record.cliente = ntohl(pkt.titulo.cliente);
			ti.m_record.valor = ntohl(pkt.titulo.valor);
			ti.AddRecord();
			AddEvent(EVENT_RECEIVED, PKT_SND_TITULO, _T("%ld titulos recebidos"), ++m_generic_inbound_record_counter);
		}
		break;
	case PKT_ASK_CLEAR_COBRANCA :
		{
			CQSCobranca cb;

			cb.Reset();

			AddEvent(EVENT_RECEIVED, 0, _T("Códigos de cobrança apagados"));

			m_generic_inbound_record_counter = 0;
		}
		break;
	case PKT_SND_COBRANCA :
		{
			CQSCobranca cb;

			cb.ClearBuffer();
			strcpy(cb.m_record.codigo, pkt.cobranca.codigo);
			strcpy(cb.m_record.descricao, pkt.cobranca.descricao);
			cb.AddRecord();
			AddEvent(EVENT_RECEIVED, PKT_SND_COBRANCA, _T("%ld codigos de cobranca recebidos"), ++m_generic_inbound_record_counter);
		}
		break;
	case PKT_ASK_CLEAR_COND_VENDA :
		/*
		{
			CQSCondicoesVenda cv;

			cv.Reset();

			AddEvent(EVENT_RECEIVED, 0, _T("Condições de venda apagadas"));

			m_generic_inbound_record_counter = 0;
		}
		*/
		break;
	case PKT_SND_COND_VENDA :
		/*
		{
			CQSCondicoesVenda cv;

			cv.ClearBuffer();
			cv.m_record.codigo = ntohs(pkt.cond_venda.codigo);
			cv.m_record.pede_percentual = ntohs(pkt.cond_venda.pede_percentual);
			cv.AddRecord();
			AddEvent(EVENT_RECEIVED, PKT_SND_COND_VENDA, _T("%ld codigos de venda recebidos"), ++m_generic_inbound_record_counter);
		}
		*/
		break;
	case PKT_ASK_CLEAR_PLANOS :
		{
			CQSPlanos p;

			p.Reset();

			AddEvent(EVENT_RECEIVED, 0, _T("Planos apagados"));

			m_generic_inbound_record_counter = 0;
		}
		break;
	case PKT_SND_PLANO :
		{
			CQSPlanos pl;

			pl.ClearBuffer();
			pl.m_record.codigo = ntohs(pkt.plano.codigo);
			strcpy(pl.m_record.descricao, pkt.plano.descricao);
			pl.m_record.coluna = ntohs(pkt.plano.coluna);
			pl.AddRecord();
			AddEvent(EVENT_RECEIVED, PKT_SND_PLANO, _T("%ld codigos de planos de pagamento recebidos"), ++m_generic_inbound_record_counter);
		}
		break;
	case PKT_ASK_CLEAR_PRODUTOS :
		{
			pd.Reset();

			AddEvent(EVENT_RECEIVED, 0, _T("Produtos apagados"));

			m_generic_inbound_record_counter = 0;
		}
		break;
	case PKT_SND_PRODUTO :
		{
			pd.ClearBuffer();
			pd.m_record.codigo = ntohl(pkt.produto.codigo);
			pd.m_record.digito = ntohs(pkt.produto.digito);
            strcpy(pd.m_record.embalagem, pkt.produto.embalagem);
            strcpy(pd.m_record.unidade, pkt.produto.unidade);
            pd.m_record.unidades = ntohs(pkt.produto.unidades);
            pd.m_record.embalagem_master = ntohs(pkt.produto.embalagem_master);
            pd.m_record.peso_bruto = ntohs(pkt.produto.peso_bruto);
            strcpy(pd.m_record.descricao, pkt.produto.descricao);
			for (int i=0; i < 8; i++)
				pd.m_record.preco[i] = ntohl(pkt.produto.preco[i]);
			pd.m_record.disponivel = ntohs(pkt.produto.disponivel);
			strcpy(pd.m_record.complemento, pkt.produto.complemento);
			pd.m_record.brinde = ntohs(pkt.produto.brinde);
			pd.m_record.desconto_maximo = ntohl(pkt.produto.desconto_maximo);

			pd.AddRecord();

			AddEvent(EVENT_RECEIVED, PKT_SND_PRODUTO, _T("%ld itens adicionados"), ++m_generic_inbound_record_counter);
		}
		break;
	case PKT_ASK_REINDEX_PRODUTOS :
        {
            AddEvent(EVENT_RECEIVED, 0, _T("Ordenando produtos por codigo"));
            pd.Reindex();
            AddEvent(EVENT_RECEIVED, 0, _T("Produtos ordenados."));
        }
		break;
	case PKT_ASK_CLEAR_CLIENTES :
		{
			cl.Reset();

			AddEvent(EVENT_RECEIVED, 0, _T("Clientes apagados"));

			m_generic_inbound_record_counter = 0;
		}
		break;
	case PKT_SND_CLIENTE :
		{
			cl.ClearBuffer();
			cl.m_record.codigo = ntohl(pkt.cliente.codigo);
			cl.m_record.digito = ntohs(pkt.cliente.digito);
			strcpy(cl.m_record.cgc, pkt.cliente.cgc);
			strcpy(cl.m_record.razao_social, pkt.cliente.razao_social);
			strcpy(cl.m_record.fantasia, pkt.cliente.fantasia);
			strcpy(cl.m_record.contato, pkt.cliente.contato);
			strcpy(cl.m_record.telefone, pkt.cliente.telefone);
			strcpy(cl.m_record.fax, pkt.cliente.fax);
			cl.m_record.ramo_atividade = ntohs(pkt.cliente.ramo_atividade);
			strcpy(cl.m_record.cod_cobranca, pkt.cliente.cod_cobranca);
			cl.m_record.emitir_duplicata = ntohs(pkt.cliente.emitir_duplicata);
			cl.m_record.cod_vendedor = ntohs(pkt.cliente.cod_vendedor);
			cl.m_record.cod_praca = ntohs(pkt.cliente.cod_praca);
			cl.m_record.limite = ntohl(pkt.cliente.limite);
			cl.m_record.valor_disponivel = ntohl(pkt.cliente.valor_disponivel);
			cl.m_record.bloqueado = ntohs(pkt.cliente.bloqueado);
            cl.m_record.tabela = ntohs(pkt.cliente.tabela);
			strcpy(cl.m_record.motivo_bloqueio, pkt.cliente.motivo_bloqueio);
			strcpy(cl.m_record.endereco_comercial.endereco, pkt.cliente.endereco_comercial.endereco);
			strcpy(cl.m_record.endereco_comercial.bairro, pkt.cliente.endereco_comercial.bairro);
			strcpy(cl.m_record.endereco_comercial.cidade, pkt.cliente.endereco_comercial.cidade);
			strcpy(cl.m_record.endereco_comercial.estado, pkt.cliente.endereco_comercial.estado);
			strcpy(cl.m_record.endereco_comercial.cep, pkt.cliente.endereco_comercial.cep);
			strcpy(cl.m_record.endereco_cobranca.endereco, pkt.cliente.endereco_cobranca.endereco);
			strcpy(cl.m_record.endereco_cobranca.bairro, pkt.cliente.endereco_cobranca.bairro);
			strcpy(cl.m_record.endereco_cobranca.cidade, pkt.cliente.endereco_cobranca.cidade);
			strcpy(cl.m_record.endereco_cobranca.estado, pkt.cliente.endereco_cobranca.estado);
			strcpy(cl.m_record.endereco_cobranca.cep, pkt.cliente.endereco_cobranca.cep);

			cl.AddRecord();

			//if (++m_generic_inbound_record_counter % 10 == 0) AddEvent(EVENT_RECEIVED, PKT_SND_CLIENTE, _T("%ld clientes adicionados"), m_generic_inbound_record_counter);
			AddEvent(EVENT_RECEIVED, PKT_SND_CLIENTE, _T("%ld clientes adicionados"), ++m_generic_inbound_record_counter);
		}
		break;
	case PKT_ASK_REINDEX_CLIENTES :
		break;
	case PKT_SND_BLOCO :
		{
			DWORD dwInicio, dwFinal;
			CDBBlocos dbBlocos;

			dwInicio = ntohl(pkt.bloco.inicial);
			dwFinal = ntohl(pkt.bloco.final);
			dbBlocos.Add(dwInicio, dwFinal);
			AddEvent(EVENT_RECEIVED, 0, _T("Recebido bloco %lu - %lu"), dwInicio, dwFinal);
		}
		break;
	case PKT_EOJ :
		{
			struct packet_s pkt;

			ClearBuffer(pkt);
			pkt.header.type = htons(PKT_EOJ_ACK);
			EnqueueMessage(pkt);
			TriggerCloserThread();
		}
		break;
    case PKT_SND_MENSAGEM :
        {
            CString msg = pkt.mensagem.texto;
            AddEvent(EVENT_RECEIVED, 0, msg.GetBuffer(80));
            msg.ReleaseBuffer();
        }
        break;
	default :
		AddEvent(EVENT_RECEIVED, 0, _T("[0x%lx] Solicitação não tratada"), (LONG)ntohs(pkt.header.type));
		break;
	}
}

void CSessionThread::EnqueueMessage(struct packet_s& packet)
{
	CSingleLock QueueGateKeeper(&m_SendQueueAccess, TRUE);

	Send(packet);//S//MT//m_SendQueue.AddTail(packet);//M

	//MT//TriggerSenderThread();//M
}

void CSessionThread::EmptyAllLists()
{
	{
		CSingleLock Closing(&m_SendQueueAccess, TRUE);
		m_SendQueue.RemoveAll();
	}
	{
		CSingleLock Closing(&m_AcknowledgementsPendingAccess, TRUE);
		m_AcknowledgementsPending.RemoveAll();
	}
	{
		CSingleLock Closing(&m_TasksPendingAccess, TRUE);
		m_TasksPending.RemoveAll();
	}
}

BOOL CSessionThread::IsOpen()
{
	return m_open;
}

void CSessionThread::EnqueueTask(struct packet_s & packet)
{
	CSingleLock QueueGateKeeper(&m_TasksPendingAccess, TRUE);

	DispatchTask(packet);//S//MT//m_TasksPending.AddTail(packet);//M

	//MT//TriggerDispatcherThread();//M
}

void CSessionThread::AddEvent(int nType, WORD nCode, TCHAR *sMessage, LONG lValue1, LONG lValue2, LONG lValue3)
{
	CString msg = _T("%05d-");

	msg += sMessage;
	msg.Format(msg, nCode, lValue1, lValue2, lValue3);

	if (nType & EVENT_SENT)
	{
		m_SentEventsGateKeeper.Lock();
		if (nCode &&
			m_last_sent_message == nCode &&
			!m_events_sent.IsEmpty())
		{
			m_events_sent.GetTail() = msg;
		}
		else
		{
			m_events_sent.AddTail(msg);
			m_last_sent_message = nCode;
		}
		m_SentEventsGateKeeper.Unlock();
	}

	if (nType & EVENT_RECEIVED)
	{
		m_ReceivedEventsGateKeeper.Lock();
		if (nCode &&
			m_last_received_message == nCode && 
			!m_events_received.IsEmpty())
		{
			m_events_received.GetTail() = msg;
		}
		else
		{
			m_events_received.AddTail(msg);
			m_last_received_message = nCode;
		}
		m_ReceivedEventsGateKeeper.Unlock();
	}
}

void CSessionThread::SendEOJ()
{
	struct packet_s pkt;

	ClearBuffer(pkt);
	pkt.header.type = htons(PKT_EOJ);
	EnqueueMessage(pkt);
}

void CSessionThread::SendABORT()
{
	struct packet_s out_pkt;
	
	ClearBuffer(out_pkt);
	out_pkt.header.type = htons(PKT_ABORT);
	Send(out_pkt);
}

void CSessionThread::SendABORTACK()
{
	struct packet_s out_pkt;

	ClearBuffer(out_pkt);
	out_pkt.header.type = htons(PKT_ABORT_ACK);
	Send(out_pkt);
}

void CSessionThread::ReportSocketError(int nWhere)
{
	/*
	LPTSTR lpBuffer;
	
	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,  WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_SYS_DEFAULT),
		(LPTSTR) &lpBuffer, 0, NULL))
	{
		AddEvent(nWhere, 0, lpBuffer);
		LocalFree(lpBuffer);
	}
	*/

	AddEvent(nWhere, 0, _T("Socket error %ld at %d"), (LONG)WSAGetLastError(), nWhere);

	m_stop = TRUE;
}
