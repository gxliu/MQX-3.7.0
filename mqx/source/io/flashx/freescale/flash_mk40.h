#ifndef __flash_mk40_h__
#define __flash_mk40_h__
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
* $FileName: flash_mk40.h$
* $Version : 3.7.5.1$
* $Date    : Mar-30-2011$
*
* Comments:
*
*   The file contains functions prototype, defines for the internal 
*   flash driver.
*
*END************************************************************************/

#include <bsp.h>

/*----------------------------------------------------------------------*/
/*
** FLASHX storage declared in Linker Command File
*/

extern const uchar __FLASHX_START_ADDR[];
extern uchar __FLASHX_END_ADDR[];
extern uchar __FLASHX_SECT_SIZE[]; 

extern uchar __INTERNAL_FLEXNVM_BASE[];
extern uchar __INTERNAL_FLEXNVM_SIZE[];

extern uchar __INTERNAL_FLEXRAM_BASE[];
extern uchar __INTERNAL_FLEXRAM_SIZE[];

#define FLASHX_START_ADDR __FLASHX_START_ADDR
#define FLASHX_END_ADDR   __FLASHX_END_ADDR
#define FLASHX_SECT_SIZE  ((uint_32)__FLASHX_SECT_SIZE)

#define INTERNAL_FLEXNVM_BASE   ((uint_32)__INTERNAL_FLEXNVM_BASE)
#define INTERNAL_FLEXNVM_SIZE   ((uint_32)__INTERNAL_FLEXNVM_SIZE)

#define INTERNAL_FLEXRAM_BASE   ((uint_32)__INTERNAL_FLEXRAM_BASE)
#define INTERNAL_FLEXRAM_SIZE   ((uint_32)__INTERNAL_FLEXRAM_SIZE)

/*----------------------------------------------------------------------*/
/*
** FUNCTION PROTOTYPES
*/

extern pointer _bsp_get_ftfl_address (void);
extern uint_32 _mk40_flash_install_internal (char_ptr, uint_32);

#endif
