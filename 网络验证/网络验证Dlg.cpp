// ������֤Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "������֤.h"
#include "������֤Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyDlg dialog
#include "WINSOCK.H"
#define Request_DOWN			0x9
#define File_Buffer				0x10
#define File_Buffer_Finish		0x11
typedef struct
{
	BYTE	Flags;
	DWORD	Buffer_Size;
	BYTE	Buffer[1024];
	BYTE	Info[256];
}NET_DATA, *LPNET_DATA;

char *DAT_NAME = "\\Install.dat";
char *INI_NAME = "������֤.ini";
char DAT_PATH[MAX_PATH] = {0}, INI_PATH[MAX_PATH] = {0};

SOCKET m_hSocket;
HANDLE hLinstenThread = NULL;
CMyDlg::CMyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyDlg)
	m_port = 0;
	m_username = _T("123");
	m_password = _T("123");
	m_dns = _T("127.0.0.1");
	m_date = _T("20210101");
	m_build = _T("1000");
	//���������ļ�����
	CTime time = CTime::GetCurrentTime();		//����CTime���� 
	strTime = time.Format("%Y-%m-%d %H:%M:%S");
	m_gengx = _T(strTime);
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_port = 8689;
	GetCurrentDirectory( sizeof(DAT_PATH), DAT_PATH );
	lstrcpy( INI_PATH, DAT_PATH );
	lstrcat( DAT_PATH, "\\" );
	lstrcat( INI_PATH, "\\" );
	lstrcat( DAT_PATH, DAT_NAME );
	lstrcat( INI_PATH, INI_NAME );
}

void CMyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyDlg)
	DDX_Text(pDX, IDC_EDIT1, m_port);
	DDV_MinMaxInt(pDX, m_port, 1, 65535);
	DDX_Text(pDX, IDC_USERNEMA, m_username);
	DDX_Text(pDX, IDC_PASSWORD, m_password);
	DDX_Text(pDX, IDC_DNS, m_dns);
	DDX_Text(pDX, IDC_DATA, m_date);
	DDX_Text(pDX, IDC_BUILD, m_build);
	DDX_Text(pDX, IDC_GENGX, m_gengx);
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMyDlg, CDialog)
	//{{AFX_MSG_MAP(CMyDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START, OnStart)
	ON_BN_CLICKED(IDC_EXIT, OnExit)
	ON_BN_CLICKED(IDC_CHECK, OnCheck)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDlg message handlers

BOOL CMyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	OnCheck();


	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMyDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CMyDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
void My_GetTime(char Rstr[])
{
	time_t curtime=time(0);
	tm tim = *localtime(&curtime);
	int day,mon,year,hour,minute,seconds;
	day = tim.tm_mday;
	mon = tim.tm_mon;
	year = tim.tm_year;
	hour = tim.tm_hour;
	minute = tim.tm_min;
	seconds = tim.tm_sec;
	year += 1900;
	mon += 1;
	sprintf(Rstr, "%04d%02d%02d", year, mon, day );
}

void SendFile( SOCKET sock, char *username, char *ConnPass )//SOCKET,�û���,�����������Ϣ
{
	char Buffer[128] = {0};
	//��֤ʹ�ô���
	char read_build[256];
	char new_build[256];
	memset( read_build, 0, sizeof(read_build) );
	GetPrivateProfileString( username, "build", NULL, read_build, sizeof(read_build), INI_PATH );
	if ( atoi(read_build) <= 0 )
	{
		return;
	}

	//�õ���������˿���Ϣ
	char read_dns[256] = {0};
	memset( read_dns, 0, sizeof(read_dns) );
	GetPrivateProfileString( username, "DNS", NULL, read_dns, sizeof(read_dns), INI_PATH );
	if ( lstrlen(read_dns) == 0 )
	{
		return;//��ȡ����ֱ�ӷ���
	}
	char finally_info[256];
	lstrcpy( finally_info, read_dns );
	NET_DATA MyData;
	while(1)
	{	
		memset( &MyData, 0, sizeof(NET_DATA) );
		if (MyData.Buffer_Size == 0 )//��ȡ���ˣ��ļ�������ɣ���������������Ϣ
		{
			memset(new_build, 0, sizeof(new_build) );
			wsprintf( new_build, "%d", atoi(read_build) - 1 );
			WritePrivateProfileString( username, "build", new_build, INI_PATH ); // ʹ�ô�����1

			memset(&MyData, 0, sizeof(NET_DATA) );
			MyData.Flags = File_Buffer_Finish;
			lstrcpy((char*)&MyData.Info, finally_info );
			MyData.Buffer_Size = lstrlen(finally_info) + 1; // ����������Ϣ �˿ں�����
			if (send( sock, (char*)&MyData, sizeof(MyData), NULL ) == SOCKET_ERROR ) break;
			recv( sock, Buffer, sizeof(Buffer), NULL );
			break;
		}
		if (send( sock, (char*)&MyData, sizeof(MyData), NULL ) == SOCKET_ERROR ) break; // ���������ȡ������
		recv( sock, Buffer, sizeof(Buffer), NULL );
	}
	return;
}
char vipname[30];
BOOL CheckUser( char *buff, char *username )
{
	//Login:�û���@����
	char read_pass[256];
	char read_date[256];
	char bendi_date[256];
	if (strncmp(buff,"Login:",6) == 0 )//���ǰ�漸����֤�ַ����
	{	
		char *pos1 = strchr( buff, ':' );
		pos1++;
		char *pos2 = strchr( pos1, '@' );
		*pos2 = '\0';
		pos2++;
		lstrcpy(vipname,pos1);
		memset( read_pass, 0, sizeof(read_pass) );
		GetPrivateProfileString( pos1, "userpass", NULL, read_pass, sizeof(read_pass), INI_PATH );
		if ( lstrcmpi( pos2, read_pass ) == 0 )//��ȫ��ȣ����Դ�Сд
		{	
			memset( read_date, 0, sizeof(read_date) );
			GetPrivateProfileString( pos1, "date", NULL, read_date, sizeof(read_date), INI_PATH );
			My_GetTime(bendi_date);
			if ( atoi(bendi_date) > atoi(read_date) ) return FALSE;
			lstrcpy( username, pos1 );
			return TRUE;
		}
		else
		{	
			return FALSE;
		}
	}
	else//����֤�ַ�������ȣ�ֱ��PASS
	{	
		return FALSE;
	}
}


//���̴߳����¼�
DWORD WINAPI AnswerThread(LPVOID lparam)
{
	SOCKET ClientSocket = (SOCKET)lparam;
	char Buffer[1024] = {0};
	char UserName[30] = {0};
	int Ret = 0;
	BOOL isLogined = FALSE;
	char *strYes = "Pass";
	char *strNO = " ";
	char read_build[30];
	char radiostr[256];
	char sendstr[256];
	char read_date[30];
	char bandiniP[30];
	while(1)
	{
		memset( Buffer, 0, sizeof(Buffer) );
		Ret = recv( ClientSocket, Buffer, sizeof(Buffer), NULL );
		if ( Ret == 0 || Ret == SOCKET_ERROR )
		{
			break;
		}

		if ( !isLogined )//û�е�¼
		{
			if ( CheckUser( Buffer, UserName ) )
			{
				GetPrivateProfileString( vipname, "date", NULL, read_date, sizeof(read_date), INI_PATH );
				GetPrivateProfileString( vipname, "build", NULL, read_build, sizeof(read_build), INI_PATH );
				GetPrivateProfileString(vipname, "radio", NULL,radiostr, sizeof(radiostr), INI_PATH );
				GetPrivateProfileString(vipname, "dns", NULL,bandiniP, sizeof(bandiniP), INI_PATH );
				
				wsprintf(sendstr,
					"%s\r\n��Ա�˺�:%s\r\n\r\n����ʱ��:%s\r\n\r\nʣ�����:%s\r\n\r\n��������:%s\r\n\r\n������:%s",
					strYes,vipname,read_date,read_build,radiostr,bandiniP);
				isLogined = TRUE;
				send(ClientSocket, sendstr, lstrlen(sendstr) + 1, NULL );//�����ַ������߿ͻ����Ѿ�ͨ����֤
				continue;
			}
			else//û�е�¼������¼�ģ�ֱ�ӶϿ�
			{
				break;
			}
		}
		else//�Ѿ���¼
		{
			if ( Buffer[0] == Request_DOWN )//����ǻ�ȡ�����ļ�
			{
				SendFile( ClientSocket, UserName, Buffer );//�����ļ���Ȼ��Ͽ�
				break;
			}
			else//����������Ϣ��ֱ�ӶϿ����ӣ���ʡ��������Դ
			{
				break;
			}
		}
	}
	closesocket(ClientSocket);
	return 0;
}

DWORD WINAPI ListenThread(LPVOID lparam)
{
	SOCKET AcceptSocket;
	DWORD dwThreadId;
	while (1)
	{
		AcceptSocket = SOCKET_ERROR;
		while(AcceptSocket == SOCKET_ERROR)
		{
			AcceptSocket = accept( m_hSocket, NULL, NULL );
		}
		CreateThread( NULL, NULL, AnswerThread, (LPVOID)AcceptSocket,0,&dwThreadId);
	}
	WSACleanup();
	return 0;
}

void CMyDlg::OnStart() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if ( m_port <= 0 || m_port >65535 )
	{
		return;
	}
	
	WSADATA wsaData;
	SOCKADDR_IN m_addr;
	int iRet = 0;
	DWORD ThreadId;
	
	if ( m_hSocket != NULL )
	{
		closesocket(m_hSocket);
	}
	
	WSACleanup();
	iRet = WSAStartup(MAKEWORD(2,2),&wsaData);
	if( iRet != NO_ERROR ) AfxMessageBox("Error at WSAStartup()");
	
	memset( &m_addr, 0, sizeof(SOCKADDR) );
	m_addr.sin_family = AF_INET;
	m_addr.sin_addr.S_un.S_addr = INADDR_ANY;
	m_addr.sin_port = htons(m_port);
	
	m_hSocket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if ( bind(m_hSocket,(LPSOCKADDR)&m_addr,sizeof(m_addr)) == SOCKET_ERROR )
	{
		AfxMessageBox("����ʧ��,�˿ڿ��ܱ�ռ��!");
		WSACleanup();
		return;
	}
	if ( listen( m_hSocket, 10000 ) ==  SOCKET_ERROR )
	{
		AfxMessageBox("Listenʧ��!");
		WSACleanup();
		return;
	}
	hLinstenThread = CreateThread( NULL, NULL, ListenThread, NULL, 0, &ThreadId);
	((CEdit*)GetDlgItem(IDC_EDIT1))->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_START))->EnableWindow(FALSE);	//���ð�ť
	return;
}

void CMyDlg::OnExit()
{
	// TODO: Add your control notification handler code here
	if ( hLinstenThread != NULL )
	{
		CloseHandle(hLinstenThread);
	}
	if ( m_hSocket != NULL )
	{
		closesocket(m_hSocket);
	}
	WSACleanup();
	ExitProcess(0);
}

void CMyDlg::OnCheck() 
{
	// TODO: Add your control notification handler code here
	static BOOL bShow = TRUE;
	RECT rct;
	GetWindowRect(&rct);
	bShow = !bShow;
	
	if	(bShow)
		rct.bottom = rct.bottom + 185;
	else
		rct.bottom = rct.bottom - 185;
	
	MoveWindow(&rct, TRUE);
	
	rct.top = rct.bottom - 20;
	//	m_wndStatusBar.MoveWindow(&rct, TRUE);
	
	InvalidateRect(NULL);
	UpdateWindow();
}

void CMyDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_inifile.SetString(m_username,"userpass",m_password);
	m_inifile.SetString(m_username,"dns",m_dns);
	m_inifile.SetString(m_username,"build",m_build);
	m_inifile.SetString(m_username,"date",m_date);
	m_inifile.SetString(m_username,"radio",m_gengx);
}

void CMyDlg::OnButton2() 
{
	UpdateData(TRUE);
	TCHAR strAppNameTemp[1024];//����AppName�ķ���ֵ
    //����AppName���ܳ���
    DWORD dwAppNameSize = GetPrivateProfileString(NULL,NULL,NULL,strAppNameTemp,1024,INI_PATH);
    if(dwAppNameSize>0)
    {
        TCHAR *pAppName = new TCHAR[dwAppNameSize];
        int nAppNameLen=0;  //ÿ��AppName�ĳ���
		
		for(unsigned int i = 0;i<dwAppNameSize;i++)
        {
            pAppName[nAppNameLen++]=strAppNameTemp[i];
            if(strAppNameTemp[i]=='\0')
            {
                OutputDebugString(pAppName);
				WritePrivateProfileString(pAppName,"radio",m_gengx,INI_PATH);
                memset(pAppName,0,dwAppNameSize);
                nAppNameLen=0;
            }
        }
        delete[]pAppName;
    }
}