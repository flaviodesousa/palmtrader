// ListaDePrecosCtrl.h : header file
//
// $Archive: /QuickSell/Pedidos/ListaDePrecosCtrl.h $
// $Author: Flávio $
// $Date: 7/07/98 8:04a $
/* $History: ListaDePrecosCtrl.h $
 * 
 * *****************  Version 2  *****************
 * User: Flávio       Date: 7/07/98    Time: 8:04a
 * Updated in $/QuickSell/Pedidos
 * Métodos básicos implementados. Classe ainda não funcional
 */

#if !defined(AFX_LISTADEPRECOSCTRL_H__A5699F53_0709_11D2_A0DB_00004403E294__INCLUDED_)
#define AFX_LISTADEPRECOSCTRL_H__A5699F53_0709_11D2_A0DB_00004403E294__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
#include <afxtempl.h>

/////////////////////////////////////////////////////////////////////////////
// CListaDePrecosCtrl window

class CListaDePrecosCtrl : public CListCtrl
{
    CArray<DWORD, DWORD &> m_ItemData;
// Construction
public:
	CListaDePrecosCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListaDePrecosCtrl)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual void SetItemCount(int nItems);
	virtual DWORD GetItemData(int nItem);
	virtual BOOL SetItemData(int nItem, DWORD dwValue);
	virtual ~CListaDePrecosCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CListaDePrecosCtrl)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTADEPRECOSCTRL_H__A5699F53_0709_11D2_A0DB_00004403E294__INCLUDED_)
