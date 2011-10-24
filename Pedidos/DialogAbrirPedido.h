#if !defined(AFX_DIALOGABRIRPEDIDO_H__FDBFFC53_77A6_11D1_9F9D_204C4F4F5020__INCLUDED_)
#define AFX_DIALOGABRIRPEDIDO_H__FDBFFC53_77A6_11D1_9F9D_204C4F4F5020__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DialogAbrirPedido.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogAbrirPedido dialog

class CDialogAbrirPedido : public CDialog
{
protected:
	DWORD m_pedido;
// Construction
public:
	DWORD GetPedidoNumero(void);
	CDialogAbrirPedido(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogAbrirPedido)
	enum { IDD = IDD_DIALOG_ABRIR_PEDIDO };
	CListCtrl	m_pedidos;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogAbrirPedido)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void PopulateList(void);
	BOOL IdentificaPedido(void);

	// Generated message map functions
	//{{AFX_MSG(CDialogAbrirPedido)
	afx_msg void OnClickListPedidos(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGABRIRPEDIDO_H__FDBFFC53_77A6_11D1_9F9D_204C4F4F5020__INCLUDED_)
