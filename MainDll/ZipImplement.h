#include "stdafx.h"
#include "zip.h"
#include "unzip.h"
#include <OleAuto.h>
#include <vector> 
#include <atlconv.h>
#include <shlwapi.h>
#pragma comment(lib,"shlwapi.lib")
HZIP hz;
ZRESULT zr;
ZIPENTRY ze;
BOOL FolderExist(CString& strPath) 
{ 
    CString sCheckPath = strPath; 
	
    if(sCheckPath.Right(1) != L"\\") 
        sCheckPath += L"\\"; 
	
    sCheckPath += L"*.*"; 
	
    WIN32_FIND_DATA wfd; 
    BOOL rValue = FALSE; 
	
    HANDLE hFind = FindFirstFile(sCheckPath, &wfd); 
	
    if ((hFind!=INVALID_HANDLE_VALUE) && 
        (wfd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY) || (wfd.dwFileAttributes&FILE_ATTRIBUTE_ARCHIVE)) 
    { 
        //������ڲ��������ļ��� 
        rValue = TRUE; 
    } 
	
    FindClose(hFind); 
    return rValue; 
} 
BOOL CreatedMultipleDirectory(wchar_t* direct) 
{ 
    std::wstring Directoryname = direct; 
	
    if (Directoryname[Directoryname.length() - 1] !=  '\\') 
    { 
        Directoryname.append(1, '\\'); 
    } 
    std::vector< std::wstring> vpath; 
    std::wstring strtemp; 
    BOOL  bSuccess = FALSE; 
    for (int i = 0; i < Directoryname.length(); i++) 
    { 
        if ( Directoryname[i] != '\\') 
        { 
            strtemp.append(1,Directoryname[i]);    
        } 
        else
        { 
            vpath.push_back(strtemp); 
            strtemp.append(1, '\\'); 
        } 
    } 
    std::vector<std::wstring>:: const_iterator vIter; 
    for (vIter = vpath.begin();vIter != vpath.end(); vIter++) 
	{
		USES_CONVERSION;
		bSuccess = CreateDirectoryA( W2A(vIter->c_str()), NULL ) ? true :false;
		
	}
	
    return bSuccess; 
}

BOOL Zip_UnPackFiles(CString mZipFileFullPath, CString mUnPackPath, CString strPW)
{ 
    //�������� 
    if ((mUnPackPath.IsEmpty()) || (mZipFileFullPath.IsEmpty())) 
    { 
        //·���쳣���� 
        return FALSE ; 
    } 
	
    CFileFind tFFind; 
    if (!tFFind.FindFile(mZipFileFullPath)) 
    { 
        //ѹ��ʧ��(δ����ѹ���ļ�) 
        return FALSE; 
    } 
	
    //�����ѹ����·�������� ��ͼ������ 
    CString tZipFilePath = mUnPackPath; 
    if(!FolderExist(tZipFilePath)) 
    { 
        //��ѹ���ŵ��ļ��в����� ������         
		CString strWZipFilePath(tZipFilePath);
        if (FALSE == CreatedMultipleDirectory((LPWSTR)(LPCWSTR)&strWZipFilePath)) 
        { 
            //����Ŀ¼ʧ�� 
            return FALSE; 
        } 
    } 
    /************************************************************************/
    //��ZIP�ļ�
	if (strPW.IsEmpty())
	{
		hz=OpenZip(mZipFileFullPath,0);
	}
	else
	{
		hz=OpenZip(mZipFileFullPath,(LPCSTR)strPW);
	}     
    if(hz == 0) 
    { 
        //��Zip�ļ�ʧ�� 
        return FALSE; 
    } 
	
    zr=SetUnzipBaseDir(hz,mUnPackPath); 
    if(zr != ZR_OK) 
    { 
        //��Zip�ļ�ʧ�� 
        CloseZip(hz); 
        return FALSE;       
    } 
	
    zr=GetZipItem(hz,-1,&ze); 
    if(zr != ZR_OK) 
    { 
        //��ȡZip�ļ�����ʧ�� 
        CloseZip(hz); 
        return FALSE;       
    } 
	
    int numitems=ze.index; 
    for (int i=0; i<numitems; i++) 
    { 
        zr=GetZipItem(hz,i,&ze); 
        zr=UnzipItem(hz,i,ze.name); 
        if(zr != ZR_OK) 
        { 
            //��ȡZip�ļ�����ʧ�� 
            CloseZip(hz); 
            return FALSE;       
        } 
    } 
	
    CloseZip(hz); 
    return TRUE; 
}