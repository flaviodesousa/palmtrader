// TitulosSynchronization.cpp: implementation of the CTitulosSynchronization class.
//
//////////////////////////////////////////////////////////////////////
// $Archive: /PalmTrader 1/Server/TitulosSynchronization.cpp $
// $Author: Fl�vio $
// $Date: 25/05/99 15:31 $
/* $History: TitulosSynchronization.cpp $
 * 
 * *****************  Version 5  *****************
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
 * *****************  Version 4  *****************
 * User: Fl�vio       Date: 11/07/98   Time: 19:52
 * Updated in $/QuickSell/Server
 * Inclu�do timestamp do t�tulo
 * 
 * *****************  Version 3  *****************
 * User: Fl�vio       Date: 9/07/98    Time: 20:02
 * Updated in $/QuickSell/Server
 * Reabilitado controle de erros
 * 
 * *****************  Version 2  *****************
 * User: Fl�vio       Date: 7/02/98    Time: 4:26p
 * Updated in $/QuickSell/Server
 * Primeira implementa��o: testada.
 */

#include "stdafx.h"
#include "server.h"
#include "TitulosSynchronization.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTitulosSynchronization::CTitulosSynchronization()
{
	nRowCount = 0;
	TRY
	{

        ti.Open();
        //ti.MoveFirst();
        while (!ti.IsEOF())
        {
            ti.Delete();
            ti.MoveNext();
        }
        /*
        ti.Close();
        ti.EnableParameterization();
		ti.Open();
        */
	}
	CATCH(CDBException, ex)
	{
		ex->ReportError();
	}
	END_CATCH;
}

CTitulosSynchronization::~CTitulosSynchronization()
{

}

BOOL CTitulosSynchronization::Process(CString & strRow)
{
	if (strRow == "/*")
	{
		return FALSE;
	}
	else
	{
		strRows[nRowCount] = strRow;
		nRowCount = ++nRowCount % 5;
		if (!nRowCount)
		{
	        TRY
	        {
                ti.AddNew();
                ti.m_ti_Numero = strRows[0];
                ti.m_ti_Valor = strRows[1];
                ti.m_ti_Emissao = strRows[2];
                ti.m_ti_Vencimento = strRows[3];
                ti.m_ti_Cliente = atol(strRows[4]);
				ti.m_ti_TimeStamp = CTime::GetCurrentTime();
                ti.Update();
			}
			CATCH(CDBException, ex)
			{
				CString strError;
				strError.Format(_T("\r\nTitulo %s\r\n"), strRows[0]);
				strError += ex->m_strError;
				listErros.AddTail(strError);
			}
			END_CATCH;
		}
		return TRUE;
	}
}

void CTitulosSynchronization::SendRequest()
{
	char buf[] = "12\012" "/*\012";
	sock.Send((void *)&buf, strlen(buf));
}
