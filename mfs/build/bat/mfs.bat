@echo off

rem Make sure we are in target directory
call "%~dp0/verify_dir.bat" %1
if %ERRORLEVEL% NEQ 0 exit 1

if exist *.h  del /F /Q *.h

copy /Y ..\..\..\mfs\source\include\mfs.h .
copy /Y ..\..\..\mfs\source\include\mfs_cnfg.h .
copy /Y ..\..\..\mfs\source\include\mfs_rev.h .
copy /Y ..\..\..\mfs\source\include\part_mgr.h .
