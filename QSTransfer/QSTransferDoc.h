// QSTransferDoc.h : interface of the CQSTransferDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_QSTRANSFERDOC_H__9B872CA4_6CB0_11D1_9F82_204C4F4F5020__INCLUDED_)
#define AFX_QSTRANSFERDOC_H__9B872CA4_6CB0_11D1_9F82_204C4F4F5020__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CQSTransferDoc : public CDocument
{
protected: // create from serialization only
	CQSTransferDoc();
	DECLARE_DYNCREATE(CQSTransferDoc)

// Attributes
public:
	CSessionThread Session;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQSTransferDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CQSTransferDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CQSTransferDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QSTRANSFERDOC_H__9B872CA4_6CB0_11D1_9F82_204C4F4F5020__INCLUDED_)
