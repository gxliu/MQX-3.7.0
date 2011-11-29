#ifndef __mpc5125_diu_h__
#define __mpc5125_diu_h__
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
* $FileName: mpc512x_diu.h$
* $Version :  3.6.2.0$
* $Date    :  Jun-4-2010$
*
* Comments:
*
*   This file contains definitions for the MPC5125 family and peripherals.
*
*END************************************************************************/


#define MPC5125_DIU_ADDR()      (&((VMPC5125_STRUCT_PTR) MPC5125_GET_IMMR() )->DIU)

/***************** Register Bit Fields and Values ***************************/
#define DIU_DESC_1_DESC_1_MASK          0xFFFFFFFF      
#define DIU_DESC_1_DESC_1_SHIFT         0

#define DIU_DESC_2_DESC_2_MASK          0xFFFFFFFF      
#define DIU_DESC_2_DESC_2_SHIFT         0

#define DIU_DESC_3_DESC_3_MASK          0xFFFFFFFF      
#define DIU_DESC_3_DESC_3_SHIFT         0

#define DIU_GAMMA_GAMMA_MASK            0xFFFFFFFF       
#define DIU_GAMMA_GAMMA_SHIFT           0

#define DIU_PALETTE_PALETTE_MASK        0xFFFFFFFF      
#define DIU_PALETTE_PALETTE_SHIFT       0

#define DIU_CURSOR_CURSOR_MASK          0xFFFFFFFF      
#define DIU_CURSOR_CURSOR_SHIFT         0

#define DIU_CURS_POS_ALL_MASK           0x07FF07FF      
#define DIU_CURS_POS_CURSOR_X_MASK      0x000007FF      
#define DIU_CURS_POS_CURSOR_X_SHIFT     0
#define DIU_CURS_POS_CURSOR_Y_MASK      0x07FF0000      
#define DIU_CURS_POS_CURSOR_Y_SHIFT     16

#define DIU_DIU_MODE_DIU_MODE_MASK      0x00000007       
#define DIU_DIU_MODE_DIU_MODE_SHIFT     0
#define DIU_DIU_MODE_DIU_MODE_MODE0     0
#define DIU_DIU_MODE_DIU_MODE_MODE1     1
#define DIU_DIU_MODE_DIU_MODE_MODE2     2
#define DIU_DIU_MODE_DIU_MODE_MODE3     3
#define DIU_DIU_MODE_DIU_MODE_MODE4     4

#define DIU_BGND_BGND_RGB_MASK          0x00FFFFFF      
#define DIU_BGND_BGND_RGB_SHIFT         0
#define DIU_BGND_BGND_B_MASK            0x000000FF      
#define DIU_BGND_BGND_B_SHIFT           0
#define DIU_BGND_BGND_G_MASK            0x0000FF00      
#define DIU_BGND_BGND_G_SHIFT           8
#define DIU_BGND_BGND_R_MASK            0x00FF0000      
#define DIU_BGND_BGND_R_SHIFT           16

#define DIU_BGND_WB_BGND_WB_RGB_MASK        0x00FFFFFF      
#define DIU_BGND_WB_BGND_WB_RGB_SHIFT       0
#define DIU_BGND_WB_BGND_WB_B_MASK      0x000000FF      
#define DIU_BGND_WB_BGND_WB_B_SHIFT     0
#define DIU_BGND_WB_BGND_WB_G_MASK      0x0000FF00      
#define DIU_BGND_WB_BGND_WB_G_SHIFT     8
#define DIU_BGND_WB_BGND_WB_R_MASK      0x00FF0000      
#define DIU_BGND_WB_BGND_WB_R_SHIFT     16

#define DIU_DISP_SIZE_ALL_MASK          0x07FF07FF      
#define DIU_DISP_SIZE_DELTA_X_MASK      0x000007FF      
#define DIU_DISP_SIZE_DELTA_X_SHIFT     0
#define DIU_DISP_SIZE_DELTA_Y_MASK      0x07FF0000      
#define DIU_DISP_SIZE_DELTA_Y_SHIFT     16

#define DIU_WB_SIZE_ALL_MASK            0x00007FF       
#define DIU_WB_SIZE_DELTA_X_WB_MASK     0x00007FF       
#define DIU_WB_SIZE_DELTA_X_WB_SHIFT        0
#define DIU_WB_SIZE_DELTA_Y_WB_MASK     0x07FF0000      
#define DIU_WB_SIZE_DELTA_Y_WB_SHIFT        16

#define DIU_WB_MEM_ADDR_WB_MEM_ADDR_MASK    0xFFFFFFFF      
#define DIU_WB_MEM_ADDR_WB_MEM_ADDR_SHIFT   0

#define DIU_HSYN_PARA_ALL_MASK          0xFFDFFBFF      
#define DIU_HSYN_PARA_FP_H_MASK         0x000003FF      
#define DIU_HSYN_PARA_FP_H_SHIFT        0
#define DIU_HSYN_PARA_PW_H_MASK         0x001FF800      
#define DIU_HSYN_PARA_PW_H_SHIFT        11
#define DIU_HSYN_PARA_BP_H_MASK         0xFFC00000      
#define DIU_HSYN_PARA_BP_H_SHIFT        22

#define DIU_VSYN_PARA_ALL_MASK          0xFFDFFBFF      
#define DIU_VSYN_PARA_FP_V_MASK         0x000003FF      
#define DIU_VSYN_PARA_FP_V_SHIFT        0
#define DIU_VSYN_PARA_PW_V_MASK         0x001FF800      
#define DIU_VSYN_PARA_PW_V_SHIFT        11
#define DIU_VSYN_PARA_BP_V_MASK         0xFFC00000      
#define DIU_VSYN_PARA_BP_V_SHIFT        22

#define DIU_SYN_POL_ALL_MASK            0x0000001F      
#define DIU_SYN_POL_INV_HS_MASK         0x00000001      
#define DIU_SYN_POL_INV_HS_SHIFT        0
#define DIU_SYN_POL_INV_VS_MASK         0x00000002      
#define DIU_SYN_POL_INV_VS_SHIFT        1
#define DIU_SYN_POL_INV_CS_MASK         0x00000004      
#define DIU_SYN_POL_INV_CS_SHIFT        2
#define DIU_SYN_POL_BP_HS_MASK          0x00000008      
#define DIU_SYN_POL_BP_HS_SHIFT         3
#define DIU_SYN_POL_BP_VS_MASK          0x00000010      
#define DIU_SYN_POL_BP_VS_SHIFT         4

#define DIU_THRESHOLDS_ALL_MASK         0x07FF00FF      
#define DIU_THRESHOLDS_OUT_BUF_LOW_MASK     0x000000FF      
#define DIU_THRESHOLDS_OUT_BUF_LOW_SHIFT    0
#define DIU_THRESHOLDS_LS_BF_VS_MASK        0x07FF0000      
#define DIU_THRESHOLDS_LS_BF_VS_SHIFT       16

#define DIU_INT_STATUS_ALL_MASK         0x0000003F      
#define DIU_INT_STATUS_ALL_SHIFT        0
#define DIU_INT_STATUS_VSYNC_MASK       0x00000001      
#define DIU_INT_STATUS_VSYNC_SHIFT      0
#define DIU_INT_STATUS_VSYNC_WB_MASK        0x00000002      
#define DIU_INT_STATUS_VSYNC_WB_SHIFT       1
#define DIU_INT_STATUS_UNDRUN_MASK      0x00000004      
#define DIU_INT_STATUS_UNDRUN_SHIFT     2
#define DIU_INT_STATUS_PARAERR_MASK     0x00000008      
#define DIU_INT_STATUS_PARAERR_SHIFT        3
#define DIU_INT_STATUS_LS_BF_VS_MASK        0x00000010      
#define DIU_INT_STATUS_LS_BF_VS_SHIFT       4
#define DIU_INT_STATUS_WB_PEND_MASK     0x00000020      
#define DIU_INT_STATUS_WB_PEND_SHIFT        5

#define DIU_INT_MASK_ALL_MASK           0x0000003F      
#define DIU_INT_MASK_ALL_SHIFT          0
#define DIU_INT_MASK_M_VSYNC_MASK       0x00000001      
#define DIU_INT_MASK_M_VSYNC_SHIFT      0
#define DIU_INT_MASK_M_VSYNC_WB_MASK        0x00000002      
#define DIU_INT_MASK_M_VSYNC_WB_SHIFT       1
#define DIU_INT_MASK_M_UNDRUN_MASK      0x00000004      
#define DIU_INT_MASK_M_UNDRUN_SHIFT     2
#define DIU_INT_MASK_M_PARERR_MASK      0x00000008      
#define DIU_INT_MASK_M_PARERR_SHIFT     3
#define DIU_INT_MASK_M_LS_BF_VS_MASK        0x00000010      
#define DIU_INT_MASK_M_LS_BF_VS_SHIFT       4
#define DIU_INT_MASK_WB_PEND_MASK       0x00000020      
#define DIU_INT_MASK_WB_PEND_SHIFT      5

#define DIU_COLBAR_1_COLBAR_1_RGB_MASK      0x00FFFFFF      
#define DIU_COLBAR_1_COLBAR_1_RGB_SHIFT     0
#define DIU_COLBAR_1_COLBAR_1_B_MASK        0x000000FF      
#define DIU_COLBAR_1_COLBAR_1_B_SHIFT       0
#define DIU_COLBAR_1_COLBAR_1_G_MASK        0x0000FF00      
#define DIU_COLBAR_1_COLBAR_1_G_SHIFT       8
#define DIU_COLBAR_1_COLBAR_1_R_MASK        0x00FF0000      
#define DIU_COLBAR_1_COLBAR_1_R_SHIFT       16

#define DIU_COLBAR_2_COLBAR_2_RGB_MASK      0x00FFFFFF      
#define DIU_COLBAR_2_COLBAR_2_RGB_SHIFT     0
#define DIU_COLBAR_2_COLBAR_2_B_MASK        0x000000FF      
#define DIU_COLBAR_2_COLBAR_2_B_SHIFT       0
#define DIU_COLBAR_2_COLBAR_2_G_MASK        0x0000FF00      
#define DIU_COLBAR_2_COLBAR_2_G_SHIFT       8
#define DIU_COLBAR_2_COLBAR_2_R_MASK        0x00FF0000      
#define DIU_COLBAR_2_COLBAR_2_R_SHIFT       16

#define DIU_COLBAR_3_COLBAR_3_RGB_MASK      0x00FFFFFF      
#define DIU_COLBAR_3_COLBAR_3_RGB_SHIFT     0
#define DIU_COLBAR_3_COLBAR_3_B_MASK        0x000000FF      
#define DIU_COLBAR_3_COLBAR_3_B_SHIFT       0
#define DIU_COLBAR_3_COLBAR_3_G_MASK        0x0000FF00      
#define DIU_COLBAR_3_COLBAR_3_G_SHIFT       8
#define DIU_COLBAR_3_COLBAR_3_R_MASK        0x00FF0000      
#define DIU_COLBAR_3_COLBAR_3_R_SHIFT       16

#define DIU_COLBAR_4_COLBAR_4_RGB_MASK      0x00FFFFFF      
#define DIU_COLBAR_4_COLBAR_4_RGB_SHIFT     0
#define DIU_COLBAR_4_COLBAR_4_B_MASK        0x000000FF      
#define DIU_COLBAR_4_COLBAR_4_B_SHIFT       0
#define DIU_COLBAR_4_COLBAR_4_G_MASK        0x0000FF00      
#define DIU_COLBAR_4_COLBAR_4_G_SHIFT       8
#define DIU_COLBAR_4_COLBAR_4_R_MASK        0x00FF0000      
#define DIU_COLBAR_4_COLBAR_4_R_SHIFT       16

#define DIU_COLBAR_5_COLBAR_5_RGB_MASK      0x00FFFFFF      
#define DIU_COLBAR_5_COLBAR_5_RGB_SHIFT     0
#define DIU_COLBAR_5_COLBAR_5_B_MASK        0x000000FF      
#define DIU_COLBAR_5_COLBAR_5_B_SHIFT       0
#define DIU_COLBAR_5_COLBAR_5_G_MASK        0x0000FF00      
#define DIU_COLBAR_5_COLBAR_5_G_SHIFT       8
#define DIU_COLBAR_5_COLBAR_5_R_MASK        0x00FF0000      
#define DIU_COLBAR_5_COLBAR_5_R_SHIFT       16

#define DIU_COLBAR_6_COLBAR_6_RGB_MASK      0x00FFFFFF      
#define DIU_COLBAR_6_COLBAR_6_RGB_SHIFT     0
#define DIU_COLBAR_6_COLBAR_6_B_MASK        0x000000FF      
#define DIU_COLBAR_6_COLBAR_6_B_SHIFT       0
#define DIU_COLBAR_6_COLBAR_6_G_MASK        0x0000FF00      
#define DIU_COLBAR_6_COLBAR_6_G_SHIFT       8
#define DIU_COLBAR_6_COLBAR_6_R_MASK        0x00FF0000      
#define DIU_COLBAR_6_COLBAR_6_R_SHIFT       16

#define DIU_COLBAR_7_COLBAR_7_RGB_MASK      0x00FFFFFF      
#define DIU_COLBAR_7_COLBAR_7_RGB_SHIFT     0
#define DIU_COLBAR_7_COLBAR_7_B_MASK        0x000000FF      
#define DIU_COLBAR_7_COLBAR_7_B_SHIFT       0
#define DIU_COLBAR_7_COLBAR_7_G_MASK        0x0000FF00      
#define DIU_COLBAR_7_COLBAR_7_G_SHIFT       8
#define DIU_COLBAR_7_COLBAR_7_R_MASK        0x00FF0000      
#define DIU_COLBAR_7_COLBAR_7_R_SHIFT       16

#define DIU_COLBAR_8_COLBAR_8_RGB_MASK      0x00FFFFFF      
#define DIU_COLBAR_8_COLBAR_8_RGB_SHIFT     0
#define DIU_COLBAR_8_COLBAR_8_B_MASK        0x000000FF      
#define DIU_COLBAR_8_COLBAR_8_B_SHIFT       0
#define DIU_COLBAR_8_COLBAR_8_G_MASK        0x0000FF00      
#define DIU_COLBAR_8_COLBAR_8_G_SHIFT       8
#define DIU_COLBAR_8_COLBAR_8_R_MASK        0x00FF0000      
#define DIU_COLBAR_8_COLBAR_8_R_SHIFT       16

#define DIU_FILLING_ALL_MASK            0x00FFFFFF      
#define DIU_FILLING_ALL_SHIFT           0
#define DIU_FILLING_FILLING_P1_MASK     0x0000000F      
#define DIU_FILLING_FILLING_P1_SHIFT        0
#define DIU_FILLING_FILLING_P2_MASK     0x000000F0      
#define DIU_FILLING_FILLING_P2_SHIFT        4
#define DIU_FILLING_FILLING_P3_MASK     0x00000F00      
#define DIU_FILLING_FILLING_P3_SHIFT        8
#define DIU_FILLING_FILLING_WB_MASK     0x0000F000      
#define DIU_FILLING_FILLING_WB_SHIFT        12
#define DIU_FILLING_FILLING_OBF_MASK        0x00FF0000      
#define DIU_FILLING_FILLING_OBF_SHIFT       16

#define DIU_PLUT_ALL_MASK           0xFFFFFFFF       
#define DIU_PLUT_ALL_SHIFT          0
#define DIU_PLUT_PRIORITY_0_MASK        0x0000000F      
#define DIU_PLUT_PRIORITY_0_SHIFT       0
#define DIU_PLUT_PRIORITY_1_MASK        0x000000F0      
#define DIU_PLUT_PRIORITY_1_SHIFT       4
#define DIU_PLUT_PRIORITY_2_MASK        0x00000F00      
#define DIU_PLUT_PRIORITY_2_SHIFT       8
#define DIU_PLUT_PRIORITY_3_MASK        0x0000F000      
#define DIU_PLUT_PRIORITY_3_SHIFT       12
#define DIU_PLUT_PRIORITY_4_MASK        0x000F0000      
#define DIU_PLUT_PRIORITY_4_SHIFT       16
#define DIU_PLUT_PRIORITY_5_MASK        0x00F00000      
#define DIU_PLUT_PRIORITY_5_SHIFT       20
#define DIU_PLUT_PRIORITY_6_MASK        0x0F000000      
#define DIU_PLUT_PRIORITY_6_SHIFT       24
#define DIU_PLUT_PRIORITY_7_MASK        0xF0000000      
#define DIU_PLUT_PRIORITY_7_SHIFT       28


#define DIU_DEBUG_CTRL_DEBUG_CTRL_MASK      0x000DFFFF
#define DIU_DEBUG_CTRL_DEBUG_CTRL_SHIFT     0       

#define DIU_GRANTED_ACK_GRANTED_ACK_MASK    0x00FFFFFF
#define DIU_GRANTED_ACK_GRANTED_ACK_SHIFT   0

#define DIU_AD_WORD0_AD_WORD0_MASK      0xFFFFFFFF
#define DIU_AD_WORD0_AD_WORD0_SHIFT     0

#define DIU_AD_WORD1_AD_WORD1_MASK      0xFFFFFFFF
#define DIU_AD_WORD1_AD_WORD1_SHIFT     0

#define DIU_AD_WORD2_AD_WORD2_MASK      0xFFFFFFFF
#define DIU_AD_WORD2_AD_WORD2_SHIFT     0

#define DIU_AD_WORD3_AD_WORD3_MASK      0xFFFFFFFF
#define DIU_AD_WORD3_AD_WORD3_SHIFT     0

#define DIU_AD_WORD4_AD_WORD4_MASK      0xFFFFFFFF
#define DIU_AD_WORD4_AD_WORD4_SHIFT     0

#define DIU_AD_WORD5_AD_WORD5_MASK      0xFFFFFFFF
#define DIU_AD_WORD5_AD_WORD5_SHIFT     0

#define DIU_AD_WORD6_AD_WORD6_MASK      0xFFFFFFFF
#define DIU_AD_WORD6_AD_WORD6_SHIFT     0

#define DIU_AD_WORD7_AD_WORD7_MASK      0xFFFFFFFF
#define DIU_AD_WORD7_AD_WORD7_SHIFT     0

#define DIU_AD_WORD8_AD_WORD8_MASK      0xFFFFFFFF
#define DIU_AD_WORD8_AD_WORD8_SHIFT     0


#define DIU_MODE_OFF                   (0)
#define DIU_MODE_3_PLANES_OUT          (1)
#define DIU_MODE_1_OUT_23_WRITE_BACK   (2)
#define DIU_MODE_3_PLANES_WRITE_BACK   (3)
#define DIU_MODE_COLOR_BAR             (4)


/**
 *  \brief Creates the Area Descriptor Word 0.
 *  \param[in] bits_comp0
 *  \param[in] bits_comp1
 *  \param[in] bits_comp2
 *  \param[in] bits_comp3
 *  \param[in] bpp
 *  \param[in] red_c
 *  \param[in] green_c
 *  \param[in] blue_c
 *  \param[in] alpha_c
 *  \param[in] byte_flip
 *  \return Word 0.
 */
#define diu_create_ad_word0(bits_comp0, bits_comp1, bits_comp2, bits_comp3, bpp, palette, red_c, green_c, blue_c, alpha_c, byte_flip) \
                                    (((byte_flip & 0x1) << 28) | \
                                    ((alpha_c & 0x7) << 25) | \
                                    ((blue_c & 0x3) << 23) | \
                                    ((green_c & 0x3) << 21) | \
                                    ((red_c & 0x3) << 19) | \
                                    ((palette & 0x1) << 18) | \
                                    (((bpp-1) & 0x3) << 16) | \
                                    ((bits_comp3 & 0xF) << 12) | \
                                    ((bits_comp2 & 0xF) << 8) | \
                                    ((bits_comp1 & 0xF) << 4) | \
                                    (bits_comp0 & 0xF))

/**
 *  \brief Creates the Area Descriptor Word 2.
 *  \param[in] delta_xs
 *  \param[in] delta_ys
 *  \param[in] g_alpha
 *  \return Word 2.
 */
#define diu_create_ad_word2(delta_xs, delta_ys, g_alpha) (((g_alpha & 0xFF) << 24) | ((delta_ys & 0x7FF) << 12) | (delta_xs & 0x7FF))

/**
 *  \brief Creates the Area Descriptor Word 3.
 *  \param[in] flip
 *  \param[in] delta_xi
 *  \param[in] delta_yi
 *  \return Word 3.
 */
#define diu_create_ad_word3(flip, delta_xi, delta_yi) (((flip & 0x3) << 30) | ((delta_yi & 0x7FF) << 16) | (delta_xi & 0x7FF))

/**
 *  \brief Creates the Area Descriptor Word 4.
 *  \param[in] offset_xi
 *  \param[in] offset_yi
 *  \return Word 4.
 */
#define diu_create_ad_word4(offset_xi, offset_yi) (((offset_yi & 0x7FF) << 16) | (offset_xi & 0x7FF))

/**
 *  \brief Creates the Area Descriptors Word 5.
 *  \param[in] offset_xd
 *  \param[in] offset_yd
 *  \return Word 5.
 */
#define diu_create_ad_word5(offset_xd, offset_yd) (((offset_yd & 0x7FF) << 16) | (offset_xd & 0x7FF))

/**
 *  \brief Creates the Area Descriptor Word 6.
 *  \param[in] ckmax_r
 *  \param[in] ckmax_g
 *  \param[in] ckmax_b
 *  \return Word 6.
 */
#define diu_create_ad_word6(ckmax_r, ckmax_g, ckmax_b) (((ckmax_b & 0xFF) << 16) | ((ckmax_g & 0xFF) << 8) | (ckmax_r & 0xFF))

/**
 *  \brief Creates the Area Descriptor Word 7.
 *  \param[in] ckmin_r
 *  \param[in] ckmin_g
 *  \param[in] ckmin_b
 *  \return Word 7.
 */
#define diu_create_ad_word7(ckmin_r, ckmin_g, ckmin_b) (((ckmin_b & 0xFF) << 16) | ((ckmin_g & 0xFF) << 8) | (ckmin_r & 0xFF))

#define DIU_PALETTE_ENTRIES 256

typedef struct {
   uchar P_B;
   uchar P_G;
   uchar P_R;
   uchar P_A;
   uchar reserved[4];
} DIU_PALETTE_ENTRY;

typedef struct {
   DIU_PALETTE_ENTRY ENTRY[DIU_PALETTE_ENTRIES];
} DIU_PALETTE , * DIU_PALETTE_PTR;


#define DIU_CURSOR_XSIZE 32
#define DIU_CURSOR_YSIZE 32

typedef struct {
   uint_16  PIXEL[DIU_CURSOR_YSIZE][DIU_CURSOR_XSIZE];
} DIU_CURSOR , * DIU_CURSOR_PTR;

#define DIU_GAMMA_RED         0
#define DIU_GAMMA_GREEN       1
#define DIU_GAMMA_BLUE        2
#define DIU_GAMMA_COMPONENTS  3
#define DIU_GAMMA_ENTRIES     256

typedef struct {
   uchar  GAMMA_RED[DIU_GAMMA_ENTRIES];
   uchar  GAMMA_GREEN[DIU_GAMMA_ENTRIES];
   uchar  GAMMA_BLUE[DIU_GAMMA_ENTRIES];
} DIU_GAMMA , * DIU_GAMMA_PTR;

typedef volatile struct mpc5125_diu_ad_struct {
   vuint_32 PIXEL_FORMAT;     // 0x00 Word 0 - Pixel format
   vuint_32 BITMAP_ADDR;      // 0x04 Word 1 - Bitmap address
   vuint_32 SOURCE_SIZE;      // 0x08 Word 2 - Source size/Global alpha
   vuint_32 AOI_SIZE;         // 0x0C Word 3 - AOI size
   vuint_32 AOI_OFFSET;       // 0x10 Word 4 - AOI offset
   vuint_32 DISPLAY_OFFSET;   // 0x14 Word 5 - Display offset
   vuint_32 CHROMA_KEY_MAX;   // 0x18 Word 6 - Chroma key maximum
   vuint_32 CHROMA_KEY_MIN;   // 0x1C Word 7 - Chroma key minimum
   vuint_32 NEXT_AD;          // 0x20 Word 8 - Next AD
   vuint_32 RESERVED_0x24;    // 0x24 Word 9 - Reserved
 } MPC5125_DIU_AD_STRUCT, _PTR_ MPC5125_DIU_AD_STRUCT_PTR;

#define DIU_PLANE_1     0
#define DIU_PLANE_2     1
#define DIU_PLANE_3     2
#define DIU_NUM_PLANES  3
#define DIU_NUM_COLOR_BARS 8

typedef volatile struct mpc5125_diu_struct {
   vuint_32 DESC[DIU_NUM_PLANES];      // 0x00 Plane 1..3 Area Descriptor Pointer Register       R/W 0x0000_0000 10.3.3.1/10-8
   vuint_32 GAMMA;       // 0x0C Gamma Table Pointer Register                   R/W 0x0000_0000 10.3.3.4/10-9
   vuint_32 PALETTE;     // 0x10 Palette Table Pointer Register                 R/W 0x0000_0000 10.3.3.5/10-10
   vuint_32 CURSOR;      // 0x14 Cursor Bitmap Table Pointer Register           R/W 0x0000_0000 10.3.3.6/10-11
   vuint_32 CURS_POS;    // 0x18 Cursor Position Register                       R/W 0x0000_0000 10.3.3.7/10-11
   vuint_32 DIU_MODE;    // 0x1C DIU Mode of Operation Register                 R/W 0x0000_0000 10.3.3.8/10-12
   vuint_32 BGND;        // 0x20 Background Color Register                      R/W 0x0000_0000 10.3.3.9/10-12
   vuint_32 BGND_WB;     // 0x24 Background Color in Writeback Mode Register    R/W 0x0000_0000 10.3.3.10/10-13
   vuint_32 DISP_SIZE;   // 0x28 Display Size Register                          R/W 0x0000_0000 10.3.3.11/10-14
   vuint_32 WB_SIZE;     // 0x2C Writeback Plane Size Register                  R/W 0x0000_0000 10.3.3.12/10-14
   vuint_32 WB_MEM_ADDR; // 0x30 Writeback Plane Address Register               R/W 0x0000_0000 10.3.3.13/10-15
   vuint_32 HSYN_PARA;   // 0x34 Horizontal Sync Pulse Parameters Register      R/W 0x0000_0000 10.3.3.14/10-16
   vuint_32 VSYN_PARA;   // 0x38 Vertical Sync Pulse Parameters Register        R/W 0x0000_0000 10.3.3.15/10-16
   vuint_32 SYN_POL;     // 0x3C Synchronization Signals Polarity Register      R/W 0x0000_0000 10.3.3.16/10-17
   vuint_32 THRESHOLDS;  // 0x40 Thresholds Register                            R/W 0x8000_F800 10.3.3.17/10-18
   vuint_32 INT_STATUS;  // 0x44 Interrupt Status Register                        R 0x0000_0000 10.3.3.18/10-18
   vuint_32 INT_MASK;    // 0x48 Interrupt Mask Register                        R/W 0x0000_003F 10.3.3.19/10-19
   vuint_32 COLBAR[DIU_NUM_COLOR_BARS];    // 0x4C Color #1 in the Color Bar (Black) Register     R/W 0xFF00_0000 10.3.3.20.1/10-21
   vuint_32 FILLING;     // 0x6C Filling Status Register                          R 0x0000_0000 10.3.3.21/10-23
   vuint_32 PLUT;        // 0x70 Priority Look Up Table Register                R/W 0x0000_0000 10.3.3.22/10-24
   RESERVED_REGISTER(0x74,0x100);
 } MPC5125_DIU_STRUCT, _PTR_ MPC5125_DIU_STRUCT_PTR;

#endif