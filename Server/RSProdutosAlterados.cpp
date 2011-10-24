// RSProdutosAlterados.cpp : implementation file
//
// $Archive: /PalmTrader 1/Server/RSProdutosAlterados.cpp $
// $Author: Flávio $
// $Date: 19/07/99 10:36 $
/* $History: RSProdutosAlterados.cpp $
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
#include "RSProdutosAlterados.h"
#include "Configuration.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSProdutosAlterados

IMPLEMENT_DYNAMIC(CRSProdutosAlterados, CRecordset)

CRSProdutosAlterados::CRSProdutosAlterados(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CRSProdutosAlterados)
	m_pd_Codigo = 0;
	m_pd_Digito = 0;
	m_pd_Descricao = _T("");
	m_pd_Embalagem = _T("");
	m_pd_Unidade = _T("");
	m_pd_Unidades = 0;
	m_pd_EmbalagemMaster = 0;
	m_pd_PesoBruto = _T("");
	m_pd_Disponivel = FALSE;
	m_nFields = 11;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CRSProdutosAlterados::GetDefaultConnect()
{
	CConfiguration config;
	return config.GetDSN();
}

CString CRSProdutosAlterados::GetDefaultSQL()
{
	return _T("[Produtos]");
}

void CRSProdutosAlterados::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSProdutosAlterados)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[pd_Codigo]"), m_pd_Codigo);
	RFX_Byte(pFX, _T("[pd_Digito]"), m_pd_Digito);
	RFX_Text(pFX, _T("[pd_Descricao]"), m_pd_Descricao);
	RFX_Text(pFX, _T("[pd_Embalagem]"), m_pd_Embalagem);
	RFX_Text(pFX, _T("[pd_Unidade]"), m_pd_Unidade);
	RFX_Long(pFX, _T("[pd_Unidades]"), m_pd_Unidades);
	RFX_Long(pFX, _T("[pd_EmbalagemMaster]"), m_pd_EmbalagemMaster);
	RFX_Text(pFX, _T("[pd_PesoBruto]"), m_pd_PesoBruto);
	RFX_Bool(pFX, _T("[pd_Disponivel]"), m_pd_Disponivel);
	RFX_Date(pFX, _T("[pd_TimeStamp]"), m_pd_TimeStamp);
	RFX_Date(pFX, _T("[pd_DisponibilidadeTimeStamp]"), m_pd_DisponibilidadeTimeStamp);
	//}}AFX_FIELD_MAP
	pFX->SetFieldType(CFieldExchange::param);
	RFX_Date(pFX, _T("m_parm_UltimaAtualizacao"), m_parm_UltimaAtualizacao);
	RFX_Date(pFX, _T("m_parm_UltimaAtualizacaoDisponibilidade"), m_parm_UltimaAtualizacao);
}

/////////////////////////////////////////////////////////////////////////////
// CRSProdutosAlterados diagnostics

#ifdef _DEBUG
void CRSProdutosAlterados::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSProdutosAlterados::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

BOOL CRSProdutosAlterados::Open(UINT nOpenType, LPCTSTR lpszSql, DWORD dwOptions) 
{
	m_nParams = 2;
	m_strFilter = "pd_TimeStamp>=? OR pd_DisponibilidadeTimeStamp>=?";
	
	return CRecordset::Open(nOpenType, lpszSql, dwOptions);
}

void CRSProdutosAlterados::SetUltimaAtualizacao(CTime timeUltimaAtualizacao)
{
	m_parm_UltimaAtualizacao = timeUltimaAtualizacao;
}
