// RSPlanos.cpp : implementation file
//
// $Archive: /PalmTrader 1/Server/RSPlanos.cpp $
// $Author: Flávio $
// $Date: 19/07/99 10:36 $
/* $History: RSPlanos.cpp $
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
 * User: Flávio       Date: 7/04/98    Time: 5:55p
 * Updated in $/QuickSell/Server
 * Colocado em source control
 */

#include "stdafx.h"
#include "RSPlanos.h"
#include "Configuration.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSPlanos

IMPLEMENT_DYNAMIC(CRSPlanos, CRecordset)

CRSPlanos::CRSPlanos(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CRSPlanos)
	m_pl_Codigo = 0;
	m_pl_Descricao = _T("");
	m_pl_ColunaPreco = 0;
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CRSPlanos::GetDefaultConnect()
{
	CConfiguration config;
	return config.GetDSN();
}

CString CRSPlanos::GetDefaultSQL()
{
	return _T("[Planos]");
}

void CRSPlanos::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSPlanos)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Byte(pFX, _T("[pl_Codigo]"), m_pl_Codigo);
	RFX_Text(pFX, _T("[pl_Descricao]"), m_pl_Descricao);
	RFX_Byte(pFX, _T("[pl_ColunaPreco]"), m_pl_ColunaPreco);
	RFX_Date(pFX, _T("[pl_TimeStamp]"), m_pl_TimeStamp);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSPlanos diagnostics

#ifdef _DEBUG
void CRSPlanos::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSPlanos::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
