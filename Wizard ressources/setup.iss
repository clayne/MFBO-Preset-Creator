[Setup]  
#define AppVersion GetVersionNumbersString(".\client release\MFBOPresetCreator.exe")
#define AppName "MFBO Preset Creator"

AppId={{F0572980-4893-4828-B9EC-B9AD99DBCE35}
AppName=MFBO Preset Creator
AppVersion={#AppVersion}
AppPublisher=Mitsuriou
AppPublisherURL=https://github.com/Mitsuriou/MFBO-Preset-Creator
AppSupportURL=https://github.com/Mitsuriou/MFBO-Preset-Creator
AppUpdatesURL=https://github.com/Mitsuriou/MFBO-Preset-Creator
DefaultDirName={commonpf64}\{#AppName}
DisableProgramGroupPage=yes
PrivilegesRequiredOverridesAllowed=dialog
OutputDir=wizard
OutputBaseFilename=mfbopc-install-wizard
SetupIconFile=.\icon.ico
Compression=lzma
SolidCompression=yes
WizardStyle=modern
UninstallDisplayIcon={app}\MFBOPresetCreator.exe
UninstallDisplayName=MFBO Preset Creator (v.{#AppVersion})

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"
Name: "french"; MessagesFile: "compiler:Languages\French.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: ".\client release\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: ".\filters.json"; DestDir: "{localappdata}\MFBOPresetCreator"; Flags: ignoreversion uninsneveruninstall onlyifdoesntexist
Source: ".\assets\*"; DestDir: "{localappdata}\MFBOPresetCreator\assets"; Flags: ignoreversion recursesubdirs createallsubdirs uninsneveruninstall onlyifdoesntexist

[Icons]
Name: "{autoprograms}\{#AppName}"; Filename: "{app}\MFBOPresetCreator.exe"
Name: "{autodesktop}\{#AppName} (v.{#AppVersion})"; Filename: "{app}\MFBOPresetCreator.exe"; Tasks: desktopicon

[Run]
Filename: "{app}\MFBOPresetCreator.exe"; Description: "{cm:LaunchProgram,{#AppName}}"; Flags: nowait postinstall skipifsilent
