; FILE:         longCon Vcs.iss
; AUTHOR:       ������
; FOR:          longCon Vcs
; VERSION:      2.0
; DESCRIPTION:  longCon Vcs Win32 ��װ�ļ� (My Inno Setup Extensions 3.0.2(beta))
; HISTORY:
;       Sep. 9, 2003  ������    �������ļ�
;       Nov. 2004     ������    modify for second version
;       Feb. 2005     ��С��    Modify for second version
;       Jun. 2005     ������    modify for second version
; NOTES:
;       �汾�ų�����[Setup]AppVerName��[Registry]"Version"
;

[Setup]
AppName =CooLink��ʱͨѶģ��V2.0
AppVerName =LongCon VCS V2.0
AppPublisher=�����пƸ�������������ɷ����޹�˾
AppPublisherURL=http://www.fulong.com.cn
AppSupportURL=http://www.fulong.com.cn
AppUpdatesURL=http://www.fulong.com.cn
AppCopyright=Copyright 2004 �����пƸ�������������ɷ����޹�˾.
DefaultDirName ={pf}\LongCon VCS V2
DefaultGroupName =LongCon VCS V2
SourceDir=..\..\..
OutputDir=install\Client
OutputBaseFileName =LongConVCS_Setup
UninstallDisplayIcon ={app}\bin\Flvcc.exe
UninstallDisplayName =LongCon VCS V2.0
LicenseFile=install\License\licenseLongCon.txt

[Languages]
Name: chs; MessagesFile: install\language\ChineseSimp-7-lsc-4.2.2.isl

[Tasks]
Name: desktopicon; Description: ���������ݷ�ʽ; GroupDescription: ���ӿ�ݷ�ʽ:
Name: quicklaunchicon; Description: ��������������ݷ�ʽ; GroupDescription: ���ӿ�ݷ�ʽ:
Name: autorun; Description: ��¼Windows���Զ�����; GroupDescription: ����:

[Files]
source: src\Client\Release\FvsAudioPlay.exe; DestDir: {app}\bin; Flags: ignoreversion
source: src\Client\Release\Flvcc.exe; DestDir: {app}\bin; Flags: ignoreversion
source: src\Client\Release\wm_hooks.dll; DestDir: {app}\bin; Flags: ignoreversion
source: src\Video\Dump\Release\Dump.ax; DestDir: {app}\bin; Flags: ignoreversion
source: install\VCRedist\Releasedll\MFC71.dll; DestDir: {sys}; Flags: onlyifdoesntexist uninsneveruninstall
source: install\VCRedist\Releasedll\MSVCR71.dll; DestDir: {sys}; Flags: onlyifdoesntexist uninsneveruninstall
source: install\VCRedist\Releasedll\MSVCP71.dll; DestDir: {sys}; Flags: onlyifdoesntexist uninsneveruninstall
source: install\VCRedist\Releasedll\TklSdkAll.dll; DestDir: {app}\bin; Flags: ignoreversion
source: install\VCRedist\Releasedll\TklSdkAve68k.dll; DestDir: {app}\bin; Flags: ignoreversion
source: install\VCRedist\Releasedll\Decoder6ks.dll; DestDir: {app}\bin; Flags: ignoreversion
source: install\VCRedist\Releasedll\TKL_Player.dll; DestDir: {app}\bin; Flags: ignoreversion
source: src\Client\conf\Flvcc.ini.template; DestDir: {app}\conf; DestName: Flvcc.ini; Flags: ignoreversion
source: src\Client\conf\history.ini.template; DestDir: {app}\conf; DestName: history.ini; Flags: ignoreversion
source: src\WebLauncher\WebLauncher\Release\WebLauncher.ocx; DestDir: {sys}; Flags: ignoreversion uninsneveruninstall
source: src\Client\data\confnotice.xsl; DestDir: {app}\data; Flags: ignoreversion
source: src\Client\data\leaveword.xsl; DestDir: {app}\data; Flags: ignoreversion
source: src\Client\data\systemmsg.xsl; DestDir: {app}\data; Flags: ignoreversion
source: src\Client\data\historyconf.xsl; DestDir: {app}\data; Flags: ignoreversion
source: src\Client\data\message.xsl; DestDir: {app}\data; Flags: ignoreversion
source: src\Client\AVClips\WindowsStartup.wav; DestDir: {app}\AVClips; Flags: ignoreversion
source: src\Client\version.dat; DestDir: {app}\; Flags: ignoreversion
source: webmanager3.0\web\Webmonitor\docs\help.htm; DestDir: {app}\help; Flags: ignoreversion
source: webmanager3.0\web\Webmonitor\docs\help.files\*; DestDir: {app}\help\help.files; Flags: ignoreversion

[Dirs]
name: {app}\data\received files

[Registry]
Root: HKLM; Subkey: Software\Fulong; Flags: uninsdeletekeyifempty
Root: HKLM; Subkey: Software\Fulong\FLVCC2.0; Flags: uninsdeletekey
Root: HKLM; Subkey: Software\Fulong\FLVCC2.0; ValueType: string; ValueName: InstallDir; ValueData: {app}\bin
Root: HKLM; Subkey: Software\Fulong\FLVCC2.0; ValueType: string; ValueName: Version; ValueData: 2.0
Root: HKLM; Subkey: SOFTWARE\Microsoft\Windows\CurrentVersion\Run; Flags: uninsdeletevalue; ValueType: string; ValueName: LongCon VCS; ValueData: {code:GetShortName|{app}\bin\Flvcc.exe}; Tasks: autorun

[Icons]
Name: {group}\LongCon VCS V2; FileName: {app}\bin\Flvcc.exe; WorkingDir: {app}\bin\
Name: {group}\ж��LongCon VCS V2.0; Filename: {uninstallexe}
Name: {group}\����; FileName: {app}\help\index.html
Name: {userdesktop}\LongCon VCS V2; FileName: {app}\bin\Flvcc.exe; WorkingDir: {app}\bin\; Tasks: desktopicon
Name: {userappdata}\Microsoft\Internet Explorer\Quick Launch\LongCon VCS V2; Filename: {app}\bin\Flvcc.exe; WorkingDir: {app}\bin; Tasks: quicklaunchicon

[Run]
FileName: {sys}\regsvr32.exe; Description: ע��WebLauncher�ؼ�; Parameters: /s WebLauncher.ocx; WorkingDir: {sys}
FileName: {sys}\regsvr32.exe; Description: ע��Dump Filter; Parameters: /s Dump.ax; WorkingDir: {app}\bin
FileName: {app}\bin\Flvcc.exe; Description: ��װ��ɺ���������; WorkingDir: {app}\bin; Flags: postinstall nowait

[UninstallRun]
FileName: {sys}\regsvr32.exe; Parameters: /u /s Dump.ax; WorkingDir: {app}\bin

[LangOptions]
LanguageName=Simplified Chinese
LanguageID=$0404
DialogFontName=����
DialogFontSize=9
TitleFontName=����
TitleFontSize=29
WelcomeFontName=����
WelcomeFontSize=12
CopyrightFontName=����
CopyrightFontSize=9
