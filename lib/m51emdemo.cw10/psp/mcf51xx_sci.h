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
* $FileName: mcf51xx_sci.h$
* $Version : 3.6.4.0$
* $Date    : Jun-4-2010$
*
* Comments:
*
*   This file contains the definitions of constants and structures
*   required for the sci drivers for the MCF51XX
*
*END************************************************************************/
#ifndef _mcf51xx_sci_h
#define _mcf51xx_sci_h 1

#ifdef __cplusplus
extern "C" {
#endif

/*------------------------------------------------------------------------*/
/*
** SCI Serial Communication Interface
*/

/* SCI1BDH */
#define MCF51XX_SCIBDH_SBR8_MASK           1
#define MCF51XX_SCIBDH_SBR9_MASK           2
#define MCF51XX_SCIBDH_SBR10_MASK          4
#define MCF51XX_SCIBDH_SBR11_MASK          8
#define MCF51XX_SCIBDH_SBR12_MASK          16
#define MCF51XX_SCIBDH_RXEDGIE_MASK        64
#define MCF51XX_SCIBDH_LBKDIE_MASK         128
#define MCF51XX_SCIBDH_SBR_8_MASK          31
#define MCF51XX_SCIBDH_SBR_8_BITNUM        0

/* SCI1BDL */
#define MCF51XX_SCIBDL_SBR0_MASK           1
#define MCF51XX_SCIBDL_SBR1_MASK           2
#define MCF51XX_SCIBDL_SBR2_MASK           4
#define MCF51XX_SCIBDL_SBR3_MASK           8
#define MCF51XX_SCIBDL_SBR4_MASK           16
#define MCF51XX_SCIBDL_SBR5_MASK           32
#define MCF51XX_SCIBDL_SBR6_MASK           64
#define MCF51XX_SCIBDL_SBR7_MASK           128

/* SCI1C1 */
#define MCF51XX_SCIC1_PT_MASK                  1
#define MCF51XX_SCIC1_PE_MASK                  2
#define MCF51XX_SCIC1_ILT_MASK                 4
#define MCF51XX_SCIC1_WAKE_MASK                8
#define MCF51XX_SCIC1_M_MASK                   16
#define MCF51XX_SCIC1_RSRC_MASK                32
#define MCF51XX_SCIC1_SCISWAI_MASK             64
#define MCF51XX_SCIC1_LOOPS_MASK               128

/* SCI1C2 */
#define MCF51XX_SCIC2_SBK_MASK                 1
#define MCF51XX_SCIC2_RWU_MASK                 2
#define MCF51XX_SCIC2_RE_MASK                  4
#define MCF51XX_SCIC2_TE_MASK                  8
#define MCF51XX_SCIC2_ILIE_MASK                16
#define MCF51XX_SCIC2_RIE_MASK                 32
#define MCF51XX_SCIC2_TCIE_MASK                64
#define MCF51XX_SCIC2_TIE_MASK                 128
 
/* SCI1S1 */
#define MCF51XX_SCIS1_PF_MASK                  1
#define MCF51XX_SCIS1_FE_MASK                  2
#define MCF51XX_SCIS1_NF_MASK                  4
#define MCF51XX_SCIS1_OR_MASK                  8
#define MCF51XX_SCIS1_IDLE_MASK                16
#define MCF51XX_SCIS1_RDRF_MASK                32
#define MCF51XX_SCIS1_TC_MASK                  64
#define MCF51XX_SCIS1_TDRE_MASK                128

/* SCI1S2 */
#define MCF51XX_SCIS2_RAF_MASK                 1
#define MCF51XX_SCIS2_LBKDE_MASK               2
#define MCF51XX_SCIS2_BRK13_MASK               4
#define MCF51XX_SCIS2_RWUID_MASK               8
#define MCF51XX_SCIS2_RXINV_MASK               16
#define MCF51XX_SCIS2_RXEDGIF_MASK             64
#define MCF51XX_SCIS2_LBKDIF_MASK              128

/* SCI1C3 */
#define MCF51XX_SCIC3_PEIE_MASK                1
#define MCF51XX_SCIC3_FEIE_MASK                2
#define MCF51XX_SCIC3_NEIE_MASK                4
#define MCF51XX_SCIC3_ORIE_MASK                8
#define MCF51XX_SCIC3_TXINV_MASK               16
#define MCF51XX_SCIC3_TXDIR_MASK               32
#define MCF51XX_SCIC3_T8_MASK                  64
#define MCF51XX_SCIC3_R8_MASK                  128

/* SCI1D */
#define MCF51XX_SCID_R0_T0_MASK                1
#define MCF51XX_SCID_R1_T1_MASK                2
#define MCF51XX_SCID_R2_T2_MASK                4
#define MCF51XX_SCID_R3_T3_MASK                8
#define MCF51XX_SCID_R4_T4_MASK                16
#define MCF51XX_SCID_R5_T5_MASK                32
#define MCF51XX_SCID_R6_T6_MASK                64
#define MCF51XX_SCID_R7_T7_MASK                128

/*
** MCF51XX_SCI_STRUCT
** SCI module
*/
typedef struct MCF51XX_sci_struct
{
    uchar SCIBDH;   /*** SCIBDH - SCIBDH SCI Baud Rate Register; ***/
    uchar SCIBDL;   /*** SCIBDL - SCIBDL SCI Baud Rate Register; ***/
    uchar SCIC1;    /*** SCIC1 - SCIC1 SCI Control Register 1; ***/
    uchar SCIC2;    /*** SCIC2 - SCIC2 SCI Control Register 2; ***/
    uchar SCIS1;    /*** SCIS1 - SCIS1 Status Register 1; ***/
    uchar SCIS2;    /*** SCIS2 - SCIS2 Status Register 2; ***/
    uchar SCIC3;    /*** SCIC3 - SCIC3 Control Register 3; ***/
    uchar SCID;     /*** SCID - SCID SCI1 Data Register; ***/
} MCF51XX_SCI_STRUCT, _PTR_ MCF51XX_SCI_STRUCT_PTR;
typedef volatile struct MCF51XX_sci_struct _PTR_ VMCF51XX_SCI_STRUCT_PTR;

#ifdef __cplusplus
}
#endif

#endif
/* EOF */
