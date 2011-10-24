// CodigosDeCobrancaSynchronization.cpp: implementation of the CCodigosDeCobrancaSynchronization class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Server.h"
#include "CodigosDeCobrancaSynchronization.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCodigosDeCobrancaSynchronization::CCodigosDeCobrancaSynchronization()
{
	nRowCount = 0;
	TRY
	{
		cb.Open();
	}
	CATCH(CDBException, ex)
	{
		ex->ReportError();
	}
	END_CATCH;
}

CCodigosDeCobrancaSynchronization::~CCodigosDeCobrancaSynchronization()
{

}

BOOL CCodigosDeCobrancaSynchronization::Process(CString & strRow)
{
	if (strRow == "/*")
	{
		return FALSE;
	}
	else
	{
		strRows[nRowCount] = strRow;
		nRowCount = ++nRowCount % 2;
		if (!nRowCount)
		{
			CString strCodigo;

			TRY
			{
				cb.AddNew();
				cb.m_cb_Codigo = strCodigo = strRows[0];
				cb.m_cb_Descricao = strRows[1];
				cb.m_cb_TimeStamp = CTime::GetCurrentTime();
				cb.Update();
			}
			CATCH(CDBException, ex)
			{
				CString strError;
				strError.Format(_T("\r\nCódigo de cobrança %s\r\n"), strCodigo);
				strError += ex->m_strError;
				listErros.AddTail(strError);
			}
			END_CATCH;
		}
		return TRUE;
	}
}

void CCodigosDeCobrancaSynchronization::SendRequest()
{
	char buf[] = "09\012" "/*\012";
	sock.Send((void *)&buf, strlen(buf));
}
