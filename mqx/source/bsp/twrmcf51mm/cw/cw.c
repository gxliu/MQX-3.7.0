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
* $FileName: cw.c$
* $Version : 3.6.2.0$
* $Date    : Jun-4-2010$
*
* Comments:
*
*   This file contains runtime support for the Metrowerks Compiler.
*
*END************************************************************************/

#include "mqx.h"
#include "bsp.h"
#include "bsp_prv.h"

#if BSPCFG_ENABLE_CPP
typedef void (*StaticInitializer)(void);
extern StaticInitializer __sinit__[];
#endif

/* CodeWarrior overrides prototypes */
extern int exit(int status);
extern asm void __initialize_hardware(void);
extern void __initialize_OS(void);
extern void __destroy_global_chain(void);
extern pointer malloc(_mem_size);
extern pointer calloc(_mem_size, _mem_size);
extern void free(pointer);
void __call_static_initializers(void);
void __temp_file_name(pointer,pointer);
int  __init_uart_console(void);
int  __write_console(pointer,pointer,pointer,pointer);
int  __read_console(pointer,pointer,pointer,pointer);
int  __close_console(pointer);
int  __delete_file(pointer);
int  __rename_file(pointer,pointer);

#if MQX_EXIT_ENABLED
/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : exit
* Returned Value   : should not return
* Comments         :
*   Replacement for Codewarrior's exit function
*
*END*----------------------------------------------------------------------*/
int exit
   (
      int status
   )
{ /* Body */
    
#if BSPCFG_ENABLE_CPP
   /* Destroy all constructed global objects */
   __destroy_global_chain();
#endif

   while (TRUE) {
   } /* Endwhile */
   // Should never return

} /* Endbody */
#else
int exit(int status) {return 0;}
void __destroy_global_chain(void) {}
#endif



/* Override C/C++ runtime heap allocation/deallocation */
pointer malloc(_mem_size bytes) {return _mem_alloc_system(bytes);}
pointer calloc(_mem_size n, _mem_size z) { return _mem_alloc_system_zero(n*z); } 
void free(pointer p)        {_mem_free(p);}

/* Override C++ inititialization so it happens later in _bsp_enable_card */
void __call_static_initializers(void){}
#pragma overload void __call_static_initializers(void);

#if BSPCFG_ENABLE_CPP
void __cpp_init
   (
      void
   )
{ /* Body */
   StaticInitializer s, *p;
   if ((p = __sinit__) != 0) {
      for (; (s = *p) != 0; p++) s();
   } /* Endif */
} /* Endbody */
#endif

/*
** Override Codewarrior runtime functions that should
** not be imported by the linker
*/
int __init_uart_console(void){return 0;}
int __write_console(pointer,pointer,pointer,pointer){return 0;}
int __read_console(pointer,pointer,pointer,pointer){return 0;}
int __close_console(pointer){return 0;}
int __delete_file(pointer){return 0;}
int __rename_file(pointer,pointer){return 0;}
void __temp_file_name(pointer,pointer){}

/* EOF */
