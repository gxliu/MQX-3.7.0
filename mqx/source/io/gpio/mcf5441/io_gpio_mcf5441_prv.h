#ifndef __io_gpio_cpu_prv_h__
#define __io_gpio_cpu_prv_h__
/**HEADER********************************************************************
* 
* Copyright (c) 2008 Freescale Semiconductor;
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
* $FileName: io_gpio_mcf5441_prv.h$
* $Version : 3.5.2.0$
* $Date    : Jan-4-2010$
*
* Comments:
*
*   The file contains definitions used in user program and/or in other
*   kernel modules to access GPIO pins
*
*END************************************************************************/

/*----------------------------------------------------------------------*/
/*
**                          CONSTANT DEFINITIONS
*/

#ifdef __cplusplus
extern "C" {
#endif

typedef enum devices {
     DEV_INPUT,
     DEV_OUTPUT
} DEVICE_TYPE;

typedef union pin_map_struct {
    struct {
        uint_8 porta;
        uint_8 portb;
        uint_8 portc;
        uint_8 portd;
        uint_8 porte;
        uint_8 portf;
        uint_8 portg;
        uint_8 porth;
        uint_8 porti;
        uint_8 portj;
        uint_8 portk;
    } reg;
    uint_32 memory32[3];
    uint_8  memory8[10];
} GPIO_PIN_MAP, _PTR_ GPIO_PIN_MAP_PTR;

#ifdef __cplusplus
}
#endif

#endif

/* EOF */
