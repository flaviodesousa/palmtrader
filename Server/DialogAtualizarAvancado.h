// DialogAtualizarAvancado.h : header file
//
// $Archive: /QuickSell/Server/DialogAtualizarAvancado.h $
// $Author: Flávio $
// $Date: 9/07/98 21:34 $
/* $History: DialogAtualizarAvancado.h $
 * 
 * *****************  Version 4  *****************
 * User: Flávio       Date: 9/07/98    Time: 21:34
 * Updated in $/QuickSell/Server
 * Incluído tratamento para atualização automática parcial de produtos,
 * preços e clientes.
 * 
 * *****************  Version 3  *****************
 * User: Flávio       Date: 7/04/98    Time: 6:03p
 * Updated in $/QuickSell/Server
 * Acrescentado suporte a atualização automática de títulos
 * 
 * *****************  Version 2  *****************
 * User: Flávio       Date: 6/26/98    Time: 1:48p
 * Updated in $/QuickSell/Server
 * Incluído suporte a atualização automática da base de dados do server
 */

#if !defined(AFX_DIALOGATUALIZARAVANCADO_H__7C1B9A85_ED96_11D0_A0FE_00004403E294__INCLUDED_)
#define AFX_DIALOGATUALIZARAVANCADO_H__7C1B9A85_ED96_11D0_A0FE_00004403E294__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
/////////////////////////////////////////////////////////////////////////////
// CDialogAtualizarAvancado dialog

class CDialogAtualizarAvancado : public CDialog
{
// Construction
public:
	CDialogAtualizarAvancado(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogAtualizarAvancado)
	enum { IDD = IDD_ATUALIZAR_AVANCADO };
	short	m_repeat_clientes;
	short	m_repeat_cobranca;
	short	m_repeat_estoque;
	short	m_repeat_planos;
	short	m_repeat_precos;
	short	m_repeat_produtos;
	short	m_repeat_tabelas;
	short	m_repeat_vendedores;
	short	m_start_clientes;
	short	m_start_cobranca;
	short	m_start_estoque;
	short	m_start_planos;
	short	m_start_precos;
	short	m_start_produtos;
	short	m_start_tabelas;
	short	m_start_vendedores;
	short	m_repeat_titulos;
	short	m_start_titulos;
	short	m_repeat_precos_partial;
	short	m_repeat_produtos_partial;
	short	m_repeat_clientes_partial;
	short	m_start_clientes_partial;
	short	m_start_precos_partial;
	short	m_start_produtos_partial;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogAtualizarAvancado)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogAtualizarAvancado)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGATUALIZARAVANCADO_H__7C1B9A85_ED96_11D0_A0FE_00004403E294__INCLUDED_)
