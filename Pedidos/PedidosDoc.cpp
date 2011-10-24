// PedidosDoc.cpp : implementation of the CPedidosDoc class
//
// $Archive: /PalmTrader 1/Pedidos/PedidosDoc.cpp $
// $Author: Flávio $
// $Date: 14/06/99 22:52 $
/* $History: PedidosDoc.cpp $
 * 
 * *****************  Version 14  *****************
 * User: Flávio       Date: 14/06/99   Time: 22:52
 * Updated in $/PalmTrader 1/Pedidos
 * Alterado mecanismo de alteração individual de preços
 * 
 * *****************  Version 13  *****************
 * User: Flávio       Date: 25/05/99   Time: 15:39
 * Updated in $/PalmTrader 1/Pedidos
 * Alterações feitas para o release 1.30
 * Generalizada rotina para conversão de números em strings
 * Permitida a alteração individual de preços no pedido
 * Acelerada rotina de localização de produto
 * Incluída rotina genérica para conversão de números em strings
 * Corrigido bug na definição do tamanho do buffer de envio de pacotes TCP
 * nos módulos de sincronização
 * Separada a porta TCP de conexão com os clientes e servidores
 * Incluído método em CPedido para retornar a data do pedido como DWORD,
 * que é usada no módulo de sincronização de pedidos
 * Implementados novos atributos em preços
 * Incluído o script de criação da base SQL
 * 
 * *****************  Version 12  *****************
 * User: Flávio       Date: 25/09/98   Time: 18:09
 * Updated in $/PalmTrader 1/Pedidos
 * Corrigido bug na re-gravação de novos pedidos.
 * 
 * *****************  Version 11  *****************
 * User: Flávio       Date: 25/09/98   Time: 13:29
 * Updated in $/PalmTrader 1/Pedidos
 * Incluídos mecanismos para prevenir e advertir possíveis problemas na
 * gravação de pedidos.
 * 
 * *****************  Version 10  *****************
 * User: Flávio       Date: 23/09/98   Time: 16:56
 * Updated in $/PalmTrader 1/Pedidos
 * Implementada classe basica para suporte a bases de dados do Windows CE.
 * Movidas as bases de dados de pedidos e de itens para a nova classe.
 * Controle de blocos removido do registry para as novas classes
 * Incluído ícone para futuro suporte a eliminação de produtos
 * 
 * *****************  Version 9  *****************
 * User: Flávio       Date: 24/07/98   Time: 18:50
 * Updated in $/PalmTrader 1/Pedidos
 * Implementada opção para apagar bloco de pedidos atual.
 * Corrigido bug na validação do código de cobrança do pedido quando este
 * é definido na seleção do cliente
 * 
 * *****************  Version 8  *****************
 * User: Flávio       Date: 7/08/98    Time: 12:41p
 * Updated in $/PalmTrader 1/Pedidos
 * Função PrecoUnitario renomeada para Preco.
 * Implementada função PrecoUnitario, que calcula o preço de cada unidade
 * contida na embalagem.
 * 
 * *****************  Version 7  *****************
 * User: Flávio       Date: 4/22/98    Time: 2:00a
 * Updated in $/QuickSell/Pedidos
 * Incluído suporte a localização de clientes pelo código.
 * Incluído campo com opção para "não faturar" que, no caso, gera uma
 * condição de venda igual a '3'.
 * Alterado formato de gravação dos pedidos que passam agora a registrar o
 * código do produto e do cliente ao invés dos números de registro.
 * Aumentada detecção de alterações no pedido, evitando perda de dados.
 * 
 * *****************  Version 6  *****************
 * User: Flávio       Date: 4/14/98    Time: 10:05a
 * Updated in $/QuickSell/Pedidos
 * Incluído suporte para percentual de desconto e retenção de pedido.
 * 
 * *****************  Version 5  *****************
 * User: Flávio       Date: 4/02/98    Time: 2:03a
 * Updated in $/QuickSell/Pedidos
 * Aumentados campos de exibição dos totais para exibi-los
 * no formato total pedido/total atendido.
 * Corrigida ausência de eliminação de arquivos de itens de blocos
 * descartados.
 * Incluído suporte para exibição de quantidade pedida/quantidade
 * atendida.
 * 
 * *****************  Version 4  *****************
 * User: Flávio       Date: 3/31/98    Time: 3:29p
 * Updated in $/QuickSell/Pedidos
 * Acrescentados comentários com keywords do SS.
 * Corrigido bug na ativação do bloco de pedidos reserva
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
		AfxMessageBox(_T("Não há blocos de pedidos disponíveis\nConecte-se e solicite um bloco de pedidos para prosseguir"), MB_OK|MB_ICONERROR);
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
		AfxMessageBox(_T("Este pedido está incompleto.\nConclua-o antes de tentar gravá-lo."), MB_ICONERROR);
		return;
	}
	if (IsPedidoEnviado())
	{
		AfxMessageBox(_T("Este pedido já foi enviado.\nNão é mais possível registrar alterações."), MB_ICONERROR);
		return;
	}

	CDBPedidos pe;
	CDBItens it;

	if (pe.Find(m_numero_pedido))
	{
		if (m_novo)
		{
			AfxMessageBox(_T("Advertência: Pedido já existente. Será regravado\nInforme esta ocorrência ao responsável pelo sistema"), MB_ICONWARNING);
		}
		pe.Read();
	}
	else
	{
		if (!m_novo)
		{
			AfxMessageBox(_T("Advertência: Este pedido será gravado como se fosse novo.\nPor favor, informe esta ocorrência ao responsável pelo sistema"), MB_ICONWARNING);
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
        ASSERT(FALSE); // É necessário localizar POR CODIGO!!
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
        ASSERT(FALSE); // É necessário localizar POR CODIGO antes!!
        m_produtos.GetRecord((WORD)dwProduto);
    }

    return (Preco(dwProduto, wColuna, wDescontoPedido, dwDescontoProduto) * 10 / (m_produtos.m_record.unidades ? m_produtos.m_record.unidades : 1) + (bArredondar ? 5 : 0)) / 10;
}

void CPedidosDoc::OnApagarbloco() 
{
	/*
	int nAnswer = AfxMessageBox(_T("Deseja apagar o bloco atual?\nEsta operação não pode ser desfeita!"), MB_YESNOCANCEL|MB_ICONQUESTION);

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

		AfxMessageBox(XXX__T("Bloco apagado!\nPor favor, saia da aplicação."), MB_ICONEXCLAMATION);

		OnNovoPedido();
	}
	*/
}
