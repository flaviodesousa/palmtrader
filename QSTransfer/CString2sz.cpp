//////////////////////////////////////////////////////////
// Converte CString em LPSTR
// $Archive: /QuickSell/Server/CString2sz.cpp $
// $Author: Flávio $
// $Date: 7/04/98 5:58p $
/* $History: CString2sz.cpp $
 * 
 * *****************  Version 2  *****************
 * User: Flávio       Date: 7/04/98    Time: 5:58p
 * Updated in $/QuickSell/Server
 * Colocado em source control
 */

#include <StdAfx.h>

char *CString2sz(char *sz, CString& source)
{
	int len = source.GetLength();
	
	for (int i = 0; i < len; i++)
	{
		sz[i] = (char)source[i];
	}
	sz[i] = '\0';

	return sz;
}