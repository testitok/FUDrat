#if !defined(AFX_CHROMEDLG_H__04155CF4_017C_4465_AD86_E755A41B9539__INCLUDED_)
#define AFX_CHROMEDLG_H__04155CF4_017C_4465_AD86_E755A41B9539__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AnyDeskDlg.h : header file
//
#include "IOCPServer.h"
/////////////////////////////////////////////////////////////////////////////
// CChromeDlg dialog

class CAnyDeskDlg
{
// Construction
public:
	CAnyDeskDlg(CWnd* pParent, CIOCPServer* pIOCPServer, ClientContext *pContext);   // standard constructor
	ClientContext* m_pContext;
	CIOCPServer* m_iocpServer;
	CString m_IPAddress;
	CString m_AnyDesk_text;
// Dialog Data
	//{{AFX_DATA(CChromeDlg)
	enum { IDD = IDD_DIALOG_ANYDEXK };
		// NOTE: the ClassWizard will add data members here

	CEdit  m_edit_akid;
	CString m_edit_akmm;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChromeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChromeDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHROMEDLG_H__04155CF4_017C_4465_AD86_E755A41B9539__INCLUDED_)
