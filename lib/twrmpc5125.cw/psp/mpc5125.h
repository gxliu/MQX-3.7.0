#ifndef __mpc5125_h__
#define __mpc5125_h__
/**HEADER********************************************************************
* 
* Copyright (c) 2008 Freescale Semiconductor;
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
* $FileName: mpc5125.h$
* $Version :  3.6.5.0$
* $Date    :  Feb-11-2011$
*
* Comments:
*
*   This file contains definitions for the MPC5125 family and peripherals.
*
*END************************************************************************/

/* The 5215 has an e300 core */
#include <e300core.h>

#define _REG_MASK(m,r,f)   (m ## _ ## r ## _ ## f ## _MASK)
#define _REG_SHIFT(m,r,f)  (m ## _ ## r ## _ ## f ## _SHIFT)
#define GET_FIELD_OF_REG(p,m,r,f) ((p->r & _REG_MASK(m,r,f)) >> _REG_SHIFT(m,r,f))
#define SET_FIELD_OF_REG(p,m,r,f,v) { p->r &= ~ _REG_MASK(m,r,f); p->r |= (v << _REG_SHIFT(m,r,f)) & _REG_MASK(m,r,f); }
#define RESERVED_REGISTER(start,next) uchar R_ ## start[next-start]
#ifndef ELEMENTS_OF
   #define ELEMENTS_OF(x) ( sizeof(x)/sizeof(x[0]) )
#endif
#ifndef min
   #define min(x,y) ((x)<(y))?(x):(y)
#endif

#ifndef __ASM__
#include <mpc512x_bdlc.h>
#include <mpc512x_ccm.h>
#include <mpc512x_csbarb.h>
#include <mpc512x_diu.h>
#include <mpc512x_dma.h>
#include <mpc512x_fec.h>
#include <mpc512x_gpio.h>
#include <mpc512x_gpt.h>
#include <mpc512x_i2c.h>
#include <mpc512x_iim.h>
#include <mpc512x_ioc.h>
#include <mpc512x_ipic.h>
#include <mpc512x_lpc.h>
#include <mpc512x_mddrc.h>
#include <mpc512x_mscan.h>
#include <mpc512x_prioman.h>
#include <mpc512x_pmc.h>
#include <mpc512x_psc.h>
#include <mpc512x_rm.h>
#include <mpc512x_rtc.h>
#include <mpc512x_sc.h>
#include <mpc512x_sdhc.h>
#include <mpc512x_usb.h>
#include <mpc512x_wdt.h>
#include <reg_nfc.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*--------------------------------------------------------------------------*/
/*
**                   MQX REQUIRED DEFINITIONS
**
** Other MQX kernel and component functions require these definitions to exist.
*/

/* Indicate processor type */
#define PSP_MPC5125  1 


#define PSP_SUPPORT_STRUCT_DEFINED                   1
#define PSP_HAS_DSP                                  0
#define PSP_HAS_DSP_TASKS                            0
#define PSP_HAS_FPU                                  1
#define PSP_ALWAYS_SAVE_AND_RESTORE_VOLATILE_FP_REGS 1

#ifndef MQXCFG_INCLUDE_MMU_SUPPORT
   #define MQXCFG_INCLUDE_MMU_SUPPORT                0     // was MQX_MMU_CONTEXT_EXISTS, that conflicts with an error code.
#endif
#undef PSP_NO_MMU_YET

#ifndef __ASM__

/* Do you want to verify kernel data can be read and written correctly */
#define PSP_KERNEL_DATA_VERIFY_ENABLE  ((uint_32)__KERNEL_DATA_VERIFY_ENABLE) 

/*
** Define padding needed to make the STOREBLOCK_STRUCT align properly
** to cache line size (see mem_prv.h)
*/
#define PSP_MEM_STOREBLOCK_ALIGNMENT   (2) /* padding in _mqx_uints */


/*---------------------------------------------------------------------------*/
/*
**  Internal Register Memory Map
** 
*/


#define MPC5125_SET_IMMR(x)     __psp_set_mbar(x)
#define MPC5125_GET_IMMR()      __psp_get_mbar()



/*==========================================================================*/
// Interrupt/Exception definitions

#define MPC5125_IRQ_BASE_VECTOR              (0x40)
#define MPC5125_Error_VECTOR                 (MPC5125_IRQ_BASE_VECTOR+MPC5125_INT_ID_Error          )
#define MPC5125_GPT10_VECTOR                 (MPC5125_IRQ_BASE_VECTOR+MPC5125_INT_ID_GPT10          )
#define MPC5125_GPT11_VECTOR                 (MPC5125_IRQ_BASE_VECTOR+MPC5125_INT_ID_GPT11          )
#define MPC5125_SDHC2_VECTOR                 (MPC5125_IRQ_BASE_VECTOR+MPC5125_INT_ID_SDHC2          )
#define MPC5125_FEC1_VECTOR                  (MPC5125_IRQ_BASE_VECTOR+MPC5125_INT_ID_FEC1           )
#define MPC5125_FEC2_VECTOR                  (MPC5125_IRQ_BASE_VECTOR+MPC5125_INT_ID_FEC2           )
#define MPC5125_NFC_VECTOR                   (MPC5125_IRQ_BASE_VECTOR+MPC5125_INT_ID_NFC            )
#define MPC5125_LPC_VECTOR                   (MPC5125_IRQ_BASE_VECTOR+MPC5125_INT_ID_LPC            )
#define MPC5125_SDHC1_VECTOR                 (MPC5125_IRQ_BASE_VECTOR+MPC5125_INT_ID_SDHC1          )
#define MPC5125_I2C1_VECTOR                  (MPC5125_IRQ_BASE_VECTOR+MPC5125_INT_ID_I2C1           )
#define MPC5125_I2C2_VECTOR                  (MPC5125_IRQ_BASE_VECTOR+MPC5125_INT_ID_I2C2           )
#define MPC5125_I2C3_VECTOR                  (MPC5125_IRQ_BASE_VECTOR+MPC5125_INT_ID_I2C3           )
#define MPC5125_MSCAN1_VECTOR                (MPC5125_IRQ_BASE_VECTOR+MPC5125_INT_ID_MSCAN1         )
#define MPC5125_MSCAN2_VECTOR                (MPC5125_IRQ_BASE_VECTOR+MPC5125_INT_ID_MSCAN2         )
#define MPC5125_BDLC_VECTOR                  (MPC5125_IRQ_BASE_VECTOR+MPC5125_INT_ID_BDLC           )
#define MPC5125_GPT0_VECTOR                  (MPC5125_IRQ_BASE_VECTOR+MPC5125_INT_ID_GPT0           )
#define MPC5125_GPT1_VECTOR                  (MPC5125_IRQ_BASE_VECTOR+MPC5125_INT_ID_GPT1           )
#define MPC5125_IRQ1_VECTOR                  (MPC5125_IRQ_BASE_VECTOR+MPC5125_INT_ID_IRQ1           )
#define MPC5125_PSC4_VECTOR                  (MPC5125_IRQ_BASE_VECTOR+MPC5125_INT_ID_PSC4           )
#define MPC5125_PSC5_VECTOR                  (MPC5125_IRQ_BASE_VECTOR+MPC5125_INT_ID_PSC5           )
#define MPC5125_PSC6_VECTOR                  (MPC5125_IRQ_BASE_VECTOR+MPC5125_INT_ID_PSC6           )
#define MPC5125_PSC7_VECTOR                  (MPC5125_IRQ_BASE_VECTOR+MPC5125_INT_ID_PSC7           )
#define MPC5125_PSC8_VECTOR                  (MPC5125_IRQ_BASE_VECTOR+MPC5125_INT_ID_PSC8           )
#define MPC5125_PSC9_VECTOR                  (MPC5125_IRQ_BASE_VECTOR+MPC5125_INT_ID_PSC9           )
#define MPC5125_GPT8_VECTOR                  (MPC5125_IRQ_BASE_VECTOR+MPC5125_INT_ID_GPT8           )
#define MPC5125_GPT9_VECTOR                  (MPC5125_IRQ_BASE_VECTOR+MPC5125_INT_ID_GPT9           )
#define MPC5125_FIFOC_VECTOR                 (MPC5125_IRQ_BASE_VECTOR+MPC5125_INT_ID_FIFOC          )
#define MPC5125_USB2OTG1_VECTOR              (MPC5125_IRQ_BASE_VECTOR+MPC5125_INT_ID_USB2OTG1       )
#define MPC5125_USB2OTG2_VECTOR              (MPC5125_IRQ_BASE_VECTOR+MPC5125_INT_ID_USB2OTG2       )
#define MPC5125_IRQ0_VECTOR                  (MPC5125_IRQ_BASE_VECTOR+MPC5125_INT_ID_IRQ0           )
#define MPC5125_DIU_VECTOR                   (MPC5125_IRQ_BASE_VECTOR+MPC5125_INT_ID_DIU            )
#define MPC5125_DMA2_VECTOR                  (MPC5125_IRQ_BASE_VECTOR+MPC5125_INT_ID_DMA2           )
#define MPC5125_PSC0_VECTOR                  (MPC5125_IRQ_BASE_VECTOR+MPC5125_INT_ID_PSC0           )
#define MPC5125_PSC1_VECTOR                  (MPC5125_IRQ_BASE_VECTOR+MPC5125_INT_ID_PSC1           )
#define MPC5125_PSC2_VECTOR                  (MPC5125_IRQ_BASE_VECTOR+MPC5125_INT_ID_PSC2           )
#define MPC5125_PSC3_VECTOR                  (MPC5125_IRQ_BASE_VECTOR+MPC5125_INT_ID_PSC3           )
#define MPC5125_GPT2_VECTOR                  (MPC5125_IRQ_BASE_VECTOR+MPC5125_INT_ID_GPT2           )
#define MPC5125_GPT3_VECTOR                  (MPC5125_IRQ_BASE_VECTOR+MPC5125_INT_ID_GPT3           )
#define MPC5125_GPT4_VECTOR                  (MPC5125_IRQ_BASE_VECTOR+MPC5125_INT_ID_GPT4           )
#define MPC5125_GPT5_VECTOR                  (MPC5125_IRQ_BASE_VECTOR+MPC5125_INT_ID_GPT5           )
#define MPC5125_GPT6_VECTOR                  (MPC5125_IRQ_BASE_VECTOR+MPC5125_INT_ID_GPT6           )
#define MPC5125_GPT7_VECTOR                  (MPC5125_IRQ_BASE_VECTOR+MPC5125_INT_ID_GPT7           )
#define MPC5125_GPIO1_VECTOR                 (MPC5125_IRQ_BASE_VECTOR+MPC5125_INT_ID_GPIO1          )
#define MPC5125_RTC_SEC_VECTOR               (MPC5125_IRQ_BASE_VECTOR+MPC5125_INT_ID_RTC_SEC        )
#define MPC5125_RTC_ALARM_VECTOR             (MPC5125_IRQ_BASE_VECTOR+MPC5125_INT_ID_RTC_ALARM      )
#define MPC5125_DDR_VECTOR                   (MPC5125_IRQ_BASE_VECTOR+MPC5125_INT_ID_DDR            )
#define MPC5125_SBA_VECTOR                   (MPC5125_IRQ_BASE_VECTOR+MPC5125_INT_ID_SBA            )
#define MPC5125_PMC_VECTOR                   (MPC5125_IRQ_BASE_VECTOR+MPC5125_INT_ID_PMC            )
#define MPC5125_USB2OTG1_WKUP_VECTOR         (MPC5125_IRQ_BASE_VECTOR+MPC5125_INT_ID_USB2OTG1_WKUP  )
#define MPC5125_USB2OTG2_WKUP_VECTOR         (MPC5125_IRQ_BASE_VECTOR+MPC5125_INT_ID_USB2OTG2_WKUP  )
#define MPC5125_GPIO2_VECTOR                 (MPC5125_IRQ_BASE_VECTOR+MPC5125_INT_ID_GPIO2          )
#define MPC5125_TEMP_105C_VECTOR             (MPC5125_IRQ_BASE_VECTOR+MPC5125_INT_ID_TEMP_105C      )
#define MPC5125_IIM_VECTOR                   (MPC5125_IRQ_BASE_VECTOR+MPC5125_INT_ID_IIM            )
#define MPC5125_PRIOMON_VECTOR               (MPC5125_IRQ_BASE_VECTOR+MPC5125_INT_ID_PRIOMON        )
#define MPC5125_MSCAN3_VECTOR                (MPC5125_IRQ_BASE_VECTOR+MPC5125_INT_ID_MSCAN3         )
#define MPC5125_MSCAN4_VECTOR                (MPC5125_IRQ_BASE_VECTOR+MPC5125_INT_ID_MSCAN4         )
#define MPC5125_GPT12_VECTOR                 (MPC5125_IRQ_BASE_VECTOR+MPC5125_INT_ID_GPT12          )
#define MPC5125_GPT13_VECTOR                 (MPC5125_IRQ_BASE_VECTOR+MPC5125_INT_ID_GPT13          )
#define MPC5125_GPT14_VECTOR                 (MPC5125_IRQ_BASE_VECTOR+MPC5125_INT_ID_GPT14          )
#define MPC5125_GPT15_VECTOR                 (MPC5125_IRQ_BASE_VECTOR+MPC5125_INT_ID_GPT15          )

#define MPC5125_FIRST_ICTL                   MPC5125_GPT10_VECTOR
#define MPC5125_LAST_ICTL                    MPC5125_GPT15_VECTOR
#define MPC5125_TOTAL_ICTL                   (MPC5125_LAST_ICTL+1)

typedef uint_32 PSP_INTERRUPT_TABLE_INDEX ;

/*
** MPC5125_STRUCT
** This structure defines the memory/registers provided by the MPC5125
*/
typedef struct mpc5125_struct {
    MPC5125_SYSTEM_CONFIGURATION_STRUCT      SYSCON;                          // 0x00000-001FF System configuration (XLBMEN) Chapter 2/2-1
    RESERVED_REGISTER(0x00200,0x00900);                                       // 0x00200-008FF Reserved2
    MPC5125_WDT_STRUCT                       WDT;                             // 0x00900-009FF Software watchdog timer (WDT) Chapter 29/29-1
    MPC5125_REAL_TIME_CLOCK                  RTC;                             // 0x00A00-00AFF Real time clock (RTC) Chapter 27/27-1
    MPC5125_GPT_STRUCT                       GPT1;                            // 0x00B00-00BFF General purpose timer 1 (GPT1) Chapter 15/15-1
    MPC5125_IPIC_STRUCT                      IPIC;                            // 0x00C00-00CFF Integrated programmable interrupt controller (IPIC) Chapter 18/18-1
    MPC5125_CSB_ARBITER_STRUCT               CSB;                             // 0x00D00-00DFF CSB arbiter Chapter 8/8-1
    MPC5125_RESET_STRUCT                     RESET;                           // 0x00E00-00EFF Reset module (RESET) Chapter 4/4-1
    MPC5125_CCM_STRUCT                       CCM;                             // 0x00F00-00FFF Clock module (CLOCK) Chapter 5/5-1
    MPC5125_PMC_STRUCT                       PMC;                             // 0x01000-010FF Power management control (PMC) Chapter 24/24-1
    MPC5125_GPIO_STRUCT                      GPIO[MPC5125_NUM_GPIO_PORTS];    // 0x01100-011FF General Purpose I/O (GPIO1/2) Chapter 16/16-1
    RESERVED_REGISTER(0x01200 ,0x01300);                                      // 0x01200-012FF Reserved
    MPC5125_MSCAN_STRUCT                     MSCAN1;                          // 0x01300-0137F MSCAN1 Chapter 22/22-1
    MPC5125_MSCAN_STRUCT                     MSCAN2;                          // 0x01380-013FF MSCAN2 Chapter 22/22-1
    MPC5125_BDLC_STRUCT                      BDLC;                            // 0x01400-014FF Byte data link controller (BDLC) Chapter 6/6-1
    MPC5125_SDHC_STRUCT                      SDHC1;                           // 0x01500-015FF Secure digital host controller (SDHC1) Chapter 28/28-1
    RESERVED_REGISTER(0x01600,0x01700);                                       // 0x01600-016FF Reserved                          
    MPC5125_I2C_STRUCT                       I2C;                             //0x01700-017FF Inter-integrated circuit (I2C1..3)  Chapter 19/19-1
    RESERVED_REGISTER(0x01800,0x02000);                                       // 0x01800-01FFF Reserved
    RESERVED_REGISTER(0x02000,0x02100);                                       // 0x02000-020FF Reserved
    MPC5125_DIU_STRUCT                       DIU;                             // 0x02100-021FF Display Interface Unit (DIU) Chapter 10/10-1
    RESERVED_REGISTER(0x02200,0x02300);                                       // 0x02200-022FF Reserved
    MPC5125_MSCAN_STRUCT                     MSCAN3;                          // 0x02300-0237F MSCAN3 Chapter 22/22-1
    MPC5125_MSCAN_STRUCT                     MSCAN4;                          // 0x02380-023FF MSCAN4 Chapter 22/22-1
    RESERVED_REGISTER(0x02400,0x02800);                                       // 0x02400-027FF Reserved
    MPC512X_FEC_STRUCT                       FEC1;                            // 0x02800-02FFF Fast Ethernet Controller (FEC1) Chapter 14/14-1
    MPC5125_USB_STRUCT                       USB_ULPI1;                       // 0x03000-033FF USB ULPI1 Chapter 32/32-1
    RESERVED_REGISTER(0x03400,0x04000);                                       // 0x03400-03FFF Reserved
    MPC5125_USB_STRUCT                       USB_ULPI2;                       // 0x04000-043FF USB ULPI2 Chapter 32/32-1
    RESERVED_REGISTER(0x04400,0x04800);                                       // 0x04400-047FF Reserved
    MPC512X_FEC_STRUCT                       FEC2;                            // 0x04800-04FFF Fast Ethernet Controller (FEC2) Chapter 14/14-1
    MPC5125_GPT_STRUCT                       GPT2;                            // 0x05000-050FF General purpose timer 2 (GPT2) Chapter 15/15-1
    MPC5125_SDHC_STRUCT                      SDHC2;                           // 0x05100-051FF Secure digital host controller (SDHC2) Chapter 28/28-1
    RESERVED_REGISTER(0x05200,0x09000);                                       // 0x05200-08FFF Reserved
    MPC5125_MDDRC_STRUCT                     MDDRC;                           // 0x09000-09FFF Multi-port DRAM controller (MDDRC) Chapter 11/11-1
    MPC5125_IO_CONTROL_STRUCT                IOC;                             // 0x0A000-0AFFF I/O control Chapter 20/20-1
    MPC5125_IIM_STRUCT                       IIM;                             // 0x0B000-0BFFF IC identification module (IIM) Chapter 17/17-1
    RESERVED_REGISTER(0x0C000,0x10000);                                       // 0x0C000-0FFFF Reserved
    MPC5125_LPC_STRUCT                       LPC;                             // 0x10000-101FF LocalPlus controller (LPC) Chapter 21/21-1
    RESERVED_REGISTER(0x10200,0x11000);                                       // 0x10200-10FFF Reserved
    MPC5125_PSC_STRUCT                       PSC[MPC5125_NUM_PSC];            // 0x11n00-11nFF Programmable Serial Controller n (PSCn) Chapter 25/25-1
    RESERVED_REGISTER(0x11A00,0x11F00);                                       // 0x11A00-11EFF Reserved
    MPC5125_PSC_FIFO_CONTROLLER              PSC_FIFO;                        // 0x11F00-11FFF Serial FIFO (SFIFO) for PSC 0 to 9 Chapter 25/25-1
    RESERVED_REGISTER(0x12000,0x14000);                                       // 0x12000-13FFF Reserved
    MPC5125_DMA_STRUCT                       DMA;                             // 0x14000-157FF DMA Chapter 9/9-1
    RESERVED_REGISTER(0x18000,0x100000);                                      // 0x15800-FFFFF Reserved
} MPC5125_STRUCT, _PTR_ MPC5125_STRUCT_PTR;

typedef volatile struct mpc5125_struct _PTR_ VMPC5125_STRUCT_PTR;


/*==========================================================================*/
// MMU management tables

typedef struct psp_bat_register_entry
{
   uchar_ptr    lo,hi;
   uint_32      attr_lo, attr_hi;
} PSP_BAT_REGISTER_ENTRY, _PTR_ PSP_BAT_REGISTER_ENTRY_PTR;

typedef struct psp_virtual_context_struct
   /* This structure is used to store the virtual context for a task.
   ** The address of this structure is kept in the task extensions struct.
   */
{
   /* What blocks of memory are assigned to this task */
   QUEUE_STRUCT PAGE_INFO;
} PSP_VIRTUAL_CONTEXT_STRUCT, _PTR_ PSP_VIRTUAL_CONTEXT_STRUCT_PTR;

typedef struct psp_pte_struct
   /* This structure is used to store the PageTableEntry */
{
   uint_32  UPPER_PTE;
   uint_32  LOWER_PTE;
} PSP_PTE_STRUCT, _PTR_ PSP_PTE_STRUCT_PTR;

typedef struct psp_page_info_struct
   /* This structure is used to store memory block information
   ** for use with the virtual memory MMU support
   */
{
   /* Queue header */
   QUEUE_ELEMENT_STRUCT ELEMENT;

   /* Physical Memory location */
   uchar_ptr            ADDR;

   /* Virtual Memory location */
   uchar_ptr            VADDR;

   /* page table entry struct */
   PSP_PTE_STRUCT       PTE;

   /* page table entry address in the table */
   PSP_PTE_STRUCT_PTR   PTE_PTR;

} PSP_PAGE_INFO_STRUCT, _PTR_ PSP_PAGE_INFO_STRUCT_PTR;

typedef struct psp_support_struct
   /* This structure is used to maintain the PSP support information */
{
   /* How many code BATs set so far */
   PSP_BAT_REGISTER_ENTRY   IBAT_TABLE[E300CORE_NUM_IBATS];
   PSP_BAT_REGISTER_ENTRY   DBAT_TABLE[E300CORE_NUM_DBATS];
   uint_16                  IBAT_COUNT;
   uint_16                  DBAT_COUNT;
   
   pointer                  IMMR_BASE;
   uint_32                  CLKIN;
   
   /* memory location for mmu pages */
   uint_32_ptr              MMU_PAGE_TABLE_BASE;

   /* Memory block of MMU mem ptrs */
   PSP_PAGE_INFO_STRUCT_PTR MMU_PAGE_INFO_BASE;

   /* Page size */
   uint_32                  PAGE_SIZE;

   /* A queue of available unmapped memory blocks */
   QUEUE_STRUCT             VPAGE_FREELIST;

   /* A light weight semaphore to protect the memory queue */
   LWSEM_STRUCT             VPAGE_FREELIST_LWSEM;

   /* A light weight semaphore to protect the mmu pages */
   LWSEM_STRUCT             MMU_LWSEM;

} PSP_SUPPORT_STRUCT, _PTR_ PSP_SUPPORT_STRUCT_PTR;

/*--------------------------------------------------------------------------*/
/*
**                  EXTERNAL DATA
*/


/*--------------------------------------------------------------------------*/
/*
**                  PROTOTYPES OF PSP FUNCTIONS
*/

extern uchar   __KERNEL_DATA_VERIFY_ENABLE[]; 

extern uint_32 _mpc5125_get_sys_clock(uint_32 external_clock);
extern uint_32 _mpc5125_get_csb_clock(uint_32 external_clock);
extern uint_32 _mpc5125_get_ipb_clock(uint_32 external_clock);
extern uint_32 _mpc5125_get_ppc_clock(uint_32 external_clock);
extern uint_32 _mpc5125_get_diu_clock(uint_32 external_clock);
extern void    _mpc5125_set_diu_clock(uint_32 extclk,uint_32 freq,uint_32 delay, boolean invert);
extern void    _mpc5125_enable_i2c_clock(void);
extern void    _mpc512x_enable_fec_clock(uint_32 fecnum);
extern boolean _mpc512x_enable_can_clock(uint_32 extclk, uint_32 candev, uint_32 src, uint_32 canclk);
extern boolean _mpc512x_set_psc_clock(uint_32 extclk, uint_32 pscdev, uint_32 src, uint_32 pscclk);

extern void    _mpc5125_prioman_config(uint_32_ptr prioman_set_ptr);
extern void    _mpc5125_csbarb_init(void);
extern uint_32 _mpc5125_psc_fifo_slice_alloc(uint_32 psc, uint_32 requested);
extern void    _mpc5125_psc_fifo_slice_free(uint_32 psc);

#endif

#ifdef __cplusplus
}
#endif

#endif
/* EOF */
