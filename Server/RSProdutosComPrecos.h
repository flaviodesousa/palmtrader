// RSProdutosComPrecos.h : header file
//
// $Archive: /PalmTrader 1/Server/RSProdutosComPrecos.h $
// $Author: Flávio $
// $Date: 25/05/99 15:31 $
/* $History: RSProdutosComPrecos.h $
 * 
 * *****************  Version 4  *****************
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
 * *****************  Version 3  *****************
 * User: Flávio       Date: 7/04/98    Time: 6:08p
 * Updated in $/QuickSell/Server
 * Colocado em source control
 * Acrescentados campos descritivos
 */

#if !defined(AFX_RSPRODUTOSCOMPRECOS_H__A5607664_A15D_11D1_9FF1_00004403E294__INCLUDED_)
#define AFX_RSPRODUTOSCOMPRECOS_H__A5607664_A15D_11D1_9FF1_00004403E294__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
/////////////////////////////////////////////////////////////////////////////
// CRSProdutosComPrecos recordset

class CRSProdutosComPrecos : public CRecordset
{
public:
	CRSProdutosComPrecos(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRSProdutosComPrecos)

// Field/Param Data
	//{{AFX_FIELD(CRSProdutosComPrecos, CRecordset)
	int		m_pr_Tabela;
	long	m_pr_Produto;
	CString	m_pr_Preco1;
	CString	m_pr_Preco2;
	CString	m_pr_Preco3;
	CString	m_pr_Preco4;
	CString	m_pr_Preco5;
	CString	m_pr_Preco6;
	CString	m_pr_Preco7;
	CString	m_pr_Preco8;
	CTime	m_pr_TimeStamp;
	long	m_pd_Codigo;
	BYTE	m_pd_Digito;
	CString	m_pd_Descricao;
	BOOL	m_pd_Disponivel;
	CTime	m_pd_TimeStamp;
	CTime	m_pd_DisponibilidadeTimeStamp;
	CString	m_pd_Embalagem;
	long	m_pd_EmbalagemMaster;
	CString	m_pd_PesoBruto;
	CString	m_pd_Unidade;
	long	m_pd_Unidades;
	BOOL	m_pd_Renovado;
	BOOL	m_pr_Brinde;
	CString	m_pr_Complemento;
	CString	m_pr_DescontoMaximo;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSProdutosComPrecos)
	public:
	virtual CString GetDefaultConnect();    // Default connection string
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RSPRODUTOSCOMPRECOS_H__A5607664_A15D_11D1_9FF1_00004403E294__INCLUDED_)
