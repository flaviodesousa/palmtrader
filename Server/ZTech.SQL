-- Script de geração da base de dados SQL do Trader
--
-- $Archive: /PalmTrader 1/Server/ZTech.SQL $
-- $Author: Flávio $
-- $Date: 28/07/99 11:49 $
-- $History: ZTech.SQL $
-- 
-- *****************  Version 5  *****************
-- User: Flávio       Date: 28/07/99   Time: 11:49
-- Updated in $/PalmTrader 1/Server
-- Código reincorporado a $/PalmTrader 1/Server
-- 
-- *****************  Version 2  *****************
-- User: Flávio       Date: 19/07/99   Time: 21:37
-- Updated in $/QuickSell/Server
-- Incluída eliminação da tabela de concorrentes (para recriá-la com novo
-- formato)
-- 
-- *****************  Version 1  *****************
-- User: Flávio       Date: 19/07/99   Time: 21:36
-- Created in $/QuickSell/Server
-- 
-- *****************  Version 4  *****************
-- User: Flávio       Date: 14/06/99   Time: 11:12
-- Updated in $/PalmTrader 1/Server
-- Incluída tabela de concorrentes
-- 
-- *****************  Version 3  *****************
-- User: Flávio       Date: 13/05/99   Time: 17:34
-- Updated in $/PalmTrader 1/Server


/****** Object:  Table dbo.PedidosItens    Script Date: 09/09/98 09:15:14 ******/
if exists (select * from sysobjects where id = object_id('dbo.PedidosItens') and sysstat & 0xf = 3)
	drop table dbo.PedidosItens
GO

/****** Object:  Table dbo.Pedidos    Script Date: 09/09/98 09:15:14 ******/
if exists (select * from sysobjects where id = object_id('dbo.Pedidos') and sysstat & 0xf = 3)
	drop table dbo.Pedidos
GO

/****** Object:  Table dbo.Titulos    Script Date: 09/09/98 09:15:14 ******/
if exists (select * from sysobjects where id = object_id('dbo.Titulos') and sysstat & 0xf = 3)
	drop table dbo.Titulos
GO

/****** Object:  Table dbo.Blocos    Script Date: 09/09/98 09:15:14 ******/
if exists (select * from sysobjects where id = object_id('dbo.Blocos') and sysstat & 0xf = 3)
	drop table dbo.Blocos
GO

/****** Object:  Table dbo.Concorrentes    Script Date: 07/19/99 21:35:34 ******/
if exists (select * from sysobjects where id = object_id('dbo.Concorrentes') and sysstat & 0xf = 3)
	drop table dbo.Concorrentes
GO

/****** Object:  Table dbo.Clientes    Script Date: 09/09/98 09:15:14 ******/
if exists (select * from sysobjects where id = object_id('dbo.Clientes') and sysstat & 0xf = 3)
	drop table dbo.Clientes
GO

/****** Object:  Table dbo.Mensagens    Script Date: 09/09/98 09:15:14 ******/
if exists (select * from sysobjects where id = object_id('dbo.Mensagens') and sysstat & 0xf = 3)
	drop table dbo.Mensagens
GO

/****** Object:  Table dbo.Sessoes    Script Date: 09/09/98 09:15:14 ******/
if exists (select * from sysobjects where id = object_id('dbo.Sessoes') and sysstat & 0xf = 3)
	drop table dbo.Sessoes
GO

/****** Object:  Table dbo.Precos    Script Date: 09/09/98 09:15:14 ******/
if exists (select * from sysobjects where id = object_id('dbo.Precos') and sysstat & 0xf = 3)
	drop table dbo.Precos
GO

/****** Object:  Table dbo.Vendedores    Script Date: 09/09/98 09:15:14 ******/
if exists (select * from sysobjects where id = object_id('dbo.Vendedores') and sysstat & 0xf = 3)
	drop table dbo.Vendedores
GO

/****** Object:  Table dbo.Cobranca    Script Date: 09/09/98 09:15:14 ******/
if exists (select * from sysobjects where id = object_id('dbo.Cobranca') and sysstat & 0xf = 3)
	drop table dbo.Cobranca
GO

/****** Object:  Table dbo.Log    Script Date: 09/09/98 09:15:14 ******/
if exists (select * from sysobjects where id = object_id('dbo.Log') and sysstat & 0xf = 3)
	drop table dbo.Log
GO

/****** Object:  Table dbo.Planos    Script Date: 09/09/98 09:15:14 ******/
if exists (select * from sysobjects where id = object_id('dbo.Planos') and sysstat & 0xf = 3)
	drop table dbo.Planos
GO

/****** Object:  Table dbo.Produtos    Script Date: 09/09/98 09:15:14 ******/
if exists (select * from sysobjects where id = object_id('dbo.Produtos') and sysstat & 0xf = 3)
	drop table dbo.Produtos
GO

/****** Object:  Table dbo.TabelaPrecos    Script Date: 09/09/98 09:15:14 ******/
if exists (select * from sysobjects where id = object_id('dbo.TabelaPrecos') and sysstat & 0xf = 3)
	drop table dbo.TabelaPrecos
GO

/****** Object:  Table dbo.Cobranca    Script Date: 09/09/98 09:15:14 ******/
CREATE TABLE dbo.Cobranca (
	cb_Codigo varchar (10) NOT NULL ,
	cb_Descricao varchar (60) NULL ,
	cb_TimeStamp datetime NOT NULL CONSTRAINT DF_Cobranca_cb_TimeStamp DEFAULT (getdate()),
	CONSTRAINT PK_Cobranca PRIMARY KEY  CLUSTERED 
	(
		cb_Codigo
	) WITH  FILLFACTOR = 90
)
GO

/****** Object:  Table dbo.Log    Script Date: 09/09/98 09:15:15 ******/
CREATE TABLE dbo.Log (
	DataHora datetime NOT NULL ,
	Vendedor smallint NULL ,
	Historico varchar (255) NOT NULL
)
GO

 CREATE CLUSTERED INDEX IX_LogPorDataHora ON dbo.Log(DataHora) WITH  FILLFACTOR = 90
GO

/****** Object:  Table dbo.Planos    Script Date: 09/09/98 09:15:15 ******/
CREATE TABLE dbo.Planos (
	pl_Codigo tinyint NOT NULL ,
	pl_Descricao varchar (60) NULL ,
	pl_ColunaPreco tinyint NOT NULL CONSTRAINT DF_Planos_pl_ColunaPreco DEFAULT (1),
	pl_TimeStamp datetime NOT NULL CONSTRAINT DF_Planos_pl_TimeStamp DEFAULT (getdate()),
	CONSTRAINT PK_Planos PRIMARY KEY  CLUSTERED 
	(
		pl_Codigo
	) WITH  FILLFACTOR = 90
)
GO

/****** Object:  Table dbo.Produtos    Script Date: 09/09/98 09:15:15 ******/
CREATE TABLE dbo.Produtos (
	pd_Codigo int NOT NULL ,
	pd_Digito tinyint NOT NULL ,
	pd_Descricao varchar (80) NOT NULL ,
	pd_Embalagem varchar (16) NULL ,
	pd_Unidade varchar (16) NULL ,
	pd_Unidades int NOT NULL CONSTRAINT DF_Produtos_pd_Unidades DEFAULT (1),
	pd_EmbalagemMaster int NOT NULL CONSTRAINT DF_Produtos_pd_Master DEFAULT (1),
	pd_PesoBruto numeric(6, 2) NOT NULL CONSTRAINT DF_Produtos_pd_PesoBruto DEFAULT (0),
	pd_Disponivel bit NOT NULL ,
	pd_Renovado bit NOT NULL CONSTRAINT DF_Produtos_pd_Renovado DEFAULT (1),
	pd_TimeStamp datetime NOT NULL CONSTRAINT DF_Produtos_pd_TimeStamp DEFAULT (getdate()),
	pd_DisponibilidadeTimeStamp datetime NOT NULL ,
	CONSTRAINT PK_Produtos PRIMARY KEY  NONCLUSTERED 
	(
		pd_Codigo
	) WITH  FILLFACTOR = 90
)
GO

 CREATE CLUSTERED INDEX IX_ProdutosPorDescricao ON dbo.Produtos(pd_Descricao) WITH  FILLFACTOR = 90
GO

 CREATE  INDEX IX_ProdutosPorDispTimeStamp ON dbo.Produtos(pd_DisponibilidadeTimeStamp) WITH  FILLFACTOR = 90
GO

 CREATE  INDEX IX_ProdutosPorTimeStamp ON dbo.Produtos(pd_TimeStamp) WITH  FILLFACTOR = 90
GO

/****** Object:  Table dbo.TabelaPrecos    Script Date: 09/09/98 09:15:15 ******/
CREATE TABLE dbo.TabelaPrecos (
	tp_Codigo smallint NOT NULL ,
	CONSTRAINT PK_TabelaPrecos PRIMARY KEY  CLUSTERED 
	(
		tp_Codigo
	) WITH  FILLFACTOR = 90
)
GO

/****** Object:  Table dbo.Precos    Script Date: 09/09/98 09:15:15 ******/
CREATE TABLE dbo.Precos (
	pr_Tabela smallint NOT NULL ,
	pr_Produto int NOT NULL ,
	pr_Complemento varchar(32) NOT NULL ,
	pr_Brinde bit NOT NULL ,
	pr_Preco1 numeric(10, 2) NOT NULL ,
	pr_Preco2 numeric(10, 2) NOT NULL ,
	pr_Preco3 numeric(10, 2) NOT NULL ,
	pr_Preco4 numeric(10, 2) NOT NULL ,
	pr_Preco5 numeric(10, 2) NOT NULL ,
	pr_Preco6 numeric(10, 2) NOT NULL ,
	pr_Preco7 numeric(10, 2) NOT NULL ,
	pr_Preco8 numeric(10, 2) NOT NULL ,
	pr_DescontoMaximo numeric(4, 2) NOT NULL ,
	pr_TimeStamp datetime NOT NULL ,
	CONSTRAINT PK_Precos PRIMARY KEY  CLUSTERED 
	(
		pr_Tabela,
		pr_Produto
	) WITH  FILLFACTOR = 90,
	CONSTRAINT FK_Precos_Produtos FOREIGN KEY 
	(
		pr_Produto
	) REFERENCES dbo.Produtos (
		pd_Codigo
	),
	CONSTRAINT FK_Precos_TabelaPrecos FOREIGN KEY 
	(
		pr_Tabela
	) REFERENCES dbo.TabelaPrecos (
		tp_Codigo
	)
)
GO

 CREATE  INDEX IX_PrecosPorTimeStamp ON dbo.Precos(pr_Tabela, pr_TimeStamp) WITH  FILLFACTOR = 90
GO

/****** Object:  Table dbo.Vendedores    Script Date: 09/09/98 09:15:15 ******/
CREATE TABLE dbo.Vendedores (
	vd_Codigo smallint NOT NULL ,
	vd_Nome varchar (60) NULL ,
	vd_Senha varchar (16) NULL ,
	vd_UltimaAtualizacao datetime NOT NULL ,
	vd_TabelaPrecos smallint NOT NULL ,
	vd_Renovado bit NOT NULL CONSTRAINT DF_Vendedores_vd_Renovado DEFAULT (1),
	CONSTRAINT PK_Vendedores PRIMARY KEY  CLUSTERED 
	(
		vd_Codigo
	) WITH  FILLFACTOR = 90,
	CONSTRAINT FK_Vendedores_TabelaPrecos FOREIGN KEY 
	(
		vd_TabelaPrecos
	) REFERENCES dbo.TabelaPrecos (
		tp_Codigo
	)
)
GO

/****** Object:  Table dbo.Blocos    Script Date: 09/09/98 09:15:15 ******/
CREATE TABLE dbo.Blocos (
	PrimeiroPedido int NOT NULL ,
	UltimoPedido int NOT NULL ,
	Entrega datetime NOT NULL CONSTRAINT DF_Blocos_Entrega DEFAULT (getdate()),
	Vendedor smallint NOT NULL ,
	BlocoAberto bit NOT NULL CONSTRAINT DF_Blocos_BlocoAberto DEFAULT (1),
	CONSTRAINT FK_Blocos_Vendedores FOREIGN KEY 
	(
		Vendedor
	) REFERENCES dbo.Vendedores (
		vd_Codigo
	)
)
GO

/****** Object:  Table dbo.Clientes    Script Date: 09/09/98 09:15:16 ******/
CREATE TABLE dbo.Clientes (
	cl_Codigo int NOT NULL ,
	cl_Digito tinyint NOT NULL ,
	cl_CGC varchar (18) NOT NULL ,
	cl_RazaoSocial varchar (60) NOT NULL ,
	cl_Fantasia varchar (60) NULL ,
	cl_Contato varchar (40) NULL ,
	cl_EnderecoComercial varchar (60) NOT NULL ,
	cl_EnderecoComercialBairro varchar (40) NULL ,
	cl_EnderecoComercialCidade varchar (30) NOT NULL ,
	cl_EnderecoComercialEstado varchar (2) NOT NULL ,
	cl_EnderecoComercialCEP varchar (9) NULL ,
	cl_EnderecoCobranca varchar (60) NULL ,
	cl_EnderecoCobrancaBairro varchar (40) NULL ,
	cl_EnderecoCobrancaCidade varchar (30) NULL ,
	cl_EnderecoCobrancaEstado varchar (2) NULL ,
	cl_EnderecoCobrancaCEP varchar (9) NULL ,
	cl_Telefone varchar (30) NULL ,
	cl_Fax varchar (30) NULL ,
	cl_RamoAtividade tinyint NULL ,
	cl_Cobranca varchar (10) NOT NULL ,
	cl_EmitirDuplicata bit NOT NULL ,
	cl_Vendedor smallint NOT NULL ,
	cl_Praca smallint NOT NULL ,
	cl_Limite numeric(10, 2) NOT NULL ,
	cl_ValorDisponivel numeric(10, 2) NOT NULL ,
	cl_Bloqueado bit NOT NULL ,
	cl_MotivoBloqueio varchar (64) NULL ,
	cl_TimeStamp datetime NOT NULL ,
	cl_LimiteTimeStamp datetime NOT NULL ,
	cl_Tabela smallint NULL CONSTRAINT DF__Clientes__cl_Tab__2EC5E7B8 DEFAULT (0),
	cl_Renovado bit NOT NULL CONSTRAINT DF_Clientes_cl_Renovado DEFAULT (1),
	CONSTRAINT PK_Clientes PRIMARY KEY  NONCLUSTERED 
	(
		cl_Codigo
	) WITH  FILLFACTOR = 90,
	CONSTRAINT FK_Clientes_Cobranca FOREIGN KEY 
	(
		cl_Cobranca
	) REFERENCES dbo.Cobranca (
		cb_Codigo
	),
	CONSTRAINT FK_Clientes_Vendedores FOREIGN KEY 
	(
		cl_Vendedor
	) REFERENCES dbo.Vendedores (
		vd_Codigo
	)
)
GO

 CREATE  UNIQUE INDEX IX_Clientes_por_Vendedor ON dbo.Clientes(cl_Vendedor, cl_Codigo) WITH  FILLFACTOR = 90
GO

 CREATE  CLUSTERED INDEX IX_Clientes_Por_VendETime ON dbo.Clientes(cl_Vendedor, cl_TimeStamp)
GO

/****** Object:  Table dbo.Mensagens    Script Date: 09/09/98 09:15:16 ******/
CREATE TABLE dbo.Mensagens (
	ms_Vendedor smallint NOT NULL ,
	ms_Mensagem text NOT NULL ,
	CONSTRAINT FK_Mensagens_Vendedores FOREIGN KEY 
	(
		ms_Vendedor
	) REFERENCES dbo.Vendedores (
		vd_Codigo
	)
)
GO

/****** Object:  Table dbo.Sessoes    Script Date: 09/09/98 09:15:16 ******/
CREATE TABLE dbo.Sessoes (
	ss_Vendedor smallint NOT NULL ,
	ss_Inicio datetime NOT NULL ,
	ss_final datetime NULL ,
	CONSTRAINT PK_Sessoes PRIMARY KEY  CLUSTERED 
	(
		ss_Vendedor,
		ss_Inicio
	),
	CONSTRAINT FK_Sessoes_Vendedores FOREIGN KEY 
	(
		ss_Vendedor
	) REFERENCES dbo.Vendedores (
		vd_Codigo
	)
)
GO


/****** Object:  Table dbo.Titulos    Script Date: 09/09/98 09:15:16 ******/
CREATE TABLE dbo.Titulos (
	ti_Numero varchar (40) NOT NULL ,
	ti_Cliente int NOT NULL ,
	ti_Valor numeric(10, 2) NULL ,
	ti_Emissao varchar (16) NULL ,
	ti_Vencimento varchar (16) NULL ,
	ti_TimeStamp datetime NOT NULL CONSTRAINT DF_Titulos_ti_TimeStamp DEFAULT (getdate()),
	CONSTRAINT PK_Titulos PRIMARY KEY  NONCLUSTERED 
	(
		ti_Numero
	),
	CONSTRAINT FK_Titulos_Clientes FOREIGN KEY 
	(
		ti_Cliente
	) REFERENCES dbo.Clientes (
		cl_Codigo
	)
)
GO

 CREATE CLUSTERED INDEX IX_Titulos_por_Cliente ON dbo.Titulos(ti_Cliente) WITH  FILLFACTOR = 90
GO



CREATE TABLE dbo.Concorrentes (
	co_Sigla varchar (16) NOT NULL ,
	co_Nome varchar (64) NOT NULL ,
	CONSTRAINT PK_Concorrentes PRIMARY KEY  CLUSTERED
	(
		co_Sigla
	)
)
GO
