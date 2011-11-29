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
* $FileName: template_list.h$
* $Version : 3.5.2.0$
* $Date    : Jan-13-2010$
*
* Comments:
*
*   This file contains the source for the ADC example program.
*   Two channels are running, one is running in loop, the second one
*   only once.
*
*END************************************************************************/

#ifndef __TEMPLATE_LIST_H__
    #define __TEMPLATE_LIST_H__



/* Task IDs */
#define ADC_TASK        5
#define IO_TASK         6
#define DISPLAY_TASK    7


/* Task Function prototypes */
extern void adc_task(uint_32);
extern void io_task(uint_32);
extern void display_task(uint_32);


extern const TASK_TEMPLATE_STRUCT MQX_template_list[];


#endif __TEMPLATE_LIST_H__