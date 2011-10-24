// AutoSynchronization.cpp: implementation of the CAutoSynchronization class.
//
//////////////////////////////////////////////////////////////////////
// $Archive: /QuickSell/Server/AutoSynchronization.cpp $
// $Author: Flávio $
// $Date: 13/11/98 10:44 $
/* $History: AutoSynchronization.cpp $
 * 
 * *****************  Version 5  *****************
 * User: Flávio       Date: 13/11/98   Time: 10:44
 * Updated in $/QuickSell/Server
 * Corrigido bug que afetava as atualizações automáticas de execução
 * diária única (sem repetição) no segundo dia após a primeira execução.
 * 
 * *****************  Version 4  *****************
 * User: Flávio       Date: 9/07/98    Time: 21:29
 * Updated in $/QuickSell/Server
 * Incluído tratamento para atualização automática parcial de produtos,
 * preços e clientes.
 * 
 * *****************  Version 3  *****************
 * User: Flávio       Date: 7/02/98    Time: 4:25p
 * Updated in $/QuickSell/Server
 * Reduzida a prioridade da thread de atualização automática;
 * Colocada a hora da última atualização no registry;
 * Incluída atualização automática da tabela de títulos.
 * 
 * *****************  Version 2  *****************
 * User: Flávio       Date: 6/26/98    Time: 1:46p
 * Updated in $/QuickSell/Server
 * Incluído suporte a atualização automática da base de dados do server
 */

#include "stdafx.h"
#include "Server.h"
#include "AutoSynchronization.h"
#include "Registry.h"
#include "RSTabelasPrecos.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAutoSynchronization::CAutoSynchronization()
{
}



CAutoSynchronization::~CAutoSynchronization()
{

}



CString CAutoSynchronization::TranslateNumberToTableName(int nTableNumber)
{
    CString strTabela;

    switch(nTableNumber)
    {
    case  0 : strTabela = "Clientes";        break;
    case  1 : strTabela = "Cobranca";        break;
    case  2 : strTabela = "Estoque";         break;
    case  3 : strTabela = "Planos";          break;
    case  4 : strTabela = "Precos";          break;
    case  5 : strTabela = "Produtos";        break;
    case  6 : strTabela = "Tabelas";         break;
    case  7 : strTabela = "Vendedores";      break;
    case  8 : strTabela = "Titulos";         break;
	case  9 : strTabela = "ClientesParcial"; break;
	case 10 : strTabela = "ProdutosParcial"; break;
	case 11 : strTabela = "PrecosParcial";   break;
    }

    return strTabela;
}



void CAutoSynchronization::Start()
{
    AfxBeginThread(AutoSynchronizationThread, this, THREAD_PRIORITY_BELOW_NORMAL);
}



UINT CAutoSynchronization::AutoSynchronizationThread(void * lpParam)
{
    ((CAutoSynchronization *)lpParam)->Run();

    return 0;
}



void CAutoSynchronization::Run()
{
    CTime timeNow;

    for (;;)
    {
        timeNow = CTime::GetCurrentTime();
        short nMinute = timeNow.GetHour() * 60 + timeNow.GetMinute();

        ReReadConfiguration(nMinute);

        for (int i = 0; i < 12; i++)
        {
            if (m_atualizacoes[i].inicio || m_atualizacoes[i].repeticao)
            {
                if (nMinute >= m_atualizacoes[i].inicio)
                {
                    if
						(
							(
							nMinute >= m_atualizacoes[i].ultima + m_atualizacoes[i].repeticao || 
							m_atualizacoes[i].ultima > nMinute
							) 
						&&
							(
							m_atualizacoes[i].repeticao > 0 ||
							m_atualizacoes[i].ultima == -1
							)
						)
                    {
                        switch (i)
                        {
	                    case Tabela_Clientes:
                            CServerApp::threadAtualizarClientes(this);
                            break;
	                    case Tabela_Cobranca:
                            CServerApp::threadAtualizarCodigosDeCobranca(this);
                            break;
	                    case Tabela_Estoque:
                            CServerApp::threadAtualizarEstoque(this);
                            break;
	                    case Tabela_Planos:
                            CServerApp::threadAtualizarPlanos(this);
                            break;
	                    case Tabela_Precos:
                            {
		                        CRSTabelasPrecos tp;
		                        tp.Open();
		                        while (!tp.IsEOF())
		                        {
			                        int *pnTabela = new int;
			                        *pnTabela = tp.m_tp_Codigo;
			                        CServerApp::threadAtualizarPrecos(pnTabela);
			                        tp.MoveNext();
		                        }
                            }
                            break;
	                    case Tabela_Produtos:
                            CServerApp::threadAtualizarProdutos(this); 
                            break;
	                    case Tabela_Tabelas:
                            CServerApp::threadAtualizarTabelas(this);
                            break;
	                    case Tabela_Vendedores:
                            CServerApp::threadAtualizarVendedores(this);
                            break;
                        case Tabela_Titulos:
                            CServerApp::threadAtualizarTitulos(this);
                            break;
						case Partial_Tabela_Clientes:
							CServerApp::threadAtualizarClientesPartial(this);
							break;
						case Partial_Tabela_Produtos:
							CServerApp::threadAtualizarProdutosPartial(this);
							break;
						case Partial_Tabela_Precos:
                            {
		                        CRSTabelasPrecos tp;
		                        tp.Open();
		                        while (!tp.IsEOF())
		                        {
			                        int *pnTabela = new int;
			                        *pnTabela = tp.m_tp_Codigo;
			                        CServerApp::threadAtualizarPrecosPartial(pnTabela);
			                        tp.MoveNext();
		                        }
                            }
							break;
                        }
                        { //------
                            CRegistry reg;
                            m_atualizacoes[i].ultima = nMinute;
                            reg.SetDWord(_T("Ultima") + TranslateNumberToTableName(i), nMinute);
                        }
                    }
                }
            }
        }

        Sleep(30000); // trinta segundos
    }
}



void CAutoSynchronization::ReReadConfiguration(short nMinute)
{
    CRegistry reg;
    CString strTabela;
    
    for (int i = 0; i < 12; i++)
    {
        strTabela = TranslateNumberToTableName(i);

        m_atualizacoes[i].inicio    = (short)reg.GetDWord(_T("Inicio")    + strTabela,  0);
        m_atualizacoes[i].repeticao = (short)reg.GetDWord(_T("Intervalo") + strTabela,  0);
        m_atualizacoes[i].ultima    = (short)reg.GetDWord(_T("Ultima")    + strTabela, -1);

		if (m_atualizacoes[i].repeticao == 0 && m_atualizacoes[i].ultima > nMinute)
		{
			reg.SetDWord(_T("Ultima") + strTabela, m_atualizacoes[i].ultima = -1);
		}
    }
}
