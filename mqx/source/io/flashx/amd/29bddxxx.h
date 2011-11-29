#ifndef _29dbbxxx_h_
#define _29dbbxxx_h_
/**HEADER********************************************************************
* 
* Copyright (c) 2008 Freescale Semiconductor;
* All Rights Reserved
*
* Copyright (c) 2004-2008 Embedded Access Inc.;
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
* $FileName: 29bddxxx.h$
* $Version : 3.6.4.0$
* $Date    : Jun-4-2010$
*
* Comments:
*
*   The file contains functions prototype, defines, structure 
*   definitions specific for the 29bddxxx devices
*
*END************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

extern FLASHX_BLOCK_INFO_STRUCT _29bdd160_block_map_16bit[];
extern FLASHX_BLOCK_INFO_STRUCT _29bdd160_block_map_32bit[];
extern FLASHX_BLOCK_INFO_STRUCT _29lv800bt_block_map_16bit[];

extern boolean _29bdd160_init_device(IO_FLASHX_STRUCT_PTR);
extern boolean _29bdd160_program(IO_FLASHX_STRUCT_PTR, uchar_ptr, uchar_ptr,
                                 _mem_size);
extern boolean _29bdd160_sector_erase(IO_FLASHX_STRUCT_PTR, uchar_ptr, _mem_size);
extern boolean _29bddxxx_chip_erase(IO_FLASHX_STRUCT_PTR);

#ifdef __cplusplus
}
#endif

#endif
/* EOF */
