How-to Program Signal Generator on DEMOEM board.

To emulate analog signals on MCF51EM256 the DEMOEM board incorporates preprogrammed. 
MC9S08QE8 (20-pin SOIC) with:
    Three Potentiometers
    6 PWM outputs with low-pass filters in order to generate 60/50 Hz signals 
      connected to MCF51EM256 ADC inputs via jumpers (AD4-AD6, DADP0-DADP2)
    6 LEDs, one for each PWM output
    1 LED connected to a GPIO
    3 buttons

Programming procedure:

1.  Turn SYSTEM_POWER switch K6  OFF
2.  Switch J39, J40 jumpers to QE position
3.  Connect USB cable
4.  Turn SYSTEM_POWER switch K6  ON

5.  To program srecord into QE you have to:  
6.  Open standalone version of HIWAVE.exe debugger. It can be found in
    "C:\Program Files\Freescale\CodeWarrior for Microcontrollers 6.x\prog\hiwave.exe"
7.    Click File-> Load Application (CTRL+L), click YES on popup window 
    to select programming connection

8.  Select HCS08 processor and P&E Multilink/Cyclone Pro connection and click OK.
9.  Choose 9S08QE8 device and click OK

10. When PEMICRO Connection Manager window pop ups, click Connect(Reset)
11. Select Files of type (Motorola S-Record (*.s?) and locate image file.
    
    + Three phase generator "3phgen.s19" is needed for "3phmeter_m51emdemo" demo
    "{MQX}\src\demo\3phmeter\m51emdemo_signal_generator\3phgen.s19"
    "{MQX}\src\demo\3phmeter\cwmcu6x\3phmeter_m51emdemo.mcp"
    
    + ADC signal generator.    
    The "adcgen.s19" contains software for adc example
    "{MQX}\src\mqx\examples\adc\m51emdemo_signal_generator\adcgen.s19"
    "{MQX}\src\mqx\examples\adc\cwmcu6x\adc_m51emdemo.mcp"

12. Click Yes to load image containing flash memory data. 
13. The debugger loads image into QE8 and the programming procedure is finished.
14. Turn SYSTEM_POWER switch K6  OFF.
15. Switch J39, J40 jumpers back to EM position.