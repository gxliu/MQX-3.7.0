
echo "~/Freescale/CodeWarrior_MCU_10.1/eclipse/cwide -nosplash -application org.eclipse.equinox.p2.director -repository file:/home/zorg/j.test/MQX_3.7.0_1/tools/codewarrior_extensions/CW\ MCU\ v10.1/mqx_p2_repository -installIU com.freescale.mqx.feature.group -destination /home/zorg/Freescale/CodeWarrior_MCU_10.1/eclipse -profile PlatformProfile"
echo "xcopy /S /I /F /Y /Q "%CD%/mqx_rtos_adapter/*" "%~1/MCU/ProcessorExpert""
