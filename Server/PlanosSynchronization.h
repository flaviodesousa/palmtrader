// PlanosSynchronization.h: interface for the CPlanosSynchronization class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLANOSSYNCHRONIZATION_H__E78D2EB7_A08F_11D1_9FEE_00004403E294__INCLUDED_)
#define AFX_PLANOSSYNCHRONIZATION_H__E78D2EB7_A08F_11D1_9FEE_00004403E294__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "RSPlanos.h"
#include "UserAppSynchronization.h"

class CPlanosSynchronization : public CUserAppSynchronization  
{
	CString strRows[3];
	int nRowCount;
	CRSPlanos pl;

public:
	CPlanosSynchronization();
	virtual ~CPlanosSynchronization();

protected:
	void SendRequest(void);
	BOOL Process(CString& strRow);
};

#endif // !defined(AFX_PLANOSSYNCHRONIZATION_H__E78D2EB7_A08F_11D1_9FEE_00004403E294__INCLUDED_)
