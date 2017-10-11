; FILE:         SME Vcs.iss
; AUTHOR:       ������
; FOR:          SME Vcs
; VERSION:      2.0
; DESCRIPTION:  SME Vcs Win32 ��װ�ļ� (My Inno Setup Extensions 3.0.2(beta))
; HISTORY:
;       Sep. 9, 2003  ������    �������ļ�
;       Nov. 2004     ������    modify for second version
;       Feb. 2005     ��С��    Modify for second version
;       Jun. 2005     ������    modify for second version
; NOTES:
;       �汾�ų�����[Setup]AppVerName��[Registry]"Version"
;

[Setup]
AppName =��С������Ƶ����ϵͳV2.0
AppVerName =SME VCS V2.0
AppPublisher=������С������Ϣ�������޹�˾
AppPublisherURL=http://web.sme.cn
AppSupportURL=http://web.sme.cn
AppUpdatesURL=http://web.sme.cn
AppCopyright=Copyright 2004 ������С������Ϣ�������޹�˾.
DefaultDirName ={pf}\SME VCS V2
DefaultGroupName =SME VCS V2
SourceDir=..\..\..
OutputDir=install\Client
OutputBaseFileName = SMEVCS_Setup
UninstallDisplayIcon ={app}\bin\Flvcc.exe
UninstallDisplayName =SME VCS V2.0
LicenseFile=install\License\licenseSME.txt

[Languages]
Name: "chs"; MessagesFile: "install\language\ChineseSimp-7-lsc-4.2.2.isl"

[Tasks]
Name: desktopicon; Description: "���������ݷ�ʽ"; GroupDescription: "���ӿ�ݷ�ʽ:"
Name: quicklaunchicon; Description: "��������������ݷ�ʽ"; GroupDescription: "���ӿ�ݷ�ʽ:"
Name: autorun; Description: "��¼Windows���Զ�����"; GroupDescription: "����:"

[Files]
source: "src\Client\Release\FvsAudioPlay.exe"; DestDir: "{app}\bin"; Flags: ignoreversion;
source: "src\Client\Release\Flvcc.exe"; DestDir: "{app}\bin"; Flags: ignoreversion;
source: "src\Client\Release\wm_hooks.dll"; DestDir: "{app}\bin"; Flags: ignoreversion;
source: "src\Video\Dump\Release\Dump.ax"; DestDir: "{app}\bin"; Flags: ignoreversion;
source: "install\VCRedist\Releasedll\MFC71.dll"; DestDir: "{sys}"; Flags: onlyifdoesntexist uninsneveruninstall;
source: "install\VCRedist\Releasedll\MSVCR71.dll"; DestDir: "{sys}"; Flags: onlyifdoesntexist uninsneveruninstall;
source: "install\VCRedist\Releasedll\MSVCP71.dll"; DestDir: "{sys}"; Flags: onlyifdoesntexist uninsneveruninstall;
source: "install\VCRedist\Releasedll\TklSdkAll.dll"; DestDir: "{app}\bin"; Flags: ignoreversion;
source: "install\VCRedist\Releasedll\TklSdkAve68k.dll"; DestDir: "{app}\bin"; Flags: ignoreversion;
source: "install\VCRedist\Releasedll\Decoder6ks.dll"; DestDir: "{app}\bin"; Flags: ignoreversion;
source: "install\VCRedist\Releasedll\TKL_Player.dll"; DestDir: "{app}\bin"; Flags: ignoreversion;
source: "src\Client\conf\SME.ini.template"; DestDir: "{app}\conf"; DestName: "Flvcc.ini"; Flags: ignoreversion;
source: "src\WebLauncher\WebLauncher\Release\WebLauncher.ocx"; DestDir: "{sys}"; Flags: ignoreversion uninsneveruninstall;
source: "src\Client\data\confnotice.xsl"; DestDir: "{app}\data"; Flags: ignoreversion;
source: "src\Client\data\leaveword.xsl"; DestDir: "{app}\data"; Flags: ignoreversion;
source: "src\Client\data\systemmsg.xsl"; DestDir: "{app}\data"; Flags: ignoreversion;
source: "src\Client\data\historyconf.xsl"; DestDir: "{app}\data"; Flags: ignoreversion;
source: "src\Client\data\message.xsl"; DestDir: "{app}\data"; Flags: ignoreversion;
source: "src\Client\AVClips\WindowsStartup.wav"; DestDir: "{app}\AVClips"; Flags:ignoreversion;
source: "src\Client\version.dat"; DestDir: "{app}\"; Flags: ignoreversion;
source: "install\SMEHelp\*"; DestDir: "{app}\help"; Flags: ignoreversion;
source: "install\SMEHelp\client\*"; DestDir: "{app}\help\client"; Flags: ignoreversion;
source: "install\SMEHelp\client\images\*"; DestDir: "{app}\help\client\images"; Flags: ignoreversion;
source: "install\SMEHelp\images\*"; DestDir: "{app}\help\images"; Flags: ignoreversion;
;source: "src\Miranda\bin7\Release Unicode\miranda32.exe"; DestDir: "{app}\bin"; Flags: ignoreversion;
;source: "src\Miranda\bin7\Release Unicode\plugins\srmm.dll"; DestDir: "{app}\bin\plugins"; Flags: ignoreversion;
;source: "src\Miranda\bin7\Release Unicode\plugins\png2dib.dll"; DestDir: "{app}\bin\plugins"; Flags: ignoreversion;
;source: "src\Miranda\bin7\Release Unicode\plugins\msn.dll"; DestDir: "{app}\bin\plugins"; Flags: ignoreversion;
;source: "src\Miranda\bin7\Release Unicode\plugins\dbx_3x.dll"; DestDir: "{app}\bin\plugins"; Flags: ignoreversion;
;source: "src\Miranda\bin7\Release Unicode\plugins\clist_classic.dll"; DestDir: "{app}\bin\plugins"; Flags: ignoreversion;
;source: "src\Miranda\bin7\dat.default"; DestDir: "{app}\bin"; DestName: "default.dat"; Flags: ignoreversion;
;source: "src\Miranda\bin7\langpack_chineses.txt"; DestDir: "{app}\bin"; Flags: ignoreversion;

[Dirs]
name: "{app}\data\received files";

[Registry]
Root: HKLM; Subkey: Software\SME; Flags: uninsdeletekeyifempty
Root: HKLM; Subkey: Software\SME\FLVCC2.0; Flags: uninsdeletekey
Root: HKLM; Subkey: Software\SME\FLVCC2.0; ValueType: string; ValueName: InstallDir; ValueData: {app}\bin
Root: HKLM; Subkey: Software\SME\FLVCC2.0; ValueType: string; ValueName: Version; ValueData: 2.0
Root: HKLM; Subkey: SOFTWARE\Microsoft\Windows\CurrentVersion\Run; Flags: uninsdeletevalue; ValueType: string; ValueName: SME VCS; ValueData: {code:GetShortName|{app}\bin\Flvcc.exe}; Tasks: autorun

[Icons]
Name: "{group}\SME VCS V2"; FileName: {app}\bin\Flvcc.exe; WorkingDir: {app}\bin\
Name: "{group}\ж��SME VCS V2.0"; Filename: {uninstallexe}
Name: "{group}\����"; FileName: {app}\help\index.html;
Name: "{userdesktop}\SME VCS V2"; FileName: {app}\bin\Flvcc.exe; WorkingDir: {app}\bin\; Tasks: desktopicon
Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\SME VCS V2"; Filename: {app}\bin\Flvcc.exe; WorkingDir: {app}\bin; Tasks: quicklaunchicon

[Run]
FileName: {sys}\regsvr32.exe; Description: ע��WebLauncher�ؼ�; Parameters: "/s WebLauncher.ocx"; WorkingDir: {sys};
FileName: {sys}\regsvr32.exe; Description: ע��Dump Filter; Parameters: "/s Dump.ax"; WorkingDir: {app}\bin;
FileName: {app}\bin\Flvcc.exe; Description: ��װ��ɺ���������; WorkingDir: {app}\bin; Flags: postinstall nowait;

[UninstallRun]
FileName: {sys}\regsvr32.exe; Parameters: "/u /s Dump.ax"; WorkingDir: {app}\bin;

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

