; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "COPASI"
#define MyAppVersion "0.0.0"
#define MyAppPublisher "copasi.org"
#define MyAppURL "http://www.copasi.org/"
#define MyAppExeName "bin\CopasiUI.exe"
#define MyBuild "0"
#define MyAppId "{{00000000-0000-0000-0000-000000000000}"
#define MyWorkDir "C:\cygwin\home\shoops\environment\COPASI\InnoSetup"
#define MyStageDir "C:\cygwin\home\shoops\environment\setup\package"

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppID={#MyAppId}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
ChangesAssociations=true
ChangesEnvironment=true
DefaultDirName={code:DefDirRoot}\{#MyAppPublisher}\{#MyAppName} {#MyAppVersion}
DefaultGroupName={#MyAppName} {#MyAppVersion}
OutputDir={#MyWorkDir}
OutputBaseFilename=COPASI-{#MyAppVersion}-Windows
SetupIconFile={#MyWorkDir}\addremov.ico
Compression=lzma/Ultra
SolidCompression=true
InternalCompressLevel=Ultra
SignedUninstaller=false
VersionInfoVersion={#MyAppVersion}.0
ShowLanguageDialog=no
UninstallDisplayIcon={app}\share\copasi\icons\Copasi.ico
UninstallDisplayName={#MyAppName} {#MyAppVersion}
PrivilegesRequired=none
VersionInfoCompany=copasi.org
ArchitecturesAllowed=x86 x64
ArchitecturesInstallIn64BitMode=x64

[Languages]
Name: english; MessagesFile: compiler:Default.isl

[Tasks]
Name: desktopicon; Description: {cm:CreateDesktopIcon}; GroupDescription: {cm:AdditionalIcons}; Flags: unchecked
Name: quicklaunchicon; Description: {cm:CreateQuickLaunchIcon}; GroupDescription: {cm:AdditionalIcons}; Flags: unchecked; OnlyBelowVersion: 0,6.1

[Files]
; NOTE: Don't use "Flags: ignoreversion" on any shared system files
; 32 bit Executables and DLLs 
Source: {#MyStageDir}\bin\32\CopasiSE.exe; DestDir: {app}\bin; Check: IsWin32();
Source: {#MyStageDir}\bin\32\CopasiUI.exe; DestDir: {app}\bin; Check: IsWin32();
Source: {#MyStageDir}\bin\32\qt.conf; DestDir: {app}\bin; Check: IsWin32();
; Source: {#MyStageDir}\bin\32\libmmd.dll; DestDir: {app}\bin; Check: IsWin32(); 
; Source: {#MyStageDir}\bin\32\svml_dispmd.dll; DestDir: {app}\bin; Check: IsWin32(); 
Source: {#MyStageDir}\bin\32\Qt5Core.dll; DestDir: {app}\bin; Check: IsWin32();
Source: {#MyStageDir}\bin\32\Qt5DataVisualization.dll; DestDir: {app}\bin; Check: IsWin32();
Source: {#MyStageDir}\bin\32\Qt5Gui.dll; DestDir: {app}\bin; Check: IsWin32();
Source: {#MyStageDir}\bin\32\Qt5Network.dll; DestDir: {app}\bin; Check: IsWin32();
Source: {#MyStageDir}\bin\32\Qt5OpenGL.dll; DestDir: {app}\bin; Check: IsWin32();
Source: {#MyStageDir}\bin\32\Qt5PrintSupport.dll; DestDir: {app}\bin; Check: IsWin32();
Source: {#MyStageDir}\bin\32\Qt5Svg.dll; DestDir: {app}\bin; Check: IsWin32();
Source: {#MyStageDir}\bin\32\Qt5Widgets.dll; DestDir: {app}\bin; Check: IsWin32();
Source: {#MyStageDir}\bin\32\Qt5Xml.dll; DestDir: {app}\bin; Check: IsWin32();
Source: {#MyStageDir}\bin\32\d3dcompiler_47.dll; DestDir: {app}\bin; Check: IsWin32();
Source: {#MyStageDir}\bin\32\libEGL.dll; DestDir: {app}\bin; Check: IsWin32();
Source: {#MyStageDir}\bin\32\libGLESV2.dll; DestDir: {app}\bin; Check: IsWin32();
Source: {#MyStageDir}\bin\32\opengl32sw.dll; DestDir: {app}\bin; Check: IsWin32();
Source: {#MyStageDir}\bin\32\libeay32.dll; DestDir: {app}\bin; Check: IsWin32();
Source: {#MyStageDir}\bin\32\ssleay32.dll; DestDir: {app}\bin; Check: IsWin32();
Source: {#MyStageDir}\bin\32\bearer\qgenericbearer.dll; DestDir: {app}\bin\bearer; Check: IsWin32();
Source: {#MyStageDir}\bin\32\iconengines\qsvgicon.dll; DestDir: {app}\bin\iconengines; Check: IsWin32();
Source: {#MyStageDir}\bin\32\imageformats\qgif.dll; DestDir: {app}\bin\imageformats; Check: IsWin32();
Source: {#MyStageDir}\bin\32\imageformats\qicns.dll; DestDir: {app}\bin\imageformats; Check: IsWin32();
Source: {#MyStageDir}\bin\32\imageformats\qico.dll; DestDir: {app}\bin\imageformats; Check: IsWin32();
Source: {#MyStageDir}\bin\32\imageformats\qjpeg.dll; DestDir: {app}\bin\imageformats; Check: IsWin32();
Source: {#MyStageDir}\bin\32\imageformats\qsvg.dll; DestDir: {app}\bin\imageformats; Check: IsWin32();
Source: {#MyStageDir}\bin\32\imageformats\qtga.dll; DestDir: {app}\bin\imageformats; Check: IsWin32();
Source: {#MyStageDir}\bin\32\imageformats\qtiff.dll; DestDir: {app}\bin\imageformats; Check: IsWin32();
Source: {#MyStageDir}\bin\32\imageformats\qwbmp.dll; DestDir: {app}\bin\imageformats; Check: IsWin32();
Source: {#MyStageDir}\bin\32\imageformats\qwebp.dll; DestDir: {app}\bin\imageformats; Check: IsWin32();
Source: {#MyStageDir}\bin\32\platforms\qwindows.dll; DestDir: {app}\bin\platforms; Check: IsWin32();
Source: {#MyStageDir}\bin\32\printsupport\windowsprintersupport.dll; DestDir: {app}\bin\printsupport; Check: IsWin32();
Source: {#MyStageDir}\bin\32\vcruntime140.dll; DestDir: {app}\bin; Check: InstallUserRuntime32(); 
Source: {#MyStageDir}\bin\32\msvcp140.dll; DestDir: {app}\bin; Check: InstallUserRuntime32(); 

; 64 bit Executables and DLLs 
Source: {#MyStageDir}\bin\64\CopasiSE.exe; DestDir: {app}\bin; Check: IsWin64();
Source: {#MyStageDir}\bin\64\CopasiUI.exe; DestDir: {app}\bin; Check: IsWin64();
Source: {#MyStageDir}\bin\64\qt.conf; DestDir: {app}\bin; Check: IsWin64();
; Source: {#MyStageDir}\bin\64\libmmd.dll; DestDir: {app}\bin; Check: IsWin64(); 
; Source: {#MyStageDir}\bin\64\svml_dispmd.dll; DestDir: {app}\bin; Check: IsWin64(); 
Source: {#MyStageDir}\bin\64\Qt5Core.dll; DestDir: {app}\bin; Check: IsWin64();
Source: {#MyStageDir}\bin\64\Qt5DataVisualization.dll; DestDir: {app}\bin; Check: IsWin64();
Source: {#MyStageDir}\bin\64\Qt5Gui.dll; DestDir: {app}\bin; Check: IsWin64();
Source: {#MyStageDir}\bin\64\Qt5Network.dll; DestDir: {app}\bin; Check: IsWin64();
Source: {#MyStageDir}\bin\64\Qt5OpenGL.dll; DestDir: {app}\bin; Check: IsWin64();
Source: {#MyStageDir}\bin\64\Qt5PrintSupport.dll; DestDir: {app}\bin; Check: IsWin64();
Source: {#MyStageDir}\bin\64\Qt5Svg.dll; DestDir: {app}\bin; Check: IsWin64();
Source: {#MyStageDir}\bin\64\Qt5Widgets.dll; DestDir: {app}\bin; Check: IsWin64();
Source: {#MyStageDir}\bin\64\Qt5Xml.dll; DestDir: {app}\bin; Check: IsWin64();
Source: {#MyStageDir}\bin\64\d3dcompiler_47.dll; DestDir: {app}\bin; Check: IsWin64();
Source: {#MyStageDir}\bin\64\libEGL.dll; DestDir: {app}\bin; Check: IsWin64();
Source: {#MyStageDir}\bin\64\libGLESV2.dll; DestDir: {app}\bin; Check: IsWin64();
Source: {#MyStageDir}\bin\64\opengl32sw.dll; DestDir: {app}\bin; Check: IsWin64();
Source: {#MyStageDir}\bin\64\libeay32.dll; DestDir: {app}\bin; Check: IsWin64();
Source: {#MyStageDir}\bin\64\ssleay32.dll; DestDir: {app}\bin; Check: IsWin64();
Source: {#MyStageDir}\bin\64\bearer\qgenericbearer.dll; DestDir: {app}\bin\bearer; Check: IsWin64();
Source: {#MyStageDir}\bin\64\iconengines\qsvgicon.dll; DestDir: {app}\bin\iconengines; Check: IsWin64();
Source: {#MyStageDir}\bin\64\imageformats\qgif.dll; DestDir: {app}\bin\imageformats; Check: IsWin64();
Source: {#MyStageDir}\bin\64\imageformats\qicns.dll; DestDir: {app}\bin\imageformats; Check: IsWin64();
Source: {#MyStageDir}\bin\64\imageformats\qico.dll; DestDir: {app}\bin\imageformats; Check: IsWin64();
Source: {#MyStageDir}\bin\64\imageformats\qjpeg.dll; DestDir: {app}\bin\imageformats; Check: IsWin64();
Source: {#MyStageDir}\bin\64\imageformats\qsvg.dll; DestDir: {app}\bin\imageformats; Check: IsWin64();
Source: {#MyStageDir}\bin\64\imageformats\qtga.dll; DestDir: {app}\bin\imageformats; Check: IsWin64();
Source: {#MyStageDir}\bin\64\imageformats\qtiff.dll; DestDir: {app}\bin\imageformats; Check: IsWin64();
Source: {#MyStageDir}\bin\64\imageformats\qwbmp.dll; DestDir: {app}\bin\imageformats; Check: IsWin64();
Source: {#MyStageDir}\bin\64\imageformats\qwebp.dll; DestDir: {app}\bin\imageformats; Check: IsWin64();
Source: {#MyStageDir}\bin\64\platforms\qwindows.dll; DestDir: {app}\bin\platforms; Check: IsWin64();
Source: {#MyStageDir}\bin\64\printsupport\windowsprintersupport.dll; DestDir: {app}\bin\printsupport; Check: IsWin64();
Source: {#MyStageDir}\bin\64\vcruntime140.dll; DestDir: {app}\bin; Check: InstallUserRuntime64(); 
Source: {#MyStageDir}\bin\64\msvcp140.dll; DestDir: {app}\bin; Check: InstallUserRuntime64(); 

; Common Resources
Source: {#MyStageDir}\README.txt; DestDir: {app}
Source: {#MyStageDir}\LICENSE.txt; DestDir: {app}

; Tutorial Wizzard
Source: {#MyStageDir}\share\copasi\config\MIRIAMResources.xml; DestDir: {app}\share\copasi\config
Source: {#MyStageDir}\share\copasi\doc\html\TutWiz-Step6.html; DestDir: {app}\share\copasi\doc\html
Source: {#MyStageDir}\share\copasi\doc\html\TutWiz-Step1.html; DestDir: {app}\share\copasi\doc\html
Source: {#MyStageDir}\share\copasi\doc\html\TutWiz-Step2.html; DestDir: {app}\share\copasi\doc\html
Source: {#MyStageDir}\share\copasi\doc\html\TutWiz-Step3.html; DestDir: {app}\share\copasi\doc\html
Source: {#MyStageDir}\share\copasi\doc\html\TutWiz-Step4.html; DestDir: {app}\share\copasi\doc\html
Source: {#MyStageDir}\share\copasi\doc\html\TutWiz-Step5.html; DestDir: {app}\share\copasi\doc\html
Source: {#MyStageDir}\share\copasi\doc\html\figures\TimeCourseDialog.png; DestDir: {app}\share\copasi\doc\html\figures
Source: {#MyStageDir}\share\copasi\doc\html\figures\ModelSettingsDialog.png; DestDir: {app}\share\copasi\doc\html\figures
Source: {#MyStageDir}\share\copasi\doc\html\figures\NewPlotAdded.png; DestDir: {app}\share\copasi\doc\html\figures
Source: {#MyStageDir}\share\copasi\doc\html\figures\ObjectBrowserSelection.png; DestDir: {app}\share\copasi\doc\html\figures
Source: {#MyStageDir}\share\copasi\doc\html\figures\ObjectBrowserTree.png; DestDir: {app}\share\copasi\doc\html\figures
Source: {#MyStageDir}\share\copasi\doc\html\figures\OutputAssistant.png; DestDir: {app}\share\copasi\doc\html\figures
Source: {#MyStageDir}\share\copasi\doc\html\figures\PlotCurveSelectionDialog.png; DestDir: {app}\share\copasi\doc\html\figures
Source: {#MyStageDir}\share\copasi\doc\html\figures\PlotDefinition.png; DestDir: {app}\share\copasi\doc\html\figures
Source: {#MyStageDir}\share\copasi\doc\html\figures\PlotWindow.png; DestDir: {app}\share\copasi\doc\html\figures
Source: {#MyStageDir}\share\copasi\doc\html\figures\ReactionDialog.png; DestDir: {app}\share\copasi\doc\html\figures
Source: {#MyStageDir}\share\copasi\doc\html\figures\ReactionOverview.png; DestDir: {app}\share\copasi\doc\html\figures
Source: {#MyStageDir}\share\copasi\doc\html\figures\ReactionOverviewEmpty.png; DestDir: {app}\share\copasi\doc\html\figures
Source: {#MyStageDir}\share\copasi\doc\html\figures\ReportDefinitionDialog.png; DestDir: {app}\share\copasi\doc\html\figures

; Icons
Source: {#MyStageDir}\share\copasi\icons\CopasiDoc.ico; DestDir: {app}\share\copasi\icons
Source: {#MyStageDir}\share\copasi\icons\Copasi.ico; DestDir: {app}\share\copasi\icons

; Examples
Source: {#MyStageDir}\share\copasi\examples\YeastGlycolysis.gps; DestDir: {app}\share\copasi\examples
Source: {#MyStageDir}\share\copasi\examples\brusselator.cps; DestDir: {app}\share\copasi\examples
Source: {#MyStageDir}\share\copasi\examples\CircadianClock.cps; DestDir: {app}\share\copasi\examples
Source: {#MyStageDir}\share\copasi\examples\DimericMWC-stiff.cps; DestDir: {app}\share\copasi\examples
Source: {#MyStageDir}\share\copasi\examples\Genetic-2000Elo.xml; DestDir: {app}\share\copasi\examples
Source: {#MyStageDir}\share\copasi\examples\MAPK-HF96-layout.cps; DestDir: {app}\share\copasi\examples
Source: {#MyStageDir}\share\copasi\examples\Metabolism-2000Poo.xml; DestDir: {app}\share\copasi\examples
Source: {#MyStageDir}\share\copasi\examples\NF-kappaB.cps; DestDir: {app}\share\copasi\examples
Source: {#MyStageDir}\share\copasi\examples\Olsen2003_peroxidase.cps; DestDir: {app}\share\copasi\examples
Source: {#MyStageDir}\share\copasi\examples\brusselator.sedml; DestDir: {app}\share\copasi\examples
Source: {#MyStageDir}\share\copasi\examples\brusselator-model.xml; DestDir: {app}\share\copasi\examples
Source: {#MyStageDir}\share\copasi\examples\NF-kappaB.sedml; DestDir: {app}\share\copasi\examples
Source: {#MyStageDir}\share\copasi\examples\NF-kappaB-model.xml; DestDir: {app}\share\copasi\examples
Source: {#MyStageDir}\share\copasi\examples\scan.sedml; DestDir: {app}\share\copasi\examples
Source: {#MyStageDir}\share\copasi\examples\oscli.xml; DestDir: {app}\share\copasi\examples

; VC Redistributable
Source: {#MyStageDir}\bin\32\vcredist_x86.exe; DestDir: {app}; Flags: deleteafterinstall; Check: IsWin32();
Source: {#MyStageDir}\bin\64\vcredist_x64.exe; DestDir: {app}; Flags: deleteafterinstall; Check: IsWin64(); 

[Icons]
Name: {group}\CopasiUI; Filename: {app}\{#MyAppExeName}; WorkingDir: {userdocs}
Name: {group}\{cm:ProgramOnTheWeb,{#MyAppName}}; Filename: {#MyAppURL}
Name: {group}\License; Filename: {app}\LICENSE.txt
Name: {group}\README; Filename: {app}\README.txt
Name: {group}\{cm:UninstallProgram,{#MyAppName}}; Filename: {uninstallexe}
Name: {commondesktop}\{#MyAppName}; Filename: {app}\{#MyAppExeName}; Tasks: desktopicon; WorkingDir: {userdocs}
Name: {userappdata}\Microsoft\Internet Explorer\Quick Launch\{#MyAppName}; Filename: {app}\{#MyAppExeName}; Tasks: quicklaunchicon; WorkingDir: {userdocs}

[Run]
Filename: {app}\vcredist_x86.exe; Parameters: /q /norestart; StatusMsg: Installing Microsoft Visual C++ 2017 32 bit Runtime Libraries; Check: InstallSystemRuntime32()
Filename: {app}\vcredist_x64.exe; Parameters: /q /norestart; StatusMsg: Installing Microsoft Visual C++ 2017 64 bit Runtime Libraries; Check: InstallSystemRuntime64()

[Dirs]
Name: {app}\bin
Name: {app}\bin\bearer
Name: {app}\bin\iconengines
Name: {app}\bin\imageformats
Name: {app}\bin\platforms
Name: {app}\bin\printsupport
Name: {app}\share
Name: {app}\share\copasi
Name: {app}\share\copasi\config
Name: {app}\share\copasi\doc
Name: {app}\share\copasi\doc\html
Name: {app}\share\copasi\doc\html\figures
Name: {app}\share\copasi\examples
Name: {app}\share\copasi\icons

[Registry]
Root: HKCR; SubKey: .cps; ValueType: string; ValueData: COPASI.document; Flags: uninsdeletekey; Check: IsAdminUser
Root: HKCR; SubKey: COPASI.document; ValueType: string; ValueData: COPASI File; Flags: uninsdeletekey; Check: IsAdminUser
Root: HKCR; SubKey: COPASI.document\Shell\Open\Command; ValueType: string; ValueData: """{app}\bin\CopasiUI.exe"" ""%1"""; Flags: uninsdeletevalue; Check: IsAdminUser
Root: HKCR; Subkey: COPASI.document\DefaultIcon; ValueType: string; ValueData: {app}\share\copasi\icons\CopasiDoc.ico,-1; Flags: uninsdeletevalue; Check: IsAdminUser
Root: HKCR; Subkey: COPASI; ValueType: string; ValueData: "URL: COPASI Protocol"; Flags: uninsdeletevalue; Check: IsAdminUser
Root: HKCR; Subkey: COPASI; ValueType: string; ValueName: "URL Protocol"; ValueData: ""; Flags: uninsdeletevalue; Check: IsAdminUser
Root: HKCR; Subkey: COPASI\DefaultIcon; ValueType: string; ValueData: {app}\share\copasi\icons\CopasiDoc.ico,-1; Flags: uninsdeletevalue; Check: IsAdminUser
Root: HKCR; Subkey: COPASI\Shell\Open\Command; ValueType: string; ValueData: """{app}\bin\CopasiUI.exe"" ""%1"""; Flags: uninsdeletevalue; Check: IsAdminUser
Root: HKLM; Subkey: SYSTEM\CurrentControlSet\Control\Session Manager\Environment; ValueType: string; ValueName: COPASIDIR; ValueData: {app}; Check: IsAdminUser
Root: HKLM; Subkey: SYSTEM\CurrentControlSet\Control\Session Manager\Environment; ValueType: expandsz; ValueName: Path; ValueData: "%COPASIDIR%\bin;{olddata}"; Check: UpdateSystemPath
Root: HKLM; Subkey: Software\Microsoft\Windows NT\CurrentVersion\AppCompatFlags\Layers; ValueType: string; ValueName: "{app}\bin\CopasiUI.exe"; ValueData: "~ WIN7RTM"; Flags: uninsdeletevalue; Check: IsAdminUserAndWindows8
Root: HKCU; SubKey: Software\Classes\.cps; ValueType: string; ValueData: COPASI.document; Flags: uninsdeletekey; Check: IsRegularUser
Root: HKCU; SubKey: Software\Classes\COPASI.document; ValueType: string; ValueData: COPASI File; Flags: uninsdeletekey; Check: IsRegularUser
Root: HKCU; SubKey: Software\Classes\COPASI.document\Shell\Open\Command; ValueType: string; ValueData: """{app}\bin\CopasiUI.exe"" ""%1"""; Flags: uninsdeletevalue; Check: IsRegularUser
Root: HKCU; Subkey: Software\Classes\COPASI.document\DefaultIcon; ValueType: string; ValueData: {app}\share\copasi\icons\CopasiDoc.ico,-1; Flags: uninsdeletevalue; Check: IsRegularUser
Root: HKCU; Subkey: Software\Classes\COPASI; ValueType: string; ValueData: "URL: COPASI Protocol"; Flags: uninsdeletevalue; Check: IsRegularUser
Root: HKCU; Subkey: Software\Classes\COPASI; ValueType: string; ValueName: "URL Protocol"; ValueData: ""; Flags: uninsdeletevalue; Check: IsRegularUser
Root: HKCU; Subkey: Software\Classes\COPASI\DefaultIcon; ValueType: string; ValueData: {app}\share\copasi\icons\CopasiDoc.ico,-1; Flags: uninsdeletevalue; Check: IsRegularUser
Root: HKCU; Subkey: Software\Classes\COPASI\Shell\Open\Command; ValueType: string; ValueData: """{app}\bin\CopasiUI.exe"" ""%1"""; Flags: uninsdeletevalue; Check: IsRegularUser
Root: HKCU; Subkey: Environment; ValueType: string; ValueName: COPASIDIR; ValueData: {app}; Check: IsRegularUser
Root: HKCU; Subkey: Environment; ValueType: expandsz; ValueName: Path; ValueData: "%COPASIDIR%\bin;{olddata}"; Check: UpdateUserPath
Root: HKCU; Subkey: Software\Microsoft\Windows NT\CurrentVersion\AppCompatFlags\Layers; ValueType: string; ValueName: "{app}\bin\CopasiUI.exe"; ValueData: "~ WIN7RTM"; Flags: uninsdeletevalue; Check: IsRegularUserAndWindows8

[Code]
type
  RunTimeVersion = array [0..3] of Integer;

function IsWin32(): Boolean;
begin
  Result := not IsWin64;
end;

function IsAdminUser(): Boolean;
begin
  Result := (IsAdminLoggedOn or IsPowerUserLoggedOn);
end;

function IsRegularUser(): Boolean;
begin
  Result := not (IsAdminLoggedOn or IsPowerUserLoggedOn);
end;

function isWindows8(): Boolean;
var
  Version: TWindowsVersion;

begin
  GetWindowsVersionEx(Version);

  Result := ((Version.Major = 6) and (Version.Minor = 2));
end;

function IsAdminUserAndWindows8(): Boolean;
begin
  Result := (IsAdminUser() and isWindows8());
end;

function IsRegularUserAndWindows8(): Boolean;
begin
  Result := (IsRegularUser() and isWindows8());
end;

function IsCopasiInSystemPath(): Boolean;
var
  CurrentPath: String;
  Position: Integer;

begin
  Result := False;

  if RegQueryStringValue(HKLM,
    'SYSTEM\CurrentControlSet\Control\Session Manager\Environment',
    'Path', CurrentPath) then
    // Successfully read the value
    begin
      Position := Pos('%COPASIDIR%\bin', CurrentPath);
      if (Position <> 0) then
        // Found an entry to the COPASI binaries in the Path
        begin
          Result := True;
        end;
    end;
end;

function IsCopasiInUserPath(): Boolean;
var
  CurrentPath: String;
  Position: Integer;

begin
  Result := IsCopasiInSystemPath();

  if RegQueryStringValue(HKCU,
    'Environment',
    'Path', CurrentPath) then
    // Successfully read the value
    begin
      Position := Pos('%COPASIDIR%\bin', CurrentPath);
      if (Position <> 0) then
        // Found an entry to the COPASI binaries in the Path
        begin
          Result := True;
        end;
    end;
end;

function UpdateSystemPath(): Boolean;
begin
  Result := (IsAdminUser() and not IsCopasiInSystemPath());
end;

function UpdateUserPath(): Boolean;
begin
  Result := (IsRegularUser() and not IsCopasiInUserPath());
end;

function StrToVersion(str: String): RunTimeVersion;
var
  Version: RunTimeVersion;
  Position: Integer;

begin
  try
    begin
      Position := Pos('.', str);
      Version[0] := StrToInt(Copy(str, 1, Position - 1));
      Delete(str, 1, Position);

      Position := Pos('.', str);
      Version[1] := StrToInt(Copy(str, 1, Position - 1));
      Delete(str, 1, Position);

      Position := Pos('.', str);
      Version[2] := StrToInt(Copy(str, 1, Position - 1));
      Delete(str, 1, Position);

      Version[3] := StrToInt(str);
    end;

  except
    begin
      Version[0] := 0;
      Version[1] := 0;
      Version[2] := 0;
      Version[3] := 0;
    end;
  end;

  Result := Version;
end;

function VersionToStr(Version: RunTimeVersion): String;
begin
  Result := IntToStr(Version[0]) + '.' +
            IntToStr(Version[1]) + '.' +
            IntToStr(Version[2]) + '.' +
            IntToStr(Version[3]);
end;

function CompareVersion(Version1: RunTimeVersion;
                        Version2: RunTimeVersion): Integer;
begin
  if Version1[0] <> Version2[0] then
    Result := Version1[0] - Version2[0]
  else if Version1[1] <> Version2[1] then
    Result := Version1[1] - Version2[1]
  else if Version1[2] <> Version2[2] then
    Result := Version1[2] - Version2[2]
  else
    Result := Version1[3] - Version2[3];
end;

function IsInVersionRange(OldVersionRange: String;
                          Version: RunTimeVersion): Boolean;
var
  LowerBound: RunTimeVersion;
  UpperBound: RunTimeVersion;
  Position: Integer;

begin
  Result := False;
  Position := Pos('-', OldVersionRange);

  if Position <> 0 then
    begin
      LowerBound := StrToVersion(Copy(OldVersionRange, 1, Position - 1));
      UpperBound := StrToVersion(Copy(OldVersionRange, Position + 1, 100));
    end
  else
    begin
      LowerBound := StrToVersion(OldVersionRange);
      UpperBound := LowerBound;
    end;

  if (CompareVersion(LowerBound, Version) <= 0) and
     (CompareVersion(Version, UpperBound) <= 0) then
    begin
      Result := True;
    end;
end;

function HaveRuntime64(): Boolean;
begin
  Result := RegKeyExists(HKEY_CLASSES_ROOT, 'Installer\\Products\\083F30FCC2E18753C8E02308E78B0C8D') or
            RegKeyExists(HKEY_LOCAL_MACHINE, 'SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\{2CD849A7-86A1-34A6-B8F9-D72F5B21A9AE}');
end;

function HaveRuntime32(): Boolean;
begin
  Result := RegKeyExists(HKEY_CLASSES_ROOT, 'Installer\\Products\\1A57DEF7C006B493386717E2A288162F') or
            RegKeyExists(HKEY_LOCAL_MACHINE, 'SOFTWARE\Wow6432Node\Microsoft\Windows\CurrentVersion\Uninstall\{56e11d69-7cc9-40a5-a4f9-8f6190c4d84d}')
end;

function InstallSystemRuntime32(): Boolean;
begin
  Result := IsWin32() and IsAdminUser() and not HaveRunTime32();  
end;

function InstallSystemRuntime64(): Boolean;
begin
  Result := IsWin64() and IsAdminUser() and not HaveRunTime64();  
end;

function InstallUserRuntime32(): Boolean;
begin
  Result := IsWin32() and IsRegularUser() and not HaveRunTime32();  
end;

function InstallUserRuntime64(): Boolean;
begin
  Result := IsWin64() and IsRegularUser() and not HaveRunTime64();  
end;

function InitializeSetup(): Boolean;
begin
  Result := True;

  RegDeleteValue(HKEY_CURRENT_USER, 'Environment', 'COPASIDIR');
end;

function DefDirRoot(Param: String): String;
begin
  if IsRegularUser() then
    Result := ExpandConstant('{localappdata}')
  else if IsWin64() then
    Result := ExpandConstant('{pf64}')
  else
    Result := ExpandConstant('{pf}');
end;
