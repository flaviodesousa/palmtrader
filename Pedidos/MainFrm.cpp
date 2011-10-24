// MainFrm.cpp : implementation of the CMainFrame class
//
// $Archive: /PalmTrader 1/Pedidos/MainFrm.cpp $
// $Author: Flávio $
// $Date: 27/10/98 10:07 $
/* $History: MainFrm.cpp $
 * 
 * *****************  Version 5  *****************
 * User: Flávio       Date: 27/10/98   Time: 10:07
 * Updated in $/PalmTrader 1/Pedidos
 * Alterado mecanismo de exibição de lista de produtos (total/somente
 * pedido)
 * 
 * *****************  Version 4  *****************
 * User: Flávio       Date: 1/10/98    Time: 16:36
 * Updated in $/PalmTrader 1/Pedidos
 * Incluídas provisões para manter pressionado o botão de modo de exibição
 * (todos produtos ou apenas os pedidos)
 * 
 * *****************  Version 3  *****************
 * User: Flávio       Date: 23/09/98   Time: 16:56
 * Updated in $/PalmTrader 1/Pedidos
 * Implementada classe basica para suporte a bases de dados do Windows CE.
 * Movidas as bases de dados de pedidos e de itens para a nova classe.
 * Controle de blocos removido do registry para as novas classes
 * Incluído ícone para futuro suporte a eliminação de produtos
 * 
 * *****************  Version 2  *****************
 * User: Flávio       Date: 4/03/98    Time: 3:02a
 * Updated in $/QuickSell/Pedidos
 * CommandBar reorganizada. Corrigido o bug na apresentação dos botões
 * (inclusive o de fechar a aplicação)
 */

#include "stdafx.h"
#include "Pedidos.h"
#include "PedidosView.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
// Array tbSTDButton contains relevant buttons of bitmap IDB_STD_SMALL_COLOR

static TBBUTTON g_tbSTDButton[] = {
	{0, 0,				    TBSTATE_ENABLED, TBSTYLE_SEP,    0, 0, 0,  0},  
	{0,	ID_NOVO_PEDIDO,		TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, -1},
	{1, ID_ABRIR_PEDIDO,	TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, -1},
	{2, ID_GRAVAR_PEDIDO,	TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, -1},
	{3, ID_ELIMINAR_PEDIDO, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, -1},
	{0, 0,				    TBSTATE_ENABLED, TBSTYLE_SEP,    0, 0, 0, -1},
	{7, ID_CB_EXIBIR_TODOS_PRODUTOS,	TBSTATE_ENABLED|TBSTATE_CHECKED, TBSTYLE_CHECK|TBSTYLE_GROUP, 0, 0, 0, -1},
	{8, ID_CB_EXIBIR_SOMENTE_PEDIDO,	TBSTATE_ENABLED,                 TBSTYLE_CHECK|TBSTYLE_GROUP, 0, 0, 0, -1},
	{0, 0,				    TBSTATE_ENABLED, TBSTYLE_SEP,    0, 0, 0, -1},
	{9, ID_APP_ABOUT,	    TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, -1},
	{0, 0,				    TBSTATE_ENABLED, TBSTYLE_SEP,    0, 0, 0,  0}
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_CB_EXIBIR_SOMENTE_PEDIDO, OnCbExibirSomentePedido)
	ON_COMMAND(ID_CB_EXIBIR_TODOS_PRODUTOS, OnCbExibirTodosProdutos)
	ON_UPDATE_COMMAND_UI(ID_CB_EXIBIR_SOMENTE_PEDIDO, OnUpdateCbExibirSomentePedido)
	ON_UPDATE_COMMAND_UI(ID_CB_EXIBIR_TODOS_PRODUTOS, OnUpdateCbExibirTodosProdutos)
	ON_COMMAND(ID_EXIBIR_SOMENTE_PEDIDO, OnExibirSomentePedido)
	ON_COMMAND(ID_EXIBIR_TODOS_PRODUTOS, OnExibirTodosProdutos)
	ON_UPDATE_COMMAND_UI(ID_EXIBIR_SOMENTE_PEDIDO, OnUpdateExibirSomentePedido)
	ON_UPDATE_COMMAND_UI(ID_EXIBIR_TODOS_PRODUTOS, OnUpdateExibirTodosProdutos)
	//}}AFX_MSG_MAP
	// Global help commands
	ON_COMMAND(ID_HELP, CFrameWnd::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// Add the buttons to the CommandBar.
	// NOTE: In order for AddAdornments() to work properly, NImages must be
	//       the true number of button images in the bitmap file (even if not
	//       all of them are used).
	if (!InsertButtons( g_tbSTDButton,
		sizeof(g_tbSTDButton)/sizeof(TBBUTTON),		// NButtons
		IDR_MAINFRAME,					// toolbar bitmap
		10 ))						// NImages
	{
		TRACE0("Failed to add command bar buttons\n");
		return -1;
	}

	// Add Exit and Help buttons
	if (!AddAdornments( 0 )) // Only Exit button
	{
		TRACE0("Failed to add exit and help buttons\n");
		return -1; 
	}


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnCbExibirSomentePedido() 
{
	(((CPedidosView *)GetActiveView()))->ExibirSomentePedido();
}



void CMainFrame::OnCbExibirTodosProdutos() 
{
	((CPedidosView *)GetActiveView())->ExibirTodosProdutos();
}



void CMainFrame::OnUpdateCbExibirSomentePedido(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(((CPedidosView *)GetActiveView())->GetTipoDeLista() == CPedidosView::en_ItensPedidos);
}



void CMainFrame::OnUpdateCbExibirTodosProdutos(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(((CPedidosView *)GetActiveView())->GetTipoDeLista() == CPedidosView::en_ListaDePrecos);
}



void CMainFrame::OnExibirSomentePedido() 
{
	((CPedidosView *)GetActiveView())->ExibirSomentePedido();
	//::PostMessage(NULL, TB_PRESSBUTTON, ID_CB_EXIBIR_TODOS_PRODUTOS, MAKELONG(FALSE, 0));
	::PostMessage(NULL, TB_PRESSBUTTON, ID_CB_EXIBIR_SOMENTE_PEDIDO, MAKELONG(TRUE, 0));
}



void CMainFrame::OnExibirTodosProdutos() 
{
	((CPedidosView *)GetActiveView())->ExibirTodosProdutos();
	::PostMessage(NULL, TB_PRESSBUTTON, ID_CB_EXIBIR_TODOS_PRODUTOS, MAKELONG(TRUE, 0));
	::PostMessage(NULL, TB_PRESSBUTTON, ID_CB_EXIBIR_SOMENTE_PEDIDO, MAKELONG(FALSE, 0));
}



void CMainFrame::OnUpdateExibirSomentePedido(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(((CPedidosView *)GetActiveView())->GetTipoDeLista() == CPedidosView::en_ItensPedidos);
}



void CMainFrame::OnUpdateExibirTodosProdutos(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(((CPedidosView *)GetActiveView())->GetTipoDeLista() == CPedidosView::en_ListaDePrecos);
}
