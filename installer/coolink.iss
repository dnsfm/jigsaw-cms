; FILE:         coolink.iss
; AUTHOR:       ����
; FOR:          Coolink 1.0
; VERSION:      1.0
; DESCRIPTION:  Coolink 1.0 Win32 ��װ�ļ� (Inno Setup 5.3.3)

#define MyAppName "CoolinkЭͬ����֧��ƽ̨"
#define MyAppVerName "CoolinkЭͬ����֧��ƽ̨ 1.0"
#define MyAppPublisher "�����пƸ�������������ɷ����޹�˾"
#define MyAppURL "http://www.fulong.cn/"

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{21206C6C-FB97-4DD0-B214-9AB01C99023D}
AppName={#MyAppName}
AppVerName={#MyAppVerName}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName=C:\coolink
SourceDir =E:\coolink1.0
DefaultGroupName=Coolink
OutputDir=E:\target2
OutputBaseFilename=coolink
Compression=lzma
InternalCompressLevel =max
SolidCompression=yes
ChangesEnvironment=yes
LicenseFile=E:\coolink1.0\license.rtf

[Languages]
;Name: "english"; MessagesFile: "compiler:Default.isl"
Name: cn; MessagesFile: compiler:Languages\ChineseSimp-7-11-lsc-5.1.13.isl

[Dirs]
Name: {app}; Permissions: users-full powerusers-full admins-full authusers-full;
Name: {app}\ORADATA
Name: {app}\ORALOG


[Icons]
;Name: {group}\{cm:ProgramOnTheWeb,{#MyAppName}}; Filename: {#MyAppURL}
Name: {group}\����Coolink; FileName: {app}\start.bat; WorkingDir: {app}; IconFilename: {app}\icons\run_group.ico
Name: {group}\ֹͣCoolink; FileName: {app}\stop.bat; WorkingDir: {app}; IconFilename: {app}\icons\stop_group.ico
Name: {group}\{cm:UninstallProgram,{#MyAppName}}; Filename: {uninstallexe}
Name: {commondesktop}\����Coolink; FileName: {app}\start.bat; WorkingDir: {app}; IconFilename: {app}\icons\run_desk.ico
Name: {commondesktop}\ֹͣCoolink; FileName: {app}\stop.bat; WorkingDir: {app}; IconFilename: {app}\icons\stop_desk.ico


[Tasks]
;Name: modifypath; Description: �Զ����û�������


[Files]
source: apache-tomcat-6.0.18\*.*; DestDir: {app}\apache-tomcat-6.0.18; Flags: ignoreversion sortfilesbyextension recursesubdirs
source: jdk1.6\*.*; DestDir: {app}\jdk1.6; Flags: ignoreversion sortfilesbyextension recursesubdirs
source: thirdparty\*.*; DestDir: {app}\thirdparty; Flags: ignoreversion sortfilesbyextension recursesubdirs
source: icons\*.*; DestDir: {app}\icons; Flags: ignoreversion sortfilesbyextension recursesubdirs
source: version.txt; DestDir: {app}; Flags: ignoreversion sortfilesbyextension recursesubdirs
source: dbinstall.bat; DestDir: {app}; Flags: ignoreversion sortfilesbyextension recursesubdirs
source: perlInstall.bat; DestDir: {app}; Flags: ignoreversion sortfilesbyextension recursesubdirs
source: coolink_database1.0.1.sql; DestDir: {app}; Flags: ignoreversion sortfilesbyextension recursesubdirs
;���ı���dmp����
;source: data.dmp; DestDir: {app}; Flags: ignoreversion sortfilesbyextension recursesubdirs
source: exec.sql; DestDir: {app}; Flags: ignoreversion sortfilesbyextension recursesubdirs
source: start.bat; DestDir: {app}; Flags: ignoreversion sortfilesbyextension recursesubdirs
source: stop.bat; DestDir: {app}; Flags: ignoreversion sortfilesbyextension recursesubdirs
source: templates\*.*; DestDir: {app}\templates; Flags: ignoreversion sortfilesbyextension recursesubdirs
;source: readme.txt; DestDir: {app}; Flags: ignoreversion sortfilesbyextension isreadme

[Run]
;Filename: {app}\apache-tomcat-6.0.18\bin\startup.bat; StatusMsg: ���ڰ�װ apache-tomcat-6.0.18; Description: ��װ apache-tomcat-6.0.18; Flags: shellexec


[Code]
var
  Page: TWizardPage;
  CDKeyPage: TWizardPage;
  DBALabel: TNewStaticText;
  DBServiceNameLabel: TNewStaticText;
  AddressLabel: TNewStaticText;
  UsernameLabel: TNewStaticText;
  PasswordLabel: TNewStaticText;
  installCDKeyLabel: TNewStaticText;
  CDKeySeparator1: TNewStaticText;
  CDKeySeparator2: TNewStaticText;
  CDKeySeparator3: TNewStaticText;
  DomainLabel: TNewStaticText;
  SizeLabel: TNewStaticText;
  UnitLabel: TNewStaticText;
  PortLabel: TNewStaticText;
  DBAEdit: TPasswordEdit;
  DBServiceNameEdit: TNewEdit;
  AddressEdit: TNewEdit;
  UsernameEdit: TNewEdit;
  PasswordEdit: TPasswordEdit;
  installCDKeyEdit1: TNewEdit;
  installCDKeyEdit2: TNewEdit;
  installCDKeyEdit3: TNewEdit;
  installCDKeyEdit4: TNewEdit;
  DomainEdit: TNewEdit;
  SizeEdit: TNewEdit;
  PortEdit: TNewEdit;
  installDB: TCheckBox;
  OKButton, CancelButton: TNewButton;
  ResultCode: Integer;
	newJAVAHOME:	String;




procedure SetEnvironment;
{��װʱ���û�������}
var
  javaHome,classPath,path,tomcatHome : String;
  oldJAVAHOME,oldCLASSPATH,oldTOMCAT_HOME:	String;
begin
  //���氲װǰ�Ļ����������Ա�ж��ʱ�ָ�
  RegQueryStringValue(HKEY_LOCAL_MACHINE, 'SYSTEM\CurrentControlSet\Control\Session Manager\Environment', 'JAVA_HOME', oldJAVAHOME);//����ԭ��JAVA_HOME��ֵ
  RegWriteStringValue(HKEY_LOCAL_MACHINE, 'SOFTWARE\COOLINK', 'oldJAVAHOME', oldJAVAHOME);
  RegQueryStringValue(HKEY_LOCAL_MACHINE, 'SYSTEM\CurrentControlSet\Control\Session Manager\Environment', 'CLASSPATH', oldCLASSPATH);//����ԭ��CLASSPATH��ֵ
  RegWriteStringValue(HKEY_LOCAL_MACHINE, 'SOFTWARE\COOLINK', 'oldCLASSPATH', oldCLASSPATH);
  RegQueryStringValue(HKEY_LOCAL_MACHINE, 'SYSTEM\CurrentControlSet\Control\Session Manager\Environment', 'TOMCAT_HOME', oldTOMCAT_HOME);//����ԭ��TOMCAT_HOME��ֵ
  RegWriteStringValue(HKEY_LOCAL_MACHINE, 'SOFTWARE\COOLINK', 'oldTOMCAT_HOME', oldTOMCAT_HOME);

  //����JAVA_HOME
  javaHome := ExpandConstant('{app}\jdk1.6');
  RegWriteStringValue(HKEY_LOCAL_MACHINE, 'SYSTEM\CurrentControlSet\Control\Session Manager\Environment', 'JAVA_HOME', javaHome);
  //����CLASSPATH
  classPath := '%JAVA_HOME%\lib\tools.jar;%JAVA_HOME%\lib\dt.jar';
  RegWriteStringValue(HKEY_LOCAL_MACHINE, 'SYSTEM\CurrentControlSet\Control\Session Manager\Environment', 'CLASSPATH', classPath);
  //����Path
  if RegQueryStringValue(HKEY_LOCAL_MACHINE, 'SYSTEM\CurrentControlSet\Control\Session Manager\Environment', 'Path', path) then begin
    path := ExpandConstant('{app}\jdk1.6\bin;') + path;
  end
  else begin
    path := ExpandConstant('{app}\jdk1.6\bin');
  end;
  RegWriteStringValue(HKEY_LOCAL_MACHINE, 'SYSTEM\CurrentControlSet\Control\Session Manager\Environment', 'Path', path);
  //����TOMCAT_HOME
  tomcatHome := ExpandConstant('{app}\apache-tomcat-6.0.18');
  RegWriteStringValue(HKEY_LOCAL_MACHINE, 'SYSTEM\CurrentControlSet\Control\Session Manager\Environment', 'TOMCAT_HOME', tomcatHome);
end;



procedure ClearEnvironment;
{ж��ʱʱ�����������}
var
  path,tomcatHome : String;
  Position : Integer;
  oldJAVAHOME,oldCLASSPATH,oldTOMCAT_HOME:	String;
begin
  RegQueryStringValue(HKEY_LOCAL_MACHINE, 'SOFTWARE\COOLINK', 'oldJAVAHOME', oldJAVAHOME);
  RegWriteStringValue(HKEY_LOCAL_MACHINE, 'SYSTEM\CurrentControlSet\Control\Session Manager\Environment', 'JAVA_HOME', oldJAVAHOME);
  RegQueryStringValue(HKEY_LOCAL_MACHINE, 'SOFTWARE\COOLINK', 'oldCLASSPATH', oldCLASSPATH);
  RegWriteStringValue(HKEY_LOCAL_MACHINE, 'SYSTEM\CurrentControlSet\Control\Session Manager\Environment', 'CLASSPATH', oldCLASSPATH);
  if RegQueryStringValue(HKEY_LOCAL_MACHINE, 'SYSTEM\CurrentControlSet\Control\Session Manager\Environment', 'Path', path) then begin
    Position := Pos(ExpandConstant('{app}\jdk1.6\bin;'),path);
    if Position = 1 then begin
      path := Copy(path,Length(ExpandConstant('{app}\jdk1.6\bin;'))+1,Length(path));
    end;
    RegWriteStringValue(HKEY_LOCAL_MACHINE, 'SYSTEM\CurrentControlSet\Control\Session Manager\Environment', 'Path', path);
  end;
  RegQueryStringValue(HKEY_LOCAL_MACHINE, 'SOFTWARE\COOLINK', 'oldTOMCAT_HOME', oldTOMCAT_HOME);
  RegWriteStringValue(HKEY_LOCAL_MACHINE, 'SYSTEM\CurrentControlSet\Control\Session Manager\Environment', 'TOMCAT_HOME', oldTOMCAT_HOME);
end;



{//////////////////////////////////////////////////////////////////////////////////////}

{�������дNextButtonClick�����õ��Ĺ��ܺ���}

procedure setRegValue();
{��ע�����д��Coolink����װ��Ϣ}
var
  versionInfo: TStringList;
begin
    RegWriteStringValue(HKEY_LOCAL_MACHINE, 'SOFTWARE\COOLINK', 'domain', Trim(DomainEdit.Text));
    RegWriteStringValue(HKEY_LOCAL_MACHINE, 'SOFTWARE\COOLINK', 'sn', installCDKeyEdit1.Text+'-'+installCDKeyEdit2.Text+'-'+installCDKeyEdit3.Text+'-'+installCDKeyEdit4.Text);
    RegWriteStringValue(HKEY_LOCAL_MACHINE, 'SOFTWARE\COOLINK', 'installedDate', GetDateTimeString('dd/mm/yyyy hh:nn:ss', '-', ':'));
    try
      versionInfo := TStringList.Create;
      if FileExists(ExpandConstant('{app}\version.txt')) then begin
        versionInfo.LoadFromFile(ExpandConstant('{app}\version.txt'));
        RegWriteStringValue(HKEY_LOCAL_MACHINE, 'SOFTWARE\COOLINK', 'version', versionInfo[0]);
      end;
    finally
      versionInfo.Free;
    end;
    RegWriteStringValue(HKEY_LOCAL_MACHINE, 'SOFTWARE\COOLINK', 'path', ExpandConstant('{app}'));

    //�������ݿ��������Ϣ���������������ʹ��
    RegWriteStringValue(HKEY_LOCAL_MACHINE, 'SOFTWARE\COOLINK', 'DBSystemPW', DBAEdit.Text);   //�������ݿ�system�û�������
    RegWriteStringValue(HKEY_LOCAL_MACHINE, 'SOFTWARE\COOLINK', 'DBSID', Trim(DBServiceNameEdit.Text));    //�������ݿ������SID
    RegWriteStringValue(HKEY_LOCAL_MACHINE, 'SOFTWARE\COOLINK', 'newDBName', Trim(UsernameEdit.Text));     //���������ʹ�õ����ݿ��ռ���
    RegWriteStringValue(HKEY_LOCAL_MACHINE, 'SOFTWARE\COOLINK', 'newDBPW', PasswordEdit.Text);      //���������ʹ�õ����ݿ�����
end;



function checkWinVersion(): Boolean;
{������ϵͳ�汾����ΪWindows 2003 �� XP�򷵻�true�����򷵻�false}
var
  Version: TWindowsVersion;
begin
  GetWindowsVersionEx(Version);
  if Version.NTPlatform and (Version.Major = 5) and ((Version.Minor = 1) or (Version.Minor = 2)) then begin
    Result := True;
  end
  else begin
    MsgBox('�˰�װ����ֻ֧��Windows 2003 �� XP �汾!', mbError, MB_OK);
		Result := false;
  end;
end;


function checkCoolinkInstalled(): Boolean;
{����Ƿ��Ѿ���װCoolink�����Ѿ���װ�򷵻�true�����򷵻�false}
var
  domainStr: String;
begin
  if RegQueryStringValue(HKEY_LOCAL_MACHINE, 'SOFTWARE\COOLINK','domain', domainStr) then begin
    MsgBox('�������Ѿ���װ��Coolink����', mbError, MB_OK);
		Result := false;
  end
  else begin
    Result := True;
  end;
end;




function checkPort(): Boolean;
{���80�˿��Ƿ��Ѿ���ռ�ã���δ��ռ���򷵻�true�����򷵻�false}
var
  portInfos,AStrings: TStringList;
  ErrorCode,i,j,Acount: Integer;
  thePID: String;
begin
  //ͨ����������������ȡ������˿�80��صĽ���
  ShellExec('open' , ExpandConstant('{cmd}'), '/c netstat -aon|findstr ":80" >c:/tempInfo.txt', '',SW_HIDE, ewWaitUntilTerminated, ErrorCode);
	portInfos := TStringList.Create;
	try
    portInfos.LoadFromFile('c:/tempInfo.txt');
    for i:=0 to portInfos.count-1 do begin
      Acount := Pos(':80',portInfos[i]);
      if (Acount < 30) and (Copy(portInfos[i],Acount+3,1) = ' ') then begin
        thePID := Copy(portInfos[i],Length(portInfos[i])-3,4)
        //ͨ��������������ݽ���ID����ȡռ��80�˿ڵĽ�������
        ShellExec('open' , ExpandConstant('{cmd}'), '/c tasklist /fi "PID eq '+thePID+'" >c:/tempInfo.txt', '',SW_HIDE, ewWaitUntilTerminated, ErrorCode);
        break;
      end;
    end;
  finally
    portInfos.Free;
  end;
  AStrings := TStringList.Create;
  try
    AStrings.LoadFromFile('c:/tempInfo.txt');
    if AStrings.count>3 then begin
      if Length(AStrings[0]) < 1 then begin
        Acount := Pos(' ',AStrings[3]);
        MsgBox('������80�˿��Ѿ������� "'+Copy(AStrings[3],0,Acount)+'"��ռ��,���ȹرմ˽����ټ�����װ!', mbError, MB_OK);
        Result := false;
      end
      else begin
        Result := True;
      end;
    end
    else begin
      Result := True;
    end;
  finally
    AStrings.Free;
    ShellExec('open' , ExpandConstant('{cmd}'), '/c del "c:/tempInfo.txt"', '',SW_HIDE, ewWaitUntilTerminated, ErrorCode);
  end;
end;




function checkOraInstalled(): Boolean;
{����Ƿ��Ѿ���װ��Oracle�ͻ��ˣ����Ѿ���װ�򷵻�true�����򷵻�false}
begin
  if RegValueExists(HKEY_LOCAL_MACHINE, 'SOFTWARE\ORACLE', 'inst_loc') then begin
    Result := True;
  end
  else begin
    MsgBox('�����ڱ����������ϰ�װOracle�ͻ��ˣ�', mbError, MB_OK);
    Result := false;
  end;
end;



function checkOraVersion(DBAPassword, DBServiceName, newDBName: String; isCreateTab: Boolean): Boolean;
{������ݿ��������Oracle�汾,���Ҽ���û���Ҫ�����������ݿ��Ƿ���ڣ���Ϊ9i���ϰ汾���������ݿⲻ�����򷵻�true�����򷵻�false}
var
  versionBat,versionSQL,versionInfo,dbExistInfo: TStringList;
  ErrorCode: Integer;
  dbVersion,newDBCountSr: String;
begin
  //�����鿴Oracle�汾���������ļ���SQL�ļ�
  ShellExec('open' , ExpandConstant('{cmd}'), '/c netstat -aon|findstr ":123456" >c:/oracleVersion.bat', '',SW_HIDE, ewWaitUntilTerminated, ErrorCode);
  ShellExec('open' , ExpandConstant('{cmd}'), '/c netstat -aon|findstr ":123456" >c:/oracleVersion.sql', '',SW_HIDE, ewWaitUntilTerminated, ErrorCode);
  try
    versionBat := TStringList.Create;
    versionSQL := TStringList.Create;
    versionBat.Add('sqlplus -L "system/'+DBAPassword+'@'+DBServiceName+'" @oracleVersion.sql || exit');
    versionBat.Add('exit');
    versionBat.SaveToFile('c:/oracleVersion.bat');
    //�ж�Oracle�汾��SQL�ű�
    versionSQL.Add('spool c:\version.log;');
    versionSQL.Add('select version from v$instance;');
    versionSQL.Add('spool off;');
    //�ж������ݿ��Ƿ��Ѿ����ڵ�SQL�ű�
    versionSQL.Add('spool c:\tab.log;');
    versionSQL.Add('select sum(no) from (');
    versionSQL.Add('select  count(*)  no  from dba_tablespaces where lower(tablespace_name)='''+newDBName+'''');
    versionSQL.Add('union all');
    versionSQL.Add('select  count(*)  no  from dba_users where lower(username) ='''+newDBName+''');');
    versionSQL.Add('spool off;');
    //ͨ�����ݿ��������������orcl81��ȡ���ݿ�������з�����SID
    versionSQL.Add('spool c:\orcl.log;');
    versionSQL.Add('select  instance_name  from v$instance;');
    versionSQL.Add('spool off;');
    //
    versionSQL.Add('spool c:\oraFilePath.log;');
    versionSQL.Add('select  SUBSTR(FILE_NAME,1,INSTR(FILE_NAME,'''+'\'+''',-1)-1) from dba_data_files  where tablespace_name ='''+'SYSTEM'+''' AND ROWNUM=1;');
    versionSQL.Add('spool off;');
    //
    versionSQL.Add('exit;');
    versionSQL.SaveToFile('c:/oracleVersion.sql');
  finally
    versionBat.Free;
    versionSQL.Free;
  end;
  //ִ���������ļ���ȡOracle������Ϣ�Ͱ汾��Ϣ
  ShellExec('open', ExpandConstant('c:/oracleVersion.bat'), '', '', SW_HIDE, ewWaitUntilTerminated, ErrorCode);
  try
    versionInfo := TStringList.Create;
    if FileExists('c:/version.log') then begin
      versionInfo.LoadFromFile('c:/version.log');
      if versionInfo.count=5 then begin
        dbVersion := versionInfo[3];
        //֧��9.2.0.1.0�����ϰ汾
        if (StrToInt(Copy(dbVersion,7,1))>=1) or ((StrToInt(Copy(dbVersion,1,1))=1)) then begin
          //���û���ѡ�ˡ���װ�����ݿ⡱�ж������ݿ��Ƿ��Ѿ�����
          if isCreateTab then begin
            dbExistInfo := TStringList.Create;
            dbExistInfo.LoadFromFile('c:/tab.log');
            newDBCountSr := dbExistInfo[3];
            if StrToInt(Trim(newDBCountSr))>0 then begin
              MsgBox('�����ݿ��Ѿ����ڣ����������������ݿ��û���!', mbError, MB_OK);
              Result := false;
            end
            else begin
              Result := True;
            end;
            dbExistInfo.Free;
          end
          else begin
            Result := True;
          end;
        end
        else begin
          MsgBox('���ݿ�汾���ͣ�������Oracle 9.2.0.1.0���ϰ汾!', mbError, MB_OK);
          Result := false;
        end;
      end
      else begin
        MsgBox('���ݿ������������ȼ�����ݿ�����״̬!', mbError, MB_OK);
        Result := false;
      end;
      ShellExec('open' , ExpandConstant('{cmd}'), '/c del "c:/version.log"', '',SW_HIDE, ewWaitUntilTerminated, ErrorCode);
      ShellExec('open' , ExpandConstant('{cmd}'), '/c del "c:/tab.log"', '',SW_HIDE, ewWaitUntilTerminated, ErrorCode);
    end
    else begin
      MsgBox('���ݿ����ӳ�������������!', mbError, MB_OK);
      Result := false;
    end;
  finally
    versionInfo.Free;
  end;
  ShellExec('open' , ExpandConstant('{cmd}'), '/c del "c:/oracleVersion.bat"', '',SW_HIDE, ewWaitUntilTerminated, ErrorCode);
  ShellExec('open' , ExpandConstant('{cmd}'), '/c del "c:/oracleVersion.sql"', '',SW_HIDE, ewWaitUntilTerminated, ErrorCode);
end;



Function EncrypKey (Src:String; Key:String):string;
{�����㷨�����ɰ�װ��������������У����CDKey}
{�˰�װ��������δʹ��}
var
  idx :integer;
  KeyLen :Integer;
  KeyPos :Integer;
  offset :Integer;
  dest :string;
  SrcPos :Integer;
  SrcAsc :Integer;
  TmpSrcAsc :Integer;
  Range :Integer;

begin
    KeyLen:=Length(Key);
    if KeyLen = 0 then key:='Think Space';
    KeyPos:=0;
    SrcPos:=0;
    SrcAsc:=0;
    Range:=256;

    offset:=Random(Range);
    dest:=format('%1.2x',[offset]);
    for SrcPos := 1 to Length(Src) do
    begin
      SrcAsc:=(Ord(Src[SrcPos]) + offset) MOD 255;
      if KeyPos < KeyLen then KeyPos:= KeyPos + 1 else KeyPos:=1;
      SrcAsc:= SrcAsc xor Ord(Key[KeyPos]);
      dest:=dest + format('%1.2x',[SrcAsc]);
      offset:=SrcAsc;
    end;
    Result:=Dest;
end;



function checkCDKey(domainStr ,key ,inputCDKey: String): Boolean;
{�������İ�װУ����CDKey������ȷ�򷵻�true�����򷵻�false}
var
  encrypStr : string;
begin
  encrypStr := Copy(GetMD5OfString(domainStr),1,16);
  if Uppercase(inputCDKey) = Uppercase(encrypStr) then begin
    Result := True;
  end
  else begin
    MsgBox('����������кŲ���ȷ�����������룡', mbError, MB_OK);
		Result := false;
  end;
end;

{NextButtonClick�����õ������к�������}
{//////////////////////////////////////////////////////////////////////////////////////}



procedure Replace(oldstring, newstring, inifile: String);
{���������inifile����ļ��е�oldstring��ȫ���滻��newstring}
var
  IniFileLines: TArrayOfString;
  i: Integer;
begin
  if FileExists(inifile) then begin
    LoadStringsFromFile(inifile, IniFileLines);
      for i:= 0 to GetArrayLength(IniFileLines)-1 do begin
        if (Pos(oldstring, IniFileLines[i]) > 0) then
          StringChange(IniFileLines[i], oldstring, newstring);
      end;
    SaveStringsToFile(inifile, IniFileLines, False);
  end;
{Replace��������}
end;



function getDBSID(): String;
{��ȡ���ݿ�������з�����SID}
var
  dbSIDInfo: TStringList;
  ErrorCode,spacePos: Integer;
  dbSIDSr: String;
begin
  try
    dbSIDInfo := TStringList.Create;
    if FileExists('c:/orcl.log') then begin
      dbSIDInfo.LoadFromFile('c:/orcl.log');
      if dbSIDInfo.count=5 then begin
        dbSIDSr := Trim(dbSIDInfo[3]);
        if dbSIDSr<>'' then begin
          Result := dbSIDSr;
        end
        else begin
          Result := 'undefinedSID';
        end;
      end
      else begin
        Result := 'undefinedSID';
      end;
      ShellExec('open' , ExpandConstant('{cmd}'), '/c del "c:/orcl.log"', '',SW_HIDE, ewWaitUntilTerminated, ErrorCode);
    end
    else begin
      Result := 'undefinedSID';
    end;
  finally
    dbSIDInfo.Free;
  end;
end;




function Dircopy(SourceFolderPath, DestinyFolderPath, Copytype: String):Boolean;
{�������ִ�и�SourceFolderPath·�����ļ���DestinyFolderPath}
{Copytype��2������, dir��files}
{dir ���ڸ��������ļ���}
{files ���ڸ��Ƶ����ļ�������*.xxx���͵ĸ���}
var
  ResultCode: Integer;
  Cmd: String;
begin
  //���ļ�·��תΪ����·��
  SourceFolderPath  := ExpandConstant('{app}') + SourceFolderPath;
  DestinyFolderPath := ExpandConstant('{app}') + DestinyFolderPath;

  case Copytype of

  'dir':
  //�ļ��и���
    begin
      //����Ŀ���ļ���
      if not DirExists(SourceFolderPath) then begin
        MsgBox(SourceFolderPath + '·�������ڡ�', mbInformation, mb_Ok);
        Result := false;
      end
      else begin
        if not ForceDirectories(DestinyFolderPath) then begin
          MsgBox(DestinyFolderPath + '�������ɹ���', mbInformation, mb_Ok);
          Result := false;
        end
        else begin
          //�����������ļ�
          Cmd := 'xcopy ' + SourceFolderPath + ' /E/Q/R/K/C/Y ' + DestinyFolderPath;
          SaveStringToFile(ExpandConstant('{app}\tempfile.bat'), #13#10 + Cmd + #13#10, True);
          //ִ�и����ļ�����
          if Exec(ExpandConstant('{app}\tempfile.bat'), '', '', SW_HIDE, ewWaitUntilTerminated, ResultCode) then begin
            if ResultCode = 0 then begin
              Result := true;
              end
            else if ResultCode = 1 then begin
              MsgBox('�ļ����Ʒ������������°�װ��', mbInformation, mb_Ok);
              Result := false;
            end
            else begin
              MsgBox('�ļ����Ʒ������������°�װ��', mbInformation, mb_Ok);
              Result := false;
            end;
          end;
        //ɾ���������ļ�
        DeleteFile(ExpandConstant('{app}\tempfile.bat'));
        end;
      end;
    end;

  'files':
  //*.txt���͵��ļ�����
    begin
      //�����������ļ�
      Cmd := 'xcopy ' + SourceFolderPath + ' /Q/R/K/C/Y ' + DestinyFolderPath;
      SaveStringToFile(ExpandConstant('{app}\tempfile.bat'), #13#10 + Cmd + #13#10, True);
      //ִ�и����ļ�����
      if Exec(ExpandConstant('{app}\tempfile.bat'), '', '', SW_HIDE, ewWaitUntilTerminated, ResultCode) then begin
        if ResultCode = 0 then begin
          Result := true;
          end
        else if ResultCode = 1 then begin
          MsgBox('�ļ����Ʒ������������°�װ��', mbInformation, mb_Ok);
          Result := false;
        end
        else begin
          MsgBox('�ļ����Ʒ������������°�װ��', mbInformation, mb_Ok);
          Result := false;
        end;
      end;
      //ɾ���������ļ�
      DeleteFile(ExpandConstant('{app}\tempfile.bat'));
    end;

  end;
end;



function getORAFilePath(): String;
var
  ORAFilePathInfo: TStringList;
  infoStr: String;
  ErrorCode: Integer;
begin
  if FileExists('c:/oraFilePath.log') then begin
    try
      ORAFilePathInfo := TStringList.Create;
      ORAFilePathInfo.LoadFromFile('c:/oraFilePath.log');
      infoStr := Trim(ORAFilePathInfo[3]);
      if Pos(':\', infoStr) <> 0 then begin
        Result := infoStr;
      end
      else begin
        Result := 'c:\';
      end;
    finally
      ORAFilePathInfo.Free;
    end;
    ShellExec('open' , ExpandConstant('{cmd}'), '/c del "c:/oraFilePath.log"', '',SW_HIDE, ewWaitUntilTerminated, ErrorCode);
  end
  else begin
    Result := 'c:\';
  end;
end;



procedure installTomcat;
{��Windowsϵͳ������ע��Tomcat����}
var
  ErrorCode: Integer;
  tomcatInstallStrs: TStringList;
begin
  try
    //������ʱ�������ļ������ڴ��ִ��ע�������������
    Replace('%JAVA_HOME%', ExpandConstant('{app}\jdk1.6'), ExpandConstant('{app}\apache-tomcat-6.0.18\bin\service.bat'));
    Replace('%theCATALINA_HOME%', ExpandConstant('{app}\apache-tomcat-6.0.18'), ExpandConstant('{app}\apache-tomcat-6.0.18\bin\service.bat'));
		ShellExec('open' , ExpandConstant('{cmd}'), '/c netstat -aon|findstr ":123456" >'+ExpandConstant('{app}\tempfile.bat'), '',SW_HIDE, ewWaitUntilTerminated, ErrorCode);
		tomcatInstallStrs := TStringList.Create;
    tomcatInstallStrs.Add('cd '+ExpandConstant('{app}\apache-tomcat-6.0.18\bin'));
    tomcatInstallStrs.Add('service install Coolink');
    tomcatInstallStrs.Add('exit');
    tomcatInstallStrs.SaveToFile(ExpandConstant('{app}\tempfile.bat'));
	finally
		tomcatInstallStrs.Free;
	end;
  //ִ�з���ע����������֮��ɾ����ʱ�������ļ�
  Exec(ExpandConstant('{app}\tempfile.bat'), '', '', SW_HIDE, ewWaitUntilTerminated, ErrorCode);
	DeleteFile(ExpandConstant('{app}\tempfile.bat'));
end;



procedure unInstallTomcat;
{ж�س���ʱ����Windowsϵͳ������ж��Tomcat����}
var
  ErrorCode: Integer;
  tomcatUnInstallStrs: TStringList;
begin
  try
    //������ʱ�������ļ������ڴ��ִ��ע�������������
		ShellExec('open' , ExpandConstant('{cmd}'), '/c netstat -aon|findstr ":123456" >'+ExpandConstant('{app}\tempfile.bat'), '',SW_HIDE, ewWaitUntilTerminated, ErrorCode);
		tomcatUnInstallStrs := TStringList.Create;
    tomcatUnInstallStrs.Add('cd '+ExpandConstant('{app}\apache-tomcat-6.0.18\bin'));
    tomcatUnInstallStrs.Add('service remove Coolink');
    tomcatUnInstallStrs.Add('exit');
    tomcatUnInstallStrs.SaveToFile(ExpandConstant('{app}\tempfile.bat'));
	finally
		tomcatUnInstallStrs.Free;
	end;
  //ִ�з���ж�ز��������֮��ɾ����ʱ�������ļ�
  Exec(ExpandConstant('{app}\tempfile.bat'), '', '', SW_HIDE, ewWaitUntilTerminated, ErrorCode);
	DeleteFile(ExpandConstant('{app}\tempfile.bat'));
end;


procedure CreateTheWizardPages;

	  begin
			Page := CreateCustomPage(wpLicense, '���ݿ�����', '�������ݿ�����');

			DBALabel := TNewStaticText.Create(Page);
      DBALabel.Caption := '���ݿ����Ա���룺';
      DBALabel.Parent := Page.Surface;

			DBAEdit := TPasswordEdit.Create(Page);
			//DBAEdit.Top := CheckBox.Top + CheckBox.Height + ScaleY(8);
			DBAEdit.Width := Page.SurfaceWidth div 2 - ScaleX(8);
			DBAEdit.Left := DBALabel.Width+ScaleX(8);
			DBAEdit.Text := '';
			DBAEdit.Parent := Page.Surface;


			DBServiceNameLabel := TNewStaticText.Create(Page);
			DBServiceNameLabel.Top := DBAEdit.Top + DBAEdit.Height + ScaleY(8);
      DBServiceNameLabel.Caption := '        ���ݿ��������';
      DBServiceNameLabel.Parent := Page.Surface;

			DBServiceNameEdit := TNewEdit.Create(Page);
			DBServiceNameEdit.Top := DBAEdit.Top + DBAEdit.Height + ScaleY(8);
			DBServiceNameEdit.Left := DBServiceNameLabel.Width+ScaleX(8);
			DBServiceNameEdit.Width := Page.SurfaceWidth div 2 - ScaleX(8);
			DBServiceNameEdit.Text := 'orcl';
			DBServiceNameEdit.Parent := Page.Surface;


			AddressLabel := TNewStaticText.Create(Page);
			AddressLabel.Top := DBServiceNameEdit.Top + DBServiceNameEdit.Height + ScaleY(8);
      AddressLabel.Caption := '���ݿ��������ַ��';
      AddressLabel.Parent := Page.Surface;

			AddressEdit := TNewEdit.Create(Page);
			AddressEdit.Top := DBServiceNameEdit.Top + DBServiceNameEdit.Height + ScaleY(8);
			AddressEdit.Left := AddressLabel.Width+ScaleX(8);
			AddressEdit.Width := Page.SurfaceWidth div 2 - ScaleX(8);
			AddressEdit.Text := '127.0.0.1';
			AddressEdit.Parent := Page.Surface;


			UsernameLabel := TNewStaticText.Create(Page);
			UsernameLabel.Top := AddressEdit.Top + AddressEdit.Height + ScaleY(8);
      UsernameLabel.Caption := '    �����ݿ��û�����';
      UsernameLabel.Parent := Page.Surface;

			UsernameEdit := TNewEdit.Create(Page);
			UsernameEdit.Top := AddressEdit.Top + AddressEdit.Height + ScaleY(8);
			UsernameEdit.Left := UsernameLabel.Width+ScaleX(8);
			UsernameEdit.Width := Page.SurfaceWidth div 2 - ScaleX(8);
			UsernameEdit.Text := 'coolink';
			UsernameEdit.Parent := Page.Surface;


			PasswordLabel := TNewStaticText.Create(Page);
			PasswordLabel.Top := UsernameEdit.Top + UsernameEdit.Height + ScaleY(8);
      PasswordLabel.Caption := '        �����ݿ����룺';
      PasswordLabel.Parent := Page.Surface;

			PasswordEdit := TPasswordEdit.Create(Page);
			PasswordEdit.Top := UsernameEdit.Top + UsernameEdit.Height + ScaleY(8);
			PasswordEdit.Left := PasswordLabel.Width+ScaleX(8);
			PasswordEdit.Width := Page.SurfaceWidth div 2 - ScaleX(8);
			PasswordEdit.Text := '';
			PasswordEdit.Parent := Page.Surface;


			SizeLabel := TNewStaticText.Create(Page);
			SizeLabel.Top := PasswordEdit.Top + PasswordEdit.Height + ScaleY(8);
      SizeLabel.Caption := '            ���ݿ��С��';
      SizeLabel.Parent := Page.Surface;

			SizeEdit := TNewEdit.Create(Page);
			SizeEdit.Top := PasswordEdit.Top + PasswordEdit.Height + ScaleY(8);
			SizeEdit.Left := SizeLabel.Width+ScaleX(8);
			SizeEdit.Width := Page.SurfaceWidth div 2 - ScaleX(8);
			SizeEdit.Text := '2048';
			SizeEdit.Parent := Page.Surface;

			UnitLabel := TNewStaticText.Create(Page);
			UnitLabel.Top := PasswordEdit.Top + PasswordEdit.Height + ScaleY(8);
			UnitLabel.Left := SizeLabel.Width+SizeEdit.Width+ScaleX(12);
      UnitLabel.Caption := 'M���ף�';
      UnitLabel.Parent := Page.Surface;


      PortLabel := TNewStaticText.Create(Page);
			PortLabel.Top := SizeEdit.Top + SizeEdit.Height + ScaleY(8);
      PortLabel.Caption := '            ���ݿ�˿ڣ�';
      PortLabel.Parent := Page.Surface;

			PortEdit := TNewEdit.Create(Page);
			PortEdit.Top := SizeEdit.Top + SizeEdit.Height + ScaleY(8);
			PortEdit.Left := PortLabel.Width+ScaleX(8);
			PortEdit.Width := Page.SurfaceWidth div 2 - ScaleX(8);
			PortEdit.Text := '1521';
			PortEdit.Parent := Page.Surface;


			DomainLabel := TNewStaticText.Create(Page);
			DomainLabel.Top := PortEdit.Top + PortEdit.Height + ScaleY(8);
      DomainLabel.Caption := '                ��վ������';
      DomainLabel.Parent := Page.Surface;

			DomainEdit := TNewEdit.Create(Page);
			DomainEdit.Top := PortEdit.Top + PortEdit.Height + ScaleY(8);
			DomainEdit.Left := DomainLabel.Width+ScaleX(8);
			DomainEdit.Width := Page.SurfaceWidth div 2 - ScaleX(8);
			DomainEdit.Text := 'www.coolink.cn';
			DomainEdit.Parent := Page.Surface;

			installDB := TCheckBox.Create(Page);
			installDB.Top := AddressEdit.Top + AddressEdit.Height + ScaleY(8);
			installDB.Left := UsernameLabel.Width+UsernameEdit.Width+ScaleX(16);
			installDB.Caption := '��װ�����ݿ�';
			installDB.Parent := Page.Surface;

			CDKeyPage := CreateCustomPage(Page.ID, '��װ��֤', '���밲װ���к�');


end;



procedure CreateTheCDKeyPages;
begin
  installCDKeyLabel := TNewStaticText.Create(CDKeyPage);
  installCDKeyLabel.Caption := '��װ���кţ�';
  installCDKeyLabel.Parent := CDKeyPage.Surface;
  installCDKeyLabel.Top := CDKeyPage.SurfaceHeight div 4 ;

  installCDKeyEdit1 := TNewEdit.Create(CDKeyPage);
  installCDKeyEdit1.Top := installCDKeyLabel.Top + installCDKeyLabel.Height + ScaleY(8);
  installCDKeyEdit1.Width := CDKeyPage.SurfaceWidth div 6 ;
  installCDKeyEdit1.MaxLength := 4;
  installCDKeyEdit1.Text := '';
  installCDKeyEdit1.Parent := CDKeyPage.Surface;

  CDKeySeparator1 := TNewStaticText.Create(CDKeyPage);
  CDKeySeparator1.Caption := '-';
  CDKeySeparator1.Font.Size := 20;
  CDKeySeparator1.Parent := CDKeyPage.Surface;
  CDKeySeparator1.Top := installCDKeyLabel.Top + installCDKeyLabel.Height + ScaleY(2);
  CDKeySeparator1.Left := installCDKeyEdit1.Left+installCDKeyEdit1.Width+ScaleX(8);

  installCDKeyEdit2 := TNewEdit.Create(CDKeyPage);
  installCDKeyEdit2.Top := installCDKeyLabel.Top + installCDKeyLabel.Height + ScaleY(8);
  installCDKeyEdit2.Left := CDKeySeparator1.Left+CDKeySeparator1.Width+ScaleX(8);
  installCDKeyEdit2.Width := CDKeyPage.SurfaceWidth div 6 ;
  installCDKeyEdit2.MaxLength := 4;
  installCDKeyEdit2.Text := '';
  installCDKeyEdit2.Parent := CDKeyPage.Surface;

  CDKeySeparator2 := TNewStaticText.Create(CDKeyPage);
  CDKeySeparator2.Caption := '-';
  CDKeySeparator2.Font.Size := 20;
  CDKeySeparator2.Parent := CDKeyPage.Surface;
  CDKeySeparator2.Top := installCDKeyLabel.Top + installCDKeyLabel.Height + ScaleY(2);
  CDKeySeparator2.Left := installCDKeyEdit2.Left+installCDKeyEdit2.Width+ScaleX(8);

  installCDKeyEdit3 := TNewEdit.Create(CDKeyPage);
  installCDKeyEdit3.Top := installCDKeyLabel.Top + installCDKeyLabel.Height + ScaleY(8);
  installCDKeyEdit3.Left := CDKeySeparator2.Left+CDKeySeparator2.Width+ScaleX(8);
  installCDKeyEdit3.Width := CDKeyPage.SurfaceWidth div 6 ;
  installCDKeyEdit3.MaxLength := 4;
  installCDKeyEdit3.Text := '';
  installCDKeyEdit3.Parent := CDKeyPage.Surface;

  CDKeySeparator3 := TNewStaticText.Create(CDKeyPage);
  CDKeySeparator3.Caption := '-';
  CDKeySeparator3.Font.Size := 20;
  CDKeySeparator3.Parent := CDKeyPage.Surface;
  CDKeySeparator3.Top := installCDKeyLabel.Top + installCDKeyLabel.Height + ScaleY(2);
  CDKeySeparator3.Left := installCDKeyEdit3.Left+installCDKeyEdit3.Width+ScaleX(8);

  installCDKeyEdit4 := TNewEdit.Create(CDKeyPage);
  installCDKeyEdit4.Top := installCDKeyLabel.Top + installCDKeyLabel.Height + ScaleY(8);
  installCDKeyEdit4.Left := CDKeySeparator3.Left+CDKeySeparator3.Width+ScaleX(8);
  installCDKeyEdit4.Width := CDKeyPage.SurfaceWidth div 6 ;
  installCDKeyEdit4.MaxLength := 4;
  installCDKeyEdit4.Text := '';
  installCDKeyEdit4.Parent := CDKeyPage.Surface;
end;



function NextButtonClick(CurPageID: Integer): Boolean;
begin
  case CurPageID of
    wpWelcome:
        begin
          Result := checkWinVersion() and checkCoolinkInstalled() and checkPort() and checkOraInstalled();
        end;
    Page.ID:
        begin
          if checkOraVersion(DBAEdit.Text, Trim(DBServiceNameEdit.Text), Trim(UsernameEdit.Text), installDB.Checked) then begin
          //if 1 = 1 then begin
            CreateTheCDKeyPages;
            Result := true;
          end
          else begin
            Result := false;
          end;
        end;
    CDKeyPage.ID:
        begin
          Result := checkCDKey(DomainEdit.Text ,'Coolink' ,installCDKeyEdit1.Text+installCDKeyEdit2.Text+installCDKeyEdit3.Text+installCDKeyEdit4.Text);
        end;
  else
    Result := True;
  end;
end;



procedure CurUninstallStepChanged(CurUninstallStep: TUninstallStep);
var
  ErrorCode: Integer;
begin
  if CurUninstallStep = usUninstall then begin //ִ��ж��ǰ��ж��ϵͳ�����е�Tomcat����
    unInstallTomcat;
  end;
	if CurUninstallStep = usPostUninstall then begin //ִ��ж�غ����ע����й��ڱ��������Ϣ
    ClearEnvironment;
    RegDeleteKeyIncludingSubkeys(HKEY_LOCAL_MACHINE, 'SOFTWARE\COOLINK');
  end;
end;

function NeedRestart(): Boolean;
begin
		Result := False;
end;


procedure CurStepChanged(CurStep: TSetupStep);
var
  fileName,fileNameNew,perlDir,perlPath,ORAFilePath,ORAFileName: String;
  ErrorCode: Integer;
begin
  if CurStep = ssPostInstall then begin
    //�ж��Ƿ񸲸�templatesĿ¼������һ�ΰ�װ��ֱ�����ɴ�Ŀ¼�����Ѵ��ڴ�Ŀ¼��ѯ���û��Ƿ񸲸�
    if not DirExists(ExpandConstant('{app}\apache-tomcat-6.0.18\webapps\template001')) then begin
      Dircopy('\templates', '\apache-tomcat-6.0.18\webapps\', 'dir');
    end
    else begin
      if MsgBox('�Ƿ�Ҫ�������е�template001Ŀ ¼��', mbConfirmation, MB_YESNO) = IDYES then begin
        Dircopy('\templates', '\apache-tomcat-6.0.18\webapps\', 'dir');
      end;
    end;
    DelTree(ExpandConstant('{app}\templates'),true,true,true);

    //�޸İ�װ���ݿ���������ļ�dbinstall.bat
    fileName := ExpandConstant('{app}\dbinstall.bat');
    Replace('%SystemPassword%', DBAEdit.Text, fileName);
    Replace('%ServiceName%', Trim(DBServiceNameEdit.Text), fileName);
    Replace('%username%', Trim(UsernameEdit.Text), fileName);
    Replace('%password%', PasswordEdit.Text, fileName);

    //�޸����ݿ�ű��ļ�exec.sql
    fileName := ExpandConstant('{app}\exec.sql');
    Replace('%Systempassword%', DBAEdit.Text, fileName);
    ORAFilePath := getORAFilePath()+'\';
    ORAFileName := Trim(UsernameEdit.Text)+IntToStr(Random(99999));
    while FileExists(ORAFilePath+ORAFileName+'.ORA') do begin   //���Ҫ������ORA�ļ��Ѵ��ڣ�����������һ���ļ�����ֱ�����ظ�Ϊֹ
      ORAFileName := Trim(UsernameEdit.Text)+IntToStr(Random(99999));
    end;
    Replace('%oraFileName%', ORAFilePath+ORAFileName+'.ORA', fileName);
    Replace('%size%', Trim(SizeEdit.Text), fileName);
    Replace('%serviceName%', Trim(DBServiceNameEdit.Text), fileName);
    Replace('%username%', Trim(UsernameEdit.Text), fileName);
    Replace('%password%', PasswordEdit.Text, fileName);
    Replace('%localhost%', Trim(DomainEdit.Text), fileName);

    //����û���ѡ�ˡ���װ�����ݿ⡱����ִ�����ݿⰲװ�ű�
    if installDB.Checked then begin
      ShellExec('open', ExpandConstant('{app}\dbinstall.bat'), '', '', SW_SHOW, ewWaitUntilTerminated, ErrorCode);
    end;

    //���Ʋ�����cgi\awstats.domain.conf�ļ��е�log��־·��
    fileName := ExpandConstant('{app}\apache-tomcat-6.0.18\webapps\monitor\WEB-INF\cgi\awstats.conf');
    fileNameNew := ExpandConstant('{app}\apache-tomcat-6.0.18\webapps\monitor\WEB-INF\cgi\awstats.'+ Trim(DomainEdit.Text) +'.conf');
    FileCopy(fileName,fileNameNew,false);
    Replace('%localhost%', Trim(DomainEdit.Text), fileNameNew);
    Replace('%TomcatHome%', ExpandConstant('{app}\apache-tomcat-6.0.18'), fileNameNew);

    //�޸������ļ�config.xml�е����ݿ�����
    //fileName := ExpandConstant('{app}\apache-tomcat-6.0.18\webapps\coolink\WEB-INF\config.xml');
    //Replace('%DBAddress%', Trim(AddressEdit.Text), fileName);
    //Replace('%DBPort%', Trim(PortEdit.Text), fileName);
    //Replace('%DBServiceName%', getDBSID(), fileName);
    //Replace('%username%', Trim(UsernameEdit.Text), fileName);
    //Replace('%password%', PasswordEdit.Text, fileName);

    //�޸�tomcat��server.xml�ļ�������
    fileName := ExpandConstant('{app}\apache-tomcat-6.0.18\conf\server.xml');
    //Replace('%coolinkPath%', ExpandConstant('{app}\apache-tomcat-6.0.18\webapps\coolink'), fileName);
    Replace('%DBAddress%', Trim(AddressEdit.Text), fileName);
    Replace('%DBPort%', Trim(PortEdit.Text), fileName);
    Replace('%DBServiceName%', getDBSID(), fileName);
    Replace('%username%', Trim(UsernameEdit.Text), fileName);
    Replace('%password%', PasswordEdit.Text, fileName);

    //�޸İ�װPerl������������ļ�perlInstall.bat
    fileName := ExpandConstant('{app}\perlInstall.bat');
    Replace('%path%', ExpandConstant('{app}'), fileName);

    //�������й���Ϣд��ע���
    setRegValue();

    //���û�������
		SetEnvironment;

		//��tomcat����ע���ϵͳ����
    installTomcat;

    //�����������δ��װPerl������ʾ��װ
    if not RegQueryStringValue(HKEY_LOCAL_MACHINE, 'SOFTWARE\Perl', 'BinDir', perlDir) then begin
      ShellExec('open', ExpandConstant('{app}\perlInstall.bat'), '', '', SW_HIDE, ewWaitUntilTerminated, ErrorCode);
      RegQueryStringValue(HKEY_LOCAL_MACHINE, 'SYSTEM\CurrentControlSet\Control\Session Manager\Environment', 'Path', perlPath);
      perlPath := perlPath + ';C:\Perl\bin';
      RegWriteStringValue(HKEY_LOCAL_MACHINE, 'SYSTEM\CurrentControlSet\Control\Session Manager\Environment', 'Path', perlPath);
    end;
  end;

  if CurStep = ssDone then begin
    //�����Ҫ���������ݿ⣬���������ݿⴴ��֮������tomcat���񣬷���ֱ������tomcat����
    if ((installDB.Checked) and (FileExists(ExpandConstant('{app}\dbInstalling.log'))))then begin
      while not FileExists(ExpandConstant('{app}\dbInstalled.log')) do begin
        Sleep(5000);
      end;
      ShellExec('open' , ExpandConstant('{cmd}'), '/c Net start "Coolink"', '',SW_HIDE, ewWaitUntilTerminated, ErrorCode);
      ShellExec('open' , ExpandConstant('{cmd}'), '/c del "'+ExpandConstant('{app}\dbInstalling.log')+'"', '',SW_HIDE, ewWaitUntilTerminated, ErrorCode);
      ShellExec('open' , ExpandConstant('{cmd}'), '/c del "'+ExpandConstant('{app}\dbInstalled.log')+'"', '',SW_HIDE, ewWaitUntilTerminated, ErrorCode);
    end
    else begin
      ShellExec('open' , ExpandConstant('{cmd}'), '/c Net start "Coolink"', '',SW_HIDE, ewWaitUntilTerminated, ErrorCode);
    end;
    ShellExec('open' , ExpandConstant('{cmd}'), '/c del "'+ExpandConstant('{app}\coolink_database1.0.1.sql')+'"', '',SW_HIDE, ewWaitUntilTerminated, ErrorCode);
    ShellExec('open' , ExpandConstant('{cmd}'), '/c del "'+ExpandConstant('{app}\dbinstall.bat')+'"', '',SW_HIDE, ewWaitUntilTerminated, ErrorCode);
    ShellExec('open' , ExpandConstant('{cmd}'), '/c del "'+ExpandConstant('{app}\exec.sql')+'"', '',SW_HIDE, ewWaitUntilTerminated, ErrorCode);
    //ShellExec('open' , ExpandConstant('{cmd}'), '/c del "'+ExpandConstant('{app}\data.dmp')+'"', '',SW_HIDE, ewWaitUntilTerminated, ErrorCode);
    ShellExec('open' , ExpandConstant('{cmd}'), '/c del "'+ExpandConstant('{app}\log.log')+'"', '',SW_HIDE, ewWaitUntilTerminated, ErrorCode);
    ShellExec('open' , ExpandConstant('{cmd}'), '/c del "'+ExpandConstant('{app}\perlInstall.bat')+'"', '',SW_HIDE, ewWaitUntilTerminated, ErrorCode);

    //tomcat�������֮��򿪷���ҳ��
    ShellExec('open', 'http://localhost/ide/cms', '', '', SW_HIDE, ewNoWait, ErrorCode);
  end;
end;



procedure InitializeWizard();

begin
  CreateTheWizardPages;
end;
