#ifndef __audio_h__
#define __audio_h__
/**HEADER********************************************************************
*
* Copyright (c) 2010 ARC International;
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
* $FileName: audio.h$
* $Version : 
* $Date    : 
*
* Comments:
*
*   This file contains audio types and definitions.
*
*END************************************************************************/

#ifdef __USB_OTG__
#include "otgapi.h"
#include "devapi.h"
#else
#include "hostapi.h"
#endif
#include "usb_host_audio.h"
#include "usbprv_host.h"

/***************************************
**
** Application-specific definitions
**
****************************************/

/* Used to initialize USB controller */
#if (defined BSP_M52259DEMO) || (defined BSP_M52259EVB) || (defined BSP_TWRMCF52259)
    #define _audio_timer_mask_int	 		_mcf5225_timer_mask_int 
    #define _audio_timer_unmask_int			_mcf5225_timer_unmask_int
    #define _audio_timer_init_freq			_mcf5225_timer_init_freq
#endif
#if (defined BSP_TWR_K40X256) || (defined BSP_TWR_K60N512)
    #define BSP_LAST_TIMER 					1
    #define _audio_timer_mask_int			_kinetis_timer_mask_int
    #define _audio_timer_unmask_int			_kinetis_timer_unmask_int
    #define _audio_timer_init_freq 			_kinetis_timer_init_freq
#endif

#define MAX_FRAME_SIZE           1024
#define HOST_CONTROLLER_NUMBER      0

#define NUMBER_OF_IT_TYPE 7
#define NUMBER_OF_OT_TYPE 8

#define USB_EVENT_CTRL 				0x01
#define USB_EVENT_RECEIVED_DATA  	0x02
#define USB_EVENT_SEND_DATA  		0x04

#define MAX_ISO_PACKET_SIZE			48

#define IN_DEVICE         			0x00
#define OUT_DEVICE         			0x01
#define UNDEFINE_DEVICE         	0xFF

#define USB_TERMINAL_TYPE			0x01
#define INPUT_TERMINAL_TYPE			0x02
#define OUTPUT_TERMINAL_TYPE		0x03

#define  USB_DEVICE_IDLE                   (0)
#define  USB_DEVICE_ATTACHED               (1)
#define  USB_DEVICE_CONFIGURED             (2)
#define  USB_DEVICE_SET_INTERFACE_STARTED  (3)
#define  USB_DEVICE_INTERFACED             (4)
#define  USB_DEVICE_DETACHED               (5)
#define  USB_DEVICE_OTHER                  (6)

/* Used for testing */

#define TEST_SET_COPY_PROTECT_REQUIRED			1
#define TEST_GET_COPY_PROTECT_REQUIRED			1

#define TEST_SET_CUR_MUTE_REQUIRED				1
#define TEST_GET_CUR_MUTE_REQUIRED				1

#define TEST_SET_CUR_VOLUME_REQUIRED			1
#define TEST_GET_CUR_VOLUME_REQUIRED			1

#define TEST_SET_MIN_VOLUME_REQUIRED			1
#define TEST_GET_MIN_VOLUME_REQUIRED			1

#define TEST_SET_MAX_VOLUME_REQUIRED			1
#define TEST_GET_MAX_VOLUME_REQUIRED			1

#define TEST_SET_RES_VOLUME_REQUIRED			1
#define TEST_GET_RES_VOLUME_REQUIRED			1

#define TEST_SET_CUR_BASS_REQUIRED				1
#define TEST_GET_CUR_BASS_REQUIRED				1

#define TEST_SET_MIN_BASS_REQUIRED				1
#define TEST_GET_MIN_BASS_REQUIRED				1

#define TEST_SET_MAX_BASS_REQUIRED				1
#define TEST_GET_MAX_BASS_REQUIRED				1

#define TEST_SET_RES_BASS_REQUIRED				1
#define TEST_GET_RES_BASS_REQUIRED				1

#define TEST_SET_CUR_MID_REQUIRED				1
#define TEST_GET_CUR_MID_REQUIRED				1

#define TEST_SET_MIN_MID_REQUIRED				1
#define TEST_GET_MIN_MID_REQUIRED				1

#define TEST_SET_MAX_MID_REQUIRED				1
#define TEST_GET_MAX_MID_REQUIRED				1

#define TEST_SET_RES_MID_REQUIRED				1
#define TEST_GET_RES_MID_REQUIRED				1

#define TEST_SET_CUR_TREBLE_REQUIRED			1
#define TEST_GET_CUR_TREBLE_REQUIRED			1

#define TEST_SET_MIN_TREBLE_REQUIRED			1
#define TEST_GET_MIN_TREBLE_REQUIRED			1

#define TEST_SET_MAX_TREBLE_REQUIRED			1
#define TEST_GET_MAX_TREBLE_REQUIRED			1

#define TEST_SET_RES_TREBLE_REQUIRED			1
#define TEST_GET_RES_TREBLE_REQUIRED			1

#define TEST_SET_CUR_GRAPHIC_REQUIRED			1
#define TEST_GET_CUR_GRAPHIC_REQUIRED			1

#define TEST_SET_MIN_GRAPHIC_REQUIRED			1
#define TEST_GET_MIN_GRAPHIC_REQUIRED			1

#define TEST_SET_MAX_GRAPHIC_REQUIRED			1
#define TEST_GET_MAX_GRAPHIC_REQUIRED			1

#define TEST_SET_RES_GRAPHIC_REQUIRED			1
#define TEST_GET_RES_GRAPHIC_REQUIRED			1

#define TEST_SET_CUR_AGC_REQUIRED				1
#define TEST_GET_CUR_AGC_REQUIRED				1

#define TEST_SET_CUR_DELAY_REQUIRED				1
#define TEST_GET_CUR_DELAY_REQUIRED				1

#define TEST_SET_MIN_DELAY_REQUIRED				1
#define TEST_GET_MIN_DELAY_REQUIRED				1

#define TEST_SET_MAX_DELAY_REQUIRED				1
#define TEST_GET_MAX_DELAY_REQUIRED				1

#define TEST_SET_RES_DELAY_REQUIRED				1
#define TEST_GET_RES_DELAY_REQUIRED				1

#define TEST_SET_CUR_BASS_BOOST_REQUIRED		1
#define TEST_GET_CUR_BASS_BOOST_REQUIRED		1

#define TEST_SET_CUR_SAMPLING_REQUIRED			1
#define TEST_GET_CUR_SAMPLING_REQUIRED			1

#define TEST_SET_MIN_SAMPLING_REQUIRED			1
#define TEST_GET_MIN_SAMPLING_REQUIRED			1

#define TEST_SET_MAX_SAMPLING_REQUIRED			1
#define TEST_GET_MAX_SAMPLING_REQUIRED			1

#define TEST_SET_RES_SAMPLING_REQUIRED			1
#define TEST_GET_RES_SAMPLING_REQUIRED			1

#define TEST_SET_CUR_PITCH_REQUIRED				1
#define TEST_GET_CUR_PITCH_REQUIRED				1


#define TEST_SET_MEM_ENDPOINT_REQUIRED			1
#define TEST_GET_MEM_ENDPOINT_REQUIRED			1


/*
** Following structs contain all states and pointers
** used by the application to control/operate devices.
*/


typedef struct audio_device_struct {
   uint_32                          DEV_STATE;  /* Attach/detach state */
   _usb_device_instance_handle      DEV_HANDLE;
   _usb_interface_descriptor_handle INTF_HANDLE;
   CLASS_CALL_STRUCT                CLASS_INTF; /* Class-specific info */
} AUDIO_CONTROL_DEVICE_STRUCT,  _PTR_ AUDIO_CONTROL_DEVICE_STRUCT_PTR;

typedef struct data_device_struct {
   uint_32                          DEV_STATE;  /* Attach/detach state */
   _usb_device_instance_handle      DEV_HANDLE;
   _usb_interface_descriptor_handle INTF_HANDLE;
   CLASS_CALL_STRUCT                CLASS_INTF; /* Class-specific info */
} AUDIO_STREAM_DEVICE_STRUCT,  _PTR_ AUDIO_STREAM_DEVICE_STRUCT_PTR;

/* Alphabetical list of Function Prototypes */

#ifdef __cplusplus
extern "C" {
#endif

void usb_host_audio_control_event(_usb_device_instance_handle,
   _usb_interface_descriptor_handle, uint_32);
void usb_host_audio_stream_event(_usb_device_instance_handle,
   _usb_interface_descriptor_handle, uint_32);
void usb_host_audio_tr_callback(_usb_pipe_handle ,pointer,
	uchar_ptr ,uint_32 ,uint_32 );
void usb_host_audio_mute_ctrl_callback(_usb_pipe_handle,pointer,
	uchar_ptr,uint_32,uint_32);
void usb_host_audio_ctrl_callback(_usb_pipe_handle,pointer,
	uchar_ptr,uint_32,uint_32);
void usb_host_audio_interrupt_callback(_usb_pipe_handle,pointer,
	uchar_ptr,uint_32,uint_32);

static void usb_host_audio_test_inf_requests();
static void usb_host_audio_test_ep_requests();

static void usb_host_audio_test_set_copy_protect_request();
static void usb_host_audio_test_get_copy_protect_request();

static void usb_host_audio_test_set_cur_mute_request();
static void usb_host_audio_test_get_cur_mute_request();

static void usb_host_audio_test_set_cur_volume_request();
static void usb_host_audio_test_get_cur_volume_request();

static void usb_host_audio_test_set_min_volume_request();
static void usb_host_audio_test_get_min_volume_request();

static void usb_host_audio_test_set_max_volume_request();
static void usb_host_audio_test_get_max_volume_request();

static void usb_host_audio_test_set_res_volume_request();
static void usb_host_audio_test_get_res_volume_request();

static void usb_host_audio_test_set_cur_bass_request();
static void usb_host_audio_test_get_cur_bass_request();

static void usb_host_audio_test_set_min_bass_request();
static void usb_host_audio_test_get_min_bass_request();

static void usb_host_audio_test_set_max_bass_request();
static void usb_host_audio_test_get_max_bass_request();

static void usb_host_audio_test_set_res_bass_request();
static void usb_host_audio_test_get_res_bass_request();

static void usb_host_audio_test_set_cur_mid_request();
static void usb_host_audio_test_get_cur_mid_request();

static void usb_host_audio_test_set_min_mid_request();
static void usb_host_audio_test_get_min_mid_request();

static void usb_host_audio_test_set_max_mid_request();
static void usb_host_audio_test_get_max_mid_request();

static void usb_host_audio_test_set_res_mid_request();
static void usb_host_audio_test_get_res_mid_request();

static void usb_host_audio_test_set_cur_treble_request();
static void usb_host_audio_test_get_cur_treble_request();

static void usb_host_audio_test_set_min_treble_request();
static void usb_host_audio_test_get_min_treble_request();

static void usb_host_audio_test_set_max_treble_request();
static void usb_host_audio_test_get_max_treble_request();

static void usb_host_audio_test_set_res_treble_request();
static void usb_host_audio_test_get_res_treble_request();

static void usb_host_audio_test_set_cur_graphic_request();
static void usb_host_audio_test_get_cur_graphic_request();

static void usb_host_audio_test_set_min_graphic_request();
static void usb_host_audio_test_get_min_graphic_request();

static void usb_host_audio_test_set_max_graphic_request();
static void usb_host_audio_test_get_max_graphic_request();

static void usb_host_audio_test_set_res_graphic_request();
static void usb_host_audio_test_get_res_graphic_request();

static void usb_host_audio_test_set_cur_agc_request();
static void usb_host_audio_test_get_cur_agc_request();

static void usb_host_audio_test_set_min_delay_request();
static void usb_host_audio_test_get_min_delay_request();

static void usb_host_audio_test_set_max_delay_request();
static void usb_host_audio_test_get_max_delay_request();

static void usb_host_audio_test_set_res_delay_request();
static void usb_host_audio_test_get_res_delay_request();

static void usb_host_audio_test_set_cur_delay_request();
static void usb_host_audio_test_get_cur_delay_request();

static void usb_host_audio_test_set_cur_bass_boost_request();
static void usb_host_audio_test_get_cur_bass_boost_request();

static void usb_host_audio_test_set_cur_sampling_fr_request();
static void usb_host_audio_test_get_cur_sampling_fr_request();

static void usb_host_audio_test_set_min_sampling_fr_request();
static void usb_host_audio_test_get_min_sampling_fr_request();

static void usb_host_audio_test_set_max_sampling_fr_request();
static void usb_host_audio_test_get_max_sampling_fr_request();

static void usb_host_audio_test_set_res_sampling_fr_request();
static void usb_host_audio_test_get_res_sampling_fr_request();

static void usb_host_audio_test_set_cur_pitch_request();
static void usb_host_audio_test_get_cur_pitch_request();

static void usb_host_audio_test_set_mem_ep_request();
static void usb_host_audio_test_get_mem_ep_request();

#ifdef __cplusplus
}
#endif


#endif

/* EOF */
