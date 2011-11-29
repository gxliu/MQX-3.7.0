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
* $FileName: vectors.c$
* $Version : 3.7.13.1$
* $Date    : Mar-29-2011$
*
* Comments:
*
*    This file contains the exception vector table.
*
*END************************************************************************/

#include "mqx_inc.h"
#include "bsp.h" 

extern unsigned long __BOOT_STACK_ADDRESS[];

/* Configuration values for flash controller */
#define CONFIG_1        (vector_entry)0xffffffff
#define CONFIG_2        (vector_entry)0xffffffff
#define CONFIG_3        (vector_entry)0xffffffff
#define CONFIG_4        (vector_entry)0xfffffffe

#define BOOT_START __boot
    
extern void __boot(void);

extern vector_entry __VECTOR_TABLE_ROM_START[]; // defined in linker command file
extern vector_entry __VECTOR_TABLE_RAM_START[]; // defined in linker command file

void kinetis_init(void);
void _svc_handler(void);
void _pend_svc(void);

#ifdef __ICCARM__
    #pragma language=extended
    #pragma segment="CSTACK"

    #pragma location = ".flashx"
    #pragma segment=".flashx"
    const uchar __FLASHX_START_ADDR[1];
#else    
    #pragma  define_section flashx ".flashx" far_abs R
    __declspec(flashx) const uchar __FLASHX_START_ADDR[1];
#endif

typedef union { vector_entry __fun; void * __ptr; } intvec_elem;

#if MQX_ROM_VECTORS
    #define DEFAULT_VECTOR  _int_kernel_isr
#else
    static void __boot_exception(void) {
        while(1);
    }
    
    #define DEFAULT_VECTOR  __boot_exception
    
    #ifdef __ICCARM__
        #pragma language=extended
        #pragma location = ".vectors_ram"
        #pragma segment=".vectors_ram"
        intvec_elem ram_vector[256] @ ".vectors_ram" =
    #else
		#pragma  define_section vectors_ram ".vectors_ram" far_abs RW
        // array for exception vectors in ram + space (6 words) for CW fun (when CW debugger handle exceptions, using(rewrite) VBR+0x408 address
        __declspec(vectors_ram) vector_entry ram_vector[256 + 6] = 
    #endif
    {
        (vector_entry)__BOOT_STACK_ADDRESS,
        BOOT_START,             /* 1 - Reset */
        _int_kernel_isr,        /* 2 - NMI */
        _int_kernel_isr,        /* 3 - HardFault */
        _int_kernel_isr,        /* 4 - MemManage */
        _int_kernel_isr,        /* 5 - BusFault */
        _int_kernel_isr,        /* 6 - UsageFault */
        0, 0, 0, 0,             /* Reserved */
        _svc_handler,           /* 11 - SVCall */
        _int_kernel_isr,        /* 12 - Debug Monitor */
        0,                      /* Reserved */
        _pend_svc,              /* 14 - PendSV */
        _int_kernel_isr         /* 15 - SysTick */
    };
#endif
/* 
** exception vector table - this table is really used
*/ 
#ifdef __ICCARM__
    #pragma language=extended
    #pragma segment="CSTACK"

    #pragma location = ".intvec"
    #pragma segment=".intvec"
    const intvec_elem __vector_table[] @ ".intvec" =
#else    
    #pragma  define_section vectors_rom ".vectors_rom" far_abs R
    __declspec(vectors_rom) vector_entry rom_vector[] = 
#endif
{
    (vector_entry)__BOOT_STACK_ADDRESS,
    BOOT_START,         /* 1 - Reset */
    DEFAULT_VECTOR,     /* 2 - NMI */
    DEFAULT_VECTOR,     /* 3 - HardFault */
    DEFAULT_VECTOR,     /* 4 - MemManage */
    DEFAULT_VECTOR,     /* 5 - BusFault */
    DEFAULT_VECTOR,     /* 6 - UsageFault */
    0, 0, 0, 0,         /* Reserved */
    _svc_handler,       /* 11 - SVCall */
    DEFAULT_VECTOR,     /* 12 - Debug Monitor */
    0,                  /* Reserved */
    _pend_svc,          /* 14 - PendSV */
    DEFAULT_VECTOR,     /* 15 - SysTick */
    /* Below: vectors for interrupts that are defined by cortex as external */
    DEFAULT_VECTOR,    /*!< DMA Channel 0 Transfer Complete */                          
    DEFAULT_VECTOR,    /*!< DMA Channel 1 Transfer Complete */                          
    DEFAULT_VECTOR,    /*!< DMA Channel 2 Transfer Complete */                          
    DEFAULT_VECTOR,    /*!< DMA Channel 3 Transfer Complete */                          
    DEFAULT_VECTOR,    /*!< DMA Channel 4 Transfer Complete */                          
    DEFAULT_VECTOR,    /*!< DMA Channel 5 Transfer Complete */                          
    DEFAULT_VECTOR,    /*!< DMA Channel 6 Transfer Complete */                          
    DEFAULT_VECTOR,    /*!< DMA Channel 7 Transfer Complete */                          
    DEFAULT_VECTOR,    /*!< DMA Channel 8 Transfer Complete */                          
    DEFAULT_VECTOR,    /*!< DMA Channel 9 Transfer Complete */                          
    DEFAULT_VECTOR,    /*!< DMA Channel 10 Transfer Complete */                         
    DEFAULT_VECTOR,    /*!< DMA Channel 11 Transfer Complete */                         
    DEFAULT_VECTOR,    /*!< DMA Channel 12 Transfer Complete */                         
    DEFAULT_VECTOR,    /*!< DMA Channel 13 Transfer Complete */                         
    DEFAULT_VECTOR,    /*!< DMA Channel 14 Transfer Complete */                         
    DEFAULT_VECTOR,    /*!< DMA Channel 15 Transfer Complete */                         
    DEFAULT_VECTOR,    /*!< DMA Error Interrupt */                                      
    DEFAULT_VECTOR,    /*!< Normal Interrupt */                                         
    DEFAULT_VECTOR,    /*!< FTFL Interrupt */                                           
    DEFAULT_VECTOR,    /*!< Read Collision Interrupt */                                 
    DEFAULT_VECTOR,    /*!< Low Voltage Detect, Low Voltage Warning */                  
    DEFAULT_VECTOR,    /*!< Low Leakage Wakeup */                                       
    DEFAULT_VECTOR,    /*!< WDOG Interrupt */                                           
    DEFAULT_VECTOR,    /*!< RNGB Interrupt */                                           
    DEFAULT_VECTOR,    /*!< I2C0 interrupt */                                           
    DEFAULT_VECTOR,    /*!< I2C1 interrupt */                                           
    DEFAULT_VECTOR,    /*!< SPI0 Interrupt */                                           
    DEFAULT_VECTOR,    /*!< SPI1 Interrupt */                                           
    DEFAULT_VECTOR,    /*!< SPI2 Interrupt */                                           
    DEFAULT_VECTOR,    /*!< CAN0 OR'd Message Buffers Interrupt */                      
    DEFAULT_VECTOR,    /*!< CAN0 Bus Off Interrupt */                                   
    DEFAULT_VECTOR,    /*!< CAN0 Error Interrupt */                                     
    DEFAULT_VECTOR,    /*!< CAN0 Tx Warning Interrupt */                                
    DEFAULT_VECTOR,    /*!< CAN0 Rx Warning Interrupt */                                
    DEFAULT_VECTOR,    /*!< CAN0 Wake Up Interrupt */                                   
    DEFAULT_VECTOR,    /*!< CAN0 Individual Matching Elements Update (IMEU) Interrupt */
    DEFAULT_VECTOR,    /*!< CAN0 Lost Receive Interrupt */                              
    DEFAULT_VECTOR,    /*!< CAN1 OR'd Message Buffers Interrupt */                      
    DEFAULT_VECTOR,    /*!< CAN1 Bus Off Interrupt */                                   
    DEFAULT_VECTOR,    /*!< CAN1 Error Interrupt */                                     
    DEFAULT_VECTOR,    /*!< CAN1 Tx Warning Interrupt */                                
    DEFAULT_VECTOR,    /*!< CAN1 Rx Warning Interrupt */                                
    DEFAULT_VECTOR,    /*!< CAN1 Wake Up Interrupt */                                   
    DEFAULT_VECTOR,    /*!< CAN1 Individual Matching Elements Update (IMEU) Interrupt */
    DEFAULT_VECTOR,    /*!< CAN1 Lost Receive Interrupt */                              
    DEFAULT_VECTOR,    /*!< UART0 Receive/Transmit interrupt */                         
    DEFAULT_VECTOR,    /*!< UART0 Error interrupt */                                    
    DEFAULT_VECTOR,    /*!< UART1 Receive/Transmit interrupt */                         
    DEFAULT_VECTOR,    /*!< UART1 Error interrupt */                                    
    DEFAULT_VECTOR,    /*!< UART2 Receive/Transmit interrupt */                         
    DEFAULT_VECTOR,    /*!< UART2 Error interrupt */                                    
    DEFAULT_VECTOR,    /*!< UART3 Receive/Transmit interrupt */                         
    DEFAULT_VECTOR,    /*!< UART3 Error interrupt */                                    
    DEFAULT_VECTOR,    /*!< UART4 Receive/Transmit interrupt */                         
    DEFAULT_VECTOR,    /*!< UART4 Error interrupt */                                    
    DEFAULT_VECTOR,    /*!< UART5 Receive/Transmit interrupt */                         
    DEFAULT_VECTOR,    /*!< UART5 Error interrupt */                                    
    DEFAULT_VECTOR,    /*!< ADC0 interrupt */                                           
    DEFAULT_VECTOR,    /*!< ADC1 interrupt */                                           
    DEFAULT_VECTOR,    /*!< CMP0 interrupt */                                           
    DEFAULT_VECTOR,    /*!< CMP1 interrupt */                                           
    DEFAULT_VECTOR,    /*!< CMP2 interrupt */                                           
    DEFAULT_VECTOR,    /*!< FTM0 fault, overflow and channels interrupt */              
    DEFAULT_VECTOR,    /*!< FTM1 fault, overflow and channels interrupt */              
    DEFAULT_VECTOR,    /*!< FTM2 fault, overflow and channels interrupt */              
    DEFAULT_VECTOR,    /*!< CMT interrupt */                                            
    DEFAULT_VECTOR,    /*!< RTC interrupt */                                            
    DEFAULT_VECTOR,    /*!< Reserved interrupt 83 */                                    
    DEFAULT_VECTOR,    /*!< PIT timer channel 0 interrupt */                            
    DEFAULT_VECTOR,    /*!< PIT timer channel 1 interrupt */                            
    DEFAULT_VECTOR,    /*!< PIT timer channel 2 interrupt */                            
    DEFAULT_VECTOR,    /*!< PIT timer channel 3 interrupt */                            
    DEFAULT_VECTOR,    /*!< PDB0 Interrupt */                                           
    DEFAULT_VECTOR,    /*!< USB0 interrupt */                                           
    DEFAULT_VECTOR,    /*!< USBDCD Interrupt */                                         
    DEFAULT_VECTOR,    /*!< Ethernet MAC IEEE 1588 Timer Interrupt */                   
    DEFAULT_VECTOR,    /*!< Ethernet MAC Transmit Interrupt */                          
    DEFAULT_VECTOR,    /*!< Ethernet MAC Receive Interrupt */                           
    DEFAULT_VECTOR,    /*!< Ethernet MAC Error and miscellaneous Interrupt */            
    DEFAULT_VECTOR,    /*!< I2S0 Interrupt */                                           
    DEFAULT_VECTOR,    /*!< SDHC Interrupt */                                           
    DEFAULT_VECTOR,    /*!< DAC0 interrupt */                                           
    DEFAULT_VECTOR,    /*!< DAC1 interrupt */                                           
    DEFAULT_VECTOR,    /*!< TSI0 Interrupt */                                           
    DEFAULT_VECTOR,    /*!< MCG Interrupt */                                            
    DEFAULT_VECTOR,    /*!< LPTimer interrupt */                                        
    DEFAULT_VECTOR,    /*!< Reserved interrupt 102 */                                   
    DEFAULT_VECTOR,    /*!< Port A interrupt */                                         
    DEFAULT_VECTOR,    /*!< Port B interrupt */                                         
    DEFAULT_VECTOR,    /*!< Port C interrupt */                                         
    DEFAULT_VECTOR,    /*!< Port D interrupt */                                         
    DEFAULT_VECTOR,    /*!< Port E interrupt */                                         
    DEFAULT_VECTOR,    /*!< Reserved interrupt 108 */                                   
    DEFAULT_VECTOR,    /*!< Reserved interrupt 109 */                                   
    DEFAULT_VECTOR,    /*!< Reserved interrupt 110 */                                   
    DEFAULT_VECTOR,    /*!< Reserved interrupt 111 */                                   
    DEFAULT_VECTOR,    /*!< Reserved interrupt 112 */                                   
    DEFAULT_VECTOR,    /*!< Reserved interrupt 113 */                                   
    DEFAULT_VECTOR,    /*!< Reserved interrupt 114 */                                   
    DEFAULT_VECTOR,    /*!< Reserved interrupt 115 */                                   
    DEFAULT_VECTOR,    /*!< Reserved interrupt 116 */                                   
    DEFAULT_VECTOR,    /*!< Reserved interrupt 117 */                                   
    DEFAULT_VECTOR,    /*!< Reserved interrupt 118 */                                   
    DEFAULT_VECTOR,    /*!< Reserved interrupt 119 */                                   
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    DEFAULT_VECTOR,
    CONFIG_1,
    CONFIG_2,
    CONFIG_3,
    CONFIG_4
};


/*FUNCTION*-------------------------------------------------------------------
*
* Function Name    : __low_level_init
* Returned Value   : void
* Comments         :
*   Call function to initialize CPU registers
*
*END*----------------------------------------------------------------------*/
#ifdef __ICCARM__

#pragma language = extended
#pragma location = "ICODE"

int __low_level_init(void)
{
	/* Initialize Kinetis device. */
	kinetis_init();
	return (1);
}

#endif /* __ICCARM__ */
