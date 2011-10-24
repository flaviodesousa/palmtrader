// RSClientesAlterados.cpp : implementation file
//
// $Archive: /PalmTrader 1/Server/RSClientesAlterados.cpp $
// $Author: Fl�vio $
// $Date: 19/07/99 10:36 $
/* $History: RSClientesAlterados.cpp $
 * 
 * *****************  Version 4  *****************
 * User: Fl�vio       Date: 19/07/99   Time: 10:36
 * Updated in $/PalmTrader 1/Server
 * Acesso � base de dados generalizado para permitir uso de tabelas Access
 * e outras
 * 
 * *****************  Version 2  *****************
 * User: Fl�vio       Date: 15/09/98   Time: 12:35
 * Updated in $/QuickSell/Server
 * Pedidos n�o mais registrados no servidor SQL, armazenados agora em
 * mem�ria para agilizar o processamento.
 * Simplificado o processo de localiza��o de clientes alterados via
 * timestamp.
 * Removido suporte a grava��o de pedidos.
 * Inclu�das classes para registro tempor�rio de pedidos na mem�ria.
 * 
 * *****************  Version 1  *****************
 * User: Fl�vio       Date: 24/07/98   Time: 14:16
 * Created in $/QuickSell/Server
 * Primeira implementa��o.
 * Suporte a sincroniza��o autom�tica do palmpc
 */

#include "stdafx.h"
#include "server.h"
#include "RSClientesAlterados.h"
#include "Configuration.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSClientesAlterados

IMPLEMENT_DYNAMIC(CRSClientesAlterados, CRecordset)

CRSClientesAlterados::CRSClientesAlterados(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CRSClientesAlterados)
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
	m_nDefaultType = snapshot;
}



CString CRSClientesAlterados::GetDefaultConnect()
{
	CConfiguration config;
	return config.GetDSN();
}



CString CRSClientesAlterados::GetDefaultSQL()
{
	return _T("[Clientes]");
}



void CRSClientesAlterados::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSClientesAlterados)
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
	pFX->SetFieldType(CFieldExchange::param);
	RFX_Int(pFX, _T("m_parm_Vendedor"), m_parm_Vendedor);
	RFX_Date(pFX, _T("m_parm_UltimaAtualizacao"), m_parm_UltimaAtualizacao);
	//RFX_Date(pFX, _T("m_parm_UltimaAtualizacaoDisponibilidade"), m_parm_UltimaAtualizacao);
}

/////////////////////////////////////////////////////////////////////////////
// CRSClientesAlterados diagnostics

#ifdef _DEBUG
void CRSClientesAlterados::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSClientesAlterados::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG



BOOL CRSClientesAlterados::Open(UINT nOpenType, LPCTSTR lpszSql, DWORD dwOptions) 
{
	m_nParams = 2;
	m_strFilter = "cl_Vendedor=? AND cl_TimeStamp>=?";
	
	return CRecordset::Open(nOpenType, lpszSql, dwOptions);
}



void CRSClientesAlterados::SetUltimaAtualizacao(CTime timeUltimaAtualizacao)
{
	m_parm_UltimaAtualizacao = timeUltimaAtualizacao;
}



void CRSClientesAlterados::SetVendedor(int nVendedor)
{
	m_parm_Vendedor = nVendedor;
}
