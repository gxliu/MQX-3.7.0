@echo off

rem Make sure we are in target directory
call "%~dp0/verify_dir.bat" %1
if %ERRORLEVEL% NEQ 0 exit 1

attrib -R *

rem  Configuration header files

for %%F in (..\..\..\config\common\*.h)      do copy /Y /B ..\..\..\mqx\source\include\dontchg.h + %%F ..\%%~nF%%~xF
for %%F in (..\..\..\config\twrmpc5125\*.h)  do copy /Y /B ..\..\..\mqx\source\include\dontchg.h + %%F ..\%%~nF%%~xF

rem  Compiler-specific BSP files
mkdir dbg
copy /Y ..\..\..\mqx\source\bsp\twrmpc5125\cw\extram.lcf .
copy /Y ..\..\..\mqx\source\bsp\twrmpc5125\cw\extnand.lcf .
copy /Y ..\..\..\mqx\source\bsp\twrmpc5125\cw\bootloader_extram.lcf .
copy /Y ..\..\..\mqx\source\bsp\twrmpc5125\cw\bootloader_extnand.lcf .
copy /Y ..\..\..\mqx\source\bsp\twrmpc5125\cw\dbg\twrmpc5125.cfg .\dbg
copy /Y ..\..\..\mqx\source\bsp\twrmpc5125\cw\dbg\twrmpc5125.mem .\dbg

rem  Board-specific BSP files

copy /Y ..\..\..\mqx\source\bsp\twrmpc5125\bsp.h .
copy /Y ..\..\..\mqx\source\bsp\twrmpc5125\bsp_rev.h .
copy /Y ..\..\..\mqx\source\bsp\twrmpc5125\twrmpc5125.h .
copy /Y ..\..\..\mqx\source\bsp\twrmpc5125\bootstrap.h .

rem  Board-specific IO driver files

copy /Y ..\..\..\mqx\source\include\io_rev.h .
copy /Y ..\..\..\mqx\source\io\int_ctrl\int_ctrl_mpc5125.h .
copy /Y ..\..\..\mqx\source\io\timer\timer_mpc512x.h .
copy /Y ..\..\..\mqx\source\io\timer\timer_e300dec.h .

copy /Y ..\..\..\mqx\source\io\enet\ethernet.h .
copy /Y ..\..\..\mqx\source\io\enet\enet.h .
copy /Y ..\..\..\mqx\source\io\enet\enet_wifi.h .
copy /Y ..\..\..\mqx\source\io\enet\mpc512x_fec\mpc5125_fec.h .
copy /Y ..\..\..\mqx\source\io\enet\mpc512x_fec\mpc5125_fec_prv.h .
copy /Y ..\..\..\mqx\source\io\enet\phy\phy_lan8710.h .
copy /Y ..\..\..\mqx\source\io\enet\phy\phy_ksz8041.h .

copy /Y ..\..\..\mqx\source\io\io_dun\io_dun.h .
copy /Y ..\..\..\mqx\source\io\io_mem\io_mem.h .
copy /Y ..\..\..\mqx\source\io\io_mem\iomemprv.h .
copy /Y ..\..\..\mqx\source\io\pcb\io_pcb.h .
copy /Y ..\..\..\mqx\source\io\pcb\mqxa\pcb_mqxa.h .
copy /Y ..\..\..\mqx\source\io\io_null\io_null.h .

copy /Y ..\..\..\mqx\source\io\serial\serial.h  .
copy /Y ..\..\..\mqx\source\io\serial\serl_mpc5125.h .

copy /Y ..\..\..\mqx\source\io\can\mscan\mscan.h .
copy /Y ..\..\..\mqx\source\io\can\mscan\mscan_mpc5125.h .

copy /Y ..\..\..\mqx\source\io\rtc\rtc.h .
copy /Y ..\..\..\mqx\source\io\rtc\irtc_mpc512x.h .

copy /Y ..\..\..\mqx\source\io\tfs\tfs.h .

copy /Y ..\..\..\mqx\source\io\display\display.h .
copy /Y ..\..\..\mqx\source\io\display\diu\diu.h .

copy /Y ..\..\..\mqx\source\io\i2c\i2c.h .
copy /Y ..\..\..\mqx\source\io\i2c\i2c_mpc512x.h
copy /Y ..\..\..\mqx\source\io\pccard\apccard_mpc5125.h .
copy /Y ..\..\..\mqx\source\io\pccard\pccardlpc_mpc5125.h .
copy /Y ..\..\..\mqx\source\io\pcflash\pcflash_mpc5125.h .
copy /Y ..\..\..\mqx\source\io\pcflash\ata_mpc5125.h .
copy /Y ..\..\..\mqx\source\io\spi\spi_mpc512x.h .
copy /Y ..\..\..\mqx\source\io\spi\spi.h .
copy /Y ..\..\..\mqx\source\io\nandflash\nandflash.h .
copy /Y ..\..\..\mqx\source\io\nandflash\nfc\nfc.h .
copy /Y ..\..\..\mqx\source\io\nandflash\nandbootloader.h .
copy /Y ..\..\..\mqx\source\io\sdcard\sdcard.h .
copy /Y ..\..\..\mqx\source\io\sdhc\sdhc.h .
copy /Y ..\..\..\mqx\source\io\sdcard\sdcard_spi\sdcard_spi.h .

copy /Y ..\..\..\mqx\source\io\usb\usb_bsp.h .
rem  Generate library readme file

call "%~dp0\write_readme.bat" > ..\twrmpc5125_lib.txt

@echo off

