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
* $FileName: display.h$
* $Version : 3.5.1.0$
* $Date    : Feb-24-2010$
*
* Comments:
* 
*    This file contains the definitions for the display driver functions.
*
*END***********************************************************************/
#ifndef _display_h_
#define _display_h_


#define DISPLAY_ALIGN_LEFT    0
#define DISPLAY_ALIGN_CENTER  1
#define DISPLAY_ALIGN_RIGHT   2
#define DISPLAY_ALIGN_TOP     0
#define DISPLAY_ALIGN_MIDDLE  1
#define DISPLAY_ALIGN_BOTTOM  2

typedef struct  {
   uchar Pos;
   uchar Bits;
} DISPLAY_PIXEL_COMPONENT_FORMAT, * DISPLAY_PIXEL_COMPONENT_FORMAT_PTR;

typedef struct DISPLAY_PIXEL_FORMAT {
   DISPLAY_PIXEL_COMPONENT_FORMAT A;
   DISPLAY_PIXEL_COMPONENT_FORMAT R;
   DISPLAY_PIXEL_COMPONENT_FORMAT G;
   DISPLAY_PIXEL_COMPONENT_FORMAT B;
} DISPLAY_PIXEL_FORMAT, * DISPLAY_PIXEL_FORMAT_PTR;


typedef struct DISPLAY_PIXEL_BUFFER {
   uint_32                 X;
   uint_32                 Y;
   uint_32                 BPP;
   uint_32                 PIXELS;
   uint_32                 SIZE;
   DISPLAY_PIXEL_FORMAT    PF;
   uchar_ptr               FB;
} DISPLAY_PIXEL_BUFFER, * DISPLAY_PIXEL_BUFFER_PTR;



typedef struct {
   uint_32  Sync;
   uint_32  Bp;
   uint_32  Res;
   uint_32  Fp;
   boolean  Bypass;
   boolean  Invert;
} DISPLAY_AXIS_TIMING_PARAM_STRUCT, * DISPLAY_AXIS_TIMING_PARAM_STRUCT_PTR;

typedef struct {
   uint_32                             Refresh;
   DISPLAY_AXIS_TIMING_PARAM_STRUCT    H;
   DISPLAY_AXIS_TIMING_PARAM_STRUCT    V;
   boolean                             InvertComposite;
} DISPLAY_TIMING_PARAM_STRUCT, * DISPLAY_TIMING_PARAM_STRUCT_PTR;

typedef struct {
   char_ptr                     Name;
   DISPLAY_TIMING_PARAM_STRUCT  Params;
   uint_32                      Reserved;
} DISPLAY_PARAM_STRUCT, * DISPLAY_PARAM_STRUCT_PTR;

typedef struct {
   uint_16  Size;
   uint_16  Buffer_Offset;
   uint_16  Display_Offset;
   uint_16  Attributes;
} DISPLAY_AXIS_STRUCT, * DISPLAY_AXIS_STRUCT_PTR;

typedef struct {
   DISPLAY_TIMING_PARAM_STRUCT_PTR TIMING_PARAMS_PTR;
   
   // will be device specific
   MPC5125_DIU_STRUCT_PTR  DIU_PTR; 
   DIU_PALETTE_PTR         PALETTE_PTR;
   DIU_CURSOR_PTR          CURSOR_PTR;
   DIU_GAMMA_PTR           GAMMA_PTR;

} DISPLAY_CONTEXT_STRUCT, * DISPLAY_CONTEXT_STRUCT_PTR;


typedef struct display_view_struct {
   DISPLAY_AXIS_STRUCT           X;
   DISPLAY_AXIS_STRUCT           Y;
   uint_32                       Flip;
   uchar                         Alpha;
   uchar                         Chroma_min[3];
   uchar                         Chroma_max[3];
   DISPLAY_CONTEXT_STRUCT_PTR    DC_PTR;
   DISPLAY_PIXEL_BUFFER_PTR      PB_PTR;
   MPC5125_DIU_AD_STRUCT_PTR     AD_PTR;
} DISPLAY_VIEW_STRUCT, * DISPLAY_VIEW_STRUCT_PTR;




#define BITMAP_FILE_TYPE 'BM'            
#define BITMAP_COMPRESSION_NONE 0

typedef struct {
   uint_32 SIZE;           
   uint_32 RESERVED;      
   uint_32 OFFSET;        
} BITMAP_FILE_HEADER_STRUCT, * BITMAP_FILE_HEADER_STRUCT_PTR;


typedef struct {                     
   uint_32 SIZE;          
   int_32  WIDTH;         
   int_32  HEIGHT;       
   uint_16 PLANES;         
   uint_16 BITS_PER_PIXEL;      
   uint_32 COMPRESSION_TYPE;    
   uint_32 IMAGE_SIZE;      
   int_32  X_PPM;  
   int_32  Y_PPM;  
   uint_32 COLORS_USED;        
   uint_32 COLORS_IMPORTANT;  
} BITMAP_INFO_HEADER_STRUCT, * BITMAP_INFO_HEADER_STRUCT_PTR;


extern DISPLAY_PIXEL_FORMAT_PTR ARGB32;
extern DISPLAY_PIXEL_FORMAT_PTR ABGR32;
extern DISPLAY_PIXEL_FORMAT_PTR RGB24;
extern DISPLAY_PIXEL_FORMAT_PTR BGR24;
extern DISPLAY_PARAM_STRUCT Display_params[]; 
extern char_ptr  Display_default;

/*----------------------------------------------------------------------------------------------------*/
#pragma mark    -
#pragma mark   Display driver functions
#pragma mark    -
/*----------------------------------------------------------------------------------------------------*/


#ifdef __cplusplus
extern "C" {
#endif

extern DISPLAY_CONTEXT_STRUCT_PTR display_initialize(char_ptr name );
extern uint_32                    display_deinit(DISPLAY_CONTEXT_STRUCT_PTR dc_ptr);
extern uint_32                    display_get_hres(DISPLAY_CONTEXT_STRUCT_PTR dc_ptr);
extern uint_32                    display_get_vres(DISPLAY_CONTEXT_STRUCT_PTR dc_ptr);

extern DISPLAY_PIXEL_BUFFER_PTR   display_create_pixel_buffer(uint_32 dx, uint_32 dy, DISPLAY_PIXEL_FORMAT_PTR pf_ptr, uchar_ptr  fb_ptr );
extern DISPLAY_PIXEL_BUFFER_PTR   display_create_pixel_buffer_from_bitmap(char_ptr filename);
extern DISPLAY_PIXEL_BUFFER_PTR   display_create_thumbnail(DISPLAY_PIXEL_BUFFER_PTR large_pb_ptr,uint_32 max_dim);
extern uint_32                    display_create_bitmap_from_pixel_buffer(DISPLAY_PIXEL_BUFFER_PTR,char_ptr filename);
extern int_32                     display_fill_pixel_buffer(DISPLAY_PIXEL_BUFFER_PTR pb_ptr, uchar_ptr fill);
extern void                       display_flush_pixel_buffer(DISPLAY_PIXEL_BUFFER_PTR pb_ptr);
extern pointer                    display_get_pixel_buffer_address(DISPLAY_PIXEL_BUFFER_PTR pb_ptr);
extern uint_32                    display_get_pixel_buffer_bpp(DISPLAY_PIXEL_BUFFER_PTR pb_ptr);
extern uint_32                    display_get_pixel_buffer_size(DISPLAY_PIXEL_BUFFER_PTR pb_ptr);
extern uint_32                    display_get_pixel_buffer_hres(DISPLAY_PIXEL_BUFFER_PTR pb_ptr);
extern uint_32                    display_get_pixel_buffer_vres(DISPLAY_PIXEL_BUFFER_PTR pb_ptr);
extern void                       display_destroy_pixel_buffer(DISPLAY_PIXEL_BUFFER_PTR pb_ptr);

extern DISPLAY_VIEW_STRUCT_PTR    display_create_view(DISPLAY_CONTEXT_STRUCT_PTR dc_ptr, DISPLAY_PIXEL_BUFFER_PTR dfb_ptr);
extern uint_32                    display_center_view(DISPLAY_VIEW_STRUCT_PTR dv_ptr);
extern uint_32                    display_flip_view(DISPLAY_VIEW_STRUCT_PTR dv_ptr, boolean horizontal, boolean vertical) ;
extern uint_32                    display_show_view(DISPLAY_VIEW_STRUCT_PTR dv_ptr, uint_32 plane) ;
extern void                       display_destroy_pixel_buffer(DISPLAY_PIXEL_BUFFER_PTR pb_ptr); 

#ifdef __cplusplus
}
#endif

#endif

