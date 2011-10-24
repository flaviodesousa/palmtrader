// RSPlanos.h : header file
//
// $Archive: /QuickSell/Server/RSPlanos.h $
// $Author: Flávio $
// $Date: 7/04/98 6:07p $
/* $History: RSPlanos.h $
 * 
 * *****************  Version 2  *****************
 * User: Flávio       Date: 7/04/98    Time: 6:07p
 * Updated in $/QuickSell/Server
 * Colocado em source control
 */

#if !defined(AFX_RSPLANOS_H__92675434_7536_11D1_9F99_204C4F4F5020__INCLUDED_)
#define AFX_RSPLANOS_H__92675434_7536_11D1_9F99_204C4F4F5020__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
/////////////////////////////////////////////////////////////////////////////
// CRSPlanos recordset

class CRSPlanos : public CRecordset
{
public:
	CRSPlanos(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRSPlanos)

// Field/Param Data
	//{{AFX_FIELD(CRSPlanos, CRecordset)
	BYTE	m_pl_Codigo;
	CString	m_pl_Descricao;
	BYTE	m_pl_ColunaPreco;
	CTime	m_pl_TimeStamp;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSPlanos)
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

#endif // !defined(AFX_RSPLANOS_H__92675434_7536_11D1_9F99_204C4F4F5020__INCLUDED_)
