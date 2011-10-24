// RSProdutos.cpp : implementation file
//
// $Archive: /PalmTrader 1/Server/RSProdutos.cpp $
// $Author: Flávio $
// $Date: 19/07/99 10:36 $
/* $History: RSProdutos.cpp $
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
 * User: Flávio       Date: 7/04/98    Time: 5:57p
 * Updated in $/QuickSell/Server
 * Colocado em source control
 * Acrescentados campos informativos
 */

#include "stdafx.h"
#include "Server.h"
#include "RSProdutos.h"
#include "Configuration.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSProdutos

IMPLEMENT_DYNAMIC(CRSProdutos, CRecordset)

CRSProdutos::CRSProdutos(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CRSProdutos)
	m_pd_Codigo = 0;
	m_pd_Digito = 0;
	m_pd_Descricao = _T("");
	m_pd_Embalagem = _T("");
	m_pd_Unidade = _T("");
	m_pd_Unidades = 0;
	m_pd_EmbalagemMaster = 0;
	m_pd_PesoBruto = _T("");
	m_pd_Disponivel = FALSE;
	m_nFields = 11;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
	m_nParams = 0;
	m_parm_Codigo = 0L;
}


CString CRSProdutos::GetDefaultConnect()
{
	CConfiguration config;
	return config.GetDSN();
}

CString CRSProdutos::GetDefaultSQL()
{
	return _T("[Produtos]");
}

void CRSProdutos::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSProdutos)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[pd_Codigo]"), m_pd_Codigo);
	RFX_Byte(pFX, _T("[pd_Digito]"), m_pd_Digito);
	RFX_Text(pFX, _T("[pd_Descricao]"), m_pd_Descricao);
	RFX_Text(pFX, _T("[pd_Embalagem]"), m_pd_Embalagem);
	RFX_Text(pFX, _T("[pd_Unidade]"), m_pd_Unidade);
	RFX_Long(pFX, _T("[pd_Unidades]"), m_pd_Unidades);
	RFX_Long(pFX, _T("[pd_EmbalagemMaster]"), m_pd_EmbalagemMaster);
	RFX_Text(pFX, _T("[pd_PesoBruto]"), m_pd_PesoBruto);
	RFX_Bool(pFX, _T("[pd_Disponivel]"), m_pd_Disponivel);
	RFX_Date(pFX, _T("[pd_TimeStamp]"), m_pd_TimeStamp);
	RFX_Date(pFX, _T("[pd_DisponibilidadeTimeStamp]"), m_pd_DisponibilidadeTimeStamp);
	//}}AFX_FIELD_MAP

	if (m_nParams)
	{
		pFX->SetFieldType( CFieldExchange::param );
		// RFX calls for parameter data members
		RFX_Long(pFX, _T("m_parm_Codigo"), m_parm_Codigo);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CRSProdutos diagnostics

#ifdef _DEBUG
void CRSProdutos::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSProdutos::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

void CRSProdutos::EnableParameterization()
{
	m_strFilter = "pd_Codigo=?";
	m_nParams = 1;
}
