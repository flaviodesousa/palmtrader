// RSPrecosAlterados.cpp : implementation file
//
// $Archive: /PalmTrader 1/Server/RSPrecosAlterados.cpp $
// $Author: Flávio $
// $Date: 19/07/99 10:36 $
/* $History: RSPrecosAlterados.cpp $
 * 
 * *****************  Version 3  *****************
 * User: Flávio       Date: 19/07/99   Time: 10:36
 * Updated in $/PalmTrader 1/Server
 * Acesso à base de dados generalizado para permitir uso de tabelas Access
 * e outras
 * 
 * *****************  Version 1  *****************
 * User: Flávio       Date: 24/07/98   Time: 14:16
 * Created in $/QuickSell/Server
 * Primeira implementação.
 * Suporte a sincronização automática do palmpc
 */

#include "stdafx.h"
#include "server.h"
#include "RSPrecosAlterados.h"
#include "Configuration.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSPrecosAlterados

IMPLEMENT_DYNAMIC(CRSPrecosAlterados, CRecordset)

CRSPrecosAlterados::CRSPrecosAlterados(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CRSPrecosAlterados)
	m_pr_Tabela = 0;
	m_pr_Produto = 0;
	m_pr_Preco1 = _T("");
	m_pr_Preco2 = _T("");
	m_pr_Preco3 = _T("");
	m_pr_Preco4 = _T("");
	m_pr_Preco5 = _T("");
	m_pr_Preco6 = _T("");
	m_pr_Preco7 = _T("");
	m_pr_Preco8 = _T("");
	m_nFields = 11;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CRSPrecosAlterados::GetDefaultConnect()
{
	CConfiguration config;
	return config.GetDSN();
}

CString CRSPrecosAlterados::GetDefaultSQL()
{
	return _T("[Precos]");
}

void CRSPrecosAlterados::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSPrecosAlterados)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[pr_Tabela]"), m_pr_Tabela);
	RFX_Long(pFX, _T("[pr_Produto]"), m_pr_Produto);
	RFX_Text(pFX, _T("[pr_Preco1]"), m_pr_Preco1);
	RFX_Text(pFX, _T("[pr_Preco2]"), m_pr_Preco2);
	RFX_Text(pFX, _T("[pr_Preco3]"), m_pr_Preco3);
	RFX_Text(pFX, _T("[pr_Preco4]"), m_pr_Preco4);
	RFX_Text(pFX, _T("[pr_Preco5]"), m_pr_Preco5);
	RFX_Text(pFX, _T("[pr_Preco6]"), m_pr_Preco6);
	RFX_Text(pFX, _T("[pr_Preco7]"), m_pr_Preco7);
	RFX_Text(pFX, _T("[pr_Preco8]"), m_pr_Preco8);
	RFX_Date(pFX, _T("[pr_TimeStamp]"), m_pr_TimeStamp);
	//}}AFX_FIELD_MAP
	pFX->SetFieldType(CFieldExchange::param);
	RFX_Int(pFX, _T("m_parm_Tabela"), m_parm_nTabela);
	RFX_Date(pFX, _T("m_parm_TimeStamp"), m_parm_timeUltimaAtualizacao);
}

/////////////////////////////////////////////////////////////////////////////
// CRSPrecosAlterados diagnostics

#ifdef _DEBUG
void CRSPrecosAlterados::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSPrecosAlterados::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

void CRSPrecosAlterados::SetTabela(int nTabela)
{
	m_parm_nTabela = nTabela;
}

void CRSPrecosAlterados::SetUltimaAtualizacao(CTime timeUltimaAtualizacao)
{
	m_parm_timeUltimaAtualizacao = timeUltimaAtualizacao;
}

BOOL CRSPrecosAlterados::Open(UINT nOpenType, LPCTSTR lpszSql, DWORD dwOptions) 
{
	m_nParams = 2;
	m_strFilter = "pr_Tabela=? and pr_TimeStamp>=?";
	
	return CRecordset::Open(nOpenType, lpszSql, dwOptions);
}
