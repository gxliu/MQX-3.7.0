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
* $FileName: io_gpio_mcf5441.c$
* $Version : 3.7.5.0$
* $Date    : Mar-15-2011$
*
* Comments:
*
*   This file contains the GPIO standard functions used on boards
*
*END************************************************************************/

#include "mqx.h"
#include "bsp.h"
#include "io_gpio.h"
#include "io_gpio_prv.h"
#include <string.h>


#define MAKE_ADDRESS(byte, bit) (byte * 8 + bit)

static const uint_8 gpio_par_offset[] = {
    MAKE_ADDRESS(1, 0), //PA 
    MAKE_ADDRESS(1, 2),
    MAKE_ADDRESS(1, 4),
    MAKE_ADDRESS(1, 6),
    MAKE_ADDRESS(0, 0),
    MAKE_ADDRESS(0, 2),
    MAKE_ADDRESS(0, 4),
    MAKE_ADDRESS(0, 6),
    MAKE_ADDRESS(3, 2), //PB
    MAKE_ADDRESS(3, 4),
    MAKE_ADDRESS(3, 6),
    MAKE_ADDRESS(2, 0),
    MAKE_ADDRESS(2, 2),
    MAKE_ADDRESS(2, 4),
    MAKE_ADDRESS(2, 6),
    MAKE_ADDRESS(0, 3),
    MAKE_ADDRESS(7, 7), //PC
    MAKE_ADDRESS(4, 0),
    MAKE_ADDRESS(5, 2),
    MAKE_ADDRESS(5, 4),
    MAKE_ADDRESS(4, 2),
    MAKE_ADDRESS(5, 6),
    MAKE_ADDRESS(4, 4),
    MAKE_ADDRESS(3, 0),
    MAKE_ADDRESS(8, 2), //PD
    MAKE_ADDRESS(8, 4),
    MAKE_ADDRESS(8, 6),
    MAKE_ADDRESS(7, 4),
    MAKE_ADDRESS(6, 4),
    MAKE_ADDRESS(6, 6),
    MAKE_ADDRESS(6, 2),
    MAKE_ADDRESS(6, 0),
    MAKE_ADDRESS(10, 2), //PE
    MAKE_ADDRESS(10, 4),
    MAKE_ADDRESS(10, 6),
    MAKE_ADDRESS(9, 0),
    MAKE_ADDRESS(9, 2),
    MAKE_ADDRESS(9, 4),
    MAKE_ADDRESS(9, 6),
    MAKE_ADDRESS(8, 0),
    MAKE_ADDRESS(12, 2), //PF
    MAKE_ADDRESS(12, 4),
    MAKE_ADDRESS(12, 6),
    MAKE_ADDRESS(11, 0),
    MAKE_ADDRESS(11, 2),
    MAKE_ADDRESS(11, 4),
    MAKE_ADDRESS(11, 6),
    MAKE_ADDRESS(10, 0),
    MAKE_ADDRESS(15, 0), //PG
    MAKE_ADDRESS(14, 0),
    MAKE_ADDRESS(14, 2),
    MAKE_ADDRESS(14, 4),
    MAKE_ADDRESS(14, 6),
    MAKE_ADDRESS(13, 0),
    MAKE_ADDRESS(13, 2),
    MAKE_ADDRESS(12, 0),
    MAKE_ADDRESS(18, 4), //PH
    MAKE_ADDRESS(18, 6),
    MAKE_ADDRESS(20, 0),
    MAKE_ADDRESS(17, 0),
    MAKE_ADDRESS(16, 0),
    MAKE_ADDRESS(16, 2),
    MAKE_ADDRESS(16, 4),
    MAKE_ADDRESS(16, 6),
    MAKE_ADDRESS(21, 0), //PI
    MAKE_ADDRESS(21, 0),
    MAKE_ADDRESS(19, 0),
    MAKE_ADDRESS(19, 2),
    MAKE_ADDRESS(19, 4),
    MAKE_ADDRESS(19, 6),
    MAKE_ADDRESS(18, 0),
    MAKE_ADDRESS(18, 2)
};

/* number of bits used in PAR register for every pin: 1 = 1 bit, 0 = 2 or more bits */
static const uint_8 gpio_par_width[] = {
    0x20, //PA
    0x88, //PB
    0x40, //PC
    0x00, //PD
    0x00, //PE
    0x00, //PF
    0x00, //PG
    0x03, //PH
    0xFC, //PI
};

/* This structure will hold 'used pins'. If somebody would like to open 'already used pin',
** the operation will fail. All open pins within all GPIO driver files will be written here.
** We can predefine this structure with 'already used' bits for those bits, which are not
** used at all - so we will prevent open operation to be successful.
*/
GPIO_PIN_MAP  gpio_global_pin_map = {
    0x00,   /* porta */
    0x00,   /* portb */
    0x00,   /* portc */
    0x00,   /* portd */
    0x00,   /* porte */
    0x00,   /* portf */
    0x00,   /* portg */
    0x00,   /* porth */
    0x00,   /* porti */
    0x00,   /* portj */
    0x00    /* portk */
};

GPIO_PIN_MAP  gpio_global_irq_map = {
    0xff,   /* porta */
    0xff,   /* portb */
    0x81,   /* portc */
    0xff,   /* portd */
    0xff,   /* porte */
    0xff,   /* portf */
    0xff,   /* portg */
    0xff,   /* porth */
    0xff,   /* porti */
    0xff,   /* portj */
    0xff    /* portk */
};

extern GPIO_DEV_DATA_PTR first_irq; /* first file having used IRQ */

/* pointer to the start of GPIO registers */
VMCF5441_GPIO_STRUCT_PTR mcf5441_gpio_ptr;
VMCF5441_EPORT_STRUCT_PTR mcf5441_eport_ptr;

static _mqx_int gpio_cpu_configure(GPIO_DEV_DATA_PTR);
static void gpio_eport_irq(pointer);
_mqx_int gpio_cpu_init();
_mqx_int gpio_cpu_open(MQX_FILE_PTR, char_ptr, char_ptr);
_mqx_int gpio_cpu_ioctl(MQX_FILE_PTR, _mqx_uint, pointer);

/*FUNCTION*****************************************************************
* 
* Function Name    : gpio_cpu_configure
* Returned Value   : IO_OK
* Comments         :
*    Looks if it is possible to configure GPIO_FEC
*
*END*********************************************************************/
static _mqx_int gpio_cpu_try_config(GPIO_DEV_DATA_PTR dev_data_ptr)
{
    _mqx_int status;
    _mqx_uint fec_group = 0;

    if ((dev_data_ptr->pin_map.reg.porti | gpio_global_pin_map.reg.porti) & 0x03)
        fec_group |= 0x01; // A
    if ((dev_data_ptr->pin_map.reg.portj | gpio_global_pin_map.reg.portj) & 0xFE)
        fec_group |= 0x02; // B
    if ((dev_data_ptr->pin_map.reg.portj | gpio_global_pin_map.reg.portj) & 0x01)
        fec_group |= 0x04; // C
    if ((dev_data_ptr->pin_map.reg.portk | gpio_global_pin_map.reg.portk) & 0x80)
        fec_group |= 0x04; // C
    if ((dev_data_ptr->pin_map.reg.portk | gpio_global_pin_map.reg.portk) & 0x7F)
        fec_group |= 0x08; // D

    if ((fec_group == 0x01) && \
        ((mcf5441_gpio_ptr->PAR_FEC == 0x05) || ((mcf5441_gpio_ptr->PAR_FEC == 0x07))))
        return IO_ERROR;  // PAR_FEC was set to peripheral mode before and we cannot guess which value to set for PAR_FEC

    return IO_OK;
}

/*FUNCTION*****************************************************************
* 
* Function Name    : gpio_cpu_configure
* Returned Value   : IO_OK
* Comments         :
*    Configures pins to be GPIO based on pin map
*
*END*********************************************************************/
static _mqx_int gpio_cpu_configure
   (
      /* [IN] pointer to file data */
      GPIO_DEV_DATA_PTR   dev_data_ptr
   )
{ /* Body */
    _mqx_uint fec_group = 0;
    volatile uint_16   eport_par;
    _mqx_int  status, i;

    status = gpio_cpu_try_config(dev_data_ptr);
    if (status != IO_OK)
        return status;

    if (dev_data_ptr->type == DEV_OUTPUT) { /* set GPIO output behavior */
        * (((uint_32 _PTR_) (&mcf5441_gpio_ptr->PDDR_A)) + 0) |= dev_data_ptr->pin_map.memory32[0];
        * (((uint_32 _PTR_) (&mcf5441_gpio_ptr->PDDR_A)) + 1) |= dev_data_ptr->pin_map.memory32[1];
        * (((uint_32 _PTR_) (&mcf5441_gpio_ptr->PDDR_A)) + 2) |= dev_data_ptr->pin_map.memory32[2];
    }
    else { /* DEV_INPUT type is supposed */
        * (((uint_32 _PTR_) (&mcf5441_gpio_ptr->PDDR_A)) + 0) &= ~dev_data_ptr->pin_map.memory32[0];
        * (((uint_32 _PTR_) (&mcf5441_gpio_ptr->PDDR_A)) + 1) &= ~dev_data_ptr->pin_map.memory32[1];
        * (((uint_32 _PTR_) (&mcf5441_gpio_ptr->PDDR_A)) + 2) &= ~dev_data_ptr->pin_map.memory32[2];
    }
 
    /* Set PAR_FEC separately: PORTI[0:2], PORTJ[0:7] and PORTK[0:7]
    ** Strategy: we will search for minimalist set that resembles all needed pins.
    ** We have 5 groups of pins:
    ** A = { PI[0:1] }
    ** B = { PJ[1:7] }
    ** C = { PJ0, PK7 }
    ** D = { PK[0:1] }
    **
    ** We have following PAR_FEC settings and its pin group usage:
    ** 0000 - none
    ** 0001 - A
    ** 0010 - reserved
    ** 0011 - none
    ** 0100 - CA (means C + A)
    ** 0101 - C
    ** 0110 - A
    ** 0111 - DC
    ** 1000 - none
    ** 1001 - DCA
    ** 1010 - A
    ** 1011 - BA
    ** 1100 - CBA
    ** 1101 - DCBA
    ** 1110 - reserved
    ** 1111 - reserved
    **
    ** note that settings { 0001, 0110, 1010 } overlap,
    ** so we have to distinguish which mode within them to select by currect MII/ULPI functionality
    */
    if ((dev_data_ptr->pin_map.reg.porti | gpio_global_pin_map.reg.porti) & 0x03)
        fec_group |= 0x01; // A
    if ((dev_data_ptr->pin_map.reg.portj | gpio_global_pin_map.reg.portj) & 0xFE)
        fec_group |= 0x02; // B
    if ((dev_data_ptr->pin_map.reg.portj | gpio_global_pin_map.reg.portj) & 0x01)
        fec_group |= 0x04; // C
    if ((dev_data_ptr->pin_map.reg.portk | gpio_global_pin_map.reg.portk) & 0x80)
        fec_group |= 0x04; // C
    if ((dev_data_ptr->pin_map.reg.portk | gpio_global_pin_map.reg.portk) & 0x7F)
        fec_group |= 0x08; // D

    switch (fec_group) {
        case 0x0F: // DCBA
            mcf5441_gpio_ptr->PAR_FEC = 0x0D; // DCBA
            break;
        case 0x0E: // DCB
            mcf5441_gpio_ptr->PAR_FEC = 0x0D; // DCBA
            break;
        case 0x0D: // DCA
            mcf5441_gpio_ptr->PAR_FEC = 0x09; // DCA
            break;
        case 0x0C: // DC
            mcf5441_gpio_ptr->PAR_FEC = 0x07; // DC
            break;
        case 0x0B: // DBA
            mcf5441_gpio_ptr->PAR_FEC = 0x0D; // DCBA
            break;
        case 0x0A: // DB
            mcf5441_gpio_ptr->PAR_FEC = 0x0D; // DCBA
            break;
        case 0x09: // DA
            mcf5441_gpio_ptr->PAR_FEC = 0x09; // DCA
            break;
        case 0x08: // D
            mcf5441_gpio_ptr->PAR_FEC = 0x07; // DC
            break;
        case 0x07: // CBA
            mcf5441_gpio_ptr->PAR_FEC = 0x0C; // CBA
            break;
        case 0x06: // CB
            mcf5441_gpio_ptr->PAR_FEC = 0x0C; // CBA
            break;
        case 0x05: // CA
            mcf5441_gpio_ptr->PAR_FEC = 0x04; // CA
            break;
        case 0x04: // C 
            mcf5441_gpio_ptr->PAR_FEC = 0x0C; // CBA
            break;
        case 0x03: // BA
            mcf5441_gpio_ptr->PAR_FEC = 0x0B; // BA
            break;
        case 0x02: // B
            mcf5441_gpio_ptr->PAR_FEC = 0x0B; // BA
            break;
        case 0x01: // A
            switch (mcf5441_gpio_ptr->PAR_FEC) {
                case 0x00:
                    mcf5441_gpio_ptr->PAR_FEC = 0x01; // A
                    break;
                case 0x03:
                    mcf5441_gpio_ptr->PAR_FEC = 0x06; // A
                    break;
                case 0x08:
                    mcf5441_gpio_ptr->PAR_FEC = 0x0A; // A
                    break;
                case 0x05:
                case 0x07:
                    break; // error, this case is already checked in gpio_cpu_try_config
                default:
                    // pin group A is already set to GPIO
                    break;
            }
    }

    /* set pin functionality to be GPIO for the whole file */
    for (i = 0; i < sizeof(gpio_par_width); i++) {
        if (dev_data_ptr->pin_map.memory8[i]) {
           _mqx_uint bit_num;
           _mqx_uint data_size;
           _mqx_uint pin_addr;
           uint_8    used_in_port = dev_data_ptr->pin_map.memory8[i];

           for (bit_num = 0; bit_num < 8; bit_num++, used_in_port = used_in_port >> 1)
                if (used_in_port & 0x01) {
                    _mqx_uint pin_addr = i * 8 + bit_num;
                    _mqx_uint par_offset_addr = gpio_par_offset[pin_addr] / 8;
                    _mqx_uint par_offset_shift = gpio_par_offset[pin_addr] % 8;
                    _mqx_uint par_width = gpio_par_width[i] & (1 << bit_num);

                    if (par_offset_addr == 21)
                        continue; /* dont set PAR_FEC for now */

                    if ((par_offset_addr == 4) || (par_offset_addr == 5))
                        if ((dev_data_ptr->irqp_map.reg.portc | dev_data_ptr->irqn_map.reg.portc) & (1 << bit_num)) {
                             /* set PAR_IRQ for interrupt pins to primary function */
                            if (par_width)
                                * (((uint_8 _PTR_) (&mcf5441_gpio_ptr->PAR_FBCTL)) + par_offset_addr) |= (0x01 << par_offset_shift);
                            else
                                * (((uint_8 _PTR_) (&mcf5441_gpio_ptr->PAR_FBCTL)) + par_offset_addr) |= (0x03 << par_offset_shift);
                            continue;
                        }

                    if (par_width)
                        * (((uint_8 _PTR_) (&mcf5441_gpio_ptr->PAR_FBCTL)) + par_offset_addr) &= ~(0x01 << par_offset_shift);
                    else
                        * (((uint_8 _PTR_) (&mcf5441_gpio_ptr->PAR_FBCTL)) + par_offset_addr) &= ~(0x03 << par_offset_shift);
                }
        }
    }

    /* configure EPORT module */
    mcf5441_eport_ptr->EPPAR |= /* react on rising / falling edge */
        ( dev_data_ptr->irqp_map.reg.portc & 0x01 ? 0x0001 : 0x0000 ) |
        ( dev_data_ptr->irqp_map.reg.portc & 0x02 ? 0x0004 : 0x0000 ) |
        ( dev_data_ptr->irqp_map.reg.portc & 0x04 ? 0x0010 : 0x0000 ) |
        ( dev_data_ptr->irqp_map.reg.portc & 0x08 ? 0x0040 : 0x0000 ) |
        ( dev_data_ptr->irqp_map.reg.portc & 0x10 ? 0x0100 : 0x0000 ) |
        ( dev_data_ptr->irqp_map.reg.portc & 0x20 ? 0x0400 : 0x0000 ) |
        ( dev_data_ptr->irqp_map.reg.portc & 0x40 ? 0x1000 : 0x0000 ) |
        ( dev_data_ptr->irqp_map.reg.portc & 0x80 ? 0x4000 : 0x0000 ) |
        ( dev_data_ptr->irqn_map.reg.portc & 0x01 ? 0x0002 : 0x0000 ) |
        ( dev_data_ptr->irqn_map.reg.portc & 0x02 ? 0x0008 : 0x0000 ) |
        ( dev_data_ptr->irqn_map.reg.portc & 0x04 ? 0x0020 : 0x0000 ) |
        ( dev_data_ptr->irqn_map.reg.portc & 0x08 ? 0x0080 : 0x0000 ) |
        ( dev_data_ptr->irqn_map.reg.portc & 0x10 ? 0x0200 : 0x0000 ) |
        ( dev_data_ptr->irqn_map.reg.portc & 0x20 ? 0x0800 : 0x0000 ) |
        ( dev_data_ptr->irqn_map.reg.portc & 0x40 ? 0x2000 : 0x0000 ) |
        ( dev_data_ptr->irqn_map.reg.portc & 0x80 ? 0x2000 : 0x0000 );
    mcf5441_eport_ptr->EPIER |= (dev_data_ptr->irqp_map.reg.portc | dev_data_ptr->irqn_map.reg.portc); /* set interrupt enable */

    return IO_OK;
} /* Endbody */

/*FUNCTION*****************************************************************
* 
* Function Name    : gpio_cpu_install
* Returned Value   : IO_OK
* Comments         :
*    Performs basic initialization specific to board
*
*END*********************************************************************/

_mqx_int gpio_cpu_init()
{ /* Body */
    VMCF5441_STRUCT_PTR  reg_ptr;
 
    reg_ptr = _PSP_GET_IPSBAR();

    mcf5441_gpio_ptr = (VMCF5441_GPIO_STRUCT_PTR) _bsp_get_gpio_base_address();
    mcf5441_eport_ptr = (VMCF5441_EPORT_STRUCT_PTR) &reg_ptr->EPORT;
 
    return IO_OK;
} /* Endbody */

/*FUNCTION*****************************************************************
* 
* Function Name    : gpio_data_open
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
    GPIO_DEV_DATA_PTR dev_data_ptr = (GPIO_DEV_DATA_PTR) fd_ptr->DEV_DATA_PTR;
    VMCF5441_STRUCT_PTR  reg_ptr;
    _mqx_int i;
    static const int_8 eport_levels[] = 
    {
        -1, /* use illegal value for non-existing interrupt source */
        BSP_EPORT_EPF1_INT_LEVEL,
        BSP_EPORT_EPF2_INT_LEVEL,
        BSP_EPORT_EPF3_INT_LEVEL,
        BSP_EPORT_EPF4_INT_LEVEL,
        BSP_EPORT_EPF5_INT_LEVEL,
        BSP_EPORT_EPF6_INT_LEVEL,
        BSP_EPORT_EPF7_INT_LEVEL,
    };
 
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
 
    /* check which irq pin to be opened and prepare interrupt service routine */
    for (i = 1; i < 8; i++) {
        if ((dev_data_ptr->irqp_map.reg.portc | dev_data_ptr->irqn_map.reg.portc) & (1 << i)) {
            if (NULL == _int_install_isr(MCF5441_INT_EPFR0_EPF1 - 1 + i, gpio_eport_irq, NULL))
                return IO_ERROR; /* could not install interrupt routine */
            if (-1 != eport_levels[i]) {
                _mcf5441_int_init(MCF5441_INT_EPFR0_EPF1 - 1 + i, eport_levels[i], TRUE);
                reg_ptr = _PSP_GET_IPSBAR();
                reg_ptr->SCM_PMM.PMM.PPMCR0 = 36; /* enable EPORT clock */
            }
        }
    }

    if ((param_ptr != NULL) && (dev_data_ptr->type == DEV_OUTPUT)) { /* set pins status before selecting GPIO function */
        /* note that this is similar to GPIO_IOCTL_WRITE function, but no checking is performed
           (was done in io_gpio_open function) */
        GPIO_PIN_STRUCT _PTR_  pin_table;
        uint_32        addr;
        uint_8         pin;
        GPIO_PIN_MAP_PTR  temp_pin0_map_ptr;
        GPIO_PIN_MAP_PTR  temp_pin1_map_ptr;

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
        * (((uint_32 _PTR_) (&mcf5441_gpio_ptr->PPDSDR_A)) + 0) = temp_pin1_map_ptr->memory32[0];
        * (((uint_32 _PTR_) (&mcf5441_gpio_ptr->PCLRR_A)) + 0) = ~temp_pin0_map_ptr->memory32[0];
        * (((uint_32 _PTR_) (&mcf5441_gpio_ptr->PPDSDR_A)) + 1) = temp_pin1_map_ptr->memory32[1];
        * (((uint_32 _PTR_) (&mcf5441_gpio_ptr->PCLRR_A)) + 1) = ~temp_pin0_map_ptr->memory32[1];
        * (((uint_32 _PTR_) (&mcf5441_gpio_ptr->PPDSDR_A)) + 2) = temp_pin1_map_ptr->memory32[2];
        * (((uint_32 _PTR_) (&mcf5441_gpio_ptr->PCLRR_A)) + 2) = ~temp_pin0_map_ptr->memory32[2];

        _mem_free(temp_pin1_map_ptr);
        _mem_free(temp_pin0_map_ptr);
    }

    return gpio_cpu_configure(dev_data_ptr);
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
                * (((uint_32 _PTR_) (&mcf5441_gpio_ptr->PPDSDR_A)) + 0) = dev_data_ptr->pin_map.memory32[0];
                * (((uint_32 _PTR_) (&mcf5441_gpio_ptr->PPDSDR_A)) + 1) = dev_data_ptr->pin_map.memory32[1];
                * (((uint_32 _PTR_) (&mcf5441_gpio_ptr->PPDSDR_A)) + 2) = dev_data_ptr->pin_map.memory32[2];
                _int_enable(); /* _lwsem_post(&gpio_sem); */
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
                * (((uint_32 _PTR_) (&mcf5441_gpio_ptr->PPDSDR_A)) + 0) = temp_pin_map_ptr->memory32[0];
                * (((uint_32 _PTR_) (&mcf5441_gpio_ptr->PPDSDR_A)) + 1) = temp_pin_map_ptr->memory32[1];
                * (((uint_32 _PTR_) (&mcf5441_gpio_ptr->PPDSDR_A)) + 2) = temp_pin_map_ptr->memory32[2];
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
                * (((uint_32 _PTR_) (&mcf5441_gpio_ptr->PCLRR_A)) + 0) = ~dev_data_ptr->pin_map.memory32[0];
                * (((uint_32 _PTR_) (&mcf5441_gpio_ptr->PCLRR_A)) + 1) = ~dev_data_ptr->pin_map.memory32[1];
                * (((uint_32 _PTR_) (&mcf5441_gpio_ptr->PCLRR_A)) + 2) = ~dev_data_ptr->pin_map.memory32[2];
                _int_enable(); /* _lwsem_post(&gpio_sem); */
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
                * (((uint_32 _PTR_) (&mcf5441_gpio_ptr->PCLRR_A)) + 0) = ~temp_pin_map_ptr->memory32[0];
                * (((uint_32 _PTR_) (&mcf5441_gpio_ptr->PCLRR_A)) + 1) = ~temp_pin_map_ptr->memory32[1];
                * (((uint_32 _PTR_) (&mcf5441_gpio_ptr->PCLRR_A)) + 2) = ~temp_pin_map_ptr->memory32[2];
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
                * (((uint_32 _PTR_) (&mcf5441_gpio_ptr->PPDSDR_A)) + 0) = temp_pin1_map_ptr->memory32[0];
                * (((uint_32 _PTR_) (&mcf5441_gpio_ptr->PCLRR_A)) + 0) = ~temp_pin0_map_ptr->memory32[0];
                * (((uint_32 _PTR_) (&mcf5441_gpio_ptr->PPDSDR_A)) + 1) = temp_pin1_map_ptr->memory32[1];
                * (((uint_32 _PTR_) (&mcf5441_gpio_ptr->PCLRR_A)) + 1) = ~temp_pin0_map_ptr->memory32[1];
                * (((uint_32 _PTR_) (&mcf5441_gpio_ptr->PPDSDR_A)) + 2) = temp_pin1_map_ptr->memory32[2];
                * (((uint_32 _PTR_) (&mcf5441_gpio_ptr->PCLRR_A)) + 2) = ~temp_pin0_map_ptr->memory32[2];
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
                            if ( *(((uint_8 _PTR_) &mcf5441_gpio_ptr->PPDSDR_A) + addr) & pin) /* check pin status */
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
            mcf5441_eport_ptr->EPIER |= (dev_data_ptr->irqp_map.reg.portc | dev_data_ptr->irqn_map.reg.portc); /* set interrupt enable */
            break;

        case GPIO_IOCTL_DISABLE_IRQ:
            mcf5441_eport_ptr->EPIER &= ~(dev_data_ptr->irqp_map.reg.portc | dev_data_ptr->irqn_map.reg.portc); /* set interrupt disable */
            break;

        case GPIO_IOCTL_SET_IRQ_FUNCTION: {
            if (dev_data_ptr->type == DEV_OUTPUT)
                return IO_ERROR; /* cannot set IRQ for output devices */

            dev_data_ptr->irq_func = (IRQ_FUNC)param_ptr;
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
    GPIO_DEV_DATA_PTR gptr = first_irq;
    
    while (gptr) { /* list through all irq files */
        if ((gptr->irqp_map.reg.portc | gptr->irqn_map.reg.portc) & mcf5441_eport_ptr->EPFR)
            gptr->irq_func(NULL);
        gptr = gptr->NEXT;
    }
    mcf5441_eport_ptr->EPFR = 0xFF; /* clear flag(s) */
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
    return (pointer)(&((VMCF5441_STRUCT_PTR)_PSP_GET_IPSBAR())->GPIO);
}
/* EOF */
