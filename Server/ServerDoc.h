// ServerDoc.h : interface of the CServerDoc class
//
/////////////////////////////////////////////////////////////////////////////
// $Archive: /QuickSell/Server/ServerDoc.h $
// $Author: Flávio $
// $Date: 7/04/98 6:10p $
/* $History: ServerDoc.h $
 * 
 * *****************  Version 3  *****************
 * User: Flávio       Date: 7/04/98    Time: 6:10p
 * Updated in $/QuickSell/Server
 * Colocado em source control
 */

#if !defined(AFX_SERVERDOC_H__26EA96FD_68B9_11D1_9F77_204C4F4F5020__INCLUDED_)
#define AFX_SERVERDOC_H__26EA96FD_68B9_11D1_9F77_204C4F4F5020__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "AutoSynchronization.h"
#include "ConnectionThread.h"

class CServerDoc : public CDocument
{
protected: // create from serialization only
	CServerDoc();
	DECLARE_DYNCREATE(CServerDoc)

	CConnectionThread ConnectionThread;
    CAutoSynchronization AutoSynchronization;

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServerDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CServerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CServerDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVERDOC_H__26EA96FD_68B9_11D1_9F77_204C4F4F5020__INCLUDED_)
