#ifndef __cmpc5125_h__
#define __cmpc5125_h__
/**HEADER********************************************************************
* 
* Copyright (c) 2008 Freescale Semiconductor;
* All Rights Reserved
*
* Copyright (c) 2004-2010 Embedded Access Inc.;
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
* $FileName: int_ctrl_mpc5125.h$
* $Version : 3.7.4.0$
* $Date    : Feb-7-2011$
*
* Comments:
*
*   This file contains interrupt definitions for the MPC5125 
*
*END************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*--------------------------------------------------------------------------*/
/*
**                    CONSTANT DEFINITIONS
*/

/* Interrupt level */
typedef uchar _int_level;

/* Interrupt ID numbers */
#define MPC5125_INT_ID_Error                 0  
#define MPC5125_INT_ID_GPT10                 1  
#define MPC5125_INT_ID_GPT11                 2  
#define MPC5125_INT_ID_SDHC2                 3  
#define MPC5125_INT_ID_FEC1                  4  
#define MPC5125_INT_ID_FEC2                  5  
#define MPC5125_INT_ID_NFC                   6  
#define MPC5125_INT_ID_LPC                   7  
#define MPC5125_INT_ID_SDHC1                 8  
#define MPC5125_INT_ID_I2C1                  9  
#define MPC5125_INT_ID_I2C2                  10 
#define MPC5125_INT_ID_I2C3                  11 
#define MPC5125_INT_ID_MSCAN1                12 
#define MPC5125_INT_ID_MSCAN2                13 
#define MPC5125_INT_ID_BDLC                  14 
#define MPC5125_INT_ID_GPT0                  15 
#define MPC5125_INT_ID_GPT1                  16 
#define MPC5125_INT_ID_IRQ1                  17 
#define MPC5125_INT_ID_PSC4                  32 
#define MPC5125_INT_ID_PSC5                  33 
#define MPC5125_INT_ID_PSC6                  34 
#define MPC5125_INT_ID_PSC7                  35 
#define MPC5125_INT_ID_PSC8                  36 
#define MPC5125_INT_ID_PSC9                  37 
#define MPC5125_INT_ID_GPT8                  38 
#define MPC5125_INT_ID_GPT9                  39 
#define MPC5125_INT_ID_FIFOC                 40 
#define MPC5125_INT_ID_USB2OTG1              43 
#define MPC5125_INT_ID_USB2OTG2              44 
#define MPC5125_INT_ID_IRQ0                  48 
#define MPC5125_INT_ID_DIU                   64 
#define MPC5125_INT_ID_DMA2                  65 
#define MPC5125_INT_ID_PSC0                  68 
#define MPC5125_INT_ID_PSC1                  69 
#define MPC5125_INT_ID_PSC2                  70 
#define MPC5125_INT_ID_PSC3                  71 
#define MPC5125_INT_ID_GPT2                  72 
#define MPC5125_INT_ID_GPT3                  73 
#define MPC5125_INT_ID_GPT4                  74 
#define MPC5125_INT_ID_GPT5                  75 
#define MPC5125_INT_ID_GPT6                  76 
#define MPC5125_INT_ID_GPT7                  77 
#define MPC5125_INT_ID_GPIO1                 78 
#define MPC5125_INT_ID_RTC_SEC               79 
#define MPC5125_INT_ID_RTC_ALARM             80 
#define MPC5125_INT_ID_DDR                   81 
#define MPC5125_INT_ID_SBA                   82 
#define MPC5125_INT_ID_PMC                   83 
#define MPC5125_INT_ID_USB2OTG1_WKUP         84 
#define MPC5125_INT_ID_USB2OTG2_WKUP         85 
#define MPC5125_INT_ID_GPIO2                 86 
#define MPC5125_INT_ID_TEMP_105C             87 
#define MPC5125_INT_ID_IIM                   88 
#define MPC5125_INT_ID_PRIOMON               89 
#define MPC5125_INT_ID_MSCAN3                90 
#define MPC5125_INT_ID_MSCAN4                91 
#define MPC5125_INT_ID_GPT12                 92 
#define MPC5125_INT_ID_GPT13                 93 
#define MPC5125_INT_ID_GPT14                 95 
#define MPC5125_INT_ID_GPT15                 95 



#define MPC5125_IPIC_SICFR_MPSA_SPREAD       (0x200000)
#define MPC5125_IPIC_SICFR_MPSB_SPREAD       (0x400000)
#define MPC5125_IPIC_SICFR_IPSA_SPREAD       (0x10000)
#define MPC5125_IPIC_SICFR_IPSB_SPREAD       (0x20000)
#define MPC5125_IPIC_SICFR_IPSC_SPREAD       (0x40000)
#define MPC5125_IPIC_SICFR_IPSD_SPREAD       (0x80000)

/* SIVCR - Global Interrupt Vector Register bit definitions */
#define MPC5125_IPIC_SIVCR_IVEC_MASK        (0x0000007F)


/*
** Interrupt Group defintions 
*/

/* Group IDs */
// TBD - arbitrary???
#define MPC5125_IPIC_INT_GID_SYSA   (0x0)
#define MPC5125_IPIC_INT_GID_SYSB   (0x1)
#define MPC5125_IPIC_INT_GID_SYSC   (0x2)
#define MPC5125_IPIC_INT_GID_SYSD   (0x3)
#define MPC5125_IPIC_INT_GID_MIXA   (0x10)
#define MPC5125_IPIC_INT_GID_MIXB   (0x11)

/* Group Type */
#define MPC5125_IPIC_INT_GTYPE_GROUP  (0)
#define MPC5125_IPIC_INT_GTYPE_SPREAD (1)

/* System Interrupts Priority Group A */
#define MPC5125_IPIC_SYSA_PSC4        (0)
#define MPC5125_IPIC_SYSA_PSC5        (1)
#define MPC5125_IPIC_SYSA_PSC6        (2)
#define MPC5125_IPIC_SYSA_PSC7        (3)
#define MPC5125_IPIC_SYSA_PSC8        (4)
#define MPC5125_IPIC_SYSA_PSC9        (5)
#define MPC5125_IPIC_SYSA_GPT8        (6)
#define MPC5125_IPIC_SYSA_GPT9        (7)

/* System Interrupts Priority Group B */
#define MPC5125_IPIC_SYSB_FIFOC       (0)
#define MPC5125_IPIC_SYSB_RSVD0       (1)
#define MPC5125_IPIC_SYSB_RSVD1       (2)
#define MPC5125_IPIC_SYSB_USBOTG1     (3)
#define MPC5125_IPIC_SYSB_USBOTG2     (4)
#define MPC5125_IPIC_SYSB_RSVD2       (5)
#define MPC5125_IPIC_SYSB_RSVD3       (6)
#define MPC5125_IPIC_SYSB_RSVD4       (7)

/* System Interrupts Priority Group C */
#define MPC5125_IPIC_SYSC_GPT10       (0)
#define MPC5125_IPIC_SYSC_GPT11       (1)
#define MPC5125_IPIC_SYSC_SDHC2       (2)
#define MPC5125_IPIC_SYSC_FEC1        (3)
#define MPC5125_IPIC_SYSC_FEC2        (4)
#define MPC5125_IPIC_SYSC_NFC         (5)
#define MPC5125_IPIC_SYSC_LPC         (6)
#define MPC5125_IPIC_SYSC_SDHC1       (7)

/* System Interrupts Priority Group D */
#define MPC5125_IPIC_SYSD_I2C1        (0)
#define MPC5125_IPIC_SYSD_I2C2        (1)
#define MPC5125_IPIC_SYSD_I2C3        (2)
#define MPC5125_IPIC_SYSD_MSCAN1      (3)
#define MPC5125_IPIC_SYSD_MSCAN2      (4)
#define MPC5125_IPIC_SYSD_BDLC        (5)
#define MPC5125_IPIC_SYSD_GPT0        (6)
#define MPC5125_IPIC_SYSD_GPT1        (7)

/* Mixed Interrupts PriorityGroup A */
#define MPC5125_IPIC_MIXA_DUI         (0)
#define MPC5125_IPIC_MIXA_DMA         (1)
#define MPC5125_IPIC_MIXA_Reserved0   (2)
#define MPC5125_IPIC_MIXA_Reserved1   (3)
#define MPC5125_IPIC_MIXA_IRQ0        (4)
#define MPC5125_IPIC_MIXA_IRQ1        (5)
#define MPC5125_IPIC_MIXA_Reserved2   (6)
#define MPC5125_IPIC_MIXA_Reserved3   (7)

/* Mixed Interrupts Priority Group B */
#define MPC5125_IPIC_MIXB_PCS0        (0)
#define MPC5125_IPIC_MIXB_PCS1        (1)
#define MPC5125_IPIC_MIXB_PCS2        (2)
#define MPC5125_IPIC_MIXB_PCS3        (3)
#define MPC5125_IPIC_MIXB_Reserved0   (4)
#define MPC5125_IPIC_MIXB_Reserved1   (5)
#define MPC5125_IPIC_MIXB_Reserved2   (6)
#define MPC5125_IPIC_MIXB_Reserved3   (7)



/*--------------------------------------------------------------------------*/
/*
**                    DATATYPE DECLARATIONS
*/

typedef struct mpc5125_int_mask_struct {
   
   uint_32    SIMSRH; 
   uint_32    SIMSRL;   
   uint_32    SEMSR;
} MPC5125_INT_MASK_STRUCT;

typedef struct mpc5125_int_group_param_struct 
{
    uchar   GID;     /* SYSA/SYSB/SYSC/SYSD/MIXA/MIXB */
    uchar   GTYPE;   /* GROUPED/SPREAD      */ 
    uint_32 PRIO_LIST[8]; /* Relative prioritis in the 
                             group, 0 - Highest, 7 - Lowest */
} MPC5125_INT_GROUP_PARAM_STRUCT, _PTR_ MPC5125_INT_GROUP_PARAM_STRUCT_PTR;

/*-----------------------------------------------------------------------*/
/*
**                    FUNCTION PROTOTYPES AND GLOBAL EXTERNS
*/
extern MPC5125_INT_GROUP_PARAM_STRUCT mpc5125_int_group_sysa_param_list;
extern MPC5125_INT_GROUP_PARAM_STRUCT mpc5125_int_group_sysb_param_list;
extern MPC5125_INT_GROUP_PARAM_STRUCT mpc5125_int_group_sysc_param_list;
extern MPC5125_INT_GROUP_PARAM_STRUCT mpc5125_int_group_sysd_param_list;
extern MPC5125_INT_GROUP_PARAM_STRUCT mpc5125_int_group_mixa_param_list;
extern MPC5125_INT_GROUP_PARAM_STRUCT mpc5125_int_group_mixb_param_list;

extern void _mpc5125_ipic_init(void);
extern void _mpc5125_disable_interrupt(uint_32);
extern void _mpc5125_enable_interrupt(uint_32);
extern void _mpc5125_external_isr(pointer);
extern void _mpc5125_ipic_set_group_prios(pointer);

#ifdef __cplusplus
}
#endif

#endif
/* EOF */

