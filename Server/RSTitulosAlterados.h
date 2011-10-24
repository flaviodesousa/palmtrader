// RSTitulosAlterados.h : header file
//
// $Archive: /QuickSell/Server/RSTitulosAlterados.h $
// $Author: Flávio $
// $Date: 24/07/98 14:16 $
/* $History: RSTitulosAlterados.h $
 * 
 * *****************  Version 1  *****************
 * User: Flávio       Date: 24/07/98   Time: 14:16
 * Created in $/QuickSell/Server
 * Primeira implementação.
 * Suporte a sincronização automática do palmpc
 */

#if !defined(AFX_RSTITULOSALTERADOS_H__316B54D7_22EC_11D2_BB62_0000216E2E31__INCLUDED_)
#define AFX_RSTITULOSALTERADOS_H__316B54D7_22EC_11D2_BB62_0000216E2E31__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CRSTitulosAlterados recordset

class CRSTitulosAlterados : public CRecordset
{
private:
	int m_parm_Vendedor;
	CTime m_parm_UltimaAtualizacao;
public:
	virtual void SetUltimaAtualizacao(CTime timeUltimaAtualizacao);
	virtual void SetVendedor(int nVendedor);
	CRSTitulosAlterados(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRSTitulosAlterados)

// Field/Param Data
	//{{AFX_FIELD(CRSTitulosAlterados, CRecordset)
	CString	m_ti_Numero;
	long	m_ti_Cliente;
	CString	m_ti_Valor;
	CString	m_ti_Emissao;
	CString	m_ti_Vencimento;
	CTime	m_ti_TimeStamp;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSTitulosAlterados)
	public:
	virtual CString GetDefaultConnect();    // Default connection string
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	virtual BOOL Open(UINT nOpenType = snapshot, LPCTSTR lpszSql = NULL, DWORD dwOptions = none);
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RSTITULOSALTERADOS_H__316B54D7_22EC_11D2_BB62_0000216E2E31__INCLUDED_)
