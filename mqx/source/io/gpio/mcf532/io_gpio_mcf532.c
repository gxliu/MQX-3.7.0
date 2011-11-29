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
* $FileName: io_gpio_mcf532.c$
* $Version : 3.7.2.0$
* $Date    : Feb-7-2011$
*
* Comments:
*
*   This file contains the GPIO standard functions used on boards
*
*END************************************************************************/

#include "mqx.h"
#include "bsp.h"
#include "../io_gpio.h"
#include "../io_gpio_prv.h"
#include <string.h>

/* This structure will hold 'used pins'. If somebody would like to open 'already used pin',
** the operation will fail. All open pins whithin all GPIO driver files will be written here.
** We can predefine this structure with 'already used' bits for those bits, which are not
** used at all - so we will prevent open operation to be successful.
*/
/* Reserved pins = 1 */
GPIO_PIN_MAP  gpio_global_pin_map = {
    0x00,    /* fech */                            
    0x00,    /* fecl */							   
    0xE0,    /* ssi */							   
    0xF0,    /* busctl */						   
    0xF0,    /* be */							   
    0x31,    /* cs */							   
    0xC3,    /* pwm */							   
    0xF0,    /* feci2c */						   
    0xFF,    /* unusedA*/						   
    0x00,    /* uart*/							   
    0xC0,    /* qspi */							   
    0xF0,    /* timer */
    0xFF,    /* unusedB */						   
    0xFC,    /* lcddatah */						   
    0x00,    /* lcddatam */						   
    0x00,    /* lcddatal */						   
    0xFE,    /* lcdctlh */						   
    0x00,    /* lcdctll */						   
    {											   
      0xFF, 0xFF  /* unusedC[2] */				   
    }
};             

GPIO_PIN_MAP  gpio_global_irq_map = {
    0xFF,     /* fech */
    0xFF,     /* fecl */
    0xFF,     /* ssi */
    0xFF,     /* busctl */
    0xFF,     /* be */
    0xFF,     /* cs */
    0xFF,     /* pwm */
    0xFF,     /* feci2c */
    0xFF,     /* unusedA*/
    0xFF,     /* uart*/
    0xFF,     /* qspi */
    0xFF,     /* timer */
    0xFF,     /* unusedB */
    0xFF,     /* lcddatah */
    0xFF,     /* lcddatam */
    0xFF,     /* lcddatal */
    0xFF,     /* lcdctlh */
    0xFF,     /* lcdctll */
    {
      0xFF, 0xFF  /* unusedE[2] */
    }
    
};

extern GPIO_DEV_DATA_PTR first_irq; /* first file having used IRQ */

/* pointer to the start of GPIO registers */
VMCF5329_GPIO_STRUCT_PTR mcf5329_gpio_ptr;

void gpio_cpu_configure(GPIO_DEV_DATA_PTR);
_mqx_int gpio_cpu_init();
_mqx_int gpio_cpu_open(MQX_FILE_PTR, char_ptr, char_ptr);
_mqx_int gpio_cpu_ioctl(MQX_FILE_PTR, _mqx_uint, pointer);

/*FUNCTION*****************************************************************
* 
* Function Name    : gpio_cpu_configure
* Returned Value   : IO_OK
* Comments         :
*    Configures pins to be GPIO based on pin map
*
*END*********************************************************************/
void gpio_cpu_configure
   (
      /* [IN] pointer to file data */
      GPIO_DEV_DATA_PTR   dev_data_ptr
   )
{ 
/* Body */
	if (dev_data_ptr->type == DEV_OUTPUT) { /* set GPIO output behavior */
        * (((uint_32 _PTR_) (&mcf5329_gpio_ptr->PDDR_FECH)) + 0) |= dev_data_ptr->pin_map.memory32[0];
        * (((uint_32 _PTR_) (&mcf5329_gpio_ptr->PDDR_FECH)) + 1) |= dev_data_ptr->pin_map.memory32[1];
        * (((uint_32 _PTR_) (&mcf5329_gpio_ptr->PDDR_FECH)) + 2) |= dev_data_ptr->pin_map.memory32[2];
        * (((uint_32 _PTR_) (&mcf5329_gpio_ptr->PDDR_FECH)) + 3) |= dev_data_ptr->pin_map.memory32[3];
        * (((uint_32 _PTR_) (&mcf5329_gpio_ptr->PDDR_FECH)) + 4) |= dev_data_ptr->pin_map.memory32[4];
    }
    else { /* DEV_INPUT type is supposed */
        * (((uint_32 _PTR_) (&mcf5329_gpio_ptr->PDDR_FECH)) + 0) &= ~dev_data_ptr->pin_map.memory32[0];
        * (((uint_32 _PTR_) (&mcf5329_gpio_ptr->PDDR_FECH)) + 1) &= ~dev_data_ptr->pin_map.memory32[1];
        * (((uint_32 _PTR_) (&mcf5329_gpio_ptr->PDDR_FECH)) + 2) &= ~dev_data_ptr->pin_map.memory32[2];
        * (((uint_32 _PTR_) (&mcf5329_gpio_ptr->PDDR_FECH)) + 3) &= ~dev_data_ptr->pin_map.memory32[3];
        * (((uint_32 _PTR_) (&mcf5329_gpio_ptr->PDDR_FECH)) + 4) &= ~dev_data_ptr->pin_map.memory32[4];
    }
    
    /* set pin functionality to be GPIO for the whole file */
    /* pin, which we will use as GPIO = 1 in dev_data_ptr, GPIO functionality = 0 in 
    ** registers. Other pins funcionality is unchanged */
    mcf5329_gpio_ptr->PAR_BE = mcf5329_gpio_ptr->PAR_BE & ~dev_data_ptr->pin_map.reg.be;
   
    mcf5329_gpio_ptr->PAR_CS = mcf5329_gpio_ptr->PAR_CS & ~(
        ( dev_data_ptr->pin_map.reg.cs & MCF5329_GPIO_PIN_0 ? MCF5329_GPIO_PAR_CS_PAR_CS1 : 0x00 ) |
        ( dev_data_ptr->pin_map.reg.cs & MCF5329_GPIO_PIN_1 ? MCF5329_GPIO_PAR_CS_PAR_CS2 : 0x00 ) |
        ( dev_data_ptr->pin_map.reg.cs & MCF5329_GPIO_PIN_2 ? MCF5329_GPIO_PAR_CS_PAR_CS3 : 0x00 ) |
        ( dev_data_ptr->pin_map.reg.cs & MCF5329_GPIO_PIN_3 ? MCF5329_GPIO_PAR_CS_PAR_CS4 : 0x00 ) |
        ( dev_data_ptr->pin_map.reg.cs & MCF5329_GPIO_PIN_4 ? MCF5329_GPIO_PAR_CS_PAR_CS5 : 0x00 ));
       
    mcf5329_gpio_ptr->PAR_FEC = mcf5329_gpio_ptr->PAR_FEC & ~(
        ( dev_data_ptr->pin_map.reg.fech & MCF5329_GPIO_PIN_0 ? MCF5329_GPIO_PAR_FEC_MII_FEC : 0x00 ) |
        ( dev_data_ptr->pin_map.reg.fech & MCF5329_GPIO_PIN_1 ? MCF5329_GPIO_PAR_FEC_7W_FEC  : 0x00 ));      
    
    mcf5329_gpio_ptr->PAR_FECI2C = mcf5329_gpio_ptr->PAR_FECI2C & ~(
        ( dev_data_ptr->pin_map.reg.feci2c & MCF5329_GPIO_PIN_0 ? MCF5329_GPIO_PAR_FECI2C_SCL_I2C_SCL : 0x00 ) |
        ( dev_data_ptr->pin_map.reg.feci2c & MCF5329_GPIO_PIN_1 ? MCF5329_GPIO_PAR_FECI2C_SDA_I2C_SDA : 0x00 ) |
        ( dev_data_ptr->pin_map.reg.feci2c & MCF5329_GPIO_PIN_2 ? MCF5329_GPIO_PAR_FECI2C_MDIO_EMDIO  : 0x00 ) |
        ( dev_data_ptr->pin_map.reg.feci2c & MCF5329_GPIO_PIN_3 ? MCF5329_GPIO_PAR_FECI2C_MDC_EMDC    : 0x00 ));
    
    mcf5329_gpio_ptr->PAR_UART = mcf5329_gpio_ptr->PAR_UART & ~(
        ( dev_data_ptr->pin_map.reg.uart & MCF5329_GPIO_PIN_0 ? MCF5329_GPIO_PAR_UART_UTXD0       : 0x00 ) |
        ( dev_data_ptr->pin_map.reg.uart & MCF5329_GPIO_PIN_1 ? MCF5329_GPIO_PAR_UART_URXD0       : 0x00 ) |
        ( dev_data_ptr->pin_map.reg.uart & MCF5329_GPIO_PIN_2 ? MCF5329_GPIO_PAR_UART_URTS0       : 0x00 ) |
        ( dev_data_ptr->pin_map.reg.uart & MCF5329_GPIO_PIN_3 ? MCF5329_GPIO_PAR_UART_UCTS0       : 0x00 ) |
        ( dev_data_ptr->pin_map.reg.uart & MCF5329_GPIO_PIN_4 ? MCF5329_GPIO_PAR_UART_UTXD1       : 0x00 ) |
        ( dev_data_ptr->pin_map.reg.uart & MCF5329_GPIO_PIN_5 ? MCF5329_GPIO_PAR_UART_URXD1       : 0x00 ) |
        ( dev_data_ptr->pin_map.reg.uart & MCF5329_GPIO_PIN_6 ? MCF5329_GPIO_PAR_UART_URTS1_URTS1 : 0x00 ) |
        ( dev_data_ptr->pin_map.reg.uart & MCF5329_GPIO_PIN_7 ? MCF5329_GPIO_PAR_UART_UCTS1_UCTS1 : 0x00 )) ;
   
    
    mcf5329_gpio_ptr->PAR_PWM = mcf5329_gpio_ptr->PAR_PWM & ~(
        ( dev_data_ptr->pin_map.reg.pwm & MCF5329_GPIO_PIN_0 ? MCF5329_GPIO_PAR_PWM_PAR_PWM1(3) : 0x00 ) |
        ( dev_data_ptr->pin_map.reg.pwm & MCF5329_GPIO_PIN_3 ? MCF5329_GPIO_PAR_PWM_PAR_PWM3(3) : 0x00)  |
        ( dev_data_ptr->pin_map.reg.pwm & MCF5329_GPIO_PIN_5 ? MCF5329_GPIO_PAR_PWM_PAR_PWM5    : 0x00 ) |
        ( dev_data_ptr->pin_map.reg.pwm & MCF5329_GPIO_PIN_7 ? MCF5329_GPIO_PAR_PWM_PAR_PWM7    : 0x00));
    
    mcf5329_gpio_ptr->PAR_TIMER = mcf5329_gpio_ptr->PAR_TIMER & ~(
        ( dev_data_ptr->pin_map.reg.timer & MCF5329_GPIO_PIN_0 ? MCF5329_GPIO_PAR_TIMER_TIN0_TIN0 : 0x00 ) |
        ( dev_data_ptr->pin_map.reg.timer & MCF5329_GPIO_PIN_1 ? MCF5329_GPIO_PAR_TIMER_TIN1_TIN1 : 0x00 ) |
        ( dev_data_ptr->pin_map.reg.timer & MCF5329_GPIO_PIN_2 ? MCF5329_GPIO_PAR_TIMER_TIN2_TIN2 : 0x00 ) |
        ( dev_data_ptr->pin_map.reg.timer & MCF5329_GPIO_PIN_3 ? MCF5329_GPIO_PAR_TIMER_TIN3_TIN3 : 0x00 ));
     
   

    mcf5329_gpio_ptr->PAR_BUSCTL = mcf5329_gpio_ptr->PAR_BUSCTL & ~(
        ( dev_data_ptr->pin_map.reg.busctl & MCF5329_GPIO_PIN_0 ? MCF5329_GPIO_PAR_BUSCTL_PAR_TS(3)  : 0x00 ) |
        ( dev_data_ptr->pin_map.reg.busctl & MCF5329_GPIO_PIN_1 ? MCF5329_GPIO_PAR_BUSCTL_PAR_RWB    : 0x00 ) |
        ( dev_data_ptr->pin_map.reg.busctl & MCF5329_GPIO_PIN_2 ? MCF5329_GPIO_PAR_BUSCTL_PAR_TA     : 0x00 ) |
        ( dev_data_ptr->pin_map.reg.busctl & MCF5329_GPIO_PIN_3 ? MCF5329_GPIO_PAR_BUSCTL_PAR_OE     : 0x00 ));    

    mcf5329_gpio_ptr->PAR_QSPI = mcf5329_gpio_ptr->PAR_QSPI & ~(
        ( dev_data_ptr->pin_map.reg.qspi & MCF5329_GPIO_PIN_0 ? MCF5329_GPIO_PAR_QSPI_SCK   : 0x00 ) |
        ( dev_data_ptr->pin_map.reg.qspi & MCF5329_GPIO_PIN_1 ? MCF5329_GPIO_PAR_QSPI_DOUT  : 0x00 ) |
        ( dev_data_ptr->pin_map.reg.qspi & MCF5329_GPIO_PIN_2 ? MCF5329_GPIO_PAR_QSPI_DIN   : 0x00 ) |
        ( dev_data_ptr->pin_map.reg.qspi & MCF5329_GPIO_PIN_3 ? MCF5329_GPIO_PAR_QSPI_PCS0  : 0x00 ) |
        ( dev_data_ptr->pin_map.reg.qspi & MCF5329_GPIO_PIN_4 ? MCF5329_GPIO_PAR_QSPI_PCS1  : 0x00 ) |
        ( dev_data_ptr->pin_map.reg.qspi & MCF5329_GPIO_PIN_5 ? MCF5329_GPIO_PAR_QSPI_PCS2  : 0x00 ));    
    
}


/*FUNCTION*****************************************************************
* 
* Function Name    : gpio_cpu_install
* Returned Value   : IO_OK
* Comments         :
*    Performs basic initialization specific to board
*
*END*********************************************************************/

_mqx_int gpio_cpu_init() 
{
    mcf5329_gpio_ptr = _bsp_get_gpio_base_address();
    return IO_OK;       
}


/*FUNCTION*****************************************************************
* 
* Function Name    : gpio_cpu_open
* Returned Value   : IO_OK or error
* Comments         :
*    Implements initialization for DATA GPIO
*
*END*********************************************************************/

_mqx_int gpio_cpu_open
   (
      /* [IN] the file handle for the device */
      MQX_FILE_PTR   fd_ptr,

      /* [IN] the file name */
      char_ptr   file_name,

      /* [IN] pointer to parameters */
      char_ptr   param_ptr
   )
{ 
/* Body */
    _mqx_int          i;
    GPIO_DEV_DATA_PTR dev_data_ptr = (GPIO_DEV_DATA_PTR) fd_ptr->DEV_DATA_PTR;
 
    /* if file_name is used, then the user wants to open peripheral */
    if ((file_name != NULL) && (*file_name != 0)) {
        if (!strncmp(file_name, "gpio:write", 11))  /* user wants write access to GPIO */
            dev_data_ptr->type = DEV_OUTPUT;
        else if (!strncmp(file_name, "gpio:output", 12))  /* user wants write access to GPIO */
            dev_data_ptr->type = DEV_OUTPUT;
        else if (!strncmp(file_name, "gpio:read", 10)) /* user wants read access to GPIO */
            dev_data_ptr->type = DEV_INPUT;
        else if (!strncmp(file_name, "gpio:input", 11)) /* user wants read access to GPIO */
            dev_data_ptr->type = DEV_INPUT;
        else
        /* peripherals not used yet */
            return IO_ERROR;
    }
    else
        return IO_ERROR;
 
    if ((param_ptr != NULL) && (dev_data_ptr->type == DEV_OUTPUT)) { /* set pins status before selecting GPIO function */
        /* note that this is similar to GPIO_IOCTL_WRITE function, but no checking is performed
           (was done in io_gpio_open function) */
        GPIO_PIN_STRUCT _PTR_  pin_table;
        uint_32        addr;
        uint_8         pin;
        GPIO_PIN_MAP_PTR    temp_pin0_map_ptr;
        GPIO_PIN_MAP_PTR    temp_pin1_map_ptr;

        if (NULL == (temp_pin0_map_ptr = (GPIO_PIN_MAP_PTR) _mem_alloc_system_zero(sizeof(GPIO_PIN_MAP))))
            return IO_ERROR;

        if (NULL == (temp_pin1_map_ptr = (GPIO_PIN_MAP_PTR) _mem_alloc_system_zero(sizeof(GPIO_PIN_MAP)))) {
            _mem_free(temp_pin0_map_ptr);
            return IO_ERROR;
        }

        /* prepare pin map */
        for (pin_table = (GPIO_PIN_STRUCT _PTR_) param_ptr; *pin_table != GPIO_LIST_END; pin_table++) {
            addr = (*pin_table & GPIO_PIN_ADDR) >> 3; /* prepare address of port */ 
            pin = 1 << (*pin_table & 0x07);  /* prepare bit mask */
            if (*pin_table & GPIO_PIN_STATUS)
                temp_pin1_map_ptr->memory8[addr] |= pin;
            else
                temp_pin0_map_ptr->memory8[addr] |= pin;
        }
        /* ok, now we can apply new map */
        /* note: applying the map after collecting pins is due to have pins applied in one instruction */
        * (((uint_32 _PTR_) (&mcf5329_gpio_ptr->PPDSDR_FECH)) + 0) = temp_pin1_map_ptr->memory32[0];
        * (((uint_32 _PTR_) (&mcf5329_gpio_ptr->PCLRR_FECH)) + 0) = ~temp_pin0_map_ptr->memory32[0];
        * (((uint_32 _PTR_) (&mcf5329_gpio_ptr->PPDSDR_FECH)) + 1) = temp_pin1_map_ptr->memory32[1];
        * (((uint_32 _PTR_) (&mcf5329_gpio_ptr->PCLRR_FECH)) + 1) = ~temp_pin0_map_ptr->memory32[1];
        * (((uint_32 _PTR_) (&mcf5329_gpio_ptr->PPDSDR_FECH)) + 2) = temp_pin1_map_ptr->memory32[2];
        * (((uint_32 _PTR_) (&mcf5329_gpio_ptr->PCLRR_FECH)) + 2) = ~temp_pin0_map_ptr->memory32[2];
        * (((uint_32 _PTR_) (&mcf5329_gpio_ptr->PPDSDR_FECH)) + 3) = temp_pin1_map_ptr->memory32[3];
        * (((uint_32 _PTR_) (&mcf5329_gpio_ptr->PCLRR_FECH)) + 3) = ~temp_pin0_map_ptr->memory32[3];
        * (((uint_32 _PTR_) (&mcf5329_gpio_ptr->PPDSDR_FECH)) + 4) = temp_pin1_map_ptr->memory32[4];
        * (((uint_32 _PTR_) (&mcf5329_gpio_ptr->PCLRR_FECH)) + 4) = ~temp_pin0_map_ptr->memory32[4];

        _mem_free(temp_pin1_map_ptr);
        _mem_free(temp_pin0_map_ptr);
    }

    gpio_cpu_configure(dev_data_ptr);
   
    return IO_OK;
} /* Endbody */

/*FUNCTION*****************************************************************
* 
* Function Name    : gpio_cpu_ioctl
* Returned Value   : depends on IOCTL command
* Comments         :
*    Implements all ioctl for GPIO
*
*END*********************************************************************/

_mqx_int gpio_cpu_ioctl
   (
      /* [IN] the file handle for the device */
      MQX_FILE_PTR   fd_ptr,

      /* [IN] the ioctl command */
      _mqx_uint  cmd,

      /* [IN] the ioctl parameters */
      pointer    param_ptr
   )
{ /* Body */
    GPIO_DEV_DATA_PTR  dev_data_ptr = (GPIO_DEV_DATA_PTR) fd_ptr->DEV_DATA_PTR;
 
    switch (cmd) {
        case GPIO_IOCTL_ADD_PINS: {
        /* Add pins to this file. Params: table with pin addresses */
            GPIO_PIN_STRUCT _PTR_  pin_table;
            uint_32        addr;
            uint_8         pin;

            /* check pin_table if they are not in global pin_map */
            _int_disable();
            for (pin_table = (GPIO_PIN_STRUCT _PTR_) param_ptr; *pin_table != GPIO_LIST_END; pin_table++) {
                if (*pin_table & GPIO_PIN_VALID) { /* check pin validity bit */
                    addr = (*pin_table & GPIO_PIN_ADDR) >> 3; /* prepare address of port */ 
                    pin = 1 << (*pin_table & 0x07);  /* prepare bit mask */
                    if (addr < sizeof(GPIO_PIN_MAP)) /* pin address out of map scope? */
                        if (! (gpio_global_pin_map.memory8[addr] & pin)) /* pin address already used? */
                            continue; /* manage next pin */
                }
                /* some problem occured */
                _int_enable();
                return IO_ERROR;
            }
            /* check successful, now we have to copy these bits to local pin map */
            for (pin_table = (GPIO_PIN_STRUCT _PTR_) param_ptr; *pin_table != GPIO_LIST_END; pin_table++) {
                addr = (*pin_table & GPIO_PIN_ADDR)  >> 3; /* prepare address of port */ 
                pin = 1 << (*pin_table & 0x07);  /* prepare bit mask */
                dev_data_ptr->pin_map.memory8[addr] |= pin; /* mark pin as used by this file */
                gpio_global_pin_map.memory8[addr] |= pin; /* mark pin as used globally */
            }
            gpio_cpu_configure(dev_data_ptr);
            _int_enable();
        }
        break;

        case GPIO_IOCTL_WRITE_LOG1: {
        /* If this file is configured as output, sets every pin to 1. Params:
           list of pin addresses to be used or NULL for every pin in the file */
            if (dev_data_ptr->type != DEV_OUTPUT)
                return IO_ERROR;
            if (param_ptr == NULL) { /* apply command to whole file */
                _int_disable(); /* _lwsem_wait(&gpio_sem) replacement */
                * (((uint_32 _PTR_) (&mcf5329_gpio_ptr->PPDSDR_FECH)) + 0) = dev_data_ptr->pin_map.memory32[0];
                * (((uint_32 _PTR_) (&mcf5329_gpio_ptr->PPDSDR_FECH)) + 1) = dev_data_ptr->pin_map.memory32[1];
                * (((uint_32 _PTR_) (&mcf5329_gpio_ptr->PPDSDR_FECH)) + 2) = dev_data_ptr->pin_map.memory32[2];
                * (((uint_32 _PTR_) (&mcf5329_gpio_ptr->PPDSDR_FECH)) + 3) = dev_data_ptr->pin_map.memory32[3];
                * (((uint_32 _PTR_) (&mcf5329_gpio_ptr->PPDSDR_FECH)) + 4) = dev_data_ptr->pin_map.memory32[4];
                _int_enable(); /* _int_enable(); */
                break;
            }
            else {
                GPIO_PIN_STRUCT _PTR_  pin_table;
                uint_32        addr;
                uint_8         pin;
                GPIO_PIN_MAP_PTR    temp_pin_map_ptr;

                if (NULL == (temp_pin_map_ptr = (GPIO_PIN_MAP_PTR) _mem_alloc_system_zero(sizeof(GPIO_PIN_MAP))))
                    return IO_ERROR;
    
                _int_disable();
                /* check if there is not pin in the list which this file does not contain */
                for (pin_table = (GPIO_PIN_STRUCT _PTR_) param_ptr; *pin_table != GPIO_LIST_END; pin_table++) {
                    if (*pin_table & GPIO_PIN_VALID) { /* check pin validity bit */
                        addr = (*pin_table & GPIO_PIN_ADDR) >> 3; /* prepare address of port */ 
                        pin = 1 << (*pin_table & 0x07);  /* prepare bit mask */
                        if (addr < sizeof(GPIO_PIN_MAP)) /* pin address out of map scope? */
                            if (dev_data_ptr->pin_map.memory8[addr] & pin) { /* pin address already used? */
                                temp_pin_map_ptr->memory8[addr] |= pin;
                                continue; /* manage next pin */
                            }
                    }
                    /* some problem occured */
                    _int_enable();
                    _mem_free(temp_pin_map_ptr);
                    return IO_ERROR;
                }
                /* ok, now we can apply new map */
                /* note: applying the map after collecting pins is due to have pins applied in one instruction */
                * (((uint_32 _PTR_) (&mcf5329_gpio_ptr->PPDSDR_FECH)) + 0) = temp_pin_map_ptr->memory32[0];
                * (((uint_32 _PTR_) (&mcf5329_gpio_ptr->PPDSDR_FECH)) + 1) = temp_pin_map_ptr->memory32[1];
                * (((uint_32 _PTR_) (&mcf5329_gpio_ptr->PPDSDR_FECH)) + 2) = temp_pin_map_ptr->memory32[2];
                * (((uint_32 _PTR_) (&mcf5329_gpio_ptr->PPDSDR_FECH)) + 3) = temp_pin_map_ptr->memory32[3];
                * (((uint_32 _PTR_) (&mcf5329_gpio_ptr->PPDSDR_FECH)) + 4) = temp_pin_map_ptr->memory32[4];
                _int_enable();
                _mem_free(temp_pin_map_ptr);
            }
        }
        break;

        case GPIO_IOCTL_WRITE_LOG0: {
        /* If this file is configured as output, clears every pin to 0. Params:
           list of pin addresses to be used or NULL for every pin in the file */
            if (dev_data_ptr->type != DEV_OUTPUT)
                return IO_ERROR;
            if (param_ptr == NULL) { /* apply command to whole file */
                _int_disable(); /* _lwsem_wait(&gpio_sem) replacement */
                * (((uint_32 _PTR_) (&mcf5329_gpio_ptr->PCLRR_FECH)) + 0) = ~dev_data_ptr->pin_map.memory32[0];
                * (((uint_32 _PTR_) (&mcf5329_gpio_ptr->PCLRR_FECH)) + 1) = ~dev_data_ptr->pin_map.memory32[1];
                * (((uint_32 _PTR_) (&mcf5329_gpio_ptr->PCLRR_FECH)) + 2) = ~dev_data_ptr->pin_map.memory32[2];
                * (((uint_32 _PTR_) (&mcf5329_gpio_ptr->PCLRR_FECH)) + 3) = ~dev_data_ptr->pin_map.memory32[3];
                * (((uint_32 _PTR_) (&mcf5329_gpio_ptr->PCLRR_FECH)) + 4) = ~dev_data_ptr->pin_map.memory32[4];
                _int_enable(); /* _int_enable(); */
                break;
            }
            else {
                GPIO_PIN_STRUCT _PTR_  pin_table;
                uint_32        addr;
                uint_8         pin;
                GPIO_PIN_MAP_PTR    temp_pin_map_ptr;

                if (NULL == (temp_pin_map_ptr = (GPIO_PIN_MAP_PTR) _mem_alloc_system_zero(sizeof(GPIO_PIN_MAP))))
                    return IO_ERROR;
    
                _int_disable();
                /* check if there is not pin in the list which this file does not contain */
                for (pin_table = (GPIO_PIN_STRUCT _PTR_) param_ptr; *pin_table != GPIO_LIST_END; pin_table++) {
                    if (*pin_table & GPIO_PIN_VALID) { /* check pin validity bit */
                        addr = (*pin_table & GPIO_PIN_ADDR) >> 3; /* prepare address of port */ 
                        pin = 1 << (*pin_table & 0x07);  /* prepare bit mask */
                        if (addr < sizeof(GPIO_PIN_MAP)) /* pin address out of map scope? */
                            if (dev_data_ptr->pin_map.memory8[addr] & pin) { /* pin address already used? */
                                temp_pin_map_ptr->memory8[addr] |= pin;
                                continue; /* manage next pin */
                            }
                    }
                    /* some problem occured */
                    _int_enable();
                    _mem_free(temp_pin_map_ptr);
                    return IO_ERROR;
                }
                /* ok, now we can apply new map */
                /* note: applying the map after collecting pins is due to have pins applied in one instruction */
                * (((uint_32 _PTR_) (&mcf5329_gpio_ptr->PCLRR_FECH)) + 0) = ~temp_pin_map_ptr->memory32[0];
                * (((uint_32 _PTR_) (&mcf5329_gpio_ptr->PCLRR_FECH)) + 1) = ~temp_pin_map_ptr->memory32[1];
                * (((uint_32 _PTR_) (&mcf5329_gpio_ptr->PCLRR_FECH)) + 2) = ~temp_pin_map_ptr->memory32[2];
                * (((uint_32 _PTR_) (&mcf5329_gpio_ptr->PCLRR_FECH)) + 3) = ~temp_pin_map_ptr->memory32[3];
                * (((uint_32 _PTR_) (&mcf5329_gpio_ptr->PCLRR_FECH)) + 4) = ~temp_pin_map_ptr->memory32[4];
                _int_enable();
                _mem_free(temp_pin_map_ptr);
            }
        }
        break;

        case GPIO_IOCTL_WRITE: {
        /* If this file is configured as output, sets every pin to the state defined in GPIO_PIN_STATUS. Params:
           list of pin addresses to be used or NULL for every pin in the file */
            if (dev_data_ptr->type != DEV_OUTPUT)
                return IO_ERROR;
            if (param_ptr == NULL) /* no param specified , but must be */
                return IO_ERROR;
            else {
                GPIO_PIN_STRUCT _PTR_  pin_table;
                uint_32        addr;
                uint_8         pin;
                GPIO_PIN_MAP_PTR    temp_pin0_map_ptr;
                GPIO_PIN_MAP_PTR    temp_pin1_map_ptr;

                if (NULL == (temp_pin0_map_ptr = (GPIO_PIN_MAP_PTR) _mem_alloc_system_zero(sizeof(GPIO_PIN_MAP))))
                    return IO_ERROR;
    
                if (NULL == (temp_pin1_map_ptr = (GPIO_PIN_MAP_PTR) _mem_alloc_system_zero(sizeof(GPIO_PIN_MAP)))) {
                    _mem_free(temp_pin0_map_ptr);
                    return IO_ERROR;
                }

                _int_disable();
                /* check if there is not pin in the list which this file does not contain */
                for (pin_table = (GPIO_PIN_STRUCT _PTR_) param_ptr; *pin_table != GPIO_LIST_END; pin_table++) {
                    if (*pin_table & GPIO_PIN_VALID) { /* check pin validity bit */
                        addr = (*pin_table & GPIO_PIN_ADDR) >> 3; /* prepare address of port */ 
                        pin = 1 << (*pin_table & 0x07);  /* prepare bit mask */
                        if (addr < sizeof(GPIO_PIN_MAP)) /* pin address out of map scope? */
                            if (dev_data_ptr->pin_map.memory8[addr] & pin) { /* pin address already used? */
                                if (*pin_table & GPIO_PIN_STATUS)
                                    temp_pin1_map_ptr->memory8[addr] |= pin;
                                else
                                    temp_pin0_map_ptr->memory8[addr] |= pin;
                                continue; /* manage next pin */
                            }
                    }
                    /* some problem occured */
                    _int_enable();
                    _mem_free(temp_pin1_map_ptr);
                    _mem_free(temp_pin0_map_ptr);
                    return IO_ERROR;
                }
                /* ok, now we can apply new map */
                /* note: applying the map after collecting pins is due to have pins applied in one instruction */
                * (((uint_32 _PTR_) (&mcf5329_gpio_ptr->PPDSDR_FECH)) + 0) = temp_pin1_map_ptr->memory32[0];
                * (((uint_32 _PTR_) (&mcf5329_gpio_ptr->PCLRR_FECH)) + 0) = ~temp_pin0_map_ptr->memory32[0];
                * (((uint_32 _PTR_) (&mcf5329_gpio_ptr->PPDSDR_FECH)) + 1) = temp_pin1_map_ptr->memory32[1];
                * (((uint_32 _PTR_) (&mcf5329_gpio_ptr->PCLRR_FECH)) + 1) = ~temp_pin0_map_ptr->memory32[1];
                * (((uint_32 _PTR_) (&mcf5329_gpio_ptr->PPDSDR_FECH)) + 2) = temp_pin1_map_ptr->memory32[2];
                * (((uint_32 _PTR_) (&mcf5329_gpio_ptr->PCLRR_FECH)) + 2) = ~temp_pin0_map_ptr->memory32[2];
                * (((uint_32 _PTR_) (&mcf5329_gpio_ptr->PPDSDR_FECH)) + 3) = temp_pin1_map_ptr->memory32[3];
                * (((uint_32 _PTR_) (&mcf5329_gpio_ptr->PCLRR_FECH)) + 3) = ~temp_pin0_map_ptr->memory32[3];
                * (((uint_32 _PTR_) (&mcf5329_gpio_ptr->PPDSDR_FECH)) + 4) = temp_pin1_map_ptr->memory32[4];
                * (((uint_32 _PTR_) (&mcf5329_gpio_ptr->PCLRR_FECH)) + 4) = ~temp_pin0_map_ptr->memory32[4];
                _int_enable();
                _mem_free(temp_pin1_map_ptr);
                _mem_free(temp_pin0_map_ptr);
            }
        }
        break;

        case GPIO_IOCTL_READ: {
        /* Read status of pins, if configured as input. Params: pointer to predefined table where data will be written */
            GPIO_PIN_STRUCT _PTR_  pin_table;
            uint_32        addr;
            uint_8         pin;

            if (dev_data_ptr->type != DEV_INPUT)
                return IO_ERROR;
            if (param_ptr == NULL) /* no list defined */
                return IO_ERROR;
            _int_disable();
            /* check if there is not pin in the list which this file does not contain */
            for (pin_table = (GPIO_PIN_STRUCT _PTR_) param_ptr; *pin_table != GPIO_LIST_END; pin_table++) {
                if (*pin_table & GPIO_PIN_VALID) { /* check pin validity bit */
                    addr = (*pin_table & GPIO_PIN_ADDR) >> 3; /* prepare address of port */ 
                    pin = 1 << (*pin_table & 0x07);  /* prepare bit mask */
                    if (addr < sizeof(GPIO_PIN_MAP)) /* pin address out of map scope? */
                        if (dev_data_ptr->pin_map.memory8[addr] & pin) { /* pin address already used? */
                            #if 0
                            if ((addr == 8) && (gpio_global_irq_map.memory8[addr] & 0xAA & pin)) { /* EPORT port and pin 1, 3, 5, or 7 */                               
                                if ( *(((uint_8 _PTR_) &mcf5225_eport_ptr->EPPDR)) & pin) /* check pin status */
                                    *pin_table |= GPIO_PIN_STATUS; /* set pin status to 1 in the list */
                                else
                                    *pin_table &= ~GPIO_PIN_STATUS; /* clear pin status to 0 in the list */
                                continue;

                            }
                            else { /* GPIO port */                            
                            #endif
                                if ( *(((uint_8 _PTR_) &mcf5329_gpio_ptr->PPDSDR_FECH) + addr) & pin) /* check pin status */
                                    *pin_table |= GPIO_PIN_STATUS; /* set pin status to 1 in the list */
                                else
                                    *pin_table &= ~GPIO_PIN_STATUS; /* clear pin status to 0 in the list */
                                continue; /* manage next pin */

                        }
                }
                /* some problem occured */
                _int_enable();
                return IO_ERROR;
            }
            _int_enable();
        }
        break;

        case GPIO_IOCTL_SET_IRQ_FUNCTION: {
            if (dev_data_ptr->type == DEV_OUTPUT)
                return IO_ERROR; /* cannot set IRQ for output devices */

            dev_data_ptr->irq_func = param_ptr;
            _int_disable();
            
            if (param_ptr == NULL) {  /* remove function from list */
                if (first_irq != NULL) {
                    GPIO_DEV_DATA_PTR gptr = first_irq;
                    while (gptr->NEXT != NULL) {
                        if (gptr == dev_data_ptr)
                            break;
                        if (gptr->NEXT == dev_data_ptr)
                            break;
                        gptr = gptr->NEXT;
                    }
                    if (gptr == dev_data_ptr) /* found as first in the list */
                        first_irq = first_irq->NEXT;
                    else if (gptr->NEXT == dev_data_ptr) /* found in the middle or at the end of list */
                        gptr->NEXT = gptr->NEXT->NEXT;
                }
            }
            else { /* add new function to the list */
                if (first_irq == NULL) {
                    first_irq = dev_data_ptr;
                }
                else {
                    GPIO_DEV_DATA_PTR gptr = first_irq;
                    while (gptr->NEXT != NULL) {
                        if (gptr == dev_data_ptr)
                            break;
                        gptr = gptr->NEXT;
                    }
                    if (gptr != dev_data_ptr)
                        gptr->NEXT = dev_data_ptr;
                }
            }
            _int_enable();
        }
        break;

        default:
            return IO_ERROR_INVALID_IOCTL_CMD;
    }
 
    return IO_OK;

general_IO_error:
    _int_enable();
    return IO_ERROR; /* cannot install interrupt routine */
} /* Endbody */

/*FUNCTION****************************************************************
* 
* Function Name    : gpio_eport_irq
* Returned Value   : 
* Comments         : GPIO IRQ handler
*    
*
*END*********************************************************************/
static void gpio_eport_irq (pointer param) {
#if 0
    GPIO_IRQ_MAP      irq_map;
    GPIO_DEV_DATA_PTR gptr = first_irq;
    
    irq_map.portnq = mcf5225_eport_ptr->EPFR;
    while (gptr) { /* list through all irq files */
        if (gptr->irq_map.reg.portnq & mcf5225_eport_ptr->EPFR)
            gptr->irq_func(NULL);
        gptr = gptr->NEXT;
    };
    mcf5225_eport_ptr->EPFR = 0xFF; /* clear flag(s) */
#endif    
}

/*FUNCTION****************************************************************
* 
* Function Name    : _bsp_get_gpio_base_address
* Returned Value   : pointer to base of GPIO registers
* Comments         :
*    This function returns base address of GPIO related register space.
*
*END*********************************************************************/
pointer _bsp_get_gpio_base_address
(
    void
)
{ /* Body */
    return (pointer)(&((VMCF5329_STRUCT_PTR)_PSP_GET_IPSBAR())->GPIO);
} /* Endbody */

/* EOF */