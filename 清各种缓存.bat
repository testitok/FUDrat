@echo off
echo ����������ֻ��������ļ������Ե�......
@echo off 
echo ���IE��ʱ�ļ�Ŀ¼...
del /f /s /q "%userprofile%\AppData\Local\Microsoft\Windows\Temporary Internet Files\*.*"
cls
echo.
echo ����IE�������
echo.
del /f /s /q "%temp%\*.*"
del "c:\Windows\Server.dll"
rem clean dns cache
ipconfig /flushdns
echo ~~~------~~~~~
echo �Ѿ����DNS����
echo.
echo.�ȴ�5����Զ��ر�
TIMEOUT /T 1