// RSPrecosAlterados.h : header file
//
// $Archive: /QuickSell/Server/RSPrecosAlterados.h $
// $Author: Flávio $
// $Date: 24/07/98 14:16 $
/* $History: RSPrecosAlterados.h $
 * 
 * *****************  Version 1  *****************
 * User: Flávio       Date: 24/07/98   Time: 14:16
 * Created in $/QuickSell/Server
 * Primeira implementação.
 * Suporte a sincronização automática do palmpc
 */

#if !defined(AFX_RSPRECOSALTERADOS_H__316B54D6_22EC_11D2_BB62_0000216E2E31__INCLUDED_)
#define AFX_RSPRECOSALTERADOS_H__316B54D6_22EC_11D2_BB62_0000216E2E31__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CRSPrecosAlterados recordset

class CRSPrecosAlterados : public CRecordset
{
protected:
	int	m_parm_nTabela;
	CTime m_parm_timeUltimaAtualizacao;
public:
	virtual void SetUltimaAtualizacao(CTime timeUltimaAtualizacao);
	virtual void SetTabela(int nTabela);
	CRSPrecosAlterados(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRSPrecosAlterados)

// Field/Param Data
	//{{AFX_FIELD(CRSPrecosAlterados, CRecordset)
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
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSPrecosAlterados)
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

#endif // !defined(AFX_RSPRECOSALTERADOS_H__316B54D6_22EC_11D2_BB62_0000216E2E31__INCLUDED_)
