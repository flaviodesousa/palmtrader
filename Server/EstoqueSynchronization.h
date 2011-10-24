// EstoqueSynchronization.h: interface for the CEstoqueSynchronization class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ESTOQUESYNCHRONIZATION_H__EF2786D3_A111_11D1_9FF0_00004403E294__INCLUDED_)
#define AFX_ESTOQUESYNCHRONIZATION_H__EF2786D3_A111_11D1_9FF0_00004403E294__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "RSProdutos.h"
#include "UserAppSynchronization.h"

class CEstoqueSynchronization : public CUserAppSynchronization  
{
	CString strRows[2];
	int nRowCount;
	CRSProdutos pd;

public:
	CEstoqueSynchronization();
	virtual ~CEstoqueSynchronization();

protected:
	void SendRequest(void);
	BOOL Process(CString& strRow);
};

#endif // !defined(AFX_ESTOQUESYNCHRONIZATION_H__EF2786D3_A111_11D1_9FF0_00004403E294__INCLUDED_)
