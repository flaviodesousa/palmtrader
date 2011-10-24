// RSTitulosPorVendedor.cpp : implementation file
//
// $Archive: /PalmTrader 1/Server/RSTitulosPorVendedor.cpp $
// $Author: Flávio $
// $Date: 28/07/99 11:49 $
/* $History: RSTitulosPorVendedor.cpp $
 * 
 * *****************  Version 4  *****************
 * User: Flávio       Date: 28/07/99   Time: 11:49
 * Updated in $/PalmTrader 1/Server
 * Código reincorporado a $/PalmTrader 1/Server
 * 
 * *****************  Version 4  *****************
 * User: Flávio       Date: 28/07/99   Time: 10:58
 * Updated in $/QuickSell/Server
 * Cláusulas SQL JOIN alteradas para padrão compatível com MS-Access
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
 * Primeira implementação
 */

#include "stdafx.h"
#include "server.h"
#include "RSTitulosPorVendedor.h"
#include "Configuration.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSTitulosPorVendedor

IMPLEMENT_DYNAMIC(CRSTitulosPorVendedor, CRecordset)

CRSTitulosPorVendedor::CRSTitulosPorVendedor(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CRSTitulosPorVendedor)
	m_ti_Numero = _T("");
	m_ti_Cliente = 0;
	m_ti_Valor = _T("");
	m_ti_Emissao = _T("");
	m_ti_Vencimento = _T("");
	m_nFields = 5;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CRSTitulosPorVendedor::GetDefaultConnect()
{
	CConfiguration config;
	return config.GetDSN();
}

CString CRSTitulosPorVendedor::GetDefaultSQL()
{
	//return _T("[dbo].[Titulos]");
    return _T(
		"SELECT "
			"ti_Numero,"
			"ti_Cliente,"
			"ti_Valor,"
			"ti_Emissao,"
			"ti_Vencimento "
		"FROM "
			"(Titulos INNER JOIN Clientes ON Titulos.ti_Cliente = Clientes.cl_Codigo) "
				"INNER JOIN Vendedores ON Clientes.cl_Vendedor = Vendedores.vd_Codigo"
        );
}

void CRSTitulosPorVendedor::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSTitulosPorVendedor)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[ti_Numero]"), m_ti_Numero);
	RFX_Long(pFX, _T("[ti_Cliente]"), m_ti_Cliente);
	RFX_Text(pFX, _T("[ti_Valor]"), m_ti_Valor);
	RFX_Text(pFX, _T("[ti_Emissao]"), m_ti_Emissao);
	RFX_Text(pFX, _T("[ti_Vencimento]"), m_ti_Vencimento);
	//}}AFX_FIELD_MAP

	if (m_nParams)
	{
		pFX->SetFieldType( CFieldExchange::param );
		// RFX calls for parameter data members
		RFX_Int(pFX, _T("m_parm_Vendedor"), m_parm_Vendedor);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CRSTitulosPorVendedor diagnostics

#ifdef _DEBUG
void CRSTitulosPorVendedor::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSTitulosPorVendedor::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

void CRSTitulosPorVendedor::EnableParameterization()
{
	m_nParams = 1;
	m_parm_Vendedor = 0;
	m_strFilter = "cl_Vendedor=?";
}
