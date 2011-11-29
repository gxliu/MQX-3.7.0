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
* $FileName: mcf5441.h$
* $Version : 3.7.41.0$
* $Date    : Feb-15-2011$
*
* Comments:
*
*   This file contains the type definitions for the mcf5441x processors.
*
*END************************************************************************/

#ifndef __mcf5441_h__
#define __mcf5441_h__

#define __mcf5441_h__version "$Version:3.7.41.0$"
#define __mcf5441_h__date    "$Date:Feb-15-2011$"

#ifndef __ASM__

/* Include registers for modules common to all Coldfire processors */
#include <reg_enet.h>           /* MACNET */
#include <mcf5xxx_irtc.h>       /* IRTC */
#include <mcf54xx_ictl.h>       /* CTRL */   
#include <mcf5xxx_pit.h>
#include <mcf54xx_sdramc.h>
#include <mcf54xx_uart.h>       /* UART */
#include <mcf5xxx_fb.h>
#include <mcf54xx_ccm.h>
#include <mcf54xx_fcan.h>
#include <mcf54xx_i2c.h>
#include <mcf5xxx_dspi.h>
#include <mcf5xxx_usbotg.h>    /* USBOTG */
#include <reg_nfc.h>           /* NFC */
#include <mcf544xx_adc.h>      /* ADC */
#include <mcf5xxx_esdhc.h>     /* ESDHC */
#include <mcf5xxx_esw.h>       /* Ethernet Switch */

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
#define PSP_HAS_IRTC                        1

#define PSP_ACR_CNT                         4       // ACR registers count

/*
** Cache and MMU definition values
*/
#define PSP_HAS_MMU                         1
#define PSP_HAS_CODE_CACHE                  1
#define PSP_HAS_DATA_CACHE                  1

#define PSP_CACHE_SPLIT                     1

#define PSP_CACHE_HAS_BUS_SNOOPING          FALSE
#define PSP_CACHE_LINE_SIZE                 (0x10)
#define PSP_CACHE_LINE_ALIGNMENT            (0xFFFFFFE0)
#define PSP_DCACHE_SIZE                     (8 * 1024)
#define PSP_ICACHE_SIZE                     (8 * 1024)
#define PSP_CACHE_SIZE                      PSP_DCACHE_SIZE
#define PSP_NUM_CACHE_LINES                 (PSP_CACHE_SIZE / PSP_CACHE_LINE_SIZE)
#define PSP_DCACHE_NUM_WAYS                 (4)
#define PSP_DCACHE_NUM_SETS                 (PSP_DCACHE_SIZE / (PSP_DCACHE_NUM_WAYS * PSP_CACHE_LINE_SIZE))

#define PSP_MEM_STOREBLOCK_ALIGNMENT        (2)

#ifndef __ASM__

/*
** Configuration information
*/
#define MCF5441_NUM_TIMERS                  (4)     // PIT
#define MCF5441_NUM_UARTS                   (10)
#define MCF5441_NUM_DMA_CH                  (64)    // DMA channels
#define MCF5441_NUM_DMA_TIMERS              (4)     // DMA timer

#define MCF5441_NUM_FB_CS                   (6)

#define MCF5441_NUM_ACRS                    (4)
#define MCF5441_NUM_DATA_ACRS               (2)
#define MCF5441_NUM_INSTR_ACRS              (2)
#define MCF5441_FIRST_DATA_ACR              (0)
#define MCF5441_FIRST_INSTR_ACR             (2)

/* Error codes from mcf548x_mmu_add_region */
#define MCF5441_OUT_OF_ACRS                 (0x00100000)

/* Do you want to verify kernel data can be read and written correctly */
#define PSP_KERNEL_DATA_VERIFY_ENABLE       ((uint_32)__KERNEL_DATA_VERIFY_ENABLE)


#define _PSP_BYTES_TO_LINES(b)              (((b) + (PSP_CACHE_LINE_SIZE - 1)) / PSP_CACHE_LINE_SIZE)
#define _PSP_MASK_CACHE_ADDR(p)             (pointer)(((uint_32)p) & ~(PSP_CACHE_LINE_SIZE - 1))

/*
** Standard cache macros
*/

#if PSP_HAS_DATA_CACHE

#define _DCACHE_ENABLE(n)                   _mcf5441_dcache_enable(n)
#define _DCACHE_DISABLE()                   _mcf5441_dcache_disable()

#define _DCACHE_FLUSH()                     // data cache is writethrough
#define _DCACHE_FLUSH_MBYTES(p, m)          // data cache is writethrough
#define _DCACHE_FLUSH_LINE(p)               // data cache is writethrough

#define _DCACHE_INVALIDATE()                _mcf5441_dcache_invalidate()
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

#define _ICACHE_ENABLE(n)                   _mcf5441_icache_enable(n)
#define _ICACHE_DISABLE()                   _mcf5441_icache_disable()
#define _ICACHE_INVALIDATE()                _mcf5441_icache_invalidate()
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
#define MCF54XX_CACR_IVO                        (1 << 20)           // Invalidate only
#define MCF54XX_CACR_BEC                        (1 << 19)           // Enable branch cache.
#define MCF54XX_CACR_BCINVA                     (1 << 18)           // Branch cache invalidate.
#define MCF54XX_CACR_IEC                        (1 << 15)           // Enable instruction cache
#define MCF54XX_CACR_SPA                        (1 << 14)           // Search by physical address
#define MCF54XX_CACR_DNFB                       (1 << 13)           // Default cache-inhibited fill buffer
#define MCF54XX_CACR_IDPI                       (1 << 12)           // Instruction CPUSHL invalidate disable
#define MCF54XX_CACR_IHLCK                      (1 << 11)           // Instruction cache half-lock
#define MCF54XX_CACR_IDCM                       (1 << 10)           // Instruction default cache mode
#define MCF54XX_CACR_ICINVA                     (1 << 8)            // Invalidate instr cache
#define MCF54XX_CACR_IDSP                       (1 << 7)            // Default instruction supervisor protection bit
#define MCF54XX_CACR_EUSP                       (1 << 5)            // Enable user stack pointer

// Bits that should be cleared
#define MCF5441_CACR_CLEAR_BITS                 (0x63025F)

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

// Bit definitions and macros for PAR_FBCTL
#define MCF5441_GPIO_PAR_FBCTL_ALE              (0xC0)
#define MCF5441_GPIO_PAR_FBCTL_OE               (0x30)
#define MCF5441_GPIO_PAR_FBCTL_FBCLK            (0x08)
#define MCF5441_GPIO_PAR_FBCTL_RW               (0x04)
#define MCF5441_GPIO_PAR_FBCTL_TA               (0x03)

// Bit definitions and macros for PAR_BE
#define MCF5441_GPIO_PAR_BE_BE3                 (0xC0)
#define MCF5441_GPIO_PAR_BE_BE2                 (0x30)
#define MCF5441_GPIO_PAR_BE_BE1                 (0x0C)
#define MCF5441_GPIO_PAR_BE_BE0                 (0x03)

// Bit definitions and macros for PAR_CS
#define MCF5441_GPIO_PAR_CS_CS5                 (0xC0)
#define MCF5441_GPIO_PAR_CS_CS4                 (0x30)
#define MCF5441_GPIO_PAR_CS_CS1                 (0x0C)
#define MCF5441_GPIO_PAR_CS_CS0                 (0x01)

// Bit definitions and macros for PAR_CANI2C
#define MCF5441_GPIO_PAR_I2C0_SCL               (0xC0)
#define MCF5441_GPIO_PAR_I2C0_SDA               (0x30)
#define MCF5441_GPIO_PAR_CAN1_TX                (0x0C)
#define MCF5441_GPIO_PAR_CAN1_RX                (0x03)

// Bit definitions and macros for PAR_IRQ0
#define MCF5441_GPIO_PAR_IRQ0H_IRQ07            (0x10)
#define MCF5441_GPIO_PAR_IRQ0H_IRQ04            (0x0C)
#define MCF5441_GPIO_PAR_IRQ0H_IRQ01            (0x01)
#define MCF5441_GPIO_PAR_IRQ0L_IRQ06            (0xC0)
#define MCF5441_GPIO_PAR_IRQ0L_IRQ03            (0x30)
#define MCF5441_GPIO_PAR_IRQ0L_IRQ02            (0x0C)

// Bit definitions and macros for PAR_DSPIOW
#define MCF5441_GPIO_PAR_DSPIOWH_SIN            (0xC0)
#define MCF5441_GPIO_PAR_DSPIOWH_SOUT           (0x30)
#define MCF5441_GPIO_PAR_DSPIOWH_SCK            (0x0C)
#define MCF5441_GPIO_PAR_DSPIOWH_PCS0           (0x03)
#define MCF5441_GPIO_PAR_DSPIOWL_PCS1           (0x80)
#define MCF5441_GPIO_PAR_DSPIOWL_OWDAT          (0x30)

// Bit definitions and macros for PAR_TIMER
#define MCF5441_GPIO_PAR_TIMER_T3IN             (0xC0)
#define MCF5441_GPIO_PAR_TIMER_T2IN             (0x30)
#define MCF5441_GPIO_PAR_TIMER_T1IN             (0x0C)
#define MCF5441_GPIO_PAR_TIMER_T0IN             (0x03)

// Bit definitions and macros for PAR_UARTx
#define MCF5441_GPIO_PAR_UART_CTS               (0xC0)
#define MCF5441_GPIO_PAR_UART_RTS               (0x30)
#define MCF5441_GPIO_PAR_UART_RXD               (0x0C)
#define MCF5441_GPIO_PAR_UART_TXD               (0x03)

#define MCF5441_PAD_PAR_UART_U0TXD_GPIO         (0)
#define MCF5441_PAD_PAR_UART_U0TXD_DSPI2_SOUT   (0x1)
#define MCF5441_PAD_PAR_UART_U0TXD_SCL4         (0x2)
#define MCF5441_PAD_PAR_UART_U0TXD_U0TXD        (0x3)
#define MCF5441_PAD_PAR_UART_U0RXD_GPIO         (0)
#define MCF5441_PAD_PAR_UART_U0RXD_DSPI2_SIN    (0x4)
#define MCF5441_PAD_PAR_UART_U0RXD_SDA4         (0x8)
#define MCF5441_PAD_PAR_UART_U0RXD_U0RXD        (0xC)
#define MCF5441_PAD_PAR_UART_U0RTS_GPIO         (0)
#define MCF5441_PAD_PAR_UART_U0RTS_DSPI2_PSC0   (0x10)
#define MCF5441_PAD_PAR_UART_U0RTS_U4RXD        (0x20)
#define MCF5441_PAD_PAR_UART_U0RTS_U0RTS        (0x30)
#define MCF5441_PAD_PAR_UART_U0CTS_GPIO         (0)
#define MCF5441_PAD_PAR_UART_U0CTS_DSPI2_SCK    (0x40)
#define MCF5441_PAD_PAR_UART_U0CTS_U4TXD        (0x80)
#define MCF5441_PAD_PAR_UART_U0CTS_U0CTS        (0xC0)

#define MCF5441_PAD_PAR_UART_U1TXD_GPIO         (0)
#define MCF5441_PAD_PAR_UART_U1TXD_DSPI3_SOUT   (0x1)
#define MCF5441_PAD_PAR_UART_U1TXD_SCL5         (0x2)
#define MCF5441_PAD_PAR_UART_U1TXD_U1TXD        (0x3)
#define MCF5441_PAD_PAR_UART_U1RXD_GPIO         (0)
#define MCF5441_PAD_PAR_UART_U1RXD_DSPI3_SIN    (0x4)
#define MCF5441_PAD_PAR_UART_U1RXD_SDA5         (0x8)
#define MCF5441_PAD_PAR_UART_U1RXD_U1RXD        (0xC)
#define MCF5441_PAD_PAR_UART_U1RTS_GPIO         (0)
#define MCF5441_PAD_PAR_UART_U1RTS_DSPI3_PCS0   (0x10)
#define MCF5441_PAD_PAR_UART_U1RTS_U5RXD        (0x20)
#define MCF5441_PAD_PAR_UART_U1RTS_U1RTS        (0x30)
#define MCF5441_PAD_PAR_UART_U1CTS_GPIO         (0)
#define MCF5441_PAD_PAR_UART_U1CTS_DSPI3_SCK    (0x40)
#define MCF5441_PAD_PAR_UART_U1CTS_U5TXD        (0x80)
#define MCF5441_PAD_PAR_UART_U1CTS_U1CTS        (0xC0)

#define MCF5441_PAD_PAR_UART_U2TXD_GPIO         (0)
#define MCF5441_PAD_PAR_UART_U2TXD_SSI1_TXD     (0x1)
#define MCF5441_PAD_PAR_UART_U2TXD_PWM_B3       (0x2)
#define MCF5441_PAD_PAR_UART_U2TXD_U2TXD        (0x3)
#define MCF5441_PAD_PAR_UART_U2RXD_GPIO         (0)
#define MCF5441_PAD_PAR_UART_U2RXD_SSI1_RXD     (0x4)
#define MCF5441_PAD_PAR_UART_U2RXD_PWM_A3       (0x8)
#define MCF5441_PAD_PAR_UART_U2RXD_U2RXD        (0xC)
#define MCF5441_PAD_PAR_UART_U2RTS_GPIO         (0)
#define MCF5441_PAD_PAR_UART_U2RTS_SSI1_FS      (0x10)
#define MCF5441_PAD_PAR_UART_U2RTS_U6RXD        (0x20)
#define MCF5441_PAD_PAR_UART_U2RTS_U2RTS        (0x30)
#define MCF5441_PAD_PAR_UART_U2CTS_GPIO         (0)
#define MCF5441_PAD_PAR_UART_U2CTS_SSI1_BCLK    (0x40)
#define MCF5441_PAD_PAR_UART_U2CTS_U6TXD        (0x80)
#define MCF5441_PAD_PAR_UART_U2CTS_U2CTS        (0xC0)

// Bit definitions and macros for PAR_SDHC
#define MCF5441_GPIO_PAR_SDHCH_DATA3            (0xC0)
#define MCF5441_GPIO_PAR_SDHCH_DATA2            (0x30)
#define MCF5441_GPIO_PAR_SDHCH_DATA1            (0x0C)
#define MCF5441_GPIO_PAR_SDHCH_DATA0            (0x03)
#define MCF5441_GPIO_PAR_SDHCL_CMD              (0x0C)
#define MCF5441_GPIO_PAR_SDHCL_CLK              (0x03)

// Bit definitions and macros for PAR_SIMP0
#define MCF5441_GPIO_PAR_SIMP0H_DATA            (0xC0)
#define MCF5441_GPIO_PAR_SIMP0H_VEN             (0x30)
#define MCF5441_GPIO_PAR_SIMP0H_RST             (0x0C)
#define MCF5441_GPIO_PAR_SIMP0H_PD              (0x03)
#define MCF5441_GPIO_PAR_SIMP0L_CLK             (0x03)

// Bit definitions and macros for PAR_SSI0
#define MCF5441_GPIO_PAR_SSI0H_RXD              (0xC0)
#define MCF5441_GPIO_PAR_SSI0H_TXD              (0x30)
#define MCF5441_GPIO_PAR_SSI0H_FS               (0x0C)
#define MCF5441_GPIO_PAR_SSI0H_MCLK             (0x03)
#define MCF5441_GPIO_PAR_SSI0L_BCLK             (0x03)

// Bit definitions and macros for PAR_DEBUG
#define MCF5441_GPIO_PAR_DEBUGH1_DDATA3         (0x40)
#define MCF5441_GPIO_PAR_DEBUGH1_DDATA2         (0x10)
#define MCF5441_GPIO_PAR_DEBUGH1_DDATA1         (0x04)
#define MCF5441_GPIO_PAR_DEBUGH1_DDATA0         (0x01)
#define MCF5441_GPIO_PAR_DEBUGH0_PST3           (0x40)
#define MCF5441_GPIO_PAR_DEBUGH0_PST2           (0x10)
#define MCF5441_GPIO_PAR_DEBUGH0_PST1           (0x04)
#define MCF5441_GPIO_PAR_DEBUGH0_PST0           (0x01)
#define MCF5441_GPIO_PAR_DEBUGL_ALLPST          (0x01)

// Bit definitions and macros for PAR_FEC
#define MCF5441_GPIO_PAR_FEC_FEC                (0x0F)

// Bit definitions and macros for PAR_FEC
#define MCF5441_PAD_PAR_FEC(x)                   (((x)&0xF)<<0)
#define MCF5441_PAD_PAR_FEC_MII_FULL             (0)
#define MCF5441_PAD_PAR_FEC_MII_NON_FULL         (0x1)
#define MCF5441_PAD_PAR_FEC_RMII0_RMII1_FULL     (0x3)
#define MCF5441_PAD_PAR_FEC_RMII0_RMII1_NON_FULL (0x4)
#define MCF5441_PAD_PAR_FEC_RMII0_FULL_RMII1_NON_FULL (0x5)
#define MCF5441_PAD_PAR_FEC_RMII0_NON_FULL_RMII1_FULL (0x6)
#define MCF5441_PAD_PAR_FEC_RMII0_FULL           (0x7)
#define MCF5441_PAD_PAR_FEC_RMII0_FULL_ULPI      (0x8)
#define MCF5441_PAD_PAR_FEC_RMII0_NON_MII        (0x9)
#define MCF5441_PAD_PAR_FEC_RMII0_NON_MII_ULPI   (0xA)
#define MCF5441_PAD_PAR_FEC_RMII1_FULL           (0xB)
#define MCF5441_PAD_PAR_FEC_RMII1_NON_MII        (0xC)
#define MCF5441_PAD_PAR_FEC_ALL_GPIO             (0xD)

/* Bit definitions and macros for PAR_UART0 */

/* Bit definitions and macros for PAR_UART1 */

/* Bit definitions and macros for PLL_DR */
#define MCF5441_PLL_CR_LOLEN                (1 << 12)
#define MCF5441_PLL_CR_REFDIV(x)            (((x) & 7) << 8)
#define MCF5441_PLL_CR_FBKDIV(x)            ((x) & 0x3f)

/* Bit definitions and macros for PLL_DR */
#define MCF5441_PLL_DR_OUTDIV1(x)           ((x) & 0x1f)
#define MCF5441_PLL_DR_OUTDIV2(x)           (((x) & 0x1f) << 5)
#define MCF5441_PLL_DR_OUTDIV3(x)           (((x) & 0x1f) << 10)
#define MCF5441_PLL_DR_OUTDIV4(x)           (((x) & 0x1f) << 16)
#define MCF5441_PLL_DR_OUTDIV5(x)           (((x) & 0x1f) << 21)

/* Bit definitions and macros for PLL_SR */
#define MCF5441_PLL_SR_LOCF                 (1 << 9)
#define MCF5441_PLL_SR_LOC                  (1 << 8)
#define MCF5441_PLL_SR_LOLF                 (1 << 6)
#define MCF5441_PLL_SR_LOCKS                (1 << 5)
#define MCF5441_PLL_SR_LOCK                 (1 << 4)

/*
** Interrupt definitions
*/
#define MCF5441_ICTRL_MASKALL               1
#define MCF5441_ICTRL0_BASEx                64
#define MCF5441_ICTRL1_BASEx                128

/*
** Interrupt vector table
*/
typedef enum mcf5441_interrupt_table_index {
    MCF5441_boot_stack_pointer,
    MCF5441_boot_program_counter,
    MCF5441_EXC_ACCESS_ERROR,
    MCF5441_EXC_ADDRESS_ERROR,
    MCF5441_EXC_ILLEGAL_INSTRUCTION,
    MCF5441_EXC_DIVIDE_BY_ZERO,
    MCF5441_EXC_rsvd6,
    MCF5441_EXC_rsvd7,
    MCF5441_EXC_PRIVILEGE_VIOLATION,
    MCF5441_EXC_NEXT_TRACE,
    MCF5441_EXC_UNIMPLEMENTED_LINE_A_OPCODE,
    MCF5441_EXC_UNIMPLEMENTED_LINE_F_OPCODE,
    MCF5441_EXC_DEBUG,
    MCF5441_EXC_rsvd13,
    MCF5441_EXC_FORMAT_ERROR,
    MCF5441_EXC_rsvd15,
    MCF5441_EXC_rsvd16,
    MCF5441_EXC_rsvd17,
    MCF5441_EXC_rsvd18,
    MCF5441_EXC_rsvd19,
    MCF5441_EXC_rsvd20,
    MCF5441_EXC_rsvd21,
    MCF5441_EXC_rsvd22,
    MCF5441_EXC_rsvd23,
    MCF5441_EXC_SPURIOUS,
    MCF5441_EXC_rsvd25,
    MCF5441_EXC_rsvd26,
    MCF5441_EXC_rsvd27,
    MCF5441_EXC_rsvd28,
    MCF5441_EXC_rsvd29,
    MCF5441_EXC_rsvd30,
    MCF5441_EXC_rsvd31,
    MCF5441_EXC_TRAP0,
    MCF5441_EXC_TRAP1,
    MCF5441_EXC_TRAP2,
    MCF5441_EXC_TRAP3,
    MCF5441_EXC_TRAP4,
    MCF5441_EXC_TRAP5,
    MCF5441_EXC_TRAP6,
    MCF5441_EXC_TRAP7,
    MCF5441_EXC_TRAP8,
    MCF5441_EXC_TRAP9,
    MCF5441_EXC_TRAP10,
    MCF5441_EXC_TRAP11,
    MCF5441_EXC_TRAP12,
    MCF5441_EXC_TRAP13,
    MCF5441_EXC_TRAP14,
    MCF5441_EXC_TRAP15,
    MCF5441_EXC_rsvd48,
    MCF5441_EXC_rsvd49,
    MCF5441_EXC_rsvd50,
    MCF5441_EXC_rsvd51,
    MCF5441_EXC_rsvd52,
    MCF5441_EXC_rsvd53,
    MCF5441_EXC_rsvd54,
    MCF5441_EXC_rsvd55,
    MCF5441_EXC_rsvd56,
    MCF5441_EXC_rsvd57,
    MCF5441_EXC_rsvd58,
    MCF5441_EXC_rsvd59,
    MCF5441_EXC_rsvd60,
    MCF5441_EXC_rsvd61,
    MCF5441_EXC_rsvd62,
    MCF5441_EXC_rsvd63,

    /* Interrupt Controller 0 */    
    MCF5441_INT_FIRST_EXTERNAL, // 0 -  Not used
    MCF5441_INT_EPFR0_EPF1, // 1 -  Edge port 0 flag 1 
    MCF5441_INT_EPFR0_EPF2, // 2 -  Edge port 0 flag 2 
    MCF5441_INT_EPFR0_EPF3, // 3 -  Edge port 0 flag 3 
    MCF5441_INT_EPFR0_EPF4, // 4 -  Edge port 0 flag 4 
    MCF5441_INT_EPFR0_EPF5, // 5 -  Edge port 0 flag 5 
    MCF5441_INT_EPFR0_EPF6, // 6 -  Edge port 0 flag 6 
    MCF5441_INT_EPFR0_EPF7, // 7 -  Edge port 0 flag 7 
    MCF5441_INT_EDMA_INTR_INT00,    // 8 -  DMA Channel 0 transfer complete 
    MCF5441_INT_EDMA_INTR_INT01,    // 9 -  DMA Channel 1 transfer complete 
    MCF5441_INT_EDMA_INTR_INT02,    // 10 -  DMA Channel 2 transfer complete 
    MCF5441_INT_EDMA_INTR_INT03,    // 11 -  DMA Channel 3 transfer complete 
    MCF5441_INT_EDMA_INTR_INT04,    // 12 -  DMA Channel 4transfer complete 
    MCF5441_INT_EDMA_INTR_INT05,    // 13 -  DMA Channel 5 transfer complete 
    MCF5441_INT_EDMA_INTR_INT06,    // 14 -  DMA Channel 6 transfer complete 
    MCF5441_INT_EDMA_INTR_INT07,    // 15 -  DMA Channel 7 transfer complete 
    MCF5441_INT_EDMA_INTR_INT08,    // 16 -  DMA Channel 8 transfer complete 
    MCF5441_INT_EDMA_INTR_INT09,    // 17 -  DMA Channel 9 transfer complete 
    MCF5441_INT_EDMA_INTR_INT10,    // 18 -  DMA Channel 10 transfer complete 
    MCF5441_INT_EDMA_INTR_INT11,    // 19 -  DMA Channel 11 transfer complete 
    MCF5441_INT_EDMA_INTR_INT12,    // 20 -  DMA Channel 12 transfer complete 
    MCF5441_INT_EDMA_INTR_INT13,    // 21 -  DMA Channel 13 transfer complete 
    MCF5441_INT_EDMA_INTR_INT14,    // 22 -  DMA Channel 14 transfer complete 
    MCF5441_INT_EDMA_INTR_INT15,    // 23 -  DMA Channel 15 transfer complete 
    MCF5441_INT_EDMA_ERR_ERRn,  // 24 -  DMA Error Interrupt 
    MCF5441_INT_SCM,    // 25 -  SCMIR_CWIC Core Watchdog Timeout 
    MCF5441_INT_UART0,  // 26 -  UISR0 register UART0 Interrupt Request Automatically cleared
    MCF5441_INT_UART1,  // 27 -  UISR1 register UART1 Interrupt Request Automatically cleared
    MCF5441_INT_UART2,  // 28 -  UISR2 register UART2 Interrupt Request Automatically cleared
    MCF5441_INT_UART3,  // 29 -  UISR3 register UART3 Interrupt Request Automatically cleared
    MCF5441_INT_I2C0,   // 30 -  I20SR_IIF I2C0 Interrupt 
    MCF5441_INT_DSPI0,  // 31 -  DSPI0_SR register DSPI0 OR’d interrupt :
    MCF5441_INT_DTIM0,  // 32 -  DTER0 register Timer 0 interrupt 
    MCF5441_INT_DTIM1,  // 33 -  DTER1 register Timer 1 interrupt 
    MCF5441_INT_DTIM2,  // 34 -  DTER2 register Timer 2 interrupt 
    MCF5441_INT_DTIM3,  // 35 -  DTER3 register Timer 3 interrupt 
    MCF5441_INT_ENET0_EIR_TXF,  // 36 -  Transmit frame interrupt 
    MCF5441_INT_ENET0_EIR_TXB,  // 37 -  Transmit buffer interrupt 
    MCF5441_INT_ENET0_EIR_UN,   // 38 -  Transmit FIFO underrun 
    MCF5441_INT_ENET0_EIR_RL,   // 39 -  Collision retry limit 
    MCF5441_INT_ENET0_EIR_RXF,  // 40 -  Receive frame interrupt 
    MCF5441_INT_ENET0_EIR_RXB,  // 41 -  Receive buffer interrupt 
    MCF5441_INT_ENET0_EIR_MII,  // 42 -  MII interrupt 
    MCF5441_INT_ENET0_EIR_LC,   // 43 -  Late collision 
    MCF5441_INT0_rsvd44,        // 44 -  Not used
    MCF5441_INT_ENET0_EIR_GRA,  // 45 -  Graceful stop complete 
    MCF5441_INT_ENET0_EIR_EBERR,// 46 -  Ethernet bus error 
    MCF5441_INT_ENET0_EIR_BABT, // 47 -  Babbling transmit error 
    MCF5441_INT_ENET0_EIR_BABR, // 48 -  Babbling receive error 
    MCF5441_INT_ENET1_EIR_TXF,  // 49 -  Transmit frame interrupt 
    MCF5441_INT_ENET1_EIR_TXB,  // 50 -  Transmit buffer interrupt 
    MCF5441_INT_ENET1_EIR_UN,   // 51 -  Transmit FIFO underrun 
    MCF5441_INT_ENET1_EIR_RL,   // 52 -  Collision retry limit 
    MCF5441_INT_ENET1_EIR_RXF,  // 53 -  Receive frame interrupt 
    MCF5441_INT_ENET1_EIR_RXB,  // 54 -  Receive buffer interrupt 
    MCF5441_INT_ENET1_EIR_MII,  // 55 -  MII interrupt 
    MCF5441_INT_ENET1_EIR_LC,   // 56 -  Late collision 
    MCF5441_INT0_rsvd57,        // 57 -  Not used
    MCF5441_INT_ENET1_EIR_GRA,  // 58 -  Graceful stop complete 
    MCF5441_INT_ENET1_EIR_EBERR,// 59 -  Ethernet bus error 
    MCF5441_INT_ENET1_EIR_BABT, // 60 -  Babbling transmit error 
    MCF5441_INT_ENET1_EIR_BABR, // 61 -  Babbling receive error 
    MCF5441_INT_SCM_SCMIR_CFEI, // 62 -  SCMIR_CFEI Core bus error interrupt 
    MCF5441_INT_1_Wire,         // 63 -  OW_ISR 1_Wire interrupt Reading OW_ISR


    /* Interrupt Controller 1 */
    MCF5441_INT_IFLAG0_BUFnI,       // 0 -  Logical OR of CAN0’s MB requests 
    MCF5441_INT_ERRSTAT0_BOFFINT,   // 1 -  Bus_off interrupt 
    MCF5441_INT1_rsvd2,             // 2 -  Not used
    MCF5441_INT_ERRSTAT0_TXWRN_or_RXWRN,    // 3 -  Error interrupt 
    MCF5441_INT_IFLAG1_BUFnI,       // 4 -  Logical OR of CAN1’s MB requests 
    MCF5441_INT_ERRSTAT1_BOFFINT,   // 5 -  Bus_off interrupt 
    MCF5441_INT1_rsvd6,             // 6 -  Not used
    MCF5441_INT_ERRSTAT1_TXWRN_or_RXWRN,    // 7 -  Error interrupt 
    MCF5441_INT_EDMA_INTR_INT16,    // 8 -  DMA Channel 16 transfer complete 
    MCF5441_INT_EDMA_INTR_INT17,    // 9 -  DMA Channel 17 transfer complete 
    MCF5441_INT_EDMA_INTR_INT18,    // 10 -  DMA Channel 18 transfer complete 
    MCF5441_INT_EDMA_INTR_INT19,    // 11 -  DMA Channel 19 transfer complete 
    MCF5441_INT_EDMA_INTR_INT20,    // 12 -  DMA Channel 20 transfer complete 
    MCF5441_INT_EDMA_INTR_INT21,    // 13 -  DMA Channel 21 transfer complete 
    MCF5441_INT_EDMA_INTR_INT22,    // 14 -  DMA Channel 22 transfer complete 
    MCF5441_INT_EDMA_INTR_INT23,    // 15 -  DMA Channel 23 transfer complete 
    MCF5441_INT_EDMA_INTR_INT24,    // 16 -  DMA Channel 24 transfer complete 
    MCF5441_INT_EDMA_INTR_INT25,    // 17 -  DMA Channel 25 transfer complete 
    MCF5441_INT_EDMA_INTR_INT26,    // 18 -  DMA Channel 26 transfer complete 
    MCF5441_INT_EDMA_INTR_INT27,    // 19 -  DMA Channel 27 transfer complete 
    MCF5441_INT_EDMA_INTR_INT28,    // 20 -  DMA Channel 28 transfer complete 
    MCF5441_INT_EDMA_INTR_INT29,    // 21 -  DMA Channel 29 transfer complete 
    MCF5441_INT_EDMA_INTR_INT30,    // 22 -  DMA Channel 30 transfer complete 
    MCF5441_INT_EDMA_INTR_INT31,    // 23 -  DMA Channel 31 transfer complete 
    MCF5441_INT_EDMA_INTR_INT32,    // 24 -  DMA Channel 32 transfer complete 
    MCF5441_INT_EDMA_INTR_INT33,    // 25 -  DMA Channel 33 transfer complete 
    MCF5441_INT_EDMA_INTR_INT34,    // 26 -  DMA Channel 34 transfer complete 
    MCF5441_INT_EDMA_INTR_INT35,    // 27 -  DMA Channel 35 transfer complete 
    MCF5441_INT_EDMA_INTR_INT36,    // 28 -  DMA Channel 36 transfer complete 
    MCF5441_INT_EDMA_INTR_INT37,    // 29 -  DMA Channel 37 transfer complete 
    MCF5441_INT_EDMA_INTR_INT38,    // 30 -  DMA Channel 38 transfer complete 
    MCF5441_INT_EDMA_INTR_INT39,    // 31 -  DMA Channel 39 transfer complete 
    MCF5441_INT_EDMA_INTR_INT40,    // 32 -  DMA Channel 40 transfer complete 
    MCF5441_INT_EDMA_INTR_INT41,    // 33 -  DMA Channel 41 transfer complete 
    MCF5441_INT_EDMA_INTR_INT42,    // 34 -  DMA Channel 42 transfer complete 
    MCF5441_INT_EDMA_INTR_INT43,    // 35 -  DMA Channel 43 transfer complete 
    MCF5441_INT_EDMA_INTR_INT44,    // 36 -  DMA Channel 44 transfer complete 
    MCF5441_INT_EDMA_INTR_INT45,    // 37 -  DMA Channel 45 transfer complete 
    MCF5441_INT_EDMA_INTR_INT46,    // 38 -  DMA Channel 46 transfer complete 
    MCF5441_INT_EDMA_INTR_INT47,    // 39 -  DMA Channel 47 transfer complete 
    MCF5441_INT_EDMA_INTR_INT48,    // 40 -  DMA Channel 48 transfer complete 
    MCF5441_INT_EDMA_INTR_INT49,    // 41 -  DMA Channel 49 transfer complete 
    MCF5441_INT_EDMA_INTR_INT50,    // 42 -  DMA Channel 50 transfer complete 
    MCF5441_INT_EDMA_INTR_INT51,    // 43 -  DMA Channel 51 transfer complete 
    MCF5441_INT_EDMA_INTR_INT52,    // 44 -  DMA Channel 52 transfer complete 
    MCF5441_INT_EDMA_INTR_INT53,    // 45 -  DMA Channel 53 transfer complete 
    MCF5441_INT_EDMA_INTR_INT54,    // 46 -  DMA Channel 54 transfer complete 
    MCF5441_INT_EDMA_INTR_INT55,    // 47 -  DMA Channel 55 transfer complete 
    MCF5441_INT_UART4,  // 48 -  UISR4 register UART4 Interrupt Request Automatically cleared
    MCF5441_INT_UART5,  // 49 -  UISR5 register UART5 Interrupt Request Automatically cleared
    MCF5441_INT_UART6,  // 50 -  UISR6 register UART6 Interrupt Request Automatically cleared
    MCF5441_INT_UART7,  // 51 -  UISR7 register UART7 Interrupt Request Automatically cleared
    MCF5441_INT_UART8,  // 52 -  UISR8 register UART8 Interrupt Request Automatically cleared
    MCF5441_INT_UART9,  // 53 -  UISR9 register UART9 Interrupt Request Automatically cleared
    MCF5441_INT_DSPI1,  // 54 -  DSPI1_SR register DSPI1 OR’d interrupt 
    MCF5441_INT_DSPI2,  // 55 -  DSPI2_SR register DSPI2 OR’d interrupt 
    MCF5441_INT_DSPI3,  // 56 -  DSPI3_SR register DSPI3 OR’d interrupt 
    MCF5441_INT_I2C1,   // 57 -  I21SR_IIF I2C1 Interrupt 
    MCF5441_INT_I2C2,   // 58 -  I22SR_IIF I2C2 Interrupt 
    MCF5441_INT_I2C3,   // 59 -  I23SR_IIF I2C3 Interrupt 
    MCF5441_INT_I2C4,   // 60 -  I24SR_IIF I2C4 Interrupt 
    MCF5441_INT_I2C5,   // 61 -  I25SR_IIF I2C5 Interrupt 
    MCF5441_INT1_rsvd62,// 62 -  Not used
    MCF5441_INT1_rsvd63,// 63 -  Not used


    /* Interrupt Controller 2 */
    MCF5441_INT_EDMA_INTR_INT56_63, // 0 -  DMA Channel 55–63 OR’d transfer complete 
    MCF5441_INT_PWM_SM0SR_CFxn, // 1 -  Submodule 0 OR’d input capture 
    MCF5441_INT_PWM_SM1SR_CFxn, // 2 -  Submodule 1 OR’d input capture 
    MCF5441_INT_PWM_SM2SR_CFxn, // 3 -  Submodule 2 OR’d input capture 
    MCF5441_INT_PWM_SM3SR_CFxn, // 4 -  Submodule 3 OR’d input capture 
    MCF5441_INT_PWM_SM0SR_RF,   // 5 -  Submodule 0 reload 
    MCF5441_INT_PWM_SM1SR_RF,   // 6 -  Submodule 1 reload 
    MCF5441_INT_PWM_SM2SR_RF,   // 7 -  Submodule 2 reload 
    MCF5441_INT_PWM_SM3SR_RF,   // 8 -  Submodule 3 reload 
    MCF5441_INT_PWM_FSR_FFLAG,  // 9 -  OR’d fault input interrupt 
    MCF5441_INT_PWM_SMnSR_REF,  // 10 -  OR’d reload error interrupt 
    MCF5441_INT_PLL_SR_LOCF,    // 11 -  Loss of clock interrupt 
    MCF5441_INT_PLL_SR_LOLF,    // 12 -  Loss of lock interrupt 
    MCF5441_INT_PIT0,           // 13 -  PCSR0_PIF PIT interrupt flag 
    MCF5441_INT_PIT1,           // 14 -  PCSR1_PIF PIT interrupt flag 
    MCF5441_INT_PIT2,           // 15 -  PCSR2_PIF PIT interrupt flag 
    MCF5441_INT_PIT3,           // 16 -  PCSR3_PIF PIT interrupt flag 
    MCF5441_INT_USB_OTG,        // 17 -  USB_STS USB OTG interrupt 
    MCF5441_INT_USB_HOST,       // 18 -  USB_STS USB host interrupt 
    MCF5441_INT_PWM_SM0SR_CMPF, // 19 -  Submodule 0 compare
    MCF5441_INT_PWM_SM1SR_CMPF, // 20 -  Submodule 1 compare
    MCF5441_INT_PWM_SM2SR_CMPF, // 21 -  Submodule 2 compare
    MCF5441_INT_PWM_SM3SR_CMPF, // 22 -  Submodule 3 compare
    MCF5441_INT_SSI0,           // 23 -  SSI0_ISR SSI0 interrupt Various
    MCF5441_INT_SSI1,           // 24 -  SSI1_ISR SSI1 interrupt Various
    MCF5441_INT_Flash,          // 25 -  NFC_ISR NAND flash controller interrupt 
    MCF5441_INT_Robust_RTC,     // 26 -  RTC_ISR RTC interrupt 
    MCF5441_INT_CCM,            // 27 -  UOCSR USB status Interrupt Read UOCSR.
    MCF5441_INT_RNG,            // 28 -  EI RNG interrupt flag 
    MCF5441_INT_SIM1,           // 29 -  SIM_RSR or SIM_TSR SIM data interrupt Various, see chapter for details
    MCF5441_INT_SIM,            // 30 -  general interrupt Various, see chapter for details
    MCF5441_INT_SDHC,           // 31 -  IRQSTAT SDHC OR’d interrupt 
    MCF5441_INT_ADC_SR_EOSI0,   // 32 -  ADC subconverter A done
    MCF5441_INT_ADC_SR_EOSI1,   // 33 -  ADC subconverter B done
    MCF5441_INT_ADC_LSR_ZCSR,   // 34 -  Zero-crossing/limit-crossed
    MCF5441_INT2_rsvd35,        // 35 -  Not used
    MCF5441_INT_SDRAM_DDR_CR27, // 36 -  SDRAM OR’d interrupt
    MCF5441_INT2_rsvd37,        // 37 -  Not used
    MCF5441_INT_ESW_ISR_EBERR,  // 38 -  Bus error interrupt 
    MCF5441_INT_ESW_ISR_RXB,    // 39 -  Receive buffer interrupt 
    MCF5441_INT_ESW_ISR_RXF,    // 40 -  Receive frame interrupt 
    MCF5441_INT_ESW_ISR_TXB,    // 41 -  Transmit buffer interrupt 
    MCF5441_INT_ESW_ISR_TXF,    // 42 -  Transmit frame interrupt 
    MCF5441_INT_ESW_ISR_QM,     // 43 -  Low amount of free memory 
    MCF5441_INT_ESW_ISR_OD0,    // 44 -  Port 0 output discard 
    MCF5441_INT_ESW_ISR_OD1,    // 45 -  Port 1 output discard 
    MCF5441_INT_ESW_ISR_OD2,    // 46 -  Port 2 output discard 
    MCF5441_INT_ESW_ISR_LRN,    // 47 -  Learning record available 
    MCF5441_INT_ENET0_EIR_TS_AVAIL, // 48 -  Timestamp available 
    MCF5441_INT_ENET0_EIR_WAKEUP,   // 49 -  Wake from sleep 
    MCF5441_INT_ENET0_EIR_PLR,  // 50 -  Payload receive error 
    MCF5441_INT2_rsvd50,        // 51 -  Not used
    MCF5441_INT2_rsvd51,        // 52 -  Not used
    MCF5441_INT2_rsvd52,        // 53 -  Not used
    MCF5441_INT2_rsvd53,        // 54 -  Not used
    MCF5441_INT_ENET1_EIR_TS_AVAIL, // 55 -  Timestamp available 
    MCF5441_INT_ENET1_EIR_WAKEUP,   // 56 -  Wake from sleep 
    MCF5441_INT_ENET1_EIR_PLR   // 57 -  Payload receive error 
} MCF5441_INTERRUPT_TABLE_INDEX;//, PSP_INTERRUPT_TABLE_INDEX;

/*
** MCF5441_PLL_STRUCT
** ColdFire PLL
*/
typedef struct mcf5441_pll_struct {
    uint_32 CR;            // PLL Control Register
    uint_32 DR;            // PLL Divider register
    uint_32 SR;            // PLL Status Register
} MCF5441_PLL_STRUCT, _PTR_ MCF5441_PLL_STRUCT_PTR;
typedef volatile struct mcf5441_pll_struct _PTR_ VMCF5441_PLL_STRUCT_PTR;

/*
** MCF5441_PMM_STRUCT
** Power Management (PMM)
** NOTE!!! in register address space, this is shared with SCM, use SCM_PMM union defined below
*/
typedef struct mcf5441_pmm_struct {
    uint_8 filler0[3];
    uint_8 WCR;
    uint_8 filler1[0x18];
    uint_8 PPMSR0;
    uint_8 PPMCR0;
    uint_8 PPMSR1;
    uint_8 PPMCR1;
    uint_32 PPMHR0;
    uint_32 PPMLR0;
    uint_32 PPMHR1;
    uint_32 PPMLR1;
} MCF5441_PMM_STRUCT, _PTR_ MCF5441_PMM_STRUCT_PTR;
typedef volatile struct mcf5441_pmm_struct _PTR_ VMCF5441_PMM_STRUCT_PTR;

/*
** MCF5441_SCM_STRUCT
** System Control Module (SCM)
** NOTE!!! in register address space, this is shared with PMM, use SCM_PMM union defined below
*/
typedef struct mcf5441_scm_struct {
    uint_8  filler0[3];
    uint_8  WCR;
    uint_8  filler1[2];
    uint_16 CWCR;           // Core watchdog control register
    uint_8  filler2[3];
    uint_8  CWSR;           // Core watchdog service register
    uint_8  filler3[3];
    uint_8  SCMISR;         // SCM interrupt status register
    uint_8  filler4[4];
    uint_32 BCR;            // Burst configuration register
    uint_8  filler5[0x70 - 0x24 + 0x04];
    uint_32 CFADR;          // Core fault address register
    uint_8  filler6[1];
    uint_8  CFIER;          // Core fault interrupt enable register
    uint_8  CFLOC;          // Core fault location register
    uint_8  CFATR;          // Core fault attributes register
    uint_8  filler7[0x7c - 0x77 + 0x01];
    uint_32 CFDTR;          // Core fault data register
} MCF5441_SCM_STRUCT, _PTR_ MCF5441_SCM_STRUCT_PTR;
typedef volatile struct mcf5441_scm_struct _PTR_ VMCF5441_SCM_STRUCT_PTR;

typedef union mcf5441_scm_pmm_union {
    volatile MCF5441_SCM_STRUCT SCM;
    volatile MCF5441_PMM_STRUCT PMM;
} MCF5441_SCM_PMM_UNION, _PTR_ MCF5441_SCM_PMM_UNION_PTR;
typedef volatile union mcf5441_scm_pmm_union _PTR_ VMCF5441_SCM_PMM_UNION_PTR;

/*
** MCF5441_GPIO_STRUCT
** GPIO Registers
*/
typedef struct mcf5441_gpio_struct {
    uint_8 PODR_A, PODR_B, PODR_C, PODR_D, PODR_E, PODR_F, PODR_G, PODR_H, PODR_I, PODR_J, PODR_K;
    uint_8 filler0[1];
    uint_8 PDDR_A, PDDR_B, PDDR_C, PDDR_D, PDDR_E, PDDR_F, PDDR_G, PDDR_H, PDDR_I, PDDR_J, PDDR_K;
    uint_8 filler1[1];
    uint_8 PPDSDR_A, PPDSDR_B, PPDSDR_C, PPDSDR_D, PPDSDR_E, PPDSDR_F, PPDSDR_G, PPDSDR_H, PPDSDR_I, PPDSDR_J, PPDSDR_K;
    uint_8 filler2[1];
    uint_8 PCLRR_A, PCLRR_B, PCLRR_C, PCLRR_D, PCLRR_E, PCLRR_F, PCLRR_G, PCLRR_H, PCLRR_I, PCLRR_J, PCLRR_K;
    uint_8 filler3[1];
    uint_16 PCR_A, PCR_B, PCR_C, PCR_D, PCR_E, PCR_F, PCR_G, PCR_H, PCR_I, PCR_J, PCR_K;
    uint_16 filler4[1];

    // Pin Assignment Registers
    uint_8 PAR_FBCTL, PAR_BE, PAR_CS, PAR_CANI2C, PAR_IRQ0H, PAR_IRQ0L, PAR_DSPIOWH, PAR_DSPIOWL, PAR_TIMER, PAR_UART2, PAR_UART1, PAR_UART0;
    uint_8 PAR_SDHCH, PAR_SDHCL, PAR_SIMP0H, PAR_SIMP0L, PAR_SSI0H, PAR_SSI0L, PAR_DEBUGH1, PAR_DEBUGH0, PAR_DEBUGL;
    uint_8 filler5[1];
    uint_8 PAR_FEC;
    uint_8 filler6[1];
    
    // Mode Select Control Registers
    uint_8 MSCR_SDRAMC;
    uint_8 filler7[3];
    
    // Slew Rate Control Registers 
    uint_8 SRCR_FB1, SRCR_FB2, SRCR_FB3, SRCR_FB4;
    uint_8 SRCR_DSPIOW, SRCR_CANI2C, SRCR_IRQ0;
    uint_8 SRCR_TIMER, SRCR_UART, SRCR_FEC;
    uint_8 SRCR_SDHC, SRCR_SIMP0, SRCR_SSI0;
    uint_8 filler8[3];
    
    // Miscellaneous UART Registers
    uint_16 URTS_POL; //RTS polarity control register
    uint_16 UCTS_POL; //CTS polarity control register
    uint_16 UTXD_WOM; //Transmitter wired-or mode control register
    uint_32 URXD_WOM; //Receiver wired-or mode control register
    
    // Hysteresis Control Registers
    uint_32 HCR1; //Hysteresis control register 1
    uint_32 HCR0; //Hysteresis control register 2  

}  MCF5441_GPIO_STRUCT, _PTR_ MCF5441_GPIO_STRUCT_PTR;
typedef volatile struct mcf5441_gpio_struct _PTR_ VMCF5441_GPIO_STRUCT_PTR;

// PAR_xx Settings (Two Bit Field)
#define GPIO_00 0
#define ALTERNATE_FC_2_01   1
#define ALTERNATE_FC_1_10   2
#define PRIMARY_FC_11       3
#define FC_MASK             3

//PAR_x Settings (One Bit Field)
#define GPIO_0  0
#define PRIMARY_FC_1    1

// I2C definitions
#define I2C0_SDA    PRIMARY_FC_11
#define I2C0_SCL    PRIMARY_FC_11
#define I2C5_SDA    ALTERNATE_FC_1_10
#define I2C5_SCL    ALTERNATE_FC_1_10
    

#define PAR_CANI2C_PAR_CAN1_RX(x)   ((x) & 0x03)
#define PAR_CANI2C_PAR_CAN1_TX(x)   (((x) & 0x03) << 2)
#define PAR_CANI2C_PAR_I2C0_SDA(x)  (((x) & 0x03) << 4)
#define PAR_CANI2C_PAR_PAR_I2C0_SCL(x)  (((x) & 0x03) << 6)

#define PAR_UARTN_PAR_TXD(x)    ((x) & 0x03)
#define PAR_UARTN_PAR_RXD(x)    (((x) & 0x03) << 2)
#define PAR_UARTN_PAR_RTS(x)    (((x) & 0x03) << 4)
#define PAR_UARTN_PAR_CTS(x)    (((x) & 0x03) << 6)

/*
** MCF5441_PAD_STRUCT
** Pin-Multiplexing and Control (PAD)
** NOTE: THIS STRUCT IS NOT USED IN MQX, USE GPIO STRUCT CONTAINING THESE REGS INSTEAD!
typedef struct mcf5441_pad_struct {
    uint_8 PAR_FBCTL;
    uint_8 PAR_BE;
    uint_8 PAR_CS;
    uint_8 PAR_CANI2C;
    uint_8 PAR_IRQ0H;
    uint_8 PAR_IRQ0L;
    uint_8 PAR_DSPIOWH;
    uint_8 PAR_DSPIOWL;
    uint_8 PAR_TIMER;
    uint_8 PAR_UART2;
    uint_8 PAR_UART1;
    uint_8 PAR_UART0;
    uint_8 PAR_SDHCH;
    uint_8 PAR_SDHCL;
    uint_8 PAR_SIMP0H;
    uint_8 PAR_SIMP0L;
    uint_8 PAR_SSI0H;
    uint_8 PAR_SSI0L;
    uint_8 PAR_DEBUGH1;
    uint_8 PAR_DEBUGH0;
    uint_8 PAR_DEBUGL;
    uint_8 filler0;
    uint_8 PAR_FEC;
    uint_8 filler1;
    uint_8 MSCR_SDRAMC;
    uint_8 filler2[3];
    uint_8 SRCR_FB1;
    uint_8 SRCR_FB2;
    uint_8 SRCR_FB3;
    uint_8 SRCR_FB4;
    uint_8 SRCR_DSPIOW;
    uint_8 SRCR_CANI2C;
    uint_8 SRCR_IRQ0;
    uint_8 SRCR_TIMER;
    uint_8 SRCR_UART;
    uint_8 SRCR_FEC;
    uint_8 SRCR_SDHC;
    uint_8 SRCR_SIMP0;
    uint_8 SRCR_SSI0;
    uint_8 filler3[3];
    uint_16 URTS_POL;
    uint_16 UCTS_POL;
    uint_16 UTXD_WOM;
    uint_8 filler4[2];
    uint_32 URXD_WOM;
    uint_32 HCR1;
    uint_32 HCR0;
} MCF5441_PAD_STRUCT, _PTR_ MCF5441_PAD_STRUCT_PTR;
typedef volatile struct mcf5441_pad_struct _PTR_ VMCF5441_PAD_STRUCT_PTR;
*/

/* Bit definitions and macros for MCF5441_DDRMC_DDR_PHY_RCR_CTRL */
#define MCF5441_DDRMC_DDR_PHY_RCR_CTRL_SL_DL_MODE         (0x00010000)
#define MCF5441_DDRMC_DDR_PHY_RCR_CTRL_FULL_PER           (0x00800000)
#define MCF5441_DDRMC_DDR_PHY_RCR_CTRL_DQS_INT            (0x01000000)
#define MCF5441_DDRMC_DDR_PHY_RCR_CTRL_REF_UPDATE_EN      (0x10000000)
#define MCF5441_DDRMC_DDR_PHY_RCR_CTRL_HW_UPDATED_OFF     (0x20000000)
#define MCF5441_DDRMC_DDR_PHY_RCR_CTRL_RCR_RST            (0x40000000)
#define MCF5441_DDRMC_DDR_PHY_RCR_CTRL_RCR_OFF            (0x80000000)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_PHY_SW_RCR_CTRL */
#define MCF5441_DDRMC_DDR_PHY_SW_RCR_CTRL_SW_INC          (0x00001000)
#define MCF5441_DDRMC_DDR_PHY_SW_RCR_CTRL_SW_ADJ_EN       (0x00002000)
#define MCF5441_DDRMC_DDR_PHY_SW_RCR_CTRL_SW_MODE         (0x00004000)
#define MCF5441_DDRMC_DDR_PHY_SW_RCR_CTRL_RUN_OVR         (0x00008000)
#define MCF5441_DDRMC_DDR_PHY_SW_RCR_CTRL_SW_UPDATE       (0x00010000)
#define MCF5441_DDRMC_DDR_PHY_SW_RCR_CTRL_PD_INCR         (0x40000000)
#define MCF5441_DDRMC_DDR_PHY_SW_RCR_CTRL_LOCK            (0x80000000)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_PHY_RCR_DL */
#define MCF5441_DDRMC_DDR_PHY_RCR_DL_RCR_DL(x)            (((x)&0x00FFFFFF)<<0)
#define MCF5441_DDRMC_DDR_PHY_RCR_DL_RCR_SRC(x)           (((x)&0x0000000F)<<28)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_PHY_MS_OVR_DL */
#define MCF5441_DDRMC_DDR_PHY_MS_OVR_DL_MS_OVR_DL(x)      (((x)&0x0000FFFF)<<0)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_PHY_RCR_DBG */
#define MCF5441_DDRMC_DDR_PHY_RCR_DBG_RD_CLK_ADJ_DL(x)    (((x)&0x000000FF)<<0)
#define MCF5441_DDRMC_DDR_PHY_RCR_DBG_DBG_CTRL(x)         (((x)&0x0000007F)<<8)
#define MCF5441_DDRMC_DDR_PHY_RCR_DBG_DBG_MUX_OUT         (0x00008000)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_PHY_SL0_ADJ_DL */
#define MCF5441_DDRMC_DDR_PHY_SL0_ADJ_DL_SL0_ADJ_DL(x)    (((x)&0x0000007F)<<0)
#define MCF5441_DDRMC_DDR_PHY_SL0_ADJ_DL_SL0ADJ_CMD       (0x80000000)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_PHY_SL1_ADJ_DL */
#define MCF5441_DDRMC_DDR_PHY_SL1_ADJ_DL_SL1_ADJ_DL(x)    (((x)&0x0000007F)<<0)
#define MCF5441_DDRMC_DDR_PHY_SL1_ADJ_DL_SL1ADJ_CMD       (0x80000000)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_PHY_SL2_ADJ_DL */
#define MCF5441_DDRMC_DDR_PHY_SL2_ADJ_DL_SL2_ADJ_DL(x)    (((x)&0x0000007F)<<0)
#define MCF5441_DDRMC_DDR_PHY_SL2_ADJ_DL_SL2ADJ_CMD       (0x80000000)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_PHY_SL3_ADJ_DL */
#define MCF5441_DDRMC_DDR_PHY_SL3_ADJ_DL_SL3_ADJ_DL(x)    (((x)&0x0000007F)<<0)
#define MCF5441_DDRMC_DDR_PHY_SL3_ADJ_DL_SL3ADJ_CMD       (0x80000000)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_PHY_SL4_ADJ_DL */
#define MCF5441_DDRMC_DDR_PHY_SL4_ADJ_DL_SL4_ADJ_DL(x)    (((x)&0x0000007F)<<0)
#define MCF5441_DDRMC_DDR_PHY_SL4_ADJ_DL_SL4ADJ_CMD       (0x80000000)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_PHY_FLIGHT_TIME */
#define MCF5441_DDRMC_DDR_PHY_FLIGHT_TIME_FLIGHT_TIME(x)  (((x)&0x00000007)<<0)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_PHY_PAD_CTRL */
#define MCF5441_DDRMC_DDR_PHY_PAD_CTRL_SPARE_DLY_CTRL(x)  (((x)&0x0000000F)<<0)
#define MCF5441_DDRMC_DDR_PHY_PAD_CTRL_PAD_DEBUG(x)       (((x)&0x000000FF)<<8)
#define MCF5441_DDRMC_DDR_PHY_PAD_CTRL_OFFSET_VALUE(x)    (((x)&0x00000003)<<16)
#define MCF5441_DDRMC_DDR_PHY_PAD_CTRL_PAD_ODT_CS0(x)     (((x)&0x00000003)<<24)
#define MCF5441_DDRMC_DDR_PHY_PAD_CTRL_PAD_ODT_CS1(x)     (((x)&0x00000003)<<26)







/* Bit definitions and macros for MCF5441_DDRMC_DDR_CR02 */
#define MCF5441_DDRMC_DDR_CR02_AREFMODE         (0x1)
#define MCF5441_DDRMC_DDR_CR02_BNKSPT           (0x100)
#define MCF5441_DDRMC_DDR_CR02_BIGEND           (0x10000)
#define MCF5441_DDRMC_DDR_CR02_CCAPEN           (0x1000000)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_CR03 */
#define MCF5441_DDRMC_DDR_CR03_DQSBEN           (0x1000000)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_CR04 */
#define MCF5441_DDRMC_DDR_CR04_DRVDQS           (0x1)
#define MCF5441_DDRMC_DDR_CR04_8BNK             (0x100)
#define MCF5441_DDRMC_DDR_CR04_QKREF            (0x10000)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_CR6 */
#define MCF5441_DDRMC_DDR_CR06_NO_CMD_INIT                    (0x00000001)
#define MCF5441_DDRMC_DDR_CR06_ODT_ADD_TURN_CLK_EN            (0x00000100)
#define MCF5441_DDRMC_DDR_CR06_ODT_ALT_EN                     (0x00010000)
#define MCF5441_DDRMC_DDR_CR06_OUT_OF_RANGE_SOURCE_ID         (0x01000000)


/* Bit definitions and macros for MCF5441_DDRMC_DDR_CR7 */
#define MCF5441_DDRMC_DDR_CR07_PLACEMENT_EN                   (0x00000001)
#define MCF5441_DDRMC_DDR_CR07_PORT_ADDR_PROTECTION_EN        (0x00000100)
#define MCF5441_DDRMC_DDR_CR07_PORT_CMD_ERROR_ID              (0x00010000)
#define MCF5441_DDRMC_DDR_CR07_POWER_DOWN                     (0x01000000)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_CR8 */
#define MCF5441_DDRMC_DDR_CR08_PRIORITY_EN                    (0x00000001)
#define MCF5441_DDRMC_DDR_CR08_PWRUP_SREFRESH_EXIT            (0x00000100)
#define MCF5441_DDRMC_DDR_CR08_RD2RD_TURN                     (0x00010000)
#define MCF5441_DDRMC_DDR_CR08_REDUC                          (0x01000000)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_CR9 */
#define MCF5441_DDRMC_DDR_CR09_REG_DIMM_ENABLE                (0x00000001)
#define MCF5441_DDRMC_DDR_CR09_RW_SAME_EN                     (0x00000100)
#define MCF5441_DDRMC_DDR_CR09_SREFRESH                       (0x00010000)
#define MCF5441_DDRMC_DDR_CR09_START                          (0x01000000)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_CR10 */
#define MCF5441_DDRMC_DDR_CR10_SWAP_EN                       (0x00000001)
#define MCF5441_DDRMC_DDR_CR10_TRAS_LOCKOUT                  (0x00000100)
#define MCF5441_DDRMC_DDR_CR10_TREF_ENABLE                   (0x00010000)
#define MCF5441_DDRMC_DDR_CR10_WRTEINTERP                    (0x01000000)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_CR11 */
#define MCF5441_DDRMC_DDR_CR11_WRITE_MODEREG                 (0x00000001)
#define MCF5441_DDRMC_DDR_CR11_AHB0_FIFO_TYPE_REG(x)         (((x)&0x00000003)<<8)
#define MCF5441_DDRMC_DDR_CR11_AHB0_RANGE_TYPE_0(x)          (((x)&0x00000003)<<16)
#define MCF5441_DDRMC_DDR_CR11_AHB0_RANGE_TYPE_1(x)          (((x)&0x00000003)<<24)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_CR12 */
#define MCF5441_DDRMC_DDR_CR12_AHB1_FIFO_TYPE_REG(x)         (((x)&0x00000003)<<0)
#define MCF5441_DDRMC_DDR_CR12_AHB1_RANGE_TYPE_0(x)          (((x)&0x00000003)<<8)
#define MCF5441_DDRMC_DDR_CR12_AHB1_RANGE_TYPE1(x)           (((x)&0x00000003)<<16)
#define MCF5441_DDRMC_DDR_CR12_CSMAP(x)                      (((x)&0x00000003)<<24)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_CR13 */
#define MCF5441_DDRMC_DDR_CR13_DRAM_CLK_DISABLE(x)           (((x)&0x00000003)<<0)
#define MCF5441_DDRMC_DDR_CR13_LOWPOWER_REFRESH_ENABLE(x)    (((x)&0x00000003)<<8)
#define MCF5441_DDRMC_DDR_CR13_MAX_CS_REG(x)                 (((x)&0x00000003)<<16)
#define MCF5441_DDRMC_DDR_CR13_ODT_RD_MAP_CS0(x)             (((x)&0x00000003)<<24)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_CR14 */
#define MCF5441_DDRMC_DDR_CR14_ODT_RD_MAP_CS1(x)             (((x)&0x00000003)<<0)
#define MCF5441_DDRMC_DDR_CR14_ODT_WR_MAP_CS0(x)             (((x)&0x00000003)<<8)
#define MCF5441_DDRMC_DDR_CR14_ODT_WR_MAP_CS1(x)             (((x)&0x00000003)<<16)
#define MCF5441_DDRMC_DDR_CR14_OUT_OF_RANGE_TYPE(x)          (((x)&0x00000003)<<24)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_CR15 */
#define MCF5441_DDRMC_DDR_CR15_Q_FULLNESS(x)                 (((x)&0x00000003)<<0)
#define MCF5441_DDRMC_DDR_CR15_RTT_0(x)                      (((x)&0x00000003)<<8)
#define MCF5441_DDRMC_DDR_CR15_ADDR_PINS(x)                  (((x)&0x00000007)<<24)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_CR16 */
#define MCF5441_DDRMC_DDR_CR16_AGE_COUNT(x)                  (((x)&0x00000007)<<0)
#define MCF5441_DDRMC_DDR_CR16_CASLAT(x)                     (((x)&0x00000007)<<8)
#define MCF5441_DDRMC_DDR_CR16_CKE_DELAY(x)                  (((x)&0x00000007)<<16)
#define MCF5441_DDRMC_DDR_CR16_COLUMN_SIZE(x)                (((x)&0x00000007)<<24)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_CR17 */
#define MCF5441_DDRMC_DDR_CR17_COMMAND_AGE_COUNT(x)          (((x)&0x00000007)<<0)
#define MCF5441_DDRMC_DDR_CR17_PORT_CMD_ERROR_TYPE(x)        (((x)&0x00000007)<<8)
#define MCF5441_DDRMC_DDR_CR17_TCKE(x)                       (((x)&0x00000007)<<16)
#define MCF5441_DDRMC_DDR_CR17_TDFI_CTRL_DELAY(x)            (((x)&0x0000000F)<<24)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_CR18 */
#define MCF5441_DDRMC_DDR_CR18_TDFI_DRAM_CLK_DISABLE(x)      (((x)&0x00000007)<<0)
#define MCF5441_DDRMC_DDR_CR18_TDFI_DRAM_CLK_ENABLE(x)       (((x)&0x0000000F)<<8)
#define MCF5441_DDRMC_DDR_CR18_TRRD(x)                       (((x)&0x00000007)<<24)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_CR19 */
#define MCF5441_DDRMC_DDR_CR19_TRTP(x)                       (((x)&0x00000007)<<0)
#define MCF5441_DDRMC_DDR_CR19_TWTR(x)                       (((x)&0x0000000F)<<8)
#define MCF5441_DDRMC_DDR_CR19_WRLAT(x)                      (((x)&0x0000000F)<<16)
#define MCF5441_DDRMC_DDR_CR19_APREBIT(x)                    (((x)&0x0000000F)<<24)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_CR20 */
#define MCF5441_DDRMC_DDR_CR20_CASLAT_LIN(x)                 (((x)&0x0000000F)<<0)
#define MCF5441_DDRMC_DDR_CR20_CASLAT_LIN_GATE(x)            (((x)&0x0000000F)<<8)
#define MCF5441_DDRMC_DDR_CR20_INITAREF(x)                   (((x)&0x0000000F)<<16)
#define MCF5441_DDRMC_DDR_CR20_MAX_COL_REG(x)                (((x)&0x0000000F)<<24)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_CR21 */
#define MCF5441_DDRMC_DDR_CR21_TDAL(x)                       (((x)&0x0000001F)<<0)
#define MCF5441_DDRMC_DDR_CR21_TDFI_CTRLUPD_MIN(x)           (((x)&0x0000000F)<<8)
#define MCF5441_DDRMC_DDR_CR21_TDFI_PHY_RDLAT(x)             (((x)&0x0000000F)<<16)
#define MCF5441_DDRMC_DDR_CR21_TDFI_PHY_WRLAT(x)             (((x)&0x0000000F)<<24)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_CR22 */
#define MCF5441_DDRMC_DDR_CR22_TDFI_PHY_WRLAT_BASE(x)        (((x)&0x0000000F)<<0)
#define MCF5441_DDRMC_DDR_CR22_TDFI_RDDATA_EN(x)             (((x)&0x0000000F)<<8)
#define MCF5441_DDRMC_DDR_CR22_TDFI_RDDATA_EN_BASE(x)        (((x)&0x0000000F)<<16)
#define MCF5441_DDRMC_DDR_CR22_TRP(x)                        (((x)&0x0000000F)<<24)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_CR23 */
#define MCF5441_DDRMC_DDR_CR23_TWR_INT(x)                    (((x)&0x0000001F)<<0)
#define MCF5441_DDRMC_DDR_CR23_LOWPOWER_AUTO_ENABLE(x)       (((x)&0x0000001F)<<8)
#define MCF5441_DDRMC_DDR_CR23_LOWPOWERCONTROL(x)            (((x)&0x0000001F)<<16)
#define MCF5441_DDRMC_DDR_CR23_MAX_ROW_REG(x)                (((x)&0x0000001F)<<24)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_CR24 */
#define MCF5441_DDRMC_DDR_CR24_OCD_ADJUST_PDN_CS_0(x)        (((x)&0x0000001F)<<0)
#define MCF5441_DDRMC_DDR_CR24_OCD_ADJUST_PUP_CS_0(x)        (((x)&0x0000001F)<<8)
#define MCF5441_DDRMC_DDR_CR24_TFAW(x)                       (((x)&0x0000001F)<<16)
#define MCF5441_DDRMC_DDR_CR24_TMRD(x)                       (((x)&0x0000001F)<<24)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_CR25 */
#define MCF5441_DDRMC_DDR_CR25_TRC(x)                        (((x)&0x0000001F)<<0)
#define MCF5441_DDRMC_DDR_CR25_DLL_LOCK(x)                   (((x)&0x0000003F)<<8)
#define MCF5441_DDRMC_DDR_CR25_INT_ACK(x)                    (((x)&0x000000FF)<<16)
#define MCF5441_DDRMC_DDR_CR25_TRAS_MIN(x)                   (((x)&0x000000FF)<<24)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_CR26 */
#define MCF5441_DDRMC_DDR_CR26_TRCD_INT(x)                   (((x)&0x000000FF)<<0)
#define MCF5441_DDRMC_DDR_CR26_TRFC(x)                       (((x)&0x000000FF)<<8)
#define MCF5441_DDRMC_DDR_CR26_INT_MASK(x)                   (((x)&0x0000FFFF)<<16)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_CR27 */
#define MCF5441_DDRMC_DDR_CR27_INT_STATUS(x)                 (((x)&0x000001FF)<<0)
#define MCF5441_DDRMC_DDR_CR27_OUT_OF_RANGE_LENGTH(x)        (((x)&0x000003FF)<<16)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_CR28 */
#define MCF5441_DDRMC_DDR_CR28_AHB0_RDCNT(x)                 (((x)&0x000007FF)<<0)
#define MCF5441_DDRMC_DDR_CR28_AHB0_WRCNT(x)                 (((x)&0x000007FF)<<16)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_CR29 */
#define MCF5441_DDRMC_DDR_CR29_AHB1_RDCNT(x)                 (((x)&0x000007FF)<<0)
#define MCF5441_DDRMC_DDR_CR29_AHB1_WRCNT(x)                 (((x)&0x000007FF)<<16)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_CR30 */
#define MCF5441_DDRMC_DDR_CR30_TDFI_CTRLUPD_MAX(x)           (((x)&0x00003FFF)<<0)
#define MCF5441_DDRMC_DDR_CR30_TDFI_PHYUPDRESP(x)            (((x)&0x00003FFF)<<16)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_CR31 */
#define MCF5441_DDRMC_DDR_CR31_TDFI_PHYUPD_TYPE0(x)          (((x)&0x00003FFF)<<0)
#define MCF5441_DDRMC_DDR_CR31_TREF(x)                       (((x)&0x00003FFF)<<16)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_CR32 */
#define MCF5441_DDRMC_DDR_CR32_TREF_INTERVAL(x)              (((x)&0x00003FFF)<<0)
#define MCF5441_DDRMC_DDR_CR32_AHB0_END_ADDR_0(x)            (((x)&0x00007FFF)<<16)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_CR33 */
#define MCF5441_DDRMC_DDR_CR33_AHB0_END_ADDR_1(x)            (((x)&0x00007FFF)<<0)
#define MCF5441_DDRMC_DDR_CR33_AHB0_START_ADDR_0(x)          (((x)&0x00007FFF)<<16)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_CR34 */
#define MCF5441_DDRMC_DDR_CR34_AHB0_START_ADDR_1(x)          (((x)&0x00007FFF)<<0)
#define MCF5441_DDRMC_DDR_CR34_AHB1_END_ADDR_0(x)            (((x)&0x00007FFF)<<16)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_CR35 */
#define MCF5441_DDRMC_DDR_CR35_AHB1_END_ADDR_1(x)            (((x)&0x00007FFF)<<0)
#define MCF5441_DDRMC_DDR_CR35_AHB1_START_ADDR_0(x)          (((x)&0x00007FFF)<<16)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_CR36 */
#define MCF5441_DDRMC_DDR_CR36_AHB1_START_ADDR_1(x)          (((x)&0x00007FFF)<<0)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_CR37 */
#define MCF5441_DDRMC_DDR_CR37_EMRS2_DATA_0(x)               (((x)&0x0000FFFF)<<0)
#define MCF5441_DDRMC_DDR_CR37_EMRS2_DATA_1(x)               (((x)&0x0000FFFF)<<16)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_CR38 */
#define MCF5441_DDRMC_DDR_CR38_LOWPOWER_EXTERNAL_CNT(x)      (((x)&0x0000FFFF)<<16)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_CR39 */
#define MCF5441_DDRMC_DDR_CR39_LOWPOWER_INTERNAL_CNT(x)      (((x)&0x0000FFFF)<<0)
#define MCF5441_DDRMC_DDR_CR39_LOWPOWER_POWER_D0WN_CNT(x)    (((x)&0x0000FFFF)<<16)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_CR40 */
#define MCF5441_DDRMC_DDR_CR40_LOWPOWER_REFRESH_HOLD(x)      (((x)&0x0000FFFF)<<0)
#define MCF5441_DDRMC_DDR_CR40_LOWPOWER_SELF_REFRESH_CNT(x)  (((x)&0x0000FFFF)<<16)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_CR41 */
#define MCF5441_DDRMC_DDR_CR41_TCPD(x)                       (((x)&0x0000FFFF)<<0)
#define MCF5441_DDRMC_DDR_CR41_TDLL(x)                       (((x)&0x0000FFFF)<<16)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_CR42 */
#define MCF5441_DDRMC_DDR_CR42_TPDEX(x)                      (((x)&0x0000FFFF)<<0)
#define MCF5441_DDRMC_DDR_CR42_TRAS_MAX(x)                   (((x)&0x0000FFFF)<<16)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_CR43 */
#define MCF5441_DDRMC_DDR_CR43_TXSNR(x)                      (((x)&0x0000FFFF)<<0)
#define MCF5441_DDRMC_DDR_CR43_TXSR(x)                       (((x)&0x0000FFFF)<<16)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_CR44 */
#define MCF5441_DDRMC_DDR_CR44_VERSION(x)                    (((x)&0x0000FFFF)<<0)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_CR45 */
#define MCF5441_DDRMC_DDR_CR45_TINIT(x)                      (((x)&0x00FFFFFF)<<0)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_CR46 */
#define MCF5441_DDRMC_DDR_CR46_DFT_CTRL_REG(x)               (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_CR47 */
#define MCF5441_DDRMC_DDR_CR47_PAD_CTRL_REG_0(x)             (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_CR48 */
#define MCF5441_DDRMC_DDR_CR48_PHY_CTRL_REG_0_0(x)           (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_CR49 */
#define MCF5441_DDRMC_DDR_CR49_PHY_CTRL_REG_0_1(x)           (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_CR50 */
#define MCF5441_DDRMC_DDR_CR50_PHY_CTRL_REG_1_0(x)           (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_CR51 */
#define MCF5441_DDRMC_DDR_CR51_PHY_CTRL_REG_1_1(x)           (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_CR52 */
#define MCF5441_DDRMC_DDR_CR52_PHY_CTRL_REG_2(x)             (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_CR53 */
#define MCF5441_DDRMC_DDR_CR53_PORT_CMD_ERROR_ADDR(x)        (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_CR54 */
#define MCF5441_DDRMC_DDR_CR54_USER_DEF_REG_0(x)             (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_CR55 */
#define MCF5441_DDRMC_DDR_CR55_OUT_OF_RANGE_ADDR31(x)        (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_CR56 */
#define MCF5441_DDRMC_DDR_CR56_RDLAT_ADJ(x)                  (((x)&0x0000000F)<<0)
#define MCF5441_DDRMC_DDR_CR56_WRLAT_ADJ(x)                  (((x)&0x0000000F)<<8)
#define MCF5441_DDRMC_DDR_CR56_DLL_RST_ADJ_DLY(x)            (((x)&0x000000FF)<<16)
#define MCF5441_DDRMC_DDR_CR56_DRAM_CLASS(x)                 (((x)&0xf) << 24)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_CR57 */
#define MCF5441_DDRMC_DDR_CR57_RDLAT_ADJ(x)                  (((x)&0x0000000F)<<0)
#define MCF5441_DDRMC_DDR_CR57_WRLAT_ADJ(x)                  (((x)&0x0000000F)<<8)
#define MCF5441_DDRMC_DDR_CR57_DLL_RST_ADJ_DLY(x)            (((x)&0x000000FF)<<16)
#define MCF5441_DDRMC_DDR_CR57_TMOD(x)                       (((x)&0x000000FF)<<24)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_CR58 */
#define MCF5441_DDRMC_DDR_CR58_DLL_RST_DELAY(x)              (((x)&0x0000FFFF)<<0)
#define MCF5441_DDRMC_DDR_CR58_EMRS1_DATA_0(x)               (((x)&0x0000FFFF)<<16)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_CR59 */
#define MCF5441_DDRMC_DDR_CR59_EMRS1_DATA_1(x)               (((x)&0x0000FFFF)<<0)
#define MCF5441_DDRMC_DDR_CR59_EMRS3_DATA_0(x)               (((x)&0x0000FFFF)<<16)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_CR60 */
#define MCF5441_DDRMC_DDR_CR60_EMRS3_DATA_1(x)               (((x)&0x0000FFFF)<<0)
#define MCF5441_DDRMC_DDR_CR60_MRS_DATA_0(x)                 (((x)&0x0000FFFF)<<16)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_CR61 */
#define MCF5441_DDRMC_DDR_CR61_MRS_DATA_1(x)                 (((x)&0x0000FFFF)<<0)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_CR62 */
#define MCF5441_DDRMC_DDR_CR62_DLL_CTRL_REG_0_0(x)           (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF5441_DDRMC_DDR_CR63 */
#define MCF5441_DDRMC_DDR_CR63_DLL_CTRL_REG_0_1(x)           (((x)&0xFFFFFFFF)<<0)


/*
** MCF5441_DDRMC_STRUCT
** 
*/
typedef struct mcf5441_ddrmc_struct {
    uint_32 DDR_CR00;
    uint_32 DDR_CR01;
    uint_32 DDR_CR02;
    uint_32 DDR_CR03;
    uint_32 DDR_CR04;
    uint_32 DDR_CR05;
    uint_32 DDR_CR06;
    uint_32 DDR_CR07;
    uint_32 DDR_CR08;
    uint_32 DDR_CR09;
    uint_32 DDR_CR10;
    uint_32 DDR_CR11;
    uint_32 DDR_CR12;
    uint_32 DDR_CR13;
    uint_32 DDR_CR14;
    uint_32 DDR_CR15;
    uint_32 DDR_CR16;
    uint_32 DDR_CR17;
    uint_32 DDR_CR18;
    uint_32 DDR_CR19;
    uint_32 DDR_CR20;
    uint_32 DDR_CR21;
    uint_32 DDR_CR22;
    uint_32 DDR_CR23;
    uint_32 DDR_CR24;
    uint_32 DDR_CR25;
    uint_32 DDR_CR26;
    uint_32 DDR_CR27;
    uint_32 DDR_CR28;
    uint_32 DDR_CR29;
    uint_32 DDR_CR30;
    uint_32 DDR_CR31;
    uint_32 DDR_CR32;
    uint_32 DDR_CR33;
    uint_32 DDR_CR34;
    uint_32 DDR_CR35;
    uint_32 DDR_CR36;
    uint_32 DDR_CR37;
    uint_32 DDR_CR38;
    uint_32 DDR_CR39;
    uint_32 DDR_CR40;
    uint_32 DDR_CR41;
    uint_32 DDR_CR42;
    uint_32 DDR_CR43;
    uint_32 DDR_CR44;
    uint_32 DDR_CR45;
    uint_32 filler0[7];
    uint_32 DDR_CR53;
    uint_32 filler1;
    uint_32 DDR_CR55;
    uint_32 DDR_CR56;
    uint_32 DDR_CR57;
    uint_32 DDR_CR58;
    uint_32 DDR_CR59;
    uint_32 DDR_CR60;
    uint_32 DDR_CR61;//    uint_32 filler2;

    uint_32 filler2[34];

    // RCR MODULE (DDR_PHY)
    uint_32 DDR_PHY_RCR_CTRL;    
    uint_32 DDR_PHY_SW_RCR_CTRL; 
    uint_32 DDR_PHY_RCR_DL;      
    uint_32 DDR_PHY_MS_OVR_DL;   
    uint_32 DDR_PHY_RCR_DBG;     
    uint_32 DDR_PHY_SL0_ADJ_DL;  
    uint_32 DDR_PHY_SL1_ADJ_DL;  
    uint_32 DDR_PHY_SL2_ADJ_DL;  
    uint_32 DDR_PHY_SL3_ADJ_DL;  
    uint_32 DDR_PHY_SL4_ADJ_DL;  
    uint_32 DDR_PHY_FLIGHT_TIME; 
    uint_32 DDR_PHY_PAD_CTRL;    
} MCF5441_DDRMC_STRUCT, _PTR_ MCF5441_DDRMC_STRUCT_PTR;
typedef volatile struct mcf5441_ddrmc_struct _PTR_ VMCF5441_DDRMC_STRUCT_PTR;

/* Bit definitions and macros for MCF5441_EDMA_EDMA_CR */
#define MCF5441_EDMA_EDMA_CR_EDBG                (0x2)
#define MCF5441_EDMA_EDMA_CR_ERCA                (0x4)
#define MCF5441_EDMA_EDMA_CR_ERGA                (0x8)
#define MCF5441_EDMA_EDMA_CR_HOE                 (0x10)
#define MCF5441_EDMA_EDMA_CR_HALT                (0x20)
#define MCF5441_EDMA_EDMA_CR_CLM                 (0x40)
#define MCF5441_EDMA_EDMA_CR_EMLM                (0x80)
#define MCF5441_EDMA_EDMA_CR_GRP0PRI(x)          (((x)&0x3)<<0x8)
#define MCF5441_EDMA_EDMA_CR_GRP1PRI(x)          (((x)&0x3)<<0xA)
#define MCF5441_EDMA_EDMA_CR_GRP2PRI(x)          (((x)&0x3)<<0xC)
#define MCF5441_EDMA_EDMA_CR_GRP3PRI(x)          (((x)&0x3)<<0xE)
#define MCF5441_EDMA_EDMA_CR_ECX                 (0x10000)
#define MCF5441_EDMA_EDMA_CR_CX                  (0x20000)

/* Bit definitions and macros for MCF5441_EDMA_EDMA_ES */
#define MCF5441_EDMA_EDMA_ES_DBE                 (0x1)
#define MCF5441_EDMA_EDMA_ES_SBE                 (0x2)
#define MCF5441_EDMA_EDMA_ES_SGE                 (0x4)
#define MCF5441_EDMA_EDMA_ES_NCE                 (0x8)
#define MCF5441_EDMA_EDMA_ES_DOE                 (0x10)
#define MCF5441_EDMA_EDMA_ES_DAE                 (0x20)
#define MCF5441_EDMA_EDMA_ES_SOE                 (0x40)
#define MCF5441_EDMA_EDMA_ES_SAE                 (0x80)
#define MCF5441_EDMA_EDMA_ES_ERRCHN(x)           (((x)&0x3F)<<0x8)
#define MCF5441_EDMA_EDMA_ES_CPE                 (0x4000)
#define MCF5441_EDMA_EDMA_ES_GPE                 (0x8000)
#define MCF5441_EDMA_EDMA_ES_ECX                 (0x10000)
#define MCF5441_EDMA_EDMA_ES_VLD                 (0x80000000)

/* Bit definitions and macros for MCF5441_EDMA_EDMA_ERQH */
#define MCF5441_EDMA_EDMA_ERQH_ERQ32             (0x1)
#define MCF5441_EDMA_EDMA_ERQH_ERQ33             (0x2)
#define MCF5441_EDMA_EDMA_ERQH_ERQ34             (0x4)
#define MCF5441_EDMA_EDMA_ERQH_ERQ35             (0x8)
#define MCF5441_EDMA_EDMA_ERQH_ERQ36             (0x10)
#define MCF5441_EDMA_EDMA_ERQH_ERQ37             (0x20)
#define MCF5441_EDMA_EDMA_ERQH_ERQ38             (0x40)
#define MCF5441_EDMA_EDMA_ERQH_ERQ39             (0x80)
#define MCF5441_EDMA_EDMA_ERQH_ERQ40             (0x100)
#define MCF5441_EDMA_EDMA_ERQH_ERQ41             (0x200)
#define MCF5441_EDMA_EDMA_ERQH_ERQ42             (0x400)
#define MCF5441_EDMA_EDMA_ERQH_ERQ43             (0x800)
#define MCF5441_EDMA_EDMA_ERQH_ERQ44             (0x1000)
#define MCF5441_EDMA_EDMA_ERQH_ERQ45             (0x2000)
#define MCF5441_EDMA_EDMA_ERQH_ERQ46             (0x4000)
#define MCF5441_EDMA_EDMA_ERQH_ERQ47             (0x8000)
#define MCF5441_EDMA_EDMA_ERQH_ERQ48             (0x10000)
#define MCF5441_EDMA_EDMA_ERQH_ERQ49             (0x20000)
#define MCF5441_EDMA_EDMA_ERQH_ERQ50             (0x40000)
#define MCF5441_EDMA_EDMA_ERQH_ERQ51             (0x80000)
#define MCF5441_EDMA_EDMA_ERQH_ERQ52             (0x100000)
#define MCF5441_EDMA_EDMA_ERQH_ERQ53             (0x200000)
#define MCF5441_EDMA_EDMA_ERQH_ERQ54             (0x400000)
#define MCF5441_EDMA_EDMA_ERQH_ERQ55             (0x800000)
#define MCF5441_EDMA_EDMA_ERQH_ERQ56             (0x1000000)
#define MCF5441_EDMA_EDMA_ERQH_ERQ57             (0x2000000)
#define MCF5441_EDMA_EDMA_ERQH_ERQ58             (0x4000000)
#define MCF5441_EDMA_EDMA_ERQH_ERQ59             (0x8000000)
#define MCF5441_EDMA_EDMA_ERQH_ERQ60             (0x10000000)
#define MCF5441_EDMA_EDMA_ERQH_ERQ61             (0x20000000)
#define MCF5441_EDMA_EDMA_ERQH_ERQ62             (0x40000000)
#define MCF5441_EDMA_EDMA_ERQH_ERQ63             (0x80000000)

/* Bit definitions and macros for MCF5441_EDMA_EDMA_ERQL */
#define MCF5441_EDMA_EDMA_ERQL_ERQ0              (0x1)
#define MCF5441_EDMA_EDMA_ERQL_ERQ1              (0x2)
#define MCF5441_EDMA_EDMA_ERQL_ERQ2              (0x4)
#define MCF5441_EDMA_EDMA_ERQL_ERQ3              (0x8)
#define MCF5441_EDMA_EDMA_ERQL_ERQ4              (0x10)
#define MCF5441_EDMA_EDMA_ERQL_ERQ5              (0x20)
#define MCF5441_EDMA_EDMA_ERQL_ERQ6              (0x40)
#define MCF5441_EDMA_EDMA_ERQL_ERQ7              (0x80)
#define MCF5441_EDMA_EDMA_ERQL_ERQ8              (0x100)
#define MCF5441_EDMA_EDMA_ERQL_ERQ9              (0x200)
#define MCF5441_EDMA_EDMA_ERQL_ERQ10             (0x400)
#define MCF5441_EDMA_EDMA_ERQL_ERQ11             (0x800)
#define MCF5441_EDMA_EDMA_ERQL_ERQ12             (0x1000)
#define MCF5441_EDMA_EDMA_ERQL_ERQ13             (0x2000)
#define MCF5441_EDMA_EDMA_ERQL_ERQ14             (0x4000)
#define MCF5441_EDMA_EDMA_ERQL_ERQ15             (0x8000)
#define MCF5441_EDMA_EDMA_ERQL_ERQ16             (0x10000)
#define MCF5441_EDMA_EDMA_ERQL_ERQ17             (0x20000)
#define MCF5441_EDMA_EDMA_ERQL_ERQ18             (0x40000)
#define MCF5441_EDMA_EDMA_ERQL_ERQ19             (0x80000)
#define MCF5441_EDMA_EDMA_ERQL_ERQ20             (0x100000)
#define MCF5441_EDMA_EDMA_ERQL_ERQ21             (0x200000)
#define MCF5441_EDMA_EDMA_ERQL_ERQ22             (0x400000)
#define MCF5441_EDMA_EDMA_ERQL_ERQ23             (0x800000)
#define MCF5441_EDMA_EDMA_ERQL_ERQ24             (0x1000000)
#define MCF5441_EDMA_EDMA_ERQL_ERQ25             (0x2000000)
#define MCF5441_EDMA_EDMA_ERQL_ERQ26             (0x4000000)
#define MCF5441_EDMA_EDMA_ERQL_ERQ27             (0x8000000)
#define MCF5441_EDMA_EDMA_ERQL_ERQ28             (0x10000000)
#define MCF5441_EDMA_EDMA_ERQL_ERQ29             (0x20000000)
#define MCF5441_EDMA_EDMA_ERQL_ERQ30             (0x40000000)
#define MCF5441_EDMA_EDMA_ERQL_ERQ31             (0x80000000)

/* Bit definitions and macros for MCF5441_EDMA_EDMA_EEIH */
#define MCF5441_EDMA_EDMA_EEIH_EEI32             (0x1)
#define MCF5441_EDMA_EDMA_EEIH_EEI33             (0x2)
#define MCF5441_EDMA_EDMA_EEIH_EEI34             (0x4)
#define MCF5441_EDMA_EDMA_EEIH_EEI35             (0x8)
#define MCF5441_EDMA_EDMA_EEIH_EEI36             (0x10)
#define MCF5441_EDMA_EDMA_EEIH_EEI37             (0x20)
#define MCF5441_EDMA_EDMA_EEIH_EEI38             (0x40)
#define MCF5441_EDMA_EDMA_EEIH_EEI39             (0x80)
#define MCF5441_EDMA_EDMA_EEIH_EEI40             (0x100)
#define MCF5441_EDMA_EDMA_EEIH_EEI41             (0x200)
#define MCF5441_EDMA_EDMA_EEIH_EEI42             (0x400)
#define MCF5441_EDMA_EDMA_EEIH_EEI43             (0x800)
#define MCF5441_EDMA_EDMA_EEIH_EEI44             (0x1000)
#define MCF5441_EDMA_EDMA_EEIH_EEI45             (0x2000)
#define MCF5441_EDMA_EDMA_EEIH_EEI46             (0x4000)
#define MCF5441_EDMA_EDMA_EEIH_EEI47             (0x8000)
#define MCF5441_EDMA_EDMA_EEIH_EEI48             (0x10000)
#define MCF5441_EDMA_EDMA_EEIH_EEI49             (0x20000)
#define MCF5441_EDMA_EDMA_EEIH_EEI50             (0x40000)
#define MCF5441_EDMA_EDMA_EEIH_EEI51             (0x80000)
#define MCF5441_EDMA_EDMA_EEIH_EEI52             (0x100000)
#define MCF5441_EDMA_EDMA_EEIH_EEI53             (0x200000)
#define MCF5441_EDMA_EDMA_EEIH_EEI54             (0x400000)
#define MCF5441_EDMA_EDMA_EEIH_EEI55             (0x800000)
#define MCF5441_EDMA_EDMA_EEIH_EEI56             (0x1000000)
#define MCF5441_EDMA_EDMA_EEIH_EEI57             (0x2000000)
#define MCF5441_EDMA_EDMA_EEIH_EEI58             (0x4000000)
#define MCF5441_EDMA_EDMA_EEIH_EEI59             (0x8000000)
#define MCF5441_EDMA_EDMA_EEIH_EEI60             (0x10000000)
#define MCF5441_EDMA_EDMA_EEIH_EEI61             (0x20000000)
#define MCF5441_EDMA_EDMA_EEIH_EEI62             (0x40000000)
#define MCF5441_EDMA_EDMA_EEIH_EEI63             (0x80000000)

/* Bit definitions and macros for MCF5441_EDMA_EDMA_EEIL */
#define MCF5441_EDMA_EDMA_EEIL_EEI0              (0x1)
#define MCF5441_EDMA_EDMA_EEIL_EEI1              (0x2)
#define MCF5441_EDMA_EDMA_EEIL_EEI2              (0x4)
#define MCF5441_EDMA_EDMA_EEIL_EEI3              (0x8)
#define MCF5441_EDMA_EDMA_EEIL_EEI4              (0x10)
#define MCF5441_EDMA_EDMA_EEIL_EEI5              (0x20)
#define MCF5441_EDMA_EDMA_EEIL_EEI6              (0x40)
#define MCF5441_EDMA_EDMA_EEIL_EEI7              (0x80)
#define MCF5441_EDMA_EDMA_EEIL_EEI8              (0x100)
#define MCF5441_EDMA_EDMA_EEIL_EEI9              (0x200)
#define MCF5441_EDMA_EDMA_EEIL_EEI10             (0x400)
#define MCF5441_EDMA_EDMA_EEIL_EEI11             (0x800)
#define MCF5441_EDMA_EDMA_EEIL_EEI12             (0x1000)
#define MCF5441_EDMA_EDMA_EEIL_EEI13             (0x2000)
#define MCF5441_EDMA_EDMA_EEIL_EEI14             (0x4000)
#define MCF5441_EDMA_EDMA_EEIL_EEI15             (0x8000)
#define MCF5441_EDMA_EDMA_EEIL_EEI16             (0x10000)
#define MCF5441_EDMA_EDMA_EEIL_EEI17             (0x20000)
#define MCF5441_EDMA_EDMA_EEIL_EEI18             (0x40000)
#define MCF5441_EDMA_EDMA_EEIL_EEI19             (0x80000)
#define MCF5441_EDMA_EDMA_EEIL_EEI20             (0x100000)
#define MCF5441_EDMA_EDMA_EEIL_EEI21             (0x200000)
#define MCF5441_EDMA_EDMA_EEIL_EEI22             (0x400000)
#define MCF5441_EDMA_EDMA_EEIL_EEI23             (0x800000)
#define MCF5441_EDMA_EDMA_EEIL_EEI24             (0x1000000)
#define MCF5441_EDMA_EDMA_EEIL_EEI25             (0x2000000)
#define MCF5441_EDMA_EDMA_EEIL_EEI26             (0x4000000)
#define MCF5441_EDMA_EDMA_EEIL_EEI27             (0x8000000)
#define MCF5441_EDMA_EDMA_EEIL_EEI28             (0x10000000)
#define MCF5441_EDMA_EDMA_EEIL_EEI29             (0x20000000)
#define MCF5441_EDMA_EDMA_EEIL_EEI30             (0x40000000)
#define MCF5441_EDMA_EDMA_EEIL_EEI31             (0x80000000)

/* Bit definitions and macros for MCF5441_EDMA_EDMA_SERQ */
#define MCF5441_EDMA_EDMA_SERQ_SERQ(x)           (((x)&0x3F)<<0)
#define MCF5441_EDMA_EDMA_SERQ_SAER              (0x40)
#define MCF5441_EDMA_EDMA_SERQ_NOP               (0x80)

/* Bit definitions and macros for MCF5441_EDMA_EDMA_CERQ */
#define MCF5441_EDMA_EDMA_CERQ_CERQ(x)           (((x)&0x3F)<<0)
#define MCF5441_EDMA_EDMA_CERQ_CAER              (0x40)
#define MCF5441_EDMA_EDMA_CERQ_NOP               (0x80)

/* Bit definitions and macros for MCF5441_EDMA_EDMA_SEEI */
#define MCF5441_EDMA_EDMA_SEEI_SEEI(x)           (((x)&0x3F)<<0)
#define MCF5441_EDMA_EDMA_SEEI_SAEE              (0x40)
#define MCF5441_EDMA_EDMA_SEEI_NOP               (0x80)

/* Bit definitions and macros for MCF5441_EDMA_EDMA_CEEI */
#define MCF5441_EDMA_EDMA_CEEI_CEEI(x)           (((x)&0x3F)<<0)
#define MCF5441_EDMA_EDMA_CEEI_CAEE              (0x40)
#define MCF5441_EDMA_EDMA_CEEI_NOP               (0x80)

/* Bit definitions and macros for MCF5441_EDMA_EDMA_CINT */
#define MCF5441_EDMA_EDMA_CINT_CINT(x)           (((x)&0x3F)<<0)
#define MCF5441_EDMA_EDMA_CINT_CAIR              (0x40)
#define MCF5441_EDMA_EDMA_CINT_NOP               (0x80)

/* Bit definitions and macros for MCF5441_EDMA_EDMA_CERR */
#define MCF5441_EDMA_EDMA_CERR_CERR(x)           (((x)&0x3F)<<0)
#define MCF5441_EDMA_EDMA_CERR_CAEI              (0x40)
#define MCF5441_EDMA_EDMA_CERR_NOP               (0x80)

/* Bit definitions and macros for MCF5441_EDMA_EDMA_SSRT */
#define MCF5441_EDMA_EDMA_SSRT_SSRT(x)           (((x)&0x3F)<<0)
#define MCF5441_EDMA_EDMA_SSRT_SAST              (0x40)
#define MCF5441_EDMA_EDMA_SSRT_NOP               (0x80)

/* Bit definitions and macros for MCF5441_EDMA_EDMA_CDNE */
#define MCF5441_EDMA_EDMA_CDNE_CDNE(x)           (((x)&0x3F)<<0)
#define MCF5441_EDMA_EDMA_CDNE_CADN              (0x40)
#define MCF5441_EDMA_EDMA_CDNE_NOP               (0x80)

/* Bit definitions and macros for MCF5441_EDMA_EDMA_INTH */
#define MCF5441_EDMA_EDMA_INTH_INT32             (0x1)
#define MCF5441_EDMA_EDMA_INTH_INT33             (0x2)
#define MCF5441_EDMA_EDMA_INTH_INT34             (0x4)
#define MCF5441_EDMA_EDMA_INTH_INT35             (0x8)
#define MCF5441_EDMA_EDMA_INTH_INT36             (0x10)
#define MCF5441_EDMA_EDMA_INTH_INT37             (0x20)
#define MCF5441_EDMA_EDMA_INTH_INT38             (0x40)
#define MCF5441_EDMA_EDMA_INTH_INT39             (0x80)
#define MCF5441_EDMA_EDMA_INTH_INT40             (0x100)
#define MCF5441_EDMA_EDMA_INTH_INT41             (0x200)
#define MCF5441_EDMA_EDMA_INTH_INT42             (0x400)
#define MCF5441_EDMA_EDMA_INTH_INT43             (0x800)
#define MCF5441_EDMA_EDMA_INTH_INT44             (0x1000)
#define MCF5441_EDMA_EDMA_INTH_INT45             (0x2000)
#define MCF5441_EDMA_EDMA_INTH_INT46             (0x4000)
#define MCF5441_EDMA_EDMA_INTH_INT47             (0x8000)
#define MCF5441_EDMA_EDMA_INTH_INT48             (0x10000)
#define MCF5441_EDMA_EDMA_INTH_INT49             (0x20000)
#define MCF5441_EDMA_EDMA_INTH_INT50             (0x40000)
#define MCF5441_EDMA_EDMA_INTH_INT51             (0x80000)
#define MCF5441_EDMA_EDMA_INTH_INT52             (0x100000)
#define MCF5441_EDMA_EDMA_INTH_INT53             (0x200000)
#define MCF5441_EDMA_EDMA_INTH_INT54             (0x400000)
#define MCF5441_EDMA_EDMA_INTH_INT55             (0x800000)
#define MCF5441_EDMA_EDMA_INTH_INT56             (0x1000000)
#define MCF5441_EDMA_EDMA_INTH_INT57             (0x2000000)
#define MCF5441_EDMA_EDMA_INTH_INT58             (0x4000000)
#define MCF5441_EDMA_EDMA_INTH_INT59             (0x8000000)
#define MCF5441_EDMA_EDMA_INTH_INT60             (0x10000000)
#define MCF5441_EDMA_EDMA_INTH_INT61             (0x20000000)
#define MCF5441_EDMA_EDMA_INTH_INT62             (0x40000000)
#define MCF5441_EDMA_EDMA_INTH_INT63             (0x80000000)

/* Bit definitions and macros for MCF5441_EDMA_EDMA_INTL */
#define MCF5441_EDMA_EDMA_INTL_INT0              (0x1)
#define MCF5441_EDMA_EDMA_INTL_INT1              (0x2)
#define MCF5441_EDMA_EDMA_INTL_INT2              (0x4)
#define MCF5441_EDMA_EDMA_INTL_INT3              (0x8)
#define MCF5441_EDMA_EDMA_INTL_INT4              (0x10)
#define MCF5441_EDMA_EDMA_INTL_INT5              (0x20)
#define MCF5441_EDMA_EDMA_INTL_INT6              (0x40)
#define MCF5441_EDMA_EDMA_INTL_INT7              (0x80)
#define MCF5441_EDMA_EDMA_INTL_INT8              (0x100)
#define MCF5441_EDMA_EDMA_INTL_INT9              (0x200)
#define MCF5441_EDMA_EDMA_INTL_INT10             (0x400)
#define MCF5441_EDMA_EDMA_INTL_INT11             (0x800)
#define MCF5441_EDMA_EDMA_INTL_INT12             (0x1000)
#define MCF5441_EDMA_EDMA_INTL_INT13             (0x2000)
#define MCF5441_EDMA_EDMA_INTL_INT14             (0x4000)
#define MCF5441_EDMA_EDMA_INTL_INT15             (0x8000)
#define MCF5441_EDMA_EDMA_INTL_INT16             (0x10000)
#define MCF5441_EDMA_EDMA_INTL_INT17             (0x20000)
#define MCF5441_EDMA_EDMA_INTL_INT18             (0x40000)
#define MCF5441_EDMA_EDMA_INTL_INT19             (0x80000)
#define MCF5441_EDMA_EDMA_INTL_INT20             (0x100000)
#define MCF5441_EDMA_EDMA_INTL_INT21             (0x200000)
#define MCF5441_EDMA_EDMA_INTL_INT22             (0x400000)
#define MCF5441_EDMA_EDMA_INTL_INT23             (0x800000)
#define MCF5441_EDMA_EDMA_INTL_INT24             (0x1000000)
#define MCF5441_EDMA_EDMA_INTL_INT25             (0x2000000)
#define MCF5441_EDMA_EDMA_INTL_INT26             (0x4000000)
#define MCF5441_EDMA_EDMA_INTL_INT27             (0x8000000)
#define MCF5441_EDMA_EDMA_INTL_INT28             (0x10000000)
#define MCF5441_EDMA_EDMA_INTL_INT29             (0x20000000)
#define MCF5441_EDMA_EDMA_INTL_INT30             (0x40000000)
#define MCF5441_EDMA_EDMA_INTL_INT31             (0x80000000)

/* Bit definitions and macros for MCF5441_EDMA_EDMA_ERRH */
#define MCF5441_EDMA_EDMA_ERRH_ERR32             (0x1)
#define MCF5441_EDMA_EDMA_ERRH_ERR33             (0x2)
#define MCF5441_EDMA_EDMA_ERRH_ERR34             (0x4)
#define MCF5441_EDMA_EDMA_ERRH_ERR35             (0x8)
#define MCF5441_EDMA_EDMA_ERRH_ERR36             (0x10)
#define MCF5441_EDMA_EDMA_ERRH_ERR37             (0x20)
#define MCF5441_EDMA_EDMA_ERRH_ERR38             (0x40)
#define MCF5441_EDMA_EDMA_ERRH_ERR39             (0x80)
#define MCF5441_EDMA_EDMA_ERRH_ERR40             (0x100)
#define MCF5441_EDMA_EDMA_ERRH_ERR41             (0x200)
#define MCF5441_EDMA_EDMA_ERRH_ERR42             (0x400)
#define MCF5441_EDMA_EDMA_ERRH_ERR43             (0x800)
#define MCF5441_EDMA_EDMA_ERRH_ERR44             (0x1000)
#define MCF5441_EDMA_EDMA_ERRH_ERR45             (0x2000)
#define MCF5441_EDMA_EDMA_ERRH_ERR46             (0x4000)
#define MCF5441_EDMA_EDMA_ERRH_ERR47             (0x8000)
#define MCF5441_EDMA_EDMA_ERRH_ERR48             (0x10000)
#define MCF5441_EDMA_EDMA_ERRH_ERR49             (0x20000)
#define MCF5441_EDMA_EDMA_ERRH_ERR50             (0x40000)
#define MCF5441_EDMA_EDMA_ERRH_ERR51             (0x80000)
#define MCF5441_EDMA_EDMA_ERRH_ERR52             (0x100000)
#define MCF5441_EDMA_EDMA_ERRH_ERR53             (0x200000)
#define MCF5441_EDMA_EDMA_ERRH_ERR54             (0x400000)
#define MCF5441_EDMA_EDMA_ERRH_ERR55             (0x800000)
#define MCF5441_EDMA_EDMA_ERRH_ERR56             (0x1000000)
#define MCF5441_EDMA_EDMA_ERRH_ERR57             (0x2000000)
#define MCF5441_EDMA_EDMA_ERRH_ERR58             (0x4000000)
#define MCF5441_EDMA_EDMA_ERRH_ERR59             (0x8000000)
#define MCF5441_EDMA_EDMA_ERRH_ERR60             (0x10000000)
#define MCF5441_EDMA_EDMA_ERRH_ERR61             (0x20000000)
#define MCF5441_EDMA_EDMA_ERRH_ERR62             (0x40000000)
#define MCF5441_EDMA_EDMA_ERRH_ERR63             (0x80000000)

/* Bit definitions and macros for MCF5441_EDMA_EDMA_ERRL */
#define MCF5441_EDMA_EDMA_ERRL_ERR0              (0x1)
#define MCF5441_EDMA_EDMA_ERRL_ERR1              (0x2)
#define MCF5441_EDMA_EDMA_ERRL_ERR2              (0x4)
#define MCF5441_EDMA_EDMA_ERRL_ERR3              (0x8)
#define MCF5441_EDMA_EDMA_ERRL_ERR4              (0x10)
#define MCF5441_EDMA_EDMA_ERRL_ERR5              (0x20)
#define MCF5441_EDMA_EDMA_ERRL_ERR6              (0x40)
#define MCF5441_EDMA_EDMA_ERRL_ERR7              (0x80)
#define MCF5441_EDMA_EDMA_ERRL_ERR8              (0x100)
#define MCF5441_EDMA_EDMA_ERRL_ERR9              (0x200)
#define MCF5441_EDMA_EDMA_ERRL_ERR10             (0x400)
#define MCF5441_EDMA_EDMA_ERRL_ERR11             (0x800)
#define MCF5441_EDMA_EDMA_ERRL_ERR12             (0x1000)
#define MCF5441_EDMA_EDMA_ERRL_ERR13             (0x2000)
#define MCF5441_EDMA_EDMA_ERRL_ERR14             (0x4000)
#define MCF5441_EDMA_EDMA_ERRL_ERR15             (0x8000)
#define MCF5441_EDMA_EDMA_ERRL_ERR16             (0x10000)
#define MCF5441_EDMA_EDMA_ERRL_ERR17             (0x20000)
#define MCF5441_EDMA_EDMA_ERRL_ERR18             (0x40000)
#define MCF5441_EDMA_EDMA_ERRL_ERR19             (0x80000)
#define MCF5441_EDMA_EDMA_ERRL_ERR20             (0x100000)
#define MCF5441_EDMA_EDMA_ERRL_ERR21             (0x200000)
#define MCF5441_EDMA_EDMA_ERRL_ERR22             (0x400000)
#define MCF5441_EDMA_EDMA_ERRL_ERR23             (0x800000)
#define MCF5441_EDMA_EDMA_ERRL_ERR24             (0x1000000)
#define MCF5441_EDMA_EDMA_ERRL_ERR25             (0x2000000)
#define MCF5441_EDMA_EDMA_ERRL_ERR26             (0x4000000)
#define MCF5441_EDMA_EDMA_ERRL_ERR27             (0x8000000)
#define MCF5441_EDMA_EDMA_ERRL_ERR28             (0x10000000)
#define MCF5441_EDMA_EDMA_ERRL_ERR29             (0x20000000)
#define MCF5441_EDMA_EDMA_ERRL_ERR30             (0x40000000)
#define MCF5441_EDMA_EDMA_ERRL_ERR31             (0x80000000)

/* Bit definitions and macros for MCF5441_EDMA_EDMA_HRSH */
#define MCF5441_EDMA_EDMA_HRSH_HRS32             (0x1)
#define MCF5441_EDMA_EDMA_HRSH_HRS33             (0x2)
#define MCF5441_EDMA_EDMA_HRSH_HRS34             (0x4)
#define MCF5441_EDMA_EDMA_HRSH_HRS35             (0x8)
#define MCF5441_EDMA_EDMA_HRSH_HRS36             (0x10)
#define MCF5441_EDMA_EDMA_HRSH_HRS37             (0x20)
#define MCF5441_EDMA_EDMA_HRSH_HRS38             (0x40)
#define MCF5441_EDMA_EDMA_HRSH_HRS39             (0x80)
#define MCF5441_EDMA_EDMA_HRSH_HRS40             (0x100)
#define MCF5441_EDMA_EDMA_HRSH_HRS41             (0x200)
#define MCF5441_EDMA_EDMA_HRSH_HRS42             (0x400)
#define MCF5441_EDMA_EDMA_HRSH_HRS43             (0x800)
#define MCF5441_EDMA_EDMA_HRSH_HRS44             (0x1000)
#define MCF5441_EDMA_EDMA_HRSH_HRS45             (0x2000)
#define MCF5441_EDMA_EDMA_HRSH_HRS46             (0x4000)
#define MCF5441_EDMA_EDMA_HRSH_HRS47             (0x8000)
#define MCF5441_EDMA_EDMA_HRSH_HRS48             (0x10000)
#define MCF5441_EDMA_EDMA_HRSH_HRS49             (0x20000)
#define MCF5441_EDMA_EDMA_HRSH_HRS50             (0x40000)
#define MCF5441_EDMA_EDMA_HRSH_HRS51             (0x80000)
#define MCF5441_EDMA_EDMA_HRSH_HRS52             (0x100000)
#define MCF5441_EDMA_EDMA_HRSH_HRS53             (0x200000)
#define MCF5441_EDMA_EDMA_HRSH_HRS54             (0x400000)
#define MCF5441_EDMA_EDMA_HRSH_HRS55             (0x800000)
#define MCF5441_EDMA_EDMA_HRSH_HRS56             (0x1000000)
#define MCF5441_EDMA_EDMA_HRSH_HRS57             (0x2000000)
#define MCF5441_EDMA_EDMA_HRSH_HRS58             (0x4000000)
#define MCF5441_EDMA_EDMA_HRSH_HRS59             (0x8000000)
#define MCF5441_EDMA_EDMA_HRSH_HRS60             (0x10000000)
#define MCF5441_EDMA_EDMA_HRSH_HRS61             (0x20000000)
#define MCF5441_EDMA_EDMA_HRSH_HRS62             (0x40000000)
#define MCF5441_EDMA_EDMA_HRSH_HRS63             (0x80000000)

/* Bit definitions and macros for MCF5441_EDMA_EDMA_HRSL */
#define MCF5441_EDMA_EDMA_HRSL_HRS0              (0x1)
#define MCF5441_EDMA_EDMA_HRSL_HRS1              (0x2)
#define MCF5441_EDMA_EDMA_HRSL_HRS2              (0x4)
#define MCF5441_EDMA_EDMA_HRSL_HRS3              (0x8)
#define MCF5441_EDMA_EDMA_HRSL_HRS4              (0x10)
#define MCF5441_EDMA_EDMA_HRSL_HRS5              (0x20)
#define MCF5441_EDMA_EDMA_HRSL_HRS6              (0x40)
#define MCF5441_EDMA_EDMA_HRSL_HRS7              (0x80)
#define MCF5441_EDMA_EDMA_HRSL_HRS8              (0x100)
#define MCF5441_EDMA_EDMA_HRSL_HRS9              (0x200)
#define MCF5441_EDMA_EDMA_HRSL_HRS10             (0x400)
#define MCF5441_EDMA_EDMA_HRSL_HRS11             (0x800)
#define MCF5441_EDMA_EDMA_HRSL_HRS12             (0x1000)
#define MCF5441_EDMA_EDMA_HRSL_HRS13             (0x2000)
#define MCF5441_EDMA_EDMA_HRSL_HRS14             (0x4000)
#define MCF5441_EDMA_EDMA_HRSL_HRS15             (0x8000)
#define MCF5441_EDMA_EDMA_HRSL_HRS16             (0x10000)
#define MCF5441_EDMA_EDMA_HRSL_HRS17             (0x20000)
#define MCF5441_EDMA_EDMA_HRSL_HRS18             (0x40000)
#define MCF5441_EDMA_EDMA_HRSL_HRS19             (0x80000)
#define MCF5441_EDMA_EDMA_HRSL_HRS20             (0x100000)
#define MCF5441_EDMA_EDMA_HRSL_HRS21             (0x200000)
#define MCF5441_EDMA_EDMA_HRSL_HRS22             (0x400000)
#define MCF5441_EDMA_EDMA_HRSL_HRS23             (0x800000)
#define MCF5441_EDMA_EDMA_HRSL_HRS24             (0x1000000)
#define MCF5441_EDMA_EDMA_HRSL_HRS25             (0x2000000)
#define MCF5441_EDMA_EDMA_HRSL_HRS26             (0x4000000)
#define MCF5441_EDMA_EDMA_HRSL_HRS27             (0x8000000)
#define MCF5441_EDMA_EDMA_HRSL_HRS28             (0x10000000)
#define MCF5441_EDMA_EDMA_HRSL_HRS29             (0x20000000)
#define MCF5441_EDMA_EDMA_HRSL_HRS30             (0x40000000)
#define MCF5441_EDMA_EDMA_HRSL_HRS31             (0x80000000)

/* Bit definitions and macros for MCF5441_EDMA_DCHPRI */
#define MCF5441_EDMA_DCHPRI_CHPRI(x)             (((x)&0xF)<<0)
#define MCF5441_EDMA_DCHPRI_GRPPRI(x)            (((x)&0x3)<<0x4)
#define MCF5441_EDMA_DCHPRI_DPA                  (0x40)
#define MCF5441_EDMA_DCHPRI_ECP                  (0x80)

/* Bit definitions and macros for MCF5441_EDMA_TCD_SADDR */
#define MCF5441_EDMA_TCD_SADDR_SADDR(x)          (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF5441_EDMA_TCD_ATTR */
#define MCF5441_EDMA_TCD_ATTR_DSIZE(x)           (((x)&0x7)<<0)
#define MCF5441_EDMA_TCD_ATTR_DSIZE_8BIT         (0)
#define MCF5441_EDMA_TCD_ATTR_DSIZE_16BIT        (0x1)
#define MCF5441_EDMA_TCD_ATTR_DSIZE_32BIT        (0x2)
#define MCF5441_EDMA_TCD_ATTR_DSIZE_16BYTE       (0x4)
#define MCF5441_EDMA_TCD_ATTR_DMOD(x)            (((x)&0x1F)<<0x3)
#define MCF5441_EDMA_TCD_ATTR_SSIZE(x)           (((x)&0x7)<<0x8)
#define MCF5441_EDMA_TCD_ATTR_SSIZE_8BIT         (0)
#define MCF5441_EDMA_TCD_ATTR_SSIZE_16BIT        (0x1)
#define MCF5441_EDMA_TCD_ATTR_SSIZE_32BIT        (0x2)
#define MCF5441_EDMA_TCD_ATTR_SSIZE_16BYTE       (0x4)
#define MCF5441_EDMA_TCD_ATTR_SMOD(x)            (((x)&0x1F)<<0xB)

/* Bit definitions and macros for MCF5441_EDMA_TCD_SOFF */
#define MCF5441_EDMA_TCD_SOFF_SOFF(x)            (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_EDMA_TCD_NBYTES_MLOFF */
#define MCF5441_EDMA_TCD_NBYTES_MLOFF_NBYTES(x)  (((x)&0x3FF)<<0)
#define MCF5441_EDMA_TCD_NBYTES_MLOFF_MLOFF(x)   (((x)&0xFFFFF)<<0xA)
#define MCF5441_EDMA_TCD_NBYTES_MLOFF_DMLOE      (0x40000000)
#define MCF5441_EDMA_TCD_NBYTES_MLOFF_SMLOE      (0x80000000)

/* Bit definitions and macros for MCF5441_EDMA_TCD_NBYTES */
#define MCF5441_EDMA_TCD_NBYTES_NBYTES(x)        (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF5441_EDMA_TCD_NBYTES_EMLM */
#define MCF5441_EDMA_TCD_NBYTES_EMLM_NBYTES(x)   (((x)&0x3FFFFFFF)<<0)
#define MCF5441_EDMA_TCD_NBYTES_EMLM_DMLOE       (0x40000000)
#define MCF5441_EDMA_TCD_NBYTES_EMLM_SMLOE       (0x80000000)

/* Bit definitions and macros for MCF5441_EDMA_TCD_SLAST */
#define MCF5441_EDMA_TCD_SLAST_SLAST(x)          (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF5441_EDMA_TCD_DADDR */
#define MCF5441_EDMA_TCD_DADDR_DADDR(x)          (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF5441_EDMA_TCD_CITER_ELINK */
#define MCF5441_EDMA_TCD_CITER_ELINK_CITER(x)    (((x)&0x1FF)<<0)
#define MCF5441_EDMA_TCD_CITER_ELINK_LINKCH(x)   (((x)&0x3F)<<0x9)
#define MCF5441_EDMA_TCD_CITER_ELINK_E_LINK      (0x8000)

/* Bit definitions and macros for MCF5441_EDMA_TCD_CITER */
#define MCF5441_EDMA_TCD_CITER_CITER(x)          (((x)&0x7FFF)<<0)
#define MCF5441_EDMA_TCD_CITER_E_LINK            (0x8000)

/* Bit definitions and macros for MCF5441_EDMA_TCD_DOFF */
#define MCF5441_EDMA_TCD_DOFF_DOFF(x)            (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_EDMA_TCD_DLAST_SGA */
#define MCF5441_EDMA_TCD_DLAST_SGA_DLAST_SGA(x)  (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF5441_EDMA_TCD_BITER */
#define MCF5441_EDMA_TCD_BITER_BITER(x)          (((x)&0x7FFF)<<0)
#define MCF5441_EDMA_TCD_BITER_E_LINK            (0x8000)

/* Bit definitions and macros for MCF5441_EDMA_TCD_BITER_ELINK */
#define MCF5441_EDMA_TCD_BITER_ELINK_BITER(x)    (((x)&0x1FF)<<0)
#define MCF5441_EDMA_TCD_BITER_ELINK_LINKCH(x)   (((x)&0x3F)<<0x9)
#define MCF5441_EDMA_TCD_BITER_ELINK_E_LINK      (0x8000)

/* Bit definitions and macros for MCF5441_EDMA_TCD_CSR */
#define MCF5441_EDMA_TCD_CSR_START               (0x1)
#define MCF5441_EDMA_TCD_CSR_INT_MAJOR           (0x2)
#define MCF5441_EDMA_TCD_CSR_INT_HALF            (0x4)
#define MCF5441_EDMA_TCD_CSR_D_REQ               (0x8)
#define MCF5441_EDMA_TCD_CSR_E_SG                (0x10)
#define MCF5441_EDMA_TCD_CSR_MAJOR_E_LINK        (0x20)
#define MCF5441_EDMA_TCD_CSR_ACTIVE              (0x40)
#define MCF5441_EDMA_TCD_CSR_DONE                (0x80)
#define MCF5441_EDMA_TCD_CSR_MAJOR_LINKCH(x)     (((x)&0x3F)<<0x8)
#define MCF5441_EDMA_TCD_CSR_BWC(x)              (((x)&0x3)<<0xE)
#define MCF5441_EDMA_TCD_CSR_BWC_NO_STALL        (0)
#define MCF5441_EDMA_TCD_CSR_BWC_4CYC_STALL      (0x8000)
#define MCF5441_EDMA_TCD_CSR_BWC_8CYC_STALL      (0xC000)


/*
** MCF5441_EDMA_STRUCT
** This structure defines eDMA registers
*/
typedef struct mcf5441_edma_struct {
    uint_32 EDMA_CR;
    uint_32 EDMA_ES;  
    uint_32 EDMA_ERQH; 
    uint_32 EDMA_ERQL; 
    uint_32 EDMA_EEIH; 
    uint_32 EDMA_EEIL; 
    uint_8  EDMA_SERQ;
    uint_8  EDMA_CERQ;
    uint_8  EDMA_SEEI;
    uint_8  EDMA_CEEI;
    uint_8  EDMA_CINT;
    uint_8  EDMA_CERR;
    uint_8  EDMA_SSRT;
    uint_8  EDMA_CDNE;
    uint_32 EDMA_INTH; 
    uint_32 EDMA_INTL; 
    uint_32 EDMA_ERRH;
    uint_32 EDMA_ERRL;
    uint_32 EDMA_HRSH;
    uint_32 EDMA_HRSL;
    uint_8  filler1[0xc8];
    uint_8  EDMA_DCHPRI[MCF5441_NUM_DMA_CH];
    uint_8  filler2[0xec0];

    struct {
        uint_32 EDMA_SADDR;      
        uint_16 EDMA_ATTR;       
        uint_16 EDMA_SOFF;       
        uint_8  EDMA_MLOFF_1B;       
        uint_8  EDMA_MLOFF_2B;       
        uint_8  EDMA_MLOFF_3B;       
        uint_8  EDMA_NBYTES;     
        uint_32 EDMA_SLAST;      
        uint_32 EDMA_DADDR;      
        uint_16 EDMA_CITER;      
        uint_16 EDMA_DOFF;       
        uint_32 EDMA_DLAST_SGA;  
        uint_16 EDMA_BITER;      
        uint_16 EDMA_CSR;        
    } EDMA_TCD[MCF5441_NUM_DMA_CH];

} MCF5441_EDMA_STRUCT, _PTR_ MCF5441_EDMA_STRUCT_PTR;
typedef volatile struct mcf5441_edma_struct _PTR_ VMCF5441_EDMA_STRUCT_PTR;

/* Bit definitions and macros for MCF5441_DTIM_DTMR */
#define MCF5441_DTIM_DTMR_RST                    (0x1)
#define MCF5441_DTIM_DTMR_CLK(x)                 (((x)&0x3)<<0x1)
#define MCF5441_DTIM_DTMR_CLK_STOP               (0)
#define MCF5441_DTIM_DTMR_CLK_DIV1               (0x2)
#define MCF5441_DTIM_DTMR_CLK_DIV16              (0x4)
#define MCF5441_DTIM_DTMR_CLK_DTIN               (0x6)
#define MCF5441_DTIM_DTMR_FRR                    (0x8)
#define MCF5441_DTIM_DTMR_ORRI                   (0x10)
#define MCF5441_DTIM_DTMR_OM                     (0x20)
#define MCF5441_DTIM_DTMR_CE(x)                  (((x)&0x3)<<0x6)
#define MCF5441_DTIM_DTMR_CE_NONE                (0)
#define MCF5441_DTIM_DTMR_CE_RISE                (0x40)
#define MCF5441_DTIM_DTMR_CE_FALL                (0x80)
#define MCF5441_DTIM_DTMR_CE_ANY                 (0xC0)
#define MCF5441_DTIM_DTMR_PS(x)                  (((x)&0xFF)<<0x8)

/* Bit definitions and macros for MCF5441_DTIM_DTXMR */
#define MCF5441_DTIM_DTXMR_MODE16                (0x1)
#define MCF5441_DTIM_DTXMR_EPD                   (0x10)
#define MCF5441_DTIM_DTXMR_EN1588                (0x20)
#define MCF5441_DTIM_DTXMR_HALTED                (0x40)
#define MCF5441_DTIM_DTXMR_DMAEN                 (0x80)

/* Bit definitions and macros for MCF5441_DTIM_DTER */
#define MCF5441_DTIM_DTER_CAP                    (0x1)
#define MCF5441_DTIM_DTER_REF                    (0x2)

/* Bit definitions and macros for MCF5441_DTIM_DTRR */
#define MCF5441_DTIM_DTRR_REF(x)                 (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF5441_DTIM_DTCR */
#define MCF5441_DTIM_DTCR_CAP(x)                 (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF5441_DTIM_DTCN */
#define MCF5441_DTIM_DTCN_CNT(x)                 (((x)&0xFFFFFFFF)<<0)


/*
** MCF5441_TIMER_STRUCT
** This structure defines DMA timer registers
*/
typedef struct mcf5441_dma_timer_struct
{
   uint_16  DTMR;           // DMA Timer mode register
   uint_8   DTXTMR;         // DMA Timer extended mode register
   uint_8   DTER;           // DMA Timer event register
   uint_32  DTRR;           // DMA Timer reference register
   uint_32  DTCR;           // DMA Timer capture register
   uint_32  DTCN;           // DMA Timer counter register
   uint_8   filler1[0x3FF0];
} MCF5441_DMA_TIMER_STRUCT, _PTR_ MCF5441_DMA_TIMER_STRUCT_PTR;
typedef volatile struct mcf5441_dma_timer_struct _PTR_ VMCF5441_DMA_TIMER_STRUCT_PTR;


/* Bit definitions and macros for MCF5441_EPORT_EPIER */
#define MCF5441_EPORT_EPIER_EPIE1                (0x2)
#define MCF5441_EPORT_EPIER_EPIE2                (0x4)
#define MCF5441_EPORT_EPIER_EPIE3                (0x8)
#define MCF5441_EPORT_EPIER_EPIE4                (0x10)
#define MCF5441_EPORT_EPIER_EPIE6                (0x40)
#define MCF5441_EPORT_EPIER_EPIE7                (0x80)

/* Bit definitions and macros for MCF5441_EPORT_EPFR */
#define MCF5441_EPORT_EPFR_EPF1                  (0x2)
#define MCF5441_EPORT_EPFR_EPF2                  (0x4)
#define MCF5441_EPORT_EPFR_EPF3                  (0x8)
#define MCF5441_EPORT_EPFR_EPF4                  (0x10)
#define MCF5441_EPORT_EPFR_EPF6                  (0x40)
#define MCF5441_EPORT_EPFR_EPF7                  (0x80)


/*
** MCF5441_EPORT_STRUCT                                                                  
** Edge Port
*/
typedef struct mcf5441_eport_struct
{
   uint_16  EPPAR; // Pin Assignment Register
   uint_8   filler0;
   uint_8   EPIER; // Interrupt Enable Register
   uint_16  filler1;
   uint_8   EPFR;  // Flag Register
} MCF5441_EPORT_STRUCT, _PTR_ MCF5441_EPORT_STRUCT_PTR;
typedef volatile struct mcf5441_eport_struct _PTR_ VMCF5441_EPORT_STRUCT_PTR;


/* Bit definitions and macros for MCF5441_DAC_CR */
#define MCF5441_DAC_CR_PDN                       (0x1)
#define MCF5441_DAC_CR_FORMAT                    (0x2)
#define MCF5441_DAC_CR_SYNC_EN                   (0x4)
#define MCF5441_DAC_CR_AUTO                      (0x8)
#define MCF5441_DAC_CR_DOWN                      (0x10)
#define MCF5441_DAC_CR_UP                        (0x20)
#define MCF5441_DAC_CR_HSLS                      (0x40)
#define MCF5441_DAC_CR_DMAEN                     (0x80)
#define MCF5441_DAC_CR_WMLVL(x)                  (((x)&0x3)<<0x8)
#define MCF5441_DAC_CR_WMLVL_0                   (0)
#define MCF5441_DAC_CR_WMLVL_2                   (0x100)
#define MCF5441_DAC_CR_WMLVL_4                   (0x200)
#define MCF5441_DAC_CR_WMLVL_6                   (0x300)
#define MCF5441_DAC_CR_FILT_EN                   (0x1000)

/* Bit definitions and macros for MCF5441_DAC_DATA */
#define MCF5441_DAC_DATA_DATA(x)                 (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_DAC_STEP */
#define MCF5441_DAC_STEP_STEP(x)                 (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_DAC_MIN */
#define MCF5441_DAC_MIN_MIN(x)                   (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_DAC_MAX */
#define MCF5441_DAC_MAX_MAX(x)                   (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_DAC_SR */
#define MCF5441_DAC_SR_EMPTY                     (0x1)
#define MCF5441_DAC_SR_FULL                      (0x2)

/* Bit definitions and macros for MCF5441_DAC_FILTCNT */
#define MCF5441_DAC_FILTCNT_FILTCNT(x)           (((x)&0x3F)<<0)

/*
** MCF5441_DAC_STRUCT                                                                  
** Digital-to-Analog Converter
*/
typedef struct mcf5441_dac_struct
{
   uint_16  DAC_CR;      // Control register
   uint_16  DAC_DATA;    // Buffered data register
   uint_16  DAC_STEP;    // Step size register
   uint_16  DAC_MIN;     // Minimum value register
   uint_16  DAC_MAX;     // Maximum value register
   uint_16  DAC_SR;      // Status register
   uint_16  DAC_FILTCNT; // Filter count register
   uint_8   filler[0x3FF2];
} MCF5441_DAC_STRUCT, _PTR_ MCF5441_DAC_STRUCT_PTR;
typedef volatile struct mcf5441_dac_struct _PTR_ VMCF5441_DAC_STRUCT_PTR;


/* Bit definitions and macros for MCF5441_SIM_CR1 */
#define MCF5441_SIM_CR1_SAPD                     (0x1)
#define MCF5441_SIM_CR1_SVEN                     (0x2)
#define MCF5441_SIM_CR1_STEN                     (0x4)
#define MCF5441_SIM_CR1_SRST                     (0x8)
#define MCF5441_SIM_CR1_SCEN                     (0x10)
#define MCF5441_SIM_CR1_SCSP                     (0x20)
#define MCF5441_SIM_CR1_3VOLT                    (0x40)
#define MCF5441_SIM_CR1_SFPD                     (0x80)

/* Bit definitions and macros for MCF5441_SIM_SETUP */
#define MCF5441_SIM_SETUP_AMODE                  (0x1)
#define MCF5441_SIM_SETUP_SPS                    (0x2)

/* Bit definitions and macros for MCF5441_SIM_DETECT1 */
#define MCF5441_SIM_DETECT1_SDIM                 (0x1)
#define MCF5441_SIM_DETECT1_SDI                  (0x2)
#define MCF5441_SIM_DETECT1_SPDP                 (0x4)
#define MCF5441_SIM_DETECT1_SPDS                 (0x8)

/* Bit definitions and macros for MCF5441_SIM_TBUF1 */
#define MCF5441_SIM_TBUF1_TXBUF(x)               (((x)&0xFF)<<0)

/* Bit definitions and macros for MCF5441_SIM_RBUF1 */
#define MCF5441_SIM_RBUF1_RXBUF(x)               (((x)&0xFF)<<0)
#define MCF5441_SIM_RBUF1_PE                     (0x100)
#define MCF5441_SIM_RBUF1_FE                     (0x200)
#define MCF5441_SIM_RBUF1_CWT                    (0x400)

/* Bit definitions and macros for MCF5441_SIM_CR0 */
#define MCF5441_SIM_CR0_SAPD                     (0x1)
#define MCF5441_SIM_CR0_SVEN                     (0x2)
#define MCF5441_SIM_CR0_STEN                     (0x4)
#define MCF5441_SIM_CR0_SRST                     (0x8)
#define MCF5441_SIM_CR0_SCEN                     (0x10)
#define MCF5441_SIM_CR0_SCSP                     (0x20)
#define MCF5441_SIM_CR0_3VOLT                    (0x40)
#define MCF5441_SIM_CR0_SFPD                     (0x80)

/* Bit definitions and macros for MCF5441_SIM_CR */
#define MCF5441_SIM_CR_ICM                       (0x2)
#define MCF5441_SIM_CR_ANACK                     (0x4)
#define MCF5441_SIM_CR_ONACK                     (0x8)
#define MCF5441_SIM_CR_SAMPLE12                  (0x10)
#define MCF5441_SIM_CR_BAUD_SEL(x)               (((x)&0x7)<<0x6)
#define MCF5441_SIM_CR_GPCNT_CLKSEL(x)           (((x)&0x3)<<0x9)
#define MCF5441_SIM_CR_CWTEN                     (0x800)
#define MCF5441_SIM_CR_LRCEN                     (0x1000)
#define MCF5441_SIM_CR_CRCEN                     (0x2000)
#define MCF5441_SIM_CR_XMT_CRC_LRC               (0x4000)
#define MCF5441_SIM_CR_BWTEN                     (0x8000)

/* Bit definitions and macros for MCF5441_SIM_PRE */
#define MCF5441_SIM_PRE_PRESCALER(x)             (((x)&0xFF)<<0)

/* Bit definitions and macros for MCF5441_SIM_RTHR */
#define MCF5441_SIM_RTHR_RDT(x)                  (((x)&0x1F)<<0)
#define MCF5441_SIM_RTHR_RTH(x)                  (((x)&0xF)<<0x5)

/* Bit definitions and macros for MCF5441_SIM_EN */
#define MCF5441_SIM_EN_RXEN                      (0x1)
#define MCF5441_SIM_EN_TXEN                      (0x2)

/* Bit definitions and macros for MCF5441_SIM_TSR */
#define MCF5441_SIM_TSR_XTE                      (0x1)
#define MCF5441_SIM_TSR_TFE                      (0x8)
#define MCF5441_SIM_TSR_ETC                      (0x10)
#define MCF5441_SIM_TSR_TC                       (0x20)
#define MCF5441_SIM_TSR_TFO                      (0x40)
#define MCF5441_SIM_TSR_TDTF                     (0x80)
#define MCF5441_SIM_TSR_GPCNT                    (0x100)

/* Bit definitions and macros for MCF5441_SIM_RSR */
#define MCF5441_SIM_RSR_OEF                      (0x1)
#define MCF5441_SIM_RSR_RFD                      (0x10)
#define MCF5441_SIM_RSR_RDRF                     (0x20)
#define MCF5441_SIM_RSR_LRCOK                    (0x40)
#define MCF5441_SIM_RSR_CRCOK                    (0x80)
#define MCF5441_SIM_RSR_CWT                      (0x100)
#define MCF5441_SIM_RSR_RTE                      (0x200)
#define MCF5441_SIM_RSR_BWT                      (0x400)
#define MCF5441_SIM_RSR_BGT                      (0x800)

/* Bit definitions and macros for MCF5441_SIM_IMR */
#define MCF5441_SIM_IMR_RIM                      (0x1)
#define MCF5441_SIM_IMR_TCIM                     (0x2)
#define MCF5441_SIM_IMR_OIM                      (0x4)
#define MCF5441_SIM_IMR_ETCIM                    (0x8)
#define MCF5441_SIM_IMR_TFEIM                    (0x10)
#define MCF5441_SIM_IMR_XTM                      (0x20)
#define MCF5441_SIM_IMR_TFOM                     (0x40)
#define MCF5441_SIM_IMR_TDTFM                    (0x80)
#define MCF5441_SIM_IMR_GPCNTM                   (0x100)
#define MCF5441_SIM_IMR_CWTM                     (0x200)
#define MCF5441_SIM_IMR_RTM                      (0x400)
#define MCF5441_SIM_IMR_BWTM                     (0x800)
#define MCF5441_SIM_IMR_BGTM                     (0x1000)

/* Bit definitions and macros for MCF5441_SIM_TBUF0 */
#define MCF5441_SIM_TBUF0_TXBUF(x)               (((x)&0xFF)<<0)

/* Bit definitions and macros for MCF5441_SIM_RBUF0 */
#define MCF5441_SIM_RBUF0_RXBUF(x)               (((x)&0xFF)<<0)
#define MCF5441_SIM_RBUF0_PE                     (0x100)
#define MCF5441_SIM_RBUF0_FE                     (0x200)
#define MCF5441_SIM_RBUF0_CWT                    (0x400)

/* Bit definitions and macros for MCF5441_SIM_DETECT0 */
#define MCF5441_SIM_DETECT0_SDIM                 (0x1)
#define MCF5441_SIM_DETECT0_SDI                  (0x2)
#define MCF5441_SIM_DETECT0_SPDP                 (0x4)
#define MCF5441_SIM_DETECT0_SPDS                 (0x8)

/* Bit definitions and macros for MCF5441_SIM_FORMAT */
#define MCF5441_SIM_FORMAT_IC                    (0x1)

/* Bit definitions and macros for MCF5441_SIM_TTHR */
#define MCF5441_SIM_TTHR_TDT(x)                  (((x)&0xF)<<0)
#define MCF5441_SIM_TTHR_XTH(x)                  (((x)&0xF)<<0x4)

/* Bit definitions and macros for MCF5441_SIM_TGCR */
#define MCF5441_SIM_TGCR_GETU(x)                 (((x)&0xFF)<<0)
#define MCF5441_SIM_TGCR_RCVR11                  (0x100)

/* Bit definitions and macros for MCF5441_SIM_ODCR */
#define MCF5441_SIM_ODCR_ODP0                    (0x1)
#define MCF5441_SIM_ODCR_ODP1                    (0x2)

/* Bit definitions and macros for MCF5441_SIM_RCR */
#define MCF5441_SIM_RCR_FLUSH_RCV                (0x1)
#define MCF5441_SIM_RCR_FLUSH_XMT                (0x2)
#define MCF5441_SIM_RCR_SOFT_RST                 (0x4)
#define MCF5441_SIM_RCR_KILL_CLOCK               (0x8)
#define MCF5441_SIM_RCR_DOZE                     (0x10)
#define MCF5441_SIM_RCR_STOP                     (0x20)
#define MCF5441_SIM_RCR_DBUG                     (0x40)

/* Bit definitions and macros for MCF5441_SIM_CWTR */
#define MCF5441_SIM_CWTR_CWT(x)                  (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_SIM_GPCNT */
#define MCF5441_SIM_GPCNT_GPCNT(x)               (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_SIM_DIV */
#define MCF5441_SIM_DIV_DIVISOR(x)               (((x)&0xFF)<<0)

/* Bit definitions and macros for MCF5441_SIM_BWTL */
#define MCF5441_SIM_BWTL_BWT(x)                  (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_SIM_BGT */
#define MCF5441_SIM_BGT_BGT(x)                   (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_SIM_BWTH */
#define MCF5441_SIM_BWTH_BWT(x)                  (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_SIM_TFSR */
#define MCF5441_SIM_TFSR_RPTR(x)                 (((x)&0xF)<<0)
#define MCF5441_SIM_TFSR_WPTR(x)                 (((x)&0xF)<<0x4)
#define MCF5441_SIM_TFSR_CNT(x)                  (((x)&0xF)<<0x8)

/* Bit definitions and macros for MCF5441_SIM_RFCR */
#define MCF5441_SIM_RFCR_CNT(x)                  (((x)&0x1FF)<<0)

/* Bit definitions and macros for MCF5441_SIM_RFWP */
#define MCF5441_SIM_RFWP_WPTR(x)                 (((x)&0x1FF)<<0)

/* Bit definitions and macros for MCF5441_SIM_RFRP */
#define MCF5441_SIM_RFRP_RPTR(x)                 (((x)&0x1FF)<<0)


/*
** MCF5441_SIM_STRUCT                                                                  
** Subscriber Identification Module
*/
typedef struct mcf5441_sim_struct
{
   uint_32  SIM_CR1;     // SIM port 1 control register
   uint_32  SIM_SETUP;   // SIM setup register
   uint_32  SIM_DETECT1; // SIM port 1 detect register
   uint_32  SIM_TBUF1;   // SIM port 1 transmit buffer register
   uint_32  SIM_RBUF1;   // SIM port 1 receive buffer register
   uint_32  SIM_CR0;     // SIM port 0 control register
   uint_32  SIM_CR;      // SIM control register
   uint_32  SIM_PRE;     // SIM clock prescaler register
   uint_32  SIM_RTHR;    // SIM receive threshold register
   uint_32  SIM_EN;      // SIM enable register
   uint_32  SIM_TSR;     // SIM transmit status register
   uint_32  SIM_RSR;     // SIM receive status register
   uint_32  SIM_IMR;     // SIM interrupt mask register
   uint_32  SIM_TBUF0;   // SIM port0 transmit buffer register
   uint_32  SIM_RBUF0;   // SIM port0 receive buffer register
   uint_32  SIM_DETECT0; // SIM port0 detect register
   uint_32  SIM_FORMAT;  // SIM data format register
   uint_32  SIM_TTHR;    // SIM transmit threshold register
   uint_32  SIM_TGCR;    // SIM transmit guard control register
   uint_32  SIM_ODCR;    // SIM open drain configuration control register
   uint_32  SIM_RCR;     // SIM reset control register
   uint_32  SIM_CWTR;    // SIM character wait time register
   uint_32  SIM_GPCNT;   // SIM general purpose counter register
   uint_32  SIM_DIV;     // SIM divisor register
   uint_32  SIM_BWTL;    // SIM block wait time register
   uint_32  SIM_BGT;     // SIM block guard time register
   uint_32  SIM_BWTH;    // SIM block wait time register high
   uint_32  SIM_TFSR;    // SIM transmit FIFO status register
   uint_32  SIM_RFCR;    // SIM receive FIFO counter register
   uint_32  SIM_RFWP;    // SIM receive FIFO write pointer register
   uint_32  SIM_RFRP;    // SIM receive FIFO read pointer register
} MCF5441_SIM_STRUCT, _PTR_ MCF5441_SIM_STRUCT_PTR;
typedef volatile struct mcf5441_sim_struct _PTR_ VMCF5441_SIM_STRUCT_PTR;


/* Bit definitions and macros for MCF5441_SSI_TX */
#define MCF5441_SSI_TX_SSI_TX(x)                 (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF5441_SSI_RX */
#define MCF5441_SSI_RX_SSI_RX(x)                 (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF5441_SSI_CR */
#define MCF5441_SSI_CR_SSI_EN                    (0x1)
#define MCF5441_SSI_CR_TE                        (0x2)
#define MCF5441_SSI_CR_RE                        (0x4)
#define MCF5441_SSI_CR_NET                       (0x8)
#define MCF5441_SSI_CR_SYN                       (0x10)
#define MCF5441_SSI_CR_I2S(x)                    (((x)&0x3)<<0x5)
#define MCF5441_SSI_CR_I2S_NORMAL                (0)
#define MCF5441_SSI_CR_I2S_MASTER                (0x20)
#define MCF5441_SSI_CR_I2S_SLAVE                 (0x40)
#define MCF5441_SSI_CR_MCE                       (0x80)
#define MCF5441_SSI_CR_TCH                       (0x100)
#define MCF5441_SSI_CR_CIS                       (0x200)
#define MCF5441_SSI_CR_TCD                       (0x400)
#define MCF5441_SSI_CR_RCD                       (0x800)

/* Bit definitions and macros for MCF5441_SSI_ISR */
#define MCF5441_SSI_ISR_TFE0                     (0x1)
#define MCF5441_SSI_ISR_TFE1                     (0x2)
#define MCF5441_SSI_ISR_RFF0                     (0x4)
#define MCF5441_SSI_ISR_RFF1                     (0x8)
#define MCF5441_SSI_ISR_RLS                      (0x10)
#define MCF5441_SSI_ISR_TLS                      (0x20)
#define MCF5441_SSI_ISR_RFS                      (0x40)
#define MCF5441_SSI_ISR_TFS                      (0x80)
#define MCF5441_SSI_ISR_TUE0                     (0x100)
#define MCF5441_SSI_ISR_TUE1                     (0x200)
#define MCF5441_SSI_ISR_ROE0                     (0x400)
#define MCF5441_SSI_ISR_ROE1                     (0x800)
#define MCF5441_SSI_ISR_TDE0                     (0x1000)
#define MCF5441_SSI_ISR_TDE1                     (0x2000)
#define MCF5441_SSI_ISR_RDR0                     (0x4000)
#define MCF5441_SSI_ISR_RDR1                     (0x8000)
#define MCF5441_SSI_ISR_RXT                      (0x10000)
#define MCF5441_SSI_ISR_CMDDU                    (0x20000)
#define MCF5441_SSI_ISR_CMDAU                    (0x40000)
#define MCF5441_SSI_ISR_TFRC                     (0x800000)
#define MCF5441_SSI_ISR_RFRC                     (0x1000000)

/* Bit definitions and macros for MCF5441_SSI_IER */
#define MCF5441_SSI_IER_TFE0                     (0x1)
#define MCF5441_SSI_IER_TFE1                     (0x2)
#define MCF5441_SSI_IER_RFF0                     (0x4)
#define MCF5441_SSI_IER_RFF1                     (0x8)
#define MCF5441_SSI_IER_RLS                      (0x10)
#define MCF5441_SSI_IER_TLS                      (0x20)
#define MCF5441_SSI_IER_RFS                      (0x40)
#define MCF5441_SSI_IER_TFS                      (0x80)
#define MCF5441_SSI_IER_TUE0                     (0x100)
#define MCF5441_SSI_IER_TUE1                     (0x200)
#define MCF5441_SSI_IER_ROE0                     (0x400)
#define MCF5441_SSI_IER_ROE1                     (0x800)
#define MCF5441_SSI_IER_TDE0                     (0x1000)
#define MCF5441_SSI_IER_TDE1                     (0x2000)
#define MCF5441_SSI_IER_RDR0                     (0x4000)
#define MCF5441_SSI_IER_RDR1                     (0x8000)
#define MCF5441_SSI_IER_RXT                      (0x10000)
#define MCF5441_SSI_IER_CMDDU                    (0x20000)
#define MCF5441_SSI_IER_CMDAU                    (0x40000)
#define MCF5441_SSI_IER_TIE                      (0x80000)
#define MCF5441_SSI_IER_TDMAE                    (0x100000)
#define MCF5441_SSI_IER_RIE                      (0x200000)
#define MCF5441_SSI_IER_RDMAE                    (0x400000)
#define MCF5441_SSI_IER_TFRC                     (0x800000)
#define MCF5441_SSI_IER_RFRC                     (0x1000000)

/* Bit definitions and macros for MCF5441_SSI_TCR */
#define MCF5441_SSI_TCR_TEFS                     (0x1)
#define MCF5441_SSI_TCR_TFSL                     (0x2)
#define MCF5441_SSI_TCR_TFSI                     (0x4)
#define MCF5441_SSI_TCR_TSCKP                    (0x8)
#define MCF5441_SSI_TCR_TSHFD                    (0x10)
#define MCF5441_SSI_TCR_TXDIR                    (0x20)
#define MCF5441_SSI_TCR_TFDIR                    (0x40)
#define MCF5441_SSI_TCR_TFEN0                    (0x80)
#define MCF5441_SSI_TCR_TFEN1                    (0x100)
#define MCF5441_SSI_TCR_TXBIT0                   (0x200)

/* Bit definitions and macros for MCF5441_SSI_RCR */
#define MCF5441_SSI_RCR_REFS                     (0x1)
#define MCF5441_SSI_RCR_RFSL                     (0x2)
#define MCF5441_SSI_RCR_RFSI                     (0x4)
#define MCF5441_SSI_RCR_RSCKP                    (0x8)
#define MCF5441_SSI_RCR_RSHFD                    (0x10)
#define MCF5441_SSI_RCR_RXDIR                    (0x20)
#define MCF5441_SSI_RCR_RFEN0                    (0x80)
#define MCF5441_SSI_RCR_RFEN1                    (0x100)
#define MCF5441_SSI_RCR_RXBIT0                   (0x200)
#define MCF5441_SSI_RCR_RXEXT                    (0x400)

/* Bit definitions and macros for MCF5441_SSI_CCR */
#define MCF5441_SSI_CCR_PM(x)                    (((x)&0xFF)<<0)
#define MCF5441_SSI_CCR_DC(x)                    (((x)&0x1F)<<0x8)
#define MCF5441_SSI_CCR_WL(x)                    (((x)&0xF)<<0xD)
#define MCF5441_SSI_CCR_PSR                      (0x20000)
#define MCF5441_SSI_CCR_DIV2                     (0x40000)

/* Bit definitions and macros for MCF5441_SSI_FCSR */
#define MCF5441_SSI_FCSR_TFWM0(x)                (((x)&0xF)<<0)
#define MCF5441_SSI_FCSR_RFWM0(x)                (((x)&0xF)<<0x4)
#define MCF5441_SSI_FCSR_TFCNT0(x)               (((x)&0xF)<<0x8)
#define MCF5441_SSI_FCSR_RFCNT0(x)               (((x)&0xF)<<0xC)
#define MCF5441_SSI_FCSR_TFWM1(x)                (((x)&0xF)<<0x10)
#define MCF5441_SSI_FCSR_RFWM1(x)                (((x)&0xF)<<0x14)
#define MCF5441_SSI_FCSR_TFCNT1(x)               (((x)&0xF)<<0x18)
#define MCF5441_SSI_FCSR_RFCNT1(x)               (((x)&0xF)<<0x1C)

/* Bit definitions and macros for MCF5441_SSI_ACR */
#define MCF5441_SSI_ACR_AC97EN                   (0x1)
#define MCF5441_SSI_ACR_FV                       (0x2)
#define MCF5441_SSI_ACR_TIF                      (0x4)
#define MCF5441_SSI_ACR_RD                       (0x8)
#define MCF5441_SSI_ACR_WR                       (0x10)
#define MCF5441_SSI_ACR_FRDIV(x)                 (((x)&0x3F)<<0x5)

/* Bit definitions and macros for MCF5441_SSI_ACADD */
#define MCF5441_SSI_ACADD_SSI_ACADD(x)           (((x)&0x7FFFF)<<0)

/* Bit definitions and macros for MCF5441_SSI_ACDAT */
#define MCF5441_SSI_ACDAT_SSI_ACDAT(x)           (((x)&0xFFFFF)<<0)

/* Bit definitions and macros for MCF5441_SSI_ATAG */
#define MCF5441_SSI_ATAG_SSI_ATAG(x)             (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_SSI_TMASK */
#define MCF5441_SSI_TMASK_SSI_TMASK(x)           (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF5441_SSI_RMASK */
#define MCF5441_SSI_RMASK_SSI_RMASK(x)           (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF5441_SSI_ACCSR */
#define MCF5441_SSI_ACCSR_ACCSR(x)               (((x)&0x3FF)<<0)

/* Bit definitions and macros for MCF5441_SSI_ACCEN */
#define MCF5441_SSI_ACCEN_ACCEN(x)               (((x)&0x3FF)<<0)

/* Bit definitions and macros for MCF5441_SSI_ACCDIS */
#define MCF5441_SSI_ACCDIS_ACCDIS(x)             (((x)&0x3FF)<<0)


/*
** MCF5441_SSI_STRUCT                                                                  
** Synchronous Serial Interface (SSI)
*/
typedef struct mcf5441_ssi_struct
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
   uint_32  SSI_ACCSR;  // SSI AC97 Channel Status Register
   uint_32  SSI_ACCEN;  // SSI AC97 Channel Enable Register
   uint_32  SSI_ACCDIS; // SSI AC97 Channel Disable Register
} MCF5441_SSI_STRUCT, _PTR_ MCF5441_SSI_STRUCT_PTR;
typedef volatile struct mcf5441_ssi_struct _PTR_ VMCF5441_SSI_STRUCT_PTR;


/* Bit definitions and macros for MCF5441_RNG_RNGVER */
#define MCF5441_RNG_RNGVER_MINOR(x)              (((x)&0xFF)<<0)
#define MCF5441_RNG_RNGVER_MAJOR(x)              (((x)&0xFF)<<0x8)
#define MCF5441_RNG_RNGVER_TYPE(x)               (((x)&0xF)<<0x1C)

/* Bit definitions and macros for MCF5441_RNG_RNGCMD */
#define MCF5441_RNG_RNGCMD_ST                    (0x1)
#define MCF5441_RNG_RNGCMD_GS                    (0x2)
#define MCF5441_RNG_RNGCMD_CI                    (0x10)
#define MCF5441_RNG_RNGCMD_CE                    (0x20)
#define MCF5441_RNG_RNGCMD_SR                    (0x40)

/* Bit definitions and macros for MCF5441_RNG_RNGCR */
#define MCF5441_RNG_RNGCR_FUFMOD(x)              (((x)&0x3)<<0)
#define MCF5441_RNG_RNGCR_AR                     (0x10)
#define MCF5441_RNG_RNGCR_MSKDN                  (0x20)
#define MCF5441_RNG_RNGCR_MSKERR                 (0x40)

/* Bit definitions and macros for MCF5441_RNG_RNGSR */
#define MCF5441_RNG_RNGSR_BUSY                   (0x2)
#define MCF5441_RNG_RNGSR_SLP                    (0x4)
#define MCF5441_RNG_RNGSR_RS                     (0x8)
#define MCF5441_RNG_RNGSR_STDN                   (0x10)
#define MCF5441_RNG_RNGSR_SDN                    (0x20)
#define MCF5441_RNG_RNGSR_NSDN                   (0x40)
#define MCF5441_RNG_RNGSR_FL(x)                  (((x)&0xF)<<0x8)
#define MCF5441_RNG_RNGSR_FS(x)                  (((x)&0xF)<<0xC)
#define MCF5441_RNG_RNGSR_ERR                    (0x10000)
#define MCF5441_RNG_RNGSR_SELFPF(x)              (((x)&0x3)<<0x16)
#define MCF5441_RNG_RNGSR_STATPF(x)              (((x)&0xFF)<<0x18)

/* Bit definitions and macros for MCF5441_RNG_RNGESR */
#define MCF5441_RNG_RNGESR_LFE                   (0x1)
#define MCF5441_RNG_RNGESR_OSCE                  (0x2)
#define MCF5441_RNG_RNGESR_STE                   (0x4)
#define MCF5441_RNG_RNGESR_SATE                  (0x8)
#define MCF5441_RNG_RNGESR_FUF                   (0x10)

/* Bit definitions and macros for MCF5441_RNG_RNGOUT */
#define MCF5441_RNG_RNGOUT_RANDOM_OUTPUT(x)      (((x)&0xFFFFFFFF)<<0)

/* Bit definitions and macros for MCF5441_RNG_RNGER */
#define MCF5441_RNG_RNGER_ENT(x)                 (((x)&0xFFFFFFFF)<<0)


/*
** MCF5441_RNG_STRUCT                                                                   
** Random Number Generator (RNG)
*/
typedef struct mcf5441_rng_struct
{
   uint_32  RNG_RNGVER; // RNG Version ID Register
   uint_32  RNG_RNGCMD; // RNG Command Register
   uint_32  RNG_RNGCR;  // RNG Control Register
   uint_32  RNG_RNGSR;  // RNG Status Register
   uint_32  RNG_RNGESR; // RNG Error Status Register
   uint_32  RNG_RNGOUT; // RNG Output FIFO
   uint_32  RNG_RNGER;  // RNG Entropy Register
} MCF5441_RNG_STRUCT, _PTR_ MCF5441_RNG_STRUCT_PTR;
typedef volatile struct mcf5441_rng_struct _PTR_ VMCF5441_RNG_STRUCT_PTR;


/* Bit definitions and macros for MCF5441_PWM_SM0CNT */
#define MCF5441_PWM_SM0CNT_CNT(x)                (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM0INIT */
#define MCF5441_PWM_SM0INIT_INIT(x)              (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM0CR2 */
#define MCF5441_PWM_SM0CR2_CLK_SEL(x)            (((x)&0x3)<<0)
#define MCF5441_PWM_SM0CR2_RELOAD_SEL            (0x4)
#define MCF5441_PWM_SM0CR2_FORCE_SEL(x)          (((x)&0x7)<<0x3)
#define MCF5441_PWM_SM0CR2_FORCE                 (0x40)
#define MCF5441_PWM_SM0CR2_FRCEN                 (0x80)
#define MCF5441_PWM_SM0CR2_INIT_SEL(x)           (((x)&0x3)<<0x8)
#define MCF5441_PWM_SM0CR2_PWMX_INIT             (0x400)
#define MCF5441_PWM_SM0CR2_PWM45_INIT            (0x800)
#define MCF5441_PWM_SM0CR2_PWM23_INIT            (0x1000)
#define MCF5441_PWM_SM0CR2_INDEP                 (0x2000)
#define MCF5441_PWM_SM0CR2_WAITEN                (0x4000)
#define MCF5441_PWM_SM0CR2_DBGEN                 (0x8000)

/* Bit definitions and macros for MCF5441_PWM_SM0CR */
#define MCF5441_PWM_SM0CR_DBLEN                  (0x1)
#define MCF5441_PWM_SM0CR_LDMOD                  (0x4)
#define MCF5441_PWM_SM0CR_PRSC(x)                (((x)&0x7)<<0x4)
#define MCF5441_PWM_SM0CR_DT(x)                  (((x)&0x3)<<0x8)
#define MCF5441_PWM_SM0CR_FULL                   (0x400)
#define MCF5441_PWM_SM0CR_HALF                   (0x800)
#define MCF5441_PWM_SM0CR_LDFQ(x)                (((x)&0xF)<<0xC)

/* Bit definitions and macros for MCF5441_PWM_SM0VAL0 */
#define MCF5441_PWM_SM0VAL0_VAL0(x)              (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM0VAL1 */
#define MCF5441_PWM_SM0VAL1_VAL1(x)              (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM0VAL2 */
#define MCF5441_PWM_SM0VAL2_VAL2(x)              (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM0VAL3 */
#define MCF5441_PWM_SM0VAL3_VAL3(x)              (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM0VAL4 */
#define MCF5441_PWM_SM0VAL4_VAL4(x)              (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM0VAL5 */
#define MCF5441_PWM_SM0VAL5_VAL5(x)              (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM0OCR */
#define MCF5441_PWM_SM0OCR_PWMXFS(x)             (((x)&0x3)<<0)
#define MCF5441_PWM_SM0OCR_PWMBFS(x)             (((x)&0x3)<<0x2)
#define MCF5441_PWM_SM0OCR_PWMAFS(x)             (((x)&0x3)<<0x4)
#define MCF5441_PWM_SM0OCR_POLX                  (0x100)
#define MCF5441_PWM_SM0OCR_POLB                  (0x200)
#define MCF5441_PWM_SM0OCR_POLA                  (0x400)
#define MCF5441_PWM_SM0OCR_PWMX_IN               (0x2000)
#define MCF5441_PWM_SM0OCR_PWMB_IN               (0x4000)
#define MCF5441_PWM_SM0OCR_PWMA_IN               (0x8000)

/* Bit definitions and macros for MCF5441_PWM_SM0SR */
#define MCF5441_PWM_SM0SR_CMPF(x)                (((x)&0x3F)<<0)
#define MCF5441_PWM_SM0SR_CFX0                   (0x40)
#define MCF5441_PWM_SM0SR_CFX1                   (0x80)
#define MCF5441_PWM_SM0SR_CFB0                   (0x100)
#define MCF5441_PWM_SM0SR_CFB1                   (0x200)
#define MCF5441_PWM_SM0SR_CFA0                   (0x400)
#define MCF5441_PWM_SM0SR_CFA1                   (0x800)
#define MCF5441_PWM_SM0SR_RF                     (0x1000)
#define MCF5441_PWM_SM0SR_REF                    (0x2000)
#define MCF5441_PWM_SM0SR_RUF                    (0x4000)

/* Bit definitions and macros for MCF5441_PWM_SM0IER */
#define MCF5441_PWM_SM0IER_CMPIE(x)              (((x)&0x3F)<<0)
#define MCF5441_PWM_SM0IER_CX0IE                 (0x40)
#define MCF5441_PWM_SM0IER_CX1IE                 (0x80)
#define MCF5441_PWM_SM0IER_CB0IE                 (0x100)
#define MCF5441_PWM_SM0IER_CB1IE                 (0x200)
#define MCF5441_PWM_SM0IER_CA0IE                 (0x400)
#define MCF5441_PWM_SM0IER_CA1IE                 (0x800)
#define MCF5441_PWM_SM0IER_RIE                   (0x1000)
#define MCF5441_PWM_SM0IER_REIE                  (0x2000)

/* Bit definitions and macros for MCF5441_PWM_SM0DMAEN */
#define MCF5441_PWM_SM0DMAEN_CX0DE               (0x1)
#define MCF5441_PWM_SM0DMAEN_CX1DE               (0x2)
#define MCF5441_PWM_SM0DMAEN_CB0DE               (0x4)
#define MCF5441_PWM_SM0DMAEN_CB1DE               (0x8)
#define MCF5441_PWM_SM0DMAEN_CA0DE               (0x10)
#define MCF5441_PWM_SM0DMAEN_CA1DE               (0x20)
#define MCF5441_PWM_SM0DMAEN_CAPTDE(x)           (((x)&0x3)<<0x6)
#define MCF5441_PWM_SM0DMAEN_FAND                (0x100)
#define MCF5441_PWM_SM0DMAEN_VALDE               (0x200)

/* Bit definitions and macros for MCF5441_PWM_SM0OTCR */
#define MCF5441_PWM_SM0OTCR_OUT_TRIG_EN(x)       (((x)&0x3F)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM0DISMAP */
#define MCF5441_PWM_SM0DISMAP_DISA(x)            (((x)&0xF)<<0)
#define MCF5441_PWM_SM0DISMAP_DISB(x)            (((x)&0xF)<<0x4)
#define MCF5441_PWM_SM0DISMAP_DISX(x)            (((x)&0xF)<<0x8)

/* Bit definitions and macros for MCF5441_PWM_SM0DTCNT0 */
#define MCF5441_PWM_SM0DTCNT0_DTCNT0(x)          (((x)&0x7FF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM0DTCNT1 */
#define MCF5441_PWM_SM0DTCNT1_DTCNT1(x)          (((x)&0x7FF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM0CCRA */
#define MCF5441_PWM_SM0CCRA_ARM                  (0x1)
#define MCF5441_PWM_SM0CCRA_ONESHOT              (0x2)
#define MCF5441_PWM_SM0CCRA_EDG0(x)              (((x)&0x3)<<0x2)
#define MCF5441_PWM_SM0CCRA_EDG1(x)              (((x)&0x3)<<0x4)
#define MCF5441_PWM_SM0CCRA_INP_SEL              (0x40)
#define MCF5441_PWM_SM0CCRA_EDGCNT_EN            (0x80)
#define MCF5441_PWM_SM0CCRA_CFWM(x)              (((x)&0x3)<<0x8)
#define MCF5441_PWM_SM0CCRA_C0CNT(x)             (((x)&0x7)<<0xA)
#define MCF5441_PWM_SM0CCRA_C1CNT(x)             (((x)&0x7)<<0xD)

/* Bit definitions and macros for MCF5441_PWM_SM0CCMPA */
#define MCF5441_PWM_SM0CCMPA_EDGCMP(x)           (((x)&0xFF)<<0)
#define MCF5441_PWM_SM0CCMPA_EDGCNT(x)           (((x)&0xFF)<<0x8)

/* Bit definitions and macros for MCF5441_PWM_SM0CCRB */
#define MCF5441_PWM_SM0CCRB_ARM                  (0x1)
#define MCF5441_PWM_SM0CCRB_ONESHOT              (0x2)
#define MCF5441_PWM_SM0CCRB_EDG0(x)              (((x)&0x3)<<0x2)
#define MCF5441_PWM_SM0CCRB_EDG1(x)              (((x)&0x3)<<0x4)
#define MCF5441_PWM_SM0CCRB_INP_SEL              (0x40)
#define MCF5441_PWM_SM0CCRB_EDGCNT_EN            (0x80)
#define MCF5441_PWM_SM0CCRB_CFWM(x)              (((x)&0x3)<<0x8)
#define MCF5441_PWM_SM0CCRB_C0CNT(x)             (((x)&0x7)<<0xA)
#define MCF5441_PWM_SM0CCRB_C1CNT(x)             (((x)&0x7)<<0xD)

/* Bit definitions and macros for MCF5441_PWM_SM0CCMPB */
#define MCF5441_PWM_SM0CCMPB_EDGCMP(x)           (((x)&0xFF)<<0)
#define MCF5441_PWM_SM0CCMPB_EDGCNT(x)           (((x)&0xFF)<<0x8)

/* Bit definitions and macros for MCF5441_PWM_SM0CCRX */
#define MCF5441_PWM_SM0CCRX_ARM                  (0x1)
#define MCF5441_PWM_SM0CCRX_ONESHOT              (0x2)
#define MCF5441_PWM_SM0CCRX_EDG0(x)              (((x)&0x3)<<0x2)
#define MCF5441_PWM_SM0CCRX_EDG1(x)              (((x)&0x3)<<0x4)
#define MCF5441_PWM_SM0CCRX_INP_SEL              (0x40)
#define MCF5441_PWM_SM0CCRX_EDGCNT_EN            (0x80)
#define MCF5441_PWM_SM0CCRX_CFWM(x)              (((x)&0x3)<<0x8)
#define MCF5441_PWM_SM0CCRX_C0CNT(x)             (((x)&0x7)<<0xA)
#define MCF5441_PWM_SM0CCRX_C1CNT(x)             (((x)&0x7)<<0xD)

/* Bit definitions and macros for MCF5441_PWM_SM0CCMPX */
#define MCF5441_PWM_SM0CCMPX_EDGCMP(x)           (((x)&0xFF)<<0)
#define MCF5441_PWM_SM0CCMPX_EDGCNT(x)           (((x)&0xFF)<<0x8)

/* Bit definitions and macros for MCF5441_PWM_SM0CVAL0 */
#define MCF5441_PWM_SM0CVAL0_CAPTVAL(x)          (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM0CCYC0 */
#define MCF5441_PWM_SM0CCYC0_CYC(x)              (((x)&0xF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM0CVAL1 */
#define MCF5441_PWM_SM0CVAL1_CAPTVAL(x)          (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM0CCYC1 */
#define MCF5441_PWM_SM0CCYC1_CYC(x)              (((x)&0xF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM0CVAL2 */
#define MCF5441_PWM_SM0CVAL2_CAPTVAL(x)          (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM0CCYC2 */
#define MCF5441_PWM_SM0CCYC2_CYC(x)              (((x)&0xF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM0CVAL3 */
#define MCF5441_PWM_SM0CVAL3_CAPTVAL(x)          (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM0CCYC3 */
#define MCF5441_PWM_SM0CCYC3_CYC(x)              (((x)&0xF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM0CVAL4 */
#define MCF5441_PWM_SM0CVAL4_CAPTVAL(x)          (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM0CCYC4 */
#define MCF5441_PWM_SM0CCYC4_CYC(x)              (((x)&0xF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM0CVAL5 */
#define MCF5441_PWM_SM0CVAL5_CAPTVAL(x)          (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM0CCYC5 */
#define MCF5441_PWM_SM0CCYC5_CYC(x)              (((x)&0xF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM1CNT */
#define MCF5441_PWM_SM1CNT_CNT(x)                (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM1INIT */
#define MCF5441_PWM_SM1INIT_INIT(x)              (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM1CR2 */
#define MCF5441_PWM_SM1CR2_CLK_SEL(x)            (((x)&0x3)<<0)
#define MCF5441_PWM_SM1CR2_RELOAD_SEL            (0x4)
#define MCF5441_PWM_SM1CR2_FORCE_SEL(x)          (((x)&0x7)<<0x3)
#define MCF5441_PWM_SM1CR2_FORCE                 (0x40)
#define MCF5441_PWM_SM1CR2_FRCEN                 (0x80)
#define MCF5441_PWM_SM1CR2_INIT_SEL(x)           (((x)&0x3)<<0x8)
#define MCF5441_PWM_SM1CR2_PWMX_INIT             (0x400)
#define MCF5441_PWM_SM1CR2_PWM45_INIT            (0x800)
#define MCF5441_PWM_SM1CR2_PWM23_INIT            (0x1000)
#define MCF5441_PWM_SM1CR2_INDEP                 (0x2000)
#define MCF5441_PWM_SM1CR2_WAITEN                (0x4000)
#define MCF5441_PWM_SM1CR2_DBGEN                 (0x8000)

/* Bit definitions and macros for MCF5441_PWM_SM1CR */
#define MCF5441_PWM_SM1CR_DBLEN                  (0x1)
#define MCF5441_PWM_SM1CR_LDMOD                  (0x4)
#define MCF5441_PWM_SM1CR_PRSC(x)                (((x)&0x7)<<0x4)
#define MCF5441_PWM_SM1CR_DT(x)                  (((x)&0x3)<<0x8)
#define MCF5441_PWM_SM1CR_FULL                   (0x400)
#define MCF5441_PWM_SM1CR_HALF                   (0x800)
#define MCF5441_PWM_SM1CR_LDFQ(x)                (((x)&0xF)<<0xC)

/* Bit definitions and macros for MCF5441_PWM_SM1VAL0 */
#define MCF5441_PWM_SM1VAL0_VAL0(x)              (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM1VAL1 */
#define MCF5441_PWM_SM1VAL1_VAL1(x)              (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM1VAL2 */
#define MCF5441_PWM_SM1VAL2_VAL2(x)              (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM1VAL3 */
#define MCF5441_PWM_SM1VAL3_VAL3(x)              (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM1VAL4 */
#define MCF5441_PWM_SM1VAL4_VAL4(x)              (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM1VAL5 */
#define MCF5441_PWM_SM1VAL5_VAL5(x)              (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM1OCR */
#define MCF5441_PWM_SM1OCR_PWMXFS(x)             (((x)&0x3)<<0)
#define MCF5441_PWM_SM1OCR_PWMBFS(x)             (((x)&0x3)<<0x2)
#define MCF5441_PWM_SM1OCR_PWMAFS(x)             (((x)&0x3)<<0x4)
#define MCF5441_PWM_SM1OCR_POLX                  (0x100)
#define MCF5441_PWM_SM1OCR_POLB                  (0x200)
#define MCF5441_PWM_SM1OCR_POLA                  (0x400)
#define MCF5441_PWM_SM1OCR_PWMX_IN               (0x2000)
#define MCF5441_PWM_SM1OCR_PWMB_IN               (0x4000)
#define MCF5441_PWM_SM1OCR_PWMA_IN               (0x8000)

/* Bit definitions and macros for MCF5441_PWM_SM1SR */
#define MCF5441_PWM_SM1SR_CMPF(x)                (((x)&0x3F)<<0)
#define MCF5441_PWM_SM1SR_CFX0                   (0x40)
#define MCF5441_PWM_SM1SR_CFX1                   (0x80)
#define MCF5441_PWM_SM1SR_CFB0                   (0x100)
#define MCF5441_PWM_SM1SR_CFB1                   (0x200)
#define MCF5441_PWM_SM1SR_CFA0                   (0x400)
#define MCF5441_PWM_SM1SR_CFA1                   (0x800)
#define MCF5441_PWM_SM1SR_RF                     (0x1000)
#define MCF5441_PWM_SM1SR_REF                    (0x2000)
#define MCF5441_PWM_SM1SR_RUF                    (0x4000)

/* Bit definitions and macros for MCF5441_PWM_SM1IER */
#define MCF5441_PWM_SM1IER_CMPIE(x)              (((x)&0x3F)<<0)
#define MCF5441_PWM_SM1IER_CX0IE                 (0x40)
#define MCF5441_PWM_SM1IER_CX1IE                 (0x80)
#define MCF5441_PWM_SM1IER_CB0IE                 (0x100)
#define MCF5441_PWM_SM1IER_CB1IE                 (0x200)
#define MCF5441_PWM_SM1IER_CA0IE                 (0x400)
#define MCF5441_PWM_SM1IER_CA1IE                 (0x800)
#define MCF5441_PWM_SM1IER_RIE                   (0x1000)
#define MCF5441_PWM_SM1IER_REIE                  (0x2000)

/* Bit definitions and macros for MCF5441_PWM_SM1DMAEN */
#define MCF5441_PWM_SM1DMAEN_CX0DE               (0x1)
#define MCF5441_PWM_SM1DMAEN_CX1DE               (0x2)
#define MCF5441_PWM_SM1DMAEN_CB0DE               (0x4)
#define MCF5441_PWM_SM1DMAEN_CB1DE               (0x8)
#define MCF5441_PWM_SM1DMAEN_CA0DE               (0x10)
#define MCF5441_PWM_SM1DMAEN_CA1DE               (0x20)
#define MCF5441_PWM_SM1DMAEN_CAPTDE(x)           (((x)&0x3)<<0x6)
#define MCF5441_PWM_SM1DMAEN_FAND                (0x100)
#define MCF5441_PWM_SM1DMAEN_VALDE               (0x200)

/* Bit definitions and macros for MCF5441_PWM_SM1OTCR */
#define MCF5441_PWM_SM1OTCR_OUT_TRIG_EN(x)       (((x)&0x3F)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM1DISMAP */
#define MCF5441_PWM_SM1DISMAP_DISA(x)            (((x)&0xF)<<0)
#define MCF5441_PWM_SM1DISMAP_DISB(x)            (((x)&0xF)<<0x4)
#define MCF5441_PWM_SM1DISMAP_DISX(x)            (((x)&0xF)<<0x8)

/* Bit definitions and macros for MCF5441_PWM_SM1DTCNT0 */
#define MCF5441_PWM_SM1DTCNT0_DTCNT0(x)          (((x)&0x7FF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM1DTCNT1 */
#define MCF5441_PWM_SM1DTCNT1_DTCNT1(x)          (((x)&0x7FF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM1CCRA */
#define MCF5441_PWM_SM1CCRA_ARM                  (0x1)
#define MCF5441_PWM_SM1CCRA_ONESHOT              (0x2)
#define MCF5441_PWM_SM1CCRA_EDG0(x)              (((x)&0x3)<<0x2)
#define MCF5441_PWM_SM1CCRA_EDG1(x)              (((x)&0x3)<<0x4)
#define MCF5441_PWM_SM1CCRA_INP_SEL              (0x40)
#define MCF5441_PWM_SM1CCRA_EDGCNT_EN            (0x80)
#define MCF5441_PWM_SM1CCRA_CFWM(x)              (((x)&0x3)<<0x8)
#define MCF5441_PWM_SM1CCRA_C0CNT(x)             (((x)&0x7)<<0xA)
#define MCF5441_PWM_SM1CCRA_C1CNT(x)             (((x)&0x7)<<0xD)

/* Bit definitions and macros for MCF5441_PWM_SM1CCMPA */
#define MCF5441_PWM_SM1CCMPA_EDGCMP(x)           (((x)&0xFF)<<0)
#define MCF5441_PWM_SM1CCMPA_EDGCNT(x)           (((x)&0xFF)<<0x8)

/* Bit definitions and macros for MCF5441_PWM_SM1CCRB */
#define MCF5441_PWM_SM1CCRB_ARM                  (0x1)
#define MCF5441_PWM_SM1CCRB_ONESHOT              (0x2)
#define MCF5441_PWM_SM1CCRB_EDG0(x)              (((x)&0x3)<<0x2)
#define MCF5441_PWM_SM1CCRB_EDG1(x)              (((x)&0x3)<<0x4)
#define MCF5441_PWM_SM1CCRB_INP_SEL              (0x40)
#define MCF5441_PWM_SM1CCRB_EDGCNT_EN            (0x80)
#define MCF5441_PWM_SM1CCRB_CFWM(x)              (((x)&0x3)<<0x8)
#define MCF5441_PWM_SM1CCRB_C0CNT(x)             (((x)&0x7)<<0xA)
#define MCF5441_PWM_SM1CCRB_C1CNT(x)             (((x)&0x7)<<0xD)

/* Bit definitions and macros for MCF5441_PWM_SM1CCMPB */
#define MCF5441_PWM_SM1CCMPB_EDGCMP(x)           (((x)&0xFF)<<0)
#define MCF5441_PWM_SM1CCMPB_EDGCNT(x)           (((x)&0xFF)<<0x8)

/* Bit definitions and macros for MCF5441_PWM_SM1CCRX */
#define MCF5441_PWM_SM1CCRX_ARM                  (0x1)
#define MCF5441_PWM_SM1CCRX_ONESHOT              (0x2)
#define MCF5441_PWM_SM1CCRX_EDG0(x)              (((x)&0x3)<<0x2)
#define MCF5441_PWM_SM1CCRX_EDG1(x)              (((x)&0x3)<<0x4)
#define MCF5441_PWM_SM1CCRX_INP_SEL              (0x40)
#define MCF5441_PWM_SM1CCRX_EDGCNT_EN            (0x80)
#define MCF5441_PWM_SM1CCRX_CFWM(x)              (((x)&0x3)<<0x8)
#define MCF5441_PWM_SM1CCRX_C0CNT(x)             (((x)&0x7)<<0xA)
#define MCF5441_PWM_SM1CCRX_C1CNT(x)             (((x)&0x7)<<0xD)

/* Bit definitions and macros for MCF5441_PWM_SM1CCMPX */
#define MCF5441_PWM_SM1CCMPX_EDGCMP(x)           (((x)&0xFF)<<0)
#define MCF5441_PWM_SM1CCMPX_EDGCNT(x)           (((x)&0xFF)<<0x8)

/* Bit definitions and macros for MCF5441_PWM_SM1CVAL0 */
#define MCF5441_PWM_SM1CVAL0_CAPTVAL(x)          (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM1CCYC0 */
#define MCF5441_PWM_SM1CCYC0_CYC(x)              (((x)&0xF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM1CVAL1 */
#define MCF5441_PWM_SM1CVAL1_CAPTVAL(x)          (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM1CCYC1 */
#define MCF5441_PWM_SM1CCYC1_CYC(x)              (((x)&0xF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM1CVAL2 */
#define MCF5441_PWM_SM1CVAL2_CAPTVAL(x)          (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM1CCYC2 */
#define MCF5441_PWM_SM1CCYC2_CYC(x)              (((x)&0xF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM1CVAL3 */
#define MCF5441_PWM_SM1CVAL3_CAPTVAL(x)          (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM1CCYC3 */
#define MCF5441_PWM_SM1CCYC3_CYC(x)              (((x)&0xF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM1CVAL4 */
#define MCF5441_PWM_SM1CVAL4_CAPTVAL(x)          (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM1CCYC4 */
#define MCF5441_PWM_SM1CCYC4_CYC(x)              (((x)&0xF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM1CVAL5 */
#define MCF5441_PWM_SM1CVAL5_CAPTVAL(x)          (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM1CCYC5 */
#define MCF5441_PWM_SM1CCYC5_CYC(x)              (((x)&0xF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM2CNT */
#define MCF5441_PWM_SM2CNT_CNT(x)                (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM2INIT */
#define MCF5441_PWM_SM2INIT_INIT(x)              (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM2CR2 */
#define MCF5441_PWM_SM2CR2_CLK_SEL(x)            (((x)&0x3)<<0)
#define MCF5441_PWM_SM2CR2_RELOAD_SEL            (0x4)
#define MCF5441_PWM_SM2CR2_FORCE_SEL(x)          (((x)&0x7)<<0x3)
#define MCF5441_PWM_SM2CR2_FORCE                 (0x40)
#define MCF5441_PWM_SM2CR2_FRCEN                 (0x80)
#define MCF5441_PWM_SM2CR2_INIT_SEL(x)           (((x)&0x3)<<0x8)
#define MCF5441_PWM_SM2CR2_PWMX_INIT             (0x400)
#define MCF5441_PWM_SM2CR2_PWM45_INIT            (0x800)
#define MCF5441_PWM_SM2CR2_PWM23_INIT            (0x1000)
#define MCF5441_PWM_SM2CR2_INDEP                 (0x2000)
#define MCF5441_PWM_SM2CR2_WAITEN                (0x4000)
#define MCF5441_PWM_SM2CR2_DBGEN                 (0x8000)

/* Bit definitions and macros for MCF5441_PWM_SM2CR */
#define MCF5441_PWM_SM2CR_DBLEN                  (0x1)
#define MCF5441_PWM_SM2CR_LDMOD                  (0x4)
#define MCF5441_PWM_SM2CR_PRSC(x)                (((x)&0x7)<<0x4)
#define MCF5441_PWM_SM2CR_DT(x)                  (((x)&0x3)<<0x8)
#define MCF5441_PWM_SM2CR_FULL                   (0x400)
#define MCF5441_PWM_SM2CR_HALF                   (0x800)
#define MCF5441_PWM_SM2CR_LDFQ(x)                (((x)&0xF)<<0xC)

/* Bit definitions and macros for MCF5441_PWM_SM2VAL0 */
#define MCF5441_PWM_SM2VAL0_VAL0(x)              (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM2VAL1 */
#define MCF5441_PWM_SM2VAL1_VAL1(x)              (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM2VAL2 */
#define MCF5441_PWM_SM2VAL2_VAL2(x)              (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM2VAL3 */
#define MCF5441_PWM_SM2VAL3_VAL3(x)              (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM2VAL4 */
#define MCF5441_PWM_SM2VAL4_VAL4(x)              (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM2VAL5 */
#define MCF5441_PWM_SM2VAL5_VAL5(x)              (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM2OCR */
#define MCF5441_PWM_SM2OCR_PWMXFS(x)             (((x)&0x3)<<0)
#define MCF5441_PWM_SM2OCR_PWMBFS(x)             (((x)&0x3)<<0x2)
#define MCF5441_PWM_SM2OCR_PWMAFS(x)             (((x)&0x3)<<0x4)
#define MCF5441_PWM_SM2OCR_POLX                  (0x100)
#define MCF5441_PWM_SM2OCR_POLB                  (0x200)
#define MCF5441_PWM_SM2OCR_POLA                  (0x400)
#define MCF5441_PWM_SM2OCR_PWMX_IN               (0x2000)
#define MCF5441_PWM_SM2OCR_PWMB_IN               (0x4000)
#define MCF5441_PWM_SM2OCR_PWMA_IN               (0x8000)

/* Bit definitions and macros for MCF5441_PWM_SM2SR */
#define MCF5441_PWM_SM2SR_CMPF(x)                (((x)&0x3F)<<0)
#define MCF5441_PWM_SM2SR_CFX0                   (0x40)
#define MCF5441_PWM_SM2SR_CFX1                   (0x80)
#define MCF5441_PWM_SM2SR_CFB0                   (0x100)
#define MCF5441_PWM_SM2SR_CFB1                   (0x200)
#define MCF5441_PWM_SM2SR_CFA0                   (0x400)
#define MCF5441_PWM_SM2SR_CFA1                   (0x800)
#define MCF5441_PWM_SM2SR_RF                     (0x1000)
#define MCF5441_PWM_SM2SR_REF                    (0x2000)
#define MCF5441_PWM_SM2SR_RUF                    (0x4000)

/* Bit definitions and macros for MCF5441_PWM_SM2IER */
#define MCF5441_PWM_SM2IER_CMPIE(x)              (((x)&0x3F)<<0)
#define MCF5441_PWM_SM2IER_CX0IE                 (0x40)
#define MCF5441_PWM_SM2IER_CX1IE                 (0x80)
#define MCF5441_PWM_SM2IER_CB0IE                 (0x100)
#define MCF5441_PWM_SM2IER_CB1IE                 (0x200)
#define MCF5441_PWM_SM2IER_CA0IE                 (0x400)
#define MCF5441_PWM_SM2IER_CA1IE                 (0x800)
#define MCF5441_PWM_SM2IER_RIE                   (0x1000)
#define MCF5441_PWM_SM2IER_REIE                  (0x2000)

/* Bit definitions and macros for MCF5441_PWM_SM2DMAEN */
#define MCF5441_PWM_SM2DMAEN_CX0DE               (0x1)
#define MCF5441_PWM_SM2DMAEN_CX1DE               (0x2)
#define MCF5441_PWM_SM2DMAEN_CB0DE               (0x4)
#define MCF5441_PWM_SM2DMAEN_CB1DE               (0x8)
#define MCF5441_PWM_SM2DMAEN_CA0DE               (0x10)
#define MCF5441_PWM_SM2DMAEN_CA1DE               (0x20)
#define MCF5441_PWM_SM2DMAEN_CAPTDE(x)           (((x)&0x3)<<0x6)
#define MCF5441_PWM_SM2DMAEN_FAND                (0x100)
#define MCF5441_PWM_SM2DMAEN_VALDE               (0x200)

/* Bit definitions and macros for MCF5441_PWM_SM2OTCR */
#define MCF5441_PWM_SM2OTCR_OUT_TRIG_EN(x)       (((x)&0x3F)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM2DISMAP */
#define MCF5441_PWM_SM2DISMAP_DISA(x)            (((x)&0xF)<<0)
#define MCF5441_PWM_SM2DISMAP_DISB(x)            (((x)&0xF)<<0x4)
#define MCF5441_PWM_SM2DISMAP_DISX(x)            (((x)&0xF)<<0x8)

/* Bit definitions and macros for MCF5441_PWM_SM2DTCNT0 */
#define MCF5441_PWM_SM2DTCNT0_DTCNT0(x)          (((x)&0x7FF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM2DTCNT1 */
#define MCF5441_PWM_SM2DTCNT1_DTCNT1(x)          (((x)&0x7FF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM2CCRA */
#define MCF5441_PWM_SM2CCRA_ARM                  (0x1)
#define MCF5441_PWM_SM2CCRA_ONESHOT              (0x2)
#define MCF5441_PWM_SM2CCRA_EDG0(x)              (((x)&0x3)<<0x2)
#define MCF5441_PWM_SM2CCRA_EDG1(x)              (((x)&0x3)<<0x4)
#define MCF5441_PWM_SM2CCRA_INP_SEL              (0x40)
#define MCF5441_PWM_SM2CCRA_EDGCNT_EN            (0x80)
#define MCF5441_PWM_SM2CCRA_CFWM(x)              (((x)&0x3)<<0x8)
#define MCF5441_PWM_SM2CCRA_C0CNT(x)             (((x)&0x7)<<0xA)
#define MCF5441_PWM_SM2CCRA_C1CNT(x)             (((x)&0x7)<<0xD)

/* Bit definitions and macros for MCF5441_PWM_SM2CCMPA */
#define MCF5441_PWM_SM2CCMPA_EDGCMP(x)           (((x)&0xFF)<<0)
#define MCF5441_PWM_SM2CCMPA_EDGCNT(x)           (((x)&0xFF)<<0x8)

/* Bit definitions and macros for MCF5441_PWM_SM2CCRB */
#define MCF5441_PWM_SM2CCRB_ARM                  (0x1)
#define MCF5441_PWM_SM2CCRB_ONESHOT              (0x2)
#define MCF5441_PWM_SM2CCRB_EDG0(x)              (((x)&0x3)<<0x2)
#define MCF5441_PWM_SM2CCRB_EDG1(x)              (((x)&0x3)<<0x4)
#define MCF5441_PWM_SM2CCRB_INP_SEL              (0x40)
#define MCF5441_PWM_SM2CCRB_EDGCNT_EN            (0x80)
#define MCF5441_PWM_SM2CCRB_CFWM(x)              (((x)&0x3)<<0x8)
#define MCF5441_PWM_SM2CCRB_C0CNT(x)             (((x)&0x7)<<0xA)
#define MCF5441_PWM_SM2CCRB_C1CNT(x)             (((x)&0x7)<<0xD)

/* Bit definitions and macros for MCF5441_PWM_SM2CCMPB */
#define MCF5441_PWM_SM2CCMPB_EDGCMP(x)           (((x)&0xFF)<<0)
#define MCF5441_PWM_SM2CCMPB_EDGCNT(x)           (((x)&0xFF)<<0x8)

/* Bit definitions and macros for MCF5441_PWM_SM2CCRX */
#define MCF5441_PWM_SM2CCRX_ARM                  (0x1)
#define MCF5441_PWM_SM2CCRX_ONESHOT              (0x2)
#define MCF5441_PWM_SM2CCRX_EDG0(x)              (((x)&0x3)<<0x2)
#define MCF5441_PWM_SM2CCRX_EDG1(x)              (((x)&0x3)<<0x4)
#define MCF5441_PWM_SM2CCRX_INP_SEL              (0x40)
#define MCF5441_PWM_SM2CCRX_EDGCNT_EN            (0x80)
#define MCF5441_PWM_SM2CCRX_CFWM(x)              (((x)&0x3)<<0x8)
#define MCF5441_PWM_SM2CCRX_C0CNT(x)             (((x)&0x7)<<0xA)
#define MCF5441_PWM_SM2CCRX_C1CNT(x)             (((x)&0x7)<<0xD)

/* Bit definitions and macros for MCF5441_PWM_SM2CCMPX */
#define MCF5441_PWM_SM2CCMPX_EDGCMP(x)           (((x)&0xFF)<<0)
#define MCF5441_PWM_SM2CCMPX_EDGCNT(x)           (((x)&0xFF)<<0x8)

/* Bit definitions and macros for MCF5441_PWM_SM2CVAL0 */
#define MCF5441_PWM_SM2CVAL0_CAPTVAL(x)          (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM2CCYC0 */
#define MCF5441_PWM_SM2CCYC0_CYC(x)              (((x)&0xF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM2CVAL1 */
#define MCF5441_PWM_SM2CVAL1_CAPTVAL(x)          (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM2CCYC1 */
#define MCF5441_PWM_SM2CCYC1_CYC(x)              (((x)&0xF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM2CVAL2 */
#define MCF5441_PWM_SM2CVAL2_CAPTVAL(x)          (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM2CCYC2 */
#define MCF5441_PWM_SM2CCYC2_CYC(x)              (((x)&0xF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM2CVAL3 */
#define MCF5441_PWM_SM2CVAL3_CAPTVAL(x)          (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM2CCYC3 */
#define MCF5441_PWM_SM2CCYC3_CYC(x)              (((x)&0xF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM2CVAL4 */
#define MCF5441_PWM_SM2CVAL4_CAPTVAL(x)          (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM2CCYC4 */
#define MCF5441_PWM_SM2CCYC4_CYC(x)              (((x)&0xF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM2CVAL5 */
#define MCF5441_PWM_SM2CVAL5_CAPTVAL(x)          (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM2CCYC5 */
#define MCF5441_PWM_SM2CCYC5_CYC(x)              (((x)&0xF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM3CNT */
#define MCF5441_PWM_SM3CNT_CNT(x)                (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM3INIT */
#define MCF5441_PWM_SM3INIT_INIT(x)              (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM3CR2 */
#define MCF5441_PWM_SM3CR2_CLK_SEL(x)            (((x)&0x3)<<0)
#define MCF5441_PWM_SM3CR2_RELOAD_SEL            (0x4)
#define MCF5441_PWM_SM3CR2_FORCE_SEL(x)          (((x)&0x7)<<0x3)
#define MCF5441_PWM_SM3CR2_FORCE                 (0x40)
#define MCF5441_PWM_SM3CR2_FRCEN                 (0x80)
#define MCF5441_PWM_SM3CR2_INIT_SEL(x)           (((x)&0x3)<<0x8)
#define MCF5441_PWM_SM3CR2_PWMX_INIT             (0x400)
#define MCF5441_PWM_SM3CR2_PWM45_INIT            (0x800)
#define MCF5441_PWM_SM3CR2_PWM23_INIT            (0x1000)
#define MCF5441_PWM_SM3CR2_INDEP                 (0x2000)
#define MCF5441_PWM_SM3CR2_WAITEN                (0x4000)
#define MCF5441_PWM_SM3CR2_DBGEN                 (0x8000)

/* Bit definitions and macros for MCF5441_PWM_SM3CR */
#define MCF5441_PWM_SM3CR_DBLEN                  (0x1)
#define MCF5441_PWM_SM3CR_LDMOD                  (0x4)
#define MCF5441_PWM_SM3CR_PRSC(x)                (((x)&0x7)<<0x4)
#define MCF5441_PWM_SM3CR_DT(x)                  (((x)&0x3)<<0x8)
#define MCF5441_PWM_SM3CR_FULL                   (0x400)
#define MCF5441_PWM_SM3CR_HALF                   (0x800)
#define MCF5441_PWM_SM3CR_LDFQ(x)                (((x)&0xF)<<0xC)

/* Bit definitions and macros for MCF5441_PWM_SM3VAL0 */
#define MCF5441_PWM_SM3VAL0_VAL0(x)              (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM3VAL1 */
#define MCF5441_PWM_SM3VAL1_VAL1(x)              (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM3VAL2 */
#define MCF5441_PWM_SM3VAL2_VAL2(x)              (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM3VAL3 */
#define MCF5441_PWM_SM3VAL3_VAL3(x)              (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM3VAL4 */
#define MCF5441_PWM_SM3VAL4_VAL4(x)              (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM3VAL5 */
#define MCF5441_PWM_SM3VAL5_VAL5(x)              (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM3OCR */
#define MCF5441_PWM_SM3OCR_PWMXFS(x)             (((x)&0x3)<<0)
#define MCF5441_PWM_SM3OCR_PWMBFS(x)             (((x)&0x3)<<0x2)
#define MCF5441_PWM_SM3OCR_PWMAFS(x)             (((x)&0x3)<<0x4)
#define MCF5441_PWM_SM3OCR_POLX                  (0x100)
#define MCF5441_PWM_SM3OCR_POLB                  (0x200)
#define MCF5441_PWM_SM3OCR_POLA                  (0x400)
#define MCF5441_PWM_SM3OCR_PWMX_IN               (0x2000)
#define MCF5441_PWM_SM3OCR_PWMB_IN               (0x4000)
#define MCF5441_PWM_SM3OCR_PWMA_IN               (0x8000)

/* Bit definitions and macros for MCF5441_PWM_SM3SR */
#define MCF5441_PWM_SM3SR_CMPF(x)                (((x)&0x3F)<<0)
#define MCF5441_PWM_SM3SR_CFX0                   (0x40)
#define MCF5441_PWM_SM3SR_CFX1                   (0x80)
#define MCF5441_PWM_SM3SR_CFB0                   (0x100)
#define MCF5441_PWM_SM3SR_CFB1                   (0x200)
#define MCF5441_PWM_SM3SR_CFA0                   (0x400)
#define MCF5441_PWM_SM3SR_CFA1                   (0x800)
#define MCF5441_PWM_SM3SR_RF                     (0x1000)
#define MCF5441_PWM_SM3SR_REF                    (0x2000)
#define MCF5441_PWM_SM3SR_RUF                    (0x4000)

/* Bit definitions and macros for MCF5441_PWM_SM3IER */
#define MCF5441_PWM_SM3IER_CMPIE(x)              (((x)&0x3F)<<0)
#define MCF5441_PWM_SM3IER_CX0IE                 (0x40)
#define MCF5441_PWM_SM3IER_CX1IE                 (0x80)
#define MCF5441_PWM_SM3IER_CB0IE                 (0x100)
#define MCF5441_PWM_SM3IER_CB1IE                 (0x200)
#define MCF5441_PWM_SM3IER_CA0IE                 (0x400)
#define MCF5441_PWM_SM3IER_CA1IE                 (0x800)
#define MCF5441_PWM_SM3IER_RIE                   (0x1000)
#define MCF5441_PWM_SM3IER_REIE                  (0x2000)

/* Bit definitions and macros for MCF5441_PWM_SM3DMAEN */
#define MCF5441_PWM_SM3DMAEN_CX0DE               (0x1)
#define MCF5441_PWM_SM3DMAEN_CX1DE               (0x2)
#define MCF5441_PWM_SM3DMAEN_CB0DE               (0x4)
#define MCF5441_PWM_SM3DMAEN_CB1DE               (0x8)
#define MCF5441_PWM_SM3DMAEN_CA0DE               (0x10)
#define MCF5441_PWM_SM3DMAEN_CA1DE               (0x20)
#define MCF5441_PWM_SM3DMAEN_CAPTDE(x)           (((x)&0x3)<<0x6)
#define MCF5441_PWM_SM3DMAEN_FAND                (0x100)
#define MCF5441_PWM_SM3DMAEN_VALDE               (0x200)

/* Bit definitions and macros for MCF5441_PWM_SM3OTCR */
#define MCF5441_PWM_SM3OTCR_OUT_TRIG_EN(x)       (((x)&0x3F)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM3DISMAP */
#define MCF5441_PWM_SM3DISMAP_DISA(x)            (((x)&0xF)<<0)
#define MCF5441_PWM_SM3DISMAP_DISB(x)            (((x)&0xF)<<0x4)
#define MCF5441_PWM_SM3DISMAP_DISX(x)            (((x)&0xF)<<0x8)

/* Bit definitions and macros for MCF5441_PWM_SM3DTCNT0 */
#define MCF5441_PWM_SM3DTCNT0_DTCNT0(x)          (((x)&0x7FF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM3DTCNT1 */
#define MCF5441_PWM_SM3DTCNT1_DTCNT1(x)          (((x)&0x7FF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM3CCRA */
#define MCF5441_PWM_SM3CCRA_ARM                  (0x1)
#define MCF5441_PWM_SM3CCRA_ONESHOT              (0x2)
#define MCF5441_PWM_SM3CCRA_EDG0(x)              (((x)&0x3)<<0x2)
#define MCF5441_PWM_SM3CCRA_EDG1(x)              (((x)&0x3)<<0x4)
#define MCF5441_PWM_SM3CCRA_INP_SEL              (0x40)
#define MCF5441_PWM_SM3CCRA_EDGCNT_EN            (0x80)
#define MCF5441_PWM_SM3CCRA_CFWM(x)              (((x)&0x3)<<0x8)
#define MCF5441_PWM_SM3CCRA_C0CNT(x)             (((x)&0x7)<<0xA)
#define MCF5441_PWM_SM3CCRA_C1CNT(x)             (((x)&0x7)<<0xD)

/* Bit definitions and macros for MCF5441_PWM_SM3CCMPA */
#define MCF5441_PWM_SM3CCMPA_EDGCMP(x)           (((x)&0xFF)<<0)
#define MCF5441_PWM_SM3CCMPA_EDGCNT(x)           (((x)&0xFF)<<0x8)

/* Bit definitions and macros for MCF5441_PWM_SM3CCRB */
#define MCF5441_PWM_SM3CCRB_ARM                  (0x1)
#define MCF5441_PWM_SM3CCRB_ONESHOT              (0x2)
#define MCF5441_PWM_SM3CCRB_EDG0(x)              (((x)&0x3)<<0x2)
#define MCF5441_PWM_SM3CCRB_EDG1(x)              (((x)&0x3)<<0x4)
#define MCF5441_PWM_SM3CCRB_INP_SEL              (0x40)
#define MCF5441_PWM_SM3CCRB_EDGCNT_EN            (0x80)
#define MCF5441_PWM_SM3CCRB_CFWM(x)              (((x)&0x3)<<0x8)
#define MCF5441_PWM_SM3CCRB_C0CNT(x)             (((x)&0x7)<<0xA)
#define MCF5441_PWM_SM3CCRB_C1CNT(x)             (((x)&0x7)<<0xD)

/* Bit definitions and macros for MCF5441_PWM_SM3CCMPB */
#define MCF5441_PWM_SM3CCMPB_EDGCMP(x)           (((x)&0xFF)<<0)
#define MCF5441_PWM_SM3CCMPB_EDGCNT(x)           (((x)&0xFF)<<0x8)

/* Bit definitions and macros for MCF5441_PWM_SM3CCRX */
#define MCF5441_PWM_SM3CCRX_ARM                  (0x1)
#define MCF5441_PWM_SM3CCRX_ONESHOT              (0x2)
#define MCF5441_PWM_SM3CCRX_EDG0(x)              (((x)&0x3)<<0x2)
#define MCF5441_PWM_SM3CCRX_EDG1(x)              (((x)&0x3)<<0x4)
#define MCF5441_PWM_SM3CCRX_INP_SEL              (0x40)
#define MCF5441_PWM_SM3CCRX_EDGCNT_EN            (0x80)
#define MCF5441_PWM_SM3CCRX_CFWM(x)              (((x)&0x3)<<0x8)
#define MCF5441_PWM_SM3CCRX_C0CNT(x)             (((x)&0x7)<<0xA)
#define MCF5441_PWM_SM3CCRX_C1CNT(x)             (((x)&0x7)<<0xD)

/* Bit definitions and macros for MCF5441_PWM_SM3CCMPX */
#define MCF5441_PWM_SM3CCMPX_EDGCMP(x)           (((x)&0xFF)<<0)
#define MCF5441_PWM_SM3CCMPX_EDGCNT(x)           (((x)&0xFF)<<0x8)

/* Bit definitions and macros for MCF5441_PWM_SM3CVAL0 */
#define MCF5441_PWM_SM3CVAL0_CAPTVAL(x)          (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM3CCYC0 */
#define MCF5441_PWM_SM3CCYC0_CYC(x)              (((x)&0xF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM3CVAL1 */
#define MCF5441_PWM_SM3CVAL1_CAPTVAL(x)          (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM3CCYC1 */
#define MCF5441_PWM_SM3CCYC1_CYC(x)              (((x)&0xF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM3CVAL2 */
#define MCF5441_PWM_SM3CVAL2_CAPTVAL(x)          (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM3CCYC2 */
#define MCF5441_PWM_SM3CCYC2_CYC(x)              (((x)&0xF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM3CVAL3 */
#define MCF5441_PWM_SM3CVAL3_CAPTVAL(x)          (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM3CCYC3 */
#define MCF5441_PWM_SM3CCYC3_CYC(x)              (((x)&0xF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM3CVAL4 */
#define MCF5441_PWM_SM3CVAL4_CAPTVAL(x)          (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM3CCYC4 */
#define MCF5441_PWM_SM3CCYC4_CYC(x)              (((x)&0xF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM3CVAL5 */
#define MCF5441_PWM_SM3CVAL5_CAPTVAL(x)          (((x)&0xFFFF)<<0)

/* Bit definitions and macros for MCF5441_PWM_SM3CCYC5 */
#define MCF5441_PWM_SM3CCYC5_CYC(x)              (((x)&0xF)<<0)

/* Bit definitions and macros for MCF5441_PWM_OUTEN */
#define MCF5441_PWM_OUTEN_PWMX_EN(x)             (((x)&0xF)<<0)
#define MCF5441_PWM_OUTEN_PWMB_EN(x)             (((x)&0xF)<<0x4)
#define MCF5441_PWM_OUTEN_PWMA_EN(x)             (((x)&0xF)<<0x8)

/* Bit definitions and macros for MCF5441_PWM_MASK */
#define MCF5441_PWM_MASK_MASKX(x)                (((x)&0xF)<<0)
#define MCF5441_PWM_MASK_MASKB(x)                (((x)&0xF)<<0x4)
#define MCF5441_PWM_MASK_MASKA(x)                (((x)&0xF)<<0x8)

/* Bit definitions and macros for MCF5441_PWM_SWCOUT */
#define MCF5441_PWM_SWCOUT_OUT45_0               (0x1)
#define MCF5441_PWM_SWCOUT_OUT23_0               (0x2)
#define MCF5441_PWM_SWCOUT_OUT45_1               (0x4)
#define MCF5441_PWM_SWCOUT_OUT23_1               (0x8)
#define MCF5441_PWM_SWCOUT_OUT45_2               (0x10)
#define MCF5441_PWM_SWCOUT_OUT23_2               (0x20)
#define MCF5441_PWM_SWCOUT_OUT45_3               (0x40)
#define MCF5441_PWM_SWCOUT_OUT23_3               (0x80)

/* Bit definitions and macros for MCF5441_PWM_DTSS */
#define MCF5441_PWM_DTSS_SEL45_0(x)              (((x)&0x3)<<0)
#define MCF5441_PWM_DTSS_SEL23_0(x)              (((x)&0x3)<<0x2)
#define MCF5441_PWM_DTSS_SEL45_1(x)              (((x)&0x3)<<0x4)
#define MCF5441_PWM_DTSS_SEL23_1(x)              (((x)&0x3)<<0x6)
#define MCF5441_PWM_DTSS_SEL45_2(x)              (((x)&0x3)<<0x8)
#define MCF5441_PWM_DTSS_SEL23_2(x)              (((x)&0x3)<<0xA)
#define MCF5441_PWM_DTSS_SEL45_3(x)              (((x)&0x3)<<0xC)
#define MCF5441_PWM_DTSS_SEL23_3(x)              (((x)&0x3)<<0xE)

/* Bit definitions and macros for MCF5441_PWM_MCR */
#define MCF5441_PWM_MCR_LDOK(x)                  (((x)&0xF)<<0)
#define MCF5441_PWM_MCR_CLDOK(x)                 (((x)&0xF)<<0x4)
#define MCF5441_PWM_MCR_RUN(x)                   (((x)&0xF)<<0x8)
#define MCF5441_PWM_MCR_IPOL(x)                  (((x)&0xF)<<0xC)

/* Bit definitions and macros for MCF5441_PWM_FCR */
#define MCF5441_PWM_FCR_FIE(x)                   (((x)&0x7)<<0)
#define MCF5441_PWM_FCR_FSAFE(x)                 (((x)&0x7)<<0x4)
#define MCF5441_PWM_FCR_FAUTO(x)                 (((x)&0x7)<<0x8)
#define MCF5441_PWM_FCR_FLVL(x)                  (((x)&0x7)<<0xC)

/* Bit definitions and macros for MCF5441_PWM_FSR */
#define MCF5441_PWM_FSR_FFLAG(x)                 (((x)&0x7)<<0)
#define MCF5441_PWM_FSR_FFULL(x)                 (((x)&0x7)<<0x4)
#define MCF5441_PWM_FSR_FFPIN(x)                 (((x)&0x7)<<0x8)
#define MCF5441_PWM_FSR_FTEST                    (0x1000)

/* Bit definitions and macros for MCF5441_PWM_FFILT */
#define MCF5441_PWM_FFILT_PER(x)                 (((x)&0xFF)<<0)
#define MCF5441_PWM_FFILT_CNT(x)                 (((x)&0x7)<<0x8)
#define MCF5441_PWM_FFILT_GSTR                   (0x8000)

/*
** MCF5441_PWM_STRUCT                                                                   
** Motor Control Pulse-Width Modulator
*/
typedef struct mcf5441_pwm_struct
{
   uint_16  PWM_SM0CNT;     // Counter register
   uint_16  PWM_SM0INIT;    // Initial Count Register
   uint_16  PWM_SM0CR2;     // Control Register 2
   uint_16  PWM_SM0CR;      // Control Register 1
   uint_16  PWM_SM0VAL0;    // Value Register 0
   uint_16  PWM_SM0VAL1;    // Value Register 1
   uint_16  PWM_SM0VAL2;    // Value Register 2
   uint_16  PWM_SM0VAL3;    // Value Register 3
   uint_16  PWM_SM0VAL4;    // Value Register 4
   uint_16  PWM_SM0VAL5;    // Value Register 5
   uint_16  filler0[2];
   uint_16  PWM_SM0OCR;     // Output Control Register
   uint_16  PWM_SM0SR;      // Status Register
   uint_16  PWM_SM0IER;     // Interrupt Enable Register
   uint_16  PWM_SM0DMAEN;   // DMA Enable Register
   uint_16  PWM_SM0OTCR;    // Output Trigger Control Register
   uint_16  PWM_SM0DISMAP;  // Fault Disable Mapping Register
   uint_16  PWM_SM0DTCNT0;  // Deadtime Count Register 0
   uint_16  PWM_SM0DTCNT1;  // Deadtime Count Register 1
   uint_16  PWM_SM0CCRA;    // Capture Control Register A
   uint_16  PWM_SM0CCMPA;   // Capture Compare Register A
   uint_16  PWM_SM0CCRB;    // Capture Control Register B
   uint_16  PWM_SM0CCMPB;   // Capture Compare Register B
   uint_16  PWM_SM0CCRX;    // Capture Control Register X
   uint_16  PWM_SM0CCMPX;   // Capture Compare Register X
   uint_16  PWM_SM0CVAL0;   // Capture Value 0 Register
   uint_16  PWM_SM0CCYC0;   // Capture Value 0 Cycle Register
   uint_16  PWM_SM0CVAL1;   // Capture Value 1 Register
   uint_16  PWM_SM0CCYC1;   // Capture Value 1 Cycle Register
   uint_16  PWM_SM0CVAL2;   // Capture Value 2 Register
   uint_16  PWM_SM0CCYC2;   // Capture Value 2 Cycle Register
   uint_16  PWM_SM0CVAL3;   // Capture Value 3 Register
   uint_16  PWM_SM0CCYC3;   // Capture Value 3 Cycle Register
   uint_16  PWM_SM0CVAL4;   // Capture Value 4 Register
   uint_16  PWM_SM0CCYC4;   // Capture Value 4 Cycle Register
   uint_16  PWM_SM0CVAL5;   // Capture Value 5 Register
   uint_16  PWM_SM0CCYC5;   // Capture Value 5 Register
   uint_16  filler1[2];
   uint_16  PWM_SM1CNT;     // Counter register
   uint_16  PWM_SM1INIT;    // Initial Count Register
   uint_16  PWM_SM1CR2;     // Control Register 2
   uint_16  PWM_SM1CR;      // Control Register 1
   uint_16  PWM_SM1VAL0;    // Value Register 0
   uint_16  PWM_SM1VAL1;    // Value Register 1
   uint_16  PWM_SM1VAL2;    // Value Register 2
   uint_16  PWM_SM1VAL3;    // Value Register 3
   uint_16  PWM_SM1VAL4;    // Value Register 4
   uint_16  PWM_SM1VAL5;    // Value Register 5
   uint_16  filler2[2];
   uint_16  PWM_SM1OCR;     // Output Control Register
   uint_16  PWM_SM1SR;      // Status Register
   uint_16  PWM_SM1IER;     // Interrupt Enable Register
   uint_16  PWM_SM1DMAEN;   // DMA Enable Register
   uint_16  PWM_SM1OTCR;    // Output Trigger Control Register
   uint_16  PWM_SM1DISMAP;  // Fault Disable Mapping Register
   uint_16  PWM_SM1DTCNT0;  // Deadtime Count Register 0
   uint_16  PWM_SM1DTCNT1;  // Deadtime Count Register 1
   uint_16  PWM_SM1CCRA;    // Capture Control Register A
   uint_16  PWM_SM1CCMPA;   // Capture Compare Register A
   uint_16  PWM_SM1CCRB;    // Capture Control Register B
   uint_16  PWM_SM1CCMPB;   // Capture Compare Register B
   uint_16  PWM_SM1CCRX;    // Capture Control Register X
   uint_16  PWM_SM1CCMPX;   // Capture Compare Register X
   uint_16  PWM_SM1CVAL0;   // Capture Value 0 Register
   uint_16  PWM_SM1CCYC0;   // Capture Value 0 Cycle Register
   uint_16  PWM_SM1CVAL1;   // Capture Value 1 Register
   uint_16  PWM_SM1CCYC1;   // Capture Value 1 Cycle Register
   uint_16  PWM_SM1CVAL2;   // Capture Value 2 Register
   uint_16  PWM_SM1CCYC2;   // Capture Value 2 Cycle Register
   uint_16  PWM_SM1CVAL3;   // Capture Value 3 Register
   uint_16  PWM_SM1CCYC3;   // Capture Value 3 Cycle Register
   uint_16  PWM_SM1CVAL4;   // Capture Value 4 Register
   uint_16  PWM_SM1CCYC4;   // Capture Value 4 Cycle Register
   uint_16  PWM_SM1CVAL5;   // Capture Value 5 Register
   uint_16  PWM_SM1CCYC5;   // Capture Value 5 Register
   uint_16  filler3[2];
   uint_16  PWM_SM2CNT;     // Counter register
   uint_16  PWM_SM2INIT;    // Initial Count Register
   uint_16  PWM_SM2CR2;     // Control Register 2
   uint_16  PWM_SM2CR;      // Control Register 1
   uint_16  PWM_SM2VAL0;    // Value Register 0
   uint_16  PWM_SM2VAL1;    // Value Register 1
   uint_16  PWM_SM2VAL2;    // Value Register 2
   uint_16  PWM_SM2VAL3;    // Value Register 3
   uint_16  PWM_SM2VAL4;    // Value Register 4
   uint_16  PWM_SM2VAL5;    // Value Register 5
   uint_16  filler4[2];
   uint_16  PWM_SM2OCR;     // Output Control Register
   uint_16  PWM_SM2SR;      // Status Register
   uint_16  PWM_SM2IER;     // Interrupt Enable Register
   uint_16  PWM_SM2DMAEN;   // DMA Enable Register
   uint_16  PWM_SM2OTCR;    // Output Trigger Control Register
   uint_16  PWM_SM2DISMAP;  // Fault Disable Mapping Register
   uint_16  PWM_SM2DTCNT0;  // Deadtime Count Register 0
   uint_16  PWM_SM2DTCNT1;  // Deadtime Count Register 1
   uint_16  PWM_SM2CCRA;    // Capture Control Register A
   uint_16  PWM_SM2CCMPA;   // Capture Compare Register A
   uint_16  PWM_SM2CCRB;    // Capture Control Register B
   uint_16  PWM_SM2CCMPB;   // Capture Compare Register B
   uint_16  PWM_SM2CCRX;    // Capture Control Register X
   uint_16  PWM_SM2CCMPX;   // Capture Compare Register X
   uint_16  PWM_SM2CVAL0;   // Capture Value 0 Register
   uint_16  PWM_SM2CCYC0;   // Capture Value 0 Cycle Register
   uint_16  PWM_SM2CVAL1;   // Capture Value 1 Register
   uint_16  PWM_SM2CCYC1;   // Capture Value 1 Cycle Register
   uint_16  PWM_SM2CVAL2;   // Capture Value 2 Register
   uint_16  PWM_SM2CCYC2;   // Capture Value 2 Cycle Register
   uint_16  PWM_SM2CVAL3;   // Capture Value 3 Register
   uint_16  PWM_SM2CCYC3;   // Capture Value 3 Cycle Register
   uint_16  PWM_SM2CVAL4;   // Capture Value 4 Register
   uint_16  PWM_SM2CCYC4;   // Capture Value 4 Cycle Register
   uint_16  PWM_SM2CVAL5;   // Capture Value 5 Register
   uint_16  PWM_SM2CCYC5;   // Capture Value 5 Register
   uint_16  filler5[2];
   uint_16  PWM_SM3CNT;     // Counter register
   uint_16  PWM_SM3INIT;    // Initial Count Register
   uint_16  PWM_SM3CR2;     // Control Register 2
   uint_16  PWM_SM3CR;      // Control Register 1
   uint_16  PWM_SM3VAL0;    // Value Register 0
   uint_16  PWM_SM3VAL1;    // Value Register 1
   uint_16  PWM_SM3VAL2;    // Value Register 2
   uint_16  PWM_SM3VAL3;    // Value Register 3
   uint_16  PWM_SM3VAL4;    // Value Register 4
   uint_16  PWM_SM3VAL5;    // Value Register 5
   uint_16  filler6[2];
   uint_16  PWM_SM3OCR;     // Output Control Register
   uint_16  PWM_SM3SR;      // Status Register
   uint_16  PWM_SM3IER;     // Interrupt Enable Register
   uint_16  PWM_SM3DMAEN;   // DMA Enable Register
   uint_16  PWM_SM3OTCR;    // Output Trigger Control Register
   uint_16  PWM_SM3DISMAP;  // Fault Disable Mapping Register
   uint_16  PWM_SM3DTCNT0;  // Deadtime Count Register 0
   uint_16  PWM_SM3DTCNT1;  // Deadtime Count Register 1
   uint_16  PWM_SM3CCRA;    // Capture Control Register A
   uint_16  PWM_SM3CCMPA;   // Capture Compare Register A
   uint_16  PWM_SM3CCRB;    // Capture Control Register B
   uint_16  PWM_SM3CCMPB;   // Capture Compare Register B
   uint_16  PWM_SM3CCRX;    // Capture Control Register X
   uint_16  PWM_SM3CCMPX;   // Capture Compare Register X
   uint_16  PWM_SM3CVAL0;   // Capture Value 0 Register
   uint_16  PWM_SM3CCYC0;   // Capture Value 0 Cycle Register
   uint_16  PWM_SM3CVAL1;   // Capture Value 1 Register
   uint_16  PWM_SM3CCYC1;   // Capture Value 1 Cycle Register
   uint_16  PWM_SM3CVAL2;   // Capture Value 2 Register
   uint_16  PWM_SM3CCYC2;   // Capture Value 2 Cycle Register
   uint_16  PWM_SM3CVAL3;   // Capture Value 3 Register
   uint_16  PWM_SM3CCYC3;   // Capture Value 3 Cycle Register
   uint_16  PWM_SM3CVAL4;   // Capture Value 4 Register
   uint_16  PWM_SM3CCYC4;   // Capture Value 4 Cycle Register
   uint_16  PWM_SM3CVAL5;   // Capture Value 5 Register
   uint_16  PWM_SM3CCYC5;   // Capture Value 5 Register
   uint_16  filler7[2];
   uint_16  PWM_OUTEN;      // Output Enable Register
   uint_16  PWM_MASK;       // Output Mask Register
   uint_16  PWM_SWCOUT;     // Software Controlled Output Register
   uint_16  PWM_DTSS;       // Deadtime Source Select Register
   uint_16  PWM_MCR;        // Master Control Register
   uint_16  filler8;
   uint_16  PWM_FCR;        // Fault Control Register
   uint_16  PWM_FSR;        // Fault Status Register
   uint_16  PWM_FFILT;      // Fault Filter Register
} MCF5441_PWM_STRUCT, _PTR_ MCF5441_PWM_STRUCT_PTR;
typedef volatile struct mcf5441_pwm_struct _PTR_ VMCF5441_PWM_STRUCT_PTR;


/* Bit definitions and macros for MCF5441_XBS_PRS0 */
#define MCF5441_XBS_PRS0_M0(x)               (((x)&0x7)<<0)
#define MCF5441_XBS_PRS0_M1(x)               (((x)&0x7)<<0x4)
#define MCF5441_XBS_PRS0_M2(x)               (((x)&0x7)<<0x8)
#define MCF5441_XBS_PRS0_M3(x)               (((x)&0x7)<<0xC)
#define MCF5441_XBS_PRS0_M4(x)               (((x)&0x7)<<0x10)
#define MCF5441_XBS_PRS0_M5(x)               (((x)&0x7)<<0x14)
#define MCF5441_XBS_PRS0_M6(x)               (((x)&0x7)<<0x18)
#define MCF5441_XBS_PRS0_M7(x)               (((x)&0x7)<<0x1C)

/* Bit definitions and macros for MCF5441_XBS_CRS0 */
#define MCF5441_XBS_CRS0_PARK(x)             (((x)&0x7)<<0)
#define MCF5441_XBS_CRS0_PARK_CORE           (0)
#define MCF5441_XBS_CRS0_PARK_EDMA           (0x1)
#define MCF5441_XBS_CRS0_PARK_USB_OTG        (0x2)
#define MCF5441_XBS_CRS0_PARK_M3_ETH         (0x3)
#define MCF5441_XBS_CRS0_PARK_M4_ETH         (0x4)
#define MCF5441_XBS_CRS0_PARK_SDHC           (0x5)
#define MCF5441_XBS_CRS0_PARK_USB_HOST       (0x6)
#define MCF5441_XBS_CRS0_PARK_NANDFLASH      (0x7)
#define MCF5441_XBS_CRS0_PCTL(x)             (((x)&0x3)<<0x4)
#define MCF5441_XBS_CRS0_PCTL_PARK_FIELD     (0)
#define MCF5441_XBS_CRS0_PCTL_PARK_ON_LAST   (0x10)
#define MCF5441_XBS_CRS0_PCTL_PARK_NO_MASTER (0x20)
#define MCF5441_XBS_CRS0_ARB                 (0x100)
#define MCF5441_XBS_CRS0_RO                  (0x80000000)

/* Bit definitions and macros for MCF5441_XBS_PRS1 */
#define MCF5441_XBS_PRS1_M0(x)               (((x)&0x7)<<0)
#define MCF5441_XBS_PRS1_M1(x)               (((x)&0x7)<<0x4)
#define MCF5441_XBS_PRS1_M2(x)               (((x)&0x7)<<0x8)
#define MCF5441_XBS_PRS1_M3(x)               (((x)&0x7)<<0xC)
#define MCF5441_XBS_PRS1_M4(x)               (((x)&0x7)<<0x10)
#define MCF5441_XBS_PRS1_M5(x)               (((x)&0x7)<<0x14)
#define MCF5441_XBS_PRS1_M6(x)               (((x)&0x7)<<0x18)
#define MCF5441_XBS_PRS1_M7(x)               (((x)&0x7)<<0x1C)

/* Bit definitions and macros for MCF5441_XBS_CRS1 */
#define MCF5441_XBS_CRS1_PARK(x)             (((x)&0x7)<<0)
#define MCF5441_XBS_CRS1_PARK_CORE           (0)
#define MCF5441_XBS_CRS1_PARK_EDMA           (0x1)
#define MCF5441_XBS_CRS1_PARK_USB_OTG        (0x2)
#define MCF5441_XBS_CRS1_PARK_M3_ETH         (0x3)
#define MCF5441_XBS_CRS1_PARK_M4_ETH         (0x4)
#define MCF5441_XBS_CRS1_PARK_SDHC           (0x5)
#define MCF5441_XBS_CRS1_PARK_USB_HOST       (0x6)
#define MCF5441_XBS_CRS1_PARK_NANDFLASH      (0x7)
#define MCF5441_XBS_CRS1_PCTL(x)             (((x)&0x3)<<0x4)
#define MCF5441_XBS_CRS1_PCTL_PARK_FIELD     (0)
#define MCF5441_XBS_CRS1_PCTL_PARK_ON_LAST   (0x10)
#define MCF5441_XBS_CRS1_PCTL_PARK_NO_MASTER (0x20)
#define MCF5441_XBS_CRS1_ARB                 (0x100)
#define MCF5441_XBS_CRS1_RO                  (0x80000000)

/* Bit definitions and macros for MCF5441_XBS_PRS2 */
#define MCF5441_XBS_PRS2_M0(x)               (((x)&0x7)<<0)
#define MCF5441_XBS_PRS2_M1(x)               (((x)&0x7)<<0x4)
#define MCF5441_XBS_PRS2_M2(x)               (((x)&0x7)<<0x8)
#define MCF5441_XBS_PRS2_M3(x)               (((x)&0x7)<<0xC)
#define MCF5441_XBS_PRS2_M4(x)               (((x)&0x7)<<0x10)
#define MCF5441_XBS_PRS2_M5(x)               (((x)&0x7)<<0x14)
#define MCF5441_XBS_PRS2_M6(x)               (((x)&0x7)<<0x18)
#define MCF5441_XBS_PRS2_M7(x)               (((x)&0x7)<<0x1C)

/* Bit definitions and macros for MCF5441_XBS_CRS2 */
#define MCF5441_XBS_CRS2_PARK(x)             (((x)&0x7)<<0)
#define MCF5441_XBS_CRS2_PARK_CORE           (0)
#define MCF5441_XBS_CRS2_PARK_EDMA           (0x1)
#define MCF5441_XBS_CRS2_PARK_USB_OTG        (0x2)
#define MCF5441_XBS_CRS2_PARK_M3_ETH         (0x3)
#define MCF5441_XBS_CRS2_PARK_M4_ETH         (0x4)
#define MCF5441_XBS_CRS2_PARK_SDHC           (0x5)
#define MCF5441_XBS_CRS2_PARK_USB_HOST       (0x6)
#define MCF5441_XBS_CRS2_PARK_NANDFLASH      (0x7)
#define MCF5441_XBS_CRS2_PCTL(x)             (((x)&0x3)<<0x4)
#define MCF5441_XBS_CRS2_PCTL_PARK_FIELD     (0)
#define MCF5441_XBS_CRS2_PCTL_PARK_ON_LAST   (0x10)
#define MCF5441_XBS_CRS2_PCTL_PARK_NO_MASTER (0x20)
#define MCF5441_XBS_CRS2_ARB                 (0x100)
#define MCF5441_XBS_CRS2_RO                  (0x80000000)

/* Bit definitions and macros for MCF5441_XBS_PRS4 */
#define MCF5441_XBS_PRS4_M0(x)               (((x)&0x7)<<0)
#define MCF5441_XBS_PRS4_M1(x)               (((x)&0x7)<<0x4)
#define MCF5441_XBS_PRS4_M2(x)               (((x)&0x7)<<0x8)
#define MCF5441_XBS_PRS4_M3(x)               (((x)&0x7)<<0xC)
#define MCF5441_XBS_PRS4_M4(x)               (((x)&0x7)<<0x10)
#define MCF5441_XBS_PRS4_M5(x)               (((x)&0x7)<<0x14)
#define MCF5441_XBS_PRS4_M6(x)               (((x)&0x7)<<0x18)
#define MCF5441_XBS_PRS4_M7(x)               (((x)&0x7)<<0x1C)

/* Bit definitions and macros for MCF5441_XBS_CRS4 */
#define MCF5441_XBS_CRS4_PARK(x)             (((x)&0x7)<<0)
#define MCF5441_XBS_CRS4_PARK_CORE           (0)
#define MCF5441_XBS_CRS4_PARK_EDMA           (0x1)
#define MCF5441_XBS_CRS4_PARK_USB_OTG        (0x2)
#define MCF5441_XBS_CRS4_PARK_M3_ETH         (0x3)
#define MCF5441_XBS_CRS4_PARK_M4_ETH         (0x4)
#define MCF5441_XBS_CRS4_PARK_SDHC           (0x5)
#define MCF5441_XBS_CRS4_PARK_USB_HOST       (0x6)
#define MCF5441_XBS_CRS4_PARK_NANDFLASH      (0x7)
#define MCF5441_XBS_CRS4_PCTL(x)             (((x)&0x3)<<0x4)
#define MCF5441_XBS_CRS4_PCTL_PARK_FIELD     (0)
#define MCF5441_XBS_CRS4_PCTL_PARK_ON_LAST   (0x10)
#define MCF5441_XBS_CRS4_PCTL_PARK_NO_MASTER (0x20)
#define MCF5441_XBS_CRS4_ARB                 (0x100)
#define MCF5441_XBS_CRS4_RO                  (0x80000000)

/* Bit definitions and macros for MCF5441_XBS_PRS6 */
#define MCF5441_XBS_PRS6_M0(x)               (((x)&0x7)<<0)
#define MCF5441_XBS_PRS6_M1(x)               (((x)&0x7)<<0x4)
#define MCF5441_XBS_PRS6_M2(x)               (((x)&0x7)<<0x8)
#define MCF5441_XBS_PRS6_M3(x)               (((x)&0x7)<<0xC)
#define MCF5441_XBS_PRS6_M4(x)               (((x)&0x7)<<0x10)
#define MCF5441_XBS_PRS6_M5(x)               (((x)&0x7)<<0x14)
#define MCF5441_XBS_PRS6_M6(x)               (((x)&0x7)<<0x18)
#define MCF5441_XBS_PRS6_M7(x)               (((x)&0x7)<<0x1C)

/* Bit definitions and macros for MCF5441_XBS_CRS6 */
#define MCF5441_XBS_CRS6_PARK(x)             (((x)&0x7)<<0)
#define MCF5441_XBS_CRS6_PARK_CORE           (0)
#define MCF5441_XBS_CRS6_PARK_EDMA           (0x1)
#define MCF5441_XBS_CRS6_PARK_USB_OTG        (0x2)
#define MCF5441_XBS_CRS6_PARK_M3_ETH         (0x3)
#define MCF5441_XBS_CRS6_PARK_M4_ETH         (0x4)
#define MCF5441_XBS_CRS6_PARK_SDHC           (0x5)
#define MCF5441_XBS_CRS6_PARK_USB_HOST       (0x6)
#define MCF5441_XBS_CRS6_PARK_NANDFLASH      (0x7)
#define MCF5441_XBS_CRS6_PCTL(x)             (((x)&0x3)<<0x4)
#define MCF5441_XBS_CRS6_PCTL_PARK_FIELD     (0)
#define MCF5441_XBS_CRS6_PCTL_PARK_ON_LAST   (0x10)
#define MCF5441_XBS_CRS6_PCTL_PARK_NO_MASTER (0x20)
#define MCF5441_XBS_CRS6_ARB                 (0x100)
#define MCF5441_XBS_CRS6_RO                  (0x80000000)

/* Bit definitions and macros for MCF5441_XBS_PRS7 */
#define MCF5441_XBS_PRS7_M0(x)               (((x)&0x7)<<0)
#define MCF5441_XBS_PRS7_M1(x)               (((x)&0x7)<<0x4)
#define MCF5441_XBS_PRS7_M2(x)               (((x)&0x7)<<0x8)
#define MCF5441_XBS_PRS7_M3(x)               (((x)&0x7)<<0xC)
#define MCF5441_XBS_PRS7_M4(x)               (((x)&0x7)<<0x10)
#define MCF5441_XBS_PRS7_M5(x)               (((x)&0x7)<<0x14)
#define MCF5441_XBS_PRS7_M6(x)               (((x)&0x7)<<0x18)
#define MCF5441_XBS_PRS7_M7(x)               (((x)&0x7)<<0x1C)

/* Bit definitions and macros for MCF5441_XBS_CRS7 */
#define MCF5441_XBS_CRS7_PARK(x)             (((x)&0x7)<<0)
#define MCF5441_XBS_CRS7_PARK_CORE           (0)
#define MCF5441_XBS_CRS7_PARK_EDMA           (0x1)
#define MCF5441_XBS_CRS7_PARK_USB_OTG        (0x2)
#define MCF5441_XBS_CRS7_PARK_M3_ETH         (0x3)
#define MCF5441_XBS_CRS7_PARK_M4_ETH         (0x4)
#define MCF5441_XBS_CRS7_PARK_SDHC           (0x5)
#define MCF5441_XBS_CRS7_PARK_USB_HOST       (0x6)
#define MCF5441_XBS_CRS7_PARK_NANDFLASH      (0x7)
#define MCF5441_XBS_CRS7_PCTL(x)             (((x)&0x3)<<0x4)
#define MCF5441_XBS_CRS7_PCTL_PARK_FIELD     (0)
#define MCF5441_XBS_CRS7_PCTL_PARK_ON_LAST   (0x10)
#define MCF5441_XBS_CRS7_PCTL_PARK_NO_MASTER (0x20)
#define MCF5441_XBS_CRS7_ARB                 (0x100)
#define MCF5441_XBS_CRS7_RO                  (0x80000000)


/*
** Cross-Bar Switch Module
*/
typedef struct mcf5441_xbs_struct {
    uint_32 XBS_PRS0; // Priority Register Slave 0
    uint_32 filler0[3];
    uint_32 XBS_CRS0; // Control Register Slave 0
    uint_32 filler1[59];
    uint_32 XBS_PRS1; // Priority Register Slave 1
    uint_32 filler2[3];
    uint_32 XBS_CRS1; // Control Register Slave 1
    uint_32 filler3[59];
    uint_32 XBS_PRS2; // Priority Register Slave 2
    uint_32 filler4[3];
    uint_32 XBS_CRS2; // Control Register Slave 2
    uint_32 filler5[123];
    uint_32 XBS_PRS4; // Priority Register Slave 4
    uint_32 filler6[3];
    uint_32 XBS_CRS4; // Control Register Slave 4
    uint_32 filler7[123];
    uint_32 XBS_PRS6; // Priority Register Slave 6
    uint_32 filler8[3];
    uint_32 XBS_CRS6; // Control Register Slave 6
    uint_32 filler9[59];
    uint_32 XBS_PRS7; // Priority Register Slave 7
    uint_32 filler10[3];
    uint_32 XBS_CRS7; // Control Register Slave 7
} MCF5441_XBS_STRUCT, _PTR_ MCF5441_XBS_STRUCT_PTR;
typedef volatile struct mcf5441_xbs_struct _PTR_ VMCF5441_XBS_STRUCT_PTR;


/*
** MCF5441_STRUCT
** This structure defines the memory/registers provided by the MCF5441x
*/
typedef struct mcf5441_struct {
    uchar                       filler0[0xec010000 - 0xec000000];   
    MCF54XX_I2C_STRUCT          I2C2;       // I2C
    uchar                       filler1[0xec014000 - (0xec010000 + sizeof(MCF54XX_I2C_STRUCT))];   
    MCF54XX_I2C_STRUCT          I2C3;       // I2C
    uchar                       filler2[0xec018000 - (0xec014000 + sizeof(MCF54XX_I2C_STRUCT))];   
    MCF54XX_I2C_STRUCT          I2C4;       // I2C
    uchar                       filler3[0xec01c000 - (0xec018000 + sizeof(MCF54XX_I2C_STRUCT))];   
    MCF54XX_I2C_STRUCT          I2C5;       // I2C

    uchar                       filler4[0xec038000 - (0xec01c000 + sizeof(MCF54XX_I2C_STRUCT))];   
    MCF5XXX_DSPI_STRUCT         DSPI2;       // DSPI
    uchar                       filler5[0xec03c000 - (0xec038000 + sizeof(MCF5XXX_DSPI_STRUCT))];   
    MCF5XXX_DSPI_STRUCT         DSPI3;       // DSPI

    uchar                       filler6[0xec060000 - (0xec03c000 + sizeof(MCF5XXX_DSPI_STRUCT))];   
    MCF54XX_UART_STRUCT         UART4;
    MCF54XX_UART_STRUCT         UART5;
    MCF54XX_UART_STRUCT         UART6;
    MCF54XX_UART_STRUCT         UART7;
    MCF54XX_UART_STRUCT         UART8;
    MCF54XX_UART_STRUCT         UART9;   

    uchar                       filler7[0xec088000 - (0xec060000 + 6 * sizeof(MCF54XX_UART_STRUCT))];   
    MCF5441_PWM_STRUCT          PWM;        // Pulse Width Modulation
    
    uchar                       filler8[0xec090000 - (0xec088000 + sizeof(MCF5441_PWM_STRUCT))];   
    MCF54XX_CCM_STRUCT          CCM;        // Chip Configuration Module
    
    uchar                       filler9[0xec094000 - (0xec090000 + sizeof(MCF54XX_CCM_STRUCT))];   
    MCF5441_GPIO_STRUCT         GPIO;
    
    uchar                       filler10[0xfc004000 - (0xec094000 + sizeof(MCF5441_GPIO_STRUCT))];   
    MCF5441_XBS_STRUCT          XBS;        // Crossbar Switch

    uchar                       filler11[0xfc008000 - (0xfc004000 + sizeof(MCF5441_XBS_STRUCT))];   
    MCF5XXX_FB_STRUCT           FB[MCF5441_NUM_FB_CS];         // Mini-FlexBus

    uchar                       filler12[0xfc020000 - (0xfc008000 + MCF5441_NUM_FB_CS * sizeof(MCF5XXX_FB_STRUCT))];   
    MCF54XX_FCAN_STRUCT         FCAN0;
    uchar                       filler13[0xfc024000 - (0xfc020000 + sizeof(MCF54XX_FCAN_STRUCT))];   
    MCF54XX_FCAN_STRUCT         FCAN1;

    uchar                       filler14[0xfc038000 - (0xfc024000 + sizeof(MCF54XX_FCAN_STRUCT))];   
    MCF54XX_I2C_STRUCT          I2C1;       // I2C

    uchar                       filler15[0xfc03c000 - (0xfc038000 + sizeof(MCF54XX_I2C_STRUCT))];   
    MCF5XXX_DSPI_STRUCT         DSPI1;       // DSPI

    uchar                       filler16[0xfc040010 - (0xfc03c000 + sizeof(MCF5XXX_DSPI_STRUCT))];
    MCF5441_SCM_PMM_UNION       SCM_PMM;

    uchar                       filler17[0xfc044000 - (0xfc040010 + sizeof(MCF5441_SCM_PMM_UNION))];   
    MCF5441_EDMA_STRUCT         EDMA;       // eDMA Channels

    uchar                       filler18[0xfc048000 - (0xfc044000 + sizeof(MCF5441_EDMA_STRUCT))];
    MCF54XX_ICTRL0_STRUCT       ICTRL0;     // Interrupt Controller 0
    uchar                       filler19[0xfc04c000 - (0xfc048000 + sizeof(MCF54XX_ICTRL0_STRUCT))];   
    MCF54XX_ICTRL1_STRUCT       ICTRL1;     // Interrupt Controller 1
    uchar                       filler20[0xfc050000 - (0xfc04c000 + sizeof(MCF54XX_ICTRL1_STRUCT))];   
    MCF54XX_ICTRL1_STRUCT       ICTRL2;     // Interrupt Controller 2

    uchar                       filler21[0xfc058000 - (0xfc050000 + sizeof(MCF54XX_ICTRL1_STRUCT))];   
    MCF54XX_I2C_STRUCT          I2C0;       // I2C

    uchar                       filler22[0xfc05c000 - (0xfc058000 + sizeof(MCF54XX_I2C_STRUCT))];   
    MCF5XXX_DSPI_STRUCT         DSPI0;       // DSPI

    uchar                       filler23[0xfc060000 - (0xfc05c000 + sizeof(MCF5XXX_DSPI_STRUCT))];   
    MCF54XX_UART_STRUCT         UART0;  // UART0
    MCF54XX_UART_STRUCT         UART1;  // UART1
    MCF54XX_UART_STRUCT         UART2;  // UART2
    MCF54XX_UART_STRUCT         UART3;  // UART3            

    MCF5441_DMA_TIMER_STRUCT    DMA_TIMER[MCF5441_NUM_DMA_TIMERS];    // DMA Timers

    MCF5XXX_PIT_STRUCT          PIT[MCF5441_NUM_TIMERS];    // Programmable Interrupt Timers

    MCF5441_EPORT_STRUCT        EPORT;

    uchar                       filler24[0xFC094000 - (0xFC090000 + sizeof(MCF5441_EPORT_STRUCT))];   
    MCF544XX_ADC_STRUCT         ADC;

    uchar                       filler25[0xFC098000 - (0xFC094000 + sizeof(MCF544XX_ADC_STRUCT))];   
    MCF5441_DAC_STRUCT          DAC0;
    MCF5441_DAC_STRUCT          DAC1;

    uchar                       filler26[0xFC0A8000 - (0xFC098000 + 2 * sizeof(MCF5441_DAC_STRUCT))];   
    MCF5XXX_IRTC_STRUCT         RTC;

    uchar                       filler27[0xFC0AC000 - (0xFC0A8000 + sizeof(MCF5XXX_IRTC_STRUCT))];   
    MCF5441_SIM_STRUCT          SIM;

    uchar                       filler28[0xFC0B0000 - (0xFC0AC000 + sizeof(MCF5441_SIM_STRUCT))];   
    MCF5XXX_USBOTG_STRUCT       USBOTG;

    uchar                       filler29[0xfc0b4000 - (0xfc0b0000 + sizeof(MCF5XXX_USBOTG_STRUCT))];   
    MCF5XXX_USBOTG_STRUCT       USBHOST;
    
    uchar                       filler30[0xfc0b8000 - (0xfc0b4000 + sizeof(MCF5XXX_USBOTG_STRUCT))];   
    MCF5441_DDRMC_STRUCT        DDRMC;
    
    uchar                       filler31[0xfc0bc000 - (0xfc0b8000 + sizeof(MCF5441_DDRMC_STRUCT))];   
    MCF5441_SSI_STRUCT          SSI0;
    
    uchar                       filler32[0xfc0c0000 - (0xfc0bc000 + sizeof(MCF5441_SSI_STRUCT))];   
    MCF5441_PLL_STRUCT          PLL;

    uchar                       filler33[0xfc0c4000 - (0xfc0c0000 + sizeof(MCF5441_PLL_STRUCT))];   
    MCF5441_RNG_STRUCT          RNG;

    uchar                       filler34[0xfc0c8000 - (0xfc0c4000 + sizeof(MCF5441_RNG_STRUCT))];   
    MCF5441_SSI_STRUCT          SSI1;

    uchar                       filler35[0xfc0cc000 - (0xfc0c8000 + sizeof(MCF5441_SSI_STRUCT))];   
    SDHC_MEMMAP                 ESDHC;

    uchar                       filler36[0xfc0d4000 - (0xfc0cc000 + sizeof(SDHC_MEMMAP))];   
    ENET_MemMap                 MACNET0;       // Fast Ethernet Controller - Registers and MIB RAM
    uchar                       filler37[0xfc0d8000 - (0xfc0d4000 + sizeof(ENET_MemMap))];   
    ENET_MemMap                 MACNET1;       // Fast Ethernet Controller - Registers and MIB RAM

    uchar                       filler38[0xfc0dc000 - (0xfc0d8000 + sizeof(ENET_MemMap))];   
    MCF5XXX_ESW_STRUCT          ESW;    // Ethernet Switch

    uchar                       filler39[0xfc0fc000 - (0xfc0dc000 + sizeof(MCF5XXX_ESW_STRUCT))];   
    NFC_STRUCT                  NFC;    // NAND Flash Controller
} MCF5441_STRUCT, _PTR_ MCF5441_STRUCT_PTR;
typedef volatile struct mcf5441_struct _PTR_ VMCF5441_STRUCT_PTR;

typedef struct psp_support_struct
{
   uint_32 ACR_VALS[MCF5441_NUM_ACRS];
   uint_32 reserved;
} PSP_SUPPORT_STRUCT, _PTR_ PSP_SUPPORT_STRUCT_PTR;

typedef struct psp_mmu_init_struct
{
   uint_32 INITIAL_CACR_ENABLE_BITS;
} PSP_MMU_INIT_STRUCT, _PTR_ PSP_MMU_INIT_STRUCT_PTR;

/*
** Assign ICTRL base adresses 
*/
#define PSP_GET_ICTRL0_BASE()   (&((VMCF5441_STRUCT_PTR)_PSP_GET_IPSBAR())->ICTRL0)
#define PSP_GET_ICTRL1_BASE()   (&((VMCF5441_STRUCT_PTR)_PSP_GET_IPSBAR())->ICTRL1)
#define PSP_GET_ICTRL2_BASE()   (&((VMCF5441_STRUCT_PTR)_PSP_GET_IPSBAR())->ICTRL2)

/*------------------------------------------------------------------------*/
/*
**                      FUNCTION PROTOTYPES AND GLOBAL EXTERNS
*/

extern volatile uint_32 _psp_saved_cacr;
extern volatile uint_32 _psp_saved_acr0;
extern volatile uint_32 _psp_saved_acr1;
extern uchar __KERNEL_DATA_VERIFY_ENABLE[]; // CR1327

void    _mcf5441_initialize_support(uint_32);

void    _mcf5441_icache_enable(uint_32);
void    _mcf5441_icache_disable(void);
void    _mcf5441_icache_invalidate(void);

void    _mcf5441_dcache_enable(uint_32);
void    _mcf5441_dcache_disable(void);
void    _mcf5441_dcache_invalidate(void);

void    _icache_invalidate_mlines(pointer,uint_32,uint_32);
void    _dcache_flush_invalidate_mlines(pointer,uint_32,uint_32,uint_32,uint_32);

void    _mcf5441_mmu_init(uint_32);
uint_32 _mcf5441_mmu_enable(void);
uint_32 _mcf5441_mmu_disable(void);
uint_32 _mcf5441_mmu_add_region(pointer,uint_32,uint_32);

void    __psp_enable_acrs(uint_32_ptr);
void    __psp_clear_acrs(void);

void _psp_dcache_flush_all(uint_32, uint_32, uint_32);

void _dcache_flush(pointer, uint_32, uint_32);
void _dcache_flush_phy(pointer, uint_32, uint_32);

#endif //__ASM__

#ifdef __cplusplus
}
#endif

#endif // __mcf5441_h__

