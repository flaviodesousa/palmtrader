// QSItens.h: interface for the CQSItens class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QSITENS_H__A25EDE44_748E_11D1_9F98_204C4F4F5020__INCLUDED_)
#define AFX_QSITENS_H__A25EDE44_748E_11D1_9F98_204C4F4F5020__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "QSFlatDatabase.h"

class CQSItens : public CQSFlatDatabase  
{
public:
	struct
	{
		DWORD	produto;
		DWORD	quantidade_pedida;
		DWORD	quantidade_confirmada;
		DWORD	preco;
		WORD	proximo_item;
	} m_record;
protected:
	static TCHAR *m_filename;
	DWORD m_bloco;

public:
	static void Remove(DWORD dwBloco);
	BOOL GetRecord(WORD lRecNo);
	BOOL GetRecord(void);
	void ReadRecord(void);
	void WriteRecord(void);
	void AddRecord(void);
	void ClearBuffer(void);
	CQSItens(DWORD bloco);
	virtual ~CQSItens();
	friend TCHAR *MakeName(DWORD dwBloco);

};

#endif // !defined(AFX_QSITENS_H__A25EDE44_748E_11D1_9F98_204C4F4F5020__INCLUDED_)
