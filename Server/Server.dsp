# Microsoft Developer Studio Project File - Name="Server" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Server - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Server.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Server.mak" CFG="Server - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Server - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Server - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""$/PalmTrader 1/Server", PEAAAAAA"
# PROP Scc_LocalPath "."
# PROP WCE_Configuration "H/PC Ver. 2.00"
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Server - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /G5 /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Server - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 mswsock.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Server - Win32 Release"
# Name "Server - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AutoSynchronization.cpp
# End Source File
# Begin Source File

SOURCE=.\ClientesSynchronization.cpp
# End Source File
# Begin Source File

SOURCE=.\CodigosDeCobrancaSynchronization.cpp
# End Source File
# Begin Source File

SOURCE=.\Configuration.cpp
# End Source File
# Begin Source File

SOURCE=.\ConnectionThread.cpp
# End Source File
# Begin Source File

SOURCE=.\CString2double.cpp
# End Source File
# Begin Source File

SOURCE=.\CString2sz.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogAtualizar.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogAtualizarAvancado.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogErros.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogOpcoes.cpp
# End Source File
# Begin Source File

SOURCE=.\EstoqueSynchronization.cpp
# End Source File
# Begin Source File

SOURCE=.\Licensing.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\PartialClientesSynchronization.cpp
# End Source File
# Begin Source File

SOURCE=.\PartialPrecosSynchronization.cpp
# End Source File
# Begin Source File

SOURCE=.\PartialProdutosSynchronization.cpp
# End Source File
# Begin Source File

SOURCE=.\Pedido.cpp
# End Source File
# Begin Source File

SOURCE=.\PedidoItem.cpp
# End Source File
# Begin Source File

SOURCE=.\PedidosSynchronization.cpp
# End Source File
# Begin Source File

SOURCE=.\PlanosSynchronization.cpp
# End Source File
# Begin Source File

SOURCE=.\PrecosSynchronization.cpp
# End Source File
# Begin Source File

SOURCE=.\ProdutosSynchronization.cpp
# End Source File
# Begin Source File

SOURCE=.\Registry.cpp
# End Source File
# Begin Source File

SOURCE=.\RSBlocos.cpp
# End Source File
# Begin Source File

SOURCE=.\RSClientes.cpp
# End Source File
# Begin Source File

SOURCE=.\RSClientesAlterados.cpp
# End Source File
# Begin Source File

SOURCE=.\RSCobranca.cpp
# End Source File
# Begin Source File

SOURCE=.\RSCondicoesVenda.cpp
# End Source File
# Begin Source File

SOURCE=.\RSPlanos.cpp
# End Source File
# Begin Source File

SOURCE=.\RSPrecos.cpp
# End Source File
# Begin Source File

SOURCE=.\RSPrecosAlterados.cpp
# End Source File
# Begin Source File

SOURCE=.\RSProdutos.cpp
# End Source File
# Begin Source File

SOURCE=.\RSProdutosAlterados.cpp
# End Source File
# Begin Source File

SOURCE=.\RSProdutosComPrecos.cpp
# End Source File
# Begin Source File

SOURCE=.\RSSessoes.cpp
# End Source File
# Begin Source File

SOURCE=.\RSTabelasPrecos.cpp
# End Source File
# Begin Source File

SOURCE=.\RSTitulos.cpp
# End Source File
# Begin Source File

SOURCE=.\RSTitulosAlterados.cpp
# End Source File
# Begin Source File

SOURCE=.\RSTitulosPorVendedor.cpp
# End Source File
# Begin Source File

SOURCE=.\RSVendedores.cpp
# End Source File
# Begin Source File

SOURCE=.\Server.cpp
# End Source File
# Begin Source File

SOURCE=.\Server.rc
# End Source File
# Begin Source File

SOURCE=.\ServerDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\ServerView.cpp
# End Source File
# Begin Source File

SOURCE=.\SessionThread.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TabelasSynchronization.cpp
# End Source File
# Begin Source File

SOURCE=.\TitulosSynchronization.cpp
# End Source File
# Begin Source File

SOURCE=.\UserAppSynchronization.cpp
# End Source File
# Begin Source File

SOURCE=.\VendedoresSynchronization.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AutoSynchronization.h
# End Source File
# Begin Source File

SOURCE=.\ClientesSynchronization.h
# End Source File
# Begin Source File

SOURCE=.\CodigosDeCobrancaSynchronization.h
# End Source File
# Begin Source File

SOURCE=.\Configuration.h
# End Source File
# Begin Source File

SOURCE=.\ConnectionThread.h
# End Source File
# Begin Source File

SOURCE=.\DialogAtualizar.h
# End Source File
# Begin Source File

SOURCE=.\DialogAtualizarAvancado.h
# End Source File
# Begin Source File

SOURCE=.\DialogErros.h
# End Source File
# Begin Source File

SOURCE=.\DialogOpcoes.h
# End Source File
# Begin Source File

SOURCE=.\EstoqueSynchronization.h
# End Source File
# Begin Source File

SOURCE=.\Licensing.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\PartialClientesSynchronization.h
# End Source File
# Begin Source File

SOURCE=.\PartialPrecosSynchronization.h
# End Source File
# Begin Source File

SOURCE=.\PartialProdutosSynchronization.h
# End Source File
# Begin Source File

SOURCE=.\Pedido.h
# End Source File
# Begin Source File

SOURCE=.\PedidoItem.h
# End Source File
# Begin Source File

SOURCE=.\PedidosSynchronization.h
# End Source File
# Begin Source File

SOURCE=.\PlanosSynchronization.h
# End Source File
# Begin Source File

SOURCE=.\PrecosSynchronization.h
# End Source File
# Begin Source File

SOURCE=.\ProdutosSynchronization.h
# End Source File
# Begin Source File

SOURCE=.\Protocol.h
# End Source File
# Begin Source File

SOURCE=.\QSTools.h
# End Source File
# Begin Source File

SOURCE=.\Registry.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\RSBlocos.h
# End Source File
# Begin Source File

SOURCE=.\RSClientes.h
# End Source File
# Begin Source File

SOURCE=.\RSClientesAlterados.h
# End Source File
# Begin Source File

SOURCE=.\RSCobranca.h
# End Source File
# Begin Source File

SOURCE=.\RSCondicoesVenda.h
# End Source File
# Begin Source File

SOURCE=.\RSPlanos.h
# End Source File
# Begin Source File

SOURCE=.\RSPrecos.h
# End Source File
# Begin Source File

SOURCE=.\RSPrecosAlterados.h
# End Source File
# Begin Source File

SOURCE=.\RSProdutos.h
# End Source File
# Begin Source File

SOURCE=.\RSProdutosAlterados.h
# End Source File
# Begin Source File

SOURCE=.\RSProdutosComPrecos.h
# End Source File
# Begin Source File

SOURCE=.\RSSessoes.h
# End Source File
# Begin Source File

SOURCE=.\RSTabelasPrecos.h
# End Source File
# Begin Source File

SOURCE=.\RSTitulos.h
# End Source File
# Begin Source File

SOURCE=.\RSTitulosAlterados.h
# End Source File
# Begin Source File

SOURCE=.\RSTitulosPorVendedor.h
# End Source File
# Begin Source File

SOURCE=.\RSVendedores.h
# End Source File
# Begin Source File

SOURCE=.\Server.h
# End Source File
# Begin Source File

SOURCE=.\ServerDoc.h
# End Source File
# Begin Source File

SOURCE=.\ServerView.h
# End Source File
# Begin Source File

SOURCE=.\SessionThread.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TabelasSynchronization.h
# End Source File
# Begin Source File

SOURCE=.\TitulosSynchronization.h
# End Source File
# Begin Source File

SOURCE=.\UserAppSynchronization.h
# End Source File
# Begin Source File

SOURCE=.\VendedoresSynchronization.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Server.ico
# End Source File
# Begin Source File

SOURCE=.\res\Server.rc2
# End Source File
# Begin Source File

SOURCE=.\res\ServerDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Group "SQL scripts"

# PROP Default_Filter "sql"
# Begin Source File

SOURCE=.\ZTech.SQL
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\ztech.flex
# End Source File
# End Target
# End Project
