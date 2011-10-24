// PedidosRegistry.h: interface for the CPedidosRegistry class.
//
//////////////////////////////////////////////////////////////////////
// $Archive: /PalmTrader 1/Config/PedidosRegistry.h $
// $Author: Flávio $
// $Date: 30/09/98 15:40 $
/* $History: PedidosRegistry.h $
 * 
 * *****************  Version 2  *****************
 * User: Flávio       Date: 30/09/98   Time: 15:40
 * Updated in $/PalmTrader 1/Config
 * Incluídos comentários de controle de versão
 */

#if !defined(AFX_PEDIDOSREGISTRY_H__848B53A1_6802_11D1_9F76_204C4F4F5020__INCLUDED_)
#define AFX_PEDIDOSREGISTRY_H__848B53A1_6802_11D1_9F76_204C4F4F5020__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class AFX_CLASS_EXPORT CPedidosRegistry  
{
public:
	CPedidosRegistry(BOOL bKeepOpen=TRUE);
	virtual ~CPedidosRegistry();

	void Open();
	void Close();

	CString GetString(CString sName, CString sDefault = _T(""), int nMaxSize=128);
	void SetString(CString sName, CString sValue);

	DWORD GetDWord(CString sName, DWORD dwDefault = 0);
	void SetDWord(CString sName, DWORD dwValue);

protected:
	HKEY hKey;
	BOOL bIsOpen;
};

#endif // !defined(AFX_PEDIDOSREGISTRY_H__848B53A1_6802_11D1_9F76_204C4F4F5020__INCLUDED_)
