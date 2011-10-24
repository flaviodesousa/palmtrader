// RSClientes.cpp : implementation file
//
// $Archive: /PalmTrader 1/Server/RSClientes.cpp $
// $Author: Flávio $
// $Date: 19/07/99 10:36 $
/* $History: RSClientes.cpp $
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
 * User: Flávio       Date: 11/07/98   Time: 19:46
 * Updated in $/QuickSell/Server
 * Implementada rotina para localização de clientes por código
 * 
 * *****************  Version 2  *****************
 * User: Flávio       Date: 7/02/98    Time: 4:37p
 * Updated in $/QuickSell/Server
 * Corrigido DSN;
 * Implantado acesso parametrizado;
 * Restituida lista de DDX.
 */

#include "stdafx.h"
#include "Server.h"
#include "RSClientes.h"
#include "Configuration.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSClientes

IMPLEMENT_DYNAMIC(CRSClientes, CRecordset)

CRSClientes::CRSClientes(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CRSClientes)
	m_cl_Codigo = 0;
	m_cl_Digito = 0;
	m_cl_CGC = _T("");
	m_cl_RazaoSocial = _T("");
	m_cl_Fantasia = _T("");
	m_cl_Contato = _T("");
	m_cl_EnderecoComercial = _T("");
	m_cl_EnderecoComercialBairro = _T("");
	m_cl_EnderecoComercialCidade = _T("");
	m_cl_EnderecoComercialEstado = _T("");
	m_cl_EnderecoComercialCEP = _T("");
	m_cl_EnderecoCobranca = _T("");
	m_cl_EnderecoCobrancaBairro = _T("");
	m_cl_EnderecoCobrancaCidade = _T("");
	m_cl_EnderecoCobrancaEstado = _T("");
	m_cl_EnderecoCobrancaCEP = _T("");
	m_cl_Telefone = _T("");
	m_cl_Fax = _T("");
	m_cl_RamoAtividade = 0;
	m_cl_Cobranca = _T("");
	m_cl_EmitirDuplicata = FALSE;
	m_cl_Vendedor = 0;
	m_cl_Praca = 0;
	m_cl_Limite = _T("");
	m_cl_ValorDisponivel = _T("");
	m_cl_Bloqueado = FALSE;
	m_cl_MotivoBloqueio = _T("");
	m_cl_Tabela = 0;
	m_nFields = 30;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
	m_nParams = 0;
	m_parm_Codigo = 0L;
}


CString CRSClientes::GetDefaultConnect()
{
	CConfiguration config;
	return config.GetDSN();
}

CString CRSClientes::GetDefaultSQL()
{
	return _T("[Clientes]");
}

void CRSClientes::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSClientes)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[cl_Codigo]"), m_cl_Codigo);
	RFX_Byte(pFX, _T("[cl_Digito]"), m_cl_Digito);
	RFX_Text(pFX, _T("[cl_CGC]"), m_cl_CGC);
	RFX_Text(pFX, _T("[cl_RazaoSocial]"), m_cl_RazaoSocial);
	RFX_Text(pFX, _T("[cl_Fantasia]"), m_cl_Fantasia);
	RFX_Text(pFX, _T("[cl_Contato]"), m_cl_Contato);
	RFX_Text(pFX, _T("[cl_EnderecoComercial]"), m_cl_EnderecoComercial);
	RFX_Text(pFX, _T("[cl_EnderecoComercialBairro]"), m_cl_EnderecoComercialBairro);
	RFX_Text(pFX, _T("[cl_EnderecoComercialCidade]"), m_cl_EnderecoComercialCidade);
	RFX_Text(pFX, _T("[cl_EnderecoComercialEstado]"), m_cl_EnderecoComercialEstado);
	RFX_Text(pFX, _T("[cl_EnderecoComercialCEP]"), m_cl_EnderecoComercialCEP);
	RFX_Text(pFX, _T("[cl_EnderecoCobranca]"), m_cl_EnderecoCobranca);
	RFX_Text(pFX, _T("[cl_EnderecoCobrancaBairro]"), m_cl_EnderecoCobrancaBairro);
	RFX_Text(pFX, _T("[cl_EnderecoCobrancaCidade]"), m_cl_EnderecoCobrancaCidade);
	RFX_Text(pFX, _T("[cl_EnderecoCobrancaEstado]"), m_cl_EnderecoCobrancaEstado);
	RFX_Text(pFX, _T("[cl_EnderecoCobrancaCEP]"), m_cl_EnderecoCobrancaCEP);
	RFX_Text(pFX, _T("[cl_Telefone]"), m_cl_Telefone);
	RFX_Text(pFX, _T("[cl_Fax]"), m_cl_Fax);
	RFX_Byte(pFX, _T("[cl_RamoAtividade]"), m_cl_RamoAtividade);
	RFX_Text(pFX, _T("[cl_Cobranca]"), m_cl_Cobranca);
	RFX_Bool(pFX, _T("[cl_EmitirDuplicata]"), m_cl_EmitirDuplicata);
	RFX_Int(pFX, _T("[cl_Vendedor]"), m_cl_Vendedor);
	RFX_Int(pFX, _T("[cl_Praca]"), m_cl_Praca);
	RFX_Text(pFX, _T("[cl_Limite]"), m_cl_Limite);
	RFX_Text(pFX, _T("[cl_ValorDisponivel]"), m_cl_ValorDisponivel);
	RFX_Bool(pFX, _T("[cl_Bloqueado]"), m_cl_Bloqueado);
	RFX_Text(pFX, _T("[cl_MotivoBloqueio]"), m_cl_MotivoBloqueio);
	RFX_Date(pFX, _T("[cl_TimeStamp]"), m_cl_TimeStamp);
	RFX_Date(pFX, _T("[cl_LimiteTimeStamp]"), m_cl_LimiteTimeStamp);
	RFX_Int(pFX, _T("[cl_Tabela]"), m_cl_Tabela);
	//}}AFX_FIELD_MAP

	if (m_nParams)
	{
		pFX->SetFieldType( CFieldExchange::param );
		// RFX calls for parameter data members
		RFX_Long(pFX, _T("m_parm_Codigo"), m_parm_Codigo);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CRSClientes diagnostics

#ifdef _DEBUG
void CRSClientes::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSClientes::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

void CRSClientes::EnableParameterization()
{
	m_strFilter = "cl_Codigo=?";
	m_nParams = 1;
}

BOOL CRSClientes::Find(DWORD dwCodigo)
{
	ASSERT(m_nParams == 1);
	m_parm_Codigo = dwCodigo;
	Requery();
	return !IsEOF();
}
