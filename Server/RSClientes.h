// RSClientes.h : header file
//
// $Archive: /QuickSell/Server/RSClientes.h $
// $Author: Flávio $
// $Date: 11/07/98 19:54 $
/* $History: RSClientes.h $
 * 
 * *****************  Version 3  *****************
 * User: Flávio       Date: 11/07/98   Time: 19:54
 * Updated in $/QuickSell/Server
 * Implementado método para localização de clientes pelo código
 * 
 * *****************  Version 2  *****************
 * User: Flávio       Date: 7/04/98    Time: 6:05p
 * Updated in $/QuickSell/Server
 * Colocado em source control
 */

#if !defined(AFX_RSCLIENTES_H__A1CC45A4_F219_11D0_A104_00004403E294__INCLUDED_)
#define AFX_RSCLIENTES_H__A1CC45A4_F219_11D0_A104_00004403E294__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
/////////////////////////////////////////////////////////////////////////////
// CRSClientes recordset

class CRSClientes : public CRecordset
{
public:
	BOOL Find(DWORD dwCodigo);
	void EnableParameterization(void);
	CRSClientes(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRSClientes)

// Field/Param Data
	//{{AFX_FIELD(CRSClientes, CRecordset)
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
	long	m_parm_Codigo; // Parametro

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSClientes)
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

#endif // !defined(AFX_RSCLIENTES_H__A1CC45A4_F219_11D0_A104_00004403E294__INCLUDED_)
