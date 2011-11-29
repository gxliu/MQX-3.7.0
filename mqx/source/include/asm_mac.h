/**HEADER********************************************************************
* 
* Copyright (c) 2008 Freescale Semiconductor;
* All Rights Reserved
*
* Copyright (c) 2008 Embedded Access Inc.;
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
* $FileName: asm_mac.h$
* $Version : 3.7.6.0$
* $Date    : Feb-23-2011$
*
* Comments:
*   This file contains macros used by the assembler and resolves
*   differences between different assemblers.  Specifically
*   the IAR and Codewarrior assemblers.
*
*END************************************************************************/


#ifndef __asm_mac_h__
	#define __asm_mac_h__	1


/* IAR compiler does not add any leading underscores to assembly symbols,
**   CW does.
** __CWARM__ defined in cw10 psp project k60, k40
*/
#if defined __ACF__ || defined __IASMARM__ || defined __CWARM__
  #define ASM_PREFIX(x) x
#else
  #define ASM_PREFIX(x) _##x
#endif

/* Macro for the equate directive */
/* Spacing is important here, label must be in first column */
#if defined __ACF__ | defined __IASMARM__
ASM_EQUATE  MACRO label, value
label   EQU  value
        ENDM
#else
ASM_EQUATE:  .macro label, value
label  .equ  value
        .endm
#endif

          
#if defined __ACF__ | defined __IASMARM__
ASM_EXTERN  MACRO value
    EXTERN  value
        ENDM
#else
ASM_EXTERN:  .macro  value
    .extern  value
        .endm
#endif

#if defined __ACF__ | defined __IASMARM__
ASM_ALIGN  MACRO value
    ALIGN  value
        ENDM
#else
ASM_ALIGN:  .macro  value
    .align  value
        .endm
#endif


#if defined __ACF__ | defined __IASMARM__
ASM_PUBLIC  MACRO label
        PUBLIC label
            ENDM
#else
ASM_PUBLIC: .macro label
    .global label
            .endm
#endif

              
#if defined __ACF__ | defined __IASMARM__
ASM_SET     MACRO label, value
label SET value
            ENDM
#else
ASM_SET:    .macro label, value
    .set label, value
            .endm
#endif


#if defined __ACF__ | defined __IASMARM__
ASM_CONST16  MACRO value
    DC16 value
            ENDM
#else
ASM_CONST16:    .macro value
    .word value
            .endm
#endif
              
              
#if defined __ACF__ | defined __IASMARM__
ASM_CONST32  MACRO value
    DC32 value
            ENDM
#else
ASM_CONST32:    .macro value
    .long value
            .endm
#endif              

#if defined __ACF__ | defined __IASMARM__
ASM_LABEL_CONST32  MACRO label, value
label DC32 value
            ENDM
#else
ASM_LABEL_CONST32:  .macro label, value
label .long value
            .endm
#endif

#if defined __ACF__ | defined __IASMARM__
ASM_SECTION MACRO label
            SECTION label : CODE (4)
            ENDM
#else
ASM_SECTION: .macro label 
             .section label,16,x
             .endm
#endif

#if defined __ACF__ | defined __IASMARM__
ASM_END:     MACRO
             END
             ENDM
#else
ASM_END:     .macro
             .end
             .endm
#endif

#endif /* __asm_mac_h__ */
