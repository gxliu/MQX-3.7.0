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
* $FileName: spi_mcf5227_dspi.c$
* $Version : 3.6.4.0$
* $Date    : Jun-4-2010$
*
* Comments:
*
*   This file contains board-specific SPI initialization functions.
*
*END************************************************************************/

#include <mqx.h>
#include <bsp.h>
#include "spi_mcf5xxx_dspi.h"

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _bsp_get_spi_base_address
* Returned Value   : Address upon success, NULL upon failure
* Comments         :
*    This function returns the base register address of the corresponding SPI
*    module.
*
*END*----------------------------------------------------------------------*/
pointer _bsp_get_dspi_base_address
(
    uint_8 dev_num
)
{
    pointer addr;
    
    switch (dev_num) 
    {
        case 0:
            addr = (pointer)&(((VMCF5227_STRUCT_PTR)_PSP_GET_IPSBAR())->DSPI);
            break;
        default:
            addr = NULL;
            break;
    }
    return addr;
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _bsp_get_spi_vector
* Returned Value   : Vector number upon success, 0 upon failure
* Comments         :
*    This function returns desired interrupt vector table index for specified 
*    SPI module and vector identifier.
*
*END*----------------------------------------------------------------------*/
uint_32 _bsp_get_dspi_vector
(
    uint_8 dev_num,
    uint_8 vector
)
{
    if (0 != dev_num) return 0;
    switch (vector) 
    {
        case MCF5XXX_DSPI_INT_GLOBAL:
            vector = MCF5227_INT0_DSPI;
            break;
        case MCF5XXX_DSPI_INT_EOQF:
            vector = MCF5227_INT1_DSPI_EOQF;
            break;
        case MCF5XXX_DSPI_INT_TFFF:
            vector = MCF5227_INT1_DSPI_TFFF;
            break;
        case MCF5XXX_DSPI_INT_TCF:
            vector = MCF5227_INT1_DSPI_TCF;
            break;
        case MCF5XXX_DSPI_INT_TFUF:
            vector = MCF5227_INT1_DSPI_TFUF;
            break;
        case MCF5XXX_DSPI_INT_RFDF:
            vector = MCF5227_INT1_DSPI_RFDF;
            break;
        case MCF5XXX_DSPI_INT_RFOF:
            vector = MCF5227_INT1_DSPI_RFOF;
            break;
        case MCF5XXX_DSPI_INT_RFOF_TFUF:
            vector = MCF5227_INT1_DSPI_RFOF_TFUF;
            break;
        default:
            vector = 0;
            break;
    }
    return vector;
}

/* EOF */
