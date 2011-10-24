// QSTitulos.h: interface for the CQSTitulos class.
//
//////////////////////////////////////////////////////////////////////
// $Archive: /PalmTrader 1/QSTransfer/QSTitulos.h $
// $Author: Flávio $
// $Date: 10/07/98 21:53 $
/* $History: QSTitulos.h $
 * 
 * *****************  Version 2  *****************
 * User: Flávio       Date: 10/07/98   Time: 21:53
 * Updated in $/PalmTrader 1/QSTransfer
 * Campos que contém datas mudados de DWORD para char[16]
 * 
 * *****************  Version 1  *****************
 * User: Flávio       Date: 10/07/98   Time: 15:23
 * Created in $/PalmTrader 1/QSTransfer
 * Primeira implementação
 */

#if !defined(AFX_QSTITULOS_H__23080B14_1653_11D2_A117_00004403E294__INCLUDED_)
#define AFX_QSTITULOS_H__23080B14_1653_11D2_A117_00004403E294__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "QSFlatDatabase.h"

class CQSTitulos : public CQSFlatDatabase  
{
public:
    struct
    {
        DWORD cliente;
        DWORD valor;
        char emissao[16];
        char vencimento[16];
        char numero[41];
    } m_record;

public:
	CQSTitulos();
	virtual ~CQSTitulos();
	static void Remove(void);
	BOOL GetRecord(WORD lRecNo);
	BOOL GetRecord(void);
	void ReadRecord(void);
	void WriteRecord(void);
	void AddRecord(void);
	void ClearBuffer(void);

};

#endif // !defined(AFX_QSTITULOS_H__23080B14_1653_11D2_A117_00004403E294__INCLUDED_)
