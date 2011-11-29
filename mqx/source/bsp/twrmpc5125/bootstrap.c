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
* $FileName: bootstrap.c$
* $Version : 3.7.3.1$
* $Date    : Apr-1-2011$
*
* Comments:
* 
*     This file contains functions for boot start up.
*
*END***********************************************************************/
#include "mqx.h"
#include "bsp.h"
#include "bsp_prv.h"
#include "bootstrap.h"

#pragma section code_type ".bootstrap_nand_loader"
#pragma optimization_level 0

uint_32 _autoboot_cmd;
uint_32 _image_index;

/*FUNCTION*----------------------------------------------------------------
*
* Function Name    : bootstrap_sram_nfcinit
* Returned Value   : pointer
* Comments         : 
*                    
*
*END*----------------------------------------------------------------------*/
__declspec(section ".text")					  
pointer bootstrap_get_nand_addr(void)
{ /* Body */
   return NAND_BASE_ADDR;
} /* Endbody */
/*FUNCTION*----------------------------------------------------------------
*
* Function Name    : bootstrap_get_nand_boot_addr
* Returned Value   : pointer
* Comments         : Return pointer to NAND address in boot mode 0xFFF00000
*                    
*
*END*----------------------------------------------------------------------*/
__declspec(section ".bootstrap_nand_loader")					  
pointer bootstrap_get_nand_boot_addr(void)
{ /* Body */
   return NAND_BOOT_BASE_ADDR;
} /* Endbody */

/*FUNCTION*----------------------------------------------------------------
*
* Function Name    : bootstrap_nfcsram_copy_code_to_ddr
* Returned Value   : void
* Comments         : Copy code from SRAM to DDR
*                    
*
*END*----------------------------------------------------------------------*/
__declspec(section ".bootstrap_nand_loader")					  
void bootstrap_nfcsram_copy_code_to_ddr(void)
{ /* Body */
   unsigned int *dst =(unsigned int *)(LOADER_DDR_START);
   unsigned int *src =(unsigned int *)(NAND_BOOT_BASE_ADDR);
   unsigned int size;

   for(size=0;size<0x200;size++)
   {
      *dst++=*src++;
   }
   return ;
} /* Endbody */

/*FUNCTION*----------------------------------------------------------------
*
* Function Name    : sram_nfcinit
* Returned Value   : void
* Comments         : Initialize nand flash device
*                    
*
*END*----------------------------------------------------------------------*/
__declspec(section ".text")
void sram_nfcinit(void) 
{ /* Body */
   VNFC_STRUCT_PTR  nfc_ptr;
   
   nfc_ptr = bootstrap_get_nand_addr();
   
   nfc_ptr->CFG  = NFC_CFG_ECCMODE(7) |
                   NFC_CFG_ECCSRAM    |
                   NFC_CFG_IDCNT(5)   |
                   NFC_CFG_TIMEOUT(6) |
                   NFC_CFG_PAGECNT(1);
   nfc_ptr->RAI  = 0;
   nfc_ptr->SECSZ = NANDFLASH_PHYSICAL_PAGE_SIZE + NANDFLASH_SPARE_AREA_SIZE;
   
  return;
} /* Endbody */

/*FUNCTION*----------------------------------------------------------------
*
* Function Name    : bootstrap_sram_read_page
* Returned Value   : int
* Comments         : Read one page from nand flash device
*                    
*
*END*----------------------------------------------------------------------*/
__declspec(section ".bootstrap_nand_loader")
static  int_32 bootstrap_sram_read_page
(
   /* [IN] Nand flash controller struct */
   VNFC_STRUCT_PTR  nfc_ptr,
   /* [IN] Block number was read from */
   uint_32 block,
   /* [IN] Page number was read from */
   uint_32 page,
   /* [OUT] Data buffer */
   uchar_ptr buffer
)
{ /* Body */
   
   uint_32                  i;
   
   /* Setting ROW and COLUMN address */
   nfc_ptr->CAR   = 0x00000000;
   nfc_ptr->RAR   = NFC_RAR_CS | NFC_RAR_RB
                  | ((block << 8) & 0x00FFFF00)
                  | (page & 0x000000FF);
                  
   nfc_ptr->CMD1  = NFC_CMD1_BYTE2(NANDFLASH_CMD_PAGE_READ_CYCLE2);
  
                  
   /* Setting sector size */
   nfc_ptr->SECSZ = NANDFLASH_PHYSICAL_PAGE_SIZE + NANDFLASH_SPARE_AREA_SIZE;
   
   nfc_ptr->RPT   = NFC_RPT_COUNT(0);
   
   nfc_ptr->CFG   = (NFC_CFG_ECCMODE(7)  
                  | NFC_CFG_IDCNT(5)   
                  | NFC_CFG_TIMEOUT(6) 
                  | NFC_CFG_PAGECNT(1)); 
                  
   nfc_ptr->RAI   = NFC_RAI_INC1(0);
   
   /* Clearing interrupts bits */
   nfc_ptr->ISR   = NFC_ISR_DONECLR
                  | NFC_ISR_DONEEN 
                  | NFC_ISR_IDLECLR
                  | NFC_ISR_IDLEEN;
   
   /* Sending START */
   nfc_ptr->CMD2  = NFC_CMD2_BYTE1(NANDFLASH_CMD_PAGE_READ_CYCLE1)
                  | NFC_CMD2_CODE(0x7EE0)
                  | NFC_CMD2_BUFNO(0)
                  | NFC_CMD2_BUSY_START;
                  
   for(i = 0;i<10;i++){
   }
   
   while(!(nfc_ptr->ISR &(NFC_ISR_IDLE | NFC_ISR_DONE ))) {
   }
   
   for(i=0;i<0x800;i++)
   {
      *(buffer)=nfc_ptr->SRAM_B0[i];
      buffer++;
   }
   
   return 0;
} /* Endbody */

/*FUNCTION*----------------------------------------------------------------
*
* Function Name    : bootstrap_sram_write_page
* Returned Value   : unsigned long
* Comments         : Erase one block at bock_addr
*                    
*
*END*----------------------------------------------------------------------*/
__declspec(section ".text")
uint_32 bootstrap_ddr_erase_block(uint_32 block_addr)
{ /* Body */
   VNFC_STRUCT_PTR  nfc_ptr;
   uint_32                  count;
   int_32                   result = 0;
   
   nfc_ptr = bootstrap_get_nand_addr();
      
   /* Setting ROW and COLUMN address */
   nfc_ptr->CAR   = 0x00000000;
   nfc_ptr->RAR   = NFC_RAR_CS | NFC_RAR_RB
                  | ((block_addr << 8) & 0x00FFFF);
   
                                 
   nfc_ptr->CMD1  = NFC_CMD1_BYTE2(NANDFLASH_CMD_BLOCK_ERASE_CYCLE2)
                  | NFC_CMD1_BYTE3(NANDFLASH_CMD_READ_STATUS);
                  
   nfc_ptr->CMD2  = NFC_CMD2_BYTE1(NANDFLASH_CMD_BLOCK_ERASE_CYCLE1)
                  | NFC_CMD2_CODE(0x4ED8)
                  | NFC_CMD2_BUFNO(0);
                  
   /* Clearing interrupts bits */
   nfc_ptr->ISR   = NFC_ISR_DONECLR
                  | NFC_ISR_DONEEN 
                  | NFC_ISR_IDLECLR
                  | NFC_ISR_IDLEEN;
   
   
   /* Sending START */
   nfc_ptr->CMD2  |= NFC_CMD2_BUSY_START;
  
   for (count = 0; count <= MAX_WAIT_COMMAND; count++){
       if (nfc_ptr->ISR & NFC_ISR_DONE){
           if (nfc_ptr->SR2 & 0x01)
               result = 0;
           else
               result = 1;
           break;
       }
   }
   return result;
} /* Endbody */

/*FUNCTION*----------------------------------------------------------------
*
* Function Name    : bootstrap_sram_write_page
* Returned Value   : unsigned long
* Comments         : Write one page to nand flash device
*                    
*
*END*----------------------------------------------------------------------*/
__declspec(section ".text")
uint_32 bootstrap_ddr_write_page(uint_32 block, uint_32 page,uchar_ptr buffer)
{ /* Body */
   
   VNFC_STRUCT_PTR  nfc_ptr;
   uint_32                  i,count;
   int_32                   result = 0;
   
   nfc_ptr = bootstrap_get_nand_addr();
      
   for ( count = 0; count < 0x800; count++ ){
     	nfc_ptr->SRAM_B0[count] = *(buffer + count);
   }
     
   /* Setting ROW and COLUMN address */
   nfc_ptr->CAR   = 0x00000000;
   nfc_ptr->RAR   = NFC_RAR_CS | NFC_RAR_RB
                  | ((block << 8) & 0x00FFFF00)
                  | (page & 0x000000FF);
                  
   nfc_ptr->CMD1  = NFC_CMD1_BYTE2(NANDFLASH_CMD_PAGE_PROGRAM_CYCLE2)
                  | NFC_CMD1_BYTE3(NANDFLASH_CMD_READ_STATUS);
                  
   nfc_ptr->CMD2  = NFC_CMD2_BYTE1(NANDFLASH_CMD_PAGE_PROGRAM_CYCLE1)
                  | NFC_CMD2_CODE(0x7FD8)
                  | NFC_CMD2_BUFNO(0);
                  
   /* Setting sector size */
   nfc_ptr->SECSZ = NANDFLASH_PHYSICAL_PAGE_SIZE + NANDFLASH_SPARE_AREA_SIZE;
   
   nfc_ptr->CFG   = (NFC_CFG_ECCMODE(7)  
                  | NFC_CFG_IDCNT(5)
                  | NFC_CFG_TIMEOUT(6) 
                  | NFC_CFG_PAGECNT(1)); 
                  
   /* Clearing interrupts bits */
   nfc_ptr->ISR   = NFC_ISR_DONECLR
                  | NFC_ISR_DONEEN 
                  | NFC_ISR_IDLECLR
                  | NFC_ISR_IDLEEN;
   
   /* Sending START */
   nfc_ptr->CMD2  |= NFC_CMD2_BUSY_START;
   
   for (count = 0; count <= MAX_WAIT_COMMAND; count++){
       if (nfc_ptr->ISR & NFC_ISR_IDLE){
          if (nfc_ptr->SR2 & 0x01){
             result = 0;             
          }
          else {
             result = 1;
          }
          break;
       }
     }
   
   return result;
} /* Endbody */

/*FUNCTION*----------------------------------------------------------------
*
* Function Name    : bootstrap_ddr_write_loader_page
* Returned Value   : unsigned long
* Comments         : Write one page to Nand flash device in boot mode
*                    
*
*END*----------------------------------------------------------------------*/
__declspec(section ".text")
uint_32 bootstrap_ddr_write_loader_page(uint_32 row_addr,uchar_ptr buf)
{ /* Body */
   
   VNFC_STRUCT_PTR  nfc_ptr;
   uint_32                  i,count;
   int_32                   result = 0;
   
   nfc_ptr = bootstrap_get_nand_addr();
      
   for ( count = 0; count < 0x800; count++ ){
     	nfc_ptr->SRAM_B0[count] = *(buf + count);
   }
     
   /* Setting ROW and COLUMN address */
   nfc_ptr->CAR   = 0x00000000;
   nfc_ptr->RAR   = NFC_RAR_CS | NFC_RAR_RB
                  | (row_addr & 0x00FFFFFF);
                  
   nfc_ptr->CMD1  = NFC_CMD1_BYTE2(NANDFLASH_CMD_PAGE_PROGRAM_CYCLE2)
                  | NFC_CMD1_BYTE3(NANDFLASH_CMD_READ_STATUS);
                  
   nfc_ptr->CMD2  = NFC_CMD2_BYTE1(NANDFLASH_CMD_PAGE_PROGRAM_CYCLE1)
                  | NFC_CMD2_CODE(0x7FD8)
                  | NFC_CMD2_BUFNO(0);
                  
   /* Setting sector size */
   nfc_ptr->SECSZ = NANDFLASH_BOOT_PAGE_SIZE + NANDFLASH_BOOT_ECCBYTES;
   
   nfc_ptr->CFG   = (NFC_CFG_ECCMODE(7)  
                  | NFC_CFG_IDCNT(5)
                  | NFC_CFG_AIBN
                  | NFC_CFG_AIAD   
                  | NFC_CFG_TIMEOUT(6) 
                  | NFC_CFG_PAGECNT(1)); 
                  
   /* Clearing interrupts bits */
   nfc_ptr->ISR   = NFC_ISR_DONECLR
                  | NFC_ISR_DONEEN 
                  | NFC_ISR_IDLECLR
                  | NFC_ISR_IDLEEN;
   
   /* Sending START */
   nfc_ptr->CMD2  |= NFC_CMD2_BUSY_START;
   
   for (count = 0; count <= MAX_WAIT_COMMAND; count++){
       if (nfc_ptr->ISR & NFC_ISR_IDLE){
          if (nfc_ptr->SR2 & 0x01){
             result = 0;             
          }
          else {
             result = 1;
          }
          break;
       }
     }
   
   return result;
} /* Endbody */

/*FUNCTION*----------------------------------------------------------------
*
* Function Name    : bootstrap_ddr_to_nand
* Returned Value   : void
* Comments         : Copy main function and entire program to Nand flash
*                    
*
*END*----------------------------------------------------------------------*/
__declspec(section ".text")
void bootstrap_ddr_to_nand(void)
{ /* Body */
   static uchar_ptr      buffer;
   static uchar_ptr      src,dst;
   static uint_32        i,j, result, page, page_size, block, block_size;
   uint_32        checksum = 0;
   IMAGE_HEADER   img_hdr,*p_img_hdr;
   static ROM_COPY_INFO  * p_rom_copy_info;
   _bsp_nandflash_io_init();
   sram_nfcinit();
   
   /* Copy boot loader code to block 0 */
   if(bootstrap_ddr_erase_block(0)) {
      src   =  (uchar_ptr)START_SRAM_TO_NAND;
      for(page = 0; page < 4; page++) {
         for(i = 0; i < SRAM_TO_NAND_SIZE; i ++) {
            for(j = 0; j < 8; j++) {
               *(buffer+(i*0x08)+j) = *(src+(i*0x20)+j+(page*0x08));
            }
         }
         bootstrap_ddr_write_loader_page(page,buffer);
      }
   }
   
   /* Remap rom copy array */ 
   p_rom_copy_info = _rom_copy_info;
   while((p_rom_copy_info)->size) {
      if((p_rom_copy_info->rom >= (uint_32)START_SRAM_TO_NAND) && (p_rom_copy_info->rom <= (uint_32)__END_DATA_BSS)) {
         p_rom_copy_info->rom = ((p_rom_copy_info-1)->rom+(p_rom_copy_info-1)->size);
         if(p_rom_copy_info->rom & 0x07)
            p_rom_copy_info->rom = (p_rom_copy_info->rom & ~0x07) + 0x08;
      }
      p_rom_copy_info++;
   }
   
   /* Copy entire MQX code to block 1 */
   src   = (uchar_ptr)(END_TEXT_CODE);
   
   dst   = (uchar_ptr)START_SRAM_TO_NAND;
   
   for(i = 0; i < BOOTSTRAP_CODE_SIZE + 0x08;i++) {
      *(src+i) = *(dst+i);
   }
   
   src   = (uchar_ptr)(END_TEXT_CODE) + BOOTSTRAP_CODE_SIZE - 0x08;
   dst   = (uchar_ptr)__START_ROSDATA;
   
   for(i = 0; i < RAM_CODE_SIZE;i++) {
      *(src+i) = *(dst+i);
   }
   
   src = (uchar_ptr)START_TEXT_CODE;
   for(i = 0; i < TEXT_CODE_SIZE + RAM_CODE_SIZE + BOOTSTRAP_CODE_SIZE;i++) {
      checksum +=*(src+i);
   }
   
   src = (uchar_ptr)START_TEXT_CODE - sizeof(IMAGE_HEADER);
   
   p_img_hdr = (IMAGE_HEADER_PTR)src;
   p_img_hdr->IMAGIC = IMAGE_IMAGIC_NUMBER;
   p_img_hdr->HEADERFLAG =  IMAGE_HEADER_FLAG;
   p_img_hdr->LEN = TEXT_CODE_SIZE + BOOTSTRAP_CODE_SIZE + RAM_CODE_SIZE;
   p_img_hdr->CHECKSUM = checksum;
   
   page_size  = (p_img_hdr->LEN + sizeof(IMAGE_HEADER) + NANDFLASH_PHYSICAL_PAGE_SIZE) 
             / NANDFLASH_PHYSICAL_PAGE_SIZE;
   block_size = (page_size + (NANDFLASH_BLOCK_SIZE/NANDFLASH_PHYSICAL_PAGE_SIZE))
             /(NANDFLASH_BLOCK_SIZE/NANDFLASH_PHYSICAL_PAGE_SIZE);
             
   /* Begin with block 1 */
   for(block = 1; block <= block_size; block++) {
      bootstrap_ddr_erase_block(block);
   }
   for(i = 0; i < page_size; i++) {
      block = (i + (NANDFLASH_BLOCK_SIZE/NANDFLASH_PHYSICAL_PAGE_SIZE))
          /(NANDFLASH_BLOCK_SIZE/NANDFLASH_PHYSICAL_PAGE_SIZE);
      page = i &0xFF;   
      result = bootstrap_ddr_write_page(block,page,src);
      src += NANDFLASH_PHYSICAL_PAGE_SIZE;
   } 

   return;
} /* Endbody */

/*FUNCTION*----------------------------------------------------------------
*
* Function Name    : bootstrap_sram_boot
* Returned Value   : void
* Comments         : Boot loader execution code
*                    
*
*END*----------------------------------------------------------------------*/
__declspec(section ".bootstrap_nand_loader")
void bootstrap_sram_boot(void)
{ /* Body */
   VNFC_STRUCT_PTR  nfc_ptr;
   void           (*boot)(void);
   uint_32        i=0, checksum =0;
   uint_32        page,page_size,block,block_size;
   IMAGE_HEADER   * p_img_hdr;
   uchar_ptr      boot_buf;
   uchar_ptr s;
   
   nfc_ptr = bootstrap_get_nand_boot_addr();
   
   /*first read block1 ,if uboot exist ,read it*/
   boot_buf=(uchar_ptr)NAND_BOOT_DST;
   p_img_hdr=(IMAGE_HEADER *)(NAND_BOOT_DST);
   boot=(void (*)(void) )NAND_BOOT_DST;
   
   /* Read Bock 1 page 0 to get image data header */
   bootstrap_sram_read_page(nfc_ptr,1,0,boot_buf);
   
   page_size  = (p_img_hdr->LEN + sizeof(IMAGE_HEADER) + NANDFLASH_PHYSICAL_PAGE_SIZE) 
             / NANDFLASH_PHYSICAL_PAGE_SIZE;
             
   block_size = (page_size + (NANDFLASH_BLOCK_SIZE/NANDFLASH_PHYSICAL_PAGE_SIZE))
             /(NANDFLASH_BLOCK_SIZE/NANDFLASH_PHYSICAL_PAGE_SIZE);
             
   boot_buf = (uchar_ptr)(NAND_BOOT_DST) - sizeof(IMAGE_HEADER);
   
   p_img_hdr = (IMAGE_HEADER *)boot_buf;
   
   for(i = 0; i < page_size; i++) {
      block = (i + (NANDFLASH_BLOCK_SIZE/NANDFLASH_PHYSICAL_PAGE_SIZE))
            /(NANDFLASH_BLOCK_SIZE/NANDFLASH_PHYSICAL_PAGE_SIZE);
      page = i & 0xFF;
      bootstrap_sram_read_page(nfc_ptr,block,page,boot_buf);
      boot_buf += NANDFLASH_PHYSICAL_PAGE_SIZE;
   }
   
   /* Checksum */
   s=(uchar_ptr)NAND_BOOT_DST;
   checksum=0;
   
   for(i=0;i<p_img_hdr->LEN;i++)
   {
      checksum+=*s++;
   }
   
   if(checksum==p_img_hdr->CHECKSUM)
   {      
      (*boot)();
      return;
   }   
   return;
} /* Endbody */

/*Function*------------------------------------------------------------
*
* Function Name  : _bootloader_reset
* Returned Value : void
* Comments       :
*
*END------------------------------------------------------------------*/
void _bootstrap_reset(void)
{
   MPC5125_RESET_STRUCT_PTR reset = (&((VMPC5125_STRUCT_PTR) MPC5125_GET_IMMR() )->RESET);
   
   uint_32 msr;
   printf ("Resetting the board.\n");
   _PSP_SYNC();
   _mmu_disable();
   _PSP_MSR_GET(msr);
   msr &= ~(PSP_MSR_IR | PSP_MSR_EE | PSP_MSR_DR); // Disable MSR[IR,EE,DR]
   _PSP_MSR_SET(msr);
   
   reset->RPR = 0x52535445;
   
   /* Verify Reset Control Reg is enabled */
	while (!((reset->RCER) & 0x00000001))
	   reset->RPR = 0x52535445;

	/* Perform reset */
	reset->RCR = 0x02;
	
}

/*FUNCTION*----------------------------------------------------------------
*
* Function Name    : bootloader_read_page
* Returned Value   : int
* Comments         : Read one page from nand flash device that was written
*   by MQX driver.
*                    
*
*END*----------------------------------------------------------------------*/
__declspec(section ".text")
static  int_32 bootloader_read_page
(
   /* [IN] Nand flash controller struct */
   VNFC_STRUCT_PTR  nfc_ptr,
   /* [IN] Block number was read from */
   uint_32 block,
   /* [IN] Page number was read from */
   uint_32 page,
   /* [OUT] Data buffer */
   uchar_ptr buffer
)
{ /* Body */
   
    uint_32                  i;
   boolean                  swap = FALSE;
   
   /* Setting ROW and COLUMN address */
   nfc_ptr->CAR   = 0x00000000;
   nfc_ptr->RAR   = NFC_RAR_CS | NFC_RAR_RB
                  | ((block << 8) & 0x00FFFF00)
                  | (page & 0x000000FF);
                  
   nfc_ptr->CMD1  = NFC_CMD1_BYTE2(NANDFLASH_CMD_PAGE_READ_CYCLE2);
   
   /* Setting sector size */
   nfc_ptr->SECSZ = NANDFLASH_PHYSICAL_PAGE_SIZE + NANDFLASH_SPARE_AREA_SIZE;
   
   swap = ((page % (NANDFLASH_BLOCK_SIZE / NANDFLASH_PHYSICAL_PAGE_SIZE) == 0) || 
           (page % (NANDFLASH_BLOCK_SIZE / NANDFLASH_PHYSICAL_PAGE_SIZE) == 1));
             
   /* If the last virtual page of the first or the second physical page
     is about to be read the virtual page needs to be enlarged
     by 8 bytes and swapping switched on due to the bad block marking */
   if(swap)
   {
      nfc_ptr->SWAP   = NFC_SWAP_ADDR1(0x100) | 
                        NFC_SWAP_ADDR2(0x100);
      nfc_ptr->SECSZ += 8;
   }
   else
   {
      nfc_ptr->SWAP   = NFC_SWAP_ADDR1(0x7FF) | 
                        NFC_SWAP_ADDR2(0x7FF);
   }
   
   nfc_ptr->RPT   = NFC_RPT_COUNT(0);
   
   nfc_ptr->CFG   = (NFC_CFG_ECCMODE(7)  
                  | NFC_CFG_IDCNT(5)   
                  | NFC_CFG_TIMEOUT(6) 
                  | NFC_CFG_PAGECNT(1)); 
                  
   nfc_ptr->RAI   = NFC_RAI_INC1(0);
   
   /* Clearing interrupts bits */
   nfc_ptr->ISR   = NFC_ISR_DONECLR
                  | NFC_ISR_DONEEN 
                  | NFC_ISR_IDLECLR
                  | NFC_ISR_IDLEEN;
   
   /* Sending START */
   nfc_ptr->CMD2  = NFC_CMD2_BYTE1(NANDFLASH_CMD_PAGE_READ_CYCLE1)
                  | NFC_CMD2_CODE(0x7EE0)
                  | NFC_CMD2_BUFNO(0)
                  | NFC_CMD2_BUSY_START;
                  
   for(i = 0;i<10;i++){
   }
   
   while(!(nfc_ptr->ISR &(NFC_ISR_IDLE | NFC_ISR_DONE ))) {
   }
   
   for(i=0;i<0x800;i++)
   {
      *(buffer)=nfc_ptr->SRAM_B0[i];
      buffer++;
   }
   
   return 0;
} /* Endbody */

/*FUNCTION*----------------------------------------------------------------
*
* Function Name    : bootloader_boot
* Returned Value   : void
* Comments         : Boot loader execution code
*                    
*
*END*----------------------------------------------------------------------*/
__declspec(section ".text")
void bootloader_boot(void)
{ /* Body */
   VNFC_STRUCT_PTR  nfc_ptr;
   void           (*boot)(void);
   uint_32        i=0, checksum =0;
   uint_32        page,page_size,block,block_size;
   IMAGE_HEADER   * p_img_hdr;
   uchar_ptr      boot_buf;
   uchar_ptr      s;
   IMAGE_INFO_PTR image_ptr;
   uint_32        block_number;
   uint_32_ptr    ram_addr = NULL;
   
   if(_autoboot_cmd == AUTOBOOT_RESET) {
      _bootstrap_reset();
   }
   
   nfc_ptr = bootstrap_get_nand_addr();
   
   boot_buf=(uchar_ptr)ram_addr;
   p_img_hdr=(IMAGE_HEADER *)(ram_addr);
   boot=(void (*)(void) )ram_addr;
   
   bootloader_read_page(nfc_ptr,IMAGE_TABLE_BLOCK_LOCATION,0,boot_buf);
   image_ptr = (IMAGE_INFO_PTR)boot_buf;
   
   while(image_ptr->IS_IMAGE == IMAGE_IN_TABLE_MASK) {
      if(_autoboot_cmd == AUTOBOOT_ENABLE){         
         if(image_ptr->BOOT_DEFAULT) {
            ram_addr = (pointer)image_ptr->ADDR;
            block_number = image_ptr->BLOCK;
            break;
         }
      }
      else if(_autoboot_cmd == AUTOBOOT_DISABLE) {
         if(image_ptr->INDEX == _image_index) {
            ram_addr = (pointer)image_ptr->ADDR;
            block_number = image_ptr->BLOCK;
            break;
         }
      }
      image_ptr++;
   }
   
   boot_buf=(uchar_ptr)ram_addr;
   p_img_hdr=(IMAGE_HEADER *)(ram_addr);
   boot=(void (*)(void) )ram_addr;
   
   /* Read boot bock at block_num, page 0 to get image data header */
   bootloader_read_page(nfc_ptr,block_number,0,boot_buf);
   
   page_size  = (p_img_hdr->LEN + sizeof(IMAGE_HEADER) + NANDFLASH_PHYSICAL_PAGE_SIZE) 
             / NANDFLASH_PHYSICAL_PAGE_SIZE;
             
   block_size = (page_size + (NANDFLASH_BLOCK_SIZE/NANDFLASH_PHYSICAL_PAGE_SIZE))
             /(NANDFLASH_BLOCK_SIZE/NANDFLASH_PHYSICAL_PAGE_SIZE);
             
   boot_buf = (uchar_ptr)(ram_addr) - sizeof(IMAGE_HEADER);
   
   p_img_hdr = (IMAGE_HEADER *)boot_buf;
   
   for(i = 0; i < page_size; i++) {
      block = i/(NANDFLASH_BLOCK_SIZE/NANDFLASH_PHYSICAL_PAGE_SIZE);
      page = i & 0xFF;
      bootloader_read_page(nfc_ptr,block_number+block,page,boot_buf);
      boot_buf += NANDFLASH_PHYSICAL_PAGE_SIZE;
   }
   
   /* Checksum */
   s=(uchar_ptr)ram_addr;
   checksum=0;
   
   for(i=0;i<p_img_hdr->LEN;i++)
   {
      checksum+=*s++;
   }
   
   if(checksum==p_img_hdr->CHECKSUM)
   {      
      (*boot)();
      return;
   }   
   return;
} /* Endbody */


/* EOF */