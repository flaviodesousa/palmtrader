// QSCondicoesVenda.h: interface for the CQSCondicoesVenda class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QSCONDICOESVENDA_H__92675437_7536_11D1_9F99_204C4F4F5020__INCLUDED_)
#define AFX_QSCONDICOESVENDA_H__92675437_7536_11D1_9F99_204C4F4F5020__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "QSFlatDatabase.h"

class CQSCondicoesVenda : public CQSFlatDatabase  
{
public:
	struct
	{
		unsigned short codigo;
		unsigned short pede_percentual;
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
	BOOL GetByCodigo(unsigned short codigo);
	CQSCondicoesVenda();
	virtual ~CQSCondicoesVenda();

};

#endif // !defined(AFX_QSCONDICOESVENDA_H__92675437_7536_11D1_9F99_204C4F4F5020__INCLUDED_)
