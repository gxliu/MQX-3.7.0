#ifndef _nandbootloader_h_
#define _nandbootloader_h_
/**HEADER********************************************************************
* 
* Copyright (c) 2010 Freescale Semiconductor;
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
* $FileName: bootloader.h$
* $Version : 3.7.2.0$
* $Date    : Feb-7-2011$
*
* Comments:
*
*   
*   
*
*END************************************************************************/

#ifdef BSP_TWRMPC5125

   #define IMAGE_TABLE_PAGE_LOCATION    2048000 /* Image table is located in page 2048000 */
   #define IMAGE_TABLE_BLOCK_LOCATION   8000    /* Image table is located in block 8000 */
   #define IMAGE_START_BLOCK            10
   #define NAND_FLASH_PAGE_SIZE         2048
   #define NAND_FLASH_BLOCK_SIZE        524288  /* 512 KB */
   #define IMAGE_TABLE_SIZE             (NAND_FLASH_PAGE_SIZE)
   #define IMAGE_MASK_AS_DELETE         0xFFFFFFFF
   #define ERASE_BLOCK_SUCCESS          1
   #define ERASE_BLOCK_FAILED           0
   #define IMAGE_IN_TABLE_MASK          0x000000FF
   #define IMAGE_IN_TABLE_UNMASK        0xFFFFFFFF
   #define CHECK_SUM_OK                 1
   #define CHECK_SUM_FAIL               0
   #define AUTOBOOT_TIMEOUT             3
#endif /* BSP_TWRMPC5125 */

int_32 _bootloader_init_table(void);
uint_32 _bootloader_del_image(uint_32);
int_32  _bootloader_store_image(uint_32, uint_32, uchar_ptr, uchar_ptr);
void _bootloader_list_image(void);
int_32 _bootloader_set_default(uint_32);
boolean _bootloader_check_image(boolean, uint_32);
void _bootloader_reset(void);
#endif
/* EOF */