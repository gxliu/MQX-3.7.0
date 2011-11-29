#ifndef __adc_mcf51xx_h__
#define __adc_mcf51xx_h__
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
* $FileName: adc_mcf51em.h$
* $Version : 3.6.11.0$
* $Date    : Jun-1-2010$
*
* Comments:
*
*   CPU specific ADC driver header file
*
*END************************************************************************/

/*----------------------------------------------------------------------*/
/*
**                          CONSTANT DEFINITIONS
*/

#ifdef __cplusplus
extern "C" {
#endif

#define ADC_MAX_CLOCK           8000000     // max ADCK

#define ADC_RESOLUTION_16BIT   0x10000
#define ADC_RESOLUTION_12BIT   0x01000
#define ADC_RESOLUTION_10BIT   0x00400
#define ADC_RESOLUTION_8BIT    0x00100

#define ADC_RESOLUTION_DEFAULT ADC_RESOLUTION_16BIT

#define ADC_SOURCE_ADC1_ADPM1    0x0801
#define ADC_SOURCE_ADC2_ADPM2    0x1802
#define ADC_SOURCE_ADC3_ADPM0    0x2800
#define ADC_SOURCE_ADC4_ADPM3    0x3803
#define ADC_SOURCE_ADC3_AD0      0x2000
#define ADC_SOURCE_ADC1_AD1      0x0001
#define ADC_SOURCE_ADC2_AD2      0x1002
#define ADC_SOURCE_ADC4_AD3      0x3003
#define ADC_SOURCE_ADC3_AD4      0x2004
#define ADC_SOURCE_ADC1_AD5      0x0005
#define ADC_SOURCE_ADC2_AD6      0x1006
#define ADC_SOURCE_ADC4_AD7      0x3007
#define ADC_SOURCE_ADC3_AD8      0x2008
#define ADC_SOURCE_ADC3_AD9      0x2009
#define ADC_SOURCE_ADC1_AD10     0x000A
#define ADC_SOURCE_ADC1_AD11     0x000B
#define ADC_SOURCE_ADC1_AD12     0x000C
#define ADC_SOURCE_ADC1_AD13     0x000D
#define ADC_SOURCE_ADC3_AD13     0x200D
#define ADC_SOURCE_ADC2_AD14     0x100E
#define ADC_SOURCE_ADC2_AD15     0x100F
#define ADC_SOURCE_ADC2_AD16     0x1010
#define ADC_SOURCE_ADC2_AD17     0x1011
#define ADC_SOURCE_ADC4_AD17     0x3011
#define ADC_SOURCE_ADC2_AD18     0x1012
#define ADC_SOURCE_ADC4_AD18     0x3012
#define ADC_SOURCE_ADC2_AD19     0x1013
#define ADC_SOURCE_ADC4_AD19     0x3013
#define ADC_SOURCE_ADC1_AD20     0x0014
#define ADC_SOURCE_ADC2_AD20     0x1014
#define ADC_SOURCE_ADC3_AD20     0x2014
#define ADC_SOURCE_ADC4_AD20     0x3014
#define ADC_SOURCE_ADC1_PMTEMP   0x081A
#define ADC_SOURCE_ADC2_PMTEMP   0x181A
#define ADC_SOURCE_ADC3_PMTEMP   0x281A
#define ADC_SOURCE_ADC4_PMTEMP   0x381A
#define ADC_SOURCE_ADC1_TEMP     0x001A
#define ADC_SOURCE_ADC2_TEMP     0x101A
#define ADC_SOURCE_ADC3_TEMP     0x201A
#define ADC_SOURCE_ADC4_TEMP     0x301A
#define ADC_SOURCE_ADC1_PMBG     0x081B
#define ADC_SOURCE_ADC2_PMBG     0x181B
#define ADC_SOURCE_ADC3_PMBG     0x281B
#define ADC_SOURCE_ADC4_PMBG     0x381B
#define ADC_SOURCE_ADC1_BGL      0x001B
#define ADC_SOURCE_ADC2_BGL      0x101B
#define ADC_SOURCE_ADC3_BGL      0x201B
#define ADC_SOURCE_ADC4_BGL      0x301B
#define ADC_SOURCE_ADC1_PMVREFH  0x081D
#define ADC_SOURCE_ADC2_PMVREFH  0x181D
#define ADC_SOURCE_ADC3_PMVREFH  0x281D
#define ADC_SOURCE_ADC4_PMVREFH  0x381D
#define ADC_SOURCE_ADC1_VREFH    0x001D
#define ADC_SOURCE_ADC2_VREFH    0x101D
#define ADC_SOURCE_ADC3_VREFH    0x201D
#define ADC_SOURCE_ADC4_VREFH    0x301D
#define ADC_SOURCE_ADC1_VREFL    0x001E
#define ADC_SOURCE_ADC2_VREFL    0x101E
#define ADC_SOURCE_ADC3_VREFL    0x201E
#define ADC_SOURCE_ADC4_VREFL    0x301E
#define ADC_GET_CHANNEL(x)  ((x) & 0x00FF)
#define ADC_GET_DIFF(x)  ((x) & 0x0800)

#define ADC_PDB_TRIGGER           (0x10000) /* HW specific trigger(s) must be controlled by hardware */

/*
**  IOCTL ADC16 hardware specific commands used in driver
*/
#define ADC_IOCTL_CALIBRATE          _IO(IO_TYPE_ADC, ADC_IOCTL_HW_SPECIFIC + 0)
#define ADC_IOCTL_SET_CALIBRATION    _IO(IO_TYPE_ADC, ADC_IOCTL_HW_SPECIFIC + 1)
#define ADC_IOCTL_GET_CALIBRATION    _IO(IO_TYPE_ADC, ADC_IOCTL_HW_SPECIFIC + 2)
#define ADC_IOCTL_SET_LONG_SAMPLE    _IO(IO_TYPE_ADC, ADC_IOCTL_HW_SPECIFIC + 3)
#define ADC_IOCTL_SET_SHORT_SAMPLE   _IO(IO_TYPE_ADC, ADC_IOCTL_HW_SPECIFIC + 4)
#define ADC_IOCTL_SET_HIGH_SPEED     _IO(IO_TYPE_ADC, ADC_IOCTL_HW_SPECIFIC + 5)
#define ADC_IOCTL_SET_LOW_SPEED      _IO(IO_TYPE_ADC, ADC_IOCTL_HW_SPECIFIC + 6)
#define ADC_IOCTL_SET_HW_AVERAGING   _IO(IO_TYPE_ADC, ADC_IOCTL_HW_SPECIFIC + 7)
#define ADC_IOCTL_SET_IDELAY         _IO(IO_TYPE_ADC, ADC_IOCTL_HW_SPECIFIC + 8)
#define ADC_IOCTL_SET_IDELAYREG      _IO(IO_TYPE_ADC, ADC_IOCTL_HW_SPECIFIC + 9)
#define ADC_IOCTL_SET_IDELAY_FCN     _IO(IO_TYPE_ADC, ADC_IOCTL_HW_SPECIFIC + 10)
#define ADC_IOCTL_SET_ERROR_FCN      _IO(IO_TYPE_ADC, ADC_IOCTL_HW_SPECIFIC + 11)
#define ADC_IOCTL_SET_IDELAY_PROCESS _IO(IO_TYPE_ADC, ADC_IOCTL_HW_SPECIFIC + 12)
#define ADC_IOCTL_SET_INT_PROCESS    _IO(IO_TYPE_ADC, ADC_IOCTL_HW_SPECIFIC + 13)
#define ADC_IOCTL_SET_BASE_PERIOD    _IO(IO_TYPE_ADC, ADC_IOCTL_HW_SPECIFIC + 14)
#define ADC_IOCTL_TRIM_BASE_PERIOD   _IO(IO_TYPE_ADC, ADC_IOCTL_HW_SPECIFIC + 15)
#define ADC_IOCTL_SET_OFFSET         _IO(IO_TYPE_ADC, ADC_IOCTL_HW_SPECIFIC + 16)
#define ADC_IOCTL_SET_PLUS_GAIN      _IO(IO_TYPE_ADC, ADC_IOCTL_HW_SPECIFIC + 17)
#define ADC_IOCTL_SET_MINUS_GAIN     _IO(IO_TYPE_ADC, ADC_IOCTL_HW_SPECIFIC + 18)
#define ADC_IOCTL_SET_THOLD          _IO(IO_TYPE_ADC, ADC_IOCTL_HW_SPECIFIC + 19)
#define ADC_IOCTL_SET_THOLD_FCN      _IO(IO_TYPE_ADC, ADC_IOCTL_HW_SPECIFIC + 20)
#define ADC_IOCTL_SET_DELAYREG       _IO(IO_TYPE_ADC, ADC_IOCTL_HW_SPECIFIC + 21)
#define ADC_IOCTL_SET_TRIGGER        _IO(IO_TYPE_ADC, ADC_IOCTL_HW_SPECIFIC + 22)
#define ADC_IOCTL_SET_REFERENCE      _IO(IO_TYPE_ADC, ADC_IOCTL_HW_SPECIFIC + 23)

/*
**  ADC16 hardware specific errors
*/
#define ADC_ERROR_PERIOD             (ADC_ERROR_BASE | (ADC_ERROR_HW_SPECIFIC + 0x00)) /* cannot run if basic period was not set */
#define ADC_ERROR_HWTRIGGER          (ADC_ERROR_BASE | (ADC_ERROR_HW_SPECIFIC + 0x01)) /* only HW trigger is supported */

/*
** MCF51EM_adc16_calib_struct
** Structure used to store ADC16 calibration data
*/
typedef struct MCF51EM_adc16_calib_struct
{
    uint_16 ADCOFS;     /*** Offset Correction Register                        ***/
    uint_16 ADCPG;      /*** Plus-Side Gain Register                           ***/                     
    uint_16 ADCMG;      /*** Minus-Side Gain Register                          ***/
    uchar   ADCCLPD;    /*** Plus-Side General Calibration Value Register D    ***/
    uchar   ADCCLPS;    /*** Plus-Side General Calibration Value Register S    ***/
    uint_16 ADCCLP4;    /*** Plus-Side General Calibration Value Register 4    ***/
    uint_16 ADCCLP3;    /*** Plus-Side General Calibration Value Register 3    ***/
    uchar   ADCCLP2;    /*** Plus-Side General Calibration Value Register 2    ***/
    uchar   ADCCLP1;    /*** Plus-Side General Calibration Value Register 1    ***/
    uchar   ADCCLP0;    /*** Plus-Side General Calibration Value Register 0    ***/
    uchar   ADCTST;     /*** Test Register                                     ***/
    uchar   ADCCLMD;    /*** Minus-Side General Calibration Value Register D   ***/
    uchar   ADCCLMS;    /*** Minus-Side General Calibration Value Register S   ***/
    uint_16 ADCCLM4;    /*** Minus-Side General Calibration Value Register 4   ***/
    uint_16 ADCCLM3;    /*** Minus-Side General Calibration Value Register 3   ***/
    uchar   ADCCLM2;    /*** Minus-Side General Calibration Value Register 2   ***/
    uchar   ADCCLM1;    /*** Minus-Side General Calibration Value Register 1   ***/
    uchar   ADCCLM0;    /*** Minus-Side General Calibration Value Register 0   ***/
} MCF51EM_ADC16_CALIB_STRUCT, _PTR_ MCF51EM_ADC16_CALIB_STRUCT_PTR;                           
typedef volatile struct MCF51EM_adc16_calib_struct _PTR_ VMCF51EM_ADC16_CALIB_STRUCT_PTR;    

typedef enum {
    ADC_CLK_BUSCLK,     /* selects BUSCLK */
    ADC_CLK_BUSCLK2,    /* selects BUSCLK/2 */
    ADC_CLK_BUSCLK_ANY, /* selects BUSCLK or BUSCLK/2 */
    ADC_CLK_ALTERNATE,
    ADC_CLK_ASYNC
} ADC_CLOCK_SOURCE;

typedef enum {
    ADC_DIV_1 = 0,
    ADC_DIV_2 = 1,
    ADC_DIV_4 = 2,
    ADC_DIV_8 = 3,
    ADC_DIV_ANY = -1 /* selects automatically the fastest one */
} ADC_CLOCK_DIV;

typedef enum {
    ADC_PDB_COMP1OUT = 0, /* Comparator 1 output trigger */
    ADC_PDB_COMP2OUT = 4, /* Comparator 2 output trigger */
    ADC_PDB_EXTRIG = 16,  /* External event trigger */
    ADC_PDB_SWTRIG = 28   /* Software trigger */
} ADC_PDB_TRIGSEL;

typedef enum {
    ADC_REF_VREF, /* internal voltage reference */
    ADC_REF_VALT, /* alternate voltage reference */
    ADC_REF_VBG   /* internal bandgap Vbgh and Vbgl */
} ADC_REFERENCE;

/*
** ADC_INSTALL_STRUCT
**
** This structure defines the initialization parameters to be used
** when ADC driver is  port is installed.
*/
typedef struct adc_install_struct
{
    /* The number of ADC peripheral, use adc_t enum from PSP */
    uint_8 ADC_NUMBER;
   
    /* The number of ADC peripheral, use adc_t enum from PSP */
    ADC_CLOCK_SOURCE CLOCK_SOURCE;

    /* The number of ADC peripheral, use adc_t enum from PSP */
    ADC_CLOCK_DIV CLOCK_DIV;

    /* The calibration data pointer */
    uint_8_ptr CALIBRATION_DATA_PTR;
   
    /* ADC interrupt vector */
    uint_32 ADC_VECTOR;
} MCF51EM_ADC_INIT_STRUCT, _PTR_ MCF51EM_ADC_INIT_STRUCT_PTR;

typedef void (_CODE_PTR_ PDB_INT_FCN)(void);

pointer _bsp_get_adc_base_address(_mqx_uint);
pointer _bsp_get_pdb_base_address();
int_16 _pdb_get_prescaler();
_mqx_int _pdb_set_prescaler(int_16 prescaler);

#ifdef __cplusplus
}
#endif

#endif

/* EOF */
