// ListaDePrecosCtrl.cpp : implementation file
//
// $Archive: /QuickSell/Pedidos/ListaDePrecosCtrl.cpp $
// $Author: Flávio $
// $Date: 7/07/98 7:56a $
/* $History: ListaDePrecosCtrl.cpp $
 * 
 * *****************  Version 2  *****************
 * User: Flávio       Date: 7/07/98    Time: 7:56a
 * Updated in $/QuickSell/Pedidos
 * Primeira implementação
 */

#include "stdafx.h"
#include "Pedidos.h"
#include "ListaDePrecosCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListaDePrecosCtrl

CListaDePrecosCtrl::CListaDePrecosCtrl()
{
}



CListaDePrecosCtrl::~CListaDePrecosCtrl()
{
}


BEGIN_MESSAGE_MAP(CListaDePrecosCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CListaDePrecosCtrl)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListaDePrecosCtrl message handlers

BOOL CListaDePrecosCtrl::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	dwStyle |= LVS_OWNERDATA;
	
	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

BOOL CListaDePrecosCtrl::SetItemData(int nItem, DWORD dwValue)
{
    m_ItemData[nItem] = dwValue;
    return  TRUE;
}

DWORD CListaDePrecosCtrl::GetItemData(int nItem)
{
    return m_ItemData[nItem];
}

void CListaDePrecosCtrl::SetItemCount(int nItems)
{
    m_ItemData.SetSize(nItems + 1); // Lowbound is 1
    CListCtrl::SetItemCount(nItems);
}
