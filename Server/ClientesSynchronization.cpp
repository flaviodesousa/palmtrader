// ClientesSynchronization.cpp: implementation of the CClientesSynchronization class.
//
//////////////////////////////////////////////////////////////////////
// $Archive: /PalmTrader 1/Server/ClientesSynchronization.cpp $
// $Author: Flávio $
// $Date: 25/05/99 15:31 $
/* $History: ClientesSynchronization.cpp $
 * 
 * *****************  Version 7  *****************
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
 * *****************  Version 6  *****************
 * User: Flávio       Date: 12/05/99   Time: 17:08
 * Updated in $/PalmTrader 1/Server
 * Corrigido bug na definição do tamanho do buffer de envio de pacotes TCP
 * nas rotinas de sincronização
 * Diferenciada a porta TCP da parte cliente e da parte servidora
 * Incluídos novos atributos na sincronização de preços
 * 
 * *****************  Version 5  *****************
 * User: Flávio       Date: 13/07/98   Time: 14:16
 * Updated in $/QuickSell/Server
 * Incluído em source control.
 * Verifica variação no conteúdo antes de se atualizar
 * Melhorado controle de erros
 */

#include "stdafx.h"
#include "QSTools.h"
#include "Server.h"

#include "ClientesSynchronization.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CClientesSynchronization::CClientesSynchronization()
{
	nRowCount = 0;
	TRY
	{
		cl.EnableParameterization();
		cl.Open();
	}
	CATCH(CDBException, ex)
	{
		ex->ReportError();
	}
	END_CATCH;
}

CClientesSynchronization::~CClientesSynchronization()
{

}

BOOL CClientesSynchronization::Process(CString & strRow)
{
	if (strRow == "/*")
	{
		return FALSE;
	}
	else
	{
		strRows[nRowCount] = strRow;
		nRowCount = ++nRowCount % 28;
		if (!nRowCount)
		{
			LONG lClienteCodigo = atol(strRows[0]);
			int nClienteDV = atoi(strRows[1]);

			cl.m_parm_Codigo = lClienteCodigo;
			cl.Requery();

			BOOL bNewOne = cl.IsEOF();
			BOOL bDoIt = FALSE;

			TRY
			{
				if (bNewOne)
				{
					cl.AddNew();
					bDoIt = TRUE;
				}
				else if (
					cl.m_cl_Digito != nClienteDV ||
					cl.m_cl_RazaoSocial != strRows[2] ||
					cl.m_cl_Fantasia != strRows[3] ||
					cl.m_cl_Contato != strRows[4] ||

					cl.m_cl_EnderecoComercial != strRows[5] ||
					cl.m_cl_EnderecoComercialBairro != strRows[6] ||
					cl.m_cl_EnderecoComercialCidade != strRows[7] ||
					cl.m_cl_EnderecoComercialEstado != strRows[8] ||
					cl.m_cl_EnderecoComercialCEP != strRows[9] ||

					cl.m_cl_EnderecoCobranca != strRows[10] ||
					cl.m_cl_EnderecoCobrancaBairro != strRows[11] ||
					cl.m_cl_EnderecoCobrancaCidade != strRows[12] ||
					cl.m_cl_EnderecoCobrancaEstado != strRows[13] ||
					cl.m_cl_EnderecoCobrancaCEP != strRows[14] ||

					cl.m_cl_Telefone != strRows[15] ||
					cl.m_cl_Fax != strRows[16] ||
					cl.m_cl_RamoAtividade != atoi(strRows[17]) ||
					cl.m_cl_Cobranca != strRows[18] ||
					cl.m_cl_EmitirDuplicata != (BOOL)(strRows[19] == "S") ||

					cl.m_cl_Vendedor != atoi(strRows[20]) ||
					cl.m_cl_Praca != atoi(strRows[21]) ||
					CStringToDouble(cl.m_cl_Limite) != CStringToDouble(strRows[22]) ||
					CStringToDouble(cl.m_cl_ValorDisponivel) != CStringToDouble(strRows[23]) ||
					cl.m_cl_CGC != strRows[24] ||

					cl.m_cl_Bloqueado != (BOOL)(strRows[25] == "S") ||
					cl.m_cl_MotivoBloqueio != strRows[26] ||
                    cl.m_cl_Tabela != atoi(strRows[27])
					)
				{
					cl.Edit();
					bDoIt = TRUE; // Later: check to see if something changed
				}

				if (bDoIt)
				{
					cl.m_cl_Codigo = lClienteCodigo;
					cl.m_cl_Digito = nClienteDV;
					cl.m_cl_RazaoSocial = strRows[2];
					cl.m_cl_Fantasia = strRows[3];
					cl.m_cl_Contato = strRows[4];

					cl.m_cl_EnderecoComercial = strRows[5];
					cl.m_cl_EnderecoComercialBairro = strRows[6];
					cl.m_cl_EnderecoComercialCidade = strRows[7];
					cl.m_cl_EnderecoComercialEstado = strRows[8];
					cl.m_cl_EnderecoComercialCEP = strRows[9];

					cl.m_cl_EnderecoCobranca = strRows[10];
					cl.m_cl_EnderecoCobrancaBairro = strRows[11];
					cl.m_cl_EnderecoCobrancaCidade = strRows[12];
					cl.m_cl_EnderecoCobrancaEstado = strRows[13];
					cl.m_cl_EnderecoCobrancaCEP = strRows[14];

					cl.m_cl_Telefone = strRows[15];
					cl.m_cl_Fax = strRows[16];
					cl.m_cl_RamoAtividade = atoi(strRows[17]);
					cl.m_cl_Cobranca = strRows[18];
					cl.m_cl_EmitirDuplicata = strRows[19] == "S";

					cl.m_cl_Vendedor = atoi(strRows[20]);
					cl.m_cl_Praca = atoi(strRows[21]);
					cl.m_cl_Limite = strRows[22];
					cl.m_cl_ValorDisponivel = strRows[23];
					cl.m_cl_CGC = strRows[24];

					cl.m_cl_Bloqueado = strRows[25] == "S";
					cl.m_cl_MotivoBloqueio = strRows[26];
                    cl.m_cl_Tabela = atoi(strRows[27]);
					cl.m_cl_TimeStamp =
					cl.m_cl_LimiteTimeStamp = CTime::GetCurrentTime();

					cl.Update();
				}
			}
			CATCH(CDBException, ex)
			{
				CString strError;
				strError.Format(_T("\r\nCliente %ld-%d\r\n"), lClienteCodigo, nClienteDV);
				strError += ex->m_strError;
				AddError(strError);
			}
			END_CATCH;
		}
		return TRUE;
	}
}

void CClientesSynchronization::SendRequest()
{
	char buf[] = "05\012" "/*\012";
	sock.Send((void *)&buf, strlen(buf));
}
