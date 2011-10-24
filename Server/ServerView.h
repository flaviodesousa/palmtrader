// ServerView.h : interface of the CServerView class
//
/////////////////////////////////////////////////////////////////////////////
// $Archive: /QuickSell/Server/ServerView.h $
// $Author: Flávio $
// $Date: 7/04/98 6:10p $
/* $History: ServerView.h $
 * 
 * *****************  Version 3  *****************
 * User: Flávio       Date: 7/04/98    Time: 6:10p
 * Updated in $/QuickSell/Server
 * Colocado em source control
 */

#if !defined(AFX_SERVERVIEW_H__26EA96FF_68B9_11D1_9F77_204C4F4F5020__INCLUDED_)
#define AFX_SERVERVIEW_H__26EA96FF_68B9_11D1_9F77_204C4F4F5020__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CServerView : public CFormView
{
protected: // create from serialization only
	CServerView();
	DECLARE_DYNCREATE(CServerView)

public:
	//{{AFX_DATA(CServerView)
	enum { IDD = IDD_SERVER_FORM };
	CListCtrl	m_conexoes;
	CEdit	m_server_status_ctl;
	CString	m_server_status;
	//}}AFX_DATA

// Attributes
public:
	CServerDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServerView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo*);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CServerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CServerView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ServerView.cpp
inline CServerDoc* CServerView::GetDocument()
   { return (CServerDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVERVIEW_H__26EA96FF_68B9_11D1_9F77_204C4F4F5020__INCLUDED_)
