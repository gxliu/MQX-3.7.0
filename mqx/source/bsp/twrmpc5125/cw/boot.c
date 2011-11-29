/**HEADER********************************************************************
* 
* Copyright (c) 2008 Freescale Semiconductor;
* All Rights Reserved
*
* Copyright (c) 2004-2010 Embedded Access Inc.;
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
* $FileName: boot.c$
* $Version : 3.5.1.0$
* $Date    : Feb-24-2010$
*
* Comments:
*
*    This file contains the boot and exception code.
*
*END************************************************************************/

#include "mqx_inc.h"

extern unsigned long __BOOT_STACK_ADDRESS[];
extern unsigned long __IPSBAR;
extern unsigned long __INTERNAL_FLASH_BASE;
extern unsigned long __INTERNAL_SRAM_BASE;

asm void __boot(void);
asm void __boot_exception(void);
void _start(void);
void mcf5225_init(void);

typedef void (*vector_entry)(void);

extern vector_entry __VECTOR_TABLE_ROM_START[]; // defined in linker command file
extern vector_entry __VECTOR_TABLE_RAM_START[]; // defined in linker command file

asm void __boot(void) {

.extern _mmu_disable
.extern __start
.extern _e_code
.extern _f_code

end_func:       .macro  name
        .type   name,@function
        .size   name, . - name
.endm
vector: .macro  sname, name
        .section sname,4,1,6
        .align  2
        .globl  name
        ## There was an exception while booting MQX.  This should not
        ## happen.  If it does, branch to self for debugging.
name:   b       name
        .type   name,@function
        .size   name, . - name
.endm

WM32:   .macro  address, value
        lis     r4, value@ha
        addi    r4, r4, value@l
        stw     r4, address(r3)
        eieio
.endm


##======================================================================
## Utility functions

   .text

   .align   2
   .globl __flush_cache
__flush_cache:
   .extern  _dcache_flush_mlines
   b        _dcache_flush_mlines
   .type __flush_cache,@function
   .size __flush_cache, . - __flush_cache

##--------------------------------------------------------------------------
## Function    : __init_hardware
## Description : Called from startup code to initialize the core.  Assumes
##               either system reset exception or JTAG emulator have
##               initialized chip selects and sdram.  Also assumes MBAR
##               has been set to 0xF0000000.
## Parameter(s): None
## Returns     : None
##--------------------------------------------------------------------------
        .text
        .align  2
        .globl  __init_hardware
__init_hardware:
        mflr       r17            ## ** WARNING: ** Save linkreg for return
                                  ## assumes r17 can be trashed @ startup

        mfmsr      r3
        ori        r3,r3,0x3000   ## Enable MSR[FP, ME]
        mtmsr      r3

        lis        r3, 0x0004
        mtspr      1011, r3       ## Enable HID2[HBE] for all 8 I/D BAT regs

        ## Initialize MMU
        bl         _mmu_disable   ## Zero I/DBAT registers

##
## insert other init code here
##
        mtlr       r17
        blr
        end_func __init_hardware

## .include "boot.inc"

##--------------------------------------------------------------------------
## System Reset Configuration Words
## 
## Placed in the Boot image to simplify flashing.
##--------------------------------------------------------------------------

        .section .system_config,4,1,6

# If you are booting at 0x100 plug the Reset
# Configuration Word in you flash image.
# If you boot at 0xfff00100, this code ends up at 0xfff00000 
# but should be at 0xff800000, so its unused and you will still
# need to modify the RCW seperately

# Default RCWLR for MPC8313RDB is 0x65040000
# Default RCWLH for MPC8313RDB is 0xA0606C00

# Default RCWLR for MPC8377RDB is 0x25040000
# Default RCWLH for MPC8377RDB is 0xA0606C02

# Placed in the required Flash layout

.if (MQX_CPU==PSP_CPU_MPC8313)
    .byte 0x65, 0x65, 0x65, 0x65, 0x65, 0x65, 0x65, 0x65
.endif

.if (MQX_CPU==PSP_CPU_MPC8377)
    .byte 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25
.endif

    .byte 4, 4, 4, 4, 4, 4, 4, 4
    .byte 0, 0, 0, 0, 0, 0, 0, 0
    .byte 0, 0, 0, 0, 0, 0, 0, 0

    .byte 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0  
    .byte 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60
    .byte 0x6C, 0x6C, 0x6C, 0x6C, 0x6C, 0x6C, 0x6C, 0x6C

.if (MQX_CPU==PSP_CPU_MPC8313)
    .byte 0, 0, 0, 0, 0, 0, 0, 0
.endif

.if (MQX_CPU==PSP_CPU_MPC8377)
    .byte 2, 2, 2, 2, 2, 2, 2, 2
.endif

# TODO: 
.if (MQX_CPU==PSP_CPU_MPC5125)
    .byte 0, 0, 0, 0, 0, 0, 0, 0
.endif
.if (MQX_CPU==PSP_CPU_MPC5121)
    .byte 0, 0, 0, 0, 0, 0, 0, 0
.endif

##--------------------------------------------------------------------------
## Function    : __system_reset
## Description : System reset exception vector for MPC5200
## Parameter(s): none
## Returns     : Does not return.  Jumps to __romboot.
##--------------------------------------------------------------------------
        .section .vector0100,4,1,6
        .align  2
        .globl __system_reset
__system_reset:
        li      r0,0            ## Set r0 to 0.

        mtspr   ibat0u,r0       ## Invalidate BATs to avoid error
        mtspr   ibat1u,r0       ## states because the state of
        mtspr   ibat2u,r0       ## the BATs is unknown after reset.
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

        mfspr   r3,311          ## R3 <- MBAR
        lis     r5,0xf000       ## r5 <- F0000000
        cmp     cr0,r3,r5       ## MBAR already set?
        beq     skipmbarset

        ## If MBAR has already been moved then we can't
        ## store to address 0x8000_0000

        srwi    r3,r5,16        ## R3 = 0x0000F000
        lis     r4, 0x8000
        stw     r3,0(r4)        ## MBAR  <- 0xf0000000
        mtspr   311,r5          ## MBAR  <- 0xf0000000

skipmbarset:
        ##b       __romboot       ## Jump to __romboot
        end_func __system_reset

## _bsp_enable_card will install new handlers in sdram
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

# EOF
