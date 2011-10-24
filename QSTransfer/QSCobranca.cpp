// QSCobranca.cpp: implementation of the CQSCobranca class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "QSCobranca.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

static TCHAR filename[] = _T("\\Pedidos\\Cobranca.dat");

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CQSCobranca::CQSCobranca()
: CQSFlatDatabase(filename, sizeof(m_record))
{

}

CQSCobranca::~CQSCobranca()
{

}

void CQSCobranca::Remove(void)
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

BOOL CQSCobranca::GetRecord(WORD wRecNo)
{
	return CQSFlatDatabase::GetRecord(wRecNo, &m_record);
}

BOOL CQSCobranca::GetRecord(void)
{
	return CQSFlatDatabase::GetRecord(&m_record);
}

void CQSCobranca::ReadRecord(void)
{
	CQSFlatDatabase::ReadRecord(&m_record);
}

void CQSCobranca::WriteRecord(void)
{
	CQSFlatDatabase::WriteRecord(&m_record);
}

void CQSCobranca::AddRecord(void)
{
	CQSFlatDatabase::AddRecord(&m_record);
}

void CQSCobranca::ClearBuffer()
{
	CQSFlatDatabase::ClearBuffer(&m_record);
}

BOOL CQSCobranca::GetByCodigo(const TCHAR * codigo)
{
	BOOL bFound = FALSE;
	CString strCodigo;

	MoveFirst();
	while (!IsEOF())
	{
		GetRecord();
		strCodigo = m_record.codigo;
		if (_tcscmp(strCodigo, codigo) == 0)
		{
			bFound = TRUE;
			break;
		}
	}
	return bFound;
}
