// DBBlocos.h: interface for the CDBBlocos class.
//
//////////////////////////////////////////////////////////////////////
// $Archive: /PalmTrader 1/QSTransfer/DBBlocos.h $
// $Author: Fl�vio $
// $Date: 23/09/98 17:59 $
/* $History: DBBlocos.h $
 * 
 * *****************  Version 2  *****************
 * User: Fl�vio       Date: 23/09/98   Time: 17:59
 * Updated in $/PalmTrader 1/QSTransfer
 * Removidas refer�ncias esp�rias ao arquivo "pedidos.h"
 * Na classe CDBBlocos foi adicionado o m�todo HaveBlocosReserva()
 * 
 * *****************  Version 1  *****************
 * User: Fl�vio       Date: 23/09/98   Time: 16:48
 * Created in $/PalmTrader 1/Pedidos
 * Primeira implementa��o. Primeira bateria de testes conclu�da.
 */

#if !defined(AFX_DBBLOCOS_H__3EF3C515_4D8A_11D2_BBB5_0000216E2E31__INCLUDED_)
#define AFX_DBBLOCOS_H__3EF3C515_4D8A_11D2_BBB5_0000216E2E31__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "DB.h"

class CDBBlocos  : public CDB
{
public:
	BOOL HaveBlocosReserva(void);
	BOOL Delete(DWORD dwPedido);
	BOOL UseNumber(DWORD dwUsedNumber);
	DWORD GetFreeNumber(void);
	BOOL Add(DWORD dwInicio, DWORD dwFinal);
	enum
	{
		en_propInicio = 0x1001,
		en_propFinal,
		en_propUltimo
	};
	CDBBlocos();
	virtual ~CDBBlocos();

};

#endif // !defined(AFX_DBBLOCOS_H__3EF3C515_4D8A_11D2_BBB5_0000216E2E31__INCLUDED_)
