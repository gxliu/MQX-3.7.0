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
* $FileName: bootstrap.c$
* $Version : 3.6.8.0$
* $Date    : Feb-10-2011$
*
* Comments:
*
*   This file contains bootstrap code to be used for booting from the NAND
*   flash memory.
*
*END************************************************************************/

#include "mqx.h"
#include "bsp.h"
#include "bsp_prv.h"

#pragma define_section bootstrap_nfcsram_vectors ".bootstrap_nfcsram_vectors" far_absolute R
#pragma define_section bootstrap_nfcsram_code ".bootstrap_nfcsram_code" far_absolute R

#pragma define_section bootstrap_sram_vectors ".bootstrap_sram_vectors" far_absolute R
#pragma define_section bootstrap_sram_code ".bootstrap_sram_code" far_absolute R

/* format of the ROM table info entry ... */
typedef struct
{
    uint_32	SOURCE;
    uint_32	TARGET;
    uint_32 SIZE;
} BOOTSTRAP_ROMINFO_STRUCT;

/* imported data */
extern BOOTSTRAP_ROMINFO_STRUCT __BOOTSTRAP_NAND_ROMP[];		/* linker defined symbol */
extern uint_32 __BOOTSTRAP_NFCSRAM_END[];
extern uint_32 __BOOTSTRAP_SRAM_SIZE[];


/* Prototypes of bootstrap functions  */
extern void __boot();
extern asm void __boot_sram_exception(void);
extern asm void __boot_nfcsram_exception(void);
extern asm void __boot_nfc(void);

void bootstrap_nfcsram_copy_code_to_sram (void);
void bootstrap_sram_main(void);

static void bootstrap_sram_nfcinit(void);
static void bootstrap_sram_read_data(uint_32 block,uint_32 page);
static boolean bootstrap_sram_check_block(uint_32 block_number);
static uint_32 bootstrap_sram_copy_section(uint_32 block, uint_32 page, 
                                           uint_32 offset, uint_32 length,
                                           uint_32* dest_addr);
static void bootstrap_sram_mcf5441_init(void);
static void bootstrap_sram_pll_init(void);
static void bootstrap_sram_sdram_init (uint_32 sd_clk_per, SDRAM_INFO sdram_params);


/* Vector table for NFCSRAM */
__declspec(bootstrap_nfcsram_vectors) void* bootstrap_nfcsram_vector[64] = 
{
   (void*)0xf80,
   __boot_nfc,
   __boot_nfcsram_exception,   /*  2 (0x008) Access Error         */
   __boot_nfcsram_exception,   /*  3 (0x00C) Address Error        */
   __boot_nfcsram_exception,   /*  4 (0x010) Illegal Instruction  */
   __boot_nfcsram_exception,   /*  5 (0x014) Reserved             */
   __boot_nfcsram_exception,   /*  6 (0x018) Reserved             */
   __boot_nfcsram_exception,   /*  7 (0x01C) Reserved             */
   __boot_nfcsram_exception,   /*  8 (0x020) Privilege Violation  */
   __boot_nfcsram_exception,   /*  9 (0x024) Trace                */
   __boot_nfcsram_exception,   /* 10 (0x028) Unimplemented A-Line */
   __boot_nfcsram_exception,   /* 11 (0x02C) Unimplemented F-Line */
   __boot_nfcsram_exception,   /* 12 (0x030) Debug Interrupt      */
   __boot_nfcsram_exception,   /* 13 (0x034) Reserved             */
   __boot_nfcsram_exception,   /* 14 (0x038) Format Error         */
   __boot_nfcsram_exception,   /* 15 (0x03C) Unitialized Int      */
   __boot_nfcsram_exception,   /* 16 (0x040) Reserved             */
   __boot_nfcsram_exception,   /* 17 (0x044) Reserved             */
   __boot_nfcsram_exception,   /* 18 (0x048) Reserved             */
   __boot_nfcsram_exception,   /* 19 (0x04C) Reserved             */
   __boot_nfcsram_exception,   /* 20 (0x050) Reserved             */
   __boot_nfcsram_exception,   /* 21 (0x054) Reserved             */
   __boot_nfcsram_exception,   /* 22 (0x058) Reserved             */
   __boot_nfcsram_exception,   /* 23 (0x05C) Reserved             */
   __boot_nfcsram_exception,   /* 24 (0x060) Spurious Interrupt   */
   __boot_nfcsram_exception,   /* 25 (0x064) Autovector Level 1   */
   __boot_nfcsram_exception,   /* 26 (0x068) Autovector Level 2   */
   __boot_nfcsram_exception,   /* 27 (0x06C) Autovector Level 3   */
   __boot_nfcsram_exception,   /* 28 (0x070) Autovector Level 4   */
   __boot_nfcsram_exception,   /* 29 (0x074) Autovector Level 5   */
   __boot_nfcsram_exception,   /* 30 (0x078) Autovector Level 6   */
   __boot_nfcsram_exception,   /* 31 (0x07C) Autovector Level 7   */
   __boot_nfcsram_exception,   /* 32 (0x080) TRAP #0              */
   __boot_nfcsram_exception,   /* 33 (0x084) TRAP #1              */
   __boot_nfcsram_exception,   /* 34 (0x088) TRAP #2              */
   __boot_nfcsram_exception,   /* 35 (0x08C) TRAP #3              */
   __boot_nfcsram_exception,   /* 36 (0x090) TRAP #4              */
   __boot_nfcsram_exception,   /* 37 (0x094) TRAP #5              */
   __boot_nfcsram_exception,   /* 38 (0x098) TRAP #6              */
   __boot_nfcsram_exception,   /* 39 (0x09C) TRAP #7              */
   __boot_nfcsram_exception,   /* 40 (0x0A0) TRAP #8              */
   __boot_nfcsram_exception,   /* 41 (0x0A4) TRAP #9              */
   __boot_nfcsram_exception,   /* 42 (0x0A8) TRAP #10             */
   __boot_nfcsram_exception,   /* 43 (0x0AC) TRAP #11             */
   __boot_nfcsram_exception,   /* 44 (0x0B0) TRAP #12             */
   __boot_nfcsram_exception,   /* 45 (0x0B4) TRAP #13             */
   __boot_nfcsram_exception,   /* 46 (0x0B8) TRAP #14             */
   __boot_nfcsram_exception,   /* 47 (0x0BC) TRAP #15             */
   __boot_nfcsram_exception,   /* 48 (0x0C0) Reserved             */
   __boot_nfcsram_exception,   /* 49 (0x0C4) Reserved             */
   __boot_nfcsram_exception,   /* 50 (0x0C8) Reserved             */
   __boot_nfcsram_exception,   /* 51 (0x0CC) Reserved             */
   __boot_nfcsram_exception,   /* 52 (0x0D0) Reserved             */
   __boot_nfcsram_exception,   /* 53 (0x0D4) Reserved             */
   __boot_nfcsram_exception,   /* 54 (0x0D8) Reserved             */
   __boot_nfcsram_exception,   /* 55 (0x0DC) Reserved             */
   __boot_nfcsram_exception,   /* 56 (0x0E0) Reserved             */
   __boot_nfcsram_exception,   /* 57 (0x0E4) Reserved             */
   __boot_nfcsram_exception,   /* 58 (0x0E8) Reserved             */
   __boot_nfcsram_exception,   /* 59 (0x0EC) Reserved             */
   __boot_nfcsram_exception,   /* 60 (0x0F0) Reserved             */
   __boot_nfcsram_exception,   /* 61 (0x0F4) Reserved             */
   __boot_nfcsram_exception,   /* 62 (0x0F8) Reserved             */
   __boot_nfcsram_exception    /* 63 (0x0FC) Reserved             */
};

/* Vector table for Internal SRAM */
__declspec(bootstrap_sram_vectors) void* bootstrap_sram_vector[64] = 
{
   (void*)0x0,              /* never used in NAND Flash target */
   (void*)0x0,              /* never used in NAND Flash target */
   __boot_sram_exception,   /*  2 (0x008) Access Error         */
   __boot_sram_exception,   /*  3 (0x00C) Address Error        */
   __boot_sram_exception,   /*  4 (0x010) Illegal Instruction  */
   __boot_sram_exception,   /*  5 (0x014) Reserved             */
   __boot_sram_exception,   /*  6 (0x018) Reserved             */
   __boot_sram_exception,   /*  7 (0x01C) Reserved             */
   __boot_sram_exception,   /*  8 (0x020) Privilege Violation  */
   __boot_sram_exception,   /*  9 (0x024) Trace                */
   __boot_sram_exception,   /* 10 (0x028) Unimplemented A-Line */
   __boot_sram_exception,   /* 11 (0x02C) Unimplemented F-Line */
   __boot_sram_exception,   /* 12 (0x030) Debug Interrupt      */
   __boot_sram_exception,   /* 13 (0x034) Reserved             */
   __boot_sram_exception,   /* 14 (0x038) Format Error         */
   __boot_sram_exception,   /* 15 (0x03C) Unitialized Int      */
   __boot_sram_exception,   /* 16 (0x040) Reserved             */
   __boot_sram_exception,   /* 17 (0x044) Reserved             */
   __boot_sram_exception,   /* 18 (0x048) Reserved             */
   __boot_sram_exception,   /* 19 (0x04C) Reserved             */
   __boot_sram_exception,   /* 20 (0x050) Reserved             */
   __boot_sram_exception,   /* 21 (0x054) Reserved             */
   __boot_sram_exception,   /* 22 (0x058) Reserved             */
   __boot_sram_exception,   /* 23 (0x05C) Reserved             */
   __boot_sram_exception,   /* 24 (0x060) Spurious Interrupt   */
   __boot_sram_exception,   /* 25 (0x064) Autovector Level 1   */
   __boot_sram_exception,   /* 26 (0x068) Autovector Level 2   */
   __boot_sram_exception,   /* 27 (0x06C) Autovector Level 3   */
   __boot_sram_exception,   /* 28 (0x070) Autovector Level 4   */
   __boot_sram_exception,   /* 29 (0x074) Autovector Level 5   */
   __boot_sram_exception,   /* 30 (0x078) Autovector Level 6   */
   __boot_sram_exception,   /* 31 (0x07C) Autovector Level 7   */
   __boot_sram_exception,   /* 32 (0x080) TRAP #0              */
   __boot_sram_exception,   /* 33 (0x084) TRAP #1              */
   __boot_sram_exception,   /* 34 (0x088) TRAP #2              */
   __boot_sram_exception,   /* 35 (0x08C) TRAP #3              */
   __boot_sram_exception,   /* 36 (0x090) TRAP #4              */
   __boot_sram_exception,   /* 37 (0x094) TRAP #5              */
   __boot_sram_exception,   /* 38 (0x098) TRAP #6              */
   __boot_sram_exception,   /* 39 (0x09C) TRAP #7              */
   __boot_sram_exception,   /* 40 (0x0A0) TRAP #8              */
   __boot_sram_exception,   /* 41 (0x0A4) TRAP #9              */
   __boot_sram_exception,   /* 42 (0x0A8) TRAP #10             */
   __boot_sram_exception,   /* 43 (0x0AC) TRAP #11             */
   __boot_sram_exception,   /* 44 (0x0B0) TRAP #12             */
   __boot_sram_exception,   /* 45 (0x0B4) TRAP #13             */
   __boot_sram_exception,   /* 46 (0x0B8) TRAP #14             */
   __boot_sram_exception,   /* 47 (0x0BC) TRAP #15             */
   __boot_sram_exception,   /* 48 (0x0C0) Reserved             */
   __boot_sram_exception,   /* 49 (0x0C4) Reserved             */
   __boot_sram_exception,   /* 50 (0x0C8) Reserved             */
   __boot_sram_exception,   /* 51 (0x0CC) Reserved             */
   __boot_sram_exception,   /* 52 (0x0D0) Reserved             */
   __boot_sram_exception,   /* 53 (0x0D4) Reserved             */
   __boot_sram_exception,   /* 54 (0x0D8) Reserved             */
   __boot_sram_exception,   /* 55 (0x0DC) Reserved             */
   __boot_sram_exception,   /* 56 (0x0E0) Reserved             */
   __boot_sram_exception,   /* 57 (0x0E4) Reserved             */
   __boot_sram_exception,   /* 58 (0x0E8) Reserved             */
   __boot_sram_exception,   /* 59 (0x0EC) Reserved             */
   __boot_sram_exception,   /* 60 (0x0F0) Reserved             */
   __boot_sram_exception,   /* 61 (0x0F4) Reserved             */
   __boot_sram_exception,   /* 62 (0x0F8) Reserved             */
   __boot_sram_exception    /* 63 (0x0FC) Reserved             */
};

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : bootstrap_nfcsram_copy_code_to_sram
* Returned Value   : void
* Comments         : This code copies sram portion of the bootstrap code 
*                    (incl. vectors) from the NFC SRAM memory to the Internal 
*                    SRAM memory. This code must be linked to NFCSRAM memory.
*
*END*----------------------------------------------------------------------*/
__declspec(bootstrap_nfcsram_code)
void bootstrap_nfcsram_copy_code_to_sram (void)
{
    char *dst = (char*)&__INTERNAL_SRAM_BASE;
    char *src = (char*)__BOOTSTRAP_NFCSRAM_END;
    uint_32 size = (uint_32)__BOOTSTRAP_SRAM_SIZE;

    if (dst != src) {
        while (size--) {
            *((char *)dst)++ = *((char *)src)++;
        }
    }
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : bootstrap_sram_main
* Returned Value   : void
* Comments         : Internal SRAM portion of the bootstrap code.
*                    This code must be linked to Internal SRAM memory.
*
*END*----------------------------------------------------------------------*/
__declspec(bootstrap_sram_code) 
void bootstrap_sram_main(void)
{
  int_32 index;
  uint_32 block, page, num_bad_blocks, bad_blocks_total = 0;
  uint_32* src_addr;
  uint_32* dest_addr;
  uint_32  nfc_sram_offset;
  VNFC_STRUCT_PTR  nfc_ptr;
  
  /* Initialize PLL and SDRAM */
  bootstrap_sram_mcf5441_init();
     
  /* Get the pointer to nfc registers structure */
  nfc_ptr = (&((VMCF5441_STRUCT_PTR)_PSP_GET_IPSBAR())->NFC);
  
  /* Clear the BTMD bit of the NFC_CFG reg. to switch from boot mode to normal mode */
  nfc_ptr->CFG &= ~NFC_CFG_BTMD;
  
  /* Initialize GPIO pins for nand flash booting and reset the NAND Flash memory */
  bootstrap_sram_nfcinit();
  
  /*
   *	Go through the entire table, copying sections from ROM to RAM.
   */
  for (index = 0;
  	 (void *)__BOOTSTRAP_NAND_ROMP[index].SOURCE != NULL ||
  	 (void *)__BOOTSTRAP_NAND_ROMP[index].TARGET != NULL ||
  	 __BOOTSTRAP_NAND_ROMP[index].SIZE != 0;
  	 ++index)
  {
    block     = ((((uint_32)(__BOOTSTRAP_NAND_ROMP[index].SOURCE))) / NANDFLASH_BLOCK_SIZE) + bad_blocks_total;
    page      = (((uint_32)(__BOOTSTRAP_NAND_ROMP[index].SOURCE))) / NANDFLASH_PHYSICAL_PAGE_SIZE;
    page      &= 0x3F;
    nfc_sram_offset = (((uint_32)(__BOOTSTRAP_NAND_ROMP[index].SOURCE))) - block*NANDFLASH_BLOCK_SIZE - page*NANDFLASH_PHYSICAL_PAGE_SIZE; 
  	
  	num_bad_blocks = bootstrap_sram_copy_section(block, page, nfc_sram_offset, (uint_32)__BOOTSTRAP_NAND_ROMP[index].SIZE, (uint_32 *)__BOOTSTRAP_NAND_ROMP[index].TARGET);
  	bad_blocks_total += num_bad_blocks;
  } 	

  /* Start the application */
  __boot();
}

__declspec(bootstrap_sram_code) 
SDRAM_INFO bootstrap_sram_sdraminf = { SDRAM_DDR2, 14, 10, 8, CASL_5, 10, 12, 8, 16, 20, 10, 0x0b, 44, 70000, 56, 152, 8, 7800, 2, 8 };

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : bootstrap_sram_nfcinit
* Returned Value   : void
* Comments         : Necessary GPIO initialization and NAND Flash memory reset.
*                    This code must be linked to Internal SRAM memory.
*
*END*----------------------------------------------------------------------*/
__declspec(bootstrap_sram_code) 
static void bootstrap_sram_nfcinit(void)
{
  VMCF5441_STRUCT_PTR reg = (VMCF5441_STRUCT_PTR)_PSP_GET_IPSBAR();
  VNFC_STRUCT_PTR  nfc_ptr;
  
  reg->GPIO.PAR_CS &= 0xF3;
  reg->GPIO.PAR_CS |= 0x04; /* /CS1-->/NFC_CE  */
  
  reg->GPIO.PAR_BE &= 0x0F;
  reg->GPIO.PAR_BE |= 0x50; /* ALE & CLE */
  
  reg->GPIO.PAR_FBCTL &= 0xFC;
  reg->GPIO.PAR_FBCTL |= 0x01; /* /FB_TA-->NFC_R/B */
  reg->CCM.FNACR = 0;
  
  /* Get the pointer to nfc registers structure */
  nfc_ptr = (&((VMCF5441_STRUCT_PTR)_PSP_GET_IPSBAR())->NFC);
  
  /* Setting up 16 bit mode */    
  nfc_ptr->CFG |= NFC_CFG_16BIT; 	
  
  /* Clearing interrupts bits */
  nfc_ptr->ISR  |= (NFC_ISR_DONECLR | 
                    NFC_ISR_DONEEN | 
                    NFC_ISR_IDLECLR |
                    NFC_ISR_IDLEEN);
  nfc_ptr->CMD2  =  NFC_CMD2_BYTE1(NANDFLASH_CMD_RESET) | 
                    NFC_CMD2_CODE(0x4040);
     
  /* Start command execution */
  nfc_ptr->CMD2 |=  NFC_CMD2_BUSY_START;
  
  /* Polling for cmd done IRQ*/	
  while(!(nfc_ptr->ISR & NFC_ISR_DONE))
  {
  }
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : bootstrap_sram_read_data
* Returned Value   : void
* Comments         : Read data from the NAND Flash memory. Block# and page#
*                    must be specified.
*                    This code must be linked to Internal SRAM memory.
*
*END*----------------------------------------------------------------------*/
__declspec(bootstrap_sram_code) 
static void bootstrap_sram_read_data(uint_32 block,uint_32 page)
{ 
  VNFC_STRUCT_PTR  nfc_ptr;
  uint_32 i;
     
  /* Get the pointer to nfc registers structure */
  nfc_ptr = (&((VMCF5441_STRUCT_PTR)_PSP_GET_IPSBAR())->NFC);
  
  /* Clearing interrupts bits */
  nfc_ptr->ISR  |= (NFC_ISR_DONECLR | 
                    NFC_ISR_DONEEN | 
                    NFC_ISR_IDLECLR |
                    NFC_ISR_IDLEEN);
   
  /* Clearing buf in use */     
  for(i=0;i<NANDFLASH_PHYSICAL_PAGE_SIZE;i++)
      nfc_ptr->SRAM_B0[i]=0;
       
  /* setting ROW and COLUMN address */
  page &= 0x3F;
  block &= 0x7FF;
  nfc_ptr->RAR = 0x11000000 + page + (block<<6);
  nfc_ptr->CAR = 0x00000000;
  
  nfc_ptr->CMD1 = NFC_CMD1_BYTE2(NANDFLASH_CMD_PAGE_READ_CYCLE2);
  nfc_ptr->CMD2 = NFC_CMD2_BYTE1(NANDFLASH_CMD_PAGE_READ_CYCLE1) | 
                  NFC_CMD2_CODE(0x7EE0) |
                  NFC_CMD2_BUFNO(0);
  
  /* configuring Sector size */
  nfc_ptr->SECSZ = NANDFLASH_PHYSICAL_PAGE_SIZE + NANDFLASH_SPARE_AREA_SIZE;
  
  /* 32bit ECC, 16bit data bus, 1 page cnt */
  nfc_ptr->CFG = (NFC_CFG_ECCMODE(7) | 
                  NFC_CFG_IDCNT(5) |
                  NFC_CFG_TIMEOUT(6) |
                  NFC_CFG_16BIT |
                  NFC_CFG_PAGECNT(1)); 	
  
  /* Sending START */
  nfc_ptr->CMD2 |=  NFC_CMD2_BUSY_START;
  
  /* Polling for cmd done IRQ*/
  while(!(nfc_ptr->ISR & NFC_ISR_IDLE))
  {
  }
}

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : bootstrap_sram_check_block
* Returned Value   : TRUE = BLOCK NOT BAD
*                    FALSE = BLOCK IS BAD
* Comments         : 
*    This function checks if the defined NAND Flash block is bad or not.
* 
*END*----------------------------------------------------------------------*/
__declspec(bootstrap_sram_code) 
static boolean bootstrap_sram_check_block(uint_32 block_number)
{
  VNFC_STRUCT_PTR  nfc_ptr;
  uint_32 result, cfg_bck;
    
  /* Get the pointer to nfc registers structure */
  nfc_ptr = (&((VMCF5441_STRUCT_PTR)_PSP_GET_IPSBAR())->NFC);

  /* Clearing interrupts bits */
  nfc_ptr->ISR  |= (NFC_ISR_DONECLR | 
                    NFC_ISR_DONEEN | 
                    NFC_ISR_IDLECLR |
                    NFC_ISR_IDLEEN);

  /* Set the ECCMODE to 0 - ECC bypass */
  cfg_bck = nfc_ptr->CFG;
  nfc_ptr->CFG &= ~(NFC_CFG_ECCMODE(7));
  
  /* setting ROW and COLUMN address */
  block_number &= 0x7FF;
  nfc_ptr->RAR  = 0x11000000 + (block_number<<6);
  nfc_ptr->CAR  = NANDFLASH_PHYSICAL_PAGE_SIZE / 2;

  nfc_ptr->CMD1 = NFC_CMD1_BYTE2(NANDFLASH_CMD_PAGE_READ_CYCLE2);
  nfc_ptr->CMD2 = NFC_CMD2_BYTE1(NANDFLASH_CMD_PAGE_READ_CYCLE1) | 
                  NFC_CMD2_CODE(0x7EE0) |
                  NFC_CMD2_BUFNO(1);

  /* configuring Sector size */
  nfc_ptr->SECSZ  = 3;

  /* Start command execution */
  nfc_ptr->CMD2 |= NFC_CMD2_BUSY_START;
 
  /* Polling for cmd done IRQ*/
  while(!(nfc_ptr->ISR & NFC_ISR_IDLE))
  {
  }

  if((nfc_ptr->SRAM_B1[0] == 0x00) && (nfc_ptr->SRAM_B1[1] == 0x00))
  {
      result = FALSE;
  }
  else
  {
      result = TRUE;
  }
  
  /* Set the ECCMODE back */
  nfc_ptr->CFG = cfg_bck;
   
  return(result);
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : bootstrap_sram_copy_section
* Returned Value   : number of skipped blocks when bad blocks are detected
* Comments         : Copies whole section from the NAND Flash memory to the
*                    specified RAM destination.
*                    This code must be linked to Internal SRAM memory.
*
*END*----------------------------------------------------------------------*/
__declspec(bootstrap_sram_code) 
static uint_32 bootstrap_sram_copy_section(uint_32 block, uint_32 page, 
                                           uint_32 offset, uint_32 length,
                                           uint_32* dest_addr)
{ 
  VNFC_STRUCT_PTR  nfc_ptr;
	uint_32* src_addr;
	int_32 size, len;
	uint_32 num_skipped_blocks = 0;

  /* Get the pointer to nfc registers structure */
  nfc_ptr = (&((VMCF5441_STRUCT_PTR)_PSP_GET_IPSBAR())->NFC);

	len = (int_32)length;
	while(1)
	{
		
		bootstrap_sram_read_data(block, page);
        size = NANDFLASH_PHYSICAL_PAGE_SIZE - offset;
        src_addr = (uint_32*)&nfc_ptr->SRAM_B0[offset];
        while (size-- && len--) {
            *((char *)dest_addr)++ = *((char *)src_addr)++;
        }
		
		if(len<0)
		{    
            break;
		}   
		if(size<0)
		{
		    offset = 0;
		    page++;
		    if((page&0x3f)==0)
		    {
		        block++;
		        while((bootstrap_sram_check_block(block)) == FALSE)
		        {
		            num_skipped_blocks++;
		            block++;
		        }
		    }
		}
	}
	return(num_skipped_blocks);
}
/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : bootstrap_sram_mcf5441_init
* Returned Value   : void
* Comments         : Initialize CPU speed and SDRAM memory.
*
*END*----------------------------------------------------------------------*/
__declspec(bootstrap_sram_code)
static void bootstrap_sram_mcf5441_init(void) {
    VMCF5441_STRUCT_PTR reg = (VMCF5441_STRUCT_PTR)_PSP_GET_IPSBAR();

    /* pll init */
    bootstrap_sram_pll_init();
    
    /* enabling peripheral clocks */
    reg->SCM_PMM.PMM.PPMCR0 = 18;   /* ICTRL0 */
    reg->SCM_PMM.PMM.PPMCR0 = 19;   /* ICTRL1 */
    reg->SCM_PMM.PMM.PPMCR0 = 20;   /* ICTRL2 */
    
    reg->SCM_PMM.PMM.PPMCR0 = 32;   /* PIT0 */
    reg->SCM_PMM.PMM.PPMCR0 = 33;   /* PIT1 */
    reg->SCM_PMM.PMM.PPMCR0 = 34;   /* PIT2 */
    reg->SCM_PMM.PMM.PPMCR0 = 35;   /* PIT3 */
    
    reg->SCM_PMM.PMM.PPMCR0 = 46;   /* SDRAM */

    /* sdram init */
    bootstrap_sram_sdram_init(4, bootstrap_sram_sdraminf);
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : bootstrap_sram_pll_init
* Returned Value   : void
* Comments         : Initialize clock.
*
*END*----------------------------------------------------------------------*/
__declspec(bootstrap_sram_code)
static void bootstrap_sram_pll_init(void) {
    VMCF5441_STRUCT_PTR reg = (VMCF5441_STRUCT_PTR)_PSP_GET_IPSBAR();
    /* pll */
    reg->CCM.MISCCR |= MCF54XX_CCM_MISCCR_LIMP;
    
    reg->PLL.DR = MCF5441_PLL_DR_OUTDIV5(14 - 1)   /* NAND clk fnfc = fvco / 14 */ 
        | MCF5441_PLL_DR_OUTDIV4(8 - 1)            /* fusb = fvco / 8 */
        | MCF5441_PLL_DR_OUTDIV3(2 - 1)            /* ffb_clk = fvco / 2 */
        | MCF5441_PLL_DR_OUTDIV2(4 - 1)            /* fbus = fsys / 2 = fvco / 4 */
        | MCF5441_PLL_DR_OUTDIV1(2 - 1);           /* fsys = fvco / 2 */

    reg->PLL.CR = MCF5441_PLL_CR_LOLEN | MCF5441_PLL_CR_FBKDIV(10 - 1);     /* fvco = 10 * 50MHz = 500MHz */

    reg->CCM.MISCCR &= ~MCF54XX_CCM_MISCCR_LIMP;
    
    while (!(reg->PLL.SR & MCF5441_PLL_SR_LOCK)) {
        /* _ASM_NOP(); */    
    };
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : bootstrap_sram_sdram_init
* Returned Value   : void
* Comments         : Initialize SDRAM controller.
*
*END*----------------------------------------------------------------------*/

__declspec(bootstrap_sram_code)
static void bootstrap_sram_sdram_init (uint_32 sd_clk_per, SDRAM_INFO sdram_params)
{
    uint_32 temp, temp2;    /* temp variables used to store intermediate register and field values */
    VMCF5441_STRUCT_PTR reg = (VMCF5441_STRUCT_PTR)_PSP_GET_IPSBAR();
    VMCF5441_DDRMC_STRUCT_PTR ddrmc = (VMCF5441_DDRMC_STRUCT_PTR)&reg->DDRMC;
    

    /*  Test to make sure that the SDRAMC has not already been initialized before
     *  starting. If it has, then we do not want to re-init.
     */
    if(!(ddrmc->DDR_CR09 & MCF5441_DDRMC_DDR_CR09_START)) {
        /* Need to parameterize this later. Right now it is hard coded for full strength DDR2 */
        reg->GPIO.MSCR_SDRAMC = 0x01;

        /* DDR PHY initialization */
        ddrmc->DDR_PHY_RCR_CTRL = 0x00000000;       /* Disable RCR */
        ddrmc->DDR_PHY_RCR_CTRL |= MCF5441_DDRMC_DDR_PHY_RCR_CTRL_RCR_RST;      /* Force RCR soft reset */
      
        /* Are these the correct settings to use for DDR1, or just for DDR2? */
        ddrmc->DDR_PHY_PAD_CTRL = (MCF5441_DDRMC_DDR_PHY_PAD_CTRL_PAD_ODT_CS0(0x1)
                                | MCF5441_DDRMC_DDR_PHY_PAD_CTRL_OFFSET_VALUE(0x3)
                                | MCF5441_DDRMC_DDR_PHY_PAD_CTRL_PAD_DEBUG(0x2)
                                | MCF5441_DDRMC_DDR_PHY_PAD_CTRL_SPARE_DLY_CTRL(0x3)
                                );
        
        ddrmc->DDR_CR02 = (MCF5441_DDRMC_DDR_CR02_BIGEND); /* enable big endian mode */
                        
        /* Enable differential DQS mode if using DDR2 */
      	ddrmc->DDR_CR03 = MCF5441_DDRMC_DDR_CR03_DQSBEN;
    
        /* To initialize CTL4 we need to determine the number of banks in the memory */
        switch (sdram_params.num_banks) {
            case 4: 
                temp = 0;   /* bit is cleared for 4 banks */
                break;
            case 8: 
                temp = MCF5441_DDRMC_DDR_CR04_8BNK;     /* bit is set for 8 banks */
                break;
            default: 
                /* ERR! Unsupported number of banks. */
                break;
        }
    
        ddrmc->DDR_CR04 = 	(temp /* use the setting for banks determined by case statement above */
                           	| MCF5441_DDRMC_DDR_CR04_QKREF
                        	);

        ddrmc->DDR_CR06 = 	(MCF5441_DDRMC_DDR_CR06_ODT_ALT_EN    /* ODT and CASL3 supported, documentation says this bit must be set */
                           	| MCF5441_DDRMC_DDR_CR06_ODT_ADD_TURN_CLK_EN /* add turnaround clock between back to back reads to different banks */
                        	);
                        
        ddrmc->DDR_CR08 = (MCF5441_DDRMC_DDR_CR08_REDUC); /* 8-bit port width */

        ddrmc->DDR_CR10 = (MCF5441_DDRMC_DDR_CR10_TREF_ENABLE);    /* enable controller to refresh the memory */
                    
        /* Will need to parameterize the FIFO_TYPE_REG settings eventually */                   
        ddrmc->DDR_CR11 = MCF5441_DDRMC_DDR_CR11_AHB0_FIFO_TYPE_REG(0x3);   /* synchronous mode */
                        
        ddrmc->DDR_CR12 = 	(MCF5441_DDRMC_DDR_CR12_CSMAP(1) /* enable chip select, right now this is a two bit field, but only one CS on MCF5441x */
                          	| MCF5441_DDRMC_DDR_CR12_AHB1_FIFO_TYPE_REG(0x3) /* synchronous mode */
                        	);  

        ddrmc->DDR_CR13 = 0;
                    
        ddrmc->DDR_CR14 = MCF5441_DDRMC_DDR_CR14_ODT_WR_MAP_CS0(1); /* enable write ODT for a chip select, right now this is a two bit field */
                    
        /* Calculate difference between max addr pins (16) and actual number of 
        * address lines used in order to initialize CTL15[ADDPINS] */
        temp = 16 - sdram_params.num_row_addr;
    
        /* Error check to make sure num of row addresses field is valid */
        /* Not sure what actual max value for the ADDPINS field is
        * so I might need to revisit this. */
        ddrmc->DDR_CR15 = (MCF5441_DDRMC_DDR_CR15_ADDR_PINS(temp)   /* allows controller to determine number of row addresses */
                            | MCF5441_DDRMC_DDR_CR15_RTT_0(0x1) /* set ODT termination resistance, use 75 ohm for now */
                            | MCF5441_DDRMC_DDR_CR15_Q_FULLNESS(0x1)    /* not really sure what this is used for, might be a status bit */
                        );
                    
        /* Calculate difference between max col pins (12) and actual number of 
        * column address lines used in order to initialize CTL16[COLSIZ] */
        temp = 12 - sdram_params.num_col_addr;
    
        /* Error check to make sure num of col addresses field is valid */
        /* Not sure what actual max value for the COLSIZ field is
        * so I might need to revisit this. */
                                                                        
        /* Calculate CASLAT field value based on passed in casl value  */
        if (sdram_params.casl == CASL_2_5)      
            temp2 = 0x6;  /* This is the DDR1 mode reg value for CASL = 2.5 */
        else
            temp2 = sdram_params.casl; /* For whole num CASL values, the mode reg setting matches the CASL */

        ddrmc->DDR_CR16 = (MCF5441_DDRMC_DDR_CR16_COLUMN_SIZE(temp)
        /*                      | MCF5441_DDRMC_DDR_CR16_CKE_DELAY(0) // additional cycles to delay CKE for status reporting */
                                | MCF5441_DDRMC_DDR_CR16_CASLAT(temp2)
                        );                  
                        
        ddrmc->DDR_CR17 = (MCF5441_DDRMC_DDR_CR17_TDFI_CTRL_DELAY(0x2) /* delay for power-down or self refresh; this value comes from old ddr2_init routine, not sure if this is really right */
                                | MCF5441_DDRMC_DDR_CR17_TCKE(0x3) /* min CKE pulse width, value comes from old ddr2_init */
        /*                      | MCF5441_DDRMC_DDR_CR17_COMMAND_AGE_COUNT // command aging counter */
                        );
                        
        ddrmc->DDR_CR18 = (MCF5441_DDRMC_DDR_CR18_TRRD((int)((sdram_params.trrd/sd_clk_per) + 1)) /* active to active delay */
        /*                      | MCF_DDR_CR18_TRRD((int)((sdram_params.trrd/sd_clk_per) + 0.5)) // active to active delay */
                                | MCF5441_DDRMC_DDR_CR18_TDFI_DRAM_CLK_ENABLE(0x1)
                                | MCF5441_DDRMC_DDR_CR18_TDFI_DRAM_CLK_DISABLE(0x2) /* cycles to needed to disable PHY clock, 0x2 is recommended setting */
                        );

        /* Forcing to DDR2 selection since memtype passing isn't working correctly */                       
        /* Determine the WRLAT value to use in CTL19 */
        temp = sdram_params.casl - 1;

        ddrmc->DDR_CR19 = (MCF5441_DDRMC_DDR_CR19_APREBIT(0xA) /* location of AP bit, set to 10 for now might need to make this a variable later */
                                | MCF5441_DDRMC_DDR_CR19_WRLAT(temp)
                                | MCF5441_DDRMC_DDR_CR19_TWTR((int)((sdram_params.twtr/sd_clk_per) + 1)) /* write to read delay */
                                | MCF5441_DDRMC_DDR_CR19_TRTP((int)((sdram_params.trtp/sd_clk_per) + 1)) /* read to precharge delay */
                        );
                    
        /* Determine value for CASLAT field in CTL20 */
        temp = sdram_params.casl << 1;  /* shift CASL by one bit. this makes space for the fractional component */
        if (sdram_params.casl > 0x200)  /* determine if the CASL has a fractional component */
        {
            temp |= 0x1;    /* set bit 1 to add 0.5 */
            temp &= ~0x200; /* clear the upper bit used for indicating the fraction in the original value */
        }               
                    
        ddrmc->DDR_CR20 = (MCF5441_DDRMC_DDR_CR20_INITAREF(0x2) /* # of refreshes needed during init sequence, need 2 for DDR1 and DDR2 */
                                | MCF5441_DDRMC_DDR_CR20_CASLAT_LIN(temp) /* CASL value */
                        );
                    
        ddrmc->DDR_CR21 = (MCF5441_DDRMC_DDR_CR21_TDFI_PHY_RDLAT(0x5) /* PHY read latency, current value comes from old ddr2_init */
                                | MCF5441_DDRMC_DDR_CR21_TDAL((int)((sdram_params.twr/sd_clk_per) + (sdram_params.trp/sd_clk_per) + 1))
                        );
                    
        ddrmc->DDR_CR22 = ( 0
                                | MCF5441_DDRMC_DDR_CR22_TRP((int)((sdram_params.trp/sd_clk_per) + 1))
                                | MCF5441_DDRMC_DDR_CR22_TDFI_RDDATA_EN_BASE(0x2) /* DFI read data enable timing parameter, manual says set to 0x2 */
                                | MCF5441_DDRMC_DDR_CR22_TDFI_PHY_WRLAT_BASE(0x2) /* DFI write latency timing parameter, manual says set to 0x2 */
                        );
                    
        ddrmc->DDR_CR23 = ( 0
                                | MCF5441_DDRMC_DDR_CR23_TWR_INT((int)((sdram_params.twr/sd_clk_per) + 1)) /* write recovery time */
                         );
                    
        ddrmc->DDR_CR24 = ( 0
                                | MCF5441_DDRMC_DDR_CR24_TMRD((int)(sdram_params.tmrd)) /* mode register command time */
                                | MCF5441_DDRMC_DDR_CR24_TFAW((int)((sdram_params.tfaw/sd_clk_per) + 1)) /* bank activate period */
                        );
                    
        ddrmc->DDR_CR25 =	(MCF5441_DDRMC_DDR_CR25_TRAS_MIN((int)((sdram_params.tras_min/sd_clk_per) + 1)) /* active to precharge time */
                            | MCF5441_DDRMC_DDR_CR25_TRC((int)((sdram_params.trc/sd_clk_per) + 1)) /* active to active time */
                        	);
                    
        ddrmc->DDR_CR26 = 	(MCF5441_DDRMC_DDR_CR26_INT_MASK(0xFFF)
                           	| MCF5441_DDRMC_DDR_CR26_TRFC((int)((sdram_params.trfc/sd_clk_per) + 1)) /* refresh command period */
                            | MCF5441_DDRMC_DDR_CR26_TRCD_INT((int)((sdram_params.trcd/sd_clk_per) + 1)) /* active to read/write delay */
                        	);                                                                                                                                                                                                                                      

        ddrmc->DDR_CR31 = 	(MCF5441_DDRMC_DDR_CR31_TREF((int)((sdram_params.trefi/sd_clk_per) - 1))); /* # of cycles between refreshes */
                    
        ddrmc->DDR_CR41 = MCF5441_DDRMC_DDR_CR41_TCPD(0x0002); /* clock enable to PRE delay, couldn't find in DRAM spec current setting comes from old ddr2_init */
                    
        ddrmc->DDR_CR42 = 	(MCF5441_DDRMC_DDR_CR42_TRAS_MAX((int)((sdram_params.tras_max/sd_clk_per) + 1)) /* max row active time */
                          	| MCF5441_DDRMC_DDR_CR42_TPDEX(sdram_params.xard) /* power down exit time */
                        	);                  
    
        ddrmc->DDR_CR43 = 	(MCF5441_DDRMC_DDR_CR43_TXSR(0x1) /* self refresh exit time is spec'd in ps, so for MCF54451x we can assume 1 */
                          	| MCF5441_DDRMC_DDR_CR43_TXSNR((int)(((sdram_params.trfc + 10)/sd_clk_per) + 1)) /* exit self refresh to non-read command delay */
                       	 	);
                    
        ddrmc->DDR_CR45 = MCF5441_DDRMC_DDR_CR45_TINIT(0x61A8); /* initialization startup time (200us), might need to parameterize this later */
    
        ddrmc->DDR_CR56 = 	( 0
        					/* forcing to DDR2 right now since memtype isn't passing correctly */
                            | MCF5441_DDRMC_DDR_CR56_DRAM_CLASS(0x4) /* setup controller for DDR1 or DDR2 mode */
                        	);
    
        ddrmc->DDR_CR57 = 	(MCF5441_DDRMC_DDR_CR57_TMOD((int)((sdram_params.tmod/sd_clk_per) + 1)) /* mrs to ODT enable delay */
                            | MCF5441_DDRMC_DDR_CR57_WRLAT_ADJ(sdram_params.casl - 1) /* PHY write latency adjustment, current value comes from old ddr2_init */
                            | MCF5441_DDRMC_DDR_CR57_RDLAT_ADJ(sdram_params.casl) /* PHY read latency adjustment, current value comes from old ddr2_init */
                        	);                                  

        ddrmc->DDR_CR58 = (MCF5441_DDRMC_DDR_CR58_EMRS1_DATA_0(0x4004)  /* set ODT resistance to 75 ohms */
                                );
                    
        /* CTL59 sets up EMR3, but DDR2 spec has all bits reserved */
        ddrmc->DDR_CR59 = 0xC0004004;
                    
        /* Calculate the value for mode register */
        temp = sdram_params.casl << 20; /* start with the CASL field value starting at bit 4 */
        temp |= 0x0002C000;                 /* set burst length to 4 */
        
        /* Calculate write recovery time */
        temp2 = ((int)( (sdram_params.twr/sd_clk_per) + 1))<<24;
        
        ddrmc->DDR_CR60 = (temp|temp2);

        /* Temp value, not really sure if this is needed. If it is need to use caculated mode register value above */                       
        ddrmc->DDR_CR61 = 0x00000242;                       

        /* Now that all the registers are setup, write the CTL9[START] bit to begin initialization sequence */
        ddrmc->DDR_CR09 |= MCF5441_DDRMC_DDR_CR09_START;
    
        /* Wait for init to complete */
        while (!(ddrmc->DDR_CR27 & (1 << 3))) {
            _ASM_NOP();
        }
    }
}
