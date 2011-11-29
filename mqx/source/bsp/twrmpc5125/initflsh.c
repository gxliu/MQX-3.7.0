/*HEADER******************************************************************
**************************************************************************
*** 
*** Copyright (c) 1989-2006 ARC International
*** All rights reserved                                          
***                                                              
*** This software embodies materials and concepts which are      
*** confidential to ARC International and is made
*** available solely pursuant to the terms of a written license   
*** agreement with ARC International             
***
*** File: initflsh.c
***
*** Comments:      
***   This file contains the definition for the flash initialization.
***                                                               
***
**************************************************************************
*END*********************************************************************/

#include "mqx.h"
#include "bsp.h"

/* Start CR 2108 */
#if MPC5200B
FLASHX_BLOCK_INFO_STRUCT _29glxxxN_block_map_8bit[] = {
{ BSP_FLASH_NUM_SECTORS, 0,  BSP_FLASH_SECTOR_SIZE},
{ 0, 0, 0}
};
FLASHX_INIT_STRUCT _bsp_flashx_init = {
   /* ID_PTR */         "flash:",
   /* SECTOR_ERASE */   _29glxxxN_erase,
   /* SECTOR_PROGRAM */ _29glxxxN_program,
   /* CHIP_ERASE */     _29glxxxN_chip_erase,
   /* INIT */           NULL,
   /* DEINIT */         NULL,
   /* WRITE_PROTET */   NULL,
   /* MAP_PTR */        _29glxxxN_block_map_8bit,
   /* BASE_ADDR */      BSP_FLASH_BASE,
   /* WIDTH */          BSP_FLASH_WIDTH,
   /* DEVICES */        BSP_FLASH_DEVICES,
   /* WRITE VERIFY? */  1
};
#else
FLASHX_BLOCK_INFO_STRUCT _block_map_32bit[] = {
{ BSP_FLASH_NUM_SECTORS, 0,  BSP_FLASH_SECTOR_SIZE},
{ 0, 0, 0}
};

FLASHX_INIT_STRUCT _bsp_flashx_init = {
   /* ID_PTR */         "flash:",
   /* SECTOR_ERASE */   _29dl3xx_erase,
   /* SECTOR_PROGRAM */ _29dl3xx_program,
   /* CHIP_ERASE */     NULL,
   /* INIT */           NULL,
   /* DEINIT */         NULL,
   /* WRITE_PROTECT */  NULL,
   /* MAP_PTR */        _block_map_32bit,
   /* BASE_ADDR */      BSP_FLASH_BASE,
   /* WIDTH */          BSP_FLASH_WIDTH,
   /* DEVICES */        BSP_FLASH_DEVICES,
   /* WRITE VERIFY? */  1
};
#endif
/* End CR 2108 */

/* EOF */
