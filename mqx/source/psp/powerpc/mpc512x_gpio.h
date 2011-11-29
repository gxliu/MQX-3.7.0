#ifndef __mpc5125_gpio_h__
#define __mpc5125_gpio_h__
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
* $FileName: mpc512x_gpio.h$
* $Version :  3.7.3.0$
* $Date    :  Feb-7-2011$
*
* Comments:
*
*   This file contains definitions for the MPC5125 family and peripherals.
*
*END************************************************************************/

#define MPC5125_GPIO_ADDR(x)     (&((VMPC5125_STRUCT_PTR) MPC5125_GET_IMMR() )->GPIO[x])

#define MPC5125_GPIO_PORT1       0
#define MPC5125_GPIO_PORT2       1
#define MPC5125_NUM_GPIO_PORTS   2
#define MPC5125_GPIO_PIN(x)      (x)
#define MPC5125_GPIO_OUT_EN      1
#define MPC5125_GPIO_OPEN_DRAIN  1
#define MPC5125_GPIO_INT_EN      1
#define MPC5125_GPIO_EDGE_DETECT 1      
      
typedef volatile struct
{
   uint_32 DIR;    // GPIO Direction Register
   uint_32 ODR;    // GPIO Open Drain Register
   uint_32 DAT;    // GPIO Data register 
   uint_32 IER;    // GPIO Interrupt Event Register
   uint_32 IMR;    // GPIO Interrupt Mask Register
   uint_32 ICR1;   // GPIO External Interrupt Control Register 1
   uint_32 ICR2;   // GPIO External Interrupt Control Register 2
   RESERVED_REGISTER(0x1c,0x80);
} MPC5125_GPIO_STRUCT, _PTR_ MPC5125_GPIO_STRUCT_PTR;

#endif
