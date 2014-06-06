::-----------------------------------------------------------------------------
:: Paths
::-----------------------------------------------------------------------------
set SCRIPT_DIR=%~dp0%
set ProjectHome=%SCRIPT_DIR%
set WorkspaceDir=%ProjectHome%\workspace
set ThisProjTools=%ProjectHome%\tools

%ThisProjTools%\eclipseArduino\eclipsec.exe -data %WorkspaceDir% -nosplash -application org.eclipse.cdt.managedbuilder.core.headlessbuild -cleanBuild all -vmargs -Dorg.eclipse.cdt.core.console=org.eclipse.cdt.core.systemConsole -XX:-UseCompressedOops
