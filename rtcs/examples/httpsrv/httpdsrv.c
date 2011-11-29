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
* $FileName: httpdsrv.c$
* $Version : 3.7.32.1$
* $Date    : Apr-1-2011$
*
* Comments:
*
*   Example HTTP server using RTCS Library.
*
*END************************************************************************/

#include <mqx.h>
#include <bsp.h>
#include <rtcs.h>

#include "httpd.h"
#include "httpdsrv.h"
#include "tfs.h"
#include "cgi.h"
#include "enet_wifi.h"
#include "config.h"

#include <select.h>

#if DEMOCFG_USE_WIFI
#include "iwcfg.h"
#include "string.h"
#endif

#define HTTPD_SEPARATE_TASK     0


#define ADC_USED_CHANNELS       1



#if ENABLE_ADC
#include "adc.h"
#endif

#if ! BSPCFG_ENABLE_IO_SUBSYSTEM
#error This application requires BSPCFG_ENABLE_IO_SUBSYSTEM defined non-zero in user_config.h. Please recompile BSP with this option.
#endif


#ifndef BSP_DEFAULT_IO_CHANNEL_DEFINED
#error This application requires BSP_DEFAULT_IO_CHANNEL to be not NULL. Please set corresponding BSPCFG_ENABLE_TTYx to non-zero in user_config.h and recompile BSP with this option.
#endif


#ifndef MQX_DEVICE
#define MQX_DEVICE BSP_DEFAULT_IO_CHANNEL
#endif

void main_task(uint_32);

/*
** MQX initialization information
*/

const TASK_TEMPLATE_STRUCT  MQX_template_list[] = 
{
   /* Task Index,   Function,   Stack,  Priority,   Name,    Attributes,          Param, Time Slice */
    { 1,            main_task,  2500,   8,          "Main",  MQX_AUTO_START_TASK, 0,     0 },
    { 0 }
};

const HTTPD_ROOT_DIR_STRUCT root_dir[] = {
    { "", "tfs:" },
    { 0, 0 }
};

#if ENABLE_ADC
const ADC_INIT_STRUCT adc_init = {
    ADC_RESOLUTION_DEFAULT,
};

const ADC_INIT_CHANNEL_STRUCT adc_channel_param[ADC_CHANNELS] = {
    { ADC_SOURCE0, ADC_CHANNEL_MEASURE_LOOP | ADC_CHANNEL_START_NOW, 10, 100000, 100000, 0x10000, 1, MY_TRIGGER, NULL },   
};

MQX_FILE_PTR adc_main_fd;
MQX_FILE_PTR adc_fd[ADC_CHANNELS];

#endif

MQX_FILE_PTR output_port = NULL;

#define SES_MAX     4

/*TASK*-----------------------------------------------------------------
*
* Function Name  : main_task
* Returned Value : void
* Comments       :
*
*END------------------------------------------------------------------*/
void main_task(uint_32 temp) {
    int_32            error;
    _enet_handle      ehandle;
    _rtcs_if_handle   ihandle;
    _enet_address     address;
    HTTPD_STRUCT *server;
    extern const HTTPD_CGI_LINK_STRUCT cgi_lnk_tbl[];
    extern const TFS_DIR_ENTRY tfs_data[];
    HTTPD_PARAMS_STRUCT *params;
#if  DEMOCFG_USE_WIFI   
    ENET_ESSID  ssid;
    uint_32 mode;// = DEMOCFG_NW_MODE;
    uint_32 sectype;// = DEMOCFG_SECURITY;
    ENET_MEDIACTL_PARAM param;
    
#endif    
    //ENET_MEDIACTL_PARAM encode_param;

#if BSPCFG_ENABLE_GPIODEV
    const uint_32 output_set[] = {
        LED_1 | GPIO_PIN_STATUS_0,
        LED_2 | GPIO_PIN_STATUS_0,
        LED_3 | GPIO_PIN_STATUS_0,
        LED_4 | GPIO_PIN_STATUS_0,
        GPIO_LIST_END
    };
#endif    

    /* Open and set port TC as output to drive LEDs (LED10 - LED13) */
#if BSPCFG_ENABLE_GPIODEV
    output_port = fopen("gpio:write", (char_ptr) &output_set);
#endif        

#if ENABLE_ADC
    
    adc_main_fd = fopen(MY_ADC, (const char*)&adc_init);
    
    if (adc_main_fd) {
        _mqx_int i;
        printf("adc device opened\n");
    
        for (i = 0; i < ADC_USED_CHANNELS; i++) {
            char dev_name[6];
            sprintf(dev_name, "adc:%i", i);
        
            adc_fd[i] = fopen(MY_ADC":adc1", (pointer)&adc_channel_param[i]);
        
            if (adc_fd[i] != NULL)
            {
               printf("%s device opened\n", MY_ADC, i);
            }
            else
            {
                printf("%s device open failed !\n", MY_ADC, i);
            }
        }
    }
    else {
        printf("adc device open failed !\n");
    }
    
#endif /* ENABLE_ADC */

#if RTCS_MINIMUM_FOOTPRINT
    /* We are running on a memory constrained device, lower RTCS's defaults */
        
#if PSP_MQX_CPU_IS_MCF5223X
    /* runtime RTCS configuration for small memory <32kB*/
    _RTCSPCB_init = 3;
    _RTCSPCB_grow = 0;
    _RTCSPCB_max = 3;
    _RTCS_msgpool_init = 3;
    _RTCS_msgpool_grow = 0;
    _RTCS_msgpool_max  = 3;
    _RTCS_socket_part_init = 2;
    _RTCS_socket_part_grow = 1;
    _RTCS_socket_part_max  = 6;
#else
    /* runtime RTCS configuration */
    _RTCSPCB_init = 4;
    _RTCSPCB_grow = 2;
    _RTCSPCB_max = 6;
    _RTCS_msgpool_init = 4;
    _RTCS_msgpool_grow = 2;
    _RTCS_msgpool_max  = 8;
    _RTCS_socket_part_init = 4;
    _RTCS_socket_part_grow = 2;
    _RTCS_socket_part_max  = 6;
#endif    
    
    _RTCSTASK_stacksize = 2200;
    
#endif /* RTCS_MINIMUM_FOOTPRINT */
    error = RTCS_create();

    ENET_get_mac_address(DEMOCFG_DEFAULT_DEVICE, ENET_IPADDR, address);
    error = ENET_initialize(DEMOCFG_DEFAULT_DEVICE, address, 0, &ehandle);
#if DEMOCFG_USE_WIFI
    ssid.flags = 1;
    ssid.essid = DEMOCFG_SSID;
    ssid.length = strlen(DEMOCFG_SSID);
    error = ENET_mediactl (ehandle,ENET_SET_MEDIACTL_ESSID,&ssid);
   
    if (strcmp(DEMOCFG_SECURITY,"wpa") == 0)
    {
       param.data = DEMOCFG_PASSPHRASE;
       param.length = strlen(DEMOCFG_PASSPHRASE);
       error = ENET_mediactl (ehandle,ENET_SET_MEDIACTL_PASSPHRASE,&param);
       sectype = ENET_MEDIACTL_SECURITY_TYPE_WPA;
    }
    else if (strcmp(DEMOCFG_SECURITY,"wpa2") == 0)
    {
       param.data = DEMOCFG_PASSPHRASE;
       param.length = strlen(DEMOCFG_PASSPHRASE);
       error = ENET_mediactl (ehandle,ENET_SET_MEDIACTL_PASSPHRASE,&param);
       sectype = ENET_MEDIACTL_SECURITY_TYPE_WPA2;
    }
    else if (strcmp(DEMOCFG_SECURITY,"wep") == 0)
    {
       param.data = DEMOCFG_WEP_KEY;
       param.length = strlen(DEMOCFG_WEP_KEY);
       param.flags = ENET_MEDIACTL_ENCODE_ENABLED;
       param.flags |= (DEMOCFG_WEP_KEY_INDEX & 0xFF); 
       error = ENET_mediactl (ehandle,ENET_SET_MEDIACTL_ENCODE,&param);
       sectype = ENET_MEDIACTL_SECURITY_TYPE_WEP;
    }
    else if (strcmp(DEMOCFG_SECURITY,"none") == 0)
    {
       sectype = ENET_MEDIACTL_SECURITY_TYPE_NONE;  
    }
    else
    {
       printf ("security type not supported\n");
       ENET_shutdown(ehandle);
       return;  
    }
        
        
    error = ENET_mediactl (ehandle,ENET_SET_MEDIACTL_SEC_TYPE,&sectype);
    
    if (strcmp(DEMOCFG_NW_MODE,"managed") == 0)
    {
        mode = ENET_MEDIACTL_MODE_INFRA;
    }
    else if (strcmp(DEMOCFG_NW_MODE,"adhoc") == 0)
    {
      mode = ENET_MEDIACTL_MODE_ADHOC;
    }
    else
    {
       printf("Network mode not supported\n");
       ENET_shutdown(ehandle);
       return;
    }
    error = ENET_mediactl (ehandle,ENET_SET_MEDIACTL_SCAN,0);
#endif  
    
    error = RTCS_if_add(ehandle, RTCS_IF_ENET, &ihandle);
    error = RTCS_if_bind(ihandle, ENET_IPADDR, ENET_IPMASK);
        
    error = _io_tfs_install("tfs:", tfs_data);
    
    
    printf("preparing http server...\n");
    
    params = httpd_default_params(NULL);
    if (params) {
        params->root_dir = (HTTPD_ROOT_DIR_STRUCT*)root_dir;
        params->index_page = "\\index.html";

#if PSP_MQX_CPU_IS_MCF5223X
        params->max_ses = 1;
#endif
        params->max_ses = _RTCS_socket_part_max - 1;

        server = httpd_init(params);
    }

    HTTPD_SET_PARAM_CGI_TBL(server, (HTTPD_CGI_LINK_STRUCT*)cgi_lnk_tbl);

    printf("run http server...\n");
#if HTTPD_SEPARATE_TASK || !HTTPDCFG_POLL_MODE    
    httpd_server_run(server);
    
    
    /* user stuff come here */

    _task_block();
#else    
    while (1) {
        httpd_server_poll(server, 1);
        
        /* user stuff come here - only non blocking calls */
    }
#endif
}
