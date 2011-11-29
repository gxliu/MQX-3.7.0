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
* $FileName: init_flash1.c$
* $Version : 3.5.4.0$
* $Date    : Oct-27-2009$
*
* Comments:
*
*   This file contains the default initialization record for the
*   flash.
*
*END************************************************************************/

#include "mqx.h"
#include "bsp.h"

extern FLASHX_BLOCK_INFO_STRUCT _JM28F128J3A_block_map_16bit[];

static boolean _bsp_flash_init(IO_FLASHX_STRUCT_PTR handle) {
   return _intel_strata_clear_lock_bits(handle);
}

const FLASHX_INIT_STRUCT _bsp_flashx1_init =
{
   /* NAME           */   "flash1:",
   /* SECTOR_ERASE   */   _intel_strata_erase,
   /* SECTOR_PROGRAM */   _intel_strata_program,
   /* CHP_ERASE      */   0,
   /* INIT           */   0,
   /* DEINIT         */   0,
   /* WRITE_PROTECT  */   _intel_strata_write_protect,
   /* MAP_PTR        */   _JM28F128J3A_block_map_16bit,
   /* BASE_ADDR      */   BSP_FLASH1_BASE,
   /* WIDTH          */   BSP_FLASH1_WIDTH,
   /* DEVICES        */   BSP_FLASH1_DEVICES,
   /* WRITE VERIFY?  */   1,
   /* IOCTL          */   _io_intel_strata_ioctl    
};

/* EOF */
