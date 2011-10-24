// RSProdutosComPrecos.cpp : implementation file
//
// $Archive: /PalmTrader 1/Server/RSProdutosComPrecos.cpp $
// $Author: Flávio $
// $Date: 28/07/99 11:49 $
/* $History: RSProdutosComPrecos.cpp $
 * 
 * *****************  Version 7  *****************
 * User: Flávio       Date: 28/07/99   Time: 11:49
 * Updated in $/PalmTrader 1/Server
 * Código reincorporado a $/PalmTrader 1/Server
 * 
 * *****************  Version 6  *****************
 * User: Flávio       Date: 28/07/99   Time: 10:58
 * Updated in $/QuickSell/Server
 * Cláusulas SQL JOIN alteradas para padrão compatível com MS-Access
 * 
 * *****************  Version 5  *****************
 * User: Flávio       Date: 21/07/98   Time: 17:39
 * Updated in $/QuickSell/Server
 * Obtenção do DSN via classe CConfiguration
 * 
 * *****************  Version 4  *****************
 * User: Flávio       Date: 7/07/98    Time: 10:43a
 * Updated in $/QuickSell/Server
 * Corrigido erro na cláusula SELECT (faltava uma vírgula após o campo
 * pd_PesoBruto)
 * 
 * *****************  Version 3  *****************
 * User: Flávio       Date: 7/04/98    Time: 5:57p
 * Updated in $/QuickSell/Server
 * Colocado em source control
 */

#include "stdafx.h"
#include "Server.h"
#include "RSProdutosComPrecos.h"
#include "Configuration.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSProdutosComPrecos

IMPLEMENT_DYNAMIC(CRSProdutosComPrecos, CRecordset)

CRSProdutosComPrecos::CRSProdutosComPrecos(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CRSProdutosComPrecos)
	m_pr_Tabela = 0;
	m_pr_Produto = 0;
	m_pr_Preco1 = _T("");
	m_pr_Preco2 = _T("");
	m_pr_Preco3 = _T("");
	m_pr_Preco4 = _T("");
	m_pr_Preco5 = _T("");
	m_pr_Preco6 = _T("");
	m_pr_Preco7 = _T("");
	m_pr_Preco8 = _T("");
	m_pd_Codigo = 0;
	m_pd_Digito = 0;
	m_pd_Descricao = _T("");
	m_pd_Disponivel = FALSE;
	m_pd_Embalagem = _T("");
	m_pd_EmbalagemMaster = 0;
	m_pd_PesoBruto = _T("");
	m_pd_Unidade = _T("");
	m_pd_Unidades = 0;
	m_nFields = 22;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CRSProdutosComPrecos::GetDefaultConnect()
{
	CConfiguration config;
	return config.GetDSN();
}

CString CRSProdutosComPrecos::GetDefaultSQL()
{
	//return _T("[dbo].[Precos],[dbo].[Produtos]");
	return _T(
		"SELECT "
			"pr_Tabela,"
			"pr_Produto,"
			"pr_Preco1,"
			"pr_Preco2,"
			"pr_Preco3,"
			"pr_Preco4,"
			"pr_Preco5,"
			"pr_Preco6,"
			"pr_Preco7,"
			"pr_Preco8,"
			"pr_TimeStamp,"
			"pd_Codigo,"
			"pd_Digito,"
			"pd_Descricao,"
			"pd_Disponivel,"
			"pd_TimeStamp,"
			"pd_DisponibilidadeTimeStamp,"
			"pd_Embalagem,"
			"pd_EmbalagemMaster,"
			"pd_PesoBruto,"
			"pd_Unidade,"
			"pd_Unidades "
		"FROM Precos "
			"INNER JOIN Produtos ON Precos.pr_Produto=Produtos.pd_Codigo"
		);
}

void CRSProdutosComPrecos::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSProdutosComPrecos)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[pr_Tabela]"), m_pr_Tabela);
	RFX_Long(pFX, _T("[pr_Produto]"), m_pr_Produto);
	RFX_Text(pFX, _T("[pr_Preco1]"), m_pr_Preco1);
	RFX_Text(pFX, _T("[pr_Preco2]"), m_pr_Preco2);
	RFX_Text(pFX, _T("[pr_Preco3]"), m_pr_Preco3);
	RFX_Text(pFX, _T("[pr_Preco4]"), m_pr_Preco4);
	RFX_Text(pFX, _T("[pr_Preco5]"), m_pr_Preco5);
	RFX_Text(pFX, _T("[pr_Preco6]"), m_pr_Preco6);
	RFX_Text(pFX, _T("[pr_Preco7]"), m_pr_Preco7);
	RFX_Text(pFX, _T("[pr_Preco8]"), m_pr_Preco8);
	RFX_Date(pFX, _T("[pr_TimeStamp]"), m_pr_TimeStamp);
	RFX_Long(pFX, _T("[pd_Codigo]"), m_pd_Codigo);
	RFX_Byte(pFX, _T("[pd_Digito]"), m_pd_Digito);
	RFX_Text(pFX, _T("[pd_Descricao]"), m_pd_Descricao);
	RFX_Bool(pFX, _T("[pd_Disponivel]"), m_pd_Disponivel);
	RFX_Date(pFX, _T("[pd_TimeStamp]"), m_pd_TimeStamp);
	RFX_Date(pFX, _T("[pd_DisponibilidadeTimeStamp]"), m_pd_DisponibilidadeTimeStamp);
	RFX_Text(pFX, _T("[pd_Embalagem]"), m_pd_Embalagem);
	RFX_Long(pFX, _T("[pd_EmbalagemMaster]"), m_pd_EmbalagemMaster);
	RFX_Text(pFX, _T("[pd_PesoBruto]"), m_pd_PesoBruto);
	RFX_Text(pFX, _T("[pd_Unidade]"), m_pd_Unidade);
	RFX_Long(pFX, _T("[pd_Unidades]"), m_pd_Unidades);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRSProdutosComPrecos diagnostics

#ifdef _DEBUG
void CRSProdutosComPrecos::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSProdutosComPrecos::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
