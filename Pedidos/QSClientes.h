// QSClientes.h: interface for the CQSClientes class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QSCLIENTES_H__3D121DD6_6FEA_11D1_9F8C_204C4F4F5020__INCLUDED_)
#define AFX_QSCLIENTES_H__3D121DD6_6FEA_11D1_9F8C_204C4F4F5020__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "QSFlatDatabase.h"

class CQSClientes : public CQSFlatDatabase  
{
public:
	struct
	{
		    unsigned long	codigo;
		    unsigned short	digito;
		    char			cgc[19];
		    char			razao_social[61];
		    char			fantasia[61];
		    char			contato[41];
		    char			telefone[14];
		    char			fax[14];
		    unsigned short	ramo_atividade;
		    char			cod_cobranca[11];
		    unsigned short	emitir_duplicata;
		    unsigned short	cod_vendedor;
		    unsigned short	cod_praca;
		    unsigned long	limite;
		    unsigned long	valor_disponivel;
		    unsigned short	bloqueado;
            unsigned short  tabela;
		    char			motivo_bloqueio[65];
		    struct
		    {
			    char		endereco[61];
			    char		bairro[41];
			    char		cidade[31];
			    char		estado[3];
			    char		cep[10];
		    } endereco_comercial, endereco_cobranca;
	} m_record;

public:
	BOOL FindByCodigo(DWORD dwCodigo);
	static void Remove(void);
	BOOL GetRecord(WORD lRecNo);
	BOOL GetRecord(void);
	void ReadRecord(void);
	void WriteRecord(void);
	void AddRecord(void);
	void ClearBuffer(void);
	CQSClientes();
	virtual ~CQSClientes();
};

#endif // !defined(AFX_QSCLIENTES_H__3D121DD6_6FEA_11D1_9F8C_204C4F4F5020__INCLUDED_)
