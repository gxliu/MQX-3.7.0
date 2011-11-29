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
* $FileName: io_gpio_mcf51je.c$
* $Version : 3.7.2.0$
* $Date    : Feb-7-2011$
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
    0xc0, /* porttj */
    {
        0xff, 0xff, 0xff /* unused[] */
    }
};

GPIO_PIN_MAP  gpio_global_irq_map = {
    0xF1, /* portta */
    0x3F, /* porttb */
    0x03, /* porttc */
    0xFF, /* porttd */
    0xF0, /* portte */
    0xDF, /* porttf */
    0x00, /* porttg */
    0xFF, /* portth */
    0xFF, /* porttj */
    {
        0xFF, 0xFF, 0xFF /* unused[] */
    }
};

extern GPIO_DEV_DATA_PTR first_irq; /* first file having used IRQ */


/* global function prototypes */
_mqx_int gpio_cpu_init();
_mqx_int gpio_cpu_open(MQX_FILE_PTR, char_ptr, char_ptr);
_mqx_int gpio_cpu_ioctl(MQX_FILE_PTR, _mqx_uint, pointer);
/* local function prototypes */
static _mqx_int gpio_enable_interrupts(GPIO_DEV_DATA_PTR, boolean);
static void gpio_cpu_configure(GPIO_DEV_DATA_PTR);
static void gpio_kbi1_irq (pointer);
static void gpio_kbi2_irq (pointer);


const VMCF51JE_GPIO_DATA_STRUCT_PTR gpio_data_ptr[GPIO_PORT_MAX] =
{
    &(MCF51JE_BASE_PTR->GPIO_DATA_A),
    &(MCF51JE_BASE_PTR->GPIO_DATA_B),
    &(MCF51JE_BASE_PTR->GPIO_DATA_C),
    &(MCF51JE_BASE_PTR->GPIO_DATA_D),
    &(MCF51JE_BASE_PTR->GPIO_DATA_E),
    &(MCF51JE_BASE_PTR->GPIO_DATA_F),
    &(MCF51JE_BASE_PTR->GPIO_DATA_G),
    &(MCF51JE_BASE_PTR->GPIO_DATA_H),
    &(MCF51JE_BASE_PTR->GPIO_DATA_J)
};

const VMCF51JE_GPIO_STRUCT_PTR gpio_ptr[GPIO_PORT_MAX] =
{
    &(MCF51JE_BASE_PTR->GPIO_A_G[GPIO_PORT_A]),
    &(MCF51JE_BASE_PTR->GPIO_A_G[GPIO_PORT_B]),
    &(MCF51JE_BASE_PTR->GPIO_A_G[GPIO_PORT_C]),
    &(MCF51JE_BASE_PTR->GPIO_A_G[GPIO_PORT_D]),
    &(MCF51JE_BASE_PTR->GPIO_A_G[GPIO_PORT_E]),
    &(MCF51JE_BASE_PTR->GPIO_A_G[GPIO_PORT_F]),
    &(MCF51JE_BASE_PTR->GPIO_A_G[GPIO_PORT_G]),
    &(MCF51JE_BASE_PTR->GPIO_H),
    &(MCF51JE_BASE_PTR->GPIO_J)   
};


/*FUNCTION*****************************************************************
* 
* Function Name    : get_kbi_mask
* Returned Value   : 8 bit KBI mask
* Comments         :
*    Returns mask for KBI register from GPIO
*
*END*********************************************************************/

#define  get_kbi_mask(port, mask, shift)            \
    ((shift) >= 0 ?                                 \
                    ((port) & (mask)) >>  (shift)   \
                  : ((port) & (mask)) << -(shift))


/*FUNCTION*****************************************************************
* 
* Function Name    : gpio_cpu_configure
* Returned Value   : none
* Comments         :
*    Configures pins to be GPIO based on pin map
*
*END*********************************************************************/


static void gpio_cpu_configure
   (
      /* [IN] pointer to file data */
      GPIO_DEV_DATA_PTR   dev_data_ptr
   ) 
{   /* Body */
    _mqx_int             i;
    
    MCF51JE_STRUCT_PTR   reg_ptr = _PSP_GET_MBAR();

    /* set GPIO output behavior */ 
    if (dev_data_ptr->type == DEV_OUTPUT)   {       
        for (i = GPIO_PORT_A; i < GPIO_PORT_MAX; i++)
        {
            gpio_data_ptr[i]->PTxDD |= dev_data_ptr->pin_map.reg.portt[i];
        }
    }
    else 
    { /* DEV_INPUT type is supposed */
        for (i = GPIO_PORT_A; i < GPIO_PORT_MAX; i++) 
        {
            /* Set direction to input */
            gpio_data_ptr[i]->PTxDD &= ~dev_data_ptr->pin_map.reg.portt[i];
            /* Enable weak pull-ups for all inputs */
            gpio_ptr[i]->PTxPE |= dev_data_ptr->pin_map.reg.portt[i];
        }          
    }
 
    gpio_enable_interrupts(dev_data_ptr, TRUE);

} /* Endbody */


/*FUNCTION*****************************************************************
* 
* Function Name    : gpio_enable_interrupts
* Returned Value   : IO_OK
* Comments         :
*   Enable or disable interrupts for associated pin map.
*
*   KBI pin mapping for MCF51JExx device
*      
*   Port pin PTC4   PTC3    PTC2    PTB7    PTB6    PTA3    PTA2    PTA1
*   KBI1 pin KBI1P7 KBI1P6  KBI1P5  KBI1P4  KBI1P3  KBI1P2  KBI1P1  KBI1P0
*
*   Port pin PTF5   PTE3    PTE2    PTE1    PTE0    PTC7    PTC6    PTC5
*   KBI2 pin KBI2P7 KBI2P6  KBI2P5  KBI2P4  KBI2P3  KBI2P2  KBI2P1  KBI2P0   
*
*END*********************************************************************/

static _mqx_int gpio_enable_interrupts
    (
        /* [IN] pointer to file data */
        GPIO_DEV_DATA_PTR   dev_data_ptr,
        /* [IN] pointer to file data */        
        boolean             state
    )
{
    
    uint_8               pmask, nmask;
    MCF51JE_STRUCT_PTR   reg_ptr = _PSP_GET_MBAR();
    
    /* Mask interrupts by clearing KBIxSC[KBIE]. */
    reg_ptr->KBI1.KBISC &= ~MCF51XX_KBIXSC_KBIE;
    /* PTA3->KBI1P2, PTA2->KBI1P1, PTA1->KBI1P0 */
    pmask  = get_kbi_mask(dev_data_ptr->irqp_map.reg.portt[GPIO_PORT_A], (MCF51XX_PTX3_MASK|MCF51XX_PTX2_MASK|MCF51XX_PTX1_MASK), (MCF51XX_PTX1_SHIFT-MCF51XX_KBIX_P0_SHIFT));
    nmask  = get_kbi_mask(dev_data_ptr->irqn_map.reg.portt[GPIO_PORT_A], (MCF51XX_PTX3_MASK|MCF51XX_PTX2_MASK|MCF51XX_PTX1_MASK), (MCF51XX_PTX1_SHIFT-MCF51XX_KBIX_P0_SHIFT));
    /* PTB7->KBI1P4, PTB6->KBI1P3 */
    pmask |= get_kbi_mask(dev_data_ptr->irqp_map.reg.portt[GPIO_PORT_B], (MCF51XX_PTX7_MASK|MCF51XX_PTX6_MASK), (MCF51XX_PTX6_SHIFT-MCF51XX_KBIX_P3_SHIFT));
    nmask |= get_kbi_mask(dev_data_ptr->irqn_map.reg.portt[GPIO_PORT_B], (MCF51XX_PTX7_MASK|MCF51XX_PTX6_MASK), (MCF51XX_PTX6_SHIFT-MCF51XX_KBIX_P3_SHIFT));
    /* PTC3->KBI1P6, PTC2->KBI1P5 */
    pmask |= get_kbi_mask(dev_data_ptr->irqp_map.reg.portt[GPIO_PORT_C], (MCF51XX_PTX4_MASK|MCF51XX_PTX3_MASK|MCF51XX_PTX2_MASK), (MCF51XX_PTX2_SHIFT-MCF51XX_KBIX_P5_SHIFT));
    nmask |= get_kbi_mask(dev_data_ptr->irqn_map.reg.portt[GPIO_PORT_C], (MCF51XX_PTX4_MASK|MCF51XX_PTX3_MASK|MCF51XX_PTX2_MASK), (MCF51XX_PTX2_SHIFT-MCF51XX_KBIX_P5_SHIFT));
    /* Select the pin polarity by setting the appropriate KBIxES[KBEDGn] bits */
    reg_ptr->KBI1.KBIES |= pmask;
    reg_ptr->KBI1.KBIES &= ~nmask; 
    
    /*  Enable or disable interrupts for associated pinlist in KBIxPE */
    if (state == TRUE) 
        reg_ptr->KBI1.KBIPE |=  (pmask | nmask);
    else
        reg_ptr->KBI1.KBIPE &= ~(pmask | nmask);
    
    /* Write to KBIxSC[KBACK] to clear any false interrupts. */
    reg_ptr->KBI1.KBISC |= MCF51XX_KBIXSC_KBACK;
    /* Set KBIxSC[KBIE] to enable interrupts. */
    if (reg_ptr->KBI1.KBIPE)
        reg_ptr->KBI1.KBISC |= MCF51XX_KBIXSC_KBIE;
    
    /* Mask interrupts by clearing KBIxSC[KBIE]. */
    reg_ptr->KBI2.KBISC &= ~MCF51XX_KBIXSC_KBIE;
    /* PTC7->KBI2P2, PTC6->KBI2P1, PTC5->KBI2P0 */
    pmask  = get_kbi_mask(dev_data_ptr->irqp_map.reg.portt[GPIO_PORT_C], (MCF51XX_PTX7_MASK|MCF51XX_PTX6_MASK|MCF51XX_PTX5_MASK), (MCF51XX_PTX5_SHIFT-MCF51XX_KBIX_P0_SHIFT));
    nmask  = get_kbi_mask(dev_data_ptr->irqn_map.reg.portt[GPIO_PORT_C], (MCF51XX_PTX7_MASK|MCF51XX_PTX6_MASK|MCF51XX_PTX5_MASK), (MCF51XX_PTX5_SHIFT-MCF51XX_KBIX_P0_SHIFT));
    /* PTE3->KBI2P6, PTE2->KBI2P5, PTE1->KBI2P4, PTE0->KBI2P3 */
    pmask |= get_kbi_mask(dev_data_ptr->irqp_map.reg.portt[GPIO_PORT_E], (MCF51XX_PTX3_MASK|MCF51XX_PTX2_MASK|MCF51XX_PTX1_MASK|MCF51XX_PTX0_MASK), (MCF51XX_PTX0_SHIFT-MCF51XX_KBIX_P3_SHIFT));
    nmask |= get_kbi_mask(dev_data_ptr->irqn_map.reg.portt[GPIO_PORT_E], (MCF51XX_PTX3_MASK|MCF51XX_PTX2_MASK|MCF51XX_PTX1_MASK|MCF51XX_PTX0_MASK), (MCF51XX_PTX0_SHIFT-MCF51XX_KBIX_P3_SHIFT));
    /* PTF5->KBI2P7 */
    pmask |= get_kbi_mask(dev_data_ptr->irqp_map.reg.portt[GPIO_PORT_F], (MCF51XX_PTX5_MASK), (MCF51XX_PTX5_SHIFT-MCF51XX_KBIX_P7_SHIFT));
    nmask |= get_kbi_mask(dev_data_ptr->irqn_map.reg.portt[GPIO_PORT_F], (MCF51XX_PTX5_MASK), (MCF51XX_PTX5_SHIFT-MCF51XX_KBIX_P7_SHIFT));
    /* Select the pin polarity by setting the appropriate KBIxES[KBEDGn] bits */
    reg_ptr->KBI2.KBIES |= pmask;
    reg_ptr->KBI2.KBIES &= ~nmask; 
 
    /*  Enable or disable interrupts for associated pinlist in KBIxPE */
    if (state == TRUE) 
        reg_ptr->KBI2.KBIPE |=  (pmask | nmask);
    else
        reg_ptr->KBI2.KBIPE &= ~(pmask | nmask); 
 
    /* Write to KBIxSC[KBACK] to clear any false interrupts. */
    reg_ptr->KBI2.KBISC |= MCF51XX_KBIXSC_KBACK;
    /* Set KBIxSC[KBIE] to enable interrupts. */
    if (reg_ptr->KBI2.KBIPE)
        reg_ptr->KBI2.KBISC |= MCF51XX_KBIXSC_KBIE;
        
    return IO_OK;
}

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
    if (_int_install_isr(MCF51JE_INT_Vkeyboard1, gpio_kbi1_irq, 0) == NULL)
        return IO_ERROR; /* cannot install interrupt routine */

    if (_int_install_isr(MCF51JE_INT_Vkeyboard2, gpio_kbi2_irq, 0) == NULL)
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
    _mqx_int            i;
    MCF51JE_STRUCT_PTR  reg_ptr = _PSP_GET_MBAR();
    GPIO_DEV_DATA_PTR   dev_data_ptr = (GPIO_DEV_DATA_PTR) fd_ptr->DEV_DATA_PTR;
 
    /* if file_name is used, then the user wants to open peripheral */
    if ((file_name != NULL) && (*file_name != 0)) 
    {
        if (!strncmp(file_name, "gpio:write",       11))  /* user wants write access to GPIO */
            dev_data_ptr->type = DEV_OUTPUT;
        else if (!strncmp(file_name, "gpio:output", 12))  /* user wants write access to GPIO */
            dev_data_ptr->type = DEV_OUTPUT;
        else if (!strncmp(file_name, "gpio:read",   10))  /* user wants read access to GPIO  */
            dev_data_ptr->type = DEV_INPUT;
        else if (!strncmp(file_name, "gpio:input",  11))  /* user wants read access to GPIO  */
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
        uint_32_ptr         pin_table;
        uint_32             addr;
        uint_8              pin;
        GPIO_PIN_MAP        temp_pin0_map = {0};
        GPIO_PIN_MAP        temp_pin1_map = {0};

        /* prepare pin map */
        for (pin_table = (uint_32 _PTR_) param_ptr; *pin_table != GPIO_LIST_END; pin_table++) 
        {
            addr = (*pin_table & GPIO_PIN_ADDR) >> 3; /* prepare address of port */ 
            pin = 1 << (*pin_table & 0x07);  /* prepare bit mask */
            if (*pin_table & GPIO_PIN_STATUS)
                temp_pin1_map.memory8[addr] |= pin;
            else
                temp_pin0_map.memory8[addr] |= pin;
        }
        /* first, configure pin as output */
        gpio_cpu_configure(dev_data_ptr);

        /* ok, now we can apply new map */
        /* note: applying the map after collecting pins is due to have pins applied in one instruction */
        for (i = GPIO_PORT_A; i < GPIO_PORT_MAX; i++)   {
            gpio_data_ptr[i]->PTxD = (gpio_data_ptr[i]->PTxD | temp_pin1_map.reg.portt[i]) & ~temp_pin0_map.reg.portt[i];
        }
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
    GPIO_DEV_DATA_PTR   dev_data_ptr = (GPIO_DEV_DATA_PTR) fd_ptr->DEV_DATA_PTR;
    MCF51JE_STRUCT_PTR  reg_ptr = _PSP_GET_MBAR();
 
    switch (cmd) 
    {
        case GPIO_IOCTL_ADD_PINS: 
        {
            /* Add pins to this file. Params: table with pin addresses */
            GPIO_PIN_STRUCT _PTR_   pin_table;
            uint_32                 addr;
            uint_8                  pin;

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
                GPIO_PIN_STRUCT _PTR_   pin_table;
                uint_32                 addr;
                uint_8                  pin;
                GPIO_PIN_MAP            temp_pin_map = {0};
    
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
                                temp_pin_map.memory8[addr] |= pin;
                                continue; /* manage next pin */
                            }
                    }
                    /* some problem occured */
                    _int_enable();
                    return IO_ERROR;
                }
                /* ok, now we can apply new map */
                /* note: applying the map after collecting pins is due to have pins applied in one instruction */
                for (i = GPIO_PORT_A; i < GPIO_PORT_MAX; i++)
                    gpio_data_ptr[i]->PTxD |= temp_pin_map.reg.portt[i];
                _int_enable();
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
                GPIO_PIN_STRUCT _PTR_   pin_table;
                uint_32                 addr;
                uint_8                  pin;
                GPIO_PIN_MAP            temp_pin_map = {0};

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
                                temp_pin_map.memory8[addr] |= pin;
                                continue; /* manage next pin */
                            }
                    }
                    /* some problem occured */
                    _int_enable();
                    return IO_ERROR;
                }
                /* ok, now we can apply new map */
                /* note: applying the map after collecting pins is due to have pins applied in one instruction */
                for (i = GPIO_PORT_A; i < GPIO_PORT_MAX; i++)                       
                        gpio_data_ptr[i]->PTxD &= ~temp_pin_map.reg.portt[i];
                _int_enable();
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
                GPIO_PIN_STRUCT _PTR_   pin_table;
                uint_32                 addr;
                uint_8                  pin;
                GPIO_PIN_MAP            temp_pin0_map = {0};
                GPIO_PIN_MAP            temp_pin1_map = {0};
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
                                      temp_pin1_map.memory8[addr] |= pin;
                                else
                                      temp_pin0_map.memory8[addr] |= pin;
                                continue; /* manage next pin */
                            }                            
                        }    
                    }
                    /* some problem occured */
                    _int_enable();
                    return IO_ERROR;
                }
                /* ok, now we can apply new map */
                /* note: applying the map after collecting pins is due to have pins applied in one instruction */
                for (i = GPIO_PORT_A; i < GPIO_PORT_MAX; i++)
                    gpio_data_ptr[i]->PTxD = (gpio_data_ptr[i]->PTxD | temp_pin1_map.reg.portt[i] ) & ~temp_pin0_map.reg.portt[i];
                _int_enable();
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

        case GPIO_IOCTL_ENABLE_IRQ: 
        {
            return gpio_enable_interrupts(dev_data_ptr, TRUE);
        }
        break;

        case GPIO_IOCTL_DISABLE_IRQ: 
        {
            return gpio_enable_interrupts(dev_data_ptr, FALSE);
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
* Function Name    : gpio_kbi1_irq
* Returned Value   : 
* Comments         : GPIO IRQ handler
*    
*
*END*********************************************************************/
static void gpio_kbi1_irq (pointer param) 
{
    GPIO_DEV_DATA_PTR gptr = first_irq;
    MCF51JE_STRUCT_PTR  reg_ptr = _PSP_GET_MBAR();
    
    while (gptr) 
    {
        if ((reg_ptr->KBI1.KBISC & MCF51XX_KBIXSC_KBF) && (gptr->irq_func != NULL)) 
        {
            gptr->irq_func(NULL);
        }
        gptr = gptr->NEXT;
    }
    
    reg_ptr->KBI1.KBISC |= MCF51XX_KBIXSC_KBACK; /* ACK the interrupt */
}

/*FUNCTION****************************************************************
* 
* Function Name    : gpio_kbi2_irq
* Returned Value   : 
* Comments         : GPIO IRQ handler
*    
*
*END*********************************************************************/
static void gpio_kbi2_irq (pointer param) 
{
    GPIO_DEV_DATA_PTR gptr = first_irq;
    MCF51JE_STRUCT_PTR  reg_ptr = _PSP_GET_MBAR();
    
    while (gptr) 
    {
        if ((reg_ptr->KBI2.KBISC & MCF51XX_KBIXSC_KBF) && (gptr->irq_func != NULL)) 
        {
            gptr->irq_func(NULL);
        }
        gptr = gptr->NEXT;
    }
    
    reg_ptr->KBI2.KBISC |= MCF51XX_KBIXSC_KBACK; /* ACK the interrupt */
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