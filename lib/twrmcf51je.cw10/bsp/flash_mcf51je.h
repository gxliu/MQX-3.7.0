/**HEADER********************************************************************
* 
* Copyright (c) 2008 Freescale Semiconductor;
* All Rights Reserved
*
* Copyright (c) 2004-2008 Embedded Access Inc.;
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
* $FileName: flash_mcf51je.h$
* $Version : 3.7.2.0$
* $Date    : Feb-7-2011$
*
* Comments:
*
*   The file contains functions prototype, defines for the internal 
*   flash driver
*
*END************************************************************************/
#ifndef __INT_FLASH_MCF51JE_H__
#define __INT_FLASH_MCF51JE_H__

/*----------------------------------------------------------------------*/
/*
** FLASHX storage declared in Linker Command File
*/

extern uchar __FLASHX_START_ADDR[];
extern uchar __FLASHX_END_ADDR[];
extern uchar __FLASHX_SECT_SIZE[]; 

#define FLASHX_START_ADDR ((uint_32)__FLASHX_START_ADDR)
#define FLASHX_END_ADDR   ((uint_32)__FLASHX_END_ADDR)
#define FLASHX_SECT_SIZE  ((uint_32)__FLASHX_SECT_SIZE)

/*----------------------------------------------------------------------*/
/*
** FUNCTION PROTOTYPES
*/
extern pointer _bsp_get_cfm_address();
extern pointer _bsp_get_pmc_address();
uint_32 _mcf51je_internal_flash_install( char_ptr , uint_32);

/********************************************************************/
#endif /* __INT_FLASH_MCF51JE_H__ */
