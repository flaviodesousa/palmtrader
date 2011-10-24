// Conversão de valores em strings para double, tratando virgulas e pontos
// igualmente.
// Ou seja, independe das configurações regionais.
//
// $Archive: /PalmTrader 1/Server/CString2double.cpp $
// $Author: Flávio $
// $Date: 28/07/99 11:48 $
/* $History: CString2double.cpp $
 * 
 * *****************  Version 3  *****************
 * User: Flávio       Date: 28/07/99   Time: 11:48
 * Updated in $/PalmTrader 1/Server
 * 
 * *****************  Version 1  *****************
 * User: Flávio       Date: 26/07/99   Time: 22:24
 * Created in $/QuickSell/Server
 * 
 * *****************  Version 1  *****************
 * User: Flávio       Date: 13/05/99   Time: 14:12
 * Created in $/PalmTrader 1/Server
 * Primeira implementação
 */

#include <StdAfx.h>

double CStringToDouble(CString strValue)
{
	int nCommaPosition;

	if ((nCommaPosition = strValue.Find(',')) >= 0)
	{
		strValue.SetAt(nCommaPosition, '.');
	}

	return atof(strValue);
}
