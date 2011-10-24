// DialogQuantidade.h : header file
//
// $Archive: /PalmTrader 1/Pedidos/DialogQuantidade.h $
// $Author: Flávio $
// $Date: 25/05/99 15:39 $
/* $History: DialogQuantidade.h $
 * 
 * *****************  Version 4  *****************
 * User: Flávio       Date: 25/05/99   Time: 15:39
 * Updated in $/PalmTrader 1/Pedidos
 * Alterações feitas para o release 1.30
 * Generalizada rotina para conversão de números em strings
 * Permitida a alteração individual de preços no pedido
 * Acelerada rotina de localização de produto
 * Incluída rotina genérica para conversão de números em strings
 * Corrigido bug na definição do tamanho do buffer de envio de pacotes TCP
 * nos módulos de sincronização
 * Separada a porta TCP de conexão com os clientes e servidores
 * Incluído método em CPedido para retornar a data do pedido como DWORD,
 * que é usada no módulo de sincronização de pedidos
 * Implementados novos atributos em preços
 * Incluído o script de criação da base SQL
 * 
 * *****************  Version 3  *****************
 * User: Flávio       Date: 13/07/98   Time: 15:40
 * Updated in $/PalmTrader 1/Pedidos
 * Incluído campo "Embalagem Master" no diálogo IDD_DIALOG_QUANTIDADE
 * 
 * *****************  Version 2  *****************
 * User: Flávio       Date: 7/07/98    Time: 8:04a
 * Updated in $/QuickSell/Pedidos
 * Incluídos campos  para exibição da embalagem e do preço unitário
 */

#if !defined(AFX_DIALOGQUANTIDADE_H__0D15CA63_60EA_11D1_9F5F_204C4F4F5020__INCLUDED_)
#define AFX_DIALOGQUANTIDADE_H__0D15CA63_60EA_11D1_9F5F_204C4F4F5020__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
/////////////////////////////////////////////////////////////////////////////
// CDialogQuantidade dialog

class CDialogQuantidade : public CDialog
{
// Construction
public:
	CDialogQuantidade(CWnd* pParent = NULL);   // standard constructor

// Atributes
	DWORD m_dwPreco;        // Preço de referência do produto
	DWORD m_dwPrecoAtual;   // Preço com desconto individual
	WORD m_wQuantidade;

// Dialog Data
	//{{AFX_DATA(CDialogQuantidade)
	enum { IDD = IDD_DIALOG_ITEM };
	CString	m_cod_item;
	CString	m_descricao;
	CString	m_quantidade;
	CString	m_total;
	CString	m_embalagem;
	CString	m_unitario;
	CString	m_preco;
	UINT	m_master;
	double	m_desconto;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogQuantidade)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void UpdateTotal(void);

	// Generated message map functions
	//{{AFX_MSG(CDialogQuantidade)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonCancelaItem();
	afx_msg void OnChangeEditQuantidade();
	afx_msg void OnButtonQuickOK();
	afx_msg void OnChangeEditDesconto();
	afx_msg void OnChangeEditPreco();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGQUANTIDADE_H__0D15CA63_60EA_11D1_9F5F_204C4F4F5020__INCLUDED_)
