// RSCobranca.h : header file
//
// $Archive: /QuickSell/Server/RSCobranca.h $
// $Author: Flávio $
// $Date: 7/04/98 6:05p $
/* $History: RSCobranca.h $
 * 
 * *****************  Version 2  *****************
 * User: Flávio       Date: 7/04/98    Time: 6:05p
 * Updated in $/QuickSell/Server
 * Colocado em source control
 */

#if !defined(AFX_RSCOBRANCA_H__A2155546_73CD_11D1_9F95_204C4F4F5020__INCLUDED_)
#define AFX_RSCOBRANCA_H__A2155546_73CD_11D1_9F95_204C4F4F5020__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
/////////////////////////////////////////////////////////////////////////////
// CRSCobranca recordset

class CRSCobranca : public CRecordset
{
public:
	CRSCobranca(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRSCobranca)

// Field/Param Data
	//{{AFX_FIELD(CRSCobranca, CRecordset)
	CString	m_cb_Codigo;
	CString	m_cb_Descricao;
	CTime	m_cb_TimeStamp;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSCobranca)
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

#endif // !defined(AFX_RSCOBRANCA_H__A2155546_73CD_11D1_9F95_204C4F4F5020__INCLUDED_)
