#if !defined(AFX_DIALOGOPCOES_H__E46AA9E3_A6B8_11D1_A011_00004403E294__INCLUDED_)
#define AFX_DIALOGOPCOES_H__E46AA9E3_A6B8_11D1_A011_00004403E294__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DialogOpcoes.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogOpcoes dialog

class CDialogOpcoes : public CDialog
{
// Construction
public:
	CDialogOpcoes(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogOpcoes)
	enum { IDD = IDD_OPCOES };
	CString	m_aplicacao_address;
	UINT	m_aplicacao_port;
	CString	m_db_dsn;
	CString	m_db_senha;
	CString	m_pedidos_ultimo_bloco;
	CString	m_db_usuario;
	DWORD	m_pedidos_tamanho_bloco;
	DWORD	m_pedidos_proximo_numero;
	UINT	m_porta_vendedores;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogOpcoes)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogOpcoes)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGOPCOES_H__E46AA9E3_A6B8_11D1_A011_00004403E294__INCLUDED_)
