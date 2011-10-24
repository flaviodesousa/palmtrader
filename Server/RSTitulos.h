// RSTitulos.h : header file
//
// $Archive: /QuickSell/Server/RSTitulos.h $
// $Author: Flávio $
// $Date: 11/07/98 19:55 $
/* $History: RSTitulos.h $
 * 
 * *****************  Version 3  *****************
 * User: Flávio       Date: 11/07/98   Time: 19:55
 * Updated in $/QuickSell/Server
 * Incluído TimeStamp do título
 * 
 * *****************  Version 2  *****************
 * User: Flávio       Date: 7/04/98    Time: 6:09p
 * Updated in $/QuickSell/Server
 * Colocado em source control
 * Primeira implementação
 */

#if !defined(AFX_RSTITULOS_H__81EBA837_F29E_11D0_A107_00004403E294__INCLUDED_)
#define AFX_RSTITULOS_H__81EBA837_F29E_11D0_A107_00004403E294__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
/////////////////////////////////////////////////////////////////////////////
// CRSTitulos recordset

class CRSTitulos : public CRecordset
{
public:
	CRSTitulos(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRSTitulos)

// Field/Param Data
	//{{AFX_FIELD(CRSTitulos, CRecordset)
	CString	m_ti_Numero;
	long	m_ti_Cliente;
	CString	m_ti_Valor;
	CString	m_ti_Emissao;
	CString	m_ti_Vencimento;
	CTime	m_ti_TimeStamp;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSTitulos)
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

#endif // !defined(AFX_RSTITULOS_H__81EBA837_F29E_11D0_A107_00004403E294__INCLUDED_)
