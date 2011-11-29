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
* $FileName: dac_pdd_mcf51je.h$
* $Version : 3.7.2.0$
* $Date    : Feb-7-2011$
*
* Comments:
*
*   
*
*END************************************************************************/

#ifndef __dac_pdd_mcf51je_h__
    #define __dac_pdd_mcf51je_h__

#ifdef __cplusplus
extern "C" {
#endif


/* ============================================================================
   ================== General PDD macros ======================================
   ============================================================================ */

#define PDD_DISABLE                         0u
#define PDD_ENABLE                          1u

/* PDD constants definitions */
#define DAC_PDD_DISABLE                     0x00u
#define DAC_PDD_ENABLE                      0x80u
#define DAC_PDD_BUFFER_WATERMARK_INT        0x04u
#define DAC_PDD_BUFFER_END_INT              0x02u
#define DAC_PDD_BUFFER_START_INT            0x01u
#define DAC_PDD_HW_TRIGGER                  0x00u
#define DAC_PDD_SW_TRIGGER                  0x20u
#define DAC_PDD_HIGH_POWER                  0x00u
#define DAC_PDD_LOW_POWER                   0x08u
#define DAC_PDD_BUFFER_WATERMARK_L1         0x00u
#define DAC_PDD_BUFFER_WATERMARK_L2         0x08u
#define DAC_PDD_BUFFER_WATERMARK_L3         0x10u
#define DAC_PDD_BUFFER_WATERMARK_L4         0x18u
#define DAC_PDD_BUFFER_NORMAL_MODE          0x00u
#define DAC_PDD_BUFFER_SWING_MODE           0x02u
#define DAC_PDD_BUFFER_OTSCAN_MODE          0x04u
#define DAC_PDD_BUFFER_DISABLE              0x00u
#define DAC_PDD_BUFFER_ENABLE               0x01u
#define DAC_PDD_V_REF_INT                   0x00u
#define DAC_PDD_V_REF_EXT                   0x40u



/*FUNCTION*********************************************************************
* 
* Function Name   : _bsp_get_dac_base_address()
*
* Input Params    : dac_module_number - the number of DAC module
*
* Returned Value  : The DAC module base address
*
* Comments        : 
*
*END**************************************************************************/


DAC_MemMapPtr _bsp_get_dac_base_address(uint_8 dac_module_number);

/*FUNCTION*********************************************************************
* 
* Function Name   : _bsp_get_dac_vector()
*
* Input Params    : dac_module_number - the number of DAC module
*
* Returned Value  : The DAC module interrupt vector number
*
* Comments        : 
*
*END**************************************************************************/

uint_32 _bsp_get_dac_vector(uint_8 dac_module_number);


#ifdef __cplusplus
}
#endif


#endif /* __dac_pdd_mcf51je_h__  */

