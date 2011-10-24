// AutoSynchronization.h: interface for the CAutoSynchronization class.
//
//////////////////////////////////////////////////////////////////////
// $Archive: /QuickSell/Server/AutoSynchronization.h $
// $Author: Flávio $
// $Date: 13/11/98 10:44 $
/* $History: AutoSynchronization.h $
 * 
 * *****************  Version 5  *****************
 * User: Flávio       Date: 13/11/98   Time: 10:44
 * Updated in $/QuickSell/Server
 * Corrigido bug que afetava as atualizações automáticas de execução
 * diária única (sem repetição) no segundo dia após a primeira execução.
 * 
 * *****************  Version 4  *****************
 * User: Flávio       Date: 9/07/98    Time: 21:32
 * Updated in $/QuickSell/Server
 * Incluído tratamento para atualização automática parcial de produtos,
 * preços e clientes.
 * 
 * *****************  Version 3  *****************
 * User: Flávio       Date: 7/02/98    Time: 4:23p
 * Updated in $/QuickSell/Server
 * Incluída atualização automática da tabela de títulos
 * 
 * *****************  Version 2  *****************
 * User: Flávio       Date: 6/26/98    Time: 1:48p
 * Updated in $/QuickSell/Server
 * Incluído suporte a atualização automática da base de dados do server
 */

#if !defined(AFX_AUTOSYNCHRONIZATION_H__7C1B9A84_ED96_11D0_A0FE_00004403E294__INCLUDED_)
#define AFX_AUTOSYNCHRONIZATION_H__7C1B9A84_ED96_11D0_A0FE_00004403E294__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CAutoSynchronization  
{
public:
	void Start(void);
	CAutoSynchronization();
	virtual ~CAutoSynchronization();

private:
	void ReReadConfiguration(short nMinute);
	void Run(void);
	static UINT AutoSynchronizationThread(LPVOID lpParam);
	CString TranslateNumberToTableName(int nTableNumber);
    enum
    {
	    Tabela_Clientes = 0,
	    Tabela_Cobranca = 1,
	    Tabela_Estoque = 2,
	    Tabela_Planos = 3,
	    Tabela_Precos = 4,
	    Tabela_Produtos = 5,
	    Tabela_Tabelas = 6,
	    Tabela_Vendedores = 7,
        Tabela_Titulos = 8,
		Partial_Tabela_Clientes = 10,
		Partial_Tabela_Produtos = 11,
		Partial_Tabela_Precos = 12
    };
    struct
    {
        short inicio;
        short repeticao;
        short ultima;
    } m_atualizacoes[13];


};

#endif // !defined(AFX_AUTOSYNCHRONIZATION_H__7C1B9A84_ED96_11D0_A0FE_00004403E294__INCLUDED_)
