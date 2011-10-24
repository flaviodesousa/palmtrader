// SessionThread.cpp : implementation file
//
// $Archive: /PalmTrader 1/Server/SessionThread.cpp $
// $Author: Flávio $
// $Date: 25/05/99 15:31 $
/* $History: SessionThread.cpp $
 * 
 * *****************  Version 18  *****************
 * User: Flávio       Date: 25/05/99   Time: 15:31
 * Updated in $/PalmTrader 1/Server
 * Alterações feitas para o release 1.30
 * Incluída rotina genérica para conversão de números em strings
 * Corrigido bug na definição do tamanho do buffer de envio de pacotes TCP
 * nos módulos de sincronização
 * Separada a porta TCP de conexão com os clientes e servidores
 * Incluído método em CPedido para retornar a data do pedido como DWORD,
 * que é usada no módulo de sincronização de pedidos
 * Implementados novos atributos em preços
 * Incluído o script de criação da base SQL
 * 
 * *****************  Version 17  *****************
 * User: Flávio       Date: 29/09/98   Time: 8:54
 * Updated in $/QuickSell/Server
 * Incluída detecção adicional de queda de conexão.
 * 
 * *****************  Version 16  *****************
 * User: Flávio       Date: 25/09/98   Time: 17:47
 * Updated in $/QuickSell/Server
 * Movidos inicializadores do construtor para o método Open()
 * 
 * *****************  Version 15  *****************
 * User: Flávio       Date: 24/10/98   Time: 17:52
 * Updated in $/QuickSell/Server
 * Incluídos controles de erros
 * 
 * *****************  Version 14  *****************
 * User: Flávio       Date: 15/09/98   Time: 12:35
 * Updated in $/QuickSell/Server
 * Pedidos não mais registrados no servidor SQL, armazenados agora em
 * memória para agilizar o processamento.
 * Simplificado o processo de localização de clientes alterados via
 * timestamp.
 * Removido suporte a gravação de pedidos.
 * Incluídas classes para registro temporário de pedidos na memória.
 * 
 * *****************  Version 13  *****************
 * User: Flávio       Date: 24/07/98   Time: 14:24
 * Updated in $/QuickSell/Server
 * Implementação primária da sincronização automática do palmpc.
 * Alteração na lógica de fim de sessão
 * 
 * *****************  Version 12  *****************
 * User: Flávio       Date: 11/07/98   Time: 19:51
 * Updated in $/QuickSell/Server
 * A cópia do pedido é agora eliminada na retransmissão.
 * Enviado novo saldo do cliente junto com o fechamento do pedido
 * 
 * *****************  Version 11  *****************
 * User: Flávio       Date: 10/07/98   Time: 22:45
 * Updated in $/QuickSell/Server
 * Incluído suporte para reenvio de pedidos (transmissão do status)
 * Implementada transferência do cadastro de títulos
 * 
 * *****************  Version 10  *****************
 * User: Flávio       Date: 7/07/98    Time: 10:44a
 * Updated in $/QuickSell/Server
 * Incluídos novos campos na recepção de produtos
 * 
 * *****************  Version 9  *****************
 * User: Flávio       Date: 6/25/98    Time: 8:11p
 * Updated in $/QuickSell/Server
 * Incluído esboço de suporte a atualização automática (ainda não
 * operacional)
 * 
 * *****************  Version 8  *****************
 * User: Flávio       Date: 4/06/98    Time: 11:10a
 * Updated in $/QuickSell/Server
 * Mudado sistema de reportagem de erros de modo ativo para passivo
 * 
 * *****************  Version 7  *****************
 * User: Flávio       Date: 4/01/98    Time: 6:26p
 * Updated in $/QuickSell/Server
 * Incluídos comentários com keywords SS
 * Corrigido erro de conversão dos preços de venda nos pedidos recebidos.
 * Corrigida ausência de reordenação de bytes no envio do corte dos
 * pedidos.
 */

#include "stdafx.h"
#include "afxmt.h"
#include "afxtempl.h"

#include "Protocol.h"
#include "Server.h"
#include "SessionThread.h"
#include "QSTools.h"
#include "PedidosSynchronization.h"
#include "Registry.h"
#include "Configuration.h"

#include "RSClientes.h"
#include "RSClientesAlterados.h"
#include "RSCobranca.h"
#include "RSCondicoesVenda.h"
#include "RSPlanos.h"
#include "RSPrecosAlterados.h"
#include "RSProdutos.h"
#include "RSProdutosAlterados.h"
#include "RSProdutosComPrecos.h"
#include "RSVendedores.h"
#include "RSTitulosAlterados.h"
#include "RSTitulosPorVendedor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

char SessionHeader[] = _T("ZTech PalmTrader(tm) Modulo Servidor Versao 1.30\n\r");

static UINT SessionSetupThreadStart(LPVOID pParam)
{
	((CSessionThread *)pParam)->SetupRun();

	return 0;
}



static UINT SessionSenderThreadStart(LPVOID pParam)
{
	((CSessionThread *)pParam)->SenderRun();

	return 0;
}



static UINT SessionReceiverThreadStart(LPVOID pParam)
{
	((CSessionThread *)pParam)->ReceiverRun();

	return 0;
}



static UINT SessionDispatcherThreadStart(LPVOID pParam)
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

CSessionThread::CSessionThread(int slot)
{
	m_slot = slot;
	m_open = FALSE;

	TRY
	{
		m_input_buffer = new char[sizeof(struct packet_s)*2];
	}
	CATCH_ALL(e)
	{
		e->ReportError();
	}
	END_CATCH_ALL;
}



CSessionThread::~CSessionThread()
{
	delete m_input_buffer;
}



void CSessionThread::Open(void)
{
	m_bytes_received = m_bytes_sent = 0;

	m_input_buffer_offset = 0;

	m_sent_packets = 0;
	m_received_packets = 0;

	m_sender_thread_instances = 0;
	m_receiver_thread_instances = 0;
	m_dispatcher_thread_instances = 0;

	m_open = TRUE;
	m_stop = FALSE;
	m_logged = FALSE;
	m_version = 0x0;

	m_ReceivedEventsGateKeeper.Lock();
		m_events_received.RemoveAll();
	m_ReceivedEventsGateKeeper.Unlock();
	
	m_SentEventsGateKeeper.Lock();
		m_events_sent.RemoveAll();
	m_SentEventsGateKeeper.Unlock();

	EmptyAllLists(); // Paranoid for sure!

	AfxBeginThread(SessionSetupThreadStart, this);
}



void CSessionThread::Close()
{
	if (!m_stop)
	{
		AfxBeginThread(CloserThreadStart, this);
		//AddEvent(EVENT_RECEIVED, 0, _T("Fim de sessão solicitado"));
	}
}



void CSessionThread::ForceClose()
{
	m_stop = TRUE;

	SendABORT();

	CloseSession();
}



void CSessionThread::CloseSession()
{
	CSingleLock Closing(&m_SessionCloserGateKeeper, TRUE);

	CSingleLock LockSender(&m_SenderGateKeeper, TRUE);
	//CSingleLock LockReceiver(&m_ReceiverGateKeeper, TRUE);
	CSingleLock LockDispatcher(&m_DispatcherGateKeeper, TRUE);

	EmptyAllLists();

	m_logged = FALSE;
	m_open = FALSE;

	if (closesocket(m_socket) == SOCKET_ERROR) // Any doubt it will be closed?
	{
		if (WSAGetLastError() != WSAENOTSOCK)
		{
			ReportSocketError(__LINE__);
		}
	}

	if (!m_stop) // Session finished normally
	{
		CRSVendedores vd;
		vd.m_strFilter.Format(_T("vd_Codigo=%d"), (int)m_vendedor);
		vd.Open();
		if (!vd.IsEOF())
		{
			vd.Edit();
			vd.m_vd_UltimaAtualizacao = m_inicio_sessao;
			vd.Update();
		}
	}
}



void CSessionThread::SetupRun()
{
	struct packet_s in_pkt, out_pkt;

	if (send(m_socket, SessionHeader, strlen(SessionHeader)+1, 0) == SOCKET_ERROR)
	{
		ReportSocketError(__LINE__);
		return;
	}

	do // Checa versao do Transfer
	{
		ClearBuffer(out_pkt);
		out_pkt.header.type = htons(PKT_ASK_VERSION);
		Send(out_pkt);
		if (!Receive(in_pkt)) { ForceClose(); return;}
	}
	while (ntohs(in_pkt.header.type) != PKT_SND_VERSION && !m_stop);
	if (m_stop) return;
	m_version = ntohs(in_pkt.version.number);

	do // Solicita logon
	{
		ClearBuffer(out_pkt);
		out_pkt.header.type = htons(PKT_ASK_LOGON);
		Send(out_pkt);
		if (!Receive(in_pkt)) { ForceClose(); return;}
	}
	while (ntohs(in_pkt.header.type) != PKT_SND_LOGON && !m_stop);
	if (m_stop) return;

	m_vendedor = ntohs(in_pkt.logon.codigo_vendedor);
	{
		CRSVendedores v;
		v.m_strFilter.Format(_T("vd_Codigo = %d"), m_vendedor);

		v.Open();

		if (v.IsEOF())
		{
			m_logged = FALSE;
			ClearBuffer(out_pkt);
			out_pkt.header.type = htons(PKT_NAK_LOGON);
			Send(out_pkt);
			ForceClose();
			return;
		}
		else
		{
			m_logged = (v.m_vd_Senha == in_pkt.logon.senha);
			m_tabela = v.m_vd_TabelaPrecos;
            m_ultima_sessao_do_vendedor = v.m_vd_UltimaAtualizacao;
			m_inicio_sessao = CTime::GetCurrentTime();
			ClearBuffer(out_pkt);
			out_pkt.header.type = htons(PKT_ACK_LOGON);
			EnqueueMessage(out_pkt);
		}
	}

	TriggerReceiverThread();
	TriggerSenderThread();

    //AtualizarProdutos();
}



void CSessionThread::ReceiverRun(void)
{
	if (m_stop||!m_open) { CloseSession(); return; }

	int whoami = ++m_receiver_thread_instances;

	CSingleLock GateKeeper(&m_ReceiverGateKeeper, TRUE);

	struct packet_s in_pkt;

	while (Receive(in_pkt) > 0)
	{
		WORD wType = ntohs(in_pkt.header.type);

		if (wType == PKT_ABORT)
		{
			SendABORTACK();
			ForceClose();
			break;
		}
		else if (wType == PKT_ABORT_ACK)
		{
			ForceClose();
			break;
		}
		else if (wType == PKT_EOJ)
		{
			EnqueueTask(in_pkt);
			break;
		}
		else if (wType == PKT_EOJ_ACK)
		{
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

	int whoami = ++m_sender_thread_instances;

	CSingleLock
		GateKeeper(&m_SenderGateKeeper, TRUE),
		ToDo(&m_SendQueueAccess, TRUE);

	struct packet_s out_pkt;

	while (!m_SendQueue.IsEmpty())
	{
		out_pkt = m_SendQueue.RemoveHead();
		ToDo.Unlock();
		Send(out_pkt);
 		ToDo.Lock();
	}

	--m_sender_thread_instances;
}



void CSessionThread::DispatcherRun()
{
	if (m_stop||!m_open) { CloseSession(); return; }

	int whoami = ++m_dispatcher_thread_instances;

	CSingleLock
		GateKeeper(&m_DispatcherGateKeeper, TRUE),
		ToDo(&m_TasksPendingAccess, TRUE);

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



void CSessionThread::TriggerSenderThread(void)
{
	if (!m_sender_thread_instances)
		AfxBeginThread(SessionSenderThreadStart, this);
}



void CSessionThread::TriggerReceiverThread(void)
{
	if (!m_receiver_thread_instances)
		AfxBeginThread(SessionReceiverThreadStart, this);
}



void CSessionThread::TriggerDispatcherThread()
{
	if (!m_dispatcher_thread_instances)
		AfxBeginThread(SessionDispatcherThreadStart, this);
}



void CSessionThread::ClearBuffer(struct packet_s& buf)
{
	memset(&buf, 0x0, sizeof buf);
}



int CSessionThread::BufferLength(struct packet_s& buf)
{
	int Length = sizeof (struct packet_s);

	while (((BYTE *)&buf)[--Length] == 0);

	return ++Length; // The position is 0 based, right? So I compensate here
}



int CSessionThread::Send(struct packet_s& pkt)
{
	CSingleLock GateKeeper(&m_ImmediateSendAccess, TRUE);
	int retcode, len;

	len = BufferLength(pkt);
	if (len < sizeof(pkt.header))
		len = sizeof(pkt.header);

	pkt.header.magic = htonl(PKT_MAGIC_NUMBER);
	pkt.header.size = htons(len);
	pkt.header.sequence = htonl(++m_sent_packets);
	retcode = send(m_socket, (LPCTSTR)&pkt, len, 0);

	if (retcode == SOCKET_ERROR)
	{
		switch (WSAGetLastError())
		{
			case WSAECONNRESET : // Conexão abortada
			case WSAECONNABORTED : // Idem
				m_stop = TRUE;
				break;
			default :
				ReportSocketError(__LINE__);
		}
	}
	else if (retcode < 0)
	{
		AfxMessageBox(_T("Error while sending packet"), MB_ICONERROR);
		retcode = 0; // Gotcha!
	}

	return retcode;
}



int CSessionThread::Receive(struct packet_s& pkt)
{
	int retcode;
	char *buffer = m_input_buffer;		// Yes, I'm lazy!
	int offset = m_input_buffer_offset;
	struct packet_s *pktx = (struct packet_s *)buffer; // to help debugging

	while (offset < ntohs(pktx->header.size) /*- 1*/ || 
		ntohl(pktx->header.magic) != PKT_MAGIC_NUMBER)
	{
		retcode = recv(m_socket, buffer+offset, sizeof pkt, 0);
		if (retcode <= 0)
		{
			if (retcode == SOCKET_ERROR)
			{
				if (WSAGetLastError() == WSAECONNRESET) // Conexão abortada
				{
					m_stop = TRUE;
					break;
				}
				else
				{
					ReportSocketError(__LINE__);
				}
			}
			break;
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

	if (offset >= ntohs(pktx->header.size) /*- 1*/)
	{
		int size = ntohs(pktx->header.size);

		ClearBuffer(pkt);
		memcpy(&pkt, buffer, size);
		offset -= size;
		
		// move rest of buffer to its beggining
		int residue = offset;
		char *source = buffer + size;
		while (residue--) *(buffer++) = *(source++);
		
		retcode = size;
	}
	
	if (retcode > 0)
	{
		if (++m_received_packets != ntohl(pkt.header.sequence))
		{
			//AddEvent(EVENT_RECEIVED, 0, _T("Should be %ld, but it was %ld"), m_received_packets, pkt.header.sequence);
			m_received_packets = ntohl(pkt.header.sequence);
		}
	}

	m_input_buffer_offset = offset; // give it back
	return retcode;
}



void CSessionThread::DispatchTask(struct packet_s& packet)
{
	switch (ntohs(packet.header.type))
	{
	case PKT_SND_PEDIDO :
		{
			ULONG data_entrada = ntohl(packet.pedido.data_entrada);
			CTime DataEntrada(
				data_entrada / 10000,
				data_entrada / 100 % 100,
				data_entrada % 100,
				0, 0, 0);
			m_Pedido = new CPedido;

			m_Pedido->m_Numero = ntohl(packet.pedido.numero);
			m_Pedido->m_Cliente = (DWORD)ntohl(packet.pedido.cliente_codigo);
			m_Pedido->m_CondicaoVenda = (BYTE)ntohs(packet.pedido.condicao_venda);
			m_Pedido->m_Plano = (BYTE)ntohs(packet.pedido.plano);
			m_Pedido->m_Cobranca = packet.pedido.cobranca;
			m_Pedido->m_Vendedor = m_vendedor;
			m_Pedido->m_Data = DataEntrada;
			m_Pedido->m_Recepcao = CTime::GetCurrentTime();
		}
		break;
	case PKT_SND_PEDIDO_ITEM :
		{
			if (ntohl(packet.pedido_item.pedido) != m_Pedido->m_Numero)
			{
				AfxMessageBox(_T("Item de outro pedido!"), MB_OK|MB_ICONEXCLAMATION);
			}
			else
			{
				m_Pedido->AddItem(
					ntohl(packet.pedido_item.produto),
					ntohl(packet.pedido_item.quantidade),
					ntohl(packet.pedido_item.preco)
					);
			}
		}
		break;
	case PKT_SND_PEDIDO_FIM :
		{
			TRY
			{
				if (ntohl(packet.pedido_fim.pedido) != m_Pedido->m_Numero)
				{
					AfxMessageBox(_T("Fim de outro pedido!"), MB_OK|MB_ICONEXCLAMATION);
				}
				else
				{
					CPedidoItem item;
					DWORD dwProduto;
					CPedidosSynchronization sync(m_Pedido);

					sync.DoIt();

					while (sync.HasErrors())
					{
						struct packet_s pkt;
						CString strMsg;

						strMsg.Format(_T("* PD %ld: %s"), m_Pedido->m_Numero, sync.GetErrorMessage());
						ClearBuffer(pkt);
						pkt.header.type = htons(PKT_SND_MENSAGEM);
						strcpy(pkt.mensagem.texto, strMsg.GetBuffer(80));
						strMsg.ReleaseBuffer();
						EnqueueMessage(pkt);
					}

					POSITION pos = m_Pedido->m_Itens.GetStartPosition();
					while (pos != NULL)
					{
						struct packet_s pkt;
						ClearBuffer(pkt);
						m_Pedido->m_Itens.GetNextAssoc(pos, dwProduto, item);
						pkt.header.type = htons(PKT_SND_PEDIDO_ITEM_CONF);
						pkt.pedido_item_conf.pedido = htonl(m_Pedido->m_Numero);
						pkt.pedido_item_conf.produto = htonl(item.m_Produto);
						pkt.pedido_item_conf.quantidade = htonl(item.m_QuantidadeAtendida);
						EnqueueMessage(pkt);
					}

					{
						struct packet_s pkt;
						CString strDiagnostic = sync.DiagnosticString();

						ClearBuffer(pkt);
						pkt.header.type = htons(PKT_SND_PEDIDO_STATUS);
						pkt.pedido_status.pedido = htonl(m_Pedido->m_Numero);
						pkt.pedido_status.reenviar = sync.ReSend();
						pkt.pedido_status.novo_saldo_cliente = htonl(sync.GetNovoSaldoCliente());
						strcpy(pkt.pedido_status.diagnostico, strDiagnostic.GetBuffer(128)); strDiagnostic.ReleaseBuffer();
						EnqueueMessage(pkt);
					}
				}
			}
			CATCH_ALL(e)
			{
				e->ReportError();
			}
			END_CATCH_ALL;
		}
		delete m_Pedido;
		break;
	case PKT_ASK_NOVOS_TITULOS :
		{
			CRSTitulosAlterados ti;

			ti.SetVendedor(m_vendedor);
			ti.SetUltimaAtualizacao(m_ultima_sessao_do_vendedor);
			ti.Open();
			if (!ti.IsEOF())
			{
				struct packet_s pkt;

				ClearBuffer(pkt);
				pkt.header.type = htons(PKT_ASK_REFILL_TITULOS);
				EnqueueTask(pkt);
			}
		}
		break;
	case PKT_ASK_REFILL_TITULOS :
		{
			struct packet_s pkt;

			ClearBuffer(pkt);
			pkt.header.type = htons(PKT_ASK_CLEAR_TITULOS);
			EnqueueMessage(pkt);
		}
		{
			CRSTitulosPorVendedor ti;
			ti.EnableParameterization();
			ti.m_parm_Vendedor = m_vendedor;
			ti.Open();

			while (!ti.IsEOF())
			{
				struct packet_s pkt;
				ClearBuffer(pkt);
				pkt.header.type = htons(PKT_SND_TITULO);
				pkt.titulo.cliente = htonl(ti.m_ti_Cliente);
				pkt.titulo.valor = htonl((DWORD)(CStringToDouble(ti.m_ti_Valor) * 100.));
				CString2sz(pkt.titulo.emissao, ti.m_ti_Emissao);
				CString2sz(pkt.titulo.vencimento, ti.m_ti_Vencimento);
				CString2sz(pkt.titulo.numero, ti.m_ti_Numero);
				EnqueueMessage(pkt);
				ti.MoveNext();
			}
		}
		break;
	case PKT_ASK_NOVOS_CLIENTES :
		{
			CRSClientesAlterados ca;

			ca.SetVendedor(m_vendedor);
			ca.SetUltimaAtualizacao(m_ultima_sessao_do_vendedor);
			ca.Open();
			if (!ca.IsEOF())
			{
				struct packet_s pkt;

				ClearBuffer(pkt);
				pkt.header.type = htons(PKT_ASK_REFILL_CLIENTES);
				EnqueueTask(pkt);
			}
		}
		break;
	case PKT_ASK_REFILL_CLIENTES :
		{
			struct packet_s pkt;

			ClearBuffer(pkt);
			pkt.header.type = htons(PKT_ASK_CLEAR_CLIENTES);
			EnqueueMessage(pkt);
		}
		{
			CRSClientes rs;
			rs.m_strFilter.Format(_T("cl_Vendedor=%d"), m_vendedor);
			rs.m_strSort = _T("cl_RazaoSocial");
			TRY
			{
				rs.Open(CRecordset::forwardOnly);
			}
			CATCH(CDBException, ex)
			{
				ex->ReportError();
			}
			END_CATCH
			
			while (!rs.IsEOF() && !m_stop)
			{
				struct packet_s pkt;
				ClearBuffer(pkt);
				pkt.header.type = htons(PKT_SND_CLIENTE);
				pkt.cliente.codigo				= htonl(rs.m_cl_Codigo);
				pkt.cliente.digito				= htons(rs.m_cl_Digito);
				pkt.cliente.ramo_atividade		= htons(rs.m_cl_RamoAtividade);
				pkt.cliente.emitir_duplicata	= htons(rs.m_cl_EmitirDuplicata);
				pkt.cliente.cod_vendedor		= htons(rs.m_cl_Vendedor);
				pkt.cliente.cod_praca			= htons(rs.m_cl_Praca);
				pkt.cliente.limite				= htonl((DWORD)(CStringToDouble(rs.m_cl_Limite) * 100.));
				pkt.cliente.valor_disponivel	= htonl((DWORD)(CStringToDouble(rs.m_cl_ValorDisponivel) * 100.));
				pkt.cliente.bloqueado			= htons(rs.m_cl_Bloqueado);
				CString2sz(pkt.cliente.motivo_bloqueio				, rs.m_cl_MotivoBloqueio);
				CString2sz(pkt.cliente.cgc							, rs.m_cl_CGC);
				CString2sz(pkt.cliente.razao_social					, rs.m_cl_RazaoSocial);
				CString2sz(pkt.cliente.fantasia						, rs.m_cl_Fantasia);
				CString2sz(pkt.cliente.contato						, rs.m_cl_Contato);
				CString2sz(pkt.cliente.telefone						, rs.m_cl_Telefone);
				CString2sz(pkt.cliente.fax							, rs.m_cl_Fax);
				CString2sz(pkt.cliente.cod_cobranca					, rs.m_cl_Cobranca);
				CString2sz(pkt.cliente.endereco_comercial.endereco	, rs.m_cl_EnderecoComercial);
				CString2sz(pkt.cliente.endereco_comercial.bairro	, rs.m_cl_EnderecoComercialBairro);
				CString2sz(pkt.cliente.endereco_comercial.cidade	, rs.m_cl_EnderecoComercialCidade);
				CString2sz(pkt.cliente.endereco_comercial.estado	, rs.m_cl_EnderecoComercialEstado);
				CString2sz(pkt.cliente.endereco_comercial.cep		, rs.m_cl_EnderecoComercialCEP);
				CString2sz(pkt.cliente.endereco_cobranca.endereco	, rs.m_cl_EnderecoCobranca);
				CString2sz(pkt.cliente.endereco_cobranca.bairro		, rs.m_cl_EnderecoCobrancaBairro);
				CString2sz(pkt.cliente.endereco_cobranca.cidade		, rs.m_cl_EnderecoCobrancaCidade);
				CString2sz(pkt.cliente.endereco_cobranca.estado		, rs.m_cl_EnderecoCobrancaEstado);
				CString2sz(pkt.cliente.endereco_cobranca.cep		, rs.m_cl_EnderecoCobrancaCEP);
				EnqueueMessage(pkt);
				rs.MoveNext();
			}
			rs.Close();
		}
		{
			struct packet_s pkt;

			ClearBuffer(pkt);
			pkt.header.type = htons(PKT_ASK_REINDEX_CLIENTES);
			EnqueueMessage(pkt);
		}
		break;
	case PKT_ASK_NOVOS_PRECOS :
	case PKT_ASK_NOVOS_SALDOS :
		// Estes dois casos estão temporariamente sendo atendidos pelo caso PKT_ASK_NOVOS_PRODUTOS
		break;
	case PKT_ASK_NOVOS_PRODUTOS :
		{
			BOOL bRefillProdutos;

			{
				CRSProdutosAlterados pa;

				pa.SetUltimaAtualizacao(m_ultima_sessao_do_vendedor);
				pa.Open();
				bRefillProdutos = !pa.IsEOF();
			}

			if (!bRefillProdutos)
			{
				CRSPrecosAlterados pa;

				pa.SetTabela(m_tabela);
				pa.SetUltimaAtualizacao(m_ultima_sessao_do_vendedor);
				pa.Open();
				bRefillProdutos = !pa.IsEOF();
			}

			if (bRefillProdutos)
			{
				struct packet_s pkt;

				ClearBuffer(pkt);
				pkt.header.type = htons(PKT_ASK_REFILL_PRODUTOS);
				EnqueueTask(pkt);
			}
		}
		break;
	case PKT_ASK_REFILL_PRODUTOS :
		{
			struct packet_s pkt;

			ClearBuffer(pkt);
			pkt.header.type = htons(PKT_ASK_CLEAR_PRODUTOS);
			EnqueueMessage(pkt);
		}
		{
			static int counter = 0; //Debug
			CRSProdutosComPrecos rs;
			TRY
			{
				rs.m_strFilter.Format(_T("pr_Tabela=%d"), m_tabela);
				rs.m_strSort = _T("pd_Descricao");
				rs.Open(CRecordset::forwardOnly);
			}
			CATCH(CDBException, ex)
			{
				ex->ReportError();
			}
			END_CATCH
			while (!rs.IsEOF() && !m_stop)
			{
				struct packet_s pkt;

				ClearBuffer(pkt);
				pkt.header.type = htons(PKT_SND_PRODUTO);
				pkt.produto.codigo = htonl(rs.m_pd_Codigo);
				pkt.produto.digito = htons(rs.m_pd_Digito);
				CString2sz(pkt.produto.descricao, rs.m_pd_Descricao);
                CString2sz(pkt.produto.embalagem, rs.m_pd_Embalagem);
                CString2sz(pkt.produto.unidade, rs.m_pd_Unidade);
                pkt.produto.unidades = htons((WORD)rs.m_pd_Unidades);
                pkt.produto.embalagem_master = htons((WORD)rs.m_pd_EmbalagemMaster);
                //pkt.produto.peso_bruto = htonl(0);
				pkt.produto.preco[0] = htonl((DWORD)(CStringToDouble(rs.m_pr_Preco1)*100. + .5));
				pkt.produto.preco[1] = htonl((DWORD)(CStringToDouble(rs.m_pr_Preco2)*100. + .5));
				pkt.produto.preco[2] = htonl((DWORD)(CStringToDouble(rs.m_pr_Preco3)*100. + .5));
				pkt.produto.preco[3] = htonl((DWORD)(CStringToDouble(rs.m_pr_Preco4)*100. + .5));
				pkt.produto.preco[4] = htonl((DWORD)(CStringToDouble(rs.m_pr_Preco5)*100. + .5));
				pkt.produto.preco[5] = htonl((DWORD)(CStringToDouble(rs.m_pr_Preco6)*100. + .5));
				pkt.produto.preco[6] = htonl((DWORD)(CStringToDouble(rs.m_pr_Preco7)*100. + .5));
				pkt.produto.preco[7] = htonl((DWORD)(CStringToDouble(rs.m_pr_Preco8)*100. + .5));
				pkt.produto.disponivel = htons(rs.m_pd_Disponivel);
				CString2sz(pkt.produto.complemento, rs.m_pr_Complemento);
				pkt.produto.brinde = htons((WORD)rs.m_pr_Brinde);
				pkt.produto.desconto_maximo = htonl((DWORD)(CStringToDouble(rs.m_pr_DescontoMaximo)));
				EnqueueMessage(pkt);
				rs.MoveNext();
				counter++; // Debug
			}
			rs.Close();
			{ // Debug
				CString msg;
				msg.Format(_T("%d"), counter);
			}
		}
		{
			struct packet_s pkt;

			ClearBuffer(pkt);
			pkt.header.type = htons(PKT_ASK_REINDEX_PRODUTOS);
			EnqueueMessage(pkt);
		}
		break;
	case PKT_ASK_REFILL_PLANOS :
		{
			struct packet_s pkt;

			ClearBuffer(pkt);
			pkt.header.type = htons(PKT_ASK_CLEAR_PLANOS);
			EnqueueMessage(pkt);
		}
		{
			static int counter = 0; //Debug
			CRSPlanos rs;
			rs.m_strSort = _T("pl_Codigo");
			TRY
			{
				rs.Open(CRecordset::forwardOnly);
			}
			CATCH(CDBException, ex)
			{
				ex->ReportError();
			}
			END_CATCH
			while (!rs.IsEOF() && !m_stop)
			{
				struct packet_s pkt;
				ClearBuffer(pkt);
				pkt.header.type = htons(PKT_SND_PLANO);
				pkt.plano.codigo = htons(rs.m_pl_Codigo);
				CString2sz(pkt.plano.descricao, rs.m_pl_Descricao);
				pkt.plano.coluna = htons(rs.m_pl_ColunaPreco);
				EnqueueMessage(pkt);
				rs.MoveNext();
			}
			rs.Close();
		}
		break;
	/*
	case PKT_ASK_REFILL_COND_VENDA :
		{
			struct packet_s pkt;

			ClearBuffer(pkt);
			pkt.header.type = htons(PKT_ASK_CLEAR_COND_VENDA);
			EnqueueMessage(pkt);
		}
		{
			static int counter = 0; //Debug
			CRSCondicoesVenda rs;
			rs.m_strSort = _T("cv_Codigo");
			TRY
			{
				rs.Open(CRecordset::forwardOnly);
			}
			CATCH(CDBException, ex)
			{
				ex->ReportError();
			}
			END_CATCH
			while (!rs.IsEOF() && !m_stop)
			{
				struct packet_s pkt;
				ClearBuffer(pkt);
				pkt.header.type = htons(PKT_SND_COND_VENDA);
				pkt.cond_venda.codigo = htons(rs.m_cv_Codigo);
				pkt.cond_venda.pede_percentual = htons(rs.m_cv_PedePercentual);
				EnqueueMessage(pkt);
				rs.MoveNext();
			}
			rs.Close();
		}
		break;
	*/
	case PKT_ASK_REFILL_COBRANCA :
		{
			struct packet_s pkt;

			ClearBuffer(pkt);
			pkt.header.type = htons(PKT_ASK_CLEAR_COBRANCA);
			EnqueueMessage(pkt);
		}
		{
			CRSCobranca rs;
			rs.m_strSort = _T("cb_Codigo");
			TRY
			{
				rs.Open(CRecordset::forwardOnly);
			}
			CATCH(CDBException, ex)
			{
				ex->ReportError();
			}
			END_CATCH
			while (!rs.IsEOF() && !m_stop)
			{
				struct packet_s pkt;
				ClearBuffer(pkt);
				pkt.header.type = htons(PKT_SND_COBRANCA);
				CString2sz(pkt.cobranca.codigo, rs.m_cb_Codigo);
				CString2sz(pkt.cobranca.descricao, rs.m_cb_Descricao);
				EnqueueMessage(pkt);
				rs.MoveNext();
			}
			rs.Close();
		}
		break;
	case PKT_ASK_BLOCO :
		{
			struct packet_s pkt;
			DWORD lBlocoAtual, lTamanhoAtual;

			{
			CRegistry reg(TRUE /*Keep Open*/);

			lBlocoAtual = reg.GetDWord(_T("PDBlocoAtual"));
			lTamanhoAtual = reg.GetDWord(_T("PDTamanhoAtual"));

			reg.SetDWord(_T("PDBlocoAnterior"), lBlocoAtual);
			reg.SetDWord(_T("PDTamanhoAnterior"), lTamanhoAtual);
			reg.SetDWord(_T("PDBlocoAtual"), lBlocoAtual + lTamanhoAtual);
			}

			ClearBuffer(pkt);
			pkt.header.type = htons(PKT_SND_BLOCO);
			pkt.bloco.inicial = htonl(lBlocoAtual);
			pkt.bloco.final = htonl(lBlocoAtual + lTamanhoAtual - 1);
			EnqueueMessage(pkt);
		}
		break;
	case PKT_EOQ :
		{
			BOOL bNoMoreTasks;
			{
				CSingleLock GateKeeper(&m_TasksPendingAccess, TRUE);
				bNoMoreTasks = m_TasksPending.IsEmpty();
			}

			if (bNoMoreTasks)
			{ // OK.. Put an end to this session
				struct packet_s pkt;

				ClearBuffer(pkt);
				pkt.header.type = htons(PKT_EOJ);
				EnqueueMessage(pkt);
			}
			else
			{ // Let the finish to happen later
				struct packet_s pkt;

				ClearBuffer(pkt);
				pkt.header.type = htons(PKT_EOQ);
				EnqueueTask(pkt);
			}
		}
		break;
	case PKT_EOJ :
		{
			struct packet_s pkt;

			ClearBuffer(pkt);
			pkt.header.type = htons(PKT_EOJ_ACK);
			EnqueueMessage(pkt);
			//TriggerCloserThread();
		}
		break;
	default:
		{
			struct packet_s pkt;

			ClearBuffer(pkt); //// MENSAGEM NAO TRATADA!!!
		}
	}
}



void CSessionThread::EnqueueMessage(struct packet_s& packet)
{
	CSingleLock QueueGateKeeper(&m_SendQueueAccess, TRUE);

	m_SendQueue.AddTail(packet);

	TriggerSenderThread(); // Just in case...
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



void CSessionThread::EnqueueTask(struct packet_s & packet)
{
	CSingleLock QueueGateKeeper(&m_TasksPendingAccess, TRUE);

	m_TasksPending.AddTail(packet);

	TriggerDispatcherThread(); // Just in case...
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

void CSessionThread::AtualizarProdutos()
{
	{
		struct packet_s pkt;

		ClearBuffer(pkt);
		pkt.header.type = htons(PKT_ASK_CLEAR_PRODUTOS);
		EnqueueMessage(pkt);
	}
	{
		static int counter = 0; //Debug
		CRSProdutosComPrecos rs;
		TRY
		{
			rs.m_strFilter.Format(_T("pr_Tabela=%d"), m_tabela);
			rs.m_strSort = _T("pd_Descricao");
			rs.Open(CRecordset::forwardOnly);
		}
		CATCH(CDBException, ex)
		{
			ex->ReportError();
		}
		END_CATCH
		while (!rs.IsEOF() && !m_stop)
		{
			struct packet_s pkt;
			ClearBuffer(pkt);
			pkt.header.type = htons(PKT_SND_PRODUTO);
			pkt.produto.codigo = htonl(rs.m_pd_Codigo);
			pkt.produto.digito = htons(rs.m_pd_Digito);
			CString2sz(pkt.produto.descricao, rs.m_pd_Descricao);
			pkt.produto.preco[0] = htonl((DWORD)(CStringToDouble(rs.m_pr_Preco1)*100. + .5));
			pkt.produto.preco[1] = htonl((DWORD)(CStringToDouble(rs.m_pr_Preco2)*100. + .5));
			pkt.produto.preco[2] = htonl((DWORD)(CStringToDouble(rs.m_pr_Preco3)*100. + .5));
			pkt.produto.preco[3] = htonl((DWORD)(CStringToDouble(rs.m_pr_Preco4)*100. + .5));
			pkt.produto.preco[4] = htonl((DWORD)(CStringToDouble(rs.m_pr_Preco5)*100. + .5));
			pkt.produto.preco[5] = htonl((DWORD)(CStringToDouble(rs.m_pr_Preco6)*100. + .5));
			pkt.produto.preco[6] = htonl((DWORD)(CStringToDouble(rs.m_pr_Preco7)*100. + .5));
			pkt.produto.preco[7] = htonl((DWORD)(CStringToDouble(rs.m_pr_Preco8)*100. + .5));
			pkt.produto.disponivel = htons(rs.m_pd_Disponivel);
			EnqueueMessage(pkt);
			rs.MoveNext();
			counter++; // Debug
		}
		rs.Close();
		{ // Debug
			CString msg;
			msg.Format(_T("%d"), counter);
		}
	}
	{
		struct packet_s pkt;

		ClearBuffer(pkt);
		pkt.header.type = htons(PKT_ASK_REINDEX_PRODUTOS);
		EnqueueMessage(pkt);
	}
}

void CSessionThread::ReportSocketError(int nLine)
{
	m_stop = TRUE;

	CString errmsg;

	errmsg.Format(_T("SessionThread got a socket error #%d in line %d"), WSAGetLastError(), nLine);

	AfxMessageBox(errmsg, MB_ICONERROR);
}
