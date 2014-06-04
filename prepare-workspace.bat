@echo off
REM ******************************************************************
REM *
REM ******************************************************************
cd workspace
echo "unpacking the metadata in workspace"
..\tools\7za920\7za.exe x -y ".metadata.zip"

echo "make the the folder workspace\.metadata writeable"
attrib -R ".metadata" /S /D

pause
