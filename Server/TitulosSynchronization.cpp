// TitulosSynchronization.cpp: implementation of the CTitulosSynchronization class.
//
//////////////////////////////////////////////////////////////////////
// $Archive: /PalmTrader 1/Server/TitulosSynchronization.cpp $
// $Author: Flávio $
// $Date: 25/05/99 15:31 $
/* $History: TitulosSynchronization.cpp $
 * 
 * *****************  Version 5  *****************
 * User: Flávio       Date: 25/05/99   Time: 15:31
 * Updated in $/PalmTrader 1/Server
 * Alterações feitas para o release 1.30
 * Incluída rotina genérica para conversão de números em strings
 * Corrigido bug na definição do tamanho do buffer de envio de pacotes TCP
 * nos módulos de sincronização
 * Separada a porta TCP de conexão com os clientes e servidores
 * Incluído método em CPedido para retornar a data do pedido como DWORD,
 * que é usada no módulo de sincronização de pedidos
 * Implementados novos atributos em preços
 * Incluído o script de criação da base SQL
 * 
 * *****************  Version 4  *****************
 * User: Flávio       Date: 11/07/98   Time: 19:52
 * Updated in $/QuickSell/Server
 * Incluído timestamp do título
 * 
 * *****************  Version 3  *****************
 * User: Flávio       Date: 9/07/98    Time: 20:02
 * Updated in $/QuickSell/Server
 * Reabilitado controle de erros
 * 
 * *****************  Version 2  *****************
 * User: Flávio       Date: 7/02/98    Time: 4:26p
 * Updated in $/QuickSell/Server
 * Primeira implementação: testada.
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
