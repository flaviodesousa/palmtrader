// DB.h: interface for the CDB class.
//
//////////////////////////////////////////////////////////////////////
// $Archive: /PalmTrader 1/Pedidos/DB.h $
// $Author: Flávio $
// $Date: 23/09/98 16:48 $
/* $History: DB.h $
 * 
 * *****************  Version 1  *****************
 * User: Flávio       Date: 23/09/98   Time: 16:48
 * Created in $/PalmTrader 1/Pedidos
 * Primeira implementação. Primeira bateria de testes concluída.
 */

#if !defined(AFX_DB_H__B092AA47_4F0F_11D2_BBB8_0000216E2E31__INCLUDED_)
#define AFX_DB_H__B092AA47_4F0F_11D2_BBB8_0000216E2E31__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <wcedb.h>

class CDB  
{
protected:
	CString m_DBName;
	CCeDBDatabase m_db;
	CCeDBRecord m_rec;
	BOOL bNewRecord;
public:
	BOOL MoveLast(void);
	BOOL MovePrev(void);
	BOOL MoveNext(void);
	BOOL MoveFirst(void);
	BOOL Delete(void);
	BOOL IsEOF();
	void SetProp(CCeDBProp *prop);
	virtual BOOL Write(void);
	virtual BOOL Read(void);
	virtual void AddNew(void);
	CDB();
	virtual ~CDB();

};

#endif // !defined(AFX_DB_H__B092AA47_4F0F_11D2_BBB8_0000216E2E31__INCLUDED_)
