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
* $FileName: display.c$
* $Version : 3.6.3.0$
* $Date    : Jun-4-2010$
*
* Comments:
* 
*    This file contains the display driver functions.
*
*END***********************************************************************/
#include <mqx.h>
#include <bsp.h>
#include <tfs.h>
#include <display.h>

DISPLAY_PIXEL_FORMAT ARGB32_data= {{3,8},{2,8},{1,8},{0,8}};
DISPLAY_PIXEL_FORMAT ABGR32_data= {{3,8},{0,8},{1,8},{2,8}};
DISPLAY_PIXEL_FORMAT BGR24_data = {{3,0},{0,8},{1,8},{2,8}};
DISPLAY_PIXEL_FORMAT RGB24_data = {{3,0},{2,8},{1,8},{0,8}};
DISPLAY_PIXEL_FORMAT_PTR ARGB32 = &ARGB32_data;
DISPLAY_PIXEL_FORMAT_PTR ABGR32 = &ABGR32_data;
DISPLAY_PIXEL_FORMAT_PTR RGB24 = &RGB24_data;
DISPLAY_PIXEL_FORMAT_PTR BGR24 = &BGR24_data;

/*----------------------------------------------------------------------------------------------------*/

static DISPLAY_CONTEXT_STRUCT_PTR display_init_initernal(DISPLAY_TIMING_PARAM_STRUCT_PTR dtp_ptr)
{
   DISPLAY_CONTEXT_STRUCT_PTR dc_ptr = NULL;
    MPC5125_DIU_STRUCT_PTR diu_ptr = MPC5125_DIU_ADDR();
   uint_32 i;
   
   dc_ptr = _mem_alloc_zero(sizeof(*dc_ptr));
   if (dc_ptr == NULL) {
      return NULL;
   }
   
   dc_ptr->TIMING_PARAMS_PTR = dtp_ptr;
   
   // will be device specific
   dc_ptr->DIU_PTR = MPC5125_DIU_ADDR();
   dc_ptr->PALETTE_PTR = _mem_alloc_zero(sizeof(DIU_PALETTE));
   dc_ptr->CURSOR_PTR = _mem_alloc_zero(sizeof(DIU_CURSOR));
   dc_ptr->GAMMA_PTR = _mem_alloc_zero(sizeof(DIU_GAMMA));

    
    for (i = 0; i <DIU_GAMMA_ENTRIES; i++) {
      dc_ptr->GAMMA_PTR->GAMMA_RED[i]=i;
      dc_ptr->GAMMA_PTR->GAMMA_GREEN[i]=i;
      dc_ptr->GAMMA_PTR->GAMMA_BLUE[i]=i;
   }
 
   diu_init_device( diu_ptr, dtp_ptr );
   diu_set_gamma( diu_ptr, dc_ptr->GAMMA_PTR );
   diu_set_cursor_image( diu_ptr, dc_ptr->CURSOR_PTR );
   
   // temporary
    diu_set_mode(diu_ptr, DIU_MODE_COLOR_BAR);

    return dc_ptr;
}

DISPLAY_CONTEXT_STRUCT_PTR display_initialize(char_ptr name )
{
   DISPLAY_TIMING_PARAM_STRUCT_PTR dtp_ptr;
   uint_32 i;
   
   if (name == NULL) {
      name = Display_default;
   } 
   
   for (i=0;Display_params[i].Name;i++) {
      if (strcasecmp(Display_params[i].Name,name)==0) {
         dtp_ptr = &Display_params[i].Params;
         return display_init_initernal(dtp_ptr);
      }
   }
   return NULL;
}      

uint_32 display_deinit(DISPLAY_CONTEXT_STRUCT_PTR dc_ptr)
{
   
   if (dc_ptr) {
    diu_set_mode(dc_ptr->DIU_PTR, DIU_MODE_OFF);

      if (dc_ptr->PALETTE_PTR) {
         _mem_free(dc_ptr->PALETTE_PTR);
      }
       if (dc_ptr->CURSOR_PTR) {
         _mem_free(dc_ptr->CURSOR_PTR);
      }
      if (dc_ptr->GAMMA_PTR) {
         _mem_free(dc_ptr->GAMMA_PTR);
      }
      _mem_free(dc_ptr);
      return MQX_OK;
   }
   return MQX_INVALID_HANDLE;
}



uint_32 display_get_hres(DISPLAY_CONTEXT_STRUCT_PTR dc_ptr)
{
   if (dc_ptr) {
      return dc_ptr->TIMING_PARAMS_PTR->H.Res;
   }
   return 0;
}   


uint_32 display_get_vres(DISPLAY_CONTEXT_STRUCT_PTR dc_ptr)
{
   if (dc_ptr) {
      return dc_ptr->TIMING_PARAMS_PTR->V.Res;
   }
   return 0;
}   

/*----------------------------------------------------------------------------------------------------*/
#pragma mark    -
#pragma mark   Pixel Buffer functions
#pragma mark    -
/*----------------------------------------------------------------------------------------------------*/


DISPLAY_PIXEL_BUFFER_PTR display_create_pixel_buffer(uint_32 dx, uint_32 dy, DISPLAY_PIXEL_FORMAT_PTR pf_ptr, uchar_ptr  fb_ptr )
{
   DISPLAY_PIXEL_BUFFER_PTR   pb_ptr;
   uint_32                    bpp,pixels,size;

   bpp = (pf_ptr->A.Bits + pf_ptr->R.Bits + pf_ptr->G.Bits + pf_ptr->B.Bits+7)>>3;
   pixels = dx*dy;
   size =  pixels*bpp;
   
   
   if (fb_ptr) {
      pb_ptr = (DISPLAY_PIXEL_BUFFER_PTR)_mem_alloc(sizeof(DISPLAY_PIXEL_BUFFER));
   } else {
      pb_ptr = (DISPLAY_PIXEL_BUFFER_PTR)_mem_alloc(sizeof(DISPLAY_PIXEL_BUFFER) + size);
      fb_ptr = (uchar_ptr) &pb_ptr[1];
   }

   if (pb_ptr) {
      pb_ptr->X = dx;
      pb_ptr->Y = dy;
      pb_ptr->BPP = bpp;
      pb_ptr->PIXELS = pixels; 
      pb_ptr->SIZE = size;
      pb_ptr->PF = *pf_ptr;
      pb_ptr->FB = fb_ptr;
   }
   return pb_ptr;   
}


static uchar bfh_endian_map[] = { 4,2,2,4,0};
static uchar bih_endian_map[] = { 4,4,4,2,2,4,4,4,4,4,4,0};





DISPLAY_PIXEL_BUFFER_PTR display_create_pixel_buffer_from_bitmap(char_ptr filename)
{
   MQX_FILE_PTR               fp;
   BITMAP_FILE_HEADER_STRUCT  bfh;
   BITMAP_INFO_HEADER_STRUCT  bih;
   DISPLAY_PIXEL_BUFFER_PTR   pb_ptr = NULL;
   uint_16                    file_type;   
   pointer                    data;
   uint_32                    width, result;
   
   fp = fopen(filename,"rb");
   
   if (fp) {
      if ( fread((pointer) &file_type, sizeof(file_type), 1, fp)==1) {
         if (file_type == BITMAP_FILE_TYPE) {
   
            if (fread((pointer) &bfh, sizeof(bfh), 1, fp) == 1) {
               _mem_swap_endian(bfh_endian_map,(pointer) &bfh );
            
            
               if (fread((pointer) &bih, sizeof(bih), 1, fp) == 1) {
                  _mem_swap_endian(bih_endian_map,(pointer) &bih );
            
                  if ( bih.COMPRESSION_TYPE  == BITMAP_COMPRESSION_NONE) {

                     if ( bih.BITS_PER_PIXEL==24 ) {
                        char discard[4];
                        uint_32 i,padding;
                        char * cptr;

                        padding = 4-((bih.WIDTH*3) & 3);
                        if (padding > 3) padding = 0;

                        pb_ptr = display_create_pixel_buffer(bih.WIDTH,bih.HEIGHT, BGR24, NULL );
                        cptr = display_get_pixel_buffer_address(pb_ptr);
                        for (i=0;i< bih.HEIGHT;i++) {
                           fread(&cptr[i*bih.WIDTH*3],bih.WIDTH*3,1,fp);
                           if (padding) {
                              fread(discard,padding,1,fp);
                           }
                        }
                     }
                  }
               }
            }               
         }
      }
      fclose(fp);
   } 
   return pb_ptr;              
}


uint_32 display_create_bitmap_from_pixel_buffer(DISPLAY_PIXEL_BUFFER_PTR pb_ptr, char_ptr filename)
{
   MQX_FILE_PTR               fp;
   BITMAP_FILE_HEADER_STRUCT  bfh;
   BITMAP_INFO_HEADER_STRUCT  bih;
   uint_32                    error=IO_ERROR;
   uint_16                    file_type = BITMAP_FILE_TYPE;
   
   if (pb_ptr->BPP != 3) {
      return IO_ERROR;
   }

   bih.SIZE   = sizeof(bih);      
   bih.WIDTH   = pb_ptr->X;         
   bih.HEIGHT  = pb_ptr->Y;       
   bih.PLANES  = 1;         
   bih.BITS_PER_PIXEL = pb_ptr->BPP*8;      
   bih.COMPRESSION_TYPE = BITMAP_COMPRESSION_NONE;    
   bih.IMAGE_SIZE = pb_ptr->X *  pb_ptr->Y * pb_ptr->BPP;      
   bih.X_PPM = 3780;  // don't know this
   bih.Y_PPM = 3780;  
   bih.COLORS_USED = 0;        
   bih.COLORS_IMPORTANT = 0;  

   bfh.OFFSET   = sizeof(file_type) + sizeof(bfh) + sizeof(bih);
   bfh.SIZE     = bfh.OFFSET + bih.IMAGE_SIZE;
   bfh.RESERVED = 0;

   
   fp = fopen(filename,"wb");
   if (fp) {
      if (fwrite((pointer) &file_type, sizeof(file_type), 1, fp)==1) {
         _mem_swap_endian(bfh_endian_map,(pointer) &bfh );
         if (fwrite((pointer) &bfh, sizeof(bfh), 1, fp) == 1) {
            _mem_swap_endian(bih_endian_map,(pointer) &bih );
            if (fwrite((pointer) &bih, sizeof(bih), 1, fp) == 1) {
               fwrite(pb_ptr->FB,pb_ptr->SIZE,1,fp);
               error=MQX_OK;
            }               
         }
      }
      fclose(fp);
   } 
   return error;              
}

DISPLAY_PIXEL_BUFFER_PTR display_create_thumbnail(DISPLAY_PIXEL_BUFFER_PTR large_pb_ptr,uint_32 max_dim) 
{
   DISPLAY_PIXEL_BUFFER_PTR   thumb_pb_ptr;
   uint_32                    x,y,lx,ly,tx,ty,px,py,ti,li,scale,fill,bx;
   uchar_ptr                  tb,lb;
   uint_32                    r,g,b;
   
   
   lx=display_get_pixel_buffer_hres(large_pb_ptr);
   ly=display_get_pixel_buffer_vres(large_pb_ptr);
   if (lx>ly) {
      scale = (lx*10/max_dim+5)/10;
    } else {
      scale = (ly*10/max_dim+5)/10;
    }
   tx = lx/scale;
   ty = ly/scale;
    
   bx = tx; 
   while ((bx*3) & 0x3) {
      bx++;
   }

    thumb_pb_ptr = display_create_pixel_buffer(bx,ty,BGR24,NULL);
    if (thumb_pb_ptr==NULL) {
      return NULL;
    }
    fill=0;
    display_fill_pixel_buffer(thumb_pb_ptr,(uchar_ptr)&fill);
    
    lb = display_get_pixel_buffer_address(large_pb_ptr);
    tb = display_get_pixel_buffer_address(thumb_pb_ptr);
    
     for (x=0;x<tx;x++) {
      for (y=0;y<ty;y++) {
         ti = (x+y*bx)*3;
         b = r = g = 0;
         for (px=x*scale;px<(x*scale+scale);px++) {
            for (py=y*scale;py<(y*scale+scale);py++) {
               li = (px+py*lx)*3;
               b += lb[li];
               r += lb[li+1];
               g += lb[li+2];
            }
         }
         tb[ti ]  = b/(scale*scale);
         tb[ti+1] = r/(scale*scale);
         tb[ti+2] = g/(scale*scale);
      }
   }
   return thumb_pb_ptr;
}         
   

int_32 display_fill_pixel_buffer(DISPLAY_PIXEL_BUFFER_PTR pb_ptr, uchar_ptr fill)
{
   uchar_ptr fb_ptr;
   uint_32   i;
 
   fb_ptr = pb_ptr->FB;
   switch (pb_ptr->BPP) {
      case 1:
         for (i=0;i<pb_ptr->PIXELS;i++) {
            *fb_ptr++ = fill[0];
         }
         break;
    
      case 2:
         for (i=0;i<pb_ptr->PIXELS;i++) {
            *fb_ptr++ = fill[0];
            *fb_ptr++ = fill[1];
         }
         break;
    
      case 3:
         for (i=0;i<pb_ptr->PIXELS;i++) {
            *fb_ptr++ = fill[0];
            *fb_ptr++ = fill[1];
            *fb_ptr++ = fill[2];
         }
         break;
     
      case 4:
         for (i=0;i<pb_ptr->PIXELS;i++) {
            *fb_ptr++ = fill[0];
            *fb_ptr++ = fill[1];
            *fb_ptr++ = fill[2];
            *fb_ptr++ = fill[3];
         }
         break;
   }
   return MQX_OK;
}

void  display_flush_pixel_buffer(DISPLAY_PIXEL_BUFFER_PTR pb_ptr)
{
  _dcache_flush_mlines((pointer) pb_ptr->FB,pb_ptr->SIZE);

}


pointer display_get_pixel_buffer_address(DISPLAY_PIXEL_BUFFER_PTR pb_ptr)
{
   if (pb_ptr==NULL) {
      return NULL;
   }
   return pb_ptr->FB;
}

uint_32 display_get_pixel_buffer_size(DISPLAY_PIXEL_BUFFER_PTR pb_ptr)
{
   if (pb_ptr==NULL) {
      return 0;
   }
   return pb_ptr->SIZE;
}

uint_32 display_get_pixel_buffer_hres(DISPLAY_PIXEL_BUFFER_PTR pb_ptr)
{
   if (pb_ptr==NULL) {
      return 0;
   }
   return pb_ptr->X;
}

uint_32 display_get_pixel_buffer_vres(DISPLAY_PIXEL_BUFFER_PTR pb_ptr)
{
   if (pb_ptr==NULL) {
      return 0;
   }
   return pb_ptr->Y;
}

uint_32 display_get_pixel_buffer_bpp(DISPLAY_PIXEL_BUFFER_PTR pb_ptr)
{
   if (pb_ptr==NULL) {
      return 0;
   }
   return pb_ptr->BPP;
}



void display_destroy_pixel_buffer(DISPLAY_PIXEL_BUFFER_PTR pb_ptr) 
{
   if (pb_ptr) {
      // We should run the list of ADs to see if this view is currently displayed.
      
      _mem_free((pointer)pb_ptr);
   }
}

/*----------------------------------------------------------------------------------------------------*/
#pragma mark    -
#pragma mark   View functions
#pragma mark    -
/*----------------------------------------------------------------------------------------------------*/


static void display_initialize_ad(DISPLAY_VIEW_STRUCT_PTR dv_ptr)
{
   DISPLAY_PIXEL_BUFFER_PTR pb_ptr = dv_ptr->PB_PTR;

   diu_ad_initialize(dv_ptr->AD_PTR, 
      pb_ptr->PF.R.Bits,pb_ptr->PF.G.Bits,
      pb_ptr->PF.B.Bits, pb_ptr->PF.A.Bits,                 // bits per component 
      pb_ptr->BPP, 0,                                       // 4 byte pixels, no palette,
      pb_ptr->PF.R.Pos,pb_ptr->PF.G.Pos,
      pb_ptr->PF.B.Pos, pb_ptr->PF.A.Pos,                   // position of component 
      1,                                                    // byte_flip = 1 - always
      (uint_32) pb_ptr->FB,                                 // The frame buffer 
    dv_ptr->X.Size, dv_ptr->Y.Size,                       // display size of AOI
       dv_ptr->Alpha,                                         // alpha, 
    pb_ptr->X, pb_ptr->Y,                                 // AOI size
       dv_ptr->Flip,                                         // no flip, 
       dv_ptr->X.Buffer_Offset, dv_ptr->Y.Buffer_Offset,     // AOI offset
       dv_ptr->X.Display_Offset, dv_ptr->Y.Display_Offset,   // display offset
       dv_ptr->Chroma_max[0],dv_ptr->Chroma_max[1],dv_ptr->Chroma_max[2],                                    // chroma kkey max/min - disabled
       dv_ptr->Chroma_min[0],dv_ptr->Chroma_min[1],dv_ptr->Chroma_min[2],                                    // chroma kkey max/min - disabled
       0
    );
}

DISPLAY_VIEW_STRUCT_PTR display_create_view(DISPLAY_CONTEXT_STRUCT_PTR dc_ptr, DISPLAY_PIXEL_BUFFER_PTR pb_ptr)
{
   MPC5125_DIU_AD_STRUCT_PTR       ad_ptr;
   DISPLAY_TIMING_PARAM_STRUCT_PTR dtp_ptr;
   DISPLAY_VIEW_STRUCT_PTR         dv_ptr; 
   uint_32                          dx,dy,i;
   
   if ((dc_ptr==NULL) || (pb_ptr==NULL)) {
      return NULL;
   }
     
   dv_ptr= _mem_alloc_zero(sizeof(*dv_ptr));
   
   if (dv_ptr == NULL) {
      return NULL;
   }
   
   ad_ptr= _mem_alloc_zero(sizeof(*ad_ptr));
   
   if (ad_ptr == NULL) {
      _mem_free(dv_ptr);
      return NULL;
   }
   
   dtp_ptr = dc_ptr->TIMING_PARAMS_PTR;
   dx=min(pb_ptr->X,dtp_ptr->H.Res);
   dy=min(pb_ptr->Y,dtp_ptr->V.Res);
   
   dv_ptr->X.Size           = dx;
   dv_ptr->X.Buffer_Offset  = 0;
   dv_ptr->X.Display_Offset = 0;
   dv_ptr->Y.Size           = dy;
   dv_ptr->Y.Buffer_Offset  = 0;
   dv_ptr->Y.Display_Offset = 0;
   dv_ptr->Flip = 0;
   dv_ptr->Alpha = 0;
   for (i=0;i<3;i++) {
      dv_ptr->Chroma_min[i] = 255;
      dv_ptr->Chroma_max[i] = 0;
   }
   
   dv_ptr->DC_PTR = dc_ptr;
   dv_ptr->PB_PTR = pb_ptr;
   dv_ptr->AD_PTR = ad_ptr;
   
   display_initialize_ad(dv_ptr);
   
   return dv_ptr;
}


void display_destroy_view(DISPLAY_PIXEL_BUFFER_PTR dv_ptr) 
{
   if (dv_ptr) {
      // We should run the list of ADs to see if this view is currently displayed.
      
      _mem_free((pointer)dv_ptr);
   }
}



static uint_32 display_center_axis(DISPLAY_AXIS_STRUCT_PTR da_ptr, uint_32 res )
{
   if (res>da_ptr->Size) {
      da_ptr->Display_Offset = (res-da_ptr->Size)/2;
      da_ptr->Buffer_Offset  = 0;
   } else {
      da_ptr->Display_Offset = 0;
      da_ptr->Buffer_Offset  = (da_ptr->Size-res)/2;
   } 
}


uint_32 display_center_view(DISPLAY_VIEW_STRUCT_PTR dv_ptr) 
{
   display_center_axis( &dv_ptr->X, display_get_hres(dv_ptr->DC_PTR));
   display_center_axis( &dv_ptr->Y, display_get_vres(dv_ptr->DC_PTR));

   display_initialize_ad( dv_ptr );
   return MQX_OK;
}


uint_32 display_flip_view(DISPLAY_VIEW_STRUCT_PTR dv_ptr, boolean horizontal, boolean vertical) 
{
   if (horizontal && vertical) {
      return IO_ERROR;
   } else if (vertical) {
      dv_ptr->Flip = 2;
   } else if (horizontal) {
      dv_ptr->Flip = 1;
   } else {
      dv_ptr->Flip = 0;
   }
   
   display_initialize_ad( dv_ptr );
   return MQX_OK;
}


uint_32 display_show_view(DISPLAY_VIEW_STRUCT_PTR dv_ptr, uint_32 plane) 
{
   if (plane >= DIU_NUM_PLANES) {
      return IO_ERROR;
   }
   
   display_flush_pixel_buffer(dv_ptr->PB_PTR);
   diu_ad_set(dv_ptr->DC_PTR->DIU_PTR, plane, dv_ptr->AD_PTR);

    diu_set_mode(dv_ptr->DC_PTR->DIU_PTR, DIU_MODE_3_PLANES_OUT);
    return MQX_OK;
}



   


