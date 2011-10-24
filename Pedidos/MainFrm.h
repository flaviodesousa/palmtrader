// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__33B20CCB_5FA4_11D1_9F58_204C4F4F5020__INCLUDED_)
#define AFX_MAINFRM_H__33B20CCB_5FA4_11D1_9F58_204C4F4F5020__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CMainFrame : public CFrameWnd
{
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnCbExibirSomentePedido();
	afx_msg void OnCbExibirTodosProdutos();
	afx_msg void OnUpdateCbExibirSomentePedido(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCbExibirTodosProdutos(CCmdUI* pCmdUI);
	afx_msg void OnExibirSomentePedido();
	afx_msg void OnExibirTodosProdutos();
	afx_msg void OnUpdateExibirSomentePedido(CCmdUI* pCmdUI);
	afx_msg void OnUpdateExibirTodosProdutos(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__33B20CCB_5FA4_11D1_9F58_204C4F4F5020__INCLUDED_)
