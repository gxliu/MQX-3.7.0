#ifndef __sdhc_prv_h__ 
#define __sdhc_prv_h__
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
* $FileName: sdhc_prv.h$
* $Version : 3.7.2.0$
* $Date    : Feb-7-2011$
*
* Comments:
*
*   This file contains definitions private to the sdhc driver.
*
*END************************************************************************/

#include "sdhc.h"

/*--------------------------------------------------------------------------*/
/*
**                    CONSTANT DEFINITIONS
*/

#define IO_SDHC_ATTRIBS (IO_DEV_ATTR_READ | IO_DEV_ATTR_REMOVE | IO_DEV_ATTR_SEEK | IO_DEV_ATTR_WRITE | IO_DEV_ATTR_BLOCK_MODE)



/*--------------------------------------------------------------------------*/
/*
**                    DATATYPE DECLARATIONS
*/

   
/*--------------------------------------------------------------------------*/
/* 
**                        FUNCTION PROTOTYPES
*/ 

#ifdef __cplusplus
extern "C" {
#endif

extern _mqx_int _sdhc_open (MQX_FILE_PTR, char_ptr, char_ptr);
extern _mqx_int _sdhc_close (MQX_FILE_PTR);
extern _mqx_int _sdhc_read (MQX_FILE_PTR, char_ptr, int_32);
extern _mqx_int _sdhc_write (MQX_FILE_PTR, char_ptr, int_32);
extern _mqx_int _sdhc_ioctl (MQX_FILE_PTR, uint_32, pointer);
extern _mqx_int _sdhc_uninstall (IO_DEVICE_STRUCT_PTR);

#ifdef __cplusplus
}
#endif
      
#endif
/* EOF */
