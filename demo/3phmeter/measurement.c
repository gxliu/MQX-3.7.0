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
* $FileName: measurement.c$
* $Version : 3.5.9.0$
* $Date    : Jan-20-2010$
*
* Comments:
*
*
*END************************************************************************/

#include <mqx.h>
#include <bsp.h>
#include "meter_config.h"
#include "metering_algorithms.h"

void process_calculation(void);
int_16 clear_offset(int_16 *values);

Power_vec       Power[4];
uint_16         Energy[3];

/*FUNCTION****************************************************************
* 
* Function Name    : process_calculation
* Returned Value   : void
* Comments         :
*
*END*********************************************************************/
void process_calculation(void)
{
    /* Calculate and clear offsets from L1, L2, L3 voltage and current buffers */
    clear_offset(vL1_buff);
    clear_offset(iL1_buff);
    clear_offset(vL2_buff);
    clear_offset(iL2_buff);
    clear_offset(vL3_buff);
    clear_offset(iL3_buff);

    /* Calculate power metering algorithms neede to be proceed each period */
    Power_Calc1((int_16 *) vL1_buff, (int_16 *) iL1_buff, &Power[0]);
    Power_Calc1((int_16 *) vL2_buff, (int_16 *) iL2_buff, &Power[1]);
    Power_Calc1((int_16 *) vL3_buff, (int_16 *) iL3_buff, &Power[2]);
    Power3_Calc1(Power);

    /* We can store energy into standby ram, etc., but better not here, in line
    ** period-based task. We can store it in the task running on lower priority task.
    */
}
  

/*FUNCTION****************************************************************
* 
* Function Name    : clear_offset
* Returned Value   : clear offset in sampled data
* Comments         : Clears in set of samples their offset (average value)
*
*END*********************************************************************/
int_16 clear_offset(int_16 *values)
{
    uint_16 i;
    int_32 long_accu = 0;
    int_16 short_accu;
    
    
    for(i = 0; i < SAMPLES_PER_PERIOD; i++)
        long_accu += (uint_16) values[i];

    short_accu = long_accu / SAMPLES_PER_PERIOD;
    
    for(i = 0; i < SAMPLES_PER_PERIOD; i++)
        values[i] -= short_accu;
    
    return short_accu;
}
