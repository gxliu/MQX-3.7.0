#ifndef _mcf532x_nfc_h_
#define _mcf532x_nfc_h_
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
* $FileName: mcf532x_nfc.h$
* $Version : 3.7.3.0$
* $Date    : Feb-23-2011$
*
* Comments:
*
*   This file contains defines and functions prototype for the mcf532x 
*   NAND Flash aController (NFC) low level driver.
*
*END************************************************************************/


#define MAX_WAIT_COMMAND	                   0x00100000


/*----------------------------------------------------------------------*/
/*
**                    Structure Definitions
*/
/*
** MCF532X_NFC_STRUCT                                                                   
** This structure defines NFC registers
*/
typedef struct mcf532x_nfc_struct
{
   /* Address and data of Nand Flash */
   uint_8   ADD;  
   uint_8   nfc_reserved0[0x80007];
   /* Address Latch Enable */
   uint_8   ALE;   
   uint_8   nfc_reserved1[0x7];
   /* Nand Flash Command */
   uint_8   CMD;  
} MCF532X_NFC_STRUCT, _PTR_ MCF532X_NFC_STRUCT_PTR;
typedef volatile struct mcf532x_nfc_struct _PTR_ VMCF532X_NFC_STRUCT_PTR;

/*----------------------------------------------------------------------*/
/*
**                     FUNCTION PROTOTYPES
*/
#ifdef __cplusplus
extern "C" {
#endif

pointer _bsp_get_nfc_address();

extern uint_32 mcf532x_nfc_init( IO_NANDFLASH_STRUCT_PTR );

extern void    mcf532x_nfc_deinit( IO_NANDFLASH_STRUCT_PTR );

extern uint_32 mcf532x_nfc_erase_flash( IO_NANDFLASH_STRUCT_PTR );

extern uint_32 mcf532x_nfc_erase_block( IO_NANDFLASH_STRUCT_PTR, uint_32, boolean );

extern uint_32 mcf532x_nfc_read_page( IO_NANDFLASH_STRUCT_PTR, uchar_ptr, 
    uint_32, uint_32 );

extern uint_32 mcf532x_nfc_write_page( IO_NANDFLASH_STRUCT_PTR, uchar_ptr, 
    uint_32, uint_32 );
    
extern uint_32 mcf532x_nfc_reset( IO_NANDFLASH_STRUCT_PTR );

extern uint_32 mcf532x_nfc_check_block( IO_NANDFLASH_STRUCT_PTR, uint_32 );
    
extern uint_32 mcf532x_nfc_mark_block_as_bad( IO_NANDFLASH_STRUCT_PTR, uint_32);
    
extern uint_32 mcf532x_nfc_read_ID( IO_NANDFLASH_STRUCT_PTR, uchar_ptr, 
    _mem_size );
    
extern _mqx_int mcf532x_nfc_ioctl(IO_NANDFLASH_STRUCT_PTR, _mqx_uint, pointer);

#ifdef __cplusplus
}
#endif

#endif
/* EOF */
