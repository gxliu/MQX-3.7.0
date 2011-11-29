@echo off

rem Make sure we are in target directory
call "%~dp0/verify_dir.bat" %1
if %ERRORLEVEL% NEQ 0 exit 1

rem  Remove old headers

attrib -R *
if exist *.h   del /F /Q *.h

rem Copy common header files

call "%~dp0\usb_ddk.bat"

rem  Copy HS-specific header files

copy /Y ..\..\..\..\usb\device\source\include\usbhs\usbprv_hs.h .
copy /Y ..\..\..\..\usb\device\source\include\usbhs\usbhs_dev_main.h .

