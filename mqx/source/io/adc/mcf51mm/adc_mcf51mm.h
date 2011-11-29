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
* $FileName: adc_mcf51mm.h$
* $Version : 3.6.4.0$
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

#define ADC_SOURCE_ADPM1   0x0801
#define ADC_SOURCE_ADPM2   0x0802
#define ADC_SOURCE_ADPM0   0x0800
#define ADC_SOURCE_ADPM3   0x0803
#define ADC_SOURCE_AD0     0x0000
#define ADC_SOURCE_AD1     0x0001
#define ADC_SOURCE_AD2     0x0002
#define ADC_SOURCE_AD3     0x0003
#define ADC_SOURCE_AD4     0x0004
#define ADC_SOURCE_AD5     0x0005
#define ADC_SOURCE_AD6     0x0006
#define ADC_SOURCE_AD7     0x0007
#define ADC_SOURCE_AD8     0x0008
#define ADC_SOURCE_AD9     0x0009
#define ADC_SOURCE_AD10    0x000A
#define ADC_SOURCE_AD11    0x000B
#define ADC_SOURCE_AD12    0x000C
#define ADC_SOURCE_AD13    0x000D
#define ADC_SOURCE_AD14    0x000E
#define ADC_SOURCE_AD15    0x000F
#define ADC_SOURCE_AD16    0x0010
#define ADC_SOURCE_AD17    0x0011
#define ADC_SOURCE_AD18    0x0012
#define ADC_SOURCE_AD19    0x0013
#define ADC_SOURCE_AD20    0x0014
#define ADC_SOURCE_AD21    0x0015
#define ADC_SOURCE_AD22    0x0016
#define ADC_SOURCE_AD23    0x0017
#define ADC_SOURCE_PMTEMP  0x081A
#define ADC_SOURCE_TEMP    0x001A
#define ADC_SOURCE_PMBG    0x081B
#define ADC_SOURCE_BGL     0x001B
#define ADC_SOURCE_PMVREFH 0x081D
#define ADC_SOURCE_VREFH   0x001D
#define ADC_SOURCE_VREFL   0x001E
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
//#define ADC_IOCTL_SET_ERROR_FCN      _IO(IO_TYPE_ADC, ADC_IOCTL_HW_SPECIFIC + 11) //errors are not supported on mcf51mm
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
**  IOCTL ADC16 hardware specific errors
*/
#define ADC_ERROR_PERIOD             (ADC_ERROR_BASE | (ADC_ERROR_HW_SPECIFIC + 0x00)) /* cannot run if basic period was not set */
#define ADC_ERROR_HWTRIGGER          (ADC_ERROR_BASE | (ADC_ERROR_HW_SPECIFIC + 0x01)) /* only HW trigger is supported */

/*
** MCF51MM_adc16_calib_struct
** Structure used to store ADC16 calibration data
*/
typedef struct MCF51MM_adc16_calib_struct
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
} MCF51MM_ADC16_CALIB_STRUCT, _PTR_ MCF51MM_ADC16_CALIB_STRUCT_PTR;                           
typedef volatile struct MCF51MM_adc16_calib_struct _PTR_ VMCF51MM_ADC16_CALIB_STRUCT_PTR;    

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
    ADC_PDB_TRIGGERIN0 = 0,   /* external trigger 0 triggering */
    ADC_PDB_TRIGGERIN1 = 4,   /* external trigger 1 triggering */
    ADC_PDB_TRIGGERIN2 = 8,   /* external trigger 2 triggering */
    ADC_PDB_TRIGGERIN3 = 12,  /* external trigger 3 triggering */
    ADC_PDB_TRIGGERIN4 = 16,  /* external trigger 4 triggering */
    ADC_PDB_TRIGGERIN5 = 20,  /* external trigger 5 triggering */
    ADC_PDB_TRIGGERIN6 = 24,  /* external trigger 6 triggering */
    ADC_PDB_SWTRIG = 28       /* default software trigger by IOCTL command */
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
** when ADC driver is installed.
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
} MCF51MM_ADC_INIT_STRUCT, _PTR_ MCF51MM_ADC_INIT_STRUCT_PTR;

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
