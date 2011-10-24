// PartialProdutosSynchronization.cpp: implementation of the CPartialProdutosSynchronization class.
//
//////////////////////////////////////////////////////////////////////
// $Archive: /PalmTrader 1/Server/PartialProdutosSynchronization.cpp $
// $Author: Flávio $
// $Date: 25/05/99 15:31 $
/* $History: PartialProdutosSynchronization.cpp $
 * 
 * *****************  Version 3  *****************
 * User: Flávio       Date: 25/05/99   Time: 15:31
 * Updated in $/PalmTrader 1/Server
 * Alterações feitas para o release 1.30
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
 * User: Flávio       Date: 9/07/98    Time: 21:37
 * Created in $/QuickSell/Server
 * Primeira implementação.
 * Incluído tratamento para atualização automática parcial de produtos,
 * preços e clientes.
 */

#include "stdafx.h"
#include "PartialProdutosSynchronization.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPartialProdutosSynchronization::CPartialProdutosSynchronization() :
	CProdutosSynchronization()
{
}

CPartialProdutosSynchronization::~CPartialProdutosSynchronization()
{
}

void CPartialProdutosSynchronization::SendRequest()
{
	char buf[] = "51\012" "/*\012";
	sock.Send((void *)&buf, strlen(buf));
}
