/**HEADER********************************************************************
* 
* Copyright (c) 2008 Freescale Semiconductor;
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
* $FileName: init_flash0.c$
* $Version : 3.0.1.0$
* $Date    : Jun-18-2009$
*
* Comments:
*
*   This file contains the default initialization record for the
*   flash.
*
*END************************************************************************/

#include "mqx.h"
#include "bsp.h"

extern FLASHX_BLOCK_INFO_STRUCT _AT49BV040_block_map_16bit[];

const FLASHX_INIT_STRUCT _bsp_flashx0_init =
{
   /* NAME           */   "flash0:",
   /* SECTOR_ERASE   */   _at49bvxx_sector_erase,
   /* SECTOR_PROGRAM */   _at49bvxx_program,
   /* CHP_ERASE      */   _at49bvxx_erase_chip,
   /* INIT           */   0,
   /* DEINIT         */   0,
   /* WRITE_PROTECT  */   0,
   /* MAP_PTR        */   _AT49BV040_block_map_16bit,
   /* BASE_ADDR      */   BSP_FLASH0_BASE,
   /* WIDTH          */   BSP_FLASH0_WIDTH,
   /* DEVICES        */   BSP_FLASH0_DEVICES,
   /* WRITE VERIFY? */    1
};

/* EOF */
