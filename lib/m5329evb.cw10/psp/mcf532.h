/**HEADER********************************************************************
* 
* Copyright (c) 2008 Freescale Semiconductor;
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
* $FileName: mcf532.h$
* $Version : 3.7.2.0$
* $Date    : Feb-7-2011$
*
* Comments:
*
*   This file contains the type definitions for the mcf5329 processors.
*
*END************************************************************************/

#ifndef __mcf5329_h__
#define __mcf5329_h__

#define __mcf5329_h__version "$Version:3.7.2.0$"
#define __mcff5329__date    "$Date:Feb-7-2011$"

#ifndef __ASM__

/* Include registers for modules common to all Coldfire processors */

#include <mcf5xxx_fec.h>         /* FEC    */
#include <mcf53xx_fcan.h>        /* FCAN   */
#include <mcf53xx_rtc.h>         /* RTC    */
#include <mcf53xx_ictl.h>        /* CTRL   */   
#include <mcf5xxx_pit.h>         /* PIT    */
#include <mcf53xx_sdramc.h>      /* SDRAM  */
#include <mcf53xx_uart.h>        /* UART   */
#include <mcf5xxx_fb.h>          /* FlexBus*/
#include <mcf53xx_ccm.h>         /* CCM    */
#include <mcf53xx_i2c.h>         /* I2C    */
/*#include <mcf53xx_sim.h>       /* SIM    */
#include <mcf53xx_dma.h>         /* DMA    */
#include <mcf5xxx_qspi.h>        /* QSPI   */
#include <mcf53xx_eport.h>       /* Eport  */
#include <mcf5xxx_usbotg.h>      /* USBOTG */
#include <mcf53xx_usbhost.h>     /* USBGOST*/
/*#include <mcf5xxx_esdhc.h>     /* ESDHC  */
#include <mcf53xx_ssi.h>         /* SSI    */
#include <mcf53xx_rng.h>         /* RNG    */
#include <mcf53xx_iim.h>         /* IMM    */

#endif /* __ASM__ */

#ifdef __cplusplus
extern "C" {
#endif

/*------------------------------------------------------------------------*/
/*
**                    CONSTANT DEFINITIONS
*/

#define PSP_HAS_DSP                         1
#define PSP_HAS_EMAC                        1

#define PSP_ACR_CNT                         2       /* ACR registers count */

/*
** Cache and MMU definition values
*/
#define PSP_HAS_MMU                         1
#define PSP_HAS_CODE_CACHE                  1
#define PSP_HAS_DATA_CACHE                  1

#define PSP_CACHE_SPLIT                     0
#define PSP_CACHE_HAS_BUS_SNOOPING          FALSE
#define PSP_CACHE_LINE_SIZE                 (0x10)
#define PSP_CACHE_LINE_ALIGNMENT            (0xFFFFFFE0)
#define PSP_DCACHE_SIZE                     (16 * 1024)
#define PSP_ICACHE_SIZE                     (16 * 1024)
#define PSP_CACHE_SIZE                      PSP_DCACHE_SIZE
#define PSP_NUM_CACHE_LINES                 (PSP_CACHE_SIZE / PSP_CACHE_LINE_SIZE)
#define PSP_DCACHE_NUM_WAYS                 (4)
#define PSP_DCACHE_NUM_SETS                 (PSP_DCACHE_SIZE / (PSP_DCACHE_NUM_WAYS * PSP_CACHE_LINE_SIZE))

#define PSP_MEM_STOREBLOCK_ALIGNMENT        (2)

#ifndef __ASM__

/*
** Configuration information
*/
#define MCF5329_NUM_TIMERS                  (4)     /* PIT */
#define MCF5329_NUM_UARTS                   (3)
#define MCF5329_NUM_DMA_CH                  (16)    /* DMA channels */
#define MCF5329_NUM_DMA_TIMERS              (4)     /* DMA timer */
#define MCF5329_NUM_EPORT                   (2)
#define MCF5329_NUM_FB_CS                   (6)

#define MCF5329_NUM_ACRS                    (2)
#define MCF5329_NUM_DATA_ACRS               (2)
#define MCF5329_NUM_INSTR_ACRS              (2)
#define MCF529_FIRST_DATA_ACR               (0)
#define MCF5329_FIRST_INSTR_ACR             (2)

/* Error codes from mcf5329x_mmu_add_region */
#define MCF5329_OUT_OF_ACRS                 (0x00100000)

/* Do you want to verify kernel data can be read and written correctly */
#define PSP_KERNEL_DATA_VERIFY_ENABLE       ((uint_32)__KERNEL_DATA_VERIFY_ENABLE)


#define _PSP_BYTES_TO_LINES(b)              (((b) + (PSP_CACHE_LINE_SIZE - 1)) / PSP_CACHE_LINE_SIZE)
#define _PSP_MASK_CACHE_ADDR(p)             (pointer)(((uint_32)p) & ~(PSP_CACHE_LINE_SIZE - 1))

/*
** Standard cache macros
*/
#if PSP_HAS_DATA_CACHE || PSP_HAS_CODE_CACHE
    #define _CACHE_ENABLE(n)                _mcf5329_cache_enable(n)
    #define _CACHE_DISABLE()                _mcf5329_cache_disable()
#else
    #define _CACHE_ENABLE(n)                 
    #define _CACHE_DISABLE()
#endif

#if PSP_HAS_DATA_CACHE

#define _DCACHE_ENABLE(n)                   _mcf5329_dcache_enable(n)
#define _DCACHE_DISABLE()                   _mcf5329_dcache_disable()
/*
#define _DCACHE_FLUSH()                     _psp_dcache_flush_all(PSP_CACHE_LINE_SIZE, PSP_DCACHE_NUM_WAYS, PSP_DCACHE_NUM_SETS)
#define _DCACHE_FLUSH_MBYTES(p, m)          _dcache_flush(_PSP_MASK_CACHE_ADDR(p), _PSP_BYTES_TO_LINES(m), PSP_CACHE_LINE_SIZE)
#define _DCACHE_FLUSH_LINE(p)               _DCACHE_FLUSH_MBYTES(p, 1)
*/
#define _DCACHE_FLUSH()                     /* data cache is writethrough */
#define _DCACHE_FLUSH_MBYTES(p, m)          /* data cache is writethrough */
#define _DCACHE_FLUSH_LINE(p)               /* data cache is writethrough */

#define _DCACHE_INVALIDATE()                _mcf5329_cache_invalidate()
#define _DCACHE_INVALIDATE_LINE(p)          _DCACHE_INVALIDATE_MBYTES(p, 1)
#define _DCACHE_INVALIDATE_MBYTES(p, m)     _dcache_flush(_PSP_MASK_CACHE_ADDR(p), _PSP_BYTES_TO_LINES(m), PSP_CACHE_LINE_SIZE)

#else

#define _DCACHE_ENABLE(n)
#define _DCACHE_DISABLE()
#define _DCACHE_FLUSH()
#define _DCACHE_FLUSH_LINE(p)
#define _DCACHE_FLUSH_MBYTES(p, m)
#define _DCACHE_INVALIDATE()
#define _DCACHE_INVALIDATE_LINE(p)
#define _DCACHE_INVALIDATE_MBYTES(p, m)

#endif  /* PSP_HAS_DATA_CACHE */



#if PSP_HAS_CODE_CACHE 

#define _ICACHE_ENABLE(n)                   _mcf5329_cache_enable(n)
#define _ICACHE_DISABLE()                   _mcf5329_cache_disable()
#define _ICACHE_INVALIDATE()                _mcf5329_cache_invalidate()
#define _ICACHE_INVALIDATE_LINE(p)          _ICACHE_INVALIDATE_MBYTES(p, 1)
#define _ICACHE_INVALIDATE_MBYTES(p, m)     _icache_invalidate_mlines(p, _PSP_BYTES_TO_LINES(m), PSP_CACHE_LINE_SIZE)

#else

#define _ICACHE_ENABLE(n)
#define _ICACHE_DISABLE()
#define _ICACHE_INVALIDATE()
#define _ICACHE_INVALIDATE_LINE(p)
#define _ICACHE_INVALIDATE_MBYTES(p, m)

#endif  /* PSP_HAS_CODE_CACHE */

#if PSP_HAS_CODE_CACHE || PSP_HAS_DATA_CACHE

#define _MMU_DISABLE()                        _mmu_disable()
#define _MMU_ENABLE()                         _mmu_enable()

#else

#define _MMU_DISABLE()
#define _MMU_ENABLE()

#endif




#define MCF53XX_CACHE_CACHEABLE_WRITETHROUGH    0       /* Unbuffered */
#define MCF53XX_CACHE_CACHEABLE_COPYBACK        1       /* Write buffered */
#define MCF53XX_CACHE_NONCACHEABLE_UNBUFFERED   2
#define MCF53XX_CACHE_NONCACHEABLE_BUFFERED     3

/*
** Configuration information
*/
#define MCF5329_REG_BASE                        ((pointer)0xEC000000)
#define MCF5329_NUM_TIMERS                      (4)
#define MCF5329_NUM_UARTS                       (3)
#define MCF5329_NUM_DMAS                        (4)


/*
** Cache control register bits
*/
#define MCF53XX_CACR_EC                         (1 << 31)           /* Enable data cache. */
#define MCF53XX_CACR_ESB                        (1 << 29)           /* Enable data store buffer. */
#define MCF53XX_CACR_DPI                        (1 << 28)           /* Disable CPUSHL invalidation. */
#define MCF53XX_CACR_HLCK                       (1 << 27)           /* Half-data cache lock mode */
#define MCF53XX_CACR_CINVA                      (1 << 24)           /* Data cache invalidate all. */
#define MCF53XX_CACR_DNFB                       (1 << 10)           /* Instruction default cache mode */
#define MCF53XX_CACR_DCM(x)                     (((x) & 3) << 8)    /* Default data cache mode. */
#define MCF53XX_CACR_DW                         (1 << 5)            /* Write accesses not permitted */
#define MCF53XX_CACR_EUSP                       (1 << 4)            /* Enable user stack pointer */

/* Bits that should be cleared */
#define MCF5329_CACR_CLEAR_BITS                 (0x63025F)

/* These bits automatically clear after the operation */
#define CACR_AUTO_CLEAR_BITS    (MCF53XX_CACR_CINVA)


/*
** Access control register bits
** See Table 7-5. ACRn Field Descriptions
*/
#define MCF53XX_ACR_BASE_ADDR                    (0xFF000000)
#define MCF53XX_ACR_BASE_ADDR_MASK               (0x00FF0000)
#define MCF53XX_ACR_ENABLE                       (0x00008000)
#define MCF53XX_ACR_SUPERVISOR                   (0x00004000)
#define MCF53XX_ACR_CM                           (0x00000600)
#define MCF53XX_ACR_WRITE_PROTECT                (0x00000004)
#define MCF53XX_ACR_NONCACHEABLE_MODE            (0x00000040)
#define MCF53XX_ACR_CACHEABLE_MODE               (0x00000000)
#define MCF53XX_ACR_BUFFER_WRITE_ENABLE          (0x00000020)


/*
** The ColdFire family of processors has a simplified exception stack
** frame that looks like the following:
**
**              3322222222221111 111111
**              1098765432109876 5432109876543210
**           8 +----------------+----------------+
**             |         Program Counter         |
**           4 +----------------+----------------+
**             |FS/Fmt/Vector/FS|      SR        |
**   SP -->  0 +----------------+----------------+
**
** The stack self-aligns to a 4-byte boundary at an exception, with
** the FS/Fmt/Vector/FS field indicating the size of the adjustment
** (SP += 0,1,2,3 bytes).
*/

#define MCF5XXX_RD_SF_FORMAT(PTR)       \
        ((*((uint_16_ptr)(PTR)) >> 12) & 0x00FF)

#define MCF5XXX_RD_SF_VECTOR(PTR)       \
        ((*((uint_16_ptr)(PTR)) >>  2) & 0x00FF)

#define MCF5XXX_RD_SF_FS(PTR)           \
        ( ((*((uint_16_ptr)(PTR)) & 0x0C00) >> 8) | (*((uint_16_ptr)(PTR)) & 0x0003) )

#define MCF5XXX_SF_SR(PTR)      *((uint_16_ptr)(PTR)+1)
#define MCF5XXX_SF_PC(PTR)      *((uint_32_ptr)(PTR)+1)

/*------------------------------------------------------------------------*/
/*
** Cache control register bits
*/
#define MCF5329_CACR_CACHE_ENABLE               (1<<31)         /* Enable Cache */
#define MCF5329_CACR_ESB                        (1<<29)         /* Enable Store Buffer */
#define MCF5329_CACR_DPI                        (1<<28)         /* Disable CPUSHL Invalidation */
#define MCF5329_CACR_HCLK                       (1<<27)         /* Half Cache Lock Mode */
#define MCF5329_CACR_CINVA                      (1<<24)         /* Cache Invalidate All */
#define MCF5329_CACR_DNFB                       (1<<10)         /* Default Noncacheable Fill Buffer */
#define MCF5329_CACR_DCM(x)                     (((x)&0x3)<<8)  /* Default Cache Mode */
#define MCF5329_CACR_DWP                        (1<< 5)         /* Default Write Protect */
/* Corrected from MCF5329 Reference Manual Errata */
#define MCF5329_CACR_EUSP                       (1<< 4)         /* Enable user stack pointer */
/*
** Access control register bits
*/
#define MCF5329_ACR_BASE_ADDR                   (0xFF000000)
#define MCF5329_ACR_BASE_ADDR_MASK              (0x00FF0000)
#define MCF5329_ACR_ENABLE                      (0x00008000)    /* Enable other ACR bits */
#define MCF5329_ACR_IGNORE_FC                   (0x00004000)    /* Execute cache matching on all accesses */
#define MCF5329_ACR_USER_ACCESS_FC              (0x00000000)    /* User mode */
#define MCF5329_ACR_SUPER_ACCESS_FC             (0x00002000)    /* Supervisor mode */
#define MCF5329_ACR_NONCACHEABLE_MODE           (0x00000040)    /* Cache-inhibited, precise */
#define MCF5329_ACR_BUFFER_WRITE_ENABLE         (0x00000020)    /* Cacheable, copyback */
#define MCF5329_ACR_CACHEABLE_MODE              (0x00000000)    /* Cacheable, write-through */
#define MCF5329_ACR_WRITE_PROTECT               (0x00000004)    /* Write protect */
/*
/** Interrupt definitions
*/
#define MCF5329_ICTRL_MASKALL   1
#define MCF5329_ICTRL0_BASEx    64
#define MCF5329_ICTRL1_BASEx    128

/*
** Interrupt vector table
*/

typedef enum mcf5329_interrupt_table_index {
   MCF5329_boot_stack_pointer,
   MCF5329_boot_program_counter,
   MCF5329_EXC_ACCESS_ERROR,
   MCF5329_EXC_ADDRESS_ERROR,
   MCF5329_EXC_ILLEGAL_INSTRUCTION,
   MCF5329_EXC_DIVIDE_BY_ZERO,
   MCF5329_EXC_rsvd6,
   MCF5329_EXC_rsvd7,
   MCF5329_EXC_PRIVILEGE_VIOLATION,
   MCF5329_EXC_NEXT_TRACE,
   MCF5329_EXC_UNIMPLEMENTED_LINE_A_OPCODE,
   MCF5329_EXC_UNIMPLEMENTED_LINE_F_OPCODE,
   MCF5329_EXC_DEBUG,
   MCF5329_EXC_rsvd13,
   MCF5329_EXC_FORMAT_ERROR,
   MCF5329_EXC_rsvd15,
   MCF5329_EXC_rsvd16,
   MCF5329_EXC_rsvd17,
   MCF5329_EXC_rsvd18,
   MCF5329_EXC_rsvd19,
   MCF5329_EXC_rsvd20,
   MCF5329_EXC_rsvd21,
   MCF5329_EXC_rsvd22,
   MCF5329_EXC_rsvd23,
   MCF5329_EXC_SPURIOUS,
   MCF5329_EXC_rsvd25,
   MCF5329_EXC_rsvd26,
   MCF5329_EXC_rsvd27,
   MCF5329_EXC_rsvd28,
   MCF5329_EXC_rsvd29,
   MCF5329_EXC_rsvd30,
   MCF5329_EXC_rsvd31,
   MCF5329_EXC_TRAP0,
   MCF5329_EXC_TRAP1,
   MCF5329_EXC_TRAP2,
   MCF5329_EXC_TRAP3,
   MCF5329_EXC_TRAP4,
   MCF5329_EXC_TRAP5,
   MCF5329_EXC_TRAP6,
   MCF5329_EXC_TRAP7,
   MCF5329_EXC_TRAP8,
   MCF5329_EXC_TRAP9,
   MCF5329_EXC_TRAP10,
   MCF5329_EXC_TRAP11,
   MCF5329_EXC_TRAP12,
   MCF5329_EXC_TRAP13,
   MCF5329_EXC_TRAP14,
   MCF5329_EXC_TRAP15,
   MCF5329_EXC_rsvd48,
   MCF5329_EXC_rsvd49,
   MCF5329_EXC_rsvd50,
   MCF5329_EXC_rsvd51,
   MCF5329_EXC_rsvd52,
   MCF5329_EXC_rsvd53,
   MCF5329_EXC_rsvd54,
   MCF5329_EXC_rsvd55,
   MCF5329_EXC_rsvd56,
   MCF5329_EXC_rsvd57,
   MCF5329_EXC_rsvd58,
   MCF5329_EXC_rsvd59,
   MCF5329_EXC_rsvd60,
   MCF5329_EXC_rsvd61,
   MCF5329_EXC_rsvd62,
   MCF5329_EXC_rsvd63,
   MCF5329_INT_FIRST_EXTERNAL,
   MCF5329_INT_EPORT1,          /*  1 Edge port flag 1 */
   MCF5329_INT_EPORT2,          /*  2 Edge port flag 2 */
   MCF5329_INT_EPORT3,          /*  3 Edge port flag 3 */
   MCF5329_INT_EPORT4,          /*  4 Edge port flag 4 */
   MCF5329_INT_EPORT5,          /*  5 Edge port flag 5 */
   MCF5329_INT_EPORT6,          /*  6 Edge port flag 6 */
   MCF5329_INT_EPORT7,          /*  7 Edge port flag 7 */
   MCF5329_INT_EDMA0,           /*  8 DMA Channel 0 transfer complete */
   MCF5329_INT_EDMA1,           /*  9 DMA Channel 1 transfer complete */
   MCF5329_INT_EDMA2,           /* 10 DMA Channel 2 transfer complete */
   MCF5329_INT_EDMA3,           /* 11 DMA Channel 3 transfer complete */
   MCF5329_INT_EDMA4,           /* 12 DMA Channel 4 transfer complete */
   MCF5329_INT_EDMA5,           /* 13 DMA Channel 5 transfer complete */
   MCF5329_INT_EDMA6,           /* 14 DMA Channel 6 transfer complete */
   MCF5329_INT_EDMA7,           /* 15 DMA Channel 7 transfer complete */
   MCF5329_INT_EDMA8,           /* 16 DMA Channel 8 transfer complete */
   MCF5329_INT_EDMA9,           /* 17 DMA Channel 9 transfer complete */
   MCF5329_INT_EDMA10,          /* 18 DMA Channel 10 transfer complete */
   MCF5329_INT_EDMA11,          /* 19 DMA Channel 11 transfer complete */
   MCF5329_INT_EDMA12,          /* 20 DMA Channel 12 transfer complete */
   MCF5329_INT_EDMA13,          /* 21 DMA Channel 13 transfer complete */
   MCF5329_INT_EDMA14,          /* 22 DMA Channel 14 transfer complete */
   MCF5329_INT_EDMA15,          /* 23 DMA Channel 15 transfer complete */
   MCF5329_INT_EDMA_ERR,        /* 24 DMA Error Interrupt */
   MCF5329_INT_CWT,             /* 25 Core Watchdog Timeout */
   MCF5329_INT_UART0,           /* 26 UART0 interrupt */
   MCF5329_INT_UART1,           /* 27 UART1 interrupt */
   MCF5329_INT_UART2,           /* 28 UART2 interrupt */
   MCF5329_INT_rsvd1,           /* 29 Not used */
   MCF5329_INT_I2C,             /* 30 I2C interrupt */
   MCF5329_INT_QSPI,            /* 31 QSPI interrupt */
   MCF5329_INT_DTIM0,           /* 32 TMR0 interrupt */
   MCF5329_INT_DTIM1,           /* 33 TMR1 interrupt */
   MCF5329_INT_DTIM2,           /* 34 TMR2 interrupt */
   MCF5329_INT_DTIM3,           /* 35 TMR3 interrupt */
   MCF5329_INT_FEC_X_INTF,      /* 36 Transmit frame interrupt */
   MCF5329_INT_FEC_X_INTB,      /* 37 Transmit buffer interrupt */
   MCF5329_INT_FEC_X_UN,        /* 38 Transmit FIFO underrun */
   MCF5329_INT_FEC_RL,          /* 39 Collision retry limit */
   MCF5329_INT_FEC_R_INTF,      /* 40 Receive frame interrupt */
   MCF5329_INT_FEC_R_INTB,      /* 41 Receive buffer interrupt */
   MCF5329_INT_FEC_MII,         /* 42 MII interrupt */
   MCF5329_INT_FEC_LC,          /* 43 Late collision */
   MCF5329_INT_FEC_HBERR,       /* 44 Heartbeat error */
   MCF5329_INT_FEC_GRA,         /* 45 Graceful stop complete */
   MCF5329_INT_FEC_EBERR,       /* 46 Ethernet bus error */
   MCF5329_INT_FEC_BABT,        /* 47 Babbling transmit error */
   MCF5329_INT_FEC_BABR,        /* 48 Babbling receive error */
   MCF5329_INT_rsvd2,           /* 49 Not used */
   MCF5329_INT_rsvd3,           /* 50 Not used */
   MCF5329_INT_rsvd4,           /* 51 Not used */
   MCF5329_INT_rsvd5,           /* 52 Not used */
   MCF5329_INT_rsvd6,           /* 53 Not used */
   MCF5329_INT_rsvd7,           /* 54 Not used */
   MCF5329_INT_rsvd8,           /* 55 Not used */
   MCF5329_INT_rsvd9,           /* 56 Not used */
   MCF5329_INT_rsvd10,          /* 57 Not used */
   MCF5329_INT_rsvd11,          /* 58 Not used */
   MCF5329_INT_rsvd12,          /* 59 Not used */
   MCF5329_INT_rsvd13,          /* 60 Not used */
   MCF5329_INT_rsvd14,          /* 61 Not used */
   MCF5329_INT_CFE,             /* 62 Bus Error Interrupt */
   MCF5329_INT_rsvd15,          /* 63 Not used */
   MCF5329_INT_FLEXCAN_MB_REQ,  /*  0 Logical OR of FlexCAN MB Requests */
   MCF5329_INT_FLEXCAN_BOFF_INT,/*  1 FlexCAN bus-off */
   MCF5329_INT_FLEXCAN_WAKE_INT,/*  2 FlexCAN wake-up */
   MCF5329_INT_FLEXCAN_ERR_INT, /*  3 FlexCAN error */
   MCF5329_INT_FLEXCAN_BUF0,    /*  4 FlexCAN MB 0 */
   MCF5329_INT_FLEXCAN_BUF1,    /*  5 FlexCAN MB 1 */
   MCF5329_INT_FLEXCAN_BUF2,    /*  6 FlexCAN MB 2 */
   MCF5329_INT_FLEXCAN_BUF3,    /*  7 FlexCAN MB 3 */
   MCF5329_INT_FLEXCAN_BUF4,    /*  8 FlexCAN MB 4 */
   MCF5329_INT_FLEXCAN_BUF5,    /*  9 FlexCAN MB 5 */
   MCF5329_INT_FLEXCAN_BUF6,    /* 10 FlexCAN MB 6 */
   MCF5329_INT_FLEXCAN_BUF7,    /* 11 FlexCAN MB 7 */
   MCF5329_INT_FLEXCAN_BUF8,    /* 12 FlexCAN MB 8 */
   MCF5329_INT_FLEXCAN_BUF9,    /* 13 FlexCAN MB 9 */
   MCF5329_INT_FLEXCAN_BUF10,   /* 14 FlexCAN MB 10 */
   MCF5329_INT_FLEXCAN_BUF11,   /* 15 FlexCAN MB 11 */
   MCF5329_INT_FLEXCAN_BUF12,   /* 16 FlexCAN MB 12 */
   MCF5329_INT_FLEXCAN_BUF13,   /* 17 FlexCAN MB 13 */
   MCF5329_INT_FLEXCAN_BUF14,   /* 18 FlexCAN MB 14 */
   MCF5329_INT_FLEXCAN_BUF15,   /* 19 FlexCAN MB 15 */
   MCF5329_INT_rsvd16,          /* 20 Not used */
   MCF5329_INT_rsvd17,          /* 21 Not used */
   MCF5329_INT_rsvd18,          /* 22 Not used */
   MCF5329_INT_rsvd19,          /* 23 Not used */
   MCF5329_INT_rsvd20,          /* 24 Not used */
   MCF5329_INT_rsvd21,          /* 25 Not used */
   MCF5329_INT_rsvd22,          /* 26 Not used */
   MCF5329_INT_rsvd23,          /* 27 Not used */
   MCF5329_INT_rsvd24,          /* 28 Not used */
   MCF5329_INT_rsvd25,          /* 29 Not used */
   MCF5329_INT_rsvd26,          /* 30 Not used */
   MCF5329_INT_rsvd27,          /* 31 Not used */
   MCF5329_INT_rsvd28,          /* 32 Not used */
   MCF5329_INT_rsvd29,          /* 33 Not used */
   MCF5329_INT_rsvd30,          /* 34 Not used */
   MCF5329_INT_rsvd31,          /* 35 Not used */
   MCF5329_INT_rsvd32,          /* 36 Not used */
   MCF5329_INT_rsvd33,          /* 37 Not used */
   MCF5329_INT_rsvd34,          /* 38 Not used */
   MCF5329_INT_rsvd35,          /* 39 Not used */
   MCF5329_INT_RNG,             /* 40 RNG interrupt flag */
   MCF5329_INT_SKHA,            /* 41 SKHA interrupt flag */
   MCF5329_INT_MDHA,            /* 42 MDHA interrupt flag */
   MCF5329_INT_PIT0,            /* 43 PIT0 PIF PIT interrupt flag */
   MCF5329_INT_PIT1,            /* 44 PIT1 PIF PIT interrupt flag */
   MCF5329_INT_PIT2,            /* 45 PIT2 PIF PIT interrupt flag */
   MCF5329_INT_PIT3,            /* 46 PIT3 PIF PIT interrupt flag */
   MCF5329_INT_USB_OTG,         /* 47 USB OTG interrupt */
   MCF5329_INT_USB_HOST,        /* 48 USB HOST interrupt */
   MCF5329_INT_SSI,             /* 49 SSI interrupt */
   MCF5329_INT_PWM,             /* 50 Pulse width modulation interrupt */
   MCF5329_INT_LCDC,            /* 51 LCD Controller interrupt */
   MCF5329_INT_RTC,             /* 52 Real Time Clock interrupt */
   MCF5329_INT_USB_STAT,        /* 53 USB status interrupt */
   MCF5329_INT_rsvd36,          /* 54 Not used */
   MCF5329_INT_rsvd37,          /* 55 Not used */
   MCF5329_INT_rsvd38,          /* 56 Not used */
   MCF5329_INT_rsvd39,          /* 57 Not used */
   MCF5329_INT_rsvd40,          /* 58 Not used */
   MCF5329_INT_rsvd41,          /* 59 Not used */
   MCF5329_INT_rsvd42,          /* 60 Not used */
   MCF5329_INT_rsvd43,          /* 61 Not used */
   MCF5329_INT_rsvd44,          /* 62 Not used */
   MCF5329_INT_rsvd45           /* 63 Not used */

} MCF5329_INTERRUPT_TABLE_INDEX;


/*------------------------------------------------------------------------*/
/*
** ENET FEC  registers bit set.
*/

/* FEC Ethernet Buffer descriptor bits */
#define MCF5329_BD_ETHER_RX_EMPTY                (1<<15)
#define MCF5329_BD_ETHER_RX_WRAP                 (1<<13)

/* The following are status bits set after reception */
#define MCF5329_BD_ETHER_RX_LAST_FRAME           (1<<11)
#define MCF5329_BD_ETHER_RX_MISS                 (1<<8)
#define MCF5329_BD_ETHER_RX_BRAUDCAST            (1<<7)
#define MCF5329_BD_ETHER_RX_MULTICAST            (1<<6)
#define MCF5329_BD_ETHER_RX_LENGTH_VIOLATION     (1<<5)
#define MCF5329_BD_ETHER_RX_NON_OCTET            (1<<4)
#define MCF5329_BD_ETHER_RX_CRC_ERROR            (1<<2)
#define MCF5329_BD_ETHER_RX_OVERRUN              (1<<1)
#define MCF5329_BD_ETHER_RX_TRUNCATED            (1<<0)

#define MCF5329_BD_ETHER_TX_READY                (1<<15)
#define MCF5329_BD_ETHER_TX_WRAP                 (1<<13)
#define MCF5329_BD_ETHER_TX_LAST                 (1<<11)
#define MCF5329_BD_ETHER_TX_SEND_CRC             (1<<10)
#define MCF5329_BD_ETHER_TX_BAD_CRC              (1<<9)

/* FEC Ethernet Control Register */
#define MCF5329_FEC_ECR_ETHER_EN                 (0x00000002)
#define MCF5329_FEC_ECR_RESET                    (0x00000001)

/* FEC Interrupt Event Register */
#define MCF5329_FEC_EIR_ALL_PENDING              (0xFFF80000)
#define MCF5329_FEC_EIR_HBERR                    (0x80000000)
#define MCF5329_FEC_EIR_BABR                     (0x40000000)
#define MCF5329_FEC_EIR_BABT                     (0x20000000)
#define MCF5329_FEC_EIR_GRA                      (0x10000000)
#define MCF5329_FEC_EIR_TXF                      (0x08000000)
#define MCF5329_FEC_EIR_TXB                      (0x04000000)
#define MCF5329_FEC_EIR_RXF                      (0x02000000)
#define MCF5329_FEC_EIR_RXB                      (0x01000000)
#define MCF5329_FEC_EIR_MII                      (0x00800000)
#define MCF5329_FEC_EIR_EBERR                    (0x00400000)
#define MCF5329_FEC_EIR_LC                       (0x00200000)
#define MCF5329_FEC_EIR_RL                       (0x00100000)
#define MCF5329_FEC_EIR_UN                       (0x00080000)

/* FEC Interrupt Mask Register */
#define MCF5329_FEC_EIMR_MASK_ALL                (0xFFF80000)
#define MCF5329_FEC_EIMR_HBERR                   (0x80000000)
#define MCF5329_FEC_EIMR_BABR                    (0x40000000)
#define MCF5329_FEC_EIMR_BABT                    (0x20000000)
#define MCF5329_FEC_EIMR_GRA                     (0x10000000)
#define MCF5329_FEC_EIMR_TXF                     (0x08000000)
#define MCF5329_FEC_EIMR_TXB                     (0x04000000)
#define MCF5329_FEC_EIMR_RXF                     (0x02000000)
#define MCF5329_FEC_EIMR_RXB                     (0x01000000)
#define MCF5329_FEC_EIMR_MII                     (0x00800000)
#define MCF5329_FEC_EIMR_EBERR                   (0x00400000)
#define MCF5329_FEC_EIMR_LC                      (0x00200000)
#define MCF5329_FEC_EIMR_RL                      (0x00100000)
#define MCF5329_FEC_EIMR_UN                      (0x00080000)

/* FEC Receive Descriptor Active Register */
#define MCF5329_FEC_RDAR_ACTIVE                  (1<<24)

/* FEC Transmit Descriptor Active Register */
#define MCF5329_FEC_TDAR_ACTIVE                  (1<<24)

/* FEC Receive Control Register */
#define MCF5329_FEC_RCR_FCE                      (0x00000020)
#define MCF5329_FEC_RCR_BC_REJ                   (0x00000010)
#define MCF5329_FEC_RCR_PROM                     (0x00000008)
#define MCF5329_FEC_RCR_MII_MODE                 (0x00000004)
#define MCF5329_FEC_RCR_DRT                      (0x00000002)
#define MCF5329_FEC_RCR_LOOP                     (0x00000001)
#define MCF5329_FEC_RCR_FRAME_LENGTH(x)          (((x)&0x7ff)<<16)

/* FEC Transmit Control Register */
#define MCF5329_FEC_TCR_FDEN                     (0x00000004)
#define MCF5329_FEC_TCR_HBC                      (0x00000002)
#define MCF5329_FEC_TCR_GTS                      (0x00000001)

/* Transmit FIFO Watermark */
#define MCF5329_FEC_TFWR_192                     (0x00000003)
#define MCF5329_FEC_TFWR_128                     (0x00000002)
#define MCF5329_FEC_TFWR_64                      (0x00000001)

/* FIFO Receive Start Register */
#define MCF5329_FEC_FRSR_R_FSTART(x)             (((x)&0xFF)<<2)

/* MII Management Frame Register */
#define FEC_MII_START_OF_FRAME                   (0x40000000)
#define FEC_MII_OPCODE_READ                      (0x20000000)
#define FEC_MII_OPCODE_WRITE                     (0x10000000)
#define FEC_MII_PA(x)                            (((x)&0x1F)<<23)
#define FEC_MII_RA(x)                            (((x)&0x1F)<<18)
#define FEC_MII_DATA(x)                          (((x)&0xFFFF))
#define FEC_MII_TURNAROUND                       (0x00020000)
#define FEC_MII_MSCR_PREAMBLE                    (1<<7)
#define FEC_MII_MSCR_SPEED(x)                    (((x) 0x3F) << 1)

#define MCF5329_SIM_ICR_ERX_IL(a)   ( 0x00000800 | (((a)&0x07)<<8) )
#define MCF5329_SIM_ICR_ETX_IL(a)   ( 0x00000080 | (((a)&0x07)<<4) )
#define MCF5329_SIM_ICR_ENTC_IL(a)  ( 0x00000008 | ((a)&0x07) )

/*------------------------------------------------------------------------*/
/*
** SCM System control module
*/

#define MCF5329_SCM_IPSBAR_BA(x)                ((x)&0xC0000000)
#define MCF5329_SCM_IPSBAR_V                    (0x00000001)

#define MCF5329_SCM_RAMBAR_BA(x)                ((x)&0xFFFFC000)
#define MCF5329_SCM_RAMBAR_BDE                  (0x00000200)

#define MCF5329_SCM_CRSR_EXT                    (0x80)
#define MCF5329_SCM_CRSR_CWDR                   (0x20)

#define MCF5329_SCM_CWCR_CWE                    (0x80)
#define MCF5329_SCM_CWCR_CWRI                   (0x40)
#define MCF5329_SCM_CWCR_CWT(x)                 (((x)&0x03)<<3)
#define MCF5329_SCM_CWCR_CWTA                   (0x04)
#define MCF5329_SCM_CWCR_CWTAVAL                (0x02)
#define MCF5329_SCM_CWCR_CWTIC                  (0x01)

#define MCF5329_SCM_LPICR_ENBSTOP               (0x80)
#define MCF5329_SCM_LPICR_XSTOP_IPL(x)          (((x)&0x07)<<4)

#define MCF5329_SCM_CWSR_SEQ1                   (0x55)
#define MCF5329_SCM_CWSR_SEQ2                   (0xAA)

#define MCF5329_SCM_DMAREQC_DMAC3(x)            (((x)&0x000F)<<12)
#define MCF5329_SCM_DMAREQC_DMAC2(x)            (((x)&0x000F)<<8)
#define MCF5329_SCM_DMAREQC_DMAC1(x)            (((x)&0x000F)<<4)
#define MCF5329_SCM_DMAREQC_DMAC0(x)            (((x)&0x000F))
#define MCF5329_SCM_DMAREQC_DMATIMER0           (0x4)
#define MCF5329_SCM_DMAREQC_DMATIMER1           (0x5)
#define MCF5329_SCM_DMAREQC_DMATIMER2           (0x6)
#define MCF5329_SCM_DMAREQC_DMATIMER3           (0x7)
#define MCF5329_SCM_DMAREQC_UART0               (0x8)
#define MCF5329_SCM_DMAREQC_UART1               (0x9)
#define MCF5329_SCM_DMAREQC_UART2               (0xA)

#define MCF5329_SCM_MPARK_M2_P_EN               (0x02000000)
#define MCF5329_SCM_MPARK_BCR24BIT              (0x01000000)
#define MCF5329_SCM_MPARK_M3_PRTY(x)            (((x)&0x03)<<22)
#define MCF5329_SCM_MPARK_M2_PRTY(x)            (((x)&0x03)<<20)
#define MCF5329_SCM_MPARK_M0_PRTY(x)            (((x)&0x03)<<18)
#define MCF5329_SCM_MPARK_M1_PRTY(x)            (((x)&0x03)<<16)
#define MCF5329_SCM_MPARK_FIXED                 (0x00040000)
#define MCF5329_SCM_MPARK_TIMEOUT               (0x00020000)
#define MCF5329_SCM_MPARK_PRK_LAST              (0x00010000)
#define MCF5329_SCM_MPARK_LCKOUT_TIME(x)        (((x)&0x000F)<<8)

#define MCF5329_SCM_MPARK_MX_PRTY_FIRST         (0x3)
#define MCF5329_SCM_MPARK_MX_PRTY_SECOND        (0x2)
#define MCF5329_SCM_MPARK_MX_PRTY_THIRD         (0x1)
#define MCF5329_SCM_MPARK_MX_PRTY_FOURTH        (0x0)

#define MCF5329_SCM_MPR_MPR(x)                  (((x)&0x0F))

#define MCF5329_SCM_PACR_LOCK1                  (0x80)
#define MCF5329_SCM_PACR_ACCESSCTRL1            (((x)&0x07)<<4)
#define MCF5329_SCM_PACR_LOCK0                  (0x08)
#define MCF5329_SCM_PACR_ACCESSCTRL0            (((x)&0x07))
#define MCF5329_SCM_PACR_RW_NA                  (0x0)
#define MCF5329_SCM_PACR_R_NA                   (0x1)
#define MCF5329_SCM_PACR_R_R                    (0x2)
#define MCF5329_SCM_PACR_RW_RW                  (0x4)
#define MCF5329_SCM_PACR_RW_R                   (0x5)
#define MCF5329_SCM_PACR_NA_NA                  (0x7)

#define MCF5329_SCM_GPACR_LOCK                  (0x80)
#define MCF5329_SCM_GPACR_ACCESSCTRL            (((x)&0x0F))
#define MCF5329_SCM_GPACR_ACCESSCTRL_RW_NA      (0x0)
#define MCF5329_SCM_GPACR_ACCESSCTRL_R_NA       (0x1)
#define MCF5329_SCM_GPACR_ACCESSCTRL_R_R        (0x2)
#define MCF5329_SCM_GPACR_ACCESSCTRL_RW_RW      (0x4)
#define MCF5329_SCM_GPACR_ACCESSCTRL_RW_R       (0x5)
#define MCF5329_SCM_GPACR_ACCESSCTRL_NA_NA      (0x7)
#define MCF5329_SCM_GPACR_ACCESSCTRL_RWE_NA     (0x8)
#define MCF5329_SCM_GPACR_ACCESSCTRL_RE_NA      (0x9)
#define MCF5329_SCM_GPACR_ACCESSCTRL_RE_RE      (0xA)
#define MCF5329_SCM_GPACR_ACCESSCTRL_E_NA       (0xB)
#define MCF5329_SCM_GPACR_ACCESSCTRL_RWE_RWE    (0xC)
#define MCF5329_SCM_GPACR_ACCESSCTRL_RWE_RE     (0xD)
#define MCF5329_SCM_GPACR_ACCESSCTRL_RWE_E      (0xF)


/*------------------------------------------------------------------------*/
/*
** SDRAM Controller Module
*/

/* Bit definitions and macros for SDMR */
#define MCF5329_SDRAMC_SDMR_BNKAD_LMR           (0x00000000)
#define MCF5329_SDRAMC_SDMR_BNKAD_LEMR          (0x40000000)    /* Non-mobile DDR devices     */
#define MCF5329_SDRAMC_SDMR_BNKAD_LEMR_MOBILE   (0x80000000)    /* Mobile DDR devices */
#define MCF5329_SDRAMC_SDMR_AD(x)               (((x)&0x00000FFF)<<18)
#define MCF5329_SDRAMC_SDMR_CMD                 (0x00010000)

/* Bit definitions and macros for SDCR */
#define MCF5329_SDRAMC_SDCR_MODE_EN             (0x80000000)
#define MCF5329_SDRAMC_SDCR_CKE                 (0x40000000)
#define MCF5329_SDRAMC_SDCR_DDR                 (0x20000000)
#define MCF5329_SDRAMC_SDCR_REF                 (0x10000000)
#define MCF5329_SDRAMC_SDCR_MUX(x)              (((x)&0x00000003)<<24)
#define MCF5329_SDRAMC_SDCR_OE_RULE             (0x00400000)
#define MCF5329_SDRAMC_SDCR_RCNT(x)             (((x)&0x0000003F)<<16)
#define MCF5329_SDRAMC_SDCR_PS_16               (0x00002000)
#define MCF5329_SDRAMC_SDCR_DQS_OE(x)           (((x)&0x00000003)<<10)
#define MCF5329_SDRAMC_SDCR_IREF                (0x00000004)
#define MCF5329_SDRAMC_SDCR_IPALL               (0x00000002)

/* Bit definitions and macros for SDCFG1 */
#define MCF5329_SDRAMC_SDCFG1_SRD2RW(x)         (((x)&0x0000000F)<<28)
#define MCF5329_SDRAMC_SDCFG1_SWT2RD(x)         (((x)&0x00000007)<<24)
#define MCF5329_SDRAMC_SDCFG1_RDLAT(x)          (((x)&0x0000000F)<<20)
#define MCF5329_SDRAMC_SDCFG1_ACT2RW(x)         (((x)&0x00000007)<<16)
#define MCF5329_SDRAMC_SDCFG1_PRE2ACT(x)        (((x)&0x00000007)<<12)
#define MCF5329_SDRAMC_SDCFG1_REF2ACT(x)        (((x)&0x0000000F)<<8)
#define MCF5329_SDRAMC_SDCFG1_WTLAT(x)          (((x)&0x00000007)<<4)

/* Bit definitions and macros for SDCFG2 */
#define MCF5329_SDRAMC_SDCFG2_BRD2PRE(x)        (((x)&0x0000000F)<<28)
#define MCF5329_SDRAMC_SDCFG2_BWT2RW(x)         (((x)&0x0000000F)<<24)
#define MCF5329_SDRAMC_SDCFG2_BRD2WT(x)         (((x)&0x0000000F)<<20)
#define MCF5329_SDRAMC_SDCFG2_BL(x)             (((x)&0x0000000F)<<16)

/* Bit definitions and macros for SDCS */
#define MCF5329_SDRAMC_SDCS_CSSZ(x)             (((x)&0x0000001F)<<0)
#define MCF5329_SDRAMC_SDCS_BASE(x)             (((x)&0x00000FFF)<<20)
#define MCF5329_SDRAMC_SDCS_BA(x)               ((x)&0xFFF00000)
#define MCF5329_SDRAMC_SDCS_CSSZ_DISABLE        (0x00000000)
#define MCF5329_SDRAMC_SDCS_CSSZ_1MBYTE         (0x00000013)
#define MCF5329_SDRAMC_SDCS_CSSZ_2MBYTE         (0x00000014)
#define MCF5329_SDRAMC_SDCS_CSSZ_4MBYTE         (0x00000015)
#define MCF5329_SDRAMC_SDCS_CSSZ_8MBYTE         (0x00000016)
#define MCF5329_SDRAMC_SDCS_CSSZ_16MBYTE        (0x00000017)
#define MCF5329_SDRAMC_SDCS_CSSZ_32MBYTE        (0x00000018)
#define MCF5329_SDRAMC_SDCS_CSSZ_64MBYTE        (0x00000019)
#define MCF5329_SDRAMC_SDCS_CSSZ_128MBYTE       (0x0000001A)
#define MCF5329_SDRAMC_SDCS_CSSZ_256MBYTE       (0x0000001B)
#define MCF5329_SDRAMC_SDCS_CSSZ_512MBYTE       (0x0000001C)
#define MCF5329_SDRAMC_SDCS_CSSZ_1GBYTE         (0x0000001D)
#define MCF5329_SDRAMC_SDCS_CSSZ_2GBYTE         (0x0000001E)
#define MCF5329_SDRAMC_SDCS_CSSZ_4GBYTE         (0x0000001F)

/*------------------------------------------------------------------------*/
/*
** General Purpose I/O (GPIO) Module
*/

/* general bit definition */
#define MCF5329_GPIO_PIN_0                            0x01
#define MCF5329_GPIO_PIN_1                            0x02
#define MCF5329_GPIO_PIN_2                            0x04
#define MCF5329_GPIO_PIN_3                            0x08
#define MCF5329_GPIO_PIN_4                            0x10
#define MCF5329_GPIO_PIN_5                            0x20
#define MCF5329_GPIO_PIN_6                            0x40
#define MCF5329_GPIO_PIN_7                            0x80

/* Bit definitions for PODR_x registers */
#define MCF5329_GPIO_PODR_x0                          0x01
#define MCF5329_GPIO_PODR_x1                          0x02
#define MCF5329_GPIO_PODR_x2                          0x04
#define MCF5329_GPIO_PODR_x3                          0x08
#define MCF5329_GPIO_PODR_x4                          0x10
#define MCF5329_GPIO_PODR_x5                          0x20
#define MCF5329_GPIO_PODR_x6                          0x40
#define MCF5329_GPIO_PODR_x7                          0x80
#define MCF5329_GPIO_PODR_x(x)                        (0x01<<x)

/* Bit definitions for PDDR_x registers */
#define MCF5329_GPIO_PDDR_x0                          0x01
#define MCF5329_GPIO_PDDR_x1                          0x02
#define MCF5329_GPIO_PDDR_x2                          0x04
#define MCF5329_GPIO_PDDR_x3                          0x08
#define MCF5329_GPIO_PDDR_x4                          0x10
#define MCF5329_GPIO_PDDR_x5                          0x20
#define MCF5329_GPIO_PDDR_x6                          0x40
#define MCF5329_GPIO_PDDR_x7                          0x80
#define MCF5329_GPIO_PDDR_x(x)                       (0x01<<x)

/* Bit definitions for PPDSDR_x registers */
#define MCF5329_GPIO_PPDSDR_x0                        0x01
#define MCF5329_GPIO_PPDSDR_x1                        0x02
#define MCF5329_GPIO_PPDSDR_x2                        0x04
#define MCF5329_GPIO_PPDSDR_x3                        0x08
#define MCF5329_GPIO_PPDSDR_x4                        0x10
#define MCF5329_GPIO_PPDSDR_x5                        0x20
#define MCF5329_GPIO_PPDSDR_x6                        0x40
#define MCF5329_GPIO_PPDSDR_x7                        0x80
#define MCF5329_GPIO_PPDSDR_x(x)                      (0x01<<x)

/* Bit definitions for PCLRR_x registers */
#define MCF5329_GPIO_PCLRR_x0                         (0x01)
#define MCF5329_GPIO_PCLRR_x1                         (0x02)
#define MCF5329_GPIO_PCLRR_x2                         (0x04)
#define MCF5329_GPIO_PCLRR_x3                         (0x08)
#define MCF5329_GPIO_PCLRR_x4                         (0x10)
#define MCF5329_GPIO_PCLRR_x5                         (0x20)
#define MCF5329_GPIO_PCLRR_x6                         (0x40)
#define MCF5329_GPIO_PCLRR_x7                         (0x80)
#define MCF5329_GPIO_PCLRR_x(x)                       (0x01<<x)

/* Bit definitions and macros for PAR_FEC */
#define MCF5329_GPIO_PAR_FEC_7W_FEC             (0x0C)
#define MCF5329_GPIO_PAR_FEC_MII_FEC            (0x03)

/* Bit definitions and macros for MCF5329_GPIO_PAR_PWM */
#define MCF5329_GPIO_PAR_PWM_PAR_PWM1(x)               (((x)&0x03)<<0)
#define MCF5329_GPIO_PAR_PWM_PAR_PWM3(x)               (((x)&0x03)<<2)
#define MCF5329_GPIO_PAR_PWM_PAR_PWM5                  (0x10)
#define MCF5329_GPIO_PAR_PWM_PAR_PWM7                  (0x20)

/* Bit definitions and macros for MCF5329_GPIO_PAR_BUSCTL */
#define MCF5329_GPIO_PAR_BUSCTL_PAR_TS(x)              (((x)&0x03)<<3)
#define MCF5329_GPIO_PAR_BUSCTL_PAR_RWB                (0x20)
#define MCF5329_GPIO_PAR_BUSCTL_PAR_TA                 (0x40)
#define MCF5329_GPIO_PAR_BUSCTL_PAR_OE                 (0x80)
#define MCF5329_GPIO_PAR_BUSCTL_PAR_OE_GPIO            (0x00)
#define MCF5329_GPIO_PAR_BUSCTL_PAR_OE_OE              (0x80)
#define MCF5329_GPIO_PAR_BUSCTL_PAR_TA_GPIO            (0x00)
#define MCF5329_GPIO_PAR_BUSCTL_PAR_TA_TA              (0x40)
#define MCF5329_GPIO_PAR_BUSCTL_PAR_RWB_GPIO           (0x00)
#define MCF5329_GPIO_PAR_BUSCTL_PAR_RWB_RWB            (0x20)
#define MCF5329_GPIO_PAR_BUSCTL_PAR_TS_GPIO            (0x00)
#define MCF5329_GPIO_PAR_BUSCTL_PAR_TS_DACK0           (0x10)
#define MCF5329_GPIO_PAR_BUSCTL_PAR_TS_TS              (0x18)

/* Bit definitions and macros for PAR_FECI2C */
#define MCF5329_GPIO_PAR_FECI2C_MDC_EMDC        (0xC0)
#define MCF5329_GPIO_PAR_FECI2C_MDIO_EMDIO      (0x30)
#define MCF5329_GPIO_PAR_FECI2C_SCL_I2C_SCL     (0x0C)
#define MCF5329_GPIO_PAR_FECI2C_SDA_I2C_SDA     (0x03)
#define MCF5329_GPIO_PAR_FECI2C_SDA_I2C_CANTX   (0x08)
#define MCF5329_GPIO_PAR_FECI2C_SDA_I2C_CANRX   (0x02)


/* Bit definitions and macros for MCF_GPIO_PAR_BE */
#define MCF5329_GPIO_PAR_BE_PAR_BE0                    (0x01)
#define MCF5329_GPIO_PAR_BE_PAR_BE1                    (0x02)
#define MCF5329_GPIO_PAR_BE_PAR_BE2                    (0x04)
#define MCF5329_GPIO_PAR_BE_PAR_BE3                    (0x08)

/* Bit definitions and macros for MCF5329_GPIO_PAR_CS */
#define MCF5329_GPIO_PAR_CS_PAR_CS1                    (0x02)
#define MCF5329_GPIO_PAR_CS_PAR_CS2                    (0x04)
#define MCF5329_GPIO_PAR_CS_PAR_CS3                    (0x08)
#define MCF5329_GPIO_PAR_CS_PAR_CS4                    (0x10)
#define MCF5329_GPIO_PAR_CS_PAR_CS5                    (0x20)
#define MCF5329_GPIO_PAR_CS_PAR_CS_CS1_GPIO            (0x00)
#define MCF5329_GPIO_PAR_CS_PAR_CS_CS1_SDCS1           (0x01)
#define MCF5329_GPIO_PAR_CS_PAR_CS_CS1_CS1             (0x03)

/* Bit definitions and macros for PAR_SSI */
#define MCF5329_GPIO_PAR_SSI_BCLK_SSI_BCLK      (0xC000)
#define MCF5329_GPIO_PAR_SSI_BCLK_U2CTS         (0x8000)
#define MCF5329_GPIO_PAR_SSI_BCLK_PWM7          (0x4000)
#define MCF5329_GPIO_PAR_SSI_BCLK_GPIO          (0x0000)
#define MCF5329_GPIO_PAR_SSI_FS_SSI_FS          (0x3000)
#define MCF5329_GPIO_PAR_SSI_FS_U2RTS           (0x2000)
#define MCF5329_GPIO_PAR_SSI_FS_PWM5            (0x1000)
#define MCF5329_GPIO_PAR_SSI_FS_GPIO            (0x0000)
#define MCF5329_GPIO_PAR_SSI_RXD_SSI_RXD        (0x0C00)
#define MCF5329_GPIO_PAR_SSI_RXD_U2RXD          (0x0800)
#define MCF5329_GPIO_PAR_SSI_RXD_CANRX          (0x0400)
#define MCF5329_GPIO_PAR_SSI_RXD_GPIO           (0x0000)
#define MCF5329_GPIO_PAR_SSI_TXD_SSI_TXD        (0x0300)
#define MCF5329_GPIO_PAR_SSI_TXD_U2TXD          (0x0200)
#define MCF5329_GPIO_PAR_SSI_TXD_CANTX          (0x0100)
#define MCF5329_GPIO_PAR_SSI_TXD_GPIO           (0x0000)
#define MCF5329_GPIO_PAR_SSI_MCLK               (0x0080)	

/* Bit definitions and macros for PAR_UART */
#define MCF5329_GPIO_PAR_UART_UTXD0             (0x0001)
#define MCF5329_GPIO_PAR_UART_URXD0             (0x0002)
#define MCF5329_GPIO_PAR_UART_URTS0             (0x0004)
#define MCF5329_GPIO_PAR_UART_UCTS0             (0x0008)
#define MCF5329_GPIO_PAR_UART_UTXD1_GPIO        (0x0000)
#define MCF5329_GPIO_PAR_UART_UTXD1_SSI_TXD     (0x0020)
#define MCF5329_GPIO_PAR_UART_UTXD1             (0x0030)
#define MCF5329_GPIO_PAR_UART_URXD1_GPIO        (0x0000)
#define MCF5329_GPIO_PAR_UART_URXD1_SSI_RXD     (0x0080)
#define MCF5329_GPIO_PAR_UART_URXD1             (0x00C0)
#define MCF5329_GPIO_PAR_UART_URTS1_GPIO        (0x0000)
#define MCF5329_GPIO_PAR_UART_URTS1_SSI_FS      (0x0200)
#define MCF5329_GPIO_PAR_UART_URTS1_URTS1       (0x0300)
#define MCF5329_GPIO_PAR_UART_UCTS1_GPIO        (0x0000)
#define MCF5329_GPIO_PAR_UART_UCTS1_SSI_BCLK    (0x0800)
#define MCF5329_GPIO_PAR_UART_UCTS1_UCTS1       (0x0C00)

/* Bit definitions and macros for PAR_QSPI */
#define MCF5329_GPIO_PAR_QSPI_SCK                   (0x0030)
#define MCF5329_GPIO_PAR_QSPI_I2C_SCL               (0x0020)
#define MCF5329_GPIO_PAR_QSPI_SCK_GPIO              (0x0000)
#define MCF5329_GPIO_PAR_QSPI_DOUT                  (0x00C0)
#define MCF5329_GPIO_PAR_QSPI_I2C_SDA               (0x0080)
#define MCF5329_GPIO_PAR_QSPI_DOUT_GPIO             (0x0000)
#define MCF5329_GPIO_PAR_QSPI_DIN                   (0x0300)
#define MCF5329_GPIO_PAR_QSPI_DIN_U2CTS             (0x0200)
#define MCF5329_GPIO_PAR_QSPI_DIN_GPIO              (0x0000)
#define MCF5329_GPIO_PAR_QSPI_PCS0                  (0x0C00)
#define MCF5329_GPIO_PAR_QSPI_PCS0_PWM5             (0x8000)
#define MCF5329_GPIO_PAR_QSPI_PCS0_GPIO             (0x0000)
#define MCF5329_GPIO_PAR_QSPI_PCS1                  (0x3000)
#define MCF5329_GPIO_PAR_QSPI_PWM7                  (0x2000)
#define MCF5329_GPIO_PAR_QSPI_GPIO                  (0x0000)
#define MCF5329_GPIO_PAR_QSPI_PCS2                  (0xC000)
#define MCF5329_GPIO_PAR_QSPI_PCS2_U2RTS            (0x8000)
#define MCF5329_GPIO_PAR_QSPI_PCS2_GPIO             (0xC000)

/* Bit definitions and macros for PAR_TIMER */
#define MCF5329_GPIO_PAR_TIMER_TIN3_TIN3        (0xC0)
#define MCF5329_GPIO_PAR_TIMER_TIN3_TOUT3       (0x80)
#define MCF5329_GPIO_PAR_TIMER_TIN3_URXD2       (0x40)
#define MCF5329_GPIO_PAR_TIMER_TIN3_GPIO        (0x00)
#define MCF5329_GPIO_PAR_TIMER_TIN2_UTXD2       (0x10)
#define MCF5329_GPIO_PAR_TIMER_TIN2_TOUT2       (0x20)
#define MCF5329_GPIO_PAR_TIMER_TIN2_TIN2        (0x30)
#define MCF5329_GPIO_PAR_TIMER_TIN2_GPIO        (0x00)
#define MCF5329_GPIO_PAR_TIMER_TIN1_TIN1        (0x0C)
#define MCF5329_GPIO_PAR_TIMER_TIN1_TOUT1       (0x08)
#define MCF5329_GPIO_PAR_TIMER_TIN1_DACK1       (0x04)
#define MCF5329_GPIO_PAR_TIMER_TIN1_GPIO        (0x00)
#define MCF5329_GPIO_PAR_TIMER_TIN0_TIN0        (0x03)
#define MCF5329_GPIO_PAR_TIMER_TIN0_TOUT0       (0x02)
#define MCF5329_GPIO_PAR_TIMER_TIN0_DREQ0       (0x01)
#define MCF5329_GPIO_PAR_TIMER_TIN0_GPIO        (0x00)

/* Bit definitions and macros for MCF_GPIO_PAR_LCDDATA */
#define MCF5329_GPIO_PAR_LCDDATA_PAR_LD7_0(x)          (((x)&0x03)<<0)
#define MCF5329_GPIO_PAR_LCDDATA_PAR_LD15_8(x)         (((x)&0x03)<<2)
#define MCF5329_GPIO_PAR_LCDDATA_PAR_LD16(x)           (((x)&0x03)<<4)
#define MCF5329_GPIO_PAR_LCDDATA_PAR_LD17(x)           (((x)&0x03)<<6)
/* Bit definitions and macros for MCF_GPIO_PAR_LCDCTL */
#define MCF5329_GPIO_PAR_LCDCTL_PAR_CLS                (0x0001)
#define MCF5329_GPIO_PAR_LCDCTL_PAR_PS                 (0x0002)
#define MCF5329_GPIO_PAR_LCDCTL_PAR_REV                (0x0004)
#define MCF5329_GPIO_PAR_LCDCTL_PAR_SPL_SPR            (0x0008)
#define MCF5329_GPIO_PAR_LCDCTL_PAR_CONTRAST           (0x0010)
#define MCF5329_GPIO_PAR_LCDCTL_PAR_LSCLK              (0x0020)
#define MCF5329_GPIO_PAR_LCDCTL_PAR_LP_HSYNC           (0x0040)
#define MCF5329_GPIO_PAR_LCDCTL_PAR_FLM_VSYNC          (0x0080)
#define MCF5329_GPIO_PAR_LCDCTL_PAR_ACD_OE             (0x0100)
/* Bit definitions and macros for MCF_GPIO_PAR_IRQ */
#define MCF5329_GPIO_PAR_IRQ_PAR_IRQ1(x)               (((x)&0x0003)<<4)
#define MCF5329_GPIO_PAR_IRQ_PAR_IRQ2(x)               (((x)&0x0003)<<6)
#define MCF5329_GPIO_PAR_IRQ_PAR_IRQ4(x)               (((x)&0x0003)<<8)
#define MCF5329_GPIO_PAR_IRQ_PAR_IRQ5(x)               (((x)&0x0003)<<10)
#define MCF5329_GPIO_PAR_IRQ_PAR_IRQ6(x)               (((x)&0x0003)<<12)

/* Bit definitions for MSCR_SDRAM */
#define MCF5329_GPIO_MSCR_SDRAM_MSCR_SDRAM(x)    ((x)&0x3)
#define MCF5329_GPIO_MSCR_SDRAM_MSCR_SDCLK(x)    (((x)&0x3)<<2)
#define MCF5329_GPIO_MSCR_SDRAM_MSCR_SDCLKB(x)   (((x)&0x3)<<4)

/* Bit definitions and macros for PAR_IRQ */

#define MCF5329_GPIO_PAR_IRQ_IRQ2_USBH_CLKIN      (0x0008)
#define MCF5329_GPIO_PAR_IRQ_IRQ5_USBH_VBUSOC     (0x0800)
#define MCF5329_GPIO_PAR_IRQ_IRQ2_USBH_VBUSEN     (0x2000)

/*------------------------------------------------------------------------*/
/*
** Chip select macros
*/

/* Bit definitions and macros for Chip-Select Address Registers */
#define MCF5329_CS_CSAR_BA(x)                   ((x)&0xFFFF0000)

/* Bit definitions and macros for Chip-Select Mask Registers */
#define MCF5329_CS_CSMR_BAM_4G                  (0xFFFF0000)
#define MCF5329_CS_CSMR_BAM_2G                  (0x7FFF0000)
#define MCF5329_CS_CSMR_BAM_1G                  (0x3FFF0000)
#define MCF5329_CS_CSMR_BAM_1024M               (0x3FFF0000)
#define MCF5329_CS_CSMR_BAM_512M                (0x1FFF0000)
#define MCF5329_CS_CSMR_BAM_256M                (0x0FFF0000)
#define MCF5329_CS_CSMR_BAM_128M                (0x07FF0000)
#define MCF5329_CS_CSMR_BAM_64M                 (0x03FF0000)
#define MCF5329_CS_CSMR_BAM_32M                 (0x01FF0000)
#define MCF5329_CS_CSMR_BAM_16M                 (0x00FF0000)
#define MCF5329_CS_CSMR_BAM_8M                  (0x007F0000)
#define MCF5329_CS_CSMR_BAM_4M                  (0x003F0000)
#define MCF5329_CS_CSMR_BAM_2M                  (0x001F0000)
#define MCF5329_CS_CSMR_BAM_1M                  (0x000F0000)
#define MCF5329_CS_CSMR_BAM_1024K               (0x000F0000)
#define MCF5329_CS_CSMR_BAM_512K                (0x00070000)
#define MCF5329_CS_CSMR_BAM_256K                (0x00030000)
#define MCF5329_CS_CSMR_BAM_128K                (0x00010000)
#define MCF5329_CS_CSMR_BAM_64K                 (0x00000000)
#define MCF5329_CS_CSMR_WP                      (0x00000100)
#define MCF5329_CS_CSMR_V                       (0x00000001)

/* Bit definitions and macros for Chip-Select Control Registers */
#define MCF5329_CS_CSCR_SWS(x)                  (((x)&0x0000003F)<<26)
#define MCF5329_CS_CSCR_SWSEN                   (0x00800000)
#define MCF5329_CS_CSCR_ASET(x)                 (((x)&0x00000003)<<20)
#define MCF5329_CS_CSCR_RDAH(x)                 (((x)&0x00000003)<<18)
#define MCF5329_CS_CSCR_WRAH(x)                 (((x)&0x00000003)<<16)
#define MCF5329_CS_CSCR_WS(x)                   (((x)&0x0000003F)<<10)
#define MCF5329_CS_CSCR_SBM                     (0x00000200)
#define MCF5329_CS_CSCR_AA                      (0x00000100)
#define MCF5329_CS_CSCR_PS_8                    (0x00000040)
#define MCF5329_CS_CSCR_PS_16                   (0x00000080)
#define MCF5329_CS_CSCR_PS_32                   (0x00000000)
#define MCF5329_CS_CSCR_BEM                     (0x00000020)
#define MCF5329_CS_CSCR_BSTR                    (0x00000010)
#define MCF5329_CS_CSCR_BSTW                    (0x00000008)


/*------------------------------------------------------------------------*/
/*
** Clock definitions
*/


/*------------------------------------------------------------------------*/
/*
** Power Management definitions
*/
#define MCF5329_CLOCK_MISCCR_LOCK               (0x2000)
#define MCF5329_CLOCK_MISCCR_LIMP               (0x1000)
#define MCF5329_CLOCK_MISCCR_LCDCHEN            (0x0100)    /* LCDC HCLK input enable */
#define MCF5329_CLOCK_MISCCR_SSIPUE             (0x0080)    /* SSI RXD/TXD pull enable */
#define MCF5329_CLOCK_MISCCR_SSIPUS             (0x0040)    /* SSI RXD/TXD pull select */
#define MCF5329_CLOCK_MISCCR_TIMDMA             (0x0020)    /* Timer DMA mux selection */
#define MCF5329_CLOCK_MISCCR_SSISRC             (0x0010)    /* PLL drives SSI baud clock */
#define MCF5329_CLOCK_MISCCR_USBDIV             (0x0002)    /* USB clock divisor */
#define MCF5329_CLOCK_MISCCR_USBSRC             (0x0001)    /* USB clock source */

#define MCF5329_CLOCK_CDR_LPDIV(x)              (((x)&0x0000000F) << 8)
#define MCF5329_CLOCK_CDR_SSIDIV(x)             ((x)&0x0000000F)


/* Bit definitions and macros for PLL_ODR */
#define MCF5329_PLL_ODR_CPUDIV(x)                     ((x) & 0xF0)
#define MCF5329_PLL_ODR_BUSDIV(x)                     ((x) & 0x0F)

/* Bit definitions and macros for PLL_CR */
#define MCF5329_PLL_CR_DITHEN                         (0x80)
#define MCF5329_PLL_CR_DITHDEV(x)                     ((x) & 0x07)

/* Bit definitions and macros for PLL_MDR */
#define MCF5329_PLL_MDR_MODDIV(x)                     ((x) & 0xFF)

/* Bit definitions and macros for PLL_FDR */
#define MCF5329_PLL_FDR_MFD(x)                        ((x) & 0xFF)


/*------------------------------------------------------------------------*/
/*
**                      TYPE DEFINITIONS
*/

/*
** SCM Registers
*/
typedef struct mcf5329_scm_a_struct {
    uint_32 MPR0;
    uchar   filler0[0x1C];
    uint_32 PACRA;
    uint_32 PACRB;
    uint_32 PACRC;
    uint_32 PACRD;
    uchar   filler1[0x10];
    uint_32 PACRE;
    uint_32 PACRF;
    uint_32 PACRG;
    uint_32 filler2[2];
    uint_32 BMT0;
} MCF5329_SCM_A_STRUCT, _PTR_ MCF5329_SCM_A_STRUCT_PTR;
typedef volatile struct mcf5329_scm_a_struct _PTR_ VMCF5329_SCM_A_STRUCT_PTR;



typedef struct mcf5329_scm_b_struct {
    uint_8 filler0[0x13];
    uint_8 WCR;
    uint_8 filler1[0x02];
    uint_16 CWCR;
    uint_8 filler2[0x03];  
    uint_8 CWSR;
    uint_8 filler3[0x03];
    uint_8 SCMISR; 
    uint_8 filler4[0x04];
    uint_32 BCR;   
    uint_8 filler5[0x48];
    uint_32 CFADR;
    uint_8 filler6[0x01];
    uint_8 CFIER;
    uint_8 CFLOC;  
    uint_8 CFATR; 
    uint_8 filler7[0x04];
    uint_32 CFDTR;
} MCF5329_SCM_B_STRUCT, _PTR_ MCF5329_SCM_B_STRUCT_PTR;
typedef volatile struct mcf5329_scm_b_struct _PTR_ VMCF5329_SCM_B_STRUCT_PTR;


/*
** MCF5329_TCD_STRUCT
** This structure defines what one Transfer Control Descriptor look like
*/
typedef struct mcf5329_tcd_struct
{
   uint_32 SADDR;               /* Source Address */
   uint_16 ATTR;                /* Transfer Attrbutes */
   uint_16 SOFF;                /* Signed Source Address Offset */
   uint_32 NBYTES;              /* Minor Byte Count */
   uint_32 SLAST;               /* Last Source Address Adjustment */
   uint_32 DADDR;               /* Destination Address */
   uint_16 CITER;               /* Current Minor Loop Link, Major Loop Count */
   uint_16 DOFF;                /* Signed Destination Address Offset */
   uint_32 DLAST_SGA;           /* Last Destination Address Adjustment/Scatter Gather Address */
   uint_16 BITER;               /* Beginning Minor Loop Link, Major Loop Count */
   uint_16 CSR;                 /* Control and Status Register */

} MCF5329_TCD_STRUCT, _PTR_ MCF5329_TCD_STRUCT_PTR;
typedef volatile struct mcf5329_tcd_struct _PTR_ VMCF5329_TCD_STRUCT_PTR;


/*
** MCF5329_EDMA_STRUCT
** This structure defines what one DMA registers look like
*/
typedef struct mcf5329_edma_struct
{
   uint_32 CR;                  /* eDMA Control Register */
   uint_32 ES;                  /* eDMA Error Status Register */
   uchar   filler1[6];
   uint_16 ERQ;                 /* eDMA Enable Request Register */
   uchar   filler2[6];
   uint_16 EEI;                 /* eDMA Enable Error Interrupt Register */
   uchar   SERQ;                /* eDMA Set Enable Request Register */
   uchar   CERQ;                /* eDMA Clear Enable Request Register */
   uchar   SEEI;                /* eDMA Set Enable Error Interrupt Register */
   uchar   CEEI;                /* eDMA Clear Enable Error Interrupt Register */
   uchar   CINT;                /* eDMA Clear Interrupt Request Register */
   uchar   CERR;                /* eDMA Clear Error Register */
   uchar   SSRT;                /* eDMA Set START Bit Register */
   uchar   CDNE;                /* eDMA Clear DONE Status Bit Register */
   uchar   filler3[6];
   uint_16 INT;                 /* eDMA Interrupt Request Register */
   uchar   filler4[6];
   uint_16 ERR;                 /* eDMA Error Register */
   uchar   filler5[208];
   uchar   DCHPRI[16];          /* eDMA Channel Priority Registers */
   uchar   filler6[3823];
   MCF5329_TCD_STRUCT TCD[16];  /* Transfer Control Descriptors */
   /*uchar   filler7[11776]; */

} MCF5329_EDMA_STRUCT, _PTR_ MCF5329_EDMA_STRUCT_PTR;
typedef volatile struct mcf5329_edma_struct _PTR_ VMCF5329_EDMA_STRUCT_PTR;


/*
** MCF5329_CS_STRUCT
** Chip selects
*/
typedef struct mcf5329_cs_struct
{
   uint_32 CSAR;                /* Chip Select Address Register */
   uint_32 CSMR;                /* Chip Select Mask Register */
   uint_32 CSCR;                /* Chip Select Control Register */
   
} MCF5329_CS_STRUCT, _PTR_ MCF5329_CS_STRUCT_PTR;
typedef volatile struct mcf5329_cs_struct _PTR_ VMCF5329_CS_STRUCT_PTR;

/*
/** MCF5329_TIMER_STRUCT
** This structure defines what one timer register look like
*/
typedef struct mcf5329_dma_timer_struct
{
   uint_16 DTMR;                /* DMA Timer Mode Register */
   uchar   DTXTMR;              /* DMA Timer Extended Mode Register */
   uchar   DTER;                /* DMA Timer Event Register */
   uint_32 DTRR;                /* DMA Timer Reference Register */
   uint_32 DTCR;                /* DMA Timer Capture Register */
   uint_32 DTCN;                /* DMA Timer Counter Register */
   uchar   filler1[16368];
   
} MCF5329_DMA_TIMER_STRUCT, _PTR_ MCF5329_DMA_TIMER_STRUCT_PTR;
typedef volatile struct mcf5329_dma_timer_struct _PTR_ VMCF5329_DMA_TIMER_STRUCT_PTR;


/*
** MCF5329_WATCHDOG_STRUCT
** Watchdog timer
*/
typedef struct mcf5329_watchdog_struct
{
   uint_16 WCR;         /* Watchdog control register */
   uint_16 WMR;         /* Watchdog modulus register */
   uint_16 WCNTR;       /* Watchdog count register */
   uint_16 WSR;         /* Watchdog service register   */

} MCF5329_WATCHDOG_STRUCT, _PTR_ MCF5329_WATCHDOG_STRUCT_PTR;
typedef volatile struct mcf5329_watchdog_struct _PTR_ VMCF5329_WATCHDOG_STRUCT_PTR;

/*
** PSP_PIT_STRUCT
** Programmable interrupt timer
*/
typedef struct psp_pit_struct
{
   uint_16 PCSR;                /* PIT control and status register */
   uint_16 PMR;                 /* PIT modulus register */
   uint_16 PCNTR;               /* PIT count register */
   uchar   filler1[16378];

} PSP_PIT_STRUCT, _PTR_ PSP_PIT_STRUCT_PTR;
typedef volatile struct psp_pit_struct _PTR_ VPSP_PIT_STRUCT_PTR;
/*
** PSP_RCP_STRUCT
** Reset control, chip config, & power management
*/
typedef struct psp_rcp_struct
{
   uchar   RCR;             /* Reset Control Register */
   uchar   RSR;             /* Reset Status Register */
   uchar   filler1[2];
   uint_16 CCR;             /* Chip Configuration Register */
   uchar   filler2;
   uchar   LPCR;            /* Low-Power Control Register */
   uint_16 RCON;            /* Reset Configuration Register */
   uint_16 CIR;             /* Chip Identification Register */
   uchar   filler3[3];
   uint_16 MISCCR;          /* Miscellaneous Control Register */
   uint_16 CDR;             /* Clock Divider Register */
   uint_16 UHCSR;
   uint_16 UOCSR;           /*OTG Status Register */

} PSP_RCP_STRUCT, _PTR_ PSP_RCP_STRUCT_PTR;
typedef volatile struct psp_rcp_struct _PTR_ VPSP_RCP_STRUCT_PTR;


/*
** PSP_CLK_STRUCT
** Clock module registers
*/
typedef struct mcf5329_pll_struct
{
   uchar PODR;              /* PLL Output Divider Register */
   uchar filler1[3];
   uchar PCR;               /* PLL Control Register */
   uchar filler2[3];
   uchar PMDR;              /* PLL Modulation Divider Register */
   uchar filler3[3];
   uchar PFDR;              /* PLL Feedback Divider Register */

} MCF5329_PLL_STRUCT, _PTR_ MCF5329_PLL_STRUCT_PTR;
typedef volatile struct mcf5329_pll_struct _PTR_ VMCF5329_PLL_STRUCT_PTR;

/*
** MCF5329_SSI_STRUCT
** Synchronous Serial Interface
*/
typedef struct mcf5329_ssi_struct
{
   uint_32 SSI_TX0;          /* SSI Transmit Data Register 0 */
   uint_32 SSI_TX1;          /* SSI Transmit Data Register 1 */
   uint_32 SSI_RX0;          /* SSI Receive Data Register 0 */
   uint_32 SSI_RX1;          /* SSI Receive Data Register 1 */
   uint_32 SSI_CR;           /* SSI Control Register */
   uint_32 SSI_ISR;          /* SSI Interrupt Status Register */
   uint_32 SSI_IER;          /* SSI Interrupt Enable Register */
   uint_32 SSI_TCR;          /* SSI Transmit Configuration Register */
   uint_32 SSI_RCR;          /* SSI Receive Configuration Register */
   uint_32 SSI_CCR;          /* SSI Clock Control Register */
   uint_32 SSI_FCSR;         /* SSI FIFO Control/Status Register */
   uint_32 SSI_ACR;          /* SSI AC97 Control Register */
   uint_32 SSI_ACADD;        /* SSI AC97 Command Address Register */
   uint_32 SSI_ACDAT;        /* SSI AC97 Command Data Register */
   uint_32 SSI_ATAG;         /* SSI AC97 Tag Register */
   uint_32 SSI_TMASK;        /* SSI Transmit Time Slot Mask Register */
   uint_32 SSI_RMASK;        /* SSI Receive Time Slot Mask Register */

} MCF5329_SSI_STRUCT, _PTR_ MCF5329_SSI_STRUCT_PTR;
typedef volatile struct mcf5329_ssi_struct _PTR_ VMCF5329_SSI_STRUCT_PTR;


/*
** MCF5329_GPIO_STRUCT
** GPIO Registers
*/

typedef struct mcf5329_gpio_struct
{
   uchar PODR_FECH, PODR_FECL, PODR_SSI, PODR_BUSCTL;     /* Port ouput Data Registers */
   uchar PODR_BE, PODR_CS, PODR_PWM, PODR_FECI2C;
   uchar filler1;
   uchar PODR_UART, PODR_QSPI, PODR_TIMER;
   uchar filler2;
   uchar PODR_LCDDATAH, PODR_LCDDATAM, PODR_LCDDATAL;
   uchar PODR_LCDCTLH, PODR_LCDCTLL;
   uchar filler3[2];
   uchar PDDR_FECH, PDDR_FECL, PDDR_SSI, PDDR_BUSCTL;     /* Port Data Direction Registers */
   uchar PDDR_BE, PDDR_CS, PDDR_PWM, PDDR_FECI2C;
   uchar filler4;
   uchar PDDR_UART, PDDR_QSPI, PDDR_TIMER;
   uchar filler5;
   uchar PDDR_LCDDATAH, PDDR_LCDDATAM, PDDR_LCDDATAL;
   uchar PDDR_LCDCTLH, PDDR_LCDCTLL;
   uchar filler6[2];
   uchar PPDSDR_FECH, PPDSDR_FECL, PPDSDR_SSI;            /* Port Pin Data/Set Data Registers */
   uchar PPDSDR_BUSCTL, PPDSDR_BE, PPDSDR_CS;
   uchar PPDSDR_PWM, PPDSDR_FECI2C;
   uchar filler7;
   uchar PPDSDR_UART, PPDSDR_QSPI, PPDSDR_TIMER;
   uchar filler8;
   uchar PPDSDR_LCDDATAH, PPDSDR_LCDDATAM, PPDSDR_LCDDATAL;
   uchar PPDSDR_LCDCTLH, PPDSDR_LCDCTLL;
   uchar filler9[2];
   uchar PCLRR_FECH, PCLRR_FECL, PCLRR_SSI;               /* Port Clear Output Data Registers */
   uchar PCLRR_BUSCTL, PCLRR_BE, PCLRR_CS;
   uchar PCLRR_PWM, PCLRR_FECI2C;
   uchar filler10;
   uchar PCLRR_UART, PCLRR_QSPI, PCLRR_TIMER;
   uchar filler11;
   uchar PCLRR_LCDDATAH, PCLRR_LCDDATAM;
   uchar PCLRR_LCDDATAL, PCLRR_LCDCTLH, PCLRR_LCDCTLL;
   uchar filler12[2];
   uchar PAR_FEC, PAR_PWM, PAR_BUSCTL, PAR_FECI2C;        /* Pin Assignment Registers */
   uchar PAR_BE, PAR_CS;
   uint_16 PAR_SSI, PAR_UART, PAR_QSPI;
   uchar PAR_TIMER, PAR_LCDDATA;
   uint_16 PAR_LCDCTL, PAR_IRQ;
   uchar filler13[2];
   uchar MSCR_FLEXBUS, MSCR_SDRAM;                        /* Mode Select Control Registers */
   uchar filler14[2];
   uchar DSCR_I2C, DSCR_PWM, DSCR_FEC, DSCR_UART;         /* Drive Strength Control Registers */
   uchar DSCR_QSPI, DSCR_TIMER, DSCR_SSI, DSCR_LCD;
   uchar DSCR_DEBUG, DSCR_CLKRST, DSCR_IRQ;
   
}  MCF5329_GPIO_STRUCT, _PTR_ MCF5329_GPIO_STRUCT_PTR;
typedef volatile struct mcf5329_gpio_struct _PTR_ VMCF5329_GPIO_STRUCT_PTR;

/*
** MCF5329_LCDC_STRUCT
** Liquid Crystal Display Controller
*/
typedef struct mcf5329_lcdc_struct
{
   uint_32 LCD_SSAR;          /* Screen Start Address Register */
   uint_32 LCD_SR;            /* LCD Size Register */
   uint_32 LCD_VPW;           /* LCD Virtual Page Width Register */
   uint_32 LCD_CPR;           /* LCD Cursor Position Register */
   uint_32 LCD_CWHB;          /* LCD Cursor Width Height and Blink Register */
   uint_32 LCD_CCMR;          /* LCD Color Cursor Mapping Register */
   uint_32 LCD_PCR;           /* LCD Panel Configuration Register */
   uint_32 LCD_HCR;           /* LCD Horizontal Configuration Register */
   uint_32 LCD_VCR;           /* LCD Vertical Configuration Register */
   uint_32 LCD_POR;           /* LCD Panning Offset Register */
   uint_32 LCD_SCR;           /* LCD Sharp Configuration Register */
   uint_32 LCD_PCCR;          /* LCD PWM Contrast Control Register */
   uint_32 LCD_DCR;           /* LCD DMA Control Register */
   uint_32 LCD_RMCR;          /* LCD Refresh Mode Control Register */
   uint_32 LCD_ICR;           /* LCD Interrupt Configuration Register */
   uint_32 LCD_IER;           /* LCD Interrupt Enable Register */
   uint_32 LCD_ISR;           /* LCD Interrupt Status Register */
   uint_32 LCD_GWSAR;         /* LCD Graphic Window Start Address Register */
   uint_32 LCD_GWSR;          /* LCD Graphic Window Size Register */
   uint_32 LCD_GWVPW;         /* LCD Graphic Window Virtual Page Width Register */
   uint_32 LCD_GWPOR;         /* LCD Graphic Window Panning Offset Register */
   uint_32 LCD_GWPR;          /* LCD Graphic Window Position Register */
   uint_32 LCD_GWCR;          /* LCD Graphic Window Control Register */
   uint_32 LCD_GWDCR;         /* LCD Graphic Window DMA Control Register */
   uint_32 BGLUT[0x3FC];      /* Background Look-up Table */
   uint_32 GWLUT[0x3FC];      /* Graphic Window Look-up Table */
   
} MCF5329_LCDC_STRUCT, _PTR_ MCF5329_LCDC_STRUCT_PTR;
typedef volatile struct mcf5329_lcdc_struct _PTR_ VMCF5329_LCDC_STRUCT_PTR;


/*
** MCF5329_FEC_BD_STRUCT
** This structure defines what the Ethernet buffer descriptor looks like
*/
typedef struct mcf5329_fec_bd_struct
{
   uint_16   CONTROL;
   uint_16   LENGTH;
   uchar_ptr BUFFER;
   
} MCF5329_FEC_BD_STRUCT, _PTR_ MCF5329_FEC_BD_STRUCT_PTR;
typedef volatile struct mcf5329_fec_bd_struct _PTR_ VMCF5329_FEC_BD_STRUCT_PTR;


/*
** MCF5329_FEC_STRUCT
** Fast Ethernet Controller
*/
typedef struct mcf5329_fec_struct
{
   uchar   filler1[4];
   uint_32 EIR;             /* Interrupt Event register */
   uint_32 EIMR;            /* Interrupt Mask register    */
   uchar   filler2[4];   
   uint_32 RDAR;            /* Receive Descriptor Active Register */
   uint_32 TDAR;            /* Transmit Descriptor Active Register */
   uchar   filler3[12];
   uint_32 ECR;             /* Ethernet Control Register */
   uchar   filler4[24];
#define MMFR MDATA
   uint_32 MDATA;           /* MII Data Register */
   uint_32 MSCR;            /* MII Speed Control Register */
   uchar   filler5[28];
   uint_32 MIBC;            /* MIB Control/Status Register */
   uchar   filler6[28];
   uint_32 RCR;             /* Receive Control Register */
   uchar   filler7[60];
   uint_32 TCR;             /* Transmit Control Register */
   uchar   filler8[28];
   uint_32 PALR;            /* Physical Address Low Register */
   uint_32 PAUR;            /* Physical Address High Register */
   uint_32 OPD;             /* Opcode/Pause Duration */
   uchar   filler9[40];
   uint_32 IAUR;            /* Upper 32-bits of Individual Hash Table */
   uint_32 IALR;            /* Lower 32-bits of Individual Hash Table */
   uint_32 GAUR;            /* Upper 32-bits of Group Hash Table */
   uint_32 GALR;            /* Lower 32-bits of Group Hash Table */
   uchar   filler10[28];
   uint_32 TFWR;            /* Transmit FIFO Watermark */
   uchar   filler11[4];
   uint_32 FRBR;            /* FIFO Receive Bound Register */
   uint_32 FRSR;            /* FIFO Receive FIFO Start Register */
   uchar   filler12[44];
   uint_32 ERDSR;           /* Pointer to Receive Descriptor Ring */
   uint_32 ETDSR;           /* Pointer to Receive Descriptor Ring */
   uint_32 EMRBR;           /* Maximum Receive Buffer Size */
   uchar   filler13[116];
   uchar   MIB_RAM[512];    /* RAM to store FEC Counters */
   
} MCF5329_FEC_STRUCT, _PTR_ MCF5329_FEC_STRUCT_PTR;
typedef volatile struct mcf5329_fec_struct _PTR_ VMCF5329_FEC_STRUCT_PTR;


/*
** MCF5329_IACK_STRUCT
** Interrupt acknowledgements
*/
typedef struct mcf5329_iack_struct
{
   uchar L1IACK;                /* Level 1 Interrupt Acknowledge Register */
   uchar filler2[3];
   uchar L2IACK;                /* Level 2 Interrupt Acknowledge Register */
   uchar filler3[3];
   uchar L3IACK;                /* Level 3 Interrupt Acknowledge Register */
   uchar filler4[3];
   uchar L4IACK;                /* Level 4 Interrupt Acknowledge Register */
   uchar filler5[3];
   uchar L5IACK;                /* Level 5 Interrupt Acknowledge Register */
   uchar filler6[3];
   uchar L6IACK;                /* Level 6 Interrupt Acknowledge Register */
   uchar filler7[3];
   uchar L7IACK;                /* Level 7 Interrupt Acknowledge Register */
   uchar filler8[3];

} MCF5329_IACK_STRUCT, _PTR_ MCF5329_IACK_STRUCT_PTR;
typedef volatile struct mcf5329_iack_struct _PTR_ VMCF5329_IACK_STRUCT_PTR;


/*
** MCF5329_ICTRL_STRUCT
** Interrupt controller
*/
typedef struct mcf5329_ictrl_struct
{
   uint_32  IPRH;                /* Interrupt Pending Register High */
   uint_32  IPRL;                /* Interrupt Pending Register Low */
   uint_32  IMRH;                /* Interrupt Mask Register High */
   uint_32  IMRL;                /* Interrupt Mask Register Low */
   uint_32  INTFRCH;             /* Interrupt Force Register High */
   uint_32  INTFRCL;             /* Interrupt Force Register Low */
   uchar    filler1[2];
   uint_16  ICONFIG;             /* Interrupt Configuration Register */
   uchar    SIMR;                /* Set Interrupt Mask */
   uchar    CIMR;                /* Clear Interrupt Mask */
   uchar    CLMASK;              /* Current Level Mask */
   uchar    SLMASK;              /* Saved Level Mask */
   uchar    filler2[32];
   uchar    ICR[64];             /* Interrupt Control Registers, 1-63 */
   uchar    filler3[96];
   uchar    SWIACK;              /* Software Interrupt Acknowledge Register */
   uchar    filler4[3];
   MCF5329_IACK_STRUCT IACK;     /* Level Interrupt Acknowledge Registers    */
   
} MCF5329_ICTRL_STRUCT, _PTR_ MCF5329_ICTRL_STRUCT_PTR;
typedef volatile struct mcf5329_ictrl_struct _PTR_ VMCF5329_ICTRL_STRUCT_PTR;

/*#define PSP_GET_ICTRL0_BASE()   \
   (&((VMCF5329_STRUCT_PTR)_PSP_GET_MBAR())->ICTRL0) */

/*#define PSP_GET_ICTRL1_BASE()   \
   (&((VMCF5329_STRUCT_PTR)_PSP_GET_MBAR())->ICTRL1) */


/*
** MCF5329_EPORT_STRUCT
** Edge Port Module
*/
typedef struct mcf5329_eport_struct
{   
   uint_16 EPPAR;               /* EPORT Pin Assignment Register */
   uchar   EPDDR;               /* EPORT Data Direction Register */
   uchar   EPIER;               /* EPORT Interrupt Enable Register */
   uchar   EPDR;                /* EPORT Data Register */
   uchar   EPPDR;               /* EPORT Pin Data Register */
   uchar   EPFR;                /* EPORT Flag Register */
   uchar   filler2[16376];
   
} MCF5329_EPORT_STRUCT, _PTR_ MCF5329_EPORT_STRUCT_PTR;
typedef volatile struct mcf5329_eport_struct _PTR_ VMCF5329_EPORT_STRUCT_PTR;


/*
** MCF5329_PWM_STRUCT
** Pulse Width Modulation
*/
typedef struct mcf5329_pwm_struct
{   
   uchar filler1[0x20];           /* Corrected from MCF5329 Reference Manual Errata */
   uchar PWME;                    /* PWM Enable Register */
   uchar PWMPOL;                  /* PWM Polarity Register */
   uchar PWMCLK;                  /* PWM Clock Select Register */
   uchar PWMPRCLK;                /* PWM Prescale Clock Select Register */
   uchar PWMCAE;                  /* PWM Center Align Enable Register */
   uchar PWMCTL;                  /* PWM Control Register */
   uchar PWMSCLA;                 /* PWM Scale A Register */
   uchar PWMSCLB;                 /* PWM Scale B Register */
   uchar PWMCNT0;                 /* PWM Channel 0 Counter Register */
   uchar PWMCNT1;                 /* PWM Channel 1 Counter Register */
   uchar PWMCNT2;                 /* PWM Channel 2 Counter Register */
   uchar PWMCNT3;                 /* PWM Channel 3 Counter Register */
   uchar PWMCNT4;                 /* PWM Channel 4 Counter Register */
   uchar PWMCNT5;                 /* PWM Channel 5 Counter Register */
   uchar PWMCNT6;                 /* PWM Channel 6 Counter Register */
   uchar PWMCNT7;                 /* PWM Channel 7 Counter Register */
   uchar PWMPER0;                 /* PWM Channel 0 Period Register */
   uchar PWMPER1;                 /* PWM Channel 1 Period Register */
   uchar PWMPER2;                 /* PWM Channel 2 Period Register */
   uchar PWMPER3;                 /* PWM Channel 3 Period Register */
   uchar PWMPER4;                 /* PWM Channel 4 Period Register */
   uchar PWMPER5;                 /* PWM Channel 5 Period Register */
   uchar PWMPER6;                 /* PWM Channel 6 Period Register */
   uchar PWMPER7;                 /* PWM Channel 7 Period Register */
   uchar PWMDTY0;                 /* PWM Channel 0 Duty Register */
   uchar PWMDTY1;                 /* PWM Channel 1 Duty Register */
   uchar PWMDTY2;                 /* PWM Channel 2 Duty Register */
   uchar PWMDTY3;                 /* PWM Channel 3 Duty Register */
   uchar PWMDTY4;                 /* PWM Channel 4 Duty Register */
   uchar PWMDTY5;                 /* PWM Channel 5 Duty Register */
   uchar PWMDTY6;                 /* PWM Channel 6 Duty Register */
   uchar PWMDTY7;                 /* PWM Channel 7 Duty Register */
   uchar PWMSDN;                  /* PWM Shutdown Register */
   
} MCF5329_PWM_STRUCT, _PTR_ MCF5329_PWM_STRUCT_PTR;
typedef volatile struct mcf5329_pwm_struct _PTR_ VMCF5329_PWM_STRUCT_PTR;


/*
** MCF5329_PWRMGMT_STRUCT
** Power Management
*/
typedef struct mcf5329_pwrmgmt_struct
{
   uchar   PPMSR0;               /* Peripheral Power Management Set Register 0 */
   uchar   PPMCR0;               /* Peripheral Power Management Clear Register 0 */
   uchar   PPMSR1;               /* Peripheral Power Management Set Register 1 */
   uchar   PPMCR1;               /* Peripheral Power Management Clear Register 1 */
   uint_32 PPMHR0;               /* Peripheral Power Management High Register 0 */
   uint_32 PPMLR0;               /* Peripheral Power Management Low Register 0 */
   uint_32 PPMHR1;               /* Peripheral Power Management High Register 1 */
   uchar   filler1[52];
   
} MCF5329_PWRMGMT_STRUCT, _PTR_ MCF5329_PWRMGMT_STRUCT_PTR;
typedef volatile struct mcf5329_pwrmgmt_struct _PTR_ VMCF5329_PWRMGMT_STRUCT_PTR;


/*
** MCF5329_XBS_STRUCT
** Cross-Bar Switch Module
*/
typedef struct mcf5329_xbs_struct
{
   uint_32 XBS_PRS1;               /* Priority Register Slave 1 */
   uchar   filler1[0xC];
   uint_32 XBS_CRS1;               /* Control Register Slave 1 */
   uchar   filler2[0x2EC];
   uint_32 XBS_PRS4;               /* Priority Register Slave 4 */
   uchar   filler3[0xC];
   uint_32 XBS_CRS4;               /* Control Register Slave 4 */
   uchar   filler4[0x1EC];
   uint_32 XBS_PRS6;               /* Priority Register Slave 6 */
   uchar   filler5[0xC];
   uint_32 XBS_CRS6;               /* Control Register Slave 6 */
   uchar   filler6[0xEC];
   uint_32 XBS_PRS7;               /* Priority Register Slave 7 */
   uchar   filler7[0xC];
   uint_32 XBS_CRS7;               /* Control Register Slave 7 */
   
} MCF5329_XBS_STRUCT, _PTR_ MCF5329_XBS_STRUCT_PTR;
typedef volatile struct mcf5329_xbs_struct _PTR_ VMCF5329_XBS_STRUCT_PTR;


/*
** MCF5329_MDHA_STRUCT
** Message Digest Hardware Accelerator
*/
typedef struct mcf5329_mdha_struct
{
   uint_32 MDMR;                /* MDHA Mode Register */
   uint_32 MDCR;                /* MDHA Control Register */
   uint_32 MDCMR;               /* MDHA Command Register */
   uint_32 MDSR;                /* MDHA Status Register */
   uint_32 MDISR;               /* MDHA Interrupt Status Register */
   uint_32 MDIMR;               /* MDHA Interrupt Mask Register */
   uchar   filler1[4];
   uint_32 MDDSR;               /* MDHA Data Size Register */
   uint_32 MDIN;                /* MDHA Input FIFO */
   uchar   filler2[0xC];
   uint_32 MDA0;                /* MDHA Message Digest A0 Register */
   uint_32 MDB0;                /* MDHA Message Digest B0 Register */
   uint_32 MDC0;                /* MDHA Message Digest C0 Register */
   uint_32 MDD0;                /* MDHA Message Digest D0 Register */
   uint_32 MDE0;                /* MDHA Message Digest E0 Register */
   uint_32 MDMDS;               /* MDHA Message Data Size Register */
   uchar   filler3[0x28];
   uint_32 MDA1;                /* MDHA Message Digest A1 Register */
   uint_32 MDB1;                /* MDHA Message Digest B1 Register */
   uint_32 MDC1;                /* MDHA Message Digest C1 Register */
   uint_32 MDD1;                /* MDHA Message Digest D1 Register */
   uint_32 MDE1;                /* MDHA Message Digest E1 Register */
   uchar   filler4[0x3F7C];

} MCF5329_MDHA_STRUCT, _PTR_ MCF5329_MDHA_STRUCT_PTR;
typedef volatile struct mcf5329_mdha_struct _PTR_ VMCF5329_MDHA_STRUCT_PTR;


/*
** MCF5329_RNG_STRUCT
** Random Number Generator
*/
typedef struct mcf5329_rng_struct
{
   uint_32 RNGCR;               /* RNG Control Register */
   uint_32 RNGSR;               /* RNG Status Register */
   uint_32 RNGER;               /* RNG Entropy Register */
   uint_32 RNGOUT;              /* RNG Ouput FIFO */

} MCF5329_RNG_STRUCT, _PTR_ MCF5329_RNG_STRUCT_PTR;
typedef volatile struct mcf5329_rng_struct _PTR_ VMCF5329_RNG_STRUCT_PTR;


/*
** MCF5329_SKHA_STRUCT
** Symmetric Key Hardware Accelerator
*/
typedef struct mcf5329_skha_struct
{
   uint_32 SKMR;               /* SKHA Mode Register */
   uint_32 SKCR;               /* SKHA Control Register */
   uint_32 SKCMR;              /* SKHA Command Register */
   uint_32 SKSR;               /* SKHA Status Register */
   uint_32 SKESR;              /* SKHA Error Status Register */
   uint_32 SKEMR;              /* SKHA Error Status Mask Register */
   uint_32 SKKSR;              /* SKHA Key Size Register */
   uint_32 SKDSR;              /* SKHA Data Size Register */
   uint_32 SKIN;               /* SKHA Input FIFO */
   uint_32 SKOUT;              /* SKHA Output FIFO */
   uchar   filler1[8];
   uint_32 SKKDR1;             /* SKHA Key Data Register 1 */
   uint_32 SKKDR2;             /* SKHA Key Data Register 2 */
   uint_32 SKKDR3;             /* SKHA Key Data Register 3 */
   uint_32 SKKDR4;             /* SKHA Key Data Register 4 */
   uint_32 SKKDR5;             /* SKHA Key Data Register 5 */
   uint_32 SKKDR6;             /* SKHA Key Data Register 6 */
   uchar   filler2[0x28];
   uint_32 SKC1;               /* SKHA Context 1 */
   uint_32 SKC2;               /* SKHA Context 2 */
   uint_32 SKC3;               /* SKHA Context 3 */
   uint_32 SKC4;               /* SKHA Context 4 */
   uint_32 SKC5;               /* SKHA Context 5 */
   uint_32 SKC6;               /* SKHA Context 6 */
   uint_32 SKC7;               /* SKHA Context 7 */
   uint_32 SKC8;               /* SKHA Context 8 */
   uint_32 SKC9;               /* SKHA Context 9 */
   uint_32 SKC10;              /* SKHA Context 10 */
   uint_32 SKC11;              /* SKHA Context 11 */
   uchar   filler3[0x3F64];
   
} MCF5329_SKHA_STRUCT, _PTR_ MCF5329_SKHA_STRUCT_PTR;
typedef volatile struct mcf5329_skha_struct _PTR_ VMCF5329_SKHA_STRUCT_PTR;


/*
** MCF5329_STRUCT
** This structure defines the memory/registers provided by the MCF5329
*/
typedef struct mcf5329_struct
{                                                               /* System Control Module */
   uint_32                        MPR1;                         /* Master Privilege Register 1 0xEC00_0000*/
   uchar                          filler1[0x3C];
   uint_32                        PACRH;                        /* Peripheral access control register H*/
   uchar                          filler2[0x10];
   uint_32                        BMT1;                         /* Bus Monitor Timeout 1 0xEC00_0054*/
   uchar                          filler3[0x7FFA8];
   MCF5329_MDHA_STRUCT            MDHA;                         /* Message Digest Hardware Accelerator */        
   MCF5329_SKHA_STRUCT            SKHA;                         /* Symmetric Key Hardware Accelerator */
   MCF5329_RNG_STRUCT             RNG;                          /* Random Number Generator */
   uchar                          filler4[0xFF77FF0];
   MCF5329_SCM_A_STRUCT           SCM_A;                         
   uchar                          filler8[0x4000 - 0 - sizeof(MCF5329_SCM_A_STRUCT)];
   MCF5329_XBS_STRUCT             XBS;                          /* Cross-Bar Switch Module */ 
   uchar                          filler9[0x8000 - 0x4000 - sizeof(MCF5329_XBS_STRUCT)];
   MCF5329_CS_STRUCT              FB[MCF5329_NUM_FB_CS ];       /* Chip Selects */
   uchar                          filler10[0x20000 - 0x8000 - MCF5329_NUM_FB_CS * sizeof(MCF5329_CS_STRUCT)];
   MCF53XX_FCAN_STRUCT            FCAN;
   uchar                          filler11[0x30000 - 0x20000 - sizeof(MCF53XX_FCAN_STRUCT)];
   MCF5329_FEC_STRUCT             FEC;                          /* Fast Ethernet Controller */
   uchar                          filler12[0x40000 - 0x30000 - sizeof(MCF5329_FEC_STRUCT)];
   
   MCF5329_SCM_B_STRUCT           SCM_B;
   uchar                          filler13[0x44000 - 0x40000 - sizeof(MCF5329_SCM_B_STRUCT)];
   MCF5329_EDMA_STRUCT            EDMA;                         /* Enhanced Direct Memory Access */   
   uchar                          filler14[0x48000 - 0x44000 - sizeof(MCF5329_EDMA_STRUCT)];
   
   MCF53XX_ICTRL0_STRUCT          ICTRL0;                       /* Interrupt Controller 0 */
   uchar                          filler15[0x4C000 - 0x48000 - sizeof(MCF53XX_ICTRL0_STRUCT)];
   MCF53XX_ICTRL1_STRUCT          ICTRL1;                       /* Interrupt Controller 1 */
   uchar                          filler16[0x54000 - 0x4C000 - sizeof(MCF53XX_ICTRL1_STRUCT)];
   MCF53XX_GIACK_STRUCT           GIACK;                        /* Global Level Interrupt Acknowledge Registers*/
   uchar                          filler17[0x58000 - 0x54000 - sizeof(MCF53XX_GIACK_STRUCT)];
   MCF53XX_I2C_STRUCT             I2C;                          /* I2C Module */
   uchar                          filler18[0x5C000 - 0x58000 - sizeof(MCF53XX_I2C_STRUCT)];
   
   MCF5XXX_QSPI_STRUCT            QSPI;                         /* Queued Serial Peripheral Interface (QSPI) */   
   uchar                          filler19[0x60000 - 0x5C000 - sizeof(MCF5XXX_QSPI_STRUCT)];
   
   MCF53XX_UART_STRUCT            UART[MCF5329_NUM_UARTS];      /* Universal Asynchronous Receiver Transmitter (UART) */
   uchar                          filler20[0x70000 - 0x60000 - sizeof(MCF53XX_UART_STRUCT) * MCF5329_NUM_UARTS]; 
   MCF53XX_DMA_TIMER_STRUCT       DMA_TIMER[MCF5329_NUM_DMAS];  /* DMA Timers */
   uchar                          filler21[0x80000 - 0x70000 - sizeof(MCF53XX_DMA_TIMER_STRUCT) * MCF5329_NUM_DMAS];
   
   MCF5XXX_PIT_STRUCT             PIT[MCF5329_NUM_TIMERS];      /* Programmable Interrupt Timer */
   MCF5329_PWM_STRUCT             PWM;                          /* Pulse Width Modulation */   
   uchar                          filler23[0x94000 - 0x90000 - sizeof(MCF5329_PWM_STRUCT)];
   MCF53XX_EPORT_STRUCT           EPORT;                        /* Edge Port Module */
   uchar                          filler24[0x98000 - 0x94000 - sizeof(MCF53XX_EPORT_STRUCT)];
      
   MCF5329_WATCHDOG_STRUCT        WATCHDOG;                     /* Watchdog Timer */
   uchar                          filler25[0xA0000 - 0x98000 - sizeof(MCF5329_WATCHDOG_STRUCT)];
 
    MCF53XX_CCM_STRUCT             CCM;
   uchar                          filler26[0xA4000 - 0xA0000 - sizeof(MCF53XX_CCM_STRUCT)];
   MCF5329_GPIO_STRUCT            GPIO;                         /* General Purpose I/O */
   uchar                          filler27[0xA8000 - 0xA4000 - sizeof(MCF5329_GPIO_STRUCT)]; 
   MCF53XX_RTC_STRUCT             RTC;                          /* Real Time Clock */
   uchar                          filler28[0xAC000 - 0xA8000 - sizeof(MCF53XX_RTC_STRUCT)];
   MCF5329_LCDC_STRUCT            LCDC;                         /* Liquid Crystal Display Controller */
   uchar                          filler29[0xB0000 - 0xAC000 - sizeof(MCF5329_LCDC_STRUCT)];
   MCF5XXX_USBOTG_STRUCT          USBOTG;                       /*Usb on the go */
   uchar                          filler30[0xB4000 - 0xB0000 - sizeof(MCF5XXX_USBOTG_STRUCT)];   
   MCF53XX_USBHOST_STRUCT          USBHOST;
   uchar                          filler31[0xB8000 - 0xB4000 - sizeof(MCF53XX_USBHOST_STRUCT)];
     
   MCF53XX_SDRAM_CTRL_STRUCT      SDRAMC;                       /* SDRAM Controller */
   uchar                          filler33[0xBC000 - 0xB8000 - sizeof(MCF53XX_SDRAM_CTRL_STRUCT)];
   MCF5329_SSI_STRUCT             SSI;                          /* Synchronous Serial Interface */
   uchar                          filler34[0xC0000 - 0xBC000 - sizeof(MCF5329_SSI_STRUCT)];
   MCF5329_PLL_STRUCT             PLL;                          /* Clock Module */   
      
} MCF5329_STRUCT, _PTR_ MCF5329_STRUCT_PTR;
typedef volatile struct mcf5329_struct _PTR_ VMCF5329_STRUCT_PTR;


/*
** PSP_SUPPORT_STRUCT
** This structure is used to maintain the PSP support information
*/

typedef struct psp_support_struct
{
   uint_32 ACR_VALS[MCF5329_NUM_ACRS];
   uint_32 reserved;
} PSP_SUPPORT_STRUCT, _PTR_ PSP_SUPPORT_STRUCT_PTR;

/*
typedef struct psp_support_struct
{
   uint_32 ACR_COUNT;   /* How many ACRs set so far  
   uint_32 reserved;

} PSP_SUPPORT_STRUCT, _PTR_ PSP_SUPPORT_STRUCT_PTR;
*/
typedef struct psp_mmu_init_struct
{
   uint_32 INITIAL_CACR_ENABLE_BITS;
} PSP_MMU_INIT_STRUCT, _PTR_ PSP_MMU_INIT_STRUCT_PTR;


/*------------------------------------------------------------------------*/
/*
**                      FUNCTION PROTOTYPES AND GLOBAL EXTERNS
*/

extern volatile uint_32 _psp_saved_mbar;
extern volatile uint_32 _psp_saved_cacr;
extern volatile uint_32 _psp_saved_acr0;
extern volatile uint_32 _psp_saved_acr1;
extern          uchar   __KERNEL_DATA_VERIFY_ENABLE[];

extern pointer _mcf5329_get_mbar(void);
extern void    _mcf5329_initialize_support(uint_32);

extern void    _mcf5329_cache_enable(uint_32);
extern void    _mcf5329_cache_disable(void);
extern void    _mcf5329_cache_flush(void);
extern void    _mcf5329_cache_invalidate(void);

extern void    _icache_invalidate_mlines(pointer,uint_32,uint_32);
extern void    _dcache_flush_invalidate_mlines(pointer,uint_32,uint_32,uint_32,uint_32);

extern void    _mcf5329_mmu_init(uint_32);
extern uint_32 _mcf5329_mmu_enable(void);
extern uint_32 _mcf5329_mmu_disable(void);
extern uint_32 _mcf5329_mmu_add_region(pointer,uint_32,uint_32);

extern void    __psp_enable_acrs(uint_32_ptr);
extern void    __psp_clear_acrs(void);
void _dcache_flush(pointer, uint_32, uint_32);
#endif /* __ASM__ */

#ifdef __cplusplus
}
#endif
#endif  /* __mcf5329_h__ */
/* EOF */
