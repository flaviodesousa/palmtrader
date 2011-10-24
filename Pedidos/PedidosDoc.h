// PedidosDoc.h : interface of the CPedidosDoc class
//
/////////////////////////////////////////////////////////////////////////////
// $Archive: /PalmTrader 1/Pedidos/PedidosDoc.h $
// $Author: Fl�vio $
// $Date: 14/06/99 22:52 $
/* $History: PedidosDoc.h $
 * 
 * *****************  Version 13  *****************
 * User: Fl�vio       Date: 14/06/99   Time: 22:52
 * Updated in $/PalmTrader 1/Pedidos
 * Alterado mecanismo de altera��o individual de pre�os
 * 
 * *****************  Version 12  *****************
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
 * *****************  Version 11  *****************
 * User: Fl�vio       Date: 27/10/98   Time: 10:07
 * Updated in $/PalmTrader 1/Pedidos
 * Alterado mecanismo de exibi��o de lista de produtos (total/somente
 * pedido)
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
 * User: Fl�vio       Date: 7/08/98    Time: 12:42p
 * Updated in $/PalmTrader 1/Pedidos
 * Fun��o PrecoUnitario renomeada para Preco.
 * Implementada fun��o PrecoUnitario, que calcula o pre�o de cada unidade
 * contida na embalagem.
 * 
 * *****************  Version 7  *****************
 * User: Fl�vio       Date: 4/22/98    Time: 2:01a
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
 * User: Fl�vio       Date: 4/02/98    Time: 5:01p
 * Updated in $/QuickSell/Pedidos
 * Eliminado �ndice de busca interno
 * 
 * *****************  Version 4  *****************
 * User: Fl�vio       Date: 4/02/98    Time: 2:05a
 * Updated in $/QuickSell/Pedidos
 * Aumentados campos de exibi��o dos totais para exibi-los no formato
 * total pedido/total atendido.
 * Corrigida aus�ncia de elimina��o de arquivos de itens de blocos
 * descartados.
 * Inclu�do suporte para exibi��o de quantidade pedida/quantidade
 * atendida.
 */

#include "afxtempl.h"

#if !defined(AFX_PEDIDOSDOC_H__33B20CCD_5FA4_11D1_9F58_204C4F4F5020__INCLUDED_)
#define AFX_PEDIDOSDOC_H__33B20CCD_5FA4_11D1_9F58_204C4F4F5020__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "QSProdutos.h"

class CPedidosDoc : public CDocument
{
public:
	//
	CQSProdutos m_produtos;
	BOOL	m_novo; // Novo pedido?
	BOOL	m_dirty; // Alterado?
	// Dados do pedido
	DWORD	m_numero_pedido;
	DWORD	m_cliente_codigo;
	BOOL	m_clienteOK;
	WORD	m_plano;
	BOOL	m_planoOK;
	BYTE	m_coluna;
    BOOL    m_reter_pedido;
    BOOL    m_nao_faturar;
    WORD    m_desconto;
	//DWORD	m_percentual;
	CString	m_cobranca;
	BOOL	m_cobrancaOK;
	CString	m_observacoes;
	CMap<WORD, WORD&, DWORD, DWORD&>
		m_quantidades,
		m_confirmacoes,
		m_descontos;

protected:
	BOOL	m_bPedidoEnviado; // Pedido j� enviado � matriz?

protected: // create from serialization only
	CPedidosDoc();
	DECLARE_DYNCREATE(CPedidosDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPedidosDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL CanCloseFrame(CFrameWnd* pFrame);
	//}}AFX_VIRTUAL

// Implementation
public:
	DWORD PrecoUnitario(DWORD dwProduto, WORD wColuna, WORD wDescontoPedido, DWORD dwDescontoProduto, BOOL bArredondar);
	DWORD Preco(DWORD dwProduto, WORD wColuna, WORD wDescontoPedido, DWORD dwDescontoProduto);
	BOOL IsPedidoEnviado(void);
	BOOL NotLosingData();
	virtual ~CPedidosDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	BOOL IsValid(void);
	//{{AFX_MSG(CPedidosDoc)
	afx_msg void OnAbrirPedido();
	afx_msg void OnGravarPedido();
	afx_msg void OnNovoPedido();
	afx_msg void OnApagarbloco();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PEDIDOSDOC_H__33B20CCD_5FA4_11D1_9F58_204C4F4F5020__INCLUDED_)
