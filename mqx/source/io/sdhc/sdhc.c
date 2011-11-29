/**HEADER********************************************************************
* 
* Copyright (c) 2009 Freescale Semiconductor;
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
* $FileName: sdhc.c$
* $Version : 3.7.2.0$
* $Date    : Feb-7-2011$
*
* Comments:
*
*   The file contains low level SDHC driver functions.
*
*END************************************************************************/

#include <mqx.h>
#include <bsp.h>
#include <io_prv.h>
#include <fio_prv.h>
#include <string.h>
#include <sdhc.h>
#include <sdhc_prv.h>
 
/* GLOBAL VARIABLES */
uint_32 gul_sdhc_sd_rca;   /* Relative Card Address */
uint_32 int_done_sdhc;
uint_32 gul_csd[8];        /* response 128bit CSD */
uint_32 gul_sector_address;
boolean gb_card_inserted;
static void _sdhc_isr(pointer);


/*FUNCTION****************************************************************
* 
* Function Name    : _sdhc_isr
* Returned Value   : 
* Comments         : 
*   card detected ISR
*END*********************************************************************/

static void _sdhc_isr(pointer param)
{  
   MPC5125_SDHC_STRUCT_PTR   sdhc_ptr = &((VMPC5125_STRUCT_PTR) MPC5125_GET_IMMR() )->SDHC1;
   MPC5125_IO_CONTROL_STRUCT_PTR ioc_ptr = MPC5125_IOC_ADDR();
   
   if(sdhc_ptr->STATUS & SDHC_STATUS_CARD_INSERTION_MASK)
   {
      gb_card_inserted = TRUE;
      sdhc_ptr->STATUS |= SDHC_STATUS_CARD_INSERTION_MASK;
      sdhc_ptr->INT_CNTR = SDHC_INT_CNTR_CARD_REMOVAL_EN_MASK;
      ioc_ptr->SDHC1_D3    = IO_CONTROL_FUNCTION_0|IO_CONTROL_PULL_UP|IO_CONTROL_SLEW_RATE_3;
   }
   if( sdhc_ptr->STATUS & SDHC_STATUS_CARD_REMOVAL_MASK)
   {
      gb_card_inserted = FALSE;
      sdhc_ptr->STATUS |= SDHC_STATUS_CARD_REMOVAL_MASK;
      sdhc_ptr->INT_CNTR = SDHC_INT_CNTR_SCARD_INSERTION_EN_MASK;
      ioc_ptr->SDHC1_D3    = IO_CONTROL_FUNCTION_0|IO_CONTROL_PULL_DOWN|IO_CONTROL_SLEW_RATE_3;
   } 
}

/*FUNCTION****************************************************************
* 
* Function Name    : _sdhc_card_detect
* Returned Value   : TRUE if card is inserted FALSE if card is detached
* Comments         : 
*   
*END*********************************************************************/
boolean _sdhc_card_detect()
{
 return gb_card_inserted;  
}
/*FUNCTION****************************************************************
* 
* Function Name    : _sdhc_reset
* Returned Value   : 
* Comments         : 
*   
*END*********************************************************************/
static void _sdhc_reset(MPC5125_SDHC_STRUCT_PTR sdhc_ptr)
{
    SDHC_COMMAND_STRUCT command;
    /* Reset SDHC */
    sdhc_ptr->STR_STP_CLK = SDHC_STR_STP_CLK_SDHC_RESET_MASK;
    sdhc_ptr->STR_STP_CLK = SDHC_STR_STP_CLK_SDHC_RESET_MASK | SDHC_STR_STP_CLK_STOP_CLK_MASK;
    sdhc_ptr->STR_STP_CLK = SDHC_STR_STP_CLK_STOP_CLK_MASK;
    sdhc_ptr->STR_STP_CLK = SDHC_STR_STP_CLK_STOP_CLK_MASK;
    sdhc_ptr->STR_STP_CLK = SDHC_STR_STP_CLK_STOP_CLK_MASK;
    sdhc_ptr->STR_STP_CLK = SDHC_STR_STP_CLK_STOP_CLK_MASK;
    sdhc_ptr->STR_STP_CLK = SDHC_STR_STP_CLK_STOP_CLK_MASK;
    sdhc_ptr->STR_STP_CLK = SDHC_STR_STP_CLK_STOP_CLK_MASK;
    sdhc_ptr->STR_STP_CLK = SDHC_STR_STP_CLK_STOP_CLK_MASK;  
    sdhc_ptr->STR_STP_CLK = SDHC_STR_STP_CLK_STOP_CLK_MASK;
       
    /* wait for the clock to really have stopped */
    while (sdhc_ptr->STATUS & SDHC_STATUS_CARD_BUS_CLK_RUN_MASK)
    {
    	sdhc_ptr->STR_STP_CLK = SDHC_STR_STP_CLK_STOP_CLK_MASK;
    }    
    sdhc_ptr->STR_STP_CLK = 0;
    
    /* Enable sdhc clocks */
    sdhc_ptr->STR_STP_CLK |= SDHC_STR_STP_CLK_START_CLK_MASK;
    
    /* wait for the clock to really have started */
    while (!(sdhc_ptr->STATUS & SDHC_STATUS_CARD_BUS_CLK_RUN_MASK))
    {
    	sdhc_ptr->STR_STP_CLK = SDHC_STR_STP_CLK_START_CLK_MASK;
    }
    
    /* Set the sdhc initial baud rate divider and start */
    sdhc_ptr->CLK_RATE = 0x040F;
    sdhc_ptr->READ_TO = 0xFFFF; /*Set Time out to maximum */
    sdhc_ptr->RES_TO = 0xFF;
    sdhc_ptr->NOB = 1;
    sdhc_ptr->BLK_LEN  = 512;
    
    /* Reset the card with CMD0/CMD520*/
    command.COMMAND = GO_IDLE_STATE;
    command.ARGUMENT = 0x0;
    command.CONFIGURATION = SDHC_CMD_DAT_CONT_INIT_MASK;
    _sdhc_send_cmd_wait_resp(sdhc_ptr, &command);
}
/*FUNCTION****************************************************************
* 
* Function Name    : _sdhc_read_resp
* Returned Value   : 
* Comments         : 
*   
*END*********************************************************************/
static void _sdhc_read_resp
(
   MPC5125_SDHC_STRUCT_PTR sdhc_ptr, 
   int len, 
   uint_16 **dst
)
{
    int i;
    for (i = 0; i < len; i++)
    {
        uint_32 reg;
        reg = sdhc_ptr->RES_FIFO;
        gul_csd[i] = (uint_16)(reg & 0xFFFF);
    }     
}

/*FUNCTION****************************************************************
* 
* Function Name    : _sdhc_read_resp32of48
* Returned Value   : 
* Comments         : 
*   
*END*********************************************************************/
static void _sdhc_read_resp32of48
      (
      MPC5125_SDHC_STRUCT_PTR sdhc_ptr,
      SDHC_COMMAND_STRUCT_PTR command_ptr
      )
{
    uint_32 uw_upper_word, uw_middle_word, uw_lower_word;
      
    command_ptr->RESPONSE = 0x00000000;
    uw_upper_word    = sdhc_ptr->RES_FIFO;
    uw_middle_word   = sdhc_ptr->RES_FIFO;
    uw_lower_word    = sdhc_ptr->RES_FIFO;

    command_ptr->RESPONSE = (uw_upper_word << 24) & 0xFF000000;
    command_ptr->RESPONSE = command_ptr->RESPONSE | (uw_middle_word << 8);
    command_ptr->RESPONSE = command_ptr->RESPONSE| ((uw_lower_word  >> 8) & 0xFF );

}
/*FUNCTION****************************************************************
* 
* Function Name    : _sdhc_send_cmd_wait_resp
* Returned Value   : 
* Comments         : 
*   
*END*********************************************************************/
static int _sdhc_send_cmd_wait_resp
(
      MPC5125_SDHC_STRUCT_PTR sdhc_ptr,
      SDHC_COMMAND_STRUCT_PTR command_ptr
)
{
    int len = 8;
    uint_16 *dst = NULL;
    uint_32 resp = DEFAULT_RESPONSE;
    _sdhc_send_cmd(sdhc_ptr,command_ptr);
    if((!(command_ptr->CONFIGURATION & SDHC_FMT_RESP_136BIT)) && (!(command_ptr->CONFIGURATION & SDHC_FMT_RESP_48BIT_CRC)))
    {
        return 0;
    }

    if((command_ptr->CONFIGURATION & SDHC_FMT_RESP_136BIT) && (!(command_ptr->CONFIGURATION & SDHC_FMT_RESP_48BIT_CRC)))
    {
        _sdhc_read_resp(sdhc_ptr, len, &dst);
    }
    else
    {
        _sdhc_read_resp32of48(sdhc_ptr,command_ptr);
    }

    return 0;
}
/*FUNCTION****************************************************************
* 
* Function Name    : _sdhc_voltage_validation
* Returned Value   : 
* Comments         : 
*   
*END*********************************************************************/
static uint_32 _sdhc_voltage_validation(MPC5125_SDHC_STRUCT_PTR sdhc_ptr)
{
    volatile uint_32 resp,result;
    int no_of_IO_functions;
    SDHC_COMMAND_STRUCT command;

    while(1)
    {
        command.COMMAND = IO_SEND_OP_COND;
        command.ARGUMENT = 0x0;
        command.CONFIGURATION = SDHC_FMT_RESP_R4;
        _sdhc_send_cmd_wait_resp(sdhc_ptr, &command);
        no_of_IO_functions = (int)((resp & 0x70000000) >> 28);

        /* It is SDIO and have IO function */
        if ((sdhc_ptr->STATUS & SDHC_STATUS_END_CMD_RESP_MASK) && (no_of_IO_functions > 0) && !(sdhc_ptr->STATUS & SDHC_STATUS_TIME_OUT_RESP_MASK))

        {
            command.COMMAND = IO_SEND_OP_COND;
            command.ARGUMENT = 0x00FF8000;
            command.CONFIGURATION = SDHC_FMT_RESP_R4;
            _sdhc_send_cmd_wait_resp(sdhc_ptr,&command);

            if(command.RESPONSE & 0x08000000)
            {
                result = SDHC_COMBO; 
                /* that is,SDIO +SD memory,need to set operation voltage to memory portion as well */
                
                command.COMMAND = APP_CMD;
                command.ARGUMENT = 0x0;
                command.CONFIGURATION = SDHC_FMT_RESP_R1;
                _sdhc_send_cmd_wait_resp(sdhc_ptr, &command);
                
                command.COMMAND = SD_APP_OP_COND;
                command.ARGUMENT = 0x00FF8000;
                command.CONFIGURATION = SDHC_FMT_RESP_R3;
                _sdhc_send_cmd_wait_resp(sdhc_ptr, &command); /* ACMD41 */
            }
            else
            {
                result  = SDHC_SDIO;
            }

            if (command.RESPONSE & 0x80000000) /* Card ready */
                break;
        }
        else
        {
            while (1)
            {
                command.COMMAND = CMD8;
                command.ARGUMENT = 0x1AA;
                command.CONFIGURATION = SDHC_FMT_RESP_48BIT_CRC;
                _sdhc_send_cmd_wait_resp(sdhc_ptr, &command);
               
                if ((sdhc_ptr->STATUS & SDHC_STATUS_END_CMD_RESP_MASK) &&
                    (!(sdhc_ptr->STATUS & SDHC_STATUS_TIME_OUT_RESP_MASK)))
                {
                
                  command.COMMAND = APP_CMD;
                  command.ARGUMENT = 0x0;
                  command.CONFIGURATION = SDHC_FMT_RESP_R1;
                	_sdhc_send_cmd_wait_resp(sdhc_ptr, &command);
                  
                  if ((sdhc_ptr->STATUS & SDHC_STATUS_END_CMD_RESP_MASK) &&
                    (!(sdhc_ptr->STATUS & SDHC_STATUS_TIME_OUT_RESP_MASK)))
                  {
                      
                      command.COMMAND = SD_APP_OP_COND;
                      command.ARGUMENT = 0x40FF8000;
                      command.CONFIGURATION = SDHC_FMT_RESP_R3;
                      _sdhc_send_cmd_wait_resp(sdhc_ptr, &command);
                      result  = SDHC_SD;
                      if (command.RESPONSE & 0x80000000) /* card ready */
                          break;
                  }
                }
                else
                {    
                  command.COMMAND = APP_CMD;
                  command.ARGUMENT = 0x0;
                  command.CONFIGURATION = SDHC_FMT_RESP_R1;
                  _sdhc_send_cmd_wait_resp(sdhc_ptr, &command);
                  
                  if ((sdhc_ptr->STATUS & SDHC_STATUS_END_CMD_RESP_MASK) &&
                    (!(sdhc_ptr->STATUS & SDHC_STATUS_TIME_OUT_RESP_MASK)))
                  {
                      command.COMMAND = SD_APP_OP_COND;
                      command.ARGUMENT = 0x00FF8000;
                      command.CONFIGURATION = SDHC_FMT_RESP_R3;
                      _sdhc_send_cmd_wait_resp(sdhc_ptr, &command);
                      result  = SDHC_SD;
                      if (command.RESPONSE & 0x80000000) /* card ready */
                          break;
                  }
                  else
                  {
                      while(1)
                      {
                          command.COMMAND = SEND_OP_COND;
                          command.ARGUMENT = 0x00FF8000;
                          command.CONFIGURATION = SDHC_FMT_RESP_R3;
                          _sdhc_send_cmd_wait_resp(sdhc_ptr, &command);
                  
                          if ((sdhc_ptr->STATUS & SDHC_STATUS_END_CMD_RESP_MASK) &&
                          (!(sdhc_ptr->STATUS & SDHC_STATUS_TIME_OUT_RESP_MASK)))
                          {
                              result  = SDHC_MMC;
                              if (command.RESPONSE & 0x80000000)
                                  break;
                          }
                          else
                          {
                              break;
                          }
                      }
                      break;
                  }
                }
            }
            break; 
        } /* else for IO function */
    } /* end outermost while -- 1 */
return result;
}

/*FUNCTION****************************************************************
* 
* Function Name    : _sdhc_get_card_status
* Returned Value   : 
* Comments         : 
*   
*END*********************************************************************/ 
uint_32 _sdhc_get_card_status 
(
      MPC5125_SDHC_STRUCT_PTR sdhc_ptr, 
      uint_32 sdhc_sd_rca,
      uint_32 card_type
)
{
    uint_32 ul_resp = DEFAULT_RESPONSE;
    SDHC_COMMAND_STRUCT command;
    
    if((card_type == SDHC_MMC) || (card_type == SDHC_SD))
    {
        command.COMMAND = SEND_STATUS;
        command.ARGUMENT = sdhc_sd_rca;
        command.CONFIGURATION = SDHC_FMT_RESP_R1;
        _sdhc_send_cmd_wait_resp(sdhc_ptr,&command);
        ul_resp = command.RESPONSE;
    }
    return ul_resp;
}
/*FUNCTION****************************************************************
* 
* Function Name    : _sdhc_card_registry
* Returned Value   : 
* Comments         : 
*   
*END*********************************************************************/
static void _sdhc_card_registry
   (
      MPC5125_SDHC_STRUCT_PTR sdhc_ptr,
      uint_32 card_type
   )
{
    uint_32 resp;
    SDHC_COMMAND_STRUCT command;
    
    gul_sdhc_sd_rca = 0x00000000;

    if((card_type == SDHC_SD) || (card_type == SDHC_MMC))
    {
        while (1)
        {
            /*  Get CID register - CMD2 */
            command.COMMAND = ALL_SEND_CID;
            command.ARGUMENT = 0x00;
            command.CONFIGURATION = SDHC_FMT_RESP_R2;
            _sdhc_send_cmd_wait_resp(sdhc_ptr, &command);

            if (!(sdhc_ptr->STATUS & SDHC_STATUS_TIME_OUT_RESP_MASK))
                break;
        }
    }
    
    if((card_type == SDHC_SD) || (card_type == SDHC_SDIO) || (card_type == SDHC_COMBO))
    {
        command.COMMAND = SEND_RELATIVE_ADDR;
        command.ARGUMENT = 0x00;
        command.CONFIGURATION = SDHC_FMT_RESP_R1;
        _sdhc_send_cmd_wait_resp(sdhc_ptr, &command);
        gul_sdhc_sd_rca = command.RESPONSE;
    }
    
    if(card_type == SDHC_MMC)
    {
        gul_sdhc_sd_rca = 0x1 << 16;
        command.COMMAND = SEND_RELATIVE_ADDR;
        command.ARGUMENT = gul_sdhc_sd_rca;
        command.CONFIGURATION = SDHC_FMT_RESP_R1;
        _sdhc_send_cmd_wait_resp(sdhc_ptr, &command);
    }

    if(card_type != SDHC_SDIO)
    {
    	command.COMMAND = SEND_CSD;
      command.ARGUMENT = gul_sdhc_sd_rca;
      command.CONFIGURATION = SDHC_FMT_RESP_R2;
      _sdhc_send_cmd_wait_resp(sdhc_ptr, &command);
      
    }

    command.COMMAND = SEL_DESEL_CARD;
    command.ARGUMENT = gul_sdhc_sd_rca;
    command.CONFIGURATION = (SDHC_CMD_DAT_CONT_INIT_MASK|SDHC_FMT_RESP_R1);
    _sdhc_send_cmd_wait_resp(sdhc_ptr, &command);
    
    /* 4-bit mode data transfer needs code below. */
    if( SDHC_BIT_MODE == BIT_4_MODE)
    {
    	if(card_type == SDHC_SD)
      {
        
        command.COMMAND = APP_CMD;
        command.ARGUMENT = gul_sdhc_sd_rca;
        command.CONFIGURATION = SDHC_FMT_RESP_R1;
        _sdhc_send_cmd_wait_resp(sdhc_ptr, &command);
      
        if ((sdhc_ptr->STATUS & SDHC_STATUS_END_CMD_RESP_MASK) &&
                          (!(sdhc_ptr->STATUS & SDHC_STATUS_TIME_OUT_RESP_MASK)))
          {
              command.COMMAND = CMD6;
              command.ARGUMENT = 0x2;
              command.CONFIGURATION = SDHC_FMT_RESP_R1; 
              _sdhc_send_cmd_wait_resp(sdhc_ptr, &command);
          }
      }
      else if(card_type== SDHC_MMC)
      {
        command.COMMAND = CMD6;
        command.ARGUMENT = 0x03B70100;
        command.CONFIGURATION = SDHC_FMT_RESP_R1;
        _sdhc_send_cmd_wait_resp(sdhc_ptr, &command);
      }
      else if(card_type == SDHC_SDIO)
      {
      	/* 
      	** Update by Lemon on Feb.26,2009
      	** When SDIO works at 4-bit mode, write CD bit in CCR to disable pull up resistor on DAT3
      	*/
      	command.COMMAND = IO_RW_DIRECT;
         command.ARGUMENT = 0x80000E82;
         command.CONFIGURATION = SDHC_FMT_RESP_R5;
      	_sdhc_send_cmd_wait_resp(sdhc_ptr, &command);
      }
    }
}
/*FUNCTION****************************************************************
* 
* Function Name    : _sdhc_init
* Returned Value   : MQX error code
* Comments         :
*    sdhc registers initialization and card detection.
*
*END*********************************************************************/
static int_32 _sdhc_init 
    (
        MPC5125_SDHC_STRUCT_PTR        sdhc_ptr, 
        MPC5125_SDHC_INFO_STRUCT_PTR   sdhc_info_ptr,
        MPC5125_SDHC_INIT_STRUCT_CPTR  sdhc_init_ptr
    )
{
    sdhc_info_ptr->CARD = SDHC_NONE;
    /* init GPIO - to prevent unwanted clocks on bus */
    if (_bsp_sdhc_io_init (sdhc_init_ptr->CHANNEL,0) != MQX_OK)
    {
        return IO_ERROR_DEVICE_INVALID;
    }
    _sdhc_reset(sdhc_ptr);
    sdhc_info_ptr->CARD = _sdhc_voltage_validation(sdhc_ptr);   /* TYPE OF CARD DETECT */
    _sdhc_card_registry(sdhc_ptr,sdhc_info_ptr->CARD);          /* IDENTIFY CARD ID and ADDRESS */
    
    if (sdhc_info_ptr->CARD != SDHC_NONE)   
    {
         /* Init GPIO again */
         if (_bsp_sdhc_io_init (sdhc_init_ptr->CHANNEL,1) != MQX_OK)
       {
           return IO_ERROR_DEVICE_INVALID;
       }
    }
    sdhc_ptr->INT_CNTR = 0x00008000;
    _int_install_isr(MPC5125_SDHC1_VECTOR,_sdhc_isr,NULL);
    _mpc5125_enable_interrupt(MPC5125_SDHC1_VECTOR);
    return SDHC_OK;
}

/*FUNCTION****************************************************************
* 
* Function Name    : _sdhc_send_cmd
* Returned Value   : 0 on success, 1 on error, -1 on timeout
* Comments         :
*    One SDHC command transaction.
*
*END*********************************************************************/
static int _sdhc_send_cmd
(
      MPC5125_SDHC_STRUCT_PTR sdhc_ptr,
      SDHC_COMMAND_STRUCT_PTR command
    
)
{
    uint_32 ul_reg;
     
#if INTR_MODE
    sdhc_ptr->INT_CNTR = SDHC_INT_CNTR_END_CMD_RES_MASK;
#else
    sdhc_ptr->INT_CNTR = SDHC_INT_CNTR_NO_INTERRUPT;
#endif

    /* Clear all the status bits */
    sdhc_ptr->STATUS = SDHC_STATUS_ALL_BITS_ONE;
#if INTR_MODE
    int_done_sdhc = 0x0;
#endif
    ul_reg = sdhc_ptr->STATUS;
    sdhc_ptr->ARG = command->ARGUMENT;
    sdhc_ptr->CMD = command->COMMAND;
#if CLOCK_CYCLE_PREFIX 
    sdhc_ptr->CMD_DAT_CONT = command->CONFIGURATION | SDHC_CMD_DAT_CONT_INIT_MASK;
#else
    sdhc_ptr->CMD_DAT_CONT = command->CONFIGURATION;
#endif

    while(1)
    {
        ul_reg=sdhc_ptr->STATUS;
        if(sdhc_ptr->STATUS & SDHC_STATUS_END_CMD_RESP_MASK)
            break;
    }
    
    ul_reg = sdhc_ptr->STATUS;
    if(sdhc_ptr->STATUS & SDHC_STATUS_TIME_OUT_RESP_MASK ) 
    {
      return -1;
    }
        
    if(sdhc_ptr->STATUS & SDHC_STATUS_RESP_CRC_ERR_MASK)
    {
      return 1;
    }
        
return 0;
}

/*FUNCTION****************************************************************
* 
* Function Name    : _sdhc_install
* Returned Value   : MQX error code
* Comments         :
*    Install an sdhc device.
*
*END*********************************************************************/
_mqx_int _sdhc_install
    (
        /* [IN] A string that identifies the device for fopen */
        char_ptr               identifier,
        
        /* [IN] The I/O init data pointer */
        MPC5125_SDHC_INIT_STRUCT_CPTR sdhc_init_ptr
    )
{
    MPC5125_SDHC_DEVICE_STRUCT_PTR    sdhc_device_ptr;
    _mqx_uint                  result;

    /* Check parameters */
    if ((NULL == identifier) || (NULL == sdhc_init_ptr))
    {
        return MQX_INVALID_PARAMETER;
    }

    /* Check previous installation */
    _int_disable();

    /* Create device context */
    sdhc_device_ptr = _mem_alloc_system_zero ((_mem_size) sizeof (MPC5125_SDHC_DEVICE_STRUCT));
    if (NULL == sdhc_device_ptr) 
    {
        _int_enable();
        return MQX_OUT_OF_MEMORY;
    }
    _mem_set_type (sdhc_device_ptr, MEM_TYPE_IO_ESDHC_DEVICE_STRUCT); 

    /* Install device */
    result = _io_dev_install_ext(identifier,
        _sdhc_open,
        _sdhc_close,
        _sdhc_read,
        _sdhc_write,
        _sdhc_ioctl, 
        _sdhc_uninstall, 
        (pointer)sdhc_device_ptr);
    
    /* Context initialization or cleanup */
    if (MQX_OK == result)
    {
        sdhc_device_ptr->INIT = sdhc_init_ptr;
        sdhc_device_ptr->COUNT = 0;
    }
    else
    {
        _mem_free (sdhc_device_ptr);
    }
    _int_enable();
    
    return result;
}


/*FUNCTION****************************************************************
*
* Function Name    : _sdhc_uninstall
* Returned Value   : MQX error code
* Comments         :
*    Uninstall an sdhc device.
*
*END**********************************************************************/

_mqx_int _sdhc_uninstall
    (
        /* [IN/OUT] The device to uninstall */            
        IO_DEVICE_STRUCT_PTR dev_ptr
    )
{
    MPC5125_SDHC_DEVICE_STRUCT_PTR  sdhc_device_ptr;
    
    /* Check parameters */
    if (NULL == dev_ptr)
    {
        return IO_DEVICE_DOES_NOT_EXIST;
    }
    sdhc_device_ptr = dev_ptr->DRIVER_INIT_PTR;
    if (NULL == sdhc_device_ptr)
    {
        return IO_ERROR_DEVICE_INVALID;
    }

    /* Uninstall only when not opened */
    if (sdhc_device_ptr->COUNT)
    {
        return IO_ERROR_DEVICE_BUSY;
    }
    /* Cleanup */
    _mem_free (sdhc_device_ptr);
    dev_ptr->DRIVER_INIT_PTR = NULL;
    
    return IO_OK;
}

/*FUNCTION****************************************************************
* 
* Function Name    : _sdhc_open  
* Returned Value   : MQX error code
* Comments         :
*    This function exclusively opens the sdhc device.
*
*END*********************************************************************/
_mqx_int _sdhc_open
    (
        /* [IN/OUT] sdhc file descriptor */
        MQX_FILE_PTR        sdhc_fd_ptr,        
        /* [IN] The remaining portion of the name of the device */
        char_ptr            open_name_ptr,
        /* [IN] The flags to be used during operation */
        char_ptr            open_flags_ptr
    )
{
    IO_DEVICE_STRUCT_PTR           io_dev_ptr;
    MPC5125_SDHC_INFO_STRUCT_PTR   sdhc_info_ptr;
    MPC5125_SDHC_DEVICE_STRUCT_PTR sdhc_device_ptr;
    MPC5125_SDHC_INIT_STRUCT_CPTR  sdhc_init_ptr;
    MPC5125_SDHC_STRUCT_PTR        sdhc_ptr;
    int_32                         result;
    /* Check parameters */
    if (NULL == sdhc_fd_ptr)
    {
        return MQX_INVALID_PARAMETER;
    }
    io_dev_ptr = sdhc_fd_ptr->DEV_PTR;
    if (NULL == io_dev_ptr)
    {
        return IO_DEVICE_DOES_NOT_EXIST;
    }
    sdhc_device_ptr = io_dev_ptr->DRIVER_INIT_PTR;
    if (NULL == sdhc_device_ptr)
    {
        return IO_ERROR_DEVICE_INVALID;
    }
    sdhc_init_ptr = sdhc_device_ptr->INIT;
    if (NULL == sdhc_init_ptr)
    {
        return IO_ERROR_DEVICE_INVALID;
    }
    /* Get register base */
    sdhc_ptr = _bsp_get_sdhc_base_address (sdhc_init_ptr->CHANNEL);
    if (NULL == sdhc_ptr)
    {
        return IO_ERROR_DEVICE_INVALID;
    }
    /* Exclusive access till close */
    _int_disable();
    if (sdhc_device_ptr->COUNT) 
    {
        /* Device is already opened */
        _int_enable();
        return MQX_IO_OPERATION_NOT_AVAILABLE;
    }
    sdhc_device_ptr->COUNT = 1;
    _int_enable();

    /* Set device info */
    sdhc_info_ptr = (MPC5125_SDHC_INFO_STRUCT_PTR)_mem_alloc_system_zero ((_mem_size) sizeof (MPC5125_SDHC_INFO_STRUCT));
    if (NULL == sdhc_info_ptr) 
    {
        return MQX_OUT_OF_MEMORY;
    }
    _mem_set_type (sdhc_info_ptr, MEM_TYPE_IO_ESDHC_INFO_STRUCT);
    sdhc_fd_ptr->DEV_DATA_PTR = sdhc_info_ptr;
    result= _sdhc_init (sdhc_ptr, sdhc_info_ptr, sdhc_init_ptr);
    
    return result;
}

/*FUNCTION****************************************************************
* 
* Function Name    : _sdhc_close  
* Returned Value   : MQX error code
* Comments         :
*    This function closes opened sdhc device.
*
*END*********************************************************************/
_mqx_int _sdhc_close
    (
        /* [IN/OUT] Opened file pointer for sdhc */            
        MQX_FILE_PTR        sdhc_fd_ptr
    )
{
    IO_DEVICE_STRUCT_PTR            io_dev_ptr;
    MPC5125_SDHC_DEVICE_STRUCT_PTR  sdhc_device_ptr;
    MPC5125_SDHC_INIT_STRUCT_CPTR   sdhc_init_ptr;
    MPC5125_SDHC_STRUCT_PTR         sdhc_ptr;
    
    /* Check parameters */
    if (NULL == sdhc_fd_ptr)
    {
        return MQX_INVALID_PARAMETER;
    }
    io_dev_ptr = (IO_DEVICE_STRUCT_PTR)sdhc_fd_ptr->DEV_PTR;
    if (NULL == io_dev_ptr)
    {
        return IO_DEVICE_DOES_NOT_EXIST;
    }
    sdhc_device_ptr = io_dev_ptr->DRIVER_INIT_PTR;
    if (NULL == sdhc_device_ptr)
    {
        return IO_ERROR_DEVICE_INVALID;
    }
    sdhc_init_ptr = sdhc_device_ptr->INIT;
    if (NULL == sdhc_init_ptr)
    {
        return IO_ERROR_DEVICE_INVALID;
    }
    /* Get register base */
    sdhc_ptr = _bsp_get_sdhc_base_address (sdhc_init_ptr->CHANNEL);
    if (NULL == sdhc_ptr)
    {
        return IO_ERROR_DEVICE_INVALID;
    }  
    /* Disable sdhc device */
    _int_disable();
    if (--sdhc_device_ptr->COUNT == 0) 
    {
    /* STOP SDHC */
    sdhc_ptr->STR_STP_CLK |= SDHC_STR_STP_CLK_STOP_CLK_MASK; 
    /* wait for the clock to really have stopped */
    while (sdhc_ptr->STATUS & SDHC_STATUS_CARD_BUS_CLK_RUN_MASK)
    {
    	sdhc_ptr->STR_STP_CLK = SDHC_STR_STP_CLK_STOP_CLK_MASK;
    }            
        _mem_free (sdhc_fd_ptr->DEV_DATA_PTR);
        sdhc_fd_ptr->DEV_DATA_PTR = NULL;
    }
    _int_enable();        
    return SDHC_OK;
}
    
/*FUNCTION****************************************************************
* 
* Function Name    : _sdhc_ioctl
* Returned Value   : MQX error code
* Comments         : 
*    This function performs miscellaneous services for the sdhc I/O device.  
*
*END*********************************************************************/
_mqx_int _sdhc_ioctl
    (
        /* [IN] Opened file pointer for sdhc */
        MQX_FILE_PTR        sdhc_fd_ptr,        
        /* [IN] The command to perform */
        uint_32             cmd,        
        /* [IN/OUT] Parameters for the command */
        pointer             param_ptr
    )
{
    IO_DEVICE_STRUCT_PTR            io_dev_ptr;
    MPC5125_SDHC_INFO_STRUCT_PTR    sdhc_info_ptr;
    MPC5125_SDHC_DEVICE_STRUCT_PTR  sdhc_device_ptr;
    MPC5125_SDHC_INIT_STRUCT_CPTR   sdhc_init_ptr;
    MPC5125_SDHC_STRUCT_PTR         sdhc_ptr;
    int_32                          val;
    uint_32                         result = SDHC_OK;
    uint_32_ptr                     param32_ptr = param_ptr;
   
    /* Check parameters */
    if (NULL == sdhc_fd_ptr)
    {
        return MQX_INVALID_PARAMETER;
    }
    io_dev_ptr = (IO_DEVICE_STRUCT_PTR)sdhc_fd_ptr->DEV_PTR;
    if (NULL == io_dev_ptr)
    {
        return IO_DEVICE_DOES_NOT_EXIST;
    }
    sdhc_info_ptr = (MPC5125_SDHC_INFO_STRUCT_PTR)sdhc_fd_ptr->DEV_DATA_PTR;
    if (NULL == sdhc_info_ptr)
    {
        return IO_DEVICE_DOES_NOT_EXIST;
    }
    sdhc_device_ptr = io_dev_ptr->DRIVER_INIT_PTR;
    if (NULL == sdhc_device_ptr)
    {
        return IO_ERROR_DEVICE_INVALID;
    }
    sdhc_init_ptr = sdhc_device_ptr->INIT;
    if (NULL == sdhc_init_ptr)
    {
        return IO_ERROR_DEVICE_INVALID;
    }
    
    /* Get register base */
    sdhc_ptr = _bsp_get_sdhc_base_address (sdhc_init_ptr->CHANNEL);
    if (NULL == sdhc_ptr)
    {
        return IO_ERROR_DEVICE_INVALID;
    }
    
    switch (cmd) 
    {
        case IO_IOCTL_SDHC_INIT:

            result = _sdhc_init(sdhc_ptr, sdhc_info_ptr, sdhc_init_ptr);
            break;
        
        case IO_IOCTL_SDHC_SEND_COMMAND:
            _sdhc_send_cmd_wait_resp (sdhc_ptr,(SDHC_COMMAND_STRUCT_PTR)(param32_ptr));
            if (sdhc_ptr->STATUS & SDHC_STATUS_RESP_CRC_ERR_MASK)
            {
                result = SDHC_ERROR_COMMAND_FAILED;
            }
            if (sdhc_ptr->STATUS & SDHC_STATUS_TIME_OUT_RESP_MASK)
            {
                result = SDHC_ERROR_COMMAND_TIMEOUT;
            }
            break;
        case IO_IOCTL_SDHC_GET_BLOCK_SIZE:
            if (NULL == sdhc_ptr) 
            {
                result = MQX_INVALID_PARAMETER;
            } 
            else 
            {
                /* Get actual sdhc block size */
                *param32_ptr = (sdhc_ptr->BLK_LEN & SDHC_BLK_LEN_BLOCK_LENGTH_MASK) >> SDHC_BLK_LEN_BLOCK_LENGTH_SHIFT;
            }       
            break;
            
        case IO_IOCTL_SDHC_SET_BUS_WIDTH:
            if (NULL == param32_ptr) 
            {
                result = MQX_INVALID_PARAMETER;
            } 
            else 
            {
                /* Set actual SDHC bus width */
            if (SDHC_BUS_WIDTH_1 == *param32_ptr)
                    {
                        sdhc_ptr->CMD_DAT_CONT &= (~ SDHC_CMD_DAT_CONT_BUS_WIDTH_MASK);
                        sdhc_ptr->CMD_DAT_CONT |= SDHC_CMD_DAT_CONT_BUS_WIDTH(0x00);
                    }
                    else if (SDHC_BUS_WIDTH_4 == *param32_ptr)
                    {
                        sdhc_ptr->CMD_DAT_CONT &= (~ SDHC_CMD_DAT_CONT_BUS_WIDTH_MASK);
                        sdhc_ptr->CMD_DAT_CONT |= SDHC_CMD_DAT_CONT_BUS_WIDTH(0x10);
                    }
                    else
                    {
                        result = SDHC_ERROR_INVALID_BUS_WIDTH; 
                    }
                
              
            }       
            break;
        case IO_IOCTL_SDHC_SET_BLOCK_SIZE:
            if (NULL == param32_ptr) 
            {
                result = MQX_INVALID_PARAMETER;
            } 
            else 
            {
                /* Set actual sdhc block size */
                    if (*param32_ptr > 0x0FFF)
                    {
                        result = MQX_INVALID_PARAMETER;
                    }
                    else
                    {
                        sdhc_ptr->BLK_LEN &= (~ SDHC_BLK_LEN_BLOCK_LENGTH_MASK); 
                        sdhc_ptr->BLK_LEN |= SDHC_BLK_LEN_BLOCK_LENGTH(*param32_ptr);
                    } 
            break;
  
        case IO_IOCTL_SDHC_GET_BUS_WIDTH:
            if (NULL == param32_ptr) 
            {
                result = MQX_INVALID_PARAMETER;
            } 
            else 
            {
                /*  Get actual sdhc bus width  */
                val = (sdhc_ptr->CMD_DAT_CONT & SDHC_CMD_DAT_CONT_BUS_WIDTH_MASK ) >> SDHC_CMD_DAT_CONT_BUS_WIDTH_SHIFT ;
                if (1 == val)
                {
                    *param32_ptr = SDHC_BUS_WIDTH_1;
                }
                else if (2== val)
                {
                    *param32_ptr = SDHC_BUS_WIDTH_4;
                }
 
                else
                {
                    result = SDHC_ERROR_INVALID_BUS_WIDTH; 
                }
            }            
      
            break;
        
        case IO_IOCTL_SDHC_GET_CARD:
            if (NULL == param32_ptr) 
            {
                result = MQX_INVALID_PARAMETER;
            } 
            else 
            {
                *param32_ptr = sdhc_info_ptr->CARD;
            }
            break;         
         case IO_IOCTL_FLUSH_OUTPUT:
            /* check transfer error */
            if (sdhc_ptr->STATUS & (SDHC_STATUS_RESP_CRC_ERR_MASK | SDHC_STATUS_READ_CRC_ERR_MASK  | SDHC_STATUS_WRITE_CRC_ERR_MASK | SDHC_STATUS_TIME_OUT_RESP_MASK | SDHC_STATUS_TIME_OUT_READ_MASK))
            {
                sdhc_ptr->STATUS |= SDHC_STATUS_RESP_CRC_ERR_MASK | SDHC_STATUS_READ_CRC_ERR_MASK  | SDHC_STATUS_WRITE_CRC_ERR_MASK | SDHC_STATUS_TIME_OUT_RESP_MASK | SDHC_STATUS_TIME_OUT_READ_MASK;
                result = SDHC_ERROR_DATA_TRANSFER;
            }
            sdhc_ptr->STATUS |= SDHC_STATUS_WRITE_OP_DONE_MASK | SDHC_STATUS_READ_OP_DONE_MASK | SDHC_STATUS_BUF_READ_READY_MASK  | SDHC_STATUS_BUF_WRITE_READY_MASK;
            break;
        
        default:
            result = IO_ERROR_INVALID_IOCTL_CMD;
            break;
    }
    }
    return result;
}

/*FUNCTION****************************************************************
* 
* Function Name    : _sdhc_read
* Returned Value   : Returns the number of bytes received or IO_ERROR
* Comments         : 
*   Reads the data into provided array.
*
*END*********************************************************************/
_mqx_int _sdhc_read
    (
        /* [IN] Opened file pointer for sdhc  */
        FILE_DEVICE_STRUCT_PTR sdhc_fd_ptr,

        /* [OUT] Where the characters are to be stored */
        char_ptr               data_ptr,

        /* [IN] The number of bytes to read */
        _mqx_int               n
    )
{
    IO_DEVICE_STRUCT_PTR            io_dev_ptr;
    MPC5125_SDHC_INFO_STRUCT_PTR    sdhc_info_ptr;
    MPC5125_SDHC_DEVICE_STRUCT_PTR  sdhc_device_ptr;
    MPC5125_SDHC_INIT_STRUCT_CPTR   sdhc_init_ptr;
    MPC5125_SDHC_STRUCT_PTR         sdhc_ptr;
    uint_32                         bytes, i, j;
    uint_32_ptr                     ptr;
    vuint_32                        resp;
   
    /* Check parameters */
    if (NULL == sdhc_fd_ptr)
    {
        return IO_ERROR;
    }
    io_dev_ptr = (IO_DEVICE_STRUCT_PTR)sdhc_fd_ptr->DEV_PTR;
    if (NULL == io_dev_ptr)
    {
        return IO_ERROR;
    }
    sdhc_info_ptr = (MPC5125_SDHC_INFO_STRUCT_PTR)sdhc_fd_ptr->DEV_DATA_PTR;
    if (NULL == sdhc_info_ptr)
    {
        return IO_ERROR;
    }
    sdhc_device_ptr = io_dev_ptr->DRIVER_INIT_PTR;
    if (NULL == sdhc_device_ptr)
    {
        return IO_ERROR;
    }
    sdhc_init_ptr = sdhc_device_ptr->INIT;
    if (NULL == sdhc_init_ptr)
    {
        return IO_ERROR;
    }
    
    /* Get register base */
    sdhc_ptr = _bsp_get_sdhc_base_address (sdhc_init_ptr->CHANNEL);
    if (NULL == sdhc_ptr)
    {
        return IO_ERROR;
    }
    /* Disable INTERUPT */
    //sdhc_ptr->INT_CNTR = SDHC_INT_CNTR_NO_INTERRUPT;
    _sdhc_read_data_cpu(sdhc_ptr, 1, 512, data_ptr,sdhc_info_ptr->CARD);
   // sdhc_ptr->INT_CNTR |= 0x00008000;
    return n;
}

/*FUNCTION****************************************************************
* 
* Function Name    : _sdhc_write
* Returned Value   : return number of byte transmitted or IO_ERROR
* Comments         : 
*   Writes the provided data buffer to the device.
*
*END*********************************************************************/
_mqx_int _sdhc_write
    (
        FILE_DEVICE_STRUCT_PTR sdhc_fd_ptr,
        char_ptr               data_ptr,
        _mqx_int               n
    )
{
    IO_DEVICE_STRUCT_PTR           io_dev_ptr;
    MPC5125_SDHC_INFO_STRUCT_PTR   sdhc_info_ptr;
    MPC5125_SDHC_DEVICE_STRUCT_PTR sdhc_device_ptr;
    MPC5125_SDHC_INIT_STRUCT_CPTR  sdhc_init_ptr;
    MPC5125_SDHC_STRUCT_PTR        sdhc_ptr;
    uint_32                        bytes, i;
    uint_32_ptr                    ptr;
    
    /* Check parameters */
    if (NULL == sdhc_fd_ptr)
    {
        return IO_ERROR;
    }
    io_dev_ptr = (IO_DEVICE_STRUCT_PTR)sdhc_fd_ptr->DEV_PTR;
    if (NULL == io_dev_ptr)
    {
        return IO_ERROR;
    }
    sdhc_info_ptr = (MPC5125_SDHC_INFO_STRUCT_PTR)sdhc_fd_ptr->DEV_DATA_PTR;
    if (NULL == sdhc_info_ptr)
    {
        return IO_ERROR;
    }
    sdhc_device_ptr = io_dev_ptr->DRIVER_INIT_PTR;
    if (NULL == sdhc_device_ptr)
    {
        return IO_ERROR;
    }
    sdhc_init_ptr = sdhc_device_ptr->INIT;
    if (NULL == sdhc_init_ptr)
    {
        return IO_ERROR;
    }

    /* Get register base */
    sdhc_ptr = _bsp_get_sdhc_base_address (sdhc_init_ptr->CHANNEL);
    if (NULL == sdhc_ptr)
    {
        return IO_ERROR;
    }
    /* Disable Interupt */
   // sdhc_ptr->INT_CNTR = SDHC_INT_CNTR_NO_INTERRUPT;
    _sdhc_write_data_cpu(sdhc_ptr, 1, 512, data_ptr,sdhc_info_ptr->CARD);
    //sdhc_ptr->INT_CNTR |= 0x00008000;
    return n;
}


/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _sdhc_read_data_cpu
* Returned Value   : 
* Comments         :
*
*
*
*END*----------------------------------------------------------------------*/
static int _sdhc_read_data_cpu
   (
      MPC5125_SDHC_STRUCT_PTR sdhc_ptr, 
      int blockNum, 
      int blockLen, 
      uint_32 *buffer,
      uint_32 card_type
   )
{
    uint_32 ul_reg_val;
    uint_32 ul_reg_val1;
    vuint_32 resp;
    int countWDT, countWhile, countMinorLoop;
    uint_32 i;
    boolean multiple=0;
    SDHC_COMMAND_STRUCT command;
    if (blockNum > 1)
        multiple = 1;
  
     /* START MMC_SD_CLK if it is stopped */
     while (!(sdhc_ptr->STATUS & SDHC_STATUS_CARD_BUS_CLK_RUN_MASK))
    {
    	sdhc_ptr->STR_STP_CLK |= SDHC_STR_STP_CLK_START_CLK_MASK;
    }
  
    
    if((card_type == SDHC_MMC) || (card_type == SDHC_SD))
    {
        while (!(resp =_sdhc_get_card_status(sdhc_ptr, gul_sdhc_sd_rca,card_type) & CARD_READY_STATUS_BIT))
        {
        }


        command.COMMAND = SET_BLOCKLEN;
        command.ARGUMENT = blockLen;
        command.CONFIGURATION = (SDHC_CMD_DATA_WRITE | SDHC_FMT_RESP_R1);
        _sdhc_send_cmd_wait_resp(sdhc_ptr, &command);

    }
        sdhc_ptr->BLK_LEN = blockLen;
        sdhc_ptr->NOB = blockNum;

    
    
    if((card_type  == SDHC_MMC) || (card_type  == SDHC_SD))
    {
        while (!(resp = _sdhc_get_card_status(sdhc_ptr, gul_sdhc_sd_rca,card_type) & CARD_READY_STATUS_BIT ))
        {
        }

        if(SDHC_BIT_MODE == BIT_1_MODE)
        {
            if(multiple)
            {
                command.COMMAND = READ_MULTIPLE_BLOCK;
                command.ARGUMENT = gul_sector_address;
                command.CONFIGURATION = (SDHC_CMD_DAT_CONT_DATA_ENABLE_MASK | SDHC_FMT_RESP_R1);
                _sdhc_send_cmd_wait_resp(sdhc_ptr, &command);
            }
            else
            {
                command.COMMAND = READ_SINGLE_BLOCK;
                command.ARGUMENT = gul_sector_address;
                command.CONFIGURATION = (SDHC_CMD_DAT_CONT_DATA_ENABLE_MASK | SDHC_FMT_RESP_R1);
               _sdhc_send_cmd_wait_resp(sdhc_ptr, &command);
            }
        }
        else
        {
            if(multiple)
            {
                command.COMMAND = READ_MULTIPLE_BLOCK;
                command.ARGUMENT = gul_sector_address;
                command.CONFIGURATION = (SDHC_BUS_WIDTH_4 | SDHC_CMD_DAT_CONT_DATA_ENABLE_MASK | SDHC_FMT_RESP_R1);
                _sdhc_send_cmd_wait_resp(sdhc_ptr, &command);
            }
            else
            {
                command.COMMAND = READ_SINGLE_BLOCK;
                command.ARGUMENT = gul_sector_address;
                command.CONFIGURATION = (SDHC_BUS_WIDTH_4 | SDHC_CMD_DAT_CONT_DATA_ENABLE_MASK | SDHC_FMT_RESP_R1);
                _sdhc_send_cmd_wait_resp(sdhc_ptr, &command);
            }
        }
    }

    while(1)
    {
        if((sdhc_ptr->STATUS & SDHC_STATUS_END_CMD_RESP_MASK ) &&
            (!(sdhc_ptr->STATUS & SDHC_STATUS_TIME_OUT_RESP_MASK)) &&
            (!(sdhc_ptr->STATUS & SDHC_STATUS_RESP_CRC_ERR_MASK )))
            break;
    }

    for(countWDT = 0; countWDT < ((blockLen*blockNum)/(XY_BUFFER_SIZE*SDHC_BIT_MODE)); countWDT++)
    {
        while(1)
        {
            if(sdhc_ptr->STATUS & SDHC_STATUS_BUF_READ_READY_MASK)
                break;
           if((sdhc_ptr->STATUS & SDHC_STATUS_READ_CRC_ERR_MASK) ||
                         (sdhc_ptr->STATUS & SDHC_STATUS_TIME_OUT_READ_MASK))
                        return FALSE;
        }
        for(countMinorLoop = 0; countMinorLoop < ((XY_BUFFER_SIZE/SDHC_REG_SIZE)*SDHC_BIT_MODE); countMinorLoop++)
        {
            
#if PSP_ENDIAN == MQX_LITTLE_ENDIAN
            buffer[((XY_BUFFER_SIZE/SDHC_REG_SIZE)*SDHC_BIT_MODE*countWDT)+countMinorLoop]= sdhc_ptr->BUFFER_ACCESS;
#else
            buffer[((XY_BUFFER_SIZE/SDHC_REG_SIZE)*SDHC_BIT_MODE*countWDT)+countMinorLoop] = _psp_swap4byte (sdhc_ptr->BUFFER_ACCESS);
#endif
        }
    }

    while(1)
    {
        if((sdhc_ptr->STATUS & SDHC_STATUS_READ_OP_DONE_MASK) &&
            (!(sdhc_ptr->STATUS & SDHC_STATUS_READ_CRC_ERR_MASK)))
            break;
    }

    if((card_type  == SDHC_MMC) || (card_type  == SDHC_SD))
    {
        if(multiple)
        {
            command.COMMAND = STOP_TRANSMISSION;
            command.ARGUMENT = STUFF_BITS;
            command.CONFIGURATION = SDHC_FMT_RESP_R1;
            _sdhc_send_cmd_wait_resp(sdhc_ptr, &command);
        }

        resp =  _sdhc_get_card_status(sdhc_ptr, gul_sdhc_sd_rca,card_type);
    }
   return TRUE; 
}

/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : _sdhc_write_data_cpu
* Returned Value   : 
* Comments         :
*
*
*
*END*----------------------------------------------------------------------*/
static int _sdhc_write_data_cpu 
  (
      MPC5125_SDHC_STRUCT_PTR sdhc_ptr, 
      int blockNum, 
      int blockLen, 
      uint_32 *buffer,
      uint_32 card_type
   )
{
  
    uint_32 ul_reg_val;
    uint_32 ul_reg_val1;
    vuint_32 resp;
    int countWDT, countWhile, countMinorLoop;
    uint_32 i;
    boolean multiple=0;
    SDHC_COMMAND_STRUCT command;
    
    if (blockNum > 1)
        multiple = 1;
   
    /* START MMC_SD_CLK if it is stopped */
     while (!(sdhc_ptr->STATUS & SDHC_STATUS_CARD_BUS_CLK_RUN_MASK))
    {
    	sdhc_ptr->STR_STP_CLK |= SDHC_STR_STP_CLK_START_CLK_MASK;
    }
    
    while (!(resp =  _sdhc_get_card_status(sdhc_ptr, gul_sdhc_sd_rca,card_type) & CARD_READY_STATUS_BIT ))
    {
    } /* CARD READY */

    command.COMMAND = SET_BLOCKLEN;
    command.ARGUMENT = blockLen;
    command.CONFIGURATION = (SDHC_CMD_DATA_WRITE | SDHC_FMT_RESP_R1);
    _sdhc_send_cmd_wait_resp(sdhc_ptr,&command);
    sdhc_ptr->BLK_LEN = blockLen;
    sdhc_ptr->NOB = blockNum;

    while (!(resp =  _sdhc_get_card_status(sdhc_ptr, gul_sdhc_sd_rca,card_type) & CARD_READY_STATUS_BIT ))
    {
    } /* CARD READY */
   
    if(SDHC_BIT_MODE == BIT_4_MODE)
    { 
        if(multiple)
        {
            command.COMMAND = WRITE_MULTIPLE_BLOCK;
            command.ARGUMENT = gul_sector_address;
            command.CONFIGURATION = (SDHC_BUS_WIDTH_4 | SDHC_CMD_DATA_WRITE | SDHC_CMD_DAT_CONT_DATA_ENABLE_MASK | SDHC_FMT_RESP_R1);
            _sdhc_send_cmd_wait_resp(sdhc_ptr, &command);
        }
        else
        {
            command.COMMAND  = WRITE_BLOCK;
            command.ARGUMENT = gul_sector_address;
            command.CONFIGURATION =  (SDHC_BUS_WIDTH_4 | SDHC_CMD_DATA_WRITE | SDHC_CMD_DAT_CONT_DATA_ENABLE_MASK | SDHC_FMT_RESP_R1);
            _sdhc_send_cmd_wait_resp(sdhc_ptr,&command);
        }
    }
    else
    {
        if(multiple)
        {
             command.COMMAND = WRITE_MULTIPLE_BLOCK;
             command.ARGUMENT = gul_sector_address;
             command.CONFIGURATION = (SDHC_CMD_DATA_WRITE | SDHC_CMD_DAT_CONT_DATA_ENABLE_MASK | SDHC_FMT_RESP_R1);
             _sdhc_send_cmd_wait_resp(sdhc_ptr, &command);
        }
        else
        {
             command.COMMAND  = WRITE_BLOCK;
             command.ARGUMENT = gul_sector_address;
             command.CONFIGURATION = (SDHC_CMD_DATA_WRITE | SDHC_CMD_DAT_CONT_DATA_ENABLE_MASK | SDHC_FMT_RESP_R1);
            _sdhc_send_cmd_wait_resp(sdhc_ptr, &command);
        }
    }

      while(1)
    {
        if((sdhc_ptr->STATUS & SDHC_STATUS_END_CMD_RESP_MASK ) &&
            (!(sdhc_ptr->STATUS & SDHC_STATUS_TIME_OUT_RESP_MASK)) &&
            (!(sdhc_ptr->STATUS & SDHC_STATUS_RESP_CRC_ERR_MASK )))
            break;
    }
   

    for(countWDT = 0; countWDT < ((blockLen*blockNum)/(XY_BUFFER_SIZE*SDHC_BIT_MODE)); countWDT++)
    {
        while(1)
        {
            if(sdhc_ptr->STATUS & SDHC_STATUS_BUF_WRITE_READY_MASK)
                break;
           if(sdhc_ptr->STATUS & SDHC_STATUS_WRITE_CRC_ERR_MASK) 
                        return FALSE;
        }
        for(countMinorLoop = 0; countMinorLoop < ((XY_BUFFER_SIZE/SDHC_REG_SIZE)*SDHC_BIT_MODE); countMinorLoop++)
        {
#if PSP_ENDIAN == MQX_LITTLE_ENDIAN
            sdhc_ptr->BUFFER_ACCESS = buffer[((XY_BUFFER_SIZE/SDHC_REG_SIZE)*SDHC_BIT_MODE*countWDT)+countMinorLoop];
#else
            sdhc_ptr->BUFFER_ACCESS =  _psp_swap4byte(buffer[((XY_BUFFER_SIZE/SDHC_REG_SIZE)*SDHC_BIT_MODE*countWDT)+countMinorLoop]);
#endif            
        }
    }

    while(1)
    {
        if((sdhc_ptr->STATUS & SDHC_STATUS_WRITE_OP_DONE_MASK ) &&
            (!(sdhc_ptr->STATUS & SDHC_STATUS_WRITE_CRC_ERR_MASK)))
            break;
    }

    if(multiple)
    {
         command.COMMAND = STOP_TRANSMISSION;
         command.ARGUMENT = STUFF_BITS;
         command.CONFIGURATION = SDHC_FMT_RESP_R1;
         _sdhc_send_cmd_wait_resp(sdhc_ptr, &command);
    }
    return TRUE;
}

/* EOF */