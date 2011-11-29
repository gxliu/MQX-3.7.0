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
* $FileName: mcf5xxx_usbotg.h$
* $Version : 3.7.9.0$
* $Date    : Feb-7-2011$
*
* Comments:
*
*   This file contains the type definitions for the mcf522x usbotg module.
*
*END************************************************************************/

#ifndef __mcf5xxx_usbotg_h__
#define __mcf5xxx_usbotg_h__

#define __mcf5xxx_usbotg_h__version "$Version:3.7.9.0$"
#define __mcf5xxx_usbotg_h__date    "$Date:Feb-7-2011$"

#ifdef __cplusplus
extern "C" {
#endif

/*------------------------------------------------------------------------*/
/*
** USB OTG
*/

/* Bit definitions and macros for OTG_PORTSC1 */
#define MCF5XXX_USBOTG_PORTSC1_PTS      (0xC0000000)
#define MCF5XXX_USBOTG_PORTSC1_PTS_ULPI (0x80000000) /* ULPI interface */
#define MCF5XXX_USBOTG_PORTSC1_PTS_OCT  (0xC0000000) /* on chip transciever */

#define MCF5XXX_USBOTG_PORTSC1_PSPD      (0x0C000000)
#define MCF5XXX_USBOTG_PORTSC1_PSPD_FS   (0x00000000)
#define MCF5XXX_USBOTG_PORTSC1_PSPD_LS   (0x04000000)
#define MCF5XXX_USBOTG_PORTSC1_PSPD_HS   (0x08000000)

#define MCF5XXX_USBOTG_PORTSC1_PFSC      (0x01000000)
#define MCF5XXX_USBOTG_PORTSC1_PHCD      (0x00800000)
#define MCF5XXX_USBOTG_PORTSC1_WKOC      (0x00400000)
#define MCF5XXX_USBOTG_PORTSC1_WKDS      (0x00200000)
#define MCF5XXX_USBOTG_PORTSC1_WLCN      (0x00100000)

#define MCF5XXX_USBOTG_PORTSC1_PTC       (0x000F0000)
#define MCF5XXX_USBOTG_PORTSC1_PTC_NEN   (0x00000000)
#define MCF5XXX_USBOTG_PORTSC1_PTC_J     (0x00010000)
#define MCF5XXX_USBOTG_PORTSC1_PTC_K     (0x00020000)
#define MCF5XXX_USBOTG_PORTSC1_PTC_SEQ_NAK (0x00030000)
#define MCF5XXX_USBOTG_PORTSC1_PTC_PACKET  (0x00040000)
#define MCF5XXX_USBOTG_PORTSC1_PTC_HS    (0x00050000)
#define MCF5XXX_USBOTG_PORTSC1_PTC_FS    (0x00060000)
#define MCF5XXX_USBOTG_PORTSC1_PTC_LS    (0x00070000)

#define MCF5XXX_USBOTG_PORTSC1_PIC       (0x0000C000)
#define MCF5XXX_USBOTG_PORTSC1_PO        (0x00002000)
#define MCF5XXX_USBOTG_PORTSC1_PP        (0x00001000)

#define MCF5XXX_USBOTG_PORTSC1_LS        (0x00000C00)
#define MCF5XXX_USBOTG_PORTSC1_LS_SE0    (0x00000000)
#define MCF5XXX_USBOTG_PORTSC1_LS_J      (0x00000400)
#define MCF5XXX_USBOTG_PORTSC1_LS_K      (0x00000800)

#define MCF5XXX_USBOTG_PORTSC1_HSP       (0x00000200)
#define MCF5XXX_USBOTG_PORTSC1_PR        (0x00000100)

#define MCF5XXX_USBOTG_PORTSC1_SUSP      (0x00000080)
#define MCF5XXX_USBOTG_PORTSC1_FPR       (0x00000040)
#define MCF5XXX_USBOTG_PORTSC1_OCC       (0x00000020)
#define MCF5XXX_USBOTG_PORTSC1_OCA       (0x00000010)
#define MCF5XXX_USBOTG_PORTSC1_PEC       (0x00000008)
#define MCF5XXX_USBOTG_PORTSC1_PE        (0x00000004)
#define MCF5XXX_USBOTG_PORTSC1_CSC       (0x00000002)
#define MCF5XXX_USBOTG_PORTSC1_CCS       (0x00000001)

#define MCF5XXX_USBOTG_GPTIMER_MODE(x)   ((x & 1) << 24)
#define MCF5XXX_USBOTG_GPTIMER_ONESHOT   (0x00000000)
#define MCF5XXX_USBOTG_GPTIMER_REPEAT    (0x01000000)

#define MCF5XXX_USBOTG_GPTIMER_RESET     (0x40000000)

#define MCF5XXX_USBOTG_GPTIMER_RUN       (0x80000000)

/*------------------------------------------------------------------------*/
/*
** MCF5XXX_USBOTG_STRUCT
** USB OTG
*/
typedef struct mcf5xxx_usbotg_struct {
    /* Module Identification Registers */
    uint_32 ID;             /* Identification Register */
    uint_32 HWGENERAL;      /* General Hardware Parameters */
    uint_32 HWHOST;         /* Host Hardware Parameters */
    uint_32 HWDEVICE;       /* Device Hardware Parameters */
    uint_32 HWTXBUF;        /* TX Buffer Hardware Parameters */
    uint_32 HWRXBUF;        /* RX Buffer Hardware Parameters */

    uint_8  filler0[104];
    
    /* Device/Host Timer Registers */
    uint_32 GPTIMER0LD;     /* General Purpose Timer 0 Load */
    uint_32 GPTIMER0CTL;    /* General Purpose Timer 0 Control */
    uint_32 GPTIMER1LD;     /* General Purpose Timer 1 Load */
    uint_32 GPTIMER1CTL;    /* General Purpose Timer 1 Control */

    uint_8  filler1[112];

    /* Capability Registers */
    uint_16 HCIVERSION;     /* Host Interface Version Number */
    uint_8  filler2;
    uint_8  CAPLENGTH;      /* Capability Register Length */
    uint_32 HCSPARAMS;      /* Host Structural Parameters  */
    uint_32 HCCPARAMS;      /* Host Capability Parameters */

    uint_8 filler3[22];

    uint_16 DCIVERSION;     /* Device Interface Version Number */
    uint_32 DCCPARAMS;      /* Device Capability Parameters */

    uint_8 filler4[24];
    
    /* Operational Registers */
    uint_32 USBCMD;         /* USB Command */
    uint_32 USBSTS;         /* USB Status */
    uint_32 USBINTR;        /* USB Interrupt Enable */
    uint_32 FRINDEX;        /* USB Frame Index */
    
    uint_8 filler5[4];
    
    union {
        uint_32 PERIODICLISTBASE;   /* Periodic Frame List Base Address */
        uint_32 DEVICEADDR;         /* Device Address */
    };
    
    union {
        uint_32 ASYNCLISTADDR;  /* Current Asynchronous List Address */
        uint_32 EPLISTADDR;     /* Address at Endpoint List */
    };
    
    uint_32 TTCTRL;         /* Host TT Asynchronous Buffer Control */
    uint_32 BURSTSIZE;      /* Master Interface Data Burst Size */
    uint_32 TXFILLTUNING;   /* Host Transmit FIFO Tuning Control */
    
    uint_8 filler6[8];
    
    uint_32 ULPI_VIEWPORT;  /* ULPI control register */
    
    uint_8 filler7[12];
    
    uint_32 CONFIGFLAG;     /* Configure Flag Register */
    uint_32 PORTSC1;        /* Port Status/Control */
    
    uint_8 filler8[28];
    
    uint_32 OTGSC;          /* On-The-Go Status and Control */
    uint_32 MODE;           /* USB Mode Register */
    uint_32 EPSETUPSR;      /* Endpoint Setup Status Register */
    uint_32 EPPRIME;        /* Endpoint Initialization */
    uint_32 EPFLUSH;        /* Endpoint De-initialize */
    uint_32 EPSR;           /* Endpoint Status Register */
    uint_32 EPCOMPLETE;     /* Endpoint Complete */
    uint_32 EPCR0;          /* Endpoint Control Register 0 */
    uint_32 EPCR1;          /* Endpoint Control Register 1 */
    uint_32 EPCR2;          /* Endpoint Control Register 2 */
    uint_32 EPCR3;          /* Endpoint Control Register 3 */
} MCF5XXX_USBOTG_STRUCT, _PTR_ MCF5XXX_USBOTG_STRUCT_PTR;
typedef volatile struct mcf5xxx_usbotg_struct _PTR_ VMCF5XXX_USBOTG_STRUCT_PTR;

#ifdef __cplusplus
}
#endif


#endif
