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
* $FileName: mcf5445.h$
* $Version : 3.7.28.0$
* $Date    : Jan-18-2011$
*
* Comments:
*
*   This file contains the type definitions for the mcf5445x processors.
*
*END************************************************************************/

#ifndef __mcf5445_h__
#define __mcf5445_h__

#define __mcf5445_h__version "$Version:3.7.28.0$"
#define __mcf5445_h__date    "$Date:Jan-18-2011$"

#ifndef __ASM__

/* Include registers for modules common to all Coldfire processors */
#include <mcf5xxx_fec.h>        /* FEC */
#include <mcf54xx_rtc.h>        /* RTC */
#include <mcf54xx_ictl.h>       /* CTRL */   
#include <mcf5xxx_pit.h>
#include <mcf54xx_sdramc.h>
#include <mcf54xx_uart.h>       /* UART */
#include <mcf5xxx_fb.h>
#include <mcf54xx_ccm.h>
#include <mcf54xx_i2c.h>
#include <mcf5xxx_dspi.h>
#include <mcf5xxx_usbotg.h>     /* USBOTG */


#endif // __ASM__

#ifdef __cplusplus
extern "C" {
#endif

/*------------------------------------------------------------------------*/
/*
**                    CONSTANT DEFINITIONS
*/

#define PSP_HAS_DSP                         1
#define PSP_HAS_EMAC                        1

#define PSP_ACR_CNT                         4       // ACR registers count

/*
** Cache and MMU definition values
*/
#define PSP_HAS_MMU                         1
#define PSP_HAS_CODE_CACHE                  0
#define PSP_HAS_DATA_CACHE                  0

#define PSP_CACHE_SPLIT                     1

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
#define MCF5445_NUM_TIMERS                  (4)     // PIT
#define MCF5445_NUM_UARTS                   (3)
#define MCF5445_NUM_DMA_CH                  (16)    // DMA channels
#define MCF5445_NUM_DMA_TIMERS              (4)     // DMA timer

#define MCF5445_NUM_FB_CS                   (6)

#define MCF5445_NUM_ACRS                    (4)
#define MCF5445_NUM_DATA_ACRS               (2)
#define MCF5445_NUM_INSTR_ACRS              (2)
#define MCF5445_FIRST_DATA_ACR              (0)
#define MCF5445_FIRST_INSTR_ACR             (2)

/* Error codes from mcf548x_mmu_add_region */
#define MCF5445_OUT_OF_ACRS                 (0x00100000)

/* Do you want to verify kernel data can be read and written correctly */
#define PSP_KERNEL_DATA_VERIFY_ENABLE       ((uint_32)__KERNEL_DATA_VERIFY_ENABLE)


#define _PSP_BYTES_TO_LINES(b)              (((b) + (PSP_CACHE_LINE_SIZE - 1)) / PSP_CACHE_LINE_SIZE)
#define _PSP_MASK_CACHE_ADDR(p)             (pointer)(((uint_32)p) & ~(PSP_CACHE_LINE_SIZE - 1))

/*
** Standard cache macros
*/

#if PSP_HAS_DATA_CACHE

#define _DCACHE_ENABLE(n)                   _mcf5445_dcache_enable(n)
#define _DCACHE_DISABLE()                   _mcf5445_dcache_disable()

//#define _DCACHE_FLUSH()                     _psp_dcache_flush_all(PSP_CACHE_LINE_SIZE, PSP_DCACHE_NUM_WAYS, PSP_DCACHE_NUM_SETS)
//#define _DCACHE_FLUSH_MBYTES(p, m)          _dcache_flush_phy(_PSP_MASK_CACHE_ADDR(p), _PSP_BYTES_TO_LINES(m), PSP_CACHE_LINE_SIZE)
//#define _DCACHE_FLUSH_LINE(p)               _DCACHE_FLUSH_MBYTES(p, 1)

#define _DCACHE_FLUSH()                     // data cache is writethrough
#define _DCACHE_FLUSH_MBYTES(p, m)          // data cache is writethrough
#define _DCACHE_FLUSH_LINE(p)               // data cache is writethrough

#define _DCACHE_INVALIDATE()                _mcf5445_dcache_invalidate()
#define _DCACHE_INVALIDATE_LINE(p)          _DCACHE_INVALIDATE_MBYTES(p, 1)
#define _DCACHE_INVALIDATE_MBYTES(p, m)     _dcache_flush_phy(_PSP_MASK_CACHE_ADDR(p), _PSP_BYTES_TO_LINES(m), PSP_CACHE_LINE_SIZE)

#else

#define _DCACHE_ENABLE(n)
#define _DCACHE_DISABLE()
#define _DCACHE_FLUSH()
#define _DCACHE_FLUSH_LINE(p)
#define _DCACHE_FLUSH_MBYTES(p, m)
#define _DCACHE_INVALIDATE()
#define _DCACHE_INVALIDATE_LINE(p)
#define _DCACHE_INVALIDATE_MBYTES(p, m)

#endif  // PSP_HAS_DATA_CACHE



#if PSP_HAS_CODE_CACHE 

#define _ICACHE_ENABLE(n)                   _mcf5445_icache_enable(n)
#define _ICACHE_DISABLE()                   _mcf5445_icache_disable()
#define _ICACHE_INVALIDATE()                _mcf5445_icache_invalidate()
#define _ICACHE_INVALIDATE_LINE(p)          _ICACHE_INVALIDATE_MBYTES(p, 1)
#define _ICACHE_INVALIDATE_MBYTES(p, m)     _icache_invalidate_mlines(p, _PSP_BYTES_TO_LINES(m), PSP_CACHE_LINE_SIZE)

#else

#define _ICACHE_ENABLE(n)
#define _ICACHE_DISABLE()
#define _ICACHE_INVALIDATE()
#define _ICACHE_INVALIDATE_LINE(p)
#define _ICACHE_INVALIDATE_MBYTES(p, m)

#endif  // PSP_HAS_CODE_CACHE

#if PSP_HAS_CODE_CACHE || PSP_HAS_DATA_CACHE

#define _MMU_DISABLE()      _mmu_disable()
#define _MMU_ENABLE()       _mmu_enable()

#else

#define _MMU_DISABLE()
#define _MMU_ENABLE()

#endif




#define MCF54XX_CACHE_CACHEABLE_WRITETHROUGH    0       /* Unbuffered */
#define MCF54XX_CACHE_CACHEABLE_COPYBACK        1       /* Write buffered */
#define MCF54XX_CACHE_NONCACHEABLE_UNBUFFERED   2
#define MCF54XX_CACHE_NONCACHEABLE_BUFFERED     3

/*
** Cache control register bits
*/
#define MCF54XX_CACR_DEC                        (1 << 31)           // Enable data cache.
#define MCF54XX_CACR_DW                         (1 << 30)           // Data default write-protect.
#define MCF54XX_CACR_DESB                       (1 << 29)           // Enable data store buffer.
#define MCF54XX_CACR_DDPI                       (1 << 28)           // Disable CPUSHL invalidation.
#define MCF54XX_CACR_DHLCK                      (1 << 27)           // Half-data cache lock mode
#define MCF54XX_CACR_DDCM(x)                    (((x) & 3) << 25)   // Default data cache mode.
#define MCF54XX_CACR_DCINVA                     (1 << 24)           // Data cache invalidate all.
#define MCF54XX_CACR_DDSP                       (1 << 23)           // Data default supervisor-protect.
#define MCF5445_CACR_IVO                        (1 << 20)           // Invalidate only
#define MCF54XX_CACR_BEC                        (1 << 19)           // Enable branch cache.
#define MCF54XX_CACR_BCINVA                     (1 << 18)           // Branch cache invalidate.
#define MCF54XX_CACR_IEC                        (1 << 15)           // Enable instruction cache
#define MCF5445_CACR_SPA                        (1 << 14)           // Search by physical address
#define MCF54XX_CACR_DNFB                       (1 << 13)           // Default cache-inhibited fill buffer
#define MCF54XX_CACR_IDPI                       (1 << 12)           // Instruction CPUSHL invalidate disable
#define MCF54XX_CACR_IHLCK                      (1 << 11)           // Instruction cache half-lock
#define MCF54XX_CACR_IDCM                       (1 << 10)           // Instruction default cache mode
#define MCF54XX_CACR_ICINVA                     (1 << 8)            // Invalidate instr cache
#define MCF54XX_CACR_IDSP                       (1 << 7)            // Default instruction supervisor protection bit
#define MCF54XX_CACR_EUSP                       (1 << 5)            // Enable user stack pointer

// Bits that should be cleared
#define MCF5445_CACR_CLEAR_BITS                 (0x63025F)

// These bits automatically clear after the operation
#define CACR_AUTO_CLEAR_BITS    (MCF54XX_CACR_DCINVA|MCF54XX_CACR_ICINVA|MCF54XX_CACR_BCINVA)


/*
** Access control register bits
** See Table 7-5. ACRn Field Descriptions
*/
#define MCF54XX_ACR_BASE_ADDR                   (0xFF000000)
#define MCF54XX_ACR_BASE_ADDR_MASK              (0x00FF0000)
#define MCF54XX_ACR_ENABLE                      (0x00008000)
#define MCF54XX_ACR_EXEC_CACHE_MATCH            (0x00004000)
#define MCF54XX_ACR_USER_ACCESS_FC              (0x00000000)
#define MCF54XX_ACR_SUPER_ACCESS_FC             (0x00002000)
#define MCF54XX_ACR_AMM                         (0x00000400)
#define MCF54XX_ACR_SUPERVISOR_PROTECT          (0x00000008)
#define MCF54XX_ACR_WRITE_PROTECT               (0x00000004)
        // 0: Cacheable, write-through   (no write buffer)
        // 2: Cacheable, copyback        (write buffered)
        // 4: Cache-inhibited, precise   (no write buffer)
        // 6: Cache-inhibited, imprecise (write buffered)
#define MCF54XX_ACR_NONCACHEABLE_MODE           (0x00000040)
#define MCF54XX_ACR_CACHEABLE_MODE              (0x00000000)
#define MCF54XX_ACR_BUFFER_WRITE_ENABLE         (0x00000020)


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

/* Bit definitions and macros for PAR_FEC */
#define MCF5445_GPIO_PAR_FEC_FEC0(x)            ((x) & 7)
#define MCF5445_GPIO_PAR_FEC_FEC0_GPIO          (0)
#define MCF5445_GPIO_PAR_FEC_FEC0_ULPI_GPIO     (1)
#define MCF5445_GPIO_PAR_FEC_FEC0_RMII_ULPI     (2)
#define MCF5445_GPIO_PAR_FEC_FEC0_RMII_GPIO     (3)
#define MCF5445_GPIO_PAR_FEC_FEC0_MII           (7)
#define MCF5445_GPIO_PAR_FEC_FEC1(x)            (((x) & 7) << 4)
#define MCF5445_GPIO_PAR_FEC_FEC1_GPIO          (0)
#define MCF5445_GPIO_PAR_FEC_FEC1_ATA           (0x10)
#define MCF5445_GPIO_PAR_FEC_FEC1_RMII_ATA      (0x20)
#define MCF5445_GPIO_PAR_FEC_FEC1_RMII_GPIO     (0x30)
#define MCF5445_GPIO_PAR_FEC_FEC1_MII           (0x70)

// Bit definitions and macros for PAR_DMA
#define MCF5445_GPIO_PAR_DMA_DREQ0              (1)
#define MCF5445_GPIO_PAR_DMA_DREQ0_GPIO         (0)
#define MCF5445_GPIO_PAR_DMA_DREQ0_DREQ0        (1)
#define MCF5445_GPIO_PAR_DMA_DACK0(x)           (((x) & 3) << 2)
#define MCF5445_GPIO_PAR_DMA_DACK0_GPIO         (0)
#define MCF5445_GPIO_PAR_DMA_DACK0_DSPI_CS3     (8)
#define MCF5445_GPIO_PAR_DMA_DACK0_DMA          (0xc)
#define MCF5445_GPIO_PAR_DMA_DREQ1(x)           (((x) & 3) << 4)
#define MCF5445_GPIO_PAR_DMA_DREQ1_GPIO         (0)
#define MCF5445_GPIO_PAR_DMA_DREQ1_USB_CLKIN    (0x10)
#define MCF5445_GPIO_PAR_DMA_DREQ1_DMA          (0x30)
#define MCF5445_GPIO_PAR_DMA_DACK1(x)           (((x) & 3) << 6)
#define MCF5445_GPIO_PAR_DMA_DACK1_GPIO         (0)
#define MCF5445_GPIO_PAR_DMA_DACK1_ULPI         (0x40)
#define MCF5445_GPIO_PAR_DMA_DACK1_DMA          (0xC0)


// Bit definitions and macros for PAR_USB
#define MCF5445_GPIO_PAR_USB_VBUSOC(x)          ((x) & 3)
#define MCF5445_GPIO_PAR_USB_VBUSOC_GPIO        (0)
#define MCF5445_GPIO_PAR_USB_VBUSOC_ULPI_STP    (1)
#define MCF5445_GPIO_PAR_USB_VBUSOC_VBUSOC      (3)
#define MCF5445_GPIO_PAR_USB_VBUSEN(x)          (((x)& 3) << 2)
#define MCF5445_GPIO_PAR_USB_VBUSEN_GPIO        (0)
#define MCF5445_GPIO_PAR_USB_VBUSEN_ULPI_NXT    (4)
#define MCF5445_GPIO_PAR_USB_VBUSEN_USBPULLUP   (8)
#define MCF5445_GPIO_PAR_USB_VBUSEN_VBUSEN      (0x0c)

/* Bit definitions and macros for PAR_UART */
#define MCF5445_GPIO_PAR_UART_U0TXD             (0x1)
#define MCF5445_GPIO_PAR_UART_U0TXD_GPIO        (0)
#define MCF5445_GPIO_PAR_UART_U0TXD_U0TXD       (0x1)
#define MCF5445_GPIO_PAR_UART_U0RXD             (0x2)
#define MCF5445_GPIO_PAR_UART_U0RXD_GPIO        (0)
#define MCF5445_GPIO_PAR_UART_U0RXD_U0RXD       (0x2)
#define MCF5445_GPIO_PAR_UART_U0RTS             (0x4)
#define MCF5445_GPIO_PAR_UART_U0RTS_GPIO        (0)
#define MCF5445_GPIO_PAR_UART_U0RTS_U0RTS       (0x4)
#define MCF5445_GPIO_PAR_UART_U0CTS             (0x8)
#define MCF5445_GPIO_PAR_UART_U0CTS_GPIO        (0)
#define MCF5445_GPIO_PAR_UART_U0CTS_U0CTS       (0x8)
#define MCF5445_GPIO_PAR_UART_U1TXD             (0x10)
#define MCF5445_GPIO_PAR_UART_U1TXD_GPIO        (0)
#define MCF5445_GPIO_PAR_UART_U1TXD_U1TXD       (0x10)
#define MCF5445_GPIO_PAR_UART_U1RXD             (0x20)
#define MCF5445_GPIO_PAR_UART_U1RXD_GPIO        (0)
#define MCF5445_GPIO_PAR_UART_U1RXD_U1RXD       (0x20)
#define MCF5445_GPIO_PAR_UART_U1RTS             (0x40)
#define MCF5445_GPIO_PAR_UART_U1RTS_GPIO        (0)
#define MCF5445_GPIO_PAR_UART_U1RTS_U1RTS       (0x40)
#define MCF5445_GPIO_PAR_UART_U1CTS             (0x80)
#define MCF5445_GPIO_PAR_UART_U1CTS_GPIO        (0)
#define MCF5445_GPIO_PAR_UART_U1CTS_U1CTS       (0x80)

/* Bit definitions and macros for PAR_FECI2C */
#define MCF5445_GPIO_PAR_FECI2C_SDA(x)          ((x) & 3)
#define MCF5445_GPIO_PAR_FECI2C_SDA_GPIO        (0)
#define MCF5445_GPIO_PAR_FECI2C_SDA_U2RXD       (0x1)
#define MCF5445_GPIO_PAR_FECI2C_SDA_SDA         (0x3)
#define MCF5445_GPIO_PAR_FECI2C_SCL(x)          (((x) & 3) << 2)
#define MCF5445_GPIO_PAR_FECI2C_SCL_GPIO        (0)
#define MCF5445_GPIO_PAR_FECI2C_SCL_U2TXD       (0x4)
#define MCF5445_GPIO_PAR_FECI2C_SCL_SCL         (0xC)
#define MCF5445_GPIO_PAR_FECI2C_MDIO0           (0x10)
#define MCF5445_GPIO_PAR_FECI2C_MDIO0_GPIO      (0)
#define MCF5445_GPIO_PAR_FECI2C_MDIO0_MDIO0     (0x10)
#define MCF5445_GPIO_PAR_FECI2C_MDC0            (0x40)
#define MCF5445_GPIO_PAR_FECI2C_MDC0_GPIO       (0)
#define MCF5445_GPIO_PAR_FECI2C_MDC0_MDC0       (0x40)
#define MCF5445_GPIO_PAR_FECI2C_MDIO1(x)        (((x) & 3) << 8)
#define MCF5445_GPIO_PAR_FECI2C_MDIO1_GPIO      (0)
#define MCF5445_GPIO_PAR_FECI2C_MDIO1_ATA_DIOW  (0x200)
#define MCF5445_GPIO_PAR_FECI2C_MDIO1_MDIO1     (0x300)
#define MCF5445_GPIO_PAR_FECI2C_MDC1(x)         (((x) & 3) << 10)
#define MCF5445_GPIO_PAR_FECI2C_MDC1_GPIO       (0)
#define MCF5445_GPIO_PAR_FECI2C_MDC1_ATA_DIOR   (0x800)
#define MCF5445_GPIO_PAR_FECI2C_MDC1_MDC1       (0xC00)



#define MCF5445_GPIO_MSCR_SDRAM_SDCTL(x)        ((x) & 3)
#define MCF5445_GPIO_MSCR_SDRAM_SDCLK(x)        (((x) & 3) << 2)
#define MCF5445_GPIO_MSCR_SDRAM_SDDQS(x)        (((x) & 3) << 4)
#define MCF5445_GPIO_MSCR_SDRAM_SDDATA(x)       (((x) & 3) << 6)

#define MCF5445_GPIO_MSCR_SDRAM_SDXXX_HS_LPDDR  (0)
#define MCF5445_GPIO_MSCR_SDRAM_SDXXX_FS_LPDDR  (1)
#define MCF5445_GPIO_MSCR_SDRAM_SDXXX_DDR2      (2)
#define MCF5445_GPIO_MSCR_SDRAM_SDXXX_DDR1      (3)

#define MCF5445_GPIO_MSCR_PCI_PCI(x)            ((x) & 1)

/* Bit definitions and macros for MCF_CLOCK_PCR */
#define MCF5445_PLL_PCR_OUTDIV1(x)          ((x) & 0x0f)
#define MCF5445_PLL_PCR_OUTDIV2(x)          (((x) & 0x0f) << 4)
#define MCF5445_PLL_PCR_OUTDIV3(x)          (((x) & 0x0f) << 8)
#define MCF5445_PLL_PCR_OUTDIV4(x)          (((x) & 0x0f) << 12)
#define MCF5445_PLL_PCR_OUTDIV5(x)          (((x) & 0x0f) << 16)
#define MCF5445_PLL_PCR_PFDR(x)             (((x) & 0xff) << 24)

/* Bit definitions and macros for SYNSR */
#define MCF5445_PLL_PSR_LOCKS               (0x01)
#define MCF5445_PLL_PSR_LOCK                (0x02)
#define MCF5445_PLL_PSR_LOLIRQ              (0x04)
#define MCF5445_PLL_PSR_LOLRE               (0x08)


/*
** Interrupt definitions
*/
#define MCF5445_ICTRL_MASKALL               1
#define MCF5445_ICTRL0_BASEx                64
#define MCF5445_ICTRL1_BASEx                128

/*
** Interrupt vector table
*/
typedef enum mcf5445_interrupt_table_index {
    MCF5445_boot_stack_pointer,
    MCF5445_boot_program_counter,
    MCF5445_EXC_ACCESS_ERROR,
    MCF5445_EXC_ADDRESS_ERROR,
    MCF5445_EXC_ILLEGAL_INSTRUCTION,
    MCF5445_EXC_DIVIDE_BY_ZERO,
    MCF5445_EXC_rsvd6,
    MCF5445_EXC_rsvd7,
    MCF5445_EXC_PRIVILEGE_VIOLATION,
    MCF5445_EXC_NEXT_TRACE,
    MCF5445_EXC_UNIMPLEMENTED_LINE_A_OPCODE,
    MCF5445_EXC_UNIMPLEMENTED_LINE_F_OPCODE,
    MCF5445_EXC_DEBUG,
    MCF5445_EXC_rsvd13,
    MCF5445_EXC_FORMAT_ERROR,
    MCF5445_EXC_rsvd15,
    MCF5445_EXC_rsvd16,
    MCF5445_EXC_rsvd17,
    MCF5445_EXC_rsvd18,
    MCF5445_EXC_rsvd19,
    MCF5445_EXC_rsvd20,
    MCF5445_EXC_rsvd21,
    MCF5445_EXC_rsvd22,
    MCF5445_EXC_rsvd23,
    MCF5445_EXC_SPURIOUS,
    MCF5445_EXC_rsvd25,
    MCF5445_EXC_rsvd26,
    MCF5445_EXC_rsvd27,
    MCF5445_EXC_rsvd28,
    MCF5445_EXC_rsvd29,
    MCF5445_EXC_rsvd30,
    MCF5445_EXC_rsvd31,
    MCF5445_EXC_TRAP0,
    MCF5445_EXC_TRAP1,
    MCF5445_EXC_TRAP2,
    MCF5445_EXC_TRAP3,
    MCF5445_EXC_TRAP4,
    MCF5445_EXC_TRAP5,
    MCF5445_EXC_TRAP6,
    MCF5445_EXC_TRAP7,
    MCF5445_EXC_TRAP8,
    MCF5445_EXC_TRAP9,
    MCF5445_EXC_TRAP10,
    MCF5445_EXC_TRAP11,
    MCF5445_EXC_TRAP12,
    MCF5445_EXC_TRAP13,
    MCF5445_EXC_TRAP14,
    MCF5445_EXC_TRAP15,
    MCF5445_EXC_rsvd48,
    MCF5445_EXC_rsvd49,
    MCF5445_EXC_rsvd50,
    MCF5445_EXC_rsvd51,
    MCF5445_EXC_rsvd52,
    MCF5445_EXC_rsvd53,
    MCF5445_EXC_rsvd54,
    MCF5445_EXC_rsvd55,
    MCF5445_EXC_rsvd56,
    MCF5445_EXC_rsvd57,
    MCF5445_EXC_rsvd58,
    MCF5445_EXC_rsvd59,
    MCF5445_EXC_rsvd60,
    MCF5445_EXC_rsvd61,
    MCF5445_EXC_rsvd62,
    MCF5445_EXC_rsvd63,
    
    MCF5445_INT_FIRST_EXTERNAL,
    /* Interrupt Controller 0 */
    MCF5445_INT_EPORT0_EPF1,    //  1 Edge port flag 1
    MCF5445_INT_EPORT0_EPF2,    //  2 Edge port flag 2
    MCF5445_INT_EPORT0_EPF3,    //  3 Edge port flag 3
    MCF5445_INT_EPORT0_EPF4,    //  4 Edge port flag 4
    MCF5445_INT_EPORT0_EPF5,    //  5 Edge port flag 5
    MCF5445_INT_EPORT0_EPF6,    //  6 Edge port flag 6
    MCF5445_INT_EPORT0_EPF7,    //  7 Edge port flag 7
    
    MCF5445_INT_EDMA_INTR0,     //  8 DMA Channel 0 transfer complete
    MCF5445_INT_EDMA_INTR1,     //  9 DMA Channel 1 transfer complete
    MCF5445_INT_EDMA_INTR2,     // 10 DMA Channel 2 transfer complete
    MCF5445_INT_EDMA_INTR3,     // 11 DMA Channel 3 transfer complete
    MCF5445_INT_EDMA_INTR4,     // 12 DMA Channel 4 transfer complete
    MCF5445_INT_EDMA_INTR5,     // 13 DMA Channel 5 transfer complete
    MCF5445_INT_EDMA_INTR6,     // 14 DMA Channel 6 transfer complete
    MCF5445_INT_EDMA_INTR7,     // 15 DMA Channel 7 transfer complete
    MCF5445_INT_EDMA_INTR8,     // 16 DMA Channel 8 transfer complete
    MCF5445_INT_EDMA_INTR9,     // 17 DMA Channel 9 transfer complete
    MCF5445_INT_EDMA_INTR10,    // 18 DMA Channel 10 transfer complete
    MCF5445_INT_EDMA_INTR11,    // 19 DMA Channel 11 transfer complete
    MCF5445_INT_EDMA_INTR12,    // 20 DMA Channel 12 transfer complete
    MCF5445_INT_EDMA_INTR13,    // 21 DMA Channel 13 transfer complete
    MCF5445_INT_EDMA_INTR14,    // 22 DMA Channel 14 transfer complete
    MCF5445_INT_EDMA_INTR15,    // 23 DMA Channel 15 transfer complete
    MCF5445_INT_EDMA_ERR,       // 24 DMA Error Interrupt
   
    MCF5445_INT_SCM_CWIC,       // 25 Core Watchdog Timeout
  
    MCF5445_INT_UART0,          // 26 UART0 interrupt
    MCF5445_INT_UART1,          // 27 UART1 interrupt
    MCF5445_INT_UART2,          // 28 UART2 interrupt
  
    MCF5445_INT_rsvd29,         // 29 not used
  
    MCF5445_INT_I2C,            // 30 I2C interrupt
  
    MCF5445_INT_DSPI,           // 31 DSPI interrupt (Logical OR of INTC1’s source #33–39)
   
    MCF5445_INT_DTIM0,          // 32 TMR0 interrupt
    MCF5445_INT_DTIM1,          // 33 TMR1 interrupt
    MCF5445_INT_DTIM2,          // 34 TMR2 interrupt
    MCF5445_INT_DTIM3,          // 35 TMR3 interrupt

    MCF5445_INT_FEC0_X_INTF,    // 36 Transmit frame interrupt
    MCF5445_INT_FEC0_X_INTB,    // 37 Transmit buffer interrupt
    MCF5445_INT_FEC0_X_UN,      // 38 Transmit FIFO underrun
    MCF5445_INT_FEC0_RL,        // 39 Collision retry limit
    MCF5445_INT_FEC0_R_INTF,    // 40 Receive frame interrupt
    MCF5445_INT_FEC0_R_INTB,    // 41 Receive buffer interrupt
    MCF5445_INT_FEC0_MII,       // 42 MII interrupt
    MCF5445_INT_FEC0_LC,        // 43 Late collision
    MCF5445_INT_FEC0_HBERR,     // 44 Heartbeat error
    MCF5445_INT_FEC0_GRA,       // 45 Graceful stop complete
    MCF5445_INT_FEC0_EBERR,     // 46 Ethernet bus error
    MCF5445_INT_FEC0_BABT,      // 47 Babbling transmit error
    MCF5445_INT_FEC0_BABR,      // 48 Babbling receive error
    
    MCF5445_INT_FEC1_X_INTF,    // 49 Transmit frame interrupt
    MCF5445_INT_FEC1_X_INTB,    // 50 Transmit buffer interrupt
    MCF5445_INT_FEC1_X_UN,      // 51 Transmit FIFO underrun
    MCF5445_INT_FEC1_RL,        // 52 Collision retry limit
    MCF5445_INT_FEC1_R_INTF,    // 53 Receive frame interrupt
    MCF5445_INT_FEC1_R_INTB,    // 54 Receive buffer interrupt
    MCF5445_INT_FEC1_MII,       // 55 MII interrupt
    MCF5445_INT_FEC1_LC,        // 56 Late collision
    MCF5445_INT_FEC1_HBERR,     // 57 Heartbeat error
    MCF5445_INT_FEC1_GRA,       // 58 Graceful stop complete
    MCF5445_INT_FEC1_EBERR,     // 59 Ethernet bus error
    MCF5445_INT_FEC1_BABT,      // 60 Babbling transmit error
    MCF5445_INT_FEC1_BABR,      // 61 Babbling receive error
   
    MCF5445_INT_SCM_CFEI,       // 62 Core bus error interrupt

    MCF5445_INT_RTC,            // 63 Real Time Clock Interrupt

    /* Interrupt Controller 1 */
    MCF5445_INT1_rsvd0,         //  0 not used
    MCF5445_INT1_rsvd1,         //  1 not used
    MCF5445_INT1_rsvd2,         //  2 not used
    MCF5445_INT1_rsvd3,         //  3 not used
    MCF5445_INT1_rsvd4,         //  4 not used
    MCF5445_INT1_rsvd5,         //  5 not used
    MCF5445_INT1_rsvd6,         //  6 not used
    MCF5445_INT1_rsvd7,         //  7 not used
    MCF5445_INT1_rsvd8,         //  8 not used
    MCF5445_INT1_rsvd9,         //  9 not used
    MCF5445_INT1_rsvd10,        // 10 not used
    MCF5445_INT1_rsvd11,        // 11 not used
    MCF5445_INT1_rsvd12,        // 12 not used
    MCF5445_INT1_rsvd13,        // 13 not used
    MCF5445_INT1_rsvd14,        // 14 not used
    MCF5445_INT1_rsvd15,        // 15 not used
    MCF5445_INT1_rsvd16,        // 16 not used
    MCF5445_INT1_rsvd17,        // 17 not used
    MCF5445_INT1_rsvd18,        // 18 not used
    MCF5445_INT1_rsvd19,        // 19 not used
    MCF5445_INT1_rsvd20,        // 20 not used
    MCF5445_INT1_rsvd21,        // 21 not used
    MCF5445_INT1_rsvd22,        // 22 not used
    MCF5445_INT1_rsvd23,        // 23 not used
    MCF5445_INT1_rsvd24,        // 24 not used
    MCF5445_INT1_rsvd25,        // 25 not used
    MCF5445_INT1_rsvd26,        // 26 not used
    MCF5445_INT1_rsvd27,        // 27 not used
    MCF5445_INT1_rsvd28,        // 28 not used
    MCF5445_INT1_rsvd29,        // 29 not used
    MCF5445_INT1_rsvd30,        // 30 not used
    MCF5445_INT1_rsvd31,        // 31 not used
    MCF5445_INT1_rsvd32,        // 32 not used

    MCF5445_INT_DSPI_EOQF,     // 33 DSPI End of queue interrupt
    MCF5445_INT_DSPI_TFFF,     // 34 DSPI Transmit FIFO fill interrupt
    MCF5445_INT_DSPI_TCF,      // 35 DSPI Transfer complete interrupt
    MCF5445_INT_DSPI_TFUF,     // 36 DSPI Transmit FIFO underflow interrupt
    MCF5445_INT_DSPI_RFDF,     // 37 DSPI Receive FIFO not empty interrupt
    MCF5445_INT_DSPI_RFOF,     // 38 DSPI Receive FIFO overflow interrupt
    MCF5445_INT_DSPI_RFOF_TFUF,// 39 DSPI Receive FIFO overflow or transmit FIFO underflow interrupt
    MCF5445_INT_RNG,           // 40 RNG interrupt flag

    MCF5445_INT1_rsvd41,        // 41 not used
    MCF5445_INT1_rsvd42,        // 42 not used

    MCF5445_INT_PIT0,          // 43 PIT0 PIF PIT interrupt flag
    MCF5445_INT_PIT1,          // 44 PIT1 PIF PIT interrupt flag
    MCF5445_INT_PIT2,          // 45 PIT0 PIF PIT interrupt flag
    MCF5445_INT_PIT3,          // 46 PIT1 PIF PIT interrupt flag

    MCF5445_INT_USB,       // 47 USB OTG interrupt

    MCF5445_INT1_rsvd48,        // 48 not used

    MCF5445_INT_SSI,           // 49 SSI interrupt

    MCF5445_INT1_rsvd50,        // 50 not used
    MCF5445_INT1_rsvd51,        // 51 not used
    MCF5445_INT1_rsvd52,        // 52 not used

    MCF5445_INT_CCM,           // 53 USB status Interrupt
    MCF5445_INT_ATA,           // 54 ATA interrupt
    MCF5445_INT_PCI_PCIGSCR,   // 55 PCI interrupt
    MCF5445_INT_PCI_PASR,      // 56 PCI arbiter interrupt
    MCF5445_INT_PLL            // 57 USB status Interrupt
} MCF5445_INTERRUPT_TABLE_INDEX;//, PSP_INTERRUPT_TABLE_INDEX;

/*
** MCF5445_PLL_STRUCT
** ColdFire PLL
*/
typedef struct mcf5445_pll_struct {
    uint_32 PCR;            // PLL Control Register
    uint_32 PSR;            // PLL Status Register
} MCF5445_PLL_STRUCT, _PTR_ MCF5445_PLL_STRUCT_PTR;
typedef volatile struct mcf5445_pll_struct _PTR_ VMCF5445_PLL_STRUCT_PTR;

/*
** SCM Registers
*/
typedef struct mcf5445_scm_a_struct {
    uint_32 MPR;
    uint_32 PACRA;
    uint_32 PACRB;
    uint_32 PACRC;
    uint_32 PACRD;
    uint_32 PACRE;
    uint_32 PACRF;
    uint_32 PACRG;
} MCF5445_SCM_A_STRUCT, _PTR_ MCF5445_SCM_A_STRUCT_PTR;
typedef volatile struct mcf5445_scm_a_struct _PTR_ VMCF5445_SCM_A_STRUCT_PTR;

typedef struct mcf5445_scm_b_struct {
    uint_16 CWCR;  
    uint_8 CWSR;
    uint_8 SCMISR; 
    uint_32 BCR;   
    uint_32 CFADR;
    uint_8 CFIER;
    uint_8 CFLOC;  
    uint_8 CFATR; 
    uint_32 CFDTR;
} MCF5445_SCM_B_STRUCT, _PTR_ MCF5445_SCM_B_STRUCT_PTR;
typedef volatile struct mcf5445_scm_b_struct _PTR_ VMCF5445_SCM_B_STRUCT_PTR;

typedef struct mcf5445_scm_struct {
    uint_32 MPR;
    uint_32 PACRA;
    uint_32 PACRB;
    uint_32 PACRC;
    uint_32 PACRD;
    uint_32 PACRE;
    uint_32 PACRF;
    uint_32 PACRG;
    
    uint_8 filler0[0x40000 - 8 * 4];
    
    uint_16 CWCR;  
    uint_8 CWSR;
    uint_8 SCMISR; 
    uint_32 BCR;   
    uint_32 CFADR;
    uint_8 CFIER;
    uint_8 CFLOC;  
    uint_8 CFATR; 
    uint_32 CFDTR;
} MCF5445_SCM_STRUCT, _PTR_ MCF5445_SCM_STRUCT_PTR;
typedef volatile struct mcf5445_scm_struct _PTR_ VMCF5445_SCM_STRUCT_PTR;



/*
** MCF5445_GPIO_STRUCT
** GPIO Registers
*/
typedef struct mcf5445_gpio_struct {
    uint_8 PODR_FEC0H, PODR_FEC0L, PODR_SSI, PODR_FBCTL, PODR_BE;
    uint_8 PODR_CS, PODR_DMA, PODR_FECI2C;
    uint_8 filler0;
    uint_8 PODR_UART, PODR_DSPI, PODR_TIMER;
    uint_8 PODR_PCI, PODR_USB, PODR_ATAH, PODR_ATAL, PODR_FEC1H, PODR_FEC1L;
    uint_8 filler1, filler2;
    uint_8 PODR_FBADH, PODR_FBADMH, PODR_FBADML, PODR_FBADL;
    
    uint_8 PDDR_FEC0H, PDDR_FEC0L, PDDR_SSI, PDDR_FBCTL, PDDR_BE, PDDR_CS;
    uint_8 PDDR_DMA, PDDR_FECI2C;
    uint_8 filler3;
    uint_8 PDDR_UART, PDDR_DSPI, PDDR_TIMER, PDDR_PCI;
    uint_8 PDDR_USB, PDDR_ATAH, PDDR_ATAL, PDDR_FEC1H, PDDR_FEC1L;
    uint_8 filler4, filler5;     
    uint_8 PDDR_FBADH, PDDR_FBADMH, PDDR_FBADML, PDDR_FBADL;
    
    uint_8 PPDSDR_FEC0H, PPDSDR_FEC0L, PPDSDR_SSI, PPDSDR_FBCTL, PPDSDR_BE;
    uint_8 PPDSDR_CS, PPDSDR_DMA, PPDSDR_FECI2C;
    uint_8 filler6;
    uint_8 PPDSDR_UART, PPDSDR_DSPI, PPDSDR_TIMER;
    uint_8 PPDSDR_PCI, PPDSDR_USB, PPDSDR_ATAH, PPDSDR_ATAL, PPDSDR_FEC1H, PPDSDR_FEC1L;
    uint_8 filler7, filler8;     
    uint_8 PPDSDR_FBADH, PPDSDR_FBADMH, PPDSDR_FBADML, PPDSDR_FBADL;  
    
    uint_8 PCLRR_FEC0H, PCLRR_FEC0L, PCLRR_SSI, PCLRR_FBCTL, PCLRR_BE, PCLRR_CS;
    uint_8 PCLRR_DMA, PCLRR_FECI2C;
    uint_8 filler9;
    uint_8 PCLRR_UART, PCLRR_DSPI, PCLRR_TIMER, PCLRR_PCI;
    uint_8 PCLRR_USB, PCLRR_ATAH, PCLRR_ATAL, PCLRR_FEC1H;
    uint_8 filler10, PCLRR_FEC1L, filler11;     
    uint_8 PCLRR_FBADH, PCLRR_FBADMH, PCLRR_FBADML, PCLRR_FBADL;
    
    uint_8 PAR_FEC, PAR_DMA, PAR_FBCTL, PAR_DSPI, PAR_BE, PAR_CS, PAR_TIMER, PAR_USB;
    uint_8 filler12;
    uint_8 PAR_UART;
    uint_16 PAR_FECI2C, PAR_SSI, PAR_ATA;
    uint_8 PAR_IRQ;
    uint_8 filler13;
    uint_16 PAR_PCI;
    
    uint_8 MSCR_SDRAM, MSCR_PCI;

    uint_8 filler14, filler15;
    
    uint_8 DSCR_I2C, DSCR_FLEXBUS, DSCR_FEC, DSCR_UART, DSCR_DSPI, DSCR_TIMER, DSCR_SSI;
    uint_8 DSCR_DMA, DSCR_DEBUG, DSCR_RESET, DSCR_IRQ, DSCR_USB, DSCR_ATA;
}  MCF5445_GPIO_STRUCT, _PTR_ MCF5445_GPIO_STRUCT_PTR;
typedef volatile struct mcf5445_gpio_struct _PTR_ VMCF5445_GPIO_STRUCT_PTR;

/*
** MCF5445_EDMA_STRUCT
** This structure defines eDMA registers
*/
typedef struct mcf5445_edma_struct {
    uint_32 CR;
    uint_32 ES;  
    uint_8  filler1[6];
    uint_16 ERQ; 
    uint_8  filler2[6];
    uint_16 EEI; 
    uint_8  SERQ;
    uint_8  CERQ;
    uint_8  SEEI;
    uint_8  CEEI;
    uint_8  CINT;
    uint_8  CERR;
    uint_8  SSRT;
    uint_8  CDNE;
    uint_8  filler3[6];
    uint_16 INT; 
    uint_8  filler4[6];
    uint_16 ERR;
    uint_8  filler5[0xD0];
    uint_8  DCHPRI[MCF5445_NUM_DMA_CH];
    uint_8  filler6[0xEF0];
    struct {
        uint_32 SADDR;      
        uint_16 ATTR;       
        uint_16 SOFF;       
        uint_32 NBYTES;     
        uint_32 SLAST;      
        uint_32 DADDR;      
        uint_16 CITER;      
        uint_16 DOFF;       
        uint_32 DLAST_SGA;  
        uint_16 BITER;      
        uint_16 CSR;        
    } TCD[MCF5445_NUM_DMA_CH];

} MCF5445_EDMA_STRUCT, _PTR_ MCF5445_EDMA_STRUCT_PTR;
typedef volatile struct mcf5445_edma_struct _PTR_ VMCF5445_EDMA_STRUCT_PTR;


/*
** Cross-Bar Switch Module
*/
typedef struct mcf5445_xbs_struct {
    uint_32 PRS1;
    uint_32 CRS1;
    uint_32 PRS2;
    uint_32 CRS2;
    uint_32 PRS3;
    uint_32 CRS3;
    uint_32 PRS4;
    uint_32 CRS4;
    uint_32 PRS5;
    uint_32 CRS5;
    uint_32 PRS7;
    uint_32 CRS7;
} MCF5445_XBS_STRUCT, _PTR_ MCF5445_XBS_STRUCT_PTR;
typedef volatile struct mcf5445_xbs_struct _PTR_ VMCF5445_XBS_STRUCT_PTR;


/* Bit definitions and macros for MCF5445_DTIM_DTMR */
#define MCF5445_DTIM_DTMR_RST                    (0x1)
#define MCF5445_DTIM_DTMR_CLK(x)                 (((x)&0x3)<<0x1)
#define MCF5445_DTIM_DTMR_CLK_STOP               (0)
#define MCF5445_DTIM_DTMR_CLK_DIV1               (0x2)
#define MCF5445_DTIM_DTMR_CLK_DIV16              (0x4)
#define MCF5445_DTIM_DTMR_CLK_DTIN               (0x6)
#define MCF5445_DTIM_DTMR_FRR                    (0x8)
#define MCF5445_DTIM_DTMR_ORRI                   (0x10)
#define MCF5445_DTIM_DTMR_OM                     (0x20)
#define MCF5445_DTIM_DTMR_CE(x)                  (((x)&0x3)<<0x6)
#define MCF5445_DTIM_DTMR_CE_NONE                (0)
#define MCF5445_DTIM_DTMR_CE_RISE                (0x40)
#define MCF5445_DTIM_DTMR_CE_FALL                (0x80)
#define MCF5445_DTIM_DTMR_CE_ANY                 (0xC0)
#define MCF5445_DTIM_DTMR_PS(x)                  (((x)&0xFF)<<0x8)

/* Bit definitions and macros for MCF5445_DTIM_DTXMR */
#define MCF5445_DTIM_DTXMR_MODE16                (0x1)
#define MCF5445_DTIM_DTXMR_HALTED                (0x40)
#define MCF5445_DTIM_DTXMR_DMAEN                 (0x80)

/* Bit definitions and macros for MCF5445_DTIM_DTER */
#define MCF5445_DTIM_DTER_CAP                    (0x1)
#define MCF5445_DTIM_DTER_REF                    (0x2)

/* Bit definitions and macros for MCF5445_DTIM_DTRR */
#define MCF5445_DTIM_DTRR_REF(x)                 (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF5445_DTIM_DTCR */
#define MCF5445_DTIM_DTCR_CAP(x)                 (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF5445_DTIM_DTCN */
#define MCF5445_DTIM_DTCN_CNT(x)                 (((x)&0xFFFFFFFF)<<0)

/*
** MCF5445_DMA_TIMER_STRUCT
** This structure defines DMA timer registers
*/
typedef struct mcf5445_dma_timer_struct
{
   uint_16  DTMR;           // DMA Timer mode register
   uint_8   DTXTMR;         // DMA Timer extended mode register
   uint_8   DTER;           // DMA Timer event register
   uint_32  DTRR;           // DMA Timer reference register
   uint_32  DTCR;           // DMA Timer capture register
   uint_32  DTCN;           // DMA Timer counter register
   uint_8   filler1[0x3FF0];
} MCF5445_DMA_TIMER_STRUCT, _PTR_ MCF5445_DMA_TIMER_STRUCT_PTR;
typedef volatile struct mcf5445_dma_timer_struct _PTR_ VMCF5445_DMA_TIMER_STRUCT_PTR;


/* Bit definitions and macros for MCF5445_EPORT_EPPAR */
#define MCF5445_EPORT_EPPAR_EPPA1(x)             (((x)&0x3)<<0x2)
#define MCF5445_EPORT_EPPAR_EPPA1_LEVEL          (0)
#define MCF5445_EPORT_EPPAR_EPPA1_RISING         (0x4)
#define MCF5445_EPORT_EPPAR_EPPA1_FALLING        (0x8)
#define MCF5445_EPORT_EPPAR_EPPA1_BOTH           (0xC)
#define MCF5445_EPORT_EPPAR_EPPA2(x)             (((x)&0x3)<<0x4)
#define MCF5445_EPORT_EPPAR_EPPA2_LEVEL          (0)
#define MCF5445_EPORT_EPPAR_EPPA2_RISING         (0x10)
#define MCF5445_EPORT_EPPAR_EPPA2_FALLING        (0x20)
#define MCF5445_EPORT_EPPAR_EPPA2_BOTH           (0x30)
#define MCF5445_EPORT_EPPAR_EPPA3(x)             (((x)&0x3)<<0x6)
#define MCF5445_EPORT_EPPAR_EPPA3_LEVEL          (0)
#define MCF5445_EPORT_EPPAR_EPPA3_RISING         (0x40)
#define MCF5445_EPORT_EPPAR_EPPA3_FALLING        (0x80)
#define MCF5445_EPORT_EPPAR_EPPA3_BOTH           (0xC0)
#define MCF5445_EPORT_EPPAR_EPPA4(x)             (((x)&0x3)<<0x8)
#define MCF5445_EPORT_EPPAR_EPPA4_LEVEL          (0)
#define MCF5445_EPORT_EPPAR_EPPA4_RISING         (0x100)
#define MCF5445_EPORT_EPPAR_EPPA4_FALLING        (0x200)
#define MCF5445_EPORT_EPPAR_EPPA4_BOTH           (0x300)
#define MCF5445_EPORT_EPPAR_EPPA5(x)             (((x)&0x3)<<0xA)
#define MCF5445_EPORT_EPPAR_EPPA5_LEVEL          (0)
#define MCF5445_EPORT_EPPAR_EPPA5_RISING         (0x400)
#define MCF5445_EPORT_EPPAR_EPPA5_FALLING        (0x800)
#define MCF5445_EPORT_EPPAR_EPPA5_BOTH           (0xC00)
#define MCF5445_EPORT_EPPAR_EPPA6(x)             (((x)&0x3)<<0xC)
#define MCF5445_EPORT_EPPAR_EPPA6_LEVEL          (0)
#define MCF5445_EPORT_EPPAR_EPPA6_RISING         (0x1000)
#define MCF5445_EPORT_EPPAR_EPPA6_FALLING        (0x2000)
#define MCF5445_EPORT_EPPAR_EPPA6_BOTH           (0x3000)
#define MCF5445_EPORT_EPPAR_EPPA7(x)             (((x)&0x3)<<0xE)
#define MCF5445_EPORT_EPPAR_EPPA7_LEVEL          (0)
#define MCF5445_EPORT_EPPAR_EPPA7_RISING         (0x4000)
#define MCF5445_EPORT_EPPAR_EPPA7_FALLING        (0x8000)
#define MCF5445_EPORT_EPPAR_EPPA7_BOTH           (0xC000)
#define MCF5445_EPORT_EPPAR_LEVEL                (0)
#define MCF5445_EPORT_EPPAR_RISING               (0x1)
#define MCF5445_EPORT_EPPAR_FALLING              (0x2)
#define MCF5445_EPORT_EPPAR_BOTH                 (0x3)

/* Bit definitions and macros for MCF5445_EPORT_EPDDR */
#define MCF5445_EPORT_EPDDR_EPDD1                (0x2)
#define MCF5445_EPORT_EPDDR_EPDD2                (0x4)
#define MCF5445_EPORT_EPDDR_EPDD3                (0x8)
#define MCF5445_EPORT_EPDDR_EPDD4                (0x10)
#define MCF5445_EPORT_EPDDR_EPDD5                (0x20)
#define MCF5445_EPORT_EPDDR_EPDD6                (0x40)
#define MCF5445_EPORT_EPDDR_EPDD7                (0x80)

/* Bit definitions and macros for MCF5445_EPORT_EPIER */
#define MCF5445_EPORT_EPIER_EPIE1                (0x2)
#define MCF5445_EPORT_EPIER_EPIE2                (0x4)
#define MCF5445_EPORT_EPIER_EPIE3                (0x8)
#define MCF5445_EPORT_EPIER_EPIE4                (0x10)
#define MCF5445_EPORT_EPIER_EPIE5                (0x20)
#define MCF5445_EPORT_EPIER_EPIE6                (0x40)
#define MCF5445_EPORT_EPIER_EPIE7                (0x80)

/* Bit definitions and macros for MCF5445_EPORT_EPDR */
#define MCF5445_EPORT_EPDR_EPD1                  (0x2)
#define MCF5445_EPORT_EPDR_EPD2                  (0x4)
#define MCF5445_EPORT_EPDR_EPD3                  (0x8)
#define MCF5445_EPORT_EPDR_EPD4                  (0x10)
#define MCF5445_EPORT_EPDR_EPD5                  (0x20)
#define MCF5445_EPORT_EPDR_EPD6                  (0x40)
#define MCF5445_EPORT_EPDR_EPD7                  (0x80)

/* Bit definitions and macros for MCF5445_EPORT_EPPDR */
#define MCF5445_EPORT_EPPDR_EPPD1                (0x2)
#define MCF5445_EPORT_EPPDR_EPPD2                (0x4)
#define MCF5445_EPORT_EPPDR_EPPD3                (0x8)
#define MCF5445_EPORT_EPPDR_EPPD4                (0x10)
#define MCF5445_EPORT_EPPDR_EPPD5                (0x20)
#define MCF5445_EPORT_EPPDR_EPPD6                (0x40)
#define MCF5445_EPORT_EPPDR_EPPD7                (0x80)

/* Bit definitions and macros for MCF5445_EPORT_EPFR */
#define MCF5445_EPORT_EPFR_EPF1                  (0x2)
#define MCF5445_EPORT_EPFR_EPF2                  (0x4)
#define MCF5445_EPORT_EPFR_EPF3                  (0x8)
#define MCF5445_EPORT_EPFR_EPF4                  (0x10)
#define MCF5445_EPORT_EPFR_EPF5                  (0x20)
#define MCF5445_EPORT_EPFR_EPF6                  (0x40)
#define MCF5445_EPORT_EPFR_EPF7                  (0x80)

/*
** MCF5445_EPORT_STRUCT                                                                  
** Edge Port
*/
typedef struct mcf5445_eport_struct
{
   uint_16  EPORT_EPPAR; // Pin Assignment Register
   uint_8   EPORT_EPDDR; // Data Direction Register
   uint_8   EPORT_EPIER; // Interrupt Enable Register
   uint_8   EPORT_EPDR;  // Data Register
   uint_8   EPORT_EPPDR; // Pin Data Register
   uint_8   EPORT_EPFR;  // Flag Register
} MCF5445_EPORT_STRUCT, _PTR_ MCF5445_EPORT_STRUCT_PTR;
typedef volatile struct mcf5445_eport_struct _PTR_ VMCF5445_EPORT_STRUCT_PTR;


/* Bit definitions and macros for MCF5445_PCI_PCIIDR */
#define MCF5445_PCI_PCIIDR_VENDORID(x)           (((x)&0xFFFF)<<0)
#define MCF5445_PCI_PCIIDR_DEVICEID(x)           (((x)&0xFFFF)<<0x10)

/* Bit definitions and macros for MCF5445_PCI_PCISCR */
#define MCF5445_PCI_PCISCR_IO                    (0x1)
#define MCF5445_PCI_PCISCR_M                     (0x2)
#define MCF5445_PCI_PCISCR_B                     (0x4)
#define MCF5445_PCI_PCISCR_SP                    (0x8)
#define MCF5445_PCI_PCISCR_MW                    (0x10)
#define MCF5445_PCI_PCISCR_V                     (0x20)
#define MCF5445_PCI_PCISCR_PER                   (0x40)
#define MCF5445_PCI_PCISCR_ST                    (0x80)
#define MCF5445_PCI_PCISCR_S                     (0x100)
#define MCF5445_PCI_PCISCR_F                     (0x200)
#define MCF5445_PCI_PCISCR_C                     (0x100000)
#define MCF5445_PCI_PCISCR_66M                   (0x200000)
#define MCF5445_PCI_PCISCR_R                     (0x400000)
#define MCF5445_PCI_PCISCR_FC                    (0x800000)
#define MCF5445_PCI_PCISCR_DP                    (0x1000000)
#define MCF5445_PCI_PCISCR_DT(x)                 (((x)&0x3)<<0x19)
#define MCF5445_PCI_PCISCR_TS                    (0x8000000)
#define MCF5445_PCI_PCISCR_TR                    (0x10000000)
#define MCF5445_PCI_PCISCR_MA                    (0x20000000)
#define MCF5445_PCI_PCISCR_SE                    (0x40000000)
#define MCF5445_PCI_PCISCR_PE                    (0x80000000)

/* Bit definitions and macros for MCF5445_PCI_PCICCRIR */
#define MCF5445_PCI_PCICCRIR_REVISIONID(x)       (((x)&0xFF)<<0)
#define MCF5445_PCI_PCICCRIR_CLASSCODE(x)        (((x)&0xFFFFFF)<<0x8)

/* Bit definitions and macros for MCF5445_PCI_PCICR1 */
#define MCF5445_PCI_PCICR1_CLS(x)                (((x)&0xFF)<<0)
#define MCF5445_PCI_PCICR1_LTMR(x)               (((x)&0xFF)<<0x8)
#define MCF5445_PCI_PCICR1_HEADERTYPE(x)         (((x)&0xFF)<<0x10)
#define MCF5445_PCI_PCICR1_BIST(x)               (((x)&0xFF)<<0x18)

/* Bit definitions and macros for MCF5445_PCI_PCIBAR0 */
#define MCF5445_PCI_PCIBAR0_IOM                  (0x1)
#define MCF5445_PCI_PCIBAR0_RANGE(x)             (((x)&0x3)<<0x1)
#define MCF5445_PCI_PCIBAR0_PREF                 (0x8)
#define MCF5445_PCI_PCIBAR0_BAR0(x)              (((x)&0x3FFF)<<0x12)

/* Bit definitions and macros for MCF5445_PCI_PCIBAR1 */
#define MCF5445_PCI_PCIBAR1_IOM                  (0x1)
#define MCF5445_PCI_PCIBAR1_RANGE(x)             (((x)&0x3)<<0x1)
#define MCF5445_PCI_PCIBAR1_PREF                 (0x8)
#define MCF5445_PCI_PCIBAR1_BAR1(x)              (((x)&0xFFF)<<0x14)

/* Bit definitions and macros for MCF5445_PCI_PCIBAR2 */
#define MCF5445_PCI_PCIBAR2_IOM                  (0x1)
#define MCF5445_PCI_PCIBAR2_RANGE(x)             (((x)&0x3)<<0x1)
#define MCF5445_PCI_PCIBAR2_PREF                 (0x8)
#define MCF5445_PCI_PCIBAR2_BAR2(x)              (((x)&0x3FF)<<0x16)

/* Bit definitions and macros for MCF5445_PCI_PCIBAR3 */
#define MCF5445_PCI_PCIBAR3_IOM                  (0x1)
#define MCF5445_PCI_PCIBAR3_RANGE(x)             (((x)&0x3)<<0x1)
#define MCF5445_PCI_PCIBAR3_PREF                 (0x8)
#define MCF5445_PCI_PCIBAR3_BAR3(x)              (((x)&0xFF)<<0x18)

/* Bit definitions and macros for MCF5445_PCI_PCIBAR4 */
#define MCF5445_PCI_PCIBAR4_IOM                  (0x1)
#define MCF5445_PCI_PCIBAR4_RANGE(x)             (((x)&0x3)<<0x1)
#define MCF5445_PCI_PCIBAR4_PREF                 (0x8)
#define MCF5445_PCI_PCIBAR4_BAR4(x)              (((x)&0x1F)<<0x1B)

/* Bit definitions and macros for MCF5445_PCI_PCIBAR5 */
#define MCF5445_PCI_PCIBAR5_IOM                  (0x1)
#define MCF5445_PCI_PCIBAR5_RANGE(x)             (((x)&0x3)<<0x1)
#define MCF5445_PCI_PCIBAR5_PREF                 (0x8)
#define MCF5445_PCI_PCIBAR5_BAR5(x)              (((x)&0x7)<<0x1D)

/* Bit definitions and macros for MCF5445_PCI_PCICCPR */
#define MCF5445_PCI_PCICCPR_PCICCP(x)            (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF5445_PCI_PCISID */
#define MCF5445_PCI_PCISID_VENDOR_ID(x)          (((x)&0xFFFF)<<0)
#define MCF5445_PCI_PCISID_SUBSYSTEM_ID(x)       (((x)&0xFFFF)<<0x10)

/* Bit definitions and macros for MCF5445_PCI_PCICR2 */
#define MCF5445_PCI_PCICR2_INTLINE(x)            (((x)&0xFF)<<0)
#define MCF5445_PCI_PCICR2_INTPIN(x)             (((x)&0xFF)<<0x8)
#define MCF5445_PCI_PCICR2_MINGNT(x)             (((x)&0xFF)<<0x10)
#define MCF5445_PCI_PCICR2_MAXLAT(x)             (((x)&0xFF)<<0x18)

/* Bit definitions and macros for MCF5445_PCI_PCIGSCR */
#define MCF5445_PCI_PCIGSCR_PR                   (0x1)
#define MCF5445_PCI_PCIGSCR_ERE                  (0x800)
#define MCF5445_PCI_PCIGSCR_SEE                  (0x1000)
#define MCF5445_PCI_PCIGSCR_PEE                  (0x2000)
#define MCF5445_PCI_PCIGSCR_DRDE                 (0x8000)
#define MCF5445_PCI_PCIGSCR_PRGDIV(x)            (((x)&0x7)<<0x10)
#define MCF5445_PCI_PCIGSCR_AUTODIV(x)           (((x)&0x7)<<0x18)
#define MCF5445_PCI_PCIGSCR_ER                   (0x8000000)
#define MCF5445_PCI_PCIGSCR_SE                   (0x10000000)
#define MCF5445_PCI_PCIGSCR_PE                   (0x20000000)
#define MCF5445_PCI_PCIGSCR_DRD                  (0x80000000)

/* Bit definitions and macros for MCF5445_PCI_PCITCR1 */
#define MCF5445_PCI_PCITCR1_WCT(x)               (((x)&0xFF)<<0)
#define MCF5445_PCI_PCITCR1_WCD                  (0x100)
#define MCF5445_PCI_PCITCR1_P                    (0x10000)
#define MCF5445_PCI_PCITCR1_PID                  (0x20000)
#define MCF5445_PCI_PCITCR1_LD                   (0x1000000)

/* Bit definitions and macros for MCF5445_PCI_PCIIW0BTAR */
#define MCF5445_PCI_PCIIW0BTAR_WTA0(x)           (((x)&0xFF)<<0x8)
#define MCF5445_PCI_PCIIW0BTAR_WAM0(x)           (((x)&0xFF)<<0x10)
#define MCF5445_PCI_PCIIW0BTAR_WBA0(x)           (((x)&0xFF)<<0x18)

/* Bit definitions and macros for MCF5445_PCI_PCIIW1BTAR */
#define MCF5445_PCI_PCIIW1BTAR_WTA1(x)           (((x)&0xFF)<<0x8)
#define MCF5445_PCI_PCIIW1BTAR_WAM1(x)           (((x)&0xFF)<<0x10)
#define MCF5445_PCI_PCIIW1BTAR_WBA1(x)           (((x)&0xFF)<<0x18)

/* Bit definitions and macros for MCF5445_PCI_PCIIW2BTAR */
#define MCF5445_PCI_PCIIW2BTAR_WTA2(x)           (((x)&0xFF)<<0x8)
#define MCF5445_PCI_PCIIW2BTAR_WAM2(x)           (((x)&0xFF)<<0x10)
#define MCF5445_PCI_PCIIW2BTAR_WBA2(x)           (((x)&0xFF)<<0x18)

/* Bit definitions and macros for MCF5445_PCI_PCIIWCR */
#define MCF5445_PCI_PCIIWCR_W2C_E                (0x100)
#define MCF5445_PCI_PCIIWCR_W2C_PRC(x)           (((x)&0x3)<<0x9)
#define MCF5445_PCI_PCIIWCR_W2C_IOM              (0x800)
#define MCF5445_PCI_PCIIWCR_W1C_E                (0x10000)
#define MCF5445_PCI_PCIIWCR_W1C_PRC(x)           (((x)&0x3)<<0x11)
#define MCF5445_PCI_PCIIWCR_W1C_IOM              (0x80000)
#define MCF5445_PCI_PCIIWCR_W0C_E                (0x1000000)
#define MCF5445_PCI_PCIIWCR_W0C_PRC(x)           (((x)&0x3)<<0x19)
#define MCF5445_PCI_PCIIWCR_W0C_IOM              (0x8000000)
#define MCF5445_PCI_PCIIWCR_W2C_MEMREAD          (0x100)
#define MCF5445_PCI_PCIIWCR_W2C_MEMRDLINE        (0x300)
#define MCF5445_PCI_PCIIWCR_W2C_MEMRDMUL         (0x500)
#define MCF5445_PCI_PCIIWCR_W2C_IO               (0x900)
#define MCF5445_PCI_PCIIWCR_W1C_MEMREAD          (0x10000)
#define MCF5445_PCI_PCIIWCR_W1C_MEMRDLINE        (0x30000)
#define MCF5445_PCI_PCIIWCR_W1C_MEMRDMUL         (0x50000)
#define MCF5445_PCI_PCIIWCR_W1C_IO               (0x90000)
#define MCF5445_PCI_PCIIWCR_W0C_MEMREAD          (0x1000000)
#define MCF5445_PCI_PCIIWCR_W0C_MEMRDLINE        (0x3000000)
#define MCF5445_PCI_PCIIWCR_W0C_MEMRDMUL         (0x5000000)
#define MCF5445_PCI_PCIIWCR_W0C_IO               (0x9000000)

/* Bit definitions and macros for MCF5445_PCI_PCIICR */
#define MCF5445_PCI_PCIICR_MAXRETRY(x)           (((x)&0xFF)<<0)
#define MCF5445_PCI_PCIICR_TAE                   (0x1000000)
#define MCF5445_PCI_PCIICR_IAE                   (0x2000000)
#define MCF5445_PCI_PCIICR_REE                   (0x4000000)

/* Bit definitions and macros for MCF5445_PCI_PCIISR */
#define MCF5445_PCI_PCIISR_TA                    (0x1000000)
#define MCF5445_PCI_PCIISR_IA                    (0x2000000)
#define MCF5445_PCI_PCIISR_RE                    (0x4000000)

/* Bit definitions and macros for MCF5445_PCI_PCITCR2 */
#define MCF5445_PCI_PCITCR2_CR                   (0x1)
#define MCF5445_PCI_PCITCR2_B0E                  (0x100)
#define MCF5445_PCI_PCITCR2_B1E                  (0x200)
#define MCF5445_PCI_PCITCR2_B2E                  (0x400)
#define MCF5445_PCI_PCITCR2_B3E                  (0x800)
#define MCF5445_PCI_PCITCR2_B4E                  (0x1000)
#define MCF5445_PCI_PCITCR2_B5E                  (0x2000)

/* Bit definitions and macros for MCF5445_PCI_PCITBATR0 */
#define MCF5445_PCI_PCITBATR0_EN                 (0x1)
#define MCF5445_PCI_PCITBATR0_BAT0(x)            (((x)&0x3FFF)<<0x12)

/* Bit definitions and macros for MCF5445_PCI_PCITBATR1 */
#define MCF5445_PCI_PCITBATR1_EN                 (0x1)
#define MCF5445_PCI_PCITBATR1_BAT1(x)            (((x)&0xFFF)<<0x14)

/* Bit definitions and macros for MCF5445_PCI_PCITBATR2 */
#define MCF5445_PCI_PCITBATR2_EN                 (0x1)
#define MCF5445_PCI_PCITBATR2_BAT2(x)            (((x)&0x3FF)<<0x16)

/* Bit definitions and macros for MCF5445_PCI_PCITBATR3 */
#define MCF5445_PCI_PCITBATR3_EN                 (0x1)
#define MCF5445_PCI_PCITBATR3_BAT3(x)            (((x)&0xFF)<<0x18)

/* Bit definitions and macros for MCF5445_PCI_PCITBATR4 */
#define MCF5445_PCI_PCITBATR4_EN                 (0x1)
#define MCF5445_PCI_PCITBATR4_BAT4(x)            (((x)&0x1F)<<0x1B)

/* Bit definitions and macros for MCF5445_PCI_PCITBATR5 */
#define MCF5445_PCI_PCITBATR5_EN                 (0x1)
#define MCF5445_PCI_PCITBATR5_BAT5(x)            (((x)&0x7)<<0x1D)

/* Bit definitions and macros for MCF5445_PCI_PCIINTR */
#define MCF5445_PCI_PCIINTR_INT                  (0x1)

/* Bit definitions and macros for MCF5445_PCI_PCICAR */
#define MCF5445_PCI_PCICAR_DWORD(x)              (((x)&0x3F)<<0x2)
#define MCF5445_PCI_PCICAR_FUNCNUM(x)            (((x)&0x7)<<0x8)
#define MCF5445_PCI_PCICAR_DEVNUM(x)             (((x)&0x1F)<<0xB)
#define MCF5445_PCI_PCICAR_BUSNUM(x)             (((x)&0xFF)<<0x10)
#define MCF5445_PCI_PCICAR_E                     (0x80000000)

/* Bit definitions and macros for MCF5445_PCI_PACR */
#define MCF5445_PCI_PACR_INTMPRI                 (0x1)
#define MCF5445_PCI_PACR_EXTMPRI(x)              (((x)&0xF)<<0x1)
#define MCF5445_PCI_PACR_RA                      (0x8000)
#define MCF5445_PCI_PACR_INTMINTEN               (0x10000)
#define MCF5445_PCI_PACR_EXTMINTEN(x)            (((x)&0xF)<<0x11)
#define MCF5445_PCI_PACR_PKMD                    (0x40000000)
#define MCF5445_PCI_PACR_DS                      (0x80000000)

/* Bit definitions and macros for MCF5445_PCI_PASR */
#define MCF5445_PCI_PASR_ITLMBK                  (0x10000)
#define MCF5445_PCI_PASR_EXTMBK(x)               (((x)&0xF)<<0x11)


/*
** MCF5445_PCI_CTRL_STRUCT                                                                  
** PCI Controller
*/
typedef struct mcf5445_pci_ctrl_struct
{
   uint_32  PCIIDR;      // PCI Device ID/Vendor ID
   uint_32  PCISCR;      // PCI Status/Command
   uint_32  PCICCRIR;    // PCI Class Code/Revision ID
   uint_32  PCICR1;      // PCI Configuration 1 Register
   uint_32  PCIBAR0;     // PCI Base Address Register 0
   uint_32  PCIBAR1;     // PCI Base Address Register 1
   uint_32  PCIBAR2;     // PCI Base Address Register 2
   uint_32  PCIBAR3;     // PCI Base Address Register 3
   uint_32  PCIBAR4;     // PCI Base Address Register 4
   uint_32  PCIBAR5;     // PCI Base Address Register 5
   uint_32  PCICCPR;     // PCI Cardbus CIS Pointer
   uint_32  PCISID;      // PCI Subsystem ID/Subsystem Vendor ID
   uint_32  PCIERBAR;    // PCI Expansion ROM Base Address Registers
   uint_32  PCICPR;      // PCI Capabilities Pointer Register
   uint_32  filler0;
   uint_32  PCICR2;      // PCI Configuration Register 2
   uint_32  filler1[8];
   uint_32  PCIGSCR;     // PCI Global Status/Control Register
   uint_32  filler2[2];
   uint_32  PCITCR1;     // PCI Target Control 1 Register
   uint_32  PCIIW0BTAR;  // PCI Initiator Window 0 Base/Translation Address Register
   uint_32  PCIIW1BTAR;  // PCI Initiator Window 1 Base/Translation Address Register
   uint_32  PCIIW2BTAR;  // PCI Initiator Window 2 Base/Translation Address Register
   uint_32  filler3;
   uint_32  PCIIWCR;     // PCI Initiator Window Configuration Register
   uint_32  PCIICR;      // PCI Initiator Control Register
   uint_32  PCIISR;      // PCI Initiator Status Register
   uint_32  PCITCR2;     // PCI Target Control 2 Register
   uint_32  PCITBATR0;   // PCI Target Base Address Translation Register 0
   uint_32  PCITBATR1;   // PCI Target Base Address Translation Register 1
   uint_32  PCITBATR2;   // PCI Target Base Address Translation Register 2
   uint_32  PCITBATR3;   // PCI Target Base Address Translation Register 3
   uint_32  PCITBATR4;   // PCI Target Base Address Translation Register 4
   uint_32  PCITBATR5;   // PCI Target Base Address Translation Register 5
   uint_32  PCIINTR;     // PCI Interrupt Register
   uint_32  filler4[19];
   uint_32  PCICAR;      // PCI Configuration Address Register
} MCF5445_PCI_CTRL_STRUCT, _PTR_ MCF5445_PCI_CTRL_STRUCT_PTR;
typedef volatile struct mcf5445_pci_ctrl_struct _PTR_ VMCF5445_PCI_CTRL_STRUCT_PTR;

/*
** MCF5445_PCI_ARB_STRUCT                                                                  
** PCI Arbiter
*/
typedef struct mcf5445_pci_arb_struct
{
   uint_32  PACR;        // PCI Arbiter Control Register
   uint_32  PASR;        // PCI Arbiter Status Register
} MCF5445_PCI_ARB_STRUCT, _PTR_ MCF5445_PCI_ARB_STRUCT_PTR;
typedef volatile struct mcf5445_pci_arb_struct _PTR_ VMCF5445_PCI_ARB_STRUCT_PTR;


/* Bit definitions and macros for MCF5445_RNG_RNGCR */
#define MCF5445_RNG_RNGCR_GO                     (0x1)
#define MCF5445_RNG_RNGCR_HA                     (0x2)
#define MCF5445_RNG_RNGCR_IM                     (0x4)
#define MCF5445_RNG_RNGCR_CI                     (0x8)

/* Bit definitions and macros for MCF5445_RNG_RNGSR */
#define MCF5445_RNG_RNGSR_SV                     (0x1)
#define MCF5445_RNG_RNGSR_LRS                    (0x2)
#define MCF5445_RNG_RNGSR_FUF                    (0x4)
#define MCF5445_RNG_RNGSR_EI                     (0x8)
#define MCF5445_RNG_RNGSR_OFL(x)                 (((x)&0xFF)<<0x8)
#define MCF5445_RNG_RNGSR_OFS(x)                 (((x)&0xFF)<<0x10)

/* Bit definitions and macros for MCF5445_RNG_RNGER */
#define MCF5445_RNG_RNGER_ENT(x)                 (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF5445_RNG_RNGOUT */
#define MCF5445_RNG_RNGOUT_RANDOM_OUTPUT(x)      (((x)&0xFFFFFFFF)<<0)


/*
** MCF5445_RNG_STRUCT                                                                   
** Random Number Generator (RNG)
*/
typedef struct mcf5445_rng_struct
{
   uint_32  RNGCR;  // RNG Control Register
   uint_32  RNGSR;  // RNG Status Register
   uint_32  RNGER;  // RNG Entropy Register
   uint_32  RNGOUT; // RNG Output FIFO
} MCF5445_RNG_STRUCT, _PTR_ MCF5445_RNG_STRUCT_PTR;
typedef volatile struct mcf5445_rng_struct _PTR_ VMCF5445_RNG_STRUCT_PTR;


/* Bit definitions and macros for MCF5445_SSI_SSI_TX */
#define MCF5445_SSI_SSI_TX_SSI_TX(x)             (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF5445_SSI_SSI_RX */
#define MCF5445_SSI_SSI_RX_SSI_RX(x)             (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF5445_SSI_SSI_CR */
#define MCF5445_SSI_SSI_CR_SSI_EN                (0x1)
#define MCF5445_SSI_SSI_CR_TE                    (0x2)
#define MCF5445_SSI_SSI_CR_RE                    (0x4)
#define MCF5445_SSI_SSI_CR_NET                   (0x8)
#define MCF5445_SSI_SSI_CR_SYN                   (0x10)
#define MCF5445_SSI_SSI_CR_I2S(x)                (((x)&0x3)<<0x5)
#define MCF5445_SSI_SSI_CR_I2S_NORMAL            (0)
#define MCF5445_SSI_SSI_CR_I2S_MASTER            (0x20)
#define MCF5445_SSI_SSI_CR_I2S_SLAVE             (0x40)
#define MCF5445_SSI_SSI_CR_MCE                   (0x80)
#define MCF5445_SSI_SSI_CR_TCH                   (0x100)
#define MCF5445_SSI_SSI_CR_CIS                   (0x200)

/* Bit definitions and macros for MCF5445_SSI_SSI_ISR */
#define MCF5445_SSI_SSI_ISR_TFE0                 (0x1)
#define MCF5445_SSI_SSI_ISR_TFE1                 (0x2)
#define MCF5445_SSI_SSI_ISR_RFF0                 (0x4)
#define MCF5445_SSI_SSI_ISR_RFF1                 (0x8)
#define MCF5445_SSI_SSI_ISR_RLS                  (0x10)
#define MCF5445_SSI_SSI_ISR_TLS                  (0x20)
#define MCF5445_SSI_SSI_ISR_RFS                  (0x40)
#define MCF5445_SSI_SSI_ISR_TFS                  (0x80)
#define MCF5445_SSI_SSI_ISR_TUE0                 (0x100)
#define MCF5445_SSI_SSI_ISR_TUE1                 (0x200)
#define MCF5445_SSI_SSI_ISR_ROE0                 (0x400)
#define MCF5445_SSI_SSI_ISR_ROE1                 (0x800)
#define MCF5445_SSI_SSI_ISR_TDE0                 (0x1000)
#define MCF5445_SSI_SSI_ISR_TDE1                 (0x2000)
#define MCF5445_SSI_SSI_ISR_RDR0                 (0x4000)
#define MCF5445_SSI_SSI_ISR_RDR1                 (0x8000)
#define MCF5445_SSI_SSI_ISR_RXT                  (0x10000)
#define MCF5445_SSI_SSI_ISR_CMDDU                (0x20000)
#define MCF5445_SSI_SSI_ISR_CMDAU                (0x40000)

/* Bit definitions and macros for MCF5445_SSI_SSI_IER */
#define MCF5445_SSI_SSI_IER_TFE0                 (0x1)
#define MCF5445_SSI_SSI_IER_TFE1                 (0x2)
#define MCF5445_SSI_SSI_IER_RFF0                 (0x4)
#define MCF5445_SSI_SSI_IER_RFF1                 (0x8)
#define MCF5445_SSI_SSI_IER_RLS                  (0x10)
#define MCF5445_SSI_SSI_IER_TLS                  (0x20)
#define MCF5445_SSI_SSI_IER_RFS                  (0x40)
#define MCF5445_SSI_SSI_IER_TFS                  (0x80)
#define MCF5445_SSI_SSI_IER_TUE0                 (0x100)
#define MCF5445_SSI_SSI_IER_TUE1                 (0x200)
#define MCF5445_SSI_SSI_IER_ROE0                 (0x400)
#define MCF5445_SSI_SSI_IER_ROE1                 (0x800)
#define MCF5445_SSI_SSI_IER_TDE0                 (0x1000)
#define MCF5445_SSI_SSI_IER_TDE1                 (0x2000)
#define MCF5445_SSI_SSI_IER_RDR0                 (0x4000)
#define MCF5445_SSI_SSI_IER_RDR1                 (0x8000)
#define MCF5445_SSI_SSI_IER_RXT                  (0x10000)
#define MCF5445_SSI_SSI_IER_CMDDU                (0x20000)
#define MCF5445_SSI_SSI_IER_CMDAU                (0x40000)
#define MCF5445_SSI_SSI_IER_TIE                  (0x80000)
#define MCF5445_SSI_SSI_IER_TDMAE                (0x100000)
#define MCF5445_SSI_SSI_IER_RIE                  (0x200000)
#define MCF5445_SSI_SSI_IER_RDMAE                (0x400000)

/* Bit definitions and macros for MCF5445_SSI_SSI_TCR */
#define MCF5445_SSI_SSI_TCR_TEFS                 (0x1)
#define MCF5445_SSI_SSI_TCR_TFSL                 (0x2)
#define MCF5445_SSI_SSI_TCR_TFSI                 (0x4)
#define MCF5445_SSI_SSI_TCR_TSCKP                (0x8)
#define MCF5445_SSI_SSI_TCR_TSHFD                (0x10)
#define MCF5445_SSI_SSI_TCR_TXDIR                (0x20)
#define MCF5445_SSI_SSI_TCR_TFDIR                (0x40)
#define MCF5445_SSI_SSI_TCR_TFEN0                (0x80)
#define MCF5445_SSI_SSI_TCR_TFEN1                (0x100)
#define MCF5445_SSI_SSI_TCR_TXBIT0               (0x200)

/* Bit definitions and macros for MCF5445_SSI_SSI_RCR */
#define MCF5445_SSI_SSI_RCR_REFS                 (0x1)
#define MCF5445_SSI_SSI_RCR_RFSL                 (0x2)
#define MCF5445_SSI_SSI_RCR_RFSI                 (0x4)
#define MCF5445_SSI_SSI_RCR_RSCKP                (0x8)
#define MCF5445_SSI_SSI_RCR_RSHFD                (0x10)
#define MCF5445_SSI_SSI_RCR_RXDIR                (0x20)
#define MCF5445_SSI_SSI_RCR_RFEN0                (0x80)
#define MCF5445_SSI_SSI_RCR_RFEN1                (0x100)
#define MCF5445_SSI_SSI_RCR_RXBIT0               (0x200)
#define MCF5445_SSI_SSI_RCR_RXEXT                (0x400)

/* Bit definitions and macros for MCF5445_SSI_SSI_CCR */
#define MCF5445_SSI_SSI_CCR_PM(x)                (((x)&0xFF)<<0)
#define MCF5445_SSI_SSI_CCR_DC(x)                (((x)&0x1F)<<0x8)
#define MCF5445_SSI_SSI_CCR_WL(x)                (((x)&0xF)<<0xD)
#define MCF5445_SSI_SSI_CCR_PSR                  (0x20000)
#define MCF5445_SSI_SSI_CCR_DIV2                 (0x40000)

/* Bit definitions and macros for MCF5445_SSI_SSI_FCSR */
#define MCF5445_SSI_SSI_FCSR_TFWM0(x)            (((x)&0xF)<<0)
#define MCF5445_SSI_SSI_FCSR_RFWM0(x)            (((x)&0xF)<<0x4)
#define MCF5445_SSI_SSI_FCSR_TFCNT0(x)           (((x)&0xF)<<0x8)
#define MCF5445_SSI_SSI_FCSR_RFCNT0(x)           (((x)&0xF)<<0xC)
#define MCF5445_SSI_SSI_FCSR_TFWM1(x)            (((x)&0xF)<<0x10)
#define MCF5445_SSI_SSI_FCSR_RFWM1(x)            (((x)&0xF)<<0x14)
#define MCF5445_SSI_SSI_FCSR_TFCNT1(x)           (((x)&0xF)<<0x18)
#define MCF5445_SSI_SSI_FCSR_RFCNT1(x)           (((x)&0xF)<<0x1C)

/* Bit definitions and macros for MCF5445_SSI_SSI_ACR */
#define MCF5445_SSI_SSI_ACR_AC97EN               (0x1)
#define MCF5445_SSI_SSI_ACR_FV                   (0x2)
#define MCF5445_SSI_SSI_ACR_TIF                  (0x4)
#define MCF5445_SSI_SSI_ACR_RD                   (0x8)
#define MCF5445_SSI_SSI_ACR_WR                   (0x10)
#define MCF5445_SSI_SSI_ACR_FRDIV(x)             (((x)&0x3F)<<0x5)

/* Bit definitions and macros for MCF5445_SSI_SSI_ACADD */
#define MCF5445_SSI_SSI_ACADD_SSI_ACADD(x)       (((x)&0x7FFFF)<<0)

/* Bit definitions and macros for MCF5445_SSI_SSI_ACDAT */
#define MCF5445_SSI_SSI_ACDAT_SSI_ACDAT(x)       (((x)&0xFFFFF)<<0)

/* Bit definitions and macros for MCF5445_SSI_SSI_ATAG */
#define MCF5445_SSI_SSI_ATAG_SSI_ATAG(x)         (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5445_SSI_SSI_TMASK */
#define MCF5445_SSI_SSI_TMASK_SSI_TMASK(x)       (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF5445_SSI_SSI_RMASK */
#define MCF5445_SSI_SSI_RMASK_SSI_RMASK(x)       (((x)&0xFFFFFFFF)<<0)


/*
** MCF5445_SSI_STRUCT                                                                  
** Synchronous Serial Interface (SSI)
*/
typedef struct mcf5445_ssi_struct
{
   uint_32  SSI_TX0;    // SSI Transmit Data Register 0
   uint_32  SSI_TX1;    // SSI Transmit Data Register 1
   uint_32  SSI_RX0;    // SSI Receive Data Register 0
   uint_32  SSI_RX1;    // SSI Receive Data Register 0
   uint_32  SSI_CR;     // SSI Control Register
   uint_32  SSI_ISR;    // SSI Interrupt Status Register
   uint_32  SSI_IER;    // SSI Interrupt Enable Register
   uint_32  SSI_TCR;    // SSI Interrupt Enable Register
   uint_32  SSI_RCR;    // SSI Receive Configuration Register
   uint_32  SSI_CCR;    // SSI Clock Control Register
   uint_32  filler0;
   uint_32  SSI_FCSR;   // SSI FIFO Control/Status Register
   uint_32  filler1;
   uint_32  filler2;
   uint_32  SSI_ACR;    // SSI AC97 Control Register
   uint_32  SSI_ACADD;  // SSI AC97 Command Address Register
   uint_32  SSI_ACDAT;  // SSI AC97 Command Data Register
   uint_32  SSI_ATAG;   // SSI AC97 Tag Register
   uint_32  SSI_TMASK;  // SSI Transmit Time Slot Mask Register
   uint_32  SSI_RMASK;  // SSI Receive Time Slot Mask Register
} MCF5445_SSI_STRUCT, _PTR_ MCF5445_SSI_STRUCT_PTR;
typedef volatile struct mcf5445_ssi_struct _PTR_ VMCF5445_SSI_STRUCT_PTR;


/*
** MCF5445_STRUCT
** This structure defines the memory/registers provided by the MCF5445x
*/
typedef struct mcf5445_struct {
    MCF5445_SCM_A_STRUCT        SCM_A;      // SCM (MPR and PACRs)

    uchar                       filler0[0x4000 - 0 - sizeof(MCF5445_SCM_A_STRUCT)];   
    MCF5445_XBS_STRUCT          XBS;        // Crossbar Switch

    uchar                       filler1[0x8000 - 0x4000 - sizeof(MCF5445_XBS_STRUCT)];   
    MCF5XXX_FB_STRUCT           FB[MCF5445_NUM_FB_CS];         // Mini-FlexBus

    uchar                       filler2[0x30000 - 0x8000 - MCF5445_NUM_FB_CS * sizeof(MCF5XXX_FB_STRUCT)];   
    MCF5XXX_FEC_STRUCT          FEC0;       // Fast Ethernet Controller - Registers and MIB RAM

    uchar                       filler3[0x34000 - 0x30000 - sizeof(MCF5XXX_FEC_STRUCT)];   
    MCF5XXX_FEC_STRUCT          FEC1;       // Fast Ethernet Controller - Registers and MIB RAM

    uchar                       filler4[0x3c000 - 0x34000 - sizeof(MCF5XXX_FEC_STRUCT)];   
    MCF54XX_RTC_STRUCT          RTC;        // RTC

    uchar                       filler5[0x40000 - 0x3c000 - sizeof(MCF54XX_RTC_STRUCT)];   
    MCF5445_SCM_B_STRUCT        SCM_B;      // SCM (CWT and Core Fault Registers)

    uchar                       filler6[0x44000 - 0x40000 - sizeof(MCF5445_SCM_B_STRUCT)];   
    MCF5445_EDMA_STRUCT         EDMA;       // DMA Channels

    uchar                       filler7[0x48000 - 0x44000 - sizeof(MCF5445_EDMA_STRUCT)];   
    MCF54XX_ICTRL0_STRUCT       ICTRL0;     // Interrupt Controller 0

    uchar                       filler8[0x4c000 - 0x48000 - sizeof(MCF54XX_ICTRL0_STRUCT)];   
    MCF54XX_ICTRL1_STRUCT       ICTRL1;     // Interrupt Controller 1

    uchar                       filler9[0x58000 - 0x4c000 - sizeof(MCF54XX_ICTRL1_STRUCT)];   
    MCF54XX_I2C_STRUCT          I2C;       // I2C

    uchar                       filler10[0x5c000 - 0x58000 - sizeof(MCF54XX_I2C_STRUCT)];   
    MCF5XXX_DSPI_STRUCT         DSPI;       // DSPI

    uchar                       filler11[0x60000 - 0x5c000 - sizeof(MCF5XXX_DSPI_STRUCT)];   
    MCF54XX_UART_STRUCT         UART[MCF5445_NUM_UARTS];  // UART

    uchar                       filler12[0x70000 - 0x60000 - MCF5445_NUM_UARTS * sizeof(MCF54XX_UART_STRUCT)];   
    MCF5445_DMA_TIMER_STRUCT    DMA_TIMER[MCF5445_NUM_DMA_TIMERS];// DMA Timers   
    
    MCF5XXX_PIT_STRUCT          PIT[MCF5445_NUM_TIMERS];    // Programmable Interrupt Timers

    uchar                       filler14[0x94000 - 0x80000 - MCF5445_NUM_TIMERS * sizeof(MCF5XXX_PIT_STRUCT)];   
    MCF5445_EPORT_STRUCT        EPORT;   // Edge Port
    
    uchar                       filler15[0xa0000 - 0x94000 - sizeof(MCF5445_EPORT_STRUCT)];   
    MCF54XX_CCM_STRUCT          CCM;        // Chip Configuration Module
    
    uchar                       filler16[0xa4000 - 0xa0000 - sizeof(MCF54XX_CCM_STRUCT)];   
    MCF5445_GPIO_STRUCT         GPIO;       // Ports 

    uchar                       filler17[0xa8000 - 0xa4000 - sizeof(MCF5445_GPIO_STRUCT)];   
    MCF5445_PCI_CTRL_STRUCT     PCI_CTRL;   // PCI Controller

    uchar                       filler18[0xac000 - 0xa8000 - sizeof(MCF5445_PCI_CTRL_STRUCT)];   
    MCF5445_PCI_ARB_STRUCT      PCI_ARB;   // PCI Arbiter

    uchar                       filler19[0xb0000 - 0xac000 - sizeof(MCF5445_PCI_ARB_STRUCT)];   
    MCF5XXX_USBOTG_STRUCT       USBOTG;

    uchar                       filler20[0xb4000 - 0xb0000 - sizeof(MCF5XXX_USBOTG_STRUCT)];   
    MCF5445_RNG_STRUCT          RNG;

    uchar                       filler21[0xb8000 - 0xb4000 - sizeof(MCF5445_RNG_STRUCT)];   
    MCF54XX_SDRAM_CTRL_STRUCT   SDRAMC;

    uchar                       filler22[0xbc000 - 0xb8000 - sizeof(MCF54XX_SDRAM_CTRL_STRUCT)];   
    MCF5445_SSI_STRUCT          SSI;
    
    uchar                       filler23[0xc4000 - 0xbc000 - sizeof(MCF5445_SSI_STRUCT)];   
    MCF5445_PLL_STRUCT          PLL;
} MCF5445_STRUCT, _PTR_ MCF5445_STRUCT_PTR;
typedef volatile struct mcf5445_struct _PTR_ VMCF5445_STRUCT_PTR;

typedef struct psp_support_struct
{
   uint_32 ACR_VALS[MCF5445_NUM_ACRS];
   uint_32 reserved;
} PSP_SUPPORT_STRUCT, _PTR_ PSP_SUPPORT_STRUCT_PTR;

typedef struct psp_mmu_init_struct
{
   uint_32 INITIAL_CACR_ENABLE_BITS;
} PSP_MMU_INIT_STRUCT, _PTR_ PSP_MMU_INIT_STRUCT_PTR;

/*------------------------------------------------------------------------*/
/*
**                      FUNCTION PROTOTYPES AND GLOBAL EXTERNS
*/

extern volatile uint_32 _psp_saved_cacr;
extern volatile uint_32 _psp_saved_acr0;
extern volatile uint_32 _psp_saved_acr1;
extern uchar __KERNEL_DATA_VERIFY_ENABLE[]; // CR1327

void    _mcf5445_initialize_support(uint_32);

void    _mcf5445_icache_enable(uint_32);
void    _mcf5445_icache_disable(void);
void    _mcf5445_icache_invalidate(void);

void    _mcf5445_dcache_enable(uint_32);
void    _mcf5445_dcache_disable(void);
void    _mcf5445_dcache_invalidate(void);

void    _icache_invalidate_mlines(pointer,uint_32,uint_32);
void    _dcache_flush_invalidate_mlines(pointer,uint_32,uint_32,uint_32,uint_32);

void    _mcf5445_mmu_init(uint_32);
uint_32 _mcf5445_mmu_enable(void);
uint_32 _mcf5445_mmu_disable(void);
uint_32 _mcf5445_mmu_add_region(pointer,uint_32,uint_32);

void    __psp_enable_acrs(uint_32_ptr);
void    __psp_clear_acrs(void);

void _psp_dcache_flush_all(uint_32, uint_32, uint_32);

void _dcache_flush(pointer, uint_32, uint_32);
void _dcache_flush_phy(pointer, uint_32, uint_32);

#endif //__ASM__

#ifdef __cplusplus
}
#endif

#endif // __mcf5445_h__

