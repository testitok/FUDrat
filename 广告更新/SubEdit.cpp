// SubEdit.cpp : implementation file
//// Download by http://www.srcfans.com

#include "stdafx.h"
#include "广告更新.h"
#include "SubEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SubEdit

SubEdit::SubEdit()
{
	m_Color = RGB(0, 0, 255);
}

SubEdit::~SubEdit()
{
}


BEGIN_MESSAGE_MAP(SubEdit, CEdit)
	//{{AFX_MSG_MAP(SubEdit)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()

HBRUSH SubEdit::CtlColor(CDC* pDC, UINT nCtlColor) 
{

	DWORD dwStyle = GetStyle();
	HBRUSH hbr = NULL;
       if (!((HFONT) m_font))
	   {
		  LOGFONT lf;
		  GetFont()->GetObject(sizeof(lf), &lf);
		  //lf.lfUnderline = TRUE;
		  lf.lfItalic=TRUE;
		  m_font.CreateFontIndirect(&lf);
	   }
		pDC->SelectObject(&m_font);
		pDC->SetTextColor(m_Color);
		pDC->SetBkMode(TRANSPARENT);
		hbr = (HBRUSH)::GetStockObject(HOLLOW_BRUSH);

	return hbr;
}

/////////////////////////////////////////////////////////////////////////////
// SubEdit message handlers
