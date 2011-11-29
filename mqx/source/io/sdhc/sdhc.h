#ifndef __sdhc_h__
#define __sdhc_h__
/**HEADER********************************************************************
* 
* Copyright (c) 2009 Freescale Semiconductor;
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
* $FileName: sdhc.h$
* $Version : 3.7.2.0$
* $Date    : Feb-7-2011$
*
* Comments:
*
*   This file contains the definitions of constants and structures
*   required for the SDHC driver
*
*END************************************************************************/


#ifndef SDHC_BASE
#   define SDHC_BASE (IMMR + 0X0C000000)
#endif

/*--------------------------------------------------------------------------*/
/*
**                    CONSTANT DEFINITIONS
** IOCTL calls specific to SDHC
*/

#define IO_IOCTL_SDHC_INIT                  _IO(IO_TYPE_ESDHC ,0x01)
#define IO_IOCTL_SDHC_SEND_COMMAND          _IO(IO_TYPE_ESDHC ,0x02)
#define IO_IOCTL_SDHC_GET_CARD              _IO(IO_TYPE_ESDHC ,0x03)
#define IO_IOCTL_SDHC_GET_BAUDRATE          _IO(IO_TYPE_ESDHC ,0x04)
#define IO_IOCTL_SDHC_SET_BAUDRATE          _IO(IO_TYPE_ESDHC ,0x05)
#define IO_IOCTL_SDHC_GET_BUS_WIDTH         _IO(IO_TYPE_ESDHC ,0x06)
#define IO_IOCTL_SDHC_SET_BUS_WIDTH         _IO(IO_TYPE_ESDHC ,0x07)
#define IO_IOCTL_SDHC_GET_BLOCK_SIZE        _IO(IO_TYPE_ESDHC ,0x08)
#define IO_IOCTL_SDHC_SET_BLOCK_SIZE        _IO(IO_TYPE_ESDHC ,0x09)

/* SDHC error codes */
#define SDHC_OK                             (0x00)
#define SDHC_ERROR_INIT_FAILED              (ESDHC_ERROR_BASE | 0x01)
#define SDHC_ERROR_COMMAND_FAILED           (ESDHC_ERROR_BASE | 0x02)
#define SDHC_ERROR_COMMAND_TIMEOUT          (ESDHC_ERROR_BASE | 0x03)
#define SDHC_ERROR_DATA_TRANSFER            (ESDHC_ERROR_BASE | 0x04)
#define SDHC_ERROR_INVALID_BUS_WIDTH        (ESDHC_ERROR_BASE | 0x05)



/**************************** Register Offsets ********************************/
#define SDHC_STR_STP_CLK_OFFSET         0x00   /* Clock Control */
#define SDHC_STATUS_OFFSET              0x04   /* Status */
#define SDHC_CLK_RATE_OFFSET            0x08   /* Clock Rate */
#define SDHC_CMD_DAT_CONT_OFFSET        0x0C   /* Command Data Control */
#define SDHC_RES_TO_OFFSET              0x10   /* Response timeout */
#define SDHC_READ_TO_OFFSET             0x14   /* Read timeout */
#define SDHC_BLK_LEN_OFFSET             0x18   /* Block Length */
#define SDHC_NOB_OFFSET                 0x1C   /* Number of Blocks */
#define SDHC_REV_NO_OFFSET              0x20   /* Revision number */
#define SDHC_INT_CNTR_OFFSET            0x24   /* Interrupt Control */
#define SDHC_CMD_OFFSET                 0x28   /* Command number */
#define SDHC_ARG_OFFSET                 0x2C   /* Command argument */
#define SDHC_RES_FIFO_OFFSET            0x34   /* Command Response FIFO Access */
#define SDHC_BUFFER_ACCESS_OFFSET       0x38   /* Data Buffer Access */
#define SDHC_REMAINING_NOB_OFFSET       0x40   /* Remaining Number of Blocks */
#define SDHC_REMAINING_BLK_SIZE_OFFSET  0x44   /* Remaining Block Size */

/*************************** Register Default Values **************************/
#define SDHC_STR_STP_CLK_DEFAULT        0x00000000   /* Clock Control */
#define SDHC_STATUS_DEFAULT             0x30000000   /* Status */
#define SDHC_CLK_RATE_DEFAULT           0x00000008   /* Clock Rate */
#define SDHC_CMD_DAT_CONT_DEFAULT       0x00000000   /* Command Data Control */
#define SDHC_RES_TO_DEFAULT             0x00000040   /* Response timeout */
#define SDHC_READ_TO_DEFAULT            0x0000FFFF   /* Read timeout */
#define SDHC_BLK_LEN_DEFAULT            0x00000000   /* Block Length */
#define SDHC_NOB_DEFAULT                0x00000000   /* Number of Blocks */
#define SDHC_REV_NO_DEFAULT             0x00000400   /* Revision number */
#define SDHC_INT_CNTR_DEFAULT           0x00000000   /* Interrupt Control */
#define SDHC_CMD_DEFAULT                0x00000000   /* Command number */
#define SDHC_ARG_DEFAULT                0x00000000   /* Command argument */
#define SDHC_RES_FIFO_DEFAULT           0x00000000   /* Command Response FIFO Access */
#define SDHC_BUFFER_ACCESS_DEFAULT      0x00000000   /* Data Buffer Access */

/***************** Register Bit Fields and Values *****************************/
#define SDHC_STR_STP_CLK_IPG_CLK_GATING_DISABLE_MASK     (0x1 << 15)
#define SDHC_STR_STP_CLK_IPG_CLK_GATING_DISABLE_SHIFT    15
#define SDHC_STR_STP_CLK_IPG_PERCLK_GATING_DISABLE_MASK  (0x1 << 14)
#define SDHC_STR_STP_CLK_IPG_PERCLK_GATING_DISABLE_SHIFT 14
#define SDHC_STR_STP_CLK_SDHC_RESET_MASK                 (0x1 << 3)
#define SDHC_STR_STP_CLK_SDHC_RESET_SHIFT                3
#define SDHC_STR_STP_CLK_START_CLK_MASK                  (0x1 << 1)
#define SDHC_STR_STP_CLK_START_CLK_SHIFT                 1
#define SDHC_STR_STP_CLK_STOP_CLK_MASK                   (0x1 << 0)
#define SDHC_STR_STP_CLK_STOP_CLK_SHIFT                  0

#define SDHC_STATUS_CARD_INSERTION_MASK                  (0x1 << 31)
#define SDHC_STATUS_CARD_INSERTION_SHIFT                 31
#define SDHC_STATUS_CARD_REMOVAL_MASK                    (0x1 << 30)
#define SDHC_STATUS_CARD_REMOVAL_SHIFT                   30
#define SDHC_STATUS_YBUF_EMPTY_MASK                      (0x1 << 29)
#define SDHC_STATUS_YBUF_EMPTY_SHIFT                     29
#define SDHC_STATUS_XBUF_EMPTY_MASK                      (0x1 << 28)
#define SDHC_STATUS_XBUF_EMPTY_SHIFT                     28
#define SDHC_STATUS_YBUF_FULL_MASK                       (0x1 << 27)
#define SDHC_STATUS_YBUF_FULL_SHIFT                      27
#define SDHC_STATUS_XBUF_FULL_MASK                       (0x1 << 26)
#define SDHC_STATUS_XBUF_FULL_SHIFT                      26
#define SDHC_STATUS_BUF_UND_RUN_MASK                     (0x1 << 25)
#define SDHC_STATUS_BUF_UND_RUN_SHIFT                    25
#define SDHC_STATUS_BUF_OVFL_MASK                        (0x1 << 24)
#define SDHC_STATUS_BUF_OVFL_SHIFT                       24
#define SDHC_STATUS_SDIO_INT_ACTIVE_MASK                 (0x1 << 14)
#define SDHC_STATUS_SDIO_INT_ACTIVE_SHIFT                14
#define SDHC_STATUS_END_CMD_RESP_MASK                    (0x1 << 13)
#define SDHC_STATUS_END_CMD_RESP_SHIFT                   13
#define SDHC_STATUS_WRITE_OP_DONE_MASK                   (0x1 << 12)
#define SDHC_STATUS_WRITE_OP_DONE_SHIFT                  12
#define SDHC_STATUS_READ_OP_DONE_MASK                    (0x1 << 11)
#define SDHC_STATUS_READ_OP_DONE_SHIFT                   11
#define SDHC_STATUS_WR_CRC_ERROR_CODE_MASK               (0x3 << 9)
#define SDHC_STATUS_WR_CRC_ERROR_CODE_SHIFT              9
#define SDHC_STATUS_CARD_BUS_CLK_RUN_MASK                (0x1 << 8)
#define SDHC_STATUS_CARD_BUS_CLK_RUN_SHIFT               8
#define SDHC_STATUS_BUF_READ_READY_MASK                  (0x1 << 7)
#define SDHC_STATUS_BUF_READ_READY_SHIFT                 7
#define SDHC_STATUS_BUF_WRITE_READY_MASK                 (0x1 << 6)
#define SDHC_STATUS_BUF_WRITE_READY_SHIFT                6
#define SDHC_STATUS_RESP_CRC_ERR_MASK                    (0x1 << 5)
#define SDHC_STATUS_RESP_CRC_ERR_SHIFT                   5
#define SDHC_STATUS_READ_CRC_ERR_MASK                    (0x1 << 3)
#define SDHC_STATUS_READ_CRC_ERR_SHIFT                   3
#define SDHC_STATUS_WRITE_CRC_ERR_MASK                   (0x1 << 2)
#define SDHC_STATUS_WRITE_CRC_ERR_SHIFT                  2
#define SDHC_STATUS_TIME_OUT_RESP_MASK                   (0x1 << 1)
#define SDHC_STATUS_TIME_OUT_RESP_SHIFT                  1
#define SDHC_STATUS_TIME_OUT_READ_MASK                   (0x1 << 0)
#define SDHC_STATUS_TIME_OUT_READ_SHIFT                  0
#define SDHC_STATUS_ALL_BITS_ONE                         0xFFFFFFFF

#define SDHC_CLK_RATE_CLK_PRESCALER(x)                   (((x)<<SDHC_CLK_RATE_CLK_PRESCALER_SHIFT )&SDHC_CLK_RATE_CLK_PRESCALER_MASK)
#define SDHC_CLK_RATE_CLK_PRESCALER_MASK                 (0xFFF << 4)
#define SDHC_CLK_RATE_CLK_PRESCALER_SHIFT                4
#define SDHC_CLK_RATE_CLK_DIVIDER(x)                     (((x)<<SDHC_CLK_RATE_CLK_DIVIDER_SHIFT )&SDHC_CLK_RATE_CLK_DIVIDER_MASK)
#define SDHC_CLK_RATE_CLK_DIVIDER_MASK                   (0xF << 0)
#define SDHC_CLK_RATE_CLK_DIVIDER_SHIFT                  0

#define SDHC_CMD_DAT_CONT_CMD_RESUME_MASK                (0x1 << 15)
#define SDHC_CMD_DAT_CONT_CMD_RESUME_SHIFT               15
#define SDHC_CMD_DAT_CONT_CMD_RESP_LONG_OFF_MASK         (0x1 << 12)
#define SDHC_CMD_DAT_CONT_CMD_RESP_LONG_OFF_SHIFT        12
#define SDHC_CMD_DAT_CONT_STOP_READWAIT_MASK             (0x1 << 11)
#define SDHC_CMD_DAT_CONT_STOP_READWAIT_SHIFT            11
#define SDHC_CMD_DAT_CONT_START_READWAIT_MASK            (0x1 << 10)
#define SDHC_CMD_DAT_CONT_START_READWAIT_SHIFT           10
/* SDHC bus widths */
#define SDHC_CMD_DAT_CONT_BUS_WIDTH_MASK                 (0x3 << 8)
#define SDHC_CMD_DAT_CONT_BUS_WIDTH_SHIFT                8
#define SDHC_BUS_WIDTH_1                                 0          // 1-bit data bus width
#define SDHC_BUS_WIDTH_4                                 (0x2 << 8) // 4-bit data bus width
#define SDHC_CMD_DAT_CONT_BUS_WIDTH(x)                   (((x)<<SDHC_CMD_DAT_CONT_BUS_WIDTH_SHIFT)&SDHC_CMD_DAT_CONT_BUS_WIDTH_MASK)
#define SDHC_CMD_DAT_CONT_INIT_MASK                      (0x1 << 7) // provide additional 80 clock cycles before every command
#define SDHC_CMD_DAT_CONT_INIT_SHIFT                     7
#define SDHC_CMD_INIT_ENABLE                             (0x1 << 7) // 80 clock cycle prefix before command
#define SDHC_CMD_INIT_DISABLE                            0          // no additional clock cycles before command
#define SDHC_CMD_DAT_CONT_WRITE_READ_MASK                (0x1 << 4)
#define SDHC_CMD_DAT_CONT_WRITE_READ_SHIFT               4
#define SDHC_CMD_DATA_READ                               0          // direction of data transfer: read
#define SDHC_CMD_DATA_WRITE                              (0x1 << 4) // direction of data transfer: write
#define SDHC_CMD_DAT_CONT_DATA_ENABLE_MASK               (0x1 << 3)
#define SDHC_CMD_DAT_CONT_DATA_ENABLE_SHIFT              3
#define SDHC_CMD_DATA_ENABLE                             (0x1 << 3) // command includes a data transfer
#define SDHC_CMD_DATA_DISABLE                            0          // command doesn't include a data transfer
#define SDHC_CMD_DAT_CONT_FORMAT_OF_RESPONSE_MASK        (0x7 << 0)
#define SDHC_CMD_DAT_CONT_FORMAT_OF_RESPONSE_SHIFT       0

#define SDHC_FMT_RESP_NO                                 0x0  // no respone for command
#define SDHC_FMT_RESP_48BIT_CRC                          0x1  // 48-bit response with CRC
#define SDHC_FMT_RESP_R1                                 0x1  // R1 response
#define SDHC_FMT_RESP_R5                                 0x1  // R5 response
#define SDHC_FMT_RESP_R6                                 0x1  // R6 response
#define SDHC_FMT_RESP_136BIT                             0x2  // 136bit, CSC/CID response
#define SDHC_FMT_RESP_R2                                 0x2  // R2 response
#define SDHC_FMT_RESP_48BIT                              0x3  // 48-bit response w/o CRC
#define SDHC_FMT_RESP_R3                                 0x3  // R3 response
#define SDHC_FMT_RESP_R4                                 0x3  // R4 response

#define SDHC_RES_TO_RESPONSE_TIME_OUT_MASK               (0xFF << 0)
#define SDHC_RES_TO_RESPONSE_TIME_OUT_SHIFT              0

#define SDHC_READ_TO_DATA_READ_TIME_OUT_MASK             (0xFFFF << 0)
#define SDHC_READ_TO_DATA_READ_TIME_OUT_SHIFT            0

#define SDHC_BLK_LEN_BLOCK_LENGTH_MASK                   (0xFFF << 0)
#define SDHC_BLK_LEN_BLOCK_LENGTH_SHIFT                  0
#define SDHC_BLK_LEN_BLOCK_LENGTH(x)                     (((x)<<SDHC_BLK_LEN_BLOCK_LENGTH_SHIFT)&SDHC_BLK_LEN_BLOCK_LENGTH_MASK)

#define SDHC_NOB_NOB_MASK                                (0xFFFF << 0)
#define SDHC_NOB_NOB_SHIFT                               0

#define SDHC_REV_NO_REVISION_NUMBER_MASK                 (0xFFFF << 0)
#define SDHC_REV_NO_REVISION_NUMBER_SHIFT                0

#define SDHC_INT_CNTR_SDIO_IRQ_WKP_EN_MASK               (0x1 << 18)
#define SDHC_INT_CNTR_SDIO_IRQ_WKP_EN_SHIFT              18
#define SDHC_INT_CNTR_CARD_INSERTION_WKP_EN_MASK         (0x1 << 17)
#define SDHC_INT_CNTR_CARD_INSERTION_WKP_EN_SHIFT        17
#define SDHC_INT_CNTR_CARD_REMOVAL_WKP_EN_MASK           (0x1 << 16)
#define SDHC_INT_CNTR_CARD_REMOVAL_WKP_EN_SHIFT          16
#define SDHC_INT_CNTR_SCARD_INSERTION_EN_MASK            (0x1 << 15)
#define SDHC_INT_CNTR_SCARD_INSERTION_EN_SHIFT           15
#define SDHC_INT_CNTR_CARD_REMOVAL_EN_MASK               (0x1 << 14)
#define SDHC_INT_CNTR_CARD_REMOVAL_EN_SHIFT              14
#define SDHC_INT_CNTR_SDIO_IRO_EN_MASK                   (0x1 << 13)
#define SDHC_INT_CNTR_SDIO_IRO_EN_SHIFT                  13
#define SDHC_INT_CNTR_DATA_EN_MASK                       (0x1 << 12)
#define SDHC_INT_CNTR_DATA_EN_SHIFT                      12
#define SDHC_INT_CNTR_BUF_READ_EN_MASK                   (0x1 << 4)
#define SDHC_INT_CNTR_BUF_READ_EN_SHIFT                  4
#define SDHC_INT_CNTR_BUF_WRITE_EN_MASK                  (0x1 << 3)
#define SDHC_INT_CNTR_BUF_WRITE_EN_SHIFT                 3
#define SDHC_INT_CNTR_END_CMD_RES_MASK                   (0x1 << 2)
#define SDHC_INT_CNTR_END_CMD_RES_SHIFT                  2
#define SDHC_INT_CNTR_WRITE_OP_DONE_MASK                 (0x1 << 1)
#define SDHC_INT_CNTR_WRITE_OP_DONE_SHIFT                1
#define SDHC_INT_CNTR_READ_OP_DONE_MASK                  (0x1 << 0)
#define SDHC_INT_CNTR_READ_OP_DONE_SHIFT                 0
#define SDHC_INT_CNTR_NO_INTERRUPT                       0

#define SDHC_CMD_COMMAND_NUMBER_MASK                     (0x3F << 0)
#define SDHC_CMD_COMMAND_NUMBER_SHIFT                    0

#define SDHC_ARG_ARG_B0_MASK                             (0xFF << 24)
#define SDHC_ARG_ARG_B0_SHIFT                            24
#define SDHC_ARG_ARG_B1_MASK                             (0xFF << 16)
#define SDHC_ARG_ARG_B1_SHIFT                            16
#define SDHC_ARG_ARG_B2_MASK                             (0xFF << 8)
#define SDHC_ARG_ARG_B2_SHIFT                            8
#define SDHC_ARG_ARG_B3_MASK                             (0xFF << 0)
#define SDHC_ARG_ARG_B3_SHIFT                            0

#define SDHC_RES_FIFO_RESPONSE_CONTENT_MASK              (0xFFFF << 0)
#define SDHC_RES_FIFO_RESPONSE_CONTENT_SHIFT             0

#define SDHC_REMAINING_NOB_REMAINING_NOB_MASK            (0xFFFF << 0)
#define SDHC_REMAINING_NOB_REMAINING_NOB_SHIFT           0

#define SDHC_REMAINING_BLK_SIZE_REMAINING_BLK_SIZE_MASK  (0xFFF << 0)
#define SDHC_REMAINING_BLK_SIZE_REMAINING_BLK_SIZE_SHIFT 0

/* SDHC command */
#define GO_IDLE_STATE                                    0 
#define SEND_OP_COND                                     1
#define ALL_SEND_CID                                     2
#define SEND_RELATIVE_ADDR                               3
#define SET_RELATIVE_ADDR                                3
#define SET_DSR                                          4
#define IO_SEND_OP_COND                                  5
#define CMD6                                             6
#define SEL_DESEL_CARD                                   7
#define CMD8                                             8
#define SEND_CSD                                         9
#define SEND_CID                                         10
#define READ_DAT_UNTIL_STOP                              11
#define STOP_TRANSMISSION                                12
#define SEND_STATUS                                      13
#define CMD14                                            14
#define GO_INACTIVE_STATE                                15
#define SET_BLOCKLEN                                     16
#define READ_SINGLE_BLOCK                                17
#define READ_MULTIPLE_BLOCK                              18
#define CMD19                                            19
#define WRITE_DAT_UNTIL_STOP                             20
#define CMD21                                            21
#define CMD22                                            22
#define SET_BLOCK_COUNT                                  23
#define WRITE_BLOCK                                      24
#define WRITE_MULTIPLE_BLOCK                             25
#define PROGRAM_CID                                      26
#define PROGRAM_CSD                                      27
#define SET_WRITE_PROT                                   28
#define CLR_WRITE_PROT                                   29
#define SEND_WRITE_PROT                                  30
#define CMD31                                            31
#define ERASE_WR_BLK_START                               32
#define ERASE_WR_BLK_END                                 33
#define CMD34                                            34
#define ERASE_GROUP_START                                35
#define ERASE_GROUP_END                                  36
#define CMD37                                            37
#define ERASE                                            38
#define FAST_IO                                          39
#define GO_IRQ_STATE                                     40
#define SD_APP_OP_COND                                   41
#define LOCK_UNLOCK                                      42
#define CMD43                                            43
#define CMD44                                            44
#define CMD45                                            45
#define CMD46                                            46
#define CMD47                                            47
#define CMD48                                            48
#define CMD49                                            49
#define CMD50                                            50
#define CMD51                                            51
#define SEND_SCR                                         51
#define IO_RW_DIRECT                                     52
#define IO_RW_EXTENDED                                   53
#define CMD54                                            54
#define APP_CMD                                          55
#define GEN_CMD                                          56
#define CMD57                                            57
#define CMD58                                            58
#define CMD59                                            59
#define CMD60                                            60

#define DEFAULT_RESPONSE                                 0x01230123
#define INTR_MODE                                        0

#define BIT_4_MODE                                       4
#define BIT_1_MODE                                       1
#define CHANNELS_PER_BIT                                 4 
#define SDHC_BIT_MODE                                    BIT_4_MODE

#define CARD_READY_STATUS_BIT                            0x00000100
#define XY_BUFFER_SIZE                                   16
#define SDHC_REG_SIZE                                    4
#define STUFF_BITS                                       0X01290129

#define Data_Slew_Rate_STD_4                             DS_MSR_4

#define CLOCK_CYCLE_PREFIX                               0
/*--------------------------------------------------------------------------*/
/*
**                    DATATYPE DECLARATIONS
*/

/* SDHC card types */

#define     SDHC_NONE      (0x0)
#define     SDHC_UNKNOWN   (0x01)
#define     SDHC_MMC       (0x02)
#define     SDHC_SD        (0x03)
#define     SDHC_SDIO      (0x04)
#define     SDHC_COMBO     (0x05)

typedef struct sdhc_command_struct
{
    int     COMMAND;
    uint_32 ARGUMENT;
    uint_32 CONFIGURATION;
    boolean READ;
    uint_32 BLOCKS;
    uint_32 RESPONSE;
} SDHC_COMMAND_STRUCT, _PTR_ SDHC_COMMAND_STRUCT_PTR;


/*
** sdhc_INIT_STRUCT
**
** This structure defines the initialization parameters to be used
** when a SDHC driver is initialized.
*/
typedef struct mpc5125_sdhc_init_struct
{
    /* The device number */
    uint_32 CHANNEL;

    /* The communication baud rate */
    uint_32 BAUD_RATE;

    /* The module input clock */
    uint_32 CLOCK_SPEED;
   
} MPC5125_SDHC_INIT_STRUCT, _PTR_ MPC5125_SDHC_INIT_STRUCT_PTR;

typedef const MPC5125_SDHC_INIT_STRUCT _PTR_ MPC5125_SDHC_INIT_STRUCT_CPTR;

/*
** sdhc_INFO_STRUCT
** sdhc run time state information
*/
typedef struct mpc5125_sdhc_info_struct
{
   /* The actual card status */
   uint_32                        CARD;

   /* The intermediate buffer */
   uint_32                        BUFFER[128];
   
} MPC5125_SDHC_INFO_STRUCT, _PTR_ MPC5125_SDHC_INFO_STRUCT_PTR;
typedef const MPC5125_SDHC_INFO_STRUCT _PTR_ MPC5125_SDHC_INFO_STRUCT_CPTR;

/*
** sdhc_DEVICE_STRUCT
** sdhc install parameters
*/
typedef struct mpc5125_sdhc_device_struct
{
   /* The current init values for this device */
   MPC5125_SDHC_INIT_STRUCT_CPTR INIT;
   
   /* The number of opened file descriptors */
   uint_32                        COUNT;

} MPC5125_SDHC_DEVICE_STRUCT, _PTR_ MPC5125_SDHC_DEVICE_STRUCT_PTR;
typedef const MPC5125_SDHC_DEVICE_STRUCT _PTR_ MPC5125_SDHC_DEVICE_STRUCT_CPTR;
 
/*--------------------------------------------------------------------------*/
/* 
**                        FUNCTION PROTOTYPES
*/

#ifdef __cplusplus
extern "C" {
#endif


extern pointer _bsp_get_sdhc_base_address(uint_8);
extern uint_32 _bsp_get_sdhc_vector(uint_8);
extern _mqx_int _sdhc_install(char_ptr,MPC5125_SDHC_INIT_STRUCT_CPTR);
extern boolean _sdhc_card_detect();
extern void _sdhc_install_isr();

#ifdef __cplusplus
}
#endif


#endif 

/* EOF */
