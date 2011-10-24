// RSPedidosItens.cpp : implementation file
//
// $Archive: /QuickSell/Server/RSPedidosItens.cpp $
// $Author: Flávio $
// $Date: 21/07/98 17:39 $
/* $History: RSPedidosItens.cpp $
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
#include "RSPedidosItens.h"
#include "Configuration.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSPedidosItens

IMPLEMENT_DYNAMIC(CRSPedidosItens, CRecordset)

CRSPedidosItens::CRSPedidosItens(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CRSPedidosItens)
	m_pi_Pedido = 0;
	m_pi_Produto = 0;
	m_pi_QuantidadePedida = _T("");
	m_pi_QuantidadeAtendida = _T("");
	m_pi_PrecoUnitario = _T("");
	m_nFields = 5;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CRSPedidosItens::GetDefaultConnect()
{
	CConfiguration config;
	return config.GetDSN();
}

CString CRSPedidosItens::GetDefaultSQL()
{
	return _T("[dbo].[PedidosItens]");
}

void CRSPedidosItens::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSPedidosItens)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[pi_Pedido]"), m_pi_Pedido);
	RFX_Long(pFX, _T("[pi_Produto]"), m_pi_Produto);
	RFX_Text(pFX, _T("[pi_QuantidadePedida]"), m_pi_QuantidadePedida);
	RFX_Text(pFX, _T("[pi_QuantidadeAtendida]"), m_pi_QuantidadeAtendida);
	RFX_Text(pFX, _T("[pi_PrecoUnitario]"), m_pi_PrecoUnitario);
	//}}AFX_FIELD_MAP

	if (m_nParams)
	{
		pFX->SetFieldType( CFieldExchange::param );
		// RFX calls for parameter data members
		RFX_Long(pFX, _T("m_parm_Pedido"), m_parm_Pedido);
		RFX_Long(pFX, _T("m_parm_Produto"), m_parm_Produto);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CRSPedidosItens diagnostics

#ifdef _DEBUG
void CRSPedidosItens::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSPedidosItens::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

void CRSPedidosItens::EnableParameterization()
{
	m_nParams = 2; // Pedido e Produto
	m_parm_Pedido = m_parm_Produto = 0;
	m_strFilter = "pi_Pedido=? AND pi_Produto=?";
}

BOOL CRSPedidosItens::Find(LONG pedido, LONG produto)
{
	ASSERT(m_nParams==2);
	m_parm_Pedido = pedido;
	m_parm_Produto = produto;
	Requery();
	return !IsEOF();
}
