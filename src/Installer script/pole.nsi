; example2.nsi
;
; This script is based on example1.nsi, but it remember the directory, 
; has uninstall support and (optionally) installs start menu shortcuts.
;
; It will install makensisw.exe into a directory that the user selects,

;--------------------------------

; The name of the installer
Name "Power of Law Encyclopedia"

; The file to write
OutFile "installpole.exe"

; The default installation directory
InstallDir "$PROGRAMFILES\Power of Law Encyclopedia"

; Registry key to check for directory (so if you install again, it will 
; overwrite the old one automatically)
InstallDirRegKey HKLM "Software\Power of Law Encyclopedia" "Install_Dir"

;--------------------------------

; Pages

Page components
Page directory
Page instfiles

UninstPage uninstConfirm
UninstPage instfiles

;--------------------------------

; The stuff to install
Section "Main files"

  SectionIn RO
  
  ; Set output path to the installation directory.
  SetOutPath $INSTDIR
  
  ; Put file there
  File pole.exe
  File QtCore4.dll
  File QtGui4.dll
  File mingwm10.dll
  File /r data
  File /r images

  
  ; Write the installation path into the registry
  WriteRegStr HKLM "Software\Power of Law Encyclopedia" "Install_Dir" "$INSTDIR"
  
  ; Write the uninstall keys for Windows
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Power of Law Encyclopedia" "DisplayName" "Power of Law Encyclopedia"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Power of Law Encyclopedia" "UninstallString" '"$INSTDIR\uninstall.exe"'
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Power of Law Encyclopedia" "NoModify" 1
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Power of Law Encyclopedia" "NoRepair" 1
  WriteUninstaller "uninstall.exe"
  
SectionEnd

; Optional section (can be disabled by the user)
Section "Start Menu Shortcuts"

  CreateDirectory "$SMPROGRAMS\Power of Law Encyclopedia"
  CreateShortCut "$SMPROGRAMS\Power of Law Encyclopedia\Power of Law Encyclopedia.lnk" "$INSTDIR\pole.exe" "" "$INSTDIR\pole.exe" 0
  CreateShortCut "$SMPROGRAMS\Power of Law Encyclopedia\Удалить.lnk" "$INSTDIR\uninstall.exe" "" "$INSTDIR\uninstall.exe" 0
  
SectionEnd

;--------------------------------

; Uninstaller

Section "Uninstall"
  
  ; Remove registry keys
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Power of Law Encyclopedia"
  DeleteRegKey HKLM "SOFTWARE\NSIS_Power of Law Encyclopedia"

  ; Remove files and uninstaller

  Delete $INSTDIR\pole.exe
  Delete $INSTDIR\QtCore4.dll
  Delete $INSTDIR\QtGui4.dll
  Delete $INSTDIR\mingwm10.dll
  Delete $INSTDIR\data\db\*
  Delete $INSTDIR\data\sounds\*
  Delete $INSTDIR\data\*
  Delete $INSTDIR\images\database\armors\*
  Delete $INSTDIR\images\database\buttons\*
  Delete $INSTDIR\images\database\forces\*
  Delete $INSTDIR\images\database\people\*
  Delete $INSTDIR\images\database\tech\*
  Delete $INSTDIR\images\database\*
  Delete $INSTDIR\images\main\*
  Delete $INSTDIR\images\navigation\maps\*
  Delete $INSTDIR\images\navigation\patch\*
  Delete $INSTDIR\images\navigation\*
  Delete $INSTDIR\images\news\*
  Delete $INSTDIR\images\wallpapers\*
  Delete $INSTDIR\images\wallpapers\small*


  ; Remove shortcuts, if any
  Delete "$SMPROGRAMS\Power of Law Encyclopedia\*.*"

  ; Remove directories used
  RMDir "$SMPROGRAMS\Power of Law Encyclopedia"
  RMDir  /r "$INSTDIR\data"
  RMDir  /r "$INSTDIR\images"
  RMDir "$INSTDIR"

SectionEnd
