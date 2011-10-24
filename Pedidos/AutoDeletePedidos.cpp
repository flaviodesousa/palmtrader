// AutoDeletePedidos.cpp: implementation of the CAutoDeletePedidos class.
//
//////////////////////////////////////////////////////////////////////
// $Archive: /PalmTrader 1/Pedidos/AutoDeletePedidos.cpp $
// $Author: Flávio $
// $Date: 11/11/98 15:10 $
/* $History: AutoDeletePedidos.cpp $
 * 
 * *****************  Version 1  *****************
 * User: Flávio       Date: 11/11/98   Time: 15:10
 * Created in $/PalmTrader 1/Pedidos
 * Implementado recurso de eliminação automática de pedidos em função da
 * data da última alteração
 */

#include "stdafx.h"
#include "pedidos.h"
#include "AutoDeletePedidos.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include "PedidosRegistry.h"
#include "DBPedidos.h"
#include "DBItens.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAutoDeletePedidos::CAutoDeletePedidos()
{

}

CAutoDeletePedidos::~CAutoDeletePedidos()
{

}

void CAutoDeletePedidos::Run()
{
	CPedidosRegistry reg;
	DWORD dwAutoDeleteLast, dwAutoDeleteDays;
	CTime Now = CTime::GetCurrentTime();
	DWORD dwNow = Now.GetYear() * 10000L + Now.GetMonth() * 100L + Now.GetDay();

	dwAutoDeleteDays = reg.GetDWord(_T("AutoDelete"), 30);
	dwAutoDeleteLast = reg.GetDWord(_T("AutoDeleteLast"), 0);

	if (dwAutoDeleteLast != dwNow) // could be "dwAutoDeleteLast < dwNow", but I think this way is safer!
	{
		CTimeSpan ThirtyDays(dwAutoDeleteDays, 0, 0, 0);
		CTime OldestPedidoAllowable = Now - ThirtyDays;
		DWORD dwOldestPedidoAllowable = OldestPedidoAllowable.GetYear() * 10000L + OldestPedidoAllowable.GetMonth() * 100L + OldestPedidoAllowable.GetDay();
		CDBPedidos pe;
		CDBItens it;

		pe.MoveFirst();

		while (!pe.IsEOF())
		{
			pe.Read();

			if (pe.GetDataPedido() < dwOldestPedidoAllowable)
			{
				DWORD dwPedidoNumero = pe.GetNumeroPedido();
				if (it.FindFirstItem(dwPedidoNumero))
				{
					do
					{
						it.Delete();
					}
					while (it.FindNextItem());
				}
				pe.Delete();
			}

			pe.MoveNext();
		}

		reg.SetDWord(_T("AutoDeleteLast"), dwNow);
	}
}
