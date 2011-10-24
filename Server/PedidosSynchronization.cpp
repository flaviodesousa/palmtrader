// PedidosSynchronization.cpp: implementation of the CPedidosSynchronization class.
//
//////////////////////////////////////////////////////////////////////
// $Archive: /PalmTrader 1/Server/PedidosSynchronization.cpp $
// $Author: Fl�vio $
// $Date: 25/05/99 15:31 $
/* $History: PedidosSynchronization.cpp $
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
 * User: Fl�vio       Date: 15/09/98   Time: 12:35
 * Updated in $/QuickSell/Server
 * Pedidos n�o mais registrados no servidor SQL, armazenados agora em
 * mem�ria para agilizar o processamento.
 * Simplificado o processo de localiza��o de clientes alterados via
 * timestamp.
 * Removido suporte a grava��o de pedidos.
 * Inclu�das classes para registro tempor�rio de pedidos na mem�ria.
 * 
 * *****************  Version 6  *****************
 * User: Fl�vio       Date: 11/07/98   Time: 19:45
 * Updated in $/QuickSell/Server
 * Aprimorado controle de erros.
 * Inclu�do novo saldo do cliente no fechamento do pedido
 * 
 * *****************  Version 5  *****************
 * User: Fl�vio       Date: 10/07/98   Time: 22:44
 * Updated in $/QuickSell/Server
 * Inclu�dos m�todos para obten��o do status do pedido
 * 
 * *****************  Version 4  *****************
 * User: Fl�vio       Date: 7/02/98    Time: 4:35p
 * Updated in $/QuickSell/Server
 * Inclu�do suporte para reenvio de pedidos
 * 
 * *****************  Version 3  *****************
 * User: Fl�vio       Date: 4/22/98    Time: 1:52a
 * Updated in $/QuickSell/Server
 * Reinclu�do campo da condi��o de venda para atender �s solicita��es dos
 * vendedores do Armaz�m Goi�s
 */

#include "stdafx.h"
#include "QSTools.h"
#include "Server.h"
#include "PedidosSynchronization.h"
#include "RSClientes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPedidosSynchronization::CPedidosSynchronization(CPedido *Pedido)
{
	m_Pedido = Pedido;
	nRowCount = nTipoRegistro = 0;
}



CPedidosSynchronization::~CPedidosSynchronization()
{
}



BOOL CPedidosSynchronization::Process(CString & strRow)
{
	if (strRow == "/*")
	{
		return FALSE;
	}
	else
	{
		switch (nTipoRegistro)
		{
		case 2 : // Confirma��o de item
			strRows[nRowCount] = strRow;
			nRowCount = ++nRowCount % 2;
			if (!nRowCount)
			{
				long produto = atol(strRows[0]);
				long quantidade = atol(strRows[1]);

				if (quantidade < 0)
				{
					CString strErrMsg;
					strErrMsg.Format(_T("Produto %ld - %s"),
						produto,
						quantidade == -1 ? _T("n�o existente") :
						quantidade == -2 ? _T("pre�o inv�lido") :
						_T("erro interno"));
					AddError(strErrMsg);
				}
				else
				{
					m_Pedido->SetQuantidadeAtendida((DWORD)produto, (DWORD)quantidade);
				}

				nTipoRegistro = 0;
			}
			break;
		case 3 : // Pedido gravado
			strRows[nRowCount] = strRow;
			nRowCount = ++nRowCount % 3;
			if (!nRowCount)
            {
				try
				{
					CRSClientes cl;
					cl.EnableParameterization();
					cl.m_parm_Codigo = m_Pedido->m_Cliente;
					cl.Open();
					if (!cl.IsEOF())
					{
						cl.Edit();
						cl.m_cl_ValorDisponivel = strRows[2];
						m_SaldoCliente = (DWORD)(CStringToDouble(strRows[2])*100.);
						cl.m_cl_TimeStamp = CTime::GetCurrentTime();
						cl.Update();
					}

					m_Pedido->m_Reenviar = (atoi(strRows[0]) != 0);
					m_Pedido->m_Diagnostico = strRows[1];
	    			m_Pedido->m_Processamento = CTime::GetCurrentTime();

				}
				catch (CDBException *e)
				{
					AddError(e->ReportError());
				}

			    nTipoRegistro = 0;
            }
			break;
		case 9 : // Erro no cabe�alho
			AddError(strRow);
			nTipoRegistro = 0;
			break;
		default :
			nTipoRegistro = atoi(strRow);
			nRowCount = 0;
			break;
		}

		return TRUE;
	}
}



void CPedidosSynchronization::SendRequest()
{
	char buf[1024];

	{
		CString strRequest;
		long lTotal = 0;
		DWORD dwProduto;
		CPedidoItem item;
		POSITION pos;
		
		pos = m_Pedido->m_Itens.GetStartPosition();
		while (pos != NULL)
		{
			m_Pedido->m_Itens.GetNextAssoc(pos, dwProduto, item);
			lTotal += (long)(item.m_PrecoUnitario * item.m_QuantidadePedida);
		}

		sprintf(
			buf
			,
			"01\012"	// 01=Cabe�alho de pedido
			"%ld\012"	// Numero do pedido
			"%d\012"	// Codigo do vendedor
			"%ld\012"	// Codigo do cliente
			"%ld\012"	// Data do pedido
            "%d\012"    // Condi��o de venda
			"%d\012"	// Plano de pagamento
			"%s\012"	// Codigo de cobran�a
			"%s\012"	// Observa��es - parte 1
			"%s\012"	// Observa��es - parte 2
			"%ld\012"	// Valor total do pedido
			,
			m_Pedido->m_Numero,
			m_Pedido->m_Vendedor,
			m_Pedido->m_Cliente,
			m_Pedido->GetDataAsNumber(),
            (int)m_Pedido->m_CondicaoVenda,
			m_Pedido->m_Plano,
			m_Pedido->m_Cobranca,
			"",			// por enquanto n�o se envia observa��es
			"",
			lTotal
			);
		sock.Send(buf, strlen(buf));

		pos = m_Pedido->m_Itens.GetStartPosition();
		while (pos != NULL)
		{
			m_Pedido->m_Itens.GetNextAssoc(pos, dwProduto, item);
			sprintf(
				buf,
				"02\012"	// 02=Item de pedido
				"%ld\012"	// Codigo do produto
				"%ld\012"	// Quantidade
				"%ld\012"	// Preco de venda
				,
				dwProduto,
				(long)(item.m_QuantidadePedida*100),
				(long)(item.m_PrecoUnitario)
				);
			sock.Send(buf, strlen(buf));
		}

		strcpy(buf, "03\012"); // 03=Fim do pedido
		sock.Send(buf, strlen(buf));
	}

	strcpy(buf, "/*\012");
	sock.Send(buf, strlen(buf));
}



BOOL CPedidosSynchronization::ReSend()
{
	return m_Pedido->m_Reenviar;
}



CString CPedidosSynchronization::DiagnosticString()
{
	return m_Pedido->m_Diagnostico;
}



DWORD CPedidosSynchronization::GetNovoSaldoCliente()
{
	return m_SaldoCliente;
}
