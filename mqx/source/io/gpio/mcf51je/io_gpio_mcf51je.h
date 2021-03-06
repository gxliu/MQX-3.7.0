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
* $FileName: io_gpio_mcf51je.h$
* $Version : 3.7.2.0$
* $Date    : Feb-7-2011$
*
* Comments:
*
*   The file contains definitions used in user program and/or in other
*   kernel modules to access GPIO pins
*
*END************************************************************************/

#ifndef __io_gpio_cpu_h__
    #define __io_gpio_cpu_h__

#ifdef __cplusplus
extern "C" {
#endif


/******************************************************************************
**                          CONSTANT DEFINITIONS
*/

#define GPIO_PORT_TA ((0x0000 << 3) | GPIO_PIN_VALID)
#define GPIO_PORT_TB ((0x0001 << 3) | GPIO_PIN_VALID)
#define GPIO_PORT_TC ((0x0002 << 3) | GPIO_PIN_VALID)
#define GPIO_PORT_TD ((0x0003 << 3) | GPIO_PIN_VALID)
#define GPIO_PORT_TE ((0x0004 << 3) | GPIO_PIN_VALID)
#define GPIO_PORT_TF ((0x0005 << 3) | GPIO_PIN_VALID)
#define GPIO_PORT_TG ((0x0006 << 3) | GPIO_PIN_VALID)
#define GPIO_PORT_TH ((0x0007 << 3) | GPIO_PIN_VALID)
#define GPIO_PORT_TJ ((0x0008 << 3) | GPIO_PIN_VALID)

/* The NULL parameter is given to the callback function as we do not know
** which pin caused that ISR was invoked.
*/

/* Exported constants */
extern const VMCF51JE_GPIO_DATA_STRUCT_PTR gpio_data_ptr[GPIO_PORT_MAX];
extern const VMCF51JE_GPIO_STRUCT_PTR gpio_ptr[GPIO_PORT_MAX];

#ifdef __cplusplus
}
#endif

#endif  /* __io_gpio_cpu_h__ */

/* EOF */
