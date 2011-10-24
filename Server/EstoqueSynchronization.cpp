// EstoqueSynchronization.cpp: implementation of the CEstoqueSynchronization class.
//
//////////////////////////////////////////////////////////////////////
// $Archive: /PalmTrader 1/Server/EstoqueSynchronization.cpp $
// $Author: Fl�vio $
// $Date: 25/05/99 15:31 $
/* $History: EstoqueSynchronization.cpp $
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
 * User: Fl�vio       Date: 4/03/98    Time: 12:01p
 * Updated in $/QuickSell/Server
 * Padronizada a chamada para ativa��o da parametriza��o do recordset
 * RSProdutos
 */

#include "stdafx.h"
#include "Server.h"
#include "EstoqueSynchronization.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEstoqueSynchronization::CEstoqueSynchronization()
{
	nRowCount = 0;
	TRY
	{
		pd.EnableParameterization();
		pd.Open();
	}
	CATCH(CDBException, ex)
	{
		ex->ReportError();
	}
	END_CATCH;
}

CEstoqueSynchronization::~CEstoqueSynchronization()
{

}

BOOL CEstoqueSynchronization::Process(CString & strRow)
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
			long lCodigo, lQuantidade;

			TRY
			{
				pd.m_parm_Codigo = lCodigo = atol(strRows[0]);
				lQuantidade = atol(strRows[1]);
				//pd.m_strFilter.Format(_T("pd_Codigo=%ld"), lCodigo);
				pd.Requery();
				if (!pd.IsEOF())
				{
					if ((lQuantidade && !pd.m_pd_Disponivel) || 
						(!lQuantidade && pd.m_pd_Disponivel))
					{
						pd.Edit();
						pd.m_pd_Disponivel = (lQuantidade != 0);
						pd.m_pd_DisponibilidadeTimeStamp = CTime::GetCurrentTime();
						pd.Update();
					}
				}
				else
				{
					CString strError;
					strError.Format(_T("Produto %ld, n�o encontrado\r\n"), lCodigo);
					listErros.AddTail(strError);
				}
			}
			CATCH(CDBException, ex)
			{
				CString strError;
				strError.Format(_T("\r\nProduto %ld\r\n"), lCodigo);
				strError += ex->m_strError;
				listErros.AddTail(strError);
			}
			END_CATCH;
		}
		return TRUE;
	}
}

void CEstoqueSynchronization::SendRequest()
{
	char buf[] = "07\012" "/*\012";
	sock.Send((void *)&buf, strlen(buf));
}
