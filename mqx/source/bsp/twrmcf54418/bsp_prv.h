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
* $FileName: bsp_prv.h$
* $Version : 3.6.13.0$
* $Date    : Sep-10-2010$
*
* Comments:
*
*   This file contains the definitions of constants and structures
*   required for initialization of the card.
*   $Header:bsp_prv.h, 4, 3/15/2007 11:19:19 AM, Jim Gard$
*   $NoKeywords$
*
*END************************************************************************/

#ifndef _bsp_prv_h_
#define _bsp_prv_h_ 1

#ifdef __cplusplus
extern "C" {
#endif

/* NAND Flash info */
#define NANDFLASH_PHYSICAL_PAGE_SIZE      2048
#define NANDFLASH_SPARE_AREA_SIZE         64
#define NANDFLASH_BLOCK_SIZE              131072 /* 128kB */

/*
 * SDRAM initialization
 */
 
#define SDRAM_DDR1  0x0
#define SDRAM_DDR2  0x4

/* Defines for different CAS latency settings */
#define CASL_2      0x2
#define CASL_2_5    0x102
#define CASL_3      0x3
#define CASL_4      0x4
#define CASL_5      0x5
#define CASL_6      0x6
#define CASL_7      0x7

/* Define a structure used to pass info on the SDRAM into the init */
typedef struct {
    uint_32 memtype;        // type of memory (SDRAM_DDR1 and SDRAM_DDR2 are valid values) 
    uint_32 num_row_addr;   // number of row addresses for the sdram
    uint_32 num_col_addr;   // number of column addresses for the sdram
    uint_32 num_banks;      // number of banks in the memory (valid values are 4 and 8)
    uint_32 casl;           // CAS latency setting (use defines above for valid values)
    uint_32 trrd;           // ACTIVE a to ACTIVE b command delay (trrd) in ns
    uint_32 twtr;           // WRITE to READ delay (twtr) in ns
    uint_32 trtp;           // READ to PRECHARDGE delay in ns
    uint_32 twr;            // WRITE recovery time in ns
    uint_32 trp;            // PRECHARGE command period in ns
    uint_32 tmrd;           // LOAD MODE REGISTER command cycle time in ns
    uint_32 tfaw;           // 4-bank activate period in ns
    uint_32 tras_min;       // minimum row active time (ACTIVATE to PRE) in ns
    uint_32 tras_max;       // max row active time in ns
    uint_32 trc;            // ACTIVATE to ACTIVATE delay in ns
    uint_32 trfc;           // REFRESH command period in ns
    uint_32 trcd;           // ACTIVE to READ/WRITE delay in ns
    uint_32 trefi;          // REF to REF internal in ns (NOTE: this is normall spec's in us)
    uint_32 xard;           // self refresh exit time in clocks
    uint_32 tmod;           // MRS to ODT enable delay in ns (use SDCLK period x 2 for DDR1)    
        
} SDRAM_INFO;

/*
**  FUNCTION PROTOTYPES
*/
void mcf5441_init(void);

#if BSPCFG_ENABLE_CPP
extern void    __cpp_init(void);
#endif
//extern void    _ExitProcess(void); /* Codewarrior */

extern void    _bsp_enet_gpio_init(uint_32 fecnum, uint_32 flags);
extern void    _bsp_dspi_gpio_init(void);
extern void    _bsp_exit_handler(void);
extern void    _bsp_timer_isr(pointer);
extern uint_32 _bsp_uart_frequency(void);

extern void _bsp_spin_time(uint_32);    // Wait by spinning for N microseconds

/* I/O initialization controlled by initialization structures for each
** channel
*/

extern MCF54XX_UART_SERIAL_INIT_STRUCT  _bsp_uart0_init;
extern MCF54XX_UART_SERIAL_INIT_STRUCT  _bsp_uart2_init;
extern MCF54XX_UART_SERIAL_INIT_STRUCT  _bsp_uart4_init;
extern MCF54XX_UART_SERIAL_INIT_STRUCT  _bsp_uart5_init;
extern MCF54XX_UART_SERIAL_INIT_STRUCT  _bsp_uart6_init;

extern MCF54XX_I2C_INIT_STRUCT _bsp_i2c0_init;
extern MCF54XX_I2C_INIT_STRUCT _bsp_i2c5_init;

extern MCF5XXX_DSPI_INIT_STRUCT _bsp_dspi0_init;
extern MCF5XXX_DSPI_INIT_STRUCT _bsp_dspi1_init;

extern const PCCARDFLEXBUS_INIT_STRUCT  _bsp_cfcard_init;

extern NANDFLASH_INIT_STRUCT _bsp_nandflash_init;

extern void _bsp_flexbus_pccard_setup (const uint_32 base_address);
extern const ESDHC_INIT_STRUCT _bsp_esdhc0_init;

#ifdef __cplusplus
}
#endif

#endif
/* EOF */

