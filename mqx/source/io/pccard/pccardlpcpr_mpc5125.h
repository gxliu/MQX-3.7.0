#ifndef _pccardlpcpr_mpc5125_h_
#define _pccardlpcpr_mpc5125_h_
/**HEADER********************************************************************
* 
* Copyright (c) 2008 Freescale Semiconductor;
* All Rights Reserved
*
* Copyright (c) 2004-2008 Embedded Access Inc.;
* All Rights Reserved
*
* Copyright (c) 1989-2008 ARC International;
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
* $FileName: pccardlpcpr_mpc5125.h$
* $Version : 3.7.2.0$
* $Date    : Feb-7-2011$
*
* Comments:
*
*   The file contains the structure definitions
*   private to the advanced PC Card 860 driver
*
*END************************************************************************/

/*----------------------------------------------------------------------*/
/*
**                          CONSTANT DEFINITIONS
*/

#define PCCARDLPC_REGISTER_MASK          0x00000000
#define PCCARDLPC_COMMON_MEM_MASK        0x00100000
#define PCCARDLPC_CARD_PRESENT_MASK      0x00200000


/*
** Timing parameters
*/

/* Minimum time to wait from card detect to VCC application (ms) */
#define PCCARDLPC_VCC_ALLOWED_TIME (50 + BSP_ALARM_RESOLUTION)

/* Minimum time to wait from VCC application to when the card is ready (ms) */
#define PCCARDLPC_RESET_ALLOWED_TIME  (300 + BSP_ALARM_RESOLUTION)
#define PCCARDLPC_ACCESS_ALLOWED_TIME (20 + BSP_ALARM_RESOLUTION)

/* Maximum time to wait for powerup (ms) */
#define PCCARDLPC_MAX_POWERUP_TIME 2000

/* Maximum size for a tuple */
#define PCCARDLPC_MAX_TUPLE_SIZE   32

/* 
** State conditions 
*/
#define PCCARDLPC_CARD_REMOVED    0
#define PCCARDLPC_CARD_INSERTED   1
#define PCCARDLPC_VCC_ALLOWED     2
#define PCCARDLPC_VCC_APPLIED     3
#define PCCARDLPC_RESET_APPLIED   4
#define PCCARDLPC_ACCESS_ALLOWED  5


/*----------------------------------------------------------------------*/
/*
**                    DATATYPE DEFINITIONS
*/

/*
** Run time state information for a PC Card slot
*/
typedef struct io_pccardlpc_struct
{
   MPC5125_PCCARDLPC_INIT_STRUCT INIT_DATA;
   boolean                CARD_IN;
   uint_32                STATE;
   volatile uchar _PTR_   PCMCIA_BASE;
   volatile uchar _PTR_   ATTRIB_PTR;
   TIME_STRUCT            START_TIME;
   uchar                  TUPLE_DATA[PCCARDLPC_MAX_TUPLE_SIZE];
} IO_PCCARDLPC_STRUCT, _PTR_ IO_PCCARDLPC_STRUCT_PTR;


#ifdef __cplusplus
extern "C" {
#endif

extern _mqx_int _io_pccardlpc_open(FILE_DEVICE_STRUCT_PTR, char _PTR_, char _PTR_);
extern _mqx_int _io_pccardlpc_close(FILE_DEVICE_STRUCT_PTR);
extern _mqx_int _io_pccardlpc_ioctl(FILE_DEVICE_STRUCT_PTR, _mqx_uint, pointer);

extern boolean   _io_pccardlpc_card_detect();
extern uint_32   _io_pccardlpc_read_tuple(volatile uchar _PTR_, uint_32, uchar_ptr);
extern void      _io_pccardlpc_card_wait_till_ready(IO_PCCARDLPC_STRUCT_PTR);
extern void      _io_pccardlpc_wait(IO_PCCARDLPC_STRUCT_PTR, uint_32);

#ifdef __cplusplus
}
#endif

#endif
/* EOF */
