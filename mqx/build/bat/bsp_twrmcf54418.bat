@echo off

rem Make sure we are in target directory
call "%~dp0/verify_dir.bat" %1
if %ERRORLEVEL% NEQ 0 exit 1

attrib -R *

rem  Configuration header files

for %%F in (..\..\..\config\common\*.h)     do copy /Y /B ..\..\..\mqx\source\include\dontchg.h + %%F ..\%%~nF%%~xF
for %%F in (..\..\..\config\twrmcf54418\*.h)  do copy /Y /B ..\..\..\mqx\source\include\dontchg.h + %%F ..\%%~nF%%~xF

rem  Compiler-specific BSP files

if /I "%~2" == "iar" goto comp_iar

rem  CodeWarrior Compiler

:comp_cw
mkdir dbg
copy /Y ..\..\..\mqx\source\bsp\twrmcf54418\cw\extram.lcf .
copy /Y ..\..\..\mqx\source\bsp\twrmcf54418\cw\extflash.lcf .
copy /Y ..\..\..\mqx\source\bsp\twrmcf54418\cw\dbg\twrmcf54418.mem .\dbg
copy /Y ..\..\..\mqx\source\bsp\twrmcf54418\cw\dbg\twrmcf54418.cfg .\dbg

goto comp_done

rem  IAR Compiler

:comp_iar
rem TODO: IAR SUPPORT
goto comp_done

rem  End of Compiler-specific files

:comp_done

rem  Board-specific BSP files

copy /Y ..\..\..\mqx\source\bsp\twrmcf54418\bsp.h .
copy /Y ..\..\..\mqx\source\bsp\twrmcf54418\bsp_rev.h .
copy /Y ..\..\..\mqx\source\bsp\twrmcf54418\twrmcf54418.h .

rem  Board-specific IO driver files

copy /Y ..\..\..\mqx\source\include\io_rev.h .
copy /Y ..\..\..\mqx\source\io\adc\adc.h .
copy /Y ..\..\..\mqx\source\io\adc\mcf544xx\adc_mcf544xx.h .

copy /Y ..\..\..\mqx\source\io\int_ctrl\int_ctrl_mcf5441.h .
copy /Y ..\..\..\mqx\source\io\timer\timer_mcf5441.h .
copy /Y ..\..\..\mqx\source\io\io_dun\io_dun.h .
copy /Y ..\..\..\mqx\source\io\io_mem\io_mem.h .
copy /Y ..\..\..\mqx\source\io\io_mem\iomemprv.h .
copy /Y ..\..\..\mqx\source\io\io_null\io_null.h .
copy /Y ..\..\..\mqx\source\io\pcb\io_pcb.h .
copy /Y ..\..\..\mqx\source\io\pcb\mqxa\pcb_mqxa.h .

copy /Y ..\..\..\mqx\source\io\serial\serial.h  .
copy /Y ..\..\..\mqx\source\io\serial\serl_mcf54xx.h .
copy /Y ..\..\..\mqx\source\io\gpio\io_gpio.h .
copy /Y ..\..\..\mqx\source\io\gpio\mcf5441\io_gpio_mcf5441.h  .
copy /Y ..\..\..\mqx\source\io\rtc\irtc_mcf5xxx.h .
copy /Y ..\..\..\mqx\source\io\rtc\irtc_mcf5441x.h .


copy /Y ..\..\..\mqx\source\io\enet\ethernet.h .
copy /Y ..\..\..\mqx\source\io\enet\enet.h .
copy /Y ..\..\..\mqx\source\io\enet\enet_wifi.h .
copy /Y ..\..\..\mqx\source\io\enet\macnet\macnet_mcf5441.h .
copy /Y ..\..\..\mqx\source\io\enet\macnet\macnet_1588.h .
copy /Y ..\..\..\mqx\source\io\enet\macnet\macnet_prv.h .
copy /Y ..\..\..\mqx\source\io\enet\phy\phy_dp83xxx.h .


copy /Y ..\..\..\mqx\source\io\tfs\tfs.h .
copy /Y ..\..\..\mqx\source\io\i2c\i2c.h .
copy /Y ..\..\..\mqx\source\io\i2c\i2c_mcf54xx.h .
copy /Y ..\..\..\mqx\source\io\nandflash\nandflash.h .
copy /Y ..\..\..\mqx\source\io\nandflash\nfc\nfc.h .
copy /Y ..\..\..\mqx\source\io\spi\spi.h .
copy /Y ..\..\..\mqx\source\io\spi\spi_mcf5xxx_dspi.h .
copy /Y ..\..\..\mqx\source\io\can\flexcan\flexcan.h .
copy /Y ..\..\..\mqx\source\io\sdcard\sdcard.h  .
copy /Y ..\..\..\mqx\source\io\sdcard\sdcard_spi\sdcard_spi.h .
copy /Y ..\..\..\mqx\source\io\sdcard\sdcard_esdhc\sdcard_esdhc.h .
copy /Y ..\..\..\mqx\source\io\esdhc\esdhc.h  .

copy /Y ..\..\..\mqx\source\io\pccard\apccard.h .
copy /Y ..\..\..\mqx\source\io\pccard\pccardflexbus.h .
copy /Y ..\..\..\mqx\source\io\pcflash\pcflash.h .
copy /Y ..\..\..\mqx\source\io\pcflash\ata.h .

copy /Y ..\..\..\mqx\source\io\usb\usb_bsp.h .


rem  Generate library readme file

call "%~dp0\write_readme.bat" > ..\twrmcf54418_lib.txt

