// QSTransferView.cpp : implementation of the CQSTransferView class
//

#include "stdafx.h"
#include "QSTransfer.h"

#include "QSDatabase.h"

#include "SessionThread.h"
#include "QSTransferDoc.h"
#include "QSTransferView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define XXX(MSG) m_intervalo_ctrl.SetWindowText(_T(MSG));
#else
#define XXX(MSG) /**/
#endif

/////////////////////////////////////////////////////////////////////////////
// CQSTransferView

IMPLEMENT_DYNCREATE(CQSTransferView, CFormView)

BEGIN_MESSAGE_MAP(CQSTransferView, CFormView)
	//{{AFX_MSG_MAP(CQSTransferView)
	ON_BN_CLICKED(IDC_BUTTON_INICIAR, OnButtonIniciar)
	ON_BN_CLICKED(IDC_BUTTON_CANCELAR, OnButtonCancelar)
	ON_WM_TIMER()
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQSTransferView construction/destruction

CQSTransferView::CQSTransferView()
	: CFormView(CQSTransferView::IDD)
{
	//{{AFX_DATA_INIT(CQSTransferView)
	m_volume_enviado = _T("");
	m_volume_recebido = _T("");
	m_ask_cobranca = FALSE;
	m_ask_planos = FALSE;
	m_ask_refill_clientes = FALSE;
	m_ask_refill_produtos = FALSE;
	m_ask_bloco = FALSE;
	m_snd_pedidos = FALSE;
	m_snd_clientes = FALSE;
	m_intervalo = _T("");
	m_ask_refill_titulos = FALSE;
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CQSTransferView::~CQSTransferView()
{
}

void CQSTransferView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CQSTransferView)
	DDX_Control(pDX, IDC_CHECK_REFILL_TITULOS, m_ask_refill_titulos_ctrl);
	DDX_Control(pDX, IDC_EDIT_INTERVALO, m_intervalo_ctrl);
	DDX_Control(pDX, IDC_EDIT_RECEBIDOS, m_volume_recebido_ctrl);
	DDX_Control(pDX, IDC_LOG_SAIDA, m_log_saida);
	DDX_Control(pDX, IDC_LOG_ENTRADA, m_log_entrada);
	DDX_Control(pDX, IDC_EDIT_ENVIADOS, m_volume_enviado_ctrl);
	DDX_Control(pDX, IDC_SLIDER_ATUALIZACOES, m_atualizacoes_ctrl);
	DDX_Control(pDX, IDC_CHECK_SEND_PEDIDOS, m_snd_pedidos_ctrl);
	DDX_Control(pDX, IDC_CHECK_SEND_CLIENTES, m_snd_clientes_ctrl);
	DDX_Control(pDX, IDC_CHECK_REQUEST_BLOCO, m_ask_bloco_ctrl);
	DDX_Control(pDX, IDC_CHECK_REFILL_PRODUTOS, m_ask_refill_produtos_ctrl);
	DDX_Control(pDX, IDC_CHECK_REFILL_CLIENTES, m_ask_refill_clientes_ctrl);
	DDX_Control(pDX, IDC_CHECK_PLANOS, m_ask_planos_ctrl);
	DDX_Control(pDX, IDC_CHECK_COBRANCA, m_ask_cobranca_ctrl);
	DDX_Control(pDX, IDC_BUTTON_INICIAR, m_button_iniciar);
	DDX_Control(pDX, IDC_BUTTON_CANCELAR, m_button_cancelar);
	DDX_Text(pDX, IDC_EDIT_ENVIADOS, m_volume_enviado);
	DDX_Text(pDX, IDC_EDIT_RECEBIDOS, m_volume_recebido);
	DDX_Check(pDX, IDC_CHECK_COBRANCA, m_ask_cobranca);
	DDX_Check(pDX, IDC_CHECK_PLANOS, m_ask_planos);
	DDX_Check(pDX, IDC_CHECK_REFILL_CLIENTES, m_ask_refill_clientes);
	DDX_Check(pDX, IDC_CHECK_REFILL_PRODUTOS, m_ask_refill_produtos);
	DDX_Check(pDX, IDC_CHECK_REQUEST_BLOCO, m_ask_bloco);
	DDX_Check(pDX, IDC_CHECK_SEND_PEDIDOS, m_snd_pedidos);
	DDX_Check(pDX, IDC_CHECK_SEND_CLIENTES, m_snd_clientes);
	DDX_Text(pDX, IDC_EDIT_INTERVALO, m_intervalo);
	DDX_Check(pDX, IDC_CHECK_REFILL_TITULOS, m_ask_refill_titulos);
	//}}AFX_DATA_MAP
}

BOOL CQSTransferView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CQSTransferView diagnostics

#ifdef _DEBUG
void CQSTransferView::AssertValid() const
{
	CFormView::AssertValid();
}

void CQSTransferView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CQSTransferDoc* CQSTransferView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CQSTransferDoc)));
	return (CQSTransferDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CQSTransferView message handlers

void CQSTransferView::OnButtonIniciar() 
{
	UpdateData();

	CQSTransferDoc *doc = GetDocument();

	doc->Session.m_ask_cobranca        = m_ask_cobranca;
	doc->Session.m_ask_refill_titulos  = m_ask_refill_titulos;
	doc->Session.m_ask_planos          = m_ask_planos;
	doc->Session.m_ask_refill_clientes = m_ask_refill_clientes;
	doc->Session.m_ask_refill_produtos = m_ask_refill_produtos;
	doc->Session.m_ask_bloco           = m_ask_bloco;
	doc->Session.m_snd_pedidos         = m_snd_pedidos;
	doc->Session.m_snd_clientes        = m_snd_clientes;

	if (doc->Session.Open())
	{
		SetOnComm(TRUE);
	}
	else
	{
		UpdateConnectionStatistics();
	}
}

void CQSTransferView::OnButtonCancelar() 
{
	CQSTransferDoc *doc = GetDocument();

	if (!doc->Session.IsOpen())
	{
		AfxMessageBox(_T("Sessão ainda não iniciada..."), MB_ICONEXCLAMATION);
		return;
	}

	doc->Session.Close();

	//SetOnComm(FALSE);
}

void CQSTransferView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	m_snd_pedidos = TRUE;
	m_snd_clientes = TRUE;
	m_intervalo = _T("");
	m_refresh_rate = 1;
	m_atualizacoes_ctrl.SetRange(1, 10, TRUE);

	UpdateData(FALSE);
}

void CQSTransferView::OnTimer(UINT nIDEvent) 
{
	XXX("In-0");
	UpdateConnectionStatistics();
	XXX("Exiting");

	if (!GetDocument()->Session.IsOpen())
	{
		SetOnComm(FALSE);
	}

	CFormView::OnTimer(nIDEvent);
	XXX("Out");
}

void CQSTransferView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	m_refresh_rate = m_atualizacoes_ctrl.GetPos();

	if (m_timer)
	{
		KillTimer(m_timer);
		m_timer = SetTimer(1, m_refresh_rate*1000, NULL);
	}
	
	CFormView::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CQSTransferView::SetOnComm(BOOL bStatus)
{
	m_oncomm = bStatus;
	if (bStatus)
	{
		m_ask_bloco_ctrl.EnableWindow(FALSE);
		m_ask_refill_produtos_ctrl.EnableWindow(FALSE);
		m_ask_refill_clientes_ctrl.EnableWindow(FALSE);
		m_ask_planos_ctrl.EnableWindow(FALSE);
		m_ask_refill_titulos_ctrl.EnableWindow(FALSE);
		m_ask_cobranca_ctrl.EnableWindow(FALSE);
		m_snd_pedidos_ctrl.EnableWindow(FALSE);
		m_snd_clientes_ctrl.EnableWindow(FALSE);
		m_button_iniciar.EnableWindow(FALSE);
		m_button_cancelar.EnableWindow();

		m_enviados_ultima_posicao =
		m_recebidos_ultima_posicao =
		m_enviados_ultima_mensagem =
		m_recebidos_ultima_mensagem = 0;

		m_log_entrada.SetWindowText(_T(""));
		m_log_saida.SetWindowText(_T(""));
		m_timer = SetTimer(1, m_refresh_rate * 1000, NULL);
	}
	else
	{
		KillTimer(m_timer); m_timer = 0;

		m_ask_bloco_ctrl.EnableWindow();
		m_ask_refill_produtos_ctrl.EnableWindow();
		m_ask_refill_clientes_ctrl.EnableWindow();
		m_ask_planos_ctrl.EnableWindow();
		m_ask_refill_titulos_ctrl.EnableWindow();
		m_ask_cobranca_ctrl.EnableWindow();
		m_snd_pedidos_ctrl.EnableWindow();
		m_snd_clientes_ctrl.EnableWindow();
		m_button_iniciar.EnableWindow();
		m_button_cancelar.EnableWindow(FALSE);

        AfxMessageBox(_T("Transferência concluída.\nDesconecte o modem"), MB_ICONEXCLAMATION);
	}

	UpdateConnectionStatistics();
}

void CQSTransferView::UpdateConnectionStatistics()
{
	CString msg;
	CSessionThread *s = &GetDocument()->Session;

	XXX("In-3");

	msg.Format(_T("%d"), s->m_bytes_sent);
	m_volume_enviado_ctrl.SetWindowText(msg);

	msg.Format(_T("%d"), s->m_bytes_received);
	m_volume_recebido_ctrl.SetWindowText(msg);

	CTimeSpan ts;
	if (s->IsOpen())
		ts = CTime::GetCurrentTime() - s->m_timeSessionStart;
	else
		ts = s->m_timeSessionEnd - s->m_timeSessionStart;
	m_intervalo.Format(_T("%ld:%02d"), ts.GetTotalMinutes(), ts.GetSeconds());
	m_intervalo_ctrl.SetWindowText(m_intervalo);

	XXX("In-4");

	AddLogEntries(
		m_log_saida, 
		s->m_events_sent, 
		s->m_SentEventsGateKeeper,
		m_enviados_ultima_posicao, 
		m_enviados_ultima_mensagem);

	XXX("In-5");

	AddLogEntries(
		m_log_entrada,
		s->m_events_received,
		s->m_ReceivedEventsGateKeeper,
		m_recebidos_ultima_posicao,
		m_recebidos_ultima_mensagem);
}

void CQSTransferView::AddLogEntries(CEdit& LogWindow, 
									CList<CString, CString&>& LogQueue, 
									CCriticalSection& LogQueueAccess,
									LONG& nLastPosition, 
									int& nLastMessage)
{
	CTime timeStartLoop = CTime::GetCurrentTime();
	XXX("In-6");

	LogQueueAccess.Lock();

	while (!LogQueue.IsEmpty())
	{
		CTimeSpan TimeSpan = CTime::GetCurrentTime() - timeStartLoop;
		if (TimeSpan.GetTotalSeconds() >= m_refresh_rate)
		{
			break;
		}
		XXX("In-7");

		CString msg = LogQueue.RemoveHead();
		int nMsgCode = _wtoi(msg);

		if (nMsgCode && !LogQueue.IsEmpty())
		{
			if (nMsgCode == _wtoi(LogQueue.GetHead()))
			{
				continue;
			}
		}
		LogQueueAccess.Unlock();

		// The first 6 positions identify the message
		// since I already took it, I'll get the rest.
		msg = msg.Mid(6);

		int nFrom, nLen = LogWindow.GetWindowTextLength();

		// Cutout the top lines when reaching 90% of
		// the log window capacity
		XXX("In-8");
	
		if ((UINT)nLen > (LogWindow.GetLimitText() * 9)/10)
		{
			// Removes the first 10% lines
			int nNewFirstLine = LogWindow.GetLineCount() / 10;
			LogWindow.SetSel(0, LogWindow.LineIndex(nNewFirstLine) - 1);
			LogWindow.ReplaceSel(_T(""));

			nLen -= nNewFirstLine;
			nLastPosition -= nNewFirstLine;
		}

		XXX("In-9");
	
		if (nMsgCode && nMsgCode == nLastMessage)
		{
			nFrom = nLastPosition;
		}
		else
		{
			LogWindow.SetSel(nLen, nLen);
			LogWindow.ReplaceSel(_T("\r\n"));
			nLen = LogWindow.GetWindowTextLength();

			nLastPosition = nFrom = nLen;
			nLastMessage = nMsgCode;
		}

		XXX("In-10");
	
		LogWindow.SetSel(nFrom, nLen);
		LogWindow.ReplaceSel(msg);

		XXX("In-11");
	
		LogQueueAccess.Lock();
		//LogQueueGateKeeper.Lock();
	}
	LogQueueAccess.Unlock();
}
