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
* $FileName: io_gpio_mcf5301_prv.h$
* $Version : 3.6.1.0$
* $Date    : Aug-2-2010$
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
    /* port structure i memory */
    struct {
        uint_8  fbctl;
        uint_8  be;
        uint_8  cs;
        uint_8  dspi;
        uint_8  unusedA;
        uint_8  fec0;
        uint_8  feci2c;
        uint_8  unusedB;
        uint_8  unusedC;
        uint_8  simp1;
        uint_8  simp0;
        uint_8  timer;
        uint_8  uart;
        uint_8  debug;
        uint_8  unusedD;
        uint_8  sdhc;
        uint_8  ssi;
        uint_8  unusedE[3];
    } reg;
    uint_32 memory32[5];
    uint_8  memory8[5 * 4];
} GPIO_PIN_MAP, _PTR_ GPIO_PIN_MAP_PTR;

#ifdef __cplusplus
}
#endif

#endif

/* EOF */
