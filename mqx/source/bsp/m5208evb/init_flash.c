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
* $FileName: init_flash.c$
* $Version : 3.6.1.0$
* $Date    : Jan-5-2011$
*
* Comments:
*
*   This file contains the default initialization record for the
*   flash.
*
*END************************************************************************/

#include "mqx.h"
#include "bsp.h"
#include "flashx.h"
#include "29wsxxxJ.h"

extern FLASHX_BLOCK_INFO_STRUCT _S28WS64_block_map_16bit[];

const FLASHX_INIT_STRUCT _bsp_flashx_init =
{
   /* NAME           */   "flash:",
   /* SECTOR_ERASE   */   _29wsxxxJ_erase,
   /* SECTOR_PROGRAM */   _29wsxxxJ_program,
   /* CHP_ERASE      */   _29wsxxxJ_chip_erase,
   /* INIT           */   0,
   /* DEINIT         */   0,
   /* WRITE_PROTECT  */   _29wsxxxJ_write_protect,
   /* MAP_PTR        */   _S28WS64_block_map_16bit,
   /* BASE_ADDR      */   BSP_FLASH_BASE,
   /* WIDTH          */   BSP_FLASH_WIDTH,
   /* DEVICES        */   BSP_FLASH_DEVICES,
   /* WRITE VERIFY? */    1,
   /* IOCTL */            _29wsxxxJ_ioctl
};

/* EOF */
