// RSTitulosAlterados.cpp : implementation file
//
// $Archive: /PalmTrader 1/Server/RSTitulosAlterados.cpp $
// $Author: Flávio $
// $Date: 28/07/99 11:49 $
/* $History: RSTitulosAlterados.cpp $
 * 
 * *****************  Version 3  *****************
 * User: Flávio       Date: 28/07/99   Time: 11:49
 * Updated in $/PalmTrader 1/Server
 * Código reincorporado a $/PalmTrader 1/Server
 * 
 * *****************  Version 2  *****************
 * User: Flávio       Date: 28/07/99   Time: 10:58
 * Updated in $/QuickSell/Server
 * Cláusulas SQL JOIN alteradas para padrão compatível com MS-Access
 * 
 * *****************  Version 1  *****************
 * User: Flávio       Date: 24/07/98   Time: 14:16
 * Created in $/QuickSell/Server
 * Primeira implementação.
 * Suporte a sincronização automática do palmpc
 */

#include "stdafx.h"
#include "server.h"
#include "RSTitulosAlterados.h"
#include "Configuration.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSTitulosAlterados

IMPLEMENT_DYNAMIC(CRSTitulosAlterados, CRecordset)

CRSTitulosAlterados::CRSTitulosAlterados(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CRSTitulosAlterados)
	m_ti_Numero = _T("");
	m_ti_Cliente = 0;
	m_ti_Valor = _T("");
	m_ti_Emissao = _T("");
	m_ti_Vencimento = _T("");
	m_nFields = 6;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CRSTitulosAlterados::GetDefaultConnect()
{
	CConfiguration config;

	return config.GetDSN();
}

CString CRSTitulosAlterados::GetDefaultSQL()
{
	return _T(
		"SELECT "
			"ti_Numero,"
			"ti_Cliente,"
			"ti_Valor,"
			"ti_Emissao,"
			"ti_Vencimento,"
			"ti_TimeStamp "
		"FROM "
			"(Titulos INNER JOIN Clientes ON Titulos.ti_Cliente = Clientes.cl_Codigo) "
				"INNER JOIN Vendedores ON Clientes.cl_Vendedor = Vendedores.vd_Codigo"
		);
}

void CRSTitulosAlterados::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSTitulosAlterados)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[ti_Numero]"), m_ti_Numero);
	RFX_Long(pFX, _T("[ti_Cliente]"), m_ti_Cliente);
	RFX_Text(pFX, _T("[ti_Valor]"), m_ti_Valor);
	RFX_Text(pFX, _T("[ti_Emissao]"), m_ti_Emissao);
	RFX_Text(pFX, _T("[ti_Vencimento]"), m_ti_Vencimento);
	RFX_Date(pFX, _T("[ti_TimeStamp]"), m_ti_TimeStamp);
	//}}AFX_FIELD_MAP
	pFX->SetFieldType(CFieldExchange::param);
	RFX_Int(pFX, _T("m_parm_Vendedor"), m_parm_Vendedor);
	RFX_Date(pFX, _T("m_parm_UltimaAtualizacao"), m_parm_UltimaAtualizacao);
}

/////////////////////////////////////////////////////////////////////////////
// CRSTitulosAlterados diagnostics

#ifdef _DEBUG
void CRSTitulosAlterados::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSTitulosAlterados::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

BOOL CRSTitulosAlterados::Open(UINT nOpenType, LPCTSTR lpszSql, DWORD dwOptions) 
{
	m_nParams = 2;
	m_strFilter="vd_Codigo=? and ti_TimeStamp>=?";
	
	return CRecordset::Open(nOpenType, lpszSql, dwOptions);
}

void CRSTitulosAlterados::SetVendedor(int nVendedor)
{
	m_parm_Vendedor = nVendedor;
}

void CRSTitulosAlterados::SetUltimaAtualizacao(CTime timeUltimaAtualizacao)
{
	m_parm_UltimaAtualizacao = timeUltimaAtualizacao;
}
