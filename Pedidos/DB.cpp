// DB.cpp: implementation of the CDB class.
//
//////////////////////////////////////////////////////////////////////
// $Archive: /PalmTrader 1/QSTransfer/DB.cpp $
// $Author: Flávio $
// $Date: 23/09/98 17:59 $
/* $History: DB.cpp $
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
#include "DB.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDB::CDB()
{

}

CDB::~CDB()
{

}

void CDB::AddNew()
{
	m_rec.DeleteAllProps();
	bNewRecord = TRUE;
}

BOOL CDB::Read()
{
	BOOL bSuccess;
	bSuccess = m_db.ReadCurrRecord(&m_rec);
	bNewRecord = FALSE;

	return bSuccess;
}


BOOL CDB::Write()
{
	BOOL bSuccess;

	if (bNewRecord)
	{
		bSuccess = m_db.AddRecord(&m_rec);
	}
	else
	{
		bSuccess = m_db.WriteCurrRecord(&m_rec);
	}

	return bSuccess;
}

void CDB::SetProp(CCeDBProp * prop)
{
	CCeDBProp *curProp = m_rec.GetPropFromIdent(prop->GetIdent());
	if (curProp == NULL)
	{
		m_rec.AddProp(prop);
	}
	else
	{
		*curProp = *prop;
	}
}

BOOL CDB::IsEOF()
{
	return m_db.m_bEOF || m_db.GetNumRecords() == 0;
}

BOOL CDB::Delete()
{
	return m_db.DeleteCurrRecord();
}

BOOL CDB::MoveFirst()
{
	BOOL bResult;

	if (m_db.GetNumRecords() == 0)
	{
		bResult = FALSE;
	}
	else
	{
		CEOID Result = m_db.SeekFirst();
		if (!Result)
		{
			DWORD dwErrCode = ::GetLastError();
			CString str;

			str.Format(_T("The error was %ld"), dwErrCode);
			AfxMessageBox(str, MB_ICONERROR);
		}
		bResult = (Result != 0);
	}

	return bResult;
}

BOOL CDB::MoveNext()
{
	return m_db.SeekNext() != 0;
}

BOOL CDB::MovePrev()
{
	return m_db.SeekPrev() != 0;
}

BOOL CDB::MoveLast()
{
	return m_db.SeekLast() != 0;
}
