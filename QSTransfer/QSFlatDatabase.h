// QSFlatDatabase.h: interface for the CQSFlatDatabase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QSFLATDATABASE_H__3D121DD4_6FEA_11D1_9F8C_204C4F4F5020__INCLUDED_)
#define AFX_QSFLATDATABASE_H__3D121DD4_6FEA_11D1_9F8C_204C4F4F5020__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CQSFlatDatabase  
{
protected:
	TCHAR *m_filename;
	CFile *m_file;
	WORD m_header_size;
	WORD m_record_size;
	WORD m_current_record;
	WORD m_last_record;

public:
	WORD GetRecordNumber(void);
	void MoveFirst(void);
	CQSFlatDatabase(TCHAR * sFileName, WORD wRecordSize, WORD wHeaderSize = 0);
	virtual ~CQSFlatDatabase();
	void ClearBuffer(void *buffer);
	WORD GetRecordCount();
	BOOL GetRecord(WORD lRecNo, void *buffer);
	BOOL GetRecord(void * buffer);
	void SetRecord(WORD wRecNo);
	void ReadRecord(void * buffer);
	void WriteRecord(void *buffer);
	void AddRecord(void * buffer);
	BOOL IsEOF();
	void Reset(void);

private:
	void ReportError(CFileException *e, int nLine);
};

#endif // !defined(AFX_QSFLATDATABASE_H__3D121DD4_6FEA_11D1_9F8C_204C4F4F5020__INCLUDED_)
