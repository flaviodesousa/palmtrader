#if !defined(AFX_DIALOGHISTORICOCLIENTE_H__94AA2CA4_F156_11D0_A101_00004403E294__INCLUDED_)
#define AFX_DIALOGHISTORICOCLIENTE_H__94AA2CA4_F156_11D0_A101_00004403E294__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DialogHistoricoCliente.h : header file
//
// $Archive: /PalmTrader 1/Pedidos/DialogHistoricoCliente.h $
// $Author: Flávio $
// $Date: 11/07/98 20:22 $
/* $History: DialogHistoricoCliente.h $
 * 
 * *****************  Version 3  *****************
 * User: Flávio       Date: 11/07/98   Time: 20:22
 * Updated in $/PalmTrader 1/Pedidos
 * Incluída propriedade m_cliente_codigo para permitir o preenchimento da
 * lista de títulos em aberto
 * 
 * *****************  Version 2  *****************
 * User: Flávio       Date: 7/07/98    Time: 7:52a
 * Updated in $/QuickSell/Pedidos
 * Primeira implementação.
 * Falta suporte a lista de títulos
 */

/////////////////////////////////////////////////////////////////////////////
// CDialogHistoricoCliente dialog

class CDialogHistoricoCliente : public CDialog
{
// Construction
public:
	CDialogHistoricoCliente(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogHistoricoCliente)
	enum { IDD = IDD_DIALOG_HISTORICO_CLIENTE };
	CListCtrl	m_titulos;
	CString	m_disponivel;
	CString	m_cliente;
	CString	m_limite;
	//}}AFX_DATA
	DWORD m_cliente_codigo;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogHistoricoCliente)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogHistoricoCliente)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGHISTORICOCLIENTE_H__94AA2CA4_F156_11D0_A101_00004403E294__INCLUDED_)
