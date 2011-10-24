// PedidosDoc.h : interface of the CPedidosDoc class
//
/////////////////////////////////////////////////////////////////////////////
// $Archive: /PalmTrader 1/Pedidos/PedidosDoc.h $
// $Author: Flávio $
// $Date: 14/06/99 22:52 $
/* $History: PedidosDoc.h $
 * 
 * *****************  Version 13  *****************
 * User: Flávio       Date: 14/06/99   Time: 22:52
 * Updated in $/PalmTrader 1/Pedidos
 * Alterado mecanismo de alteração individual de preços
 * 
 * *****************  Version 12  *****************
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
 * *****************  Version 11  *****************
 * User: Flávio       Date: 27/10/98   Time: 10:07
 * Updated in $/PalmTrader 1/Pedidos
 * Alterado mecanismo de exibição de lista de produtos (total/somente
 * pedido)
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
 * User: Flávio       Date: 7/08/98    Time: 12:42p
 * Updated in $/PalmTrader 1/Pedidos
 * Função PrecoUnitario renomeada para Preco.
 * Implementada função PrecoUnitario, que calcula o preço de cada unidade
 * contida na embalagem.
 * 
 * *****************  Version 7  *****************
 * User: Flávio       Date: 4/22/98    Time: 2:01a
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
 * User: Flávio       Date: 4/02/98    Time: 5:01p
 * Updated in $/QuickSell/Pedidos
 * Eliminado índice de busca interno
 * 
 * *****************  Version 4  *****************
 * User: Flávio       Date: 4/02/98    Time: 2:05a
 * Updated in $/QuickSell/Pedidos
 * Aumentados campos de exibição dos totais para exibi-los no formato
 * total pedido/total atendido.
 * Corrigida ausência de eliminação de arquivos de itens de blocos
 * descartados.
 * Incluído suporte para exibição de quantidade pedida/quantidade
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
	BOOL	m_bPedidoEnviado; // Pedido já enviado à matriz?

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
