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
* $FileName: mcf5301.h$
* $Version : 3.6.4.0$
* $Date    : Dec-3-2010$
*
* Comments:
*
*   This file contains the type definitions for the mcf5301x processors.
*
*END************************************************************************/

#ifndef __mcf5301_h__
#define __mcf5301_h__

#define __mcf5301_h__version "$Version:3.6.4.0$"
#define __mcff5301__date    "$Date:Dec-3-2010$"

#ifndef __ASM__

/* Include registers for modules common to all Coldfire processors */
#include <mcf5xxx_fec.h>        /* FEC    */
#include <mcf53xx_rtc.h>        /* RTC    */
#include <mcf53xx_ictl.h>       /* CTRL   */   
#include <mcf5xxx_pit.h>        /* PIT    */
#include <mcf53xx_sdramc.h>     /* SDRAM  */
#include <mcf53xx_uart.h>       /* UART   */
#include <mcf5xxx_fb.h>         /* FlexBus*/
#include <mcf53xx_ccm.h>        /* CCM    */
#include <mcf53xx_i2c.h>        /* I2C    */
#include <mcf53xx_sim.h>        /* SIM    */
#include <mcf53xx_dma.h>        /* DMA    */
#include <mcf5xxx_dspi.h>       /* DSPI   */
#include <mcf53xx_eport.h>      /* Eport  */
#include <mcf5xxx_usbotg.h>     /* USBOTG */
#include <mcf53xx_usbhost.h>    /* USBGOST*/
#include <mcf5xxx_esdhc.h>      /* ESDHC  */
#include <mcf53xx_ssi.h>        /* SSI    */
#include <mcf53xx_rng.h>        /* RNG    */
#include <mcf53xx_iim.h>        /* IMM    */

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
#define MCF5301_NUM_TIMERS                  (4)     /* PIT */
#define MCF5301_NUM_UARTS                   (3)
#define MCF5301_NUM_DMA_CH                  (16)    /* DMA channels */
#define MCF5301_NUM_DMA_TIMERS              (4)     /* DMA timer */
#define MCF5301_NUM_EPORT                   (2)
#define MCF5301_NUM_FB_CS                   (6)

#define MCF5301_NUM_ACRS                    (2)
#define MCF5301_NUM_DATA_ACRS               (2)
#define MCF5301_NUM_INSTR_ACRS              (2)
#define MCF5301_FIRST_DATA_ACR              (0)
#define MCF5301_FIRST_INSTR_ACR             (2)

/* Error codes from mcf5301x_mmu_add_region */
#define MCF5301_OUT_OF_ACRS                 (0x00100000)

/* Do you want to verify kernel data can be read and written correctly */
#define PSP_KERNEL_DATA_VERIFY_ENABLE       ((uint_32)__KERNEL_DATA_VERIFY_ENABLE)


#define _PSP_BYTES_TO_LINES(b)              (((b) + (PSP_CACHE_LINE_SIZE - 1)) / PSP_CACHE_LINE_SIZE)
#define _PSP_MASK_CACHE_ADDR(p)             (pointer)(((uint_32)p) & ~(PSP_CACHE_LINE_SIZE - 1))

/*
** Standard cache macros
*/
#if PSP_HAS_DATA_CACHE || PSP_HAS_CODE_CACHE
    #define _CACHE_ENABLE(n)                _mcf5301_cache_enable(n)
    #define _CACHE_DISABLE()                _mcf5301_cache_disable()
#else
    #define _CACHE_ENABLE(n)                 
    #define _CACHE_DISABLE()
#endif

#if PSP_HAS_DATA_CACHE

#define _DCACHE_ENABLE(n)                   _mcf5301_dcache_enable(n)
#define _DCACHE_DISABLE()                   _mcf5301_dcache_disable()
/*
#define _DCACHE_FLUSH()                     _psp_dcache_flush_all(PSP_CACHE_LINE_SIZE, PSP_DCACHE_NUM_WAYS, PSP_DCACHE_NUM_SETS)
#define _DCACHE_FLUSH_MBYTES(p, m)          _dcache_flush(_PSP_MASK_CACHE_ADDR(p), _PSP_BYTES_TO_LINES(m), PSP_CACHE_LINE_SIZE)
#define _DCACHE_FLUSH_LINE(p)               _DCACHE_FLUSH_MBYTES(p, 1)
*/
#define _DCACHE_FLUSH()                     /* data cache is writethrough */
#define _DCACHE_FLUSH_MBYTES(p, m)          /* data cache is writethrough */
#define _DCACHE_FLUSH_LINE(p)               /* data cache is writethrough */

#define _DCACHE_INVALIDATE()                _mcf5301_dcache_invalidate()
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

#define _ICACHE_ENABLE(n)                   _mcf5301_icache_enable(n)
#define _ICACHE_DISABLE()                   _mcf5301_icache_disable()
#define _ICACHE_INVALIDATE()                _mcf5301_icache_invalidate()
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
#define MCF5301_CACR_CLEAR_BITS                 (0x63025F)

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
** General Purpose I/O (GPIO) Module
*/

/* general bit definition */
#define MCF5301_GPIO_PIN_0                            0x01
#define MCF5301_GPIO_PIN_1                            0x02
#define MCF5301_GPIO_PIN_2                            0x04
#define MCF5301_GPIO_PIN_3                            0x08
#define MCF5301_GPIO_PIN_4                            0x10
#define MCF5301_GPIO_PIN_5                            0x20
#define MCF5301_GPIO_PIN_6                            0x40
#define MCF5301_GPIO_PIN_7                            0x80

/* Bit definitions for PODR_x registers */
#define MCF5301_GPIO_PODR_x0                          0x01
#define MCF5301_GPIO_PODR_x1                          0x02
#define MCF5301_GPIO_PODR_x2                          0x04
#define MCF5301_GPIO_PODR_x3                          0x08
#define MCF5301_GPIO_PODR_x4                          0x10
#define MCF5301_GPIO_PODR_x5                          0x20
#define MCF5301_GPIO_PODR_x6                          0x40
#define MCF5301_GPIO_PODR_x7                          0x80
#define MCF5301_GPIO_PODR_x(x)	                      (0x01<<x)

/* Bit definitions for PDDR_x registers */
#define MCF5301_GPIO_PDDR_x0                          0x01
#define MCF5301_GPIO_PDDR_x1                          0x02
#define MCF5301_GPIO_PDDR_x2                          0x04
#define MCF5301_GPIO_PDDR_x3                          0x08
#define MCF5301_GPIO_PDDR_x4                          0x10
#define MCF5301_GPIO_PDDR_x5                          0x20
#define MCF5301_GPIO_PDDR_x6                          0x40
#define MCF5301_GPIO_PDDR_x7                          0x80
#define MCF5301_GPIO_PDDR_x(x)                       (0x01<<x)

/* Bit definitions for PPDSDR_x registers */
#define MCF5301_GPIO_PPDSDR_x0                        0x01
#define MCF5301_GPIO_PPDSDR_x1                        0x02
#define MCF5301_GPIO_PPDSDR_x2                        0x04
#define MCF5301_GPIO_PPDSDR_x3                        0x08
#define MCF5301_GPIO_PPDSDR_x4                        0x10
#define MCF5301_GPIO_PPDSDR_x5                        0x20
#define MCF5301_GPIO_PPDSDR_x6                        0x40
#define MCF5301_GPIO_PPDSDR_x7                        0x80
#define MCF5301_GPIO_PPDSDR_x(x)                      (0x01<<x)

/* Bit definitions for PCLRR_x registers */
#define MCF5301_GPIO_PCLRR_x0                         (0x01)
#define MCF5301_GPIO_PCLRR_x1                         (0x02)
#define MCF5301_GPIO_PCLRR_x2                         (0x04)
#define MCF5301_GPIO_PCLRR_x3                         (0x08)
#define MCF5301_GPIO_PCLRR_x4                         (0x10)
#define MCF5301_GPIO_PCLRR_x5                         (0x20)
#define MCF5301_GPIO_PCLRR_x6                         (0x40)
#define MCF5301_GPIO_PCLRR_x7                         (0x80)
#define MCF5301_GPIO_PCLRR_x(x)                       (0x01<<x)
                                                       
/* Bit definitions and macros for PAR_FEC */
#define MCF5301_GPIO_PAR_FEC_7WIRE1                   (0x40)
#define MCF5301_GPIO_PAR_FEC_RMII1                    (0x10)
#define MCF5301_GPIO_PAR_FEC_7WIRE0                   (0x04)
#define MCF5301_GPIO_PAR_FEC_RMII0                    (0x01)

/* Bit definitions and macros for PAR_UART */
#define MCF5301_GPIO_PAR_UART_U0CTS(x)                ((x) & 3)
#define MCF5301_GPIO_PAR_UART_U0CTS_GPIO              (0)
#define MCF5301_GPIO_PAR_UART_U0CTS_USB_PULLUP        (1)
#define MCF5301_GPIO_PAR_UART_U0CTS_USBO_VBUS_EN      (2)
#define MCF5301_GPIO_PAR_UART_U0CTS_U0CTS             (3)
#define MCF5301_GPIO_PAR_UART_U0RTS(x)                (((x)& 3) << 2)
#define MCF5301_GPIO_PAR_UART_U0RTS_GPIO              (0)
#define MCF5301_GPIO_PAR_UART_U0RTS_USBO_VBUSOC       (8)
#define MCF5301_GPIO_PAR_UART_U0RTS_U0RTS             (0x0c)
#define MCF5301_GPIO_PAR_UART_U0RXD                   (0x10)
#define MCF5301_GPIO_PAR_UART_U0RXD_GPIO              (0)
#define MCF5301_GPIO_PAR_UART_U0RXD_U0RXD             (0x10)
#define MCF5301_GPIO_PAR_UART_U0TXD                   (0x20)
#define MCF5301_GPIO_PAR_UART_U0TXD_GPIO              (0)
#define MCF5301_GPIO_PAR_UART_U0TXD_U0TXD             (0x20)
#define MCF5301_GPIO_PAR_UART_U2RXD                   (0x40)
#define MCF5301_GPIO_PAR_UART_U2RXD_GPIO              (0)
#define MCF5301_GPIO_PAR_UART_U2RXD_U2RXD             (0x40)
#define MCF5301_GPIO_PAR_UART_U2TXD                   (0x80)
#define MCF5301_GPIO_PAR_UART_U2TXD_GPIO              (0)
#define MCF5301_GPIO_PAR_UART_U2TXD_U2TXD             (0x80)
#define MCF5301_GPIO_PAR_SIM_DATA1_U1TXD              (0x40)
#define MCF5301_GPIO_PAR_SIM_DATA1_U1RXD              (0x10)
#define MCF5301_GPIO_PAR_SIM_DATA1_U1RTS              (0x04)
#define MCF5301_GPIO_PAR_SIM_DATA1_U1CTS              (0x01)
#define MCF5301_GPIO_PAR_SSIH_U1RXD                   (0x40)
#define MCF5301_GPIO_PAR_SSIH_U1TXD                   (0x10)
#define MCF5301_GPIO_PAR_SSIH_U1RTS                   (0x04)
#define MCF5301_GPIO_PAR_SSIL_U1CTS                   (0x40)

/* Bit definitions and macros for PAR_FBCTL */
#define MCF5301_GPIO_PAR_FBCTL_PAR_TS_GPIO            (0x00)
#define MCF5301_GPIO_PAR_FBCTL_PAR_TS_FB_START        (0x18)
#define MCF5301_GPIO_PAR_FBCTL_RWB                    (0x20)
#define MCF5301_GPIO_PAR_FBCTL_TA                     (0x40)
#define MCF5301_GPIO_PAR_FBCTL_OE                     (0x80)
#define MCF5301_GPIO_PAR_FBCTL_TS_MASK                (0x18)
#define MCF5301_GPIO_PAR_FBCTL_RWB_MASK               (0x20)
#define MCF5301_GPIO_PAR_FBCTL_TA_MASK                (0x40)
#define MCF5301_GPIO_PAR_FBCTL_OE_MASK                (0x80)

/* Bit definitions and macros for PAR_BE */
#define MCF5301_GPIO_PAR_BE0                          (0x01)
#define MCF5301_GPIO_PAR_BE1                          (0x04)
#define MCF5301_GPIO_PAR_BE2                          (0x10)
#define MCF5301_GPIO_PAR_BE3                          (0x40)

/* Bit definitions and macros for PAR_CS */      
#define MCF5301_GPIO_PAR_CS0_GPIO                     (0x01)
#define MCF5301_GPIO_PAR_CS0_FLEXBUS                  (0x03)
#define MCF5301_GPIO_PAR_CS1_GPIO                     (0x00)
#define MCF5301_GPIO_PAR_CS1_SD_CS1                   (0x08)
#define MCF5301_GPIO_PAR_CS1_FLEXBUS                  (0x0C)
#define MCF5301_GPIO_PAR_CS4_GPIO                     (0x00)
#define MCF5301_GPIO_PAR_CS4_FLEXBUS                  (0x10)
#define MCF5301_GPIO_PAR_CS5_GPIO                     (0x00) 
#define MCF5301_GPIO_PAR_CS5_FLEXBUS                  (0x40)
#define MCF5301_GPIO_PAR_CS0_MASK                     (0x03)
#define MCF5301_GPIO_PAR_CS1_MASK                     (0x0C)
#define MCF5301_GPIO_PAR_CS4_MASK                     (0x10)
#define MCF5301_GPIO_PAR_CS5_MASK                     (0x40)
                                                           
/* Bit definitions and macros for PAR_DSPI */              
#define MCF5301_GPIO_PAR_DSPI_SCK_DSPISCK             (0x0C)
#define MCF5301_GPIO_PAR_DSPI_SCK_U2CTS               (0x08)
#define MCF5301_GPIO_PAR_DSPI_SCK_GPIO                (0x00)
#define MCF5301_GPIO_PAR_DSPI_SOUT_DSPISOUT           (0x30)
#define MCF5301_GPIO_PAR_DSPI_SOUT_U2TXD              (0x20)
#define MCF5301_GPIO_PAR_DSPI_SOUT_GPIO               (0x00)
#define MCF5301_GPIO_PAR_DSPI_SIN_DSPISIN             (0xC0)
#define MCF5301_GPIO_PAR_DSPI_SIN_U2RXD               (0x80)
#define MCF5301_GPIO_PAR_DSPI_SIN_GPIO                (0x00)
#define MCF5301_GPIO_PAR_DSPI_PCS0_DSPIPCS0           (0x03)
#define MCF5301_GPIO_PAR_DSPI_PCS0_U2RTS              (0x02)
#define MCF5301_GPIO_PAR_DSPI_PCS0_GPIO               (0x00)
#define MCF5301_GPIO_PAR_DSPI_SCK_MASK                (0x0C)
#define MCF5301_GPIO_PAR_DSPI_SOUT_MASK               (0x30)
#define MCF5301_GPIO_PAR_DSPI_SIN_MASK                (0xC0)
#define MCF5301_GPIO_PAR_DSPI_PCS0_MASK               (0x03) 
/* Bit definitions and macros for PAR_DSPIL */   
#define MCF5301_GPIO_PAR_DSPIL_PCS3                   (0x08)

/* Bit definitions and macros for PAR_FECI2C */
#define MCF5301_GPIO_PAR_FECI2C_SCL(x)                ((x) & 3)
#define MCF5301_GPIO_PAR_FECI2C_SCL_GPIO              (0)
#define MCF5301_GPIO_PAR_FECI2C_SCL_RMII1_MDC         (1) 
#define MCF5301_GPIO_PAR_FECI2C_SCL_U2RXD             (2)
#define MCF5301_GPIO_PAR_FECI2C_SCL_SCL               (3)
#define MCF5301_GPIO_PAR_FECI2C_SDA(x)                (((x) & 3)<< 2)
#define MCF5301_GPIO_PAR_FECI2C_SDA_GPIO              (0)
#define MCF5301_GPIO_PAR_FECI2C_SDA_RMII1_MDIO        (4)
#define MCF5301_GPIO_PAR_FECI2C_SDA_U2TXD             (8)
#define MCF5301_GPIO_PAR_FECI2C_SDA_SDA               (0x0C)
#define MCF5301_GPIO_PAR_FECI2C_RMII1_MDC             (0x20)
#define MCF5301_GPIO_PAR_FECI2C_RMII1_MDIO            (0x10)
#define MCF5301_GPIO_PAR_FECI2C_RMII0_MDIO            (0x40)
#define MCF5301_GPIO_PAR_FECI2C_RMII0_MDC             (0x80)


/* Bit definitions and macros for PAR_IRQ0H Port*/
#define MCF5301_GPIO_PAR_EPORT_IRQ04(x)               ((x) & 3)
#define MCF5301_GPIO_PAR_EPORT_IRQ04_GPIO             (0)
#define MCF5301_GPIO_PAR_EPORT_IRQ04_DREQ0            (2)
#define MCF5301_GPIO_PAR_EPORT_IRQ06_GPIO             (0)
#define MCF5301_GPIO_PAR_EPORT_IRQ06_USB_CLKIN        (0x10)
#define MCF5301_GPIO_PAR_EPORT_IRQ07_GPIO             (0)

/* Bit definitions and macros for PAR_IRQ0L Port*/
#define MCF5301_GPIO_PAR_EPORT_IRQ01(x)               (((x) & 3)<<2)
#define MCF5301_GPIO_PAR_EPORT_DREQ1                  (2)
	
/* Bit definitions and macros for PAR_TIMER Port*/
#define MCF5301_GPIO_PAR_TIMER_T0IN(x)                ((x) & 3)
#define MCF5301_GPIO_PAR_TIMER_T0IN_GPIO              (0)
#define MCF5301_GPIO_PAR_TIMER_T0IN_CODEC_ALTCLK      (1)
#define MCF5301_GPIO_PAR_TIMER_T0IN_T0OUT             (2)
#define MCF5301_GPIO_PAR_TIMER_T0IN_T0IN              (3)
#define MCF5301_GPIO_PAR_TIMER_T1IN(x)                (((x) & 3)<<2)
#define MCF5301_GPIO_PAR_TIMER_T1IN_GPIO              (0)
#define MCF5301_GPIO_PAR_TIMER_T1IN_DACK1             (0x04)
#define MCF5301_GPIO_PAR_TIMER_T1IN_T1OUT             (0x08)
#define MCF5301_GPIO_PAR_TIMER_T1IN_T1IN              (0x0C)
#define MCF5301_GPIO_PAR_TIMER_T2IN(x)                (((x) & 3)<<4)
#define MCF5301_GPIO_PAR_TIMER_T2IN_GPIO              (0)
#define MCF5301_GPIO_PAR_TIMER_T2IN_IRQ2              (0x10)
#define MCF5301_GPIO_PAR_TIMER_T2IN_T2OUT             (0x20)
#define MCF5301_GPIO_PAR_TIMER_T2IN_T2IN              (0x30)
#define MCF5301_GPIO_PAR_TIMER_T3IN(x)                (((x) & 3)<<6)
#define MCF5301_GPIO_PAR_TIMER_T3IN_GPIO              (0)
#define MCF5301_GPIO_PAR_TIMER_T3IN_IRQ3              (0x40)
#define MCF5301_GPIO_PAR_TIMER_T3IN_T3OUT             (0x80)
#define MCF5301_GPIO_PAR_TIMER_T3IN_T3IN              (0xC0)

/* Bit definitions and macros for Mode Select Control Registers*/
#define MCF5301_GPIO_MSCR1(x)                         ((x) & 0xe0)
#define MCF5301_GPIO_MSCR2(x)                         ((x) & 0xe0)
#define MCF5301_GPIO_MSCR3(x)                         ((x) & 0xe0)
#define MCF5301_GPIO_MSCR4(x)                         ((x) & 0xe0)
#define MCF5301_GPIO_MSCR5(x)                         ((x) & 0x1c)

/* Bit definitions and macros for PAR_TIMER Port*/
#define MCF5301_GPIO_PAR_SDHC_CLK                     (0x00)
#define MCF5301_GPIO_PAR_SDHC_CMD                     (0x01)
#define MCF5301_GPIO_PAR_SDHC_DATA0                   (0x02)
#define MCF5301_GPIO_PAR_SDHC_DATA1                   (0x04)
#define MCF5301_GPIO_PAR_SDHC_DATA2                   (0x10)
#define MCF5301_GPIO_PAR_SDHC_DATA3                   (0x20)

#define MCF5301_GPIO_MSCR_SDRAM_SDXXX_HS_LPDDR        (0)
#define MCF5301_GPIO_MSCR_SDRAM_SDXXX_FS_LPDDR        (1)
#define MCF5301_GPIO_MSCR_SDRAM_SDXXX_DDR2            (2)
#define MCF5301_GPIO_MSCR_SDRAM_SDXXX_DDR1            (3)

/* Bit definitions and macros for MCF_CLOCK_PCR */
#define MCF5301_PLL_DR_OUTDIV1(x)                     ((x) & 0x0f)
#define MCF5301_PLL_DR_OUTDIV2(x)                     (((x) & 0x0f) << 4)
#define MCF5301_PLL_DR_OUTDIV3(x)                     (((x) & 0x0f) << 8)
#define MCF5301_PLL_DR_OUTDIV4(x)                     (((x) & 0x0f) << 12)



/* Bit definitions and macros for PLL_CR */
#define MCF5301_PLL_CR_FBKDIV(x)                      ((x) & 0x3f)
#define MCF5301_PLL_CR_REFDIV(x)                      (((x) & 0x07) << 0x08)
#define MCF5301_PLL_CR_LOLEN                          (0x00001000)
#define MCF5301_PLL_CR_LOLEN_DISABLE                  (0)           /* Loss of lock disabled */
#define MCF5301_PLL_CR_LOLEN_ENABLE                   (0x00001000)  /* Loss of lock disabled */
#define MCF5301_PLL_CR_LORE                           (0x00002000)
#define MCF5301_PLL_CR_LORE_IGNORE                    (0)           /* Ignore loss of lock, reset not requested */
#define MCF5301_PLL_CR_LORE_REQUEST                   (0x00002000)  /* Request reset on loss of lock */
#define MCF5301_PLL_CR_LOLIRQ                         (0x00004000)
#define MCF5301_PLL_CR_LOLIRQ_NOT_INTERRUPT           (0)           /* Interrupt not requested */
#define MCF5301_PLL_CR_LOLIRQ_INTERRUPT               (0x00004000)  /* Request interrupt on loss of lock */

/* Bit definitions and macros for PLL_SR */
#define MCF5301_PLL_SR_MODE(x)                        ((x) & 0x7)                  
#define MCF5301_PLL_SR_LOCK                           (0x00000010)
#define MCF5301_PLL_SR_UNLOCK                         (0)
#define MCF5301_PLL_SR_LOLF_IRQ                       (0x00000020)   /* Interrupt service  requested */
#define MCF5301_PLL_SR_LOLF_NOT_IRQ                   (0)            /* Interrupt service not requested */
#define MCF5301_PLL_SR_LOC_NORMAL                     (0x00000100)
#define MCF5301_PLL_SR_LOC_FAIL                       (0)
#define MCF5301_PLL_SR_LOCF_IRQ                       (0x00000200)   /*Interrupt Request*/
#define MCF5301_PLL_SR_LOCF_NOT_IRQ                   (0)            /*Interrupt not Request*/


/*
** Interrupt definitions
*/
#define MCF5301_ICTRL_MASKALL                         1
#define MCF5301_ICTRL0_BASEx                          64
#define MCF5301_ICTRL1_BASEx                          128

/*
** Interrupt vector table
*/
typedef enum mcf5301_interrupt_table_index {
    MCF5301_boot_stack_pointer,
    MCF5301_boot_program_counter,
    MCF5301_EXC_ACCESS_ERROR,
    MCF5301_EXC_ADDRESS_ERROR,
    MCF5301_EXC_ILLEGAL_INSTRUCTION,
    MCF5301_EXC_DIVIDE_BY_ZERO,
    MCF5301_EXC_rsvd6,
    MCF5301_EXC_rsvd7,
    MCF5301_EXC_PRIVILEGE_VIOLATION,
    MCF5301_EXC_NEXT_TRACE,
    MCF5301_EXC_UNIMPLEMENTED_LINE_A_OPCODE,
    MCF5301_EXC_UNIMPLEMENTED_LINE_F_OPCODE,
    MCF5301_EXC_DEBUG,
    MCF5301_EXC_rsvd13,
    MCF5301_EXC_FORMAT_ERROR,
    MCF5301_EXC_rsvd15,
    MCF5301_EXC_rsvd16,
    MCF5301_EXC_rsvd17,
    MCF5301_EXC_rsvd18,
    MCF5301_EXC_rsvd19,
    MCF5301_EXC_rsvd20,
    MCF5301_EXC_rsvd21,
    MCF5301_EXC_rsvd22,
    MCF5301_EXC_rsvd23,
    MCF5301_EXC_SPURIOUS,
    MCF5301_EXC_rsvd25,
    MCF5301_EXC_rsvd26,
    MCF5301_EXC_rsvd27,
    MCF5301_EXC_rsvd28,
    MCF5301_EXC_rsvd29,
    MCF5301_EXC_rsvd30,
    MCF5301_EXC_rsvd31,
    MCF5301_EXC_TRAP0,
    MCF5301_EXC_TRAP1,
    MCF5301_EXC_TRAP2,
    MCF5301_EXC_TRAP3,
    MCF5301_EXC_TRAP4,
    MCF5301_EXC_TRAP5,
    MCF5301_EXC_TRAP6,
    MCF5301_EXC_TRAP7,
    MCF5301_EXC_TRAP8,
    MCF5301_EXC_TRAP9,
    MCF5301_EXC_TRAP10,
    MCF5301_EXC_TRAP11,
    MCF5301_EXC_TRAP12,
    MCF5301_EXC_TRAP13,
    MCF5301_EXC_TRAP14,
    MCF5301_EXC_TRAP15,
    MCF5301_EXC_rsvd48,
    MCF5301_EXC_rsvd49,
    MCF5301_EXC_rsvd50,
    MCF5301_EXC_rsvd51,
    MCF5301_EXC_rsvd52,
    MCF5301_EXC_rsvd53,
    MCF5301_EXC_rsvd54,
    MCF5301_EXC_rsvd55,
    MCF5301_EXC_rsvd56,
    MCF5301_EXC_rsvd57,
    MCF5301_EXC_rsvd58,
    MCF5301_EXC_rsvd59,
    MCF5301_EXC_rsvd60,
    MCF5301_EXC_rsvd61,
    MCF5301_EXC_rsvd62,
    MCF5301_EXC_rsvd63,
    
    MCF5301_INT_FIRST_EXTERNAL,
    /* Interrupt Controller 0 */
    MCF5301_INT_EPORT0_EPF1,    /* 1 Edge port flag 1 */  
    MCF5301_INT_EPORT0_EPF2,    /* 2 Edge port flag 2 */  
    MCF5301_INT_EPORT0_EPF3,    /* 3 Edge port flag 3 */   
    MCF5301_INT_EPORT0_EPF4,    /* 4 Edge port flag 4 */  
    MCF5301_INT_EPORT0_EPF5,    /* 5 Edge port flag 5 */
    MCF5301_INT_EPORT0_EPF6,    /* 6 Edge port flag 6 */
    MCF5301_INT_EPORT0_EPF7,    /* 7 Edge port flag 7 */
    
    MCF5301_INT_EDMA_INTR0,     /* 8  DMA Channel 0  transfer complete  */ 
    MCF5301_INT_EDMA_INTR1,     /* 9  DMA Channel 1  transfer complete  */ 
    MCF5301_INT_EDMA_INTR2,     /* 10 DMA Channel 2  transfer complete  */ 
    MCF5301_INT_EDMA_INTR3,     /* 11 DMA Channel 3  transfer complete  */ 
    MCF5301_INT_EDMA_INTR4,     /* 12 DMA Channel 4  transfer complete  */ 
    MCF5301_INT_EDMA_INTR5,     /* 13 DMA Channel 5  transfer complete  */ 
    MCF5301_INT_EDMA_INTR6,     /* 14 DMA Channel 6  transfer complete  */ 
    MCF5301_INT_EDMA_INTR7,     /* 15 DMA Channel 7  transfer complete  */ 
    MCF5301_INT_EDMA_INTR8,     /* 16 DMA Channel 8  transfer complete  */ 
    MCF5301_INT_EDMA_INTR9,     /* 17 DMA Channel 9  transfer complete  */ 
    MCF5301_INT_EDMA_INTR10,    /* 18 DMA Channel 10 transfer complete  */ 
    MCF5301_INT_EDMA_INTR11,    /* 19 DMA Channel 11 transfer complete  */ 
    MCF5301_INT_EDMA_INTR12,    /* 20 DMA Channel 12 transfer complete  */ 
    MCF5301_INT_EDMA_INTR13,    /* 21 DMA Channel 13 transfer complete  */ 
    MCF5301_INT_EDMA_INTR14,    /* 22 DMA Channel 14 transfer complete  */ 
    MCF5301_INT_EDMA_INTR15,    /* 23 DMA Channel 15 transfer complete  */ 
    
    MCF5301_INT_EDMA_ERR,       /* 24 DMA Error Interrupt   */ 
    MCF5301_INT_SCM_CWIC,       /* 25 Core Watchdog Timeout */ 
    MCF5301_INT_UART0,          /* 26 UART0 interrupt       */ 
    MCF5301_INT_UART1,          /* 27 UART1 interrupt       */ 
    MCF5301_INT_UART2,          /* 28 UART2 interrupt       */ 
    MCF5301_INT_rsvd29,         /* 29 not used              */ 
    MCF5301_INT_I2C,            /* 30 I2C interrupt         */ 
    MCF5301_INT_DSPI,           /* 31 DSPI interrupt (Logical OR of INTC1’s source #33–39) */ 
    MCF5301_INT_DTIM0,          /* 32 TMR0 interrupt         */ 
    MCF5301_INT_DTIM1,          /* 33 TMR1 interrupt         */ 
    MCF5301_INT_DTIM2,          /* 34 TMR2 interrupt         */ 
    MCF5301_INT_DTIM3,          /* 35 TMR3 interrupt         */ 

    MCF5301_INT_FEC0_X_INTF,    /* 36 Transmit frame interrupt   */ 
    MCF5301_INT_FEC0_X_INTB,    /* 37 Transmit buffer interrupt  */ 
    MCF5301_INT_FEC0_X_UN,      /* 38 Transmit FIFO underrun     */ 
    MCF5301_INT_FEC0_RL,        /* 39 Collision retry limit      */ 
    MCF5301_INT_FEC0_R_INTF,    /* 40 Receive frame interrupt    */ 
    MCF5301_INT_FEC0_R_INTB,    /* 41 Receive buffer interrupt   */ 
    MCF5301_INT_FEC0_MII,       /* 42 MII interrupt              */ 
    MCF5301_INT_FEC0_LC,        /* 43 Late collision             */ 
    MCF5301_INT_FEC0_HBERR,     /* 44 Heartbeat error            */ 
    MCF5301_INT_FEC0_GRA,       /* 45 Graceful stop complete     */ 
    MCF5301_INT_FEC0_EBERR,     /* 46 Ethernet bus error         */ 
    MCF5301_INT_FEC0_BABT,      /* 47 Babbling transmit error    */ 
    MCF5301_INT_FEC0_BABR,      /* 48 Babbling receive error     */
    
    MCF5301_INT_FEC1_X_INTF,    /* 49 Transmit frame interrupt   */ 
    MCF5301_INT_FEC1_X_INTB,    /* 50 Transmit buffer interrupt  */ 
    MCF5301_INT_FEC1_X_UN,      /* 51 Transmit FIFO underrun     */ 
    MCF5301_INT_FEC1_RL,        /* 52 Collision retry limit      */ 
    MCF5301_INT_FEC1_R_INTF,    /* 53 Receive frame interrupt    */ 
    MCF5301_INT_FEC1_R_INTB,    /* 54 Receive buffer interrupt   */ 
    MCF5301_INT_FEC1_MII,       /* 55 MII interrupt              */ 
    MCF5301_INT_FEC1_LC,        /* 56 Late collision             */ 
    MCF5301_INT_FEC1_HBERR,     /* 57 Heartbeat error            */ 
    MCF5301_INT_FEC1_GRA,       /* 58 Graceful stop complete     */ 
    MCF5301_INT_FEC1_EBERR,     /* 59 Ethernet bus error         */ 
    MCF5301_INT_FEC1_BABT,      /* 60 Babbling transmit error    */ 
    MCF5301_INT_FEC1_BABR,      /* 61 Babbling receive error     */ 
    MCF5301_INT_SCM_CFEI,       /* 62 Core bus error interrupt   */
    MCF5301_INT_rsvd63,         /* 63 Not use Interrupt          */

    /* Interrupt Controller 1 */
    MCF5301_INT1_rsvd0,         /* 0 not used  */  
    MCF5301_INT1_rsvd1,         /* 1 not used  */  
    MCF5301_INT1_rsvd2,         /* 2 not used  */  
    MCF5301_INT1_rsvd3,         /* 3 not used  */  
    MCF5301_INT1_rsvd4,         /* 4 not used  */  
    MCF5301_INT1_rsvd5,         /* 5 not used  */  
    MCF5301_INT1_rsvd6,         /* 6 not used  */  
    MCF5301_INT1_rsvd7,         /* 7 not used  */  
    MCF5301_INT1_rsvd8,         /* 8 not used  */  
    MCF5301_INT1_rsvd9,         /* 9 not used  */  
    MCF5301_INT1_rsvd10,        /* 10 not used */ 
    MCF5301_INT1_rsvd11,        /* 11 not used */ 
    MCF5301_INT1_rsvd12,        /* 12 not used */ 
    MCF5301_INT1_rsvd13,        /* 13 not used */ 
    MCF5301_INT1_rsvd14,        /* 14 not used */ 
    MCF5301_INT1_rsvd15,        /* 15 not used */
    MCF5301_INT1_rsvd16,        /* 16 not used */
    MCF5301_INT1_rsvd17,        /* 17 not used */
    MCF5301_INT1_rsvd18,        /* 18 not used */
    MCF5301_INT1_rsvd19,        /* 19 not used */
    MCF5301_INT1_rsvd20,        /* 20 not used */
    MCF5301_INT1_rsvd21,        /* 21 not used */
    MCF5301_INT1_rsvd22,        /* 22 not used */
    MCF5301_INT1_rsvd23,        /* 23 not used */
    MCF5301_INT1_rsvd24,        /* 24 not used */
    MCF5301_INT1_EPORT0_EPF0,   /* 25 Edge port flag 0 */
    MCF5301_INT1_EPORT0_EPF1,   /* 26 Edge port flag 1 */
    MCF5301_INT1_EPORT0_EPF2,   /* 27 Edge port flag 2 */
    MCF5301_INT1_EPORT0_EPF3,   /* 28 Edge port flag 3 */
    MCF5301_INT1_EPORT0_EPF4,   /* 29 Edge port flag 4 */
    MCF5301_INT1_EPORT0_EPF5,   /* 30 Edge port flag 5 */
    MCF5301_INT1_EPORT0_EPF6,   /* 31 Edge port flag 6 */
    MCF5301_INT1_EPORT0_EPF7,   /* 32 Edge port flag 7 */
    
    MCF5301_INT1_DSPI_EOQF,     /* 33 DSPI End of queue interrupt            */
    MCF5301_INT1_DSPI_TFFF,     /* 34 DSPI Transmit FIFO fill interrupt      */
    MCF5301_INT1_DSPI_TCF,      /* 35 DSPI Transfer complete interrupt       */
    MCF5301_INT1_DSPI_TFUF,     /* 36 DSPI Transmit FIFO underflow interrupt */
    MCF5301_INT1_DSPI_RFDF,     /* 37 DSPI Receive FIFO not empty interrupt  */
    MCF5301_INT1_DSPI_RFOF,     /* 38 DSPI Receive FIFO overflow interrupt   */
    MCF5301_INT1_DSPI_RFOF_TFUF,/* 39 DSPI Receive FIFO overflow or transmit FIFO underflow interrupt */
    MCF5301_INT1_RNG,           /* 40 RNG interrupt flag  			          */
    MCF5301_INT1_PLL_LOCF,      /* 41 Loss of clock interrupt                 */
    MCF5301_INT1_PLL_LOLF,		  /* 42 Loss of clock interrupt                 */
    MCF5301_INT1_PIT0,          /* 43 PIT0 PIF PIT interrupt flag             */
    MCF5301_INT1_PIT1,          /* 44 PIT1 PIF PIT interrupt flag             */
    MCF5301_INT1_PIT2,          /* 45 PIT0 PIF PIT interrupt flag             */
    MCF5301_INT1_PIT3,          /* 46 PIT1 PIF PIT interrupt flag             */

    MCF5301_INT1_USB,       	  /* 47 USB OTG interrupt                       */
    MCF5301_INT1_USBHOST,       /* 48 USB HOST interrupt                      */
    MCF5301_INT_SSI,            /* 49 SSI interrupt                           */
    MCF5301_INT1_IIM,           /* 50 IIM interrupt                           */
    MCF5301_INT1_rsvd51,        /* 51 not used                                */
    MCF5301_INT1_RTC,           /* 52 RTC interrupt                           */
    MCF5301_INT1_CCM,           /* 53 USB status Interrupt                    */
    MCF5301_INT1_CODEC,         /* 54 Voice codec OR’d interrupt              */
    MCF5301_INT1_CODEC_VCRF,	  /* 55 Voice codec  interrupt                  */
    MCF5301_INT1_CODEC_VROE,    /* 56 Voice codec transmit underrun error interrup  */
    MCF5301_INT1_CODEC_VTOE,	  /* 57 Voice codec transmit underrun error interrup  */
    MCF5301_INT1_rsvd58,        /* 58 not used                                */
    MCF5301_INT1_SIM1_RSR,		  /* 59 SIM data interrupt                      */
    MCF5301_INT1_SIM1_TSR,		  /* 60 SIM general interrupt                   */
    MCF5301_INT1_rsvd61,		  /* 61Not use                                  */
    MCF5301_INT1_rsvd62,		  /* 62Not use                                  */
    MCF5301_INT1_SDHC		     /* 63SDHC OR’d interrupt                      */
}   MCF5301_INTERRUPT_TABLE_INDEX; /* PSP_INTERRUPT_TABLE_INDEX               */

/*
** MCF53015_PLL_STRUCT
** ColdFire PLL
*/
typedef struct mcf5301_pll_struct {
    uint_32 PCR;            /* PLL Control Register                           */
    uint_32 PDR;            /* PLL Divider Register                           */
    uint_32 PSR;            /* PLL Status Register                            */
} MCF5301_PLL_STRUCT, _PTR_ MCF5301_PLL_STRUCT_PTR;
typedef volatile struct mcf5301_pll_struct _PTR_ VMCF5301_PLL_STRUCT_PTR;

/*
** MCF5301_PMM_STRUCT
** Power Management (PMM)
** NOTE!!! in register address space, this is shared with SCM, use SCM_PMM union defined below
*/
typedef struct mcf5301_pmm_struct {
    uint_8  filler0[3];
    uint_8  WCR;
    uint_8  filler1[0x18];
    uint_8  PPMSR0;
    uint_8  PPMCR0;
    uint_8  PPMSR1;
    uint_8  PPMCR1;
    uint_32 PPMHR0;
    uint_32 PPMLR0;
    uint_32 PPMHR1;
    uint_32 PPMLR1;
} MCF5301_PMM_STRUCT, _PTR_ MCF5301_PMM_STRUCT_PTR;
typedef volatile struct mcf5301_pmm_struct _PTR_ VMCF5301_PMM_STRUCT_PTR;

/*
** SCM Registers
*/
typedef struct mcf5301_scm_a_struct {
    uint_32 MPR  ;
    uint_32 PACRA;
    uint_32 PACRB;
    uint_32 PACRC;
    uint_32 PACRD;
    uint_32 PACRE;
    uint_32 PACRF;
    uint_32 PACRG;
} MCF5301_SCM_A_STRUCT, _PTR_ MCF5301_SCM_A_STRUCT_PTR;
typedef volatile struct mcf5301_scm_a_struct _PTR_ VMCF5301_SCM_A_STRUCT_PTR;



typedef struct mcf5301_scm_b_struct {
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
    uint_8 filler5[0x04];
    uint_8 PPMSR0;
    uint_8 PPMCR0;
    uint_8 filler6[0x02];
    uint_32 PPMHR0;
    uint_32 PPMLR0;
    uint_8 filler7[0x38];
    uint_32 CFADR;
    uint_8 filler8[0x01];
    uint_8 CFIER;
    uint_8 CFLOC;  
    uint_8 CFATR; 
    uint_8 filler9[0x04];
    uint_32 CFDTR;
} MCF5301_SCM_B_STRUCT, _PTR_ MCF5301_SCM_B_STRUCT_PTR;
typedef volatile struct mcf5301_scm_b_struct _PTR_ VMCF5301_SCM_B_STRUCT_PTR;

/*
** MCF5301_GPIO_STRUCT
** GPIO Registers
*/
typedef struct mcf5301_gpio_struct {

    /*Port Output Data Registers*/
    uint_8 PODR_FBCTL, PODR_BE,PODR_CS,PODR_DSPI;
    uint_8  filler0;
    uint_8 PODR_FEC0,PODR_FECI2C;
    uint_8 filler1,filler2;
    uint_8 PODR_SIMP1,PODR_SIMP0,PODR_TIMER,PODR_UART,PODR_DEBUG;
    uint_8  filler3;
    uint_8  PODR_SDHC,PODR_SSI;
    uint_8 filler4,filler5,filler6;
    /*Port Data Direction Registers*/
    uint_8 PDDR_FBCTL, PDDR_BE,PDDR_CS,PDDR_DSPI;
    uint_8  filler7;
    uint_8 PDDR_FEC0,PDDR_FECI2C;
    uint_8 filler8,filler9;
    uint_8 PDDR_SIMP1,PDDR_SIMP0,PDDR_TIMER,PDDR_UART,PDDR_DEBUG;
    uint_8  filler10;
    uint_8  PDDR_SDHC,PDDR_SSI;
    uint_8 filler11,filler12,filler13;
    /*Port Pin Data/Set Data Registers*/
    uint_8 PPDSDR_FBCTL,PPDSDR_BE,PPDSDR_CS,PPDSDR_DSPI;
    uint_8  filler14;
    uint_8 PPDSDR_FEC0,PPDSDR_FECI2C;
    uint_8 filler15,filler16;
    uint_8 PPDSDR_SIMP1,PPDSDR_SIMP0,PPDSDR_TIMER,PPDSDR_UART,PPDSDR_DEBUG;
    uint_8  filler17;
    uint_8  PPDSDR_SDHC,PPDSDR_SSI;
    uint_8 filler18,filler19,filler20;
    /*Port Clear Output Data Registers*/
    uint_8 PCLRR_FBCTL,PCLRR_BE,PCLRR_CS,PCLRR_DSPI;
    uint_8 filler21;
    uint_8 PCLRR_FEC0,PCLRR_FECI2C;
    uint_8 filler22,filler23;
    uint_8 PCLRR_SIMP1,PCLRR_SIMP0,PCLRR_TIMER,PCLRR_UART,PCLRR_DEBUG;
    uint_8  filler24;
    uint_8  PCLRR_SDHC,PCLRR_SSI;
    uint_8 filler25,filler26,filler27;
    /* Pin Assignment Registers*/
    
    uint_8 PAR_FBCTL,PAR_BE,PAR_CS;
    uint_8 filler28; 
    uint_8 PAR_DSPIH,PAR_DSPIL;
    uint_8 PAR_FEC,PAR_FECI2C;
    uint_8 PAR_IRQ0H,PAR_IRQ0L,PAR_IRQ1DEBUGH,PAR_IRQ1DEBUGL;
    uint_8 PAR_SIMP1H,PAR_SIMP1L,PAR_SIMP0,PAR_TIMER,PAR_UART;
    uint_8 filler29;
    uint_8 PAR_DEBUG,PAR_SDHC,PAR_SSIH,PAR_SSIL;
    uint_8 filler30,filler31;
    /*Mode Select Control Registers*/
    uint_8 MSCR_1,MSCR_2,MSCR_3,MSCR_4;
    /*Slew Rate/Drive Strength Control Registers*/
    uint_8 SRCR_DSPI,DSCR_FEC,SRCR_I2C,SRCR_IRQ,SRCR_SIM;
    uint_8 SRCR_TIMER,SRCR_UART;
    uint_8 filler32;
    uint_8 SRCR_SDHC,SRCR_SSI  ;
    uint_8 filler33,filler34;
    uint_8 PCRH,PCRL;
}  MCF5301_GPIO_STRUCT, _PTR_ MCF5301_GPIO_STRUCT_PTR;
typedef volatile struct mcf5301_gpio_struct _PTR_ VMCF5301_GPIO_STRUCT_PTR;

/*
** MCF5301_EDMA_STRUCT
** This structure defines eDMA registers
*/
typedef struct mcf5301_edma_struct {
    uint_32 CR;
    uint_32 ES;  
    uint_16 ERQ; 
    uint_16 EEI; 
    uint_8 SERQ;
    uint_8 CERQ;
    uint_8 SEEI;
    uint_8 CEEI;
    uint_8 CINT;
    uint_8 CERR;
    uint_8 SSRT;
    uint_8 CDNE;
    uint_16 INT; 
    uint_16 ERR;

    uint_8 DCHPRI[MCF5301_NUM_DMA_CH];

    struct {
        uint_32 SADDR;      
        uint_16 ATTR;       
        uint_16 SOFF;       
        uint_32 NBYTES;     
        uint_32 SLAST;      
        uint_32 DADDR;      
        uint_16 CITER;      
        uint_16 CITER_ELINK;
        uint_16 DOFF;       
        uint_32 DLAST_SGA;  
        uint_16 BITER;      
        uint_16 BITER_ELINK;
        uint_16 CSR;        
    } TCD[MCF5301_NUM_DMA_CH];

} MCF5301_EDMA_STRUCT, _PTR_ MCF5301_EDMA_STRUCT_PTR;
typedef volatile struct mcf5301_edma_struct _PTR_ VMCF5301_EDMA_STRUCT_PTR;


/*
** Cross-Bar Switch Module
*/
typedef struct mcf5301_xbs_struct {
    uint_32 PRS1;
    uint_32 CRS1;
    uint_32 PRS4;
    uint_32 CRS4;
    uint_32 PRS7;
    uint_32 CRS7;
} MCF5301_XBS_STRUCT, _PTR_ MCF5301_XBS_STRUCT_PTR;
typedef volatile struct mcf5301_xbs_struct _PTR_ VMCF5301_XBS_STRUCT_PTR;



/*
** MCF5301_STRUCT
** This structure defines the memory/registers provided by the MCF5301x
*/
typedef struct mcf5301_struct {
    MCF5301_SCM_A_STRUCT        SCM_A;      /* SCM (MPR and PACRs) */
    uchar                       filler0[0x4000 - 0 - sizeof(MCF5301_SCM_A_STRUCT)];   
    MCF5301_XBS_STRUCT          XBS;        /* Crossbar Switch */
    uchar                       filler1[0x8000 - 0x4000 - sizeof(MCF5301_XBS_STRUCT)];   
    MCF5XXX_FB_STRUCT           FB[MCF5301_NUM_FB_CS];         /* Mini-FlexBus */
    uchar                       filler2[0x30000 - 0x8000 - MCF5301_NUM_FB_CS * sizeof(MCF5XXX_FB_STRUCT)];   
    MCF5XXX_FEC_STRUCT          FEC0;       /* Fast Ethernet Controller - Registers and MIB RAM */
    uchar                       filler3[0x34000 - 0x30000 - sizeof(MCF5XXX_FEC_STRUCT)];   
    MCF5XXX_FEC_STRUCT          FEC1;       /* Fast Ethernet Controller - Registers and MIB RAM */
    uchar                       filler4[0x40000 - 0x34000 - sizeof(MCF5XXX_FEC_STRUCT)];   
    MCF5301_SCM_B_STRUCT        SCM_B;      /* SCM (CWT and Core Fault Registers) */
    uchar                       filler5[0x44000 - 0x40000 - sizeof(MCF5301_SCM_B_STRUCT)];   
    MCF5301_EDMA_STRUCT         EDMA;       /* DMA Channels */
    uchar                       filler6[0x48000 - 0x44000 - sizeof(MCF5301_EDMA_STRUCT)];   
    MCF53XX_ICTRL0_STRUCT       ICTRL0;     /* Interrupt Controller 0 */
    uchar                       filler7[0x4c000 - 0x48000 - sizeof(MCF53XX_ICTRL0_STRUCT)];   
    MCF53XX_ICTRL1_STRUCT       ICTRL1;     /* Interrupt Controller 1 */
    uchar                       filler8[0x54000 - 0x4c000 - sizeof(MCF53XX_ICTRL1_STRUCT)];   
    MCF53XX_IACK_STRUCT         IACK;
    uchar                       filler9[0x58000 - 0x54000 - sizeof(MCF53XX_IACK_STRUCT)];
    MCF53XX_I2C_STRUCT          I2C;        /* I2C */
    uchar                       filler10[0x5c000 - 0x58000 - sizeof(MCF53XX_I2C_STRUCT)];
    MCF5XXX_DSPI_STRUCT         DSPI;       /* DSPI */
    uchar                       filler11[0x60000 - 0x5c000 - sizeof(MCF5XXX_DSPI_STRUCT)];
    MCF53XX_UART_STRUCT         UART[MCF5301_NUM_UARTS];  /* UART */
    uchar                       filler12[0x70000 - 0x60000 - MCF5301_NUM_UARTS * sizeof(MCF53XX_UART_STRUCT)];   
    MCF53XX_DMA_TIMER_STRUCT    DMA_TIMER[MCF5301_NUM_DMA_TIMERS ];/* DMA Timers */
    uchar                       filler13[0x80000 - 0x70000 - MCF5301_NUM_DMA_TIMERS * sizeof(MCF53XX_DMA_TIMER_STRUCT)];         
    MCF5XXX_PIT_STRUCT          PIT[MCF5301_NUM_TIMERS];    /* Programmable Interrupt Timers */    
    MCF53XX_EPORT_STRUCT        EPORT[MCF5301_NUM_EPORT];   /* Edge Port */
    uchar                       filler15[0xA0000 - 0x90000 - MCF5301_NUM_EPORT * sizeof(MCF53XX_EPORT_STRUCT)];  
    MCF53XX_CCM_STRUCT          CCM;        /* Chip Configuration Module */    
    uchar                       filler17[0xa4000 - 0xa0000-sizeof(MCF53XX_CCM_STRUCT)];   
    MCF5301_GPIO_STRUCT         GPIO;       /* Ports */
    uchar                       filler18[0xa8000 - 0xA4000 - sizeof(MCF5301_GPIO_STRUCT)];   
    MCF53XX_RTC_STRUCT          RTC;        /* Realtime */
    uchar                       filler19[0xac000 - 0xa8000 - sizeof(MCF53XX_RTC_STRUCT)];   
    MCF53XX_SIM_STRUCT          SIM;        /* Sim */
    uchar                       filler20[0xb0000 - 0xac000 - sizeof(MCF53XX_SIM_STRUCT)];   
    MCF5XXX_USBOTG_STRUCT       USBOTG;     /*Usb on the go */
    uchar                       filler21[0xb4000 - 0xb0000 - sizeof(MCF5XXX_USBOTG_STRUCT)];   
    MCF53XX_USBHOST_STRUCT      USBHOST;    /* Usb host */
    uchar                       filler22[0xb8000 - 0xb4000 - sizeof(MCF53XX_USBHOST_STRUCT)]; 
    MCF53XX_SDRAM_CTRL_STRUCT   SDRAMC;
    uchar                       filler23[0xbc000 - 0xb8000 - sizeof(MCF53XX_SDRAM_CTRL_STRUCT)];
    MCF53XX_SSI_STRUCT          SSI;
    uchar                       filler24[0xc0000 - 0xbc000 - sizeof(MCF53XX_SSI_STRUCT)];
    MCF5301_PLL_STRUCT          PLL;
    uchar                       filler25[0xc4000 - 0xc0000 - sizeof( MCF5301_PLL_STRUCT)];     
    MCF53XX_RNG_STRUCT          RNG;
    uchar                       filler26[0xc8000 - 0xc4000 - sizeof(MCF53XX_RNG_STRUCT)];    
    MCF53XX_IIM_STRUCT          IIM;
    uchar                       filler27[0xcc000 - 0xc8000 - sizeof(MCF53XX_IIM_STRUCT)]; 
    SDHC_MEMMAP                 ESDHC;

} MCF5301_STRUCT, _PTR_ MCF5301_STRUCT_PTR;
typedef volatile struct mcf5301_struct _PTR_ VMCF5301_STRUCT_PTR;

typedef struct psp_support_struct
{
   uint_32 ACR_VALS[MCF5301_NUM_ACRS];
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
extern uchar __KERNEL_DATA_VERIFY_ENABLE[]; /* CR1327 */

void    _mcf5301_initialize_support(uint_32);

void    _mcf5301_icache_enable(uint_32);
void    _mcf5301_icache_disable(void);
void    _mcf5301_icache_invalidate(void);

void    _mcf5301_dcache_enable(uint_32);
void    _mcf5301_dcache_disable(void);
void    _mcf5301_dcache_invalidate(void);

void    _mcf5301_cache_enable(uint_32);
void    _mcf5301_cache_disable(void);

void    _icache_invalidate_mlines(pointer,uint_32,uint_32);
void    _dcache_flush_invalidate_mlines(pointer,uint_32,uint_32,uint_32,uint_32);

void    _mcf5301_mmu_init(uint_32);
uint_32 _mcf5301_mmu_enable(void);
uint_32 _mcf5301_mmu_disable(void);
uint_32 _mcf5301_mmu_add_region(pointer,uint_32,uint_32);

void    __psp_enable_acrs(uint_32_ptr);
void    __psp_clear_acrs(void);

void _psp_dcache_flush_all(uint_32, uint_32, uint_32);

void _dcache_flush(pointer, uint_32, uint_32);
void _dcache_flush_phy(pointer, uint_32, uint_32);

#endif /* __ASM__ */

#ifdef __cplusplus
}
#endif

#endif /* __mcf5301_h__ */

