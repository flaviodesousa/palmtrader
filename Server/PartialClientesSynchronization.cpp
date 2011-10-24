// PartialClientesSynchronization.cpp: implementation of the CPartialClientesSynchronization class.
//
//////////////////////////////////////////////////////////////////////
// $Archive: /PalmTrader 1/Server/PartialClientesSynchronization.cpp $
// $Author: Fl�vio $
// $Date: 25/05/99 15:31 $
/* $History: PartialClientesSynchronization.cpp $
 * 
 * *****************  Version 3  *****************
 * User: Fl�vio       Date: 25/05/99   Time: 15:31
 * Updated in $/PalmTrader 1/Server
 * Altera��es feitas para o release 1.30
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
 * User: Fl�vio       Date: 9/07/98    Time: 21:37
 * Created in $/QuickSell/Server
 * Primeira implementa��o.
 * Inclu�do tratamento para atualiza��o autom�tica parcial de produtos,
 * pre�os e clientes.
 */

#include "stdafx.h"
#include "PartialClientesSynchronization.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPartialClientesSynchronization::CPartialClientesSynchronization() :
	CClientesSynchronization()
{
}

CPartialClientesSynchronization::~CPartialClientesSynchronization()
{
}

void CPartialClientesSynchronization::SendRequest()
{
	char buf[] = "50\012" "/*\012";
	sock.Send((void *)&buf, strlen(buf));
}
