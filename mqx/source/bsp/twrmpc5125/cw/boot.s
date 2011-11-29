/*HEADER*******************************************************************
* Copyright (c) 2008-2009 Freescale Semiconductor;
* All Rights Reserved
*
* Copyright (c) 2004-2010 Embedded Access Inc.;
* All Rights Reserved
*
* Copyright (c) 1989-2008 ARC International;
* All Rights Reserved
*
//*************************************************************************** 
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
* $FileName: boot.s$
* $Version : 3.7.4.0$
* $Date    : Feb-7-2011$
*
* Comments:
*
*   This assembler file contains the system reset vector code.
*
*   WARNING:  This code should NOT reference SDRAM.  It must assume
*             program data has not yet been initialized.  It cannot
*             call or return from any function.
*
*END************************************************************************/
      .file    "boot.s"
      
#define __ASM__
   #include"mpc512x_mddrc.h"
   #include "bootstrap.h"
#undef __ASM__

.extern __LOADER_DDR_START
.extern __BOOT_ROM_START
.extern __NAND_BOOT_BASE_ADDR
.extern __NAND_BOOT_DST
.extern __SRAM_BASE
.extern __SRAM_SIZE
.extern __IMMR_BASE
.extern __BOOT_ROM_START

.extern _mmu_disable
.extern __start
.extern _e_code
.extern _f_code
.extern bootstrap_nfcsram_copy_code_to_ddr
.extern bootstrap_sram_boot
.extern bootstrap_ddr_to_nand
.extern bootloader_boot
.extern __init_user
.extern __init_registers
.extern __init_data
.extern main
.extern exit

vector: .macro  sname, name
        .section sname,4,1,6
        .align  2
        .globl  name
        // There was an exception while booting MQX.  This should not
        // happen.  If it does, branch to self for debugging.
name:   b       name
        .type   name,@function
        .size   name, . - name
.endm

SET_REG32: .macro r, v, offset, mr
   lis     r, v@h
   ori     r, r, v@l
   stw     r, offset(mr)
.endm


/*
##FUNCTION*-------------------------------------------------------------------
##
## Function Name    : __flush_cache
## Comments         :
##
## 
##
##END*------------------------------------------------------------------------
*/

      .text

      .align   2
      .globl __flush_cache
__flush_cache:
      .extern  _dcache_flush_mlines
      b        _dcache_flush_mlines
      .type __flush_cache,@function
      .size __flush_cache, . - __flush_cache
/*
##FUNCTION*-------------------------------------------------------------------
##
## Function Name    : __init_hardware
## Comments         :
##
## Called from startup code to initialize the core.  Assumes
## either system reset exception or JTAG emulator have
## initialized chip selects and sdram.  Also assumes MBAR
## has been set to 0xF0000000.
##
##END*------------------------------------------------------------------------
*/
      .text
      .align  2
      .globl  __init_hardware
__init_hardware:
      mflr       r17            // ** WARNING: ** Save linkreg for return
                                // assumes r17 can be trashed @ startup

      mfmsr      r3
      ori        r3,r3,0x3000   // Enable MSR[FP, ME]
      mtmsr      r3

      lis        r3, 0x0004
      mtspr      1011, r3       // Enable HID2[HBE] for all 8 I/D BAT regs

      // Initialize MMU
      bl         _mmu_disable   // Zero I/DBAT registers

      //
      // insert other init code here
      //
      mtlr       r17
      blr
      .type __init_hardware,@function
      .size __init_hardware, . - __init_hardware
/*
##--------------------------------------------------------------------------
## Function    : __cold_start
## Description : 
##               
## Parameter(s):
## Returns     :
## 
##--------------------------------------------------------------------------
*/
      .section .cold_start,4,1,6
      .align  2
      .globl __cold_start
__cold_start:
      
      mfmsr  r5
      lis    r4,0xFF400000@h
     
      /* Set IMMR area to our preferred location */
      mfspr r6, MBAR
      lis   r3, (__IMMR_BASE)@h
      ori   r3, r3, (__IMMR_BASE)@l

      cmpw  r3, r6
      beq   skipimmrbarset /* it has already been set to what we want it to be */
      /* -- nice to chk if coming out of the BDI          */


      stw   r3, 0x0000(r4)
      mtspr MBAR, r3 /* IMMRBAR is mirrored into the MBAR SPR (311) */
      isync 
skipimmrbarset: 

      lis   r4, (__NAND_BOOT_BASE_ADDR)@h
      ori   r4, r4, STOP_REG(0xFFF00000, 0x100000)
      stw   r4, LPBAW(r3)
      stw   r4, LPCS0AW(r3)  

      isync
      bl    cpu_early_init
      isync

      /*
      * The SRAM window has a fixed size (256K),
      * so only the start addressis necessary
      */
      lis     r3, CFG_IMMR@h
      ori     r3, r3, CFG_IMMR@l
      lis     r4, START_REG(CFG_SRAM_BASE) & 0xff00
      stw     r4, SRAMBAR(r3)

      /*
      * According to MPC5125 RM, configuring local access windows should
      * be followed by a dummy read of the config register that was
      * modified last and an isync
      */
      lwz	r4, SRAMBAR(r3)
      isync

      /* r3: BOOTFLAG */
      mr r3, r21
      bl	dram_init


      /* r3: BOOTFLAG */
      mr	r3, r21
      lis	r1, (CFG_INIT_RAM_ADDR + CFG_GBL_DATA_OFFSET)@h
      ori	r1, r1, (CFG_INIT_RAM_ADDR + CFG_GBL_DATA_OFFSET)@l
      
      /*copy sram to ddr*/
      bl	bootstrap_nfcsram_copy_code_to_ddr
      /* copy the full NAND innto DDR  */
      /* and jump to it */
boot:
      lis      r10,(bootstrap_sram_boot)@h
      ori      r10,r10,(bootstrap_sram_boot)@l
      addis    r10,r10,(__LOADER_DDR_START)@h
      addi     r10,r10,(__LOADER_DDR_START)@l      
      lis      r3,(__BOOT_ROM_START)@h
      ori      r3,r3,(__BOOT_ROM_START)@l
      sub      r10,r10,r3
      
      mtlr	r10
      isync
      blr

      /* NOTREACHED - nand_boot() does not return */
      /*
      * This code initialises the machine,
      * it expects original MSR contents to be in r5
      */
      
cpu_early_init:
      /* Initialize machine status; enable machine check interrupt */
      /*-----------------------------------------------------------*/
      
      li	r3, MSR_KERNEL		/* Set ME and RI flags */ //0x18a
      rlwimi	r3, r5, 0, 25, 25	/* preserve IP bit */
      
      rlwimi	r3, r5, 0, 21, 22	/* debugger might set SE, BE bits */
      
      mtmsr	r3
      SYNC
      isync
      mtspr	SRR1, r3		/* Mirror current MSR state in SRR1 */
      
      lis	r3, CFG_IMMR@h
      
      /* Disable the watchdog */
      /*----------------------*/
      lwz r4, SWCRR(r3)
      /*
      * Check to see if it's enabled for disabling: once disabled by s/w
      * it's not possible to re-enable it
      */
      andi. r4, r4, 0x4
      
      beq skipdisable
      
      xor r4, r4, r4
      stw r4, SWCRR(r3)

skipdisable:

      /* Initialize the Hardware Implementation-dependent Registers */
      /* HID0 also contains cache control			*/
      /*------------------------------------------------------*/
      lis	r3, CFG_HID0_INIT@h
      ori	r3, r3, CFG_HID0_INIT@l
      SYNC
      isync
      mtspr	HID0, r3
      blr
      
dram_init:

      lis       r3,(CFG_IMMR + IOCTL_BASE_ADDR+1)@h;
      ori       r3,r3,(CFG_IMMR + IOCTL_BASE_ADDR)@l;
      
      SET_REG32 r4, (IOCTRL_MUX_DDR<<24), IOCTL_MEM , r3
      
      lis       r3,(CFG_IMMR)@h;
      ori       r3,r3,(CFG_IMMR)@l;
      
      SET_REG32 r4, MPC5125_CFG_DDR_BASE & 0xFFFFF000, MPC5125_DDR_LAW_BAR, r3
      SET_REG32 r4, 0x0000001b, MPC5125_DDR_LAW_AR, r3
      lwz       r0, MPC5125_DDR_LAW_AR(r3)
      isync
      
      lis       r3,(CFG_IMMR + MPC5125_MDDRC_BASE_OFFSET)@h;
      ori       r3,r3,(CFG_IMMR + MPC5125_MDDRC_BASE_OFFSET)@l;
      SET_REG32 r4, MPC5125_CFG_MDDRC_SYS_CFG_EN, MPC5125_DDR_SYS_CONFIG, r3
      
      SET_REG32 r4, MPC5125_CFG_MDDRCGRP_PM_CFG1, MPC5125_DRAMPRIOM_PRIOMAN_CONFIG1, r3
      SET_REG32 r4, MPC5125_CFG_MDDRCGRP_PM_CFG2, MPC5125_DRAMPRIOM_PRIOMAN_CONFIG2, r3
      SET_REG32 r4, MPC5125_CFG_MDDRCGRP_HIPRIO_CFG, MPC5125_DRAMPRIOM_HIPRIO_CONFIG, r3
      SET_REG32 r4, MPC5125_CFG_MDDRCGRP_LUT0_MU, MPC5125_DRAMPRIOM_LUT_TABLE0_MAIN_UP, r3
      SET_REG32 r4, MPC5125_CFG_MDDRCGRP_LUT0_ML, MPC5125_DRAMPRIOM_LUT_TABLE0_MAIN_LOW, r3
      SET_REG32 r4, MPC5125_CFG_MDDRCGRP_LUT1_MU, MPC5125_DRAMPRIOM_LUT_TABLE1_MAIN_UP, r3
      SET_REG32 r4, MPC5125_CFG_MDDRCGRP_LUT1_ML, MPC5125_DRAMPRIOM_LUT_TABLE1_MAIN_LOW, r3
      SET_REG32 r4, MPC5125_CFG_MDDRCGRP_LUT2_MU, MPC5125_DRAMPRIOM_LUT_TABLE2_MAIN_UP, r3
      SET_REG32 r4, MPC5125_CFG_MDDRCGRP_LUT2_ML, MPC5125_DRAMPRIOM_LUT_TABLE2_MAIN_LOW, r3
      SET_REG32 r4, MPC5125_CFG_MDDRCGRP_LUT3_MU, MPC5125_DRAMPRIOM_LUT_TABLE3_MAIN_UP, r3
      SET_REG32 r4, MPC5125_CFG_MDDRCGRP_LUT3_ML, MPC5125_DRAMPRIOM_LUT_TABLE3_MAIN_LOW, r3
      SET_REG32 r4, MPC5125_CFG_MDDRCGRP_LUT4_MU, MPC5125_DRAMPRIOM_LUT_TABLE4_MAIN_UP, r3
      SET_REG32 r4, MPC5125_CFG_MDDRCGRP_LUT4_ML, MPC5125_DRAMPRIOM_LUT_TABLE4_MAIN_LOW, r3
      SET_REG32 r4, MPC5125_CFG_MDDRCGRP_LUT0_AU, MPC5125_DRAMPRIOM_LUT_TABLE0_ALT_UP, r3
      SET_REG32 r4, MPC5125_CFG_MDDRCGRP_LUT0_AL, MPC5125_DRAMPRIOM_LUT_TABLE0_ALT_LOW, r3
      SET_REG32 r4, MPC5125_CFG_MDDRCGRP_LUT1_AU, MPC5125_DRAMPRIOM_LUT_TABLE1_ALT_UP, r3
      SET_REG32 r4, MPC5125_CFG_MDDRCGRP_LUT1_AL, MPC5125_DRAMPRIOM_LUT_TABLE1_ALT_LOW, r3
      SET_REG32 r4, MPC5125_CFG_MDDRCGRP_LUT2_AU, MPC5125_DRAMPRIOM_LUT_TABLE2_ALT_UP, r3
      SET_REG32 r4, MPC5125_CFG_MDDRCGRP_LUT2_AL, MPC5125_DRAMPRIOM_LUT_TABLE2_ALT_LOW, r3
      SET_REG32 r4, MPC5125_CFG_MDDRCGRP_LUT3_AU, MPC5125_DRAMPRIOM_LUT_TABLE3_ALT_UP, r3
      SET_REG32 r4, MPC5125_CFG_MDDRCGRP_LUT3_AL, MPC5125_DRAMPRIOM_LUT_TABLE3_ALT_LOW, r3
      SET_REG32 r4, MPC5125_CFG_MDDRCGRP_LUT4_AU, MPC5125_DRAMPRIOM_LUT_TABLE4_ALT_UP, r3
      SET_REG32 r4, MPC5125_CFG_MDDRCGRP_LUT4_AL, MPC5125_DRAMPRIOM_LUT_TABLE4_ALT_LOW, r3
      
      /* Initialize MDDRC */
      SET_REG32 r4, MPC5125_CFG_MDDRC_SYS_CFG_EN, MPC5125_DDR_SYS_CONFIG, r3
      SET_REG32 r4, MPC5125_CFG_MDDRC_TIME_CFG0, MPC5125_DDR_TIME_CONFIG0, r3
      SET_REG32 r4, MPC5125_CFG_MDDRC_TIME_CFG1, MPC5125_DDR_TIME_CONFIG1, r3
      SET_REG32 r4, MPC5125_CFG_MDDRC_TIME_CFG2, MPC5125_DDR_TIME_CONFIG2, r3
      
      
      /* Initialize DDR */
      SET_REG32 r4, MPC5125_CFG_MICRON_NOP, MPC5125_DDR_COMMAND, r3
      stw       r4, MPC5125_DDR_COMMAND(r3);
      stw       r4, MPC5125_DDR_COMMAND(r3);
      stw       r4, MPC5125_DDR_COMMAND(r3);
      stw       r4, MPC5125_DDR_COMMAND(r3);
      stw       r4, MPC5125_DDR_COMMAND(r3);
      stw       r4, MPC5125_DDR_COMMAND(r3);
      stw       r4, MPC5125_DDR_COMMAND(r3);
      stw       r4, MPC5125_DDR_COMMAND(r3);
      stw       r4, MPC5125_DDR_COMMAND(r3);
      stw       r4, MPC5125_DDR_COMMAND(r3);
      
      SET_REG32 r4, MPC5125_CFG_MICRON_PCHG_ALL, MPC5125_DDR_COMMAND, r3
      SET_REG32 r5, MPC5125_CFG_MICRON_NOP, MPC5125_DDR_COMMAND, r3
      SET_REG32 r4, MPC5125_CFG_MICRON_RFSH, MPC5125_DDR_COMMAND, r3
      stw       r5, MPC5125_DDR_COMMAND(r3);
      SET_REG32 r4, MPC5125_CFG_MICRON_RFSH, MPC5125_DDR_COMMAND, r3
      stw       r5, MPC5125_DDR_COMMAND(r3);
      SET_REG32 r4, MPC5125_CFG_MICRON_INIT_DEV_OP, MPC5125_DDR_COMMAND, r3
      stw       r5, MPC5125_DDR_COMMAND(r3);
      SET_REG32 r4, MPC5125_CFG_MICRON_EM2, MPC5125_DDR_COMMAND, r3
      stw       r5, MPC5125_DDR_COMMAND(r3);
      SET_REG32 r4, MPC5125_CFG_MICRON_PCHG_ALL, MPC5125_DDR_COMMAND, r3
      SET_REG32 r4, MPC5125_CFG_MICRON_EM2, MPC5125_DDR_COMMAND, r3
      SET_REG32 r4, MPC5125_CFG_MICRON_EM3, MPC5125_DDR_COMMAND, r3
      SET_REG32 r4, MPC5125_CFG_MICRON_EN_DLL, MPC5125_DDR_COMMAND, r3
      SET_REG32 r4, MPC5125_CFG_MICRON_INIT_DEV_OP, MPC5125_DDR_COMMAND, r3
      SET_REG32 r4, MPC5125_CFG_MICRON_PCHG_ALL, MPC5125_DDR_COMMAND, r3
      SET_REG32 r4, MPC5125_CFG_MICRON_RFSH, MPC5125_DDR_COMMAND, r3
      SET_REG32 r4, MPC5125_CFG_MICRON_INIT_DEV_OP, MPC5125_DDR_COMMAND, r3
      SET_REG32 r4, MPC5125_CFG_MICRON_OCD_DEFAULT, MPC5125_DDR_COMMAND, r3
      SET_REG32 r4, MPC5125_CFG_MICRON_PCHG_ALL, MPC5125_DDR_COMMAND, r3
      stw       r5, MPC5125_DDR_COMMAND(r3);
      
      /* Start MDDRC */
      SET_REG32 r4, MPC5125_CFG_MDDRC_TIME_CFG0_RUN, MPC5125_DDR_TIME_CONFIG0, r3
      SET_REG32 r4, MPC5125_CFG_MDDRC_SYS_CFG_RUN, MPC5125_DDR_SYS_CONFIG, r3

      isync
      blr
       
     .type __cold_start,@function
     .size __cold_start, . - __cold_start
/*
##--------------------------------------------------------------------------
## Function    : __nand_download
## Description : Copy Boot loader and Operating system to the NAND flash 
##               memory
## Parameter(s):
## Returns     :
## 
##--------------------------------------------------------------------------
*/
      .section .nand_download,4,1,6
      .align  2
      .globl __nand_download,
__nand_download:
   	
   	/*
   	 *	PowerPC EABI init registers (stack, small data areas)
   	 */
   	bl		__init_registers
   		
   	/*
   	 *	board-level initialization
   	 */
   	bl		__init_hardware

   	/*
   	 *	Prepare a terminating stack record.
   	 */
     	stwu	r1, -8(r1)				/* Decrement stack by 8 bytes, (write word)*/
    	li		r0, 0x0000				/* load up r0 with 0x00000000 */
   	stw	r0, 0(r1)				/* SysVr4 EABI Supp indicated that initial back chain word should be null */
   	li		r0, 0xFFFF				/* load up r0 with 0xFFFFFFFF */
   	stw	r0, 4(r1)				/* Make an illegal return address of 0xFFFFFFFF */

   	 
   	/*
   	 *	Data initialization: copy ROM data to RAM as necessary
   	 */
   	bl		__init_data
   	
   	bl  bootstrap_ddr_to_nand
	   
	   lis      r6,exit@ha	
	   addi     r6,r6,exit@l
	   mtlr     r6
	   blr
       
      .type __nand_download,@function
      .size __nand_download, . - __nand_download
/*
##--------------------------------------------------------------------------
## warm entry point
## 
##--------------------------------------------------------------------------
*/
      .section .warm_start,4,1,6
      .globl _psp_set_disable_sr

      bl       _psp_set_disable_sr
      b        __start

/*
##--------------------------------------------------------------------------
## boot loader entry point
## 
##--------------------------------------------------------------------------
*/

      .section .boot_loader,4,1,6
      .globl _psp_set_disable_sr,__boot
__boot:
      bl       _psp_set_disable_sr
   
   	bl		__init_registers
   		
   	/*
   	 *	board-level initialization
   	 */
   	bl		__init_hardware

     	stwu	r1, -8(r1)				/* Decrement stack by 8 bytes, (write word)*/
    	li		r0, 0x0000				/* load up r0 with 0x00000000 */
   	stw	r0, 0(r1)				/* SysVr4 EABI Supp indicated that initial back chain word should be null */
   	li		r0, 0xFFFF				/* load up r0 with 0xFFFFFFFF */
   	stw	r0, 4(r1)				/* Make an illegal return address of 0xFFFFFFFF */

   	/*
   	 *	Data initialization: copy ROM data to RAM as necessary
   	 */
   	bl		__init_data
   	
      lis      r6,main@ha
	   addi     r6,r6,main@l
	   mtlr     r6
	   mr		 r3, r14
	   mr		 r4, r15
	   mr		 r5, r16
	   blrl
	
	   bl bootloader_boot

/*
##--------------------------------------------------------------------------
## Function    : __system_reset
## Description : System reset exception vector for MPC5125
## Parameter(s): none
## Returns     : Does not return.  Jumps to __romboot.
##--------------------------------------------------------------------------
*/
      .section .vector0100,4,1,6
      .align  2
      .globl __system_reset
__system_reset:
      li      r0,0            // Set r0 to 0.

      mtspr   ibat0u,r0       // Invalidate BATs to avoid error
      mtspr   ibat1u,r0       // states because the state of
      mtspr   ibat2u,r0       // the BATs is unknown after reset.
      mtspr   ibat3u,r0
      mtspr   ibat4u,r0
      mtspr   ibat5u,r0
      mtspr   ibat6u,r0
      mtspr   ibat7u,r0
      isync
      mtspr   dbat0u,r0
      mtspr   dbat1u,r0
      mtspr   dbat2u,r0
      mtspr   dbat3u,r0
      mtspr   dbat4u,r0
      mtspr   dbat5u,r0
      mtspr   dbat6u,r0
      mtspr   dbat7u,r0
      isync

      mfspr   r3,311          // R3 <- MBAR
      lis     r5,0xf000       // r5 <- F0000000
      cmp     cr0,r3,r5       // MBAR already set?
      beq     skipmbarset

      // If MBAR has already been moved then we can't
      // store to address 0x8000_0000

      srwi    r3,r5,16        // R3 = 0x0000F000
      lis     r4, 0x8000
      stw     r3,0(r4)        // MBAR  <- 0xf0000000
      mtspr   311,r5          // MBAR  <- 0xf0000000

skipmbarset:
      
      .type __system_reset,@function
      .size __system_reset, . - __system_reset

/* _bsp_enable_card will install new handlers in sdram */
vector .vector0200, __vector0200
vector .vector0500, __vector0500
vector .vector0600, __vector0600
vector .vector0700, __vector0700
vector .vector0800, __vector0800
vector .vector0900, __vector0900
vector .vector0A00, __vector0A00
vector .vector0C00, __vector0C00
vector .vector1300, __vector1300
vector .vector1400, __vector1400
vector .boot_header, __boot_header

# EOF
