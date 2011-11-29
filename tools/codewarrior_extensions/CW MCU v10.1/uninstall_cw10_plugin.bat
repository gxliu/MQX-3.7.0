@ECHO OFF

IF "%~1"=="" GOTO HelpScreen 

:Install
echo  **** Uninstalling CW10.1 Task Aware Debugging and New Project Wizard Plugins ***
echo  **** It can take up to 60 seconds ***  
"%~1/eclipse/cwidec.exe" -nosplash -application org.eclipse.equinox.p2.director -repository file:"%CD%/mqx_p2_repository/" -uninstallIU com.freescale.mqx.feature.group -destination "%~1/eclipse" -profile PlatformProfile
echo  **** Done ***
GOTO End

:HelpScreen
echo This batch file uninstalls CW10 Task Aware Debugging and New Project wizard plugins
echo     Usage:   uninstall_cw10_plugin.bat "<Path to CW10.1 installation>"
echo     Example  uninstall_cw10_plugin.bat "c:\Program Files\Freescale\CW MCU v10.1"
 
:End  