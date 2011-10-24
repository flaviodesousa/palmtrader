// DBBlocos.cpp: implementation of the CDBBlocos class.
//
//////////////////////////////////////////////////////////////////////
// $Archive: /PalmTrader 1/QSTransfer/DBBlocos.cpp $
// $Author: Flávio $
// $Date: 29/04/99 22:01 $
/* $History: DBBlocos.cpp $
 * 
 * *****************  Version 5  *****************
 * User: Flávio       Date: 29/04/99   Time: 22:01
 * Updated in $/PalmTrader 1/QSTransfer
 * Inserido espaçamento extra entre funções
 * 
 * *****************  Version 3  *****************
 * User: Flávio       Date: 24/10/98   Time: 17:39
 * Updated in $/PalmTrader 1/QSTransfer
 * Alteradas chamadas diretas a membros da classe CCeDBDatabase para
 * chamadas equivalentes da classe CDB
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
//#include "pedidos.h"
#include "DBBlocos.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDBBlocos::CDBBlocos()
{
	CCeDBProp SortProperty(CCeDBProp::Type_ULong, en_propInicio);

	m_DBName = _T("Trader Blocos");

	if (!m_db.Exists(m_DBName))
	{
		m_db.Create(m_DBName, 0, 1, &SortProperty);
	}

	m_db.Open(m_DBName, &SortProperty);
}



CDBBlocos::~CDBBlocos()
{

}



BOOL CDBBlocos::Add(DWORD dwInicio, DWORD dwFinal)
{
	CCeDBProp props[2];
	
	props[0] = CCeDBProp(dwInicio, en_propInicio);
	props[1] = CCeDBProp(dwFinal, en_propFinal);

	m_rec.DeleteAllProps();
	m_rec.AddProps(props, 2);

	return m_db.AddRecord(&m_rec);
}



DWORD CDBBlocos::GetFreeNumber()
{
	DWORD dwTheNumber = 0;
	CCeDBProp *propInicio, *propFinal, *propUltimo;

	MoveFirst();

	while (!IsEOF())
	{
		Read();
		propInicio = m_rec.GetPropFromIdent(en_propInicio);
		propFinal = m_rec.GetPropFromIdent(en_propFinal);
		propUltimo = m_rec.GetPropFromIdent(en_propUltimo);

		if (propUltimo == NULL)
		{
			dwTheNumber = propInicio->GetULong();
			break;
		}
		else if (propUltimo->GetULong() < propFinal->GetULong())
		{
			dwTheNumber = propUltimo->GetULong() + 1;
			break;
		}

		MoveNext();
	}

	return dwTheNumber;
}



BOOL CDBBlocos::UseNumber(DWORD dwUsedNumber)
{
	BOOL bUsed = FALSE;
	CCeDBProp *propInicio, *propFinal, *propUltimo, newpropUltimo;

	MoveFirst();

	while (!IsEOF())
	{
		Read();
		propInicio = m_rec.GetPropFromIdent(en_propInicio);
		propFinal = m_rec.GetPropFromIdent(en_propFinal);
		propUltimo = m_rec.GetPropFromIdent(en_propUltimo);

		if (propInicio->GetULong() <= dwUsedNumber && propFinal->GetULong() >= dwUsedNumber)
		{
			if (propUltimo == NULL)
			{
				ASSERT(propInicio->GetULong() == dwUsedNumber);
				newpropUltimo = CCeDBProp(dwUsedNumber, en_propUltimo);
				m_rec.AddProp(&newpropUltimo);
			}
			else
			{
				ASSERT(propUltimo->GetULong() == dwUsedNumber - 1);
				propUltimo->SetULong(dwUsedNumber);
			}

			Write();

			bUsed = TRUE;
			break;
		}

		MoveNext();
	}

	return bUsed;
}



BOOL CDBBlocos::Delete(DWORD dwPedido)
{
	BOOL bDeleted = FALSE;

	MoveFirst();

	while (!IsEOF())
	{
		Read();

		if (m_rec.GetPropFromIdent(en_propInicio)->GetULong() == dwPedido)
		{
			CDB::Delete();
			bDeleted = TRUE;
			break;
		}

		MoveNext();
	}

	return bDeleted;
}



BOOL CDBBlocos::HaveBlocosReserva()
{
	BOOL bHaveThem = FALSE;
	CCeDBProp *propUltimo;

	MoveFirst();

	while (!IsEOF())
	{
		Read();
		propUltimo = m_rec.GetPropFromIdent(en_propUltimo);

		if (propUltimo == NULL)
		{
			bHaveThem = TRUE;
			break;
		}

		MoveNext();
	}

	return bHaveThem;
}
