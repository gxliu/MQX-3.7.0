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
;* $FileName: dispatch.s$
;* $Version : 3.7.16.0$
;* $Date    : Mar-22-2011$
;*
;* Comments:
;*
;*   This assembler file contains functions for task scheduling
;*
;*END***********************************************************************

#include <asm_mac.h>
#include "mqx_cnfg.h"
#include "types.s"
#include "psp_prv.s"

#define __ASM__
#include <mqx_prv.h>
#undef __ASM__

 ASM_EQUATE SVC_RUN_SCHED, 1
 ASM_EQUATE SVC_TASK_BLOCK, 2
 ASM_EQUATE SVC_TASK_SWITCH, 3

                ASM_EXTERN _mqx_kernel_data
                ASM_EXTERN _klog_isr_start_internal
                ASM_EXTERN _klog_isr_end_internal
                        
                ASM_SECTION KERNEL
                
                ASM_PUBLIC _sched_start_internal
                ASM_PUBLIC _sched_run_internal
                ASM_PUBLIC _sched_check_scheduler_internal
                ASM_PUBLIC _sched_execute_scheduler_internal
                
                ASM_PUBLIC _task_block
                ASM_PUBLIC _svc_handler
                ASM_PUBLIC _pend_svc
                ASM_PUBLIC _int_kernel_isr

		SET_FUNCTION_ALIGNMENT


;FUNCTION*----------------------------------------------------------------------
; 
; Function Name    : _sched_start_internal
; Returned Value   : none
; Comments         : start MQX scheduler
;
;END*---------------------------------------------------------------------------

_sched_start_internal:
		svc SVC_RUN_SCHED
		bx lr

_sched_run_internal:
		svc SVC_RUN_SCHED
_sched_run_internal_loop:
		b _sched_run_internal_loop

_sched_check_scheduler_internal:
                
                GET_KERNEL_DATA r0
                
                cpsid.n i
                ldrh r1, [r0, #KD_IN_ISR]
                cbnz r1, _sched_execute_scheduler_internal_end
                
                ldr r1, [r0, #KD_CURRENT_READY_Q]
                ldr r2, [r0, #KD_ACTIVE_PTR]
                ldr r3, [r2, #TD_MY_QUEUE]
                cmp r1, r3
                beq _sched_execute_scheduler_internal_end       ; current task is still the active task
                
                cpsie.n i
_sched_execute_scheduler_internal:
		svc SVC_TASK_SWITCH
                
_sched_execute_scheduler_internal_end:
                cpsie.n i                
		bx lr



;FUNCTION*----------------------------------------------------------------------
; 
; Function Name    : _task_block
; Returned Value   : none
; Comments         : task block function - block actual task - switch to another
;
;END*---------------------------------------------------------------------------

_task_block:
		svc SVC_TASK_BLOCK
		bx lr


;FUNCTION*----------------------------------------------------------------------
; 
; Function Name    : _svc_handler
; Returned Value   : none
; Comments         : SVC handler - called after SVC instruction
;                    call MQX scheduler functions
;
;END*---------------------------------------------------------------------------

_svc_handler:
                push {lr}
                cpsid.n i
                
		tst lr, #0x4						; test EXC_RETURN number in LR bit 2
		ite eq								; if zero (equal) then
		mrseq r1, MSP						; Main Stack was used, put MSP in R1
		mrsne r1, PSP						; else, Process Stack was used, put PSP in R1
;		ldr r0, [r1, #0]					; get stacked R0 from stack
		ldr r1, [r1, #24]					; get stacked PC from stack
		ldrb r1, [r1, #-2]					; get the immediate data from the instruction

svc_task_switch:
		cmp r1, #SVC_TASK_SWITCH
		bne svc_run_sched
                
                bl _set_pend_sv
                b svc_handler_end

svc_run_sched:
		cmp r1, #SVC_RUN_SCHED
		bne svc_task_block
                
		GET_KERNEL_DATA r0
                pop {lr}
		b first_run

svc_task_block:
		cmp r1, #SVC_TASK_BLOCK
		bne svc_handler_end

		GET_KERNEL_DATA r0
		ldr r1, [r0, #KD_ACTIVE_PTR]		; get active task descriptor

		; set task block bit
		ldr r2, [r1, #TD_STATE]
		orr r2, r2, #1					; TODO change from number to define
		str r2, [r1, #TD_STATE]

#if MQX_KERNEL_LOGGING
                KLOG r0, ASM_PREFIX(_klog_block_internal)        ; kernel log this function
#endif // MQX_KERNEL_LOGGING
                ; remove active task from ready que
                ldr r2, [r1, #TD_TD_PREV]            ; get ptr to ready_q structure
                ldr r3, [r1, #TD_TD_NEXT]
                str r3, [r2, #RQ_HEAD_READY_Q]
                str r2, [r3, #TD_TD_PREV]
                
                bl _set_pend_sv
        
svc_handler_end:
                cpsie.n i
                pop {pc}

;FUNCTION*----------------------------------------------------------------------
; 
; Function Name    : _set_pend_sv
; Returned Value   : none
; Comments         : This functions set pending sv flag - request for PendSV
;                    request for task switch
;
;END*---------------------------------------------------------------------------

_set_pend_sv:
                push {r0-r2, lr}

                ; get PendSV flag
                ldr r0, =0xE000ED00
                ldr r1, [r0, #4]                        ; 0xE000ED04
                tst r1, #0x10000000
                bne _set_pend_sv_end

                mrs r2, BASEPRI
                sub r2, r2, #0x10
              
                ; set priority for PendSV
                strb r2, [r0, #0x22]                    ; 0xE000ED22
                
                ; set PendSV flag
                ldr r2, =0x10000000
                orrs r1, r2
                str r1, [r0, #4]                        ; 0xE000ED04

_set_pend_sv_end:
                pop {r0-r2, pc}

;FUNCTION*----------------------------------------------------------------------
; 
; Function Name    : _pend_svc
; Returned Value   : none
; Comments         : PendSV handler - task switch functionality
;
;END*---------------------------------------------------------------------------

; Pending Service Call
_pend_svc:
                cpsid.n i
                
                ; store active task registers
                mrs r12, PSP                        ; get process stack pointer for active task
                
                ldr r1, =0xE000ED20                 ; SHPR3
                ldrb r2, [r1, #2]

                mrs r3, BASEPRI
                stmdb r12!, {r2-r11, lr}    ; store remaining registers

                GET_KERNEL_DATA r0
                ldr r3, [r0, #KD_ACTIVE_PTR]        ; get active task descriptor
                str r12, [r3, #TD_STACK_PTR]        ; store task SP to task descriptor td

first_run:
                cpsid.n i
                ldr r1, [r0, #KD_CURRENT_READY_Q]   ; get current ready q
find_noempty_que:
                ldr r2, [r1, #0]            ; address of first td
                cmp r2, r1                  ; ready_q structure itself?
                bne switch_task        
                ldr r1, [r1, #RQ_NEXT_Q]    ; try next queue
                movs r1, r1
                bne find_noempty_que

                ; r1 is 0 -> empty
no_one_to_run:
                ; TODO set system task ???
                ; enable all interrupts (r1 = 0)
                ; TODO maybe (maybe not necessary) restore PendSV priority and BASEPRI after wfi
                msr BASEPRI, r1
                
                ldr r1, =0xE000ED20                    ; SHPR3
                ldr r2, =0xff
                strb r2, [r1, #2]

                ; wait for interrupt
                cpsie.n i
                wfi
                cpsid.n i

                ; TODO check r0, must be kernel data
                ldr r1, [r0, #KD_READY_Q_LIST]        ; get first que from ready list
                b find_noempty_que

switch_task:
                ; update kernel structures
                str r1, [r0, #KD_CURRENT_READY_Q]    ; store addr for active que
                str r2, [r0, #KD_ACTIVE_PTR]        ; active task descriptor
    
                ldrh r3, [r2, #TD_TASK_SR]
                strh r3, [r0, #KD_ACTIVE_SR]        ; restore priority mask for enabled interrupt for active task
            
                ; activate task, restore registers
                ldr r12, [r2, #TD_STACK_PTR]        ; get task SP
                ldmia r12!, {r2-r11, lr}            ; restore registers
                msr BASEPRI, r3
                
                msr PSP, r12                        ; restore process stack pointer for task
                
#if MQX_KERNEL_LOGGING
                KLOG r0, ASM_PREFIX(_klog_context_switch_internal)  ; do kernel logging
#endif
                cpsie.n i
                bx lr

;FUNCTION*----------------------------------------------------------------------
; 
; Function Name    : _int_kernel_isr
; Returned Value   : none
; Comments         : MQX kernel interrupt handler
;
;END*---------------------------------------------------------------------------

; kernel interrupt handler
_int_kernel_isr:
                cpsid.n i
                push {lr}

                GET_KERNEL_DATA r3            ; get the kernel data address

                ; increment in interrupt counter
                ldrh r1, [r3, #KD_IN_ISR]
                add r1, r1, #1
                strh r1, [r3, #KD_IN_ISR]
                
                ; create interrupt content
                ldr r0, =0                      ; error code (set 0)
                push {r0}                       ; store in stack
                mrs r2, BASEPRI                 ; actual priority
                mrs r1, IPSR                    ; exception number
                ldr r0, [r3, #KD_INTERRUPT_CONTEXT_PTR] ; previous interrupt content
                push {r0-r2}                    ; store in stack
                
                mrs r0, MSP                     ; get address of interrupt content
                str r0, [r3, #KD_INTERRUPT_CONTEXT_PTR] ; store address of actual interrupt content in kernel data
                
                mov r0, r1
                
#if MQX_KERNEL_LOGGING
                ldr r1, [r3, #KD_LOG_CONTROL]
                tst r1, #0x00000001
                beq _isr_no_logging
                
                ; prepare parameters for klog function
                push {r0-r3}
                bl _klog_isr_start_internal
                pop {r0-r3}
_isr_no_logging:
#endif // MQX_KERNEL_LOGGING
		; get C function address from MQX interrupt table
                ; r0 - interrupt number
                
		; check if isr is in table range
                ldr r2, [r3, #KD_LAST_USER_ISR_VECTOR]
                
#ifndef __CODEWARRIOR__
                cbz r2, _isr_run_default                ; isr not used
#else
                ; CW 10 workaround
                cbnz r2, _my_jump
                b _isr_run_default
_my_jump:                
#endif
                cmp r0, r2
                bhi _isr_run_default
                
                ldr r2, [r3, #KD_FIRST_USER_ISR_VECTOR]
		subs r1, r0, r2                         ; r1 = actual exception number in table
                blt _isr_run_default

#if MQX_SPARSE_ISR_TABLE

_int_kernel_isr_vect_ok:
                ldr r2, [r3, #KD_INTERRUPT_TABLE_PTR]   ; get the interrupt table pointer
                lsr r1, r1, #MQX_SPARSE_ISR_SHIFT
                lsl r1, r1, #2

                ldr r1, [r2, r1]                        ; get address of first isr in linked list
#ifndef __CODEWARRIOR__
                cbz r1, _isr_run_default                ; isr not used
#else
                ; CW 10 workaround
                cbnz r1, _my_jump2		        ; isr not used
		b _isr_run_default
_my_jump2:
#endif
                ; r1 - address of first isr in linked list
_isr_search:
                ldr r2, [r1, #HASH_ISR_NUM]             ; get isr num
                cbz r2, _isr_search_fail
                
                cmp r2, r0                              ; compare isr number in record with actual isr number
                beq _isr_search_suc
                
                ldr r1, [r1, #HASH_ISR_NEXT]            ; next vector in list
                tst r1, r1
                bne _isr_search
                
_isr_search_fail:
                b _isr_run_default
                
_isr_search_suc:
                ldr r0, [r1, #HASH_ISR_DATA]            ; move notifier data into r0 = first parameter in C func
                ldr r2, [r1, #HASH_ISR_ADDR]            ; move interrupt function address to r2
#else
_int_kernel_isr_vect_ok:
		; calculate offset in table
		; each table entry is 12 bytes in size
                mov r2, #12
                mul r1, r2, r1

                ldr r2, [r3, #KD_INTERRUPT_TABLE_PTR] 	; pointer to interrupt table begin
                add r1, r1, r2                        	; get address of entry in table
                ldr r2, [r1, #0]
                ldr r0, [r1, #IT_APP_ISR_DATA]          ; move notifier data into r0 = first parameter in C func
#endif

_isr_execute:
                ; r0 = first parameter in C func
                ; r2 contain interrupt function address
                
                cpsie.n i
		push {r3}

		blx r2

_int_kernel_isr_epilog:

		pop {r3}
                cpsid.n i
                
_int_kernel_isr_return_internal:

#if MQX_KERNEL_LOGGING
                ldr r1, [r3, #KD_LOG_CONTROL]
                tst r1, #0x00000001
                beq _isr_return_no_logging
                
                mrs r0, IPSR                    ; exception number

                ; prepare parameters for klog function
                push {r0-r3}
                bl _klog_isr_end_internal
                pop {r0-r3}                
_isr_return_no_logging:                
#endif // MQX_KERNEL_LOGGING

                ; remove interrupt content
                pop {r0-r2}
                str r0, [r3, #KD_INTERRUPT_CONTEXT_PTR] ; update pointer to interrupt content

                pop {r0}                                ; error code

		; decrement interrupt counter
		ldrh r1, [r3, #KD_IN_ISR]
		subs r1, r1, #1
                strh r1, [r3, #KD_IN_ISR]
                
                ; check for reschedule
                ; check preemtion
                ldr r2, [r3, #KD_ACTIVE_PTR]    ; TD pointer
                ldr r0, [r2, #TD_FLAGS]
                tst r0, #TASK_PREEMPTION_DISABLED
                bne _isr_return_end

                cbnz r1, _isr_return_end        ; waiting another isr, do not reschedulle
                
                ; if a different TD at head of current readyq, then we need to run the scheduler
                ; check for reschedule
                ldr r1, [r3, #KD_CURRENT_READY_Q]
                ldr r1, [r1]
                cmp r1, r2
#ifdef __CODEWARRIOR__
                it ne
                bl _set_pend_sv
#else
                it ne
                blne _set_pend_sv
#endif
                
_isr_return_end:
                cpsie.n i
                pop {pc}
                
_isr_run_default:
                ; r0 - interrupt number

                ldr r2, [r3, #KD_DEFAULT_ISR]
              
                b _isr_execute

;FUNCTION*-------------------------------------------------------------------
; 
; Function Name    : _psp_exception_return
; Returned Value   : none
; Comments         : This functions returns us from an isr exception
;
;END*----------------------------------------------------------------------

                ASM_PUBLIC ASM_PREFIX(_psp_exception_return)

ASM_PREFIX(_psp_exception_return):
                cpsid.n i
                push {r0, r4-r7}    ; store parameter and registers wich are used for copy and cpu do not store if 

                GET_KERNEL_DATA r3
                
                ; copy actual int context + 4WORDS -> prev int context - (1 + 8)WORDS
                ldr r12, [r3, #KD_INTERRUPT_CONTEXT_PTR]    ; get actual int context
                add r12, r12, #16               ; calculate source address
                
                ldr lr, [r12], #4               ; lr - return from exception... (0xfffffff1)
                
                ; modify return address (PC) in exception stack frame (kernel isr epilog)
                ldr r0, =_int_kernel_isr_epilog
                bic r0, r0, #1
                str r0, [r12, #24]
                
                ldmia r12, {r0-r7}              ; read exception stack frame
                
                pop {r12}                       ; get prev int context address (function parameter - r0)
                
                ; destination stack address (4B + 32B - exception stack frame)
                sub r12, r12, #4    ;#36
                stmdb r12!, {r0-r7}
                
                ; restore modified registers which are not restored by cpu
                pop {r4-r7}
                
       		msr MSP, r12   ; update MSP (main stack pointer)
                
                cpsie.n i

                bx lr


/*******************************************************************************
 * test support
 ******************************************************************************/

;FUNCTION*-------------------------------------------------------------------
;
; Function Name    : _mem_test_and_set
; Returned Value   : previous value of location
; Comments         :
;   This function tests a byte location, and if AND 0x80 is 0 (7bit is set !!!), sets it to 0x80.
;   It returns the previous value of the byte (0 or 0x80).
;
;END*----------------------------------------------------------------------

                ASM_PUBLIC _mem_test_and_set

_mem_test_and_set:
                push {r1, lr}
                
                ldrb r1, [r0]
                tst r1, #0x80
                ittte eq
                orreq r1, r1, #0x80
                strbeq r1, [r0]
                eoreq r0, r0
                movne r0, #0x80
                
                pop {r1, pc}

;FUNCTION*----------------------------------------------------------------------
; 
; Function Name    : __get_PSP
; Returned Value   : none
; Comments         : This functions returns PSP register value
;
;END*---------------------------------------------------------------------------
                ASM_PUBLIC ASM_PREFIX(__get_PSP)

ASM_PREFIX(__get_PSP):
                mrs r0, PSP
                bx lr

;FUNCTION*----------------------------------------------------------------------
; 
; Function Name    : __get_MSP
; Returned Value   : none
; Comments         : This functions returns MSP register value
;
;END*---------------------------------------------------------------------------
                ASM_PUBLIC ASM_PREFIX(__get_MSP)

ASM_PREFIX(__get_MSP):
                mrs r0, MSP
                bx lr

;FUNCTION*----------------------------------------------------------------------
; 
; Function Name    : __get_PSR
; Returned Value   : none
; Comments         : This functions returns PSR (procesor status register) value
;
;END*---------------------------------------------------------------------------
                ASM_PUBLIC ASM_PREFIX(__get_PSR)

ASM_PREFIX(__get_PSR):
        #ifdef __CWARM__
                 mrs r0, XPSR
        #else 
                 mrs r0, PSR
        #endif
                 bx lr

#ifdef __CWARM__

;FUNCTION*----------------------------------------------------------------------
; 
; Function Name    : __get_LR
; Returned Value   : none
; Comments         : This functions returns LR register value
;
;END*---------------------------------------------------------------------------
                ASM_PUBLIC ASM_PREFIX(__get_LR)

ASM_PREFIX(__get_LR):
                mov r0, lr
                bx lr



;FUNCTION*----------------------------------------------------------------------
; 
; Function Name    : __get_PC
; Returned Value   : none
; Comments         : This functions returns LR register value
;
;END*---------------------------------------------------------------------------
                ASM_PUBLIC ASM_PREFIX(__get_PC)

ASM_PREFIX(__get_PC):
                mov r0, PC
                bx lr
                

;FUNCTION*----------------------------------------------------------------------
; 
; Function Name    : __enable_interrupt
; Returned Value   : none
; Comments         : This functions enables interrupts
;
;END*---------------------------------------------------------------------------

		ASM_PUBLIC ASM_PREFIX(__enable_interrupt)
		
ASM_PREFIX(__enable_interrupt):
                 cpsie.n i
                 bx lr

;FUNCTION*----------------------------------------------------------------------
; 
; Function Name    : __disable_interrupt
; Returned Value   : none
; Comments         : This functions disables interrupts
;
;END*---------------------------------------------------------------------------

                ASM_PUBLIC ASM_PREFIX(__disable_interrupt)

ASM_PREFIX(__disable_interrupt):
                 cpsid.n i
                 bx lr

#endif  /* __CWARM__ */

    ASM_END


