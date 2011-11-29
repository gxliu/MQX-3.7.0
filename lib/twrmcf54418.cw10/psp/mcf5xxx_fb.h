/**HEADER********************************************************************
* 
* Copyright (c) 2008 Freescale Semiconductor;
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
* $FileName: mcf5xxx_fb.h$
* $Version : 3.0.3.0$
* $Date    : Aug-10-2009$
*
* Comments:
*
*   This file contains the type definitions for the mcf5xxx Flex BUS module.
*
*END************************************************************************/

#ifndef __mcf5xxx_fb_h__
#define __mcf5xxx_fb_h__

#define __mcf5xxx_fb_h__version "$Version:3.0.3.0$"
#define __mcf5xxx_fb_h__date    "$Date:Aug-10-2009$"

#ifdef __cplusplus
extern "C" {
#endif

/*------------------------------------------------------------------------*/
/*
** Flex BUS registers
*/


/*------------------------------------------------------------------------*/
/*

// Mini-FlexBus related constants

/* Bit definitions and macros for MCF5XXX_FBCS_CSAR */
#define MCF5XXX_FBCS_CSAR_BA(x)                  ((x)&0xFFFF0000)

/* Bit definitions and macros for FBCS_CSMR */
#define MCF5XXX_FBCS_CSMR_V                     (1)
#define MCF5XXX_FBCS_CSMR_WP                    (1 << 8)
#define MCF5XXX_FBCS_CSMR_BAM(x)                (((x) & 0xFFFF) << 16)
#define MCF5XXX_FBCS_CSMR_BAM_4G                (0xFFFF0000)
#define MCF5XXX_FBCS_CSMR_BAM_2G                (0x7FFF0000)
#define MCF5XXX_FBCS_CSMR_BAM_1G                (0x3FFF0000)
#define MCF5XXX_FBCS_CSMR_BAM_1024M             (0x3FFF0000)
#define MCF5XXX_FBCS_CSMR_BAM_512M              (0x1FFF0000)
#define MCF5XXX_FBCS_CSMR_BAM_256M              (0xFFF0000)
#define MCF5XXX_FBCS_CSMR_BAM_128M              (0x7FF0000)
#define MCF5XXX_FBCS_CSMR_BAM_64M               (0x3FF0000)
#define MCF5XXX_FBCS_CSMR_BAM_32M               (0x1FF0000)
#define MCF5XXX_FBCS_CSMR_BAM_16M               (0xFF0000)
#define MCF5XXX_FBCS_CSMR_BAM_8M                (0x7F0000)
#define MCF5XXX_FBCS_CSMR_BAM_4M                (0x3F0000)
#define MCF5XXX_FBCS_CSMR_BAM_2M                (0x1F0000)
#define MCF5XXX_FBCS_CSMR_BAM_1M                (0xF0000)
#define MCF5XXX_FBCS_CSMR_BAM_1024K             (0xF0000)
#define MCF5XXX_FBCS_CSMR_BAM_512K              (0x70000)
#define MCF5XXX_FBCS_CSMR_BAM_256K              (0x30000)
#define MCF5XXX_FBCS_CSMR_BAM_128K              (0x10000)
#define MCF5XXX_FBCS_CSMR_BAM_64K               (0)

/* Bit definitions and macros for FBCS_CSCR */
#define MCF5XXX_FBCS_CSCR_BSTW                  (1 << 3)
#define MCF5XXX_FBCS_CSCR_BSTR                  (1 << 4)
#define MCF5XXX_FBCS_CSCR_BEM                   (1 << 5)
#define MCF5XXX_FBCS_CSCR_PS(x)                 (((x) & 3) << 6)
#define MCF5XXX_FBCS_CSCR_PS_32                 (0)
#define MCF5XXX_FBCS_CSCR_PS_8                  (1 << 6)
#define MCF5XXX_FBCS_CSCR_PS_16                 (1 << 7)
#define MCF5XXX_FBCS_CSCR_AA                    (1 << 8)
#define MCF5XXX_FBCS_CSCR_SBM                   (1 << 9)
#define MCF5XXX_FBCS_CSCR_WS(x)                 (((x) & 0x3f) << 10)
#define MCF5XXX_FBCS_CSCR_WRAH(x)               (((x) & 3) << 16)
#define MCF5XXX_FBCS_CSCR_RDAH(x)               (((x) & 3) << 18)
#define MCF5XXX_FBCS_CSCR_ASET(x)               (((x) & 3) << 20)
#define MCF5XXX_FBCS_CSCR_SWSEN                 (1 << 23)
#define MCF5XXX_FBCS_CSCR_SWS(x)                (((x) & 0x3f) << 26)

/*
** MCF5XXX_FB_STRUCT
** This structure defines FlexBus registers
*/
typedef struct mcf5xxx_fb_struct {
    uint_32 CSAR;           // Chip-Select Address Register
    uint_32 CSMR;           // Chip-Select Mask Register
    uint_32 CSCR;           // Chip-Select Control Register
} MCF5XXX_FB_STRUCT, _PTR_ MCF5XXX_FB_STRUCT_PTR;
typedef volatile struct mcf5xxx_fb_struct _PTR_ VMCF5XXX_FB_STRUCT_PTR;

#ifdef __cplusplus
}
#endif

#endif /* __mcf5xxx_fb_h__ */
