@echo off

rem Make sure we are in target directory
call "%~dp0/verify_dir.bat" %1
if %ERRORLEVEL% NEQ 0 exit 1
attrib -R *

rem  Configuration header files

for %%F in (..\..\..\config\common\*.h)     do copy /Y /B ..\..\..\mqx\source\include\dontchg.h + %%F ..\%%~nF%%~xF
for %%F in (..\..\..\config\twrmcf51mm\*.h)  do copy /Y /B ..\..\..\mqx\source\include\dontchg.h + %%F ..\%%~nF%%~xF

rem  Compiler-specific BSP files

if /I "%~2" == "iar" goto comp_iar

rem  CodeWarrior Compiler

:comp_cw
mkdir dbg
copy /Y ..\..\..\mqx\source\bsp\twrmcf51mm\cw\intflash.lcf .
copy /Y ..\..\..\mqx\source\bsp\twrmcf51mm\cw\dbg\CFV1_OSBDM_Erase_Unsecure.cmd .\dbg
copy /Y ..\..\..\mqx\source\bsp\twrmcf51mm\cw\dbg\CFV1_OSBDM_Postload.cmd .\dbg
copy /Y ..\..\..\mqx\source\bsp\twrmcf51mm\cw\dbg\CFV1_OSBDM_Preload.cmd .\dbg
copy /Y ..\..\..\mqx\source\bsp\twrmcf51mm\cw\dbg\CFV1_OSBDM_Reset.cmd .\dbg
copy /Y ..\..\..\mqx\source\bsp\twrmcf51mm\cw\dbg\CFV1_OSBDM_Startup.cmd .\dbg

rem copy /Y ..\..\..\mqx\source\bsp\twrmcf51mm\cw\dbg\CFV1_PEBDM_Postload.cmd .\dbg
rem copy /Y ..\..\..\mqx\source\bsp\twrmcf51mm\cw\dbg\CFV1_PEBDM_Preload.cmd .\dbg
rem copy /Y ..\..\..\mqx\source\bsp\twrmcf51mm\cw\dbg\CFV1_PEBDM_Reset.cmd .\dbg
rem copy /Y ..\..\..\mqx\source\bsp\twrmcf51mm\cw\dbg\CFV1_PEBDM_Startup.cmd .\dbg
rem copy /Y ..\..\..\mqx\source\bsp\twrmcf51mm\cw\dbg\CFV1_PEBDM.ini .\dbg

copy /Y ..\..\..\mqx\source\bsp\twrmcf51mm\cw\dbg\CFV1_OSBDM.ini .\dbg

copy /Y ..\..\..\mqx\source\bsp\twrmcf51mm\cw\dbg\Default.mem .\dbg
copy /Y ..\..\..\mqx\source\bsp\twrmcf51mm\cw\dbg\twrmcf51mm.cfg .\dbg
copy /Y ..\..\..\mqx\source\bsp\twrmcf51mm\cw\dbg\twrmcf51mm.mem .\dbg
goto comp_done

rem  IAR Compiler

:comp_iar
rem TODO: IAR SUPPORT
goto comp_done

rem  End of Compiler-specific files

:comp_done

rem  Board-specific BSP files
copy /Y ..\..\..\mqx\source\bsp\twrmcf51mm\bsp.h .
copy /Y ..\..\..\mqx\source\bsp\twrmcf51mm\bsp_rev.h .
copy /Y ..\..\..\mqx\source\bsp\twrmcf51mm\twrmcf51mm.h .

rem  Board-specific IO driver files

copy /Y ..\..\..\mqx\source\include\io_rev.h .
copy /Y ..\..\..\mqx\source\io\int_ctrl\int_ctrl_mcf51mm.h .
copy /Y ..\..\..\mqx\source\io\timer\timer_mcf51mm.h .
copy /Y ..\..\..\mqx\source\io\enet\ethernet.h .
copy /Y ..\..\..\mqx\source\io\enet\enet.h .
copy /Y ..\..\..\mqx\source\io\enet\enet_wifi.h .
copy /Y ..\..\..\mqx\source\io\io_dun\io_dun.h .
copy /Y ..\..\..\mqx\source\io\io_mem\io_mem.h .
copy /Y ..\..\..\mqx\source\io\io_mem\iomemprv.h .
copy /Y ..\..\..\mqx\source\io\io_null\io_null.h .
copy /Y ..\..\..\mqx\source\io\pcb\io_pcb.h .
copy /Y ..\..\..\mqx\source\io\pcb\mqxa\pcb_mqxa.h .
copy /Y ..\..\..\mqx\source\io\serial\serial.h  .
copy /Y ..\..\..\mqx\source\io\serial\serinprv.h .
copy /Y ..\..\..\mqx\source\io\serial\serl_mcf51xx.h .
copy /Y ..\..\..\mqx\source\io\gpio\io_gpio.h .
copy /Y ..\..\..\mqx\source\io\gpio\mcf51mm\io_gpio_mcf51mm.h .
copy /Y ..\..\..\mqx\source\io\usb\usb_bsp.h .
copy /Y ..\..\..\mqx\source\io\pccard\apccard.h .
copy /Y ..\..\..\mqx\source\io\pcflash\pcflash.h .
copy /Y ..\..\..\mqx\source\io\pcflash\ata.h .
copy /Y ..\..\..\mqx\source\io\pccard\apccard.h .
copy /Y ..\..\..\mqx\source\io\pccard\pccardflexbus.h .
copy /Y ..\..\..\mqx\source\io\pcflash\pcflash.h .
copy /Y ..\..\..\mqx\source\io\pcflash\ata.h .
copy /Y ..\..\..\mqx\source\io\i2c\i2c.h  .
copy /Y ..\..\..\mqx\source\io\i2c\i2c_mcf51xx.h .
copy /Y ..\..\..\mqx\source\io\tfs\tfs.h .
copy /Y ..\..\..\mqx\source\io\adc\adc_conf.h .
copy /Y ..\..\..\mqx\source\io\adc\adc.h .
copy /Y ..\..\..\mqx\source\io\adc\mcf51mm\adc_mcf51mm.h .
copy /Y ..\..\..\mqx\source\io\spi\spi.h  .
copy /Y ..\..\..\mqx\source\io\spi\spi_mcf5xxx_spi8.h .
copy /Y ..\..\..\mqx\source\io\spi\spi_mcf5xxx_spi16.h .
copy /Y ..\..\..\mqx\source\io\flashx\flashx.h .
copy /Y ..\..\..\mqx\source\io\flashx\freescale\flash_mcf51mm.h .
copy /Y ..\..\..\mqx\source\io\sdcard\sdcard.h  .
copy /Y ..\..\..\mqx\source\io\sdcard\sdcard_spi\sdcard_spi.h .
copy /Y ..\..\..\mqx\source\io\rtc\rtc.h  .
copy /Y ..\..\..\mqx\source\io\rtc\rtc_mcf51xx.h .
copy /Y ..\..\..\mqx\source\io\dac\dac_ldd.h  .
copy /Y ..\..\..\mqx\source\io\dac\dac_pdd_mcf51mm.h  .


rem  Generate library readme file

call "%~p0\write_readme.bat" > ..\twrmcf51mm_lib.txt
