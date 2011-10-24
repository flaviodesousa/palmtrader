// QSPlanos.h: interface for the CQSPlanos class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QSPLANOS_H__92675435_7536_11D1_9F99_204C4F4F5020__INCLUDED_)
#define AFX_QSPLANOS_H__92675435_7536_11D1_9F99_204C4F4F5020__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "QSFlatDatabase.h"

class CQSPlanos : public CQSFlatDatabase  
{
public:
	struct
	{
		unsigned short codigo;
		char descricao[61];
		unsigned short coluna;
	} m_record;

public:
	BOOL GetByCodigo(unsigned short codigo);
	static void Remove(void);
	BOOL GetRecord(WORD lRecNo);
	BOOL GetRecord(void);
	void ReadRecord(void);
	void WriteRecord(void);
	void AddRecord(void);
	void ClearBuffer(void);
	CQSPlanos();
	virtual ~CQSPlanos();

};

#endif // !defined(AFX_QSPLANOS_H__92675435_7536_11D1_9F99_204C4F4F5020__INCLUDED_)
