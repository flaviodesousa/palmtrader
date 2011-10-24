// RSProdutosAlterados.h : header file
//
// $Archive: /QuickSell/Server/RSProdutosAlterados.h $
// $Author: Flávio $
// $Date: 24/07/98 14:16 $
/* $History: RSProdutosAlterados.h $
 * 
 * *****************  Version 1  *****************
 * User: Flávio       Date: 24/07/98   Time: 14:16
 * Created in $/QuickSell/Server
 * Primeira implementação.
 * Suporte a sincronização automática do palmpc
 */

#if !defined(AFX_RSPRODUTOSALTERADOS_H__316B54D8_22EC_11D2_BB62_0000216E2E31__INCLUDED_)
#define AFX_RSPRODUTOSALTERADOS_H__316B54D8_22EC_11D2_BB62_0000216E2E31__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CRSProdutosAlterados recordset

class CRSProdutosAlterados : public CRecordset
{
public:
	virtual void SetUltimaAtualizacao(CTime timeUltimaAlteracao);
	CRSProdutosAlterados(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRSProdutosAlterados)

// Field/Param Data
	//{{AFX_FIELD(CRSProdutosAlterados, CRecordset)
	long	m_pd_Codigo;
	BYTE	m_pd_Digito;
	CString	m_pd_Descricao;
	CString	m_pd_Embalagem;
	CString	m_pd_Unidade;
	long	m_pd_Unidades;
	long	m_pd_EmbalagemMaster;
	CString	m_pd_PesoBruto;
	BOOL	m_pd_Disponivel;
	CTime	m_pd_TimeStamp;
	CTime	m_pd_DisponibilidadeTimeStamp;
	//}}AFX_FIELD
	CTime	m_parm_UltimaAtualizacao;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSProdutosAlterados)
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

#endif // !defined(AFX_RSPRODUTOSALTERADOS_H__316B54D8_22EC_11D2_BB62_0000216E2E31__INCLUDED_)
