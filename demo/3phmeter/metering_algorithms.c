#include <mqx.h>
#include <bsp.h>
#include "meter_config.h"
#include "metering_algorithms.h"

static const int_16 Cos_coef_k_1[] = {
    32767,
    32757,
    32728,
    32678,
    32609,
    32521,
    32412,
    32285,
    32137,
    31971,
    31785,
    31580,
    31356,
    31113,
    30852,
    30571,
    30273,
    29956,
    29621,
    29268,
    28898,
    28510,
    28105,
    27683,
    27245,
    26790,
    26319,
    25832,
    25329,
    24811,
    24279,
    23731,
    23170,
    22594,
    22005,
    21403,
    20787,
    20159,
    19519,
    18868,
    18204,
    17530,
    16846,
    16151,
    15446,
    14732,
    14010,
    13279,
    12539,
    11793,
    11039,
    10278,
    9512,
    8739,
    7962,
    7179,
    6393,
    5602,
    4808,
    4011,
    3212,
    2410,
    1608,
    804,
    0,
    -804,
    -1608,
    -2410,
    -3212,
    -4011,
    -4808,
    -5602,
    -6393,
    -7179,
    -7962,
    -8739,
    -9512,
    -10278,
    -11039,
    -11793,
    -12539,
    -13279,
    -14010,
    -14732,
    -15446,
    -16151,
    -16846,
    -17530,
    -18204,
    -18868,
    -19519,
    -20159,
    -20787,
    -21403,
    -22005,
    -22594,
    -23170,
    -23731,
    -24279,
    -24811,
    -25329,
    -25832,
    -26319,
    -26790,
    -27245,
    -27683,
    -28105,
    -28510,
    -28898,
    -29268,
    -29621,
    -29956,
    -30273,
    -30571,
    -30852,
    -31113,
    -31356,
    -31580,
    -31785,
    -31971,
    -32137,
    -32285,
    -32412,
    -32521,
    -32609,
    -32678,
    -32728,
    -32757,
    -32767,
    -32757,
    -32728,
    -32678,
    -32609,
    -32521,
    -32412,
    -32285,
    -32137,
    -31971,
    -31785,
    -31580,
    -31356,
    -31113,
    -30852,
    -30571,
    -30273,
    -29956,
    -29621,
    -29268,
    -28898,
    -28510,
    -28105,
    -27683,
    -27245,
    -26790,
    -26319,
    -25832,
    -25329,
    -24811,
    -24279,
    -23731,
    -23170,
    -22594,
    -22005,
    -21403,
    -20787,
    -20159,
    -19519,
    -18868,
    -18204,
    -17530,
    -16846,
    -16151,
    -15446,
    -14732,
    -14010,
    -13279,
    -12539,
    -11793,
    -11039,
    -10278,
    -9512,
    -8739,
    -7962,
    -7179,
    -6393,
    -5602,
    -4808,
    -4011,
    -3212,
    -2410,
    -1608,
    -804,
    0,
    804,
    1608,
    2410,
    3212,
    4011,
    4808,
    5602,
    6393,
    7179,
    7962,
    8739,
    9512,
    10278,
    11039,
    11793,
    12539,
    13279,
    14010,
    14732,
    15446,
    16151,
    16846,
    17530,
    18204,
    18868,
    19519,
    20159,
    20787,
    21403,
    22005,
    22594,
    23170,
    23731,
    24279,
    24811,
    25329,
    25832,
    26319,
    26790,
    27245,
    27683,
    28105,
    28510,
    28898,
    29268,
    29621,
    29956,
    30273,
    30571,
    30852,
    31113,
    31356,
    31580,
    31785,
    31971,
    32137,
    32285,
    32412,
    32521,
    32609,
    32678,
    32728,
    32757
    };
    
static const int_16 Sin_coef_k_1[] = {
    0,
    804,
    1608,
    2410,
    3212,
    4011,
    4808,
    5602,
    6393,
    7179,
    7962,
    8739,
    9512,
    10278,
    11039,
    11793,
    12539,
    13279,
    14010,
    14732,
    15446,
    16151,
    16846,
    17530,
    18204,
    18868,
    19519,
    20159,
    20787,
    21403,
    22005,
    22594,
    23170,
    23731,
    24279,
    24811,
    25329,
    25832,
    26319,
    26790,
    27245,
    27683,
    28105,
    28510,
    28898,
    29268,
    29621,
    29956,
    30273,
    30571,
    30852,
    31113,
    31356,
    31580,
    31785,
    31971,
    32137,
    32285,
    32412,
    32521,
    32609,
    32678,
    32728,
    32757,
    32767,
    32757,
    32728,
    32678,
    32609,
    32521,
    32412,
    32285,
    32137,
    31971,
    31785,
    31580,
    31356,
    31113,
    30852,
    30571,
    30273,
    29956,
    29621,
    29268,
    28898,
    28510,
    28105,
    27683,
    27245,
    26790,
    26319,
    25832,
    25329,
    24811,
    24279,
    23731,
    23170,
    22594,
    22005,
    21403,
    20787,
    20159,
    19519,
    18868,
    18204,
    17530,
    16846,
    16151,
    15446,
    14732,
    14010,
    13279,
    12539,
    11793,
    11039,
    10278,
    9512,
    8739,
    7962,
    7179,
    6393,
    5602,
    4808,
    4011,
    3212,
    2410,
    1608,
    804,
    0,
    -804,
    -1608,
    -2410,
    -3212,
    -4011,
    -4808,
    -5602,
    -6393,
    -7179,
    -7962,
    -8739,
    -9512,
    -10278,
    -11039,
    -11793,
    -12539,
    -13279,
    -14010,
    -14732,
    -15446,
    -16151,
    -16846,
    -17530,
    -18204,
    -18868,
    -19519,
    -20159,
    -20787,
    -21403,
    -22005,
    -22594,
    -23170,
    -23731,
    -24279,
    -24811,
    -25329,
    -25832,
    -26319,
    -26790,
    -27245,
    -27683,
    -28105,
    -28510,
    -28898,
    -29268,
    -29621,
    -29956,
    -30273,
    -30571,
    -30852,
    -31113,
    -31356,
    -31580,
    -31785,
    -31971,
    -32137,
    -32285,
    -32412,
    -32521,
    -32609,
    -32678,
    -32728,
    -32757,
    -32767,
    -32757,
    -32728,
    -32678,
    -32609,
    -32521,
    -32412,
    -32285,
    -32137,
    -31971,
    -31785,
    -31580,
    -31356,
    -31113,
    -30852,
    -30571,
    -30273,
    -29956,
    -29621,
    -29268,
    -28898,
    -28510,
    -28105,
    -27683,
    -27245,
    -26790,
    -26319,
    -25832,
    -25329,
    -24811,
    -24279,
    -23731,
    -23170,
    -22594,
    -22005,
    -21403,
    -20787,
    -20159,
    -19519,
    -18868,
    -18204,
    -17530,
    -16846,
    -16151,
    -15446,
    -14732,
    -14010,
    -13279,
    -12539,
    -11793,
    -11039,
    -10278,
    -9512,
    -8739,
    -7962,
    -7179,
    -6393,
    -5602,
    -4808,
    -4011,
    -3212,
    -2410,
    -1608,
    -804
};
#define COS_SAMPLES (sizeof(Cos_coef_k_1) / sizeof(Cos_coef_k_1[0]))
#define SIN_SAMPLES (sizeof(Sin_coef_k_1) / sizeof(Sin_coef_k_1[0]))

/*FUNCTION****************************************************************
*
* Function Name    : SquareRoot
* Input Parameter  : 32 bit unsigned value
* Returned Value   : 16 bit unsigned value in the size of input
* Comments         : Computes square root of the number
*    A condition for algorithm convergence is proved for any input > 0.
*    Static subroutine SquareRootPower used to make first estimation.
*END*********************************************************************/
__declspec(register_abi)
static asm uint_32 SquareRootPower(uint_32 A)
{
    ff1.l d0                  // get first 'one' index from the left
    neg.l d0
    add.l #32, d0
    lsr.l #1, d0
    rts
}

uint_16 SquareRoot(uint_32 A)
{
    uint_32 Acc_temp, Acc = 0;
    _mqx_int j;
    
    if (A == 0)
        return 0;

    Acc = 1 << SquareRootPower(A); // First estimation of square root

    for(j = 0; j < MAX_ITERATION; j++) {
        Acc_temp = (A / Acc + Acc) / 2; // Estimate new square root as a middle of A and Acc
        if (((Acc - Acc_temp) < 1) && ((Acc_temp - Acc) < 1))
            break;                      // break if a good precision (or zero) was reached
        Acc = Acc_temp;
    }

    return Acc_temp;
}

/*FUNCTION****************************************************************
* 
* Function Name    : RMS_calc
* Input Parameter  : pointer to the set of samples to compute RMS from
* Returned Value   : 16 bit RMS value of the same size as the input is
* Comments         : Computes RMS value from samples
*   Static subroutine ADD64bits used to accumulate 32b numbers into 64b.
*END*********************************************************************/
__declspec(register_abi)
static asm void ADD64bits(int_64 *ACC, int_32 A)
{
     add.l  D0,4(A0)        // Add 32-bit to 64-bit accumulator
     bcc    __ADD64bits     // Check overflow
     addq.l #01,(A0)        // if overflow, increase MS 32-bits of ACC
__ADD64bits:
     rts
}

uint_16 RMS_calc(int_16 *input)
{
    _mqx_int i;       // Internal loops index  
    int_64 Sum = 0;       // Intermediate result for the RMS calculation (64)
     
    for (i = 0; i < RMS_SAMPLES; i++) {
#if ASM_SUM == 1                             // Assembly implementation of 64-bit sum
        ADD64bits(&Sum, (*input) * (*input));  // call Assembly function
#else
        Sum = Sum + (*input) * (*input);   // multiply and accumulate
#endif
        input += (SAMPLES_PER_PERIOD / RMS_SAMPLES);
    }

    Sum = Sum / RMS_SAMPLES;
    return SquareRoot((uint_32) Sum);          // output square root of Sum
}

/*FUNCTION****************************************************************
* 
* Function Name    : Power_Calc1
* Input Parameter  : pointer to the set of voltage samples
*                  : pointer to the set of current samples
*                  : pointer to the power vector to fill the information
* Returned Value   :
* Comments         : Computes active power as well as active energy
*     consumed / produced.
*END*********************************************************************/
void Power_Calc1(int_16 *V, int_16 *I, Power_vec *Out)
{
    int_16 *tempV = V, *tempI = I;
    _mqx_int i;
    int_64 Sum = 0;

    for (i = 0; i < PWR_SAMPLES; i++) {
#if ASM_SUM == 1                             // Assembly implementation of 64-bit sum
        ADD64bits(&Sum, (*tempV) * (*tempI));  // call Assembly function
#else
        Sum = Sum + (*tempV) * (*tempI);
#endif
        tempV += (SAMPLES_PER_PERIOD / PWR_SAMPLES);
        tempI += (SAMPLES_PER_PERIOD / PWR_SAMPLES);
    }
    //Active power
    Out->Act_Pwr = (int_32) ((Sum * VOLTAGE_CORRECTION_MUL * CURRENT_CORRECTION_MUL / PWR_SAMPLES) / (VOLTAGE_CORRECTION_DIV * CURRENT_CORRECTION_DIV));
    //Active Energy in one period
    Out->Act_Eng += Out->Act_Pwr / LINE_FREQUENCY / 65536;
}

/*FUNCTION****************************************************************
* 
* Function Name    : Power_Calc2
* Input Parameter  : pointer to the set of voltage samples
*                  : pointer to the set of current samples
*                  : pointer to the power vector to fill the information
* Returned Value   :
* Comments         : Computes reactive, apparent power and power factor
*END*********************************************************************/
void Power_Calc2(int_16 *V, int_16 *I, Power_vec *Out)
{
    //Voltage RMS
    Out->Vrms = (RMS_calc(V) * VOLTAGE_CORRECTION_MUL) / VOLTAGE_CORRECTION_DIV;
    //Current RMS
    Out->Irms = (RMS_calc(I) * CURRENT_CORRECTION_MUL) / CURRENT_CORRECTION_DIV;
    //Apparent power = Vrms * Irms
    Out->Apr_Pwr = (int_32) ((Out->Vrms) * (Out->Irms));
    //Correction of apparent power
    if (Out->Act_Pwr < 0) { // generator
        if (Out->Apr_Pwr < -Out->Act_Pwr)
            Out->Apr_Pwr = -Out->Act_Pwr;   //Correct if Papp < Pact (-> absurdity, but it can happen when rounding numbers)
        //Power Factor Calculation
        if (Out->Apr_Pwr == -Out->Act_Pwr)
            Out->Pwr_fct = MAX_UINT_16;     //Power Factor equals one if Papp = Pact
        else
            Out->Pwr_fct = (-Out->Act_Pwr) / (Out->Apr_Pwr >> 16);
    }
    else { // load
        if (Out->Apr_Pwr < Out->Act_Pwr)
            Out->Apr_Pwr = Out->Act_Pwr;    //Correct if Papp < Pact (-> absurdity, but it can happen when rounding numbers)
        //Power Factor Calculation
        if (Out->Apr_Pwr == Out->Act_Pwr)
            Out->Pwr_fct = MAX_UINT_16;     //Power Factor equals one if Papp = Pact
        else
            Out->Pwr_fct = (Out->Act_Pwr) / (Out->Apr_Pwr >> 16);
    }

    //Reactive Power (from triangle)
    Out->React_Pwr = SquareRoot(Out->Apr_Pwr * Out->Apr_Pwr - Out->Act_Pwr * Out->Act_Pwr); 
}                

/*FUNCTION****************************************************************
* 
* Function Name    : Power3_Calc1
* Input Parameter  : pointer to the set of computed power
*                  : pointer to the result total power
* Returned Value   :
* Comments         : Computes total active 3-phase power and energy from
*    particulars phase powers. The output scale is the same as input scale.
*    Assuming each power is maximum 30+1 bits wide, the 64 bit Sum64
*    cannot ever overflow.
*END*********************************************************************/
void Power3_Calc1(Power_vec *Pow)
{
    //Active power: accumulate 3 * 30bits
    Pow[3].Act_Pwr = Pow[0].Act_Pwr + Pow[1].Act_Pwr + Pow[2].Act_Pwr;
    
    //Active energy
    Pow[3].Act_Eng += Pow[3].Act_Pwr / LINE_FREQUENCY / 65536;
}

/*FUNCTION****************************************************************
* 
* Function Name    : Power3_Calc2
* Input Parameter  : pointer to the set of computed power
*                  : pointer to the result total power
* Returned Value   :
* Comments         : Computes total reactive, apparent 3-phase power from
*    particulars phase powers. The output scale is the same as input scale.
*    Assuming each power is maximum 30+1 bits wide, the 64 bit Sum64
*    cannot ever overflow.
*END*********************************************************************/
void Power3_Calc2(Power_vec *Pow)
{
    uint_64 Sum64;

    // Apparent power
    Sum64 = (int_64) Pow[0].Apr_Pwr * Pow[0].Apr_Pwr + (int_64) Pow[1].Apr_Pwr * Pow[1].Apr_Pwr + (int_64) Pow[2].Apr_Pwr * Pow[2].Apr_Pwr;
    Pow[3].Apr_Pwr = (uint_32) SquareRoot(Sum64 >> 28) << 14; // Sum64 is 60b wide, sqrt input is 32b wide, sqrt result is 16b wide, overall result is 30 bit wide
    
    // Reactive Power
    Sum64 = (int_64) Pow[0].React_Pwr * Pow[0].React_Pwr + (int_64) Pow[1].React_Pwr * Pow[1].React_Pwr + (int_64) Pow[2].React_Pwr * Pow[2].React_Pwr;
    Pow[3].React_Pwr = (uint_32) SquareRoot(Sum64 >> 28) << 14; // Sum64 is 60b wide, sqrt input is 32b wide, sqrt result is 16b wide, overall result is 30 bit wide
    
    // Power Factor
    Pow[3].Pwr_fct = (Pow[3].Act_Pwr) / (Pow[3].Apr_Pwr >> 16);
}                

/*FUNCTION****************************************************************
* 
* Function Name    : DFT
* Input Parameter  : pointer to the set of samples
* Returned Value   : Complex number: active and reactive component
* Comments         : Discrete Fourier Transformation for fundamental frequency
*   The result complex numbers are amplitude {Re,Im}, 65536-times higher
*   than input vector variable
*END*********************************************************************/
void DFT(int_16 *input, Complex *Res)
{
    int_16 *p1;
    const int_16 *p2;
    int_64 Sum;    
    _mqx_int i;

    if (Res == NULL)
        return;

    /* Going to compute real component: sum(i = 0..k) { input[k] * cos[k] } */
    Sum = 0;
    p1 = input;
    p2 = &Cos_coef_k_1[0];  // cosine wave with amplitude 0x7FFF
    for (i = 0; i < DFT_SAMPLES; i++) {
#if ASM_SUM == 1                             // Assembly implementation of 64-bit sum
        ADD64bits(&Sum, (*p1) * (*p2));  // call Assembly function
#else
        Sum = Sum + (*p1) * (*p2);
#endif
        p1 += (SAMPLES_PER_PERIOD / DFT_SAMPLES);
        p2 += (COS_SAMPLES / DFT_SAMPLES);
    }
    /* Sum is now 15 bit + 15 bit + sign bit + sizeof(DFT_SAMPLES)
    ** We still have to correct current
    ** The amplitude of signal component should be 2 times higher than computed till now.
    ** That makes full 32 bit signed number result
    */
    Sum = (Sum * CURRENT_CORRECTION_MUL / DFT_SAMPLES) / CURRENT_CORRECTION_DIV;
    Res->Real = (int_32) (Sum << 1);

    /* Going to compute img component: sum(i = 0..k) { input[k] * sin[k] } */
    Sum = 0;
    p1 = input;
    p2 = &Sin_coef_k_1[0]; // sine wave with amplitude 0x7FFF
    for (i = 0; i < DFT_SAMPLES; i++) {
#if ASM_SUM == 1                             // Assembly implementation of 64-bit sum
        ADD64bits(&Sum, (*p1) * (*p2));  // call Assembly function
#else
        Sum = Sum + (*p1) * (*p2);
#endif        
        p1 += (SAMPLES_PER_PERIOD / DFT_SAMPLES);
        p2 += (SIN_SAMPLES / DFT_SAMPLES);
    }
    /* Sum is now 15 bit + 15 bit + sign bit + sizeof(DFT_SAMPLES)
    ** The amplitude of signal component should be 2 times higher than computed till now.
    ** That makes full 32 bit signed number result
    */
    Sum = (Sum * CURRENT_CORRECTION_MUL / DFT_SAMPLES) / CURRENT_CORRECTION_DIV;
    Res->Real = (int_32) (Sum << 1);
}

/*FUNCTION****************************************************************
* 
* Function Name    : THD
* Input Parameter  : pointer to the set of current samples
* Returned Value   : THD (0..65535), 32768 = 100%
* Comments         : Computes Total Harmonic Distortion
*   The input is current waveform and Irms. Note that current waveform
*   itself is enough to compute THD, but not to perform additional Irms
*   computation, the function just uses already computed value.
*END*********************************************************************/
uint_16 THD_Calc(int_16 *I, uint_16 Irms)
{
    Complex I1;
    uint_16 I1rms;
    uint_32 THD;

    DFT(I, &I1); // gets the fundamental frequency component
    /* I1's amplitude is: I1a = sqrt(I1.Real * I1.Real + I1.Img * I1.Img)
    ** I1's RMS is: I1rms = I1a / sqrt(2)
    ** THD = Vrms * Irms / (V1rms * I1rms) - 1
    ** supposing that V1rms = Vrms (voltage is harmonic), we get:
    ** THD = Vrms * Irms / (Vrms * I1rms) - 1 = Irms / I1rms - 1
    */
    I1rms = SquareRoot((I1.Real >> 16) * (I1.Real >> 16) + (I1.Img >> 16) * (I1.Img >> 16));
    I1rms = ((uint_32) I1rms * 46341) >> 16; //46341 = 65536 / sqrt(2)
    
    if (I1rms > Irms)
        I1rms = Irms;

    THD = ((Irms << 16) - (I1rms << 16)) / I1rms;

    /* 32768 is 100%, so divide by 2 */
    return (uint_16) (THD >> 1);
}

