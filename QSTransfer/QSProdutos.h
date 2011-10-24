// QSProdutos.h: interface for the CQSProdutos class.
//
//////////////////////////////////////////////////////////////////////
// $Archive: /PalmTrader 1/QSTransfer/QSProdutos.h $
// $Author: Fl�vio $
// $Date: 13/05/99 22:21 $
/* $History: QSProdutos.h $
 * 
 * *****************  Version 3  *****************
 * User: Fl�vio       Date: 13/05/99   Time: 22:21
 * Updated in $/PalmTrader 1/QSTransfer
 * Inclu�dos atributos adicionais
 * 
 * *****************  Version 2  *****************
 * User: Fl�vio       Date: 7/06/98    Time: 11:51a
 * Updated in $/QuickSell/QSTransfer
 * Aumentada a precis�o do campo peso_bruto
 */

#if !defined(AFX_QSPRODUTOS_H__3D121DD5_6FEA_11D1_9F8C_204C4F4F5020__INCLUDED_)
#define AFX_QSPRODUTOS_H__3D121DD5_6FEA_11D1_9F8C_204C4F4F5020__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "QSFlatDatabase.h"

class CQSProdutos : public CQSFlatDatabase  
{
private:
	static int _Compare(const void *first, const void *second);
    CFile *m_keyfile;
    WORD *m_index;
    DWORD *m_codigos; // tabela tempor�ria para indexa��o
    WORD m_nKeysInIndex;

public:
	struct
	{
		DWORD	codigo;
		WORD	digito;
		char	descricao[81];
		char	complemento[33];
        char    embalagem[17];
        char    unidade[17];
        WORD    unidades;
        WORD    embalagem_master;
        DWORD   peso_bruto;
		DWORD	preco[8];
		DWORD	desconto_maximo;
		WORD	brinde;
		WORD	disponivel;
	} m_record;

public:
	BOOL FindByCodigo(DWORD dwCodigo);
	void Reindex(void);
	static void Remove(void);
	BOOL GetRecord(WORD lRecNo);
	BOOL GetRecord(void);
	void ReadRecord(void);
	void WriteRecord(void);
	void AddRecord(void);
	void ClearBuffer(void);
	CQSProdutos();
	virtual ~CQSProdutos();
};

#endif // !defined(AFX_QSPRODUTOS_H__3D121DD5_6FEA_11D1_9F8C_204C4F4F5020__INCLUDED_)
