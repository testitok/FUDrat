// ������Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "������.h"
#include "������Dlg.h"
#include <afxinet.h>
#include <WinSock.h>
#pragma comment(lib, "ws2_32.lib")

#include "decode.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CMyDlg::CMyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyDlg)
	DDX_Control(pDX, IDC_PROGRESS1, m_Prog);
	DDX_Control(pDX, IDC_EDIT_LOG, m_edit_log);
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMyDlg, CDialog)
	//{{AFX_MSG_MAP(CMyDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR() //��ɫ����
	ON_BN_CLICKED(IDB_BTN_START1,OnBtnStart1)//��ʼ����1
	ON_BN_CLICKED(IDB_BTN_START2,OnBtnStart2)//��ʼ����2
	ON_BN_CLICKED(IDB_BTN_START3,OnBtnStart3)//��ʼ����3
	ON_BN_CLICKED(IDB_BTN_START4,OnBtnStart4)//��ʼ����4
	ON_BN_CLICKED(IDB_BTN_STOP,OnBtnStop)   //�˳�
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDlg message handlers

///��ɫ��ʾ
void CMyDlg::LogOut(LPCSTR outtext)
{
	int length = m_edit_log.GetWindowTextLength(); 
	m_edit_log.SetSel(length, length);
	m_edit_log.SetLimitText(MAXDWORD); // ������󳤶�
	m_edit_log.ReplaceSel (outtext); 
}
HBRUSH CMyDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	if ((pWnd->GetDlgCtrlID() == IDC_EDIT_LOG) && (nCtlColor == CTLCOLOR_EDIT))
	{
		COLORREF clr = RGB(0, 255, 0);
		pDC->SetTextColor(clr);
		clr = RGB(0,0,0);
		pDC->SetBkColor(clr);
		return CreateSolidBrush(clr);
	}
	else
	{
		return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	}
}
////
int nTerminate  = 0;
int nDownloaded = 0;
//��ȡ����IP
CString GotHost(CString YM)
{
	WSAData wsa;
	WSAStartup(MAKEWORD(2,2),&wsa);
	hostent *phst=gethostbyname(YM);
	in_addr * iddr=(in_addr*)phst->h_addr;
	unsigned long IPUL=iddr->s_addr;
	char *IP=inet_ntoa(*iddr);
	return IP;
}
UINT DownloadFile1(LPVOID pParam)
{
	CWnd*			pwnd = AfxGetMainWnd();
	CProgressCtrl*	m_Prog = (CProgressCtrl*)pwnd->GetDlgItem(IDC_PROGRESS1);
	CButton*		bStart1 = (CButton*)pwnd->GetDlgItem(IDB_BTN_START1);
	CButton*		bStart2 = (CButton*)pwnd->GetDlgItem(IDB_BTN_START2);
	CButton*		bStart3 = (CButton*)pwnd->GetDlgItem(IDB_BTN_START3);
	CButton*		bStart4 = (CButton*)pwnd->GetDlgItem(IDB_BTN_START4);
	
	char				filebuf[512];
	CInternetSession	netSession;
	CStdioFile			*fTargFile;
	int					outfs;
	CString				szFile,DKOU,FileSize,KBin,KBsec,NewName,Perc,Install,SSVP,SSVO,HTTP;
	
	try
	{ 	
		pwnd->GetDlgItemText(IDC_EDIT3,szFile);
		pwnd->GetDlgItemText(IDC_EDIT5,DKOU);
		pwnd->SetDlgItemText(IDC_EDIT_LOG,"�������ӷ�����...\r\n");

		////////////////////////////////////////////////
		CString IP=GotHost(szFile);

		char WEjnt[] = {'a','H','R','0','c','D','o','v','L','w','=','=','\0'}; 
		HTTP = Base64Decode(WEjnt);//http://
		char hGgCA[] = {'L','2','R','h','d','C','9','J','b','n','N','0','Y','W','x','s','M','S','5','k','Y','X','Q','=','\0'};
 		Install = Base64Decode(hGgCA);
		CString url0 = CString(HTTP)+IP+":"+DKOU+Install;  //Install.dat
//		MessageBoxA(0,url0,0,0);
		/////////////////////////////////////////////////////////////////////////////////////////////
		fTargFile = netSession.OpenURL(url0,1,INTERNET_FLAG_TRANSFER_BINARY | INTERNET_FLAG_RELOAD);
		
		nDownloaded = 1;

		COleDateTime dlStart = COleDateTime::GetCurrentTime();
		int filesize = fTargFile->SeekToEnd();
		fTargFile->SeekToBegin();
		outfs = filesize / 1024;		// �����ļ���С��ǧ�ֽڣ�
		FileSize.Format(_T("%d"),outfs);	// ��KBΪ��λ��ʽ�ļ���С

#if 0

		CString filepath,filename;
		filepath = _T("Cache"); //�Լ����Կ��ǽ��ļ����ص�ʲôλ�ã������趨ΪF�̸�Ŀ¼���� 
		filename = filepath + fTargFile->GetFileName();  //�ļ�·�� 
		CFile fDestFile(filename, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);
#endif
		// �ڵ�ǰĿ¼�����µ�Ŀ���ļ�
	//	CFile fDestFile(fTargFile->GetFileName(), CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);
		CString filepath,filename;
		filepath = _T("Cache\\"); //�Լ����Կ��ǽ��ļ����ص�ʲôλ�ã������趨ΪF�̸�Ŀ¼���� 
		filename = filepath + fTargFile->GetFileName();  //�ļ�·�� 
		CFile fDestFile(filename, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);
		int byteswrite;		// д���ļ����ֽ���
		int pos = 0;		// ��ǰ��������λ��
		int nperc,kbrecv;	// �������İٷֱ�,��ȡ�������ݴ�С��KbsΪ��λ��
		double secs,kbsec;	// ��¼����, �ٶȣ�KB/�룩
		
		// ����ļ���̫�������̴��ڵı��Ⲣ��״̬��ʾ
		NewName = fTargFile->GetFileName();					// ��ȡ���ļ���
		
		if(fTargFile->GetFileName().GetLength() >= 10)
		{
			NewName = fTargFile->GetFileName().Mid(0,7);	// �ָ��ļ�
			NewName = NewName + "...";
		}
		
		pwnd->SetDlgItemText(IDC_EDIT_LOG,"���ڸ���...");
		m_Prog->SetRange32(0,filesize);
		
		while (byteswrite = fTargFile->Read(filebuf, 512))	// ��ȡ�ļ�
		{
			if(nTerminate == 1)						// ������ȡ������
			{
				fDestFile.Close();					// �ر����ǵ�Ŀ���ļ�
				fTargFile->Close();					// �ر�Զ���ļ�
				delete fTargFile;					// ɾ��CStdioFile�����Է�ֹй©
				pwnd->SetDlgItemText(IDC_EDIT_LOG,"����ʱ�ѱ��û�ȡ����"); // Set satus bar text
				AfxEndThread(0);					// ���������߳�
			}

			// ���ݿ�ʼʱ���뵱ǰʱ��Ƚϣ���ȡ����
			COleDateTimeSpan dlElapsed = COleDateTime::GetCurrentTime() - dlStart;
			secs = dlElapsed.GetTotalSeconds();
			pos = pos + byteswrite;					// �����µĽ�����λ��
			fDestFile.Write(filebuf, byteswrite);	// ��ʵ������д���ļ�
			m_Prog->SetPos(pos);
			
			nperc = pos * 100 / filesize;			// ���Ȱٷֱ�
			kbrecv = pos / 1024;					// ��ȡ�յ�������
			kbsec = kbrecv / secs;					// ��ȡÿ�����ض��٣�KB��

			Perc.Format(_T("%d"), nperc);				// ��ʽ�����Ȱٷֱ�
			KBin.Format(_T("%d"), kbrecv);				// ��ʽ�����������ݴ�С��KB��
			KBsec.Format(_T("%d"), (int)kbsec);			// ��ʽ�������ٶȣ�KB/�룩

			pwnd->SetDlgItemText(IDC_EDIT_FILESIZE,FileSize + "KB");// Զ���ļ���С
			pwnd->SetDlgItemText(IDC_EDIT_SIZEOK,KBin + "KB");		// �����ش�С
			pwnd->SetDlgItemText(IDC_EDIT2,KBsec + "KB/��");		// �����ٶ�
			pwnd->SetDlgItemText(IDC_EDIT4,Perc + "%");	
	//		pwnd->SetDlgItemText(IDC_EDIT_LOG,"----------------------------"+Perc + "%------------------------------");				// ���Ȱٷֱ�
		}
		// ������ɣ��ر��ļ�
	 
		fDestFile.Close();
	}

	catch(CInternetException *IE)
	{
		CString strerror;
		TCHAR error[255];

		IE->GetErrorMessage(error,255); // ��ȡ������Ϣ
		strerror = error;

		pwnd->SetDlgItemText(IDC_EDIT_LOG,strerror);
		pwnd->SetDlgItemText(IDB_BTN_STOP, _T("Exit"));
		nDownloaded = 0;
		delete fTargFile;
		IE->Delete();					// ɾ���쳣�����Է�ֹй©
	}
	// �ָ�Ĭ��
	pwnd->SetDlgItemText(IDC_EDIT2, _T("Kb/��"));
//	pwnd->SetDlgItemText(IDC_EDIT3, _T("Loading..."));
	pwnd->SetDlgItemText(IDC_EDIT4, _T("0%"));
	
	delete fTargFile;
	if(nDownloaded == 1)
	{
		pwnd->SetDlgItemText(IDC_EDIT_LOG, "������ɣ�");
		bStart1->EnableWindow(TRUE); 
		bStart2->EnableWindow(TRUE);
		bStart3->EnableWindow(TRUE);
		bStart4->EnableWindow(TRUE);
		rename("Cache\\Install1.dat","Cache\\Install.dat"); 
	}
	return 0;
}
UINT DownloadFile2(LPVOID pParam)
{
	CWnd*			pwnd = AfxGetMainWnd();
	CProgressCtrl*	m_Prog = (CProgressCtrl*)pwnd->GetDlgItem(IDC_PROGRESS1);
	CButton*		bStart1 = (CButton*)pwnd->GetDlgItem(IDB_BTN_START1);
	CButton*		bStart2 = (CButton*)pwnd->GetDlgItem(IDB_BTN_START2);
	CButton*		bStart3 = (CButton*)pwnd->GetDlgItem(IDB_BTN_START3);
	CButton*		bStart4 = (CButton*)pwnd->GetDlgItem(IDB_BTN_START4);
	
	char				filebuf[512];
	CInternetSession	netSession;
	CStdioFile			*fTargFile;
	int					outfs;
	CString				szFile,DKOU,FileSize,KBin,KBsec,NewName,Perc,Install,SSVP,SSVO,HTTP;
	
	try
	{ 	
		pwnd->GetDlgItemText(IDC_EDIT3,szFile);
		pwnd->GetDlgItemText(IDC_EDIT5,DKOU);
		pwnd->SetDlgItemText(IDC_EDIT_LOG,"�������ӷ�����...\r\n");

		////////////////////////////////////////////////
		CString IP=GotHost(szFile);
		char WEjnt[] = {'a','H','R','0','c','D','o','v','L','w','=','=','\0'}; 
		HTTP = Base64Decode(WEjnt);//http://
		char hGgCA[] = {'L','2','R','h','d','C','9','J','b','n','N','0','Y','W','x','s','M','i','5','k','Y','X','Q','=','\0'};
		Install = Base64Decode(hGgCA);
		CString url0 = CString(HTTP)+IP+":"+DKOU+Install;  //Install.dat
		//		MessageBoxA(0,url0,0,0);
		/////////////////////////////////////////////////////////////////////////////////////////////
		fTargFile = netSession.OpenURL(url0,1,INTERNET_FLAG_TRANSFER_BINARY | INTERNET_FLAG_RELOAD);
		
		nDownloaded = 1;

		COleDateTime dlStart = COleDateTime::GetCurrentTime();
		int filesize = fTargFile->SeekToEnd();
		fTargFile->SeekToBegin();
		outfs = filesize / 1024;		// �����ļ���С��ǧ�ֽڣ�
		FileSize.Format(_T("%d"),outfs);	// ��KBΪ��λ��ʽ�ļ���С

#if 0

		CString filepath,filename;
		filepath = _T("Cache"); //�Լ����Կ��ǽ��ļ����ص�ʲôλ�ã������趨ΪF�̸�Ŀ¼���� 
		filename = filepath + fTargFile->GetFileName();  //�ļ�·�� 
		CFile fDestFile(filename, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);
#endif
		// �ڵ�ǰĿ¼�����µ�Ŀ���ļ�
	//	CFile fDestFile(fTargFile->GetFileName(), CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);
		CString filepath,filename;
		filepath = _T("Cache\\"); //�Լ����Կ��ǽ��ļ����ص�ʲôλ�ã������趨ΪF�̸�Ŀ¼���� 
		filename = filepath + fTargFile->GetFileName();  //�ļ�·�� 
		CFile fDestFile(filename, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);
		int byteswrite;		// д���ļ����ֽ���
		int pos = 0;		// ��ǰ��������λ��
		int nperc,kbrecv;	// �������İٷֱ�,��ȡ�������ݴ�С��KbsΪ��λ��
		double secs,kbsec;	// ��¼����, �ٶȣ�KB/�룩
		
		// ����ļ���̫�������̴��ڵı��Ⲣ��״̬��ʾ
		NewName = fTargFile->GetFileName();					// ��ȡ���ļ���
		
		if(fTargFile->GetFileName().GetLength() >= 10)
		{
			NewName = fTargFile->GetFileName().Mid(0,7);	// �ָ��ļ�
			NewName = NewName + "...";
		}
		
		pwnd->SetDlgItemText(IDC_EDIT_LOG,"���ڸ���...");
		m_Prog->SetRange32(0,filesize);
		
		while (byteswrite = fTargFile->Read(filebuf, 512))	// ��ȡ�ļ�
		{
			if(nTerminate == 1)						// ������ȡ������
			{
				fDestFile.Close();					// �ر����ǵ�Ŀ���ļ�
				fTargFile->Close();					// �ر�Զ���ļ�
				delete fTargFile;					// ɾ��CStdioFile�����Է�ֹй©
				pwnd->SetDlgItemText(IDC_EDIT_LOG,"����ʱ�ѱ��û�ȡ����"); // Set satus bar text
				AfxEndThread(0);					// ���������߳�
			}

			// ���ݿ�ʼʱ���뵱ǰʱ��Ƚϣ���ȡ����
			COleDateTimeSpan dlElapsed = COleDateTime::GetCurrentTime() - dlStart;
			secs = dlElapsed.GetTotalSeconds();
			pos = pos + byteswrite;					// �����µĽ�����λ��
			fDestFile.Write(filebuf, byteswrite);	// ��ʵ������д���ļ�
			m_Prog->SetPos(pos);
			
			nperc = pos * 100 / filesize;			// ���Ȱٷֱ�
			kbrecv = pos / 1024;					// ��ȡ�յ�������
			kbsec = kbrecv / secs;					// ��ȡÿ�����ض��٣�KB��

			Perc.Format(_T("%d"), nperc);				// ��ʽ�����Ȱٷֱ�
			KBin.Format(_T("%d"), kbrecv);				// ��ʽ�����������ݴ�С��KB��
			KBsec.Format(_T("%d"), (int)kbsec);			// ��ʽ�������ٶȣ�KB/�룩

			pwnd->SetDlgItemText(IDC_EDIT_FILESIZE,FileSize + "KB");// Զ���ļ���С
			pwnd->SetDlgItemText(IDC_EDIT_SIZEOK,KBin + "KB");		// �����ش�С
			pwnd->SetDlgItemText(IDC_EDIT2,KBsec + "KB/��");		// �����ٶ�
			pwnd->SetDlgItemText(IDC_EDIT4,Perc + "%");	
	//		pwnd->SetDlgItemText(IDC_EDIT_LOG,"----------------------------"+Perc + "%------------------------------");				// ���Ȱٷֱ�
		}
		// ������ɣ��ر��ļ�
	 
		fDestFile.Close();
	}

	catch(CInternetException *IE)
	{
		CString strerror;
		TCHAR error[255];

		IE->GetErrorMessage(error,255); // ��ȡ������Ϣ
		strerror = error;

		pwnd->SetDlgItemText(IDC_EDIT_LOG,strerror);
		pwnd->SetDlgItemText(IDB_BTN_STOP, _T("Exit"));
		nDownloaded = 0;
		delete fTargFile;
		IE->Delete();					// ɾ���쳣�����Է�ֹй©
	}
	// �ָ�Ĭ��
	pwnd->SetDlgItemText(IDC_EDIT2, _T("Kb/��"));
//	pwnd->SetDlgItemText(IDC_EDIT3, _T("Loading..."));
	pwnd->SetDlgItemText(IDC_EDIT4, _T("0%"));
	
	delete fTargFile;
	if(nDownloaded == 1)
	{
		pwnd->SetDlgItemText(IDC_EDIT_LOG, "������ɣ�");
		bStart1->EnableWindow(TRUE); 
		bStart2->EnableWindow(TRUE);
		bStart3->EnableWindow(TRUE);
		bStart4->EnableWindow(TRUE);
		rename("Cache\\Install2.dat","Cache\\Install.dat"); 
	}
	return 0;
}
UINT DownloadFile3(LPVOID pParam)
{
	CWnd*			pwnd = AfxGetMainWnd();
	CProgressCtrl*	m_Prog = (CProgressCtrl*)pwnd->GetDlgItem(IDC_PROGRESS1);
	CButton*		bStart1 = (CButton*)pwnd->GetDlgItem(IDB_BTN_START1);
	CButton*		bStart2 = (CButton*)pwnd->GetDlgItem(IDB_BTN_START2);
	CButton*		bStart3 = (CButton*)pwnd->GetDlgItem(IDB_BTN_START3);
	CButton*		bStart4 = (CButton*)pwnd->GetDlgItem(IDB_BTN_START4);
	
	char				filebuf[512];
	CInternetSession	netSession;
	CStdioFile			*fTargFile;
	int					outfs;
	CString				szFile,DKOU,FileSize,KBin,KBsec,NewName,Perc,Install,SSVP,SSVO,HTTP;
	
	try
	{ 	
		pwnd->GetDlgItemText(IDC_EDIT3,szFile);
		pwnd->GetDlgItemText(IDC_EDIT5,DKOU);
		pwnd->SetDlgItemText(IDC_EDIT_LOG,"�������ӷ�����...\r\n");

		////////////////////////////////////////////////
		CString IP=GotHost(szFile);
		char WEjnt[] = {'a','H','R','0','c','D','o','v','L','w','=','=','\0'}; 
		HTTP = Base64Decode(WEjnt);//http://
		char hGgCA[] = {'L','2','R','h','d','C','9','J','b','n','N','0','Y','W','x','s','M','y','5','k','Y','X','Q','=','\0'};
		Install = Base64Decode(hGgCA);
		CString url0 = CString(HTTP)+IP+":"+DKOU+Install;  //Install.dat
		//		MessageBoxA(0,url0,0,0);
		/////////////////////////////////////////////////////////////////////////////////////////////
		fTargFile = netSession.OpenURL(url0,1,INTERNET_FLAG_TRANSFER_BINARY | INTERNET_FLAG_RELOAD);
		
		nDownloaded = 1;

		COleDateTime dlStart = COleDateTime::GetCurrentTime();
		int filesize = fTargFile->SeekToEnd();
		fTargFile->SeekToBegin();
		outfs = filesize / 1024;		// �����ļ���С��ǧ�ֽڣ�
		FileSize.Format(_T("%d"),outfs);	// ��KBΪ��λ��ʽ�ļ���С

#if 0
		CString filepath,filename;
		filepath = _T("Cache"); //�Լ����Կ��ǽ��ļ����ص�ʲôλ�ã������趨ΪF�̸�Ŀ¼���� 
		filename = filepath + fTargFile->GetFileName();  //�ļ�·�� 
		CFile fDestFile(filename, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);
#endif
		// �ڵ�ǰĿ¼�����µ�Ŀ���ļ�
	//	CFile fDestFile(fTargFile->GetFileName(), CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);
		CString filepath,filename;
		filepath = _T("Cache\\"); //�Լ����Կ��ǽ��ļ����ص�ʲôλ�ã������趨ΪF�̸�Ŀ¼���� 
		filename = filepath + fTargFile->GetFileName();  //�ļ�·�� 
		CFile fDestFile(filename, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);
		int byteswrite;		// д���ļ����ֽ���
		int pos = 0;		// ��ǰ��������λ��
		int nperc,kbrecv;	// �������İٷֱ�,��ȡ�������ݴ�С��KbsΪ��λ��
		double secs,kbsec;	// ��¼����, �ٶȣ�KB/�룩
		
		// ����ļ���̫�������̴��ڵı��Ⲣ��״̬��ʾ
		NewName = fTargFile->GetFileName();					// ��ȡ���ļ���
		if(fTargFile->GetFileName().GetLength() >= 10)
		{
			NewName = fTargFile->GetFileName().Mid(0,7);	// �ָ��ļ�
			NewName = NewName + "...";
		}
		pwnd->SetDlgItemText(IDC_EDIT_LOG,"���ڸ���...");
		m_Prog->SetRange32(0,filesize);
		while (byteswrite = fTargFile->Read(filebuf, 512))	// ��ȡ�ļ�
		{
			if(nTerminate == 1)						// ������ȡ������
			{
				fDestFile.Close();					// �ر����ǵ�Ŀ���ļ�
				fTargFile->Close();					// �ر�Զ���ļ�
				delete fTargFile;					// ɾ��CStdioFile�����Է�ֹй©
				pwnd->SetDlgItemText(IDC_EDIT_LOG,"����ʱ�ѱ��û�ȡ����"); // Set satus bar text
				AfxEndThread(0);					// ���������߳�
			}
			// ���ݿ�ʼʱ���뵱ǰʱ��Ƚϣ���ȡ����
			COleDateTimeSpan dlElapsed = COleDateTime::GetCurrentTime() - dlStart;
			secs = dlElapsed.GetTotalSeconds();
			pos = pos + byteswrite;					// �����µĽ�����λ��
			fDestFile.Write(filebuf, byteswrite);	// ��ʵ������д���ļ�
			m_Prog->SetPos(pos);
			
			nperc = pos * 100 / filesize;			// ���Ȱٷֱ�
			kbrecv = pos / 1024;					// ��ȡ�յ�������
			kbsec = kbrecv / secs;					// ��ȡÿ�����ض��٣�KB��

			Perc.Format(_T("%d"), nperc);				// ��ʽ�����Ȱٷֱ�
			KBin.Format(_T("%d"), kbrecv);				// ��ʽ�����������ݴ�С��KB��
			KBsec.Format(_T("%d"), (int)kbsec);			// ��ʽ�������ٶȣ�KB/�룩

			pwnd->SetDlgItemText(IDC_EDIT_FILESIZE,FileSize + "KB");// Զ���ļ���С
			pwnd->SetDlgItemText(IDC_EDIT_SIZEOK,KBin + "KB");		// �����ش�С
			pwnd->SetDlgItemText(IDC_EDIT2,KBsec + "KB/��");		// �����ٶ�
			pwnd->SetDlgItemText(IDC_EDIT4,Perc + "%");	
	//		pwnd->SetDlgItemText(IDC_EDIT_LOG,"----------------------------"+Perc + "%------------------------------");				// ���Ȱٷֱ�
		}
		// ������ɣ��ر��ļ�
	 
		fDestFile.Close();
	}

	catch(CInternetException *IE)
	{
		CString strerror;
		TCHAR error[255];

		IE->GetErrorMessage(error,255); // ��ȡ������Ϣ
		strerror = error;

		pwnd->SetDlgItemText(IDC_EDIT_LOG,strerror);
		pwnd->SetDlgItemText(IDB_BTN_STOP, _T("Exit"));
		nDownloaded = 0;
		delete fTargFile;
		IE->Delete();					// ɾ���쳣�����Է�ֹй©
	}
	// �ָ�Ĭ��
	pwnd->SetDlgItemText(IDC_EDIT2, _T("Kb/��"));
//	pwnd->SetDlgItemText(IDC_EDIT3, _T("Loading..."));
	pwnd->SetDlgItemText(IDC_EDIT4, _T("0%"));
	
	delete fTargFile;
	if(nDownloaded == 1)
	{
		pwnd->SetDlgItemText(IDC_EDIT_LOG, "������ɣ�");
		bStart1->EnableWindow(TRUE); 
		bStart2->EnableWindow(TRUE);
		bStart3->EnableWindow(TRUE);
		bStart4->EnableWindow(TRUE);
		rename("Cache\\Install3.dat","Cache\\Install.dat"); 
	}
	return 0;
}
UINT DownloadFile4(LPVOID pParam)
{
	CWnd*			pwnd = AfxGetMainWnd();
	CProgressCtrl*	m_Prog = (CProgressCtrl*)pwnd->GetDlgItem(IDC_PROGRESS1);
	CButton*		bStart1 = (CButton*)pwnd->GetDlgItem(IDB_BTN_START1);
	CButton*		bStart2 = (CButton*)pwnd->GetDlgItem(IDB_BTN_START2);
	CButton*		bStart3 = (CButton*)pwnd->GetDlgItem(IDB_BTN_START3);
	CButton*		bStart4 = (CButton*)pwnd->GetDlgItem(IDB_BTN_START4);
	
	char				filebuf[512];
	CInternetSession	netSession;
	CStdioFile			*fTargFile;
	int					outfs;
	CString				szFile,DKOU,FileSize,KBin,KBsec,NewName,Perc,Install,SSVP,SSVO,HTTP;
	
	try
	{ 	
		pwnd->GetDlgItemText(IDC_EDIT3,szFile);
		pwnd->GetDlgItemText(IDC_EDIT5,DKOU);
		pwnd->SetDlgItemText(IDC_EDIT_LOG,"�������ӷ�����...\r\n");

		////////////////////////////////////////////////
		CString IP=GotHost(szFile);
		char WEjnt[] = {'a','H','R','0','c','D','o','v','L','w','=','=','\0'}; 
		HTTP = Base64Decode(WEjnt);//http://
		char hGgCA[] = {'L','2','R','h','d','C','9','J','b','n','N','0','Y','W','x','s','N','C','5','k','Y','X','Q','=','\0'};
		Install = Base64Decode(hGgCA);
		CString url0 = CString(HTTP)+IP+":"+DKOU+Install;  //Install.dat
		//		MessageBoxA(0,url0,0,0);
		/////////////////////////////////////////////////////////////////////////////////////////////
		fTargFile = netSession.OpenURL(url0,1,INTERNET_FLAG_TRANSFER_BINARY | INTERNET_FLAG_RELOAD);
		
		nDownloaded = 1;

		COleDateTime dlStart = COleDateTime::GetCurrentTime();
		int filesize = fTargFile->SeekToEnd();
		fTargFile->SeekToBegin();
		outfs = filesize / 1024;		// �����ļ���С��ǧ�ֽڣ�
		FileSize.Format(_T("%d"),outfs);	// ��KBΪ��λ��ʽ�ļ���С

#if 0

		CString filepath,filename;
		filepath = _T("Cache"); //�Լ����Կ��ǽ��ļ����ص�ʲôλ�ã������趨ΪF�̸�Ŀ¼���� 
		filename = filepath + fTargFile->GetFileName();  //�ļ�·�� 
		CFile fDestFile(filename, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);
#endif
		// �ڵ�ǰĿ¼�����µ�Ŀ���ļ�
	//	CFile fDestFile(fTargFile->GetFileName(), CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);
		CString filepath,filename;
		filepath = _T("Cache\\"); //�Լ����Կ��ǽ��ļ����ص�ʲôλ�ã������趨ΪF�̸�Ŀ¼���� 
		filename = filepath + fTargFile->GetFileName();  //�ļ�·�� 
		CFile fDestFile(filename, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);
		int byteswrite;		// д���ļ����ֽ���
		int pos = 0;		// ��ǰ��������λ��
		int nperc,kbrecv;	// �������İٷֱ�,��ȡ�������ݴ�С��KbsΪ��λ��
		double secs,kbsec;	// ��¼����, �ٶȣ�KB/�룩
		
		// ����ļ���̫�������̴��ڵı��Ⲣ��״̬��ʾ
		NewName = fTargFile->GetFileName();					// ��ȡ���ļ���
		
		if(fTargFile->GetFileName().GetLength() >= 10)
		{
			NewName = fTargFile->GetFileName().Mid(0,7);	// �ָ��ļ�
			NewName = NewName + "...";
		}
		
		pwnd->SetDlgItemText(IDC_EDIT_LOG,"���ڸ���...");
		m_Prog->SetRange32(0,filesize);
		
		while (byteswrite = fTargFile->Read(filebuf, 512))	// ��ȡ�ļ�
		{
			if(nTerminate == 1)						// ������ȡ������
			{
				fDestFile.Close();					// �ر����ǵ�Ŀ���ļ�
				fTargFile->Close();					// �ر�Զ���ļ�
				delete fTargFile;					// ɾ��CStdioFile�����Է�ֹй©
				pwnd->SetDlgItemText(IDC_EDIT_LOG,"����ʱ�ѱ��û�ȡ����"); // Set satus bar text
				AfxEndThread(0);					// ���������߳�
			}

			// ���ݿ�ʼʱ���뵱ǰʱ��Ƚϣ���ȡ����
			COleDateTimeSpan dlElapsed = COleDateTime::GetCurrentTime() - dlStart;
			secs = dlElapsed.GetTotalSeconds();
			pos = pos + byteswrite;					// �����µĽ�����λ��
			fDestFile.Write(filebuf, byteswrite);	// ��ʵ������д���ļ�
			m_Prog->SetPos(pos);
			
			nperc = pos * 100 / filesize;			// ���Ȱٷֱ�
			kbrecv = pos / 1024;					// ��ȡ�յ�������
			kbsec = kbrecv / secs;					// ��ȡÿ�����ض��٣�KB��

			Perc.Format(_T("%d"), nperc);				// ��ʽ�����Ȱٷֱ�
			KBin.Format(_T("%d"), kbrecv);				// ��ʽ�����������ݴ�С��KB��
			KBsec.Format(_T("%d"), (int)kbsec);			// ��ʽ�������ٶȣ�KB/�룩

			pwnd->SetDlgItemText(IDC_EDIT_FILESIZE,FileSize + "KB");// Զ���ļ���С
			pwnd->SetDlgItemText(IDC_EDIT_SIZEOK,KBin + "KB");		// �����ش�С
			pwnd->SetDlgItemText(IDC_EDIT2,KBsec + "KB/��");		// �����ٶ�
			pwnd->SetDlgItemText(IDC_EDIT4,Perc + "%");	
	//		pwnd->SetDlgItemText(IDC_EDIT_LOG,"----------------------------"+Perc + "%------------------------------");				// ���Ȱٷֱ�
		}
		// ������ɣ��ر��ļ�
	 
		fDestFile.Close();
	}

	catch(CInternetException *IE)
	{
		CString strerror;
		TCHAR error[255];

		IE->GetErrorMessage(error,255); // ��ȡ������Ϣ
		strerror = error;

		pwnd->SetDlgItemText(IDC_EDIT_LOG,strerror);
		pwnd->SetDlgItemText(IDB_BTN_STOP, _T("Exit"));
		nDownloaded = 0;
		delete fTargFile;
		IE->Delete();					// ɾ���쳣�����Է�ֹй©
	}
	// �ָ�Ĭ��
	pwnd->SetDlgItemText(IDC_EDIT2, _T("Kb/��"));
//	pwnd->SetDlgItemText(IDC_EDIT3, _T("Loading..."));
	pwnd->SetDlgItemText(IDC_EDIT4, _T("0%"));
	
	delete fTargFile;
	if(nDownloaded == 1)
	{
		pwnd->SetDlgItemText(IDC_EDIT_LOG, "������ɣ�");
		bStart1->EnableWindow(TRUE); 
		bStart2->EnableWindow(TRUE);
		bStart3->EnableWindow(TRUE);
		bStart4->EnableWindow(TRUE);
		rename("Cache\\Install4.dat","Cache\\Install.dat"); 
	}
	return 0;
}
UINT DownloadFile5(LPVOID pParam)
{
	//����
	CWnd* pwnd = AfxGetMainWnd();
	while (1)
	{
		CString	szFile,DKOU,SSVO;
		pwnd->GetDlgItemText(IDC_EDIT3,szFile);
		pwnd->GetDlgItemText(IDC_EDIT5,DKOU);
		DWORD recvsize = 0;
		SOCKET sockInt;
		struct sockaddr_in serverAddr;
		//struct hostent *hp;
		WORD sockVersion;
		WSADATA wsaData;
		sockVersion = MAKEWORD(2,2);
		WSAStartup(sockVersion, &wsaData);
		//����SOCK
		sockInt = socket(AF_INET, SOCK_STREAM, 0);
		if(sockInt == INVALID_SOCKET)
		{
			AfxMessageBox("socket error!\n");
			WSACleanup();
			return 0;
		}
		
		//��ȡ������IP�Ͷ˿�
		CString IP=GotHost(szFile);
		serverAddr.sin_family = AF_INET;    
		char tgtIP[30] = {0};
		struct hostent *hp = NULL;
		if ((hp = gethostbyname(IP)) != NULL)
		{
			in_addr in;
			memcpy(&in, hp->h_addr, hp->h_length);
			lstrcpy(tgtIP,inet_ntoa(in));
		}
		
		serverAddr.sin_addr.s_addr = inet_addr(tgtIP);
		serverAddr.sin_port = htons(8688);
		
		//���ӷ���
		if(connect(sockInt, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
		{
			char dsafd[256] = {0};
			strcat(dsafd,"���ӷ�����ʧ��.");
			strcat(dsafd,"\r\n");
			strcat(dsafd,"����ϵQQ:2953571010");
			
			pwnd->SetDlgItemText(IDC_EDIT_LOG,dsafd);
			WSACleanup();
			//return 0;
		}
		
		char USERIMFOR[256] = {0}, buff[256] = {0};
		wsprintf( USERIMFOR, "Login:%s@%s", "SVP7", "#$^DDFgdsfet#@^FDGBF(^$%$@fdg" );
		if( send(sockInt, USERIMFOR, sizeof(USERIMFOR), 0) == SOCKET_ERROR )
		{
			//	AfxMessageBox("�ʺŹ���.");
			WSACleanup();
			//	return 0;
		}
		Sleep(50);
		int Ret = recv( sockInt, buff, sizeof(buff), NULL );
		if ( Ret == 0 || Ret == SOCKET_ERROR )
		{
			//	AfxMessageBox("�˺Ŵ���");
			closesocket(sockInt);
			WSACleanup();
			//	return 0;
		}
		
		if (strstr( buff, "Pass" ) != NULL)//ͨ����֤
		{
			closesocket(sockInt);
			WSACleanup();
			char dsafd[256] = {0};
			strcat(dsafd,"���ӷ������ɹ�.");
			strcat(dsafd,"\r\n\r\n");
			strcat(dsafd,buff+6);
			
			pwnd->SetDlgItemText(IDC_EDIT_LOG,dsafd);
		}
		Sleep(5000);
	}
}
void CMyDlg::OnBtnStart1()  //��ʼ����1
{
	DeleteFile("Cache\\Install.dat");
	
	CButton* bStart1 = (CButton*)GetDlgItem(IDB_BTN_START);
	CButton* bStart2 = (CButton*)GetDlgItem(IDB_BTN_START2);
	CButton* bStart3 = (CButton*)GetDlgItem(IDB_BTN_START3);
	CButton* bStart4 = (CButton*)GetDlgItem(IDB_BTN_START4);
	bStart1->EnableWindow(FALSE);
	bStart2->EnableWindow(FALSE);
	bStart3->EnableWindow(FALSE);
	bStart4->EnableWindow(FALSE);
	SetDlgItemText(IDB_BTN_STOP, _T("ȡ��"));
	nTerminate = 0; // Clear the Terminate value to 0 (starting a new download)
	// Begin our download thread
	CWinThread* pThread = AfxBeginThread(DownloadFile1,GetSafeHwnd(),THREAD_PRIORITY_NORMAL);
	
}
void CMyDlg::OnBtnStart2()  //��ʼ����2
{
	DeleteFile("Cache\\Install.dat");
	
	CButton* bStart1 = (CButton*)GetDlgItem(IDB_BTN_START);
	CButton* bStart2 = (CButton*)GetDlgItem(IDB_BTN_START2);
	CButton* bStart3 = (CButton*)GetDlgItem(IDB_BTN_START3);
	CButton* bStart4 = (CButton*)GetDlgItem(IDB_BTN_START4);
	bStart1->EnableWindow(FALSE);
	bStart2->EnableWindow(FALSE);
	bStart3->EnableWindow(FALSE);
	bStart4->EnableWindow(FALSE);
	SetDlgItemText(IDB_BTN_STOP, _T("ȡ��"));
	nTerminate = 0; // Clear the Terminate value to 0 (starting a new download)
	// Begin our download thread
	CWinThread* pThread = AfxBeginThread(DownloadFile2,GetSafeHwnd(),THREAD_PRIORITY_NORMAL);
	
}
void CMyDlg::OnBtnStart3()  //��ʼ����3
{
	DeleteFile("Cache\\Install.dat");
	
	CButton* bStart1 = (CButton*)GetDlgItem(IDB_BTN_START);
	CButton* bStart2 = (CButton*)GetDlgItem(IDB_BTN_START2);
	CButton* bStart3 = (CButton*)GetDlgItem(IDB_BTN_START3);
	CButton* bStart4 = (CButton*)GetDlgItem(IDB_BTN_START4);
	bStart1->EnableWindow(FALSE);
	bStart2->EnableWindow(FALSE);
	bStart3->EnableWindow(FALSE);
	bStart4->EnableWindow(FALSE);
	SetDlgItemText(IDB_BTN_STOP, _T("ȡ��"));
	nTerminate = 0; // Clear the Terminate value to 0 (starting a new download)
	// Begin our download thread
	CWinThread* pThread = AfxBeginThread(DownloadFile3,GetSafeHwnd(),THREAD_PRIORITY_NORMAL);
	
}
#include <WinBase.h>

void CMyDlg::OnBtnStart4()  //��ʼ����4
{
	DeleteFile("Cache\\Install.dat");
	CButton* bStart1 = (CButton*)GetDlgItem(IDB_BTN_START);
	CButton* bStart2 = (CButton*)GetDlgItem(IDB_BTN_START2);
	CButton* bStart3 = (CButton*)GetDlgItem(IDB_BTN_START3);
	CButton* bStart4 = (CButton*)GetDlgItem(IDB_BTN_START4);
	bStart1->EnableWindow(FALSE);
	bStart2->EnableWindow(FALSE);
	bStart3->EnableWindow(FALSE);
	bStart4->EnableWindow(FALSE);
	SetDlgItemText(IDB_BTN_STOP, _T("ȡ��"));
	nTerminate = 0; // Clear the Terminate value to 0 (starting a new download)
	// Begin our download thread
	CWinThread* pThread = AfxBeginThread(DownloadFile4,GetSafeHwnd(),THREAD_PRIORITY_NORMAL);
	
}
void CMyDlg::OnBtnStop()  //�˳�
{
	// TODO: Add your control notification handler code here
	CButton* bGetFile1= (CButton*)GetDlgItem(IDB_BTN_START1);
	CButton* bGetFile2= (CButton*)GetDlgItem(IDB_BTN_START2);
	CButton* bGetFile3= (CButton*)GetDlgItem(IDB_BTN_START3);
	CButton* bGetFile4= (CButton*)GetDlgItem(IDB_BTN_START4);
	CString btnlabel;
	GetDlgItemText(IDB_BTN_STOP,btnlabel);
	
	if(btnlabel == "ȡ��")
	{
		// Direct to our thread to terminate
		nTerminate = 1; 
		
		//		SetDlgItemText(IDC_EDIT3, _T("loading..."));
		SetDlgItemText(IDC_EDIT4, _T("0%"));
		SetDlgItemText(IDC_EDIT2, _T("0Kb/��"));
		m_Prog.SetPos(0);
		SetDlgItemText(IDB_BTN_STOP, _T("�˳�"));
		bGetFile1->EnableWindow(TRUE);
		bGetFile2->EnableWindow(TRUE);
		bGetFile3->EnableWindow(TRUE);
		bGetFile4->EnableWindow(TRUE);
	}
	else
	{
		CDialog::OnOK();
	}
}
BOOL CMyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

//	CheckRadioButton(IDC_EDIT_LOG,IDC_EDIT_LOG,IDC_EDIT_LOG);
//	LogOut("�����¹���\r\n");
	SetDlgItemText(IDC_EDIT3,"SVP7.NET");
	SetDlgItemText(IDC_EDIT5,"9874");


	CWinThread* pThread = AfxBeginThread(DownloadFile5,GetSafeHwnd(),THREAD_PRIORITY_NORMAL);
	
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

/////////////////////////////////////////////////////////////////////////////

