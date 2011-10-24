// DBPedidos.cpp: implementation of the CDBPedidos class.
//
//////////////////////////////////////////////////////////////////////
// $Archive: /PalmTrader 1/QSTransfer/DBPedidos.cpp $
// $Author: Flávio $
// $Date: 23/09/98 17:59 $
/* $History: DBPedidos.cpp $
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
#include "DBPedidos.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDBPedidos::CDBPedidos(WORD wSortOrder)
{
	props[en_PedidoNumero	- DBPEDIDOS_BASEID] = CCeDBProp(CCeDBProp::Type_ULong,	en_PedidoNumero);
	props[en_ClienteCodigo	- DBPEDIDOS_BASEID] = CCeDBProp(CCeDBProp::Type_ULong,	en_ClienteCodigo);
	props[en_CondicaoVenda	- DBPEDIDOS_BASEID] = CCeDBProp(CCeDBProp::Type_UShort,	en_CondicaoVenda);
	props[en_Plano			- DBPEDIDOS_BASEID] = CCeDBProp(CCeDBProp::Type_UShort,	en_Plano);
	props[en_Desconto		- DBPEDIDOS_BASEID] = CCeDBProp(CCeDBProp::Type_UShort,	en_Desconto);
	props[en_ReterPedido	- DBPEDIDOS_BASEID] = CCeDBProp(CCeDBProp::Type_UShort,	en_ReterPedido);
	props[en_Cobranca		- DBPEDIDOS_BASEID] = CCeDBProp(CCeDBProp::Type_String,	en_Cobranca);
	props[en_Diagnostico	- DBPEDIDOS_BASEID] = CCeDBProp(CCeDBProp::Type_String,	en_Diagnostico);
	props[en_PedidoEnviado	- DBPEDIDOS_BASEID] = CCeDBProp(CCeDBProp::Type_UShort,	en_PedidoEnviado);
	props[en_Data			- DBPEDIDOS_BASEID] = CCeDBProp(CCeDBProp::Type_ULong,	en_Data);

	m_DBName = _T("Trader Pedidos");

	if (!m_db.Exists(m_DBName))
	{
		CCeDBProp SortProperties[3];

		SortProperties[0] = CCeDBProp(CCeDBProp::Type_ULong, en_PedidoNumero);
		SortProperties[1] = CCeDBProp(CCeDBProp::Type_ULong, en_Data, CCeDBProp::Sort_Descending);
		SortProperties[2] = CCeDBProp(CCeDBProp::Type_ULong, en_ClienteCodigo);

		m_db.Create(m_DBName, 0, 3, SortProperties);
	}

	CCeDBProp SortProperty(CCeDBProp::Type_ULong /*All three are ULongs*/, wSortOrder);

	CEOID oid = m_db.Open(m_DBName, &SortProperty);

	if (!oid)
	{
		DWORD dwErrCode = ::GetLastError();
		CString str;

		str.Format(_T("The error was %ld"), dwErrCode);
		AfxMessageBox(str, MB_ICONERROR);
	}
}



CDBPedidos::~CDBPedidos()
{

}



void CDBPedidos::SetNumeroPedido(DWORD dwNumeroPedido)
{
	props[en_PedidoNumero-DBPEDIDOS_BASEID].SetULong(dwNumeroPedido);
	SetProp(&props[en_PedidoNumero-DBPEDIDOS_BASEID]);
}



void CDBPedidos::SetCodigoCliente(DWORD dwCodigoCliente)
{
	props[en_ClienteCodigo-DBPEDIDOS_BASEID].SetULong(dwCodigoCliente);
	SetProp(&props[en_ClienteCodigo-DBPEDIDOS_BASEID]);
}



void CDBPedidos::SetCondicaoVenda(WORD wCondicaoVenda)
{
	props[en_CondicaoVenda-DBPEDIDOS_BASEID].SetUShort(wCondicaoVenda);
	SetProp(&props[en_CondicaoVenda-DBPEDIDOS_BASEID]);
}



void CDBPedidos::SetPlano(WORD wPlano)
{
	props[en_Plano-DBPEDIDOS_BASEID].SetUShort(wPlano);
	SetProp(&props[en_Plano-DBPEDIDOS_BASEID]);
}



void CDBPedidos::SetDesconto(WORD wDesconto)
{
	props[en_Desconto-DBPEDIDOS_BASEID].SetUShort(wDesconto);
	SetProp(&props[en_Desconto-DBPEDIDOS_BASEID]);
}



void CDBPedidos::SetReterPedido(BOOL bReterPedido)
{
	props[en_ReterPedido-DBPEDIDOS_BASEID].SetUShort(bReterPedido);
	SetProp(&props[en_ReterPedido-DBPEDIDOS_BASEID]);
}



void CDBPedidos::SetCodigoCobranca(CString strCobranca)
{
	props[en_Cobranca-DBPEDIDOS_BASEID].SetString(strCobranca.GetBuffer(33));
	strCobranca.ReleaseBuffer();
	SetProp(&props[en_Cobranca-DBPEDIDOS_BASEID]);
}



void CDBPedidos::SetDiagnostico(CString strDiagnostico)
{
	props[en_Diagnostico-DBPEDIDOS_BASEID].SetString(strDiagnostico.GetBuffer(256));
	strDiagnostico.ReleaseBuffer();
	SetProp(&props[en_Diagnostico-DBPEDIDOS_BASEID]);
}



void CDBPedidos::SetPedidoEnviado(BOOL bPedidoEnviado)
{
	props[en_PedidoEnviado-DBPEDIDOS_BASEID].SetUShort(bPedidoEnviado);
	SetProp(&props[en_PedidoEnviado-DBPEDIDOS_BASEID]);
}



void CDBPedidos::SetDataPedido(DWORD dwDataPedido)
{
	props[en_Data-DBPEDIDOS_BASEID].SetULong(dwDataPedido);
	SetProp(&props[en_Data-DBPEDIDOS_BASEID]);
}



DWORD	CDBPedidos::GetDataPedido(void)
{
	return m_rec.GetPropFromIdent(en_Data)->GetULong();
}



BOOL	CDBPedidos::GetPedidoEnviado(void)
{
	BOOL bResult;
	CCeDBProp *prop = m_rec.GetPropFromIdent(en_PedidoEnviado);
	if (prop == NULL)
	{
		bResult = FALSE;
	}
	else
	{
		bResult = prop->GetUShort();
	}
	return bResult;
}



CString	CDBPedidos::GetDiagnostico(void)
{
	CCeDBProp *prop = m_rec.GetPropFromIdent(en_Diagnostico);
	CString str;
	if (prop == NULL)
	{
		str.Empty();
	}
	else
	{
		str = CString(prop->GetString());
	}

	return str;
}



CString	CDBPedidos::GetCodigoCobranca(void)
{
	return CString(m_rec.GetPropFromIdent(en_Cobranca)->GetString());
}



BOOL	CDBPedidos::GetReterPedido(void)
{
	return m_rec.GetPropFromIdent(en_ReterPedido)->GetUShort();
}



WORD	CDBPedidos::GetDesconto(void)
{
	return m_rec.GetPropFromIdent(en_Desconto)->GetUShort();
}



WORD	CDBPedidos::GetPlano(void)
{
	return m_rec.GetPropFromIdent(en_Plano)->GetUShort();
}



WORD	CDBPedidos::GetCondicaoVenda(void)
{
	return m_rec.GetPropFromIdent(en_CondicaoVenda)->GetUShort();
}



DWORD	CDBPedidos::GetCodigoCliente(void)
{
	return m_rec.GetPropFromIdent(en_ClienteCodigo)->GetULong();
}



DWORD	CDBPedidos::GetNumeroPedido(void)
{
	return m_rec.GetPropFromIdent(en_PedidoNumero)->GetULong();
}



BOOL CDBPedidos::Find(DWORD dwNumeroPedido)
{
	CCeDBProp propSearch(dwNumeroPedido, en_PedidoNumero);

	if (m_db.SeekFirstEqual(propSearch))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
