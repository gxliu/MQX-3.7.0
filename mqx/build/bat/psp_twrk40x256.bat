@echo off

rem make sure we are in target directory
call "%~dp0/verify_dir.bat" %1
if %ERRORLEVEL% NEQ 0 exit 1

rem  Common non-private header files

call "%~dp0\psp_cortex.bat" %1 %2

rem  Configuration header files

for %%F in (..\..\..\config\common\*.h)     do copy /Y /B ..\..\..\mqx\source\include\dontchg.h + %%F ..\%%~nF%%~xF
for %%F in (..\..\..\config\twrk40x256\*.h)  do copy /Y /B ..\..\..\mqx\source\include\dontchg.h + %%F ..\%%~nF%%~xF

rem  Processor-specific PSP files

copy /Y ..\..\..\mqx\source\psp\cortex\kinetis.h  .
copy /Y ..\..\..\mqx\source\psp\cortex\reg_enet.h  .
copy /Y ..\..\..\mqx\source\psp\cortex\regfile.h  .
copy /Y ..\..\..\mqx\source\psp\cortex\MK40X256VMD100.h  .
copy /Y ..\..\..\mqx\source\psp\cortex\kinetis_fcan.h  .
