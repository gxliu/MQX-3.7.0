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
* $FileName: vectors.c$
* $Version : 3.6.1.0$
* $Date    : Aug-2-2010$
*
* Comments:
*
*    This file contains the exception vector table.
*
*END************************************************************************/

#include "mqx_inc.h"

extern unsigned long __BOOT_STACK_ADDRESS[];

/* CFM init */
#define KEY_UPPER   0
#define KEY_LOWER   0
#define CFMPROT     0
#define CFMSACC     0
#define CFMDACC     0
#define CFMSEC      0

#ifdef __ICCCF__
    #define BOOT_START __program_start
    
    extern void __program_start(void);
    
    #pragma diag_suppress=Pe177
    #pragma segment="CFMCONFIG"

    const unsigned long _cfm[6] @ "CFMCONFIG" =
#else
    #define BOOT_START __boot
    
    extern void __boot(void);
    
    #pragma define_section cfmconfig ".cfmconfig"  far_absolute RW
    #pragma explicit_zero_data on

    __declspec(cfmconfig) unsigned long _cfm[6] = 
#endif  
{
    KEY_UPPER,
    KEY_LOWER,
    CFMPROT,
    CFMSACC,
    CFMDACC,
    CFMSEC,
};

typedef void (*vector_entry)(void);

extern vector_entry __VECTOR_TABLE_ROM_START[]; /* defined in linker command file */
extern vector_entry __VECTOR_TABLE_RAM_START[]; /* defined in linker command file */

#if MQX_ROM_VECTORS

    #define DEFAULT_VECTOR  _int_kernel_isr

#else
    extern void __boot_exception(void);

    #define DEFAULT_VECTOR  __boot_exception
    #ifdef __ICCCF__
        #pragma segment="INTVECRAM"
        const vector_entry ram_vector[256] @ "INTVECRAM" =
    #else
        #pragma define_section vectors_ram ".vectors_ram" far_absolute RW
        /*
        ** array for excepion vectors in ram + space (6 words)
        ** for CW fun (when CW debuger handle exceptions,
        ** using(rewrite) VBR+0x408 address
        */
        __declspec(vectors_ram) vector_entry ram_vector[256 + 6] = 
    #endif  
    { (vector_entry)__BOOT_STACK_ADDRESS, BOOT_START };
#endif

/* 
** exception vector table - this table is really used
*/ 
#ifdef __ICCCF__
    #pragma segment="INTVEC"
    const vector_entry rom_vector[256] @ "INTVEC" = 
#else    
    #pragma define_section vectors_rom ".vectors_rom" far_absolute R
    __declspec(vectors_rom) vector_entry rom_vector[256] = 
#endif
{
   (vector_entry)__BOOT_STACK_ADDRESS,
    BOOT_START,              /*   1 (0x004) Initial PC                 */
   DEFAULT_VECTOR,           /*   2 (0x008) Access Error               */
   DEFAULT_VECTOR,           /*   3 (0x00C) Address Error              */
   DEFAULT_VECTOR,           /*   4 (0x010) Illegal Instruction        */
   DEFAULT_VECTOR,           /*   5 (0x014) Reserved                   */
   DEFAULT_VECTOR,           /*   6 (0x018) Reserved                   */
   DEFAULT_VECTOR,           /*   7 (0x01C) Reserved                   */
   DEFAULT_VECTOR,           /*   8 (0x020) Privilege Violation        */
   DEFAULT_VECTOR,           /*   9 (0x024) Trace                      */
   DEFAULT_VECTOR,           /*  10 (0x028) Unimplemented A-Line       */
   DEFAULT_VECTOR,           /*  11 (0x02C) Unimplemented F-Line       */
   DEFAULT_VECTOR,           /*  12 (0x030) Debug Interrupt            */
   DEFAULT_VECTOR,           /*  13 (0x034) Reserved                   */
   DEFAULT_VECTOR,           /*  14 (0x038) Format Error               */
   DEFAULT_VECTOR,           /*  15 (0x03C) Unitialized Int            */
   DEFAULT_VECTOR,           /*  16 (0x040) Reserved                   */
   DEFAULT_VECTOR,           /*  17 (0x044) Reserved                   */
   DEFAULT_VECTOR,           /*  18 (0x048) Reserved                   */
   DEFAULT_VECTOR,           /*  19 (0x04C) Reserved                   */
   DEFAULT_VECTOR,           /*  20 (0x050) Reserved                   */
   DEFAULT_VECTOR,           /*  21 (0x054) Reserved                   */
   DEFAULT_VECTOR,           /*  22 (0x058) Reserved                   */
   DEFAULT_VECTOR,           /*  23 (0x05C) Reserved                   */
   DEFAULT_VECTOR,           /*  24 (0x060) Spurious Interrupt         */
   DEFAULT_VECTOR,           /*  25 (0x064) Autovector Level 1         */
   DEFAULT_VECTOR,           /*  26 (0x068) Autovector Level 2         */
   DEFAULT_VECTOR,           /*  27 (0x06C) Autovector Level 3         */
   DEFAULT_VECTOR,           /*  28 (0x070) Autovector Level 4         */
   DEFAULT_VECTOR,           /*  29 (0x074) Autovector Level 5         */
   DEFAULT_VECTOR,           /*  30 (0x078) Autovector Level 6         */
   DEFAULT_VECTOR,           /*  31 (0x07C) Autovector Level 7         */
   DEFAULT_VECTOR,           /*  32 (0x080) TRAP #0                    */
   DEFAULT_VECTOR,           /*  33 (0x084) TRAP #1                    */
   DEFAULT_VECTOR,           /*  34 (0x088) TRAP #2                    */
   DEFAULT_VECTOR,           /*  35 (0x08C) TRAP #3                    */
   DEFAULT_VECTOR,           /*  36 (0x090) TRAP #4                    */
   DEFAULT_VECTOR,           /*  37 (0x094) TRAP #5                    */
   DEFAULT_VECTOR,           /*  38 (0x098) TRAP #6                    */
   DEFAULT_VECTOR,           /*  39 (0x09C) TRAP #7                    */
   DEFAULT_VECTOR,           /*  40 (0x0A0) TRAP #8                    */
   DEFAULT_VECTOR,           /*  41 (0x0A4) TRAP #9                    */
   DEFAULT_VECTOR,           /*  42 (0x0A8) TRAP #10                   */
   DEFAULT_VECTOR,           /*  43 (0x0AC) TRAP #11                   */
   DEFAULT_VECTOR,           /*  44 (0x0B0) TRAP #12                   */
   DEFAULT_VECTOR,           /*  45 (0x0B4) TRAP #13                   */
   DEFAULT_VECTOR,           /*  46 (0x0B8) TRAP #14                   */
   DEFAULT_VECTOR,           /*  47 (0x0BC) TRAP #15                   */
   DEFAULT_VECTOR,           /*  48 (0x0C0) Reserved                   */
   DEFAULT_VECTOR,           /*  49 (0x0C4) Reserved                   */
   DEFAULT_VECTOR,           /*  50 (0x0C8) Reserved                   */
   DEFAULT_VECTOR,           /*  51 (0x0CC) Reserved                   */
   DEFAULT_VECTOR,           /*  52 (0x0D0) Reserved                   */
   DEFAULT_VECTOR,           /*  53 (0x0D4) Reserved                   */
   DEFAULT_VECTOR,           /*  54 (0x0D8) Reserved                   */
   DEFAULT_VECTOR,           /*  55 (0x0DC) Reserved                   */
   DEFAULT_VECTOR,           /*  56 (0x0E0) Reserved                   */
   DEFAULT_VECTOR,           /*  57 (0x0E4) Reserved                   */
   DEFAULT_VECTOR,           /*  58 (0x0E8) Reserved                   */
   DEFAULT_VECTOR,           /*  59 (0x0EC) Reserved                   */
   DEFAULT_VECTOR,           /*  60 (0x0F0) Reserved                   */
   DEFAULT_VECTOR,           /*  61 (0x0F4) Reserved                   */
   DEFAULT_VECTOR,           /*  62 (0x0F8) Reserved                   */
   DEFAULT_VECTOR,           /*  63 (0x0FC) Reserved                   */
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR,
   DEFAULT_VECTOR, 
};
/* EOF */