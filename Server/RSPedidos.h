// RSPedidos.h : header file
//
// $Archive: /QuickSell/Server/RSPedidos.h $
// $Author: Flávio $
// $Date: 11/07/98 19:55 $
/* $History: RSPedidos.h $
 * 
 * *****************  Version 3  *****************
 * User: Flávio       Date: 11/07/98   Time: 19:55
 * Updated in $/QuickSell/Server
 * Implementado método para localização de pedidos pelo número
 * 
 * *****************  Version 2  *****************
 * User: Flávio       Date: 7/04/98    Time: 6:06p
 * Updated in $/QuickSell/Server
 * Colocado em source control
 * Incluídos campos para suporte a reenvio de pedidos
 * Excluídos campos espúrios
 */

#if !defined(AFX_RSPEDIDOS_H__A2155549_73CD_11D1_9F95_204C4F4F5020__INCLUDED_)
#define AFX_RSPEDIDOS_H__A2155549_73CD_11D1_9F95_204C4F4F5020__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
/////////////////////////////////////////////////////////////////////////////
// CRSPedidos recordset

class CRSPedidos : public CRecordset
{
public:
	BOOL Find(DWORD dwPedido);
	void EnableParameterization(void);
	CRSPedidos(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRSPedidos)

// Field/Param Data
	//{{AFX_FIELD(CRSPedidos, CRecordset)
	long	m_pe_Cliente;
	CString	m_pe_Cobranca;
	BYTE	m_pe_CondicaoVenda;
	CTime	m_pe_Data;
	CTime	m_pe_Devolucao;
	CString	m_pe_Diagnostico;
	long	m_pe_Numero;
	BYTE	m_pe_Plano;
	CTime	m_pe_Processamento;
	CTime	m_pe_Recepcao;
	BOOL	m_pe_Reenviar;
	int		m_pe_Vendedor;
	//}}AFX_FIELD
	long	m_parm_Numero;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSPedidos)
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

#endif // !defined(AFX_RSPEDIDOS_H__A2155549_73CD_11D1_9F95_204C4F4F5020__INCLUDED_)
