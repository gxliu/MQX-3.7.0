#!/bin/sh

source `dirname $0`/verify_dir.bat $1

source `dirname $0`/psp_cortex.bat $1 $2

for f in ../../../config/common/*.h; do
  cp -f ../../../mqx/source/include/dontchg.h ../`basename $f`
  cat $f >> ../`basename $f`
done

for f in ../../../config/twrk60n512/*.h; do
  cp -f ../../../mqx/source/include/dontchg.h ../`basename $f`
  cat $f >> ../`basename $f`
done

cp -f ../../../mqx/source/psp/cortex/regfile.h .
cp -f ../../../mqx/source/psp/cortex/MK60N512VMD100.h .
cp -f ../../../mqx/source/psp/cortex/kinetis.h .
cp -f ../../../mqx/source/psp/cortex/kinetis_fcan.h .

exit

@echo off

rem make sure we are in target directory
call "%~dp0/verify_dir.bat" %1
if %ERRORLEVEL% NEQ 0 exit 1

rem  Common non-private header files

call "%~dp0\psp_cortex.bat" %1 %2

rem  Configuration header files

for %%F in (..\..\..\config\common\*.h)     do copy /Y /B ..\..\..\mqx\source\include\dontchg.h + %%F ..\%%~nF%%~xF
for %%F in (..\..\..\config\twrk60n512\*.h)  do copy /Y /B ..\..\..\mqx\source\include\dontchg.h + %%F ..\%%~nF%%~xF

rem  Processor-specific PSP files

copy /Y ..\..\..\mqx\source\psp\cortex\regfile.h  .
copy /Y ..\..\..\mqx\source\psp\cortex\MK60N512VMD100.h  .
copy /Y ..\..\..\mqx\source\psp\cortex\kinetis.h  .
copy /Y ..\..\..\mqx\source\psp\cortex\kinetis_fcan.h  .

