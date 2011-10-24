// RSVendedores.h : header file
//
// $Archive: /QuickSell/Server/RSVendedores.h $
// $Author: Flávio $
// $Date: 7/04/98 6:09p $
/* $History: RSVendedores.h $
 * 
 * *****************  Version 2  *****************
 * User: Flávio       Date: 7/04/98    Time: 6:09p
 * Updated in $/QuickSell/Server
 * Colocado em source control
 */

#if !defined(AFX_RSVENDEDORES_H__D2DC2436_7287_11D1_9F93_204C4F4F5020__INCLUDED_)
#define AFX_RSVENDEDORES_H__D2DC2436_7287_11D1_9F93_204C4F4F5020__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
/////////////////////////////////////////////////////////////////////////////
// CRSVendedores recordset

class CRSVendedores : public CRecordset
{
public:
	void EnableParameterization(void);
	CRSVendedores(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRSVendedores)

// Field/Param Data
	//{{AFX_FIELD(CRSVendedores, CRecordset)
	int		m_vd_Codigo;
	CString	m_vd_Nome;
	CString	m_vd_Senha;
	CTime	m_vd_UltimaAtualizacao;
	int		m_vd_TabelaPrecos;
	//}}AFX_FIELD
    int     m_parm_Codigo;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSVendedores)
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

#endif // !defined(AFX_RSVENDEDORES_H__D2DC2436_7287_11D1_9F93_204C4F4F5020__INCLUDED_)
