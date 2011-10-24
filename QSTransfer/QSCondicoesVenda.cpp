// QSCondicoesVenda.cpp: implementation of the CQSCondicoesVenda class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "QSCondicoesVenda.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

static TCHAR filename[] = _T("\\Pedidos\\CondicoesVenda.dat");

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CQSCondicoesVenda::CQSCondicoesVenda()
: CQSFlatDatabase(filename, sizeof(m_record))
{

}

CQSCondicoesVenda::~CQSCondicoesVenda()
{

}

void CQSCondicoesVenda::Remove(void)
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

BOOL CQSCondicoesVenda::GetRecord(WORD wRecNo)
{
	return CQSFlatDatabase::GetRecord(wRecNo, &m_record);
}

BOOL CQSCondicoesVenda::GetRecord(void)
{
	return CQSFlatDatabase::GetRecord(&m_record);
}

void CQSCondicoesVenda::ReadRecord(void)
{
	CQSFlatDatabase::ReadRecord(&m_record);
}

void CQSCondicoesVenda::WriteRecord(void)
{
	CQSFlatDatabase::WriteRecord(&m_record);
}

void CQSCondicoesVenda::AddRecord(void)
{
	CQSFlatDatabase::AddRecord(&m_record);
}

void CQSCondicoesVenda::ClearBuffer()
{
	CQSFlatDatabase::ClearBuffer(&m_record);
}

BOOL CQSCondicoesVenda::GetByCodigo(unsigned short codigo)
{
	BOOL bFound = FALSE;
	MoveFirst();
	while (!IsEOF())
	{
		GetRecord();
		{
			CString msg;
			msg.Format(_T("%d %d"), (int)m_record.codigo, (int)codigo);
		}
		if (m_record.codigo == codigo)
		{
			bFound = TRUE;
			break;
		}
	}
	return bFound;
}
