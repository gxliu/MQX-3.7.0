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
* $FileName: sockio.c$
* $Version : 3.6.10.0$
* $Date    : Jun-4-2010$
*
* Comments:
*
*   This file contains the implementation of an MQX
*   socket I/O device.
*
*END************************************************************************/

#include <rtcs.h>
#include <fio.h>


typedef struct io_socket {
   uint_32  SOCKET;
} IO_SOCKET, _PTR_ IO_SOCKET_PTR;

_mqx_int _io_socket_open  (MQX_FILE_PTR, char _PTR_,  char _PTR_);
_mqx_int _io_socket_close (MQX_FILE_PTR);
_mqx_int _io_socket_read  (MQX_FILE_PTR, char _PTR_, _mqx_int);
_mqx_int _io_socket_write (MQX_FILE_PTR, char _PTR_, _mqx_int);
_mqx_int _io_socket_ioctl (MQX_FILE_PTR, _mqx_uint, pointer);


/*FUNCTION*-------------------------------------------------------------
*
* Function Name  : _io_socket_install
* Returned Value :
* Comments       :
*
*END*-----------------------------------------------------------------*/

int_32 _io_socket_install
   (
      char_ptr identifier
   )
{ /* Body */

   return _io_dev_install(identifier,
                          _io_socket_open,
                          _io_socket_close,
                          _io_socket_read,
                          _io_socket_write,
#if MQX_VERSION < 250
                          (int_32(_CODE_PTR_)(MQX_FILE_PTR, uint_32, uint_32_ptr))
#endif
                          _io_socket_ioctl,
                          NULL );
} /* Endbody */


/*FUNCTION*-------------------------------------------------------------
*
* Function Name  : _io_socket_open
* Returned Value :
* Comments       :
*
*END*-----------------------------------------------------------------*/

_mqx_int _io_socket_open
   (
      MQX_FILE_PTR fd_ptr,
      char _PTR_  open_name_ptr,
      char _PTR_  flags_ptr
   )
{ /* Body */
   IO_SOCKET_PTR io_ptr;

   io_ptr = RTCS_mem_alloc_zero(sizeof(*io_ptr));
   if (io_ptr == NULL) {
      return MQX_OUT_OF_MEMORY;
   } /* Endif */
   
   _mem_set_type(io_ptr, MEM_TYPE_IO_SOCKET);
   
   fd_ptr->DEV_DATA_PTR = io_ptr;

   io_ptr->SOCKET = (uint_32)flags_ptr;

   return MQX_OK;

} /* Endbody */


/*FUNCTION*-------------------------------------------------------------
*
* Function Name  : _io_socket_close
* Returned Value :
* Comments       :
*
*END*-----------------------------------------------------------------*/

_mqx_int _io_socket_close
   (
      MQX_FILE_PTR fd_ptr
   )
{ /* Body */

   if (fd_ptr->DEV_DATA_PTR != NULL) {
      _mem_free(fd_ptr->DEV_DATA_PTR);
      fd_ptr->DEV_DATA_PTR = NULL;
   } /* Endif */

   return MQX_OK;

} /* Endbody */


/*FUNCTION*-------------------------------------------------------------
*
* Function Name  : _io_socket_read
* Returned Value : void
* Comments       :
*
*END*-----------------------------------------------------------------*/

_mqx_int _io_socket_read
   (
      MQX_FILE_PTR fd_ptr,
      char _PTR_  data_ptr,
      _mqx_int    num
   )
{ /* Body */
   IO_SOCKET_PTR io_ptr;

   io_ptr = fd_ptr->DEV_DATA_PTR;
   if (io_ptr != NULL) {
     return (_mqx_int)recv(io_ptr->SOCKET, data_ptr, num, 0);
   } /* Endif */

   return -1;

} /* Endbody */


/*FUNCTION*-------------------------------------------------------------
*
* Function Name  : _io_socket_write
* Returned Value : void
* Comments       :
*
*END*-----------------------------------------------------------------*/

_mqx_int _io_socket_write
   (
      MQX_FILE_PTR fd_ptr,
      char _PTR_  data_ptr,
      _mqx_int    num
   )
{ /* Body */
   IO_SOCKET_PTR io_ptr;

   io_ptr = fd_ptr->DEV_DATA_PTR;
   if (io_ptr != NULL) {
      return (_mqx_int)send(io_ptr->SOCKET, data_ptr, num, 0);
   } /* Endif */

   return 0;

} /* Endbody */


/*FUNCTION*-------------------------------------------------------------
*
* Function Name  : _io_socket_ioctl
* Returned Value : void
* Comments       :
*
*END*-----------------------------------------------------------------*/

_mqx_int _io_socket_ioctl
   (
      MQX_FILE_PTR fd_ptr,
      _mqx_uint   cmd,
      pointer     param_ptr
   )
{ /* Body */
   IO_SOCKET_PTR  io_ptr;
   _mqx_int       result = IO_ERROR;

   io_ptr = fd_ptr->DEV_DATA_PTR;
   if ((io_ptr != NULL) && (cmd == IO_IOCTL_CHAR_AVAIL)) {
      result = MQX_OK;
      if (RTCS_selectset(&io_ptr->SOCKET, 1, (uint_32)-1)) {
         *(boolean _PTR_)param_ptr = TRUE;
      } else {
         *(boolean _PTR_)param_ptr = FALSE;
      } /* Endif */
   } /* Endif */

   return result;

} /* Endbody */


/* EOF */
