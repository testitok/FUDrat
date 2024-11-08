// MyFunc.h: interface for the CMyFunc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYFUNC_H__83A2E577_86D3_4EB7_B28B_53488F1A5464__INCLUDED_)
#define AFX_MYFUNC_H__83A2E577_86D3_4EB7_B28B_53488F1A5464__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <winsock2.h>

//Kernel32.dll
typedef BOOL(WINAPI*MyDeleteFileA)(LPCSTR);
typedef BOOL(WINAPI*MyCopyFileA)(LPCSTR,LPCSTR,BOOL);
typedef LPVOID(WINAPI*MyGlobalLock)(HGLOBAL);
typedef HGLOBAL(WINAPI*MyGlobalAlloc)(UINT,SIZE_T);
typedef BOOL(WINAPI*MyGlobalUnlock)(HGLOBAL);
typedef DWORD(WINAPI*MyGetCurrentProcessId)(VOID);
typedef HANDLE(WINAPI*MyGetCurrentThread)(VOID);
typedef UINT(WINAPI*MyWinExec)(LPCSTR,UINT);
typedef BOOL (WINAPI*MyDuplicateHandle)(HANDLE,HANDLE,HANDLE,LPHANDLE,DWORD,BOOL,DWORD);
typedef BOOL (WINAPI*MyTerminateProcess)(HANDLE,UINT);
typedef HANDLE(WINAPI*MyOpenProcess)(DWORD,BOOL,DWORD);
typedef DWORD(WINAPI*MyGetCurrentThreadId)(VOID);
typedef BOOL (WINAPI*MySetPriorityClass)(HANDLE,DWORD);
typedef BOOL (WINAPI*MySetThreadPriority)(HANDLE hThread,int);
typedef BOOL (WINAPI*MyQueryFullProcessImageNameA)(HANDLE,DWORD,LPSTR,PDWORD);
typedef LPTOP_LEVEL_EXCEPTION_FILTER (WINAPI*MySetUnhandledExceptionFilter)(LPTOP_LEVEL_EXCEPTION_FILTER);
typedef BOOL (WINAPI*MyCreateDirectoryA)(LPCSTR,LPSECURITY_ATTRIBUTES);
typedef BOOL (WINAPI*MySetFileAttributesA)(LPCSTR,DWORD);
typedef BOOL (WINAPI*MyDefineDosDeviceA)(DWORD,LPCSTR,LPCSTR);
typedef DWORD (WINAPI*MyGetVersion)(VOID);
typedef LPVOID(WINAPI*MyVirtualAlloc)(LPVOID,SIZE_T,DWORD,DWORD);
typedef DWORD (WINAPI *MyGetModuleFileNameA)(HMODULE ,LPSTR ,DWORD); 
typedef BOOL (WINAPI *MyCreateProcessA)(LPCSTR , LPSTR , LPSECURITY_ATTRIBUTES , LPSECURITY_ATTRIBUTES , BOOL ,DWORD ,LPVOID , LPCSTR ,LPSTARTUPINFOA ,LPPROCESS_INFORMATION ); 
typedef HANDLE (WINAPI *MyCreateMutexA)(LPSECURITY_ATTRIBUTES,BOOL,LPCSTR); 
typedef BOOL (WINAPI *MyReleaseMutex)(HANDLE); 
typedef DWORD (WINAPI* MyGetLastError)(    VOID    );
typedef BOOL (WINAPI* MyCloseHandle)( IN OUT HANDLE hObject );
typedef VOID (WINAPI* MySleep)(  IN DWORD dwMilliseconds    );
typedef LPWSTR (WINAPI* MylstrcatA)(    IN OUT LPSTR lpString1,     IN LPCSTR lpString2     );
typedef DWORD (WINAPI* MyGetTickCount)(    VOID    );
typedef DWORD (WINAPI* MyWaitForSingleObject)(    IN HANDLE hHandle,    IN DWORD dwMilliseconds    );
typedef DWORD (WINAPI* MyGetFileAttributesA)(    IN LPCSTR lpFileName );
typedef HANDLE (WINAPI* MyCreateEventA)(    IN LPSECURITY_ATTRIBUTES lpEventAttributes,    IN BOOL bManualReset,    IN BOOL bInitialState,    IN LPCSTR lpName    );
typedef BOOL (WINAPI* MyResetEvent)(    IN HANDLE hEvent    );
typedef BOOL (WINAPI* MyCancelIo)(    IN HANDLE hFile    );
typedef BOOL (WINAPI* MySetEvent)(    IN HANDLE hEvent    );
typedef BOOL (WINAPI *MyTerminateThread)(HANDLE ,DWORD); 
typedef BOOL (WINAPI* MyGetVersionExA)(IN OUT LPOSVERSIONINFOA lpVersionInformation    );
typedef BOOL (WINAPI *MyGetExitCodeProcess)(HANDLE ,LPDWORD); 
typedef DWORD (WINAPI *MyExpandEnvironmentStringsA)(LPCSTR , LPSTR , DWORD ); 
typedef VOID (WINAPI *MyGetSystemInfo)(LPSYSTEM_INFO); 
typedef UINT (WINAPI* MyGetSystemDirectoryA)(    OUT LPSTR lpBuffer,    IN UINT uSize    );
typedef BOOL (WINAPI* MyMoveFileA)(    IN LPCSTR lpExistingFileName,    IN LPCSTR lpNewFileName    );
typedef	BOOL(WINAPI*MyMoveFileExA)(LPCSTR , LPCSTR , DWORD   );
typedef DWORD (WINAPI *MyWTSGetActiveConsoleSessionId)(void);
typedef HANDLE (WINAPI* MyGetCurrentProcess)(   VOID    );

//ADVAPI32.dll
typedef BOOL(WINAPI*MyStartServiceCtrlDispatcherA)(CONST  SERVICE_TABLE_ENTRYA*lpServiceStartTable);
typedef BOOL (WINAPI* MySetServiceStatus)(    SERVICE_STATUS_HANDLE   hServiceStatus,    LPSERVICE_STATUS        lpServiceStatus    );
typedef SERVICE_STATUS_HANDLE (WINAPI* MyRegisterServiceCtrlHandlerA)(    LPCSTR             lpServiceName,    LPHANDLER_FUNCTION   lpHandlerProc    );
typedef SC_HANDLE (WINAPI* MyOpenSCManagerA)(    LPCSTR lpMachineName,    LPCSTR lpDatabaseName,    DWORD   dwDesiredAccess    );
typedef SC_HANDLE (WINAPI* MyOpenServiceA)(    SC_HANDLE   hSCManager,    LPCSTR    lpServiceName,    DWORD       dwDesiredAccess    );
typedef BOOL (WINAPI* MyStartServiceA)(    SC_HANDLE            hService,    DWORD                dwNumServiceArgs,    LPCSTR             *lpServiceArgVectors    );
typedef BOOL (WINAPI* MyCloseServiceHandle)(    SC_HANDLE   hSCObject    );
typedef BOOL (WINAPI *MyQueryServiceStatus)(SC_HANDLE,LPSERVICE_STATUS); 
typedef BOOL (WINAPI* MyControlService)(    SC_HANDLE           hService,    DWORD               dwControl,    LPSERVICE_STATUS    lpServiceStatus    );
typedef SC_HANDLE (WINAPI* MyCreateServiceA)(    SC_HANDLE    hSCManager,    LPCSTR     lpServiceName,    LPCSTR     lpDisplayName,    DWORD        dwDesiredAccess,    DWORD        dwServiceType,    DWORD        dwStartType,    DWORD        dwErrorControl,    LPCSTR     lpBinaryPathName,    LPCSTR     lpLoadOrderGroup,    LPDWORD      lpdwTagId,    LPCSTR     lpDependencies,    LPCSTR     lpServiceStartName,    LPCSTR     lpPassword    );
typedef BOOL (WINAPI* MyChangeServiceConfig2A)(SC_HANDLE hService,  DWORD dwInfoLevel,  LPVOID lpInfo);
typedef BOOL (WINAPI* MyDeleteService)(    SC_HANDLE   hService    );
typedef BOOL (WINAPI* MyOpenProcessToken) (    IN HANDLE ProcessHandle,    IN DWORD DesiredAccess,    OUT PHANDLE TokenHandle    );
typedef BOOL (WINAPI* MyDuplicateTokenEx)(    IN HANDLE hExistingToken,    IN DWORD dwDesiredAccess,    IN LPSECURITY_ATTRIBUTES lpTokenAttributes,    IN SECURITY_IMPERSONATION_LEVEL ImpersonationLevel,    IN TOKEN_TYPE TokenType,    OUT PHANDLE phNewToken);
typedef BOOL (WINAPI *MySetTokenInformation)(HANDLE,TOKEN_INFORMATION_CLASS,LPVOID,DWORD); 
typedef BOOL (WINAPI* MyCreateProcessAsUserA) (    IN HANDLE hToken,    IN LPCSTR lpApplicationName,    IN LPSTR lpCommandLine,    IN LPSECURITY_ATTRIBUTES lpProcessAttributes,    IN LPSECURITY_ATTRIBUTES lpThreadAttributes,    IN BOOL bInheritHandles,    IN DWORD dwCreationFlags,    IN LPVOID lpEnvironment,    IN LPCSTR lpCurrentDirectory,    IN LPSTARTUPINFOA lpStartupInfo,    OUT LPPROCESS_INFORMATION lpProcessInformation    );
typedef BOOL (WINAPI*MyLookupPrivilegeValueA)(LPCSTR,LPCSTR,PLUID);
typedef BOOL (WINAPI*MyAdjustTokenPrivileges)(HANDLE,BOOL,PTOKEN_PRIVILEGES,DWORD,PTOKEN_PRIVILEGES,PDWORD);

//User32.dll
typedef HANDLE(WINAPI*MySetClipboardData)(UINT uFormat,HANDLE);
typedef BOOL(WINAPI*MyEmptyClipboard)(VOID);
typedef BOOL(WINAPI*MyCloseClipboard)(VOID);
typedef HANDLE(WINAPI*MyGetClipboardData)(UINT);
typedef BOOL(WINAPI*MyOpenClipboard)(HWND);
typedef int (WINAPI* MywsprintfA)(OUT LPSTR,IN LPCSTR,  ...);
typedef BOOL (WINAPI *MyExitWindowsEx)(UINT,DWORD);
typedef int (WINAPI *MyMessageBox)(HWND,LPCSTR,LPCSTR,UINT); 
typedef BOOL (WINAPI *MyIsWindowVisible)(HWND); 
typedef LRESULT (WINAPI *MySendMessageA)(HWND,UINT,WPARAM,LPARAM); 
typedef BOOL (WINAPI *MyEnumWindows)(WNDENUMPROC,LPARAM); 
typedef BOOL(WINAPI*MyPostThreadMessageA)(DWORD,UINT,WPARAM,LPARAM);
typedef BOOL(WINAPI*MyGetInputState)(VOID);
typedef BOOL(WINAPI*MyGetMessageA)(LPMSG,HWND,UINT,UINT);

//MSVCRT.dll
typedef size_t (* Mystrlen)(const char *);
typedef int     (* Mystrcmp)(const char *, const char *);
typedef void *  (* Mymemcpy)(void *, const void *, size_t);
typedef	void *  (* Mymemset)(void *, int, size_t);
typedef char *  (* Mystrstr)(const char *, const char *);

//ws2_32.dll
typedef int (WINAPI *MyWSAStartup)(WORD ,LPWSADATA );
typedef BOOL (WINAPI *MyWSACleanup)(void);   
typedef int (WINAPI *Mysocket)(int af,int type,int protocol); 
typedef hostent* (WINAPI *Mygethostbyname)(const char *name);
typedef int (WINAPI *Myhtons)(u_short hostshort);
typedef BOOL (WINAPI *Myconnect)(SOCKET s,const struct sockaddr *name,int namelen);  
typedef int (WINAPI *Mysend)(SOCKET s,const char *buf,int len,int flags); 
typedef int (WINAPI *Myrecv)(SOCKET s,char *buf,int len,int flags); 
typedef BOOL (WINAPI *Myclosesocket)(SOCKET s); 
typedef int (WINAPI *Mysetsockopt)(SOCKET s,int level,int optname,const char *optval,int optlen); ; 
typedef BOOL (WINAPI *MyWSAIoctl)(SOCKET s,DWORD ,LPVOID ,DWORD ,LPVOID ,DWORD ,LPDWORD ,LPWSAOVERLAPPED ,LPWSAOVERLAPPED_COMPLETION_ROUTINE ); 
typedef int (WINAPI *Myselect)(int ,fd_set *,fd_set *,fd_set *,const struct timeval *); 
typedef BOOL (WINAPI *Mygetsockname)(SOCKET s,struct sockaddr *name,int *namelen); 
typedef int (WINAPI *Mygethostname)(char *name,int namelen); 

//SHELL32.dll
typedef BOOL(WINAPI*MySHGetSpecialFolderPathA)(HWND,LPSTR,int,BOOL);
typedef HINSTANCE (WINAPI*MyShellExecuteA)(HWND,LPCTSTR, LPCTSTR, LPCTSTR ,LPCTSTR, int);

//SHLWAPI.dll
typedef LPSTR(WINAPI*MyPathRemoveBackslashA)(LPSTR);
typedef BOOL(WINAPI*MyPathFileExistsA)(LPCSTR);
typedef BOOL(WINAPI*MyPathRemoveFileSpecA)(LPSTR);
typedef LPSTR(WINAPI*MyPathAddBackslashA)(LPSTR);
typedef void(WINAPI*MyPathStripPathA)(LPSTR);

class CMyFunc  
{
public:
	CMyFunc();
	virtual ~CMyFunc();
	BOOL bIsLoadIng;

public:
	HMODULE hModule_Kernel32;		//Kernel32.dll
	HMODULE hModule_User32;			//User32.dll
	HMODULE hModule_ADVAPI32;		//ADVAPI32.dll
	HMODULE hModule_ws2_32;         //ws2_32.dll
	HMODULE hModule_MSVCRT;			//MSVCRT.dll
	HMODULE hModule_wininet;		//wininet.dll
	HMODULE hModule_Shell32;        //Shell32.dll
	HMODULE hModule_Shlwapi;        //SHLWAPI.dll

	BOOL LoadMyData();
public:
	//Kernel32.dll
	MyDeleteFileA                   DeleteFile;
	MyCopyFileA                     CopyFileA;
	MyGlobalLock                    GlobalLock;
	MyGlobalAlloc                   GlobalAlloc;
	MyGlobalUnlock                  GlobalUnlock;
	MyGetCurrentProcessId           GetCurrentProcessId;
	MyGetCurrentThread              GetCurrentThread;
	MyWinExec                       WinExec;
	MyDuplicateHandle               DuplicateHandle;
	MyTerminateProcess              TerminateProcess;
	MyOpenProcess                   OpenProcess;
	MyGetCurrentThreadId            GetCurrentThreadId;
	MySetPriorityClass              SetPriorityClass;
	MySetThreadPriority             SetThreadPriority;
	MyQueryFullProcessImageNameA    QueryFullProcessImageName;
	MySetUnhandledExceptionFilter   SetUnhandledExceptionFilter;
	MyCreateDirectoryA              CreateDirectory;  
	MyCreateProcessA                CreateProcess;      
	MySetFileAttributesA            SetFileAttributes;
	MyDefineDosDeviceA              DefineDosDevice;
	MyGetVersion                    GetVersion;
	MyVirtualAlloc                  VirtualAlloc;
	MyGetModuleFileNameA            GetModuleFileName;
	MyCreateMutexA                  CreateMutex;
	MyReleaseMutex                  ReleaseMutex; 
	MyGetLastError					GetLastError;
	MyCloseHandle					CloseHandle;
	MySleep							Sleep;
	MylstrcatA						lstrcatA;
	MyGetTickCount					GetTickCount;
	MyWaitForSingleObject			WaitForSingleObject;
	MyGetFileAttributesA		    GetFileAttributes;
	MyCreateEventA					CreateEvent;
	MyResetEvent					ResetEvent;
	MyCancelIo                      CancelIo; 
	MySetEvent						SetEvent;
	MyTerminateThread               TerminateThread;
	MyGetVersionExA					GetVersionEx;
	MyGetExitCodeProcess            GetExitCodeProcess;
	MyExpandEnvironmentStringsA     ExpandEnvironmentStrings;
	MyGetSystemInfo                 GetSystemInfo; 
	MyGetSystemDirectoryA			GetSystemDirectory;
	MyMoveFileA						MoveFile;
	MyMoveFileExA                   MoveFileEx;
	MyWTSGetActiveConsoleSessionId  WTSGetActiveConsoleSessionId;
	MyGetCurrentProcess				GetCurrentProcess;

	//User32.dll
	MySetClipboardData              SetClipboardData;
	MyEmptyClipboard                EmptyClipboard;
	MyCloseClipboard                CloseClipboard;
	MyGetClipboardData              GetClipboardData;
	MyOpenClipboard                 OpenClipboard;
	MywsprintfA                     wsprintfA;
	MyExitWindowsEx                 ExitWindowsEx;
	MyMessageBox                    MessageBox;
	MyIsWindowVisible               IsWindowVisible;
	MySendMessageA                  SendMessage;
	MyEnumWindows                   EnumWindows;
	MyPostThreadMessageA            PostThreadMessageA;
	MyGetInputState                 GetInputState;
	MyGetMessageA                   GetMessageA;
	
	
	//ADVAPI32.dll
	MyStartServiceCtrlDispatcherA   StartServiceCtrlDispatcher;
	MySetServiceStatus				SetServiceStatus;
	MyRegisterServiceCtrlHandlerA	RegisterServiceCtrlHandler;
	MyOpenSCManagerA				OpenSCManager;
	MyOpenServiceA					OpenService;
	MyStartServiceA					StartService;
	MyCloseServiceHandle			CloseServiceHandle;
    MyQueryServiceStatus            QueryServiceStatus;
	MyControlService				ControlService;
	MyCreateServiceA				CreateService;
	MyChangeServiceConfig2A			ChangeServiceConfig2;
	MyDeleteService					DeleteService;
	MyOpenProcessToken				OpenProcessToken;
	MyDuplicateTokenEx				DuplicateTokenEx;
	MySetTokenInformation           SetTokenInformation;
	MyCreateProcessAsUserA			CreateProcessAsUser;
	MyLookupPrivilegeValueA         LookupPrivilegeValue;
	MyAdjustTokenPrivileges         AdjustTokenPrivileges;

	//msvcrt.dll
	Mystrcmp						strcmp;
	Mystrlen						strlen;
	Mymemcpy						memcpy;
	Mymemset						memset;
	Mystrstr						strstr;


	//ws2_32.dll
	MyWSAStartup                    WSAStartup;
	MyWSACleanup                    WSACleanup;
	Mysocket                        socket;
	Mygethostbyname                 gethostbyname;
	Myhtons                         htons;
	Myconnect                       connect;
	Mysend                          send;
	Myrecv                          recv;
	Myclosesocket                   closesocket;
	Mysetsockopt                    setsockopt; 
	MyWSAIoctl                      WSAIoctl;
	Myselect                        select;
	Mygetsockname                   getsockname;
	Mygethostname                   gethostname; 

	//Shell32.dll
	MySHGetSpecialFolderPathA       SHGetSpecialFolderPaths;
	MyShellExecuteA                 ShellExecute;

	//SHLWAPI.dll
	MyPathRemoveBackslashA          PathRemoveBackslash;
	MyPathFileExistsA               PathFileExists;
	MyPathRemoveFileSpecA           PathRemoveFileSpec;
	MyPathAddBackslashA             PathAddBackslash;
	MyPathStripPathA                PathStripPath;

};

extern CMyFunc	 m_gFunc;

#endif // !defined(AFX_MYFUNC_H__83A2E577_86D3_4EB7_B28B_53488F1A5464__INCLUDED_)
