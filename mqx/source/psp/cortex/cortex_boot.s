;/**HEADER********************************************************************
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
;* $FileName: cortex_boot.s$
;* $Version : 3.6.3.0$
;* $Date    : Nov-2-2010$
;*
;* Comments:
;*
;*
;*END************************************************************************/

#include <asm_mac.h>
#include "types.s"

;FUNCTION*-------------------------------------------------------------------
; 
; Function Name    : _arm920t_get_ctrl_reg
; Returned Value   : Contents of control register
; Comments         : This functions reads the control register 
;
;END*----------------------------------------------------------------------
        ASM_SECTION .text
        
        ASM_PUBLIC   __boot
        ASM_PUBLIC   __set_MSP

        ASM_EXTERN __iar_program_start
        
__boot:
        mrs r0, MSP
        msr PSP, r0
        
        ; switch to proccess stack (PSP)
        mrs r0, CONTROL
        orr r0, r0, #2
        msr CONTROL, r0
        
        b __iar_program_start
        
__set_MSP:
        msr MSP, r0
        bx lr

        ASM_END
