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
* $Version : 3.7.5.0$
* $Date    : Feb-22-2011$
*
* Comments:
*
*   This file contains runtime support for the Metrowerks Compiler.
*
*END************************************************************************/

#include "mqx.h"
#include "bsp.h"
#include "bsp_prv.h"


typedef void (*StaticInitializer)(void);
extern StaticInitializer __sinit__[];


/* CodeWarrior overrides prototypes */
void    __init_hardware(void);
void    kinetis_init (void);
pointer malloc(_mem_size);
pointer calloc(_mem_size, _mem_size);
void    free(pointer);
void    __cpp_init(void);
int     exit(int status);
void    __destroy_global_chain(void);

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : __init_hardware
* Returned Value   : void
* Comments         :
*   Function __init_hardware() overloads its default instance 
*   in EWL Runtime library. It calls function which initializes CPU registers.  
*
*END*----------------------------------------------------------------------*/
#pragma overload void __init_hardware(void);

void __init_hardware
   (
      void
   )
{
	/* Initialize Kinetis device. */
	kinetis_init ();
}



/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : malloc
* Returned Value   : pointer
* Comments         :
*   Override C/C++ runtime heap allocation function
*
*END*----------------------------------------------------------------------*/
#pragma overload pointer malloc(_mem_size bytes);

pointer malloc(_mem_size bytes) {return _mem_alloc_system(bytes);}



/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : calloc
* Returned Value   : pointer
* Comments         :
*   Override C/C++ runtime heap deallocation
*
*END*----------------------------------------------------------------------*/
#pragma overload pointer calloc(_mem_size bytes, _mem_size z);

pointer calloc(_mem_size n, _mem_size z){return _mem_alloc_system_zero(n*z);} 



/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : free
* Returned Value   : void
* Comments         :
*   Override C/C++ runtime free 
*
*END*----------------------------------------------------------------------*/
#pragma overload void free(pointer p);

void free(pointer p) {_mem_free(p);}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : __cpp_init
* Returned Value   : void
* Comments         :
*   Override C++ initialization so it happens later in _bsp_enable_card 
*
*END*----------------------------------------------------------------------*/

#if BSPCFG_ENABLE_CPP
#pragma overload void __cpp_init(void);

void __cpp_init
   (
      void
   )
{
   StaticInitializer s, *p;
   if ((p = __sinit__) != 0) {
      for (; (s = *p) != 0; p++) s();
   }
}
#endif /* BSPCFG_ENABLE_CPP */


/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : exit
* Returned Value   : should not return
* Comments         :
*   Replacement for Codewarrior's exit function
*
*END*----------------------------------------------------------------------*/
#if MQX_EXIT_ENABLED
#pragma overload int exit(int status);

int exit
   (
      int status
   )
{
   /* Destroy all constructed global objects */
   __destroy_global_chain();

   while (TRUE) {
   }
}

#else  /* MQX_EXIT_ENABLED */
#pragma overload int exit( int status);
int exit(int status) 
{
	return 0;
}
#endif /* MQX_EXIT_ENABLED */


/* EOF */
