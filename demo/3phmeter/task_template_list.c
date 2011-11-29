/**HEADER********************************************************************
* 
* Copyright (c) 2008-2009 Freescale Semiconductor;
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
* $FileName: task_template_list.c$
* $Version : 3.5.4.0$
* $Date    : Jan-15-2010$
*
* Comments:
*
*   This file contains the source for the ADC example program.
*   Two channels are running, one is running in loop, the second one
*   only once.
*
*END************************************************************************/

#include <mqx.h>
#include <bsp.h>
#include "meter_config.h"
#include "task_template_list.h"



const TASK_TEMPLATE_STRUCT MQX_template_list[] =
{
    {
        /* Task Index       */  ADC_TASK, 
        /* Function         */  adc_task,
        /* Stack Size       */  1000,
        /* Priority Level   */  8,
        /* Name             */  "ADC Task",
        /* Attributes       */  MQX_AUTO_START_TASK,
        /* Creation Params  */  0,
        /* Time Slice       */  0,
    },
    {
        /* Task Index       */  IO_TASK, 
        /* Function         */  io_task,
        /* Stack Size       */  300,
        /* Priority Level   */  9,
        /* Name             */  "IO Task",
        /* Attributes       */  MQX_AUTO_START_TASK,
        /* Creation Params  */  0,
        /* Time Slice       */  0,
    },    
    {
        /* Task Index       */  DISPLAY_TASK, 
        /* Function         */  display_task,
        /* Stack Size       */  1000,
        /* Priority Level   */  10,
        /* Name             */  "Display Task",
        /* Attributes       */  MQX_AUTO_START_TASK,
        /* Creation Params  */  0,
        /* Time Slice       */  0,
    },

    { 0 }
};


