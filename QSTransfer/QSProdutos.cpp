// QSProdutos.cpp: implementation of the CQSProdutos class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "QSProdutos.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

static TCHAR filename[] = _T("\\Pedidos\\Produtos.dat");
static TCHAR keyfile[] = _T("\\Pedidos\\Produtos.key");
static CQSProdutos *ya_this; // Outro 'this' pointer para a rotina de sort

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CQSProdutos::CQSProdutos()
: CQSFlatDatabase(filename, sizeof(m_record))
{
    TRY
    {
        m_keyfile = new CFile(
            keyfile,
            CFile::modeCreate|CFile::modeNoTruncate|CFile::modeReadWrite);

	    if (m_keyfile->GetLength() >= sizeof(m_nKeysInIndex))
	    {
		    m_keyfile->Read(&m_nKeysInIndex, sizeof m_nKeysInIndex);
	    }
	    else
	    {
            m_nKeysInIndex = 0;
		    m_keyfile->SeekToBegin();
		    m_keyfile->SetLength(0);
		    m_keyfile->Write(&m_nKeysInIndex, sizeof m_nKeysInIndex);
	    }

        m_index = new WORD[m_nKeysInIndex];

        if (m_nKeysInIndex)
        {
            // Carrega índice para a memória
            m_keyfile->Read(m_index, m_nKeysInIndex * sizeof WORD);
        }
    }
    CATCH(CFileException, e)
    {
        e->ReportError();
    }
    END_CATCH;
}

CQSProdutos::~CQSProdutos()
{
    delete m_keyfile;
}

void CQSProdutos::Remove(void)
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

BOOL CQSProdutos::GetRecord(WORD wRecNo)
{
	return CQSFlatDatabase::GetRecord(wRecNo, &m_record);
}

BOOL CQSProdutos::GetRecord(void)
{
	return CQSFlatDatabase::GetRecord(&m_record);
}

void CQSProdutos::ReadRecord(void)
{
	CQSFlatDatabase::ReadRecord(&m_record);
}

void CQSProdutos::WriteRecord(void)
{
	CQSFlatDatabase::WriteRecord(&m_record);
}

void CQSProdutos::AddRecord(void)
{
	CQSFlatDatabase::AddRecord(&m_record);
}

void CQSProdutos::ClearBuffer()
{
	CQSFlatDatabase::ClearBuffer(&m_record);
}

void CQSProdutos::Reindex()
{
    delete m_index;
    m_index = new WORD[m_nKeysInIndex = m_last_record];
    m_codigos = new DWORD[m_nKeysInIndex + 1];

    for (int i = 0; i < m_last_record; i++)
    {
        GetRecord(m_index[i] = i + 1);
        m_codigos[i+1] = m_record.codigo;
    }

    // Cria uma referência a this usável pelo método estático _Compare
    ya_this = this; 

    qsort(m_index, (size_t)m_nKeysInIndex, sizeof WORD, _Compare);

    delete m_codigos;

    m_keyfile->SeekToBegin();
    m_keyfile->SetLength(0);
    m_keyfile->Write(&m_nKeysInIndex, sizeof m_nKeysInIndex);
    m_keyfile->Write(m_index, (size_t)((sizeof WORD) * m_nKeysInIndex));
}

int CQSProdutos::_Compare(const void * first, const void * second)
{
    DWORD codigo[2];

    codigo[0] = ya_this->m_codigos[*(WORD *)first];

    codigo[1] = ya_this->m_codigos[*(WORD *)second];

    if (codigo[0] < codigo[1])
    {
        return -1;
    }
    else if (codigo[0] > codigo[1])
    {
        return 1;
    }
    else // (codigo[0] == codigo[1])
    {
        return 0;
    }
}

BOOL CQSProdutos::FindByCodigo(DWORD dwCodigo)
{
    WORD wLower, wUpper, wMiddle;
    BOOL bFound = FALSE;

    wLower = 0;
    wUpper = m_nKeysInIndex;

    while (TRUE)
    {
        wMiddle = wLower + (wUpper - wLower) / 2;

        GetRecord(m_index[wMiddle]);
        if (m_record.codigo == dwCodigo)
        {
            bFound = TRUE;
            break;
        }
        else if (wLower >= wUpper)
        {
            bFound = FALSE;
            break;
        }
        else if (m_record.codigo > dwCodigo)
        {
            wUpper = wMiddle;
        }
        else // m_record.codigo < dwCodigo
        {
            if (wLower == wMiddle)
            {
                wLower++;
            }
            else
            {
                wLower = wMiddle;
            }
        }
    }

    return bFound;
}
