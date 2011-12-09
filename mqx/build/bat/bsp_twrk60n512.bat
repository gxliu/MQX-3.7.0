#!/bin/sh

source `dirname $0`/verify_dir.bat $1

gen_files_copy_skip()
{
  source `dirname $0`/write_readme.bat > ../twrk60n512_lib.txt
}

comp_done()
{
  cp -f ../../../mqx/source/bsp/twrk60n512/bsp.h .
  cp -f ../../../mqx/source/bsp/twrk60n512/bsp_rev.h .
  cp -f ../../../mqx/source/bsp/twrk60n512/twrk60n512.h .

  cp -f ../../../mqx/source/io/adc/adc.h .
  cp -f ../../../mqx/source/io/adc/kadc/adc_kadc.h .
  cp -f ../../../mqx/source/io/io_dun/io_dun.h .
  cp -f ../../../mqx/source/io/io_mem/io_mem.h .
  cp -f ../../../mqx/source/io/io_mem/iomemprv.h .
  cp -f ../../../mqx/source/io/pcb/io_pcb.h .
  cp -f ../../../mqx/source/io/pcb/mqxa/pcb_mqxa.h .
  cp -f ../../../mqx/source/io/io_null/io_null.h .
  cp -f ../../../mqx/source/io/serial/serial.h  .
  cp -f ../../../mqx/source/io/serial/serl_kuart.h .
  cp -f ../../../mqx/source/io/lwgpio/lwgpio.h .
  cp -f ../../../mqx/source/io/lwgpio/lwgpio_kgpio.h .
  cp -f ../../../mqx/source/io/gpio/io_gpio.h .
  cp -f ../../../mqx/source/io/gpio/kgpio/io_gpio_kgpio.h .
  cp -f ../../../mqx/source/io/spi/spi.h .
  cp -f ../../../mqx/source/io/spi/spi_dspi.h .
  cp -f ../../../mqx/source/io/can/flexcan/kflexcan.h .
  cp -f ../../../mqx/source/io/usb/usb_bsp.h .
  cp -f ../../../mqx/source/io/rtc/krtc.h .
  cp -f ../../../mqx/source/io/rtc/rtc.h .
  cp -f ../../../mqx/source/io/i2c/i2c.h  .
  cp -f ../../../mqx/source/io/i2c/i2c_ki2c.h .
  cp -f ../../../mqx/source/io/tfs/tfs.h .
  cp -f ../../../mqx/source/io/flashx/flashx.h .
  cp -f ../../../mqx/source/io/flashx/freescale/flash_kinetis.h .
  cp -f ../../../mqx/source/io/flashx/freescale/flash_mk60.h .
  cp -f ../../../mqx/source/io/esdhc/esdhc.h .
  cp -f ../../../mqx/source/io/sdcard/sdcard.h .
  cp -f ../../../mqx/source/io/sdcard/sdcard_spi/sdcard_spi.h .
  cp -f ../../../mqx/source/io/sdcard/sdcard_esdhc/sdcard_esdhc.h .
  cp -f ../../../mqx/source/io/enet/ethernet.h .
  cp -f ../../../mqx/source/io/enet/enet.h .
  cp -f ../../../mqx/source/io/enet/enet_wifi.h .
  cp -f ../../../mqx/source/io/enet/macnet/macnet_mk60.h .
  cp -f ../../../mqx/source/io/enet/macnet/macnet_1588.h .
  cp -f ../../../mqx/source/io/enet/phy/phy_dp83xxx.h .
  cp -f ../../../mqx/source/io/tchres/tchres.h .

  mkdir -p Generated_Code
  cd Generated_Code
  
  rm -f *.h

  cp -f ../../../../mqx/source/bsp/twrk60n512/PE_LDD.h .
  
  if [ "$2" == "iar" ]; then
    gen_files_copy_skip
  fi
  
  if [ -e ../../../../mqx/build/cw10/bsp_twrk60n512/Generated_Code/PE_LDD.h ]; then
    cp -f ../../../../mqx/build/cw10/bsp_twrk60n512/Generated_Code/*.h .
    cp -f ../../../../mqx/build/cw10/bsp_twrk60n512/Sources/*.h .
  else
    gen_files_copy_skip
  fi

}

comp_cw()
{
  mkdir -p dbg
  cp -f ../../../mqx/source/bsp/twrk60n512/cw/intram.lcf .
  cp -f ../../../mqx/source/bsp/twrk60n512/cw/intflash.lcf .
  cp -f ../../../mqx/source/bsp/twrk60n512/cw/dbg/twrk60n512.mem ./dbg
  cp -f ../../../mqx/source/bsp/twrk60n512/cw/dbg/init_kinetis.tcl ./dbg
  cp -f ../../../mqx/source/bsp/twrk60n512/cw/dbg/mass_erase_kinetis.tcl ./dbg
  comp_done
}

comp_iar()
{
  comp_done
}

for f in ../../../config/common/*.h; do
  cp -f ../../../mqx/source/include/dontchg.h ../`basename $f`
  cat $f >> ../`basename $f`
done

for f in ../../../config/twrk60n512/*.h; do
  cp -f ../../../mqx/source/include/dontchg.h ../`basename $f`
  cat $f >> ../`basename $f`
done

if [ "$2" == "iar" ]; then
 comp_iar
else
 comp_cw
fi

exit

@echo off

rem Make sure we are in target directory
call "%~dp0/verify_dir.bat" %1
if %ERRORLEVEL% NEQ 0 exit 1

attrib -R *

rem  Configuration header files

for %%F in (..\..\..\config\common\*.h)      do copy /Y /B ..\..\..\mqx\source\include\dontchg.h + %%F ..\%%~nF%%~xF
for %%F in (..\..\..\config\twrk60n512\*.h)  do copy /Y /B ..\..\..\mqx\source\include\dontchg.h + %%F ..\%%~nF%%~xF

rem  Compiler-specific BSP files

if /I "%~2" == "iar" goto comp_iar

rem  CodeWarrior Compiler

:comp_cw
mkdir dbg
copy /Y ..\..\..\mqx\source\bsp\twrk60n512\cw\intram.lcf .
copy /Y ..\..\..\mqx\source\bsp\twrk60n512\cw\intflash.lcf .
copy /Y ..\..\..\mqx\source\bsp\twrk60n512\cw\dbg\twrk60n512.mem .\dbg
copy /Y ..\..\..\mqx\source\bsp\twrk60n512\cw\dbg\init_kinetis.tcl .\dbg
copy /Y ..\..\..\mqx\source\bsp\twrk60n512\cw\dbg\mass_erase_kinetis.tcl .\dbg
goto comp_done

rem  IAR Compiler

:comp_iar
copy /Y ..\..\..\mqx\source\bsp\twrk60n512\iar\ram.icf .
copy /Y ..\..\..\mqx\source\bsp\twrk60n512\iar\intflash.icf .
goto comp_done

rem  End of Compiler-specific files

:comp_done

rem  Board-specific BSP files

copy /Y ..\..\..\mqx\source\bsp\twrk60n512\bsp.h .
copy /Y ..\..\..\mqx\source\bsp\twrk60n512\bsp_rev.h .
copy /Y ..\..\..\mqx\source\bsp\twrk60n512\twrk60n512.h .

rem  Board-specific IO driver files

copy /Y ..\..\..\mqx\source\io\adc\adc.h .
copy /Y ..\..\..\mqx\source\io\adc\kadc\adc_kadc.h .
copy /Y ..\..\..\mqx\source\io\io_dun\io_dun.h .
copy /Y ..\..\..\mqx\source\io\io_mem\io_mem.h .
copy /Y ..\..\..\mqx\source\io\io_mem\iomemprv.h .
copy /Y ..\..\..\mqx\source\io\pcb\io_pcb.h .
copy /Y ..\..\..\mqx\source\io\pcb\mqxa\pcb_mqxa.h .
copy /Y ..\..\..\mqx\source\io\io_null\io_null.h .
copy /Y ..\..\..\mqx\source\io\serial\serial.h  .
copy /Y ..\..\..\mqx\source\io\serial\serl_kuart.h .
copy /Y ..\..\..\mqx\source\io\lwgpio\lwgpio.h .
copy /Y ..\..\..\mqx\source\io\lwgpio\lwgpio_kgpio.h .
copy /Y ..\..\..\mqx\source\io\gpio\io_gpio.h .
copy /Y ..\..\..\mqx\source\io\gpio\kgpio\io_gpio_kgpio.h .
copy /Y ..\..\..\mqx\source\io\spi\spi.h .
copy /Y ..\..\..\mqx\source\io\spi\spi_dspi.h .
copy /Y ..\..\..\mqx\source\io\can\flexcan\kflexcan.h .
copy /Y ..\..\..\mqx\source\io\usb\usb_bsp.h .
copy /Y ..\..\..\mqx\source\io\rtc\krtc.h .
copy /Y ..\..\..\mqx\source\io\rtc\rtc.h .
copy /Y ..\..\..\mqx\source\io\i2c\i2c.h  .
copy /Y ..\..\..\mqx\source\io\i2c\i2c_ki2c.h .
copy /Y ..\..\..\mqx\source\io\tfs\tfs.h .
copy /Y ..\..\..\mqx\source\io\flashx\flashx.h .
copy /Y ..\..\..\mqx\source\io\flashx\freescale\flash_kinetis.h .
copy /Y ..\..\..\mqx\source\io\flashx\freescale\flash_mk60.h .
copy /Y ..\..\..\mqx\source\io\esdhc\esdhc.h .
copy /Y ..\..\..\mqx\source\io\sdcard\sdcard.h .
copy /Y ..\..\..\mqx\source\io\sdcard\sdcard_spi\sdcard_spi.h .
copy /Y ..\..\..\mqx\source\io\sdcard\sdcard_esdhc\sdcard_esdhc.h .
copy /Y ..\..\..\mqx\source\io\enet\ethernet.h .
copy /Y ..\..\..\mqx\source\io\enet\enet.h .
copy /Y ..\..\..\mqx\source\io\enet\enet_wifi.h .
copy /Y ..\..\..\mqx\source\io\enet\macnet\macnet_mk60.h .
copy /Y ..\..\..\mqx\source\io\enet\macnet\macnet_1588.h .
copy /Y ..\..\..\mqx\source\io\enet\phy\phy_dp83xxx.h .
copy /Y ..\..\..\mqx\source\io\tchres\tchres.h .


rem Create Generated_Code directory if not exist?
call "%~dp0/verify_dir.bat" Generated_Code

if %ERRORLEVEL% EQU 0 goto gen_dir_exist
    rem Making directory Generated_Code 
    mkdir Generated_Code

    rem Changing working directory to Generated_Code 
    cd Generated_Code

:gen_dir_exist
    rem Directory Generated_Code already exist
    rem Deleting old *.h files in bsp\Generated_Code directory
    attrib -R *
    del /Q *.h 

    rem Copy default PE_LDD.h to bsp\Generated_Code
    copy /Y ..\..\..\..\mqx\source\bsp\twrk60n512\PE_LDD.h .

rem skip copying of generated files for IAR compiler
if /I "%~2" == "iar" goto gen_files_copy_skip

rem Copy Processor Expert generated files into Generated_Code directory
if not exist ..\..\..\..\mqx\build\cw10\bsp_twrk60n512\Generated_Code\PE_LDD.h goto gen_files_copy_skip
    rem Copy PE generated files to bsp\Generated_Code
    copy /Y ..\..\..\..\mqx\build\cw10\bsp_twrk60n512\Generated_Code\*.h .
    copy /Y ..\..\..\..\mqx\build\cw10\bsp_twrk60n512\Sources\*.h .

:gen_files_copy_skip

rem Generate library readme file
call "%~dp0\write_readme.bat" > ..\twrk60n512_lib.txt