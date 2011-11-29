@ECHO OFF

IF "%~1"=="" GOTO HelpScreen 

:Install
echo  **** Installing CW10.1 Task Aware Debugging and New Project Wizard Plugins ***
echo  **** It can take up to 60 seconds ***  
if exist "%~1/MCU/bin/plugins/Debugger/rtos/mqx/tools/tad/mqx.tad"  "%~1/eclipse/cwidec.exe" -nosplash -application org.eclipse.equinox.p2.director -repository file:"%CD%/mqx_p2_repository/" -uninstallIU com.freescale.mqx.feature.group -destination "%~1/eclipse" -profile PlatformProfile
"%~1/eclipse/cwidec.exe" -nosplash -application org.eclipse.equinox.p2.director -repository file:"%CD%/mqx_p2_repository/" -installIU com.freescale.mqx.feature.group -destination "%~1/eclipse" -profile PlatformProfile

echo  **** Installing CW10.1 Processor Expert MQX RTOS Adapter update ****
xcopy /S /I /F /Y /Q "%CD%/mqx_rtos_adapter/*" "%~1/MCU/ProcessorExpert"
echo  **** Done ****
GOTO End

:HelpScreen
echo This batch file re-installs CW10 Task Aware Debugging and New Project wizard plugins
echo     Usage:   install_cw10_plugin.bat "<Path to CW10.1 installation>"
echo     Example  install_cw10_plugin.bat "c:\Program Files\Freescale\CW MCU v10.1"

:End