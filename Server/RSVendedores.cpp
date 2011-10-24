// RSVendedores.cpp : implementation file
//
// $Archive: /PalmTrader 1/Server/RSVendedores.cpp $
// $Author: Flávio $
// $Date: 19/07/99 10:36 $
/* $History: RSVendedores.cpp $
 * 
 * *****************  Version 4  *****************
 * User: Flávio       Date: 19/07/99   Time: 10:36
 * Updated in $/PalmTrader 1/Server
 * Acesso à base de dados generalizado para permitir uso de tabelas Access
 * e outras
 * 
 * *****************  Version 3  *****************
 * User: Flávio       Date: 21/07/98   Time: 17:39
 * Updated in $/QuickSell/Server
 * Obtenção do DSN via classe CConfiguration
 * 
 * *****************  Version 2  *****************
 * User: Flávio       Date: 7/04/98    Time: 5:59p
 * Updated in $/QuickSell/Server
 * Colocado em source control
 */

#include "stdafx.h"
#include "RSVendedores.h"
#include "Configuration.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSVendedores

IMPLEMENT_DYNAMIC(CRSVendedores, CRecordset)

CRSVendedores::CRSVendedores(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CRSVendedores)
	m_vd_Codigo = 0;
	m_vd_Nome = _T("");
	m_vd_Senha = _T("");
	m_vd_TabelaPrecos = 0;
	m_nFields = 5;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
	m_nParams = 0;
	m_parm_Codigo = 0;
}


CString CRSVendedores::GetDefaultConnect()
{
	CConfiguration config;
	return config.GetDSN();
}

CString CRSVendedores::GetDefaultSQL()
{
	return _T("[Vendedores]");
}

void CRSVendedores::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSVendedores)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[vd_Codigo]"), m_vd_Codigo);
	RFX_Text(pFX, _T("[vd_Nome]"), m_vd_Nome);
	RFX_Text(pFX, _T("[vd_Senha]"), m_vd_Senha);
	RFX_Date(pFX, _T("[vd_UltimaAtualizacao]"), m_vd_UltimaAtualizacao);
	RFX_Int(pFX, _T("[vd_TabelaPrecos]"), m_vd_TabelaPrecos);
	//}}AFX_FIELD_MAP

	if (m_nParams)
	{
		pFX->SetFieldType( CFieldExchange::param );
		// RFX calls for parameter data members
		RFX_Int(pFX, _T("m_parm_Codigo"), m_parm_Codigo);
	}}

/////////////////////////////////////////////////////////////////////////////
// CRSVendedores diagnostics

#ifdef _DEBUG
void CRSVendedores::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSVendedores::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

void CRSVendedores::EnableParameterization()
{
	m_strFilter = "vd_Codigo=?";
	m_nParams = 1;
}
