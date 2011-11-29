#ifndef __mpc5125_usb_h__
#define __mpc5125_usb_h__
/**HEADER********************************************************************
* 
* Copyright (c) 2008 Freescale Semiconductor;
* All Rights Reserved
*
* Copyright (c) 2004-2008 Embedded Access Inc.;
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
* $FileName: mpc512x_usb.h$
* $Version :  3.7.3.0$
* $Date    :  Feb-7-2011$
*
* Comments:
*
*   This file contains definitions for the MPC5125 family and peripherals.
*
*END************************************************************************/

#define MCF5XXX_USBOTG_GPTIMER_REPEAT       (0x01000000)
#define MCF5XXX_USBOTG_GPTIMER_RESET        (0x40000000)
#define MCF5XXX_USBOTG_GPTIMER_RUN          (0x80000000)
#define MPC512X_USB_ULPIVIEWPORT_WU         (0x01 << 31)
#define MPC512X_USB_ULPIVIEWPORT_RUN        (0x01 << 30)
#define MPC512X_USB_ULPIVIEWPORT_RW         (0x01 << 29)
#define MPC512X_USB_ULPIVIEWPORT_PORT(x)    ((x&0x07 ) << 24)
#define MPC512X_USB_ULPIVIEWPORT_ADDR(x)    ((x&0xFF) << 16)
#define MPC512X_USB_ULPIVIEWPORT_DATWR(x)   (x&0xFF)

// NOT IMPLEMENTED YET
typedef volatile struct mpc5125_usb_struct
{   

   // Module Identification Registers
    uint_32 ID;             // Identification Register
    uint_32 HWGENERAL;      // General Hardware Parameters
    uint_32 HWHOST;         // Host Hardware Parameters
    uint_32 HWDEVICE;       // Device Hardware Parameters
    uint_32 HWTXBUF;        // TX Buffer Hardware Parameters
    uint_32 HWRXBUF;        // RX Buffer Hardware Parameters
    
    RESERVED_REGISTER(0x18,0x80); 

    uint_32 GPTIMER0LD;     // General Purpose Timer 0 Load
    uint_32 GPTIMER0CTL;    // General Purpose Timer 0 Control
    uint_32 GPTIMER1LD;     // General Purpose Timer 1 Load
    uint_32 GPTIMER1CTL;    // General Purpose Timer 1 Control
    uint_32 SBUSCFG;
    RESERVED_REGISTER(0x94,0x100); 
    
    uint_32 CAPLENGTH;
    uint_32 HCSPARAMS;      /* Host Structural Parameters  */   
    uint_32 HCCPARAMS;      /* Host Capability Parameters  */
    RESERVED_REGISTER(0x10C,0x120);
    uint_32 DCIVERSION;     /*Device Interface Version Number */
    uint_32 DCCPARAMS;      /* Device Capability Parameters  */
    RESERVED_REGISTER(0x128,0x140); 
   
    uint_32 USBCMD;         /* USB Command */
    uint_32 USBSTS;         /* USB Status */
    uint_32 USBINTR;        /* USB Interrupt Enable */
    uint_32 FRINDEX;        /*  USB Frame Index */
    RESERVED_REGISTER(0x150,0x154);
    union
    {
    uint_32 PERIODICLISTBASE;   /* Periodic Frame List Base Address */
    uint_32 DEVICEADDR;     // Device Address
    };
    union
    {
    uint_32 ASYNCLISTADDR;  // Current Asynchronous List Address
    uint_32 EPLISTADDR;     // Address at Endpoint List
    };
    uint_32 TTCTRL;         // Host TT Asynchronous Buffer Control
    uint_32 BURSTSIZE;      // Master Interface Data Burst Size
    uint_32 TXFILLTUNING;   // Host Transmit FIFO Tuning Control
    RESERVED_REGISTER(0x168,0x170);
    uint_32 ULPI_VIEWPORT;  // ULPI control register
    RESERVED_REGISTER(0x174,0x178);

    uint_32 ENDPTNAK;
    uint_32 ENDPTNAKEN;
    uint_32 CONFIGFLAG;     // Configure Flag Register
    uint_32 PORTSC0;        // Port Status/Control
    uint_32 PORTSC1;        // Port Status/Control
    RESERVED_REGISTER(0x18C,0x1A4);
    uint_32 OTGSC;          // On-The-Go Status and Control
    uint_32 MODE;           // USB Mode Register
    uint_32 EPSETUPSR;      // Endpoint Setup Status Register
    uint_32 EPPRIME;        // Endpoint Initialization
    uint_32 EPFLUSH;        // Endpoint De-initialize
    uint_32 EPSR;           // Endpoint Status Register
    uint_32 EPCOMPLETE;     // Endpoint Complete
    uint_32 EPCR0;          // Endpoint Control Register 0
    uint_32 EPCR1;          // Endpoint Control Register 1
    uint_32 EPCR2;          // Endpoint Control Register 2
    uint_32 EPCR3;          // Endpoint Control Register 3
    RESERVED_REGISTER(0x1D0,0x200);
    uint_32 USBGENCTRL;
  
   RESERVED_REGISTER(0x204,0x400);
 
} MPC5125_USB_STRUCT, _PTR_ MPC5125USB_STRUCT_PTR;



#endif