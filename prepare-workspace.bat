::@echo off
::-----------------------------------------------------------------------------
:: Configured Settings
::-----------------------------------------------------------------------------
:: Arduino IDE (see http://arduino.cc/en/Main/OldSoftwareReleases) 
set ArduinoDownloadUrl=http://downloads.arduino.cc
set ArduinoVer=1.5.2

:: Eclipse Arduino Workbench Bundle (see http://www.baeyens.it/eclipse/download.php)
set EclipseArduinoDownloadUrl=http://www.baeyens.it/eclipse/download/product
set EclipseArduinoVer=2014-05-22_02-07-31
::set EclipseArduinoVer=2014-05-15_02-07-18

::-----------------------------------------------------------------------------
:: Get the OS Variant
::-----------------------------------------------------------------------------
IF "%PROCESSOR_ARCHITECTURE%;%PROCESSOR_ARCHITEW6432%"=="x86;" (
  set OsVariant=win32
) ELSE (
  set OsVariant=win64
)

::-----------------------------------------------------------------------------
:: Paths
::-----------------------------------------------------------------------------
set SCRIPT_DIR=%~dp0%
set ProjectHome=%SCRIPT_DIR%
set WorkspaceDir=%ProjectHome%\workspace
set ArduinoTools=%ProjectHome%\..\Tools
set ThisProjTools=%ProjectHome%\tools

set EclipseArduinoRevs=%ArduinoTools%\eclipseArduino_revs
set CurEclipseArduino=%EclipseArduinoRevs%\%OsVariant%.%EclipseArduinoVer%\eclipseArduino

set ArduinoRevs=%ArduinoTools%\arduino_revs
set CurArduino=%ArduinoRevs%\arduino-%ArduinoVer%

set Archiver=%ThisProjTools%\7za920\7za.exe
set Curl= %ThisProjTools%\curl\curl.exe

::-----------------------------------------------------------------------------
:: Get the tools
::-----------------------------------------------------------------------------
:: Arduino IDE
if not exist "%CurArduino%" (
  if not exist "%ArduinoRevs%\arduino-%ArduinoVer%-windows.zip" (
    %Curl% -# -o "%ArduinoRevs%\arduino-%ArduinoVer%-windows.zip" "%ArduinoDownloadUrl%/arduino-%ArduinoVer%-windows.zip"
  )
  %Archiver% x -y -o%ArduinoRevs% %ArduinoRevs%\arduino-%ArduinoVer%-windows.zip
)
:: create softlink (junction) for Arduino IDE in current project tools
rmdir %ThisProjTools%\arduino
mklink /J %ThisProjTools%\arduino %CurArduino%

:: Eclipse Arduino Workbench Bundle
if not exist "%CurEclipseArduino%" (
  if not exist "%EclipseArduinoRevs%\%OsVariant%.%EclipseArduinoVer%.tar.gz" (
    %Curl% -# -o "%EclipseArduinoRevs%\%OsVariant%.%EclipseArduinoVer%.tar.gz" "%EclipseArduinoDownloadUrl%/%OsVariant%.%EclipseArduinoVer%.tar.gz"
  )
  %Archiver% x -y -o%EclipseArduinoRevs% %EclipseArduinoRevs%\%OsVariant%.%EclipseArduinoVer%.tar.gz
  %Archiver% x -y -o%EclipseArduinoRevs%\%OsVariant%.%EclipseArduinoVer% %EclipseArduinoRevs%\%OsVariant%.%EclipseArduinoVer%.tar
)
:: create softlink (junction) for Eclipse Arduino Workbench Bundle in current project tools
rmdir %ThisProjTools%\eclipseArduino
mklink /J %ThisProjTools%\eclipseArduino %CurEclipseArduino%

:: unpack Eclipse metadata in workspace
if not exist "%WorkspaceDir%\.metadata" (
  %Archiver% x -y -o%WorkspaceDir% "%WorkspaceDir%\.metadata.zip"
)

::pause