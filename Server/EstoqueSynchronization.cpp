// EstoqueSynchronization.cpp: implementation of the CEstoqueSynchronization class.
//
//////////////////////////////////////////////////////////////////////
// $Archive: /PalmTrader 1/Server/EstoqueSynchronization.cpp $
// $Author: Flávio $
// $Date: 25/05/99 15:31 $
/* $History: EstoqueSynchronization.cpp $
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
 * User: Flávio       Date: 4/03/98    Time: 12:01p
 * Updated in $/QuickSell/Server
 * Padronizada a chamada para ativação da parametrização do recordset
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
					strError.Format(_T("Produto %ld, não encontrado\r\n"), lCodigo);
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
