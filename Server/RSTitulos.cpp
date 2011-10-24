// RSTitulos.cpp : implementation file
//
// $Archive: /PalmTrader 1/Server/RSTitulos.cpp $
// $Author: Flávio $
// $Date: 19/07/99 10:36 $
/* $History: RSTitulos.cpp $
 * 
 * *****************  Version 5  *****************
 * User: Flávio       Date: 19/07/99   Time: 10:36
 * Updated in $/PalmTrader 1/Server
 * Acesso à base de dados generalizado para permitir uso de tabelas Access
 * e outras
 * 
 * *****************  Version 4  *****************
 * User: Flávio       Date: 21/07/98   Time: 17:39
 * Updated in $/QuickSell/Server
 * Obtenção do DSN via classe CConfiguration
 * 
 * *****************  Version 3  *****************
 * User: Flávio       Date: 11/07/98   Time: 19:47
 * Updated in $/QuickSell/Server
 * Incluído TimeStamp do título
 * 
 * *****************  Version 2  *****************
 * User: Flávio       Date: 7/04/98    Time: 5:58p
 * Updated in $/QuickSell/Server
 * Colocado em source control
 * Primeira implementação
 */

#include "stdafx.h"
#include "server.h"
#include "RSTitulos.h"
#include "Configuration.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSTitulos

IMPLEMENT_DYNAMIC(CRSTitulos, CRecordset)

CRSTitulos::CRSTitulos(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CRSTitulos)
	m_ti_Numero = _T("");
	m_ti_Cliente = 0;
	m_ti_Valor = _T("");
	m_ti_Emissao = _T("");
	m_ti_Vencimento = _T("");
	m_nFields = 6;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CRSTitulos::GetDefaultConnect()
{
	CConfiguration config;
	return config.GetDSN();
}

CString CRSTitulos::GetDefaultSQL()
{
	return _T("[Titulos]");
}

void CRSTitulos::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSTitulos)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[ti_Numero]"), m_ti_Numero);
	RFX_Long(pFX, _T("[ti_Cliente]"), m_ti_Cliente);
	RFX_Text(pFX, _T("[ti_Valor]"), m_ti_Valor);
	RFX_Text(pFX, _T("[ti_Emissao]"), m_ti_Emissao);
	RFX_Text(pFX, _T("[ti_Vencimento]"), m_ti_Vencimento);
	RFX_Date(pFX, _T("[ti_TimeStamp]"), m_ti_TimeStamp);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSTitulos diagnostics

#ifdef _DEBUG
void CRSTitulos::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSTitulos::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
