// Configuration.cpp: implementation of the CConfiguration class.
//
//////////////////////////////////////////////////////////////////////
// $Archive: /QuickSell/Server/Configuration.cpp $
// $Author: Fl�vio $
// $Date: 21/07/98 17:34 $
/* $History: Configuration.cpp $
 * 
 * *****************  Version 2  *****************
 * User: Fl�vio       Date: 21/07/98   Time: 17:34
 * Updated in $/QuickSell/Server
 * Primeira implementa��o
 */

#include "stdafx.h"
#include "Configuration.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CConfiguration::CConfiguration()
{

}

CConfiguration::~CConfiguration()
{

}

CString CConfiguration::GetDSN()
{
	return _T("ODBC;DSN=ZTech;UID=sa;PWD=");
}
