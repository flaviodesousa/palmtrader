# Microsoft Developer Studio Project File - Name="QSTransfer" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (WCE x86em) Application" 0x0b01
# TARGTYPE "Win32 (WCE MIPS) Application" 0x0a01
# TARGTYPE "Win32 (WCE SH) Application" 0x0901

CFG=QSTransfer - Win32 (WCE MIPS) Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "QSTransfer.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "QSTransfer.mak" CFG="QSTransfer - Win32 (WCE MIPS) Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "QSTransfer - Win32 (WCE MIPS) Release" (based on\
 "Win32 (WCE MIPS) Application")
!MESSAGE "QSTransfer - Win32 (WCE MIPS) Debug" (based on\
 "Win32 (WCE MIPS) Application")
!MESSAGE "QSTransfer - Win32 (WCE x86em) Release" (based on\
 "Win32 (WCE x86em) Application")
!MESSAGE "QSTransfer - Win32 (WCE x86em) Debug" (based on\
 "Win32 (WCE x86em) Application")
!MESSAGE "QSTransfer - Win32 (WCE SH) Release" (based on\
 "Win32 (WCE SH) Application")
!MESSAGE "QSTransfer - Win32 (WCE SH) Debug" (based on\
 "Win32 (WCE SH) Application")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""$/PalmTrader 1/QSTransfer", MPAAAAAA"
# PROP Scc_LocalPath "."
# PROP WCE_Configuration "H/PC Ver. 2.00"

!IF  "$(CFG)" == "QSTransfer - Win32 (WCE MIPS) Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WMIPSRel"
# PROP BASE Intermediate_Dir "WMIPSRel"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WMIPSRel"
# PROP Intermediate_Dir "WMIPSRel"
# PROP Target_Dir ""
CPP=clmips.exe
# ADD BASE CPP /nologo /MT /W3 /O2 /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "NDEBUG" /D "MIPS" /D "_MIPS_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_AFXDLL" /Yu"stdafx.h" /QMRWCE /c
# ADD CPP /nologo /MT /W3 /O2 /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "NDEBUG" /D "MIPS" /D "_MIPS_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_AFXDLL" /Yu"stdafx.h" /QMRWCE /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /r /d "MIPS" /d "_MIPS_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /r /d "MIPS" /d "_MIPS_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "NDEBUG" /d "_AFXDLL"
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /entry:"wWinMainCRTStartup" /machine:MIPS /subsystem:$(CESubsystem)
# SUBTRACT BASE LINK32 /pdb:none /nodefaultlib
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /machine:MIPS /subsystem:$(CESubsystem)
# SUBTRACT LINK32 /pdb:none /nodefaultlib
PFILE=pfile.exe
# ADD BASE PFILE COPY
# ADD PFILE COPY

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE MIPS) Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WMIPSDbg"
# PROP BASE Intermediate_Dir "WMIPSDbg"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WMIPSDbg"
# PROP Intermediate_Dir "WMIPSDbg"
# PROP Target_Dir ""
CPP=clmips.exe
# ADD BASE CPP /nologo /MTd /W3 /Zi /Od /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "DEBUG" /D "MIPS" /D "_MIPS_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_AFXDLL" /Yu"stdafx.h" /QMRWCE /c
# ADD CPP /nologo /MTd /W3 /Zi /Od /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "DEBUG" /D "MIPS" /D "_MIPS_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_AFXDLL" /Yu"stdafx.h" /QMRWCE /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /r /d "MIPS" /d "_MIPS_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /r /d "MIPS" /d "_MIPS_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "DEBUG" /d "_AFXDLL"
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /entry:"wWinMainCRTStartup" /debug /machine:MIPS /subsystem:$(CESubsystem)
# SUBTRACT BASE LINK32 /pdb:none /nodefaultlib
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /debug /machine:MIPS /subsystem:$(CESubsystem)
# SUBTRACT LINK32 /pdb:none /nodefaultlib
PFILE=pfile.exe
# ADD BASE PFILE COPY
# ADD PFILE COPY

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE x86em) Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "x86emRel"
# PROP BASE Intermediate_Dir "x86emRel"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "x86emRel"
# PROP Intermediate_Dir "x86emRel"
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /MT /W3 /O2 /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_UNICODE" /D "WIN32" /D "STRICT" /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "_WIN32_WCE_EMULATION" /D "INTERNATIONAL" /D "USA" /D "INTLMSG_CODEPAGE" /D "NDEBUG" /D "x86" /D "i486" /D "_x86_" /D "_AFXDLL" /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /O2 /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_UNICODE" /D "WIN32" /D "STRICT" /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "_WIN32_WCE_EMULATION" /D "INTERNATIONAL" /D "USA" /D "INTLMSG_CODEPAGE" /D "NDEBUG" /D "x86" /D "i486" /D "_x86_" /D "_AFXDLL" /Yu"stdafx.h" /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d UNDER_CE=$(CEVersion) /d "UNICODE" /d "_UNICODE" /d "WIN32" /d "STRICT" /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "_WIN32_WCE_EMULATION" /d "INTERNATIONAL" /d "USA" /d "INTLMSG_CODEPAGE" /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d UNDER_CE=$(CEVersion) /d "UNICODE" /d "_UNICODE" /d "WIN32" /d "STRICT" /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "_WIN32_WCE_EMULATION" /d "INTERNATIONAL" /d "USA" /d "INTLMSG_CODEPAGE" /d "NDEBUG" /d "_AFXDLL"
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /machine:I386 /windowsce:emulation
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /machine:I386 /windowsce:emulation
EMPFILE=empfile.exe
# ADD BASE EMPFILE -COPY
# ADD EMPFILE -COPY

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE x86em) Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "x86emDbg"
# PROP BASE Intermediate_Dir "x86emDbg"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "x86emDbg"
# PROP Intermediate_Dir "x86emDbg"
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /MTd /W3 /Gm /Zi /Od /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_UNICODE" /D "WIN32" /D "STRICT" /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "_WIN32_WCE_EMULATION" /D "INTERNATIONAL" /D "USA" /D "INTLMSG_CODEPAGE" /D "_DEBUG" /D "x86" /D "i486" /D "_x86_" /D "_AFXDLL" /Yu"stdafx.h" /c
# ADD CPP /nologo /MTd /W3 /Gm /Zi /Od /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_UNICODE" /D "WIN32" /D "STRICT" /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "_WIN32_WCE_EMULATION" /D "INTERNATIONAL" /D "USA" /D "INTLMSG_CODEPAGE" /D "_DEBUG" /D "x86" /D "i486" /D "_x86_" /D "_AFXDLL" /Yu"stdafx.h" /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d UNDER_CE=$(CEVersion) /d "UNICODE" /d "_UNICODE" /d "WIN32" /d "STRICT" /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "_WIN32_WCE_EMULATION" /d "INTERNATIONAL" /d "USA" /d "INTLMSG_CODEPAGE" /d "_DEBUG" /d "x86" /d "i486" /d "_x86_" /d "_AFXDLL"
# ADD RSC /l 0x409 /d UNDER_CE=$(CEVersion) /d "UNICODE" /d "_UNICODE" /d "WIN32" /d "STRICT" /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "_WIN32_WCE_EMULATION" /d "INTERNATIONAL" /d "USA" /d "INTLMSG_CODEPAGE" /d "_DEBUG" /d "x86" /d "i486" /d "_x86_" /d "_AFXDLL"
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386 /windowsce:emulation
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386 /windowsce:emulation
EMPFILE=empfile.exe
# ADD BASE EMPFILE -COPY
# ADD EMPFILE -COPY

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE SH) Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WCESHRel"
# PROP BASE Intermediate_Dir "WCESHRel"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WCESHRel"
# PROP Intermediate_Dir "WCESHRel"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=shcl.exe
# ADD BASE CPP /nologo /MT /W3 /O2 /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "NDEBUG" /D "SHx" /D "SH3" /D "_SH3_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_AFXDLL" /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /O2 /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "NDEBUG" /D "SHx" /D "SH3" /D "_SH3_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_AFXDLL" /FR /Yu"stdafx.h" /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /r /d "SHx" /d "SH3" /d "_SH3_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /r /d "SHx" /d "SH3" /d "_SH3_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "NDEBUG" /d "_AFXDLL"
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /entry:"wWinMainCRTStartup" /machine:SH3 /subsystem:$(CESubsystem)
# SUBTRACT BASE LINK32 /pdb:none /nodefaultlib
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /machine:SH3 /subsystem:$(CESubsystem)
# SUBTRACT LINK32 /pdb:none /nodefaultlib
PFILE=pfile.exe
# ADD BASE PFILE COPY
# ADD PFILE COPY

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE SH) Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WCESHDbg"
# PROP BASE Intermediate_Dir "WCESHDbg"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WCESHDbg"
# PROP Intermediate_Dir "WCESHDbg"
# PROP Target_Dir ""
CPP=shcl.exe
# ADD BASE CPP /nologo /MTd /W3 /Zi /Od /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "DEBUG" /D "SHx" /D "SH3" /D "_SH3_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_AFXDLL" /Yu"stdafx.h" /c
# ADD CPP /nologo /MTd /W3 /Zi /Od /D _WIN32_WCE=$(CEVersion) /D "$(CEConfigName)" /D "DEBUG" /D "SHx" /D "SH3" /D "_SH3_" /D UNDER_CE=$(CEVersion) /D "UNICODE" /D "_AFXDLL" /Yu"stdafx.h" /c
RSC=rc.exe
# ADD BASE RSC /l 0x409 /r /d "SHx" /d "SH3" /d "_SH3_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /r /d "SHx" /d "SH3" /d "_SH3_" /d UNDER_CE=$(CEVersion) /d _WIN32_WCE=$(CEVersion) /d "$(CEConfigName)" /d "UNICODE" /d "DEBUG" /d "_AFXDLL"
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /entry:"wWinMainCRTStartup" /debug /machine:SH3 /subsystem:$(CESubsystem)
# SUBTRACT BASE LINK32 /pdb:none /nodefaultlib
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /debug /machine:SH3 /subsystem:$(CESubsystem)
# SUBTRACT LINK32 /pdb:none /nodefaultlib
PFILE=pfile.exe
# ADD BASE PFILE COPY
# ADD PFILE COPY

!ENDIF 

# Begin Target

# Name "QSTransfer - Win32 (WCE MIPS) Release"
# Name "QSTransfer - Win32 (WCE MIPS) Debug"
# Name "QSTransfer - Win32 (WCE x86em) Release"
# Name "QSTransfer - Win32 (WCE x86em) Debug"
# Name "QSTransfer - Win32 (WCE SH) Release"
# Name "QSTransfer - Win32 (WCE SH) Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CString2sz.cpp

!IF  "$(CFG)" == "QSTransfer - Win32 (WCE MIPS) Release"

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE MIPS) Debug"

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE x86em) Release"

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE x86em) Debug"

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE SH) Release"

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE SH) Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DB.cpp

!IF  "$(CFG)" == "QSTransfer - Win32 (WCE MIPS) Release"

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE MIPS) Debug"

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE x86em) Release"

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE x86em) Debug"

DEP_CPP_DB_CP=\
	".\DB.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"wcedb.h"\
	

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE SH) Release"

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE SH) Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DBBlocos.cpp

!IF  "$(CFG)" == "QSTransfer - Win32 (WCE MIPS) Release"

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE MIPS) Debug"

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE x86em) Release"

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE x86em) Debug"

DEP_CPP_DBBLO=\
	".\DB.h"\
	".\DBBlocos.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"wcedb.h"\
	

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE SH) Release"

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE SH) Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DBItens.cpp

!IF  "$(CFG)" == "QSTransfer - Win32 (WCE MIPS) Release"

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE MIPS) Debug"

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE x86em) Release"

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE x86em) Debug"

DEP_CPP_DBITE=\
	".\DB.h"\
	".\DBItens.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"wcedb.h"\
	

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE SH) Release"

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE SH) Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DBPedidos.cpp

!IF  "$(CFG)" == "QSTransfer - Win32 (WCE MIPS) Release"

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE MIPS) Debug"

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE x86em) Release"

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE x86em) Debug"

DEP_CPP_DBPED=\
	".\DB.h"\
	".\DBPedidos.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"wcedb.h"\
	

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE SH) Release"

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE SH) Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp

!IF  "$(CFG)" == "QSTransfer - Win32 (WCE MIPS) Release"

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE MIPS) Debug"

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE x86em) Release"

DEP_CPP_MAINF=\
	".\MainFrm.h"\
	".\QSTransfer.h"\
	".\StdAfx.h"\
	

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE x86em) Debug"

DEP_CPP_MAINF=\
	".\MainFrm.h"\
	".\QSTransfer.h"\
	".\StdAfx.h"\
	

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE SH) Release"

DEP_CPP_MAINF=\
	".\MainFrm.h"\
	".\QSTransfer.h"\
	".\StdAfx.h"\
	

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE SH) Debug"

DEP_CPP_MAINF=\
	".\MainFrm.h"\
	".\QSTransfer.h"\
	".\StdAfx.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\PedidosRegistry.cpp

!IF  "$(CFG)" == "QSTransfer - Win32 (WCE MIPS) Release"

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE MIPS) Debug"

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE x86em) Release"

DEP_CPP_PEDID=\
	".\PedidosRegistry.h"\
	".\StdAfx.h"\
	

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE x86em) Debug"

DEP_CPP_PEDID=\
	".\PedidosRegistry.h"\
	".\StdAfx.h"\
	

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE SH) Release"

DEP_CPP_PEDID=\
	".\PedidosRegistry.h"\
	".\StdAfx.h"\
	

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE SH) Debug"

DEP_CPP_PEDID=\
	".\PedidosRegistry.h"\
	".\StdAfx.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\QSClientes.cpp

!IF  "$(CFG)" == "QSTransfer - Win32 (WCE MIPS) Release"

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE MIPS) Debug"

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE x86em) Release"

DEP_CPP_QSCLI=\
	".\QSClientes.h"\
	".\QSFlatDatabase.h"\
	".\StdAfx.h"\
	

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE x86em) Debug"

DEP_CPP_QSCLI=\
	".\QSClientes.h"\
	".\QSFlatDatabase.h"\
	".\StdAfx.h"\
	

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE SH) Release"

DEP_CPP_QSCLI=\
	".\QSClientes.h"\
	".\QSFlatDatabase.h"\
	".\StdAfx.h"\
	

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE SH) Debug"

DEP_CPP_QSCLI=\
	".\QSClientes.h"\
	".\QSFlatDatabase.h"\
	".\StdAfx.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\QSCobranca.cpp

!IF  "$(CFG)" == "QSTransfer - Win32 (WCE MIPS) Release"

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE MIPS) Debug"

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE x86em) Release"

DEP_CPP_QSCOB=\
	".\QSCobranca.h"\
	".\QSFlatDatabase.h"\
	".\StdAfx.h"\
	

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE x86em) Debug"

DEP_CPP_QSCOB=\
	".\QSCobranca.h"\
	".\QSFlatDatabase.h"\
	".\StdAfx.h"\
	

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE SH) Release"

DEP_CPP_QSCOB=\
	".\QSCobranca.h"\
	".\QSFlatDatabase.h"\
	".\StdAfx.h"\
	

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE SH) Debug"

DEP_CPP_QSCOB=\
	".\QSCobranca.h"\
	".\QSFlatDatabase.h"\
	".\StdAfx.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\QSCondicoesVenda.cpp

!IF  "$(CFG)" == "QSTransfer - Win32 (WCE MIPS) Release"

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE MIPS) Debug"

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE x86em) Release"

DEP_CPP_QSCON=\
	".\QSCondicoesVenda.h"\
	".\QSFlatDatabase.h"\
	".\StdAfx.h"\
	

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE x86em) Debug"

DEP_CPP_QSCON=\
	".\QSCondicoesVenda.h"\
	".\QSFlatDatabase.h"\
	".\StdAfx.h"\
	

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE SH) Release"

DEP_CPP_QSCON=\
	".\QSCondicoesVenda.h"\
	".\QSFlatDatabase.h"\
	".\StdAfx.h"\
	

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE SH) Debug"

DEP_CPP_QSCON=\
	".\QSCondicoesVenda.h"\
	".\QSFlatDatabase.h"\
	".\StdAfx.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\QSFlatDatabase.cpp

!IF  "$(CFG)" == "QSTransfer - Win32 (WCE MIPS) Release"

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE MIPS) Debug"

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE x86em) Release"

DEP_CPP_QSFLA=\
	".\QSFlatDatabase.h"\
	".\StdAfx.h"\
	

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE x86em) Debug"

DEP_CPP_QSFLA=\
	".\QSFlatDatabase.h"\
	".\StdAfx.h"\
	

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE SH) Release"

DEP_CPP_QSFLA=\
	".\QSFlatDatabase.h"\
	".\StdAfx.h"\
	

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE SH) Debug"

DEP_CPP_QSFLA=\
	".\QSFlatDatabase.h"\
	".\StdAfx.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\QSPlanos.cpp

!IF  "$(CFG)" == "QSTransfer - Win32 (WCE MIPS) Release"

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE MIPS) Debug"

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE x86em) Release"

DEP_CPP_QSPLA=\
	".\QSFlatDatabase.h"\
	".\QSPlanos.h"\
	".\StdAfx.h"\
	

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE x86em) Debug"

DEP_CPP_QSPLA=\
	".\QSFlatDatabase.h"\
	".\QSPlanos.h"\
	".\StdAfx.h"\
	

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE SH) Release"

DEP_CPP_QSPLA=\
	".\QSFlatDatabase.h"\
	".\QSPlanos.h"\
	".\StdAfx.h"\
	

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE SH) Debug"

DEP_CPP_QSPLA=\
	".\QSFlatDatabase.h"\
	".\QSPlanos.h"\
	".\StdAfx.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\QSProdutos.cpp

!IF  "$(CFG)" == "QSTransfer - Win32 (WCE MIPS) Release"

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE MIPS) Debug"

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE x86em) Release"

DEP_CPP_QSPRO=\
	".\QSFlatDatabase.h"\
	".\QSProdutos.h"\
	".\StdAfx.h"\
	

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE x86em) Debug"

DEP_CPP_QSPRO=\
	".\QSFlatDatabase.h"\
	".\QSProdutos.h"\
	".\StdAfx.h"\
	

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE SH) Release"

DEP_CPP_QSPRO=\
	".\QSFlatDatabase.h"\
	".\QSProdutos.h"\
	".\StdAfx.h"\
	

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE SH) Debug"

DEP_CPP_QSPRO=\
	".\QSFlatDatabase.h"\
	".\QSProdutos.h"\
	".\StdAfx.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\QSTitulos.cpp

!IF  "$(CFG)" == "QSTransfer - Win32 (WCE MIPS) Release"

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE MIPS) Debug"

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE x86em) Release"

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE x86em) Debug"

DEP_CPP_QSTIT=\
	".\QSFlatDatabase.h"\
	".\QSTitulos.h"\
	".\QSTransfer.h"\
	".\StdAfx.h"\
	

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE SH) Release"

DEP_CPP_QSTIT=\
	".\QSFlatDatabase.h"\
	".\QSTitulos.h"\
	".\QSTransfer.h"\
	".\StdAfx.h"\
	

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE SH) Debug"

DEP_CPP_QSTIT=\
	".\QSFlatDatabase.h"\
	".\QSTitulos.h"\
	".\QSTransfer.h"\
	".\StdAfx.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\QSTransfer.cpp

!IF  "$(CFG)" == "QSTransfer - Win32 (WCE MIPS) Release"

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE MIPS) Debug"

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE x86em) Release"

DEP_CPP_QSTRA=\
	".\MainFrm.h"\
	".\Protocol.h"\
	".\QSClientes.h"\
	".\QSCobranca.h"\
	".\QSCondicoesVenda.h"\
	".\QSDatabase.h"\
	".\QSFlatDatabase.h"\
	".\QSPlanos.h"\
	".\QSProdutos.h"\
	".\QSTransfer.h"\
	".\QSTransferDoc.h"\
	".\QSTransferView.h"\
	".\SessionThread.h"\
	".\StdAfx.h"\
	
NODEP_CPP_QSTRA=\
	".\QSItens.h"\
	".\QSPedidos.h"\
	

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE x86em) Debug"

DEP_CPP_QSTRA=\
	".\DB.h"\
	".\DBItens.h"\
	".\DBPedidos.h"\
	".\MainFrm.h"\
	".\Protocol.h"\
	".\QSClientes.h"\
	".\QSCobranca.h"\
	".\QSCondicoesVenda.h"\
	".\QSDatabase.h"\
	".\QSFlatDatabase.h"\
	".\QSPlanos.h"\
	".\QSProdutos.h"\
	".\QSTitulos.h"\
	".\QSTransfer.h"\
	".\QSTransferDoc.h"\
	".\QSTransferView.h"\
	".\SessionThread.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"wcedb.h"\
	

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE SH) Release"

DEP_CPP_QSTRA=\
	".\MainFrm.h"\
	".\Protocol.h"\
	".\QSClientes.h"\
	".\QSCobranca.h"\
	".\QSCondicoesVenda.h"\
	".\QSDatabase.h"\
	".\QSFlatDatabase.h"\
	".\QSPlanos.h"\
	".\QSProdutos.h"\
	".\QSTitulos.h"\
	".\QSTransfer.h"\
	".\QSTransferDoc.h"\
	".\QSTransferView.h"\
	".\SessionThread.h"\
	".\StdAfx.h"\
	
NODEP_CPP_QSTRA=\
	".\QSItens.h"\
	".\QSPedidos.h"\
	

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE SH) Debug"

DEP_CPP_QSTRA=\
	".\MainFrm.h"\
	".\Protocol.h"\
	".\QSClientes.h"\
	".\QSCobranca.h"\
	".\QSCondicoesVenda.h"\
	".\QSDatabase.h"\
	".\QSFlatDatabase.h"\
	".\QSPlanos.h"\
	".\QSProdutos.h"\
	".\QSTitulos.h"\
	".\QSTransfer.h"\
	".\QSTransferDoc.h"\
	".\QSTransferView.h"\
	".\SessionThread.h"\
	".\StdAfx.h"\
	
NODEP_CPP_QSTRA=\
	".\QSItens.h"\
	".\QSPedidos.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\QSTransfer.rc

!IF  "$(CFG)" == "QSTransfer - Win32 (WCE MIPS) Release"

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE MIPS) Debug"

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE x86em) Release"

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE x86em) Debug"

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE SH) Release"

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE SH) Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\QSTransferDoc.cpp

!IF  "$(CFG)" == "QSTransfer - Win32 (WCE MIPS) Release"

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE MIPS) Debug"

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE x86em) Release"

DEP_CPP_QSTRAN=\
	".\Protocol.h"\
	".\QSClientes.h"\
	".\QSCobranca.h"\
	".\QSCondicoesVenda.h"\
	".\QSDatabase.h"\
	".\QSFlatDatabase.h"\
	".\QSPlanos.h"\
	".\QSProdutos.h"\
	".\QSTransfer.h"\
	".\QSTransferDoc.h"\
	".\SessionThread.h"\
	".\StdAfx.h"\
	
NODEP_CPP_QSTRAN=\
	".\QSItens.h"\
	".\QSPedidos.h"\
	

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE x86em) Debug"

DEP_CPP_QSTRAN=\
	".\DB.h"\
	".\DBItens.h"\
	".\DBPedidos.h"\
	".\Protocol.h"\
	".\QSClientes.h"\
	".\QSCobranca.h"\
	".\QSCondicoesVenda.h"\
	".\QSDatabase.h"\
	".\QSFlatDatabase.h"\
	".\QSPlanos.h"\
	".\QSProdutos.h"\
	".\QSTitulos.h"\
	".\QSTransfer.h"\
	".\QSTransferDoc.h"\
	".\SessionThread.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"wcedb.h"\
	

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE SH) Release"

DEP_CPP_QSTRAN=\
	".\Protocol.h"\
	".\QSClientes.h"\
	".\QSCobranca.h"\
	".\QSCondicoesVenda.h"\
	".\QSDatabase.h"\
	".\QSFlatDatabase.h"\
	".\QSPlanos.h"\
	".\QSProdutos.h"\
	".\QSTitulos.h"\
	".\QSTransfer.h"\
	".\QSTransferDoc.h"\
	".\SessionThread.h"\
	".\StdAfx.h"\
	
NODEP_CPP_QSTRAN=\
	".\QSItens.h"\
	".\QSPedidos.h"\
	

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE SH) Debug"

DEP_CPP_QSTRAN=\
	".\Protocol.h"\
	".\QSClientes.h"\
	".\QSCobranca.h"\
	".\QSCondicoesVenda.h"\
	".\QSDatabase.h"\
	".\QSFlatDatabase.h"\
	".\QSPlanos.h"\
	".\QSProdutos.h"\
	".\QSTitulos.h"\
	".\QSTransfer.h"\
	".\QSTransferDoc.h"\
	".\SessionThread.h"\
	".\StdAfx.h"\
	
NODEP_CPP_QSTRAN=\
	".\QSItens.h"\
	".\QSPedidos.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\QSTransferView.cpp

!IF  "$(CFG)" == "QSTransfer - Win32 (WCE MIPS) Release"

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE MIPS) Debug"

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE x86em) Release"

DEP_CPP_QSTRANS=\
	".\Protocol.h"\
	".\QSClientes.h"\
	".\QSCobranca.h"\
	".\QSCondicoesVenda.h"\
	".\QSDatabase.h"\
	".\QSFlatDatabase.h"\
	".\QSPlanos.h"\
	".\QSProdutos.h"\
	".\QSTransfer.h"\
	".\QSTransferDoc.h"\
	".\QSTransferView.h"\
	".\SessionThread.h"\
	".\StdAfx.h"\
	
NODEP_CPP_QSTRANS=\
	".\QSItens.h"\
	".\QSPedidos.h"\
	

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE x86em) Debug"

DEP_CPP_QSTRANS=\
	".\DB.h"\
	".\DBItens.h"\
	".\DBPedidos.h"\
	".\Protocol.h"\
	".\QSClientes.h"\
	".\QSCobranca.h"\
	".\QSCondicoesVenda.h"\
	".\QSDatabase.h"\
	".\QSFlatDatabase.h"\
	".\QSPlanos.h"\
	".\QSProdutos.h"\
	".\QSTitulos.h"\
	".\QSTransfer.h"\
	".\QSTransferDoc.h"\
	".\QSTransferView.h"\
	".\SessionThread.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"wcedb.h"\
	

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE SH) Release"

DEP_CPP_QSTRANS=\
	".\Protocol.h"\
	".\QSClientes.h"\
	".\QSCobranca.h"\
	".\QSCondicoesVenda.h"\
	".\QSDatabase.h"\
	".\QSFlatDatabase.h"\
	".\QSPlanos.h"\
	".\QSProdutos.h"\
	".\QSTitulos.h"\
	".\QSTransfer.h"\
	".\QSTransferDoc.h"\
	".\QSTransferView.h"\
	".\SessionThread.h"\
	".\StdAfx.h"\
	
NODEP_CPP_QSTRANS=\
	".\QSItens.h"\
	".\QSPedidos.h"\
	

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE SH) Debug"

DEP_CPP_QSTRANS=\
	".\Protocol.h"\
	".\QSClientes.h"\
	".\QSCobranca.h"\
	".\QSCondicoesVenda.h"\
	".\QSDatabase.h"\
	".\QSFlatDatabase.h"\
	".\QSPlanos.h"\
	".\QSProdutos.h"\
	".\QSTitulos.h"\
	".\QSTransfer.h"\
	".\QSTransferDoc.h"\
	".\QSTransferView.h"\
	".\SessionThread.h"\
	".\StdAfx.h"\
	
NODEP_CPP_QSTRANS=\
	".\QSItens.h"\
	".\QSPedidos.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\SessionThread.cpp

!IF  "$(CFG)" == "QSTransfer - Win32 (WCE MIPS) Release"

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE MIPS) Debug"

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE x86em) Release"

DEP_CPP_SESSI=\
	".\PedidosRegistry.h"\
	".\Protocol.h"\
	".\QSClientes.h"\
	".\QSCobranca.h"\
	".\QSCondicoesVenda.h"\
	".\QSDatabase.h"\
	".\QSFlatDatabase.h"\
	".\QSPlanos.h"\
	".\QSProdutos.h"\
	".\QSTools.h"\
	".\QSTransfer.h"\
	".\SessionThread.h"\
	".\StdAfx.h"\
	
NODEP_CPP_SESSI=\
	".\QSItens.h"\
	".\QSPedidos.h"\
	

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE x86em) Debug"

DEP_CPP_SESSI=\
	".\DB.h"\
	".\DBBlocos.h"\
	".\DBItens.h"\
	".\DBPedidos.h"\
	".\PedidosRegistry.h"\
	".\Protocol.h"\
	".\QSClientes.h"\
	".\QSCobranca.h"\
	".\QSCondicoesVenda.h"\
	".\QSDatabase.h"\
	".\QSFlatDatabase.h"\
	".\QSPlanos.h"\
	".\QSProdutos.h"\
	".\QSTitulos.h"\
	".\QSTools.h"\
	".\QSTransfer.h"\
	".\SessionThread.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"wcedb.h"\
	

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE SH) Release"

DEP_CPP_SESSI=\
	".\PedidosRegistry.h"\
	".\Protocol.h"\
	".\QSClientes.h"\
	".\QSCobranca.h"\
	".\QSCondicoesVenda.h"\
	".\QSDatabase.h"\
	".\QSFlatDatabase.h"\
	".\QSPlanos.h"\
	".\QSProdutos.h"\
	".\QSTitulos.h"\
	".\QSTools.h"\
	".\QSTransfer.h"\
	".\SessionThread.h"\
	".\StdAfx.h"\
	
NODEP_CPP_SESSI=\
	".\QSItens.h"\
	".\QSPedidos.h"\
	

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE SH) Debug"

DEP_CPP_SESSI=\
	".\PedidosRegistry.h"\
	".\Protocol.h"\
	".\QSClientes.h"\
	".\QSCobranca.h"\
	".\QSCondicoesVenda.h"\
	".\QSDatabase.h"\
	".\QSFlatDatabase.h"\
	".\QSPlanos.h"\
	".\QSProdutos.h"\
	".\QSTitulos.h"\
	".\QSTools.h"\
	".\QSTransfer.h"\
	".\SessionThread.h"\
	".\StdAfx.h"\
	
NODEP_CPP_SESSI=\
	".\QSItens.h"\
	".\QSPedidos.h"\
	

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "QSTransfer - Win32 (WCE MIPS) Release"

# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE MIPS) Debug"

# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE x86em) Release"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	
# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE x86em) Debug"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	
# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE SH) Release"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	
# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "QSTransfer - Win32 (WCE SH) Debug"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	
# ADD CPP /Yc"stdafx.h"

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\DB.h
# End Source File
# Begin Source File

SOURCE=.\DBBlocos.h
# End Source File
# Begin Source File

SOURCE=.\DBItens.h
# End Source File
# Begin Source File

SOURCE=.\DBPedidos.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\PedidosRegistry.h
# End Source File
# Begin Source File

SOURCE=.\Protocol.h
# End Source File
# Begin Source File

SOURCE=.\QSClientes.h
# End Source File
# Begin Source File

SOURCE=.\QSCobranca.h
# End Source File
# Begin Source File

SOURCE=.\QSCondicoesVenda.h
# End Source File
# Begin Source File

SOURCE=.\QSDatabase.h
# End Source File
# Begin Source File

SOURCE=.\QSFlatDatabase.h
# End Source File
# Begin Source File

SOURCE=.\QSPlanos.h
# End Source File
# Begin Source File

SOURCE=.\QSProdutos.h
# End Source File
# Begin Source File

SOURCE=.\QSTitulos.h
# End Source File
# Begin Source File

SOURCE=.\QSTools.h
# End Source File
# Begin Source File

SOURCE=.\QSTransfer.h
# End Source File
# Begin Source File

SOURCE=.\QSTransferDoc.h
# End Source File
# Begin Source File

SOURCE=.\QSTransferView.h
# End Source File
# Begin Source File

SOURCE=.\RequestsDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SessionThread.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Cmdbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\QSTransfer.ico
# End Source File
# Begin Source File

SOURCE=.\res\QSTransfer.rc2
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
