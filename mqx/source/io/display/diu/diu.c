/**HEADER********************************************************************
* 
* Copyright (c) 2008-2009 Freescale Semiconductor;
* All Rights Reserved
*
* Copyright (c) 2004-2010 Embedded Access Inc.;
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
* $FileName: diu.c$
* $Version : 3.6.2.0$
* $Date    : Jun-4-2010$
*
* Comments:
* 
*    This file contains the funcions for the DIU driver.
*
*END***********************************************************************/

#include <mqx.h>
#include <bsp.h>
#include <display.h>


extern int _bsp_diu_init(void);




void diu_set_display_size(MPC5125_DIU_STRUCT_PTR diu_ptr, uint_32 hsize, uint_32 vsize)
{
    diu_ptr->DISP_SIZE = 
       ((hsize<<DIU_DISP_SIZE_DELTA_X_SHIFT) & DIU_DISP_SIZE_DELTA_X_MASK) |
       ((vsize<<DIU_DISP_SIZE_DELTA_Y_SHIFT) & DIU_DISP_SIZE_DELTA_Y_MASK) ;
}

void diu_set_timing(
   MPC5125_DIU_STRUCT_PTR diu_ptr, 
   uint_32 bp_h,     uint_32 pw_h,     uint_32 fp_h,  boolean bp_hs, boolean inv_hs,
   uint_32 bp_v,     uint_32 pw_v,     uint_32 fp_v,  boolean bp_vs, boolean inv_vs,      
   boolean inv_cs) 
{
   diu_ptr->HSYN_PARA =
       ((bp_h<<DIU_HSYN_PARA_BP_H_SHIFT) & DIU_HSYN_PARA_BP_H_MASK) |
       ((pw_h<<DIU_HSYN_PARA_PW_H_SHIFT) & DIU_HSYN_PARA_PW_H_MASK) |
       ((fp_h<<DIU_HSYN_PARA_FP_H_SHIFT) & DIU_HSYN_PARA_FP_H_MASK) ;

   diu_ptr->VSYN_PARA =
       ((bp_v<<DIU_VSYN_PARA_BP_V_SHIFT) & DIU_VSYN_PARA_BP_V_MASK) |
       ((pw_v<<DIU_VSYN_PARA_PW_V_SHIFT) & DIU_VSYN_PARA_PW_V_MASK) |
       ((fp_v<<DIU_VSYN_PARA_FP_V_SHIFT) & DIU_VSYN_PARA_FP_V_MASK) ;

   diu_ptr->SYN_POL = 
      (bp_vs ? DIU_SYN_POL_BP_VS_MASK:0)  |
      (bp_hs ? DIU_SYN_POL_BP_HS_MASK:0)  |
      (inv_cs? DIU_SYN_POL_INV_CS_MASK:0) |
      (inv_vs? DIU_SYN_POL_INV_VS_MASK:0) |
      (inv_hs? DIU_SYN_POL_INV_HS_MASK:0) ;
}


void diu_set_mode(MPC5125_DIU_STRUCT_PTR diu_ptr,uint_32 mode)
{
   diu_ptr->DIU_MODE = mode;
} 


int diu_init_device(MPC5125_DIU_STRUCT_PTR diu_ptr, DISPLAY_TIMING_PARAM_STRUCT_PTR dtp_ptr)
{
   uint_32 htot,vtot,tot;
   
    // Set DIU clock divider.
    htot =dtp_ptr->H.Res+dtp_ptr->H.Bp+dtp_ptr->H.Sync+dtp_ptr->H.Fp;
    vtot =dtp_ptr->V.Res+dtp_ptr->V.Bp+dtp_ptr->V.Sync+dtp_ptr->V.Fp;
    tot = htot*vtot*dtp_ptr->Refresh;
   _mpc5125_set_diu_clock(BSP_EXCLK_CLOCK,tot,1,0);
   
    diu_set_mode(diu_ptr, DIU_MODE_OFF);

   _bsp_diu_init();

    // Set up the DIU
    diu_set_display_size(diu_ptr,dtp_ptr->H.Res,dtp_ptr->V.Res);
    
    diu_set_timing(diu_ptr, 
       dtp_ptr->H.Bp, dtp_ptr->H.Sync, dtp_ptr->H.Fp, dtp_ptr->H.Bypass, dtp_ptr->H.Invert,
       dtp_ptr->V.Bp, dtp_ptr->V.Sync, dtp_ptr->V.Fp, dtp_ptr->V.Bypass, dtp_ptr->V.Invert,
       dtp_ptr->InvertComposite);


   diu_ptr->PLUT=0x01F5F666;
   

    return(MQX_OK);
}

void diu_set_gamma(MPC5125_DIU_STRUCT_PTR diu_ptr, DIU_GAMMA_PTR gamma_ptr )
{

   _dcache_flush_mlines((pointer) gamma_ptr, sizeof(*gamma_ptr));

   diu_ptr->GAMMA=(uint_32) gamma_ptr;
}

void diu_set_cursor_image(MPC5125_DIU_STRUCT_PTR diu_ptr, DIU_CURSOR_PTR cursor_ptr )
{

   _dcache_flush_mlines((pointer) cursor_ptr, sizeof(*cursor_ptr));

   diu_ptr->CURSOR=(uint_32) cursor_ptr;
}

void diu_set_cursor_position(MPC5125_DIU_STRUCT_PTR diu_ptr,uint_16 x, uint_16 y )
{

   diu_ptr->CURS_POS=(uint_32) (y&0x7ff)<<16 | (x&0x7ff);
}


static uchar diu_ad_endian_map[] = { 4,4,4,4,4,4,4,4,4,0 };         

void diu_ad_initialize( 
   MPC5125_DIU_AD_STRUCT_PTR ad_ptr, 
   uint_8 bits_comp0, uint_8 bits_comp1, uint_8 bits_comp2, uint_8 bits_comp3, 
   uint_8 bpp, uint_8 palette,
    uint_8 red_c, uint_8 green_c, uint_8 blue_c, uint_8 alpha_c, uint_8 byte_flip, 
    uint_32 data_addr, 
    uint_16 delta_xs,   uint_16 delta_ys, 
    uint_8 g_alpha, 
    uint_16 delta_xi, uint_16 delta_yi, 
    uint_8 flip, 
    uint_16 offset_xi, uint_16 offset_yi,
    uint_16 offset_xd, uint_16 offset_yd, 
    uint_8 ckmax_r, uint_8 ckmax_g, uint_8 ckmax_b, uint_8 ckmin_r, uint_8 ckmin_g, uint_8 ckmin_b, 
    uint_32 nextAD)
{
    ad_ptr->PIXEL_FORMAT   = diu_create_ad_word0(bits_comp0, bits_comp1, bits_comp2, bits_comp3, bpp, palette, red_c, green_c, blue_c, alpha_c, byte_flip);
    ad_ptr->BITMAP_ADDR    = data_addr;
    ad_ptr->SOURCE_SIZE    = diu_create_ad_word2(delta_xs, delta_ys, g_alpha);
    ad_ptr->AOI_SIZE       = diu_create_ad_word3(flip, delta_xi, delta_yi);
    ad_ptr->AOI_OFFSET     = diu_create_ad_word4(offset_xi, offset_yi);
    ad_ptr->DISPLAY_OFFSET = diu_create_ad_word5(offset_xd, offset_yd);
    ad_ptr->CHROMA_KEY_MAX = diu_create_ad_word6(ckmax_r, ckmax_g, ckmax_b);
    ad_ptr->CHROMA_KEY_MIN = diu_create_ad_word7(ckmin_r, ckmin_g, ckmin_b);
    ad_ptr->NEXT_AD        = nextAD;
    ad_ptr->RESERVED_0x24  = 0x00000000;

    _mem_swap_endian(diu_ad_endian_map, (pointer) ad_ptr);
}

MPC5125_DIU_AD_STRUCT_PTR diu_ad_set(MPC5125_DIU_STRUCT_PTR diu_ptr, uint_32 plane, MPC5125_DIU_AD_STRUCT_PTR ad_ptr)
{
   MPC5125_DIU_AD_STRUCT_PTR old_ad_ptr;
   
   if (plane>=DIU_NUM_PLANES) {
      return NULL;
   }

   _dcache_flush_mlines((pointer) ad_ptr, sizeof(*ad_ptr));
   
    old_ad_ptr = (MPC5125_DIU_AD_STRUCT_PTR) diu_ptr->DESC[plane];
    diu_ptr->DESC[plane] =  (uint_32) ad_ptr;
   return old_ad_ptr;
}


int diu_show_color_bar(void)
{
    MPC5125_DIU_STRUCT_PTR diu_ptr = MPC5125_DIU_ADDR();

    // Turn the DIU color bar on.
    diu_set_mode(diu_ptr, DIU_MODE_COLOR_BAR);
}

int diu_set_color_bar(uint_32 color_bar, uint_32 color)
{
    MPC5125_DIU_STRUCT_PTR diu_ptr = MPC5125_DIU_ADDR();
   diu_ptr->COLBAR[color_bar] = color;
}


int diu_print_registers(void)
{
   MPC5125_CCM_STRUCT_PTR ccm_ptr = MPC5125_CCM_ADDR();
    MPC5125_DIU_STRUCT_PTR diu_ptr = MPC5125_DIU_ADDR();
   uint_32 i;
   
   printf("DIU @        0x%x\n", diu_ptr);
   printf("DIU clock    %d\n", _mpc5125_get_diu_clock(BSP_EXCLK_CLOCK));
   printf("DIU_DIV      0x%x\n", GET_FIELD_OF_REG(ccm_ptr,CCM,SCFR1,DIU_DIV));
   printf("DESC_1       0x%x\n", diu_ptr->DESC[DIU_PLANE_1]);
   printf("DESC_2       0x%x\n", diu_ptr->DESC[DIU_PLANE_2]);
   printf("DESC_3       0x%x\n", diu_ptr->DESC[DIU_PLANE_3]);
   printf("GAMMA        0x%x\n", diu_ptr->GAMMA);
   printf("PALETTE      0x%x\n", diu_ptr->PALETTE);
   printf("CURSOR       0x%x\n", diu_ptr->CURSOR);
   printf("CURS_POS     0x%x\n", diu_ptr->CURS_POS);
   printf("DIU_MODE     0x%x\n", diu_ptr->DIU_MODE);
   printf("BGND         0x%x\n", diu_ptr->BGND);
   printf("BGND_WB      0x%x\n", diu_ptr->BGND_WB);
   printf("DISP_SIZE    0x%x\n", diu_ptr->DISP_SIZE);
   printf("WB_SIZE      0x%x\n", diu_ptr->WB_SIZE);
   printf("WB_MEM_ADDR  0x%x\n", diu_ptr->WB_MEM_ADDR);
   printf("HSYN_PARA    0x%x\n", diu_ptr->HSYN_PARA);
   printf("VSYN_PARA    0x%x\n", diu_ptr->VSYN_PARA);
   printf("SYN_POL      0x%x\n", diu_ptr->SYN_POL);
   printf("THRESHOLDS   0x%x\n", diu_ptr->THRESHOLDS);
   printf("INT_STATUS   0x%x\n", diu_ptr->INT_STATUS);
   printf("INT_MASK     0x%x\n", diu_ptr->INT_MASK);
   for (i=0;i<DIU_NUM_COLOR_BARS;i++) {
      printf("COLBAR_%d     0x%x\n", i+1,diu_ptr->COLBAR[i]);
   }
   printf("FILLING      0x%x\n", diu_ptr->FILLING);
   printf("PLUT         0x%x\n", diu_ptr->PLUT);
}



