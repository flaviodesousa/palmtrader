// Banco de dados residente no HPC
// $Archive: /PalmTrader 1/Pedidos/QSDatabase.h $
// $Author: Flávio $
// $Date: 18/09/98 13:04 $
/* $History: QSDatabase.h $
 * 
 * *****************  Version 4  *****************
 * User: Flávio       Date: 18/09/98   Time: 13:04
 * Updated in $/PalmTrader 1/Pedidos
 * Removida base de dados de Pedidos e de Itens usando formato
 * proprietário
 * 
 * *****************  Version 3  *****************
 * User: Flávio       Date: 10/07/98   Time: 15:23
 * Updated in $/PalmTrader 1/QSTransfer
 * Implementada tabela de títulos
 * 
 * *****************  Version 2  *****************
 * User: Flávio       Date: 7/06/98    Time: 11:48a
 * Updated in $/QuickSell/Pedidos
 * Colocado em source control
 */

#include "QSFlatDatabase.h"

#include "QSProdutos.h"
#include "QSClientes.h"
#include "QSCondicoesVenda.h"
#include "QSCobranca.h"
#include "QSPlanos.h"
#include "QSTitulos.h"