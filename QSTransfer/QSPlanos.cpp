// QSPlanos.cpp: implementation of the CQSPlanos class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "QSPlanos.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

static TCHAR filename[] = _T("\\Pedidos\\Planos.dat");

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CQSPlanos::CQSPlanos()
: CQSFlatDatabase(filename, sizeof(m_record))
{

}

CQSPlanos::~CQSPlanos()
{

}

void CQSPlanos::Remove(void)
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

BOOL CQSPlanos::GetRecord(WORD wRecNo)
{
	return CQSFlatDatabase::GetRecord(wRecNo, &m_record);
}

BOOL CQSPlanos::GetRecord(void)
{
	return CQSFlatDatabase::GetRecord(&m_record);
}

void CQSPlanos::ReadRecord(void)
{
	CQSFlatDatabase::ReadRecord(&m_record);
}

void CQSPlanos::WriteRecord(void)
{
	CQSFlatDatabase::WriteRecord(&m_record);
}

void CQSPlanos::AddRecord(void)
{
	CQSFlatDatabase::AddRecord(&m_record);
}

void CQSPlanos::ClearBuffer()
{
	CQSFlatDatabase::ClearBuffer(&m_record);
}

BOOL CQSPlanos::GetByCodigo(unsigned short codigo)
{
	BOOL bFound = FALSE;
	MoveFirst();
	while (!IsEOF())
	{
		GetRecord();
		if (m_record.codigo == codigo)
		{
			bFound = TRUE;
			break;
		}
	}
	return bFound;
}
