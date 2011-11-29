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
* $FileName: display_params.c$
* $Version : 3.5.1.0$
* $Date    : Feb-24-2010$
*
* Comments:
* 
*    This file contains the default display parameters for the DIU driver.
*
*END***********************************************************************/

#include <mqx.h>
#include <bsp.h>
#include <display.h>

DISPLAY_PARAM_STRUCT Display_params[] = 
{ // Name                RR    HS   HBP  Hres  HFP  BP I      VS   VBP  Vres  VFP BP I   CI  
   { "720x576x60",      {60, { 20, 106,  720, 106,  0, 1 }, { 13,  30,  576,  30,  0, 1},  0 }, 0 },

   { "1024x768x60",     {60, { 136, 160, 1024, 24,  0, 0 }, { 6,   29,  768,  3,  0, 0},  0 }, 0 },
   { "1024x768x26",     {26, { 136, 144, 1024, 144, 0, 0 }, { 6,   16,  768,  16, 0, 0},  0 }, 0 },
   { "640x480x60",      {60, { 20,  80,  640,  80,  0, 0 }, { 13,  23,  480,  22, 0, 0},  0 }, 0 },
   { "800x600x42",      {42, { 20,  112, 800,  112, 0, 0 }, { 3,   16,  600,  15, 0, 0},  0 }, 0 },
   { "1280x1024x60",    {60, { 216, 38,  1280, 128, 0, 0 }, { 37,  2,  1024,  7,  0, 0},  0 }, 0 },
   { "720x576x58",      {58, { 20,  105,  720, 105, 0, 0 }, { 13,  29,  576,  29, 0, 0},  0 }, 0 },
   
   { "720x400x70",      {70, { 20,  105,  720, 105, 0, 1 }, { 13,  29,  400,  29, 0, 0},  0 }, 0 },
   { "640x480x60i",     {60, { 20,  80,  640,  80,  1, 1 }, { 13,  23,  480,  22, 0, 0},  0 }, 0 },
   { "640x480x75",      {75, { 20,  80,  640,  80,  1, 1 }, { 13,  23,  480,  22, 0, 0},  0 }, 0 },
   { "800x600x60",      {60, { 20,  112, 800,  112, 0, 0 }, { 3,   16,  600,  15, 0, 0},  0 }, 0 },
   { "800x600x75",      {75, { 20,  112, 800,  112, 0, 0 }, { 3,   16,  600,  15, 0, 0},  0 }, 0 },
   { "1024x768x60i",    {60, { 136, 160, 1024, 24,  1, 1 }, { 6,   29,  768,  3,  0, 0},  0 }, 0 },
   { "1024x768x75",     {75, { 136, 160, 1024, 24,  0, 0 }, { 6,   29,  768,  3,  0, 0},  0 }, 0 },
   { "1152x864x75",     {75, { 136, 160, 1152, 24,  0, 0 }, { 6,   29,  864,  3,  0, 0},  0 }, 0 },
   { "1280x1024x75",    {75, { 216, 38,  1280, 128, 0, 0 }, { 37,  2,  1024,  7,  0, 0},  0 }, 0 },
   { "1680x1050x60",    {60, { 216, 38,  1280, 128, 0, 0 }, { 37,  2,  1024,  7,  0, 0},  0 }, 0 },
   { 0 }
};

char_ptr  Display_default = "1024x768x60"; //"720x576x58"; 
