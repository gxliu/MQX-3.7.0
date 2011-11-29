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
* $FileName: init_sci1.c$
* $Version : 3.6.3.0$
* $Date    : Jun-15-2010$
*
* Comments:
*
*   This file contains the definition for the baud rate for the serial
*   channel
*
*END************************************************************************/

#include "mqx.h"
#include "bsp.h"

const MCF51XX_SCI_INIT_STRUCT _bsp_sci1_init = {
   /* queue size         */ BSPCFG_SCI1_QUEUE_SIZE,
   /* Channel            */ MCF51XX_SCI1,
   /* Clock Speed        */ BSP_BUS_CLOCK,
   /* SCI1C1 Value       */ 0,
   /* SCI1C2 Value       */ 0,
   /* SCI1C3 Value       */ 0,
   /* Baud rate          */ BSPCFG_SCI1_BAUD_RATE,
   /* RX Interrupt vect  */ MCF51JM_INT_Vsci2rx,
   /* TX Interrupt vect  */ MCF51JM_INT_Vsci2tx,
   /* ER Interrupt vect  */ MCF51JM_INT_Vsci2err
};

/* EOF */
