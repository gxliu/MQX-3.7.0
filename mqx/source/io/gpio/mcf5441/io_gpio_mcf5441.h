#ifndef __io_gpio_cpu_h__
#define __io_gpio_cpu_h__
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
* $FileName: io_gpio_mcf5441.h$
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

#define GPIO_PORT_A     ((0x0000 << 3) | GPIO_PIN_VALID)
#define GPIO_PORT_B     ((0x0001 << 3) | GPIO_PIN_VALID)
#define GPIO_PORT_C     ((0x0002 << 3) | GPIO_PIN_VALID)
#define GPIO_PORT_D     ((0x0003 << 3) | GPIO_PIN_VALID)
#define GPIO_PORT_E     ((0x0004 << 3) | GPIO_PIN_VALID)
#define GPIO_PORT_F     ((0x0005 << 3) | GPIO_PIN_VALID)
#define GPIO_PORT_G     ((0x0006 << 3) | GPIO_PIN_VALID)
#define GPIO_PORT_H     ((0x0007 << 3) | GPIO_PIN_VALID)
#define GPIO_PORT_I     ((0x0008 << 3) | GPIO_PIN_VALID)
#define GPIO_PORT_J     ((0x0009 << 3) | GPIO_PIN_VALID)
#define GPIO_PORT_K     ((0x000A << 3) | GPIO_PIN_VALID)

#ifdef __cplusplus
}
#endif

#endif

/* EOF */
