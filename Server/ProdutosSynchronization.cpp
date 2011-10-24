// ProdutosSynchronization.cpp: implementation of the CProdutosSynchronization class.
//
//////////////////////////////////////////////////////////////////////
// $Archive: /PalmTrader 1/Server/ProdutosSynchronization.cpp $
// $Author: Flávio $
// $Date: 25/05/99 15:31 $
/* $History: ProdutosSynchronization.cpp $
 * 
 * *****************  Version 10  *****************
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
 * *****************  Version 9  *****************
 * User: Flávio       Date: 21/07/98   Time: 17:36
 * Updated in $/QuickSell/Server
 * Incluída atualização de disponibilidade na atualização de produtos
 * 
 * *****************  Version 8  *****************
 * User: Flávio       Date: 11/07/98   Time: 19:46
 * Updated in $/QuickSell/Server
 * Aprimorado controle de erros.
 * 
 * *****************  Version 7  *****************
 * User: Flávio       Date: 7/04/98    Time: 5:40p
 * Updated in $/QuickSell/Server
 * Incluído campo disponibilidade na sincronização de produtos
 * 
 * *****************  Version 6  *****************
 * User: Flávio       Date: 7/02/98    Time: 4:27p
 * Updated in $/QuickSell/Server
 * Incluídos novos campos.
 * 
 * *****************  Version 5  *****************
 * User: Flávio       Date: 6/25/98    Time: 8:04p
 * Updated in $/QuickSell/Server
 * Acrescentados novos campos, por enquanto tratando somente o campo
 * "Embalagem"
 * 
 * *****************  Version 4  *****************
 * User: Flávio       Date: 4/03/98    Time: 12:01p
 * Updated in $/QuickSell/Server
 * Padronizada a chamada para ativação da parametrização do recordset
 * RSProdutos
 */

#include "stdafx.h"
#include "QSTools.h"
#include "Server.h"

#include "ProdutosSynchronization.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CProdutosSynchronization::CProdutosSynchronization()
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

CProdutosSynchronization::~CProdutosSynchronization()
{

}

BOOL CProdutosSynchronization::Process(CString& strRow)
{
	if (strRow == "/*")
	{
		return FALSE;
	}
	else
	{
		strRows[nRowCount] = strRow;
		nRowCount = ++nRowCount % 9;
		if (!nRowCount)
		{
			long lCodigo = atol(strRows[0]);
			int nDigito = atoi(strRows[1]);

			TRY
			{
                pd.m_parm_Codigo = lCodigo;
                pd.Requery();
                if (pd.IsEOF())
                {
                    pd.AddNew();
                    pd.m_pd_Codigo = lCodigo;
                    pd.m_pd_Digito = nDigito;
                    pd.m_pd_Descricao = strRows[2];
                    pd.m_pd_Unidade = strRows[3];
                    pd.m_pd_Embalagem = strRows[4];
                    pd.m_pd_Unidades = atoi(strRows[5]);
                    pd.m_pd_EmbalagemMaster = atoi(strRows[6]);
                    pd.m_pd_PesoBruto = strRows[7];
				    pd.m_pd_Disponivel = atol(strRows[8])>0;
				    pd.m_pd_TimeStamp =
				    pd.m_pd_DisponibilidadeTimeStamp = CTime::GetCurrentTime();
				    pd.Update();
                }
                else
				{
					if (
						pd.m_pd_Digito != nDigito ||
						pd.m_pd_Descricao != strRows[2] ||
						pd.m_pd_Unidade != strRows[3] ||
						pd.m_pd_Embalagem != strRows[4] ||
						pd.m_pd_Unidades != atoi(strRows[5]) ||
						pd.m_pd_EmbalagemMaster != atoi(strRows[6]) ||
						CStringToDouble(pd.m_pd_PesoBruto) != CStringToDouble(strRows[7])
						)
					{
						pd.Edit();
						pd.m_pd_Descricao = strRows[2];
						pd.m_pd_Unidade = strRows[3];
						pd.m_pd_Embalagem = strRows[4];
						pd.m_pd_Unidades = atoi(strRows[5]);
						pd.m_pd_EmbalagemMaster = atoi(strRows[6]);
						pd.m_pd_PesoBruto = strRows[7];
						pd.m_pd_TimeStamp = CTime::GetCurrentTime();
						pd.Update();
					}

					BOOL bDisponivel = atol(strRows[8]) > 0;
					if (pd.m_pd_Disponivel != bDisponivel)
					{
						pd.Edit();
						pd.m_pd_Disponivel = bDisponivel;
						pd.m_pd_DisponibilidadeTimeStamp = CTime::GetCurrentTime();
						pd.Update();
					}
				}
			}
			CATCH(CDBException, ex)
			{
				CString strError;
				strError.Format(_T("\r\nProduto %ld-%d\r\n"), lCodigo, nDigito);
				strError += ex->m_strError;
				AddError(strError);
			}
			END_CATCH;
		}
		return TRUE;
	}
}

void CProdutosSynchronization::SendRequest()
{
	char buf[] = "04\012" "/*\012";
	sock.Send((void *)&buf, strlen(buf));
}
