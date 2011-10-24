// TabelasSynchronization.cpp: implementation of the CTabelasSynchronization class.
//
//////////////////////////////////////////////////////////////////////
// $Archive: /PalmTrader 1/Server/TabelasSynchronization.cpp $
// $Author: Fl�vio $
// $Date: 28/07/99 11:49 $
/* $History: TabelasSynchronization.cpp $
 * 
 * *****************  Version 6  *****************
 * User: Fl�vio       Date: 28/07/99   Time: 11:49
 * Updated in $/PalmTrader 1/Server
 * C�digo reincorporado a $/PalmTrader 1/Server
 * 
 * *****************  Version 5  *****************
 * User: Fl�vio       Date: 28/07/99   Time: 10:59
 * Updated in $/QuickSell/Server
 * Aprimorado tratamento de erros
 * 
 * *****************  Version 4  *****************
 * User: Fl�vio       Date: 24/07/98   Time: 14:22
 * Updated in $/QuickSell/Server
 * Removida a exibi��o de erros para se evitar a paraliza��o do programa
 * durante as atualiza��es. Nota: o erro � geralmente relativo a tentativa
 * de inclus�o de registros duplicados
 */

#include "stdafx.h"
#include "Server.h"
#include "TabelasSynchronization.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTabelasSynchronization::CTabelasSynchronization()
{
	tp.Open();
}

CTabelasSynchronization::~CTabelasSynchronization()
{

}

void CTabelasSynchronization::SendRequest()
{
	char buf[] = "10\012" "/*\012";
	sock.Send((void *)&buf, sizeof buf);
}

BOOL CTabelasSynchronization::Process(CString & strRow)
{
	if (strRow == "/*")
	{
		return FALSE;
	}
	else
	{
		TRY
		{
			tp.AddNew();
			tp.m_tp_Codigo = atoi(strRow);
			tp.Update();
		}
		CATCH(CDBException, ex)
		{
			CString strError;
			strError += ex->m_strError;
			listErros.AddTail(strError);
		}
		END_CATCH;

		return TRUE;
	}
}
