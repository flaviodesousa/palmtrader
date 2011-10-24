// QSPedidos.h: interface for the CQSPedidos class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QSPEDIDOS_H__7351B5F3_734D_11D1_9F94_204C4F4F5020__INCLUDED_)
#define AFX_QSPEDIDOS_H__7351B5F3_734D_11D1_9F94_204C4F4F5020__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "QSFlatDatabase.h"

class CQSPedidos : public CQSFlatDatabase  
{
public:
	struct
	{
		DWORD	pedido_numero;
		DWORD	cliente_codigo;
		BYTE	condicao_venda;
		BYTE	plano;
        BYTE    desconto;
        BOOL    reter_pedido;
        BOOL    apagado;
		char	cobranca[11];
		char	diagnostico[41];
		BOOL	pedido_enviado;
		DWORD	data_entrada;
		WORD	ptr_primeiro_item;
	} m_record;
protected:
	static TCHAR *m_filename;
	DWORD m_bloco;

public:
	BOOL FindByNumero(DWORD lPedido);
	static void Remove(DWORD dwBloco);
	BOOL GetRecord(WORD lRecNo);
	BOOL GetRecord(void);
	void ReadRecord(void);
	void WriteRecord(void);
	void AddRecord(void);
	void ClearBuffer(void);
	CQSPedidos(DWORD bloco);
	virtual ~CQSPedidos();
	friend TCHAR *MakeName(DWORD dwBloco);

};

#endif // !defined(AFX_QSPEDIDOS_H__7351B5F3_734D_11D1_9F94_204C4F4F5020__INCLUDED_)
