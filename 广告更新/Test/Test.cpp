// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <STRING.H>

#include <STDLIB.H>
#include <WinUser.h>
int main(int argc, char* argv[])
{
	char dsafd1[256] = {0};
	char dsafd2[256] = {0};
	printf("���IE��ʱ�ļ�Ŀ¼...\n");
	system("echo.");
	strcat(dsafd1,"del /f /s /q ");
	strcat(dsafd1,"%userprofile%\\AppData\\Local\\Microsoft\\Windows\\Temporary Internet Files\\*.*");
	system(dsafd1);

	printf("\n����IE�������\n");
	system("echo.");
	strcat(dsafd2,"del /f /s /q ");
	strcat(dsafd2,"%temp%\\*.*");
	system(dsafd2);
	system("echo.");
	system("del C:\\Windows\\Server.dll");
	system("ipconfig /flushdns");
	system("echo ~~~------~~~~~");
	printf("�ȴ�2����Զ��ر�\n");
	system("TIMEOUT /T 2");
	return 0;
}

