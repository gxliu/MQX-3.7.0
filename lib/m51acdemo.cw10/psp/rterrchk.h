#ifndef _rterrchk_h_
#define _rterrchk_h_ 1
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
* $FileName: rterrchk.h$
* $Version : 3.0.3.0$
* $Date    : Nov-21-2008$
*
* Comments:
*
*   This file is intended to be used by applications when including run-time
*   error checking.
*
*END************************************************************************/

/*--------------------------------------------------------------------------*/
/*
** STRUCTURE DEFINITIONS
*/
#ifdef __DCC__
/* Diab Data RTA Suite-specific */
#include <stdlib.h>
#include <rta/rtc.h>
#include <rta/rtaenv.h>  

/* Over-ride the MQX memory manager calls to go through the RTEC memory checker first */
/* Over-ride the MQX memory manager calls to go through the RTEC memory checker first */

#define _mem_alloc(size)      _rterrchk_mem_alloc(size)
#define _mem_alloc_zero(size) _rterrchk_mem_alloc_zero(size)
#define _mem_free(p)          _rterrchk_mem_free(p)

extern pointer   _rterrchk_mem_alloc(_mem_size);
extern pointer   _rterrchk_mem_alloc_zero(_mem_size);
extern _mqx_uint _rterrchk_mem_free(pointer);

#endif /* __DCC__ */

#endif
/* EOF */
