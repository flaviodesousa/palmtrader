// DialogQuantidade.cpp : implementation file
//
// $Archive: /PalmTrader 1/Pedidos/DialogQuantidade.cpp $
// $Author: Fl�vio $
// $Date: 25/05/99 15:39 $
/* $History: DialogQuantidade.cpp $
 * 
 * *****************  Version 6  *****************
 * User: Fl�vio       Date: 25/05/99   Time: 15:39
 * Updated in $/PalmTrader 1/Pedidos
 * Altera��es feitas para o release 1.30
 * Generalizada rotina para convers�o de n�meros em strings
 * Permitida a altera��o individual de pre�os no pedido
 * Acelerada rotina de localiza��o de produto
 * Inclu�da rotina gen�rica para convers�o de n�meros em strings
 * Corrigido bug na defini��o do tamanho do buffer de envio de pacotes TCP
 * nos m�dulos de sincroniza��o
 * Separada a porta TCP de conex�o com os clientes e servidores
 * Inclu�do m�todo em CPedido para retornar a data do pedido como DWORD,
 * que � usada no m�dulo de sincroniza��o de pedidos
 * Implementados novos atributos em pre�os
 * Inclu�do o script de cria��o da base SQL
 * 
 * *****************  Version 5  *****************
 * User: Fl�vio       Date: 30/09/98   Time: 15:41
 * Updated in $/PalmTrader 1/Pedidos
 * Inclu�dos coment�rios de controle de vers�o
 */

#include "stdafx.h"
#include "Pedidos.h"
#include "DialogQuantidade.h"
#include "Formatter.h"
#include "QSTools.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
//#define X {CString s;s.Format(_T("%d"), __LINE__);AfxMessageBox(s);}

/////////////////////////////////////////////////////////////////////////////
// CDialogQuantidade dialog


CDialogQuantidade::CDialogQuantidade(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogQuantidade::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogQuantidade)
	m_cod_item = _T("");
	m_descricao = _T("");
	m_quantidade = _T("");
	m_total = _T("");
	m_embalagem = _T("");
	m_unitario = _T("");
	m_preco = _T("");
	m_master = 0;
	m_desconto = 0.0;
	//}}AFX_DATA_INIT
}


void CDialogQuantidade::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogQuantidade)
	DDX_Text(pDX, IDC_EDIT_COD_ITEM, m_cod_item);
	DDX_Text(pDX, IDC_EDIT_DESCRICAO, m_descricao);
	DDX_Text(pDX, IDC_EDIT_QUANTIDADE, m_quantidade);
	DDX_Text(pDX, IDC_EDIT_TOTAL, m_total);
	DDX_Text(pDX, IDC_EDIT_EMBALAGEM, m_embalagem);
	DDX_Text(pDX, IDC_EDIT_UNITARIO, m_unitario);
	DDX_Text(pDX, IDC_EDIT_PRECO, m_preco);
	DDX_Text(pDX, IDC_EDIT_MASTER, m_master);
	DDX_Text(pDX, IDC_EDIT_DESCONTO, m_desconto);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogQuantidade, CDialog)
	//{{AFX_MSG_MAP(CDialogQuantidade)
	ON_BN_CLICKED(IDC_BUTTON_CANCELA_ITEM, OnButtonCancelaItem)
	ON_EN_CHANGE(IDC_EDIT_QUANTIDADE, OnChangeEditQuantidade)
	ON_BN_CLICKED(IDC_BUTTON_QUICKOK, OnButtonQuickOK)
	ON_EN_CHANGE(IDC_EDIT_DESCONTO, OnChangeEditDesconto)
	ON_EN_CHANGE(IDC_EDIT_PRECO, OnChangeEditPreco)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogQuantidade message handlers

BOOL CDialogQuantidade::OnInitDialog() 
{
    CDialog::OnInitDialog();

	UpdateTotal();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CDialogQuantidade::OnButtonCancelaItem() 
{
	m_quantidade.Empty();

	EndDialog(IDOK);
}



void CDialogQuantidade::OnChangeEditQuantidade() 
{
    if (IsWindowVisible())
    {
	    UpdateTotal();
    }
}



void CDialogQuantidade::OnChangeEditDesconto() 
{
    if (IsWindowVisible())
    {
        UpdateData(TRUE);
        m_dwPrecoAtual = (DWORD)(m_dwPreco * (100.0 - m_desconto)) / 100UL;
        m_preco = CFormatter::DWordAsMoney(m_dwPrecoAtual);
        UpdateData(FALSE);
	    UpdateTotal();
    }
}



void CDialogQuantidade::OnChangeEditPreco() 
{
    if (IsWindowVisible())
    {
        UpdateData(TRUE);
        m_dwPrecoAtual = (DWORD)(CStringToDouble(m_preco) * 100);
        m_desconto = (double)((m_dwPreco - m_dwPrecoAtual) * 100UL) / m_dwPreco;
        UpdateData(FALSE);
        UpdateTotal();
    }
}



void CDialogQuantidade::OnButtonQuickOK() 
{
	EndDialog(IDOK);
}



void CDialogQuantidade::UpdateTotal()
{
	UpdateData(TRUE);
	m_total = CFormatter::DWordAsMoney((DWORD)_wtol(m_quantidade) * m_dwPrecoAtual);
	UpdateData(FALSE);
}
