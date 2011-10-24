// PrecosSynchronization.h: interface for the CPrecosSynchronization class.
//
// $Archive: /PalmTrader 1/Server/PrecosSynchronization.h $
// $Author: Flávio $
// $Date: 5/08/99 13:59 $
/* $History: PrecosSynchronization.h $
 * 
 * *****************  Version 6  *****************
 * User: Flávio       Date: 5/08/99    Time: 13:59
 * Updated in $/PalmTrader 1/Server
 * Corrigido tamanho do vetor de itens
 */

//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRECOSSYNCHRONIZATION_H__EF2786D5_A111_11D1_9FF0_00004403E294__INCLUDED_)
#define AFX_PRECOSSYNCHRONIZATION_H__EF2786D5_A111_11D1_9FF0_00004403E294__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "RSPrecos.h"
#include "UserAppSynchronization.h"

class CPrecosSynchronization : public CUserAppSynchronization  
{
	CString strRows[12];
	int nTabela;
	int nRowCount;
	CRSPrecos pr;

	//>>>>[BEGIN] Remover este trecho posteriormente
	CStdioFile m_Log;
	CString m_strLog;
	int m_comparados;
	int m_alterados;
	int m_adicionados;
	void LogString(CString str);
	//<<<<[END]

public:
	CPrecosSynchronization(int nTabelaPrecos);
	virtual ~CPrecosSynchronization();

protected:
	virtual void SendRequest(void);
	virtual BOOL Process(CString& strRow);
};

#endif // !defined(AFX_PRECOSSYNCHRONIZATION_H__EF2786D5_A111_11D1_9FF0_00004403E294__INCLUDED_)
