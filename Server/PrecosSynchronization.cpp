// PrecosSynchronization.cpp: implementation of the CPrecosSynchronization class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "QSTools.h"
#include "Server.h"
#include "PrecosSynchronization.h"
#include "RSTabelasPrecos.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPrecosSynchronization::CPrecosSynchronization(int nTabelaPrecos)
{
	nTabela = nTabelaPrecos;
	nRowCount = 0;
	m_comparados = m_alterados = m_adicionados = 0;
	
	TRY
	{
		pr.EnableParameterization();
		pr.Open();

		m_Log.Open("\\SynchPrecos.log", CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::shareDenyWrite);
		m_Log.SeekToEnd();
		LogString((m_strLog.Format("Sincronizacao iniciada - Tabela %d", nTabela), m_strLog));
	}
	CATCH_ALL(ex)
	{
		ex->ReportError();
	}
	END_CATCH_ALL;
}

CPrecosSynchronization::~CPrecosSynchronization()
{
}

BOOL CPrecosSynchronization::Process(CString & strRow)
{
	if (strRow == "/*")
	{
		LogString((m_strLog.Format("Sincronizacao finalizada - %d inc, %d comp, %d alt\n", m_adicionados, m_comparados, m_alterados), m_strLog));
		return FALSE;
	}
	else
	{
		strRows[nRowCount] = strRow;
		nRowCount = ++nRowCount % 12;
		if (!nRowCount)
		{
			long lCodigo;

			TRY
			{
				lCodigo = atol(strRows[0]);
				if (strRows[1].IsEmpty()) strRows[1] = " ";
				pr.m_parm_Produto = lCodigo;
				pr.m_parm_Tabela = nTabela;
				pr.Requery();
				if (pr.IsEOF())
				{
					pr.AddNew();
					pr.m_pr_Tabela = nTabela;
					pr.m_pr_Produto = lCodigo;
					pr.m_pr_Complemento = strRows[1];
					pr.m_pr_Preco1 = strRows[2];
					pr.m_pr_Preco2 = strRows[3];
					pr.m_pr_Preco3 = strRows[4];
					pr.m_pr_Preco4 = strRows[5];
					pr.m_pr_Preco5 = strRows[6];
					pr.m_pr_Preco6 = strRows[7];
					pr.m_pr_Preco7 = strRows[8];
					pr.m_pr_Preco8 = strRows[9];
					pr.m_pr_DescontoMaximo = strRows[10];
					pr.m_pr_Brinde = (strRows[11] == "S");
					pr.m_pr_TimeStamp = CTime::GetCurrentTime();
					pr.Update();

					LogString((m_strLog.Format("Inclusao  - Prod %ld", lCodigo), m_strLog));
					m_adicionados++;
				}
				else
				{
					m_comparados++;
					if (pr.m_pr_Complemento    != strRows[1] ||
						CStringToDouble(pr.m_pr_Preco1)   != CStringToDouble(strRows[2]) ||
						CStringToDouble(pr.m_pr_Preco2)   != CStringToDouble(strRows[3]) ||
						CStringToDouble(pr.m_pr_Preco3)   != CStringToDouble(strRows[4]) ||
						CStringToDouble(pr.m_pr_Preco4)   != CStringToDouble(strRows[5]) ||
						CStringToDouble(pr.m_pr_Preco5)   != CStringToDouble(strRows[6]) ||
						CStringToDouble(pr.m_pr_Preco6)   != CStringToDouble(strRows[7]) ||
						CStringToDouble(pr.m_pr_Preco7)   != CStringToDouble(strRows[8]) ||
						CStringToDouble(pr.m_pr_Preco8)   != CStringToDouble(strRows[9]) ||
						CStringToDouble(pr.m_pr_DescontoMaximo) != CStringToDouble(strRows[10]) ||
						pr.m_pr_Brinde         != strRows[11]
						)
					{
						pr.Edit();
						pr.m_pr_TimeStamp   = CTime::GetCurrentTime();
						pr.m_pr_Complemento = strRows[1];
						pr.m_pr_Preco1      = strRows[2];
						pr.m_pr_Preco2      = strRows[3];
						pr.m_pr_Preco3      = strRows[4];
						pr.m_pr_Preco4      = strRows[5];
						pr.m_pr_Preco5      = strRows[6];
						pr.m_pr_Preco6      = strRows[7];
						pr.m_pr_Preco7      = strRows[8];
						pr.m_pr_Preco8      = strRows[9];
						pr.m_pr_DescontoMaximo = strRows[10];
						pr.m_pr_Brinde      = (strRows[11] == "S");
						pr.Update();

						LogString((m_strLog.Format("Alteracao - Prod %ld ", lCodigo), m_strLog += strRows[1], m_strLog));
						m_alterados++;
					}
				}
			}
			CATCH(CDBException, ex)
			{
				CString strError;
				strError.Format(_T("\r\nProduto %ld\r\n"), lCodigo);
				strError += ex->m_strError;
				LogString(strError);
				listErros.AddTail(strError);
			}
			END_CATCH;
		}
		return TRUE;
	}
}

void CPrecosSynchronization::SendRequest()
{
	char mask[] = "06\012" "%d\012" "/*\012";
	char buf[sizeof mask + 5];

	sprintf(buf, mask, nTabela);
	sock.Send(buf, strlen(buf));
}

void CPrecosSynchronization::LogString(CString str)
{
	m_Log.WriteString(CTime::GetCurrentTime().Format("%d/%m/%Y %H:%M:%S ") + str + "\n");
}