@echo off

rem make sure we are in target directory
call "%~dp0/verify_dir.bat" %1
if %ERRORLEVEL% NEQ 0 exit 1

rem  Common non-private header files

call "%~dp0\psp_mcf.bat" %1 %2

rem  Configuration header files

for %%F in (..\..\..\config\common\*.h)      do copy /Y /B ..\..\..\mqx\source\include\dontchg.h + %%F ..\%%~nF%%~xF
for %%F in (..\..\..\config\twrmcf52259\*.h)  do copy /Y /B ..\..\..\mqx\source\include\dontchg.h + %%F ..\%%~nF%%~xF

rem  Processor-specific PSP files

copy /Y ..\..\..\mqx\source\psp\coldfire\mcf5225.h  .
copy /Y ..\..\..\mqx\source\psp\coldfire\mcf52xx_ictl.h  .
copy /Y ..\..\..\mqx\source\psp\coldfire\mcf522x_usbotg.h  .
copy /Y ..\..\..\mqx\source\psp\coldfire\mcf5xxx_fec.h  .
copy /Y ..\..\..\mqx\source\psp\coldfire\mcf52xx_uart.h  .
copy /Y ..\..\..\mqx\source\psp\coldfire\mcf52xx_fcan.h  .
copy /Y ..\..\..\mqx\source\psp\coldfire\mcf5xxx_qspi.h  .
copy /Y ..\..\..\mqx\source\psp\coldfire\mcf52xx_rtc.h  .
copy /Y ..\..\..\mqx\source\psp\coldfire\mcf52xx_i2c.h  .
copy /Y ..\..\..\mqx\source\psp\coldfire\mcf5xxx_minifb.h  .
copy /Y ..\..\..\mqx\source\psp\coldfire\mcf522xx_adc.h  .
copy /Y ..\..\..\mqx\source\psp\coldfire\mcf522xx_pit.h  .
copy /Y ..\..\..\mqx\source\psp\coldfire\mcf52xx_cfm.h  .
copy /Y ..\..\..\mqx\source\psp\coldfire\mcf522xx_eport.h  .
