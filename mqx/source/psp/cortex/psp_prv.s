;*HEADER********************************************************************
;* 
;* Copyright (c) 2010 Freescale Semiconductor;
;* All Rights Reserved                       
;*
;*************************************************************************** 
;*
;* THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR 
;* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
;* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  
;* IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
;* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
;* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
;* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
;* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
;* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
;* IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
;* THE POSSIBILITY OF SUCH DAMAGE.
;*
;**************************************************************************
;*
;* $FileName: psp_prv.s$
;* $Version : 3.7.6.1$
;* $Date    : Mar-28-2011$
;*
;* Comments:
;*   This assembler header file contains private declarations for 
;*   use with the mqx assembler files
;*
;*END***********************************************************************

#include <asm_mac.h>
;------------------------------------------------------------------------
;                         EXTERNAL REFERENCES
;

#if MQX_KERNEL_LOGGING
        ASM_EXTERN   ASM_PREFIX(_klog_block_internal)
        ASM_EXTERN   ASM_PREFIX(_klog_execute_scheduler_internal)
        ASM_EXTERN   ASM_PREFIX(_klog_yield_internal)
        ASM_EXTERN   ASM_PREFIX(_klog_context_switch_internal)
        ASM_EXTERN   ASM_PREFIX(_klog_isr_start_internal)
        ASM_EXTERN   ASM_PREFIX(_klog_isr_end_internal)
#endif
        ASM_EXTERN   ASM_PREFIX(_mqx_kernel_data)
        ASM_EXTERN   ASM_PREFIX(_mqx_system_stack)       

        ASM_EXTERN   ASM_PREFIX(_psp_irq_sp)
        ASM_EXTERN   ASM_PREFIX(_psp_fiq_sp)
        ASM_EXTERN   ASM_PREFIX(_psp_undef_sp)
        ASM_EXTERN   ASM_PREFIX(_psp_abort_sp)

;------------------------------------------------------------------------
;                       CONSTANT DECLARATIONS
;
; The following are the bits in the CONFIG field of the kernel data structure
; to set for the psp options.
; NOTE: These must agree with values in mqx_prv.h

PSP_CNFG_MQX_KERNEL_LOGGING          =       0x8000
PSP_CNFG_FP_REGISTERS_EXIST          =       0x4000

#ifndef MQX_FP_REGISTERS_EXIST
#define MQX_FP_REGISTERS_EXIST 0
#endif

#if MQX_KERNEL_LOGGING == 1
#if MQX_FP_REGISTERS_EXIST == 1
PSP_CNFG =  (PSP_CNFG_MQX_KERNEL_LOGGING | PSP_CNFG_FP_REGISTERS_EXIST)
#else
PSP_CNFG =  PSP_CNFG_MQX_KERNEL_LOGGING
#endif
#else
#if MQX_FP_REGISTERS_EXIST == 1
PSP_CNFG =  PSP_CNFG_FP_REGISTERS_EXIST
#else
PSP_CNFG =  0
#endif
#endif



;  Task FLAGS bits
;  These must match definitions in mqx_prv.h

FP_TASK_MASK            =       0x0002
FP_CONTEXT_SAVED_MASK   =       0x0200
FP_CONTEXT_CLEAR_MASK   =       0xfdff
PREEMPTION_DISABLED     =       0x1000

;------------------------------------------------------------------------
;                          MACRO DECLARATIONS
;
#ifdef __IASMARM__

; This macro returns the address of the kernel data in the specified register
GET_KERNEL_DATA MACRO reg
                ldr reg, =_mqx_kernel_data
                ldr reg, [reg, #0]
        ENDM
 
SET_FUNCTION_ALIGNMENT MACRO
                ALIGNROM 2
        ENDM

; This macro calls the kernel logging function, if logging enabled
KLOG    MACRO KDATA, KLOG_FUNCTION
#if MQX_KERNEL_LOGGING
                push {r1}
                ldr r1, [KDATA, #KD_LOG_CONTROL]
                tst r1, #1
                ittt ne
                pushne {lr}
                blne KLOG_FUNCTION
                popne {lr}
                pop {r1}
#endif
        ENDM

#else /* __IASMARM__ */

; This macro returns the address of the kernel data in the specified register
GET_KERNEL_DATA: .macro reg
        ldr reg, =_mqx_kernel_data
        ldr reg, [reg, #0]
	.endm
 
SET_FUNCTION_ALIGNMENT: .macro
        .align 2
	.endm

; This macro calls the kernel logging function, if logging enabled
KLOG:   .macro KDATA,KLOG_FUNCTION
        .if MQX_KERNEL_LOGGING
                push {r1}
                ldr r1, [KDATA, #KD_LOG_CONTROL]
                tst r1, #1
                ittt ne
                pushne {lr}
                blne KLOG_FUNCTION
                popne {lr}
                pop {r1}        
        .endif
        .endm

#endif
