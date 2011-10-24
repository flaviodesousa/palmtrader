// RSProdutos.h : header file
//
// $Archive: /QuickSell/Server/RSProdutos.h $
// $Author: Flávio $
// $Date: 7/04/98 6:07p $
/* $History: RSProdutos.h $
 * 
 * *****************  Version 2  *****************
 * User: Flávio       Date: 7/04/98    Time: 6:07p
 * Updated in $/QuickSell/Server
 * Colocado em source control
 * Acrescentados campos descritivos do produto
 */

#if !defined(AFX_RSPRODUTOS_H__7F6A9011_F292_11D0_A107_00004403E294__INCLUDED_)
#define AFX_RSPRODUTOS_H__7F6A9011_F292_11D0_A107_00004403E294__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
/////////////////////////////////////////////////////////////////////////////
// CRSProdutos recordset

class CRSProdutos : public CRecordset
{
public:
	void EnableParameterization(void);
	CRSProdutos(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRSProdutos)

// Field/Param Data
	//{{AFX_FIELD(CRSProdutos, CRecordset)
	long	m_pd_Codigo;
	BYTE	m_pd_Digito;
	CString	m_pd_Descricao;
	CString	m_pd_Embalagem;
	CString	m_pd_Unidade;
	long	m_pd_Unidades;
	long	m_pd_EmbalagemMaster;
	CString	m_pd_PesoBruto;
	BOOL	m_pd_Disponivel;
	CTime	m_pd_TimeStamp;
	CTime	m_pd_DisponibilidadeTimeStamp;
	//}}AFX_FIELD
    long    m_parm_Codigo;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSProdutos)
	public:
	virtual CString GetDefaultConnect();    // Default connection string
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RSPRODUTOS_H__7F6A9011_F292_11D0_A107_00004403E294__INCLUDED_)
