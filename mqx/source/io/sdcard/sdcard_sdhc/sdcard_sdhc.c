/**HEADER********************************************************************
* 
* Copyright (c) 2010 Freescale Semiconductor;
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
* $FileName: sdcard_sdhc.c$
* $Version : 3.7.2.0$
* $Date    : Feb-7-2011$
*
* Comments:
*
*   This file contains the SD card driver functions.
*
*END************************************************************************/


#include <mqx.h>
#include <bsp.h>
#include <io_prv.h>
#include <sdcard.h>
#include <sdcard_prv.h>
#include <sdcard_sdhc.h>
#include <sdhc.h>

extern uint_32 gul_sdhc_sd_rca;   //Relative Card Address
extern uint_32 int_done_sdhc;
extern uint_32 gul_csd[8];        //response 128bit CSD
extern uint_32 gul_sector_address;
/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : _io_sdcard_sdhc_init
* Returned Value   : TRUE if successful, FALSE otherwise
* Comments         :
*    Initializes sdhc communication, SD card itself and reads its parameters.
*
*END*----------------------------------------------------------------------*/

boolean _io_sdcard_sdhc_init 
(
    /* [IN/OUT] SD card file descriptor */
    MQX_FILE_PTR fd_ptr
)
{
    uint_32              param, c_size, c_size_mult, read_bl_len, result;
    SDHC_COMMAND_STRUCT  command;
    IO_DEVICE_STRUCT_PTR io_dev_ptr = fd_ptr->DEV_PTR;
    SDCARD_STRUCT_PTR    sdcard_ptr = (SDCARD_STRUCT_PTR)io_dev_ptr->DRIVER_INIT_PTR;
    
    /* Check parameters */
    if ((NULL == sdcard_ptr) || (NULL == sdcard_ptr->COM_DEVICE) || (NULL == sdcard_ptr->INIT))
    {
        return FALSE;
    }

    sdcard_ptr->TIMEOUT = 0;
    sdcard_ptr->NUM_BLOCKS = 0;
    sdcard_ptr->ADDRESS = 0;
    sdcard_ptr->SDHC = FALSE;
    sdcard_ptr->VERSION2 = FALSE;
  
    /* Initialize and detect card */
    if (SDHC_OK != ioctl (sdcard_ptr->COM_DEVICE, IO_IOCTL_SDHC_INIT, NULL))
    {
        return FALSE;
    }
    /* SDHC check */
    param = 0;
    if (SDHC_OK != ioctl (sdcard_ptr->COM_DEVICE, IO_IOCTL_SDHC_GET_CARD, &param))
    {
        return FALSE;
    }
    if (!((SDHC_SD == param) || (SDHC_COMBO == param) || (SDHC_MMC == param) || (SDHC_SDIO == param)))
    {
        return FALSE;
    }

    /* Get card address */
    gul_sdhc_sd_rca &= 0xFFFF0000;
    sdcard_ptr->ADDRESS = gul_sdhc_sd_rca;
    read_bl_len = gul_csd[2]  & 0x000F;
    c_size = gul_csd[3] & 0x03FF;
    c_size = (c_size << 2) | (gul_csd[4] >> 14);
    c_size_mult = ((gul_csd[4] & 0x0003) << 1)|(gul_csd[5] >> 15);
    sdcard_ptr->NUM_BLOCKS = (c_size + 1) * (1 << (c_size_mult + 2)) * (1 << (read_bl_len -9));
    return TRUE;
}


/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : _io_sdcard_sdhc_read_block
* Returned Value   : TRUE if successful, FALSE otherwise
* Comments         :
*    Reads sector (512 byte) from SD card with given index into given buffer.
*
*END*----------------------------------------------------------------------*/

boolean _io_sdcard_sdhc_read_block 
(
    /* [IN] SD card info */
    MQX_FILE_PTR fd_ptr, 

    /* [OUT] Buffer to fill with read 512 bytes */
    uchar_ptr buffer, 

    /* [IN] Index of sector to read */
    uint_32   index
)
{
    SDHC_COMMAND_STRUCT  command;
    IO_DEVICE_STRUCT_PTR io_dev_ptr = fd_ptr->DEV_PTR;
    SDCARD_STRUCT_PTR    sdcard_ptr = (SDCARD_STRUCT_PTR)io_dev_ptr->DRIVER_INIT_PTR;
    
    /* Check parameters */
    if ((NULL == sdcard_ptr) || (NULL == sdcard_ptr->COM_DEVICE) || (NULL == sdcard_ptr->INIT) || (NULL == buffer))
    {
        return FALSE;
    }

    /* SD card data address adjustment */
    if (! sdcard_ptr->SDHC)
    {
        index <<= IO_SDCARD_BLOCK_SIZE_POWER;
    }
    
    gul_sector_address = index;
   
    fread (buffer, 1, IO_SDCARD_BLOCK_SIZE, sdcard_ptr->COM_DEVICE);

    /* Wait for transfer complete */
    if (SDHC_OK != fflush (sdcard_ptr->COM_DEVICE))
    {
        return FALSE;
    }

    return TRUE;
}


/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : _io_sdcard_sdhc_write_block
* Returned Value   : TRUE if successful, FALSE otherwise
* Comments         :
*    Writes sector (512 byte) with given index to SD card from given buffer.
*
*END*----------------------------------------------------------------------*/

boolean _io_sdcard_sdhc_write_block 
(
    /* [IN] SD card file descriptor */
    MQX_FILE_PTR fd_ptr, 

    /* [IN] Buffer with 512 bytes to write */
    uchar_ptr buffer, 

    /* [IN] Index of sector to write */
    uint_32   index
)
{
    SDHC_COMMAND_STRUCT command;
    IO_DEVICE_STRUCT_PTR io_dev_ptr = fd_ptr->DEV_PTR;
    SDCARD_STRUCT_PTR    sdcard_ptr = (SDCARD_STRUCT_PTR)io_dev_ptr->DRIVER_INIT_PTR;

    /* Check parameters */
    if ((NULL == sdcard_ptr) || (NULL == sdcard_ptr->COM_DEVICE) || (NULL == sdcard_ptr->INIT) || (NULL == buffer))
    {
        return FALSE;
    }

    /* SD card data address adjustment */
    if (! sdcard_ptr->SDHC)
    {
        index <<= IO_SDCARD_BLOCK_SIZE_POWER;
    }

    gul_sector_address = index;
    
    fwrite (buffer, 1, IO_SDCARD_BLOCK_SIZE, sdcard_ptr->COM_DEVICE);
    
    /* Wait for transfer complete */
    if (SDHC_OK != fflush (sdcard_ptr->COM_DEVICE))
    {
        return FALSE;
    } 
    
    return TRUE;
}

/* EOF */
