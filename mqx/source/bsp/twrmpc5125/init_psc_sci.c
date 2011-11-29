/**HEADER********************************************************************
* 
* Copyright (c) 2008 Freescale Semiconductor;
* All Rights Reserved                       
*
* Copyright (c) 2004-2010 Embedded Access Inc.;
* All Rights Reserved
*
* Copyright (c) 1989-2008 ARC International;
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
* $FileName: init_psc_sci.c$
* $Version : 3.7.2.0$
* $Date    : Feb-7-2011$
*
* Comments:
*
*   This file contains the initialization parameters for the serial port.
*
*END************************************************************************/


#include "mqx.h"
#include "bsp.h"
#include "bsp_prv.h"


const MPC5125_SERIAL_INIT_STRUCT _bsp_psc0_init = {
   /* Device #            */ 0,
   /* Queue Size          */ BSPCFG_PSC0_DEFAULT_QUEUE_SIZE,
   /* Input Alarm Size    */ BSPCFG_PSC0_DEFAULT_INPUT_ALARM_SIZE,
   /* Output Alarm Size   */ BSPCFG_PSC0_DEFAULT_OUTPUT_ALARM_SIZE,
   /* Baud rate           */ BSPCFG_PSC0_DEFAULT_BAUD_RATE,
   /* Bits Per Character  */ 8,
   /* Parity              */ IO_SERIAL_NO_PARITY,
   /* Stop bits           */ IO_SERIAL_1_STOP_BIT,
   /* Clock speed         */ _bsp_ipb_frequency
};

const MPC5125_SERIAL_INIT_STRUCT _bsp_psc1_init = {
   /* Device #            */ 1,
   /* Queue Size          */ BSPCFG_PSC1_DEFAULT_QUEUE_SIZE,
   /* Input Alarm Size    */ BSPCFG_PSC1_DEFAULT_INPUT_ALARM_SIZE,
   /* Output Alarm Size   */ BSPCFG_PSC1_DEFAULT_OUTPUT_ALARM_SIZE,
   /* Baud rate           */ BSPCFG_PSC1_DEFAULT_BAUD_RATE,
   /* Bits Per Character  */ 8,
   /* Parity              */ IO_SERIAL_NO_PARITY,
   /* Stop bits           */ IO_SERIAL_1_STOP_BIT,
   /* Clock speed         */ _bsp_ipb_frequency
};

const MPC5125_SERIAL_INIT_STRUCT _bsp_psc2_init = {
   /* Device #            */ 2,
   /* Queue Size          */ BSPCFG_PSC2_DEFAULT_QUEUE_SIZE,
   /* Input Alarm Size    */ BSPCFG_PSC2_DEFAULT_INPUT_ALARM_SIZE,
   /* Output Alarm Size   */ BSPCFG_PSC2_DEFAULT_OUTPUT_ALARM_SIZE,
   /* Baud rate           */ BSPCFG_PSC2_DEFAULT_BAUD_RATE,
   /* Bits Per Character  */ 8,
   /* Parity              */ IO_SERIAL_NO_PARITY,
   /* Stop bits           */ IO_SERIAL_1_STOP_BIT,
   /* Clock speed         */ _bsp_ipb_frequency
};

const MPC5125_SERIAL_INIT_STRUCT _bsp_psc3_init = {
   /* Device #            */ 3,
   /* Queue Size          */ BSPCFG_PSC3_DEFAULT_QUEUE_SIZE,
   /* Input Alarm Size    */ BSPCFG_PSC3_DEFAULT_INPUT_ALARM_SIZE,
   /* Output Alarm Size   */ BSPCFG_PSC3_DEFAULT_OUTPUT_ALARM_SIZE,
   /* Baud rate           */ BSPCFG_PSC3_DEFAULT_BAUD_RATE,
   /* Bits Per Character  */ 8,
   /* Parity              */ IO_SERIAL_NO_PARITY,
   /* Stop bits           */ IO_SERIAL_1_STOP_BIT,
   /* Clock speed         */ _bsp_ipb_frequency
};

const MPC5125_SERIAL_INIT_STRUCT _bsp_psc4_init = {
   /* Device #            */ 4,
   /* Queue Size          */ BSPCFG_PSC4_DEFAULT_QUEUE_SIZE,
   /* Input Alarm Size    */ BSPCFG_PSC4_DEFAULT_INPUT_ALARM_SIZE,
   /* Output Alarm Size   */ BSPCFG_PSC4_DEFAULT_OUTPUT_ALARM_SIZE,
   /* Baud rate           */ BSPCFG_PSC4_DEFAULT_BAUD_RATE,
   /* Bits Per Character  */ 8,
   /* Parity              */ IO_SERIAL_NO_PARITY,
   /* Stop bits           */ IO_SERIAL_1_STOP_BIT,
   /* Clock speed         */ _bsp_ipb_frequency
};

const MPC5125_SERIAL_INIT_STRUCT _bsp_psc5_init = {
   /* Device #            */ 5,
   /* Queue Size          */ BSPCFG_PSC5_DEFAULT_QUEUE_SIZE,
   /* Input Alarm Size    */ BSPCFG_PSC5_DEFAULT_INPUT_ALARM_SIZE,
   /* Output Alarm Size   */ BSPCFG_PSC5_DEFAULT_OUTPUT_ALARM_SIZE,
   /* Baud rate           */ BSPCFG_PSC5_DEFAULT_BAUD_RATE,
   /* Bits Per Character  */ 8,
   /* Parity              */ IO_SERIAL_NO_PARITY,
   /* Stop bits           */ IO_SERIAL_1_STOP_BIT,
   /* Clock speed         */ _bsp_ipb_frequency
};

const MPC5125_SERIAL_INIT_STRUCT _bsp_psc6_init = {
   /* Device #            */ 6,
   /* Queue Size          */ BSPCFG_PSC6_DEFAULT_QUEUE_SIZE,
   /* Input Alarm Size    */ BSPCFG_PSC6_DEFAULT_INPUT_ALARM_SIZE,
   /* Output Alarm Size   */ BSPCFG_PSC6_DEFAULT_OUTPUT_ALARM_SIZE,
   /* Baud rate           */ BSPCFG_PSC6_DEFAULT_BAUD_RATE,
   /* Bits Per Character  */ 8,
   /* Parity              */ IO_SERIAL_NO_PARITY,
   /* Stop bits           */ IO_SERIAL_1_STOP_BIT,
   /* Clock speed         */ _bsp_ipb_frequency
};

const MPC5125_SERIAL_INIT_STRUCT _bsp_psc7_init = {
   /* Device #            */ 7,
   /* Queue Size          */ BSPCFG_PSC7_DEFAULT_QUEUE_SIZE,
   /* Input Alarm Size    */ BSPCFG_PSC7_DEFAULT_INPUT_ALARM_SIZE,
   /* Output Alarm Size   */ BSPCFG_PSC7_DEFAULT_OUTPUT_ALARM_SIZE,
   /* Baud rate           */ BSPCFG_PSC7_DEFAULT_BAUD_RATE,
   /* Bits Per Character  */ 8,
   /* Parity              */ IO_SERIAL_NO_PARITY,
   /* Stop bits           */ IO_SERIAL_1_STOP_BIT,
   /* Clock speed         */ _bsp_ipb_frequency
};

const MPC5125_SERIAL_INIT_STRUCT _bsp_psc8_init = {
   /* Device #            */ 8,
   /* Queue Size          */ BSPCFG_PSC8_DEFAULT_QUEUE_SIZE,
   /* Input Alarm Size    */ BSPCFG_PSC8_DEFAULT_INPUT_ALARM_SIZE,
   /* Output Alarm Size   */ BSPCFG_PSC8_DEFAULT_OUTPUT_ALARM_SIZE,
   /* Baud rate           */ BSPCFG_PSC8_DEFAULT_BAUD_RATE,
   /* Bits Per Character  */ 8,
   /* Parity              */ IO_SERIAL_NO_PARITY,
   /* Stop bits           */ IO_SERIAL_1_STOP_BIT,
   /* Clock speed         */ _bsp_ipb_frequency
};

const MPC5125_SERIAL_INIT_STRUCT _bsp_psc9_init = {
   /* Device #            */ 9,
   /* Queue Size          */ BSPCFG_PSC9_DEFAULT_QUEUE_SIZE,
   /* Input Alarm Size    */ BSPCFG_PSC9_DEFAULT_INPUT_ALARM_SIZE,
   /* Output Alarm Size   */ BSPCFG_PSC9_DEFAULT_OUTPUT_ALARM_SIZE,
   /* Baud rate           */ BSPCFG_PSC9_DEFAULT_BAUD_RATE,
   /* Bits Per Character  */ 8,
   /* Parity              */ IO_SERIAL_NO_PARITY,
   /* Stop bits           */ IO_SERIAL_1_STOP_BIT,
   /* Clock speed         */ _bsp_ipb_frequency
};

/* EOF */
