// VendedoresSynchronization.cpp: implementation of the CVendedoresSynchronization class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Server.h"
#include "VendedoresSynchronization.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVendedoresSynchronization::CVendedoresSynchronization()
{
    vd.EnableParameterization();
	vd.Open();
	nRowCount = 0;
}

CVendedoresSynchronization::~CVendedoresSynchronization()
{

}

BOOL CVendedoresSynchronization::Process(CString & strRow)
{
	if (strRow == "/*")
	{
		return FALSE;
	}
	else
	{
		strRows[nRowCount] = strRow;
		nRowCount = ++nRowCount % 4;
		if (!nRowCount)
		{
			TRY
			{
                long lCodigo = atol(strRows[0]);

                vd.m_parm_Codigo = lCodigo;
                vd.Requery();

                if (vd.IsEOF())
                {
				    vd.AddNew();
				    vd.m_vd_Codigo = lCodigo;
				    vd.m_vd_Nome = strRows[1];
				    vd.m_vd_Senha = strRows[2];
				    vd.m_vd_TabelaPrecos = atoi(strRows[3]);
				    vd.m_vd_UltimaAtualizacao = CTime::GetCurrentTime();
				    vd.Update();
                }
                else
                {
                    vd.Edit();
				    vd.m_vd_Nome = strRows[1];
				    vd.m_vd_Senha = strRows[2];
				    vd.m_vd_TabelaPrecos = atoi(strRows[3]);
				    vd.m_vd_UltimaAtualizacao = CTime::GetCurrentTime();
				    vd.Update();
                }
			}
			CATCH(CDBException, ex)
			{
				ex->ReportError();
			}
			END_CATCH;
		}
		return TRUE;
	}
}

void CVendedoresSynchronization::SendRequest()
{
	char buf[] = "11\012" "/*\012";
	sock.Send((void *)&buf, strlen(buf));
}
