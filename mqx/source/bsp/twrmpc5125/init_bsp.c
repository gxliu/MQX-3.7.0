/**HEADER********************************************************************
* 
* Copyright (c) 2008 Freescale Semiconductor;
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
* $FileName: init_bsp.c$
* $Version : 3.7.3.0$
* $Date    : Feb-7-2011$
*
* Comments:
*
*   This file contains the source functions for functions required to
*   specifically initialize the card.
*
*END************************************************************************/

#include "mqx_inc.h"
#include "bsp.h"
#include "bsp_prv.h"
#include "bsp_rev.h"
#include "io_rev.h"
#include "bsp_rev.h"
#include "init_sdhc.c"
#include "init_sdcard.c"

const char _PTR_ _mqx_bsp_revision = REAL_NUM_TO_STR(BSP_REVISION);
const char _PTR_ _mqx_io_revision  = REAL_NUM_TO_STR(IO_REVISION);

/*
** Only use when debugging with JTAG and cache and MMU are interferring
** with the debugging
*/
//volatile uint_32 _mqx_monitor_type = MQX_MONITOR_TYPE_BDM;


#if BSPCF_USE_PAGE_TABLES
   /* Defined in link.lcf */
   extern uchar __PAGE_TABLE_START[];
   extern uchar __PAGE_TABLE_SIZE[];
   extern uchar __VIRTUAL_MEMORY_START[];
   extern uchar __VIRTUAL_MEMORY_SIZE[];

   PSP_MMU_VINIT_STRUCT mmu_init = {
      /* MMU_PAGE_TABLE_BASE  */ __PAGE_TABLE_START,
      /* MMU_PAGE_TABLE_SIZE  */ (uint_32)__PAGE_TABLE_SIZE,

   /* Needed for virtual contexts */
      /* UNMAPPED_MEMORY_BASE */ __VIRTUAL_MEMORY_START,
      /* UNMAPPED_MEMORY_SIZE */ (uint_32)__VIRTUAL_MEMORY_SIZE
   };
#endif

static void _bsp_null_isr(pointer unused) {}

MPC5125_INT_GROUP_PARAM_STRUCT mpc5125_int_group_sysa_param_list = {
   /* Group ID      */ MPC5125_IPIC_INT_GID_SYSA,
   /* Group Type    */ MPC5125_IPIC_INT_GTYPE_GROUP,
   /* Priority list */ {MPC5125_IPIC_SYSA_PSC4,
                        MPC5125_IPIC_SYSA_PSC5,
                        MPC5125_IPIC_SYSA_PSC6,
                        MPC5125_IPIC_SYSA_PSC7,
                        MPC5125_IPIC_SYSA_PSC8,
                        MPC5125_IPIC_SYSA_PSC9,
                        MPC5125_IPIC_SYSA_GPT8,
                        MPC5125_IPIC_SYSA_GPT9
                       }
};

MPC5125_INT_GROUP_PARAM_STRUCT mpc5125_int_group_sysb_param_list = {
   /* Group ID      */ MPC5125_IPIC_INT_GID_SYSB,
   /* Group Type    */ MPC5125_IPIC_INT_GTYPE_GROUP,
   /* Priority list */ {MPC5125_IPIC_SYSB_FIFOC,
                        MPC5125_IPIC_SYSB_RSVD0,
                        MPC5125_IPIC_SYSB_RSVD1,
                        MPC5125_IPIC_SYSB_USBOTG1,
                        MPC5125_IPIC_SYSB_USBOTG2,
                        MPC5125_IPIC_SYSB_RSVD2,
                        MPC5125_IPIC_SYSB_RSVD3,
                        MPC5125_IPIC_SYSB_RSVD4
                       }
};

MPC5125_INT_GROUP_PARAM_STRUCT mpc5125_int_group_sysc_param_list = {
   /* Group ID      */ MPC5125_IPIC_INT_GID_SYSC,
   /* Group Type    */ MPC5125_IPIC_INT_GTYPE_GROUP,
   /* Priority list */ {MPC5125_IPIC_SYSC_GPT10,
                        MPC5125_IPIC_SYSC_GPT11,
                        MPC5125_IPIC_SYSC_SDHC2,
                        MPC5125_IPIC_SYSC_FEC1,
                        MPC5125_IPIC_SYSC_FEC2,
                        MPC5125_IPIC_SYSC_NFC,
                        MPC5125_IPIC_SYSC_LPC,
                        MPC5125_IPIC_SYSC_SDHC1
                       }
};

MPC5125_INT_GROUP_PARAM_STRUCT mpc5125_int_group_sysd_param_list = {
   /* Group ID      */ MPC5125_IPIC_INT_GID_SYSD,
   /* Group Type    */ MPC5125_IPIC_INT_GTYPE_GROUP,
   /* Priority list */ {MPC5125_IPIC_SYSD_I2C1,
                        MPC5125_IPIC_SYSD_I2C2,
                        MPC5125_IPIC_SYSD_I2C3,
                        MPC5125_IPIC_SYSD_MSCAN1,
                        MPC5125_IPIC_SYSD_MSCAN2,
                        MPC5125_IPIC_SYSD_BDLC,
                        MPC5125_IPIC_SYSD_GPT0,
                        MPC5125_IPIC_SYSD_GPT1
                       }
};

MPC5125_INT_GROUP_PARAM_STRUCT mpc5125_int_group_mixa_param_list = {
   /* Group ID      */ MPC5125_IPIC_INT_GID_MIXA,
   /* Group Type    */ MPC5125_IPIC_INT_GTYPE_GROUP,
   /* Priority list */ {MPC5125_IPIC_MIXA_DUI,
                        MPC5125_IPIC_MIXA_DMA,
                        MPC5125_IPIC_MIXA_Reserved0,
                        MPC5125_IPIC_MIXA_Reserved1,
                        MPC5125_IPIC_MIXA_IRQ0,
                        MPC5125_IPIC_MIXA_IRQ1,
                        MPC5125_IPIC_MIXA_Reserved2,
                        MPC5125_IPIC_MIXA_Reserved3
                       }
};

MPC5125_INT_GROUP_PARAM_STRUCT mpc5125_int_group_mixb_param_list = {
   /* Group ID      */ MPC5125_IPIC_INT_GID_MIXB,
   /* Group Type    */ MPC5125_IPIC_INT_GTYPE_GROUP,
   /* Priority list */ {MPC5125_IPIC_MIXB_PCS0,
                        MPC5125_IPIC_MIXB_PCS1,
                        MPC5125_IPIC_MIXB_PCS2,
                        MPC5125_IPIC_MIXB_PCS3,
                        MPC5125_IPIC_MIXB_Reserved0,
                        MPC5125_IPIC_MIXB_Reserved1,
                        MPC5125_IPIC_MIXB_Reserved2,
                        MPC5125_IPIC_MIXB_Reserved3
                       }
};


/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _bsp_enable_card
* Returned Value   : uint_32 result
* Comments         :
*   This function sets up operation of the card.
*
*END*----------------------------------------------------------------------*/

uint_32 _bsp_enable_card(void)
{ 
   KERNEL_DATA_STRUCT_PTR  kernel_data;
   uint_32                 result;
   uint_32                 timer_preload;
   uint_32                 i=0, t;

   #if BSPCFG_TRAP_EXCEPTIONS
      for (t = 0; t < 0x100; t +=4) {
         *(uint_32*)t = 0x7e9de808; // twle %r29,%r29
      } /* Endfor */
   #endif

   _GET_KERNEL_DATA(kernel_data);

   /* Set the CPU type */
   _mqx_set_cpu_type(PSP_CPU_MPC5125);

   /* Set the bsp exit handler, called by _mqx_exit */
   _mqx_set_exit_handler(_bsp_exit_handler);

   /* Initialize the MPC5125 support functions */
   _mpc5125_initialize_support(BSP_IMMR_BASE); 

   /* Initialize interrupt Controller */
   _mpc5125_ipic_init(); 


   /* Debugging is not allowed from here */
   {
      // Disable MSR[IP] - Now interrupt table prefix = 0x0000_0000
      _PSP_SYNC();
      _PSP_MSR_GET(t);
      t &= ~(PSP_MSR_CE | PSP_MSR_EE | PSP_MSR_IP); // Disable MSR[CE,EE,IP]
      t |=  (PSP_MSR_FP | PSP_MSR_ME | PSP_MSR_RI); // Enable  MSR[FP,ME,RI]
      _PSP_MSR_SET(t);
      _PSP_SPR_GET(t, 1010);       // Exception prefix changes so we need
      t &= ~0xFFF00000;            // to change the hardware instruction
      _PSP_SPR_SET(1010, t);       // address breakpoint for the debugger
      _PSP_SYNC();
      _PSP_ISYNC();

      /* Initilize the interrupt handling */
      result =  _psp_int_init(BSP_FIRST_INTERRUPT_VECTOR_USED,
         BSP_LAST_INTERRUPT_VECTOR_USED);
      if (result != MQX_OK) {
         return result;
      } 
   }
   /* Debugging may now resume */


   #if BSPCFG_TRAP_EXCEPTIONS
      _int_install_unexpected_isr();
   #endif

   /* 
   ** Initialize the interrupt controller.
   ** Direct critical interrupt sources to the normal core interrupt pin.
   */

   if (_int_install_isr(PSP_EXCPT_PROGRAM,
      (void (_CODE_PTR_)(pointer))_bsp_null_isr, NULL) == NULL)
   {
      return _task_get_error();
   } 

   /* Install external exception handler */
   if (_int_install_isr(PSP_EXCPT_EXTERNAL,
      (void (_CODE_PTR_)(pointer))_mpc5125_external_isr, NULL) == NULL)
   {
      return _task_get_error();
   } 

   #ifdef BSPCFG_TIMER_GPT_CHANNEL
      // if BSPCFG_TIMER_GPT_CHANNEL is defined, we use the specified GPT, 
      
      /* Install an empty decrementer interrupt handler */
      if (_int_install_isr(PSP_EXCPT_DECREMENTER,
         (void (_CODE_PTR_)(pointer))_bsp_null_isr, NULL) == NULL)
      {
         return _task_get_error();
      } 

      if (_int_install_isr(BSP_TIMER_INTERRUPT_VECTOR,
         (void (_CODE_PTR_)(pointer))_mpc512x_gpt_isr, BSPCFG_TIMER_GPT_CHANNEL) == NULL)
      {
         return MQX_TIMER_ISR_INSTALL_FAIL;
      } 

      timer_preload = _mpc512x_gpt_init(
          BSPCFG_TIMER_GPT_CHANNEL, BSP_TIMER_INTERRUPT_VECTOR, BSP_ALARM_FREQUENCY, BSP_EXCLK_CLOCK);

      _time_set_hwtick_function(_mpc512x_gpt_get_hwticks, BSPCFG_TIMER_GPT_CHANNEL);
   #else
      // otherwise if BSPCFG_TIMER_GPT_CHANNEL is NOT defined, we use the decrementer
      /* Install the decrementer interrupt handler */
      if (_int_install_isr(PSP_EXCPT_DECREMENTER,
         (void (_CODE_PTR_)(pointer))_e300_decrementer_isr, NULL) == NULL)
      {
         return _task_get_error();
      }

      result = _e300_decrementer_timer_init(BSP_ALARM_FREQUENCY, BSP_EXCLK_CLOCK,&timer_preload);
      if (result != MQX_OK) {
         return(result);
      }
      
      _time_set_hwtick_function(_e300_decrementer_get_hwticks, (pointer)timer_preload);

   #endif
   kernel_data->TIMER_HW_REFERENCE = timer_preload;

   _time_set_hwticks_per_tick(kernel_data->TIMER_HW_REFERENCE);

   _time_set_ticks_per_sec(BSP_ALARM_FREQUENCY);

   if (_mqx_monitor_type == MQX_MONITOR_TYPE_NONE){


      #if BSPCFG_USE_PAGE_TABLES
            /*---------------------------------------------------------------------*/
            /* Use BAT registers and MMU Page tables */

            result = _mmu_vinit(0, &mmu_init);
            if (result != MQX_OK) return result;

            /* Map in DRAM  , page tables used */
            result = _mmu_add_vregion(BSP_CACHED_RAM_BASE, BSP_CACHED_RAM_SIZE, BSP_RAM_SIZE, 0);
            result = _mmu_add_vregion(BSP_UNCACHED_RAM_BASE, BSP_UNCACHED_RAM_SIZE, BSP_RAM_SIZE, 0);
            if (result != MQX_OK) return result;
      #else
            /*---------------------------------------------------------------------*/
            /* Just use the BAT registers */

            _mmu_init(0);

            /* IBAT+DBAT for SDRAM */
            result  = _mmu_add_region((pointer)BSP_CACHED_RAM_BASE, BSP_CACHED_RAM_SIZE, E300CORE_MMU_SET_IBAT);
            result |= _mmu_add_region((pointer)BSP_CACHED_RAM_BASE, BSP_CACHED_RAM_SIZE, E300CORE_MMU_SET_DBAT | E300CORE_MMU_CACHE_WRITE_THRU );
            result |= _mmu_add_region((pointer)BSP_UNCACHED_RAM_BASE, BSP_UNCACHED_RAM_SIZE, E300CORE_MMU_SET_IBAT | E300CORE_MMU_CACHE_INHIBIT);
            result |= _mmu_add_region((pointer)BSP_UNCACHED_RAM_BASE, BSP_UNCACHED_RAM_SIZE, E300CORE_MMU_SET_DBAT | E300CORE_MMU_CACHE_INHIBIT );
            if (result != MQX_OK) return result;
      #endif
     
      /* DBAT for internally mapped peripheral registers */
      result = _mmu_add_region(BSP_IMMR_BASE,BSP_IMMR_SIZE,
         E300CORE_MMU_SET_DBAT | E300CORE_MMU_CACHE_INHIBIT | E300CORE_MMU_CACHE_WRITE_THRU | E300CORE_MMU_CACHE_GUARDED | E300CORE_MMU_CACHE_COHERENT);

      if (result != MQX_OK) 
         return result;

      result = _mmu_add_region((unsigned char *)0x10000000,0x8000,
         E300CORE_MMU_SET_DBAT | E300CORE_MMU_CACHE_INHIBIT | E300CORE_MMU_CACHE_WRITE_THRU | E300CORE_MMU_CACHE_GUARDED | E300CORE_MMU_CACHE_COHERENT);

      if (result != MQX_OK) 
         return result;
      
      result = _mmu_add_region((unsigned char *)0x40000000,0x8000,
         E300CORE_MMU_SET_DBAT | E300CORE_MMU_CACHE_INHIBIT | E300CORE_MMU_CACHE_WRITE_THRU | E300CORE_MMU_CACHE_GUARDED | E300CORE_MMU_CACHE_COHERENT);
      
      
      if (result != MQX_OK) 
         return result;


      #if BSPCFG_USE_PAGE_TABLES
         _mmu_venable();
      #else
         _mmu_enable();
      #endif

      #if !BSPCFG_ICACHE_INHIBIT
         _icache_enable(0);
      #endif
      #if !BSPCFG_DCACHE_INHIBIT
         _dcache_enable(0);
      #endif
   } 



   #if BSPCFG_ENABLE_CPP
      /* initialize C++ constructors       */
      __init_cpp();
   #endif

   /* Initialize RTC and MQX time */
   #if BSPCFG_ENABLE_RTCDEV
      _rtc_sync_with_mqx(TRUE);
   #endif

   #if BSPCFG_ENABLE_IO_SUBSYSTEM
      /* Initialize the I/O Sub-system */
      result = _io_init();
      if (result != MQX_OK) {
         return result;
      } 

      /* Install device drivers */
      #if BSPCFG_ENABLE_TTYA
         _mpc5125_serial_polled_install("ttya:", &_bsp_psc0_init);
      #endif
      #if BSPCFG_ENABLE_ITTYA
         _mpc5125_serial_int_install("ittya:", &_bsp_psc0_init);
      #endif

      #if BSPCFG_ENABLE_TTYB
         _mpc5125_serial_polled_install("ttyb:", &_bsp_psc1_init);
      #endif
      #if BSPCFG_ENABLE_ITTYB
         _mpc5125_serial_int_install("ittyb:", &_bsp_psc1_init);
      #endif
      
      #if BSPCFG_ENABLE_TTYC
         _mpc5125_serial_polled_install("ttyc:", &_bsp_psc2_init);
      #endif
      #if BSPCFG_ENABLE_ITTYC
         _mpc5125_serial_int_install("ittyc:", &_bsp_psc2_init);
      #endif
      
      #if BSPCFG_ENABLE_TTYD
         _mpc5125_serial_polled_install("ttyd:", &_bsp_psc3_init);
      #endif
      #if BSPCFG_ENABLE_ITTYD
         _mpc5125_serial_int_install("ittyd:", &_bsp_psc3_init);
      #endif
      
      #if BSPCFG_ENABLE_TTYE
         _mpc5125_serial_polled_install("ttye:", &_bsp_psc4_init);
      #endif
      #if BSPCFG_ENABLE_ITTYE
         _mpc5125_serial_int_install("ittye:", &_bsp_psc4_init);
      #endif
      
      #if BSPCFG_ENABLE_TTYF
         _mpc5125_serial_polled_install("ttyf:", &_bsp_psc5_init);
      #endif
      #if BSPCFG_ENABLE_ITTYF
         _mpc5125_serial_int_install("ittyf:", &_bsp_psc5_init);
      #endif
      
      #if BSPCFG_ENABLE_TTYG
         _mpc5125_serial_polled_install("ttyg:", &_bsp_psc6_init);
      #endif
      #if BSPCFG_ENABLE_ITTYG
         _mpc5125_serial_int_install("ittyg:", &_bsp_psc6_init);
      #endif
      
      #if BSPCFG_ENABLE_TTYH
         _mpc5125_serial_polled_install("ttyh:", &_bsp_psc7_init);
      #endif
      #if BSPCFG_ENABLE_ITTYH
         _mpc5125_serial_int_install("ittyh:", &_bsp_psc7_init);
      #endif
      
      #if BSPCFG_ENABLE_TTYI
         _mpc5125_serial_polled_install("ttyi:", &_bsp_psc8_init);
      #endif
      #if BSPCFG_ENABLE_ITTYI
         _mpc5125_serial_int_install("ittyi:", &_bsp_psc8_init);
      #endif
      
      #if BSPCFG_ENABLE_TTYJ
         _mpc5125_serial_polled_install("ttyj:", &_bsp_psc9_init);
      #endif
      #if BSPCFG_ENABLE_ITTYJ
         _mpc5125_serial_int_install("ittyj:", &_bsp_psc9_init);
      #endif
      
      #if BSPCFG_ENABLE_I2C0
        _mpc512x_i2c_polled_install("i2c0:", (MPC512X_I2C_INIT_STRUCT_CPTR)&_bsp_i2c0_init);
      #endif
       
      #if BSPCFG_ENABLE_II2C0
        _mpc512x_i2c_int_install("ii2c0:", (MPC512X_I2C_INIT_STRUCT_CPTR)&_bsp_i2c0_init);
      #endif
          /* Install the PCCard Flash drivers */
      #if BSPCFG_ENABLE_PCFLASH   
        _io_pccardlpc_install("pccarda:", (MPC5125_PCCARDLPC_INIT_STRUCT _PTR_) &_bsp_cfcard_init);
        _io_apcflash_install("pcflasha:");
      #endif
      /* Install the SDHC driver */
      #if BSPCFG_ENABLE_SDHC
         _sdhc_install ("sdhc:", &_bsp_sdhc_init);
      #endif
       /* install external flash */
      #if BSPCFG_ENABLE_NANDFLASH
        _io_nandflash_install(&_bsp_nandflash_init);
      #endif
      /* Install SPI driver */
      #if BSPCFG_ENABLE_SPI0
         _mpc512x_spi_polled_install("spi0:", &_bsp_spi0_init);
      #endif
      #if BSPCFG_ENABLE_ISPI0
         _mpc512x_spi_int_install("ispi0:", &_bsp_spi0_init);
      #endif
      
      #if BSPCFG_ENABLE_SPI1
         _mpc512x_spi_polled_install("spi1:", &_bsp_spi1_init);
      #endif
      #if BSPCFG_ENABLE_ISPI1
         _mpc512x_spi_int_install("ispi1:", &_bsp_spi1_init);
      #endif
      
      #if BSPCFG_ENABLE_SPI2
         _mpc512x_spi_polled_install("spi2:", &_bsp_spi2_init);
      #endif
      #if BSPCFG_ENABLE_ISPI2
         _mpc512x_spi_int_install("ispi2:", &_bsp_spi2_init);
      #endif
      
      #if BSPCFG_ENABLE_SPI3
         _mpc512x_spi_polled_install("spi3:", &_bsp_spi3_init);
      #endif
      #if BSPCFG_ENABLE_ISPI3
         _mpc512x_spi_int_install("ispi3:", &_bsp_spi3_init);
      #endif
      
      #if BSPCFG_ENABLE_SPI4
         _mpc512x_spi_polled_install("spi4:", &_bsp_spi4_init);
      #endif
      #if BSPCFG_ENABLE_ISPI4
         _mpc512x_spi_int_install("ispi4:", &_bsp_spi4_init);
      #endif
      
      #if BSPCFG_ENABLE_SPI5
         _mpc512x_spi_polled_install("spi5:", &_bsp_spi5_init);
      #endif
      #if BSPCFG_ENABLE_ISPI5
         _mpc512x_spi_int_install("ispi5:", &_bsp_spi5_init);
      #endif
      
      #if BSPCFG_ENABLE_SPI6
         _mpc512x_spi_polled_install("spi6:", &_bsp_spi6_init);
      #endif
      #if BSPCFG_ENABLE_ISPI6
         _mpc512x_spi_int_install("ispi6:", &_bsp_spi6_init);
      #endif
      
      #if BSPCFG_ENABLE_SPI7
         _mpc512x_spi_polled_install("spi7:", &_bsp_spi7_init);
      #endif
      #if BSPCFG_ENABLE_ISPI7
         _mpc512x_spi_int_install("ispi7:", &_bsp_spi7_init);
      #endif
      
      #if BSPCFG_ENABLE_SPI8
         _mpc512x_spi_polled_install("spi8:", &_bsp_spi8_init);
      #endif
      #if BSPCFG_ENABLE_ISPI8
         _mpc512x_spi_int_install("ispi8:", &_bsp_spi8_init);
      #endif
      
      #if BSPCFG_ENABLE_SPI9
         _mpc512x_spi_polled_install("spi9:", &_bsp_spi9_init);
      #endif
      #if BSPCFG_ENABLE_ISPI9
         _mpc512x_spi_int_install("ispi9:", &_bsp_spi9_init);
      #endif
     
      #if BSP_DEFAULT_IO_CHANNEL_DEFINED
         /* Initialize the default serial I/O */
         _io_serial_default_init();
      #endif     
   #endif

   return MQX_OK;
}


/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _bsp_get_mac_address
* Returned Value   : uint_32
* Comments         :
*    This function returns the mac address associated with the specified device
*
* If the MAC address is stored in NV-storage, this fuction should read the
* MAC address from NV-storage and set it.
*
* If the MAC address is generated from a device serial number and an OUI, the
* serial number should be passed in, and the MAC address should be constructed
*
*END*----------------------------------------------------------------------*/

const _enet_address _enet_oui = BSP_DEFAULT_ENET_OUI;

boolean _bsp_get_mac_address
   (
      uint_32        device,
      uint_32        value,
      _enet_address  address
   )
{ 
   char_ptr value_ptr = (char_ptr) &value;

   if (device >= BSP_ENET_DEVICE_COUNT) 
      return FALSE;

   address[0] = _enet_oui[0];
   address[1] = _enet_oui[1];
   address[2] = _enet_oui[2];
   address[3] = (value & 0xFF0000) >> 16;
   address[4] = (value & 0xFF00) >> 8;
   address[5] = (value & 0xFF);

   return TRUE;
} 


/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _bsp_exit_handler
* Returned Value   : none
* Comments         :
*    This function is called when MQX exits
*
*END*----------------------------------------------------------------------*/

void _bsp_exit_handler
   (
      void
   )
{ 
   _dcache_flush();
   _dcache_disable();
   _icache_disable();
   _mmu_disable();
}



/* EOF */
