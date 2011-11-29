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
* $FileName: mcf5227.h$
* $Version : 3.5.40.0$
* $Date    : Feb-24-2010$
*
* Comments:
*
*   This file contains the type definitions for the mcf5227x processors.
*
*END************************************************************************/

#ifndef __mcf5227_h__
#define __mcf5227_h__

#define __mcf5227_h__version "$Version:3.5.40.0$"
#define __mcf5227_h__date    "$Date:Feb-24-2010$"

#ifndef __ASM__

/* Include registers for modules common to all Coldfire processors */
#include <mcf5xxx_usbotg.h>     /* USBOTG */
#include <mcf52xx_uart.h>       /* UART */
#include <mcf52xx_fcan.h>       /* Flex CAN */
#include <mcf5xxx_dspi.h>       /* DSPI */
#include <mcf52xx_i2c.h>        /* I2C */
#include <mcf52xx_rtc.h>        /* RTC */

#include <mcf5xxx_sdramc.h>
#include <mcf5xxx_fb.h>
#include <mcf5xxx_pit.h>

#endif // __ASM__

#ifdef __cplusplus
extern "C" {
#endif

/*------------------------------------------------------------------------*/
/*
**                    CONSTANT DEFINITIONS
*/

/* Indicate processor type */
#define PSP_MCF5227                         1

#define PSP_HAS_DSP                         1
#define PSP_HAS_EMAC                        1

#define PSP_ACR_CNT                         2

/*
** Cache and MMU definition values
*/
#define PSP_HAS_MMU                         0
#define PSP_HAS_CODE_CACHE                  1
#define PSP_HAS_DATA_CACHE                  1

#define PSP_CACHE_SPLIT                     0

#define PSP_CACHE_HAS_BUS_SNOOPING          FALSE
#define PSP_CACHE_LINE_SIZE                 (0x10)

#define PSP_CACHE_SIZE                      (8 * 1024)

#ifdef __CODEWARRIOR__
#define NEED_MODF
#endif

/*
** Define padding needed to make the STOREBLOCK_STRUCT align properly
** to cache line size (see mem_prv.h)
*/
#define PSP_MEM_STOREBLOCK_ALIGNMENT        (2) /* padding in _mqx_uints */

#ifndef __ASM__

#define MCF5227_NUM_ACRS                    (2)

/* Error codes from mcf5227_mmu_add_region */
#define MCF5227_OUT_OF_ACRS                 (0x00100000)

/* Do you want to verify kernel data can be read and written correctly */
#define PSP_KERNEL_DATA_VERIFY_ENABLE       ((uint_32)__KERNEL_DATA_VERIFY_ENABLE)

#if PSP_HAS_DATA_CACHE
#define PSP_DCACHE_SIZE                     ((PSP_CACHE_SIZE)/2)
#define PSP_ICACHE_SIZE                     ((PSP_CACHE_SIZE)/2)
#define PSP_NUM_CACHE_LINES                 (PSP_DCACHE_SIZE/PSP_CACHE_LINE_SIZE)
#define PSP_DCACHE_NUM_SETS                 (PSP_DCACHE_SIZE / (PSP_DCACHE_NUM_WAYS * PSP_CACHE_LINE_SIZE))
#define PSP_DCACHE_NUM_WAYS                 (4)
#else
#define PSP_DCACHE_SIZE                     0
#define PSP_ICACHE_SIZE                     PSP_CACHE_SIZE
#define PSP_NUM_CACHE_LINES                 (PSP_ICACHE_SIZE/PSP_CACHE_LINE_SIZE)
#define PSP_DCACHE_NUM_SETS                 0
#define PSP_DCACHE_NUM_WAYS                 0
#endif

#define _PSP_BYTES_TO_LINES(b)              (((b)+(PSP_CACHE_LINE_SIZE-1)) / PSP_CACHE_LINE_SIZE)
#define _PSP_MASK_CACHE_ADDR(p)             (pointer)(((uint_32)p) & ~(PSP_CACHE_LINE_SIZE - 1))


#if PSP_HAS_DATA_CACHE || PSP_HAS_CODE_CACHE
    #define _CACHE_ENABLE(n)                    _mcf5227_cache_enable(n)
    #define _CACHE_DISABLE()                    _mcf5227_cache_disable()
#else
    #define _CACHE_ENABLE(n)                 
    #define _CACHE_DISABLE()
#endif

/*
** Standard cache macros
*/
#define _DCACHE_FLUSH()                     /* Data cache is writethrough */
#define _DCACHE_FLUSH_LINE(p)               /* Data cache is writethrough */
#define _DCACHE_FLUSH_MBYTES(p, m)          /* Data cache is writethrough */

#if PSP_HAS_DATA_CACHE
    #define _DCACHE_INVALIDATE()                _mcf5227_dcache_invalidate()
    #define _DCACHE_INVALIDATE_LINE(p)          _DCACHE_INVALIDATE_MBYTES(p, 1)
    #define _DCACHE_INVALIDATE_MBYTES(p, m)     _dcache_flush(_PSP_MASK_CACHE_ADDR(p), _PSP_BYTES_TO_LINES(m), PSP_CACHE_LINE_SIZE)
#else
    #define _DCACHE_INVALIDATE()
    #define _DCACHE_INVALIDATE_LINE(p)
    #define _DCACHE_INVALIDATE_MBYTES(p, m)
#endif


#if PSP_HAS_CODE_CACHE
    #define _ICACHE_INVALIDATE()                _mcf5227_icache_invalidate()
    #define _ICACHE_INVALIDATE_LINE(p)          _ICACHE_INVALIDATE_MBYTES(p, 1)
    #define _ICACHE_INVALIDATE_MBYTES(p, m)     _icache_invalidate_mlines(p, _PSP_BYTES_TO_LINES(m), PSP_CACHE_LINE_SIZE)
#else
    #define _ICACHE_INVALIDATE()
    #define _ICACHE_INVALIDATE_LINE(p)
    #define _ICACHE_INVALIDATE_MBYTES(p, m)
#endif

#if PSP_HAS_CODE_CACHE || PSP_HAS_DATA_CACHE

#define _MMU_DISABLE()      _mmu_disable()
#define _MMU_ENABLE()       _mmu_enable()

#else

#define _MMU_DISABLE()
#define _MMU_ENABLE()

#endif

#define MCF5227_CACHE_CACHEABLE_WRITETHROUGH    0       /* Unbuffered */
#define MCF5227_CACHE_CACHEABLE_COPYBACK        1       /* Write buffered */
#define MCF5227_CACHE_NONCACHEABLE_UNBUFFERED   2
#define MCF5227_CACHE_NONCACHEABLE_BUFFERED     3

/*
** Configuration information
*/
#define MCF5227_NUM_TIMERS                  (2) /* PIT */
#define MCF5227_NUM_UARTS                   (3)
#define MCF5227_NUM_DMAS                    (16)
#define MCF5227_NUM_DMA_TIMERS              (4)
#define MCF5227_NUM_FB_CS                   (6) /* FlexBus chip selects */

/*
** Cache control register bits
*/
#define MCF5227_CACR_CENB                       (1 << 31)
#define MCF5227_CACR_CPDI                       (1 << 28) // Disable CPUSHL
#define MCF5227_CACR_CFRZ                       (1 << 27) // Cache Freeze
#define MCF5227_CACR_CINV                       (1 << 24) // Cache Invalidate
#define MCF5227_CACR_DISI                       (1 << 23) // Disable Instruction Cache
#define MCF5227_CACR_DISD                       (1 << 22) // Disable Data Cache
#define MCF5227_CACR_INVI                       (1 << 21) // Invalidate instr cache only
#define MCF5227_CACR_INVD                       (1 << 20) // Invalidate data cache only
#define MCF5227_CACR_CEIB                       (1 << 10) // Enable noncacheable instruction bursting
#define MCF5227_CACR_DCM                        (1 << 9) // Default cache mode
#define MCF5227_CACR_DBWE                       (1 << 8) // Write Buffered
#define MCF5227_CACR_DWP                        (1 << 5) // Default Write Protect
#define MCF5227_CACR_EUSP                       (1 << 4) // Enable user stack pointer
#define MCF5227_CACR_LINE_FILL_00               0
#define MCF5227_CACR_LINE_FILL_01               1
#define MCF5227_CACR_LINE_FILL_10               2
#define MCF5227_CACR_LINE_FILL_11               3

// These bits automatically clear after the operation
#define CACR_AUTO_CLEAR_BITS    (MCF5227_CACR_CINV | MCF5227_CACR_INVD | MCF5227_CACR_INVI)

/*
** Access control register bits
*/
#define MCF5227_ACR_BASE_ADDR                   (0xFF000000)
#define MCF5227_ACR_BASE_ADDR_MASK              (0x00FF0000)
#define MCF5227_ACR_ENABLE                      (0x00008000)
#define MCF5227_ACR_IGNORE_FC                   (0x00004000)
#define MCF5227_ACR_USER_ACCESS_FC              (0x00000000)
#define MCF5227_ACR_SUPER_ACCESS_FC             (0x00002000)
#define MCF5227_ACR_NONCACHEABLE_MODE           (0x00000040)
#define MCF5227_ACR_CACHEABLE_MODE              (0x00000000)
#define MCF5227_ACR_BUFFER_WRITE_ENABLE         (0x00000020)
#define MCF5227_ACR_WRITE_PROTECT               (0x00000004)

/*
** Interrupt definitions
*/
#define MCF5227_ICTRL_MASKALL   1
#define MCF5227_ICTRL0_BASEx    64
#define MCF5227_ICTRL1_BASEx    128

/*
** Interrupt vector table
*/
typedef enum mcf5227_interrupt_table_index {
   MCF5227_boot_stack_pointer,
   MCF5227_boot_program_counter,
   MCF5227_EXC_ACCESS_ERROR,
   MCF5227_EXC_ADDRESS_ERROR,
   MCF5227_EXC_ILLEGAL_INSTRUCTION,
   MCF5227_EXC_DIVIDE_BY_ZERO,
   MCF5227_EXC_rsvd6,
   MCF5227_EXC_rsvd7,
   MCF5227_EXC_PRIVILEGE_VIOLATION,
   MCF5227_EXC_NEXT_TRACE,
   MCF5227_EXC_UNIMPLEMENTED_LINE_A_OPCODE,
   MCF5227_EXC_UNIMPLEMENTED_LINE_F_OPCODE,
   MCF5227_EXC_DEBUG,
   MCF5227_EXC_rsvd13,
   MCF5227_EXC_FORMAT_ERROR,
   MCF5227_EXC_rsvd15,
   MCF5227_EXC_rsvd16,
   MCF5227_EXC_rsvd17,
   MCF5227_EXC_rsvd18,
   MCF5227_EXC_rsvd19,
   MCF5227_EXC_rsvd20,
   MCF5227_EXC_rsvd21,
   MCF5227_EXC_rsvd22,
   MCF5227_EXC_rsvd23,
   MCF5227_EXC_SPURIOUS,
   MCF5227_EXC_rsvd25,
   MCF5227_EXC_rsvd26,
   MCF5227_EXC_rsvd27,
   MCF5227_EXC_rsvd28,
   MCF5227_EXC_rsvd29,
   MCF5227_EXC_rsvd30,
   MCF5227_EXC_rsvd31,
   MCF5227_EXC_TRAP0,
   MCF5227_EXC_TRAP1,
   MCF5227_EXC_TRAP2,
   MCF5227_EXC_TRAP3,
   MCF5227_EXC_TRAP4,
   MCF5227_EXC_TRAP5,
   MCF5227_EXC_TRAP6,
   MCF5227_EXC_TRAP7,
   MCF5227_EXC_TRAP8,
   MCF5227_EXC_TRAP9,
   MCF5227_EXC_TRAP10,
   MCF5227_EXC_TRAP11,
   MCF5227_EXC_TRAP12,
   MCF5227_EXC_TRAP13,
   MCF5227_EXC_TRAP14,
   MCF5227_EXC_TRAP15,
   MCF5227_EXC_rsvd48,
   MCF5227_EXC_rsvd49,
   MCF5227_EXC_rsvd50,
   MCF5227_EXC_rsvd51,
   MCF5227_EXC_rsvd52,
   MCF5227_EXC_rsvd53,
   MCF5227_EXC_rsvd54,
   MCF5227_EXC_rsvd55,
   MCF5227_EXC_rsvd56,
   MCF5227_EXC_rsvd57,
   MCF5227_EXC_rsvd58,
   MCF5227_EXC_rsvd59,
   MCF5227_EXC_rsvd60,
   MCF5227_EXC_rsvd61,
   MCF5227_EXC_rsvd62,
   MCF5227_EXC_rsvd63,
   MCF5227_INT_FIRST_EXTERNAL,
   
   /* Interrupt Controller 0 */
   MCF5227_INT0_EPORT0_EPF1,     //  1 Edge port flag 1
   MCF5227_INT0_rsvd2,
   MCF5227_INT0_rsvd3,
   MCF5227_INT0_EPORT0_EPF4,     //  4 Edge port flag 4
   MCF5227_INT0_rsvd5,
   MCF5227_INT0_rsvd6,
   MCF5227_INT0_EPORT0_EPF7,     //  7 Edge port flag 7
   MCF5227_INT0_DMA0,            //  8 DMA Channel 0 transfer complete
   MCF5227_INT0_DMA1,            //  9 DMA Channel 1 transfer complete
   MCF5227_INT0_DMA2,            // 10 DMA Channel 2 transfer complete
   MCF5227_INT0_DMA3,            // 11 DMA Channel 3 transfer complete
   MCF5227_INT0_DMA4,            // 12 DMA Channel 4 transfer complete
   MCF5227_INT0_DMA5,            // 13 DMA Channel 5 transfer complete
   MCF5227_INT0_DMA6,            // 14 DMA Channel 6 transfer complete
   MCF5227_INT0_DMA7,            // 15 DMA Channel 7 transfer complete
   MCF5227_INT0_DMA8,            // 16 DMA Channel 8 transfer complete
   MCF5227_INT0_DMA9,            // 17 DMA Channel 9 transfer complete
   MCF5227_INT0_DMA10,           // 18 DMA Channel 10 transfer complete
   MCF5227_INT0_DMA11,           // 19 DMA Channel 11 transfer complete
   MCF5227_INT0_DMA12,           // 20 DMA Channel 12 transfer complete
   MCF5227_INT0_DMA13,           // 21 DMA Channel 13 transfer complete
   MCF5227_INT0_DMA14,           // 22 DMA Channel 14 transfer complete
   MCF5227_INT0_DMA15,           // 23 DMA Channel 15 transfer complete
   MCF5227_INT0_DMAERR,          // 24 DMA error interrupt
   MCF5227_INT0_SCM_CWIC,        // 25 Core watchdog timeout   
   MCF5227_INT0_UART0,           // 26 UART0 interrupt
   MCF5227_INT0_UART1,           // 27 UART1 interrupt
   MCF5227_INT0_UART2,           // 28 UART2 interrupt
   MCF5227_INT0_rsvd29,         // 29 not used
   MCF5227_INT0_I2C0,            // 30 I2C interrupt
   MCF5227_INT0_DSPI,            // 31 DSPI all interrupts
   MCF5227_INT0_DTIM0,           // 32 TMR0 interrupt
   MCF5227_INT0_DTIM1,           // 33 TMR1 interrupt
   MCF5227_INT0_DTIM2,           // 34 TMR2 interrupt
   MCF5227_INT0_DTIM3,           // 35 TMR3 interrupt
   MCF5227_INT0_rsvd36,         // 36 not used
   MCF5227_INT0_rsvd37,         // 37 not used
   MCF5227_INT0_rsvd38,         // 38 not used
   MCF5227_INT0_rsvd39,         // 39 not used
   MCF5227_INT0_rsvd40,         // 40 not used
   MCF5227_INT0_rsvd41,         // 41 not used
   MCF5227_INT0_rsvd42,         // 42 not used
   MCF5227_INT0_rsvd43,         // 43 not used
   MCF5227_INT0_rsvd44,         // 44 not used
   MCF5227_INT0_rsvd45,         // 45 not used
   MCF5227_INT0_rsvd46,         // 46 not used
   MCF5227_INT0_rsvd47,         // 47 not used
   MCF5227_INT0_rsvd48,         // 48 not used
   MCF5227_INT0_rsvd49,         // 49 not used
   MCF5227_INT0_rsvd50,         // 50 not used
   MCF5227_INT0_rsvd51,         // 51 not used
   MCF5227_INT0_rsvd52,         // 52 not used
   MCF5227_INT0_rsvd53,         // 53 not used
   MCF5227_INT0_rsvd54,         // 54 not used
   MCF5227_INT0_rsvd55,         // 55 not used
   MCF5227_INT0_rsvd56,         // 56 not used
   MCF5227_INT0_rsvd57,         // 57 not used
   MCF5227_INT0_rsvd58,         // 58 not used
   MCF5227_INT0_rsvd59,         // 59 not used
   MCF5227_INT0_rsvd60,         // 60 not used
   MCF5227_INT0_rsvd61,         // 61 not used
   MCF5227_INT0_SCM_CFEI,        // 62 Core bus error interrupt
   MCF5227_INT0_RTC,                // 63 RTC interrupt 
   /* Interrupt Controller 1 */
   MCF5227_INT1_FLEXCAN_BUFS,   //  0 FlexCAN0 all MBs interrupt
   MCF5227_INT1_FLEXCAN_BOFF_INT,//  1 FlexCAN0 bus-off
   MCF5227_INT1_rsvd2,          //  2 not used
   MCF5227_INT1_FLEXCAN_ERR_INT,    //  3 FlexCAN0 error
   MCF5227_INT1_FLEXCAN_BUF0,   //  4 FlexCAN0 MB 0
   MCF5227_INT1_FLEXCAN_BUF1,   //  5 FlexCAN0 MB 1
   MCF5227_INT1_FLEXCAN_BUF2,   //  6 FlexCAN0 MB 2
   MCF5227_INT1_FLEXCAN_BUF3,   //  7 FlexCAN0 MB 3
   MCF5227_INT1_FLEXCAN_BUF4,   //  8 FlexCAN0 MB 4
   MCF5227_INT1_FLEXCAN_BUF5,   //  9 FlexCAN0 MB 5
   MCF5227_INT1_FLEXCAN_BUF6,   // 10 FlexCAN0 MB 6
   MCF5227_INT1_FLEXCAN_BUF7,   // 11 FlexCAN0 MB 7
   MCF5227_INT1_FLEXCAN_BUF8,   // 12 FlexCAN0 MB 8
   MCF5227_INT1_FLEXCAN_BUF9,   // 13 FlexCAN0 MB 9
   MCF5227_INT1_FLEXCAN_BUF10,  // 14 FlexCAN0 MB 10
   MCF5227_INT1_FLEXCAN_BUF11,  // 15 FlexCAN0 MB 11
   MCF5227_INT1_FLEXCAN_BUF12,  // 16 FlexCAN0 MB 12
   MCF5227_INT1_FLEXCAN_BUF13,  // 17 FlexCAN0 MB 13
   MCF5227_INT1_FLEXCAN_BUF14,  // 18 FlexCAN0 MB 14
   MCF5227_INT1_FLEXCAN_BUF15,  // 19 FlexCAN0 MB 15
   MCF5227_INT1_rsvd20,         // 20 not used
   MCF5227_INT1_rsvd21,         // 21 not used
   MCF5227_INT1_rsvd22,         // 22 not used
   MCF5227_INT1_rsvd23,         // 23 not used
   MCF5227_INT1_rsvd24,         // 24 not used
   MCF5227_INT1_rsvd25,         // 25 not used
   MCF5227_INT1_rsvd26,         // 26 not used
   MCF5227_INT1_rsvd27,         // 27 not used
   MCF5227_INT1_rsvd28,         // 28 not used
   MCF5227_INT1_rsvd29,         // 29 not used
   MCF5227_INT1_rsvd30,         // 30 not used
   MCF5227_INT1_rsvd31,         // 31 not used
   MCF5227_INT1_rsvd32,         // 32 not used
   MCF5227_INT1_rsvd33,         // 33 not used
   MCF5227_INT1_rsvd34,         // 34 not used
   MCF5227_INT1_rsvd35,         // 35 not used
   MCF5227_INT1_rsvd36,         // 36 not used
   MCF5227_INT1_rsvd37,         // 37 not used
   MCF5227_INT1_rsvd38,         // 38 not used
   MCF5227_INT1_rsvd39,         // 39 not used
   MCF5227_INT1_rsvd40,         // 40 not used
   MCF5227_INT1_rsvd41,         // 41 not used
   MCF5227_INT1_rsvd42,         // 42 not used
   MCF5227_INT1_PIT0,           // 43 PIT0 PIF PIT interrupt flag
   MCF5227_INT1_PIT1,           // 44 PIT1 PIF PIT interrupt flag
   MCF5227_INT1_rsvd45,         // 45 not used
   MCF5227_INT1_rsvd46,         // 46 not used
   MCF5227_INT1_USB,            // 47 USB OTG STS interrupt
   MCF5227_INT1_rsvd48,         // 48 not used
   MCF5227_INT1_SSI,            // 49 SSI interrupt
   MCF5227_INT1_PWM,            // 50 Pulse width modulation interrupt
   MCF5227_INT1_LCDC,           // 51 LCD controller interrupt
   MCF5227_INT1_rsvd52,         // 52 not used
   MCF5227_INT1_CCM,            // 53 USB UOCSR status interrupt
   MCF5227_INT1_DSPI_EOQF,      // 54 DSPI end of queue interrupt
   MCF5227_INT1_DSPI_TFFF,      // 55 DSPI transmit fifo fill interrupt
   MCF5227_INT1_DSPI_TCF,       // 56 DSPI transfer complete interrupt
   MCF5227_INT1_DSPI_TFUF,      // 57 DSPI transmit fifo underflow interrupt
   MCF5227_INT1_DSPI_RFDF,      // 58 DSPI receive fifo not empty interrupt
   MCF5227_INT1_DSPI_RFOF,      // 59 DSPI receive fifo overflow interrupt
   MCF5227_INT1_DSPI_RFOF_TFUF, // 60 DSPI TFUF or RFOF
   MCF5227_INT1_ADC_TOUCH,      // 61 ADC and Touchscreen controller interrupt
   MCF5227_INT1_PLL,            // 62 PLL loss of lock interrupt
   MCF5227_INT1_rsvd63          // 63 not used
} MCF5227_INTERRUPT_TABLE_INDEX;//, PSP_INTERRUPT_TABLE_INDEX;

/*
** MCF5227_IACK_STRUCT
** Interrupt acknowledgements
*/
typedef struct mcf5227_iack_struct
{
   uchar L1IACK;                // Level 1 Interrupt Acknowledge Register
   uchar filler2[3];
   uchar L2IACK;                // Level 2 Interrupt Acknowledge Register
   uchar filler3[3];
   uchar L3IACK;                // Level 3 Interrupt Acknowledge Register
   uchar filler4[3];
   uchar L4IACK;                // Level 4 Interrupt Acknowledge Register
   uchar filler5[3];
   uchar L5IACK;                // Level 5 Interrupt Acknowledge Register
   uchar filler6[3];
   uchar L6IACK;                // Level 6 Interrupt Acknowledge Register
   uchar filler7[3];
   uchar L7IACK;                // Level 7 Interrupt Acknowledge Register
   uchar filler8[3];

} MCF5227_IACK_STRUCT, _PTR_ MCF5227_IACK_STRUCT_PTR;
typedef volatile struct mcf5227_iack_struct _PTR_ VMCF5227_IACK_STRUCT_PTR;

/*
** MCF5227_ICTRL_STRUCT
** Interrupt controller
*/
typedef struct mcf5227_ictrl_struct
{
   uint_32  IPRH;               // Interrupt Pending Register High
   uint_32  IPRL;               // Interrupt Pending Register Low
   uint_32  IMRH;               // Interrupt Mask Register High
   uint_32  IMRL;               // Interrupt Mask Register Low
   uint_32  INTFRCH;            // Interrupt Force Register High
   uint_32  INTFRCL;            // Interrupt Force Register Low
   uchar    filler1[2];
   uint_16  ICONFIG;            // Interrupt Configuration Register
   uchar    SIMR;               // Set Interrupt Mask
   uchar    CIMR;               // Clear Interrupt Mask
   uchar    CLMASK;             // Current Level Mask
   uchar    SLMASK;             // Saved Level Mask
   uchar    filler2[32];
   uchar    ICR[64];            // Interrupt Control Registers, 1-63
   uchar    filler3[96];
   uchar    SWIACK;             // Software Interrupt Acknowledge Register
   MCF5227_IACK_STRUCT IACK;        // Level Interrupt Acknowledge Registers
   uchar        filler4[0xc000 - (0x80e1 + sizeof(MCF5227_IACK_STRUCT))];
} MCF5227_ICTRL_STRUCT, _PTR_ MCF5227_ICTRL_STRUCT_PTR;
typedef volatile struct mcf5227_ictrl_struct _PTR_ VMCF5227_ICTRL_STRUCT_PTR;

#define PSP_GET_ICTRL0_BASE()   \
   (&((VMCF5227_STRUCT_PTR)_PSP_GET_MBAR())->ICTRL[0])
#define PSP_GET_ICTRL1_BASE()   \
   (&((VMCF5227_STRUCT_PTR)_PSP_GET_MBAR())->ICTRL[1])

/*------------------------------------------------------------------------*/
/*
** SCM System control module
*/

/* Bit definitions and macros for RAMBAR */
#define MCF5227_SCM_RAMBAR_BA(x)                ((x)&0xFFFE0000)
#define MCF5227_SCM_RAMBAR_BDE                  (0x00000200)

/* Bit definitions and macros for MPR */
#define MCF5227_SCM_MPR_MPR(x)                  (((x)&0x0F))

/* Bit definitions and macros for WCR */
#define MCF5227_SCM_WCR_CWE                    (0x80)
#define MCF5227_SCM_WCR_LPMD_RUN               (0 << 4)
#define MCF5227_SCM_WCR_LPMD_DOZE              (1 << 4)
#define MCF5227_SCM_WCR_LPMD_WAIT              (2 << 4)
#define MCF5227_SCM_WCR_LPMD_STOP              (3 << 4)
#define MCF5227_SCM_WCR_LPMD_MASK              (3 << 4)
#define MCF5227_SCM_WCR_PRIV_MASK              (7)
#define MCF5227_SCM_WCR_PRIV                   ((x) & MCF5227_SCM_CWCR_PRIV_MASK)

/* Bit definitions and macros for CWCR */
#define MCF5227_SCM_CWCR_CWE                    (0x80)
#define MCF5227_SCM_CWCR_CWRI                   (0x40)
#define MCF5227_SCM_CWCR_CWT(x)                 (((x)&0x03)<<3)
#define MCF5227_SCM_CWCR_CWTA                   (0x04)
#define MCF5227_SCM_CWCR_CWTAVAL                (0x02)
#define MCF5227_SCM_CWCR_CWTIC                  (0x01)

/* Bit definitions and macros for WCR */
#define MCF5227_SCM_WCR_ENBSTOP                 (0x80
#define MCF5227_SCM_WCR_LPMD                    (0x30)
#define MCF5227_SCM_WCR_PRILVL(x)               (((x)&0x07)<<0)

/* Bit definitions and macros for CWSR */
#define MCF5227_SCM_CWSR_SEQ1                   (0x55)
#define MCF5227_SCM_CWSR_SEQ2                   (0xAA)


/*------------------------------------------------------------------------*/
/*
** DMA registers
*/

/* Bit definitions and macros for MCF5227_DMA_SAR */
#define MCF5227_DMA_SAR_SAR(x)                   (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF5227_DMA_DAR */
#define MCF5227_DMA_DAR_DAR(x)                   (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF5227_DMA_DTMR */
#define MCF5227_DMA_DSR_DONE                     (0x1)
#define MCF5227_DMA_DSR_BSY                      (0x2)
#define MCF5227_DMA_DSR_REQ                      (0x4)
#define MCF5227_DMA_DSR_BED                      (0x10)
#define MCF5227_DMA_DSR_BES                      (0x20)
#define MCF5227_DMA_DSR_CE                       (0x40)

/* Bit definitions and macros for MCF5227_DMA_BCR */
#define MCF5227_DMA_BCR_BCR(x)                   (((x)&0xFFFFFF)<<0)
#define MCF5227_DMA_BCR_DSR(x)                   (((x)&0xFF)<<0x18)

/* Bit definitions and macros for MCF5227_DMA_DCR */
#define MCF5227_DMA_DCR_LCH2(x)                  (((x)&0x3)<<0)
#define MCF5227_DMA_DCR_LCH2_CH0                 (0)
#define MCF5227_DMA_DCR_LCH2_CH1                 (0x1)
#define MCF5227_DMA_DCR_LCH2_CH2                 (0x2)
#define MCF5227_DMA_DCR_LCH2_CH3                 (0x3)
#define MCF5227_DMA_DCR_LCH1(x)                  (((x)&0x3)<<0x2)
#define MCF5227_DMA_DCR_LCH1_CH0                 (0)
#define MCF5227_DMA_DCR_LCH1_CH1                 (0x1)
#define MCF5227_DMA_DCR_LCH1_CH2                 (0x2)
#define MCF5227_DMA_DCR_LCH1_CH3                 (0x3)
#define MCF5227_DMA_DCR_LINKCC(x)                (((x)&0x3)<<0x4)
#define MCF5227_DMA_DCR_D_REQ                    (0x80)
#define MCF5227_DMA_DCR_DMOD(x)                  (((x)&0xF)<<0x8)
#define MCF5227_DMA_DCR_DMOD_DIS                 (0)
#define MCF5227_DMA_DCR_DMOD_16                  (0x1)
#define MCF5227_DMA_DCR_DMOD_32                  (0x2)
#define MCF5227_DMA_DCR_DMOD_64                  (0x3)
#define MCF5227_DMA_DCR_DMOD_128                 (0x4)
#define MCF5227_DMA_DCR_DMOD_256                 (0x5)
#define MCF5227_DMA_DCR_DMOD_512                 (0x6)
#define MCF5227_DMA_DCR_DMOD_1K                  (0x7)
#define MCF5227_DMA_DCR_DMOD_2K                  (0x8)
#define MCF5227_DMA_DCR_DMOD_4K                  (0x9)
#define MCF5227_DMA_DCR_DMOD_8K                  (0xA)
#define MCF5227_DMA_DCR_DMOD_16K                 (0xB)
#define MCF5227_DMA_DCR_DMOD_32K                 (0xC)
#define MCF5227_DMA_DCR_DMOD_64K                 (0xD)
#define MCF5227_DMA_DCR_DMOD_128K                (0xE)
#define MCF5227_DMA_DCR_DMOD_256K                (0xF)
#define MCF5227_DMA_DCR_SMOD(x)                  (((x)&0xF)<<0xC)
#define MCF5227_DMA_DCR_SMOD_DIS                 (0)
#define MCF5227_DMA_DCR_SMOD_16                  (0x1)
#define MCF5227_DMA_DCR_SMOD_32                  (0x2)
#define MCF5227_DMA_DCR_SMOD_64                  (0x3)
#define MCF5227_DMA_DCR_SMOD_128                 (0x4)
#define MCF5227_DMA_DCR_SMOD_256                 (0x5)
#define MCF5227_DMA_DCR_SMOD_512                 (0x6)
#define MCF5227_DMA_DCR_SMOD_1K                  (0x7)
#define MCF5227_DMA_DCR_SMOD_2K                  (0x8)
#define MCF5227_DMA_DCR_SMOD_4K                  (0x9)
#define MCF5227_DMA_DCR_SMOD_8K                  (0xA)
#define MCF5227_DMA_DCR_SMOD_16K                 (0xB)
#define MCF5227_DMA_DCR_SMOD_32K                 (0xC)
#define MCF5227_DMA_DCR_SMOD_64K                 (0xD)
#define MCF5227_DMA_DCR_SMOD_128K                (0xE)
#define MCF5227_DMA_DCR_SMOD_256K                (0xF)
#define MCF5227_DMA_DCR_START                    (0x10000)
#define MCF5227_DMA_DCR_DSIZE(x)                 (((x)&0x3)<<0x11)
#define MCF5227_DMA_DCR_DSIZE_LONG               (0)
#define MCF5227_DMA_DCR_DSIZE_BYTE               (0x1)
#define MCF5227_DMA_DCR_DSIZE_WORD               (0x2)
#define MCF5227_DMA_DCR_DSIZE_LINE               (0x3)
#define MCF5227_DMA_DCR_DINC                     (0x80000)
#define MCF5227_DMA_DCR_SSIZE(x)                 (((x)&0x3)<<0x14)
#define MCF5227_DMA_DCR_SSIZE_LONG               (0)
#define MCF5227_DMA_DCR_SSIZE_BYTE               (0x1)
#define MCF5227_DMA_DCR_SSIZE_WORD               (0x2)
#define MCF5227_DMA_DCR_SSIZE_LINE               (0x3)
#define MCF5227_DMA_DCR_SINC                     (0x400000)
#define MCF5227_DMA_DCR_BWC(x)                   (((x)&0x7)<<0x19)
#define MCF5227_DMA_DCR_BWC_16K                  (0x1)
#define MCF5227_DMA_DCR_BWC_32K                  (0x2)
#define MCF5227_DMA_DCR_BWC_64K                  (0x3)
#define MCF5227_DMA_DCR_BWC_128K                 (0x4)
#define MCF5227_DMA_DCR_BWC_256K                 (0x5)
#define MCF5227_DMA_DCR_BWC_512K                 (0x6)
#define MCF5227_DMA_DCR_BWC_1024K                (0x7)
#define MCF5227_DMA_DCR_AA                       (0x10000000)
#define MCF5227_DMA_DCR_CS                       (0x20000000)
#define MCF5227_DMA_DCR_EEXT                     (0x40000000)
#define MCF5227_DMA_DCR_INT                      (0x80000000)

/*------------------------------------------------------------------------*/
/*
** UART registers
*/
#define MCF5227_UART_UMR1_RXRTS             (0x80)
#define MCF5227_UART_UMR1_RXIRQ             (0x40)
#define MCF5227_UART_UMR1_ERR               (0x20)
#define MCF5227_UART_UMR1_EVEN_PARITY       (0x00)
#define MCF5227_UART_UMR1_ODD_PARITY        (0x04)
#define MCF5227_UART_UMR1_LOW_PARITY        (0x08)
#define MCF5227_UART_UMR1_HI_PARITY         (0x0C)
#define MCF5227_UART_UMR1_NO_PARITY         (0x10)
#define MCF5227_UART_UMR1_MULTI_DROP        (0x18)
#define MCF5227_UART_UMR1_MD_ADDRESS        (0x1C)
#define MCF5227_UART_UMR1_5_BITS            (0x00)
#define MCF5227_UART_UMR1_6_BITS            (0x01)
#define MCF5227_UART_UMR1_7_BITS            (0x02)
#define MCF5227_UART_UMR1_8_BITS            (0x03)
#define MCF5227_UART_UMR1_MASK_DATA_BITS    (0x03)

#define MCF5227_UART_UMR2_AUTO_ECHO         (0x40)
#define MCF5227_UART_UMR2_LOCAL_LOOP        (0x80)
#define MCF5227_UART_UMR2_RMT_LOOP          (0xC0)
#define MCF5227_UART_UMR2_TXRTS             (0x20)
#define MCF5227_UART_UMR2_TXCTS             (0x10)
#define MCF5227_UART_UMR2_1_STOP_BIT        (0x07)
#define MCF5227_UART_UMR2_2_STOP_BITS       (0x0F)
#define MCF5227_UART_UMR2_MASK_STOP_BITS    (0x0F)

#define MCF5227_UART_USR_RB                 (0x80)
#define MCF5227_UART_USR_FE                 (0x40)
#define MCF5227_UART_USR_PE                 (0x20)
#define MCF5227_UART_USR_OE                 (0x10)
#define MCF5227_UART_USR_TXEMP              (0x08)
#define MCF5227_UART_USR_TXRDY              (0x04)
#define MCF5227_UART_USR_FFULL              (0x02)
#define MCF5227_UART_USR_RXRDY              (0x01)

#define MCF5227_UART_UCSR_RX_TIMER          (0xD0)
#define MCF5227_UART_UCSR_RXCLK16           (0xE0)
#define MCF5227_UART_UCSR_RXCLK1            (0xF0)
#define MCF5227_UART_UCSR_TX_TIMER          (0x0D)
#define MCF5227_UART_UCSR_TXCLK16           (0x0E)
#define MCF5227_UART_UCSR_TXCLK1            (0x0F)

#define MCF5227_UART_UCR_RESET_POINTER      (0x10)
#define MCF5227_UART_UCR_RESET_RX           (0x20)
#define MCF5227_UART_UCR_RESET_TX           (0x30)
#define MCF5227_UART_UCR_RESET_ERROR        (0x40)
#define MCF5227_UART_UCR_RESET_BREAK        (0x50)
#define MCF5227_UART_UCR_START_BREAK        (0x60)
#define MCF5227_UART_UCR_STOP_BREAK         (0x70)
#define MCF5227_UART_UCR_AUTOBAUD           (0x80)
#define MCF5227_UART_UCR_TX_ENABLE          (0x04)
#define MCF5227_UART_UCR_TX_DISABLE         (0x08)
#define MCF5227_UART_UCR_RX_ENABLE          (0x01)
#define MCF5227_UART_UCR_RX_DISABLE         (0x02)

#define MCF5227_UART_UIPCR_CTS_CHANGE       (0x10)
#define MCF5227_UART_UIPCR_CTS              (0x01)

#define MCF5227_UART_UACR_INPUT_CNTRL       (0x01)

#define MCF5227_UART_UISR_CHANGE_STATE      (0x80)
#define MCF5227_UART_UISR_CHANGE_BRK        (0x04)
#define MCF5227_UART_UISR_RXRDY             (0x02)
#define MCF5227_UART_UISR_TXRDY             (0x01)

#define MCF5227_UART_UIMR_CHANGE_STATE      (0x80)
#define MCF5227_UART_UIMR_CHANGE_BRK        (0x04)
#define MCF5227_UART_UIMR_FFULL             (0x02)
#define MCF5227_UART_UIMR_TXRDY             (0x01)

#define MCF5227_UART_UIP_CTS                (0x01)

#define MCF5227_UART_UOP_RTS                (0x01)

/*------------------------------------------------------------------------*/
/*
** General Purpose I/O (GPIO) Module
*/

/* general bit definition */
#define MCF5227_GPIO_PIN_0      0x01
#define MCF5227_GPIO_PIN_1      0x02
#define MCF5227_GPIO_PIN_2      0x04
#define MCF5227_GPIO_PIN_3      0x08
#define MCF5227_GPIO_PIN_4      0x10
#define MCF5227_GPIO_PIN_5      0x20
#define MCF5227_GPIO_PIN_6      0x40
#define MCF5227_GPIO_PIN_7      0x80

/* Bit definitions for PODR_x registers */
#define MCF5227_GPIO_PODR_x0    0x01
#define MCF5227_GPIO_PODR_x1    0x02
#define MCF5227_GPIO_PODR_x2    0x04
#define MCF5227_GPIO_PODR_x3    0x08
#define MCF5227_GPIO_PODR_x4    0x10
#define MCF5227_GPIO_PODR_x5    0x20
#define MCF5227_GPIO_PODR_x6    0x40
#define MCF5227_GPIO_PODR_x7    0x80
#define MCF5227_GPIO_PODR_x(x)  (0x01<<x)

/* Bit definitions for PDDR_x registers */
#define MCF5227_GPIO_PDDR_x0    0x01
#define MCF5227_GPIO_PDDR_x1    0x02
#define MCF5227_GPIO_PDDR_x2    0x04
#define MCF5227_GPIO_PDDR_x3    0x08
#define MCF5227_GPIO_PDDR_x4    0x10
#define MCF5227_GPIO_PDDR_x5    0x20
#define MCF5227_GPIO_PDDR_x6    0x40
#define MCF5227_GPIO_PDDR_x7    0x80
#define MCF5227_GPIO_PDDR_x(x)  (0x01<<x)

/* Bit definitions for PPDSDR_x registers */
#define MCF5227_GPIO_PPDSDR_x0  0x01
#define MCF5227_GPIO_PPDSDR_x1  0x02
#define MCF5227_GPIO_PPDSDR_x2  0x04
#define MCF5227_GPIO_PPDSDR_x3  0x08
#define MCF5227_GPIO_PPDSDR_x4  0x10
#define MCF5227_GPIO_PPDSDR_x5  0x20
#define MCF5227_GPIO_PPDSDR_x6  0x40
#define MCF5227_GPIO_PPDSDR_x7  0x80
#define MCF5227_GPIO_PPDSDR_x(x)    (0x01<<x)

/* Bit definitions for PCLRR_x registers */
#define MCF5227_GPIO_PCLRR_x0   0x01
#define MCF5227_GPIO_PCLRR_x1   0x02
#define MCF5227_GPIO_PCLRR_x2   0x04
#define MCF5227_GPIO_PCLRR_x3   0x08
#define MCF5227_GPIO_PCLRR_x4   0x10
#define MCF5227_GPIO_PCLRR_x5   0x20
#define MCF5227_GPIO_PCLRR_x6   0x40
#define MCF5227_GPIO_PCLRR_x7   0x80
#define MCF5227_GPIO_PCLRR_x(x) (0x01<<x)

/* Bit definitions and macros for PAR_BE */
#define MCF5227_GPIO_PAR_BE0    0x01
#define MCF5227_GPIO_PAR_BE1    0x02
#define MCF5227_GPIO_PAR_BE2    0x04
#define MCF5227_GPIO_PAR_BE3    0x08 

/* Bit definitions and macros for PAR_CS */
#define MCF5227_GPIO_PAR_CS0        0x01
#define MCF5227_GPIO_PAR_CS1_GPIO   0x00
#define MCF5227_GPIO_PAR_CS1_SD_CS1 0x04
#define MCF5227_GPIO_PAR_CS1_FLEXBUS 0x06
#define MCF5227_GPIO_PAR_CS2        0x08
#define MCF5227_GPIO_PAR_CS3        0x10 
#define MCF5227_GPIO_PAR_CS0_MASK   0x01
#define MCF5227_GPIO_PAR_CS1_MASK   0x06
#define MCF5227_GPIO_PAR_CS2_MASK   0x08
#define MCF5227_GPIO_PAR_CS3_MASK   0x10

/* Bit definitions and macros for PAR_FBCTL */
#define MCF5227_GPIO_PAR_FBCTL_PAR_TS_GPIO      0x00
#define MCF5227_GPIO_PAR_FBCTL_PAR_TS_DMA_ACK   0x10
#define MCF5227_GPIO_PAR_FBCTL_PAR_TS_FB_START  0x18
#define MCF5227_GPIO_PAR_FBCTL_RWB              0x20
#define MCF5227_GPIO_PAR_FBCTL_TA               0x40
#define MCF5227_GPIO_PAR_FBCTL_OE               0x80
#define MCF5227_GPIO_PAR_FBCTL_TS_MASK          0x18
#define MCF5227_GPIO_PAR_FBCTL_RWB_MASK         0x20
#define MCF5227_GPIO_PAR_FBCTL_TA_MASK          0x40
#define MCF5227_GPIO_PAR_FBCTL_OE_MASK          0x80

/* Bit definitions and macros for PAR_I2C */
#define MCF5227_GPIO_PAR_SDA_UART2      0x01
#define MCF5227_GPIO_PAR_SDA_FLEXCAN    0x02
#define MCF5227_GPIO_PAR_SDA_I2C        0x03
#define MCF5227_GPIO_PAR_SCL_UART2      0x04
#define MCF5227_GPIO_PAR_SCL_FLEXCAN    0x08
#define MCF5227_GPIO_PAR_SCL_I2C        0x0C
#define MCF5227_GPIO_PAR_GPIO   0x00
#define MCF5227_GPIO_PAR_I2C_SDA_MASK   0x03
#define MCF5227_GPIO_PAR_I2C_SCL_MASK   0x0C

/* Bit definitions and macros for PAR_LCDCTL */
#define MCF5227_GPIO_PAR_LCDCTL_LSCLK       0x01
#define MCF5227_GPIO_PAR_LCDCTL_LP_HSYNC    0x02
#define MCF5227_GPIO_PAR_LCDCTL_FLM_VSYNC   0x04
#define MCF5227_GPIO_PAR_LCDCTL_ACD_OE_GPIO 0x00
#define MCF5227_GPIO_PAR_LCDCTL_ACD_OE_LCD_SPRL_SPR 0x10
#define MCF5227_GPIO_PAR_LCDCTL_ACD_OE      0x18
#define MCF5227_GPIO_PAR_LCDCTL_LSCLK_MASK  0x01
#define MCF5227_GPIO_PAR_LCDCTL_LP_HSYNC_MASK   0x02 
#define MCF5227_GPIO_PAR_LCDCTL_FLM_VSYNC_MASK  0x04
#define MCF5227_GPIO_PAR_LCDCTL_ACD_OE_MASK 0x18

/* Bit definitions and macros for PAR_IRQ */
#define MCF5227_GPIO_PAR_IRQ_GPIO       0x00
#define MCF5227_GPIO_PAR_IRQ_SSI_CLKIN  0x01
#define MCF5227_GPIO_PAR_IRQ_USB_CLKIN  0x02
#define MCF5227_GPIO_PAR_IRQ_DSPI_PCS4  0x04
#define MCF5227_GPIO_PAR_IRQ_DMA        0x08
#define MCF5227_GPIO_PAR_IRQ1_MASK      0x03
#define MCF5227_GPIO_PAR_IRQ4_MASK      0x0C

/* Bit definitions and macros for PAR_LCDH */
#define MCF5227_GPIO_PAR_LCDH_GPIO              0x00000000
#define MCF5227_GPIO_PAR_LCDH_LD12_CANRX        0x00000002
#define MCF5227_GPIO_PAR_LCDH_LD12_LCD_D12_P    0x00000003
#define MCF5227_GPIO_PAR_LCDH_LD13_CANTX        0x00000008
#define MCF5227_GPIO_PAR_LCDH_LD13_LCD_D13_P    0x0000000C
#define MCF5227_GPIO_PAR_LCDH_LD14_LCD_D8_A     0x00000020
#define MCF5227_GPIO_PAR_LCDH_LD14_LCD_D14_P    0x00000030
#define MCF5227_GPIO_PAR_LCDH_LD15_LCD_D9_A     0x00000080
#define MCF5227_GPIO_PAR_LCDH_LD15_LCD_D15_P    0x000000C0
#define MCF5227_GPIO_PAR_LCDH_LD16_LCD_D10_A    0x00000200
#define MCF5227_GPIO_PAR_LCDH_LD16_LCD_D16_P    0x00000300
#define MCF5227_GPIO_PAR_LCDH_LD17_LCD_D11_A    0x00000800
#define MCF5227_GPIO_PAR_LCDH_LD17_LCD_D17_P    0x00000C00
#define MCF5227_GPIO_PAR_LCDH_LD12_MASK         0x00000003
#define MCF5227_GPIO_PAR_LCDH_LD13_MASK         0x0000000C
#define MCF5227_GPIO_PAR_LCDH_LD14_MASK         0x00000030
#define MCF5227_GPIO_PAR_LCDH_LD15_MASK         0x000000C0
#define MCF5227_GPIO_PAR_LCDH_LD16_MASK         0x00000300
#define MCF5227_GPIO_PAR_LCDH_LD17_MASK         0x00000C00

/* Bit definitions and macros for PAR_LCDL */ 
#define MCF5227_GPIO_PAR_LCDL_LD11_LCD_D7_A     0x80000000
#define MCF5227_GPIO_PAR_LCDL_LD11_LCD_D11_P    0xC0000000
#define MCF5227_GPIO_PAR_LCDL_LD10_LCD_D6_A     0x20000000
#define MCF5227_GPIO_PAR_LCDL_LD10_LCD_D10_P    0x30000000
#define MCF5227_GPIO_PAR_LCDL_LD9_LCD_D5_A      0x08000000
#define MCF5227_GPIO_PAR_LCDL_LD9_LCD_D9_P      0x0C000000
#define MCF5227_GPIO_PAR_LCDL_LD8_LCD_D4_A      0x02000000
#define MCF5227_GPIO_PAR_LCDL_LD8_LCD_D8_P      0x03000000
#define MCF5227_GPIO_PAR_LCDL_LD7_PWM7          0x00800000
#define MCF5227_GPIO_PAR_LCDL_LD7_LCD_D7_P      0x00C00000
#define MCF5227_GPIO_PAR_LCDL_LD6_PWM5          0x00200000
#define MCF5227_GPIO_PAR_LCDL_LD6_LCD_D6_P      0x00300000
#define MCF5227_GPIO_PAR_LCDL_LD5_LCD_D3_A      0x00080000
#define MCF5227_GPIO_PAR_LCDL_LD5_LCD_D5_P      0x000C0000
#define MCF5227_GPIO_PAR_LCDL_LD4_LCD_D2_A      0x00020000
#define MCF5227_GPIO_PAR_LCDL_LD4_LCD_D4_P      0x00030000
#define MCF5227_GPIO_PAR_LCDL_LD3_LCD_D1_A      0x00008000
#define MCF5227_GPIO_PAR_LCDL_LD3_LCD_D3_P      0x0000C000
#define MCF5227_GPIO_PAR_LCDL_LD2_LCD_D0_A      0x00002000
#define MCF5227_GPIO_PAR_LCDL_LD2_LCD_D2_P      0x00003000
#define MCF5227_GPIO_PAR_LCDL_LD1_PWM3          0x00000800
#define MCF5227_GPIO_PAR_LCDL_LD1_LCD_D1_P      0x00000C00
#define MCF5227_GPIO_PAR_LCDL_LD0_PWM1          0x00000200
#define MCF5227_GPIO_PAR_LCDL_LD0_LCD0_P        0x00000300
#define MCF5227_GPIO_PAR_LCDL_GPIO              0x00000000
#define MCF5227_GPIO_PAR_LCDL_LD0_MASK          0x00000300
#define MCF5227_GPIO_PAR_LCDL_LD1_MASK          0x00000C00
#define MCF5227_GPIO_PAR_LCDL_LD2_MASK          0x00003000
#define MCF5227_GPIO_PAR_LCDL_LD3_MASK          0x0000C000
#define MCF5227_GPIO_PAR_LCDL_LD4_MASK          0x00030000
#define MCF5227_GPIO_PAR_LCDL_LD5_MASK          0x000C0000
#define MCF5227_GPIO_PAR_LCDL_LD6_MASK          0x00300000
#define MCF5227_GPIO_PAR_LCDL_LD7_MASK          0x00C00000
#define MCF5227_GPIO_PAR_LCDL_LD8_MASK          0x03000000
#define MCF5227_GPIO_PAR_LCDL_LD9_MASK          0x0C000000
#define MCF5227_GPIO_PAR_LCDL_LD10_MASK         0x30000000
#define MCF5227_GPIO_PAR_LCDL_LD11_MASK         0xC0000000

/* Bit definitions and macros for PAR_TIMER */
#define MCF5227_GPIO_PAR_TIMER_TIN3_GPIO    (0x00)
#define MCF5227_GPIO_PAR_TIMER_TIN3_SSIMCLK     (0x40)
#define MCF5227_GPIO_PAR_TIMER_TIN3_TOUT3       (0x80)
#define MCF5227_GPIO_PAR_TIMER_TIN3_TIN3        (0xC0)
#define MCF5227_GPIO_PAR_TIMER_TIN2_GPIO        (0x00)
#define MCF5227_GPIO_PAR_TIMER_TIN2_DSPIPCS2    (0x10)
#define MCF5227_GPIO_PAR_TIMER_TIN2_TOUT2       (0x20)
#define MCF5227_GPIO_PAR_TIMER_TIN2_TIN2        (0x30)
#define MCF5227_GPIO_PAR_TIMER_TIN1_GPIO        (0x00)
#define MCF5227_GPIO_PAR_TIMER_TIN1_LCDCONTRAST (0x04)
#define MCF5227_GPIO_PAR_TIMER_TIN1_TOUT1       (0x08)
#define MCF5227_GPIO_PAR_TIMER_TIN1_TIN1        (0x0C)
#define MCF5227_GPIO_PAR_TIMER_TIN0_GPIO        (0x00)
#define MCF5227_GPIO_PAR_TIMER_TIN0_LCDREV      (0x01)
#define MCF5227_GPIO_PAR_TIMER_TIN0_TOUT0       (0x02)
#define MCF5227_GPIO_PAR_TIMER_TIN0_TIN0        (0x03)
#define MCF5227_GPIO_PAR_TIMER_T0IN_MASK        (0x03)
#define MCF5227_GPIO_PAR_TIMER_T1IN_MASK        (0x0C)
#define MCF5227_GPIO_PAR_TIMER_T2IN_MASK        (0x30)
#define MCF5227_GPIO_PAR_TIMER_T3IN_MASK        (0xC0)

/* Bit definitions and macros for PAR_UART */
#define MCF5227_GPIO_PAR_UART_U0TXD_U0TXD   (0x0003)
#define MCF5227_GPIO_PAR_UART_U0TXD_CANTX   (0x0002)
#define MCF5227_GPIO_PAR_UART_U0TXD_GPIO    (0x0000)
#define MCF5227_GPIO_PAR_UART_U0RXD_U0RXD   (0x000C)
#define MCF5227_GPIO_PAR_UART_U0RXD_CANTX   (0x0008)
#define MCF5227_GPIO_PAR_UART_U0RXD_GPIO    (0x0000)
#define MCF5227_GPIO_PAR_UART_U0RTS_U0RTS   (0x0030)
#define MCF5227_GPIO_PAR_UART_U0RTS_T1IN    (0x0020)
#define MCF5227_GPIO_PAR_UART_U0RTS_USBVBOC (0x0010)
#define MCF5227_GPIO_PAR_UART_U0RTS_GPIO    (0x0000)
#define MCF5227_GPIO_PAR_UART_U0CTS_U0CTS   (0x00C0)
#define MCF5227_GPIO_PAR_UART_U0CTS_T1OUT   (0x0080)
#define MCF5227_GPIO_PAR_UART_U0CTS_USBVBEN (0x0040)
#define MCF5227_GPIO_PAR_UART_U0CTS_GPIO    (0x0000)
#define MCF5227_GPIO_PAR_UART_U1TXD_U1TXD   (0x0300)
#define MCF5227_GPIO_PAR_UART_U1TXD_SSITXD  (0x0200)
#define MCF5227_GPIO_PAR_UART_U1TXD_GPIO    (0x0000)
#define MCF5227_GPIO_PAR_UART_U1RXD_U1RXD   (0x0C00)
#define MCF5227_GPIO_PAR_UART_U1RXD_SSIRXD  (0x0800)
#define MCF5227_GPIO_PAR_UART_U1RXD_GPIO    (0x0000)
#define MCF5227_GPIO_PAR_UART_U1RTS_U1RTS   (0x3000)
#define MCF5227_GPIO_PAR_UART_U1RTS_SSIFS   (0x2000)
#define MCF5227_GPIO_PAR_UART_U1RTS_LCDPS   (0x1000)
#define MCF5227_GPIO_PAR_UART_U1RTS_GPIO    (0x0000)
#define MCF5227_GPIO_PAR_UART_U1CTS_U1CTS   (0xC000)
#define MCF5227_GPIO_PAR_UART_U1CTS_SSIBCLK (0x8000)
#define MCF5227_GPIO_PAR_UART_U1CTS_LCDCLS  (0x4000)
#define MCF5227_GPIO_PAR_UART_U1CTS_GPIO    (0x0000)
#define MCF5227_GPIO_PAR_UART_U0TXD_MASK    (0x0003)
#define MCF5227_GPIO_PAR_UART_U0RXD_MASK    (0x000C)
#define MCF5227_GPIO_PAR_UART_U0RTS_MASK    (0x0030)
#define MCF5227_GPIO_PAR_UART_U0CTS_MASK    (0x00C0)
#define MCF5227_GPIO_PAR_UART_U1TXD_MASK    (0x0300)
#define MCF5227_GPIO_PAR_UART_U1RXD_MASK    (0x0C00)
#define MCF5227_GPIO_PAR_UART_U1RTS_MASK    (0x3000)
#define MCF5227_GPIO_PAR_UART_U1CTS_MASK    (0xC000)

/* Bit definitions and macros for PAR_DSPI */
#define MCF5227_GPIO_PAR_DSPI_SCK_DSPISCK   (0x03)
#define MCF5227_GPIO_PAR_DSPI_SCK_U2CTS     (0x02)
#define MCF5227_GPIO_PAR_DSPI_SCK_GPIO      (0x00)
#define MCF5227_GPIO_PAR_DSPI_SOUT_DSPISOUT (0x0C)
#define MCF5227_GPIO_PAR_DSPI_SOUT_U2TXD    (0x08)
#define MCF5227_GPIO_PAR_DSPI_SOUT_GPIO     (0x00)
#define MCF5227_GPIO_PAR_DSPI_SIN_DSPISIN   (0x30)
#define MCF5227_GPIO_PAR_DSPI_SIN_U2RXD     (0x20)
#define MCF5227_GPIO_PAR_DSPI_SIN_GPIO      (0x00)
#define MCF5227_GPIO_PAR_DSPI_PCS0_DSPIPCS0 (0xC0)
#define MCF5227_GPIO_PAR_DSPI_PCS0_U2RTS    (0x80)
#define MCF5227_GPIO_PAR_DSPI_PCS0_GPIO     (0x00)
#define MCF5227_GPIO_PAR_DSPI_SCK_MASK      (0x03)
#define MCF5227_GPIO_PAR_DSPI_SOUT_MASK     (0x0C)
#define MCF5227_GPIO_PAR_DSPI_SIN_MASK      (0x30)
#define MCF5227_GPIO_PAR_DSPI_PCS0_MASK     (0xC0) 

/* Bit definitions and macros for PAR_FEC */
#define MCF5227_GPIO_PAR_FEC_7W_FEC         (0x0C)
#define MCF5227_GPIO_PAR_FEC_MII_FEC            (0x03)

/* Bit definitions and macros for PAR_FECI2C */
#define MCF5227_GPIO_PAR_FECI2C_MDC_EMDC        (0xC0)
#define MCF5227_GPIO_PAR_FECI2C_MDIO_EMDIO      (0x30)

/*------------------------------------------------------------------------*/
/*
**  I2C  registers bit set.
*/

/* Bit definitions and macros for MCF5227_I2C_I2ADR */
#define MCF5227_I2C_I2ADR_ADR(x)                 (((x)&0x7F)<<0x1)

/* Bit definitions and macros for MCF5227_I2C_I2FDR */
#define MCF5227_I2C_I2FDR_IC(x)                  (((x)&0x3F)<<0)

/* Bit definitions and macros for MCF5227_I2C_I2CR */
#define MCF5227_I2C_I2CR_RSTA                    (0x4)
#define MCF5227_I2C_I2CR_TXAK                    (0x8)
#define MCF5227_I2C_I2CR_MTX                     (0x10)
#define MCF5227_I2C_I2CR_MSTA                    (0x20)
#define MCF5227_I2C_I2CR_IIEN                    (0x40)
#define MCF5227_I2C_I2CR_IEN                     (0x80)

/* Bit definitions and macros for MCF5227_I2C_I2SR */
#define MCF5227_I2C_I2SR_RXAK                    (0x1)
#define MCF5227_I2C_I2SR_IIF                     (0x2)
#define MCF5227_I2C_I2SR_SRW                     (0x4)
#define MCF5227_I2C_I2SR_IAL                     (0x10)
#define MCF5227_I2C_I2SR_IBB                     (0x20)
#define MCF5227_I2C_I2SR_IAAS                    (0x40)
#define MCF5227_I2C_I2SR_ICF                     (0x80)

/* Bit definitions and macros for MCF5227_I2C_I2DR */
#define MCF5227_I2C_I2DR_DATA(x)                 (((x)&0xFF)<<0)


/*------------------------------------------------------------------------*/
/*
** DMA_TIMER  registers bit set.
*/
/* Bit definitions and macros for MCF5227_DTIM_DTMR */
#define MCF5227_DTIM_DTMR_RST                    (0x1)
#define MCF5227_DTIM_DTMR_CLK(x)                 (((x)&0x3)<<0x1)
#define MCF5227_DTIM_DTMR_CLK_STOP               (0)
#define MCF5227_DTIM_DTMR_CLK_DIV1               (0x2)
#define MCF5227_DTIM_DTMR_CLK_DIV16              (0x4)
#define MCF5227_DTIM_DTMR_CLK_DTIN               (0x6)
#define MCF5227_DTIM_DTMR_FRR                    (0x8)
#define MCF5227_DTIM_DTMR_ORRI                   (0x10)
#define MCF5227_DTIM_DTMR_OM                     (0x20)
#define MCF5227_DTIM_DTMR_CE(x)                  (((x)&0x3)<<0x6)
#define MCF5227_DTIM_DTMR_CE_NONE                (0)
#define MCF5227_DTIM_DTMR_CE_RISE                (0x40)
#define MCF5227_DTIM_DTMR_CE_FALL                (0x80)
#define MCF5227_DTIM_DTMR_CE_ANY                 (0xC0)
#define MCF5227_DTIM_DTMR_PS(x)                  (((x)&0xFF)<<0x8)

/* Bit definitions and macros for MCF5227_DTIM_DTXMR */
#define MCF5227_DTIM_DTXMR_MODE16                (0x1)
#define MCF5227_DTIM_DTXMR_DMAEN                 (0x80)

/* Bit definitions and macros for MCF5227_DTIM_DTER */
#define MCF5227_DTIM_DTER_CAP                    (0x1)
#define MCF5227_DTIM_DTER_REF                    (0x2)

/* Bit definitions and macros for MCF5227_DTIM_DTRR */
#define MCF5227_DTIM_DTRR_REF(x)                 (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF5227_DTIM_DTCR */
#define MCF5227_DTIM_DTCR_CAP(x)                 (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF5227_DTIM_DTCN */
#define MCF5227_DTIM_DTCN_CNT(x)                 (((x)&0xFFFFFFFF)<<0)


/*------------------------------------------------------------------------*/
/*
** General Purpose I/O (GPIO) Module
*/

#define MCF5227_GPIO_PORTx7                     (0x80)
#define MCF5227_GPIO_PORTx6                     (0x40)
#define MCF5227_GPIO_PORTx5                     (0x20)
#define MCF5227_GPIO_PORTx4                     (0x10)
#define MCF5227_GPIO_PORTx3                     (0x08)
#define MCF5227_GPIO_PORTx2                     (0x04)
#define MCF5227_GPIO_PORTx1                     (0x02)
#define MCF5227_GPIO_PORTx0                     (0x01)
#define MCF5227_GPIO_PORTx(x)                   (0x01<<x)

#define MCF5227_GPIO_DDRx7                      (0x80)
#define MCF5227_GPIO_DDRx6                      (0x40)
#define MCF5227_GPIO_DDRx5                      (0x20)
#define MCF5227_GPIO_DDRx4                      (0x10)
#define MCF5227_GPIO_DDRx3                      (0x08)
#define MCF5227_GPIO_DDRx2                      (0x04)
#define MCF5227_GPIO_DDRx1                      (0x02)
#define MCF5227_GPIO_DDRx0                      (0x01)
#define MCF5227_GPIO_DDRx(x)                    (0x01<<x)

#define MCF5227_GPIO_PORTxP7                    (0x80)
#define MCF5227_GPIO_PORTxP6                    (0x40)
#define MCF5227_GPIO_PORTxP5                    (0x20)
#define MCF5227_GPIO_PORTxP4                    (0x10)
#define MCF5227_GPIO_PORTxP3                    (0x08)
#define MCF5227_GPIO_PORTxP2                    (0x04)
#define MCF5227_GPIO_PORTxP1                    (0x02)
#define MCF5227_GPIO_PORTxP0                    (0x01)
#define MCF5227_GPIO_PORTxP(x)                  (0x01<<x)

#define MCF5227_GPIO_SETx7                      (0x80)
#define MCF5227_GPIO_SETx6                      (0x40)
#define MCF5227_GPIO_SETx5                      (0x20)
#define MCF5227_GPIO_SETx4                      (0x10)
#define MCF5227_GPIO_SETx3                      (0x08)
#define MCF5227_GPIO_SETx2                      (0x04)
#define MCF5227_GPIO_SETx1                      (0x02)
#define MCF5227_GPIO_SETx0                      (0x01)
#define MCF5227_GPIO_SETx(x)                    (0x01<<x)

#define MCF5227_GPIO_CLRx7                      (0x80)
#define MCF5227_GPIO_CLRx6                      (0x40)
#define MCF5227_GPIO_CLRx5                      (0x20)
#define MCF5227_GPIO_CLRx4                      (0x10)
#define MCF5227_GPIO_CLRx3                      (0x08)
#define MCF5227_GPIO_CLRx2                      (0x04)
#define MCF5227_GPIO_CLRx1                      (0x02)
#define MCF5227_GPIO_CLRx0                      (0x01)
#define MCF5227_GPIO_CLRx(x)                    (0x01<<x)

#define MCF5227_GPIO_PBCDPAR_PBPA               (0x80)
#define MCF5227_GPIO_PBCDPAR_PCDPA              (0x40)

#define MCF5227_GPIO_PEPAR_PEPA7                (0x4000)
#define MCF5227_GPIO_PEPAR_PEPA6                (0x1000)
#define MCF5227_GPIO_PEPAR_PEPA5                (0x0400)
#define MCF5227_GPIO_PEPAR_PEPA4                (0x0100)
#define MCF5227_GPIO_PEPAR_PEPA3                (0x0040)
#define MCF5227_GPIO_PEPAR_PEPA2                (0x0010)
#define MCF5227_GPIO_PEPAR_PEPA1(x)             (((x)&0x3)<<2)
#define MCF5227_GPIO_PEPAR_PEPA0(x)             (((x)&0x3))

#define MCF5227_GPIO_PFPAR_PFPA7                (0x80)
#define MCF5227_GPIO_PFPAR_PFPA6                (0x40)
#define MCF5227_GPIO_PFPAR_PFPA5                (0x20)

#define MCF5227_GPIO_PJPAR_PJPA7                (0x80)
#define MCF5227_GPIO_PJPAR_PJPA6                (0x40)
#define MCF5227_GPIO_PJPAR_PJPA5                (0x20)
#define MCF5227_GPIO_PJPAR_PJPA4                (0x10)
#define MCF5227_GPIO_PJPAR_PJPA3                (0x08)
#define MCF5227_GPIO_PJPAR_PJPA2                (0x04)
#define MCF5227_GPIO_PJPAR_PJPA1                (0x02)
#define MCF5227_GPIO_PJPAR_PJPA0                (0x01)
#define MCF5227_GPIO_PJPAR_PJPA(x)              (0x01<<x)

#define MCF5227_GPIO_PSDPAR_PSDPA               (0x80)

#define MCF5227_GPIO_PASPAR_PASPA5(x)           (((x)&0x3)<<10)
#define MCF5227_GPIO_PASPAR_PASPA4(x)           (((x)&0x3)<<8)
#define MCF5227_GPIO_PASPAR_PASPA3(x)           (((x)&0x3)<<6)
#define MCF5227_GPIO_PASPAR_PASPA2(x)           (((x)&0x3)<<4)
#define MCF5227_GPIO_PASPAR_PASPA1(x)           (((x)&0x3)<<2)
#define MCF5227_GPIO_PASPAR_PASPA0(x)           (((x)&0x3))

#define MCF5227_GPIO_PEHLPAR_PEHPA              (0x80)
#define MCF5227_GPIO_PEHLPAR_PELPA              (0x40)

/* Bit definitions and macros for MCF5227_GPIO_PQSPAR */
#define MCF5227_GPIO_PQSPAR_PQSPA6(x)           (((x) & 3) << 12)
#define MCF5227_GPIO_PQSPAR_PQSPA5(x)           (((x) & 3) << 10)
#define MCF5227_GPIO_PQSPAR_PQSPA4(x)           (((x) & 3) << 8)
#define MCF5227_GPIO_PQSPAR_PQSPA3(x)           (((x) & 3) << 6)
#define MCF5227_GPIO_PQSPAR_PQSPA2(x)           (((x) & 3) << 4)
#define MCF5227_GPIO_PQSPAR_PQSPA1(x)           (((x) & 3) << 2)
#define MCF5227_GPIO_PQSPAR_PQSPA0(x)           (((x) & 3) << 0)

#define MCF5227_GPIO_PTCPAR_PTCPA3(x)           (((x)&0x3)<<6)
#define MCF5227_GPIO_PTCPAR_PTCPA2(x)           (((x)&0x3)<<4)
#define MCF5227_GPIO_PTCPAR_PTCPA1(x)           (((x)&0x3)<<2)
#define MCF5227_GPIO_PTCPAR_PTCPA0(x)           (((x)&0x3))

#define MCF5227_GPIO_PTDPAR_PTDPA3(x)           (((x)&0x3)<<6)
#define MCF5227_GPIO_PTDPAR_PTDPA2(x)           (((x)&0x3)<<4)
#define MCF5227_GPIO_PTDPAR_PTDPA1(x)           (((x)&0x3)<<2)
#define MCF5227_GPIO_PTDPAR_PTDPA0(x)           (((x)&0x3))

#define MCF5227_GPIO_PUAPAR_PUAPA3              (0x08)
#define MCF5227_GPIO_PUAPAR_PUAPA2              (0x04)
#define MCF5227_GPIO_PUAPAR_PUAPA1              (0x02)
#define MCF5227_GPIO_PUAPAR_PUAPA0              (0x01)

/* Bit definitions and macros for MCF5227_GPIO_PUAPAR */
#define MCF5227_GPIO_PUAPAR_PUAPAR0(x)          (((x)&0x03)<<0)
#define MCF5227_GPIO_PUAPAR_PUAPAR1(x)          (((x)&0x03)<<2)
#define MCF5227_GPIO_PUAPAR_PUAPAR2(x)          (((x)&0x03)<<4)
#define MCF5227_GPIO_PUAPAR_PUAPAR3(x)          (((x)&0x03)<<6)
#define MCF5227_GPIO_PUAPAR_TXD0_TXD0           (0x01)
#define MCF5227_GPIO_PUAPAR_RXD0_RXD0           (0x04)
#define MCF5227_GPIO_PUAPAR_RTS0_RTS0           (0x10)
#define MCF5227_GPIO_PUAPAR_CTS0_CTS0           (0x40)
#define MCF5227_GPIO_PUAPAR_RTS0_CANTX          (0x20)
#define MCF5227_GPIO_PUAPAR_CTS0_CANRX          (0x80)

/* Bit definitions and macros for PUBPAR */
#define MCF5227_GPIO_PUBPAR_PUBPAR0(x)          (((x)&0x03)<<0)
#define MCF5227_GPIO_PUBPAR_PUBPAR1(x)          (((x)&0x03)<<2)
#define MCF5227_GPIO_PUBPAR_PUBPAR2(x)          (((x)&0x03)<<4)
#define MCF5227_GPIO_PUBPAR_PUBPAR3(x)          (((x)&0x03)<<6)
#define MCF5227_GPIO_PUBPAR_TXD1_TXD1           (0x01)
#define MCF5227_GPIO_PUBPAR_RXD1_RXD1           (0x04)
#define MCF5227_GPIO_PUBPAR_RTS1_RTS1           (0x10)
#define MCF5227_GPIO_PUBPAR_CTS1_CTS1           (0x40)
#define MCF5227_GPIO_PUBPAR_RTS1_SYNCB          (0x20)
#define MCF5227_GPIO_PUBPAR_CTS1_SYNCA          (0x80)
#define MCF5227_GPIO_PUBPAR_RTS1_TXD2           (0x30)
#define MCF5227_GPIO_PUBPAR_CTS1_RXD2           (0xC0)

/* Bit definitions and macros for PUCPAR */
#define MCF5227_GPIO_PUCPAR_PUCPAR0             (0x01)
#define MCF5227_GPIO_PUCPAR_PUCPAR1             (0x02)
#define MCF5227_GPIO_PUCPAR_PUCPAR2             (0x04)
#define MCF5227_GPIO_PUCPAR_PUCPAR3             (0x08)
#define MCF5227_GPIO_PUCPAR_TXD2_TXD2           (0x01)
#define MCF5227_GPIO_PUCPAR_RXD2_RXD2           (0x02)
#define MCF5227_GPIO_PUCPAR_RTS2_RTS2           (0x04)
#define MCF5227_GPIO_PUCPAR_CTS2_CTS2           (0x08)

/* Bit definitions and macros for PDDPAR */
#define MCF5227_GPIO_PDDPAR_PST                 (0x0F)


/*------------------------------------------------------------------------*/
/*
** CCM  registers bit set.
*/

/* Bit definitions and macros for MCF5227_CCM_CCR */
#define MCF5227_CCM_CCR_BMT(x)                  (((x)&0x7)<<0)
#define MCF5227_CCM_CCR_BMT_65536               (0)
#define MCF5227_CCM_CCR_BMT_32768               (0x1)
#define MCF5227_CCM_CCR_BMT_16384               (0x2)
#define MCF5227_CCM_CCR_BMT_8192                (0x3)
#define MCF5227_CCM_CCR_BMT_4096                (0x4)
#define MCF5227_CCM_CCR_BMT_2048                (0x5)
#define MCF5227_CCM_CCR_BMT_1024                (0x6)
#define MCF5227_CCM_CCR_BMT_512                 (0x7)
#define MCF5227_CCM_CCR_BME                     (0x8)
#define MCF5227_CCM_CCR_PSTEN                   (0x20)
#define MCF5227_CCM_CCR_SZEN                    (0x40)
#define MCF5227_CCM_CCR_LOAD                    (0x8000)

/* Bit definitions and macros for MCF5227_CCM_RCON */
#define MCF5227_CCM_RCON_MODE                   (0x1)
#define MCF5227_CCM_RCON_BOOTPS(x)              (((x)&0x3)<<0x3)
#define MCF5227_CCM_RCON_RLOAD                  (0x20)
#define MCF5227_CCM_RCON_RCSC(x)                (((x)&0x3)<<0x8)

/* Bit definitions and macros for MCF5227_CCM_CIR */
#define MCF5227_CCM_CIR_PRN(x)                  (((x)&0x3F)<<0)
#define MCF5227_CCM_CIR_PIN(x)                  (((x)&0x3FF)<<0x6)

/* Bit definitions and macros for MCF5227_CCM_CCE */
#define MCF5227_CCM_CCE_USBEND                  (1 << 14)
#define MCF5227_CCM_CCE_MBMOD                   (1 << 15)

/* Bit definitions and macros for MCF5227_CCM_MISCCR */
#define MCF5227_CCM_MISCCR_RTCSRC               (1 << 14)
#define MCF5227_CCM_MISCCR_LIMP                 (1 << 12)


/*------------------------------------------------------------------------*/
/*
** CLK  registers bit set.
*/

/* Bit definitions and macros for SYNCR */
/*#define MCF5227_CLOCK_SYNCR_LOLRE               (0x8000)
#define MCF5227_CLOCK_SYNCR_MFD(x)              (((x)&0x0007)<<12)
#define MCF5227_CLOCK_SYNCR_LOCRE               (0x0800)
#define MCF5227_CLOCK_SYNCR_RFD(x)              (((x)&0x0007)<<8)
#define MCF5227_CLOCK_SYNCR_LOCEN               (0x0080)
#define MCF5227_CLOCK_SYNCR_DISCLK              (0x0040)
#define MCF5227_CLOCK_SYNCR_FWKUP               (0x0020)
#define MCF5227_CLOCK_SYNCR_CLKSRC              (0x0004)
#define MCF5227_CLOCK_SYNCR_PLLMODE             (0x0002)
#define MCF5227_CLOCK_SYNCR_PLLEN               (0x0001)
*/
/* Bit definitions and macros for SYNSR */
/*#define MCF5227_CLOCK_SYNSR_LOCKS               (0x10)
#define MCF5227_CLOCK_SYNSR_LOCK                (0x08)
#define MCF5227_CLOCK_SYNSR_LOCS                (0x04)
*/
/* Bit definitions and macros for LPCR */
//#define MCF5227_CLOCK_LPCR_LPD(x)             (((x)&0x0F)<<0)

/* Bit definitions and macros for CCHR */
//#define MCF5227_CLOCK_CCHR_PFD(x)             (((x)&0x07)<<0)

/* Bit definitions and macros for RTCDR */
//#define MCF5227_CLOCK_RTCDR_RTCDF(x)          (((x)&0xFFFFFFFF)<<0)

/*------------------------------------------------------------------------*/
/*
** PLL  registers bit set.
*/

/* Bit definitions and macros for PCR */
#define MCF5227_PLL_PCR_OUTDIV1(x)          ((x) & 0x0f)
#define MCF5227_PLL_PCR_OUTDIV2(x)          (((x) & 0x0f) << 4)
#define MCF5227_PLL_PCR_OUTDIV3(x)          (((x) & 0x0f) << 8)
//#define MCF5227_PLL_PCR_OUTDIV4(x)          (((x) & 0x0f) << 12)
#define MCF5227_PLL_PCR_OUTDIV5(x)          (((x) & 0x0f) << 16)
#define MCF5227_PLL_PCR_PFDR(x)             (((x) & 0xff) << 24)

/* Bit definitions and macros for PSR */
#define MCF5227_PLL_PSR_LOCKS               (0x01)
#define MCF5227_PLL_PSR_LOCK                (0x02)
#define MCF5227_PLL_PSR_LOLIRQ              (0x04)
#define MCF5227_PLL_PSR_LOLRE               (0x08)

/*------------------------------------------------------------------------*/
/*
** EPORT  registers bit set.
*/

/* Bit definitions and macros for MCF5227_EPORT_EPPAR */
#define MCF5227_EPORT_EPPAR_EPPA1(x)             (((x)&0x3)<<0x2)
#define MCF5227_EPORT_EPPAR_EPPA1_LEVEL          (0)
#define MCF5227_EPORT_EPPAR_EPPA1_RISING         (0x4)
#define MCF5227_EPORT_EPPAR_EPPA1_FALLING        (0x8)
#define MCF5227_EPORT_EPPAR_EPPA1_BOTH           (0xC)
#define MCF5227_EPORT_EPPAR_EPPA2(x)             (((x)&0x3)<<0x4)
#define MCF5227_EPORT_EPPAR_EPPA2_LEVEL          (0)
#define MCF5227_EPORT_EPPAR_EPPA2_RISING         (0x10)
#define MCF5227_EPORT_EPPAR_EPPA2_FALLING        (0x20)
#define MCF5227_EPORT_EPPAR_EPPA2_BOTH           (0x30)
#define MCF5227_EPORT_EPPAR_EPPA3(x)             (((x)&0x3)<<0x6)
#define MCF5227_EPORT_EPPAR_EPPA3_LEVEL          (0)
#define MCF5227_EPORT_EPPAR_EPPA3_RISING         (0x40)
#define MCF5227_EPORT_EPPAR_EPPA3_FALLING        (0x80)
#define MCF5227_EPORT_EPPAR_EPPA3_BOTH           (0xC0)
#define MCF5227_EPORT_EPPAR_EPPA4(x)             (((x)&0x3)<<0x8)
#define MCF5227_EPORT_EPPAR_EPPA4_LEVEL          (0)
#define MCF5227_EPORT_EPPAR_EPPA4_RISING         (0x100)
#define MCF5227_EPORT_EPPAR_EPPA4_FALLING        (0x200)
#define MCF5227_EPORT_EPPAR_EPPA4_BOTH           (0x300)
#define MCF5227_EPORT_EPPAR_EPPA5(x)             (((x)&0x3)<<0xA)
#define MCF5227_EPORT_EPPAR_EPPA5_LEVEL          (0)
#define MCF5227_EPORT_EPPAR_EPPA5_RISING         (0x400)
#define MCF5227_EPORT_EPPAR_EPPA5_FALLING        (0x800)
#define MCF5227_EPORT_EPPAR_EPPA5_BOTH           (0xC00)
#define MCF5227_EPORT_EPPAR_EPPA6(x)             (((x)&0x3)<<0xC)
#define MCF5227_EPORT_EPPAR_EPPA6_LEVEL          (0)
#define MCF5227_EPORT_EPPAR_EPPA6_RISING         (0x1000)
#define MCF5227_EPORT_EPPAR_EPPA6_FALLING        (0x2000)
#define MCF5227_EPORT_EPPAR_EPPA6_BOTH           (0x3000)
#define MCF5227_EPORT_EPPAR_EPPA7(x)             (((x)&0x3)<<0xE)
#define MCF5227_EPORT_EPPAR_EPPA7_LEVEL          (0)
#define MCF5227_EPORT_EPPAR_EPPA7_RISING         (0x4000)
#define MCF5227_EPORT_EPPAR_EPPA7_FALLING        (0x8000)
#define MCF5227_EPORT_EPPAR_EPPA7_BOTH           (0xC000)
#define MCF5227_EPORT_EPPAR_LEVEL                (0)
#define MCF5227_EPORT_EPPAR_RISING               (0x1)
#define MCF5227_EPORT_EPPAR_FALLING              (0x2)
#define MCF5227_EPORT_EPPAR_BOTH                 (0x3)

/* Bit definitions and macros for MCF5227_EPORT_EPDDR */
#define MCF5227_EPORT_EPDDR_EPDD1                (0x2)
#define MCF5227_EPORT_EPDDR_EPDD2                (0x4)
#define MCF5227_EPORT_EPDDR_EPDD3                (0x8)
#define MCF5227_EPORT_EPDDR_EPDD4                (0x10)
#define MCF5227_EPORT_EPDDR_EPDD5                (0x20)
#define MCF5227_EPORT_EPDDR_EPDD6                (0x40)
#define MCF5227_EPORT_EPDDR_EPDD7                (0x80)

/* Bit definitions and macros for MCF5227_EPORT_EPIER */
#define MCF5227_EPORT_EPIER_EPIE1                (0x2)
#define MCF5227_EPORT_EPIER_EPIE2                (0x4)
#define MCF5227_EPORT_EPIER_EPIE3                (0x8)
#define MCF5227_EPORT_EPIER_EPIE4                (0x10)
#define MCF5227_EPORT_EPIER_EPIE5                (0x20)
#define MCF5227_EPORT_EPIER_EPIE6                (0x40)
#define MCF5227_EPORT_EPIER_EPIE7                (0x80)

/* Bit definitions and macros for MCF5227_EPORT_EPDR */
#define MCF5227_EPORT_EPDR_EPD1                  (0x2)
#define MCF5227_EPORT_EPDR_EPD2                  (0x4)
#define MCF5227_EPORT_EPDR_EPD3                  (0x8)
#define MCF5227_EPORT_EPDR_EPD4                  (0x10)
#define MCF5227_EPORT_EPDR_EPD5                  (0x20)
#define MCF5227_EPORT_EPDR_EPD6                  (0x40)
#define MCF5227_EPORT_EPDR_EPD7                  (0x80)

/* Bit definitions and macros for MCF5227_EPORT_EPPDR */
#define MCF5227_EPORT_EPPDR_EPPD1                (0x2)
#define MCF5227_EPORT_EPPDR_EPPD2                (0x4)
#define MCF5227_EPORT_EPPDR_EPPD3                (0x8)
#define MCF5227_EPORT_EPPDR_EPPD4                (0x10)
#define MCF5227_EPORT_EPPDR_EPPD5                (0x20)
#define MCF5227_EPORT_EPPDR_EPPD6                (0x40)
#define MCF5227_EPORT_EPPDR_EPPD7                (0x80)

/* Bit definitions and macros for MCF5227_EPORT_EPFR */
#define MCF5227_EPORT_EPFR_EPF1                  (0x2)
#define MCF5227_EPORT_EPFR_EPF2                  (0x4)
#define MCF5227_EPORT_EPFR_EPF3                  (0x8)
#define MCF5227_EPORT_EPFR_EPF4                  (0x10)
#define MCF5227_EPORT_EPFR_EPF5                  (0x20)
#define MCF5227_EPORT_EPFR_EPF6                  (0x40)
#define MCF5227_EPORT_EPFR_EPF7                  (0x80)

/*------------------------------------------------------------------------*/
/*
** ADC  registers bit set.
*/

#define MCF5227_ADC_CTRL1_STOP0                     (1<<14)
#define MCF5227_ADC_CTRL1_START0                    (1<<13)
#define MCF5227_ADC_CTRL1_SYNC0                     (1<<12)
#define MCF5227_ADC_CTRL1_EOSIE0                    (1<<11)
#define MCF5227_ADC_CTRL1_ZCIE                      (1<<10)
#define MCF5227_ADC_CTRL1_LLMTIE                    (1<<9)
#define MCF5227_ADC_CTRL1_HLMTIE                    (1<<8)
#define MCF5227_ADC_CTRL1_CHNCFG_READ(x)            (((x)>>0x04)&0x0F)
#define MCF5227_ADC_CTRL1_CHNCFG_WRITE(x)           (((x)&0x0F)<<0x04)
#define MCF5227_ADC_CTRL2_DIV(x)                    (((x)&0x1F))
#define MCF5227_ADC_CTRL1_STOP1                     (1<<14)
#define MCF5227_ADC_CTRL1_START1                    (1<<13)
#define MCF5227_ADC_CTRL1_SYNC1                     (1<<12)
#define MCF5227_ADC_CTRL1_EOSIE1                    (1<<11)
#define MCF5227_ADC_CTRL1_SIMULT                    (1<<5)
#define MCF5227_ADC_ADZCC_ZCE0_WRITE(x)             (((x)&0x03)<<0x00)
#define MCF5227_ADC_ADZCC_ZCE1_WRITE(x)             (((x)&0x03)<<0x02)
#define MCF5227_ADC_ADZCC_ZCE2_WRITE(x)             (((x)&0x03)<<0x04)
#define MCF5227_ADC_ADZCC_ZCE3_WRITE(x)             (((x)&0x03)<<0x06)
#define MCF5227_ADC_ADZCC_ZCE4_WRITE(x)             (((x)&0x03)<<0x08)
#define MCF5227_ADC_ADZCC_ZCE5_WRITE(x)             (((x)&0x03)<<0x0A)
#define MCF5227_ADC_ADZCC_ZCE6_WRITE(x)             (((x)&0x03)<<0x0C)
#define MCF5227_ADC_ADZCC_ZCE7_WRITE(x)             (((x)&0x03)<<0x0E)
#define MCF5227_ADC_ADZCC_ZCE0_READ(x)              (((x)>>0x00)&0x03)
#define MCF5227_ADC_ADZCC_ZCE1_READ(x)              (((x)>>0x02)&0x03)
#define MCF5227_ADC_ADZCC_ZCE2_READ(x)              (((x)>>0x04)&0x03)
#define MCF5227_ADC_ADZCC_ZCE3_READ(x)              (((x)>>0x06)&0x03)
#define MCF5227_ADC_ADZCC_ZCE4_READ(x)              (((x)>>0x08)&0x03)
#define MCF5227_ADC_ADZCC_ZCE5_READ(x)              (((x)>>0x0A)&0x03)
#define MCF5227_ADC_ADZCC_ZCE6_READ(x)              (((x)>>0x0C)&0x03)
#define MCF5227_ADC_ADZCC_ZCE7_READ(x)              (((x)>>0x0E)&0x03)
#define MCF5227_ADC_ADLST1_SAMPLE0_WRITE(x)         (((x)&0x07)<<0)
#define MCF5227_ADC_ADLST1_SAMPLE1_WRITE(x)         (((x)&0x07)<<4)
#define MCF5227_ADC_ADLST1_SAMPLE2_WRITE(x)         (((x)&0x07)<<8)
#define MCF5227_ADC_ADLST1_SAMPLE3_WRITE(x)         (((x)&0x07)<<12)
#define MCF5227_ADC_ADLST2_SAMPLE4_WRITE(x)         (((x)&0x07)<<0)
#define MCF5227_ADC_ADLST2_SAMPLE5_WRITE(x)         (((x)&0x07)<<4)
#define MCF5227_ADC_ADLST2_SAMPLE6_WRITE(x)         (((x)&0x07)<<8)
#define MCF5227_ADC_ADLST2_SAMPLE7_WRITE(x)         (((x)&0x07)<<12)
#define MCF5227_ADC_ADSDIS_DS(x)                    (1<<(x))
#define MCF5227_ADC_ADSTAT_RDY(x)                   (1<<(x))
#define MCF5227_ADC_ADSTAT_HLMTI                    (1<<8)
#define MCF5227_ADC_ADSTAT_LLMTI                    (1<<9)
#define MCF5227_ADC_ADSTAT_ZCI                      (1<<10)
#define MCF5227_ADC_ADSTAT_EOSI0                    (1<<11)
#define MCF5227_ADC_ADSTAT_EOSI1                    (1<<12)
#define MCF5227_ADC_ADSTAT_CIP1                     (1<<14)
#define MCF5227_ADC_ADSTAT_CIP0                     (1<<15)
#define MCF5227_ADC_ADLSTAT_LLS(x)                  (1<<(x))
#define MCF5227_ADC_ADLSTAT_HLS(x)                  (1<<(8 +(x)))
#define MCF5227_ADC_ADZCSTAT_ZCS(x)                 (1<<(x))
#define MCF5227_ADC_ADRSLT_RSLT_READ(x)             (((x)>>3)&0x0FFF)
#define MCF5227_ADC_ADLLMT_LLMT_WRITE(x)            (((x)&0x0FFF)<<3)
#define MCF5227_ADC_ADHLMT_HLMT_WRITE(x)            (((x)&0x0FFF)<<3)
#define MCF5227_ADC_ADOFS_OFFSET_WRITE(x)           (((x)&0x0FFF)<<3)
#define MCF5227_ADC_POWER_PUDELAY_WRITE(x)          (((x)&0x3F)<<4)
#define MCF5227_ADC_POWER_PUDELAY_READ(x)           (((x)>>4)&0x3F)
#define MCF5227_ADC_POWER_PD(x)                     (1<<(x))
#define MCF5227_ADC_POWER_APD                       (1<<3)
#define MCF5227_ADC_POWER_PSTS(x)                   (1<<(10+(x)))
#define MCF5227_ADC_POWER_ASB                       (1<<15)
#define MCF5227_ADC_CAL_SEL_VREFL                   (1<<14)
#define MCF5227_ADC_CAL_SEL_VREFH                   (1<<15)

/*------------------------------------------------------------------------*/
/*
** GPT  registers bit set.
*/
#define MCF5227_GPT_GPTIOS_IOS(x)                   ((x)&0x0F)
#define MCF5227_GPT_GPCFORC_FOC(x)                  ((x)&0x0F)
#define MCF5227_GPT_GPTOC3M_OC3M(x)                 ((x)&0x0F)
 //     TBD


/*------------------------------------------------------------------------*/
/*
** PWM  registers bit set.
*/
 //     TBD

/*------------------------------------------------------------------------*/
/*
** CFM  registers bit set.
*/

//       TBD

/*------------------------------------------------------------------------*/
/*
** RNG  registers bit set.
*/

//      TBD


/*------------------------------------------------------------------------*/
/*
** FEC  registers bit set.
*/

//      TBD



/* Bit definitions and macros for MCF_RNG_RNGCR */
#define MCF5227_RNG_RNGCR_GO                     (0x1)
#define MCF5227_RNG_RNGCR_HA                     (0x2)
#define MCF5227_RNG_RNGCR_IM                     (0x4)
#define MCF5227_RNG_RNGCR_CI                     (0x8)

/* Bit definitions and macros for MCF_RNG_RNGSR */
#define MCF5227_RNG_RNGSR_SV                     (0x1)
#define MCF5227_RNG_RNGSR_LRS                    (0x2)
#define MCF5227_RNG_RNGSR_FUF                    (0x4)
#define MCF5227_RNG_RNGSR_EI                     (0x8)
#define MCF5227_RNG_RNGSR_OFL(x)                 (((x)&0xFF)<<0x8)
#define MCF5227_RNG_RNGSR_OFS(x)                 (((x)&0xFF)<<0x10)

/* Bit definitions and macros for MCF_RNG_RNGER */
#define MCF5227_RNG_RNGER_ENT(x)                 (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF_RNG_RNGOUT */
#define MCF5227_RNG_RNGOUT_RANDOM_OUTPUT(x)      (((x)&0xFFFFFFFF)<<0)

/*------------------------------------------------------------------------*/
/*
** SDRAM Controller Module
*/
#if 0
/* Bit definitions and macros for SDMR */
#define MCF5227_SDRAMC_SDMR_BNKAD_LMR           (0x00000000)
#define MCF5227_SDRAMC_SDMR_BNKAD_LEMR          (0x40000000)
#define MCF5227_SDRAMC_SDMR_BNKAD(x)            (((x)&0x00000003)<<30)
#define MCF5227_SDRAMC_SDMR_AD(x)               (((x)&0x00000FFF)<<18)
#define MCF5227_SDRAMC_SDMR_CMD                 (0x00010000)

/* Bit definitions and macros for SDCR */
#define MCF5227_SDRAMC_SDCR_MODE_EN             (0x80000000)
#define MCF5227_SDRAMC_SDCR_CKE                 (0x40000000)
#define MCF5227_SDRAMC_SDCR_DDR                 (0x20000000)
#define MCF5227_SDRAMC_SDCR_REF                 (0x10000000)
#define MCF5227_SDRAMC_SDCR_MUX(x)              (((x)&0x00000003)<<24)
#define MCF5227_SDRAMC_SDCR_RCNT(x)             (((x)&0x0000003F)<<16)
#define MCF5227_SDRAMC_SDCR_PS                  (0x00002000)
#define MCF5227_SDRAMC_SDCR_DQS_OE(x)           (((x)&0x00000003)<<10)
#define MCF5227_SDRAMC_SDCR_IREF                (0x00000004)
#define MCF5227_SDRAMC_SDCR_IPALL               (0x00000002)

/* Bit definitions and macros for SDCFG1 */
#define MCF5227_SDRAMC_SDCFG1_SRD2RW(x)         (((x)&0x0000000F)<<28)
#define MCF5227_SDRAMC_SDCFG1_SWT2RD(x)         (((x)&0x00000007)<<24)
#define MCF5227_SDRAMC_SDCFG1_RDLAT(x)          (((x)&0x0000000F)<<20)
#define MCF5227_SDRAMC_SDCFG1_ACT2RW(x)         (((x)&0x00000007)<<16)
#define MCF5227_SDRAMC_SDCFG1_PRE2ACT(x)        (((x)&0x00000007)<<12)
#define MCF5227_SDRAMC_SDCFG1_REF2ACT(x)        (((x)&0x0000000F)<<8)
#define MCF5227_SDRAMC_SDCFG1_WTLAT(x)          (((x)&0x00000007)<<4)

/* Bit definitions and macros for SDCFG2 */
#define MCF5227_SDRAMC_SDCFG2_BRD2PRE(x)        (((x)&0x0000000F)<<28)
#define MCF5227_SDRAMC_SDCFG2_BWT2RW(x)         (((x)&0x0000000F)<<24)
#define MCF5227_SDRAMC_SDCFG2_BRD2WT(x)         (((x)&0x0000000F)<<20)
#define MCF5227_SDRAMC_SDCFG2_BL(x)             (((x)&0x0000000F)<<16)

#define MCF5227_SDRAMC_SDBAR_BASE(x)            ((x)&0xFFFC0000)

#define MCF5227_SDRAMC_SDMR_BASE_4G             (0xFFFC0000)
#define MCF5227_SDRAMC_SDMR_BASE_2G             (0x7FFC0000)
#define MCF5227_SDRAMC_SDMR_BASE_1G             (0x3FFC0000)
#define MCF5227_SDRAMC_SDMR_BASE_1024M          (0x3FFC0000)
#define MCF5227_SDRAMC_SDMR_BASE_512M           (0x1FFC0000)
#define MCF5227_SDRAMC_SDMR_BASE_256M           (0x0FFC0000)
#define MCF5227_SDRAMC_SDMR_BASE_128M           (0x07FC0000)
#define MCF5227_SDRAMC_SDMR_BASE_64M            (0x03FC0000)
#define MCF5227_SDRAMC_SDMR_BASE_32M            (0x01FC0000)
#define MCF5227_SDRAMC_SDMR_BASE_16M            (0x00FC0000)
#define MCF5227_SDRAMC_SDMR_BASE_8M             (0x007C0000)
#define MCF5227_SDRAMC_SDMR_BASE_4M             (0x003C0000)
#define MCF5227_SDRAMC_SDMR_BASE_2M             (0x001C0000)
#define MCF5227_SDRAMC_SDMR_BASE_1M             (0x000C0000)
#define MCF5227_SDRAMC_SDMR_BASE_1024K          (0x000C0000)
#define MCF5227_SDRAMC_SDMR_BASE_512K           (0x00040000)
#define MCF5227_SDRAMC_SDMR_BASE_256K           (0x00000000)
#define MCF5227_SDRAMC_SDMR_WP                  (0x00000100)
#define MCF5227_SDRAMC_SDMR_V                   (0x00000001)

/* Bit definitions and macros for SDCS */
#define MCF5227_SDRAMC_SDCS_CSSZ(x)             (((x)&0x0000001F)<<0)
#define MCF5227_SDRAMC_SDCS_BASE(x)             (((x)&0x00000FFF)<<20)
#define MCF5227_SDRAMC_SDCS_BA(x)               ((x)&0xFFF00000)
#define MCF5227_SDRAMC_SDCS_CSSZ_DIABLE         (0x00000000)
#define MCF5227_SDRAMC_SDCS_CSSZ_1MBYTE         (0x00000013)
#define MCF5227_SDRAMC_SDCS_CSSZ_2MBYTE         (0x00000014)
#define MCF5227_SDRAMC_SDCS_CSSZ_4MBYTE         (0x00000015)
#define MCF5227_SDRAMC_SDCS_CSSZ_8MBYTE         (0x00000016)
#define MCF5227_SDRAMC_SDCS_CSSZ_16MBYTE        (0x00000017)
#define MCF5227_SDRAMC_SDCS_CSSZ_32MBYTE        (0x00000018)
#define MCF5227_SDRAMC_SDCS_CSSZ_64MBYTE        (0x00000019)
#define MCF5227_SDRAMC_SDCS_CSSZ_128MBYTE       (0x0000001A)
#define MCF5227_SDRAMC_SDCS_CSSZ_256MBYTE       (0x0000001B)
#define MCF5227_SDRAMC_SDCS_CSSZ_512MBYTE       (0x0000001C)
#define MCF5227_SDRAMC_SDCS_CSSZ_1GBYTE         (0x0000001D)
#define MCF5227_SDRAMC_SDCS_CSSZ_2GBYTE         (0x0000001E)
#define MCF5227_SDRAMC_SDCS_CSSZ_4GBYTE         (0x0000001F)

#endif
/*------------------------------------------------------------------------*/
/*
** Chip select macros
*/

#define MCF5227_CS_CSAR_BA(a)                   (uint_16)(((a)&0xFFFF0000)>>16)

#define MCF5227_CS_CSMR_BAM_4G                  (0xFFFF0000)
#define MCF5227_CS_CSMR_BAM_2G                  (0x7FFF0000)
#define MCF5227_CS_CSMR_BAM_1G                  (0x3FFF0000)
#define MCF5227_CS_CSMR_BAM_1024M               (0x3FFF0000)
#define MCF5227_CS_CSMR_BAM_512M                (0x1FFF0000)
#define MCF5227_CS_CSMR_BAM_256M                (0x0FFF0000)
#define MCF5227_CS_CSMR_BAM_128M                (0x07FF0000)
#define MCF5227_CS_CSMR_BAM_64M                 (0x03FF0000)
#define MCF5227_CS_CSMR_BAM_32M                 (0x01FF0000)
#define MCF5227_CS_CSMR_BAM_16M                 (0x00FF0000)
#define MCF5227_CS_CSMR_BAM_8M                  (0x007F0000)
#define MCF5227_CS_CSMR_BAM_4M                  (0x003F0000)
#define MCF5227_CS_CSMR_BAM_2M                  (0x001F0000)
#define MCF5227_CS_CSMR_BAM_1M                  (0x000F0000)
#define MCF5227_CS_CSMR_BAM_1024K               (0x000F0000)
#define MCF5227_CS_CSMR_BAM_512K                (0x00070000)
#define MCF5227_CS_CSMR_BAM_256K                (0x00030000)
#define MCF5227_CS_CSMR_BAM_128K                (0x00010000)
#define MCF5227_CS_CSMR_BAM_64K                 (0x00000000)
#define MCF5227_CS_CSMR_WP                      (0x00000100)
#define MCF5227_CS_CSMR_AM                      (0x00000040)
#define MCF5227_CS_CSMR_CI                      (0x00000020)
#define MCF5227_CS_CSMR_SC                      (0x00000010)
#define MCF5227_CS_CSMR_SD                      (0x00000008)
#define MCF5227_CS_CSMR_UC                      (0x00000004)
#define MCF5227_CS_CSMR_UD                      (0x00000002)
#define MCF5227_CS_CSMR_V                       (0x00000001)

/* Bit definitions and macros for Chip-Select Control Registers */
#define MCF5227_CS_CSCR_SWS(x)                  (((x)&0x0000003F)<<26)
#define MCF5227_CS_CSCR_SWSEN                   (0x00800000)
#define MCF5227_CS_CSCR_ASET(x)                 (((x)&0x00000003)<<20)
#define MCF5227_CS_CSCR_RDAH(x)                 (((x)&0x00000003)<<18)
#define MCF5227_CS_CSCR_WRAH(x)                 (((x)&0x00000003)<<16)
#define MCF5227_CS_CSCR_WS(x)                   (((x)&0x0000003F)<<10)
#define MCF5227_CS_CSCR_SBM                     (0x00000200)
#define MCF5227_CS_CSCR_AA                      (0x00000100)
#define MCF5227_CS_CSCR_PS_8                    (0x00000040)
#define MCF5227_CS_CSCR_PS_16                   (0x00000080)
#define MCF5227_CS_CSCR_PS_32                   (0x00000000)
#define MCF5227_CS_CSCR_BEM                     (0x00000020)
#define MCF5227_CS_CSCR_BSTR                    (0x00000010)
#define MCF5227_CS_CSCR_BSTW                    (0x00000008)


/*------------------------------------------------------------------------*/
/*
**                      TYPE DEFINITIONS
*/

/*
** MCF5227_TCD_STRUCT
** This structure defines what one Transfer Control Descriptor look like
*/
typedef struct mcf5227_tcd_struct
{
   uint_32 SADDR;               // Source Address
   uint_16 ATTR;                // Transfer Attrbutes
   uint_16 SOFF;                // Signed Source Address Offset
   uint_32 NBYTES;              // Minor Byte Count
   uint_32 SLAST;               // Last Source Address Adjustment
   uint_32 DADDR;               // Destination Address
   uint_16 CITER;               // Current Minor Loop Link, Major Loop Count
   uint_16 DOFF;                // Signed Destination Address Offset
   uint_32 DLAST_SGA;           // Last Destination Address Adjustment/Scatter Gather Address
   uint_16 BITER;               // Beginning Minor Loop Link, Major Loop Count
   uint_16 CSR;                 // Control and Status Register
} MCF5227_TCD_STRUCT, _PTR_ MCF5227_TCD_STRUCT_PTR;
typedef volatile struct mcf5227_tcd_struct _PTR_ VMCF5227_TCD_STRUCT_PTR;

/*
** MCF5227_DMA_STRUCT
** This structure defines what one DMA registers look like
*/
typedef struct mcf5227_dma_struct
{
   uint_32 CR;                  // eDMA Control Register
   uint_32 ES;                  // eDMA Error Status Register
   uchar   filler1[6];
   uint_16 ERQ;                 // eDMA Enable Request Register
   uchar   filler2[6];
   uint_16 EEI;                 // eDMA Enable Error Interrupt Register
   uchar   SERQ;                // eDMA Set Enable Request Register
   uchar   CERQ;                // eDMA Clear Enable Request Register
   uchar   SEEI;                // eDMA Set Enable Error Interrupt Register
   uchar   CEEI;                // eDMA Clear Enable Error Interrupt Register
   uchar   CINT;                // eDMA Clear Interrupt Request Register
   uchar   CERR;                // eDMA Clear Error Register
   uchar   SSRT;                // eDMA Set START Bit Register
   uchar   CDNE;                // eDMA Clear DONE Status Bit Register
   uchar   filler3[6];
   uint_16 INT;             // eDMA Interrupt Request Register
   uchar   filler4[6];
   uint_16 ERR;             // eDMA Error Register
   uchar   filler5[208];
   uchar   DCHPRI[MCF5227_NUM_DMAS];    // eDMA Channel Priority Registers
   uchar   filler6[3823];
   MCF5227_TCD_STRUCT TCD[MCF5227_NUM_DMAS]; // Transfer Control Descriptors
} MCF5227_DMA_STRUCT, _PTR_ MCF5227_DMA_STRUCT_PTR;
typedef volatile struct mcf5227_dma_struct _PTR_ VMCF5227_DMA_STRUCT_PTR;

/*
** MCF5227_I2C_STRUCT
** I2C registers
*/
typedef struct mcf5227_i2c_struct
{
   uchar    I2ADR;          // I2C address register
   uchar    filler1[3];
   uchar    I2FDR;          // I2C frequency divider register
   uchar    filler2[3];
   uchar    I2CR;           // I2C control register
   uchar    filler3[3];
   uchar    I2SR;           // I2C status register
   uchar    filler4[3];
   uchar    I2DR;           // I2C data I/O register
} MCF5227_I2C_STRUCT, _PTR_ MCF5227_I2C_STRUCT_PTR;
typedef volatile struct mcf5227_i2c_struct _PTR_ VMCF5227_I2C_STRUCT_PTR;

/*
** MCF5227_UART_STRUCT
** This structure defines what one uart register look like
*/
typedef union mcf5227_uart_struct
{
   struct  {
      uchar UMR;             // UART Mode Register
      uchar filler1[3];
      uchar USR;             // UART Status Register
      uchar filler2[3];
      uchar UCR;             // UART Command Register
      uchar filler3[3];
      uchar URB;             // UART Receiver Buffers
      uchar filler4[3];
      uchar UIPCR;           // UART Input Port Change Register
      uchar filler5[3];
      uchar UISR;            // UART Interrupt Status Register
      uchar filler6[3];
      uchar UBG1;            // UART Baud Rate Generator Register 1
      uchar filler7[3];
      uchar UBG2;            // UART Baud Rate Generator Register 2
      uchar filler8[23];
      uchar UIP;             // UART Input Port Register
      uchar filler9[3];
      uchar UOP1;            // UART Output Port Bit Set Command Register 1
      uchar filler10[3];
      uchar UOP0;            // UART Output Port Bit Set Command Register 2
      uchar filler11[16323];
   } READ;
   struct  {
      uchar UMR;             // UART Mode Register
      uchar filler1[3];
      uchar UCSR;            // UART Clock Select Register
      uchar filler2[3];
      uchar UCR;             // UART Command Register
      uchar filler3[3];
      uchar UTB;             // UART Transmit Buffers
      uchar filler4[3];
      uchar UACR;            // UART Auxillary Control Register
      uchar filler5[3];
      uchar UIMR;            // UART Interrupt Mask Register
      uchar filler6[3];
      uchar UBG1;            // UART Baud Rate Generator Register 1
      uchar filler7[3];
      uchar UBG2;            // UART Baud Rate Generator Register 2
      uchar filler8[23];
      uchar UIP;             // UART Input Port Register
      uchar filler9[3];
      uchar UOP1;            // UART Output Port Bit Set Command Register 1
      uchar filler10[3];
      uchar UOP0;            // UART Output Port Bit Set Command Register 2
      uchar filler11[16323];
   } WRITE;
} MCF5227_UART_STRUCT, _PTR_ MCF5227_UART_STRUCT_PTR;

/*
** MCF5227_QSPI_STRUCT
** QSPI
*/
typedef struct mcf5227_qspi_struct
{
   uint_16 QMR;                 // QSPI mode register
   uint_16 filler1;
   uint_16 QDLYR;               // QSPI delay register
   uint_16 filler2;
   uint_16 QWR;                 // QSPI wrap register
   uint_16 filler3;
   uint_16 QIR;                 // QSPI interrupt register
   uint_16 filler4;
   uint_16 QAR;                 // QSPI address register
   uint_16 filler5;
   uint_16 QDR;                 // QSPI data register
} MCF5227_QSPI_STRUCT, _PTR_ MCF5227_QSPI_STRUCT_PTR;
typedef volatile struct mcf5227_qspi_struct _PTR_ VMCF5227_QSPI_STRUCT_PTR;

/*
** MCF5227_TIMER_STRUCT
** This structure defines what one timer register look like
*/
typedef struct mcf5227_dma_timer_struct
{
   uint_16  DTMR;           // DMA Timer mode register
   uchar    DTXTMR;         // DMA Timer extended mode register
   uchar    DTER;           // DMA Timer event register
   uint_32  DTRR;           // DMA Timer reference register
   uint_32  DTCR;           // DMA Timer capture register
   uint_32  DTCN;           // DMA Timer counter register
   uchar   filler1[16368];
} MCF5227_DMA_TIMER_STRUCT, _PTR_ MCF5227_DMA_TIMER_STRUCT_PTR;
typedef volatile struct mcf5227_dma_timer_struct _PTR_ VMCF5227_DMA_TIMER_STRUCT_PTR;

/*
** MCF5227_GPIO_STRUCT
** GPIO Registers
*/
typedef struct mcf5227_gpio_struct
{
    /* Port Output Data Registers */
    uchar   PODR_BE, PODR_CS, PODR_FBCTL, PODR_I2C; 
    uchar   fillerA;
    uchar   PODR_UART, PODR_DSPI, PODR_TIMER;
    uchar   PODR_LCDCTL, PODR_LCDDATAH, PODR_LCDDATAM, PODR_LCDDATAL;
    /* Port Data Direction Registers */
    uchar   PDDR_BE, PDDR_CS, PDDR_FBCTL, PDDR_I2C; 
    uchar   fillerB;
    uchar   PDDR_UART, PDDR_DSPI, PDDR_TIMER;
    uchar   PDDR_LCDCTL, PDDR_LCDDATAH, PDDR_LCDDATAM, PDDR_LCDDATAL;
    /* Port Pin Data/Set Data Registers */
    uchar   PPDSDR_BE, PPDSDR_CS, PPDSDR_FBCTL, PPDSDR_I2C; 
    uchar   fillerC;
    uchar   PPDSDR_UART, PPDSDR_DSPI, PPDSDR_TIMER;
    uchar   PPDSDR_LCDCTL, PPDSDR_LCDDATAH, PPDSDR_LCDDATAM, PPDSDR_LCDDATAL;
    /* Port Clear Output Data Registers */
    uchar   PCLRR_BE, PCLRR_CS, PCLRR_FBCTL, PCLRR_I2C; 
    uchar   fillerD;
    uchar   PCLRR_UART, PCLRR_DSPI, PCLRR_TIMER;
    uchar   PCLRR_LCDCTL, PCLRR_LCDDATAH, PCLRR_LCDDATAM, PCLRR_LCDDATAL;
    /* Port Pin Assignment Registers */
    uchar   PAR_BE, PAR_CS, PAR_FBCTL, PAR_I2C; 
    uint_16 PAR_UART;
    uchar   PAR_DSPI, PAR_TIMER;
    uchar   PAR_LCDCTL, PAR_IRQ;
    uchar   fillerE[0x403c - 0x403a];
    uint_32 PAR_LCDH, PAR_LCDL;
    /* Mode Select Control Registers */
    uchar   MSCR_FLEXBUS, MSCR_SDRAM;
    /* Drive Strength Control Registers */
    uchar   DSCR_DSPI, DSCR_TIMER, DSCR_I2C, DSCR_LCD, DSCR_DEBUG, DSCR_CLKRST, DSCR_IRQ, DSCR_UART; 
} MCF5227_GPIO_STRUCT, _PTR_ MCF5227_GPIO_STRUCT_PTR;
typedef volatile struct mcf5227_gpio_struct _PTR_ VMCF5227_GPIO_STRUCT_PTR;

/*
** MCF5227_CCM_STRUCT
** ColdFire Integration Module
*/
typedef struct mcf5227_ccm_struct
{
   uchar    filler1[4];
   uint_16  CCR;            // Chip Configuration Register
   uchar    filler2;
   uchar    LPCR;           // Low-Power Control Register
   uint_16  RCON;           // Reset Configuration Register
   uint_16  CIR;            // Chip Identification Register
   uchar    filler3[4];
   uint_16  MISCCR;         // Miscellaneous Control Register
   uint_16  CDR;            // Clock Divider Register
   uint_16  UOCSR;          // USB OTG Status Register
   uchar    filler4[2];
   uint_16  SBFSR;          // Serial Boot Facility Status Register
   uint_16  SBFCR;          // Serial Boot Facility Control Register
} MCF5227_CCM_STRUCT, _PTR_ MCF5227_CCM_STRUCT_PTR;
typedef volatile struct mcf5227_ccm_struct _PTR_ VMCF5227_CCM_STRUCT_PTR;

/*
** MCF5227_CLK_STRUCT
** Clock module registers
*/
typedef struct mcf5227_clk_struct
{
   uint_32  PCR;         // PLL Control Register
   uint_32  PSR;         // PLL Status Register
} MCF5227_CLK_STRUCT, _PTR_ MCF5227_CLK_STRUCT_PTR;
typedef volatile struct mcf5227_clk_struct _PTR_ VMCF5227_CLK_STRUCT_PTR;

/*
** MCF5227_EPORT_STRUCT
** Edge port registers
*/
typedef struct mcf5227_eport_struct
{
   uint_16  EPPAR;          // EPORT pin assignment register
   uchar    EPDDR;          // EPORT data direction register
   uchar    EPIER;          // EPORT interrupt enable register
   uchar    EPDR;           // EPORT data register
   uchar    EPPDR;          // EPORT pin data register
   uchar    EPFR;           // EPORT flag register
} MCF5227_EPORT_STRUCT, _PTR_ MCF5227_EPORT_STRUCT_PTR;
typedef volatile struct mcf5227_eport_struct _PTR_ VMCF5227_EPORT_STRUCT_PTR;

/*
** MCF5227_ADC_STRUCT                                                                   
** Touchscreen / ADC registers
*/
typedef struct mcf5227_adc_struct
{
   uint_32  CR;         // ASP Control Register
   uint_32  SET;        // ASP Sampling Setting Register
   uint_32  TIM;        // A/D Sampling Timing Register
   uint_32  ICR;        // ASP Interrupt / DMA Control Register

   uint_32  ISR;        // ASP Interrupt Status Register
   uint_32  SFIFO;      // ASP Sample FIFO
   uint_32  FIFOP;      // ASP FIFO Pointer
   uint_32  CLKDIV;      // ASP Clock Divider Register
} MCF5227_ADC_STRUCT, _PTR_ MCF5227_ADC_STRUCT_PTR;
typedef volatile struct mcf5227_adc_struct _PTR_ VMCF5227_ADC_STRUCT_PTR;

/*
** MCF5227_PWM_STRUCT                                                              
** PWM registers...
** IMPORTANT !!!
** A 32-bit access to any of these registers results in a bus transfer error!
** Ref: mcf52237 Reference Manual, section 24.2 "PWM Module / Memory Map"
*/
typedef struct mcf5227_pwm_struct
{   
   uchar    filer[0x20];
   uchar    PWME;            // PWM Enable Register
   uchar    PWMPOL;          // PWM Polarity Register
   uchar    PWMCLK;          // PWM Clock Select Register
   uchar    PWMPRCLK;        // PWM Prescale Clock Select Register
   uchar    PWMCAE;          // PWM Center Align Enable Register
   uchar    PWMCTL;          // PWM Control Register
   uchar    filler1[2];
   uchar    PWMSCLA;         // PWM Scale A Register
   uchar    PWMSCLB;         // PWM Scale B Register
   uchar    filler2[2];
   uchar    PWMCNT[8];       // PWM Channel Counter Registers (0-7)
   uchar    PWMPER[8];       // PWM Channel Period Registers (0-7)
   uchar    PWMDTY[8];       // PWM Channel Duty Register (0-7)
   uchar    PWMSDN;          // PWM Shutdown Register
} MCF5227_PWM_STRUCT, _PTR_ MCF5227_PWM_STRUCT_PTR;
typedef volatile struct mcf5227_pwm_struct _PTR_ VMCF5227_PWM_STRUCT_PTR;

/*
** MCF5227_SSI_STRUCT
** SSI controller
*/
typedef struct mcf5227_ssi_struct
{
   uint_32 TX0;                 // Transmit Data Register 0
   uint_32 TX1;                 // Transmit Data Register 1
   uint_32 RX0;                 // Receive Data Register 0
   uint_32 RX1;                 // Receive Data Register 1
   uint_32 CR;                  // Control Register
   uint_32 ISR;                 // Interrupt Status Register
   uint_32 IER;                 // Interrupt Enable Register
   uint_32 TCR;                 // Transmit Configuration Register
   uint_32 RCR;                 // Receive Configuration Register
   uint_32 CCR;                 // Clock Control Register
   uchar fillerA[4];
   uint_32 FCSR;                // FIFO Control/Status Register
   uchar fillerB[8];
   uint_32 ACR;                 // AC97 Control Register
   uint_32 ACADD;               // AC97 Command Address Register
   uint_32 ACDAT;               // Command Data Register
   uint_32 ATAG;                // AC97 Tag Register
   uint_32 TMASK;               // Transmit Time Slot Mask Register
   uint_32 RMASK;               // Receive Time Slot Mask Register
   
} MCF5227_SSI_STRUCT, _PTR_ MCF5227_SSI_STRUCT_PTR;
typedef volatile struct mcf5227_ssi_struct _PTR_ VMCF5227_SSI_STRUCT_PTR;

/*
** MCF5227_LCD_STRUCT
** LCD controller
*/
typedef struct mcf5227_lcd_struct
{
   uint_32 SSAR;                 //Screen Start Address Register
   uint_32 SR;                   //Size Register
   uint_32 VPW;                  //Virtual Page Register
   uint_32 CPR;                  //Cursor Position Register
   uint_32 CWHB;                 //Cursor Width Height and Blink Register
   uint_32 CCMR;                 //Color Cursor Mapping Register
   uint_32 PCR;                  //Panel Configuration Register
   uint_32 HCR;                  //Horizontal Configuration Register
   uint_32 VCR;                  //Vertical Configuration Register
   uint_32 POR;                  //Panning Offset Register
   uint_32 SCR;                  //Sharp Configuration Register
   uint_32 PCCR;                 //PWM Contrast Control Register
   uint_32 DCR;                  //DMA Control Register
   uint_32 RMCR;                 //Refresh Mode Control Register
   uint_32 ICR;                  //LCD Interrupt Configration Register
   uint_32 IER;                  //LCD Interrupt Enable Register
   uint_32 ISR;                  //LCD Interrupt Status Register
   uchar fillerA[12];
   uint_32 GWSAR;                //Graphic Window Start Address Register
   uint_32 GWSR;                 //Graphic Window Size Register
   uint_32 GWVPW;                //Graphic Window Virtual Page Width Register
   uint_32 GWPOR;                //Graphic Window Panning Offset Register
   uint_32 GWPR;                 //Graphic Window Position Register
   uint_32 GWCR;                 //Graphic Window Control Register 
   uint_32 GWDCR;                //Graphic Window DMA Control Register
   uchar fillerB[0x800-0x06c];
   uint_32 BGLUT[256];           //Background Look-up Table
   uint_32 GWLUT[256];           //Graphic Window Look-up Table
   
} MCF5227_LCD_STRUCT, _PTR_ MCF5227_LCD_STRUCT_PTR;
typedef volatile struct mcf5227_lcd_struct _PTR_ VMCF5227_LCD_STRUCT_PTR;

/*
** MCF5227_STRUCT
** This structure defines the memory/registers provided by the MCF5227
*/
typedef struct mcf5227_struct
{
   /* System Control Module, first part */
   uint_32  MPR;        // Master privilege register
   uchar    fillerA[0x00020 - 0x00004];
   uint_32  PACRA;          // Peripheral Access Control Register A
   uint_32  PACRB;          // Peripheral Access Control Register B
   uint_32  PACRC;          // Peripheral Access Control Register C
   uint_32  PACRD;          // Peripheral Access Control Register D
   uchar    fillerB[0x00040 - 0x00030];
   uint_32  PACRE;          // Peripheral Access Control Register E
   uint_32  PACRF;          // Peripheral Access Control Register F
   uint_32  PACRG;          // Peripheral Access Control Register G
   uchar    fillerC[0x00050 - 0x0004c];
   uint_32  PACRI;          // Peripheral Access Control Register I
   uchar                     filerA[0xfc004000 - (0xfc000054)];

//  MCF_CROSSBAR_STRUCT
   uchar                     filerB[0xfc008000 - (0xfc004000 + 0)];
   MCF5XXX_FB_STRUCT         FB[MCF5227_NUM_FB_CS]; // FlexBus Module
   uchar                     filerC[0xfc020000 - (0xfc008000 + MCF5227_NUM_FB_CS * sizeof(MCF5XXX_FB_STRUCT))];
   MCF52XX_FCAN_STRUCT       FCAN;            // FlexCAN Module
   uchar                     filerD[0xfc03c000 - (0xfc020000 + sizeof(MCF52XX_FCAN_STRUCT))];
   MCF52XX_RTC_STRUCT        RTC;             // Real Time Clock Module
   uchar                     filerE[0xfc040000 - (0xfc03c000 + sizeof(MCF52XX_RTC_STRUCT))];

   /* System Control Module, first part */
   uchar    fillerF[0xfc040013 - 0xfc040000];
   uchar    WCR;            // Wakeup Control Register
   uchar    fillerG[0x40016 - 0x40014];
   uint_16  CWCR;            // Core Watchdog Control Register
   uchar    fillerH[0x4001b - 0x40018];
   uchar    CWSR;            // Core Watchdog Service Register
   uchar    fillerI[0x4001f - 0x4001c];
   uchar    SCMISR;          // SCM Interrupt Status Register
   uchar    fillerJ[0x40024 - 0x40020];
   uint_32  BCR;             // Burst Configuration Register
   uchar    fillerK[0x40070 - 0x40028];
   uint_32  CFADR;           // Core Fault Address Register
   uchar    fillerL[0x40075 - 0x40074];
   uchar    CFIER;           // Core Fault Interrupt Enable Register
   uchar    CFLOC;           // Core Fault Location Register
   uchar    CFATR;           // Core Fault Attributes Register
   uint_32  CFDTR;           // Core Fault Data Register
   uchar fillerM[0xfc044000 - 0xfc04007c];

   MCF5227_DMA_STRUCT        DMA;             // eDMA Controller
   uchar fillerN[0xfc048000 - (0xfc044000 + sizeof(MCF5227_DMA_STRUCT))];
   MCF5227_ICTRL_STRUCT     ICTRL[2];           // Interrupt Controller 0 and 1
   uchar fillerO[0xfc0540e0 - (0xfc048000 + 2 * sizeof(MCF5227_ICTRL_STRUCT))];
   uchar                    GSWIACK;         // Global Software Interrupt Acknowledge Register
   MCF5227_IACK_STRUCT      GIACK;           // Global Level Interrupt Acknowledge Registers
   uchar fillerP[0xfc058000 - (0xfc0540e0 + 1 + sizeof(MCF5227_IACK_STRUCT))];
   MCF5227_I2C_STRUCT        I2C;              // I2C Registers
   uchar fillerQ[0xfc05c000 - (0xfc058000 + sizeof(MCF5227_I2C_STRUCT))];
   MCF5XXX_DSPI_STRUCT       DSPI;             // SPI Registers
   uchar fillerR[0xfc060000 - (0xfc05c000 + sizeof(MCF5XXX_DSPI_STRUCT))];
   MCF5227_UART_STRUCT       UART[MCF5227_NUM_UARTS];  // UARTs
   uchar fillerS[0xfc070000 - (0xfc060000 + MCF5227_NUM_UARTS * sizeof(MCF5227_UART_STRUCT))];
   MCF5227_DMA_TIMER_STRUCT  DMA_TIMER[MCF5227_NUM_DMA_TIMERS]; // DMA Timers
   MCF5XXX_PIT_STRUCT        PIT[MCF5227_NUM_TIMERS];   // Programmable Interrupt Timers
   uchar fillerT[0xfc090000 - (0xfc080000 + MCF5227_NUM_TIMERS * sizeof(MCF5XXX_PIT_STRUCT))];
   MCF5227_PWM_STRUCT        PWM;              // PWM Controller
   uchar fillerU[0xfc094000 - (0xfc090000 + sizeof(MCF5227_PWM_STRUCT))];
   MCF5227_EPORT_STRUCT      EPORT[1];         // Edge Port 0
   uchar fillerV[0xfc0a0000 - (0xfc094000 + sizeof(MCF5227_EPORT_STRUCT))];
   MCF5227_CCM_STRUCT        CCM;              // CCM, Reset Controller, Power Management
   uchar fillerW[0xfc0a4000 - (0xfc0a0000 + sizeof(MCF5227_CCM_STRUCT))];
   MCF5227_GPIO_STRUCT       GPIO;             // GPIO Controller
   uchar fillerX[0xfc0a8000 - (0xfc0a4000 + sizeof(MCF5227_GPIO_STRUCT))];
   MCF5227_ADC_STRUCT        ADC;              // A/D Controller + Touchscreen
   uchar fillerY[0xfc0ac000 - (0xfc0a8000 + sizeof(MCF5227_ADC_STRUCT))];
   MCF5227_LCD_STRUCT        LCD;              // LCD Controller
   uchar fillerZ[0xfc0b0000 - (0xfc0ac000 + sizeof(MCF5227_LCD_STRUCT))];
   MCF5XXX_USBOTG_STRUCT     USBOTG;           // USB On-The-Go Controller
   uchar filler0[0xfc0b8000 - (0xfc0b0000 + sizeof(MCF5XXX_USBOTG_STRUCT))];
   MCF5XXX_SDRAM_CTRL_STRUCT   SDRAMC;            // SDRAM
   uchar filler1[0xfc0bc000 - (0xfc0b8000 + sizeof(MCF5XXX_SDRAM_CTRL_STRUCT))];
   MCF5227_SSI_STRUCT        SSI;            // SSI
   uchar filler2[0xfc0c0000 - (0xfc0bc000 + sizeof(MCF5227_SSI_STRUCT))];
   MCF5227_CLK_STRUCT        PLL;            // PLL (CLK Controller)
} MCF5227_STRUCT, _PTR_ MCF5227_STRUCT_PTR;
typedef volatile struct mcf5227_struct _PTR_ VMCF5227_STRUCT_PTR;

/*
** PSP_SUPPORT_STRUCT
** This structure is used to maintain the PSP support information
*/
typedef struct psp_support_struct
{
   uint_32 ACR_VALS[MCF5227_NUM_ACRS];
//   uint_32 ACR_COUNT;   // How many ACRs set so far
   uint_32 Reserved;

} PSP_SUPPORT_STRUCT, _PTR_ PSP_SUPPORT_STRUCT_PTR;

/*------------------------------------------------------------------------*/
/*
**                      FUNCTION PROTOTYPES AND GLOBAL EXTERNS
*/

extern volatile uint_32 _psp_saved_cacr;
extern volatile uint_32 _psp_saved_acr0;
extern volatile uint_32 _psp_saved_acr1;
extern          uchar   __KERNEL_DATA_VERIFY_ENABLE[]; // CR1327

extern void    _mcf5227_initialize_support(uint_32);

extern void    _mcf5227_cache_enable(uint_32);
extern void    _mcf5227_cache_disable(void);
extern void    _mcf5227_icache_invalidate(void);
extern void    _mcf5227_dcache_invalidate(void);

extern void    _icache_invalidate_mlines(pointer,uint_32,uint_32);
extern void    _dcache_flush_invalidate_mlines(pointer,uint_32,uint_32,uint_32,uint_32);

extern void    __psp_enable_acrs(uint_32_ptr);
extern void    __psp_clear_acrs(void);

void _psp_dcache_flush_all(uint_32, uint_32, uint_32);
void _dcache_flush(pointer, uint_32, uint_32);

#endif //__ASM__

#ifdef __cplusplus
}
#endif

#endif // __mcf5227_h__
/* EOF */
