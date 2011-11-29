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
* $FileName: mpc512x_fec.c$
* $Version : 3.6.2.0$
* $Date    : Jun-4-2010$
*
* Comments:
*
*   Processor family specific file needed for enet module.
*   Revision History:
*   Date             Version  Changes
*   ---------        -------  -------
*   Sep 26/08        2.50     Initial version
*
*END************************************************************************/

#include <mqx.h>
#include <bsp.h>
#include <enet.h>
#include <enetprv.h>
#include <mpc512x_fec_prv.h>


const uint_32 MPC512X_FEC_vectors[MPC512X_FEC_DEVICE_COUNT] = {MPC5125_FEC1_VECTOR,MPC5125_FEC2_VECTOR};

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : MPC512X_FEC_get_base_address  
* Returned Value   : Pointer to desired enem device or NULL if not present
* Comments         :
*    This function returns pointer to base address of address space of the 
*    desired enet device. Returns NULL otherwise.
*
*END*----------------------------------------------------------------------*/

pointer MPC512X_FEC_get_base_address(uint_32 device) 
{
   VMPC5125_STRUCT_PTR vmpc5125_ptr = (VMPC5125_STRUCT_PTR) MPC5125_GET_IMMR();
   pointer addr = NULL;
   
   switch (device) {
      case MPC5125_FEC0:
         addr = (pointer)&vmpc5125_ptr->FEC1;
         break;
      case MPC5125_FEC1:
         addr = (pointer)&vmpc5125_ptr->FEC2;
         break;
    }
    
    return addr;
}


 
/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : MPC512X_FEC_io_init
* Returned Value   : none
* Comments         :
*    This function performs BSP-specific initialization related to ENET
*
*END*----------------------------------------------------------------------*/

void MPC512X_FEC_io_init( uint_32   device, uint_32 mode )
{

   if (device >= MPC512X_FEC_DEVICE_COUNT) 
      return;

   _bsp_enet_io_init(device, mode);
}
