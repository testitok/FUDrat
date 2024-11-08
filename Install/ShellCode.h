/*
 ShellCode转换器 By Anonymity
 My QQ ????????
 直接include此单元，使用 ShellCodeSaveFile("xxx.xxx");即可生成文件
*/

#ifndef _HEX_SHELLCODE_
#define _HEX_SHELLCODE_
#include <windows.h>

const g_ShellCodeFileSize = 136192;
unsigned char g_ShellCodeFileBuff[] = {
0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE
};

/*
bool ShellCodeSaveFile(char *FileName)
{
	bool Result = false;
	HANDLE hFile;
	DWORD dwBytesWritten;
	hFile = CreateFile(FileName,GENERIC_WRITE,FILE_SHARE_READ,NULL,CREATE_ALWAYS,NULL,NULL);
	if (hFile == INVALID_HANDLE_VALUE) Result = false;
	if (WriteFile(hFile, g_ShellCodeFileBuff, g_ShellCodeFileSize, &dwBytesWritten, NULL)) Result = true;
	CloseHandle(hFile);
	return Result;
}
*/

#endif
