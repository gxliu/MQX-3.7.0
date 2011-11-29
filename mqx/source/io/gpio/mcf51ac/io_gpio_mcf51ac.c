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
* $FileName: io_gpio_mcf51ac.c$
* $Version : 3.6.2.0$
* $Date    : Jun-4-2010$
*
* Comments:
*
*   This file contains the GPIO standard functions used on boards
*
*END************************************************************************/
#include <user_config.h> 
#include "mqx.h"
#include "bsp.h"
#include "../io_gpio.h"
#include "../io_gpio_prv.h"
#include <string.h>

#if BSPCFG_ENABLE_GPIODEV

/* This structure will hold 'used pins'. If somebody would like to open 'already used pin',
** the operation will fail. All open pins within all GPIO driver files will be written here.
** We can predefine this structure with 'already used' bits for those bits, which are not
** used at all - so we will prevent open operation to be successful.
*/
GPIO_PIN_MAP  gpio_global_pin_map = {
    0x00, /* portta */
    0x00, /* porttb */
    0x00, /* porttc */
    0x00, /* porttd */
    0x00, /* portte */
    0x00, /* porttf */
    0x00, /* porttg */
    0x00, /* portth */
    0x00, /* porttj */
    {
        0xff, 0xff, 0xff /* unused[] */
    }
};

GPIO_PIN_MAP  gpio_global_irq_map = {
    0xff, /* portta */
    0xff, /* porttb */
    0xff, /* porttc */
    0x73, /* porttd */
    0xff, /* portte */
    0xff, /* porttf */
    0xe0, /* porttg */
    0xff, /* portth */
    0xff, /* porttj */
    {
        0xff, 0xff, 0xff /* unused[] */
    }
};


static const VMCF51AC_GPIO_DATA_STRUCT_PTR gpio_data_ptr[GPIO_PORT_MAX] = 
{
    &((VMCF51AC_STRUCT_PTR)BSP_IPSBAR)->GPIO_A,
    &((VMCF51AC_STRUCT_PTR)BSP_IPSBAR)->GPIO_B,
    &((VMCF51AC_STRUCT_PTR)BSP_IPSBAR)->GPIO_C,
    &((VMCF51AC_STRUCT_PTR)BSP_IPSBAR)->GPIO_D,
    &((VMCF51AC_STRUCT_PTR)BSP_IPSBAR)->GPIO_E,
    &((VMCF51AC_STRUCT_PTR)BSP_IPSBAR)->GPIO_F,
    &((VMCF51AC_STRUCT_PTR)BSP_IPSBAR)->GPIO_G,
    &((VMCF51AC_STRUCT_PTR)BSP_IPSBAR)->GPIO_H,
    &((VMCF51AC_STRUCT_PTR)BSP_IPSBAR)->GPIO_J
};

static const VMCF51AC_GPIO_STRUCT_PTR gpio_ptr[GPIO_PORT_MAX] =
{
    &((VMCF51AC_STRUCT_PTR)BSP_IPSBAR)->GPIO_SET_A,
    &((VMCF51AC_STRUCT_PTR)BSP_IPSBAR)->GPIO_SET_B,
    &((VMCF51AC_STRUCT_PTR)BSP_IPSBAR)->GPIO_SET_C,
    &((VMCF51AC_STRUCT_PTR)BSP_IPSBAR)->GPIO_SET_D,
    &((VMCF51AC_STRUCT_PTR)BSP_IPSBAR)->GPIO_SET_E,
    &((VMCF51AC_STRUCT_PTR)BSP_IPSBAR)->GPIO_SET_F,
    &((VMCF51AC_STRUCT_PTR)BSP_IPSBAR)->GPIO_SET_G,
    &((VMCF51AC_STRUCT_PTR)BSP_IPSBAR)->GPIO_SET_H,
    &((VMCF51AC_STRUCT_PTR)BSP_IPSBAR)->GPIO_SET_J   
};

extern GPIO_DEV_DATA_PTR first_irq; /* first file having used IRQ */

void gpio_cpu_configure(GPIO_DEV_DATA_PTR);
_mqx_int gpio_cpu_init();
_mqx_int gpio_cpu_open(MQX_FILE_PTR, char_ptr, char_ptr);
_mqx_int gpio_cpu_ioctl(MQX_FILE_PTR, _mqx_uint, pointer);

static void gpio_kbi_irq (pointer);

/*FUNCTION*****************************************************************
* 
* Function Name    : gpio_PTxPF_mask
* Returned Value   : 16 bit mask
* Comments         :
*    Configures pins to be GPIO based on pin map
*
*END*********************************************************************/
static const uint_16 PTxPF_mask[8] = {
    MCF51XX_PTXPF_X0_MASK,
    MCF51XX_PTXPF_X1_MASK,                  
    MCF51XX_PTXPF_X2_MASK,                  
    MCF51XX_PTXPF_X3_MASK,                  
    MCF51XX_PTXPF_X4_MASK,                  
    MCF51XX_PTXPF_X5_MASK,                  
    MCF51XX_PTXPF_X6_MASK,                  
    MCF51XX_PTXPF_X7_MASK 
};

static const char gpio_enable_mask[GPIO_PORT_MAX] = { 0xff, 0xff, 0xf7, 0xbf, 0xff, 0xff, 0xff, 0xff, 0x1f }; 
static const uint_16 gpio_special[GPIO_PORT_MAX] = { 0, 0, 0x0080, 0x2000, 0, 0, 0, 0, 0 }; /* these bits must be set to have GPIO functionality */

static uint_16 gpio_PTxPF_mask(uchar data, uchar enabled) 
{
    uint_32  i;
    uint_16  mask = 0, bit = 1;
      
    for (i = 0; i < 8; i++) {
        mask |= (data & bit & enabled ? PTxPF_mask[i] : 0x0000);
        bit = bit << 1;
    }
    return mask;
}

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
{ /* Body */
    _mqx_int i;
    MCF51AC_STRUCT_PTR  reg_ptr = _PSP_GET_MBAR();

    /* set GPIO output behavior */ 
    if (dev_data_ptr->type == DEV_OUTPUT)   
    {       
        for (i = GPIO_PORT_A; i < GPIO_PORT_MAX; i++)     
        {
            /* Set direction to output */
            gpio_data_ptr[i]->PTxDD |= dev_data_ptr->pin_map.reg.portt[i];
        }
    }
    else 
    {
        for (i = GPIO_PORT_A; i < GPIO_PORT_MAX; i++)     
        {
            /* Set direction to input */
            gpio_data_ptr[i]->PTxDD &= ~dev_data_ptr->pin_map.reg.portt[i];
            /* Enable weak pull-ups for all inputs */
            gpio_ptr[i]->PTxPE |= dev_data_ptr->pin_map.reg.portt[i];
        }
    }

    if ( dev_data_ptr->irqp_map.reg.portt[GPIO_PORT_D] | dev_data_ptr->irqp_map.reg.portt[GPIO_PORT_G] )
    {
        reg_ptr->KBI.KBIxPE |= dev_data_ptr->irqp_map.reg.portt[GPIO_PORT_D] | dev_data_ptr->irqn_map.reg.portt[GPIO_PORT_G];
        reg_ptr->KBI.KBIxSC |= MCF51XX_KBIXSC_KBIE;
    }

} /* Endbody */


/*FUNCTION*****************************************************************
* 
* Function Name    : gpio_cpu_init
* Returned Value   : IO_OK
* Comments         :
*    Performs basic initialization specific to board
*
*END*********************************************************************/

_mqx_int gpio_cpu_init()
{ /* Body */
    if (_int_install_isr(MCF51AC_INT_Vkeyboard, gpio_kbi_irq, 0) == NULL)
        return IO_ERROR; /* cannot install interrupt routine */

    return IO_OK;
} /* Endbody */

/*FUNCTION*****************************************************************
* 
* Function Name    : gpio_cpu_open
* Returned Value   : IO_OK or error
* Comments         :
*    Implements initialization for DATA GPIO
*
*END*********************************************************************/

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
      MQX_FILE_PTR fd_ptr,

      /* [IN] the file name */
      char_ptr   file_name,

      /* [IN] pointer to parameters */
      char_ptr   param_ptr
   )
{ /* Body */
    _mqx_int          i;
    MCF51AC_STRUCT_PTR  reg_ptr = _PSP_GET_MBAR();
    GPIO_DEV_DATA_PTR dev_data_ptr = (GPIO_DEV_DATA_PTR) fd_ptr->DEV_DATA_PTR;
 
    /* if file_name is used, then the user wants to open peripheral */
    if ((file_name != NULL) && (*file_name != 0)) 
    {
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
 
    if ((param_ptr != NULL) && (dev_data_ptr->type == DEV_OUTPUT)) 
    { /* set pins status before selecting GPIO function */
        /* note that this is similar to GPIO_IOCTL_WRITE function, but no checking is performed
           (was done in io_gpio_open function) */
        uint_32 _PTR_  pin_table;
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
        for (pin_table = (uint_32 _PTR_) param_ptr; *pin_table != GPIO_LIST_END; pin_table++) 
        {
            addr = (*pin_table & GPIO_PIN_ADDR) >> 3; /* prepare address of port */ 
            pin = 1 << (*pin_table & 0x07);  /* prepare bit mask */
            if (*pin_table & GPIO_PIN_STATUS)
                temp_pin1_map_ptr->memory8[addr] |= pin;
            else
                temp_pin0_map_ptr->memory8[addr] |= pin;
        }
        /* first, configure pin as output */
        gpio_cpu_configure(dev_data_ptr);

        /* ok, now we can apply new map */
        /* note: applying the map after collecting pins is due to have pins applied in one instruction */
        for (i = GPIO_PORT_A; i < GPIO_PORT_MAX; i++)
        {
            gpio_data_ptr[i]->PTxD = (gpio_data_ptr[i]->PTxD | temp_pin1_map_ptr->reg.portt[i]) & ~temp_pin0_map_ptr->reg.portt[i];
        }
        
        _mem_free(temp_pin1_map_ptr);
        _mem_free(temp_pin0_map_ptr);
    }
    else
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
      MQX_FILE_PTR fd_ptr,

      /* [IN] the ioctl command */
      _mqx_uint  cmd,

      /* [IN] the ioctl parameters */
      pointer    param_ptr
   )
{ /* Body */
    GPIO_DEV_DATA_PTR  dev_data_ptr = (GPIO_DEV_DATA_PTR) fd_ptr->DEV_DATA_PTR;
    MCF51AC_STRUCT_PTR  reg_ptr = _PSP_GET_MBAR();
 
    switch (cmd) 
    {
        case GPIO_IOCTL_ADD_PINS: 
        {
            /* Add pins to this file. Params: table with pin addresses */
            GPIO_PIN_STRUCT _PTR_  pin_table;
            uint_32        addr;
            uint_8         pin;

            /* check pin_table if they are not in global pin_map */
            _int_disable();
            for (pin_table = (uint_32 _PTR_) param_ptr; *pin_table != GPIO_LIST_END; pin_table++) 
            {
                if (*pin_table & GPIO_PIN_VALID) 
                { /* check pin validity bit */
                    addr = (*pin_table & GPIO_PIN_ADDR) >> 3; /* prepare address of port */ 
                    pin = 1 << (*pin_table & 0x07);  /* prepare bit mask */
                    if (addr < sizeof(GPIO_PIN_MAP)) /* pin address out of map scope? */
                        if (! (dev_data_ptr->pin_map.memory8[addr] & pin)) /* pin address already used? */
                            continue; /* manage next pin */
                }
                /* some problem occured */
                _int_enable();
                return IO_ERROR;
            }
            /* check successful, now we have to copy these bits to local pin map */
            for (pin_table = (uint_32 _PTR_) param_ptr; *pin_table != GPIO_LIST_END; pin_table++) 
            {
                addr = (*pin_table & GPIO_PIN_ADDR)  >> 3; /* prepare address of port */ 
                pin = 1 << (*pin_table & 0x07);  /* prepare bit mask */
                dev_data_ptr->pin_map.memory8[addr] |= pin; /* mark pin as used by this file */
                gpio_global_pin_map.memory8[addr] |= pin; /* mark pin as used globally */
            }
            gpio_cpu_configure(dev_data_ptr);
            _int_enable();
        }
        break;

        case GPIO_IOCTL_WRITE_LOG1: 
        {
            _mqx_int i;
        /* If this file is configured as output, sets every pin to 1. Params:
           list of pin addresses to be used or NULL for every pin in the file */
            if (dev_data_ptr->type != DEV_OUTPUT)
                return IO_ERROR;
            if (param_ptr == NULL) 
            { /* apply command to whole file */
                _int_disable(); /* _lwsem_wait(&gpio_sem) replacement */
                for (i = GPIO_PORT_A; i < GPIO_PORT_MAX; i++)
                    gpio_data_ptr[i]->PTxD |= dev_data_ptr->pin_map.reg.portt[i];
                _int_enable(); /* _int_enable(); */
                break;
            }
            else 
            {
                GPIO_PIN_STRUCT _PTR_  pin_table;
                uint_32        addr;
                uint_8         pin;
                GPIO_PIN_MAP_PTR    temp_pin_map_ptr;

                if (NULL == (temp_pin_map_ptr = (GPIO_PIN_MAP_PTR) _mem_alloc_system_zero(sizeof(GPIO_PIN_MAP))))
                    return IO_ERROR;
    
                _int_disable();
                /* check if there is not pin in the list which this file does not contain */
                for (pin_table = (uint_32 _PTR_) param_ptr; *pin_table != GPIO_LIST_END; pin_table++) 
                {
                    if (*pin_table & GPIO_PIN_VALID) 
                    { /* check pin validity bit */
                        addr = (*pin_table & GPIO_PIN_ADDR) >> 3; /* prepare address of port */ 
                        pin = 1 << (*pin_table & 0x07);  /* prepare bit mask */
                        if (addr < sizeof(GPIO_PIN_MAP)) /* pin address out of map scope? */
                            if (dev_data_ptr->pin_map.memory8[addr] & pin) 
                            { /* pin address already used? */
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
                for (i = GPIO_PORT_A; i < GPIO_PORT_MAX; i++)
                    gpio_data_ptr[i]->PTxD |= temp_pin_map_ptr->reg.portt[i];          
                _int_enable();
                _mem_free(temp_pin_map_ptr);
            }
        }
        break;

        case GPIO_IOCTL_WRITE_LOG0: 
        {
            _mqx_int i;
        /* If this file is configured as output, clears every pin to 0. Params:
           list of pin addresses to be used or NULL for every pin in the file */
            if (dev_data_ptr->type != DEV_OUTPUT)
                return IO_ERROR;
            if (param_ptr == NULL) 
            { /* apply command to whole file */
                _int_disable();
                for (i = GPIO_PORT_A; i < GPIO_PORT_MAX; i++)
                    gpio_data_ptr[i]->PTxD &= ~dev_data_ptr->pin_map.reg.portt[i];
                _int_enable();
                break;
            }
            else 
            {
                GPIO_PIN_STRUCT _PTR_  pin_table;
                uint_32        addr;
                uint_8         pin;
                GPIO_PIN_MAP_PTR    temp_pin_map_ptr;

                if (NULL == (temp_pin_map_ptr = (GPIO_PIN_MAP_PTR) _mem_alloc_system_zero(sizeof(GPIO_PIN_MAP))))
                    return IO_ERROR;
    
                _int_disable();
                /* check if there is not pin in the list which this file does not contain */
                for (pin_table = (uint_32 _PTR_) param_ptr; *pin_table != GPIO_LIST_END; pin_table++) 
                {
                    if (*pin_table & GPIO_PIN_VALID) 
                    { /* check pin validity bit */
                        addr = (*pin_table & GPIO_PIN_ADDR) >> 3; /* prepare address of port */ 
                        pin = 1 << (*pin_table & 0x07);  /* prepare bit mask */
                        if (addr < sizeof(GPIO_PIN_MAP)) /* pin address out of map scope? */
                            if (dev_data_ptr->pin_map.memory8[addr] & pin) 
                            { /* pin address already used? */
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
                for (i = GPIO_PORT_A; i < GPIO_PORT_MAX; i++)                       
                        gpio_data_ptr[i]->PTxD &= ~temp_pin_map_ptr->reg.portt[i];                
                _int_enable();
                _mem_free(temp_pin_map_ptr);
            }
        }
        break;

        case GPIO_IOCTL_WRITE: 
        {
            _mqx_int i;
        /* If this file is configured as output, sets every pin to the state defined in GPIO_PIN_STATUS. Params:
           list of pin addresses to be used or NULL for every pin in the file */
            if (dev_data_ptr->type != DEV_OUTPUT)
                return IO_ERROR;
            if (param_ptr == NULL) /* no param specified , but must be */
                return IO_ERROR;
            else 
            {
                GPIO_PIN_STRUCT _PTR_  pin_table;
                uint_32        addr;
                uint_8         pin;
                GPIO_PIN_MAP_PTR    temp_pin0_map_ptr;
                GPIO_PIN_MAP_PTR    temp_pin1_map_ptr;

                if (NULL == (temp_pin0_map_ptr = (GPIO_PIN_MAP_PTR) _mem_alloc_system_zero(sizeof(GPIO_PIN_MAP))))
                    return IO_ERROR;
    
                if (NULL == (temp_pin1_map_ptr = (GPIO_PIN_MAP_PTR) _mem_alloc_system_zero(sizeof(GPIO_PIN_MAP)))) 
                {
                    _mem_free(temp_pin0_map_ptr);
                    return IO_ERROR;
                }

                _int_disable();
                /* check if there is not pin in the list which this file does not contain */
                for (pin_table = (uint_32 _PTR_) param_ptr; *pin_table != GPIO_LIST_END; pin_table++) 
                {
                    if (*pin_table & GPIO_PIN_VALID) 
                    { /* check pin validity bit */
                        addr = (*pin_table & GPIO_PIN_ADDR) >> 3; /* prepare address of port */ 
                        pin = 1 << (*pin_table & 0x07);  /* prepare bit mask */
                        if (addr < sizeof(GPIO_PIN_MAP)) /* pin address out of map scope? */
                        {
                            if (dev_data_ptr->pin_map.memory8[addr] & pin) 
                            { /* pin address already used? */
                                if (*pin_table & GPIO_PIN_STATUS)
                                    temp_pin1_map_ptr->memory8[addr] |= pin;
                                else
                                    temp_pin0_map_ptr->memory8[addr] |= pin;
                                continue; /* manage next pin */
                            }                            
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
                for (i = GPIO_PORT_A; i < GPIO_PORT_MAX; i++)
                    gpio_data_ptr[i]->PTxD = (gpio_data_ptr[i]->PTxD | temp_pin1_map_ptr->reg.portt[i] ) & ~temp_pin0_map_ptr->reg.portt[i];                
                _int_enable();
                _mem_free(temp_pin1_map_ptr);
                _mem_free(temp_pin0_map_ptr);
            }
        }
        break;

        case GPIO_IOCTL_READ: 
        {
        /* Read status of pins, if configured as input. Params: pointer to predefined table where data will be written */
            volatile GPIO_PIN_STRUCT _PTR_  pin_table;
            vuint_32        addr; 
            vuint_8         pin; 

            if (dev_data_ptr->type != DEV_INPUT)
                return IO_ERROR;
            if (param_ptr == NULL) /* no list defined */
                return IO_ERROR;
            _int_disable();
            /* check if there is not pin in the list which this file does not contain */
            for (pin_table = (uint_32 _PTR_) param_ptr; *pin_table != GPIO_LIST_END; pin_table++) 
            {
                if (*pin_table & GPIO_PIN_VALID) 
                { /* check pin validity bit */
                    addr = (*pin_table & GPIO_PIN_ADDR) >> 3; /* prepare address of port */ 
                    pin = 1 << (*pin_table & 0x07);  /* prepare bit mask */
                    if (addr < sizeof(GPIO_PIN_MAP)) /* pin address out of map scope? */
                        if (dev_data_ptr->pin_map.memory8[addr] & pin) 
                        { /* pin address already used? */
                            vuint_8_ptr temp = (uint_8_ptr)&gpio_data_ptr[addr]->PTxD ; 
                            if ( *temp & pin) /* check pin status */
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

        case GPIO_IOCTL_SET_IRQ_FUNCTION: 
        {
            if (dev_data_ptr->type == DEV_OUTPUT)
                return IO_ERROR; /* cannot set IRQ for output devices */

            _int_disable();
            
            dev_data_ptr->irq_func = param_ptr;
            
            if (param_ptr == NULL) 
            {  /* remove function from list */
                if (first_irq != NULL) 
                {
                    GPIO_DEV_DATA_PTR gptr = first_irq;
                    while (gptr->NEXT != NULL) 
                    {
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
            else 
            { /* add new function to the list */
                if (first_irq == NULL) 
                {
                    first_irq = dev_data_ptr;
                }
                else 
                {
                    GPIO_DEV_DATA_PTR gptr = first_irq;
                    while (gptr->NEXT != NULL) 
                    {
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
} /* Endbody */

/*FUNCTION****************************************************************
* 
* Function Name    : gpio_kbi_irq
* Returned Value   : 
* Comments         : GPIO IRQ handler
*    
*
*END*********************************************************************/
static void gpio_kbi_irq (pointer param) 
{
    GPIO_DEV_DATA_PTR gptr = first_irq;
    MCF51AC_STRUCT_PTR  reg_ptr = _PSP_GET_MBAR();
    
    while (gptr) {
        if ((reg_ptr->KBI.KBIxSC & MCF51XX_KBIXSC_KBF)/* && (gptr->irq_map.reg.portte & mcf521jm_gpio_ptr->KBI1PE)*/ && (gptr->irq_func != NULL)) {
            gptr->irq_func(NULL);
        }
        gptr = gptr->NEXT;
    };
    
    reg_ptr->KBI.KBIxSC |= MCF51XX_KBIXSC_KBACK; /* ACK the interrupt */
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
{
    return NULL;
}

/* EOF */
#endif