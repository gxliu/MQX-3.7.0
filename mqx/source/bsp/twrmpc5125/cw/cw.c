/**HEADER********************************************************************
* 
* Copyright (c) 2008-2009 Freescale Semiconductor;
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
* $FileName: cw.c$
* $Version : 3.6.2.0$
* $Date    : Jun-4-2010$
*
* Comments:
* 
*     This file contains runtime support for the CodeWarrior Compiler.
*
*END***********************************************************************/
#include "mqx_inc.h"
#include "bsp.h"
#include "bsp_prv.h"

static void __fini_cpp(void);
void __init_user(void);
typedef void (*voidfunctionptr) (void); /* ptr to function returning void */
__declspec(section ".init") extern voidfunctionptr _ctors[];
__declspec(section ".init") extern voidfunctionptr _dtors[];
extern int  exit(int);
extern int  __exit(int);
extern void __destroy_global_chain(void);
extern void _ExitProcess(void);

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _ExitProcess
* Returned Value   : none
* Comments         :
*   Final loop
*
*END*----------------------------------------------------------------------*/
void _ExitProcess(void)
{ 
   static volatile _mqx_int count;
   for(;;){
      count++;
   }
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : __exit
* Returned Value   : none
* Comments         :
*   Final exit function
*
*END*----------------------------------------------------------------------*/
int __exit(int status)
{ 
   // Semi-normal Codewarrior shutdown sequence
#if BSPCFG_ENABLE_CPP
   __destroy_global_chain();
   __fini_cpp();
#endif

   /*
   ** Change for whatever is appropriate for your board
   ** and application.  Perhaps a software reset or
   ** some kind of trap/call to the kernel soft re-boot.
   */
   _ExitProcess();

   return(0);
} 

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : exit
* Returned Value   : none
* Comments         :
*   Replacement for Codewarrior's exit function
*
*END*----------------------------------------------------------------------*/
int exit(int status)
{
   return __exit(status);
} 

#if BSPCFG_ENABLE_CPP
void __init_cpp(void)
{ 
   voidfunctionptr *constructor;

   // call static initializers
   for (constructor = _ctors; *constructor; constructor++) {
      (*constructor)();
   } 
}

static void __fini_cpp(void)
{ 
   voidfunctionptr *destructor;

   // call static destructors
   for (destructor = _dtors; *destructor; destructor++) {
      (*destructor)();
   } 
} 
#endif

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : __init_user
* Returned Value   : none
* Comments         :
*   Early board initialization.  Occurs after memory has been initialized.
*
*END*----------------------------------------------------------------------*/

void __init_user(void)
{ 
}

/*
** Override Codewarrior runtime functions that should
** not be imported by the linker
*/
int __init_uart_console(void);
int __write_console(pointer,pointer,pointer,pointer);
int __read_console(pointer,pointer,pointer,pointer);
int __close_console(pointer);
int __delete_file(pointer);
int __rename_file(pointer,pointer);
void __temp_file_name(pointer,pointer);

int __init_uart_console(void){return 0;}
int __write_console(pointer,pointer,pointer,pointer){return 0;}
int __read_console(pointer,pointer,pointer,pointer){return 0;}
int __close_console(pointer){return 0;}
int __delete_file(pointer){return 0;}
int __rename_file(pointer,pointer){return 0;}
void __temp_file_name(pointer,pointer){}

/* Override malloc/free and new/delete allocator */

pointer malloc(_mem_size bytes);
pointer calloc(_mem_size n, _mem_size z);
void free(pointer p);

pointer malloc(_mem_size bytes) 
{
   return _mem_alloc_system(bytes);
}

pointer calloc(_mem_size n, _mem_size z) 
{ 
   return _mem_alloc_system_zero(n*z); 
} 

void free(pointer p)        
{
   _mem_free(p);
}

/* EOF */