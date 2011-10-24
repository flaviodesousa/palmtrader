// PedidosView.cpp : implementation of the CPedidosView class
//
// $Archive: /PalmTrader 1/Pedidos/PedidosView.cpp $
// $Author: Flávio $
// $Date: 5/08/99 13:59 $
/* $History: PedidosView.cpp $
 * 
 * *****************  Version 31  *****************
 * User: Flávio       Date: 5/08/99    Time: 13:59
 * Updated in $/PalmTrader 1/Pedidos
 * Corrigido tratamento de limites em CPedidosView::FindItem()
 * 
 * *****************  Version 30  *****************
 * User: Flávio       Date: 24/06/99   Time: 21:07
 * Updated in $/PalmTrader 1/Pedidos
 * Corrigida rotina de busca Find_Item() para localizar a PRIMEIRA
 * ocorrência da substring fornecida pelo usuário
 * 
 * *****************  Version 29  *****************
 * User: Flávio       Date: 14/06/99   Time: 22:53
 * Updated in $/PalmTrader 1/Pedidos
 * Alterado mecanismo de alteração individual de preços
 * 
 * *****************  Version 28  *****************
 * User: Flávio       Date: 1/06/99    Time: 22:33
 * Updated in $/PalmTrader 1/Pedidos
 * Exibição do número de pedido ampliada de 6 para 8 dígitos
 * 
 * *****************  Version 27  *****************
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
 * *****************  Version 26  *****************
 * User: Flávio       Date: 27/10/98   Time: 10:07
 * Updated in $/PalmTrader 1/Pedidos
 * Alterado mecanismo de exibição de lista de produtos (total/somente
 * pedido)
 * 
 * *****************  Version 25  *****************
 * User: Flávio       Date: 1/10/98    Time: 16:36
 * Updated in $/PalmTrader 1/Pedidos
 * Incluídas provisões para manter pressionado o botão de modo de exibição
 * (todos produtos ou apenas os pedidos)
 * 
 * *****************  Version 24  *****************
 * User: Flávio       Date: 6/08/98    Time: 15:32
 * Updated in $/PalmTrader 1/Pedidos
 * Corrigido bug na localização do item em foco (estava ativando o
 * selecionado).
 * Habilitado processamento da tecla enter na lista de itens pedidos
 * 
 * *****************  Version 23  *****************
 * User: Flávio       Date: 4/08/98    Time: 11:08
 * Updated in $/PalmTrader 1/Pedidos
 * Incluído suporte para venda de ítens não disponíveis.
 * Implementada limpeza artificial dos campos de cobrança e plano de
 * pagamento.
 * 
 * *****************  Version 22  *****************
 * User: Flávio       Date: 29/07/98   Time: 18:11
 * Updated in $/PalmTrader 1/Pedidos
 * Corrigido bug na atualização automática do código de cobraça a partir
 * da definição do cliente,
 * Habilitado processamento avançado de teclado  para o modo de exibição
 * de itens pedidos
 * 
 * *****************  Version 21  *****************
 * User: Flávio       Date: 24/07/98   Time: 18:50
 * Updated in $/PalmTrader 1/Pedidos
 * Implementada opção para apagar bloco de pedidos atual.
 * Corrigido bug na validação do código de cobrança do pedido quando este
 * é definido na seleção do cliente
 * 
 * *****************  Version 20  *****************
 * User: Flávio       Date: 21/07/98   Time: 17:25
 * Updated in $/PalmTrader 1/Pedidos
 * Incluído suporte a atribuição automática do código de cobrança
 * associado ao cliente.
 * Reatribuido controle de definição do ListCtrl m_itens para o
 * ClassViewer
 * 
 * *****************  Version 18  *****************
 * User: Flávio       Date: 13/07/98   Time: 15:40
 * Updated in $/PalmTrader 1/Pedidos
 * Incluído campo "Embalagem Master" no diálogo IDD_DIALOG_QUANTIDADE
 * 
 * *****************  Version 17  *****************
 * User: Flávio       Date: 11/07/98   Time: 20:19
 * Updated in $/PalmTrader 1/Pedidos
 * Incluído registro do código do cliente no diálogo
 * CDialogHistoricoCliente, para permitir o preenchimento da lista de
 * títulos em aberto
 * 
 * *****************  Version 16  *****************
 * User: Flávio       Date: 7/08/98    Time: 12:39p
 * Updated in $/PalmTrader 1/Pedidos
 * Corrigido bug que fazia surgir a mensagem "Unsupported Operation"
 * quando compilado para WinCE 2.0.
 * Implementado recurso que possibilita a exibição do preço unitário ao
 * lado do preço do produto no ListCtrl m_itens e m_itens_pedidos.
 * Variáveis com o nome iItem renomeadas para nItem.
 * Eliminado campo Observações.
 * 
 * *****************  Version 15  *****************
 * User: Flávio       Date: 7/07/98    Time: 8:03a
 * Updated in $/QuickSell/Pedidos
 * Incluídos campos para exibição da embalagem e do preço unitário no
 * diálogo de CDialogQuantidade.
 * Melhorado o mecanismo de localização da linha corrente
 * Aperfeiçoado o mecanismo de formatação de valores monetários
 * Incluída rotina para exibição do extrato do cliente
 * 
 * *****************  Version 14  *****************
 * User: Flávio       Date: 4/22/98    Time: 2:02a
 * Updated in $/QuickSell/Pedidos
 * Incluído suporte a localização de clientes pelo código.
 * Incluído campo com opção para "não faturar" que, no caso, gera uma
 * condição de venda igual a '3'.
 * Alterado formato de gravação dos pedidos que passam agora a registrar o
 * código do produto e do cliente ao invés dos números de registro.
 * Aumentada detecção de alterações no pedido, evitando perda de dados.
 * 
 * *****************  Version 13  *****************
 * User: Flávio       Date: 4/14/98    Time: 10:09a
 * Updated in $/QuickSell/Pedidos
 * Incluído suporte para lançamento de percentual de desconto e retenção
 * de pedido. Limpeza automática da string de busca.
 * Acrescentado recurso para evitar que seja ativado o diálogo de
 * solicitação de quantidade no primeiro 'click' após a obtenção de foco
 * no ListCtrl m_itens. O primeiro click irá somente ativar o foco
 * permitindo a seleção do item via teclado.
 * 
 * *****************  Version 12  *****************
 * User: Flávio       Date: 4/05/98    Time: 1:15p
 * Updated in $/QuickSell/Pedidos
 * Reduzido o delay para limpeza automática da string de busca de 5 para 3
 * segundos
 * 
 * *****************  Version 11  *****************
 * User: Flávio       Date: 4/03/98    Time: 3:01a
 * Updated in $/QuickSell/Pedidos
 * Desmembrado botão da CommandBar para exibição de todos os produtos ou
 * apenas os que foram pedidos.
 * Corrigido bug que ocorria quando confirmava a janela de seleção de
 * clientes sem haver cliente selecionado.
 * 
 * *****************  Version 10  *****************
 * User: Flávio       Date: 4/02/98    Time: 5:48p
 * Updated in $/QuickSell/Pedidos
 * Mudanças cosméticas na localização de produtos.
 * Reconhecimento do produto ativo com apenas o foco, permitindo
 * seleção mais ágil pelo teclado.
 * 
 * *****************  Version 9  *****************
 * User: Flávio       Date: 4/02/98    Time: 5:25p
 * Updated in $/QuickSell/Pedidos
 * Eliminados handlers fora de uso.
 * Implementada rotinas para localização rápida de produtos
 * 
 * *****************  Version 8  *****************
 * User: Flávio       Date: 4/02/98    Time: 9:25a
 * Updated in $/QuickSell/Pedidos
 * Colocado asterisco na frente da quantidade de produtos que sofreram
 * corte.
 * Forçada seleção de produto localizado.
 * 
 * *****************  Version 7  *****************
 * User: Flávio       Date: 4/02/98    Time: 2:05a
 * Updated in $/QuickSell/Pedidos
 * Aumentados campos de exibição dos totais para exibi-los no formato
 * total pedido/total atendido.
 * Corrigida ausência de eliminação de arquivos de itens de blocos
 * descartados.
 * Incluído suporte para exibição de quantidade pedida/quantidade
 * atendida.
 * 
 * *****************  Version 6  *****************
 * User: Flávio       Date: 3/31/98    Time: 3:32p
 * Updated in $/QuickSell/Pedidos
 * Acrescentados comentários com keywords do SS.
 * Implementado tratamento básico de teclado no ListCtrl m_itens (falta
 * agora
 * acrescentar tratamentos para teclas alfanuméricas e permitir tratamento
 * para o controle m_itens_pedidos)
 */

#include "stdafx.h"
#include "Pedidos.h"
#include "QSDatabase.h"
#include "PedidosRegistry.h"
#include "Formatter.h"

#include "PedidosDoc.h"
#include "PedidosView.h"
#include "DialogQuantidade.h"
#include "DialogPesquisaClientes.h"
#include "DialogHistoricoCliente.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define X {CString s;s.Format(_T("%d"), __LINE__);AfxMessageBox(s);}

/////////////////////////////////////////////////////////////////////////////
// Column headings for m_itens CListCtrl
#define M_ITENS_COLUMNS 3
static const LV_COLUMN m_itens_headings[] =
{
	{ LVCF_FMT|LVCF_SUBITEM|LVCF_TEXT|LVCF_WIDTH, LVCFMT_LEFT, 250+55, _T("Descrição"), 0, 0 },
	{ LVCF_FMT|LVCF_SUBITEM|LVCF_TEXT|LVCF_WIDTH, LVCFMT_RIGHT, 70, _T("Quantidade"), 0, 1 },
	{ LVCF_FMT|LVCF_SUBITEM|LVCF_TEXT|LVCF_WIDTH, LVCFMT_RIGHT, 80, _T("Preço"), 0, 2 }
};

/////////////////////////////////////////////////////////////////////////////
// CPedidosView

IMPLEMENT_DYNCREATE(CPedidosView, CFormView)

BEGIN_MESSAGE_MAP(CPedidosView, CFormView)
	//{{AFX_MSG_MAP(CPedidosView)
	ON_BN_CLICKED(IDC_BUTTON_PESQ_CLIENTES, OnButtonPesqClientes)
	ON_NOTIFY(LVN_GETDISPINFO, IDC_ITENS, OnGetdispinfoItens)
	ON_CBN_SELENDOK(IDC_COMBO_COND_PAGAMENTO, OnSelendokComboCondPagamento)
	ON_NOTIFY(NM_CLICK, IDC_ITENS, OnClickItens)
	ON_NOTIFY(LVN_GETDISPINFO, IDC_ITENS_PEDIDOS, OnGetdispinfoItensPedidos)
	ON_NOTIFY(NM_CLICK, IDC_ITENS_PEDIDOS, OnClickItensPedidos)
	ON_CBN_SELENDOK(IDC_COMBO_COBRANCA_COD, OnSelendokComboCobrancaCod)
	ON_WM_TIMER()
	ON_EN_CHANGE(IDC_EDIT_DESCONTO, OnChangeEditDesconto)
	ON_BN_CLICKED(IDC_CHECK_RETER_PEDIDO, OnCheckReterPedido)
	ON_NOTIFY(NM_SETFOCUS, IDC_ITENS, OnSetfocusItens)
	ON_NOTIFY(NM_SETFOCUS, IDC_ITENS_PEDIDOS, OnSetfocusItensPedidos)
	ON_BN_CLICKED(IDC_CHECK_NAO_FATURAR, OnCheckNaoFaturar)
	ON_COMMAND(ID_CMD_EXIBIR_EXTRATO, OnCmdExibirExtrato)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPedidosView construction/destruction

CPedidosView::CPedidosView()
	: CFormView(CPedidosView::IDD)
{
	//{{AFX_DATA_INIT(CPedidosView)
	m_cobranca_codigo = _T("");
	m_condicao_pagamento = _T("");
	m_cliente_codigo = _T("");
	m_cliente_nome = _T("");
	m_numero_pedido = _T("");
	m_total = _T("");
	m_reter_pedido = FALSE;
	m_nao_faturar = FALSE;
	m_desconto = 0;
	//}}AFX_DATA_INIT
	// TODO: add construction code here
	m_dwTotalPedido = 0;
    m_dwTotalAtendido = 0;
	m_lista_montada = FALSE;
	m_tipo_de_lista = en_ListaDePrecos;
}



CPedidosView::~CPedidosView()
{
}



void CPedidosView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPedidosView)
	DDX_Control(pDX, IDC_ITENS, m_itens);
	DDX_Control(pDX, IDC_EDIT_TOTAL, m_total_ctrl);
	DDX_Control(pDX, IDC_ITENS_PEDIDOS, m_itens_pedidos);
	DDX_Control(pDX, IDC_COMBO_COND_PAGAMENTO, m_condicao_pagamento_ctrl);
	DDX_Control(pDX, IDC_COMBO_COBRANCA_COD, m_cobranca_codigo_ctrl);
	DDX_CBString(pDX, IDC_COMBO_COBRANCA_COD, m_cobranca_codigo);
	DDV_MaxChars(pDX, m_cobranca_codigo, 4);
	DDX_CBString(pDX, IDC_COMBO_COND_PAGAMENTO, m_condicao_pagamento);
	DDV_MaxChars(pDX, m_condicao_pagamento, 4);
	DDX_Text(pDX, IDC_EDIT_CLIENTE_CODIGO, m_cliente_codigo);
	DDV_MaxChars(pDX, m_cliente_codigo, 8);
	DDX_Text(pDX, IDC_EDIT_CLIENTE_NOME, m_cliente_nome);
	DDV_MaxChars(pDX, m_cliente_nome, 40);
	DDX_Text(pDX, IDC_EDIT_PEDIDO, m_numero_pedido);
	DDX_Text(pDX, IDC_EDIT_TOTAL, m_total);
	DDX_Check(pDX, IDC_CHECK_RETER_PEDIDO, m_reter_pedido);
	DDX_Check(pDX, IDC_CHECK_NAO_FATURAR, m_nao_faturar);
	DDX_Text(pDX, IDC_EDIT_DESCONTO, m_desconto);
	//}}AFX_DATA_MAP
}



BOOL CPedidosView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPedidosView diagnostics

#ifdef _DEBUG
void CPedidosView::AssertValid() const
{
	CFormView::AssertValid();
}

void CPedidosView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CPedidosDoc* CPedidosView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPedidosDoc)));
	return (CPedidosDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPedidosView message handlers

void CPedidosView::OnInitialUpdate() 
{
	CWaitCursor HourGlass;
	CFormView::OnInitialUpdate();

	WORD Records;
	CPedidosDoc *doc = GetDocument();
	
	if (!m_lista_montada)
	{
		BOOL incluir_produtos_nao_disponiveis;

		{
			CPedidosRegistry reg;

			incluir_produtos_nao_disponiveis = reg.GetDWord(_T("ExibirProdutosNaoDisponiveis"), TRUE);
			m_vender_itens_em_falta = reg.GetDWord(_T("PermitirVendaItensEmFalta"), FALSE);
            m_autoclear_timeout = reg.GetDWord(_T("Autoclear"), 3);
            m_arredondar = reg.GetDWord(_T("ArredondarUnitarios"), TRUE);
            m_exibir_unitarios = reg.GetDWord(_T("ExibirUnitarios"), FALSE);
		}

		m_itens.SetRedraw(FALSE);

		for (int i = 0; i < M_ITENS_COLUMNS; i++)
		{
			m_itens.InsertColumn(i, &m_itens_headings[i]);
			m_itens_pedidos.InsertColumn(i, &m_itens_headings[i]);
		}

		m_itens.ShowWindow(SW_HIDE);
		{
			int nCount, nItem = 0;
			
			Records = nCount = doc->m_produtos.GetRecordCount();
			m_itens.SetItemCount(nCount);
			m_itens_pedidos.SetItemCount(100);

			for (i = 0; i < nCount; i++)
			{
				//i += 15; // Debug. Load faster
				doc->m_produtos.GetRecord(i+1);
				if (doc->m_produtos.m_record.disponivel || incluir_produtos_nao_disponiveis)
				{
					if (nItem == m_itens.InsertItem(nItem, LPSTR_TEXTCALLBACK))
					{
						m_itens.SetItemData(nItem, doc->m_produtos.GetRecordNumber());
						nItem++;
					}
				}
			}
		}
		m_itens.SetRedraw(TRUE);
		m_itens.ShowWindow(SW_SHOW);
		
		{
			CQSCobranca cb;
			
			m_cobranca_codigo_ctrl.ResetContent();
			m_cobranca_codigo_ctrl.AddString(_T("***"));
			while (!cb.IsEOF())
			{
				cb.GetRecord();
				CString str = cb.m_record.codigo;
				m_cobranca_codigo_ctrl.AddString(str);
			}
		}

		{
			CQSPlanos pl;
			
			m_condicao_pagamento_ctrl.ResetContent();
			m_condicao_pagamento_ctrl.AddString(_T("***"));
			while (!pl.IsEOF())
			{
				pl.GetRecord();
				CString str;
				
				str.Format(_T("%d"), pl.m_record.codigo);
				m_condicao_pagamento_ctrl.AddString(str);
			}
			
		}

		m_lista_montada = TRUE;
	}

	m_numero_pedido.Format(_T("%08ld"), (DWORD)doc->m_numero_pedido);

	UpdateData(FALSE);
}



void CPedidosView::SolicitarQuantidade(CListCtrl *listctrl)
{
	int nItem = listctrl->GetNextItem(-1, LVNI_FOCUSED);

	if (nItem >= 0)
	{
		WORD wRecordNumber = (WORD)listctrl->GetItemData(nItem);
		CPedidosDoc *doc = GetDocument();

		doc->m_produtos.GetRecord(wRecordNumber);

		if (!doc->m_produtos.m_record.disponivel && !m_vender_itens_em_falta)
		{
			AfxMessageBox(_T("Produto não disponível!"), MB_OK|MB_ICONERROR);
		}
		else
		{
			CDialogQuantidade dlgQuantidade(this);
			CPedidosDoc *doc;
			DWORD dwQuant[2];
			DWORD dwPreco[2];
			DWORD dwDesconto[2];
			DWORD dwPrecoBasico;
			DWORD dwPrecoUnitario;
			DWORD dwUnidadesPorEmbalagem;

			doc = GetDocument();

			dwPrecoBasico = 
				dlgQuantidade.m_dwPreco = 
				doc->Preco(
					doc->m_produtos.m_record.codigo,
					doc->m_coluna,
					m_desconto,
					0
					);
            dwUnidadesPorEmbalagem = 
				doc->m_produtos.m_record.unidades > 1
					? doc->m_produtos.m_record.unidades
					: 1;
			dwPrecoUnitario =
				doc->PrecoUnitario(
					doc->m_produtos.m_record.codigo,
					doc->m_coluna,
					doc->m_desconto,
					0,
					m_arredondar
					);
			
			BOOL bExists = GetDocument()->m_quantidades.Lookup(wRecordNumber, dwQuant[0]);

			if (!bExists)
			{
				dwQuant[0] = 0;
				dwDesconto[0] = 0;
				dwPreco[0] = dwPrecoBasico;
			}
			else
			{
				doc->m_descontos.Lookup(wRecordNumber, dwDesconto[0]);
				dwPreco[0] =
					doc->Preco(
						doc->m_produtos.m_record.codigo,
						doc->m_coluna,
						m_desconto,
						dwDesconto[0]);
			}
				
			dlgQuantidade.m_cod_item.Format(_T("%06d-%d"), doc->m_produtos.m_record.codigo, doc->m_produtos.m_record.digito);
			dlgQuantidade.m_descricao	= doc->m_produtos.m_record.descricao;
			if (strlen(doc->m_produtos.m_record.complemento))
			{
				dlgQuantidade.m_descricao += " ";
				dlgQuantidade.m_descricao += doc->m_produtos.m_record.complemento;
			}
			dlgQuantidade.m_quantidade.Format(_T("%ld"), (long)dwQuant[0]);
			dlgQuantidade.m_preco		= CFormatter::DWordAsMoney(dwPreco[0]);
            dlgQuantidade.m_desconto    = dwDesconto[0] / 10000.0;
            dlgQuantidade.m_embalagem   = doc->m_produtos.m_record.embalagem;
			dlgQuantidade.m_master		= doc->m_produtos.m_record.embalagem_master;
            dlgQuantidade.m_unitario = CFormatter::DWordAsMoney(dwPrecoUnitario);

			dlgQuantidade.m_dwPrecoAtual = dwPreco[0];

			if (dlgQuantidade.DoModal() == IDOK)
			{
				dwQuant[1] = (DWORD)_wtol(dlgQuantidade.m_quantidade);
				dwPreco[1] = dlgQuantidade.m_dwPrecoAtual;
				m_dwTotalPedido += dwPreco[1] * dwQuant[1] - dwPreco[0] * dwQuant[0];
				ShowTotal();
				
				doc->m_dirty |= (dwQuant[0] != dwQuant[1]) || (dwPreco[0] != dwPreco[1]);
				
				if (dwQuant[1])
				{
					doc->m_quantidades[wRecordNumber] = dwQuant[1];
					doc->m_descontos[wRecordNumber] = (DWORD)(dlgQuantidade.m_desconto * 10000);
				}
				else
				{
					if (bExists)
					{
						doc->m_quantidades.RemoveKey(wRecordNumber);
						doc->m_descontos.RemoveKey(wRecordNumber);
					}
				}

				// Atualiza lista de itens pedidos
				if (bExists)
				{
					LV_FINDINFO FindInfo;

					FindInfo.flags = LVFI_PARAM;
					FindInfo.lParam = wRecordNumber;

					int nItem = m_itens_pedidos.FindItem(&FindInfo, -1);

					if (nItem >= 0)
					{
						if (dwQuant[1])
						{
							m_itens_pedidos.Update(nItem);
						}
						else
						{
							m_itens_pedidos.DeleteItem(nItem);
						}
					}
				}
				else if (dwQuant[1])
				{
					int nItem = m_itens_pedidos.InsertItem(0, LPSTR_TEXTCALLBACK);
					if (nItem >= 0)
					{
						m_itens_pedidos.SetItemData(nItem, wRecordNumber);
					}
				}

				listctrl->Update(nItem);
			}
		}
	}
}



void CPedidosView::OnClickItens(NMHDR* pNMHDR, LRESULT* pResult) 
{
    if (m_bJustGetFocused)
    {
        m_bJustGetFocused = FALSE;
    }
    else
    {
        SolicitarQuantidade(&m_itens);
    }
	
	*pResult = 0;
}



void CPedidosView::OnButtonPesqClientes() 
{
	CDialogPesquisaClientes dlgClientes(this);

	if (dlgClientes.DoModal() == IDOK)
	{
        if (dlgClientes.m_cliente_codigo != 0)
        {
		    UpdateData(TRUE);

		    m_cliente_codigo = dlgClientes.m_cliente_codigo_str;
		    m_cliente_nome = dlgClientes.m_cliente_nome;
		    GetDocument()->m_cliente_codigo = dlgClientes.m_cliente_codigo;
		    GetDocument()->m_clienteOK = TRUE;

			GetDocument()->m_cobranca = m_cobranca_codigo = dlgClientes.m_cobranca_codigo;
			GetDocument()->m_cobrancaOK = TRUE;

		    GetDocument()->m_dirty = TRUE;
		    UpdateData(FALSE);
        }
	}
}



void CPedidosView::OnGetdispinfoItens(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;

	ItemListGetDispInfo(pDispInfo, &m_itens);
	
	*pResult = 0;
}



void CPedidosView::OnGetdispinfoItensPedidos(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;

	ItemListGetDispInfo(pDispInfo, &m_itens_pedidos);
	
	*pResult = 0;
}



void CPedidosView::OnClickItensPedidos(NMHDR* pNMHDR, LRESULT* pResult) 
{
    if (m_bJustGetFocused)
    {
        m_bJustGetFocused = FALSE;
    }
    else
    {
        SolicitarQuantidade(&m_itens_pedidos);
    }
	
	*pResult = 0;
}



void CPedidosView::RecalcularTotal()
{
	CPedidosDoc *d = GetDocument();
    m_dwTotalPedido = m_dwTotalAtendido = 0;
	POSITION pos = d->m_quantidades.GetStartPosition();
	if (pos != NULL)
	{
		do
		{
			WORD wRec;
			DWORD dwQuant;
			DWORD dwDesconto;

			d->m_quantidades.GetNextAssoc(pos, wRec, dwQuant);
			d->m_produtos.GetRecord(wRec);
			if (!d->m_descontos.Lookup(wRec, dwDesconto))
			{
				dwDesconto = 0;
			}
            DWORD dwPreco = d->Preco(d->m_produtos.m_record.codigo, d->m_coluna, d->m_desconto, dwDesconto);
			m_dwTotalPedido += dwQuant * dwPreco;
		} while (pos != NULL);
	}

    if (d->IsPedidoEnviado())
    {
	    pos = d->m_confirmacoes.GetStartPosition();
	    if (pos != NULL)
	    {
		    do
		    {
			    WORD wRec;
			    DWORD dwQuant;
				DWORD dwDesconto;

			    d->m_confirmacoes.GetNextAssoc(pos, wRec, dwQuant);
			    d->m_produtos.GetRecord(wRec);
				if (!d->m_descontos.Lookup(wRec, dwDesconto))
				{
					dwDesconto = 0;
				}
			    m_dwTotalAtendido += dwQuant * d->Preco(d->m_produtos.m_record.codigo, d->m_coluna, d->m_desconto, dwDesconto);
		    } while (pos != NULL);
	    }
    }

	ShowTotal();
}



void CPedidosView::ShowTotal()
{
    m_total = CFormatter::DWordAsMoney(m_dwTotalPedido);
    if (GetDocument()->IsPedidoEnviado())
    {
        m_total = m_total + 
            _T("/") + 
            CFormatter::DWordAsMoney(m_dwTotalAtendido);
    }
	m_total_ctrl.SetWindowText(m_total);
}



void CPedidosView::ItemListGetDispInfo(LV_DISPINFO * pDispInfo, CListCtrl * pListCtrl)
{
	CString txt;
	int nLastItem = -1;
	WORD wRecord;
	CPedidosDoc *doc = GetDocument();
    BOOL bEnviado = doc->IsPedidoEnviado();

	if (nLastItem != pDispInfo->item.iItem)
	{
		nLastItem = pDispInfo->item.iItem;
		wRecord = (WORD)pListCtrl->GetItemData(nLastItem);
		doc->m_produtos.GetRecord(wRecord);
	}

	switch (pDispInfo->item.iSubItem)
	{
	case 99 :
		txt.Format(_T("%06lu-%d"), 
			doc->m_produtos.m_record.codigo, doc->m_produtos.m_record.digito);
		break;
	case 0 :
		txt = doc->m_produtos.m_record.descricao;
		if (strlen(doc->m_produtos.m_record.complemento) > 1)
		{
			txt += " ";
			txt += doc->m_produtos.m_record.complemento;
		}
		break;
	case 1 :
        txt.Empty();
		if (!doc->m_produtos.m_record.disponivel)
        {
			txt += _T("*** ");
		}

		DWORD dwQuantidade;
		if (doc->m_quantidades.Lookup(wRecord, dwQuantidade))
		{
            CString strQuantidade;
            if (bEnviado) // Exibir o corte em paralelo
            {
                DWORD dwAtendido = doc->m_confirmacoes[wRecord];
                strQuantidade.Format(_T("%s%lu/%lu"), 
                    dwQuantidade != dwAtendido ? _T("* ") : _T(""),
                    dwQuantidade,
                    dwAtendido);
            }
            else
            {
				strQuantidade.Format(_T("%lu"), dwQuantidade);
            }
            txt += strQuantidade;
		}
		break;
	case 2 :
		{
            DWORD dwPrecoTabela = doc->Preco(doc->m_produtos.m_record.codigo, doc->m_coluna, doc->m_desconto, 0);
            DWORD dwDesconto;
            if (doc->m_descontos.Lookup(wRecord, dwDesconto))
            {
				DWORD dwPrecoAtual = doc->Preco(doc->m_produtos.m_record.codigo, doc->m_coluna, doc->m_desconto, dwDesconto);
                txt = CFormatter::DWordAsMoney(dwPrecoAtual);
                if (dwPrecoAtual != dwPrecoTabela) // Destacar preço diferenciado
                {
                    txt = _T("[") + txt + _T("]");
                }
            }
            else
            {
                txt = CFormatter::DWordAsMoney(dwPrecoTabela);
				dwDesconto = 0;
            }

            if (m_exibir_unitarios)
            {
                txt += (_T("      ") + CFormatter::DWordAsMoney(doc->PrecoUnitario(doc->m_produtos.m_record.codigo, doc->m_coluna, doc->m_desconto, dwDesconto, m_arredondar))).Right(6);
            }
		}
		break;
	}

	_tcsncpy(pDispInfo->item.pszText, txt, 
		pDispInfo->item.cchTextMax);
}



void CPedidosView::OnSelendokComboCondPagamento() 
{
	CQSPlanos pl;
	CPedidosDoc *doc = GetDocument();

	UpdateData(TRUE);
	if (m_condicao_pagamento != _T("***"))
	{
		if (pl.GetByCodigo((USHORT)_wtoi(m_condicao_pagamento)))
		{
			int nColunaAnterior = doc->m_coluna;
			doc->m_coluna = pl.m_record.coluna - 1;
			doc->m_plano = (BYTE)pl.m_record.codigo;
			doc->m_dirty = doc->m_planoOK = TRUE;
			if (doc->m_coluna != nColunaAnterior)
				{
					RecalcularTotal();
					m_itens.RedrawItems(m_itens.GetTopIndex(), m_itens.GetTopIndex() + m_itens.GetCountPerPage());
					m_itens_pedidos.RedrawItems(m_itens_pedidos.GetTopIndex(), m_itens_pedidos.GetTopIndex() + m_itens.GetCountPerPage());
				}
		}
		else
		{
			doc->m_dirty = doc->m_planoOK = FALSE;
		}
	}
	else
	{
		doc->m_dirty = TRUE;
		doc->m_planoOK = FALSE;
	}
	UpdateData(FALSE);
}



void CPedidosView::OnSelendokComboCobrancaCod() 
{
	CPedidosDoc *doc = GetDocument();

	UpdateData(TRUE);
	if (m_cobranca_codigo != _T("***"))
	{
		doc->m_cobranca = m_cobranca_codigo;
		doc->m_dirty = doc->m_cobrancaOK = TRUE;
	}
	else
	{
		doc->m_dirty = TRUE;
		doc->m_cobrancaOK = FALSE;
	}
}



void CPedidosView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	CPedidosDoc *doc = GetDocument();
	if (doc->m_novo)
	{
		m_cobranca_codigo =
			m_condicao_pagamento = _T("***");
		m_cliente_codigo =
			m_cliente_nome = _T("");

        m_nao_faturar =
            m_reter_pedido = FALSE;
        m_desconto = 0;
		m_cobranca_codigo_ctrl.Clear();
		m_condicao_pagamento_ctrl.Clear();
	}
	else
	{
        m_desconto = doc->m_desconto;
        m_reter_pedido = doc->m_reter_pedido;
        m_nao_faturar = doc->m_nao_faturar;
		m_cobranca_codigo = doc->m_cobranca;
		m_condicao_pagamento.Format(_T("%d"), doc->m_plano);
		
		{
			CQSClientes cl;
			
			cl.FindByCodigo(doc->m_cliente_codigo);
			m_cliente_codigo.Format(_T("%06d-%d"), 
				cl.m_record.codigo, 
				cl.m_record.digito);
			m_cliente_nome = cl.m_record.razao_social;
		}
	}

	m_numero_pedido.Format(_T("%08d"), doc->m_numero_pedido);

	{
		POSITION pos = doc->m_quantidades.GetStartPosition();
		m_itens_pedidos.DeleteAllItems();
		
		while (pos != NULL)
		{
			WORD wRec;
			DWORD dwQuant;
			doc->m_quantidades.GetNextAssoc(pos, wRec, dwQuant);
			m_itens_pedidos.InsertItem(0, LPSTR_TEXTCALLBACK);
			m_itens_pedidos.SetItemData(0, wRec);
		}
	}

	UpdateData(FALSE);
		
	RecalcularTotal();
	m_itens.RedrawItems(m_itens.GetTopIndex(), m_itens.GetTopIndex() + m_itens.GetCountPerPage());
	m_itens_pedidos.RedrawItems(m_itens_pedidos.GetTopIndex(), m_itens_pedidos.GetTopIndex() + m_itens_pedidos.GetCountPerPage());
}



BOOL CPedidosView::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->hwnd == m_itens.m_hWnd || pMsg->hwnd == m_itens_pedidos.m_hWnd)
	{
		if (pMsg->message == WM_KEYDOWN)
		{
			switch (pMsg->wParam)
			{
			case VK_RETURN :
				{
					CListCtrl *listctrl;

					if (pMsg->hwnd == m_itens.m_hWnd)
					{
						listctrl = &m_itens;
					}
					else if (pMsg->hwnd == m_itens_pedidos.m_hWnd)
					{
						listctrl = &m_itens_pedidos;
					}
					SolicitarQuantidade(listctrl);
					return TRUE;
				}
				break;
			case VK_UP :
			case VK_DOWN :
			case VK_PRIOR :
			case VK_NEXT :
			case VK_HOME :
			case VK_END :
			case VK_TAB :
                ClearFindString();
				return CFormView::PreTranslateMessage(pMsg);
				break;
            case VK_BACK :
                BackspaceFindString();
            default :
	            TCHAR ch = (TCHAR)MapVirtualKey(pMsg->wParam, 2);

	            if (_istprint(ch))
	            {
                    IncrementFindString(ch);
	            }
			}

			return TRUE; // Cancel it
		}
	}
	
	return CFormView::PreTranslateMessage(pMsg);
}



void CPedidosView::FindItem()
{
	CPedidosDoc *doc = GetDocument();
	int iLowerBound, iUpperBound; // Area para busca
    BOOL bFound = FALSE;
    WORD wItem;
	int nSoughtStringSize = m_BuscaItem.strDescricao.GetLength();

	iLowerBound = 0;
	iUpperBound = m_itens.GetItemCount() - 1;

    while (iLowerBound <= iUpperBound)
    {
        int iMiddle = (iUpperBound + iLowerBound) / 2;
		doc->m_produtos.GetRecord((WORD)m_itens.GetItemData(iMiddle));
		int nComparisonResult =
			CString(doc->m_produtos.m_record.descricao)
				.Left(nSoughtStringSize)
				.CompareNoCase(m_BuscaItem.strDescricao);

        if (nComparisonResult == 0)
        {
			if (iMiddle > iLowerBound) // Vê se o anterior tb é igual...
			{
				doc->m_produtos.GetRecord((WORD)m_itens.GetItemData(iMiddle - 1));
				nComparisonResult = 
					CString(doc->m_produtos.m_record.descricao)
						.Left(nSoughtStringSize)
						.CompareNoCase(m_BuscaItem.strDescricao);
				if (nComparisonResult == 0) // ...se for, continua procurando (o primeiro)...
				{
					iUpperBound = iMiddle - 1;
					continue;
				}
			} // senão, já achou!
			bFound = TRUE;
			wItem = iMiddle;
			break;
        }
        else if (nComparisonResult < 0)
		{
			iLowerBound = iMiddle + 1;
		}
		else //if (nComparisonResult < 0)
		{
			iUpperBound = iMiddle - 1;
		}
    }

    if (bFound)
    {
        m_itens.EnsureVisible(wItem, FALSE);
        m_itens.SetItemState(wItem, TRUE, LVIS_FOCUSED|LVIS_SELECTED);
        UpdateFindHeader();
    }
	else
	{
        BackspaceFindString();
        MessageBeep(MB_ICONEXCLAMATION);
	}

    if (m_BuscaItem.timer == 0)
    {
        m_BuscaItem.timer = SetTimer(1, 1000, NULL);
    }
}



void CPedidosView::BackspaceFindString()
{
	m_BuscaItem.timeLastKeyPressed = CTime::GetCurrentTime();
    if (!m_BuscaItem.strDescricao.IsEmpty())
    {
        m_BuscaItem.strDescricao
            = m_BuscaItem.strDescricao.Left(m_BuscaItem.strDescricao.GetLength() - 1);

        if (!m_BuscaItem.strDescricao.IsEmpty())
        {
            FindItem();
        }
        else
        {
            UpdateFindHeader();
        }
    }
}



void CPedidosView::IncrementFindString(TCHAR ch)
{
	m_BuscaItem.timeLastKeyPressed = CTime::GetCurrentTime();
    m_BuscaItem.strDescricao += ch;
    FindItem();
}



void CPedidosView::ClearFindString()
{
    if (!m_BuscaItem.strDescricao.IsEmpty())
    {
	    m_BuscaItem.strDescricao.Empty();
        UpdateFindHeader();
    }
}



void CPedidosView::OnTimer(UINT nIDEvent) 
{
	CTimeSpan delay = CTime::GetCurrentTime() - m_BuscaItem.timeLastKeyPressed;
	if (delay.GetTotalSeconds() > (int)m_autoclear_timeout)
	{
        ClearFindString();
        if (m_BuscaItem.timer)
        {
            KillTimer(m_BuscaItem.timer);
            m_BuscaItem.timer = 0;
        }
	}
	
	CFormView::OnTimer(nIDEvent);
}



void CPedidosView::UpdateFindHeader()
{
    LVCOLUMN col;
    CString strHeading;

    strHeading = m_itens_headings[0].pszText;

    if (!m_BuscaItem.strDescricao.IsEmpty())
    {
        strHeading += _T(" [");
        strHeading += m_BuscaItem.strDescricao;
        strHeading += _T("]");
    }

    col.mask = LVCF_TEXT;
    col.pszText = strHeading.GetBuffer(64);
    m_itens.SetColumn(0, &col);
    strHeading.ReleaseBuffer();
}



void CPedidosView::ExibirSomentePedido() 
{
	m_tipo_de_lista = en_ItensPedidos;
	
	m_itens.ShowWindow(SW_HIDE);
	m_itens_pedidos.ShowWindow(SW_SHOW);
}



void CPedidosView::ExibirTodosProdutos() 
{
	m_tipo_de_lista = en_ListaDePrecos;
	
	m_itens.ShowWindow(SW_SHOW);
	m_itens_pedidos.ShowWindow(SW_HIDE);
}



CPedidosView::en_TipoDeLista CPedidosView::GetTipoDeLista()
{
	return m_tipo_de_lista;
}



void CPedidosView::OnChangeEditDesconto() 
{
    if (IsWindowVisible())
    {
        UpdateData(TRUE);
        m_itens.RedrawItems(m_itens.GetTopIndex(), m_itens.GetTopIndex() + m_itens.GetCountPerPage());
        m_itens_pedidos.RedrawItems(m_itens_pedidos.GetTopIndex(), m_itens_pedidos.GetTopIndex() + m_itens.GetCountPerPage());
        GetDocument()->m_desconto = m_desconto;
        RecalcularTotal();
        GetDocument()->m_dirty = TRUE;
    }
}



void CPedidosView::OnCheckReterPedido() 
{
    UpdateData(TRUE);
    GetDocument()->m_reter_pedido = m_reter_pedido;
    GetDocument()->m_dirty = TRUE;
}



void CPedidosView::OnCheckNaoFaturar() 
{
    UpdateData(TRUE);
    GetDocument()->m_nao_faturar = m_nao_faturar;
    GetDocument()->m_dirty = TRUE;
}



void CPedidosView::OnSetfocusItens(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_bJustGetFocused = TRUE;
	
	*pResult = 0;
}



void CPedidosView::OnSetfocusItensPedidos(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_bJustGetFocused = TRUE;
	
	*pResult = 0;
}



void CPedidosView::OnCmdExibirExtrato() 
{		    
    if (!GetDocument()->m_clienteOK)
    {
        AfxMessageBox(_T("Não há cliente indicado!"), MB_ICONERROR);
    }
    else
    {
        CQSClientes cliente;

        if (cliente.FindByCodigo(GetDocument()->m_cliente_codigo))
        {
            CDialogHistoricoCliente dlg;

			dlg.m_cliente_codigo = cliente.m_record.codigo;
            dlg.m_cliente = cliente.m_record.razao_social;
                dlg.m_cliente += _T(" (");
                dlg.m_cliente += cliente.m_record.fantasia;
                dlg.m_cliente += _T(")");

            dlg.m_limite = CFormatter::DWordAsMoney(cliente.m_record.limite);
            dlg.m_disponivel = CFormatter::DWordAsMoney(cliente.m_record.limite - cliente.m_record.valor_disponivel);

            dlg.DoModal();
        }
    }
}
