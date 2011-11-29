#ifndef _pccardlpc_mpc5125_h_
#define _pccardlpc_mpc5125_h_
/**HEADER********************************************************************
* 
* Copyright (c) 2008 Freescale Semiconductor;
* All Rights Reserved
*
* Copyright (c) 2004-2008 Embedded Access Inc.;
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
* $FileName: pccardlpc_mpc5125.h$
* $Version : 3.7.2.0$
* $Date    : Feb-7-2011$
*
* Comments:
*
*   The file contains the structure definitions
*   public to the advacned PC Card 850 driver
*
*END************************************************************************/


/*----------------------------------------------------------------------*/
/*
**                          CONSTANT DEFINITIONS
*/


/*----------------------------------------------------------------------*/
/*
**                    DATATYPE DEFINITIONS
*/


/* Initialization parameters for the CompactFlash Card driver */
typedef struct mpc5125_pccardlpc_init_struct
{
   /* Base address for Compact Flash address space */
   pointer             PCMCIA_BASE;

} MPC5125_PCCARDLPC_INIT_STRUCT, _PTR_ PCCARDLPC_INIT_STRUCT_PTR;
typedef const MPC5125_PCCARDLPC_INIT_STRUCT _PTR_ PCCARDLPC_INIT_STRUCT_CPTR;


/*-----------------------------------------------------------------------
**                      FUNCTION PROTOTYPES
*/
#ifdef __cplusplus
extern "C" {
#endif

/* Interface functions */
uint_32 _io_pccardlpc_install(char_ptr, PCCARDLPC_INIT_STRUCT_CPTR);

#ifdef __cplusplus
}
#endif

#endif
/* EOF */

