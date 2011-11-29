#ifndef __mpc5125_prioman_h__
#define __mpc5125_prioman_h__
/**HEADER********************************************************************
* 
* Copyright (c) 2008 Freescale Semiconductor;
* All Rights Reserved
*
* Copyright (c) 2004-2008 Embedded Access Inc.;
* All Rights Reserved
*
*************************************************************************** 
*
* THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR 
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  
* IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
* IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
* THE POSSIBILITY OF SUCH DAMAGE.
*
**************************************************************************
*
* $FileName: mpc512x_prioman.h$
* $Version :  3.7.3.0$
* $Date    :  Feb-7-2011$
*
* Comments:
*
*   This file contains definitions for the MPC5125 family and peripherals.
*
*END************************************************************************/

#define MPC5125_PRIOMAN_ADDR()       (&((VMPC5125_STRUCT_PTR) MPC5125_GET_IMMR() )->MDDRC.PRIOMAN)

#define MPC5125_DRAMPRIOM_PRIOMAN_CONFIG1                      0x080
#define MPC5125_DRAMPRIOM_PRIOMAN_CONFIG2                      0x084
#define MPC5125_DRAMPRIOM_HIPRIO_CONFIG                        0x088
#define MPC5125_DRAMPRIOM_LUT_TABLE0_MAIN_UP                   0x08C
#define MPC5125_DRAMPRIOM_LUT_TABLE1_MAIN_UP                   0x090
#define MPC5125_DRAMPRIOM_LUT_TABLE2_MAIN_UP                   0x094
#define MPC5125_DRAMPRIOM_LUT_TABLE3_MAIN_UP                   0x098
#define MPC5125_DRAMPRIOM_LUT_TABLE4_MAIN_UP                   0x09C
#define MPC5125_DRAMPRIOM_LUT_TABLE0_MAIN_LOW                  0x0A0
#define MPC5125_DRAMPRIOM_LUT_TABLE1_MAIN_LOW                  0x0A4
#define MPC5125_DRAMPRIOM_LUT_TABLE2_MAIN_LOW                  0x0A8
#define MPC5125_DRAMPRIOM_LUT_TABLE3_MAIN_LOW                  0x0AC
#define MPC5125_DRAMPRIOM_LUT_TABLE4_MAIN_LOW                  0x0B0
#define MPC5125_DRAMPRIOM_LUT_TABLE0_ALT_UP                    0x0B4
#define MPC5125_DRAMPRIOM_LUT_TABLE1_ALT_UP                    0x0B8
#define MPC5125_DRAMPRIOM_LUT_TABLE2_ALT_UP                    0x0BC
#define MPC5125_DRAMPRIOM_LUT_TABLE3_ALT_UP                    0x0C0
#define MPC5125_DRAMPRIOM_LUT_TABLE4_ALT_UP                    0x0C4
#define MPC5125_DRAMPRIOM_LUT_TABLE0_ALT_LOW                   0x0C8
#define MPC5125_DRAMPRIOM_LUT_TABLE1_ALT_LOW                   0x0CC
#define MPC5125_DRAMPRIOM_LUT_TABLE2_ALT_LOW                   0x0D0
#define MPC5125_DRAMPRIOM_LUT_TABLE3_ALT_LOW                   0x0D4
#define MPC5125_DRAMPRIOM_LUT_TABLE4_ALT_LOW                   0x0D8
#define MPC5125_DRAMPRIOM_PERF_MONITOR_CONFIG                  0x0DC
#define MPC5125_DRAMPRIOM_EVENT_TIME_COUNTER                   0x0E0
#define MPC5125_DRAMPRIOM_EVENT_TIME_PRESET                    0x0E4
#define MPC5125_DRAMPRIOM_PERF_MNTR1_ADDR_LOW                  0x0E8
#define MPC5125_DRAMPRIOM_PERF_MNTR2_ADDR_LOW                  0x0EC
#define MPC5125_DRAMPRIOM_PERF_MNTR1_ADDR_HI                   0x0F0
#define MPC5125_DRAMPRIOM_PERF_MNTR2_ADDR_HI                   0x0F4
#define MPC5125_DRAMPRIOM_PERF_MNTR1_READ_CNTR                 0x100
#define MPC5125_DRAMPRIOM_PERF_MNTR2_READ_CNTR                 0x104
#define MPC5125_DRAMPRIOM_PERF_MNTR1_WRITE_CNTR                0x108
#define MPC5125_DRAMPRIOM_PERF_MNTR2_WRITE_CNTR                0x10C
#define MPC5125_DRAMPRIOM_GRANTED_ACK_CNTR0                    0x110
#define MPC5125_DRAMPRIOM_GRANTED_ACK_CNTR1                    0x114
#define MPC5125_DRAMPRIOM_GRANTED_ACK_CNTR2                    0x118
#define MPC5125_DRAMPRIOM_GRANTED_ACK_CNTR3                    0x11C
#define MPC5125_DRAMPRIOM_GRANTED_ACK_CNTR4                    0x120
#define MPC5125_DRAMPRIOM_CUMULATIVE_WAIT_CNTR0                0x124
#define MPC5125_DRAMPRIOM_CUMULATIVE_WAIT_CNTR1                0x128
#define MPC5125_DRAMPRIOM_CUMULATIVE_WAIT_CNTR2                0x12C
#define MPC5125_DRAMPRIOM_CUMULATIVE_WAIT_CNTR3                0x130
#define MPC5125_DRAMPRIOM_CUMULATIVE_WAIT_CNTR4                0x134
#define MPC5125_DRAMPRIOM_SUMMED_PRIORITY_CNTR0                0x138
#define MPC5125_DRAMPRIOM_SUMMED_PRIORITY_CNTR1                0x13C
#define MPC5125_DRAMPRIOM_SUMMED_PRIORITY_CNTR2                0x140
#define MPC5125_DRAMPRIOM_SUMMED_PRIORITY_CNTR3                0x144
#define MPC5125_DRAMPRIOM_SUMMED_PRIORITY_CNTR4                0x148

#ifndef __ASM__

typedef volatile struct mpc5125_prioman_struct { 
   vuint_32 CONFIG1;          // 0x0080 PRIOMAN_CONFIG1 R/W 0x0007_7777 12.3.2.1/12-4
   vuint_32 CONFIG2;          // 0x0084 PRIOMAN_CONFIG2 R/W 0x0000_00U1 12.3.2.1/12-4
   vuint_32 HIPRIO_CONFIG;    // 0x0088 HIPRIO_CONFIG R/W 0x0000_UUUU 12.3.2.3/12-6
   vuint_32 LUT0MU;           // 0x008C LUT table 0 main upper R/W 0x1111_1222 12.3.2.4/12-7
   vuint_32 LUT1MU;           // 0x0090 LUT table 1 main upper R/W 0x1111_1222 12.3.2.4/12-7
   vuint_32 LUT2MU;           // 0x0094 LUT table 2 main upper R/W 0x1111_1222 12.3.2.4/12-7
   vuint_32 LUT3MU;           // 0x0098 LUT table 3 main upper R/W 0x1111_1222 12.3.2.4/12-7
   vuint_32 LUT4MU;           // 0x009C LUT table 4 main upper R/W 0x1111_1222 12.3.2.4/12-7
   vuint_32 LUT0ML;           // 0x00A0 LUT table 0 main lower R/W 0x2334_567A 12.3.2.5/12-8
   vuint_32 LUT1ML;           // 0x00A4 LUT table 1 main lower R/W 0x2334_567A 12.3.2.5/12-8
   vuint_32 LUT2ML;           // 0x00A8 LUT table 2 main lower R/W 0x2334_567A 12.3.2.5/12-8
   vuint_32 LUT3ML;           // 0x00AC LUT table 3 main lower R/W 0x2334_567A 12.3.2.5/12-8
   vuint_32 LUT4ML;           // 0x00B0 LUT table 4 main lower R/W 0x2334_567A 12.3.2.5/12-8
   vuint_32 LUT0AU;           // 0x00B4 LUT table 0 alternate upper R/W 0x0000_0000 12.3.2.6/12-9
   vuint_32 LUT1AU;           // 0x00B8 LUT table 1 alternate upper R/W 0x0000_0000 12.3.2.6/12-9
   vuint_32 LUT2AU;           // 0x00BC LUT table 2 alternate upper R/W 0x0000_0000 12.3.2.6/12-9
   vuint_32 LUT3AU;           // 0x00C0 LUT table 3 alternate upper R/W 0x0000_0000 12.3.2.6/12-9
   vuint_32 LUT4AU;           // 0x00C4 LUT table 4 alternate upper R/W 0x0000_0000 12.3.2.6/12-9
   vuint_32 LUT0AL;           // 0x00C8 LUT table 0 alternate lower R/W 0x0000_0000 12.3.2.7/12-10
   vuint_32 LUT1AL;           // 0x00CC LUT table 1 alternate lower R/W 0x0000_0000 12.3.2.7/12-10
   vuint_32 LUT2AL;           // 0x00D0 LUT table 2 alternate lower R/W 0x0000_0000 12.3.2.7/12-10
   vuint_32 LUT3AL;           // 0x00D4 LUT table 3 alternate lower R/W 0x0000_0000 12.3.2.7/12-10
   vuint_32 LUT4AL;           // 0x00D8 LUT table 4 alternate lower R/W 0x0000_0000 12.3.2.7/12-10
   vuint_32 PERFMON_CONFIG;   // 0x00DC PERMON_CONFIG - Performance monitor configuration R/W 0x0800_0000 12.3.2.8/12-11
   vuint_32 ETC;              // 0x00E0 Event time counter R/W 0x0000_0000 12.3.2.9/12-12
   vuint_32 ETP;              // 0x00E4 Event time preset R/W 0x0000_0000 12.3.2.10/12-1
   vuint_32 PM1AL;            // 0x00E8 Performance monitor 1 address low R/W 0x0000_0000 12.3.2.11/12-1
   vuint_32 PM2AL;            // 0x00EC Performance monitor 2 address low R/W 0x0000_0000 12.3.2.11/12-1
   vuint_32 PM1AH;            // 0x00F0 Performance monitor 1 address hi R/W 0x0000_0000 12.3.2.11/12-1
   vuint_32 PM2AH;            // 0x00F4 Performance monitor 2 address hi R/W 0x0000_0000 12.3.2.11/12-1
   RESERVED_REGISTER(0xf8,0x100);
   vuint_32 PM1RC;            // 0x0100 Performance monitor 1 read counter R 0x0000_0000 12.3.2.12/12-1
   vuint_32 PM2RC;            // 0x0104 Performance monitor 2 read counter R 0x0000_0000 12.3.2.12/12-1
   vuint_32 PM1WC;            // 0x0108 Performance monitor 1 write counter R 0x0000_0000 12.3.2.12/12-1
   vuint_32 PM2WC;            // 0x010C Performance monitor 2 write counter R 0x0000_0000 12.3.2.12/12-1
   vuint_32 GAC0;             // 0x0110 Granted ack counter 0 R 0x0000_0000 12.3.2.13/12-1
   vuint_32 GAC1;             // 0x0114 Granted ack counter 1 R 0x0000_0000 12.3.2.13/12-1
   vuint_32 GAC2;             // 0x0118 Granted ack counter 2 R 0x0000_0000 12.3.2.13/12-1
   vuint_32 GAC3;             // 0x011C Granted ack counter 3 R 0x0000_0000 12.3.2.13/12-1
   vuint_32 GAC4;             // 0x0120 Granted ack counter 4 R 0x0000_0000 12.3.2.13/12-1
   vuint_32 CWC0;             // 0x0124 Cumulative wait counter 0 R 0x0000_0000 12.3.2.14/12-16
   vuint_32 CWC1;             // 0x0128 Cumulative wait counter 1 R 0x0000_0000 12.3.2.14/12-16
   vuint_32 CWC2;             // 0x012C Cumulative wait counter 2 R 0x0000_0000 12.3.2.14/12-16
   vuint_32 CWC3;             // 0x0130 Cumulative wait counter 3 R 0x0000_0000 12.3.2.14/12-16
   vuint_32 CWC4;             // 0x0134 Cumulative wait counter 4 R 0x0000_0000 12.3.2.14/12-16
   vuint_32 SPC0;             // 0x0138 Summed priority counter 0 R 0x0000_0000 12.3.2.15/12-16
   vuint_32 SPC1;             // 0x013C Summed priority counter 1 R 0x0000_0000 12.3.2.15/12-16
   vuint_32 SPC2;             // 0x0140 Summed priority counter 2 R 0x0000_0000 12.3.2.15/12-16
   vuint_32 SPC3;             // 0x0144 Summed priority counter 3 R 0x0000_0000 12.3.2.15/12-16
   vuint_32 SPC4;             // 0x0148 Summed priority counter 4 R 0x0000_0000 12.3.2.15/12-16
   RESERVED_REGISTER(0x014C,0x400);
} MPC5125_PRIOMAN_STRUCT, _PTR_ MPC5125_PRIOMAN_STRUCT_PTR;

#endif __ASM__

#endif