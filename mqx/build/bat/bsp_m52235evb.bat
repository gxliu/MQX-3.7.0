@echo off

rem Make sure we are in target directory
call "%~dp0/verify_dir.bat" %1
if %ERRORLEVEL% NEQ 0 exit 1

attrib -R *

rem  Configuration header files

for %%F in (..\..\..\config\common\*.h)     do copy /Y /B ..\..\..\mqx\source\include\dontchg.h + %%F ..\%%~nF%%~xF
for %%F in (..\..\..\config\m52235evb\*.h)  do copy /Y /B ..\..\..\mqx\source\include\dontchg.h + %%F ..\%%~nF%%~xF

rem  Compiler-specific BSP files

if /I "%~2" == "iar" goto comp_iar

rem  CodeWarrior Compiler

:comp_cw
mkdir dbg
copy /Y ..\..\..\mqx\source\bsp\m52235evb\cw\intram.lcf .
copy /Y ..\..\..\mqx\source\bsp\m52235evb\cw\intflash.lcf .
copy /Y ..\..\..\mqx\source\bsp\m52235evb\cw\extmram.lcf .
copy /Y ..\..\..\mqx\source\bsp\m52235evb\cw\dbg\m52235evb.mem .\dbg
copy /Y ..\..\..\mqx\source\bsp\m52235evb\cw\dbg\m52235evb.cfg .\dbg

goto comp_done

rem  IAR Compiler

:comp_iar
rem TODO: IAR SUPPORT
goto comp_done

rem  End of Compiler-specific files

:comp_done

rem  Board-specific BSP files

copy /Y ..\..\..\mqx\source\bsp\m52235evb\bsp.h .
copy /Y ..\..\..\mqx\source\bsp\m52235evb\bsp_rev.h .
copy /Y ..\..\..\mqx\source\bsp\m52235evb\m52235evb.h .

rem  Board-specific IO driver files

copy /Y ..\..\..\mqx\source\include\io_rev.h .
copy /Y ..\..\..\mqx\source\io\adc\adc.h .
copy /Y ..\..\..\mqx\source\io\adc\mcf522xx\adc_mcf522xx.h .
copy /Y ..\..\..\mqx\source\io\int_ctrl\int_ctrl_mcf5223.h .
copy /Y ..\..\..\mqx\source\io\timer\timer_mcf5223.h .
copy /Y ..\..\..\mqx\source\io\enet\ethernet.h .
copy /Y ..\..\..\mqx\source\io\enet\enet.h .
copy /Y ..\..\..\mqx\source\io\enet\enet_wifi.h .
copy /Y ..\..\..\mqx\source\io\enet\mcf5xxx_fec\mcf5223_fec.h .
copy /Y ..\..\..\mqx\source\io\enet\mcf5xxx_fec\mcf5xxx_fec_prv.h .
copy /Y ..\..\..\mqx\source\io\enet\phy\phy_mcf5223x.h .

copy /Y ..\..\..\mqx\source\io\io_dun\io_dun.h .
copy /Y ..\..\..\mqx\source\io\io_mem\io_mem.h .
copy /Y ..\..\..\mqx\source\io\io_mem\iomemprv.h .
copy /Y ..\..\..\mqx\source\io\io_null\io_null.h .
copy /Y ..\..\..\mqx\source\io\pcb\io_pcb.h .
copy /Y ..\..\..\mqx\source\io\pcb\mqxa\pcb_mqxa.h .
copy /Y ..\..\..\mqx\source\io\serial\serial.h  .
copy /Y ..\..\..\mqx\source\io\serial\serl_mcf52xx.h .
copy /Y ..\..\..\mqx\source\io\gpio\io_gpio.h .
copy /Y ..\..\..\mqx\source\io\gpio\mcf5223\io_gpio_mcf5223.h .
copy /Y ..\..\..\mqx\source\io\spi\spi.h .
copy /Y ..\..\..\mqx\source\io\spi\spi_mcf5xxx_qspi.h .
copy /Y ..\..\..\mqx\source\io\can\flexcan\flexcan.h .
copy /Y ..\..\..\mqx\source\io\usb\usb_bsp.h .
copy /Y ..\..\..\mqx\source\io\rtc\rtc.h .
copy /Y ..\..\..\mqx\source\io\rtc\rtc_mcf52xx.h .
copy /Y ..\..\..\mqx\source\io\i2c\i2c.h  .
copy /Y ..\..\..\mqx\source\io\i2c\i2c_mcf52xx.h .
copy /Y ..\..\..\mqx\source\io\tfs\tfs.h .
copy /Y ..\..\..\mqx\source\io\flashx\flashx.h .
copy /Y ..\..\..\mqx\source\io\flashx\freescale\flash_mcf5223.h .



rem  Generate library readme file

call "%~dp0\write_readme.bat" > ..\m52235evb_lib.txt
