// QSPedidos.cpp: implementation of the CQSPedidos class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "QSPedidos.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

static TCHAR basename_prefix[] = _T("\\Pedidos\\Bloco");
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

CQSPedidos::CQSPedidos(DWORD dwBloco)
: CQSFlatDatabase(MakeName(dwBloco), sizeof(m_record))
{
	m_bloco = dwBloco;
}

CQSPedidos::~CQSPedidos()
{
	delete filename;
}

void CQSPedidos::Remove(DWORD dwPedido)
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
		// Assume the only error should be
		// a nonexistent file
	}
	END_CATCH;
}

BOOL CQSPedidos::GetRecord(WORD wRecNo)
{
	return CQSFlatDatabase::GetRecord(wRecNo, &m_record);
}

BOOL CQSPedidos::GetRecord(void)
{
	return CQSFlatDatabase::GetRecord(&m_record);
}

void CQSPedidos::ReadRecord(void)
{
	CQSFlatDatabase::ReadRecord(&m_record);
}

void CQSPedidos::WriteRecord(void)
{
	CQSFlatDatabase::WriteRecord(&m_record);
}

void CQSPedidos::AddRecord(void)
{
	CQSFlatDatabase::AddRecord(&m_record);
}

void CQSPedidos::ClearBuffer()
{
	CQSFlatDatabase::ClearBuffer(&m_record);
}

BOOL CQSPedidos::FindByNumero(DWORD lPedido)
{
    if (lPedido >= m_bloco)
    {
        SetRecord((WORD)(lPedido - m_bloco + 1));
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
