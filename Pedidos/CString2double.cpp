// Conversão de valores em strings para double, tratando virgulas e pontos
// igualmente.
// Ou seja, independe das configurações regionais.
//
// $Archive: /PalmTrader 1/Pedidos/CString2double.cpp $
// $Author: Flávio $
// $Date: 25/05/99 15:39 $
/* $History: CString2double.cpp $
 * 
 * *****************  Version 2  *****************
 * User: Flávio       Date: 25/05/99   Time: 15:39
 * Updated in $/PalmTrader 1/Pedidos
 * Alterações feitas para o release 1.30
 * Generalizada rotina para conversão de números em strings
 * Permitida a alteração individual de preços no pedido
 * Acelerada rotina de localização de produto
 * Incluída rotina genérica para conversão de números em strings
 * Corrigido bug na definição do tamanho do buffer de envio de pacotes TCP
 * nos módulos de sincronização
 * Separada a porta TCP de conexão com os clientes e servidores
 * Incluído método em CPedido para retornar a data do pedido como DWORD,
 * que é usada no módulo de sincronização de pedidos
 * Implementados novos atributos em preços
 * Incluído o script de criação da base SQL
 * 
 * *****************  Version 1  *****************
 * User: Flávio       Date: 13/05/99   Time: 14:12
 * Created in $/PalmTrader 1/Server
 * Primeira implementação
 */

#include <StdAfx.h>
#include <math.h>

double CStringToDouble(CString strValue)
{
	int nCommaPosition;
    long lIntegerPart;
    long lFractionaryPart;

	
    lIntegerPart = _wtol(strValue);

    if ((nCommaPosition = strValue.FindOneOf(_T(".,"))) >= 0)
    {
        lFractionaryPart = _wtol(strValue.Mid(nCommaPosition + 1));
    }
    else
    {
        lFractionaryPart = 0L;
    }

	return (double)lIntegerPart + lFractionaryPart / pow(10, strValue.GetLength() - nCommaPosition - 1);
}
