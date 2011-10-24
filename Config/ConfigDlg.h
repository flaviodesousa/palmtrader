// ConfigDlg.h : header file
//
// $Archive: /PalmTrader 1/Config/ConfigDlg.h $
// $Author: Fl�vio $
// $Date: 11/11/98 15:12 $
/* $History: ConfigDlg.h $
 * 
 * *****************  Version 6  *****************
 * User: Fl�vio       Date: 11/11/98   Time: 15:12
 * Updated in $/PalmTrader 1/Config
 * Implementado recurso de elimina��o autom�tica de pedidos em fun��o da
 * data da �ltima altera��o
 * Eliminado par�metro "Nome do Vendedor"
 * 
 * *****************  Version 5  *****************
 * User: Fl�vio       Date: 10/07/98   Time: 23:16
 * Updated in $/PalmTrader 1/Config
 * Implementado item de configura��o que regula a permiss�o de venda de
 * itens n�o dispon�veis
 * 
 * *****************  Version 4  *****************
 * User: Fl�vio       Date: 7/05/98    Time: 1:02p
 * Updated in $/QuickSell/QSConfig
 * Inclu�das op��es para exibi��o de pre�os unit�rios
 * 
 * *****************  Version 3  *****************
 * User: Fl�vio       Date: 4/13/98    Time: 1:35a
 * Updated in $/QuickSell/QSConfig
 * Inclu�da op��o para se determinar o tempo em segundos em que a busca
 * autom�tica limpa o texto de busca.
 */

#if !defined(AFX_CONFIGDLG_H__848B5399_6802_11D1_9F76_204C4F4F5020__INCLUDED_)
#define AFX_CONFIGDLG_H__848B5399_6802_11D1_9F76_204C4F4F5020__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CConfigDlg dialog

class CConfigDlg : public CDialog
{
// Construction
public:
	CConfigDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CConfigDlg)
	enum { IDD = IDD_CONFIG_DIALOG };
	CComboBox	m_conexoes_ctrl;
	UINT	m_porta;
	CString	m_senha;
	CString	m_servidor;
	UINT	m_tentativas;
	UINT	m_vendedor_numero;
	CString	m_conexao;
	BOOL	m_exibir_nao_disponiveis;
	UINT	m_autoclear;
	BOOL	m_arredondar;
	BOOL	m_exibir_unitarios;
	BOOL	m_vender_falta;
	UINT	m_autodelete;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CConfigDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGDLG_H__848B5399_6802_11D1_9F76_204C4F4F5020__INCLUDED_)
