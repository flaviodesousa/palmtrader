// RSSessoes.h : header file
//
// $Archive: /QuickSell/Server/RSSessoes.h $
// $Author: Flávio $
// $Date: 7/04/98 6:08p $
/* $History: RSSessoes.h $
 * 
 * *****************  Version 2  *****************
 * User: Flávio       Date: 7/04/98    Time: 6:08p
 * Updated in $/QuickSell/Server
 * Colocado em source control
 */

#if !defined(AFX_RSSESSOES_H__3C4781C3_BAFE_11D0_A093_00004403E294__INCLUDED_)
#define AFX_RSSESSOES_H__3C4781C3_BAFE_11D0_A093_00004403E294__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
/////////////////////////////////////////////////////////////////////////////
// CRSSessoes recordset

class CRSSessoes : public CRecordset
{
public:
	CRSSessoes(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRSSessoes)

// Field/Param Data
	//{{AFX_FIELD(CRSSessoes, CRecordset)
	int		m_ss_Vendedor;
	CTime	m_ss_Inicio;
	CTime	m_ss_final;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSSessoes)
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

#endif // !defined(AFX_RSSESSOES_H__3C4781C3_BAFE_11D0_A093_00004403E294__INCLUDED_)
