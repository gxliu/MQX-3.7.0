@echo off

rem Make sure we are in target directory
call "%~dp0/verify_dir.bat" %1
if %ERRORLEVEL% NEQ 0 exit 1

rem  Remove old headers

attrib -R *
if exist *.h   del /F /Q *.h

rem Copy common header files

call "%~dp0\usb_hdk.bat"

rem Copy KHCI-specific header files

copy /Y ..\..\..\..\usb\host\source\host\khci\khci.h .
copy /Y ..\..\..\..\usb\host\source\host\khci\usbprv_host.h .
