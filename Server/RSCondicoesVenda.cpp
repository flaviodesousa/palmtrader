// RSCondicoesVenda.cpp : implementation file
//
// $Archive: /PalmTrader 1/Server/RSCondicoesVenda.cpp $
// $Author: Flávio $
// $Date: 19/07/99 10:36 $
/* $History: RSCondicoesVenda.cpp $
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
#include "Server.h"
#include "RSCondicoesVenda.h"
#include "Configuration.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSCondicoesVenda

IMPLEMENT_DYNAMIC(CRSCondicoesVenda, CRecordset)

CRSCondicoesVenda::CRSCondicoesVenda(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CRSCondicoesVenda)
	m_cv_Codigo = 0;
	m_cv_PedePercentual = FALSE;
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CRSCondicoesVenda::GetDefaultConnect()
{
	CConfiguration config;
	return config.GetDSN();
}

CString CRSCondicoesVenda::GetDefaultSQL()
{
	return _T("[CondicoesVenda]");
}

void CRSCondicoesVenda::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSCondicoesVenda)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Byte(pFX, _T("[cv_Codigo]"), m_cv_Codigo);
	RFX_Bool(pFX, _T("[cv_PedePercentual]"), m_cv_PedePercentual);
	RFX_Binary(pFX, _T("[cv_TimeStamp]"), m_cv_TimeStamp);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSCondicoesVenda diagnostics

#ifdef _DEBUG
void CRSCondicoesVenda::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSCondicoesVenda::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
