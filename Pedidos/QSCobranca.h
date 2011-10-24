// QSCobranca.h: interface for the CQSCobranca class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QSCOBRANCA_H__92675436_7536_11D1_9F99_204C4F4F5020__INCLUDED_)
#define AFX_QSCOBRANCA_H__92675436_7536_11D1_9F99_204C4F4F5020__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "QSFlatDatabase.h"

class CQSCobranca : public CQSFlatDatabase  
{
public:
	struct
	{
		char codigo[11];
		char descricao[61];
	} m_record;

public:
	static void Remove(void);
	BOOL GetRecord(WORD lRecNo);
	BOOL GetRecord(void);
	void ReadRecord(void);
	void WriteRecord(void);
	void AddRecord(void);
	void ClearBuffer(void);
public:
	BOOL GetByCodigo(const TCHAR *codigo);
	CQSCobranca();
	virtual ~CQSCobranca();

};

#endif // !defined(AFX_QSCOBRANCA_H__92675436_7536_11D1_9F99_204C4F4F5020__INCLUDED_)
