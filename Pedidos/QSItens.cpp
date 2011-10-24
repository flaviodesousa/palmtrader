// QSItens.cpp: implementation of the CQSItens class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "QSItens.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

static TCHAR basename_prefix[] = _T("\\Pedidos\\Itens");
static TCHAR basename_sufix[] = _T(".dat");
static TCHAR *filename;

static TCHAR *MakeName(DWORD dwBloco)
{
	filename = new TCHAR[sizeof(basename_prefix) + sizeof(basename_sufix) + 6];

	_stprintf(
		filename, 
		_T("%s%06ld%s"), 
		basename_prefix,
		dwBloco,
		basename_sufix);

	return filename;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CQSItens::CQSItens(DWORD dwBloco)
: CQSFlatDatabase(MakeName(dwBloco), sizeof(m_record))
{
	m_bloco = dwBloco;
}

CQSItens::~CQSItens()
{
	delete filename;
}

void CQSItens::Remove(DWORD dwPedido)
{
	TCHAR filename[128];
	_stprintf(
		filename, 
		_T("%s%06ld%s"), 
		basename_prefix,
		dwPedido,
		basename_sufix);
	TRY
	{
		CFile::Remove(filename);
	}
	CATCH(CFileException, e)
	{
		// Assuming the only error should be
		// a nonexistent file
	}
	END_CATCH;
}

BOOL CQSItens::GetRecord(WORD wRecNo)
{
	return CQSFlatDatabase::GetRecord(wRecNo, &m_record);
}

BOOL CQSItens::GetRecord(void)
{
	return CQSFlatDatabase::GetRecord(&m_record);
}

void CQSItens::ReadRecord(void)
{
	CQSFlatDatabase::ReadRecord(&m_record);
}

void CQSItens::WriteRecord(void)
{
	CQSFlatDatabase::WriteRecord(&m_record);
}

void CQSItens::AddRecord(void)
{
	CQSFlatDatabase::AddRecord(&m_record);
}

void CQSItens::ClearBuffer()
{
	CQSFlatDatabase::ClearBuffer(&m_record);
}
