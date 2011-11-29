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
* $FileName: mcf5208.h$
* $Version : 3.7.5.0$
* $Date    : Feb-7-2011$
*
* Comments:
*
*   This file contains the type definitions for the mcf5208x processors.
*
*END************************************************************************/
 
#ifndef __mcf5208_h__
#define __mcf5208_h__

#define __mcf5208_h__version "$Version:3.7.5.0$"
#define __mcf5208_h__date    "$Date:Feb-7-2011$"

#ifndef __ASM__

/* Include registers for modules common to all Coldfire processors */
#include <mcf52xx_uart.h>       /* UART */
#include <mcf5xxx_qspi.h>       /* QSPI */
#include <mcf52xx_i2c.h>        /* I2C */
#include <mcf5xxx_fec.h>        /* FEC */

#include <mcf5xxx_sdramc.h>
#include <mcf5xxx_fb.h>
#include <mcf5xxx_pit.h>

#endif /* __ASM__

#ifdef __cplusplus
extern "C" {
#endif

/*------------------------------------------------------------------------*/
/*
**                    CONSTANT DEFINITIONS
*/

/* Indicate processor type */
#define PSP_MCF5208                         1

#define PSP_HAS_DSP                         1
#define PSP_HAS_EMAC                        1

#define PSP_HAS_ACR                         1

/*
** Cache and MMU definition values
*/
#define PSP_HAS_MMU                         0
#define PSP_HAS_CODE_CACHE                  0 /*ToDo_LR check Cache implementation */
#define PSP_HAS_DATA_CACHE                  0

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

#define MCF5208_NUM_ACRS                    (2)

/* Error codes from mcf5208_mmu_add_region */
#define MCF5208_OUT_OF_ACRS                 (0x00100000)

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
    #define _CACHE_ENABLE(n)                    _mcf5208_cache_enable(n)
    #define _CACHE_DISABLE()                    _mcf5208_cache_disable()
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
    #define _DCACHE_INVALIDATE()                _mcf5208_dcache_invalidate()
    #define _DCACHE_INVALIDATE_LINE(p)          _DCACHE_INVALIDATE_MBYTES(p, 1)
    #define _DCACHE_INVALIDATE_MBYTES(p, m)     _dcache_flush(_PSP_MASK_CACHE_ADDR(p), _PSP_BYTES_TO_LINES(m), PSP_CACHE_LINE_SIZE)
#else
    #define _DCACHE_INVALIDATE()
    #define _DCACHE_INVALIDATE_LINE(p)
    #define _DCACHE_INVALIDATE_MBYTES(p, m)
#endif


#if PSP_HAS_CODE_CACHE
    #define _ICACHE_INVALIDATE()                _mcf5208_icache_invalidate()
    #define _ICACHE_INVALIDATE_LINE(p)          _ICACHE_INVALIDATE_MBYTES(p, 1)
    #define _ICACHE_INVALIDATE_MBYTES(p, m)     _icache_invalidate_mlines(p, _PSP_BYTES_TO_LINES(m), PSP_CACHE_LINE_SIZE)
#else
    #define _ICACHE_INVALIDATE()
    #define _ICACHE_INVALIDATE_LINE(p)
    #define _ICACHE_INVALIDATE_MBYTES(p, m)
#endif

#define _MMU_DISABLE()
#define _MMU_ENABLE()


#define MCF5208_CACHE_CACHEABLE_WRITETHROUGH    0       /* Unbuffered */
#define MCF5208_CACHE_CACHEABLE_COPYBACK        1       /* Write buffered */
#define MCF5208_CACHE_NONCACHEABLE_UNBUFFERED   2
#define MCF5208_CACHE_NONCACHEABLE_BUFFERED     3

/*
** Configuration information
*/
#define MCF5208_NUM_TIMERS                  (2) /* PIT */
#define MCF5208_NUM_UARTS                   (3)
#define MCF5208_NUM_DMAS                    (16)
#define MCF5208_NUM_DMA_TIMERS              (4)
#define MCF5208_NUM_FB_CS                   (6) /* FlexBus chip selects */

/*
** Cache control register bits
*/
#define MCF5208_CACR_CENB                       (1 << 31)
#define MCF5208_CACR_CPDI                       (1 << 28) /* Disable CPUSHL */
#define MCF5208_CACR_CFRZ                       (1 << 27) /* Cache Freeze */
#define MCF5208_CACR_CINV                       (1 << 24) /* Cache Invalidate */
#define MCF5208_CACR_DISI                       (1 << 23) /* Disable Instruction Cache */
#define MCF5208_CACR_DISD                       (1 << 22) /* Disable Data Cache */
#define MCF5208_CACR_INVI                       (1 << 21) /* Invalidate instr cache only */
#define MCF5208_CACR_INVD                       (1 << 20) /* Invalidate data cache only */
#define MCF5208_CACR_CEIB                       (1 << 10) /* Enable noncacheable instruction bursting */
#define MCF5208_CACR_DCM                        (1 << 9) /* Default cache mode */
#define MCF5208_CACR_DBWE                       (1 << 8) /* Write Buffered */
#define MCF5208_CACR_DWP                        (1 << 5) /* Default Write Protect */
#define MCF5208_CACR_EUSP                       (1 << 4) /* Enable user stack pointer */
#define MCF5208_CACR_LINE_FILL_00               0
#define MCF5208_CACR_LINE_FILL_01               1
#define MCF5208_CACR_LINE_FILL_10               2
#define MCF5208_CACR_LINE_FILL_11               3

/* These bits automatically clear after the operation */
#define CACR_AUTO_CLEAR_BITS    (MCF5208_CACR_CINV | MCF5208_CACR_INVD | MCF5208_CACR_INVI)

/*
** Access control register bits
*/
#define MCF5208_ACR_BASE_ADDR                   (0xFF000000)
#define MCF5208_ACR_BASE_ADDR_MASK              (0x00FF0000)
#define MCF5208_ACR_ENABLE                      (0x00008000)
#define MCF5208_ACR_IGNORE_FC                   (0x00004000)
#define MCF5208_ACR_USER_ACCESS_FC              (0x00000000)
#define MCF5208_ACR_SUPER_ACCESS_FC             (0x00002000)
#define MCF5208_ACR_NONCACHEABLE_MODE           (0x00000040)
#define MCF5208_ACR_CACHEABLE_MODE              (0x00000000)
#define MCF5208_ACR_BUFFER_WRITE_ENABLE         (0x00000020)
#define MCF5208_ACR_WRITE_PROTECT               (0x00000004)

/*
** Interrupt definitions
*/
#define MCF5208_ICTRL_BASEx	64

/*
** Interrupt vector table
*/
typedef enum mcf5208_interrupt_table_index {
   MCF5208_boot_stack_pointer,
   MCF5208_boot_program_counter,
   MCF5208_EXC_ACCESS_ERROR,
   MCF5208_EXC_ADDRESS_ERROR,
   MCF5208_EXC_ILLEGAL_INSTRUCTION,
   MCF5208_EXC_DIVIDE_BY_ZERO,
   MCF5208_EXC_rsvd6,
   MCF5208_EXC_rsvd7,
   MCF5208_EXC_PRIVILEGE_VIOLATION,
   MCF5208_EXC_NEXT_TRACE,
   MCF5208_EXC_UNIMPLEMENTED_LINE_A_OPCODE,
   MCF5208_EXC_UNIMPLEMENTED_LINE_F_OPCODE,
   MCF5208_EXC_DEBUG,
   MCF5208_EXC_rsvd13,
   MCF5208_EXC_FORMAT_ERROR,
   MCF5208_EXC_rsvd15,
   MCF5208_EXC_rsvd16,
   MCF5208_EXC_rsvd17,
   MCF5208_EXC_rsvd18,
   MCF5208_EXC_rsvd19,
   MCF5208_EXC_rsvd20,
   MCF5208_EXC_rsvd21,
   MCF5208_EXC_rsvd22,
   MCF5208_EXC_rsvd23,
   MCF5208_EXC_SPURIOUS,
   MCF5208_EXC_rsvd25,
   MCF5208_EXC_rsvd26,
   MCF5208_EXC_rsvd27,
   MCF5208_EXC_rsvd28,
   MCF5208_EXC_rsvd29,
   MCF5208_EXC_rsvd30,
   MCF5208_EXC_rsvd31,
   MCF5208_EXC_TRAP0,
   MCF5208_EXC_TRAP1,
   MCF5208_EXC_TRAP2,
   MCF5208_EXC_TRAP3,
   MCF5208_EXC_TRAP4,
   MCF5208_EXC_TRAP5,
   MCF5208_EXC_TRAP6,
   MCF5208_EXC_TRAP7,
   MCF5208_EXC_TRAP8,
   MCF5208_EXC_TRAP9,
   MCF5208_EXC_TRAP10,
   MCF5208_EXC_TRAP11,
   MCF5208_EXC_TRAP12,
   MCF5208_EXC_TRAP13,
   MCF5208_EXC_TRAP14,
   MCF5208_EXC_TRAP15,
   MCF5208_EXC_rsvd48,
   MCF5208_EXC_rsvd49,
   MCF5208_EXC_rsvd50,
   MCF5208_EXC_rsvd51,
   MCF5208_EXC_rsvd52,
   MCF5208_EXC_rsvd53,
   MCF5208_EXC_rsvd54,
   MCF5208_EXC_rsvd55,
   MCF5208_EXC_rsvd56,
   MCF5208_EXC_rsvd57,
   MCF5208_EXC_rsvd58,
   MCF5208_EXC_rsvd59,
   MCF5208_EXC_rsvd60,
   MCF5208_EXC_rsvd61,
   MCF5208_EXC_rsvd62,
   MCF5208_EXC_rsvd63,
   MCF5208_INT_FIRST_EXTERNAL,
   
   /* Interrupt Controller  */
   MCF5208_INT_EPORT0_EPF1,      /*  1 Edge port flag 1 */
   MCF5208_INT_EPORT0_EPF4,      /*  2 Edge port flag 4 */
   MCF5208_INT_EPORT0_EPF7,      /*  3 Edge port flag 7 */
   MCF5208_INT_PIT0,             /*  4 PIT0 PIF PIT interrupt flag */
   MCF5208_INT_PIT1,             /*  5 PIT1 PIF PIT interrupt flag */
   MCF5208_INT_rsvd6,            /*  6 not used */
   MCF5208_INT_rsvd7,            /*  7 not used */
   MCF5208_INT_DMA0,             /*  8 DMA Channel 0 transfer complete */
   MCF5208_INT_DMA1,             /*  9 DMA Channel 1 transfer complete */
   MCF5208_INT_DMA2,             /* 10 DMA Channel 2 transfer complete */
   MCF5208_INT_DMA3,             /* 11 DMA Channel 3 transfer complete */
   MCF5208_INT_DMA4,             /* 12 DMA Channel 4 transfer complete */
   MCF5208_INT_DMA5,             /* 13 DMA Channel 5 transfer complete */
   MCF5208_INT_DMA6,             /* 14 DMA Channel 6 transfer complete */
   MCF5208_INT_DMA7,             /* 15 DMA Channel 7 transfer complete */
   MCF5208_INT_DMA8,             /* 16 DMA Channel 8 transfer complete */
   MCF5208_INT_DMA9,             /* 17 DMA Channel 9 transfer complete */
   MCF5208_INT_DMA10,            /* 18 DMA Channel 10 transfer complete */
   MCF5208_INT_DMA11,            /* 19 DMA Channel 11 transfer complete */
   MCF5208_INT_DMA12,            /* 20 DMA Channel 12 transfer complete */
   MCF5208_INT_DMA13,            /* 21 DMA Channel 13 transfer complete */
   MCF5208_INT_DMA14,            /* 22 DMA Channel 14 transfer complete */
   MCF5208_INT_DMA15,            /* 23 DMA Channel 15 transfer complete */
   MCF5208_INT_DMAERR,           /* 24 DMA error interrupt */
   MCF5208_INT_SCM_CWIC,         /* 25 Core watchdog timeout */
   MCF5208_INT_UART0,            /* 26 UART0 interrupt */
   MCF5208_INT_UART1,            /* 27 UART1 interrupt */
   MCF5208_INT_UART2,            /* 28 UART2 interrupt */
   MCF5208_INT_rsvd29,           /* 29 not used */
   MCF5208_INT_I2C,              /* 30 I2C interrupt */
   MCF5208_INT_QSPI,             /* 31 QSPI all interrupts */
   MCF5208_INT_DTIM0,            /* 32 TMR0 interrupt */
   MCF5208_INT_DTIM1,            /* 33 TMR1 interrupt */
   MCF5208_INT_DTIM2,            /* 34 TMR2 interrupt */
   MCF5208_INT_DTIM3,            /* 35 TMR3 interrupt */
   MCF5208_INT_FEC_X_INTF,       /* 36 Transmit frame interrupt */
   MCF5208_INT_FEC_X_INTB,       /* 37 Transmit buffer interrupt */
   MCF5208_INT_FEC_X_UN,         /* 38 Transmit FIFO underrun */
   MCF5208_INT_FEC_RL,           /* 39 Collision retry limit */
   MCF5208_INT_FEC_R_INTF,       /* 40 Receive frame interrupt */
   MCF5208_INT_FEC_R_INTB,       /* 41 Receive buffer interrupt */
   MCF5208_INT_FEC_MII,          /* 42 MII interrupt */
   MCF5208_INT_FEC_LC,           /* 43 Late collision */
   MCF5208_INT_FEC_HBERR,        /* 44 Heartbeat error */
   MCF5208_INT_FEC_GRA,          /* 45 Graceful stop complete */
   MCF5208_INT_FEC_EBERR,        /* 46 Ethernet bus error */
   MCF5208_INT_FEC_BABT,         /* 47 Babbling transmit error */
   MCF5208_INT_FEC_BABR,         /* 48 Babbling receive error */
   MCF5208_INT_rsvd49,           /* 49 not used */
   MCF5208_INT_rsvd50,           /* 50 not used */
   MCF5208_INT_rsvd51,           /* 51 not used */
   MCF5208_INT_rsvd52,           /* 52 not used */
   MCF5208_INT_rsvd53,           /* 53 not used */
   MCF5208_INT_rsvd54,           /* 54 not used */
   MCF5208_INT_rsvd55,           /* 55 not used */
   MCF5208_INT_rsvd56,           /* 56 not used */
   MCF5208_INT_rsvd57,           /* 57 not used */
   MCF5208_INT_rsvd58,           /* 58 not used */
   MCF5208_INT_rsvd59,           /* 59 not used */
   MCF5208_INT_rsvd60,           /* 60 not used */
   MCF5208_INT_rsvd61,           /* 61 not used */
   MCF5208_INT_SCM_CFEI,         /* 62 Core bus error interrupt */
   MCF5208_INT_rsvd63            /* 63 not used */
} MCF5208_INTERRUPT_TABLE_INDEX;/*, PSP_INTERRUPT_TABLE_INDEX; */

#define PSP_GET_ICTRL0_BASE()   \
   (&((VMCF5208_STRUCT_PTR)_PSP_GET_MBAR())->ICTRL)

/*------------------------------------------------------------------------*/
/*
** SCM System control module
*/

/* Bit definitions and macros for RAMBAR */
#define MCF5208_SCM_RAMBAR_BA(x)                ((x)&0xFFFF0000)
#define MCF5208_SCM_RAMBAR_BDE                  (0x00000200)


/* Bit definitions and macros for WCR */
#define MCF5208_SCM_WCR_CWE                    (0x80)
#define MCF5208_SCM_WCR_PRIV_MASK              (7)
#define MCF5208_SCM_WCR_PRIV                   ((x) & MCF5208_SCM_CWCR_PRIV_MASK)

/* Bit definitions and macros for CWCR */
#define MCF5208_SCM_CWCR_CWE                    (0x80)
#define MCF5208_SCM_CWCR_CWRI                   (0x40)
#define MCF5208_SCM_CWCR_CWT(x)                 (((x)&0x03)<<3)
#define MCF5208_SCM_CWCR_CWTA                   (0x04)
#define MCF5208_SCM_CWCR_CWTAVAL                (0x02)
#define MCF5208_SCM_CWCR_CWTIC                  (0x01)

/* Bit definitions and macros for WCR */
#define MCF5208_SCM_WCR_ENBSTOP                 (0x80
#define MCF5208_SCM_WCR_PRILVL(x)               (((x)&0x07)<<0)

/* Bit definitions and macros for CWSR */
#define MCF5208_SCM_CWSR_SEQ1                   (0x55)
#define MCF5208_SCM_CWSR_SEQ2                   (0xAA)


/*------------------------------------------------------------------------*/
/*
** DMA registers
*/

/* Bit definitions and macros for MCF5208_DMA_SAR */
#define MCF5208_DMA_SAR_SAR(x)                   (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF5208_DMA_DAR */
#define MCF5208_DMA_DAR_DAR(x)                   (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF5208_DMA_DTMR */
#define MCF5208_DMA_DSR_DONE                     (0x1)
#define MCF5208_DMA_DSR_BSY                      (0x2)
#define MCF5208_DMA_DSR_REQ                      (0x4)
#define MCF5208_DMA_DSR_BED                      (0x10)
#define MCF5208_DMA_DSR_BES                      (0x20)
#define MCF5208_DMA_DSR_CE                       (0x40)

/* Bit definitions and macros for MCF5208_DMA_BCR */
#define MCF5208_DMA_BCR_BCR(x)                   (((x)&0xFFFFFF)<<0)
#define MCF5208_DMA_BCR_DSR(x)                   (((x)&0xFF)<<0x18)

/* Bit definitions and macros for MCF5208_DMA_DCR */
#define MCF5208_DMA_DCR_LCH2(x)                  (((x)&0x3)<<0)
#define MCF5208_DMA_DCR_LCH2_CH0                 (0)
#define MCF5208_DMA_DCR_LCH2_CH1                 (0x1)
#define MCF5208_DMA_DCR_LCH2_CH2                 (0x2)
#define MCF5208_DMA_DCR_LCH2_CH3                 (0x3)
#define MCF5208_DMA_DCR_LCH1(x)                  (((x)&0x3)<<0x2)
#define MCF5208_DMA_DCR_LCH1_CH0                 (0)
#define MCF5208_DMA_DCR_LCH1_CH1                 (0x1)
#define MCF5208_DMA_DCR_LCH1_CH2                 (0x2)
#define MCF5208_DMA_DCR_LCH1_CH3                 (0x3)
#define MCF5208_DMA_DCR_LINKCC(x)                (((x)&0x3)<<0x4)
#define MCF5208_DMA_DCR_D_REQ                    (0x80)
#define MCF5208_DMA_DCR_DMOD(x)                  (((x)&0xF)<<0x8)
#define MCF5208_DMA_DCR_DMOD_DIS                 (0)
#define MCF5208_DMA_DCR_DMOD_16                  (0x1)
#define MCF5208_DMA_DCR_DMOD_32                  (0x2)
#define MCF5208_DMA_DCR_DMOD_64                  (0x3)
#define MCF5208_DMA_DCR_DMOD_128                 (0x4)
#define MCF5208_DMA_DCR_DMOD_256                 (0x5)
#define MCF5208_DMA_DCR_DMOD_512                 (0x6)
#define MCF5208_DMA_DCR_DMOD_1K                  (0x7)
#define MCF5208_DMA_DCR_DMOD_2K                  (0x8)
#define MCF5208_DMA_DCR_DMOD_4K                  (0x9)
#define MCF5208_DMA_DCR_DMOD_8K                  (0xA)
#define MCF5208_DMA_DCR_DMOD_16K                 (0xB)
#define MCF5208_DMA_DCR_DMOD_32K                 (0xC)
#define MCF5208_DMA_DCR_DMOD_64K                 (0xD)
#define MCF5208_DMA_DCR_DMOD_128K                (0xE)
#define MCF5208_DMA_DCR_DMOD_256K                (0xF)
#define MCF5208_DMA_DCR_SMOD(x)                  (((x)&0xF)<<0xC)
#define MCF5208_DMA_DCR_SMOD_DIS                 (0)
#define MCF5208_DMA_DCR_SMOD_16                  (0x1)
#define MCF5208_DMA_DCR_SMOD_32                  (0x2)
#define MCF5208_DMA_DCR_SMOD_64                  (0x3)
#define MCF5208_DMA_DCR_SMOD_128                 (0x4)
#define MCF5208_DMA_DCR_SMOD_256                 (0x5)
#define MCF5208_DMA_DCR_SMOD_512                 (0x6)
#define MCF5208_DMA_DCR_SMOD_1K                  (0x7)
#define MCF5208_DMA_DCR_SMOD_2K                  (0x8)
#define MCF5208_DMA_DCR_SMOD_4K                  (0x9)
#define MCF5208_DMA_DCR_SMOD_8K                  (0xA)
#define MCF5208_DMA_DCR_SMOD_16K                 (0xB)
#define MCF5208_DMA_DCR_SMOD_32K                 (0xC)
#define MCF5208_DMA_DCR_SMOD_64K                 (0xD)
#define MCF5208_DMA_DCR_SMOD_128K                (0xE)
#define MCF5208_DMA_DCR_SMOD_256K                (0xF)
#define MCF5208_DMA_DCR_START                    (0x10000)
#define MCF5208_DMA_DCR_DSIZE(x)                 (((x)&0x3)<<0x11)
#define MCF5208_DMA_DCR_DSIZE_LONG               (0)
#define MCF5208_DMA_DCR_DSIZE_BYTE               (0x1)
#define MCF5208_DMA_DCR_DSIZE_WORD               (0x2)
#define MCF5208_DMA_DCR_DSIZE_LINE               (0x3)
#define MCF5208_DMA_DCR_DINC                     (0x80000)
#define MCF5208_DMA_DCR_SSIZE(x)                 (((x)&0x3)<<0x14)
#define MCF5208_DMA_DCR_SSIZE_LONG               (0)
#define MCF5208_DMA_DCR_SSIZE_BYTE               (0x1)
#define MCF5208_DMA_DCR_SSIZE_WORD               (0x2)
#define MCF5208_DMA_DCR_SSIZE_LINE               (0x3)
#define MCF5208_DMA_DCR_SINC                     (0x400000)
#define MCF5208_DMA_DCR_BWC(x)                   (((x)&0x7)<<0x19)
#define MCF5208_DMA_DCR_BWC_16K                  (0x1)
#define MCF5208_DMA_DCR_BWC_32K                  (0x2)
#define MCF5208_DMA_DCR_BWC_64K                  (0x3)
#define MCF5208_DMA_DCR_BWC_128K                 (0x4)
#define MCF5208_DMA_DCR_BWC_256K                 (0x5)
#define MCF5208_DMA_DCR_BWC_512K                 (0x6)
#define MCF5208_DMA_DCR_BWC_1024K                (0x7)
#define MCF5208_DMA_DCR_AA                       (0x10000000)
#define MCF5208_DMA_DCR_CS                       (0x20000000)
#define MCF5208_DMA_DCR_EEXT                     (0x40000000)
#define MCF5208_DMA_DCR_INT                      (0x80000000)


/*------------------------------------------------------------------------*/
/*
** General Purpose I/O (GPIO) Module
*/

/* general bit definition */
#define MCF5208_GPIO_PIN_0      0x01
#define MCF5208_GPIO_PIN_1      0x02
#define MCF5208_GPIO_PIN_2      0x04
#define MCF5208_GPIO_PIN_3      0x08
#define MCF5208_GPIO_PIN_4      0x10
#define MCF5208_GPIO_PIN_5      0x20
#define MCF5208_GPIO_PIN_6      0x40
#define MCF5208_GPIO_PIN_7      0x80

/* Bit definitions for PODR_x registers */
#define MCF5208_GPIO_PODR_x0    0x01
#define MCF5208_GPIO_PODR_x1    0x02
#define MCF5208_GPIO_PODR_x2    0x04
#define MCF5208_GPIO_PODR_x3    0x08
#define MCF5208_GPIO_PODR_x4    0x10
#define MCF5208_GPIO_PODR_x5    0x20
#define MCF5208_GPIO_PODR_x6    0x40
#define MCF5208_GPIO_PODR_x7    0x80
#define MCF5208_GPIO_PODR_x(x) (0x01<<x)

/* Bit definitions for PDDR_x registers */
#define MCF5208_GPIO_PDDR_x0    0x01
#define MCF5208_GPIO_PDDR_x1    0x02
#define MCF5208_GPIO_PDDR_x2    0x04
#define MCF5208_GPIO_PDDR_x3    0x08
#define MCF5208_GPIO_PDDR_x4    0x10
#define MCF5208_GPIO_PDDR_x5    0x20
#define MCF5208_GPIO_PDDR_x6    0x40
#define MCF5208_GPIO_PDDR_x7    0x80
#define MCF5208_GPIO_PDDR_x(x)  (0x01<<x)

/* Bit definitions for PPDSDR_x registers */
#define MCF5208_GPIO_PPDSDR_x0  0x01
#define MCF5208_GPIO_PPDSDR_x1  0x02
#define MCF5208_GPIO_PPDSDR_x2  0x04
#define MCF5208_GPIO_PPDSDR_x3  0x08
#define MCF5208_GPIO_PPDSDR_x4  0x10
#define MCF5208_GPIO_PPDSDR_x5  0x20
#define MCF5208_GPIO_PPDSDR_x6  0x40
#define MCF5208_GPIO_PPDSDR_x7  0x80
#define MCF5208_GPIO_PPDSDR_x(x)   (0x01<<x)

/* Bit definitions for PCLRR_x registers */
#define MCF5208_GPIO_PCLRR_x0   0x01
#define MCF5208_GPIO_PCLRR_x1   0x02
#define MCF5208_GPIO_PCLRR_x2   0x04
#define MCF5208_GPIO_PCLRR_x3   0x08
#define MCF5208_GPIO_PCLRR_x4   0x10
#define MCF5208_GPIO_PCLRR_x5   0x20
#define MCF5208_GPIO_PCLRR_x6   0x40
#define MCF5208_GPIO_PCLRR_x7   0x80
#define MCF5208_GPIO_PCLRR_x(x) (0x01<<x)

/* Bit definitions and macros for MCF5208_GPIO_PAR_BUSCTL */
#define MCF5208_GPIO_PAR_BUSCTL_PAR_TS(x)         (((x)&0x3)<<0)
#define MCF5208_GPIO_PAR_BUSCTL_PAR_TS_GPIO       (0)
#define MCF5208_GPIO_PAR_BUSCTL_PAR_TS_DACK0      (0x2)
#define MCF5208_GPIO_PAR_BUSCTL_PAR_TS_TS         (0x3)
#define MCF5208_GPIO_PAR_BUSCTL_PAR_RWB           (0x4)
#define MCF5208_GPIO_PAR_BUSCTL_PAR_TA            (0x8)
#define MCF5208_GPIO_PAR_BUSCTL_PAR_OE            (0x10)

/* Bit definitions and macros for MCF5208_GPIO_PAR_BE */
#define MCF5208_GPIO_PAR_BE_PAR_BE0               (0x1)
#define MCF5208_GPIO_PAR_BE_PAR_BE1               (0x2)
#define MCF5208_GPIO_PAR_BE_PAR_BE2               (0x4)
#define MCF5208_GPIO_PAR_BE_PAR_BE3               (0x8)

/* Bit definitions and macros for MCF5208_GPIO_PAR_CS */
#define MCF5208_GPIO_PAR_CS_PAR_CS1(x)            (((x)&0x3)<<0)
#define MCF5208_GPIO_PAR_CS_PAR_CS1_GPIO          (0)
#define MCF5208_GPIO_PAR_CS_PAR_CS1_SDCS1         (0x2)
#define MCF5208_GPIO_PAR_CS_PAR_CS1_CS1           (0x3)
#define MCF5208_GPIO_PAR_CS_PAR_CS2               (0x4)
#define MCF5208_GPIO_PAR_CS_PAR_CS3               (0x8)

/* Bit definitions and macros for MCF5208_GPIO_PAR_FECI2C */
#define MCF5208_GPIO_PAR_FECI2C_PAR_SDA(x)        (((x)&0x3)<<0)
#define MCF5208_GPIO_PAR_FECI2C_PAR_SDA_GPIO      (0)
#define MCF5208_GPIO_PAR_FECI2C_PAR_SDA_URXD2     (0x1)
#define MCF5208_GPIO_PAR_FECI2C_PAR_SDA_SDA       (0x3)
#define MCF5208_GPIO_PAR_FECI2C_PAR_SCL(x)        (((x)&0x3)<<0x2)
#define MCF5208_GPIO_PAR_FECI2C_PAR_SCL_GPIO      (0)
#define MCF5208_GPIO_PAR_FECI2C_PAR_SCL_UTXD2     (0x4)
#define MCF5208_GPIO_PAR_FECI2C_PAR_SCL_SCL       (0xC)
#define MCF5208_GPIO_PAR_FECI2C_PAR_MDIO(x)       (((x)&0x3)<<0x4)
#define MCF5208_GPIO_PAR_FECI2C_PAR_MDIO_GPIO     (0)
#define MCF5208_GPIO_PAR_FECI2C_PAR_MDIO_URXD2    (0x10)
#define MCF5208_GPIO_PAR_FECI2C_PAR_MDIO_SDA      (0x20)
#define MCF5208_GPIO_PAR_FECI2C_PAR_MDIO_EMDIO    (0x30)
#define MCF5208_GPIO_PAR_FECI2C_PAR_MDC(x)        (((x)&0x3)<<0x6)
#define MCF5208_GPIO_PAR_FECI2C_PAR_MDC_GPIO      (0)
#define MCF5208_GPIO_PAR_FECI2C_PAR_MDC_UTXD2     (0x40)
#define MCF5208_GPIO_PAR_FECI2C_PAR_MDC_SCL       (0x80)
#define MCF5208_GPIO_PAR_FECI2C_PAR_MDC_EMDC      (0xC0)

/* Bit definitions and macros for MCF5208_GPIO_PAR_QSPI */
#define MCF5208_GPIO_PAR_QSPI_PAR_SCK(x)          (((x)&0x3)<<0)
#define MCF5208_GPIO_PAR_QSPI_PAR_SCK_GPIO        (0)
#define MCF5208_GPIO_PAR_QSPI_PAR_SCK_SCL         (0x2)
#define MCF5208_GPIO_PAR_QSPI_PAR_SCK_SCK         (0x3)
#define MCF5208_GPIO_PAR_QSPI_PAR_DOUT(x)         (((x)&0x3)<<0x2)
#define MCF5208_GPIO_PAR_QSPI_PAR_DOUT_GPIO       (0)
#define MCF5208_GPIO_PAR_QSPI_PAR_DOUT_SDA        (0x8)
#define MCF5208_GPIO_PAR_QSPI_PAR_DOUT_DOUT       (0xC)
#define MCF5208_GPIO_PAR_QSPI_PAR_DIN(x)          (((x)&0x3)<<0x4)
#define MCF5208_GPIO_PAR_QSPI_PAR_DIN_GPIO        (0)
#define MCF5208_GPIO_PAR_QSPI_PAR_DIN_UCTS2       (0x10)
#define MCF5208_GPIO_PAR_QSPI_PAR_DIN_DREQ0       (0x20)
#define MCF5208_GPIO_PAR_QSPI_PAR_DIN_DIN         (0x30)
#define MCF5208_GPIO_PAR_QSPI_PAR_PCS2(x)         (((x)&0x3)<<0x6)
#define MCF5208_GPIO_PAR_QSPI_PAR_PCS2_GPIO       (0)
#define MCF5208_GPIO_PAR_QSPI_PAR_PCS2_URTS2      (0x40)
#define MCF5208_GPIO_PAR_QSPI_PAR_PCS2_DACK0      (0x80)
#define MCF5208_GPIO_PAR_QSPI_PAR_PCS2_PCS2       (0xC0)

/* Bit definitions and macros for MCF5208_GPIO_PAR_TIMER */
#define MCF5208_GPIO_PAR_TIMER_PAR_T0IN(x)        (((x)&0x3)<<0)
#define MCF5208_GPIO_PAR_TIMER_PAR_TIN0_GPIO      (0)
#define MCF5208_GPIO_PAR_TIMER_PAR_TIN0_UTXD2     (0x1)
#define MCF5208_GPIO_PAR_TIMER_PAR_TIN0_TOUT0     (0x2)
#define MCF5208_GPIO_PAR_TIMER_PAR_TIN0_TIN0      (0x3)
#define MCF5208_GPIO_PAR_TIMER_PAR_T1IN(x)        (((x)&0x3)<<0x2)
#define MCF5208_GPIO_PAR_TIMER_PAR_TIN1_GPIO      (0)
#define MCF5208_GPIO_PAR_TIMER_PAR_TIN1_URXD2     (0x4)
#define MCF5208_GPIO_PAR_TIMER_PAR_TIN1_TOUT1     (0x8)
#define MCF5208_GPIO_PAR_TIMER_PAR_TIN1_TIN1      (0xC)
#define MCF5208_GPIO_PAR_TIMER_PAR_T2IN(x)        (((x)&0x3)<<0x4)
#define MCF5208_GPIO_PAR_TIMER_PAR_TIN2_GPIO      (0)
#define MCF5208_GPIO_PAR_TIMER_PAR_TIN2_URTS2     (0x10)
#define MCF5208_GPIO_PAR_TIMER_PAR_TIN2_TOUT2     (0x20)
#define MCF5208_GPIO_PAR_TIMER_PAR_TIN2_TIN2      (0x30)
#define MCF5208_GPIO_PAR_TIMER_PAR_T3IN(x)        (((x)&0x3)<<0x6)
#define MCF5208_GPIO_PAR_TIMER_PAR_TIN3_GPIO      (0)
#define MCF5208_GPIO_PAR_TIMER_PAR_TIN3_UCTS2     (0x40)
#define MCF5208_GPIO_PAR_TIMER_PAR_TIN3_TOUT3     (0x80)
#define MCF5208_GPIO_PAR_TIMER_PAR_TIN3_TIN3      (0xC0)

/* Bit definitions and macros for MCF5208_GPIO_PAR_UART */
#define MCF5208_GPIO_PAR_UART_PAR_U0RXD           (0x1)
#define MCF5208_GPIO_PAR_UART_PAR_U0TXD           (0x2)
#define MCF5208_GPIO_PAR_UART_PAR_U0RTS(x)        (((x)&0x3)<<0x2)
#define MCF5208_GPIO_PAR_UART_PAR_URTS0_GPIO      (0)
#define MCF5208_GPIO_PAR_UART_PAR_URTS0_PCS0      (0x4)
#define MCF5208_GPIO_PAR_UART_PAR_URTS0_TOUT0     (0x8)
#define MCF5208_GPIO_PAR_UART_PAR_URTS0_URTS0     (0xC)
#define MCF5208_GPIO_PAR_UART_PAR_U0CTS(x)        (((x)&0x3)<<0x4)
#define MCF5208_GPIO_PAR_UART_PAR_UCTS0_GPIO      (0)
#define MCF5208_GPIO_PAR_UART_PAR_UCTS0_PCS0      (0x10)
#define MCF5208_GPIO_PAR_UART_PAR_UCTS0_TIN0      (0x20)
#define MCF5208_GPIO_PAR_UART_PAR_UCTS0_UCTS0     (0x30)
#define MCF5208_GPIO_PAR_UART_PAR_U1RXD           (0x40)
#define MCF5208_GPIO_PAR_UART_PAR_U1TXD           (0x80)
#define MCF5208_GPIO_PAR_UART_PAR_U1RTS(x)        (((x)&0x3)<<0x8)
#define MCF5208_GPIO_PAR_UART_PAR_URTS1_GPIO      (0)
#define MCF5208_GPIO_PAR_UART_PAR_URTS1_PCS1      (0x100)
#define MCF5208_GPIO_PAR_UART_PAR_URTS1_TOUT1     (0x200)
#define MCF5208_GPIO_PAR_UART_PAR_URTS1_URTS1     (0x300)
#define MCF5208_GPIO_PAR_UART_PAR_U1CTS(x)        (((x)&0x3)<<0xA)
#define MCF5208_GPIO_PAR_UART_PAR_UCTS1_GPIO      (0)
#define MCF5208_GPIO_PAR_UART_PAR_UCTS1_PCS1      (0x400)
#define MCF5208_GPIO_PAR_UART_PAR_UCTS1_TIN1      (0x800)
#define MCF5208_GPIO_PAR_UART_PAR_UCTS1_UCTS1     (0xC00)

/* Bit definitions and macros for MCF5208_GPIO_PAR_FEC */
#define MCF5208_GPIO_PAR_FEC_PAR_FEC_MII(x)       (((x)&0x3)<<0)
#define MCF5208_GPIO_PAR_FEC_PAR_FEC_MII_GPIO     (0)
#define MCF5208_GPIO_PAR_FEC_PAR_FEC_MII_UART     (0x1)
#define MCF5208_GPIO_PAR_FEC_PAR_FEC_MII_FEC      (0x3)
#define MCF5208_GPIO_PAR_FEC_PAR_FEC_7W(x)        (((x)&0x3)<<0x2)
#define MCF5208_GPIO_PAR_FEC_PAR_FEC_7W_GPIO      (0)
#define MCF5208_GPIO_PAR_FEC_PAR_FEC_7W_UART      (0x4)
#define MCF5208_GPIO_PAR_FEC_PAR_FEC_7W_FEC       (0xC)

/* Bit definitions and macros for MCF5208_GPIO_PAR_IRQ */
#define MCF5208_GPIO_PAR_IRQ_PAR_IRQ4             (0x1)

/*------------------------------------------------------------------------*/
/*
** DMA_TIMER  registers bit set.
*/
/* Bit definitions and macros for MCF5208_DTIM_DTMR */
#define MCF5208_DTIM_DTMR_RST                    (0x1)
#define MCF5208_DTIM_DTMR_CLK(x)                 (((x)&0x3)<<0x1)
#define MCF5208_DTIM_DTMR_CLK_STOP               (0)
#define MCF5208_DTIM_DTMR_CLK_DIV1               (0x2)
#define MCF5208_DTIM_DTMR_CLK_DIV16              (0x4)
#define MCF5208_DTIM_DTMR_CLK_DTIN               (0x6)
#define MCF5208_DTIM_DTMR_FRR                    (0x8)
#define MCF5208_DTIM_DTMR_ORRI                   (0x10)
#define MCF5208_DTIM_DTMR_OM                     (0x20)
#define MCF5208_DTIM_DTMR_CE(x)                  (((x)&0x3)<<0x6)
#define MCF5208_DTIM_DTMR_CE_NONE                (0)
#define MCF5208_DTIM_DTMR_CE_RISE                (0x40)
#define MCF5208_DTIM_DTMR_CE_FALL                (0x80)
#define MCF5208_DTIM_DTMR_CE_ANY                 (0xC0)
#define MCF5208_DTIM_DTMR_PS(x)                  (((x)&0xFF)<<0x8)

/* Bit definitions and macros for MCF5208_DTIM_DTXMR */
#define MCF5208_DTIM_DTXMR_MODE16                (0x1)
#define MCF5208_DTIM_DTXMR_DMAEN                 (0x80)

/* Bit definitions and macros for MCF5208_DTIM_DTER */
#define MCF5208_DTIM_DTER_CAP                    (0x1)
#define MCF5208_DTIM_DTER_REF                    (0x2)

/* Bit definitions and macros for MCF5208_DTIM_DTRR */
#define MCF5208_DTIM_DTRR_REF(x)                 (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF5208_DTIM_DTCR */
#define MCF5208_DTIM_DTCR_CAP(x)                 (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF5208_DTIM_DTCN */
#define MCF5208_DTIM_DTCN_CNT(x)                 (((x)&0xFFFFFFFF)<<0)


/*------------------------------------------------------------------------*/
/*
** CCM  registers bit set.
*/

/* Bit definitions and macros for MCF5208_CCM_CCR */
#define MCF5208_CCM_CCR_RESERVED                 (0x1)
#define MCF5208_CCM_CCR_PLLMODE                  (0x3)
#define MCF5208_CCM_CCR_OSCMODE                  (0x5)
#define MCF5208_CCM_CCR_BOOTPS(x)                (((x)&0x3)<<0x3|0x1)
#define MCF5208_CCM_CCR_LOAD                     (0x21)
#define MCF5208_CCM_CCR_LIMP                     (0x41)
#define MCF5208_CCM_CCR_OSCFREQ                  (0x81)
#define MCF5208_CCM_CCR_CSC                      (0x201)

/* Bit definitions and macros for MCF5208_CCM_RCON */
#define MCF5208_CCM_RCON_RESERVED                (0x1)
#define MCF5208_CCM_RCON_PLLMODE                 (0x3)
#define MCF5208_CCM_RCON_OSCMODE                 (0x5)
#define MCF5208_CCM_RCON_BOOTPS(x)               (((x)&0x3)<<0x3|0x1)
#define MCF5208_CCM_RCON_LOAD                    (0x21)
#define MCF5208_CCM_RCON_LIMP                    (0x41)
#define MCF5208_CCM_RCON_OSCFREQ                 (0x81)
#define MCF5208_CCM_RCON_CSC                     (0x201)

/* Bit definitions and macros for MCF5208_CCM_CIR */
#define MCF5208_CCM_CIR_PRN(x)                   (((x)&0x3F)<<0)
#define MCF5208_CCM_CIR_PIN(x)                   (((x)&0x3FF)<<0x6)


/*------------------------------------------------------------------------*/
/*
** CLK  registers bit set.
*/

/* Bit definitions and macros for MCF5208_CLOCK_PODR */
#define MCF5208_CLOCK_PODR_BUSDIV(x)             (((x)&0xF)<<0)
#define MCF5208_CLOCK_PODR_CPUDIV(x)             (((x)&0xF)<<0x4)

/* Bit definitions and macros for MCF5208_CLOCK_PCR */
#define MCF5208_CLOCK_PCR_DITHDEV(x)             (((x)&0x7)<<0)
#define MCF5208_CLOCK_PCR_DITHEN                 (0x80)

/* Bit definitions and macros for MCF5208_CLOCK_PMDR */
#define MCF5208_CLOCK_PMDR_MODDIV(x)             (((x)&0xFF)<<0)

/* Bit definitions and macros for MCF5208_CLOCK_PFDR */
#define MCF5208_CLOCK_PFDR_MFD(x)                (((x)&0xFF)<<0)


/*------------------------------------------------------------------------*/
/*
** EPORT  registers bit set.
*/

/* Bit definitions and macros for MCF5208_EPORT_EPPAR */
#define MCF5208_EPORT_EPPAR_EPPA1(x)             (((x)&0x3)<<0x2)
#define MCF5208_EPORT_EPPAR_EPPA1_LEVEL          (0)
#define MCF5208_EPORT_EPPAR_EPPA1_RISING         (0x4)
#define MCF5208_EPORT_EPPAR_EPPA1_FALLING        (0x8)
#define MCF5208_EPORT_EPPAR_EPPA1_BOTH           (0xC)
#define MCF5208_EPORT_EPPAR_EPPA2(x)             (((x)&0x3)<<0x4)
#define MCF5208_EPORT_EPPAR_EPPA2_LEVEL          (0)
#define MCF5208_EPORT_EPPAR_EPPA2_RISING         (0x10)
#define MCF5208_EPORT_EPPAR_EPPA2_FALLING        (0x20)
#define MCF5208_EPORT_EPPAR_EPPA2_BOTH           (0x30)
#define MCF5208_EPORT_EPPAR_EPPA3(x)             (((x)&0x3)<<0x6)
#define MCF5208_EPORT_EPPAR_EPPA3_LEVEL          (0)
#define MCF5208_EPORT_EPPAR_EPPA3_RISING         (0x40)
#define MCF5208_EPORT_EPPAR_EPPA3_FALLING        (0x80)
#define MCF5208_EPORT_EPPAR_EPPA3_BOTH           (0xC0)
#define MCF5208_EPORT_EPPAR_EPPA4(x)             (((x)&0x3)<<0x8)
#define MCF5208_EPORT_EPPAR_EPPA4_LEVEL          (0)
#define MCF5208_EPORT_EPPAR_EPPA4_RISING         (0x100)
#define MCF5208_EPORT_EPPAR_EPPA4_FALLING        (0x200)
#define MCF5208_EPORT_EPPAR_EPPA4_BOTH           (0x300)
#define MCF5208_EPORT_EPPAR_EPPA5(x)             (((x)&0x3)<<0xA)
#define MCF5208_EPORT_EPPAR_EPPA5_LEVEL          (0)
#define MCF5208_EPORT_EPPAR_EPPA5_RISING         (0x400)
#define MCF5208_EPORT_EPPAR_EPPA5_FALLING        (0x800)
#define MCF5208_EPORT_EPPAR_EPPA5_BOTH           (0xC00)
#define MCF5208_EPORT_EPPAR_EPPA6(x)             (((x)&0x3)<<0xC)
#define MCF5208_EPORT_EPPAR_EPPA6_LEVEL          (0)
#define MCF5208_EPORT_EPPAR_EPPA6_RISING         (0x1000)
#define MCF5208_EPORT_EPPAR_EPPA6_FALLING        (0x2000)
#define MCF5208_EPORT_EPPAR_EPPA6_BOTH           (0x3000)
#define MCF5208_EPORT_EPPAR_EPPA7(x)             (((x)&0x3)<<0xE)
#define MCF5208_EPORT_EPPAR_EPPA7_LEVEL          (0)
#define MCF5208_EPORT_EPPAR_EPPA7_RISING         (0x4000)
#define MCF5208_EPORT_EPPAR_EPPA7_FALLING        (0x8000)
#define MCF5208_EPORT_EPPAR_EPPA7_BOTH           (0xC000)
#define MCF5208_EPORT_EPPAR_LEVEL                (0)
#define MCF5208_EPORT_EPPAR_RISING               (0x1)
#define MCF5208_EPORT_EPPAR_FALLING              (0x2)
#define MCF5208_EPORT_EPPAR_BOTH                 (0x3)

/* Bit definitions and macros for MCF5208_EPORT_EPDDR */
#define MCF5208_EPORT_EPDDR_EPDD1                (0x2)
#define MCF5208_EPORT_EPDDR_EPDD2                (0x4)
#define MCF5208_EPORT_EPDDR_EPDD3                (0x8)
#define MCF5208_EPORT_EPDDR_EPDD4                (0x10)
#define MCF5208_EPORT_EPDDR_EPDD5                (0x20)
#define MCF5208_EPORT_EPDDR_EPDD6                (0x40)
#define MCF5208_EPORT_EPDDR_EPDD7                (0x80)

/* Bit definitions and macros for MCF5208_EPORT_EPIER */
#define MCF5208_EPORT_EPIER_EPIE1                (0x2)
#define MCF5208_EPORT_EPIER_EPIE2                (0x4)
#define MCF5208_EPORT_EPIER_EPIE3                (0x8)
#define MCF5208_EPORT_EPIER_EPIE4                (0x10)
#define MCF5208_EPORT_EPIER_EPIE5                (0x20)
#define MCF5208_EPORT_EPIER_EPIE6                (0x40)
#define MCF5208_EPORT_EPIER_EPIE7                (0x80)

/* Bit definitions and macros for MCF5208_EPORT_EPDR */
#define MCF5208_EPORT_EPDR_EPD1                  (0x2)
#define MCF5208_EPORT_EPDR_EPD2                  (0x4)
#define MCF5208_EPORT_EPDR_EPD3                  (0x8)
#define MCF5208_EPORT_EPDR_EPD4                  (0x10)
#define MCF5208_EPORT_EPDR_EPD5                  (0x20)
#define MCF5208_EPORT_EPDR_EPD6                  (0x40)
#define MCF5208_EPORT_EPDR_EPD7                  (0x80)

/* Bit definitions and macros for MCF5208_EPORT_EPPDR */
#define MCF5208_EPORT_EPPDR_EPPD1                (0x2)
#define MCF5208_EPORT_EPPDR_EPPD2                (0x4)
#define MCF5208_EPORT_EPPDR_EPPD3                (0x8)
#define MCF5208_EPORT_EPPDR_EPPD4                (0x10)
#define MCF5208_EPORT_EPPDR_EPPD5                (0x20)
#define MCF5208_EPORT_EPPDR_EPPD6                (0x40)
#define MCF5208_EPORT_EPPDR_EPPD7                (0x80)

/* Bit definitions and macros for MCF5208_EPORT_EPFR */
#define MCF5208_EPORT_EPFR_EPF1                  (0x2)
#define MCF5208_EPORT_EPFR_EPF2                  (0x4)
#define MCF5208_EPORT_EPFR_EPF3                  (0x8)
#define MCF5208_EPORT_EPFR_EPF4                  (0x10)
#define MCF5208_EPORT_EPFR_EPF5                  (0x20)
#define MCF5208_EPORT_EPFR_EPF6                  (0x40)
#define MCF5208_EPORT_EPFR_EPF7                  (0x80)


/*------------------------------------------------------------------------*/
/*
** SDRAM Controller Module
*/
/* Bit definitions and macros for MCF5208_SDRAMC_SDMR */
#define MCF5208_SDRAMC_SDMR_CMD                  (0x10000)
#define MCF5208_SDRAMC_SDMR_AD(x)                (((x)&0xFFF)<<0x12)
#define MCF5208_SDRAMC_SDMR_BK(x)                (((x)&0x3)<<0x1E)
#define MCF5208_SDRAMC_SDMR_BK_LMR               (0)
#define MCF5208_SDRAMC_SDMR_BK_LEMR              (0x40000000)

/* Bit definitions and macros for MCF5208_SDRAMC_SDCR */
#define MCF5208_SDRAMC_SDCR_IPALL                (0x2)
#define MCF5208_SDRAMC_SDCR_IREF                 (0x4)
#define MCF5208_SDRAMC_SDCR_DQS_OE(x)            (((x)&0x3)<<0xA)
#define MCF5208_SDRAMC_SDCR_MEM_PS               (0x2000)
#define MCF5208_SDRAMC_SDCR_PS_32                (0)
#define MCF5208_SDRAMC_SDCR_PS_16                (0x2000)
#define MCF5208_SDRAMC_SDCR_REF_CNT(x)           (((x)&0x3F)<<0x10)
#define MCF5208_SDRAMC_SDCR_OE_RULE              (0x400000)
#define MCF5208_SDRAMC_SDCR_ADDR_MUX(x)          (((x)&0x3)<<0x18)
#define MCF5208_SDRAMC_SDCR_REF_EN               (0x10000000)
#define MCF5208_SDRAMC_SDCR_DDR_MODE             (0x20000000)
#define MCF5208_SDRAMC_SDCR_CKE                  (0x40000000)
#define MCF5208_SDRAMC_SDCR_MODE_EN              (0x80000000)

/* Bit definitions and macros for MCF5208_SDRAMC_SDCFG1 */
#define MCF5208_SDRAMC_SDCFG1_WT_LAT(x)          (((x)&0x7)<<0x4)
#define MCF5208_SDRAMC_SDCFG1_REF2ACT(x)         (((x)&0xF)<<0x8)
#define MCF5208_SDRAMC_SDCFG1_PRE2ACT(x)         (((x)&0x7)<<0xC)
#define MCF5208_SDRAMC_SDCFG1_ACT2RW(x)          (((x)&0x7)<<0x10)
#define MCF5208_SDRAMC_SDCFG1_RD_LAT(x)          (((x)&0xF)<<0x14)
#define MCF5208_SDRAMC_SDCFG1_SWT2RWP(x)         (((x)&0x7)<<0x18)
#define MCF5208_SDRAMC_SDCFG1_SRD2RWP(x)         (((x)&0xF)<<0x1C)

/* Bit definitions and macros for MCF5208_SDRAMC_SDCFG2 */
#define MCF5208_SDRAMC_SDCFG2_BL(x)              (((x)&0xF)<<0x10)
#define MCF5208_SDRAMC_SDCFG2_BRD2W(x)           (((x)&0xF)<<0x14)
#define MCF5208_SDRAMC_SDCFG2_BWT2RWP(x)         (((x)&0xF)<<0x18)
#define MCF5208_SDRAMC_SDCFG2_BRD2RP(x)          (((x)&0xF)<<0x1C)

/* Bit definitions and macros for MCF5208_SDRAMC_SDCS */
#define MCF5208_SDRAMC_SDCS_CSSZ(x)              (((x)&0x1F)<<0)
#define MCF5208_SDRAMC_SDCS_CSSZ_DISABLED        (0)
#define MCF5208_SDRAMC_SDCS_CSSZ_1MBYTE          (0x13)
#define MCF5208_SDRAMC_SDCS_CSSZ_2MBYTE          (0x14)
#define MCF5208_SDRAMC_SDCS_CSSZ_4MBYTE          (0x15)
#define MCF5208_SDRAMC_SDCS_CSSZ_8MBYTE          (0x16)
#define MCF5208_SDRAMC_SDCS_CSSZ_16MBYTE         (0x17)
#define MCF5208_SDRAMC_SDCS_CSSZ_32MBYTE         (0x18)
#define MCF5208_SDRAMC_SDCS_CSSZ_64MBYTE         (0x19)
#define MCF5208_SDRAMC_SDCS_CSSZ_128MBYTE        (0x1A)
#define MCF5208_SDRAMC_SDCS_CSSZ_256MBYTE        (0x1B)
#define MCF5208_SDRAMC_SDCS_CSSZ_512MBYTE        (0x1C)
#define MCF5208_SDRAMC_SDCS_CSSZ_1GBYTE          (0x1D)
#define MCF5208_SDRAMC_SDCS_CSSZ_2GBYTE          (0x1E)
#define MCF5208_SDRAMC_SDCS_CSSZ_4GBYTE          (0x1F)
#define MCF5208_SDRAMC_SDCS_CSBA(x)              (((x)&0xFFF)<<0x14)
#define MCF5208_SDRAMC_SDCS_BA(x)                ((x)&0xFFF00000)


/*------------------------------------------------------------------------*/
/*
** Chip select macros
*/

/* Bit definitions and macros for MCF5208_FBCS_CSAR */
#define MCF5208_FBCS_CSAR_BA(x)                  ((x)&0xFFFF0000)

/* Bit definitions and macros for MCF5208_FBCS_CSMR */
#define MCF5208_FBCS_CSMR_V                      (0x1)
#define MCF5208_FBCS_CSMR_WP                     (0x100)
#define MCF5208_FBCS_CSMR_BAM(x)                 (((x)&0xFFFF)<<0x10)
#define MCF5208_FBCS_CSMR_BAM_4G                 (0xFFFF0000)
#define MCF5208_FBCS_CSMR_BAM_2G                 (0x7FFF0000)
#define MCF5208_FBCS_CSMR_BAM_1G                 (0x3FFF0000)
#define MCF5208_FBCS_CSMR_BAM_1024M              (0x3FFF0000)
#define MCF5208_FBCS_CSMR_BAM_512M               (0x1FFF0000)
#define MCF5208_FBCS_CSMR_BAM_256M               (0xFFF0000)
#define MCF5208_FBCS_CSMR_BAM_128M               (0x7FF0000)
#define MCF5208_FBCS_CSMR_BAM_64M                (0x3FF0000)
#define MCF5208_FBCS_CSMR_BAM_32M                (0x1FF0000)
#define MCF5208_FBCS_CSMR_BAM_16M                (0xFF0000)
#define MCF5208_FBCS_CSMR_BAM_8M                 (0x7F0000)
#define MCF5208_FBCS_CSMR_BAM_4M                 (0x3F0000)
#define MCF5208_FBCS_CSMR_BAM_2M                 (0x1F0000)
#define MCF5208_FBCS_CSMR_BAM_1M                 (0xF0000)
#define MCF5208_FBCS_CSMR_BAM_1024K              (0xF0000)
#define MCF5208_FBCS_CSMR_BAM_512K               (0x70000)
#define MCF5208_FBCS_CSMR_BAM_256K               (0x30000)
#define MCF5208_FBCS_CSMR_BAM_128K               (0x10000)
#define MCF5208_FBCS_CSMR_BAM_64K                (0)

/* Bit definitions and macros for MCF5208_FBCS_CSCR */
#define MCF5208_FBCS_CSCR_BSTW                   (0x8)
#define MCF5208_FBCS_CSCR_BSTR                   (0x10)
#define MCF5208_FBCS_CSCR_BEM                    (0x20)
#define MCF5208_FBCS_CSCR_PS(x)                  (((x)&0x3)<<0x6)
#define MCF5208_FBCS_CSCR_PS_32                  (0)
#define MCF5208_FBCS_CSCR_PS_8                   (0x40)
#define MCF5208_FBCS_CSCR_PS_16                  (0x80)
#define MCF5208_FBCS_CSCR_AA                     (0x100)
#define MCF5208_FBCS_CSCR_SBM                    (0x200)
#define MCF5208_FBCS_CSCR_WS(x)                  (((x)&0x3F)<<0xA)
#define MCF5208_FBCS_CSCR_WRAH(x)                (((x)&0x3)<<0x10)
#define MCF5208_FBCS_CSCR_RDAH(x)                (((x)&0x3)<<0x12)
#define MCF5208_FBCS_CSCR_ASET(x)                (((x)&0x3)<<0x14)
#define MCF5208_FBCS_CSCR_SWSEN                  (0x800000)
#define MCF5208_FBCS_CSCR_SWS(x)                 (((x)&0x3F)<<0x1A)



/*------------------------------------------------------------------------*/
/*
**                      TYPE DEFINITIONS
*/

/*
** SCM Registers
*/
typedef struct mcf5208_scm_a_struct {
    uint_32 MPR;
    uint_8  filler0[0x20 - 0x04];
    uint_32 PACRA;
    uint_32 PACRB;
    uint_32 PACRC;
    uint_32 PACRD;
    uint_32 PACRE;
    uint_32 PACRF;
    uint_8  filler1[0x54 - 0x48];
    uint_32 BMT;
} MCF5208_SCM_A_STRUCT, _PTR_ MCF5208_SCM_A_STRUCT_PTR;
typedef volatile struct mcf5208_scm_a_struct _PTR_ VMCF5208_SCM_A_STRUCT_PTR;

typedef struct mcf5208_scm_power_struct {
    uint_8  filler0[0x13 - 0x00];  
    uint_8  WCR;  
    uint_8  filler1[0x16 - 0x14];  
    uint_16 CWCR;  
    uint_8  filler2[0x1B - 0x18];  
    uint_8  CWSR;
    uint_8  filler3[0x1F - 0x1C];  
    uint_8  SCMISR; 
    uint_8  filler4[0x2C - 0x20];  
    uint_8  PPMSR0;
    uint_8  PPMCR0;
    uint_8  filler5[0x30 - 0x2E];  
    uint_32 PPMHR0;
    uint_32 PPMLR0;
    uint_8  filler6[0x70 - 0x38];  
    uint_32 CFADR;
    uint_8  filler7[0x75 - 0x24];  
    uint_8 CFIER;
    uint_8 CFLOC;  
    uint_8 CFATR; 
    uint_8  filler8[0x7C - 0x78];  
    uint_32 CFDTR;
} MCF5208_SCM_POWER_STRUCT, _PTR_ MCF5208_SCM_POWER_STRUCT_PTR;
typedef volatile struct mcf5208_scm_power_struct _PTR_ VMCF5208_SCM_POWER_STRUCT_PTR;

/*
** Cross-Bar Switch Module
*/
typedef struct mcf5208_xbs_struct {
    uint_8 filler0[0x4100 - 0x4000];
    uint_32 PRS1;
    uint_8 filler1[0x4110 - 0x4104];
    uint_32 CRS1;
    uint_8 filler2[0x4400 - 0x4114];
    uint_32 PRS4;
    uint_8 filler3[0x4410 - 0x4404];
    uint_32 CRS4;
    uint_8 filler4[0x4700 - 0x4414];
    uint_32 PRS7;
    uint_8 filler5[0x4710 - 0x4704];
    uint_32 CRS7;
} MCF5208_XBS_STRUCT, _PTR_ MCF5208_XBS_STRUCT_PTR;
typedef volatile struct mcf5208_xbs_struct _PTR_ VMCF5208_XBS_STRUCT_PTR;


/*
** MCF5208_TCD_STRUCT
** This structure defines what one Transfer Control Descriptor look like
*/
typedef struct mcf5208_tcd_struct
{
   uint_32 SADDR;               /* Source Address */
   uint_16 ATTR;                /* Transfer Attrbutes */
   uint_16 SOFF;                /* Signed Source Address Offset */
   uint_32 NBYTES;              /* Minor Byte Count */
   uint_32 SLAST;               /* Last Source Address Adjustment */
   uint_32 DADDR;               /* Destination Address */
   uint_16 CITER;               /* Current Minor Loop Link, Major Loop Count */
   uint_16 DOFF;                /* Signed Destination Address Offset */
   uint_32 DLAST_SGA;           /* Last Destination Address Adjustment/Scatter Gather Address*/
   uint_16 BITER;               /* Beginning Minor Loop Link, Major Loop Count */
   uint_16 CSR;                 /* Control and Status Register */
} MCF5208_TCD_STRUCT, _PTR_ MCF5208_TCD_STRUCT_PTR;
typedef volatile struct mcf5208_tcd_struct _PTR_ VMCF5208_TCD_STRUCT_PTR;

/*
** MCF5208_DMA_STRUCT
** This structure defines what one DMA registers look like
*/
typedef struct mcf5208_dma_struct
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
   uchar   DCHPRI[MCF5208_NUM_DMAS];                   /* eDMA Channel Priority Registers */
   uchar   filler6[3823];
   MCF5208_TCD_STRUCT TCD[MCF5208_NUM_DMAS];           /* Transfer Control Descriptors */
} MCF5208_DMA_STRUCT, _PTR_ MCF5208_DMA_STRUCT_PTR;
typedef volatile struct mcf5208_dma_struct _PTR_ VMCF5208_DMA_STRUCT_PTR;


/*
** MCF5208_IACK_STRUCT
** Interrupt acknowledgements
*/
typedef struct mcf5208_iack_struct
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

} MCF5208_IACK_STRUCT, _PTR_ MCF5208_IACK_STRUCT_PTR;
typedef volatile struct mcf5208_iack_struct _PTR_ VMCF5208_IACK_STRUCT_PTR;

/*
** MCF5208_ICTRL_STRUCT
** Interrupt controller
*/
typedef struct mcf5208_ictrl_struct
{
   uint_32  IPRH;                      /* Interrupt Pending Register High */
   uint_32  IPRL;                      /* Interrupt Pending Register Low */
   uint_32  IMRH;                      /* Interrupt Mask Register High */
   uint_32  IMRL;                      /* Interrupt Mask Register Low */
   uint_32  INTFRCH;                   /* Interrupt Force Register High */
   uint_32  INTFRCL;                   /* Interrupt Force Register Low */
   uchar    filler1[2];
   uint_16  ICONFIG;                   /* Interrupt Configuration Register */
   uchar    SIMR;                      /* Set Interrupt Mask */
   uchar    CIMR;                      /* Clear Interrupt Mask */
   uchar    CLMASK;                    /* Current Level Mask */
   uchar    SLMASK;                    /* Saved Level Mask */
   uchar    filler2[32];
   uchar    ICR[64];                   /* Interrupt Control Registers, 1-63 */
   uchar    filler3[96];
   uchar    SWIACK;                    /* Software Interrupt Acknowledge Register */
   MCF5208_IACK_STRUCT IACK;           /* Level Interrupt Acknowledge Registers */
   uchar        filler4[0xc000 - (0x80e1 + sizeof(MCF5208_IACK_STRUCT))];
} MCF5208_ICTRL_STRUCT, _PTR_ MCF5208_ICTRL_STRUCT_PTR;
typedef volatile struct mcf5208_ictrl_struct _PTR_ VMCF5208_ICTRL_STRUCT_PTR;

/*
** MCF5208_TIMER_STRUCT
** This structure defines what one timer register look like
*/
typedef struct mcf5208_dma_timer_struct
{
   uint_16  DTMR;           /* DMA Timer mode register */
   uchar    DTXTMR;         /* DMA Timer extended mode register */
   uchar    DTER;           /* DMA Timer event register */
   uint_32  DTRR;           /* DMA Timer reference register */
   uint_32  DTCR;           /* DMA Timer capture register */
   uint_32  DTCN;           /* DMA Timer counter register */
   uchar   filler1[16368];
} MCF5208_DMA_TIMER_STRUCT, _PTR_ MCF5208_DMA_TIMER_STRUCT_PTR;
typedef volatile struct mcf5208_dma_timer_struct _PTR_ VMCF5208_DMA_TIMER_STRUCT_PTR;

/*
** MCF5208_GPIO_STRUCT
** GPIO Registers
*/
typedef struct mcf5208_gpio_struct
{
    /* Port Output Data Registers */
    uchar   PODR_BUSCTL, PODR_BE, PODR_CS, PODR_FECI2C, PODR_QSPI;
    uchar   PODR_TIMER, PODR_UART, PODR_FECH, PODR_FECL;
    uchar   fillerA[0x400C-0x4009];
    /* Port Data Direction Registers */
    uchar   PDDR_BUSCTL, PDDR_BE, PDDR_CS, PDDR_FECI2C, PDDR_QSPI;
    uchar   PDDR_TIMER, PDDR_UART, PDDR_FECH, PDDR_FECL;
    uchar   fillerB[0x4018-0x4015];
    /* Port Pin Data/Set Data Registers */
    uchar   PPDSDR_BUSCTL, PPDSDR_BE, PPDSDR_CS, PPDSDR_FECI2C, PPDSDR_QSPI;
    uchar   PPDSDR_TIMER, PPDSDR_UART, PPDSDR_FECH, PPDSDR_FECL;
    uchar   fillerC[0x4024-0x4021];
    /* Port Clear Output Data Registers */
    uchar   PCLRR_BUSCTL, PCLRR_BE, PCLRR_CS, PCLRR_FECI2C, PCLRR_QSPI;
    uchar   PCLRR_TIMER, PCLRR_UART, PCLRR_FECH, PCLRR_FECL;
    uchar   fillerD[0x4030-0x402D];
    /* Port Pin Assignment Registers */
    uchar   PAR_BUSCTL, PAR_BE, PAR_CS, PAR_FECI2C, PAR_QSPI;
    uchar   PAR_TIMER;
    uint_16 PAR_UART;
    uchar   PAR_FEC, PAR_IRQ;
    /* Mode Select Control Registers */
    uchar   MSCR_FLEXBUS, MSCR_SDRAM;
    /* Drive Strength Control Registers */
    uchar   DSCR_I2C, DSCR_MISC, DSCR_FEC, DSCR_UART, DSCR_QSPI; 
} MCF5208_GPIO_STRUCT, _PTR_ MCF5208_GPIO_STRUCT_PTR;
typedef volatile struct mcf5208_gpio_struct _PTR_ VMCF5208_GPIO_STRUCT_PTR;

/*
** MCF5208_CCM_STRUCT
** ColdFire Integration Module
*/
typedef struct mcf5208_ccm_struct
{
   uchar    RCR;            /* Reset control register */
   uchar    RSR;            /* Reset status register */
   uchar    filler1[2];
   uint_16  CCR;            /* Chip Configuration Register */
   uchar    filler2;
   uchar    LPCR;           /* Low-Power Control Register */
   uint_16  RCON;           /* Reset Configuration Register */
   uint_16  CIR;            /* Chip Identification Register */
   uchar    filler3[4];
   uint_16  MISCCR;         /* Miscellaneous Control Register */
} MCF5208_CCM_STRUCT, _PTR_ MCF5208_CCM_STRUCT_PTR;
typedef volatile struct mcf5208_ccm_struct _PTR_ VMCF5208_CCM_STRUCT_PTR;

/*
** MCF5208_PLL_STRUCT
** Clock module registers
*/
typedef struct mcf5208_pll_struct
{
   uint_8   PODR;         /* PLL Output Divider Register */
   uint_8   filler0;
   uint_8   PCR;          /* PLL Control Register */
   uint_8   filler1;
   uint_8   PMDR;         /* PLL Modulation Divider Register */
   uint_8   filler2;
   uint_8   PFDR;         /* PLL Feedback Divider Register */
} MCF5208_PLL_STRUCT, _PTR_ MCF5208_PLL_STRUCT_PTR;
typedef volatile struct mcf5208_pll_struct _PTR_ VMCF5208_PLL_STRUCT_PTR;

/*
** MCF5208_EPORT_STRUCT
** Edge port registers
*/
typedef struct mcf5208_eport_struct
{
   uint_16  EPPAR;            /* EPORT pin assignment register */
   uchar    EPDDR;            /* EPORT data direction register */
   uchar    EPIER;            /* EPORT interrupt enable register */
   uchar    EPDR;             /* EPORT data register */
   uchar    EPPDR;            /* EPORT pin data register */
   uchar    EPFR;             /* EPORT flag register */
} MCF5208_EPORT_STRUCT, _PTR_ MCF5208_EPORT_STRUCT_PTR;
typedef volatile struct mcf5208_eport_struct _PTR_ VMCF5208_EPORT_STRUCT_PTR;
/*
** MCF5208_WATCHDOG_STRUCT
** Watchdog timer
*/
typedef struct mcf5208_watchdog_struct
{
   uint_16  WCR;            /* Watchdog control register */
   uint_16  WMR;            /* Watchdog modulus register */
   uint_16  WCNTR;          /* Watchdog count register */
   uint_16  WSR;            /* Watchdog service register */
} MCF5208_WATCHDOG_STRUCT, _PTR_ MCF5208_WATCHDOG_STRUCT_PTR;
typedef volatile struct mcf5208_watchdog_struct _PTR_ VMCF5208_WATCHDOG_STRUCT_PTR;

typedef union mcf5208_uart_struct
{
   struct  {
      uchar UMR;             /* UART Mode Register */
      uchar filler1[3];
      uchar USR;             /* UART Status Register */
      uchar filler2[3];
      uchar UCR;             /* UART Command Register */
      uchar filler3[3];
      uchar URB;             /* UART Receiver Buffers */
      uchar filler4[3];
      uchar UIPCR;           /* UART Input Port Change Register */
      uchar filler5[3];
      uchar UISR;            /* UART Interrupt Status Register */
      uchar filler6[3];
      uchar UBG1;            /* UART Baud Rate Generator Register 1 */
      uchar filler7[3];
      uchar UBG2;            /* UART Baud Rate Generator Register 2 */
      uchar filler8[23];
      uchar UIP;             /* UART Input Port Register */
      uchar filler9[3];
      uchar UOP1;            /* UART Output Port Bit Set Command Register 1 */
      uchar filler10[3];
      uchar UOP0;            /* UART Output Port Bit Set Command Register 2 */
      uchar filler11[16323];
   } READ;
   struct  {
      uchar UMR;             /* UART Mode Register */
      uchar filler1[3];
      uchar UCSR;            /* UART Clock Select Register */
      uchar filler2[3];
      uchar UCR;             /* UART Command Register */
      uchar filler3[3];
      uchar UTB;             /* UART Transmit Buffers */
      uchar filler4[3];
      uchar UACR;            /* UART Auxillary Control Register */
      uchar filler5[3];
      uchar UIMR;            /* UART Interrupt Mask Register */
      uchar filler6[3];
      uchar UBG1;            /* UART Baud Rate Generator Register 1 */
      uchar filler7[3];
      uchar UBG2;            /* UART Baud Rate Generator Register 2 */
      uchar filler8[23];
      uchar UIP;             /* UART Input Port Register */
      uchar filler9[3];
      uchar UOP1;            /* UART Output Port Bit Set Command Register 1 */
      uchar filler10[3];
      uchar UOP0;            /* UART Output Port Bit Set Command Register 2 */
      uchar filler11[16323];
   } WRITE;
} MCF5208_UART_STRUCT, _PTR_ MCF5208_UART_STRUCT_PTR;

/*
** MCF5208_STRUCT
** This structure defines the memory/registers provided by the MCF5208
*/
typedef struct mcf5208_struct
{
    MCF5208_SCM_A_STRUCT        SCM_A;                              /* SCM (MPR and PACRs) */
    uchar                       filler0[0xFC004000 - ( 0xFC000000 + sizeof(MCF5208_SCM_A_STRUCT))];   
    MCF5208_XBS_STRUCT          XBS;                                /* Crossbar Switch */
    uchar                       filler1[0xFC008000 - (0xFC004000 + sizeof(MCF5208_XBS_STRUCT))];   
    MCF5XXX_FB_STRUCT           FB[MCF5208_NUM_FB_CS];              /* FlexBus Module */
    uchar                       filler2[0xFC030000 - (0xFC008000 + (MCF5208_NUM_FB_CS * sizeof(MCF5XXX_FB_STRUCT)))];   
    MCF5XXX_FEC_STRUCT          FEC;                                /* Fast Ethernet Controller - Registers and MIB RAM */
    uchar                       filler3[0xFC040000 - (0xFC030000 + sizeof(MCF5XXX_FEC_STRUCT))];   
    MCF5208_SCM_POWER_STRUCT    SCM_POWER;                          /* SCM (CWT and Core Fault) and Power Management */
    uchar                       filler4[0xFC044000 - ( 0xFC040000 + sizeof(MCF5208_SCM_POWER_STRUCT))];   
    MCF5208_DMA_STRUCT          DMA;                                /* eDMA Controller */
    uchar                       filler5[0xfc048000 - (0xFC044000 + sizeof(MCF5208_DMA_STRUCT))];
    MCF5208_ICTRL_STRUCT        ICTRL;                             /* Interrupt Controller 0 and 1 */
    uchar                       filler6[0xfc058000 - (0xfc048000 + sizeof(MCF5208_ICTRL_STRUCT))];
    MCF52XX_I2C_STRUCT          I2C;                                /* I2C Registers */
    uchar                       filler7[0xfc05C000 - (0xfc058000 + sizeof(MCF52XX_I2C_STRUCT))];
    MCF5XXX_QSPI_STRUCT         QSPI;                               /* QSPI Registers */
    uchar                       filler8[0xfc060000 - (0xfc05C000 + sizeof(MCF5XXX_QSPI_STRUCT))];
    MCF5208_UART_STRUCT         UART[MCF5208_NUM_UARTS];            /* UARTs */
    uchar                       filler9[0xfc070000 - (0xfc060000 + MCF5208_NUM_UARTS * sizeof(MCF5208_UART_STRUCT))];
    MCF5208_DMA_TIMER_STRUCT    DMA_TIMER[MCF5208_NUM_DMA_TIMERS];  /* DMA Timers */
    /*uchar                     filler10[0xfc080000 - (0xfc070000 + MCF5208_NUM_DMA_TIMERS * sizeof(MCF5208_DMA_TIMER_STRUCT))]; */
    MCF5XXX_PIT_STRUCT          PIT[MCF5208_NUM_TIMERS];   /* Programmable Interrupt Timers */
    /*uchar                     filler11[0xfc088000 - (0xfc080000 + MCF5208_NUM_TIMERS * sizeof(MCF5XXX_PIT_STRUCT))]; */
    MCF5208_EPORT_STRUCT        EPORT;                              /* Edge Port */
    uchar                       filler12[0xfc08C000 - (0xfc088000 + sizeof(MCF5208_EPORT_STRUCT))];
    MCF5208_WATCHDOG_STRUCT     WATCHDOG;
    uchar                       filler13[0xfc090000 - (0xfc08C000 + sizeof(MCF5208_WATCHDOG_STRUCT))];
    MCF5208_PLL_STRUCT          PLL;                                /* PLL (CLK Controller) */
    uchar                       filler14[0xfc0A0000 - (0xfc090000 + sizeof(MCF5208_PLL_STRUCT))];
    MCF5208_CCM_STRUCT          CCM;                                /* CCM, Reset Controller, Power Management */
    uchar                       filler15[0xfc0A4000 - (0xfc0A0000 + sizeof(MCF5208_CCM_STRUCT))];
    MCF5208_GPIO_STRUCT         GPIO;                               /* GPIO Controller */
    uchar                       filler16[0xfc0A8000 - (0xfc0A4000 + sizeof(MCF5208_GPIO_STRUCT))];
    MCF5XXX_SDRAM_CTRL_STRUCT   SDRAMC;                             /* SDRAM */
} MCF5208_STRUCT, _PTR_ MCF5208_STRUCT_PTR;
typedef volatile struct mcf5208_struct _PTR_ VMCF5208_STRUCT_PTR;

/*
** PSP_SUPPORT_STRUCT
** This structure is used to maintain the PSP support information
*/
typedef struct psp_support_struct
{
   uint_32 ACR_VALS[MCF5208_NUM_ACRS];
/*   uint_32 ACR_COUNT;   /* How many ACRs set so far */
   uint_32 Reserved;

} PSP_SUPPORT_STRUCT, _PTR_ PSP_SUPPORT_STRUCT_PTR;

/*------------------------------------------------------------------------*/
/*
**                      FUNCTION PROTOTYPES AND GLOBAL EXTERNS
*/

extern volatile uint_32 _psp_saved_cacr;
extern volatile uint_32 _psp_saved_acr0;
extern volatile uint_32 _psp_saved_acr1;
extern          uchar   __KERNEL_DATA_VERIFY_ENABLE[]; /* CR1327 */

extern void    _mcf5208_initialize_support(uint_32);

extern void    _mcf5208_cache_enable(uint_32);
extern void    _mcf5208_cache_disable(void);
extern void    _mcf5208_icache_invalidate(void);
extern void    _mcf5208_dcache_invalidate(void);

extern void    _icache_invalidate_mlines(pointer,uint_32,uint_32);
extern void    _dcache_flush_invalidate_mlines(pointer,uint_32,uint_32,uint_32,uint_32);

extern void    __psp_enable_acrs(uint_32_ptr);
extern void    __psp_clear_acrs(void);

void _psp_dcache_flush_all(uint_32, uint_32, uint_32);
void _dcache_flush(pointer, uint_32, uint_32);

#endif /*__ASM__*/

#ifdef __cplusplus
}
#endif

#endif /* __mcf5208_h__ */
/* EOF */
