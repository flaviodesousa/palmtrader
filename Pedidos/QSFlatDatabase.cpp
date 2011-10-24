// QSFlatDatabase.cpp: implementation of the CQSFlatDatabase class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "QSFlatDatabase.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CQSFlatDatabase::CQSFlatDatabase(TCHAR *sFileName, WORD wRecordSize, WORD wHeaderSize)
{
	m_filename = sFileName;
	m_header_size = wHeaderSize;
	m_record_size = wRecordSize;

	TRY
	{
		m_file = new CFile(
			m_filename,
			CFile::modeCreate|CFile::modeNoTruncate|CFile::modeReadWrite);
	}
	CATCH(CFileException, e)
	{
		e->ReportError();
	}
	END_CATCH;

	if (m_file->GetLength() >= sizeof(m_last_record))
	{
		TRY
		{
			m_file->Read(&m_last_record, sizeof m_last_record);
		}
		CATCH(CFileException, e)
		{
			e->ReportError();
		}
		END_CATCH;
	}
	else
	{
		Reset();
	}
	m_current_record = 1;
}

CQSFlatDatabase::~CQSFlatDatabase()
{
	TRY
	{
		m_file->Close();
	}
	CATCH(CFileException, e)
	{
		e->ReportError();
	}
	END_CATCH;
	delete m_file;
}

BOOL CQSFlatDatabase::IsEOF()
{
	return (m_current_record > m_last_record);
}

void CQSFlatDatabase::AddRecord(void * buffer)
{
	m_current_record = ++m_last_record;
	TRY
	{
		m_file->SeekToBegin();
		m_file->Write(&m_last_record, sizeof(m_last_record));
		m_file->SeekToEnd();
	}
	CATCH(CFileException, e)
	{
		e->ReportError();
	}
	END_CATCH;
	WriteRecord(buffer);
}

void CQSFlatDatabase::WriteRecord(void * buffer)
{
	TRY
	{
		m_file->Write(buffer, m_record_size);
	}
	CATCH(CFileException, e)
	{
		e->ReportError();
	}
	END_CATCH;
}

BOOL CQSFlatDatabase::GetRecord(WORD wRecNo, void * buffer)
{
	if (wRecNo <= m_last_record)
	{
		SetRecord(wRecNo);
		ReadRecord(buffer);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void CQSFlatDatabase::ReadRecord(void * buffer)
{
	TRY
	{
		m_file->Read(buffer, m_record_size);
	}
	CATCH(CFileException, e)
	{
		e->ReportError();
	}
	END_CATCH;
}

BOOL CQSFlatDatabase::GetRecord(void * buffer)
{
	BOOL bRetCode = GetRecord(m_current_record, buffer);
	++m_current_record;
	return bRetCode;
}

void CQSFlatDatabase::SetRecord(WORD wRecNo)
{
	TRY
	{
		m_file->Seek(
			sizeof(m_last_record) + m_header_size + (wRecNo - 1) * m_record_size,
			CFile::begin);
	}
	CATCH(CFileException, e)
	{
		e->ReportError();
	}
	END_CATCH;
	m_current_record = wRecNo;
}

void CQSFlatDatabase::Reset()
{
	m_last_record = 0;
	TRY
	{
		m_file->SeekToBegin();
		m_file->SetLength(0);
		m_file->Write(&m_last_record, sizeof m_last_record);
	}
	CATCH(CFileException, e)
	{
		e->ReportError();
	}
	END_CATCH;
}

void CQSFlatDatabase::ReportError(CFileException *e, int nLine)
{
	e->ReportError();
	/* Perhaps someday this stuff will be useful...
	CString msg, line;

	line.Format(_T("CFile Exception %d at line %d"), nLine);
	
	switch(e->m_cause)
	{
	case CFileException::none: msg = _T("No error occurred."); break;
	case CFileException::generic: msg = _T("An unspecified error occurred."); break;
	case CFileException::fileNotFound: msg = _T("The file could not be located."); break;
	case CFileException::badPath: msg = _T("All or part of the path is invalid."); break;
	case CFileException::tooManyOpenFiles: msg = _T("The permitted number of open files was exceeded."); break;
	case CFileException::accessDenied: msg = _T("The file could not be accessed."); break;
	case CFileException::invalidFile: msg = _T("There was an attempt to use an invalid file handle."); break;
	case CFileException::removeCurrentDir: msg = _T("The current working directory cannot be removed."); break;
	case CFileException::directoryFull: msg = _T("There are no more directory entries."); break;
	case CFileException::badSeek: msg = _T("There was an error trying to set the file pointer."); break;
	case CFileException::hardIO: msg = _T("There was a hardware error."); break;
	case CFileException::sharingViolation: msg = _T("SHARE.EXE was not loaded, or a shared region was locked."); break;
	case CFileException::lockViolation: msg = _T("There was an attempt to lock a region that was already locked."); break;
	case CFileException::diskFull: msg = _T("The disk is full."); break;
	case CFileException::endOfFile: msg = _T("The end of file was reached."); break;
	default: msg = _T("Unknown cause");
	}

	AfxMessageBox(msg + line);
	*/
}

WORD CQSFlatDatabase::GetRecordCount()
{
	return m_last_record;
}

void CQSFlatDatabase::ClearBuffer(void * buffer)
{
	memset(buffer, 0x0, m_record_size);
}

void CQSFlatDatabase::MoveFirst()
{
	SetRecord(1);
}

WORD CQSFlatDatabase::GetRecordNumber()
{
	return m_current_record;
}
