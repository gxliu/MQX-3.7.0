#!/bin/sh

comp_cw()
{
  cp -f ../../../mqx/source/psp/cortex/cw_comp.h  .
}

comp_iar()
{
  cp -f ../../../mqx/source/psp/cortex/iar_comp.h  .
}

cp -f ../../../mqx/source/psp/cortex/psp.h  .
cp -f ../../../mqx/source/psp/cortex/psptypes.h  .
cp -f ../../../mqx/source/psp/cortex/psp_cpu.h  .
cp -f ../../../mqx/source/psp/cortex/psp_rev.h  .
cp -f ../../../mqx/source/psp/cortex/psp_time.h  .
cp -f ../../../mqx/source/psp/cortex/psp_math.h  .
cp -f ../../../mqx/source/psp/cortex/psp_comp.h  .

cp -f ../../../mqx/source/psp/cortex/cortex.h  .

#cp -f ../../../mqx/source/psp/cortex/MK40N512MD100.h .
#cp -f ../../../mqx/source/psp/cortex/MK60N512MD100.h .

cp -f ../../../mqx/source/psp/cortex/psp_cpudef.h  .

cp -f ../../../mqx/source/psp/cortex/psp_supp.h  .

cp -f ../../../mqx/source/include/eds.h  .
cp -f ../../../mqx/source/include/edserial.h  .
cp -f ../../../mqx/source/include/event.h  .
cp -f ../../../mqx/source/include/fio.h  .
cp -f ../../../mqx/source/include/gen_rev.h  .
cp -f ../../../mqx/source/include/io.h  .
cp -f ../../../mqx/source/include/io_rev.h  .
cp -f ../../../mqx/source/include/ipc.h  .
cp -f ../../../mqx/source/include/ipc_pcb.h  .
cp -f ../../../mqx/source/include/klog.h  .
cp -f ../../../mqx/source/include/log.h  .
cp -f ../../../mqx/source/include/lwevent.h  .
cp -f ../../../mqx/source/include/lwlog.h  .
cp -f ../../../mqx/source/include/lwmem.h  .
cp -f ../../../mqx/source/include/lwmsgq.h  .
cp -f ../../../mqx/source/include/lwtimer.h  .
cp -f ../../../mqx/source/include/message.h  .
cp -f ../../../mqx/source/include/mqx.h  .
cp -f ../../../mqx/source/include/mqx_cpudef.h  .
cp -f ../../../mqx/source/include/mqx_cnfg.h .
cp -f ../../../mqx/source/include/mqx_ioc.h  .
cp -f ../../../mqx/source/include/mqx_str.h  .
cp -f ../../../mqx/source/include/mutex.h  .
cp -f ../../../mqx/source/include/name.h  .
cp -f ../../../mqx/source/include/part.h  .
cp -f ../../../mqx/source/include/pcb.h  .
cp -f ../../../mqx/source/include/posix.h  .

#cp -f ../../../mqx/source/include/rterrchk.h  .

cp -f ../../../mqx/source/include/sem.h  .
cp -f ../../../mqx/source/include/timer.h  .
cp -f ../../../mqx/source/include/watchdog.h .
cp -f ../../../mqx/source/include/ioctl.h .

cp -f ../../../mqx/source/io/serial/serial.h .

cp -f ../../../mqx/source/tad/tad.h .

if [ "$2" == "iar" ]; then
 comp_iar
else
 comp_cw
fi

return 0

@echo off

attrib -R *

rem  Cortex specific files

copy /Y ..\..\..\mqx\source\psp\cortex\psp.h  .
copy /Y ..\..\..\mqx\source\psp\cortex\psptypes.h  .
copy /Y ..\..\..\mqx\source\psp\cortex\psp_cpu.h  .
copy /Y ..\..\..\mqx\source\psp\cortex\psp_rev.h  .
copy /Y ..\..\..\mqx\source\psp\cortex\psp_time.h  .
copy /Y ..\..\..\mqx\source\psp\cortex\psp_math.h  .
copy /Y ..\..\..\mqx\source\psp\cortex\psp_comp.h  .

copy /Y ..\..\..\mqx\source\psp\cortex\cortex.h  .
copy /Y ..\..\..\mqx\source\psp\cortex\MK40N512MD100.h .
copy /Y ..\..\..\mqx\source\psp\cortex\MK60N512MD100.h .

copy /Y ..\..\..\mqx\source\psp\cortex\psp_cpudef.h  .

copy /Y ..\..\..\mqx\source\psp\cortex\psp_supp.h  .

copy /Y ..\..\..\mqx\source\include\eds.h  .
copy /Y ..\..\..\mqx\source\include\edserial.h  .
copy /Y ..\..\..\mqx\source\include\event.h  .
copy /Y ..\..\..\mqx\source\include\fio.h  .
copy /Y ..\..\..\mqx\source\include\gen_rev.h  .
copy /Y ..\..\..\mqx\source\include\io.h  .
copy /Y ..\..\..\mqx\source\include\io_rev.h  .
copy /Y ..\..\..\mqx\source\include\ipc.h  .
copy /Y ..\..\..\mqx\source\include\ipc_pcb.h  .
copy /Y ..\..\..\mqx\source\include\klog.h  .
copy /Y ..\..\..\mqx\source\include\log.h  .
copy /Y ..\..\..\mqx\source\include\lwevent.h  .
copy /Y ..\..\..\mqx\source\include\lwlog.h  .
copy /Y ..\..\..\mqx\source\include\lwmem.h  .
copy /Y ..\..\..\mqx\source\include\lwmsgq.h  .
copy /Y ..\..\..\mqx\source\include\lwtimer.h  .
copy /Y ..\..\..\mqx\source\include\message.h  .
copy /Y ..\..\..\mqx\source\include\mqx.h  .
copy /Y ..\..\..\mqx\source\include\mqx_cpudef.h  .
copy /Y ..\..\..\mqx\source\include\mqx_cnfg.h .
copy /Y ..\..\..\mqx\source\include\mqx_ioc.h  .
copy /Y ..\..\..\mqx\source\include\mqx_str.h  .
copy /Y ..\..\..\mqx\source\include\mutex.h  .
copy /Y ..\..\..\mqx\source\include\name.h  .
copy /Y ..\..\..\mqx\source\include\part.h  .
copy /Y ..\..\..\mqx\source\include\pcb.h  .
copy /Y ..\..\..\mqx\source\include\posix.h  .
copy /Y ..\..\..\mqx\source\include\rterrchk.h  .
copy /Y ..\..\..\mqx\source\include\sem.h  .
copy /Y ..\..\..\mqx\source\include\timer.h  .
copy /Y ..\..\..\mqx\source\include\watchdog.h .
copy /Y ..\..\..\mqx\source\include\ioctl.h .

rem Required by RTCS
copy /Y ..\..\..\mqx\source\io\serial\serial.h .

rem Required by SHELL
copy /Y ..\..\..\mqx\source\tad\tad.h .

rem  Compiler-specific PSP files

if /I "%~2" == "iar" goto comp_iar

rem  CodeWarrior Compiler

:comp_cw
copy /Y ..\..\..\mqx\source\psp\cortex\cw_comp.h  .
goto comp_done

rem  IAR Compiler

:comp_iar
copy /Y ..\..\..\mqx\source\psp\cortex\iar_comp.h  .
goto comp_done

rem  End of Compiler-specific files

:comp_done

