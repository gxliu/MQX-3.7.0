/**HEADER********************************************************************
* 
* Copyright (c) 2008 Freescale Semiconductor;
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
* $FileName: boot.c$
* $Version : 3.7.2.2$
* $Date    : Apr-1-2011$
*
* Comments:
*
*   Example using RTCS Library.
*
*END************************************************************************/

#include <mqx.h>
#include <bsp.h>
#include <rtcs.h>
#include <shell.h>
#include <sh_rtcs.h>
#include "config.h"
#include "bootstrap.h" 
#include "ipcfg.h"

#if ! BSPCFG_ENABLE_IO_SUBSYSTEM
#error This application requires BSPCFG_ENABLE_IO_SUBSYSTEM defined non-zero in user_config.h. Please recompile BSP with this option.
#endif


#ifndef BSP_DEFAULT_IO_CHANNEL_DEFINED
#error This application requires BSP_DEFAULT_IO_CHANNEL to be not NULL. Please set corresponding BSPCFG_ENABLE_TTYx to non-zero in user_config.h and recompile BSP with this option.
#endif

#if ! BSPCFG_ENABLE_NANDFLASH
#error This application requires BSPCFG_ENABLE_NANDFLASH defined non-zero in user_config.h. Please recompile BSP with this option.
#endif

#define MAIN_TASK 1

extern const SHELL_COMMAND_STRUCT Shell_commands[];
extern void Main_task (uint_32);

/* Global variables */
extern uint_32 _autoboot_cmd;

const TASK_TEMPLATE_STRUCT  MQX_template_list[] = 
{
   /* Task Index,   Function,   Stack,  Priority,   Name,   Attributes,          Param, Time Slice */
    { MAIN_TASK,    Main_task,  8000,   9,          "Main", MQX_AUTO_START_TASK, 0,     0 },
    { 0 }
};


/*FUNCTION*------------------------------------------------
* 
* Function Name: Auto_boot_startup
* Comments     :
*    
*
*END*-----------------------------------------------------*/
void Auto_boot_startup(void) 
{
   int_32  timeout;
   boolean autoboot;
   
   timeout = _bootloader_get_timeout();
   if(timeout<0) {
      printf("\nError can't get kernel image!");
      printf("\nPlease setup your network to take image (.bin file) from TFTP protocol\n");
      return;
   }
   
   printf("\nHit any key to stop autoboot:");
   
   while(0 <= timeout) {
      printf("%2d",timeout);
      if(status()) {
         autoboot = FALSE;
         fflush(stdin);
         break;
      }
      _time_delay(1000);
      
      autoboot = TRUE;
      timeout--;
   }
   
   if(autoboot) {
      if(_bootloader_check_image(TRUE,0)) {
         _autoboot_cmd = AUTOBOOT_ENABLE;
         _mqx_exit(0);
      }
      else {
         printf("\nError no autoboot image found!\n");
         
      }      
   }
   
}

/*TASK*-----------------------------------------------------------------
*
* Task Name      : Main_task
* Returned Value : void
* Comments       :
*
*END------------------------------------------------------------------*/

void Main_task(uint_32 temp)
{
    uint_32           error;
    
    error = RTCS_create();
    if (error != RTCS_OK) 
    {
        printf("\nRTCS failed to initialize, error = %X", error);
        _task_block();
    }

    /* Enable IP forwarding */
    _IP_forward = TRUE;

#ifdef ENET_DEVICE
    IPCFG_default_enet_device = ENET_DEVICE;
    IPCFG_default_ip_address = ENET_IPADDR;
    IPCFG_default_ip_mask = ENET_IPMASK;
    IPCFG_default_ip_gateway = 0;
    ENET_get_mac_address (IPCFG_default_enet_device, IPCFG_default_ip_address, IPCFG_default_enet_address);
#endif

   printf("\nMQX version %s",_mqx_version);
   printf("\nBoot loader application (build: %s)", __DATE__);
   
   /* Initialize Image Table if not exist image */
   _bootloader_init_table();
   
   /* Run the shell */
   Auto_boot_startup();   
   Shell(Shell_commands, NULL);
   for(;;) 
   {
       printf("Shell exited, restarting...\n");
       Shell(Shell_commands, NULL);
   }
}

/* EOF */
