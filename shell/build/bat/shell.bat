#!/bin/sh

source `dirname $0`/verify_dir.bat $1

rm -f *.h

cp -f ../../../shell/source/include/shell.h .
cp -f ../../../shell/source/include/sh_mfs.h .
cp -f ../../../shell/source/include/sh_rtcs.h .
cp -f ../../../shell/source/include/sh_enet.h .

exit

@echo off

rem Make sure we are in target directory
call "%~dp0/verify_dir.bat" %1
if %ERRORLEVEL% NEQ 0 exit 1

if exist *.h del /F /Q *.h

copy /Y ..\..\..\shell\source\include\shell.h .
copy /Y ..\..\..\shell\source\include\sh_mfs.h .
copy /Y ..\..\..\shell\source\include\sh_rtcs.h .
copy /Y ..\..\..\shell\source\include\sh_enet.h .
