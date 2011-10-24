// Convers�o de valores em strings para double, tratando virgulas e pontos
// igualmente.
// Ou seja, independe das configura��es regionais.
//
// $Archive: /PalmTrader 1/Server/CString2double.cpp $
// $Author: Fl�vio $
// $Date: 28/07/99 11:48 $
/* $History: CString2double.cpp $
 * 
 * *****************  Version 3  *****************
 * User: Fl�vio       Date: 28/07/99   Time: 11:48
 * Updated in $/PalmTrader 1/Server
 * 
 * *****************  Version 1  *****************
 * User: Fl�vio       Date: 26/07/99   Time: 22:24
 * Created in $/QuickSell/Server
 * 
 * *****************  Version 1  *****************
 * User: Fl�vio       Date: 13/05/99   Time: 14:12
 * Created in $/PalmTrader 1/Server
 * Primeira implementa��o
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
