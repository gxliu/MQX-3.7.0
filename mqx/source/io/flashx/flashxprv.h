#ifndef _flashxprv_h_
#define _flashxprv_h_
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
* $FileName: flashxprv.h$
* $Version : 3.6.6.0$
* $Date    : Jun-4-2010$
*
* Comments:
*
*   The file contains functions prototype, defines, structure 
*   definitions private to the flash drivers
*
*END************************************************************************/


/*----------------------------------------------------------------------*/
/*
**                    Structure Definitions
*/



/*----------------------------------------------------------------------*/
/*
**                    FUNCTION PROTOTYPES
*/

#ifdef __cplusplus
extern "C" {
#endif

/* These are from flashx.c */
extern _mqx_int  _io_flashx_flush_buffer(IO_FLASHX_STRUCT_PTR); 
extern  boolean   _io_flashx_erase_sector(IO_FLASHX_STRUCT_PTR, _mqx_uint, 
   _mqx_uint, _mqx_uint);
extern  void      _io_flashx_find_correct_sectors(IO_FLASHX_STRUCT_PTR, 
   _mqx_int, _mem_size, _mqx_uint _PTR_, _mqx_uint _PTR_, _mqx_uint _PTR_, 
   _mqx_uint _PTR_, _mqx_uint _PTR_);
extern _mqx_int  _io_flashx_open(MQX_FILE_PTR, char_ptr, char_ptr);
extern _mqx_int  _io_flashx_close(MQX_FILE_PTR);
extern _mqx_int  _io_flashx_write(MQX_FILE_PTR, char_ptr, _mqx_int);
extern _mqx_int  _io_flashx_read (MQX_FILE_PTR, char_ptr, _mqx_int);
extern _mqx_int  _io_flashx_ioctl(MQX_FILE_PTR, _mqx_uint, pointer);
extern _mem_size _io_flashx_write_partial_sector(MQX_FILE_PTR, _mqx_uint, _mqx_uint, 
   _mem_size, _mem_size, _mqx_uint, uchar_ptr);
extern _mem_size _io_flashx_check_free_space(uchar_ptr, _mem_size );   
extern void      _io_flashx_wait_us(_mqx_int);

boolean _allocate_sector_cache( IO_FLASHX_STRUCT_PTR handle_ptr );
   
#ifdef __cplusplus
}
#endif

#endif
/* EOF */
