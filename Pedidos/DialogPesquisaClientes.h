// DialogPesquisaClientes.h : header file
//
// $Archive: /PalmTrader 1/Pedidos/DialogPesquisaClientes.h $
// $Author: Fl�vio $
// $Date: 21/07/98 17:18 $
/* $History: DialogPesquisaClientes.h $
 * 
 * *****************  Version 4  *****************
 * User: Fl�vio       Date: 21/07/98   Time: 17:18
 * Updated in $/PalmTrader 1/Pedidos
 * Suporte a atribui��o autom�tica do c�digo de cobran�a do cliente
 * 
 * *****************  Version 3  *****************
 * User: Fl�vio       Date: 4/22/98    Time: 2:00a
 * Updated in $/QuickSell/Pedidos
 * Inclu�do suporte a localiza��o de clientes pelo c�digo.
 * Inclu�do campo com op��o para "n�o faturar" que, no caso, gera uma
 * condi��o de venda igual a '3'.
 * Alterado formato de grava��o dos pedidos que passam agora a registrar o
 * c�digo do produto e do cliente ao inv�s dos n�meros de registro.
 * Aumentada detec��o de altera��es no pedido, evitando perda de dados.
 * 
 * *****************  Version 2  *****************
 * User: Fl�vio       Date: 4/03/98    Time: 3:04a
 * Updated in $/QuickSell/Pedidos
 * Acrescentado suporte a teclado.
 * Mudada a ordem das colunas, a coluna principal passa a ser o nome do
 * cliente.
 */

#if !defined(AFX_DIALOGPESQUISACLIENTES_H__7A769233_6B30_11D1_9F7C_204C4F4F5020__INCLUDED_)
#define AFX_DIALOGPESQUISACLIENTES_H__7A769233_6B30_11D1_9F7C_204C4F4F5020__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
/////////////////////////////////////////////////////////////////////////////
// CDialogPesquisaClientes dialog

class CDialogPesquisaClientes : public CDialog
{
public:
	DWORD m_cliente_codigo;
	CString m_cliente_codigo_str;
	CString m_cliente_nome;
	CString m_cobranca_codigo;
protected:
	CQSClientes m_clientes_db;

// Construction
public:
	CDialogPesquisaClientes(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogPesquisaClientes)
	enum { IDD = IDD_DIALOG_CLIENTES };
	CListCtrl	m_clientes;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogPesquisaClientes)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL IdentificaCliente(void);

	// Generated message map functions
	//{{AFX_MSG(CDialogPesquisaClientes)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickListClientes(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGPESQUISACLIENTES_H__7A769233_6B30_11D1_9F7C_204C4F4F5020__INCLUDED_)
