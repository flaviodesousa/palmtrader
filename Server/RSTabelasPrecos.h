// RSTabelasPrecos.h : header file
//
// $Archive: /QuickSell/Server/RSTabelasPrecos.h $
// $Author: Flávio $
// $Date: 7/04/98 6:08p $
/* $History: RSTabelasPrecos.h $
 * 
 * *****************  Version 3  *****************
 * User: Flávio       Date: 7/04/98    Time: 6:08p
 * Updated in $/QuickSell/Server
 * Colocado em source control
 */

#if !defined(AFX_RSTABELASPRECOS_H__A8522233_9F7B_11D1_9FEB_00004403E294__INCLUDED_)
#define AFX_RSTABELASPRECOS_H__A8522233_9F7B_11D1_9FEB_00004403E294__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
/////////////////////////////////////////////////////////////////////////////
// CRSTabelasPrecos recordset

class CRSTabelasPrecos : public CRecordset
{
public:
	CRSTabelasPrecos(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRSTabelasPrecos)

// Field/Param Data
	//{{AFX_FIELD(CRSTabelasPrecos, CRecordset)
	int		m_tp_Codigo;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSTabelasPrecos)
	public:
	virtual CString GetDefaultConnect();    // Default connection string
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RSTABELASPRECOS_H__A8522233_9F7B_11D1_9FEB_00004403E294__INCLUDED_)
