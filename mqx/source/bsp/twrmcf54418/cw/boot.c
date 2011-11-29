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
* $FileName: boot.c$
* $Version : 3.6.7.0$
* $Date    : Sep-17-2010$
*
* Comments:
*
*    This file contains the boot and exception code.
*
*END************************************************************************/

#include "mqx_inc.h"

#pragma define_section bootstrap_nfcsram_code ".bootstrap_nfcsram_code" far_absolute R
#pragma define_section bootstrap_sram_code ".bootstrap_sram_code" far_absolute R
#pragma define_section warm_start ".warm_start" far_absolute R

extern unsigned long far __BOOT_STACK_ADDRESS[];
extern unsigned long __INTERNAL_SRAM_BASE;

void warm_start (void);
asm void __boot(void);
asm void __boot_exception(void);

__declspec(bootstrap_nfcsram_code) 
asm void __boot_nfc(void);

__declspec(bootstrap_sram_code) 
asm void __boot_sram_exception(void);

__declspec(bootstrap_nfcsram_code) 
asm void __boot_nfcsram_exception(void);

void _start(void);
void mcf5441_init(void);
void _mcf5441_int_mask_all(void);
extern void bootstrap_nfcsram_copy_code_to_sram (void);
extern void bootstrap_sram_main(void);
extern void* bootstrap_nfcsram_vector[64];
extern void* bootstrap_sram_vector[64];

typedef void (*vector_entry)(void);

extern vector_entry __VECTOR_TABLE_ROM_START[]; /* defined in linker command file */
extern vector_entry __VECTOR_TABLE_RAM_START[]; /* defined in linker command file */

#if   __REGABI__
    __declspec(register_abi)
#elif __STDABI__
      __declspec(standard_abi)
#endif

__declspec(warm_start) 
void warm_start (void)
{
        __boot();
}

#if   __REGABI__
    __declspec(register_abi)
#elif __STDABI__
      __declspec(standard_abi)
#endif

asm void __boot(void) {
        /* Assume we could start here via the debugger or jump here at any time */
        move.w #0x2700, sr                  /* Disable all interrupts */
        move.l #__BOOT_STACK_ADDRESS, sp    /* Establish a stack pointer */

        /* Invalidate the cache and disable it */
        move.l #0x01000000, d0
        movec d0, CACR

        /* Disable ACRs */
        moveq.l #0, d0
        movec d0, ACR0
        movec d0, ACR1
        movec d0, ACR2
        movec d0, ACR3

        /* Initialize RAMBAR - locate it on the data bus */
        move.l #__INTERNAL_SRAM_BASE, d0
        andi.l #0xFFF80000, d0
        add.l #0x221, d0
        movec d0, RAMBAR

        move.l #__VECTOR_TABLE_ROM_START, d0
        movec d0, VBR

        /* Mask all interrupts */
        jsr _mcf5441_int_mask_all
        
        /* Initialize mcf5441 peripherals */
        jsr mcf5441_init

        /* Jump to the main process */
        jmp _start
}

#if   __REGABI__
    __declspec(register_abi)
#elif __STDABI__
      __declspec(standard_abi)
#endif

__declspec(bootstrap_nfcsram_code) 
asm void __boot_nfc(void) {
        /* Assume we could start here via the debugger or jump here at any time */
        move.w #0x2700, sr                  /* Disable all interrupts*/

        /* Initialize RAMBAR - locate it on the data bus*/
        move.l #__INTERNAL_SRAM_BASE, d0
        andi.l #0xFFF80000, d0
        add.l #0x221, d0
        movec d0, RAMBAR

        /* Establish a stack pointer */
        move.l #__BOOT_STACK_ADDRESS, sp    

        /* Invalidate the cache and disable it */
        move.l #0x01000000, d0
        movec d0, CACR

        /* Disable ACRs */
        moveq.l #0, d0
        movec d0, ACR0
        movec d0, ACR1
        movec d0, ACR2
        movec d0, ACR3


        /* Set VBR to NFC_SRAM vector table address */
        move.l #bootstrap_nfcsram_vector, d0 
        movec d0, VBR

        /* Copy the rest of the bootstrap code to the SRAM memory */
        jsr bootstrap_nfcsram_copy_code_to_sram
        
        /* Change VBR to SRAM vector table address */
        move.l #bootstrap_sram_vector, d0 
        movec d0, VBR

        /* Jump to the SRAM portion of the bootstrap code */
        jmp bootstrap_sram_main
}

#if   __REGABI__
    __declspec(register_abi)
#elif __STDABI__
      __declspec(standard_abi)
#endif

asm void __boot_exception(void)
{
   halt
   rte
}

#if   __REGABI__
    __declspec(register_abi)
#elif __STDABI__
      __declspec(standard_abi)
#endif

__declspec(bootstrap_sram_code) 
asm void __boot_sram_exception(void)
{
   halt
   rte
}

#if   __REGABI__
    __declspec(register_abi)
#elif __STDABI__
      __declspec(standard_abi)
#endif

__declspec(bootstrap_nfcsram_code) 
asm void __boot_nfcsram_exception(void)
{
   halt
   rte
}
