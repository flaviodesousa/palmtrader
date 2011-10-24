// QSTransferView.h : interface of the CQSTransferView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_QSTRANSFERVIEW_H__9B872CA6_6CB0_11D1_9F82_204C4F4F5020__INCLUDED_)
#define AFX_QSTRANSFERVIEW_H__9B872CA6_6CB0_11D1_9F82_204C4F4F5020__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CQSTransferView : public CFormView
{
protected: // create from serialization only
	CQSTransferView();
	DECLARE_DYNCREATE(CQSTransferView)

protected:
	LONG m_enviados_ultima_posicao;
	LONG m_recebidos_ultima_posicao;
	int m_enviados_ultima_mensagem;
	int m_recebidos_ultima_mensagem;
	UINT m_timer;
	BOOL m_oncomm; // Indica estado dos controles
	int m_refresh_rate;

public:
	//{{AFX_DATA(CQSTransferView)
	enum { IDD = IDD_QSTRANSFER_FORM };
	CButton	m_ask_refill_titulos_ctrl;
	CEdit	m_intervalo_ctrl;
	CEdit	m_volume_recebido_ctrl;
	CEdit	m_log_saida;
	CEdit	m_log_entrada;
	CEdit	m_volume_enviado_ctrl;
	CSliderCtrl	m_atualizacoes_ctrl;
	CButton	m_snd_pedidos_ctrl;
	CButton	m_snd_clientes_ctrl;
	CButton	m_ask_bloco_ctrl;
	CButton	m_ask_refill_produtos_ctrl;
	CButton	m_ask_refill_clientes_ctrl;
	CButton	m_ask_planos_ctrl;
	CButton	m_ask_cobranca_ctrl;
	CButton	m_button_iniciar;
	CButton	m_button_cancelar;
	CString	m_volume_enviado;
	CString	m_volume_recebido;
	BOOL	m_ask_cobranca;
	BOOL	m_ask_planos;
	BOOL	m_ask_refill_clientes;
	BOOL	m_ask_refill_produtos;
	BOOL	m_ask_bloco;
	BOOL	m_snd_pedidos;
	BOOL	m_snd_clientes;
	CString	m_intervalo;
	BOOL	m_ask_refill_titulos;
	//}}AFX_DATA

// Attributes
public:
	CQSTransferDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQSTransferView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CQSTransferView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	void UpdateConnectionStatistics(void);
	void AddLogEntries(CEdit& LogWindow, CList<CString, CString&>& LogQueue, CCriticalSection& LogQueueAccess, LONG& nLastPosition, int& nLastMessage);
	void SetOnComm(BOOL bStatus);
	//{{AFX_MSG(CQSTransferView)
	afx_msg void OnButtonIniciar();
	afx_msg void OnButtonCancelar();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in QSTransferView.cpp
inline CQSTransferDoc* CQSTransferView::GetDocument()
   { return (CQSTransferDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QSTRANSFERVIEW_H__9B872CA6_6CB0_11D1_9F82_204C4F4F5020__INCLUDED_)
