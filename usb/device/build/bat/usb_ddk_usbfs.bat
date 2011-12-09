#!/bin/sh

source `dirname $0`/verify_dir.bat $1

rm -f *.h

source `dirname $0`/usb_ddk.bat

cp -f ../../../../usb/device/source/include/usbfs/usbprv_fs.h .
cp -f ../../../../usb/device/source/include/usbfs/usbfs_dev_main.h .

exit

@echo off

rem Make sure we are in target directory
call "%~dp0/verify_dir.bat" %1
if %ERRORLEVEL% NEQ 0 exit 1

rem  Remove old headers

attrib -R *
if exist *.h   del /F /Q *.h

rem  Copy common header files

call "%~dp0/usb_ddk.bat"

rem  Copy FS-specific header files

copy /Y ..\..\..\..\usb\device\source\include\usbfs\usbprv_fs.h .
copy /Y ..\..\..\..\usb\device\source\include\usbfs\usbfs_dev_main.h .

