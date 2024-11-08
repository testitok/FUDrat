// Client.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Client.h"
#include "MainFrm.h"
#include "ClientDoc.h"
#include "ClientView.h"
#include "PcView.h"
#include "LOGIN.h"
LOGIN Login;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
HANDLE m_mutex;
HMODULE hModule_shell32;
/*
		void dbg_dump(struct _EXCEPTION_POINTERS* ExceptionInfo) 
		{
			char buff[1024];
			memset(buff, 0, sizeof(buff));
			wsprintf
				(buff, 
				"CRASH CODE:0x%.8x ADDR=0x%.8x FLAGS=0x%.8x PARAMS=0x%.8x\n"
				"eax=%.8x ebx=%.8x ecx=%.8x\nedx=%.8x esi=%.8x edi=%.8x\neip=%.8x esp=%.8x ebp=%.8x\n",
				ExceptionInfo->ExceptionRecord->ExceptionCode,
				ExceptionInfo->ExceptionRecord->ExceptionAddress,
				ExceptionInfo->ExceptionRecord->ExceptionFlags,
				ExceptionInfo->ExceptionRecord->NumberParameters,
				ExceptionInfo->ContextRecord->Eax,
				ExceptionInfo->ContextRecord->Ebx,
				ExceptionInfo->ContextRecord->Ecx,
				ExceptionInfo->ContextRecord->Edx,
				ExceptionInfo->ContextRecord->Esi,
				ExceptionInfo->ContextRecord->Edi,
				ExceptionInfo->ContextRecord->Eip,
				ExceptionInfo->ContextRecord->Esp,
				ExceptionInfo->ContextRecord->Ebp
				);
*/

void dbg_dump(struct _EXCEPTION_POINTERS* ExceptionInfo) {
	char buff[1024];
	memset(buff, 0, sizeof(buff));
	wsprintf
		(buff, 
		"CRASH CODE:0x%.8x ADDR=0x%.8x FLAGS=0x%.8x PARAMS=0x%.8x\n"
		"eax=%.8x ebx=%.8x ecx=%.8x\nedx=%.8x esi=%.8x edi=%.8x\neip=%.8x esp=%.8x ebp=%.8x\n",
		ExceptionInfo->ExceptionRecord->ExceptionCode,
		ExceptionInfo->ExceptionRecord->ExceptionAddress,
		ExceptionInfo->ExceptionRecord->ExceptionFlags,
		ExceptionInfo->ExceptionRecord->NumberParameters,
		ExceptionInfo->ContextRecord->Eax,
		ExceptionInfo->ContextRecord->Ebx,
		ExceptionInfo->ContextRecord->Ecx,
		ExceptionInfo->ContextRecord->Edx,
		ExceptionInfo->ContextRecord->Esi,
		ExceptionInfo->ContextRecord->Edi,
		ExceptionInfo->ContextRecord->Eip,
		ExceptionInfo->ContextRecord->Esp,
		ExceptionInfo->ContextRecord->Ebp
		);
		
	
	MessageBox(NULL, buff, "Client RAT Exception", MB_OK);
}

LONG WINAPI bad_exception(struct _EXCEPTION_POINTERS* ExceptionInfo) 
{
	dbg_dump(ExceptionInfo);
	return true;
}
/////////////////////////////////////////////////////////////////////////////
// CClientApp

BEGIN_MESSAGE_MAP(CClientApp, CWinApp)
	//{{AFX_MSG_MAP(CClientApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientApp construction
DWORD CClientApp::GetRand()
{
	typedef DWORD (WINAPI *tGetRandNum)();
	tGetRandNum pGetRandNum = (tGetRandNum)GetProcAddress(m_Hmodule,"GetRandNum");
	
	if(pGetRandNum)
		return pGetRandNum();
}

CClientApp::CClientApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	// 加载系统图标,后面在Filemanager要用到
	
	typedef BOOL (WINAPI * pfn_FileIconInit) (BOOL fFullInit);
	hModule_shell32 = LoadLibrary("shell32.dll");
	if(hModule_shell32)
	{
		pfn_FileIconInit FileIconInit = (pfn_FileIconInit) GetProcAddress(hModule_shell32, (LPCSTR)660);
		FileIconInit(TRUE);
	}
	else
	{
		AfxMessageBox("LoadLibray shell32 error!");
	}
	// 读取qqwry.dat（位置文件）
	char szQQwryPath[MAX_PATH]={0};
	GetModuleFileName(NULL,AppPath,MAX_PATH);
	*strrchr(AppPath,'\\') = 0;
	sprintf(szQQwryPath,"%s\\Plugins\\QQwry.dat",AppPath);

	HANDLE	hFile = CreateFile(szQQwryPath, 0, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		m_bIsQQwryExist = true;
	}
	else
	{
		m_bIsQQwryExist = false;
	}
	CloseHandle(hFile);
	// 是否要禁用气泡提示 false（不禁用气泡）
	
	m_bIsDisablePopTips = (m_IniFile.GetInt("Settings", "PopTips", false) && true);
	//
	m_bIsWarning_Tone   = (m_IniFile.GetInt("Settings", "Alarm", false) && true);

}

/////////////////////////////////////////////////////////////////////////////
// The one and only CClientApp object

CClientApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CClientApp initialization


BOOL CClientApp::InitInstance()
{
// 	CString strSysTime, strDeadline, strSWCreateTime;
//     CTime sysTime; // 系统时间
//     sysTime = CTime::GetCurrentTime();
//     strSysTime = sysTime.Format(_T("%Y%m%d%H")); // 格式化为 年月日小时（24小时格式）
//     strSWCreateTime.Format(_T("2021081612")); // 包含小时信息的生成日期，格式化为 年月日小时
//     strDeadline.Format(_T("2024092224")); // 包含小时信息的截止日期，格式化为 年月日小时
//     // 判断系统时间是否更改
//     if (strSysTime < strSWCreateTime)
//     {
//         AfxMessageBox(_T("系统时间有误，无法打开软件！"));
//         return FALSE;
//     }
//     // 判断是否到截止日期
//     if (strSysTime > strDeadline)
//     {
//         AfxMessageBox(_T("过期!联系作者:coco54188"));
//         return FALSE;
//     }
// 

	/*创建一个互斥体*/
// 	m_mutex = CreateMutex(NULL, FALSE, "Snips <8.0> 远程管理系统"); 
// 	if(ERROR_ALREADY_EXISTS == GetLastError()) 
// 	{
// 		AfxMessageBox("请勿重复运行,请检查右下角!"); 
// 		return FALSE; 
// 	}

	//崩溃处理
	SetUnhandledExceptionFilter(bad_exception);
	AfxEnableControlContainer();
	if(m_IniFile.GetInt("Settings", "SKIN"))
				{
		char Path[200]={0};
		GetModuleFileName(NULL,Path,200);
		*strrchr(Path,'\\')=0;
		strcat(Path,"\\Plugins\\SkinH.she");
		SkinH_AttachEx(Path,NULL);
	}

	//皮肤
	if (((CClientApp *)AfxGetApp())->m_IniFile.GetString("Settings", "SKIN", "")=="")
	{
		char Path[200]={0};
		GetModuleFileName(NULL,Path,200);
		*strrchr(Path,'\\')=0;
		strcat(Path,"\\Plugins\\SkinH.she");
		SkinH_AttachEx(Path,NULL);
	}
	else if (((CClientApp *)AfxGetApp())->m_IniFile.GetInt("Settings", "SKIN", TRUE))
	{
		char Path[200]={0};
		GetModuleFileName(NULL,Path,200);
		*strrchr(Path,'\\')=0;
		strcat(Path,"\\Plugins\\SkinH.she");
		SkinH_AttachEx(Path,NULL);
	}
 		
// 	Login.DoModal();   //登录
// 	if (Login.dLogin <= 10000 )
 //	{
 //		return FALSE;
 //	}

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CClientDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CClientView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	// 启动IOCP服务器
	int	nPort = m_IniFile.GetInt("Settings", "ListenPort");
	if (nPort == 0)	nPort = 8081;
	
	int	nMaxConnection = m_IniFile.GetInt("Settings", "MaxConnection");
	if (nMaxConnection == 0) nMaxConnection = 8000;
	
	((CMainFrame*) m_pMainWnd)->Activate(nPort, nMaxConnection);


	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CClientApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CClientApp message handlers

