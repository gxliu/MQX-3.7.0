#ifndef _istrata_h_
#define _istrata_h_
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
* $FileName: istrata.h$
* $Version : 3.0.4.0$
* $Date    : Jun-23-2009$
*
* Comments:
*
*   The file contains functions prototype, defines, structure 
*   definitions specific for the Intel strataflash devices
*
*END************************************************************************/


/*----------------------------------------------------------------------*/
/*
**                     FUNCTION PROTOTYPES
*/
#ifdef __cplusplus
extern "C" {
#endif

/* Top level functions visible to the generic flashx driver */
extern boolean _intel_strata_program(IO_FLASHX_STRUCT_PTR, uchar_ptr, uchar_ptr, _mem_size);

/* Top level functions visible to the generic flashx driver */
extern boolean _intel_strata_erase(IO_FLASHX_STRUCT_PTR, uchar_ptr, _mem_size);

extern boolean _intel_strata_write_protect(IO_FLASHX_STRUCT_PTR , _mqx_uint);
extern boolean _intel_strata_clear_lock_bits(IO_FLASHX_STRUCT_PTR);
extern boolean _intel_strata_set_lock_bits(IO_FLASHX_STRUCT_PTR);
extern _mqx_int _io_intel_strata_ioctl(IO_FLASHX_STRUCT_PTR, _mqx_uint, pointer);
#ifdef __cplusplus
}
#endif

#endif

/* EOF */
