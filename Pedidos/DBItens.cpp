// DBItens.cpp: implementation of the CDBItens class.
//
//////////////////////////////////////////////////////////////////////
// $Archive: /PalmTrader 1/Pedidos/DBItens.cpp $
// $Author: Flávio $
// $Date: 13/05/99 22:31 $
/* $History: DBItens.cpp $
 * 
 * *****************  Version 3  *****************
 * User: Flávio       Date: 13/05/99   Time: 22:31
 * Updated in $/PalmTrader 1/Pedidos
 * Incluído atributo Desconto
 * 
 * *****************  Version 2  *****************
 * User: Flávio       Date: 23/09/98   Time: 17:59
 * Updated in $/PalmTrader 1/QSTransfer
 * Removidas referências espúrias ao arquivo "pedidos.h"
 * Na classe CDBBlocos foi adicionado o método HaveBlocosReserva()
 * 
 * *****************  Version 1  *****************
 * User: Flávio       Date: 23/09/98   Time: 16:48
 * Created in $/PalmTrader 1/Pedidos
 * Primeira implementação. Primeira bateria de testes concluída.
 */

#include "stdafx.h"
#include "DBItens.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDBItens::CDBItens()
{
	props[en_Pedido				- DBITENS_BASEID] = CCeDBProp(CCeDBProp::Type_ULong,	en_Pedido);
	props[en_Produto			- DBITENS_BASEID] = CCeDBProp(CCeDBProp::Type_ULong,	en_Produto);
	props[en_QuantidadePedida	- DBITENS_BASEID] = CCeDBProp(CCeDBProp::Type_ULong,	en_QuantidadePedida);
	props[en_QuantidadeAtendida	- DBITENS_BASEID] = CCeDBProp(CCeDBProp::Type_ULong,	en_QuantidadeAtendida);
	props[en_Preco				- DBITENS_BASEID] = CCeDBProp(CCeDBProp::Type_ULong,	en_Preco);
	props[en_Desconto			- DBITENS_BASEID] = CCeDBProp(CCeDBProp::Type_ULong,	en_Desconto);

	CCeDBProp SortProperty(CCeDBProp::Type_ULong, en_Pedido);

	m_DBName = _T("Trader Itens");

	if (!m_db.Exists(m_DBName))
	{
		m_db.Create(m_DBName, 0, 1, &SortProperty);
	}

	m_db.Open(m_DBName, &SortProperty);
}

CDBItens::~CDBItens()
{

}

void CDBItens::SetPedido(DWORD dwPedido)
{
	props[en_Pedido - DBITENS_BASEID].SetULong(dwPedido);
	SetProp(&props[en_Pedido - DBITENS_BASEID]);
}

void CDBItens::SetProduto(DWORD dwProduto)
{
	props[en_Produto - DBITENS_BASEID].SetULong(dwProduto);
	SetProp(&props[en_Produto - DBITENS_BASEID]);
}

void CDBItens::SetQuantidadePedida(DWORD dwQuantidadePedida)
{
	props[en_QuantidadePedida - DBITENS_BASEID].SetULong(dwQuantidadePedida);
	SetProp(&props[en_QuantidadePedida - DBITENS_BASEID]);
}

void CDBItens::SetQuantidadeAtendida(DWORD dwQuantidadeAtendida)
{
	props[en_QuantidadeAtendida - DBITENS_BASEID].SetULong(dwQuantidadeAtendida);
	SetProp(&props[en_QuantidadeAtendida - DBITENS_BASEID]);
}

void CDBItens::SetPreco(DWORD dwPreco)
{
	props[en_Preco - DBITENS_BASEID].SetULong(dwPreco);
	SetProp(&props[en_Preco - DBITENS_BASEID]);
}

void CDBItens::SetDesconto(DWORD dwDesconto)
{
	props[en_Desconto - DBITENS_BASEID].SetULong(dwDesconto);
	SetProp(&props[en_Desconto - DBITENS_BASEID]);
}

DWORD CDBItens::GetPedido()
{
	return m_rec.GetPropFromIdent(en_Pedido)->GetULong();
}

DWORD CDBItens::GetProduto()
{
	return m_rec.GetPropFromIdent(en_Produto)->GetULong();
}

DWORD CDBItens::GetQuantidadePedida()
{
	return m_rec.GetPropFromIdent(en_QuantidadePedida)->GetULong();
}

DWORD CDBItens::GetQuantidadeAtendida()
{
	DWORD dwValue;
	CCeDBProp *prop = m_rec.GetPropFromIdent(en_QuantidadeAtendida);
	if (prop == NULL)
	{
		dwValue = 0;
	}
	else
	{
		dwValue = prop->GetULong();
	}
	return dwValue;
}

DWORD CDBItens::GetPreco()
{
	return m_rec.GetPropFromIdent(en_Preco)->GetULong();
}

DWORD CDBItens::GetDesconto()
{
	DWORD dwValue;
	CCeDBProp *prop = m_rec.GetPropFromIdent(en_Desconto);
	if (prop == NULL)
	{
		dwValue = 0;
	}
	else
	{
		dwValue = prop->GetULong();
	}
	return dwValue;
}

BOOL CDBItens::FindFirstItem(DWORD dwPedido)
{
	propSearch = CCeDBProp(dwPedido, en_Pedido);

	if (m_db.SeekFirstEqual(propSearch))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CDBItens::FindNextItem()
{
	if (m_db.SeekNextEqual(propSearch))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CDBItens::FindItem(DWORD dwPedido, DWORD dwProduto)
{
	BOOL bFound = FALSE;

	if (FindFirstItem(dwPedido))
	{
		do
		{
			Read();

			if (GetProduto() == dwProduto)
			{
				bFound = TRUE;
				break;
			}
		} while (FindNextItem());
	}

	return bFound;
}
