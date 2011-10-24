// Registry.h: interface for the CRegistry class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REGISTRY_H__70E8FE63_A6C8_11D1_A012_00004403E294__INCLUDED_)
#define AFX_REGISTRY_H__70E8FE63_A6C8_11D1_A012_00004403E294__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CRegistry  
{
public:
	void SetDWord(CString sName, DWORD dwValue);
	DWORD GetDWord(CString sName, DWORD dwDefault = 0);
	void SetString(CString sName, CString sValue);
	CString GetString(CString sName, CString sDefault = _T(""), int nMaxSize = 128);
	void Close(void);
	void Open(void);
	CRegistry(BOOL bKeepOpen = TRUE);
	virtual ~CRegistry();

protected:
	HKEY hKey;
	BOOL bIsOpen;
};

#endif // !defined(AFX_REGISTRY_H__70E8FE63_A6C8_11D1_A012_00004403E294__INCLUDED_)
