// RSSessoes.cpp : implementation file
//
// $Archive: /PalmTrader 1/Server/RSSessoes.cpp $
// $Author: Flávio $
// $Date: 19/07/99 10:36 $
/* $History: RSSessoes.cpp $
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
 * User: Flávio       Date: 6/06/98    Time: 3:12p
 * Updated in $/QuickSell/Server
 * Connection string corrigida
 */

#include "stdafx.h"
#include "Server.h"
#include "RSSessoes.h"
#include "Configuration.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSSessoes

IMPLEMENT_DYNAMIC(CRSSessoes, CRecordset)

CRSSessoes::CRSSessoes(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CRSSessoes)
	m_ss_Vendedor = 0;
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CRSSessoes::GetDefaultConnect()
{
	CConfiguration config;
	return config.GetDSN();
}

CString CRSSessoes::GetDefaultSQL()
{
	return _T("[Sessoes]");
}

void CRSSessoes::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSSessoes)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[ss_Vendedor]"), m_ss_Vendedor);
	RFX_Date(pFX, _T("[ss_Inicio]"), m_ss_Inicio);
	RFX_Date(pFX, _T("[ss_final]"), m_ss_final);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSSessoes diagnostics

#ifdef _DEBUG
void CRSSessoes::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSSessoes::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
