// Server.h : main header file for the SERVER application
//
// $Archive: /QuickSell/Server/Server.h $
// $Author: Flávio $
// $Date: 9/07/98 21:35 $
/* $History: Server.h $
 * 
 * *****************  Version 4  *****************
 * User: Flávio       Date: 9/07/98    Time: 21:35
 * Updated in $/QuickSell/Server
 * Incluído tratamento para atualização automática parcial de produtos,
 * preços e clientes.
 * 
 * *****************  Version 3  *****************
 * User: Flávio       Date: 7/04/98    Time: 6:10p
 * Updated in $/QuickSell/Server
 * Acrescentado suporte a atualização de títulos
 */

#if !defined(AFX_SERVER_H__26EA96F7_68B9_11D1_9F77_204C4F4F5020__INCLUDED_)
#define AFX_SERVER_H__26EA96F7_68B9_11D1_9F77_204C4F4F5020__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CServerApp:
// See Server.cpp for the implementation of this class
//

class CServerApp : public CWinApp
{
public:
	static UINT threadAtualizarPrecosPartial(LPVOID p);
	static UINT threadAtualizarProdutosPartial(LPVOID p);
	static UINT threadAtualizarClientesPartial(LPVOID p);
	static UINT threadAtualizarTitulos(LPVOID p);
	static UINT threadAtualizarVendedores(LPVOID p);
	static UINT threadAtualizarTabelas(LPVOID p);
	static UINT threadAtualizarCodigosDeCobranca(LPVOID p);
	static UINT threadAtualizarPlanos(LPVOID p);
	static UINT threadAtualizarClientes(LPVOID p);
	static UINT threadAtualizarEstoque(LPVOID p);
	static UINT threadAtualizarPrecos(LPVOID p);
	static UINT threadAtualizarProdutos(LPVOID p);
	CServerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CServerApp)
	afx_msg void OnAppAbout();
	afx_msg void OnAtualizarBase();
	afx_msg void OnOpcoes();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVER_H__26EA96F7_68B9_11D1_9F77_204C4F4F5020__INCLUDED_)
