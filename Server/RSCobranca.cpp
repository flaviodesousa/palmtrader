// RSCobranca.cpp : implementation file
//
// $Archive: /PalmTrader 1/Server/RSCobranca.cpp $
// $Author: Flávio $
// $Date: 19/07/99 10:36 $
/* $History: RSCobranca.cpp $
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
 * User: Flávio       Date: 7/02/98    Time: 4:37p
 * Updated in $/QuickSell/Server
 * Implementação local
 */

#include "stdafx.h"
#include "Server.h"
#include "RSCobranca.h"
#include "Configuration.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSCobranca

IMPLEMENT_DYNAMIC(CRSCobranca, CRecordset)

CRSCobranca::CRSCobranca(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CRSCobranca)
	m_cb_Codigo = _T("");
	m_cb_Descricao = _T("");
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CRSCobranca::GetDefaultConnect()
{
	CConfiguration config;
	return config.GetDSN();
}

CString CRSCobranca::GetDefaultSQL()
{
	return _T("[Cobranca]");
}

void CRSCobranca::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSCobranca)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[cb_Codigo]"), m_cb_Codigo);
	RFX_Text(pFX, _T("[cb_Descricao]"), m_cb_Descricao);
	RFX_Date(pFX, _T("[cb_TimeStamp]"), m_cb_TimeStamp);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSCobranca diagnostics

#ifdef _DEBUG
void CRSCobranca::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSCobranca::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
