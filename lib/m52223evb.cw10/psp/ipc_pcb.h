#ifndef __ipc_pcb_h__
#define __ipc_pcb_h__ 1
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
* $FileName: ipc_pcb.h$
* $Version : 3.0.3.0$
* $Date    : Nov-21-2008$
*
* Comments:
*
*   This file contains the definitions for the 
*   interprocessor drivers that work over IO PCB devices.
*
*END************************************************************************/


/*--------------------------------------------------------------------------*/
/*
**                          CONSTANT DECLARATIONS
*/

/*
** Initialization errors
*/
#define IPC_PCB_PACKET_POOL_CREATE_FAILED     (0x9031)
#define IPC_PCB_INVALID_QUEUE                 (0x9032)
#define IPC_PCB_DEVICE_OPEN_FAILED            (0x9033)
#define IPC_PCB_OUTPUT_PCB_POOL_CREATE_FAILED (0x9034)
#define IPC_PCB_INPUT_PCB_POOL_CREATE_FAILED  (0x9035)

/*--------------------------------------------------------------------------*/
/*
**                          DATATYPE DECLARATIONS
*/

/*
** IPC_PCB_INIT_STRUCT
** This structure contains the initialization information for the
** async_serial protocol
**
*/
typedef struct ipc_pcb_init_struct
{

   /* The string name of the PCB IO Device driver to use */
   char _PTR_            IO_PCB_DEVICE_NAME;

   /*
   ** The function to call to install the IO Device (optional)
   ** If null, the device is not installed.
   */
   _mqx_uint (_CODE_PTR_ DEVICE_INSTALL)(char_ptr, pointer);

   /* The parameter to pass to the IO Device installation function */
   pointer               DEVICE_INSTALL_PARAMETER;
   
   /* 
   ** The following are parameters used to create the 
   ** input pool of messages
   */
   uint_16               IN_MESSAGES_MAX_SIZE;
   uint_16               IN_MESSAGES_TO_ALLOCATE;
   uint_16               IN_MESSAGES_TO_GROW;
   uint_16               IN_MESSAGES_MAX_ALLOCATE;

   /* 
   ** The following are parameters used to create the 
   ** output pool of pcbs.
   */
   uint_16               OUT_PCBS_INITIAL;
   uint_16               OUT_PCBS_TO_GROW;
   uint_16               OUT_PCBS_MAX;

} IPC_PCB_INIT_STRUCT, _PTR_ IPC_PCB_INIT_STRUCT_PTR;

/*--------------------------------------------------------------------------*/
/*
**                          C PROTOTYPES
*/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __TAD_COMPILE__
extern _mqx_uint _ipc_pcb_init(IPC_PROTOCOL_INIT_STRUCT_PTR, pointer);
#endif

#ifdef __cplusplus
}
#endif

#endif
/* EOF */
