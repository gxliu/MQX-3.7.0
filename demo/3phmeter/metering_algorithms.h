/**HEADER********************************************************************
* 
* Copyright (c) 2008-2009 Freescale Semiconductor;
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
* $FileName: metering_algorithms.h$
* $Version : 3.5.7.0$
* $Date    : Jan-20-2010$
*
* Comments:
*
*
*END************************************************************************/

#ifndef __METERING_ALGORITHMS_H__
#define __METERING_ALGORITHMS_H__

#define PWR_SAMPLES     SAMPLES_PER_PERIOD  // number of samples in the buffer
#define RMS_SAMPLES     SAMPLES_PER_PERIOD  // number of samples used for the RMS
#define DFT_SAMPLES     SAMPLES_PER_PERIOD  // number of samples used for the DFT

#define VOLTAGE_CORRECTION_MUL (1)  // means no correction
#define VOLTAGE_CORRECTION_DIV (1)
#define CURRENT_CORRECTION_MUL (1)  // means no correction
#define CURRENT_CORRECTION_DIV (1)

#define MAX_ITERATION   5       // maximum number of iterations for square root calculation
#define ASM_SUM         0       // use summary function written in assembler

/* Power Measures Structure */
typedef struct{
    int_64  Act_Eng;    // Consumed Energy
    int_32  Act_Pwr;    // Active Power
    int_32  React_Pwr;  // Reactive Power
    int_32  Apr_Pwr;    // Apparent Power
    uint_16 Vrms;       // Vrms
    uint_16 Irms;       // Irms
    uint_16  Pwr_fct;   // Power_factor /* 65535 = 100% */
} Power_vec;

//Complex Number
typedef struct {
    int_32 Real;
    int_32 Img;
} Complex;

/* Function prototypes */
uint_16  SquareRoot(uint_32 A);
uint_16 RMS_calc(int_16 *input);
void Power_Calc1(short *V, short *I, Power_vec *Out);
void Power_Calc2(short *V, short *I, Power_vec *Out);
void Power3_Calc1(Power_vec *Pow);
void Power3_Calc2(Power_vec *Pow);
void DFT(int_16 *input, Complex *Res);
uint_16 THD_Calc(int_16 *I, uint_16 Irms);

#endif /*  __METERING_ALGORITHMS_H__ */