// RSPrecos.h : header file
//
// $Archive: /PalmTrader 1/Server/RSPrecos.h $
// $Author: Flávio $
// $Date: 25/05/99 15:31 $
/* $History: RSPrecos.h $
 * 
 * *****************  Version 3  *****************
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
 * *****************  Version 2  *****************
 * User: Flávio       Date: 7/04/98    Time: 6:07p
 * Updated in $/QuickSell/Server
 * Colocado em source control
 */

#if !defined(AFX_RSPRECOS_H__D2DC2437_7287_11D1_9F93_204C4F4F5020__INCLUDED_)
#define AFX_RSPRECOS_H__D2DC2437_7287_11D1_9F93_204C4F4F5020__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
/////////////////////////////////////////////////////////////////////////////
// CRSPrecos recordset

class CRSPrecos : public CRecordset
{
public:
	void EnableParameterization(void);
	CRSPrecos(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRSPrecos)

// Field/Param Data
	//{{AFX_FIELD(CRSPrecos, CRecordset)
	long	m_pr_Produto;
	CString	m_pr_Preco1;
	CString	m_pr_Preco2;
	CString	m_pr_Preco3;
	CString	m_pr_Preco4;
	CString	m_pr_Preco5;
	CString	m_pr_Preco6;
	CString	m_pr_Preco7;
	CString	m_pr_Preco8;
	int		m_pr_Tabela;
	CTime	m_pr_TimeStamp;
	CString	m_pr_Complemento;
	CString	m_pr_DescontoMaximo;
	BOOL	m_pr_Brinde;
	//}}AFX_FIELD
	long	m_parm_Produto;
	int		m_parm_Tabela;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSPrecos)
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

#endif // !defined(AFX_RSPRECOS_H__D2DC2437_7287_11D1_9F93_204C4F4F5020__INCLUDED_)
