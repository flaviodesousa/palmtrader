// RSPedidosItens.h : header file
//
// $Archive: /QuickSell/Server/RSPedidosItens.h $
// $Author: Flávio $
// $Date: 7/04/98 6:06p $
/* $History: RSPedidosItens.h $
 * 
 * *****************  Version 2  *****************
 * User: Flávio       Date: 7/04/98    Time: 6:06p
 * Updated in $/QuickSell/Server
 * Colocado em source control
 */

#if !defined(AFX_RSPEDIDOSITENS_H__A2155548_73CD_11D1_9F95_204C4F4F5020__INCLUDED_)
#define AFX_RSPEDIDOSITENS_H__A2155548_73CD_11D1_9F95_204C4F4F5020__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
/////////////////////////////////////////////////////////////////////////////
// CRSPedidosItens recordset

class CRSPedidosItens : public CRecordset
{
public:
	BOOL Find(LONG pedido, LONG produto);
	void EnableParameterization(void);
	CRSPedidosItens(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRSPedidosItens)

// Field/Param Data
	//{{AFX_FIELD(CRSPedidosItens, CRecordset)
	long	m_pi_Pedido;
	long	m_pi_Produto;
	CString	m_pi_QuantidadePedida;
	CString	m_pi_QuantidadeAtendida;
	CString	m_pi_PrecoUnitario;
	//}}AFX_FIELD
	long	m_parm_Pedido;
	long	m_parm_Produto;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSPedidosItens)
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

#endif // !defined(AFX_RSPEDIDOSITENS_H__A2155548_73CD_11D1_9F95_204C4F4F5020__INCLUDED_)
