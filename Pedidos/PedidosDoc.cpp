// PedidosDoc.cpp : implementation of the CPedidosDoc class
//
// $Archive: /PalmTrader 1/Pedidos/PedidosDoc.cpp $
// $Author: Fl�vio $
// $Date: 14/06/99 22:52 $
/* $History: PedidosDoc.cpp $
 * 
 * *****************  Version 14  *****************
 * User: Fl�vio       Date: 14/06/99   Time: 22:52
 * Updated in $/PalmTrader 1/Pedidos
 * Alterado mecanismo de altera��o individual de pre�os
 * 
 * *****************  Version 13  *****************
 * User: Fl�vio       Date: 25/05/99   Time: 15:39
 * Updated in $/PalmTrader 1/Pedidos
 * Altera��es feitas para o release 1.30
 * Generalizada rotina para convers�o de n�meros em strings
 * Permitida a altera��o individual de pre�os no pedido
 * Acelerada rotina de localiza��o de produto
 * Inclu�da rotina gen�rica para convers�o de n�meros em strings
 * Corrigido bug na defini��o do tamanho do buffer de envio de pacotes TCP
 * nos m�dulos de sincroniza��o
 * Separada a porta TCP de conex�o com os clientes e servidores
 * Inclu�do m�todo em CPedido para retornar a data do pedido como DWORD,
 * que � usada no m�dulo de sincroniza��o de pedidos
 * Implementados novos atributos em pre�os
 * Inclu�do o script de cria��o da base SQL
 * 
 * *****************  Version 12  *****************
 * User: Fl�vio       Date: 25/09/98   Time: 18:09
 * Updated in $/PalmTrader 1/Pedidos
 * Corrigido bug na re-grava��o de novos pedidos.
 * 
 * *****************  Version 11  *****************
 * User: Fl�vio       Date: 25/09/98   Time: 13:29
 * Updated in $/PalmTrader 1/Pedidos
 * Inclu�dos mecanismos para prevenir e advertir poss�veis problemas na
 * grava��o de pedidos.
 * 
 * *****************  Version 10  *****************
 * User: Fl�vio       Date: 23/09/98   Time: 16:56
 * Updated in $/PalmTrader 1/Pedidos
 * Implementada classe basica para suporte a bases de dados do Windows CE.
 * Movidas as bases de dados de pedidos e de itens para a nova classe.
 * Controle de blocos removido do registry para as novas classes
 * Inclu�do �cone para futuro suporte a elimina��o de produtos
 * 
 * *****************  Version 9  *****************
 * User: Fl�vio       Date: 24/07/98   Time: 18:50
 * Updated in $/PalmTrader 1/Pedidos
 * Implementada op��o para apagar bloco de pedidos atual.
 * Corrigido bug na valida��o do c�digo de cobran�a do pedido quando este
 * � definido na sele��o do cliente
 * 
 * *****************  Version 8  *****************
 * User: Fl�vio       Date: 7/08/98    Time: 12:41p
 * Updated in $/PalmTrader 1/Pedidos
 * Fun��o PrecoUnitario renomeada para Preco.
 * Implementada fun��o PrecoUnitario, que calcula o pre�o de cada unidade
 * contida na embalagem.
 * 
 * *****************  Version 7  *****************
 * User: Fl�vio       Date: 4/22/98    Time: 2:00a
 * Updated in $/QuickSell/Pedidos
 * Inclu�do suporte a localiza��o de clientes pelo c�digo.
 * Inclu�do campo com op��o para "n�o faturar" que, no caso, gera uma
 * condi��o de venda igual a '3'.
 * Alterado formato de grava��o dos pedidos que passam agora a registrar o
 * c�digo do produto e do cliente ao inv�s dos n�meros de registro.
 * Aumentada detec��o de altera��es no pedido, evitando perda de dados.
 * 
 * *****************  Version 6  *****************
 * User: Fl�vio       Date: 4/14/98    Time: 10:05a
 * Updated in $/QuickSell/Pedidos
 * Inclu�do suporte para percentual de desconto e reten��o de pedido.
 * 
 * *****************  Version 5  *****************
 * User: Fl�vio       Date: 4/02/98    Time: 2:03a
 * Updated in $/QuickSell/Pedidos
 * Aumentados campos de exibi��o dos totais para exibi-los
 * no formato total pedido/total atendido.
 * Corrigida aus�ncia de elimina��o de arquivos de itens de blocos
 * descartados.
 * Inclu�do suporte para exibi��o de quantidade pedida/quantidade
 * atendida.
 * 
 * *****************  Version 4  *****************
 * User: Fl�vio       Date: 3/31/98    Time: 3:29p
 * Updated in $/QuickSell/Pedidos
 * Acrescentados coment�rios com keywords do SS.
 * Corrigido bug na ativa��o do bloco de pedidos reserva
 */

#include "stdafx.h"
#include "Pedidos.h"
#include "QSDatabase.h"
#include "QSTools.h"

#include "DBPedidos.h"
#include "DBItens.h"
#include "DBBlocos.h"

#include "PedidosDoc.h"
#include "PedidosRegistry.h"
#include "DialogAbrirPedido.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define X(Z) AfxMessageBox(_T(Z));

/////////////////////////////////////////////////////////////////////////////
// CPedidosDoc

IMPLEMENT_DYNCREATE(CPedidosDoc, CDocument)

BEGIN_MESSAGE_MAP(CPedidosDoc, CDocument)
	//{{AFX_MSG_MAP(CPedidosDoc)
	ON_COMMAND(ID_ABRIR_PEDIDO, OnAbrirPedido)
	ON_COMMAND(ID_GRAVAR_PEDIDO, OnGravarPedido)
	ON_COMMAND(ID_NOVO_PEDIDO, OnNovoPedido)
	ON_COMMAND(ID_APAGARBLOCO, OnApagarbloco)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPedidosDoc construction/destruction

CPedidosDoc::CPedidosDoc()
{
	// TODO: add one-time construction code here

}



CPedidosDoc::~CPedidosDoc()
{
}



BOOL CPedidosDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	//CPedidosRegistry Reg;
	CDBBlocos bloco;
	m_numero_pedido = bloco.GetFreeNumber();

	if (!m_numero_pedido)
	{
		AfxMessageBox(_T("N�o h� blocos de pedidos dispon�veis\nConecte-se e solicite um bloco de pedidos para prosseguir"), MB_OK|MB_ICONERROR);
		return FALSE;
	}

	m_coluna = 0;
    m_desconto = 0;
    m_nao_faturar =
    m_reter_pedido = FALSE;

	m_planoOK			= 
	m_cobrancaOK		= 
	m_clienteOK			= FALSE;

	m_quantidades.RemoveAll();
	m_confirmacoes.RemoveAll();
	m_descontos.RemoveAll();

	m_novo = TRUE;

	m_dirty = FALSE;

	m_bPedidoEnviado = FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CPedidosDoc serialization

void CPedidosDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CPedidosDoc diagnostics

#ifdef _DEBUG
void CPedidosDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPedidosDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPedidosDoc commands

void CPedidosDoc::OnAbrirPedido() 
{
    if (NotLosingData())
    {
	    CDialogAbrirPedido dlgAbrirPedido;

	    if (dlgAbrirPedido.DoModal() == IDOK)
	    {
		    CDBPedidos pe;
		    CDBItens it;
		    CQSPlanos pl;

			m_numero_pedido = dlgAbrirPedido.GetPedidoNumero();

		    if (!pe.Find(m_numero_pedido))
			{
				AfxMessageBox(_T("Erro na carga do pedido!"), MB_ICONERROR);
			}
			else
			{
				pe.Read();

				m_cliente_codigo    = pe.GetCodigoCliente();
				m_plano             = pe.GetPlano();
				m_cobranca          = pe.GetCodigoCobranca();
				m_reter_pedido      = pe.GetReterPedido();
				m_nao_faturar       = pe.GetCondicaoVenda() != 1;
				m_desconto          = pe.GetDesconto();
				m_bPedidoEnviado    = pe.GetPedidoEnviado();

				m_planoOK		=
				m_cobrancaOK	=
				m_clienteOK		= TRUE;

				if (pl.GetByCodigo(m_plano))
				{
					m_coluna = pl.m_record.coluna - 1;
				}

				m_quantidades.RemoveAll();
				m_confirmacoes.RemoveAll();
				m_descontos.RemoveAll();

				if (it.FindFirstItem(m_numero_pedido))
				{
					do
					{
						it.Read();
						m_produtos.FindByCodigo(it.GetProduto());
						WORD wItemRecord = m_produtos.GetRecordNumber();
						m_quantidades[wItemRecord] = it.GetQuantidadePedida();
						m_confirmacoes[wItemRecord] = it.GetQuantidadeAtendida();
						DWORD dwPrecoTabela = Preco(m_produtos.m_record.codigo, m_coluna, m_desconto, 0);
						DWORD dwPreco = it.GetPreco();
						DWORD dwDesconto  = (DWORD)((dwPrecoTabela - dwPreco) / (double)dwPrecoTabela * 1000000);
						m_descontos[wItemRecord] = dwDesconto;
					}
					while (it.FindNextItem());
				}

				m_novo = FALSE;

				m_dirty = FALSE;

				UpdateAllViews(NULL);
			}
	    }
    }
}



void CPedidosDoc::OnGravarPedido() 
{
	if (!IsValid())
	{
		AfxMessageBox(_T("Este pedido est� incompleto.\nConclua-o antes de tentar grav�-lo."), MB_ICONERROR);
		return;
	}
	if (IsPedidoEnviado())
	{
		AfxMessageBox(_T("Este pedido j� foi enviado.\nN�o � mais poss�vel registrar altera��es."), MB_ICONERROR);
		return;
	}

	CDBPedidos pe;
	CDBItens it;

	if (pe.Find(m_numero_pedido))
	{
		if (m_novo)
		{
			AfxMessageBox(_T("Advert�ncia: Pedido j� existente. Ser� regravado\nInforme esta ocorr�ncia ao respons�vel pelo sistema"), MB_ICONWARNING);
		}
		pe.Read();
	}
	else
	{
		if (!m_novo)
		{
			AfxMessageBox(_T("Advert�ncia: Este pedido ser� gravado como se fosse novo.\nPor favor, informe esta ocorr�ncia ao respons�vel pelo sistema"), MB_ICONWARNING);
		}
		pe.AddNew();
	}

	pe.SetNumeroPedido(m_numero_pedido);
	pe.SetCodigoCliente(m_cliente_codigo);
	pe.SetPlano(m_plano);
    pe.SetReterPedido(m_reter_pedido);
    pe.SetCondicaoVenda(m_nao_faturar ? 3 : 1);
    pe.SetDesconto(m_desconto);
	pe.SetDataPedido(
		CTime::GetCurrentTime().GetYear() * 10000 +
		CTime::GetCurrentTime().GetMonth() * 100 +
		CTime::GetCurrentTime().GetDay()
		);
	pe.SetCodigoCobranca(m_cobranca);
	pe.Write();

	if (m_novo)
	{
		CDBBlocos bloco;
		bloco.UseNumber(m_numero_pedido);
	}

	// Remove itens previamente gravados.
	if (it.FindFirstItem(m_numero_pedido))
	{
		do
		{
			it.Delete();
		}
		while (it.FindNextItem());
	}

	POSITION pos = m_quantidades.GetStartPosition();
	while(pos != NULL)
	{
		WORD wRec;
		DWORD dwQuant;
		DWORD dwDesconto;

		m_quantidades.GetNextAssoc(pos, wRec, dwQuant);
		m_produtos.GetRecord(wRec);
		m_descontos.Lookup(wRec, dwDesconto);
		DWORD dwPreco = Preco(m_produtos.m_record.codigo, m_coluna, m_desconto, dwDesconto);
		it.AddNew();
		it.SetPedido(m_numero_pedido);
		it.SetProduto(m_produtos.m_record.codigo);
		it.SetQuantidadePedida(dwQuant);
		it.SetPreco(dwPreco);
		it.Write();
	};

	AfxMessageBox(_T("Pedido gravado!"), MB_ICONEXCLAMATION);

	m_dirty = FALSE;
	m_novo = FALSE;
}



void CPedidosDoc::OnNovoPedido() 
{
	if (NotLosingData())
	{
		if (OnNewDocument())
		{
			UpdateAllViews(NULL);
		}
		else
		{
			X("False!?");
		}
	}
}



BOOL CPedidosDoc::IsValid()
{
	if (m_quantidades.IsEmpty()	) return FALSE;
	if (!m_planoOK				) return FALSE;
	if (!m_cobrancaOK			) return FALSE;
	if (!m_clienteOK			) return FALSE;

	return TRUE;
}



BOOL CPedidosDoc::NotLosingData()
{
	if (!m_dirty) return TRUE;
	// Alguma coisa preenchida?
	if (!m_quantidades.IsEmpty() ||
		m_planoOK ||
		m_cobrancaOK ||
		m_clienteOK)
	{
		// Tudo preenchido?
		if (IsValid())
		{
			int iAnswer = AfxMessageBox(_T("Deseja gravar este pedido?"), MB_YESNOCANCEL|MB_ICONQUESTION);

			if (iAnswer == IDYES)
			{
				OnGravarPedido();
				return TRUE;
			}
			else if (iAnswer == IDNO)
			{
				return TRUE;
			}
			else // iAnswer == IDCANCEL;
			{
				return FALSE;
			}
		}
		else
		{
			if (AfxMessageBox(_T("Deseja cancelar este pedido?"), MB_YESNO|MB_ICONQUESTION) == IDYES)
			{
				return TRUE;
			}
			else
			{
				return FALSE;
			}
		}
	}
	else
	{
		return TRUE;
	}
}



BOOL CPedidosDoc::CanCloseFrame(CFrameWnd* pFrame) 
{
	return NotLosingData();
	
	//return CDocument::CanCloseFrame(pFrame);
}

BOOL CPedidosDoc::IsPedidoEnviado()
{
    return m_bPedidoEnviado;
}

DWORD CPedidosDoc::Preco(DWORD dwProduto, WORD wColuna, WORD wDescontoPedido, DWORD dwDescontoProduto)
{
    DWORD dwPreco;

    if (m_produtos.m_record.codigo != dwProduto)
    {
        ASSERT(FALSE); // � necess�rio localizar POR CODIGO!!
        m_produtos.GetRecord((WORD)dwProduto);
    }

    dwPreco = m_produtos.m_record.preco[wColuna];

    if (wDescontoPedido)
    {
        // Aplica desconto com arredondamento
        dwPreco = (dwPreco * (100 - wDescontoPedido) / 10 + 5) / 10;
    }

    if (dwDescontoProduto)
    {
        // Aplica desconto com arredondamento
		if (dwPreco > 4294) // 2 ^ 32 = 4294967296... calcular em double para evitar overflow
		{
			dwPreco = (DWORD)(dwPreco * (1000000.0 - dwDescontoProduto) / 1000000.0 + 0.5);
		}
		else
		{
			dwPreco = (dwPreco * (1000000 - dwDescontoProduto) / 100000 + 5) / 10;
		}
    }

    return dwPreco;
}

DWORD CPedidosDoc::PrecoUnitario(DWORD dwProduto, WORD wColuna, WORD wDescontoPedido, DWORD dwDescontoProduto, BOOL bArredondar)
{
    if (m_produtos.m_record.codigo != dwProduto)
    {
        ASSERT(FALSE); // � necess�rio localizar POR CODIGO antes!!
        m_produtos.GetRecord((WORD)dwProduto);
    }

    return (Preco(dwProduto, wColuna, wDescontoPedido, dwDescontoProduto) * 10 / (m_produtos.m_record.unidades ? m_produtos.m_record.unidades : 1) + (bArredondar ? 5 : 0)) / 10;
}

void CPedidosDoc::OnApagarbloco() 
{
	/*
	int nAnswer = AfxMessageBox(_T("Deseja apagar o bloco atual?\nEsta opera��o n�o pode ser desfeita!"), MB_YESNOCANCEL|MB_ICONQUESTION);

	if (nAnswer == IDYES)
	{
		CPedidosRegistry Reg(TRUE);
		struct
		{
			DWORD
				inicio,
				fim,
				ultimo;
		} bloco_anterior, bloco_atual, bloco_reserva;

		bloco_atual.inicio = Reg.GetDWord(XXX__T("BlocoAtualInicio"));
		bloco_atual.fim =  Reg.GetDWord(XXX__T("BlocoAtualFim"));
		bloco_atual.ultimo =  Reg.GetDWord(XXX__T("BlocoAtualUltimo"));
		bloco_anterior.inicio = Reg.GetDWord("BlocoAnteriorInicio");
		bloco_reserva.inicio = Reg.GetDWord(XXX__T("BlocoReservaInicio"));
		bloco_reserva.fim = Reg.GetDWord(XXX__T("BlocoReservaFim"));

		CQSPedidos::Remove(bloco_anterior.inicio);
		CQSItens::Remove(bloco_anterior.inicio);
		
		Reg.SetDWord(XXX__T("BlocoAnteriorInicio"), bloco_atual.inicio);
		Reg.SetDWord(XXX__T("BlocoAnteriorFim"),	bloco_atual.ultimo ? bloco_atual.ultimo : bloco_atual.fim);
		
		Reg.SetDWord(XXX__T("BlocoAtualInicio"),	bloco_reserva.inicio);
		Reg.SetDWord(XXX__T("BlocoAtualFim"),		bloco_reserva.fim);
		Reg.SetDWord(XXX__T("BlocoAtualUltimo"),	0);
		
		Reg.SetDWord(XXX__T("BlocoReservaInicio"),	0);
		Reg.SetDWord(XXX__T("BlocoReservaFim"),		0);
		Reg.SetDWord(XXX__T("BlocoReservaUltimo"),	0);
		
		bloco_atual.ultimo	= bloco_reserva.inicio;
		bloco_atual.inicio	= bloco_reserva.inicio;
		bloco_atual.fim		= bloco_reserva.fim;

		AfxMessageBox(XXX__T("Bloco apagado!\nPor favor, saia da aplica��o."), MB_ICONEXCLAMATION);

		OnNovoPedido();
	}
	*/
}
