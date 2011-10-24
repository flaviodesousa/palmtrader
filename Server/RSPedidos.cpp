// RSPedidos.cpp : implementation file
//
// $Archive: /QuickSell/Server/RSPedidos.cpp $
// $Author: Flávio $
// $Date: 21/07/98 17:39 $
/* $History: RSPedidos.cpp $
 * 
 * *****************  Version 4  *****************
 * User: Flávio       Date: 21/07/98   Time: 17:39
 * Updated in $/QuickSell/Server
 * Obtenção do DSN via classe CConfiguration
 * 
 * *****************  Version 3  *****************
 * User: Flávio       Date: 11/07/98   Time: 19:47
 * Updated in $/QuickSell/Server
 * Implementada rotina para localização de pedidos pelo número
 * 
 * *****************  Version 2  *****************
 * User: Flávio       Date: 7/04/98    Time: 5:56p
 * Updated in $/QuickSell/Server
 * Colocado em source control
 * Acrescentados campos para controle de reenvio de pedido.
 * Removidos campos espúrios
 */

#include "stdafx.h"
#include "Server.h"
#include "RSPedidos.h"
#include "Configuration.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSPedidos

IMPLEMENT_DYNAMIC(CRSPedidos, CRecordset)

CRSPedidos::CRSPedidos(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CRSPedidos)
	m_pe_Cliente = 0;
	m_pe_Cobranca = _T("");
	m_pe_CondicaoVenda = 0;
	m_pe_Diagnostico = _T("");
	m_pe_Numero = 0;
	m_pe_Plano = 0;
	m_pe_Reenviar = FALSE;
	m_pe_Vendedor = 0;
	m_nFields = 12;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CRSPedidos::GetDefaultConnect()
{
	CConfiguration config;
	return config.GetDSN();
}

CString CRSPedidos::GetDefaultSQL()
{
	return _T("[dbo].[Pedidos]");
}

void CRSPedidos::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSPedidos)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[pe_Cliente]"), m_pe_Cliente);
	RFX_Text(pFX, _T("[pe_Cobranca]"), m_pe_Cobranca);
	RFX_Byte(pFX, _T("[pe_CondicaoVenda]"), m_pe_CondicaoVenda);
	RFX_Date(pFX, _T("[pe_Data]"), m_pe_Data);
	RFX_Date(pFX, _T("[pe_Devolucao]"), m_pe_Devolucao);
	RFX_Text(pFX, _T("[pe_Diagnostico]"), m_pe_Diagnostico);
	RFX_Long(pFX, _T("[pe_Numero]"), m_pe_Numero);
	RFX_Byte(pFX, _T("[pe_Plano]"), m_pe_Plano);
	RFX_Date(pFX, _T("[pe_Processamento]"), m_pe_Processamento);
	RFX_Date(pFX, _T("[pe_Recepcao]"), m_pe_Recepcao);
	RFX_Bool(pFX, _T("[pe_Reenviar]"), m_pe_Reenviar);
	RFX_Int(pFX, _T("[pe_Vendedor]"), m_pe_Vendedor);
	//}}AFX_FIELD_MAP

	if (m_nParams)
	{
		pFX->SetFieldType( CFieldExchange::param );
		// RFX calls for parameter data members
		RFX_Long(pFX, _T("m_parm_Numero"), m_parm_Numero);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CRSPedidos diagnostics

#ifdef _DEBUG
void CRSPedidos::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSPedidos::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

void CRSPedidos::EnableParameterization()
{
	m_nParams = 1;
	m_strFilter = "pe_Numero=?";
}

BOOL CRSPedidos::Find(DWORD dwPedido)
{
	ASSERT(m_nParams == 1);
	m_parm_Numero = dwPedido;
	Requery();
	return !IsEOF();
}
