#if !defined(AFX_REQUESTSDLG_H__9B872CAD_6CB0_11D1_9F82_204C4F4F5020__INCLUDED_)
#define AFX_REQUESTSDLG_H__9B872CAD_6CB0_11D1_9F82_204C4F4F5020__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RequestsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRequestsDlg dialog

class CRequestsDlg : public CDialog
{
// Construction
public:
	CRequestsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRequestsDlg)
	enum { IDD = IDD_REQUESTS_DIALOG };
	BOOL	m_request_cobranca;
	BOOL	m_request_venda;
	BOOL	m_request_plano;
	BOOL	m_request_clientes;
	BOOL	m_request_produtos;
	BOOL	m_request_bloco;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRequestsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRequestsDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REQUESTSDLG_H__9B872CAD_6CB0_11D1_9F82_204C4F4F5020__INCLUDED_)
