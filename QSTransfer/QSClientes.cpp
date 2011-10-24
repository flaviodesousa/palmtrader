// QSClientes.cpp: implementation of the CQSClientes class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "QSClientes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

static TCHAR filename[] = _T("\\Pedidos\\Clientes.dat");

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CQSClientes::CQSClientes()
: CQSFlatDatabase(filename, sizeof(m_record))
{
}

CQSClientes::~CQSClientes()
{
}

void CQSClientes::Remove(void)
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

BOOL CQSClientes::GetRecord(WORD wRecNo)
{
	return CQSFlatDatabase::GetRecord(wRecNo, &m_record);
}

BOOL CQSClientes::GetRecord(void)
{
	return CQSFlatDatabase::GetRecord(&m_record);
}

void CQSClientes::ReadRecord(void)
{
	CQSFlatDatabase::ReadRecord(&m_record);
}

void CQSClientes::WriteRecord(void)
{
	CQSFlatDatabase::WriteRecord(&m_record);
}

void CQSClientes::AddRecord(void)
{
	CQSFlatDatabase::AddRecord(&m_record);
}

void CQSClientes::ClearBuffer()
{
	CQSFlatDatabase::ClearBuffer(&m_record);
}

BOOL CQSClientes::FindByCodigo(DWORD dwCodigo)
{
    BOOL bFound = FALSE;

    for (int i=1; i <= m_last_record; i++)
    {
        GetRecord(i);

        if (m_record.codigo == dwCodigo)
        {
            bFound = TRUE;
            break;
        }
    }

    return bFound;
}
