// Protocolo Palmtop <-> Server
// $Archive: /PalmTrader 1/Server/Protocol.h $
// $Author: Flávio $
// $Date: 13/05/99 21:24 $
/* $History: Protocol.h $
 * 
 * *****************  Version 9  *****************
 * User: Flávio       Date: 13/05/99   Time: 21:24
 * Updated in $/PalmTrader 1/Server
 * Protocolo versão 1.20
 * Incluídos atributos adicionais aos produtos
 * 
 * *****************  Version 8  *****************
 * User: Flávio       Date: 13/05/99   Time: 17:36
 * Updated in $/PalmTrader 1/Server
 * 
 * *****************  Version 7  *****************
 * User: Flávio       Date: 25/04/99   Time: 22:08
 * Updated in $/PalmTrader 1/QSTransfer
 * Incluído indicador de versão do protocolo
 * Incluída estrutura para sincronização de data e hora
 * 
 * *****************  Version 6  *****************
 * User: Flávio       Date: 14/07/98   Time: 18:06
 * Updated in $/PalmTrader 1/QSTransfer
 * Incluídos códigos das solicitações parciais
 * 
 * *****************  Version 5  *****************
 * User: Flávio       Date: 11/07/98   Time: 19:53
 * Updated in $/QuickSell/Server
 * Incluído saldo atualizado do cliente no fechamento do pedido
 * 
 * *****************  Version 4  *****************
 * User: Flávio       Date: 10/07/98   Time: 21:48
 * Updated in $/QuickSell/Server
 * Implementado suporte para reenvio de pedidos;
 * Alterações na estrutura de transmissão de títulos
 * 
 * *****************  Version 3  *****************
 * User: Flávio       Date: 7/04/98    Time: 2:14p
 * Updated in $/QuickSell/Server
 * Data corrigida
 * 
 * *****************  Version 2  *****************
 * User: Flávio       Date: 7/04/97    Time: 2:03p
 * Updated in $/QuickSell/Server
 * Suporte a transmissão de títulos (Contas a Receber)
 */

#define PROTOCOL_VERSION 0x120
#define DEFAULT_PORT 47375U

struct packet_s
{
	struct
	{
		unsigned long magic;
		unsigned short size;
		unsigned short type;
		unsigned long sequence; // Is it necessary?
	} header;
	union
	{
		// PKT_SND_VERSION - Versao do Transfer
		struct // version
		{
			unsigned short number;
		} version;
		
		// PKT_SND_LOGON - Logon do usuario
		struct // logon
		{
			unsigned short codigo_vendedor;
			char senha[17];
		} logon;
		
		// PKT_SND_PEDIDO - Header de pedido
		struct // pedido
		{
			unsigned long	numero;
			unsigned long	cliente_codigo;
			unsigned short	condicao_venda;
			unsigned short	plano;
			unsigned long	data_entrada;
			char            cobranca[11];
		} pedido;
		
		// PKT_SND_PEDIDO_ITEM - Item de pedido
		struct // pedido_item
		{
			unsigned long	pedido;
			unsigned long	produto;
			unsigned long	quantidade;
			unsigned long	preco;
		} pedido_item;
		
		// PKT_SND_PEDIDO_FIM - Indica fim do pedido
		struct
		{
			unsigned long	pedido;
		} pedido_fim;

		// PKT_SND_PEDIDO_STATUS - Indica situação do pedido
		struct
		{
			unsigned long	pedido;
			unsigned short	reenviar;
			unsigned long	novo_saldo_cliente;
            char            diagnostico[41];
		} pedido_status;
		
		// PKT_SND_NOVO_CLIENTE - Novo cliente
		struct // novo_cliente
		{
		} novo_cliente;
		
		// PKT_SND_ATUALIZA_CLIENTE - Atualiza cliente
		struct // atualiza_cliente
		{
		} atualiza_cliente;
		
		// PKT_SND_PEDIDO_ITEM_CONF - Confirmação de item pedido
		struct // pedido_item_conf
		{
			unsigned long pedido;
			unsigned long produto;
			unsigned long quantidade;
		} pedido_item_conf;
		
		// PKT_SND_PRODUTO - Atualização/Inclusão de produto
		struct // produto
		{
			unsigned long	codigo;
			unsigned short	digito;
			unsigned short	disponivel;
            unsigned short  unidades;
            unsigned short  embalagem_master;
            unsigned short  peso_bruto;
			unsigned long	preco[8];
			char			descricao[41];
            char			embalagem[17];
            char			unidade[17];
			unsigned short	brinde;
			unsigned long	desconto_maximo;
			char			complemento[33];
        } produto;

		// PKT_SND_CLIENTE - Atualização/inclusão de cliente
		struct // cliente
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
				char		endereco[41];
				char		bairro[21];
				char		cidade[21];
				char		estado[3];
				char		cep[10];
			} endereco_comercial, endereco_cobranca;
		} cliente;

		// PKT_SND_PRODUTO_PRECO - Atualização de preço de produto
		struct // produto_preco
		{
			unsigned long codigo;
			unsigned long preco[8];
		} produto_preco;

		// PKT_SND_PRODUTO_FALTA - Atualização no status de disponibilidade
		struct // produto_falta
		{
			unsigned long codigo;
			unsigned short disponivel;
		} produto_falta;

		// PKT_SND_COBRANCA - Códigos de cobrança
		struct // cobranca
		{
			char codigo[11];
			char descricao[61];
		} cobranca;

		// PKT_SND_PLANO - Planos de pagamento
		struct // plano
		{
			unsigned short codigo;
			char descricao[61];
			unsigned short coluna;
		} plano;

		// PKT_SND_COND_VENDA
		struct // cond_venda
		{
			unsigned short codigo;
			unsigned short pede_percentual;
		} cond_venda;

		// PKT_SND_BLOCO - Bloco de pedidos em branco
		struct // bloco
		{
			DWORD inicial;
			DWORD final;
		} bloco;

		// PKT_SND_MENSAGEM - Mensagem exibina na janela de log
		struct // mensagem
		{
			char texto[81];
		} mensagem;

        // PKT_SND_TITULO
        struct
        {
            unsigned long cliente;
            unsigned long valor;
            char emissao[16];
            char vencimento[16];
            char numero[41];
        } titulo;

		// PKT_SND_DATE_TIME
		struct
		{
			unsigned long date; // YYYYMMDD
			unsigned long time; // Seconds in day
		} date_time;
	};
};

#define PKT_MAGIC_NUMBER			0x46645371UL

#define PKT_ACK						0x001
#define PKT_NAK						0x002

// Solicitações HPC->Host

#define	PKT_ASK_REFILL_PRODUTOS		0x1010	//Reenvia toda a relação de produtos
#define	PKT_ASK_REFILL_CLIENTES		0x1020	//Reenvia toda a relação de clientes
											//do vendedor.
#define	PKT_ASK_REFILL_COND_VENDA	0x1030	//Reenvia tabela de condições de venda
#define	PKT_ASK_REFILL_PLANOS		0x1040	//Reenvia tabela de planos de pagamento
#define	PKT_ASK_REFILL_COBRANCA		0x1050	//Reenvia tabela de cobrança
#define PKT_ASK_BLOCO				0x1060	//Solicita bloco de pedidos
#define PKT_ASK_REFILL_TITULOS      0x1070  //Solicita títulos
#define PKT_ASK_NOVOS_PRODUTOS		0x1080	//Solicita novos produtos
#define PKT_ASK_NOVOS_PRECOS		0x1090	//Solicita novos preços
#define PKT_ASK_NOVOS_SALDOS		0x10a0	//Solicita novos saldos de estoque
#define PKT_ASK_NOVOS_CLIENTES		0x10b0	//Solicita novos clientes
#define PKT_ASK_NOVOS_TITULOS		0x10c0	//Solicita novos titulos

// Solicitações Host->HPC

#define	PKT_ASK_VERSION				0x2010	//Solicita versão do Transfer do HPC
#define PKT_ASK_LOGON				0x2020	//Solicita logon
#define	PKT_ASK_CLEAR_COND_VENDA	0x2030	//Limpar tabela de condições de venda
#define	PKT_ASK_CLEAR_PLANOS		0x2040	//Limpar tabela de planos de pagamento
#define	PKT_ASK_CLEAR_COBRANCA		0x2050	//Limpar tabela de tipos de cobrança
#define PKT_ASK_CLEAR_CLIENTES		0x2060	//Apagar todos clientes
#define PKT_ASK_CLEAR_PRODUTOS		0x2070	//Apagar todos produtos
#define	PKT_ASK_REINDEX_CLIENTES	0x2080	//Reindexar o arquivo de clientes
#define	PKT_ASK_REINDEX_PRODUTOS	0x2090	//Reindexar o arquivo de produtos
#define PKT_ASK_CLEAR_TITULOS		0x20A0	//Limpar tabela de títulos

// Transferência HPC->Host

#define	PKT_SND_VERSION				0x3010	//Envia a versão do Transfer
#define PKT_SND_LOGON				0x3020	//Envia dados de logon
#define	PKT_SND_PEDIDO				0x3030	//Envia o cabeçalho de um pedido
#define	PKT_SND_PEDIDO_ITEM			0x3040	//Envia um item do pedido
#define	PKT_SND_PEDIDO_FIM			0x3050	//Envia um item do pedido
#define	PKT_SND_NOVO_CLIENTE		0x3050	//Envia dados de novo cliente
#define	PKT_SND_ATUALIZA_CLIENTE	0x3060	//Envia dados atualizados de um cliente

// Transferência Host->HPC

#define	PKT_SND_PEDIDO_STATUS		0x4010	//Envia confirmação de pedido
#define	PKT_SND_PEDIDO_ITEM_CONF	0x4020	//Envia confirmação de item pedido
#define	PKT_SND_PRODUTO				0x4030	//Envia atualização/inclusão de produto
#define	PKT_SND_CLIENTE				0x4040	//Envia atualização/inclusão de cliente
#define	PKT_SND_PRODUTO_PRECO		0x4050	//Envia atualização de preço de produto
#define	PKT_SND_PRODUTO_FALTA		0x4060	//Envia atualização no status de disponibilidade
#define PKT_SND_BLOCO				0x4070	//Envia bloco de pedidos em branco
#define PKT_SND_PLANO				0x4080	//Envia codigo de plano de pagamento
#define PKT_SND_COBRANCA			0x4090	//Envia codigo de cobrança
#define PKT_SND_COND_VENDA			0x40A0	//Envia codigo de condição de venda
#define PKT_SND_MENSAGEM			0x40B0	//Envia mensagem a ser exibida no log de acesso
#define PKT_SND_TITULO              0x40C0  //Envia titulo em aberto de cliente

// Reconhecimentos de recepção Host->HPC

#define	PKT_ACK_VERSION				(PKT_ACK|PKT_SND_VERSION			)	
#define PKT_ACK_LOGON				(PKT_ACK|PKT_SND_LOGON				)
#define	PKT_ACK_PEDIDO				(PKT_ACK|PKT_SND_PEDIDO				)
#define	PKT_ACK_PEDIDO_ITEM			(PKT_ACK|PKT_SND_PEDIDO_ITEM		)	
#define	PKT_ACK_NOVO_CLIENTE		(PKT_ACK|PKT_SND_NOVO_CLIENTE		)
#define	PKT_ACK_ATUALIZA_CLIENTE	(PKT_ACK|PKT_SND_ATUALIZA_CLIENTE	)

// Reconhecimentos de recepção HPC->Host

#define	PKT_ACK_PEDIDO_ITEM_CONF	(PKT_ACK|PKT_SND_PEDIDO_ITEM_CONF	)
#define	PKT_ACK_PRODUTO				(PKT_ACK|PKT_SND_PRODUTO			)	
#define	PKT_ACK_CLIENTE				(PKT_ACK|PKT_SND_CLIENTE			)	
#define	PKT_ACK_PRODUTO_PRECO		(PKT_ACK|PKT_SND_PRODUTO_PRECO		)
#define	PKT_ACK_PRODUTO_FALTA		(PKT_ACK|PKT_SND_PRODUTO_FALTA		)
#define	PKT_ACK_BLOCO				(PKT_ACK|PKT_SND_BLOCO				)

// Negação de recepção Host->HPC

#define	PKT_NAK_VERSION				(PKT_NAK|PKT_SND_VERSION			)	
#define PKT_NAK_LOGON				(PKT_NAK|PKT_SND_LOGON				)
#define	PKT_NAK_PEDIDO				(PKT_NAK|PKT_SND_PEDIDO				)
#define	PKT_NAK_PEDIDO_ITEM			(PKT_NAK|PKT_SND_PEDIDO_ITEM		)	
#define	PKT_NAK_NOVO_CLIENTE		(PKT_NAK|PKT_SND_NOVO_CLIENTE		)
#define	PKT_NAK_ATUALIZA_CLIENTE	(PKT_NAK|PKT_SND_ATUALIZA_CLIENTE	)

// Negação de recepção HPC->Host

#define	PKT_NAK_PEDIDO_ITEM_CONF	(PKT_NAK|PKT_SND_PEDIDO_ITEM_CONF	)
#define	PKT_NAK_PRODUTO				(PKT_NAK|PKT_SND_PRODUTO			)	
#define	PKT_NAK_CLIENTE				(PKT_NAK|PKT_SND_CLIENTE			)	
#define	PKT_NAK_PRODUTO_PRECO		(PKT_NAK|PKT_SND_PRODUTO_PRECO		)
#define	PKT_NAK_PRODUTO_FALTA		(PKT_NAK|PKT_SND_PRODUTO_FALTA		)
#define	PKT_NAK_BLOCO				(PKT_NAK|PKT_SND_BLOCO				)

// Notificações

#define PKT_EOQ						0xf010	//Sinaliza todas solicitacoes enviadas
#define PKT_EOQ_ACK					(PKT_EOQ|PKT_ACK)
#define PKT_EOJ						0xf020	//Sinaliza todas solicitações atendidas
#define PKT_EOJ_ACK					(PKT_EOJ|PKT_ACK) 
#define PKT_ABORT					0xf0f0	//Cancela comunicação
#define PKT_ABORT_ACK				(PKT_ABORT|PKT_ACK)
