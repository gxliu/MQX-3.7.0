#ifndef __iodun_h__
#define __iodun_h__
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
* $FileName: io_dun.h$
* $Version : 3.7.5.0$
* $Date    : Mar-11-2011$
*
* Comments:
*
*   The file contains functions prototype, defines, structure
*   definitions specific for the DUN and RAS drivers
*
*END************************************************************************/

/***************************************
**
** MQX compatibility
*/

#define _iodun_mutex             LWSEM_STRUCT
#define IODUN_mutex_init(p)      _lwsem_create(p,1)
#define IODUN_mutex_destroy(p)   _lwsem_destroy(p)
#define IODUN_mutex_lock(p)      _lwsem_wait(p)
#define IODUN_mutex_unlock(p)    _lwsem_post(p)

// Start CR 2184
#define IO_IOCTL_SET_LINK_UP        (0x1001)
// End CR 2184

/*--------------------------------------------------------------------*/
/*
**                    TYPE DEFINITIONS
*/

/*
** RAS DEVICE STRUCT
** Must be kept in sync with mqx io_dun.h
*/
/* Start CR 1823 */
typedef struct iodun_dev_struct {
/* End CR 1823 */
   char_ptr     RECV;
   char_ptr     SEND;
// Start CR 2182
   _mqx_uint    RECV_INDEX;
// End CR 2182
} IODUN_DEV_STRUCT, _PTR_ IODUN_DEV_STRUCT_PTR;

/*
** RAS FILE STRUCT
** Must be kept in sync with mqx io_dun.h
*/
/* Start CR 1823 */
typedef struct iodun_struct {
/* End CR 1823 */
   MQX_FILE_PTR   F_PTR;
// Start CR 2182
   _iodun_mutex   MUTEX;
// Start CR 2184
   boolean      LINK_UP;
// End CR 2184
// End CR 2182
} IODUN_STRUCT, _PTR_ IODUN_STRUCT_PTR;


/*--------------------------------------------------------------------*/
/*
**                    FUNCTION PROTOTYPES
*/

#ifdef __cplusplus
extern "C" {
#endif


uint_32 _io_ras_install(char_ptr);
uint_32 _io_dun_install(char_ptr);

extern _mqx_int _io_dun_open      (MQX_FILE_PTR, char_ptr, char_ptr);
extern _mqx_int _io_dun_close     (MQX_FILE_PTR);
extern _mqx_int _io_dun_write     (MQX_FILE_PTR, char_ptr, _mqx_int);
extern _mqx_int _io_dun_read      (MQX_FILE_PTR, char_ptr, _mqx_int);
extern _mqx_int _io_dun_ioctl     (MQX_FILE_PTR, _mqx_uint, pointer);
extern char     _io_dun_read_char (MQX_FILE_PTR);

#ifdef __cplusplus
}
#endif


#endif
/* EOF */
