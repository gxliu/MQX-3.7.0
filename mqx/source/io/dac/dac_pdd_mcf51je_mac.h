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
* $FileName: dac_pdd_mcf51je_mac.h$
* $Version : 3.7.2.0$
* $Date    : Feb-7-2011$
*
* Comments:
*
*   
*
*END************************************************************************/

#ifndef __dac_pdd_mcf51je_mac_h__
    #define __dac_pdd_mcf51je_mac_h__

#ifdef __cplusplus
extern "C" {
#endif




/* ============================================================================
   ================== General register manipulating routines ==================
   ============================================================================ */


#define setReg8(Reg, val)                                   ((Reg)  = (uint_8)(val))
#define getReg8(Reg)                                        (Reg)
#define testReg8Bits(Reg, GetMask)                          ((Reg) & (uint_8)(GetMask))
#define clrReg8Bits(Reg, ClrMask)                           ((Reg) &= (uint_8)(~(uint_8)(ClrMask)))
#define setReg8Bits(Reg, SetMask)                           ((Reg) |= (uint_8)(SetMask))
#define invertReg8Bits(Reg, InvMask)                        ((Reg) ^= (uint_8)(InvMask))
#define clrSetReg8Bits(Reg, ClrMask, SetMask)               ((Reg)  = (uint_8)(((Reg) & (~(uint_8)(ClrMask))) | (uint_8)(SetMask)))

#define setReg16(Reg, val)                                  ((Reg)  = (uint_16)(val))
#define getReg16(Reg)                                       (Reg)
#define testReg16Bits(Reg, GetMask)                         ((Reg) & (uint_16)(GetMask))
#define clrReg16Bits(Reg, ClrMask)                          ((Reg) &= (uint_16)(~(uint_16)(ClrMask)))
#define setReg16Bits(Reg, SetMask)                          ((Reg) |= (uint_16)(SetMask))
#define invertReg16Bits(Reg, InvMask)                       ((Reg) ^= (uint_16)(InvMask))
#define clrSetReg16Bits(Reg, ClrMask, SetMask)              ((Reg)  = (uint_16)(((Reg) & (uint_16)((~(uint_16)(ClrMask))) | (uint_16)(SetMask))))

#define setReg32(Reg, val)                                  ((Reg)  = (uint_32)(val))
#define getReg32(Reg)                                       (Reg)
#define testReg32Bits(Reg, GetMask)                         ((Reg) & (uint_32)(GetMask))
#define clrReg32Bits(Reg, ClrMask)                          ((Reg) &= (uint_32)(~(uint_32)(ClrMask)))
#define setReg32Bits(Reg, SetMask)                          ((Reg) |= (uint_32)(SetMask))
#define invertReg32Bits(Reg, InvMask)                       ((Reg) ^= (uint_32)(InvMask))
#define clrSetReg32Bits(Reg, ClrMask, SetMask)              ((Reg)  = (uint_32)(((Reg) & (~(uint_32)(ClrMask))) | (uint_32)(SetMask)))




/* PDD macro definitions */
#define DAC_PDD_EnableDevice(BaseAddr) ( \
    setReg8Bits(DAC_C0_REG(BaseAddr),DAC_C0_DACEN_MASK) , \
    (void)0 \
  )


#define DAC_PDD_DisableDevice(BaseAddr) ( \
    clrReg8Bits(DAC_C0_REG(BaseAddr),DAC_C0_DACEN_MASK) , \
    (void)0 \
  )


#define DAC_PDD_GetDeviceState(BaseAddr) ( \
    ( \
      getReg8(DAC_C0_REG(BaseAddr)) \
      & DAC_C0_DACEN_MASK \
    ) \
  )
  

#define DAC_PDD_EnableInterrupts(BaseAddr,Mask) ( \
    setReg8Bits(DAC_C0_REG(BaseAddr),(Mask)) , \
    (void)0 \
  )


#define DAC_PDD_DisableInterrupts(BaseAddr,Mask) ( \
    clrReg8Bits(DAC_C0_REG(BaseAddr),(Mask)) , \
    (void)0 \
  )


#define DAC_PDD_SetInterruptsMask(BaseAddr,Mask) ( \
    clrSetReg8Bits( \
      DAC_C0_REG(BaseAddr), \
      (DAC_SR_DACBFWMF_MASK | DAC_SR_DACBFRPTF_MASK | DAC_SR_DACBFRPBF_MASK), \
      (Mask)) , \
    (void)0 \
  )

#define DAC_PDD_GetInterruptsMask(BaseAddr) ( \
    ( \
      getReg8(DAC_C0_REG(BaseAddr)) \
      & (uint_8)(DAC_SR_DACBFWMF_MASK | DAC_SR_DACBFRPTF_MASK | DAC_SR_DACBFRPBF_MASK) \
    ) \
  )

#define DAC_PDD_GetInterruptFlags(BaseAddr) ( \
    getReg8(DAC_SR_REG(BaseAddr)) \
  )
  
#define DAC_PDD_ClearInterruptFlags(BaseAddr,Mask) ( \
    clrReg8Bits(DAC_SR_REG(BaseAddr),(Mask)) , \
    (void)0 \
  )

  
#define DAC_PDD_SetData(BaseAddr,Data,Index) ( \
    setReg16(DAC_DAT_REG(BaseAddr,Index), Data) , \
    (void)0 \
  )  


#define DAC_PDD_EnableBuffer(BaseAddr,EnableDisable) ( \
    ((EnableDisable) ? ( \
      setReg8Bits(DAC_C1_REG(BaseAddr),DAC_C1_DACBFEN_MASK) , \
      (void)0 \
    ) : ( \
      clrReg8Bits(DAC_C1_REG(BaseAddr),DAC_C1_DACBFEN_MASK) , \
      (void)0 \
    )) , \
    (void)0 \
  )


#define DAC_PDD_GetBufferState(BaseAddr) ( \
    ( \
      getReg8(DAC_C1_REG(BaseAddr)) \
      & DAC_C1_DACBFEN_MASK \
    ) \
  )


#define DAC_PDD_SelectTrigger(BaseAddr,Trigger) ( \
    setReg8Bits(DAC_C0_REG(BaseAddr),(Trigger)), \
    (void)0 \
  )


#define DAC_PDD_GetTriggerSource(BaseAddr) ( \
    ( \
      getReg8(DAC_C0_REG(BaseAddr)) \
      & DAC_C0_DACTRGSEL_MASK \
    ) \
  )
  

#define DAC_PDD_SWTrigger(BaseAddr) ( \
    setReg8Bits(DAC_C0_REG(BaseAddr),DAC_C0_DACSWTRG_MASK) , \
    (void)0 \
  )


#define DAC_PDD_SelectBufferMode(BaseAddr,Mode) ( \
    clrSetReg8Bits(DAC_C1_REG(BaseAddr),DAC_C1_DACBFMD_MASK,(Mode)) , \
    (void)0 \
  )


#define DAC_PDD_SetBufferWatermark(BaseAddr,Watermark) ( \
    clrSetReg8Bits(DAC_C1_REG(BaseAddr),DAC_C1_DACBFWM_MASK,(Watermark)) , \
    (void)0 \
  )


#define DAC_PDD_SetBufferReadPointer(BaseAddr,Pointer) ( \
    clrSetReg8Bits( \
      DAC_C2_REG(BaseAddr), \
      DAC_C2_DACBFRP_MASK, \
      ((Pointer) << DAC_C2_DACBFRP_SHIFT) \
    ) , \
    (void)0 \
  )


#define DAC_PDD_GetBufferReadPointer(BaseAddr) ( \
    ( \
      getReg8(DAC_C2_REG(BaseAddr)) \
      & DAC_C2_DACBFRP_MASK \
    ) >> DAC_C2_DACBFRP_SHIFT \
  )


#define DAC_PDD_SetBufferSize(BaseAddr,Limit) ( \
    clrSetReg8Bits(DAC_C2_REG(BaseAddr),DAC_C2_DACBFUP_MASK,(Limit)) , \
    (void)0 \
  )


#define DAC_PDD_GetBufferSize(BaseAddr) ( \
    ( \
      getReg8(DAC_C2_REG(BaseAddr)) \
      & DAC_C2_DACBFUP_MASK \
    ) \
  )


#define DAC_PDD_SelectReference(BaseAddr,Reference) ( \
    setReg8Bits(DAC_C0_REG(BaseAddr),(Reference)) ,   \
    (void)0 \
  )


#ifdef __cplusplus
}
#endif


#endif /* __dac_pdd_mcf51je_mac_h__  */

