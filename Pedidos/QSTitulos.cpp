// QSTitulos.cpp: implementation of the CQSTitulos class.
//
//////////////////////////////////////////////////////////////////////
// $Archive: /PalmTrader 1/Pedidos/QSTitulos.cpp $
// $Author: Flávio $
// $Date: 11/07/98 20:20 $
/* $History: QSTitulos.cpp $
 * 
 * *****************  Version 2  *****************
 * User: Flávio       Date: 11/07/98   Time: 20:20
 * Updated in $/PalmTrader 1/Pedidos
 * Removida referência espúria ao include "QSTransfer.h"
 * 
 * *****************  Version 1  *****************
 * User: Flávio       Date: 10/07/98   Time: 15:23
 * Created in $/PalmTrader 1/QSTransfer
 * Primeira implementação
 */

#include "stdafx.h"
#include "QSTitulos.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

static TCHAR filename[] = _T("\\Pedidos\\Titulos.dat");

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CQSTitulos::CQSTitulos()
: CQSFlatDatabase(filename, sizeof(m_record))
{

}

CQSTitulos::~CQSTitulos()
{

}

void CQSTitulos::Remove(void)
{
	TRY
	{
		CFile::Remove(filename);
	}
	CATCH(CFileException, e)
	{
		// Assume the only error should be
		// a nonexistent file
	}
	END_CATCH;
}

BOOL CQSTitulos::GetRecord(WORD wRecNo)
{
	return CQSFlatDatabase::GetRecord(wRecNo, &m_record);
}

BOOL CQSTitulos::GetRecord(void)
{
	return CQSFlatDatabase::GetRecord(&m_record);
}

void CQSTitulos::ReadRecord(void)
{
	CQSFlatDatabase::ReadRecord(&m_record);
}

void CQSTitulos::WriteRecord(void)
{
	CQSFlatDatabase::WriteRecord(&m_record);
}

void CQSTitulos::AddRecord(void)
{
	CQSFlatDatabase::AddRecord(&m_record);
}

void CQSTitulos::ClearBuffer()
{
	CQSFlatDatabase::ClearBuffer(&m_record);
}
