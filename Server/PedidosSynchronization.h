// PedidosSynchronization.h: interface for the CPedidosSynchronization class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PEDIDOSSYNCHRONIZATION_H__2ED27031_A6D6_11D1_A012_00004403E294__INCLUDED_)
#define AFX_PEDIDOSSYNCHRONIZATION_H__2ED27031_A6D6_11D1_A012_00004403E294__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "UserAppSynchronization.h"
#include "Pedido.h"

class CPedidosSynchronization : public CUserAppSynchronization  
{
public:
	DWORD GetNovoSaldoCliente(void);
	CString DiagnosticString(void);
	BOOL ReSend(void);
	CPedidosSynchronization(CPedido *Pedido);
	virtual ~CPedidosSynchronization();

protected:
	long m_SaldoCliente;
	CPedido *m_Pedido;
	void SendRequest(void);
	BOOL Process(CString& strRow);
	int nTipoRegistro;
	int nRowCount;
	CString strRows[3];
};

#endif // !defined(AFX_PEDIDOSSYNCHRONIZATION_H__2ED27031_A6D6_11D1_A012_00004403E294__INCLUDED_)
