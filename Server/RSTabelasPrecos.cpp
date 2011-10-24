// RSTabelasPrecos.cpp : implementation file
//
// $Archive: /PalmTrader 1/Server/RSTabelasPrecos.cpp $
// $Author: Flávio $
// $Date: 19/07/99 10:36 $
/* $History: RSTabelasPrecos.cpp $
 * 
 * *****************  Version 6  *****************
 * User: Flávio       Date: 19/07/99   Time: 10:36
 * Updated in $/PalmTrader 1/Server
 * Acesso à base de dados generalizado para permitir uso de tabelas Access
 * e outras
 * 
 * *****************  Version 5  *****************
 * User: Flávio       Date: 21/07/98   Time: 17:39
 * Updated in $/QuickSell/Server
 * Obtenção do DSN via classe CConfiguration
 * 
 * *****************  Version 4  *****************
 * User: Flávio       Date: 7/04/98    Time: 5:58p
 * Updated in $/QuickSell/Server
 * Colocado em source control
 */

#include "stdafx.h"
#include "Server.h"
#include "RSTabelasPrecos.h"
#include "Configuration.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSTabelasPrecos

IMPLEMENT_DYNAMIC(CRSTabelasPrecos, CRecordset)

CRSTabelasPrecos::CRSTabelasPrecos(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CRSTabelasPrecos)
	m_tp_Codigo = 0;
	m_nFields = 1;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CRSTabelasPrecos::GetDefaultConnect()
{
	CConfiguration config;
	return config.GetDSN();
}

CString CRSTabelasPrecos::GetDefaultSQL()
{
	return _T("[TabelaPrecos]");
}

void CRSTabelasPrecos::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSTabelasPrecos)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[tp_Codigo]"), m_tp_Codigo);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSTabelasPrecos diagnostics

#ifdef _DEBUG
void CRSTabelasPrecos::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSTabelasPrecos::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
