// PedidosView.h : interface of the CPedidosView class
//
/////////////////////////////////////////////////////////////////////////////
// $Archive: /PalmTrader 1/Pedidos/PedidosView.h $
// $Author: Fl�vio $
// $Date: 27/10/98 10:07 $
/* $History: PedidosView.h $
 * 
 * *****************  Version 17  *****************
 * User: Fl�vio       Date: 27/10/98   Time: 10:07
 * Updated in $/PalmTrader 1/Pedidos
 * Alterado mecanismo de exibi��o de lista de produtos (total/somente
 * pedido)
 * 
 * *****************  Version 16  *****************
 * User: Fl�vio       Date: 1/10/98    Time: 16:36
 * Updated in $/PalmTrader 1/Pedidos
 * Inclu�das provis�es para manter pressionado o bot�o de modo de exibi��o
 * (todos produtos ou apenas os pedidos)
 * 
 * *****************  Version 15  *****************
 * User: Fl�vio       Date: 4/08/98    Time: 11:08
 * Updated in $/PalmTrader 1/Pedidos
 * Inclu�do suporte para venda de �tens n�o dispon�veis.
 * Implementada limpeza artificial dos campos de cobran�a e plano de
 * pagamento.
 * 
 * *****************  Version 14  *****************
 * User: Fl�vio       Date: 21/07/98   Time: 17:25
 * Updated in $/PalmTrader 1/Pedidos
 * Inclu�do suporte a atribui��o autom�tica do c�digo de cobran�a
 * associado ao cliente.
 * Reatribuido controle de defini��o do ListCtrl m_itens para o
 * ClassViewer
 * 
 * *****************  Version 13  *****************
 * User: Fl�vio       Date: 10/07/98   Time: 15:34
 * Updated in $/PalmTrader 1/Pedidos
 * Removida refer�ncia ao m�dulo de localiza��o de produtos
 * 
 * *****************  Version 12  *****************
 * User: Fl�vio       Date: 7/08/98    Time: 12:42p
 * Updated in $/PalmTrader 1/Pedidos
 * Removido campo m_observacoes
 * 
 * *****************  Version 11  *****************
 * User: Fl�vio       Date: 7/07/98    Time: 8:06a
 * Updated in $/QuickSell/Pedidos
 * Inclu�da rotina para exibi��o do extrato do cliente.
 * Novas op��es para controlar a exibi��o dos pre�os unit�rios
 * Prepara��o para implementa��o de CListaDePrecosCtrl no lugar de
 * CListCtrl
 * 
 * *****************  Version 10  *****************
 * User: Fl�vio       Date: 4/22/98    Time: 2:02a
 * Updated in $/QuickSell/Pedidos
 * Inclu�do suporte a localiza��o de clientes pelo c�digo.
 * Inclu�do campo com op��o para "n�o faturar" que, no caso, gera uma
 * condi��o de venda igual a '3'.
 * Alterado formato de grava��o dos pedidos que passam agora a registrar o
 * c�digo do produto e do cliente ao inv�s dos n�meros de registro.
 * Aumentada detec��o de altera��es no pedido, evitando perda de dados.
 * 
 * *****************  Version 9  *****************
 * User: Fl�vio       Date: 4/14/98    Time: 10:09a
 * Updated in $/QuickSell/Pedidos
 * Inclu�do suporte para lan�amento de percentual de desconto e reten��o
 * de pedido. Limpeza autom�tica da string de busca.
 * Acrescentado recurso para evitar que seja ativado o di�logo de
 * solicita��o de quantidade no primeiro 'click' ap�s a obten��o de foco
 * no ListCtrl m_itens. O primeiro click ir� somente ativar o foco
 * permitindo a sele��o do item via teclado.
 * 
 * *****************  Version 8  *****************
 * User: Fl�vio       Date: 4/03/98    Time: 3:01a
 * Updated in $/QuickSell/Pedidos
 * Desmembrado bot�o da CommandBar para exibi��o de todos os produtos ou
 * apenas os que foram pedidos.
 * Corrigido bug que ocorria quando confirmava a janela de sele��o de
 * clientes sem haver cliente selecionado.
 * 
 * *****************  Version 7  *****************
 * User: Fl�vio       Date: 4/02/98    Time: 5:15p
 * Updated in $/QuickSell/Pedidos
 * Eliminados handlers fora de uso
 * Adicionada estrutura para localiza��o r�pida de produtos
 * 
 * *****************  Version 6  *****************
 * User: Fl�vio       Date: 4/02/98    Time: 2:07a
 * Updated in $/QuickSell/Pedidos
 * Acrescentado suporte a keywords SS.
 * Desdobrado total em total pedido e total atendido
 *
 * *****************  Version 5  ***************** 
 * User: Fl�vio       Date: 3/31/98    Time: 3:36p 
 * Updated in $/QuickSell/Pedidos 
 * Corrigido fechamento de coment�rio (falha na expans�o de keyword) 
 *  
 * *****************  Version 4  ***************** 
 * User: Fl�vio       Date: 3/31/98    Time: 3:33p 
 * Updated in $/QuickSell/Pedidos 
 * Acrescentados coment�rios com keywords do SS. 
 * Implementa��o de pr�-tratamento de mensagens para melhorar o 
 * processamento de teclado.
 */

#if !defined(AFX_PEDIDOSVIEW_H__33B20CCF_5FA4_11D1_9F58_204C4F4F5020__INCLUDED_)
#define AFX_PEDIDOSVIEW_H__33B20CCF_5FA4_11D1_9F58_204C4F4F5020__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "ListaDePrecosCtrl.h"
#include "PedidosDoc.h"

class CPedidosView : public CFormView
{
public:
	enum en_TipoDeLista
	{
		en_ListaDePrecos,
		en_ItensPedidos
	};
protected:
	BOOL m_vender_itens_em_falta;
    BOOL m_arredondar;
    BOOL m_exibir_unitarios;
    BOOL m_bJustGetFocused;
    DWORD m_autoclear_timeout;
	DWORD m_dwTotalPedido, m_dwTotalAtendido;
	BOOL m_lista_montada;
	// Indica qual lista est� sendo exibida
	en_TipoDeLista m_tipo_de_lista;
	// 
	struct BuscaItem_tag
	{
	CString strDescricao;
	CTime timeLastKeyPressed; // Para definir timeout
    UINT timer;
	} m_BuscaItem;
	//

protected: // create from serialization only
	CPedidosView();
	DECLARE_DYNCREATE(CPedidosView)

public:
	//{{AFX_DATA(CPedidosView)
	enum { IDD = IDD_PEDIDOS_FORM };
	CListCtrl	m_itens;
	CEdit	m_total_ctrl;
	CListCtrl	m_itens_pedidos;
	CComboBox	m_condicao_pagamento_ctrl;
	CComboBox	m_cobranca_codigo_ctrl;
	CString	m_cobranca_codigo;
	CString	m_condicao_pagamento;
	CString	m_cliente_codigo;
	CString	m_cliente_nome;
	CString	m_numero_pedido;
	CString	m_total;
	BOOL	m_reter_pedido;
	BOOL	m_nao_faturar;
	int		m_desconto;
	//}}AFX_DATA

// Attributes
public:
	CPedidosDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPedidosView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	en_TipoDeLista GetTipoDeLista(void);
	void ExibirSomentePedido(void);
	void ExibirTodosProdutos(void);
	virtual ~CPedidosView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	void SolicitarQuantidade(CListCtrl *clistctrl);

// Generated message map functions
protected:
	void ClearFindString(void);
	void UpdateFindHeader(void);
	void IncrementFindString(TCHAR ch);
	void BackspaceFindString(void);
	void FindItem();
	void ItemListGetDispInfo(LV_DISPINFO *pDispInfo, CListCtrl * pListCtrl);
	static int CALLBACK CompararItens(LPARAM lItem1, LPARAM lItem2, LPARAM lParamSort);
	void ShowTotal(void);
	void RecalcularTotal(void);
	//{{AFX_MSG(CPedidosView)
	afx_msg void OnButtonPesqClientes();
	afx_msg void OnGetdispinfoItens(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelendokComboCondPagamento();
	afx_msg void OnClickItens(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnGetdispinfoItensPedidos(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickItensPedidos(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelendokComboCobrancaCod();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnChangeEditDesconto();
	afx_msg void OnCheckReterPedido();
	afx_msg void OnSetfocusItens(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSetfocusItensPedidos(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCheckNaoFaturar();
	afx_msg void OnCmdExibirExtrato();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in PedidosView.cpp
inline CPedidosDoc* CPedidosView::GetDocument()
   { return (CPedidosDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PEDIDOSVIEW_H__33B20CCF_5FA4_11D1_9F58_204C4F4F5020__INCLUDED_)
