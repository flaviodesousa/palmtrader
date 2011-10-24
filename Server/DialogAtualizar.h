// DialogAtualizar.h : header file
//
// $Archive: /QuickSell/Server/DialogAtualizar.h $
// $Author: Flávio $
// $Date: 9/07/98 21:34 $
/* $History: DialogAtualizar.h $
 * 
 * *****************  Version 7  *****************
 * User: Flávio       Date: 9/07/98    Time: 21:34
 * Updated in $/QuickSell/Server
 * Incluído tratamento para atualização automática parcial de produtos,
 * preços e clientes.
 * 
 * *****************  Version 6  *****************
 * User: Flávio       Date: 7/04/98    Time: 6:03p
 * Updated in $/QuickSell/Server
 * Acrescentado suporte a atualização de títulos
 * 
 * *****************  Version 5  *****************
 * User: Flávio       Date: 6/26/98    Time: 1:48p
 * Updated in $/QuickSell/Server
 * Incluído suporte a atualização automática da base de dados do server
 * 
 * *****************  Version 4  *****************
 * User: Flávio       Date: 6/25/98    Time: 8:02p
 * Updated in $/QuickSell/Server
 * Removido tratamento manual do botão "Iniciar...", este botão agora
 * retorna IDOK
 * Incluído cabeçalho padrão
 */

#if !defined(AFX_DIALOGATUALIZAR_H__D5738B33_9E58_11D1_9FE8_00004403E294__INCLUDED_)
#define AFX_DIALOGATUALIZAR_H__D5738B33_9E58_11D1_9FE8_00004403E294__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
/////////////////////////////////////////////////////////////////////////////
// CDialogAtualizar dialog

class CDialogAtualizar : public CDialog
{
// Construction
public:
	CDialogAtualizar(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogAtualizar)
	enum { IDD = IDD_ATUALIZAR };
	BOOL	m_atualizar_clientes;
	BOOL	m_atualizar_codigos_de_cobranca;
	BOOL	m_atualizar_planos;
	BOOL	m_atualizar_precos;
	BOOL	m_atualizar_produtos;
	BOOL	m_atualizar_estoque;
	BOOL	m_atualizar_tabelas;
	BOOL	m_atualizar_vendedores;
	BOOL	m_paralelo;
	BOOL	m_atualizar_titulos;
	BOOL	m_atualizar_clientes_partial;
	BOOL	m_atualizar_precos_partial;
	BOOL	m_atualizar_produtos_partial;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogAtualizar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogAtualizar)
	afx_msg void OnButtonAvancado();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGATUALIZAR_H__D5738B33_9E58_11D1_9FE8_00004403E294__INCLUDED_)
