// RSBlocos.h : header file
//
// $Archive: /QuickSell/Server/RSBlocos.h $
// $Author: Flávio $
// $Date: 7/04/98 6:05p $
/* $History: RSBlocos.h $
 * 
 * *****************  Version 2  *****************
 * User: Flávio       Date: 7/04/98    Time: 6:05p
 * Updated in $/QuickSell/Server
 * Colocado em source control
 */

#if !defined(AFX_RSBLOCOS_H__A2155544_73CD_11D1_9F95_204C4F4F5020__INCLUDED_)
#define AFX_RSBLOCOS_H__A2155544_73CD_11D1_9F95_204C4F4F5020__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CRSBlocos recordset

class CRSBlocos : public CRecordset
{
public:
	CRSBlocos(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRSBlocos)

// Field/Param Data
	//{{AFX_FIELD(CRSBlocos, CRecordset)
	long	m_PrimeiroPedido;
	long	m_UltimoPedido;
	CTime	m_Entrega;
	int		m_Vendedor;
	BOOL	m_BlocoAberto;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSBlocos)
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

#endif // !defined(AFX_RSBLOCOS_H__A2155544_73CD_11D1_9F95_204C4F4F5020__INCLUDED_)
