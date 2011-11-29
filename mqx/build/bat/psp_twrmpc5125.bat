@echo off

rem make sure we are in target directory
call "%~dp0/verify_dir.bat" %1
if %ERRORLEVEL% NEQ 0 exit 1

rem  Common non-private header files

call "%~dp0\psp_mpc.bat" %1 %2

rem  Configuration header files

for %%F in (..\..\..\config\common\*.h)     do copy /Y /B ..\..\..\mqx\source\include\dontchg.h + %%F ..\%%~nF%%~xF
for %%F in (..\..\..\config\twrmpc5125\*.h)  do copy /Y /B ..\..\..\mqx\source\include\dontchg.h + %%F ..\%%~nF%%~xF

rem  Processor-specific PSP files
copy /Y ..\..\..\mqx\source\psp\powerpc\mpc5125.h  		    
copy /Y ..\..\..\mqx\source\psp\powerpc\mpc512x_bdlc.h  	
copy /Y ..\..\..\mqx\source\psp\powerpc\mpc512x_ccm.h  		
copy /Y ..\..\..\mqx\source\psp\powerpc\mpc512x_csbarb.h  	
copy /Y ..\..\..\mqx\source\psp\powerpc\mpc512x_diu.h  		
copy /Y ..\..\..\mqx\source\psp\powerpc\mpc512x_dma.h  		
copy /Y ..\..\..\mqx\source\psp\powerpc\mpc512x_fec.h  		
copy /Y ..\..\..\mqx\source\psp\powerpc\mpc512x_gpio.h      
copy /Y ..\..\..\mqx\source\psp\powerpc\mpc512x_gpt.h  	    
copy /Y ..\..\..\mqx\source\psp\powerpc\mpc512x_i2c.h  	    
copy /Y ..\..\..\mqx\source\psp\powerpc\mpc512x_iim.h  	    
copy /Y ..\..\..\mqx\source\psp\powerpc\mpc512x_ioc.h  	    
copy /Y ..\..\..\mqx\source\psp\powerpc\mpc512x_ipic.h      
copy /Y ..\..\..\mqx\source\psp\powerpc\mpc512x_lpc.h  	    
copy /Y ..\..\..\mqx\source\psp\powerpc\mpc512x_mddrc.h     
copy /Y ..\..\..\mqx\source\psp\powerpc\mpc512x_mscan.h    
copy /Y ..\..\..\mqx\source\psp\powerpc\mpc512x_prioman.h  
copy /Y ..\..\..\mqx\source\psp\powerpc\mpc512x_pmc.h  		
copy /Y ..\..\..\mqx\source\psp\powerpc\mpc512x_psc.h  		
copy /Y ..\..\..\mqx\source\psp\powerpc\mpc512x_rm.h  		
copy /Y ..\..\..\mqx\source\psp\powerpc\mpc512x_rtc.h  		
copy /Y ..\..\..\mqx\source\psp\powerpc\mpc512x_sc.h  		
copy /Y ..\..\..\mqx\source\psp\powerpc\mpc512x_sdhc.h  	
copy /Y ..\..\..\mqx\source\psp\powerpc\mpc512x_usb.h  
copy /Y ..\..\..\mqx\source\psp\powerpc\mpc512x_wdt.h  	   
copy /Y ..\..\..\mqx\source\psp\powerpc\reg_nfc.h
copy /Y ..\..\..\mqx\source\psp\powerpc\e300core.h      	
