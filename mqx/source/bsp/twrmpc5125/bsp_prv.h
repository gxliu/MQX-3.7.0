#ifndef _bsp_prv_h
#define _bsp_prv_h 1
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
* $FileName:bsp_prv.h$
* $Version : 3.7.4.0$
* $Date    : Feb-7-2011$
*
* Comments:
* 
*    This file contains the definitions of constants and structures
*    required for initialization of the card.
*
*END***********************************************************************/

/*
**  FUNCTION PROTOTYPES
*/                     

#ifdef __cplusplus
extern "C" {
#endif

/* NAND Flash info */
#define NANDFLASH_PHYSICAL_PAGE_SIZE      2048
#define NANDFLASH_SPARE_AREA_SIZE         60
#define NANDFLASH_BLOCK_SIZE              524288
#define NANDFLASH_BOOT_PAGE_SIZE          0x3E4
#define NANDFLASH_BOOT_ECCBYTES           0x3C

extern void    bootstrap_ddr_to_nand(void);
extern void    __init_cpp(void);    // Codewarrior C++ constructors

extern void    _bsp_exit_handler(void);

extern uint_64 _bsp_elapsed_time(void); // Elapsed time since boot
extern void    _bsp_spin_time(uint_32); // Wait by spinning for N microseconds

/*
** Clock frequencies
*/
extern uint_32 _bsp_ipb_frequency(void);


/* I/O initialization controlled by initialization structures for each
** channel
*/
extern const MPC5125_SERIAL_INIT_STRUCT _bsp_psc0_init;
extern const MPC5125_SERIAL_INIT_STRUCT _bsp_psc1_init;
extern const MPC5125_SERIAL_INIT_STRUCT _bsp_psc2_init;
extern const MPC5125_SERIAL_INIT_STRUCT _bsp_psc3_init;
extern const MPC5125_SERIAL_INIT_STRUCT _bsp_psc4_init;
extern const MPC5125_SERIAL_INIT_STRUCT _bsp_psc5_init;
extern const MPC5125_SERIAL_INIT_STRUCT _bsp_psc6_init;
extern const MPC5125_SERIAL_INIT_STRUCT _bsp_psc7_init;
extern const MPC5125_SERIAL_INIT_STRUCT _bsp_psc8_init;
extern const MPC5125_SERIAL_INIT_STRUCT _bsp_psc9_init;
extern const MPC512X_I2C_INIT_STRUCT _bsp_i2c0_init;

extern const MPC512X_SPI_INIT_STRUCT _bsp_spi0_init;
extern const MPC512X_SPI_INIT_STRUCT _bsp_spi1_init;
extern const MPC512X_SPI_INIT_STRUCT _bsp_spi2_init;
extern const MPC512X_SPI_INIT_STRUCT _bsp_spi3_init;
extern const MPC512X_SPI_INIT_STRUCT _bsp_spi4_init;
extern const MPC512X_SPI_INIT_STRUCT _bsp_spi5_init;
extern const MPC512X_SPI_INIT_STRUCT _bsp_spi6_init;
extern const MPC512X_SPI_INIT_STRUCT _bsp_spi7_init;
extern const MPC512X_SPI_INIT_STRUCT _bsp_spi8_init;
extern const MPC512X_SPI_INIT_STRUCT _bsp_spi9_init;
extern const MPC5125_SDHC_INIT_STRUCT _bsp_sdhc_init;
extern const MPC5125_PCCARDLPC_INIT_STRUCT  _bsp_cfcard_init;
extern NANDFLASH_INIT_STRUCT _bsp_nandflash_init;

#ifdef __cplusplus
}
#endif

#endif
/* EOF */
