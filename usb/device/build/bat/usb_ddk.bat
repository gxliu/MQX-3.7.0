#!/bin/sh

cp -f ../../../../usb/device/source/include/types.h .
cp -f ../../../../usb/device/source/include/usb.h .
cp -f ../../../../usb/device/source/include/usbprv.h .
#cp -f ../../../../usb/device/source/include/debug.h .
cp -f ../../../../usb/device/source/include/devapi.h .
cp -f ../../../../usb/device/source/include/dev_cnfg.h .
cp -f ../../../../usb/device/source/include/rtos/mqx_dev.h .
cp -f ../../../../usb/device/source/classes/include/usb_stack_config.h .
cp -f ../../../../usb/device/source/classes/include/usb_cdc.h .
cp -f ../../../../usb/device/source/classes/include/usb_cdc_pstn.h .
cp -f ../../../../usb/device/source/classes/include/usb_class.h .
cp -f ../../../../usb/device/source/classes/include/usb_hid.h .
cp -f ../../../../usb/device/source/classes/include/usb_framework.h .
cp -f ../../../../usb/device/source/classes/include/usb_msc.h .
cp -f ../../../../usb/device/source/classes/include/usb_phdc.h .

return 0

@echo off

rem  Copy common header files

copy /Y ..\..\..\..\usb\device\source\include\types.h .
copy /Y ..\..\..\..\usb\device\source\include\usb.h .
copy /Y ..\..\..\..\usb\device\source\include\usbprv.h .
copy /Y ..\..\..\..\usb\device\source\include\debug.h .
copy /Y ..\..\..\..\usb\device\source\include\devapi.h .
copy /Y ..\..\..\..\usb\device\source\include\dev_cnfg.h .
copy /Y ..\..\..\..\usb\device\source\include\rtos\mqx_dev.h .
copy /Y ..\..\..\..\usb\device\source\classes\include\usb_stack_config.h .
copy /Y ..\..\..\..\usb\device\source\classes\include\usb_cdc.h .
copy /Y ..\..\..\..\usb\device\source\classes\include\usb_cdc_pstn.h .
copy /Y ..\..\..\..\usb\device\source\classes\include\usb_class.h .
copy /Y ..\..\..\..\usb\device\source\classes\include\usb_hid.h .
copy /Y ..\..\..\..\usb\device\source\classes\include\usb_framework.h .
copy /Y ..\..\..\..\usb\device\source\classes\include\usb_msc.h .
copy /Y ..\..\..\..\usb\device\source\classes\include\usb_phdc.h .
