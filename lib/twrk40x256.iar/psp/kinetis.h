/**HEADER********************************************************************
* 
* Copyright (c) 2010 Freescale Semiconductor;
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
* $FileName: kinetis.h$
* $Version : 3.7.5.0$
* $Date    : Feb-7-2011$
*
* Comments:
*
*   This file contains the type definitions for the Kinetis microcontrollers.
*
*END************************************************************************/

#ifndef __kinetis_h__
#define __kinetis_h__

#define __kinetis_h__version "$Version:3.7.5.0$"
#define __kinetis_h__date    "$Date:Feb-7-2011$"

#ifndef __ASM__

/* Include header file for specific Kinetis platform */
#if     MQX_CPU == PSP_CPU_MK10N512
    #include "MK10N512VMD100.h"
#elif   MQX_CPU == PSP_CPU_MK10X128
    #include "MK10X128VMD100.h"
#elif   MQX_CPU == PSP_CPU_MK10X256
    #include "MK10X256VMD100.h"
#elif   MQX_CPU == PSP_CPU_MK20N512
    #include "MK20N512VMD100.h"
#elif   MQX_CPU == PSP_CPU_MK20X128
    #include "MK20X128VMD100.h"
#elif   MQX_CPU == PSP_CPU_MK20X256
    #include "MK20X256VMD100.h"
#elif   MQX_CPU == PSP_CPU_MK30N512
    #include "MK30N512VMD100.h"
#elif   MQX_CPU == PSP_CPU_MK30X128
    #include "MK30X128VMD100.h"
#elif   MQX_CPU == PSP_CPU_MK30X256
    #include "MK30X256VMD100.h"
#elif   MQX_CPU == PSP_CPU_MK40N512
    #include "MK40N512VMD100.h"
#elif   MQX_CPU == PSP_CPU_MK40X128
    #include "MK40X128VMD100.h"
#elif   MQX_CPU == PSP_CPU_MK40X256
    #include "MK40X256VMD100.h"
#elif   MQX_CPU == PSP_CPU_MK60N256
    #include "MK60N256VMD100.h"
#elif   MQX_CPU == PSP_CPU_MK60N512
    #include "MK60N512VMD100.h"
#elif   MQX_CPU == PSP_CPU_MK60X256
    #include "MK60X256VMD100.h"
#endif

#endif /* __ASM__ */

#ifdef __cplusplus
extern "C" {
#endif

/*------------------------------------------------------------------------*/
/*
**                    CONSTANT DEFINITIONS
*/

/*
** Cache and MMU definition values
*/
#define PSP_HAS_MMU                         0
#define PSP_HAS_CODE_CACHE                  0
#define PSP_HAS_DATA_CACHE                  0

#define PSP_CACHE_LINE_SIZE                 (0x10)

#ifndef __ASM__

/*
** Standard cache macros
*/
#define _DCACHE_FLUSH()
#define _DCACHE_FLUSH_LINE(p)
#define _DCACHE_FLUSH_MBYTES(p, m)
#define _DCACHE_INVALIDATE()
#define _DCACHE_INVALIDATE_LINE(p)
#define _DCACHE_INVALIDATE_MBYTES(p, m)

#define _CACHE_ENABLE(n)
#define _CACHE_DISABLE()

#define _ICACHE_INVALIDATE()
#define _ICACHE_INVALIDATE_LINE(p)
#define _ICACHE_INVALIDATE_MBYTES(p, m)

#define PSP_INTERRUPT_TABLE_INDEX  IRQInterruptIndex

/*------------------------------------------------------------------------*/
/*
**                      TYPE DEFINITIONS
*/
  

/*
** PSP_SUPPORT_STRUCT
** This structure is used to maintain the PSP support information
*/

#if PSP_HAS_SUPPORT_STRUCT

typedef struct psp_support_struct
{
    uint_32                   FIQIRQ_BIT;
    /* Interrupt stack struct */
    //   PSP_INT_STACK_INFO_STRUCT STACKS;
    /* Where in memory does the page table start */
    uint_32_ptr               PAGE_TABLE_BASE;
    /* Number of entries */
    uint_32                   NUMBER_OF_ENTRIES;
    /* Reserved field for future use */
    uint_32                   Reserved1[4];
} PSP_SUPPORT_STRUCT, _PTR_ PSP_SUPPORT_STRUCT_PTR;
#endif

/*------------------------------------------------------------------------*/
/*
**                      FUNCTION PROTOTYPES AND GLOBAL EXTERNS
*/


#endif /* __ASM__ */

#ifdef __cplusplus
}
#endif

#endif /* __kinetis_h__ */
