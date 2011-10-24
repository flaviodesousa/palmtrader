// RSClientesAlterados.h : header file
//
// $Archive: /QuickSell/Server/RSClientesAlterados.h $
// $Author: Flávio $
// $Date: 24/07/98 14:16 $
/* $History: RSClientesAlterados.h $
 * 
 * *****************  Version 1  *****************
 * User: Flávio       Date: 24/07/98   Time: 14:16
 * Created in $/QuickSell/Server
 * Primeira implementação.
 * Suporte a sincronização automática do palmpc
 */

#if !defined(AFX_RSCLIENTESALTERADOS_H__316B54D9_22EC_11D2_BB62_0000216E2E31__INCLUDED_)
#define AFX_RSCLIENTESALTERADOS_H__316B54D9_22EC_11D2_BB62_0000216E2E31__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CRSClientesAlterados recordset

class CRSClientesAlterados : public CRecordset
{
public:
	virtual void SetVendedor(int nVendedor);
	virtual void SetUltimaAtualizacao(CTime timeUltimaAtualizacao);
	CRSClientesAlterados(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRSClientesAlterados)

// Field/Param Data
	//{{AFX_FIELD(CRSClientesAlterados, CRecordset)
	long	m_cl_Codigo;
	BYTE	m_cl_Digito;
	CString	m_cl_CGC;
	CString	m_cl_RazaoSocial;
	CString	m_cl_Fantasia;
	CString	m_cl_Contato;
	CString	m_cl_EnderecoComercial;
	CString	m_cl_EnderecoComercialBairro;
	CString	m_cl_EnderecoComercialCidade;
	CString	m_cl_EnderecoComercialEstado;
	CString	m_cl_EnderecoComercialCEP;
	CString	m_cl_EnderecoCobranca;
	CString	m_cl_EnderecoCobrancaBairro;
	CString	m_cl_EnderecoCobrancaCidade;
	CString	m_cl_EnderecoCobrancaEstado;
	CString	m_cl_EnderecoCobrancaCEP;
	CString	m_cl_Telefone;
	CString	m_cl_Fax;
	BYTE	m_cl_RamoAtividade;
	CString	m_cl_Cobranca;
	BOOL	m_cl_EmitirDuplicata;
	int		m_cl_Vendedor;
	int		m_cl_Praca;
	CString	m_cl_Limite;
	CString	m_cl_ValorDisponivel;
	BOOL	m_cl_Bloqueado;
	CString	m_cl_MotivoBloqueio;
	CTime	m_cl_TimeStamp;
	CTime	m_cl_LimiteTimeStamp;
	int		m_cl_Tabela;
	//}}AFX_FIELD
	int		m_parm_Vendedor;
	CTime	m_parm_UltimaAtualizacao;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSClientesAlterados)
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

#endif // !defined(AFX_RSCLIENTESALTERADOS_H__316B54D9_22EC_11D2_BB62_0000216E2E31__INCLUDED_)
