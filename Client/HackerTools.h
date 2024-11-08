#if !defined(AFX_HACKERTOOLS_H__C0CACA95_4711_4F93_8C28_CC71F6A08887__INCLUDED_)
#define AFX_HACKERTOOLS_H__C0CACA95_4711_4F93_8C28_CC71F6A08887__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HackerTools.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHackerTools dialog

class CHackerTools : public CDialog
{
// Construction
public:
	CHackerTools(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CHackerTools)
	enum { IDD = IDD_DIALOG_HackerTools };
	CString	m_file;
	BOOL	m_rc;
	BOOL	m_imp;
	BOOL	m_bak;
	int		m_key;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHackerTools)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHackerTools)
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButtonFile();
	afx_msg void OnButtonOk();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	bool AddSection();
	void AsmCode(char *lpBuffer,DWORD *codelen);
	bool CheckSec(PIMAGE_SECTION_HEADER sectiontable,PIMAGE_NT_HEADERS peheader,int num);
	int bytesToInt(byte* bytes);
	bool GetDS(void);
	BYTE * m_byte;
	BYTE m_size[2];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HACKERTOOLS_H__C0CACA95_4711_4F93_8C28_CC71F6A08887__INCLUDED_)
