// Registry.cpp: implementation of the CRegistry class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Server.h"
#include "Registry.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

static char RegistryKey[] = _T("SOFTWARE\\ZTech\\Server\\1.0");

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRegistry::CRegistry(BOOL bKeepOpen)
{
	LONG lRc;
	DWORD dwDisposition;

	lRc = RegCreateKeyEx(HKEY_LOCAL_MACHINE,
		RegistryKey,
		0,
		NULL,
		REG_OPTION_NON_VOLATILE,
		KEY_ALL_ACCESS,
		NULL,
		&hKey,
		&dwDisposition);
	//if (lRc != ERROR_SUCCESS) RegShowError(lRc, __LINE__);
	ASSERT(lRc == ERROR_SUCCESS);

	if (dwDisposition == REG_CREATED_NEW_KEY)
	{
		SetString(_T("AppServidor"), _T(""));
		SetDWord(_T("AppPorta"), 47375);
		SetDWord(_T("Porta"), 47375);
		SetDWord(_T("PDBlocoAtual"), 1);
		SetDWord(_T("PDTamanhoAtual"), 100);
	}

	Close();

	if (bKeepOpen)
	{
		Open();
		bIsOpen = TRUE;
	}
}

CRegistry::~CRegistry()
{
	if (bIsOpen)
		Close();
}

//////////////////////////////////////////////////////////////////////
// Public Methods
//////////////////////////////////////////////////////////////////////

void CRegistry::Open()
{
	LONG lRc;

	lRc = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
		RegistryKey,
		0,
		KEY_ALL_ACCESS,
		&hKey);
	//if (lRc != ERROR_SUCCESS) RegShowError(lRc, __LINE__);
	ASSERT(lRc == ERROR_SUCCESS);

	bIsOpen = TRUE;
}

void CRegistry::Close()
{
	LONG lRc;

	lRc = RegCloseKey(hKey);
	//if (lRc != ERROR_SUCCESS) RegShowError(lRc, __LINE__);
	ASSERT(lRc == ERROR_SUCCESS);

	bIsOpen = FALSE;
}

CString CRegistry::GetString(CString sName, CString sDefault, int nMaxSize)
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
	if ((dwType == REG_NONE && lRc == ERROR_INVALID_PARAMETER) || lRc == ERROR_FILE_NOT_FOUND)
	{
		sResult = sDefault;
		SetString(sName, sDefault);
		lRc = ERROR_SUCCESS;
		dwType = REG_SZ;
	}
	//if (lRc != ERROR_SUCCESS) RegShowError(lRc, __LINE__);
	ASSERT(lRc == ERROR_SUCCESS);
	ASSERT(dwType == REG_SZ);


	if (!bWasOpen) Close();

	return sResult;
}

void CRegistry::SetString(CString sName, CString sValue)
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
	//if (lRc != ERROR_SUCCESS) RegShowError(lRc, __LINE__);
	ASSERT(lRc == ERROR_SUCCESS);
	ASSERT(dwType == REG_SZ);

	if (!bWasOpen) Close();
}

DWORD CRegistry::GetDWord(CString sName, DWORD dwDefault)
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
	if ((dwType == REG_NONE && lRc == ERROR_INVALID_PARAMETER) || lRc == ERROR_FILE_NOT_FOUND)
	{
		dwResult = dwDefault;
		SetDWord(sName, dwDefault);
		lRc = ERROR_SUCCESS;
		dwType = REG_DWORD;
	}
	//if (lRc != ERROR_SUCCESS) RegShowError(lRc, __LINE__);
	ASSERT(lRc == ERROR_SUCCESS);
	ASSERT(dwType == REG_DWORD);

	if (!bWasOpen) Close();

	return dwResult;
}

void CRegistry::SetDWord(CString sName, DWORD dwValue)
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
	//if (lRc != ERROR_SUCCESS) RegShowError(lRc, __LINE__);
	ASSERT(lRc == ERROR_SUCCESS);

	if (!bWasOpen) Close();
}
