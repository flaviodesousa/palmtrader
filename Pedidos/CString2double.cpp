// Convers�o de valores em strings para double, tratando virgulas e pontos
// igualmente.
// Ou seja, independe das configura��es regionais.
//
// $Archive: /PalmTrader 1/Pedidos/CString2double.cpp $
// $Author: Fl�vio $
// $Date: 25/05/99 15:39 $
/* $History: CString2double.cpp $
 * 
 * *****************  Version 2  *****************
 * User: Fl�vio       Date: 25/05/99   Time: 15:39
 * Updated in $/PalmTrader 1/Pedidos
 * Altera��es feitas para o release 1.30
 * Generalizada rotina para convers�o de n�meros em strings
 * Permitida a altera��o individual de pre�os no pedido
 * Acelerada rotina de localiza��o de produto
 * Inclu�da rotina gen�rica para convers�o de n�meros em strings
 * Corrigido bug na defini��o do tamanho do buffer de envio de pacotes TCP
 * nos m�dulos de sincroniza��o
 * Separada a porta TCP de conex�o com os clientes e servidores
 * Inclu�do m�todo em CPedido para retornar a data do pedido como DWORD,
 * que � usada no m�dulo de sincroniza��o de pedidos
 * Implementados novos atributos em pre�os
 * Inclu�do o script de cria��o da base SQL
 * 
 * *****************  Version 1  *****************
 * User: Fl�vio       Date: 13/05/99   Time: 14:12
 * Created in $/PalmTrader 1/Server
 * Primeira implementa��o
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
