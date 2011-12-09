#!/bin/sh

source `dirname $0`/verify_dir.bat $1

if [ $? -ne 0 ]; then
  return 1
fi

if [ -e "$1/$2" ]; then
 rm -f $1/$2
fi

exit

@echo off

rem Make sure we are in target directory
call "%~dp0/verify_dir.bat" %1
if %ERRORLEVEL% NEQ 0 exit 1

rem Deleting old BSP library
if exist %2 del %2
