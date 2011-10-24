// RSPrecos.cpp : implementation file
//
// $Archive: /PalmTrader 1/Server/RSPrecos.cpp $
// $Author: Fl�vio $
// $Date: 25/05/99 15:31 $
/* $History: RSPrecos.cpp $
 * 
 * *****************  Version 4  *****************
 * User: Fl�vio       Date: 25/05/99   Time: 15:31
 * Updated in $/PalmTrader 1/Server
 * Altera��es feitas para o release 1.30
 * Inclu�da rotina gen�rica para convers�o de n�meros em strings
 * Corrigido bug na defini��o do tamanho do buffer de envio de pacotes TCP
 * nos m�dulos de sincroniza��o
 * Separada a porta TCP de conex�o com os clientes e servidores
 * Inclu�do m�todo em CPedido para retornar a data do pedido como DWORD,
 * que � usada no m�dulo de sincroniza��o de pedidos
 * Implementados novos atributos em pre�os
 * Inclu�do o script de cria��o da base SQL
 * 
 * *****************  Version 3  *****************
 * User: Fl�vio       Date: 21/07/98   Time: 17:39
 * Updated in $/QuickSell/Server
 * Obten��o do DSN via classe CConfiguration
 * 
 * *****************  Version 2  *****************
 * User: Fl�vio       Date: 7/04/98    Time: 5:55p
 * Updated in $/QuickSell/Server
 * Colocado em source control
 */

#include "stdafx.h"
#include "RSPrecos.h"
#include "Configuration.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSPrecos

IMPLEMENT_DYNAMIC(CRSPrecos, CRecordset)

CRSPrecos::CRSPrecos(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CRSPrecos)
	m_pr_Produto = 0;
	m_pr_Preco1 = _T("");
	m_pr_Preco2 = _T("");
	m_pr_Preco3 = _T("");
	m_pr_Preco4 = _T("");
	m_pr_Preco5 = _T("");
	m_pr_Preco6 = _T("");
	m_pr_Preco7 = _T("");
	m_pr_Preco8 = _T("");
	m_pr_Tabela = 0;
	m_pr_Complemento = _T("");
	m_pr_DescontoMaximo = _T("");
	m_pr_Brinde = FALSE;
	m_nFields = 14;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CRSPrecos::GetDefaultConnect()
{
	CConfiguration config;
	return config.GetDSN();
}

CString CRSPrecos::GetDefaultSQL()
{
	return _T(
		"SELECT "
			"pr_Produto,"
			"pr_Preco1,"
			"pr_Preco2,"
			"pr_Preco3,"
			"pr_Preco4,"
			"pr_Preco5,"
			"pr_Preco6,"
			"pr_Preco7,"
			"pr_Preco8,"
			"pr_Tabela,"
			"pr_TimeStamp,"
			"pr_Complemento,"
			"pr_DescontoMaximo,"
			"pr_Brinde "
		"FROM Precos"
		);
}

void CRSPrecos::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRSPrecos)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[pr_Produto]"), m_pr_Produto);
	RFX_Text(pFX, _T("[pr_Preco1]"), m_pr_Preco1);
	RFX_Text(pFX, _T("[pr_Preco2]"), m_pr_Preco2);
	RFX_Text(pFX, _T("[pr_Preco3]"), m_pr_Preco3);
	RFX_Text(pFX, _T("[pr_Preco4]"), m_pr_Preco4);
	RFX_Text(pFX, _T("[pr_Preco5]"), m_pr_Preco5);
	RFX_Text(pFX, _T("[pr_Preco6]"), m_pr_Preco6);
	RFX_Text(pFX, _T("[pr_Preco7]"), m_pr_Preco7);
	RFX_Text(pFX, _T("[pr_Preco8]"), m_pr_Preco8);
	RFX_Int(pFX, _T("[pr_Tabela]"), m_pr_Tabela);
	RFX_Date(pFX, _T("[pr_TimeStamp]"), m_pr_TimeStamp);
	RFX_Text(pFX, _T("[pr_Complemento]"), m_pr_Complemento);
	RFX_Text(pFX, _T("[pr_DescontoMaximo]"), m_pr_DescontoMaximo);
	RFX_Bool(pFX, _T("[pr_Brinde]"), m_pr_Brinde);
	//}}AFX_FIELD_MAP

	if (m_nParams)
	{
		pFX->SetFieldType( CFieldExchange::param );
		// RFX calls for parameter data members
		RFX_Long(pFX, _T("m_parm_Produto"), m_parm_Produto);
		RFX_Int(pFX, _T("m_parm_Tabela"), m_parm_Tabela);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CRSPrecos diagnostics

#ifdef _DEBUG
void CRSPrecos::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRSPrecos::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

void CRSPrecos::EnableParameterization()
{
	m_nParams = 2; // Produto e Tabela
	m_parm_Produto = m_parm_Tabela = 0;
	m_strFilter = "pr_Produto=? AND pr_Tabela=?";
}
