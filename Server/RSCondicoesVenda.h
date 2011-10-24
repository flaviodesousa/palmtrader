// RSCondicoesVenda.h : header file
//
// $Archive: /QuickSell/Server/RSCondicoesVenda.h $
// $Author: Flávio $
// $Date: 7/04/98 6:06p $
/* $History: RSCondicoesVenda.h $
 * 
 * *****************  Version 2  *****************
 * User: Flávio       Date: 7/04/98    Time: 6:06p
 * Updated in $/QuickSell/Server
 * Colocado em source control
 */

#if !defined(AFX_RSCONDICOESVENDA_H__A2155547_73CD_11D1_9F95_204C4F4F5020__INCLUDED_)
#define AFX_RSCONDICOESVENDA_H__A2155547_73CD_11D1_9F95_204C4F4F5020__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
/////////////////////////////////////////////////////////////////////////////
// CRSCondicoesVenda recordset

class CRSCondicoesVenda : public CRecordset
{
public:
	CRSCondicoesVenda(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRSCondicoesVenda)

// Field/Param Data
	//{{AFX_FIELD(CRSCondicoesVenda, CRecordset)
	BYTE	m_cv_Codigo;
	BOOL	m_cv_PedePercentual;
	CByteArray	m_cv_TimeStamp;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSCondicoesVenda)
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

#endif // !defined(AFX_RSCONDICOESVENDA_H__A2155547_73CD_11D1_9F95_204C4F4F5020__INCLUDED_)
