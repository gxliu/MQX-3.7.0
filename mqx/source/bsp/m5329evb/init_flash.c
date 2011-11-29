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
* $Date    : Dec-15-2010$
*
* Comments:
*
*   This file contains the default initialization record for the
*   flash.
*
*END************************************************************************/

#include "mqx.h"
#include "bsp.h"


extern FLASHX_BLOCK_INFO_STRUCT _i28f160bot_block_map_16bit[];
extern FLASHX_BLOCK_INFO_STRUCT _i28f160top_block_map_16bit[];
extern NANDFLASH_INFO_STRUCT _TC58DVM72A1_organization_16bit[];

static boolean _bsp_flash_init(IO_FLASHX_STRUCT_PTR handle) {
   return _intel_strata_clear_lock_bits(handle);
}

const FLASHX_INIT_STRUCT       _bsp_flashx_init =
{
   /* NAME           */   "flash:",
   /* SECTOR_ERASE   */   _intel_strata_erase,
   /* SECTOR_PROGRAM */   _intel_strata_program,
   /* CHP_ERASE      */   0,
   /* INIT           */   _bsp_flash_init,
   /* DEINIT         */   0,
   /* WRITE_PROTECT  */   _intel_strata_write_protect,
   /* MAP_PTR        */   _i28f160bot_block_map_16bit,
   /* BASE_ADDR      */   BSP_FLASH_BASE,
   /* WIDTH          */   BSP_FLASH_WIDTH,
   /* DEVICES        */   BSP_FLASH_DEVICES,
   /* WRITE VERIFY? */    1,
   /* IOCTL          */   _io_intel_strata_ioctl 
};

const NANDFLASH_INIT_STRUCT _bsp_nandflash_init =
{
   /* NAME                 */   "nandflash:",
   /* INIT                 */   mcf532x_nfc_init,
   /* DEINIT               */   mcf532x_nfc_deinit,
   /* CHIP_ERASE           */   mcf532x_nfc_erase_flash,
   /* BLOCK_ERASE          */   mcf532x_nfc_erase_block,
   /* PAGE_READ            */   mcf532x_nfc_read_page,
   /* PAGE_PROGRAM         */   mcf532x_nfc_write_page,
   /* WRITE_PROTECT        */   NULL,
   /* IS_BLOCK_BAD         */   mcf532x_nfc_check_block,
   /* MARK_BLOCK_AS_BAD    */   mcf532x_nfc_mark_block_as_bad,
   /* IOCTL                */   mcf532x_nfc_ioctl,
   /* NANDFLASH_INFO_PTR   */   _TC58DVM72A1_organization_16bit,
   /* VIRTUAL_PAGE_SIZE    */   0,
   /* NUM_VIRTUAL_PAGES    */   0,
   /* PHY_PAGE_SIZE_TO_VIRTUAL_PAGE_SIZE_RATIO */  
                                0,
   /* ECC_SIZE             */   0,
   /* WRITE_VERIFY         */   0,
   /* DEVICE_SPECIFIC_DATA */   0
};

/* EOF */