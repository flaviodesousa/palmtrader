// PlanosSynchronization.cpp: implementation of the CPlanosSynchronization class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Server.h"
#include "PlanosSynchronization.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPlanosSynchronization::CPlanosSynchronization()
{
	nRowCount = 0;
	TRY
	{
		pl.Open();
	}
	CATCH(CDBException, ex)
	{
		ex->ReportError();
	}
	END_CATCH;
}

CPlanosSynchronization::~CPlanosSynchronization()
{

}

BOOL CPlanosSynchronization::Process(CString & strRow)
{
	if (strRow == "/*")
	{
		return FALSE;
	}
	else
	{
		strRows[nRowCount] = strRow;
		nRowCount = ++nRowCount % 3;
		if (!nRowCount)
		{
			int nCodigo;

			TRY
			{
				pl.AddNew();
				pl.m_pl_Codigo = nCodigo = atoi(strRows[0]);
				pl.m_pl_Descricao = strRows[1];
				pl.m_pl_ColunaPreco = atoi(strRows[2]);
				pl.m_pl_TimeStamp = CTime::GetCurrentTime();
				pl.Update();
			}
			CATCH(CDBException, ex)
			{
				CString strError;
				strError.Format(_T("\r\nPlano %d\r\n"), nCodigo);
				strError += ex->m_strError;
				listErros.AddTail(strError);
			}
			END_CATCH;
		}
		return TRUE;
	}
}

void CPlanosSynchronization::SendRequest()
{
	char buf[] = "08\012" "/*\012";
	sock.Send((void *)&buf, strlen(buf));
}
