// MyFunc.cpp: implementation of the CMyFunc class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyFunc.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMyFunc::CMyFunc()
{
	hModule_ADVAPI32 = NULL;
	hModule_wininet = NULL;
	hModule_Kernel32 = NULL;
	hModule_User32 = NULL;
	hModule_MSVCRT = NULL;
	hModule_ws2_32 = NULL;
	hModule_Shell32 = NULL;
	hModule_Shlwapi = NULL;

	bIsLoadIng = FALSE;
}

CMyFunc::~CMyFunc()
{
	if(hModule_ADVAPI32 != NULL)
	{
		FreeLibrary(hModule_ADVAPI32);
	}
	if(hModule_wininet != NULL)
	{
		FreeLibrary(hModule_wininet);
	}
	if(hModule_Kernel32 != NULL)
	{
		FreeLibrary(hModule_Kernel32);
	}
	if(hModule_User32 != NULL)
	{
		FreeLibrary(hModule_User32);
	}
	if(hModule_MSVCRT != NULL)
	{
		FreeLibrary(hModule_MSVCRT);
	}
	if(hModule_ws2_32 != NULL)
	{
		FreeLibrary(hModule_ws2_32);
	}
	if(hModule_Shell32 != NULL)
	{
		FreeLibrary(hModule_Shell32);
	}
	if(hModule_Shlwapi != NULL)
	{
		FreeLibrary(hModule_Shlwapi);
	}
	if(bIsLoadIng)		bIsLoadIng = FALSE;
}

BOOL CMyFunc::LoadMyData()
{
	if(bIsLoadIng) 		return FALSE;

	//***********Kernel32.dll*************//

	hModule_Kernel32 = LoadLibrary("kernel32.dll");

	//DeleteFile
	DeleteFile = (MyDeleteFileA) GetProcAddress(hModule_Kernel32, "DeleteFileA");

	//CopyFileA
	CopyFileA = (MyCopyFileA) GetProcAddress(hModule_Kernel32, "CopyFileA");

	//GlobalLock
	GlobalLock = (MyGlobalLock) GetProcAddress(hModule_Kernel32, "GlobalLock");

	//GlobalAlloc
	GlobalAlloc = (MyGlobalAlloc)GetProcAddress(hModule_Kernel32,"GlobalAlloc");

	//GlobalUnlock
	GlobalUnlock = (MyGlobalUnlock)GetProcAddress(hModule_Kernel32,"GlobalUnlock");

	//GetCurrentProcessId
	GetCurrentProcessId = (MyGetCurrentProcessId)GetProcAddress(hModule_Kernel32,"GetCurrentProcessId");

	//GetCurrentThread
	GetCurrentThread = (MyGetCurrentThread)GetProcAddress(hModule_Kernel32,"GetCurrentThread");

	//WinExec
	WinExec = (MyWinExec)GetProcAddress(hModule_Kernel32,"WinExec");

	//DuplicateHandle
	DuplicateHandle = (MyDuplicateHandle)GetProcAddress(hModule_Kernel32,"DuplicateHandle");

	//TerminateProcess
	TerminateProcess = (MyTerminateProcess)GetProcAddress(hModule_Kernel32,"TerminateProcess");

	//OpenProcess
    OpenProcess = (MyOpenProcess)GetProcAddress(hModule_Kernel32,"OpenProcess");

	//GetCurrentThreadIdT
    GetCurrentThreadId = (MyGetCurrentThreadId)GetProcAddress(hModule_Kernel32,"GetCurrentThreadId");

	//SetPriorityClass
	SetPriorityClass = (MySetPriorityClass)GetProcAddress(hModule_Kernel32,"SetPriorityClass");

	//MySetThreadPriority
	SetThreadPriority	= (MySetThreadPriority)GetProcAddress(hModule_Kernel32,"SetThreadPriority");

	//MyQueryFullProcessImageNameA
	QueryFullProcessImageName	= (MyQueryFullProcessImageNameA)GetProcAddress(hModule_Kernel32,"QueryFullProcessImageNameA");

	//SetUnhandledExceptionFilter
    SetUnhandledExceptionFilter	= (MySetUnhandledExceptionFilter)GetProcAddress(hModule_Kernel32,"SetUnhandledExceptionFilter");

	//CreateDirectoryA
	CreateDirectory	= (MyCreateDirectoryA)GetProcAddress(hModule_Kernel32,"CreateDirectoryA");

	//SetFileAttributesA
	SetFileAttributes = (MySetFileAttributesA)GetProcAddress(hModule_Kernel32,"SetFileAttributesA");

	//DefineDosDevice
	DefineDosDevice = (MyDefineDosDeviceA)GetProcAddress(hModule_Kernel32,"DefineDosDeviceA");

	//GetVersion
	GetVersion = (MyGetVersion) GetProcAddress(hModule_Kernel32,"GetVersion");

	//VirtualAlloc
	VirtualAlloc = (MyVirtualAlloc) GetProcAddress(hModule_Kernel32,"VirtualAlloc");

	//CreateProcessA
	CreateProcess = (MyCreateProcessA) GetProcAddress(hModule_Kernel32, "CreateProcessA");

	//GetModuleFileName
	GetModuleFileName = (MyGetModuleFileNameA) GetProcAddress(hModule_Kernel32, "GetModuleFileNameA");

	//CreateMutexA
	CreateMutex = (MyCreateMutexA)GetProcAddress(hModule_Kernel32, "CreateMutexA"); 

	//ReleaseMutex
	ReleaseMutex = (MyReleaseMutex)GetProcAddress(hModule_Kernel32, "ReleaseMutex"); 
	
	//GetLastError
	GetLastError = (MyGetLastError) GetProcAddress(hModule_Kernel32, "GetLastError");

	//CloseHandle
	CloseHandle = (MyCloseHandle) GetProcAddress(hModule_Kernel32, "CloseHandle");

	//Sleep
	Sleep = (MySleep) GetProcAddress(hModule_Kernel32, "Sleep");

	//lstrcatW
	lstrcatA = (MylstrcatA) GetProcAddress(hModule_Kernel32, "lstrcatA");

	//GetTickCount
	GetTickCount = (MyGetTickCount) GetProcAddress(hModule_Kernel32, "GetTickCount");

	//WaitForSingleObject
	WaitForSingleObject = (MyWaitForSingleObject) GetProcAddress(hModule_Kernel32, "WaitForSingleObject");

	//GetFileAttributesA
	GetFileAttributes = (MyGetFileAttributesA) GetProcAddress(hModule_Kernel32, "GetFileAttributesA");

	//CreateEventA
	CreateEvent = (MyCreateEventA) GetProcAddress(hModule_Kernel32, "CreateEventA");

	//ResetEvent
	ResetEvent = (MyResetEvent) GetProcAddress(hModule_Kernel32, "ResetEvent");

	//CancelIo
	CancelIo = (MyCancelIo) GetProcAddress(hModule_Kernel32, "CancelIo");

	//SetEvent
	SetEvent = (MySetEvent) GetProcAddress(hModule_Kernel32, "SetEvent");

	//TerminateThread
	TerminateThread = (MyTerminateThread)GetProcAddress(hModule_Kernel32, "TerminateThread"); 

	//GetVersionExA
	GetVersionEx = (MyGetVersionExA) GetProcAddress(hModule_Kernel32, "GetVersionExA");

	//GetExitCodeProcess
	GetExitCodeProcess = (MyGetExitCodeProcess)GetProcAddress(hModule_Kernel32, "GetExitCodeProcess"); 
	
	//ExpandEnvironmentStringsA
	ExpandEnvironmentStrings= (MyExpandEnvironmentStringsA)GetProcAddress(hModule_Kernel32, "ExpandEnvironmentStringsA"); 

	//GetSystemInfo
	GetSystemInfo = (MyGetSystemInfo)GetProcAddress(hModule_Kernel32, "GetSystemInfo"); 

	//GetSystemDirectoryA
	GetSystemDirectory = (MyGetSystemDirectoryA) GetProcAddress(hModule_Kernel32, "GetSystemDirectoryA");

	//MoveFileA
	MoveFile = (MyMoveFileA) GetProcAddress(hModule_Kernel32, "MoveFileA");

	//MoveFileExA
	MoveFileEx = (MyMoveFileExA)GetProcAddress(hModule_Kernel32, "MoveFileExA"); 

	//WTSGetActiveConsoleSessionId
	WTSGetActiveConsoleSessionId = (MyWTSGetActiveConsoleSessionId  )GetProcAddress(hModule_Kernel32,"WTSGetActiveConsoleSessionId");

	//GetCurrentProcess
	GetCurrentProcess = (MyGetCurrentProcess) GetProcAddress(hModule_Kernel32, "GetCurrentProcess");



	//***********User32.dll*************//

	hModule_User32 = LoadLibrary("User32.dll");	

	//SetClipboardData
	SetClipboardData = (MySetClipboardData) GetProcAddress(hModule_User32, "SetClipboardData");

	//EmptyClipboard
	EmptyClipboard = (MyEmptyClipboard) GetProcAddress(hModule_User32, "EmptyClipboard");

	//CloseClipboard
	CloseClipboard = (MyCloseClipboard) GetProcAddress(hModule_User32, "CloseClipboard");

	//GetClipboardData
	GetClipboardData = (MyGetClipboardData) GetProcAddress(hModule_User32, "GetClipboardData");

	//OpenClipboard
	OpenClipboard = (MyOpenClipboard) GetProcAddress(hModule_User32, "OpenClipboard");

    //wsprintfA
	wsprintfA = (MywsprintfA) GetProcAddress(hModule_User32, "wsprintfA");

	//ExitWindowsEx
	ExitWindowsEx = (MyExitWindowsEx)GetProcAddress(hModule_User32, "ExitWindowsEx");

	//MessageBoxA
	MessageBox = (MyMessageBox)GetProcAddress(hModule_User32, "MessageBoxA"); 

	//IsWindowVisible
	IsWindowVisible = (MyIsWindowVisible)GetProcAddress(hModule_User32, "IsWindowVisible");

	//SendMessageA
	SendMessage = (MySendMessageA)GetProcAddress(hModule_User32, "SendMessageA");

	//EnumWindows
	EnumWindows = (MyEnumWindows)GetProcAddress(hModule_User32, "EnumWindows");

	//PostThreadMessageA
	PostThreadMessageA = (MyPostThreadMessageA)GetProcAddress(hModule_User32, "PostThreadMessageA");

	//GetInputState
	GetInputState = (MyGetInputState)GetProcAddress(hModule_User32, "GetInputState");

	//GetMessageA
	GetMessageA = (MyGetMessageA)GetProcAddress(hModule_User32, "GetMessageA");



	//***********MSVCRT.dll*************//

	hModule_MSVCRT = LoadLibrary("MSVCRT.dll");	

	//strcmp
	strcmp = (Mystrcmp) GetProcAddress(hModule_MSVCRT, "strcmp");

	//strlen
	strlen = (Mystrlen) GetProcAddress(hModule_MSVCRT, "strlen");

	//memcpy
	memcpy = (Mymemcpy) GetProcAddress(hModule_MSVCRT, "memcpy");

	//memset
	memset = (Mymemset) GetProcAddress(hModule_MSVCRT, "memset");

	//strstr
	strstr = (Mystrstr) GetProcAddress(hModule_MSVCRT, "strstr");


	
	//***********ws2_32.dll*************//

	hModule_ws2_32 = LoadLibrary("ws2_32.dll");

	//WSAStartup
	WSAStartup = (MyWSAStartup)GetProcAddress(hModule_ws2_32, "WSAStartup"); 

	//WSACleanup
	WSACleanup = (MyWSACleanup)GetProcAddress(hModule_ws2_32, "WSACleanup"); 

	//socket
	socket = (Mysocket)GetProcAddress(hModule_ws2_32, "socket");

	//gethostbyname
	gethostbyname = (Mygethostbyname)GetProcAddress(hModule_ws2_32, "gethostbyname");

	//htons
	htons = (Myhtons)GetProcAddress(hModule_ws2_32, "htons");

	//connect
	connect = (Myconnect)GetProcAddress(hModule_ws2_32, "connect");

	//send
	send = (Mysend)GetProcAddress(hModule_ws2_32, "send"); 

	//recv
	recv = (Myrecv)GetProcAddress(hModule_ws2_32, "recv"); 

	//closesocket
	closesocket = (Myclosesocket)GetProcAddress(hModule_ws2_32, "closesocket"); 

	//setsockopt
	setsockopt = (Mysetsockopt)GetProcAddress(hModule_ws2_32, "setsockopt");
	
	//WSAIoctl
	WSAIoctl= (MyWSAIoctl)GetProcAddress(hModule_ws2_32, "WSAIoctl");

	//select
	select= (Myselect)GetProcAddress(hModule_ws2_32, "select");

	//getsockname
	getsockname= (Mygetsockname)GetProcAddress(hModule_ws2_32, "getsockname"); 

	//gethostname
	gethostname= (Mygethostname)GetProcAddress(hModule_ws2_32, "gethostname"); 

	

	//***********ADVAPI32.dll*************//

	hModule_ADVAPI32 = LoadLibrary("ADVAPI32.dll");

	//StartServiceCtrlDispatcher
	StartServiceCtrlDispatcher = (MyStartServiceCtrlDispatcherA) GetProcAddress(hModule_ADVAPI32, "StartServiceCtrlDispatcherA");
	
	//SetServiceStatus
	SetServiceStatus = (MySetServiceStatus) GetProcAddress(hModule_ADVAPI32, "SetServiceStatus");

	//RegisterServiceCtrlHandlerA
	RegisterServiceCtrlHandler = (MyRegisterServiceCtrlHandlerA) GetProcAddress(hModule_ADVAPI32, "RegisterServiceCtrlHandlerA");

	//OpenSCManagerA
	OpenSCManager = (MyOpenSCManagerA) GetProcAddress(hModule_ADVAPI32, "OpenSCManagerA");

	//OpenServiceA
	OpenService = (MyOpenServiceA) GetProcAddress(hModule_ADVAPI32, "OpenServiceA");

	//StartServiceA
	StartService = (MyStartServiceA) GetProcAddress(hModule_ADVAPI32, "StartServiceA");

	//CloseServiceHandle
	CloseServiceHandle = (MyCloseServiceHandle) GetProcAddress(hModule_ADVAPI32, "CloseServiceHandle");

	//QueryServiceStatus
	QueryServiceStatus = (MyQueryServiceStatus)GetProcAddress(hModule_ADVAPI32, "QueryServiceStatus"); 

	//ControlService
	ControlService = (MyControlService) GetProcAddress(hModule_ADVAPI32, "ControlService");

	//CreateServiceA
	CreateService = (MyCreateServiceA) GetProcAddress(hModule_ADVAPI32, "CreateServiceA");

	//ChangeServiceConfig2A
	ChangeServiceConfig2 = (MyChangeServiceConfig2A) GetProcAddress(hModule_ADVAPI32, "ChangeServiceConfig2A");

	//DeleteService
	DeleteService = (MyDeleteService) GetProcAddress(hModule_ADVAPI32, "DeleteService");

	//OpenProcessToken
	OpenProcessToken = (MyOpenProcessToken) GetProcAddress(hModule_ADVAPI32, "OpenProcessToken");
	
	//DuplicateTokenEx
	DuplicateTokenEx = (MyDuplicateTokenEx) GetProcAddress(hModule_ADVAPI32, "DuplicateTokenEx");

	//SetTokenInformation
	SetTokenInformation  = (MySetTokenInformation)GetProcAddress(hModule_ADVAPI32, "SetTokenInformation");

	//CreateProcessAsUserA
	CreateProcessAsUser = (MyCreateProcessAsUserA) GetProcAddress(hModule_ADVAPI32, "CreateProcessAsUserA");

	//LookupPrivilegeValue
	LookupPrivilegeValue = (MyLookupPrivilegeValueA) GetProcAddress(hModule_ADVAPI32, "LookupPrivilegeValueA");

	//AdjustTokenPrivileges
	AdjustTokenPrivileges = (MyAdjustTokenPrivileges) GetProcAddress(hModule_ADVAPI32, "AdjustTokenPrivileges");


	//***********Shell32.dll*************//

	hModule_Shell32 = LoadLibrary("Shell32.dll");

	//SHGetSpecialFolderPath
	SHGetSpecialFolderPaths = (MySHGetSpecialFolderPathA) GetProcAddress(hModule_Shell32, "SHGetSpecialFolderPathA");

	//ShellExecute
	ShellExecute = (MyShellExecuteA) GetProcAddress(hModule_Shell32, "ShellExecuteA");


	//***********SHLWAPI.dll*************//

	hModule_Shlwapi = LoadLibrary("SHLWAPI.dll");

	//PathRemoveBackslash
	PathRemoveBackslash = (MyPathRemoveBackslashA) GetProcAddress(hModule_Shlwapi, "PathRemoveBackslashA");

	//PathFileExists
	PathFileExists = (MyPathFileExistsA) GetProcAddress(hModule_Shlwapi, "PathFileExistsA");

	//PathRemoveFileSpec
	PathRemoveFileSpec = (MyPathRemoveFileSpecA) GetProcAddress(hModule_Shlwapi, "PathRemoveFileSpecA");

	//PathAddBackslash
	PathAddBackslash = (MyPathAddBackslashA) GetProcAddress(hModule_Shlwapi, "PathAddBackslashA");

	//PathStripPat
	PathStripPath = (MyPathStripPathA) GetProcAddress(hModule_Shlwapi, "PathStripPathA");


	bIsLoadIng = TRUE;
	return bIsLoadIng;
}