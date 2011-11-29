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
* $FileName: psp_cpudef.h$
* $Version : 3.7.5.0$
* $Date    : Feb-7-2011$
*
* Comments:
* 
*   Processor and platform identifiers defined here
*
*END************************************************************************/

#ifndef __psp_cpudef_h__
#define __psp_cpudef_h__

#include "mqx_cpudef.h"

/* CPU groups */
#define PSP_CPU_GROUP_KINETIS_K10   (1)
#define PSP_CPU_GROUP_KINETIS_K20   (2)
#define PSP_CPU_GROUP_KINETIS_K30   (3)
#define PSP_CPU_GROUP_KINETIS_K40   (4)
#define PSP_CPU_GROUP_KINETIS_K50   (5)
#define PSP_CPU_GROUP_KINETIS_K60   (6)

/* Specific CPU identification macros */
#define PSP_CPU_MK40X128        (PSP_CPU_NUM(PSP_CPU_ARCH_ARM, PSP_CPU_GROUP_KINETIS_K40, 0))
#define PSP_CPU_MK40X256        (PSP_CPU_NUM(PSP_CPU_ARCH_ARM, PSP_CPU_GROUP_KINETIS_K40, 1))
#define PSP_CPU_MK40N512        (PSP_CPU_NUM(PSP_CPU_ARCH_ARM, PSP_CPU_GROUP_KINETIS_K40, 2))
#define PSP_CPU_MK60N256        (PSP_CPU_NUM(PSP_CPU_ARCH_ARM, PSP_CPU_GROUP_KINETIS_K60, 0))
#define PSP_CPU_MK60X256        (PSP_CPU_NUM(PSP_CPU_ARCH_ARM, PSP_CPU_GROUP_KINETIS_K60, 1))
#define PSP_CPU_MK60N512        (PSP_CPU_NUM(PSP_CPU_ARCH_ARM, PSP_CPU_GROUP_KINETIS_K60, 2))

/* backward compatibility with early access verions */
#define PSP_CPU_K60N512         PSP_CPU_MK60N512
#define PSP_CPU_K40N512         PSP_CPU_MK40N512         
#define PSP_CPU_K40N256         PSP_CPU_MK40X256         

/* CPU id check support macros */
#define PSP_MQX_CPU_IS_KINETIS_K10  ((PSP_GET_CPU_GROUP(MQX_CPU) == PSP_CPU_GROUP_KINETIS_K10))
#define PSP_MQX_CPU_IS_KINETIS_K20  ((PSP_GET_CPU_GROUP(MQX_CPU) == PSP_CPU_GROUP_KINETIS_K20))
#define PSP_MQX_CPU_IS_KINETIS_K30  ((PSP_GET_CPU_GROUP(MQX_CPU) == PSP_CPU_GROUP_KINETIS_K30))
#define PSP_MQX_CPU_IS_KINETIS_K40  ((PSP_GET_CPU_GROUP(MQX_CPU) == PSP_CPU_GROUP_KINETIS_K40))
#define PSP_MQX_CPU_IS_KINETIS_K50  ((PSP_GET_CPU_GROUP(MQX_CPU) == PSP_CPU_GROUP_KINETIS_K50))
#define PSP_MQX_CPU_IS_KINETIS_K60  ((PSP_GET_CPU_GROUP(MQX_CPU) == PSP_CPU_GROUP_KINETIS_K60))

#define PSP_MQX_CPU_IS_KINETIS      (PSP_MQX_CPU_IS_KINETIS_K10 | PSP_MQX_CPU_IS_KINETIS_K20 | \
                                     PSP_MQX_CPU_IS_KINETIS_K30 | PSP_MQX_CPU_IS_KINETIS_K40 | \
                                     PSP_MQX_CPU_IS_KINETIS_K50 | PSP_MQX_CPU_IS_KINETIS_K60)   

#endif
