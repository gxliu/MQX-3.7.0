@echo off

rem make sure we are in target directory
call "%~dp0/verify_dir.bat" %1
if %ERRORLEVEL% NEQ 0 exit 1

rem  Common non-private header files

call "%~dp0\psp_mcf.bat" %1 %2

rem  Configuration header files
rem  Configuration header files

for %%F in (..\..\..\config\common\*.h)     do copy /Y /B ..\..\..\mqx\source\include\dontchg.h + %%F ..\%%~nF%%~xF
for %%F in (..\..\..\config\m5208evb\*.h)  do copy /Y /B ..\..\..\mqx\source\include\dontchg.h + %%F ..\%%~nF%%~xF

rem  Processor-specific PSP files
copy /Y ..\..\..\mqx\source\psp\coldfire\mcf5208.h  .
copy /Y ..\..\..\mqx\source\psp\coldfire\mcf52xx_uart.h  .
copy /Y ..\..\..\mqx\source\psp\coldfire\mcf5xxx_qspi.h  .
copy /Y ..\..\..\mqx\source\psp\coldfire\mcf52xx_i2c.h  .
copy /Y ..\..\..\mqx\source\psp\coldfire\mcf5xxx_fec.h  .
copy /Y ..\..\..\mqx\source\psp\coldfire\mcf5xxx_sdramc.h  .
copy /Y ..\..\..\mqx\source\psp\coldfire\mcf5xxx_fb.h  .
copy /Y ..\..\..\mqx\source\psp\coldfire\mcf5xxx_pit.h  .
