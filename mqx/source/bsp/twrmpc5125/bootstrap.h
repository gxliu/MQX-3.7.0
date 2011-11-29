#ifndef _bootstrap_h_
#define _bootstrap_h_ 1
/**HEADER********************************************************************
* 
* Copyright (c) 2008-2009 Freescale Semiconductor;
* All Rights Reserved
*
* Copyright (c) 2004-2010 Embedded Access Inc.;
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
* $FileName: bootstrap.h$
* $Version : 3.7.2.0$
* $Date    : Feb-7-2011$
*
* Comments:
* 
*     This file contains functions for boot start up.
*
*END***********************************************************************/



#define CFG_IMMR                     0x80000000
#define IOCTL_BASE_ADDR              0x0a000
#define MBAR                         0x137
#define HID0                         0x3F0	               /* Hardware Implementation Register 0 */
#define HID0_ICE_SHIFT               15
#define HID0_DCE_SHIFT               14
#define HID0_ICE                     (1<<HID0_ICE_SHIFT)	  /* Instruction Cache Enable */
#define HID0_DCE                     (1<<HID0_DCE_SHIFT)	  /* Data Cache Enable */
#define HID0_ICFI                    (1<<11)               /* Instr. Cache Flash Invalidate */
#define CONFIG_SYS_HID0_INIT         HID0_ICE | HID0_ICFI
#define CFG_HID0_INIT                CONFIG_SYS_HID0_INIT
                                     
#define SWCRR                        0x0904                 /* Register offset to immr */
#define LPBAW                        0x0020                 /* Register offset to immr */
#define LPCS0AW                      0x0024
#define LPCS1AW                      0x0028
#define LPCS2AW                      0x002C
#define LPCS3AW                      0x0030
#define LPCS4AW                      0x0034
#define LPCS5AW                      0x0038
#define LPCS6AW                      0x003C
#define LPCA7AW                      0x0040
#define SRAMBAR                      0x00C4
#define NFCBAR                       0x00C8
#define LAWBAR_BAR                   0xFFFFF000             /* Base address mask */
#define MSR_FP                       (1<<13)	               /* Floating Point enable */
#define MSR_ME                       (1<<12)	               /* Machine Check Enable */
#define MSR_RI                       (1<<1)	               /* Recoverable Exception */
#define MSR_KERNEL                   (MSR_FP|MSR_RI)
                                     
#define CONFIG_SYS_SRAM_BASE	       0x30000000
#define CONFIG_SYS_SRAM_SIZE	       0x00008000	            /* 32 KB */
#define CFG_SRAM_BASE	             CONFIG_SYS_SRAM_BASE
#define CFG_INIT_RAM_ADDR            CFG_SRAM_BASE	         /* Initial RAM address */
#define CFG_GBL_DATA_SIZE	          CONFIG_SYS_GBL_DATA_SIZE			/* num bytes initial data */
#define CFG_GBL_DATA_OFFSET          CONFIG_SYS_GBL_DATA_OFFSET
#define CFG_INIT_SP_OFFSET           CONFIG_SYS_INIT_SP_OFFSET
#define CONFIG_SYS_INIT_RAM_ADDR     CONFIG_SYS_SRAM_BASE		/* Initial RAM address */
#define CONFIG_SYS_INIT_RAM_END      CONFIG_SYS_SRAM_SIZE		/* End of used area in RAM */

#define CONFIG_SYS_GBL_DATA_SIZE	    0x100			/* num bytes initial data */
#define CONFIG_SYS_GBL_DATA_OFFSET	 (CONFIG_SYS_INIT_RAM_END - CONFIG_SYS_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_OFFSET	 CONFIG_SYS_GBL_DATA_OFFSET

/* Set for DDR */
#define IOCTRL_MUX_DDR		          0x00000000
#define IOCTL_MEM		                0x00

#define START_REG(start)	          ((start) >> 16)
#define STOP_REG(start, size)        (((start) + (size) - 1) >> 16)

#ifndef __ASM__

extern uint_32 __NAND_BASE_ADDR[];
extern uint_32 __NAND_BOOT_BASE_ADDR[];
extern uint_32 __LOADER_DDR_START[];
extern uint_32 __NAND_BOOT_DST[];
extern uint_32 __START_SRAM_TO_NAND[];
extern uint_32 __END_SRAM_TO_NAND[];
extern uint_32 __SRAM_TO_NAND_SIZE[];
extern uint_32 __START_TEXT_CODE[];
extern uint_32 __END_TEXT_CODE[];
extern uint_32 __TEXT_CODE_SIZE[];
extern uint_32 __BOOTSTRAP_CODE_SIZE[];
extern uint_32 __RAM_CODE_SIZE[];
extern uint_32 __START_SRAM_TO_NAND[];
extern uint_32 __START_ROSDATA[];
extern uint_32 __END_DATA_BSS[];
extern uint_32 __START_IMAGE_DATA[];

#define NAND_BASE_ADDR            ((uint_32_ptr)__NAND_BASE_ADDR)
#define NAND_BOOT_BASE_ADDR       ((uint_32_ptr)__NAND_BOOT_BASE_ADDR)
#define LOADER_DDR_START          ((uint_32_ptr)__LOADER_DDR_START)
#define NAND_BOOT_DST             ((uint_32_ptr)__NAND_BOOT_DST)
#define START_SRAM_TO_NAND        ((uint_32_ptr)__START_SRAM_TO_NAND)
#define END_SRAM_TO_NAND          ((uint_32_ptr)__END_SRAM_TO_NAND)
#define START_TEXT_CODE           ((uint_32_ptr)__START_TEXT_CODE)
#define END_TEXT_CODE             ((uint_32_ptr)__END_TEXT_CODE)

#define SRAM_TO_NAND_SIZE         ((uint_32)__SRAM_TO_NAND_SIZE)
#define TEXT_CODE_SIZE            ((uint_32)__TEXT_CODE_SIZE)
#define BOOTSTRAP_CODE_SIZE       ((uint_32)__BOOTSTRAP_CODE_SIZE)
#define RAM_CODE_SIZE             ((uint_32)__RAM_CODE_SIZE)

#define IMAGE_IMAGIC_NUMBER       0x27051956
#define IMAGE_HEADER_FLAG         0x4d544300

#define IMAGE_IN_TABLE_MASK          0x000000FF
#define IMAGE_TABLE_BLOCK_LOCATION   8000    /* Image table is located in block 8000 */

#define AUTOBOOT_ENABLE    1
#define AUTOBOOT_DISABLE   2
#define AUTOBOOT_RESET     3

typedef struct rom_copy_info {
   uint_32			rom;		/* address in rom */
	uint_32        addr;		/* address in ram (executing address) */
	uint_32     	size;		/* size of section */
} ROM_COPY_INFO;

typedef struct image_header{
   uint_32 IMAGIC;
   uint_32 LEN;
   uint_32 HEADERFLAG;
   uint_32 CHECKSUM;
} IMAGE_HEADER, _PTR_ IMAGE_HEADER_PTR;

typedef struct image_info {
   uint_32 UNUSED;
   uint_32 INDEX;
   uint_32 ADDR;
   uint_32 SIZE;
   uint_32 BLOCK;
   uint_32 BLOCK_NUM;
   uint_32 IS_IMAGE;
   boolean BOOT_DEFAULT;
   uchar   NAME[15];
   uint_32 BOOT_TIMEOUT;
} IMAGE_INFO, _PTR_ IMAGE_INFO_PTR;

extern ROM_COPY_INFO _rom_copy_info[];

#endif __ASM__

#endif
/* EOF */