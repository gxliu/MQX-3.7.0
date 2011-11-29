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
* $FileName: int_ctrl_mpc5125.c$
* $Version : 3.6.2.0$
* $Date    : Jun-4-2010$
*
* Comments:
*
*   Utilities for handling interrupts and priorities
*
*END************************************************************************/

#include "mqx_inc.h"
#include "bsp.h"

/* Vector Numbers are used as indexes to an array of priority masks for each vector. */
/* A mask set is 3 32-bit registers.
/* When an interrupt occurs, the mask saved for that vector is applied. */
/* The original values are saved and restored */


#define MPC5125_MAX_IPIC_INTS        (128)

#define _GET_MIXA_GROUP_INDEX(num,index) \
     if(num < 4) { \
        index = 64 + num; \
     } \
     else if(num == 4) { \
        index = 48; \
     } \
     else { \
        index = 12 + num; \
     }             

#define _GET_MIXB_GROUP_INDEX(num,index) \
     if(num < 4) { \
        index = 68 + num; \
     } \
     else { \
        index = 16 + num; \
     }    

      
#define _GET_SYSA_GROUP_INDEX(num,index)  index=32+num
#define _GET_SYSB_GROUP_INDEX(num,index)  index=40+num
#define _GET_SYSC_GROUP_INDEX(num,index)  index=1+num
#define _GET_SYSD_GROUP_INDEX(num,index)  index=9+num


#define _GET_MIXA0_NUM(num)   num = (ipic_ptr->SMPRRA >> 29) & 0x07
#define _GET_MIXA1_NUM(num)   num = (ipic_ptr->SMPRRA >> 26) & 0x07
#define _GET_MIXA2_NUM(num)   num = (ipic_ptr->SMPRRA >> 23) & 0x07
#define _GET_MIXA3_NUM(num)   num = (ipic_ptr->SMPRRA >> 20) & 0x07
#define _GET_MIXA4_NUM(num)   num = (ipic_ptr->SMPRRA >> 13) & 0x07
#define _GET_MIXA5_NUM(num)   num = (ipic_ptr->SMPRRA >> 10) & 0x07
#define _GET_MIXA6_NUM(num)   num = (ipic_ptr->SMPRRA >>  7) & 0x07
#define _GET_MIXA7_NUM(num)   num = (ipic_ptr->SMPRRA >>  4) & 0x07

#define _GET_MIXB0_NUM(num)   num = (ipic_ptr->SMPRRB >> 29) & 0x07
#define _GET_MIXB1_NUM(num)   num = (ipic_ptr->SMPRRB >> 26) & 0x07
#define _GET_MIXB2_NUM(num)   num = (ipic_ptr->SMPRRB >> 23) & 0x07
#define _GET_MIXB3_NUM(num)   num = (ipic_ptr->SMPRRB >> 20) & 0x07
#define _GET_MIXB4_NUM(num)   num = (ipic_ptr->SMPRRB >> 13) & 0x07
#define _GET_MIXB5_NUM(num)   num = (ipic_ptr->SMPRRB >> 10) & 0x07
#define _GET_MIXB6_NUM(num)   num = (ipic_ptr->SMPRRB >>  7) & 0x07
#define _GET_MIXB7_NUM(num)   num = (ipic_ptr->SMPRRB >>  4) & 0x07

#define _GET_SYSA0_NUM(num)   num = (ipic_ptr->SIPRRA >> 29) & 0x07
#define _GET_SYSA1_NUM(num)   num = (ipic_ptr->SIPRRA >> 26) & 0x07
#define _GET_SYSA2_NUM(num)   num = (ipic_ptr->SIPRRA >> 23) & 0x07
#define _GET_SYSA3_NUM(num)   num = (ipic_ptr->SIPRRA >> 20) & 0x07
#define _GET_SYSA4_NUM(num)   num = (ipic_ptr->SIPRRA >> 13) & 0x07
#define _GET_SYSA5_NUM(num)   num = (ipic_ptr->SIPRRA >> 10) & 0x07
#define _GET_SYSA6_NUM(num)   num = (ipic_ptr->SIPRRA >>  7) & 0x07
#define _GET_SYSA7_NUM(num)   num = (ipic_ptr->SIPRRA >>  4) & 0x07

#define _GET_SYSB0_NUM(num)   num = (ipic_ptr->SIPRRB >> 29) & 0x07
#define _GET_SYSB1_NUM(num)   num = (ipic_ptr->SIPRRB >> 26) & 0x07
#define _GET_SYSB2_NUM(num)   num = (ipic_ptr->SIPRRB >> 23) & 0x07
#define _GET_SYSB3_NUM(num)   num = (ipic_ptr->SIPRRB >> 20) & 0x07
#define _GET_SYSB4_NUM(num)   num = (ipic_ptr->SIPRRB >> 13) & 0x07
#define _GET_SYSB5_NUM(num)   num = (ipic_ptr->SIPRRB >> 10) & 0x07
#define _GET_SYSB6_NUM(num)   num = (ipic_ptr->SIPRRB >>  7) & 0x07
#define _GET_SYSB7_NUM(num)   num = (ipic_ptr->SIPRRB >>  4) & 0x07

#define _GET_SYSC0_NUM(num)   num = (ipic_ptr->SIPRRC >> 29) & 0x07
#define _GET_SYSC1_NUM(num)   num = (ipic_ptr->SIPRRC >> 26) & 0x07
#define _GET_SYSC2_NUM(num)   num = (ipic_ptr->SIPRRC >> 23) & 0x07
#define _GET_SYSC3_NUM(num)   num = (ipic_ptr->SIPRRC >> 20) & 0x07
#define _GET_SYSC4_NUM(num)   num = (ipic_ptr->SIPRRC >> 13) & 0x07
#define _GET_SYSC5_NUM(num)   num = (ipic_ptr->SIPRRC >> 10) & 0x07
#define _GET_SYSC6_NUM(num)   num = (ipic_ptr->SIPRRC >>  7) & 0x07
#define _GET_SYSC7_NUM(num)   num = (ipic_ptr->SIPRRC >>  4) & 0x07

#define _GET_SYSD0_NUM(num)   num = (ipic_ptr->SIPRRD >> 29) & 0x07
#define _GET_SYSD1_NUM(num)   num = (ipic_ptr->SIPRRD >> 26) & 0x07
#define _GET_SYSD2_NUM(num)   num = (ipic_ptr->SIPRRD >> 23) & 0x07
#define _GET_SYSD3_NUM(num)   num = (ipic_ptr->SIPRRD >> 20) & 0x07
#define _GET_SYSD4_NUM(num)   num = (ipic_ptr->SIPRRD >> 13) & 0x07
#define _GET_SYSD5_NUM(num)   num = (ipic_ptr->SIPRRD >> 10) & 0x07
#define _GET_SYSD6_NUM(num)   num = (ipic_ptr->SIPRRD >>  7) & 0x07
#define _GET_SYSD7_NUM(num)   num = (ipic_ptr->SIPRRD >>  4) & 0x07

#define _SET_INT_MASK_TABLE_ENTRY(index,inum) \
   if(inum < 17) { \
      mpc5125_int_mask_table[index].SIMSRH |= (0x80000000 >> (15 + inum)); \
   } \
   else if(inum < 32) { \
      mpc5125_int_mask_table[index].SEMSR |= (0x80000000 >> (inum - 16)); \
   } \
   else if(inum < 48) { \
      mpc5125_int_mask_table[index].SIMSRH |= (0x80000000 >> (inum - 32)); \
   } \
   else if(inum == 48) { \
      mpc5125_int_mask_table[index].SEMSR |= (0x80000000); \
   } \
   else if(inum < 64) { \
   } \
   else if(inum < 96) { \
      mpc5125_int_mask_table[index].SIMSRL |= (0x80000000 >> (inum - 64)); \
   }

#define _COPY_OLD_INT_MASK_TABLE_ENTRY(index,oldindex) \
   mpc5125_int_mask_table[index].SIMSRH = mpc5125_int_mask_table[oldindex].SIMSRH; \
   mpc5125_int_mask_table[index].SIMSRL = mpc5125_int_mask_table[oldindex].SIMSRL; \
   mpc5125_int_mask_table[index].SEMSR = mpc5125_int_mask_table[oldindex].SEMSR;
        
#define CHECK_INT_ID(intid) { \
   oldindex = index;\
   index = intid;\
   _COPY_OLD_INT_MASK_TABLE_ENTRY(index,oldindex);          \
   _SET_INT_MASK_TABLE_ENTRY(index,oldindex);}
        
        
#define CHECK_INT(intsrc,intnum) { \
      oldindex = index; \
    _GET_ ## intsrc ## intnum ## _NUM(num); \
      _GET_ ## intsrc ## _GROUP_INDEX(num,index);    \
      _COPY_OLD_INT_MASK_TABLE_ENTRY(index,oldindex);      \
      _SET_INT_MASK_TABLE_ENTRY(index,oldindex);  }
      
        
#define CHECK_INT_IF(c,intsrc,intnum)       {if (c) {CHECK_INT(intsrc,intnum)}  }
      

MPC5125_INT_MASK_STRUCT mpc5125_int_mask_table[MPC5125_MAX_IPIC_INTS];


/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _mpc5125_ipic_set_group_prios_internal
* Returned Value   : none
* Comments         :
*    Sets relative priorities in a group and updates mask table
*
*END*------------------------------------------------------------------------*/
static void _mpc5125_ipic_set_group_prios_internal
   (
      /* [IN] pointer to Interrupt group parameter structure */
      pointer param
      
   )
{ 
   MPC5125_INT_GROUP_PARAM_STRUCT_PTR   param_ptr = param;
   MPC5125_IPIC_STRUCT_PTR              ipic_ptr = MPC5125_IPIC_ADDR();
   
   switch (param_ptr->GID) {
    
      case MPC5125_IPIC_INT_GID_SYSA :
         ipic_ptr->SIPRRA = (param_ptr->PRIO_LIST[0] << 29) |
                            (param_ptr->PRIO_LIST[1] << 26) |
                            (param_ptr->PRIO_LIST[2] << 23) |
                            (param_ptr->PRIO_LIST[3] << 20) |
                            (param_ptr->PRIO_LIST[4] << 13) |
                            (param_ptr->PRIO_LIST[5] << 10) |
                            (param_ptr->PRIO_LIST[6] <<  7) |
                            (param_ptr->PRIO_LIST[7] <<  4); 
         if(param_ptr->GTYPE == MPC5125_IPIC_INT_GTYPE_GROUP) {
            ipic_ptr->SICFR &= ~MPC5125_IPIC_SICFR_IPSA_SPREAD;
         }
         else {
            ipic_ptr->SICFR |= MPC5125_IPIC_SICFR_IPSA_SPREAD;
         }
         break;

      case MPC5125_IPIC_INT_GID_SYSB :
         ipic_ptr->SIPRRB = (param_ptr->PRIO_LIST[0] << 29) |
                            (param_ptr->PRIO_LIST[1] << 26) |
                            (param_ptr->PRIO_LIST[2] << 23) |
                            (param_ptr->PRIO_LIST[3] << 20) |
                            (param_ptr->PRIO_LIST[4] << 13) |
                            (param_ptr->PRIO_LIST[5] << 10) |
                            (param_ptr->PRIO_LIST[6] <<  7) |
                            (param_ptr->PRIO_LIST[7] <<  4); 
         if(param_ptr->GTYPE == MPC5125_IPIC_INT_GTYPE_GROUP) {
            ipic_ptr->SICFR &= ~MPC5125_IPIC_SICFR_IPSB_SPREAD;
         }
         else {
            ipic_ptr->SICFR |= MPC5125_IPIC_SICFR_IPSB_SPREAD;
         }
         break;

      case MPC5125_IPIC_INT_GID_SYSC :
         ipic_ptr->SIPRRC = (param_ptr->PRIO_LIST[0] << 29) |
                            (param_ptr->PRIO_LIST[1] << 26) |
                            (param_ptr->PRIO_LIST[2] << 23) |
                            (param_ptr->PRIO_LIST[3] << 20) |
                            (param_ptr->PRIO_LIST[4] << 13) |
                            (param_ptr->PRIO_LIST[5] << 10) |
                            (param_ptr->PRIO_LIST[6] <<  7) |
                            (param_ptr->PRIO_LIST[7] <<  4); 
         if(param_ptr->GTYPE == MPC5125_IPIC_INT_GTYPE_GROUP) {
            ipic_ptr->SICFR &= ~MPC5125_IPIC_SICFR_IPSC_SPREAD;
         }
         else {
            ipic_ptr->SICFR |= MPC5125_IPIC_SICFR_IPSC_SPREAD;
         }
         break;

      case MPC5125_IPIC_INT_GID_SYSD :
         ipic_ptr->SIPRRD = (param_ptr->PRIO_LIST[0] << 29) |
                            (param_ptr->PRIO_LIST[1] << 26) |
                            (param_ptr->PRIO_LIST[2] << 23) |
                            (param_ptr->PRIO_LIST[3] << 20) |
                            (param_ptr->PRIO_LIST[4] << 13) |
                            (param_ptr->PRIO_LIST[5] << 10) |
                            (param_ptr->PRIO_LIST[6] <<  7) |
                            (param_ptr->PRIO_LIST[7] <<  4); 
         if(param_ptr->GTYPE == MPC5125_IPIC_INT_GTYPE_GROUP) {
            ipic_ptr->SICFR &= ~MPC5125_IPIC_SICFR_IPSD_SPREAD;
         }
         else {
            ipic_ptr->SICFR |= MPC5125_IPIC_SICFR_IPSD_SPREAD;
         }
         break;

      case MPC5125_IPIC_INT_GID_MIXA :
         ipic_ptr->SMPRRA = (param_ptr->PRIO_LIST[0] << 29) |
                            (param_ptr->PRIO_LIST[1] << 26) |
                            (param_ptr->PRIO_LIST[2] << 23) |
                            (param_ptr->PRIO_LIST[3] << 20) |
                            (param_ptr->PRIO_LIST[4] << 13) |
                            (param_ptr->PRIO_LIST[5] << 10) |
                            (param_ptr->PRIO_LIST[6] <<  7) |
                            (param_ptr->PRIO_LIST[7] <<  4); 
         if(param_ptr->GTYPE == MPC5125_IPIC_INT_GTYPE_GROUP) {
            ipic_ptr->SICFR &= ~MPC5125_IPIC_SICFR_MPSA_SPREAD;
         }
         else {
            ipic_ptr->SICFR |= MPC5125_IPIC_SICFR_MPSA_SPREAD;
         }
         break;

      case MPC5125_IPIC_INT_GID_MIXB :
         ipic_ptr->SMPRRB = (param_ptr->PRIO_LIST[0] << 29) |
                            (param_ptr->PRIO_LIST[1] << 26) |
                            (param_ptr->PRIO_LIST[2] << 23) |
                            (param_ptr->PRIO_LIST[3] << 20) |
                            (param_ptr->PRIO_LIST[4] << 13) |
                            (param_ptr->PRIO_LIST[5] << 10) |
                            (param_ptr->PRIO_LIST[6] <<  7) |
                            (param_ptr->PRIO_LIST[7] <<  4); 
         if(param_ptr->GTYPE == MPC5125_IPIC_INT_GTYPE_GROUP) {
            ipic_ptr->SICFR &= ~MPC5125_IPIC_SICFR_MPSB_SPREAD;
         }
         else {
            ipic_ptr->SICFR |= MPC5125_IPIC_SICFR_MPSB_SPREAD;
         }
         break;
         
   } /* Endswitch */

   _int_enable();
} 

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _mpc5125_update_int_mask_table
* Returned Value   : none
* Comments         :
*    Updates interrupt mask table. This table is going to be used by 
*    mpc5125_external_isr to handle nested interrupts
*
*END*------------------------------------------------------------------------*/
static void _mpc5125_update_int_mask_table
   (
      void
   )
{
   MPC5125_IPIC_STRUCT_PTR              ipic_ptr = MPC5125_IPIC_ADDR();
   uint_32                              sicfg;
   uint_32                              num, index, oldindex;
   uchar                                sysaspread = 0, sysbspread = 0, syscspread = 0, sysdspread = 0;
   uchar                                mixaspread = 0, mixbspread = 0;

  
   sicfg = ipic_ptr->SICFR;
   
   /* Get the Priority scheme */
   sysaspread = (sicfg & MPC5125_IPIC_SICFR_IPSA_SPREAD) ? 1 : 0;
   sysbspread = (sicfg & MPC5125_IPIC_SICFR_IPSB_SPREAD) ? 1 : 0;
   syscspread = (sicfg & MPC5125_IPIC_SICFR_IPSC_SPREAD) ? 1 : 0;
   sysdspread = (sicfg & MPC5125_IPIC_SICFR_IPSD_SPREAD) ? 1 : 0;
   mixaspread = (sicfg & MPC5125_IPIC_SICFR_MPSA_SPREAD) ? 1 : 0;
   mixbspread = (sicfg & MPC5125_IPIC_SICFR_MPSB_SPREAD) ? 1 : 0;

   _mem_zero(mpc5125_int_mask_table, sizeof(mpc5125_int_mask_table));

   /* Interrupts masks are created in priority order */
   /* The order depends on each groups Priority scheme */
   /* It is dynamic, so the masks may need to be rebuilt often */

   /* Except for the user specified Highest Priority Int, the source at MIXA0 is the highest priority int */
   /* Who is number 2 depends on the combination of group priority schemes. */
   
   /* This code determines the priority order and builds a masking table. */
   /* For each priority level it determines the interrupt source and vector (index) */
   /* copies the higher priorities 3 register mask and appends that sources mask bit to its mask */
   
    _GET_MIXA0_NUM(num);                       /* find our source */
    _GET_MIXA_GROUP_INDEX(num,index);          /* establish our vector */          

   /* Find the next highest level and so on */
   
   if(!mixaspread) {
      CHECK_INT(MIXA,1);
      CHECK_INT(MIXA,2);
      CHECK_INT(MIXA,3);
   }
   
   CHECK_INT_IF(mixbspread,MIXB,0);

   if(!sysbspread) {
      CHECK_INT(SYSB,0);
      CHECK_INT(SYSB,1);
      CHECK_INT(SYSB,2);
      CHECK_INT(SYSB,3);
   } 

   CHECK_INT_IF(mixaspread,MIXA,1);

   if(!sysbspread) {
      CHECK_INT(SYSB,4);
      CHECK_INT(SYSB,5);
      CHECK_INT(SYSB,6);
      CHECK_INT(SYSB,7);
   }
      
   if(mixbspread) {
      CHECK_INT(MIXB,1);
   } else {
      CHECK_INT(MIXB,0);
      CHECK_INT(MIXB,1);
      CHECK_INT(MIXB,2);
      CHECK_INT(MIXB,3);
   } 
   
   if(!sysaspread) {
      CHECK_INT(SYSA,0);
      CHECK_INT(SYSA,1);
      CHECK_INT(SYSA,2);
      CHECK_INT(SYSA,3);
   } 
   
   CHECK_INT_IF(mixaspread,MIXA,2);
   
   if(!sysaspread) {
      CHECK_INT(SYSA,4);
      CHECK_INT(SYSA,5);
      CHECK_INT(SYSA,6);
      CHECK_INT(SYSA,7);
   } 

   if(!mixaspread) {
      CHECK_INT(MIXA,4);
      CHECK_INT(MIXA,5);
      CHECK_INT(MIXA,6);
      CHECK_INT(MIXA,7);
   } 
    
   CHECK_INT_IF(mixbspread,MIXB,2);

    if(!syscspread) {
      CHECK_INT(SYSC,0);
      CHECK_INT(SYSC,1);
      CHECK_INT(SYSC,2);
      CHECK_INT(SYSC,3);
    } 

   CHECK_INT_IF(mixaspread,MIXA,3);
   
   if(!syscspread) {
      CHECK_INT(SYSC,4);
      CHECK_INT(SYSC,5);
      CHECK_INT(SYSC,6);
      CHECK_INT(SYSC,7);
    } 
   
   if(mixbspread) {
      CHECK_INT(MIXB,3);
   } else {
      CHECK_INT(MIXB,4);
      CHECK_INT(MIXB,5);
      CHECK_INT(MIXB,6);
      CHECK_INT(MIXB,7);
   } 
   
   if(!sysdspread) {
      CHECK_INT(SYSD,0);
      CHECK_INT(SYSD,1);
      CHECK_INT(SYSD,2);
      CHECK_INT(SYSD,3);
   } 
   
   CHECK_INT_IF(mixaspread,MIXA,4);

   if(!sysdspread) {
      CHECK_INT(SYSD,4);
      CHECK_INT(SYSD,5);
      CHECK_INT(SYSD,6);
      CHECK_INT(SYSD,7);
   } 

   CHECK_INT_IF(mixbspread,MIXB,4);
   CHECK_INT_ID(MPC5125_INT_ID_GPT2);
   CHECK_INT_IF(sysbspread,SYSB,1);
   CHECK_INT_IF(sysaspread,SYSA,1);
   CHECK_INT_ID(MPC5125_INT_ID_GPT3);
   CHECK_INT_IF(syscspread,SYSC,1);
   CHECK_INT_IF(sysdspread,SYSD,0);
   CHECK_INT_ID(MPC5125_INT_ID_GPT4);
   CHECK_INT_IF(mixaspread,MIXA,5);
   CHECK_INT_ID(MPC5125_INT_ID_GPT5);
   CHECK_INT_IF(sysbspread,SYSB,1);
   CHECK_INT_IF(sysaspread,SYSA,1);
   CHECK_INT_ID(MPC5125_INT_ID_GPT6);
   CHECK_INT_IF(syscspread,SYSC,1);
   CHECK_INT_IF(sysdspread,SYSD,1);
   CHECK_INT_ID(MPC5125_INT_ID_GPT7);
   CHECK_INT_IF(mixbspread,MIXB,5);
   CHECK_INT_ID(MPC5125_INT_ID_GPIO1);
   CHECK_INT_IF(sysbspread,SYSB,2);
   CHECK_INT_IF(sysaspread,SYSA,2);
   CHECK_INT_ID(MPC5125_INT_ID_RTC_SEC);
   CHECK_INT_IF(syscspread,SYSC,2);
   CHECK_INT_IF(sysdspread,SYSD,2);
   CHECK_INT_ID(MPC5125_INT_ID_RTC_ALARM);
   CHECK_INT_IF(mixaspread,MIXA,6);
   CHECK_INT_ID(MPC5125_INT_ID_DDR);
   CHECK_INT_IF(sysbspread,SYSB,3);
   CHECK_INT_IF(sysaspread,SYSA,3);
   CHECK_INT_ID(MPC5125_INT_ID_SBA);
   CHECK_INT_IF(syscspread,SYSC,3);
   CHECK_INT_IF(sysdspread,SYSD,3);
   CHECK_INT_ID(MPC5125_INT_ID_PMC);
   CHECK_INT_IF(mixbspread,MIXB,6);
   CHECK_INT_ID(MPC5125_INT_ID_USB2OTG1_WKUP);
   CHECK_INT_IF(sysbspread,SYSB,4);
   CHECK_INT_IF(sysaspread,SYSA,4);
   CHECK_INT_ID(MPC5125_INT_ID_USB2OTG2_WKUP);
   CHECK_INT_IF(syscspread,SYSC,4);
   CHECK_INT_IF(sysdspread,SYSD,4);
   CHECK_INT_ID(MPC5125_INT_ID_GPIO2);
   CHECK_INT_IF(mixaspread,MIXA,7);
   CHECK_INT_ID(MPC5125_INT_ID_TEMP_105C);
   CHECK_INT_IF(sysbspread,SYSB,5);
   CHECK_INT_IF(sysaspread,SYSA,5);
   CHECK_INT_ID(MPC5125_INT_ID_IIM);
   CHECK_INT_IF(syscspread,SYSC,5);
   CHECK_INT_IF(sysdspread,SYSD,5);
   CHECK_INT_ID(MPC5125_INT_ID_PRIOMON);
   CHECK_INT_IF(mixbspread,MIXB,7);
   CHECK_INT_ID(MPC5125_INT_ID_MSCAN3);
   CHECK_INT_IF(sysbspread,SYSB,6);
   CHECK_INT_IF(sysaspread,SYSA,6);
   CHECK_INT_ID(MPC5125_INT_ID_MSCAN4);
   CHECK_INT_IF(syscspread,SYSC,6);
   CHECK_INT_IF(sysdspread,SYSD,6);
   CHECK_INT_ID(MPC5125_INT_ID_GPT12);
   CHECK_INT_ID(MPC5125_INT_ID_GPT13);
   CHECK_INT_IF(sysbspread,SYSB,7);
   CHECK_INT_IF(sysaspread,SYSA,7);
   CHECK_INT_ID(MPC5125_INT_ID_GPT14);
   CHECK_INT_IF(syscspread,SYSC,7);
   CHECK_INT_IF(sysdspread,SYSD,7);
   CHECK_INT_ID(MPC5125_INT_ID_GPT15);
   
} 


/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _mpc5125_ipic_init
* Returned Value   : none
* Comments         :
*    Initializes MPC5125 Integrated Programmable Interrupt Controller
*
*END*------------------------------------------------------------------------*/
void _mpc5125_ipic_init
   (
      void
   )
{ 
   MPC5125_IPIC_STRUCT_PTR              ipic_ptr = MPC5125_IPIC_ADDR();
   
   ipic_ptr->SIMSRH = 0;
   ipic_ptr->SIMSRL = 0;
   ipic_ptr->SEMSR = 0;
   ipic_ptr->SERSR = 0xFFFFFFFF;  /* Clear Error status register */

   _mpc5125_ipic_set_group_prios_internal(&mpc5125_int_group_sysa_param_list);
   _mpc5125_ipic_set_group_prios_internal(&mpc5125_int_group_sysb_param_list);
   _mpc5125_ipic_set_group_prios_internal(&mpc5125_int_group_sysc_param_list);
   _mpc5125_ipic_set_group_prios_internal(&mpc5125_int_group_sysd_param_list);
   _mpc5125_ipic_set_group_prios_internal(&mpc5125_int_group_mixa_param_list);
   _mpc5125_ipic_set_group_prios_internal(&mpc5125_int_group_mixb_param_list);
   _mpc5125_update_int_mask_table();   
}


/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _mpc5125_ipic_set_group_prios
* Returned Value   : none
* Comments         :
*   Dynamically Sets relative priorities in a group and updates mask table
*
*END*------------------------------------------------------------------------*/
void _mpc5125_ipic_set_group_prios
   (
      /* [IN] pointer to Interrupt group parameter structure */
      pointer param
   )
{   _int_disable();   
   
   _mpc5125_ipic_set_group_prios_internal(param);
   _mpc5125_update_int_mask_table();
   
   _int_enable();   
}


/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _mpc5125_enable_interrupt
* Returned Value   : none
* Comments         :
*    Enables an interrupt at IPIC level
*
*END*------------------------------------------------------------------------*/

void _mpc5125_enable_interrupt
   (
      /* [IN] the interrupt vector number */
      uint_32 vector
   )
{
   MPC5125_IPIC_STRUCT_PTR              ipic_ptr = MPC5125_IPIC_ADDR();
   uchar                     inum;                   

   inum = (uchar)(vector - MPC5125_IRQ_BASE_VECTOR);
   
   if(inum < 17) {
      ipic_ptr->SIMSRH |= (0x80000000 >> (15 + inum));
   }
   else if(inum < 32) {
      ipic_ptr->SEMSR |= (0x80000000 >> (inum - 16));
   }
   else if(inum < 48) {
      ipic_ptr->SIMSRH |= (0x80000000 >> (inum - 32));
   }
   else if(inum == 48) {
      ipic_ptr->SEMSR |= (0x80000000);
   }
   else if(inum < 64) {
    // Do nothing
   }
   else if(inum < 96) {
      ipic_ptr->SIMSRL |= (0x80000000 >> (inum - 64));
   }
}


/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _mpc5125_disable_external_interrupt
* Returned Value   : none
* Comments         :
*    Disables an interrupt at IPIC level
*
*END*------------------------------------------------------------------------*/

void _mpc5125_disable_interrupt
   (
      /* [IN] the interrupt vector number */
      uint_32 vector

   )
{
   MPC5125_IPIC_STRUCT_PTR              ipic_ptr = MPC5125_IPIC_ADDR();
   uchar                     inum;                   

   inum = (uchar)(vector - MPC5125_IRQ_BASE_VECTOR);
   
   if(inum < 17) {
      ipic_ptr->SIMSRH &= ~(0x80000000 >> (15 + inum));
   }
   else if(inum < 32) {
      ipic_ptr->SEMSR &= ~(0x80000000 >> (inum - 16));
   }
   else if(inum < 48) {
      ipic_ptr->SIMSRH &= ~(0x80000000 >> (inum - 32));
   }
   else if(inum == 48) {
      ipic_ptr->SEMSR &= ~(0x80000000);
   }
   else if(inum < 64) {
    // Do nothing
   }
   else if(inum < 96) {
      ipic_ptr->SIMSRL &= ~(0x80000000 >> (inum - 64));
   }
}

/*ISR*---------------------------------------------------------------------
*
* Function Name    : _mpc5125_external_isr
* Comments         :
*   This ISR is to be installed into the external interrupt vector
* location in order to capture all external interrupts
*
*END*----------------------------------------------------------------------*/

void _mpc5125_external_isr
   (
      pointer dummy
   )
{ /* Body */
   MPC5125_IPIC_STRUCT_PTR              ipic_ptr = MPC5125_IPIC_ADDR();
   uint_32                   sivec_int_code, vector;
   uint_32                   simsr_h, simsr_l,semsr;

   /* Get the interrupt VECTOR offset */
   sivec_int_code = ipic_ptr->SIVCR & MPC5125_IPIC_SIVCR_IVEC_MASK;
   
   vector = sivec_int_code + MPC5125_IRQ_BASE_VECTOR;

   /* save the original interrupt masks */      
   simsr_h = ipic_ptr->SIMSRH;
   simsr_l = ipic_ptr->SIMSRL;
   semsr = ipic_ptr->SEMSR;

   ipic_ptr->SIMSRH = simsr_h & mpc5125_int_mask_table[sivec_int_code].SIMSRH;
   ipic_ptr->SIMSRL = simsr_l & mpc5125_int_mask_table[sivec_int_code].SIMSRL;
   ipic_ptr->SEMSR = semsr & mpc5125_int_mask_table[sivec_int_code].SEMSR;

   /* dummy read needed to avert hardware race */
   ipic_ptr->SIMSRH;
   
   /* allow the core to service interrupts */
   _PSP_SET_SR (_PSP_GET_SR() | PSP_MSR_EE);

   /* invoke the interrupt service routine associated with the interrupt code */
   _PSP_GENERATE_INTERRUPT(vector);

   /* prevent the core from servicing interrupts */
   _PSP_SET_SR (_PSP_GET_SR() & ~PSP_MSR_EE);

   /* restore the original interrupt masks */
   ipic_ptr->SIMSRH = simsr_h;
   ipic_ptr->SIMSRL = simsr_l;
   ipic_ptr->SEMSR = semsr;
}

/* EOF */
