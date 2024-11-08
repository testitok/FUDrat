// GUOFUDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Client.h"
#include "GUOFUDlg.h"
#include "PcView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGUOFUDlg dialog

CGUOFUDlg::CGUOFUDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGUOFUDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGUOFUDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
//	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


/////////////////////////////////////////////////////////////////////////////
// CGUOFUDlg message handlers

typedef struct 
{
	BYTE bToken;
	UINT nType;
	char lpCmdLine[MAX_PATH];
	char lpFileName[256];
}LOCALUP;

