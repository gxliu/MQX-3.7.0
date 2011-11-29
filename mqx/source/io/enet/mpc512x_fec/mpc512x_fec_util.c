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
* $FileName: mpc512x_fec_util.c$
* $Version : 3.6.2.0$
* $Date    : Jun-4-2010$
*
* Comments:
*
*   This file contains the MPC512x processor
*   Ethernet initialization
*
*END************************************************************************/

#include "mqx.h"
#include "bsp.h"
#include "enetprv.h"
#include "mpc512x_fec_prv.h"          


/*NOTIFIER*-------------------------------------------------------------
*
*  Function Name  : MPC512X_FEC_ISR
*  Returned Value : void
*  Comments       :
*        Interrupt service routine for FEC.
*
*END*-----------------------------------------------------------------*/

void MPC512X_FEC_ISR 
   (
         /* [IN] the Ethernet state structure */
      pointer  enet
   )
{    
   ENET_CONTEXT_STRUCT_PTR          enet_ptr = (ENET_CONTEXT_STRUCT_PTR)enet;
   MPC512X_FEC_CONTEXT_STRUCT_PTR   fec_context_ptr = (MPC512X_FEC_CONTEXT_STRUCT_PTR) enet_ptr->MAC_CONTEXT_PTR;
   VMPC512X_FEC_STRUCT_PTR          fec_ptr= fec_context_ptr->FEC_ADDRESS;
   uint_32                          events;

   if (fec_ptr == NULL) return;
   
   events = fec_ptr->EIR;
   while (events & (MPC512X_FEC_EIR_TXF | MPC512X_FEC_EIR_TXB | MPC512X_FEC_EIR_RXF | MPC512X_FEC_EIR_RXB)) {

      if (events & (MPC512X_FEC_EIR_TXB | MPC512X_FEC_EIR_TXF)) {
         /* clear the TX interrupt */
         fec_ptr->EIR = MPC512X_FEC_EIR_TXB | MPC512X_FEC_EIR_TXF;
         MPC512X_FEC_process_tx_bds(enet_ptr);
      }

      if (events & (MPC512X_FEC_EIR_RXF | MPC512X_FEC_EIR_RXB)) {

         /* clear the RX interrupt */
         fec_ptr->EIR = (MPC512X_FEC_EIR_RXF | MPC512X_FEC_EIR_RXB); 
         MPC512X_FEC_process_rx_bds(enet_ptr);
      }
      
      events = fec_ptr->EIR;
   } 
} 


/*FUNCTION*-------------------------------------------------------------
*
*  Function Name  : MPC512X_FEC_install_isrs
*  Returned Value :  
*  Comments       :
*        
*
*END*-----------------------------------------------------------------*/

boolean MPC512X_FEC_install_isrs( ENET_CONTEXT_STRUCT_PTR enet_ptr  ) 
{
   uint_32  vector = MPC512X_FEC_get_vector(enet_ptr->PARAM_PTR->ENET_IF->MAC_NUMBER, 0);
 
#if BSPCFG_ENET_RESTORE
   MPC512X_FEC_CONTEXT_STRUCT_PTR    fec_context_ptr = (MPC512X_FEC_CONTEXT_STRUCT_PTR) enet_ptr->MAC_CONTEXT_PTR;

   // Save old ISR and data
   fec_context_ptr->OLDISR_PTR[0]   = _int_get_isr(vector);
   fec_context_ptr->OLDISR_DATA[0] = _int_get_isr_data(vector);
#endif

   if (_int_install_isr(vector, MPC512X_FEC_ISR, (pointer)enet_ptr)==NULL) {
      return FALSE;
   }

   /* Enable Ethernet Interrupt at IPIC level  */
   _mpc5125_enable_interrupt(vector);

   return TRUE;
}

/*FUNCTION*-------------------------------------------------------------
*
*  Function Name  : MPC512X_FEC_mask_interrupts
*  Returned Value :  
*  Comments       :
*        
*
*END*-----------------------------------------------------------------*/

void MPC512X_FEC_mask_interrupts( ENET_CONTEXT_STRUCT_PTR enet_ptr ) 
{
   _mpc5125_disable_interrupt(MPC512X_FEC_get_vector(enet_ptr->PARAM_PTR->ENET_IF->MAC_NUMBER,0));
}


#if BSPCFG_ENET_RESTORE


/*FUNCTION*-------------------------------------------------------------
*
*  Function Name  : MPC512X_FEC_uninstall_all_isrs
*  Returned Value :  
*  Comments       :
*        
*
*END*-----------------------------------------------------------------*/

void MPC512X_FEC_uninstall_all_isrs( ENET_CONTEXT_STRUCT_PTR enet_ptr ) 
{
   uint_32  vector = MPC512X_FEC_get_vector(enet_ptr->PARAM_PTR->ENET_IF->MAC_NUMBER, 0);
   MPC512X_FEC_CONTEXT_STRUCT_PTR    fec_context_ptr = (MPC512X_FEC_CONTEXT_STRUCT_PTR) enet_ptr->MAC_CONTEXT_PTR;
 
   _mpc5125_disable_interrupt(vector);
   if (fec_context_ptr->OLDISR_PTR[0]) {
      _int_install_isr(vector, fec_context_ptr->OLDISR_PTR[0], fec_context_ptr->OLDISR_DATA[0]);
      fec_context_ptr->OLDISR_PTR[0] = NULL;
   }
}
#endif


/*FUNCTION*-------------------------------------------------------------
* 
* Function Name    : MPC512X_FEC_get_vector
* Returned Value   : MQX vector number for specified interrupt
* Comments         :
*    This function returns index into MQX interrupt vector table for
*    specified enet interrupt. If not known, returns 0.
*
*END*-----------------------------------------------------------------*/


uint_32 MPC512X_FEC_get_vector 
(
    uint_32 device,
    uint_32 vector_index
)
{ 
    uint_32 vector = 0;

    if (device < MPC512X_FEC_DEVICE_COUNT) {
      vector = MPC512X_FEC_vectors[device];
    }

    return vector;
} 


/*FUNCTION*-------------------------------------------------------------
*
*  Function Name  : MPC512X_FEC_free_context
*  Returned Value :  
*  Comments       :
*        
*
*END*-----------------------------------------------------------------*/

void MPC512X_FEC_free_context( MPC512X_FEC_CONTEXT_STRUCT_PTR fec_context_ptr ) 
{
   if (fec_context_ptr) {
      if (fec_context_ptr->UNALIGNED_BUFFERS) {
         _mem_free((pointer)fec_context_ptr->UNALIGNED_BUFFERS);
      }
      if (fec_context_ptr->RX_PCB_BASE) {
         _mem_free((pointer)fec_context_ptr->RX_PCB_BASE);
      }
      if (fec_context_ptr->TxPCBS_PTR) {
         _mem_free((pointer)fec_context_ptr->TxPCBS_PTR);
      }
      if (fec_context_ptr->UNALIGNED_RING_PTR) {
         _mem_free((pointer)fec_context_ptr->UNALIGNED_RING_PTR);
      }
   
      _mem_free((pointer)fec_context_ptr);
   }
}




/* EOF */
