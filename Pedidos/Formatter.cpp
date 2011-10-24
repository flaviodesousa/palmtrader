// Formatter.cpp: implementation of the CFormatter class.
// CFormatter: rotinas genéricas para apresentação de dados
//////////////////////////////////////////////////////////////////////
// $Archive: /PalmTrader 1/Pedidos/Formatter.cpp $
// $Author: Flávio $
// $Date: 7/08/98 16:25 $
/* $History: Formatter.cpp $
 * 
 * *****************  Version 2  *****************
 * User: Flávio       Date: 7/08/98    Time: 16:25
 * Updated in $/PalmTrader 1/Pedidos
 * Eliminado bug na exibição de saldos negativos no extrato do cliente.
 * 
 * *****************  Version 1  *****************
 * User: Flávio       Date: 7/05/98    Time: 1:27p
 * Created in $/QuickSell/Pedidos
 * Primeira implementação
 * Rotina para formatar DWORDs como valores monetários (divididos por 100)
 */

#include "stdafx.h"
#include "Pedidos.h"
#include "Formatter.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFormatter::CFormatter()
{

}

CFormatter::~CFormatter()
{

}

CString CFormatter::DWordAsMoney(DWORD dwValue)
{
	signed long lValue = (signed long)dwValue;
    CString strOut;

    strOut.Format(_T("%ld,%02ld"), lValue / 100, lValue % 100);

    return strOut;
}
