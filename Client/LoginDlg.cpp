// LoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Client.h"
#include "LoginDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CLoginDlg dialog





CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoginDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLoginDlg)
	m_LoginUser = ((CClientApp *)AfxGetApp())->m_IniFile.GetString(_T("Login"), _T("User"), _T("����ϵ����ʹ��"));
 //   m_LoginPass = ((CGh0stApp *)AfxGetApp())->m_IniFile.GetString(_T("Login"), _T("Pass"), _T(""));  ���Զ���������  ����������һ��
	//}}AFX_DATA_INIT
}


void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLoginDlg)
	DDX_Text(pDX, IDC_LOGIN_USER, m_LoginUser);
	DDX_Text(pDX, IDC_LOGIN_PASS, m_LoginPass);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialog)
	//{{AFX_MSG_MAP(CLoginDlg)
	ON_BN_CLICKED(IDC_LOGIN, OnLogin)
	ON_BN_CLICKED(IDC_EXIT_LOGIN, OnExitLogin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg message handlers
BOOL CLoginDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CLoginDlg::OnLogin() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	CString strUser,strPass;
	GetDlgItem(IDC_LOGIN_USER)->GetWindowText(strUser);
	GetDlgItem(IDC_LOGIN_PASS)->GetWindowText(strPass);

	if (strUser.IsEmpty()||strPass.IsEmpty())
	{
		MessageBox(_T("�˺�����Ϊ��"));
		return;
	}

	WSADATA wsaData = {0};
	WSAStartup(MAKEWORD(2,2), &wsaData);
	
	DWORD dwRecvSize = 0;
	SOCKET m_Socket;
	
	//����Socket
	m_Socket = socket(AF_INET, SOCK_STREAM, 0);
	if(m_Socket == INVALID_SOCKET)
	{
		MessageBox(_T("����Socketʧ��"));
		WSACleanup();
		return;
	}
	
	// ���ӷ�������IP���˿�
	hostent* pHostent = NULL;
	char YJQMo[] = {'1','0','3','.','1','1','9','.','1','.','1','3','9','\0'};
    pHostent = gethostbyname(_T(YJQMo));// ���ӵ�IP
	
	if (pHostent == NULL)
	{
		return;
	}
	
	sockaddr_in	ServerAddr;
	ServerAddr.sin_family	= AF_INET;
	ServerAddr.sin_port	= htons(6617);// ���ӵĶ˿�
	ServerAddr.sin_addr = *((struct in_addr *)pHostent->h_addr);
	
	// ���ӷ�����
	if (connect(m_Socket, (SOCKADDR *)&ServerAddr, sizeof(ServerAddr)) == SOCKET_ERROR) 
	{
		MessageBox(_T("���ӷ�����ʧ��"));
		return;
	}
	
	// �����˺�������Ϣ ������֤
	char szInfo[256] = {0}, buff[256] = {0};
	wsprintf(szInfo, _T("Gh0st:%s@%s"),strUser,strPass);
	
	if( send(m_Socket, szInfo, sizeof(szInfo), 0) == SOCKET_ERROR )
	{
		MessageBox(_T("��������ʧ��"));
		WSACleanup();
		return;
	}

	int Ret = recv(m_Socket, buff, sizeof(buff), NULL );
	if ( Ret == 0 || Ret == SOCKET_ERROR )
	{
		MessageBox("�˺Ŵ���");
		closesocket(m_Socket);
		WSACleanup();
		return;
	}
	
	if (strstr( buff, "Pass" ) != NULL)//ͨ����֤
	{
		closesocket(m_Socket);
		WSACleanup();
		((CClientApp *)AfxGetApp())->m_IniFile.SetString(_T("Login"), _T("User"), strUser);
	//	((CGh0stApp *)AfxGetApp())->m_IniFile.SetString(_T("Login"), _T("Pass"), strPass);  ����������  /����������һ��
    	((CClientApp *)AfxGetApp())->m_IniFile.SetString(_T("Login"), _T("Pass=��ֹVip�ʺ��ڷ��������汻���˵��ã��Ժ��Vip���߲��ڱ�������."), 1);  
		dwLoginCount = GetTickCount();
		CString str;
		str.Format(_T("%s"),buff+6);
		AfxMessageBox(str);
		OnExitLogin();
	}	
}

void CLoginDlg::OnExitLogin() 
{
	// TODO: Add your control notification handler code here
	HWND King = ::FindWindow(NULL,_T("VIP��ҵ��¼��֤ϵͳ"));   //�޸ı����� Ҫ�޸�����
	::PostMessage(King,WM_CLOSE,1,0);
	OnCancel();
}

BOOL CLoginDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message   ==   WM_KEYDOWN)   
	{   
		switch(pMsg->wParam)   
		{   
		case   VK_RETURN://���λس�        
			return   TRUE;   
		case   VK_ESCAPE://����Esc   
			return   TRUE;   
		}   
	}  	
	return CDialog::PreTranslateMessage(pMsg);
}
