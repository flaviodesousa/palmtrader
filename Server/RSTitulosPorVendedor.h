// RSTitulosPorVendedor.h : header file
//
// $Archive: /QuickSell/Server/RSTitulosPorVendedor.h $
// $Author: Flávio $
// $Date: 7/04/98 6:09p $
/* $History: RSTitulosPorVendedor.h $
 * 
 * *****************  Version 2  *****************
 * User: Flávio       Date: 7/04/98    Time: 6:09p
 * Updated in $/QuickSell/Server
 * Colocado em source control
 * Primeira implementação
 */

#if !defined(AFX_RSTITULOSPORVENDEDOR_H__81EBA834_F29E_11D0_A107_00004403E294__INCLUDED_)
#define AFX_RSTITULOSPORVENDEDOR_H__81EBA834_F29E_11D0_A107_00004403E294__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
/////////////////////////////////////////////////////////////////////////////
// CRSTitulosPorVendedor recordset

class CRSTitulosPorVendedor : public CRecordset
{
public:
	void EnableParameterization(void);
	CRSTitulosPorVendedor(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRSTitulosPorVendedor)

// Field/Param Data
	//{{AFX_FIELD(CRSTitulosPorVendedor, CRecordset)
	CString	m_ti_Numero;
	long	m_ti_Cliente;
	CString	m_ti_Valor;
	CString	m_ti_Emissao;
	CString	m_ti_Vencimento;
	//}}AFX_FIELD
    int     m_parm_Vendedor;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSTitulosPorVendedor)
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

#endif // !defined(AFX_RSTITULOSPORVENDEDOR_H__81EBA834_F29E_11D0_A107_00004403E294__INCLUDED_)
