@echo off

rem Make sure we are in target directory
call "%~dp0/verify_dir.bat" %1
if %ERRORLEVEL% NEQ 0 exit 1
attrib -R *

rem  Configuration header files

for %%F in (..\..\..\config\common\*.h)     do copy /Y /B ..\..\..\mqx\source\include\dontchg.h + %%F ..\%%~nF%%~xF
for %%F in (..\..\..\config\m5208evb\*.h)  do copy /Y /B ..\..\..\mqx\source\include\dontchg.h + %%F ..\%%~nF%%~xF

if /I "%~2" == "iar" goto comp_iar

rem  CodeWarrior Compiler

:comp_cw
mkdir dbg
copy /Y ..\..\..\mqx\source\bsp\m5208evb\cw\extram.lcf .
copy /Y ..\..\..\mqx\source\bsp\m5208evb\cw\extflash.lcf .
copy /Y ..\..\..\mqx\source\bsp\m5208evb\cw\dbg\m5208evb.mem .\dbg
copy /Y ..\..\..\mqx\source\bsp\m5208evb\cw\dbg\m5208evb.cfg .\dbg
goto comp_done

rem  IAR Compiler

:comp_iar
rem TODO: IAR SUPPORT
goto comp_done

rem  End of Compiler-specific files

:comp_done

rem  Board-specific BSP files
copy /Y ..\..\..\mqx\source\bsp\m5208evb\bsp.h .
copy /Y ..\..\..\mqx\source\bsp\m5208evb\bsp_rev.h .
copy /Y ..\..\..\mqx\source\bsp\m5208evb\m5208evb.h .
rem  Board-specific IO driver files

copy /Y ..\..\..\mqx\source\include\io_rev.h .
copy /Y ..\..\..\mqx\source\io\int_ctrl\int_ctrl_mcf520.h .
copy /Y ..\..\..\mqx\source\io\timer\timer_mcf520.h .

copy /Y ..\..\..\mqx\source\io\enet\ethernet.h .
copy /Y ..\..\..\mqx\source\io\enet\enet.h .
copy /Y ..\..\..\mqx\source\io\enet\mcf5xxx_fec\mcf520_fec.h .
copy /Y ..\..\..\mqx\source\io\enet\mcf5xxx_fec\mcf5xxx_fec_prv.h .
copy /Y ..\..\..\mqx\source\io\enet\phy\phy_dp83xxx.h .
copy /Y ..\..\..\mqx\source\io\enet\enet_wifi.h .

copy /Y ..\..\..\mqx\source\io\io_dun\io_dun.h .
copy /Y ..\..\..\mqx\source\io\io_mem\io_mem.h .
copy /Y ..\..\..\mqx\source\io\io_mem\iomemprv.h .
copy /Y ..\..\..\mqx\source\io\io_null\io_null.h .
copy /Y ..\..\..\mqx\source\io\serial\serial.h  .
copy /Y ..\..\..\mqx\source\io\serial\serl_mcf52xx.h .
copy /Y ..\..\..\mqx\source\include\pcb.h  .
copy /Y ..\..\..\mqx\source\io\pcb\io_pcb.h .
copy /Y ..\..\..\mqx\source\io\pcb\mqxa\pcb_mqxa.h .
copy /Y ..\..\..\mqx\source\io\can\flexcan\flexcan.h .
copy /Y ..\..\..\mqx\source\io\rtc\rtc.h .
copy /Y ..\..\..\mqx\source\io\tfs\tfs.h .
copy /Y ..\..\..\mqx\source\io\spi\spi.h .
copy /Y ..\..\..\mqx\source\io\spi\spi_mcf5xxx_qspi.h .
copy /Y ..\..\..\mqx\source\io\usb\usb_bsp.h .
copy /Y ..\..\..\mqx\source\io\i2c\i2c.h  .
copy /Y ..\..\..\mqx\source\io\i2c\i2c_mcf52xx.h .
copy /Y ..\..\..\mqx\source\io\flashx\flashx.h .
copy /Y ..\..\..\mqx\source\io\flashx\spansion\29wsxxxN.h .
copy /Y ..\..\..\mqx\source\io\gpio\io_gpio.h .
copy /Y ..\..\..\mqx\source\io\gpio\mcf520\io_gpio_mcf520.h .


rem  Generate library readme file

call "%~p0\write_readme.bat" > ..\m5208evb_lib.txt
