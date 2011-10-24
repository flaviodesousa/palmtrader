// RSBlocos.cpp : implementation file
//
// $Archive: /PalmTrader 1/Server/RSBlocos.cpp $
// $Author: Flávio $
// $Date: 19/07/99 10:36 $
/* $History: RSBlocos.cpp $
 * 
 * *****************  Version 3  *****************
 * User: Flávio       Date: 19/07/99   Time: 10:36
 * Updated in $/PalmTrader 1/Server
 * Acesso à base de dados generalizado para permitir uso de tabelas Access
 * e outras
 * 
 * *****************  Version 2  *****************
 * User: Flávio       Date: 21/07/98   Time: 17:39
 * Updated in $/QuickSell/Server
 * Obtenção do DSN via classe CConfiguration
 */

#include "stdafx.h"
#include "RSBlocos.h"
#include "Configuration.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSBlocos

IMPLEMENT_DYNAMIC(CRSBlocos, CRecordset)

CRSBlocos::CRSBlocos(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CRSBlocos)
	m_PrimeiroPedido = 0;
	m_UltimoPedido = 0;
	m_Vendedor = 0;
	m_BlocoAberto = FALSE;
	m_nFields = 5;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CRSBlocos::GetDefaultConnect()
{
	CConfiguration config;
	return config.GetDSN();
}

CString CRSBlocos::GetDefaultSQL()
{
	return _T("[Blocos]");
}

void CRSBlocos::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSBlocos)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[PrimeiroPedido]"), m_PrimeiroPedido);
	RFX_Long(pFX, _T("[UltimoPedido]"), m_UltimoPedido);
	RFX_Date(pFX, _T("[Entrega]"), m_Entrega);
	RFX_Int(pFX, _T("[Vendedor]"), m_Vendedor);
	RFX_Bool(pFX, _T("[BlocoAberto]"), m_BlocoAberto);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSBlocos diagnostics

#ifdef _DEBUG
void CRSBlocos::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSBlocos::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
