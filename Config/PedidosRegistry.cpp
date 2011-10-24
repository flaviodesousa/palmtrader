// PedidosRegistry.cpp: implementation of the CPedidosRegistry class.
//
//////////////////////////////////////////////////////////////////////
// $Archive: /PalmTrader 1/Config/PedidosRegistry.cpp $
// $Author: Flávio $
// $Date: 30/09/98 15:40 $
/* $History: PedidosRegistry.cpp $
 * 
 * *****************  Version 3  *****************
 * User: Flávio       Date: 30/09/98   Time: 15:40
 * Updated in $/PalmTrader 1/Config
 * Incluídos comentários de controle de versão
 */

#include "stdafx.h"

#include "PedidosRegistry.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

static void RegShowError(LONG lRc, int lineno)
{
	if (lRc != ERROR_SUCCESS)
	{
		CString msg;

		msg.Format(_T("CreateEx returned %ld at %d"), lRc, lineno);
		AfxMessageBox(msg);
	}
}

static const unsigned short PedidosRegistryKey[] = _T("SOFTWARE\\ZTech\\PalmTrader\\1.0");

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPedidosRegistry::CPedidosRegistry(BOOL bKeepOpen)
{
	LONG lRc;
	DWORD dwDisposition;

	lRc = RegCreateKeyEx(HKEY_LOCAL_MACHINE,
		PedidosRegistryKey,
		0,
		NULL,
		0,
		0,
		NULL,
		&hKey,
		&dwDisposition);
	if (lRc != ERROR_SUCCESS) RegShowError(lRc, __LINE__);
	ASSERT(lRc == ERROR_SUCCESS);

	if (dwDisposition == REG_CREATED_NEW_KEY)
	{
		SetString(_T("Conexao"), _T("<não definido>"));
		SetString(_T("Servidor"), _T("192.168.55.1"));
		SetDWord(_T("Porta"), 47375);
		SetDWord(_T("Tentativas"), 3);

		SetDWord(_T("VendedorCodigo"), 0);
		SetString(_T("VendedorNome"), _T("<não definido>"));
		SetString(_T("VendedorSenha"), _T("<não definido>"));
	}

	if (bKeepOpen)
		bIsOpen = TRUE;
	else
		Close();
}

CPedidosRegistry::~CPedidosRegistry()
{
	if (bIsOpen)
		Close();
}

void CPedidosRegistry::Open()
{
	LONG lRc;

	lRc = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
		PedidosRegistryKey,
		0,
		KEY_ALL_ACCESS,
		&hKey);
	if (lRc != ERROR_SUCCESS) RegShowError(lRc, __LINE__);
	ASSERT(lRc == ERROR_SUCCESS);

	bIsOpen = TRUE;
}

void CPedidosRegistry::Close()
{
	LONG lRc;

	lRc = RegCloseKey(hKey);
	if (lRc != ERROR_SUCCESS) RegShowError(lRc, __LINE__);
	ASSERT(lRc == ERROR_SUCCESS);

	bIsOpen = FALSE;
}

CString CPedidosRegistry::GetString(CString sName, CString sDefault, int nMaxSize)
{
	LONG lRc;
	CString sResult;
	DWORD dwType, dwLength = nMaxSize;
	BOOL bWasOpen;

	bWasOpen = bIsOpen;

	if (!bWasOpen) Open();

	lRc = RegQueryValueEx(hKey,
		sName,
		NULL,
		&dwType,
		(BYTE *)sResult.GetBuffer(nMaxSize+1),
		&dwLength);
	sResult.ReleaseBuffer();
	if (dwType == REG_NONE && lRc == ERROR_INVALID_PARAMETER) 
	{
		sResult = sDefault;
		SetString(sName, sDefault);
		lRc = ERROR_SUCCESS;
		dwType = REG_SZ;
	}
	if (lRc != ERROR_SUCCESS) RegShowError(lRc, __LINE__);
	ASSERT(lRc == ERROR_SUCCESS);
	ASSERT(dwType == REG_SZ);


	if (!bWasOpen) Close();

	return sResult;
}

void CPedidosRegistry::SetString(CString sName, CString sValue)
{
	LONG lRc;
	DWORD dwLength, dwType;
	BOOL bWasOpen;

	bWasOpen = bIsOpen;

	dwLength = sValue.GetLength();
	dwType = REG_SZ;

	if (!bWasOpen) Open();

	lRc = RegSetValueEx(hKey,
		sName,
		0,
		dwType,
		(BYTE *)sValue.GetBuffer(dwLength+1), //lpszResultBuffer,
		(dwLength+1)*2);
	sValue.ReleaseBuffer();
	if (lRc != ERROR_SUCCESS) RegShowError(lRc, __LINE__);
	ASSERT(lRc == ERROR_SUCCESS);
	ASSERT(dwType == REG_SZ);

	if (!bWasOpen) Close();
}

DWORD CPedidosRegistry::GetDWord(CString sName, DWORD dwDefault)
{
	LONG lRc;
	DWORD dwResult;
	DWORD dwType, dwLength;
	BOOL bWasOpen;

	bWasOpen = bIsOpen;

	if (!bWasOpen) Open();

	dwLength = sizeof(dwResult);
	dwType = 0; // Just to help checking

	lRc = RegQueryValueEx(hKey,
		sName,
		NULL,
		&dwType,
		(BYTE *)&dwResult,
		&dwLength);
	if (dwType == REG_NONE && lRc == ERROR_INVALID_PARAMETER)
	{
		dwResult = dwDefault;
		SetDWord(sName, dwDefault);
		lRc = ERROR_SUCCESS;
		dwType = REG_DWORD;
	}
	if (lRc != ERROR_SUCCESS) RegShowError(lRc, __LINE__);
	ASSERT(lRc == ERROR_SUCCESS);
	ASSERT(dwType == REG_DWORD);

	if (!bWasOpen) Close();

	return dwResult;
}

void CPedidosRegistry::SetDWord(CString sName, DWORD dwValue)
{
	LONG lRc;
	DWORD dwLength, dwType;
	BOOL bWasOpen;

	bWasOpen = bIsOpen;

	dwLength = sizeof(dwValue);
	dwType = REG_DWORD;

	if (!bWasOpen) Open();

	lRc = RegSetValueEx(hKey,
		sName,
		0,
		dwType,
		(BYTE *)&dwValue,
		dwLength);
	if (lRc != ERROR_SUCCESS) RegShowError(lRc, __LINE__);
	ASSERT(lRc == ERROR_SUCCESS);

	if (!bWasOpen) Close();
}
