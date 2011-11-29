
#ifndef _diu_h_
#define _diu_h_
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
* $FileName: diu.h$
* $Version : 3.6.2.0$
* $Date    : Jun-4-2010$
*
* Comments:
* 
*    This file contains the definitions for the DIU driver.
*
*END***********************************************************************/

#ifdef __cplusplus
extern "C" {
#endif


void diu_set_display_size(MPC5125_DIU_STRUCT_PTR diu_ptr, uint_32 hsize, uint_32 vsize);
void diu_set_timing(
   MPC5125_DIU_STRUCT_PTR diu_ptr, 
   uint_32 bp_h,     uint_32 pw_h,     uint_32 fp_h,  boolean bp_hs, boolean inv_hs,
   uint_32 bp_v,     uint_32 pw_v,     uint_32 fp_v,  boolean bp_vs, boolean inv_vs,      
   boolean inv_cs) ;
void diu_set_mode(MPC5125_DIU_STRUCT_PTR diu_ptr,uint_32 mode);
int diu_init_device(MPC5125_DIU_STRUCT_PTR diu_ptr, DISPLAY_TIMING_PARAM_STRUCT_PTR dtp_ptr);
void diu_set_gamma(MPC5125_DIU_STRUCT_PTR diu_ptr, DIU_GAMMA_PTR gamma_ptr );
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
    uint_32 nextAD);
MPC5125_DIU_AD_STRUCT_PTR diu_ad_set(MPC5125_DIU_STRUCT_PTR diu_ptr, uint_32 plane, MPC5125_DIU_AD_STRUCT_PTR ad_ptr);
uint_32 display_get_hres(DISPLAY_CONTEXT_STRUCT_PTR dc_ptr);
uint_32 display_get_vres(DISPLAY_CONTEXT_STRUCT_PTR dc_ptr);
DISPLAY_PIXEL_BUFFER_PTR display_create_pixel_buffer(uint_32 dx, uint_32 dy, DISPLAY_PIXEL_FORMAT_PTR pf_ptr, uchar_ptr  fb_ptr );
int diu_show_color_bar(void);
int diu_set_color_bar(uint_32 color_bar, uint_32 color);
int diu_print_registers(void);

#ifdef __cplusplus
}
#endif


#endif

