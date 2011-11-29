/**HEADER********************************************************************
*
* Copyright (c) 2008 Freescale Semiconductor;
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
* $FileName: boot_cmd.c$
* $Version : 3.7.2.1$
* $Date    : Apr-1-2011$
*
* Comments:
*
*   This file contains the RTCS shell.
*
*END************************************************************************/

#include <mqx.h>
#include <fio.h>
#include <rtcs.h>
#include <ftpc.h>
#include <ftpd.h>
#include <shell.h>
#include <sh_rtcs.h>
#include "config.h"
#include "bootstrap.h"
#include <ctype.h>
#include <string.h>
#include <math.h>

extern boolean _autoboot_cmd;
extern uint_32 _image_index;

int_32 Shell_bootloader_store_image(int_32 argc, char_ptr argv[] );
int_32 Shell_bootloader_del_image(int_32 argc, char_ptr argv[] );
int_32 Shell_bootloader_store_image(int_32 argc, char_ptr argv[] );
int_32 Shell_bootloader_list_image(int_32 argc, char_ptr argv[] );
int_32 Shell_bootloader_del_table(int_32 argc, char_ptr argv[] );
int_32 Shell_bootloader_set_default(int_32 argc, char_ptr argv[] );
int_32 Shell_bootloader_tftp_client(int_32 argc, char_ptr argv[] );
int_32 Shell_bootloader_go_image(int_32 argc, char_ptr argv[] );
int_32 Shell_bootloader_reset(int_32 argc, char_ptr argv[] );
int_32 Shell_bootloader_set_timeout(int_32 argc, char_ptr argv[] );

const SHELL_COMMAND_STRUCT Shell_commands[] = {
    { "arpadd",    Shell_arpadd },
    { "arpdel",    Shell_arpdel },
    { "arpdisp",   Shell_arpdisp },
#if RTCSCFG_ENABLE_NAT
    { "dnat",      Shell_dnat },
#endif
#if RTCSCFG_ENABLE_UDP
    { "exec",      Shell_exec },
#endif
    { "exit",      Shell_exit },
    { "gate",      Shell_gate },
    { "gethbn",    Shell_get_host_by_name },
    { "getrt",     Shell_getroute },
    { "help",      Shell_help },
    { "ipconfig",  Shell_ipconfig },
#if RTCSCFG_ENABLE_UDP
    { "load",      Shell_load },
#endif
#if RTCSCFG_ENABLE_NAT
    { "natinit",   Shell_natinit },
    { "natinfo",   Shell_natinfo },
#endif
    { "netstat",   Shell_netstat },
#if RTCSCFG_ENABLE_ICMP
    { "ping",      Shell_ping },
#endif
#if RTCSCFG_ENABLE_UDP
    { "sendto",    Shell_sendto },
#endif
#if RTCSCFG_ENABLE_SNMP
    { "snmpd",     Shell_SNMPd },
#endif
#if RTCSCFG_ENABLE_UDP
    { "tftp",      Shell_TFTP_client },
#endif

    { "walkrt",    Shell_walkroute },
/* Bootloader commands */

#if BSPCFG_ENABLE_NANDFLASH
   { "nande",     Shell_erase },
   { "nandw",     Shell_write_block },
   { "nandr",     Shell_read_block },
   { "imglst",    Shell_bootloader_list_image },
   { "imgstr",    Shell_bootloader_store_image },
   { "imgdel",    Shell_bootloader_del_image },
   { "tbldel",    Shell_bootloader_del_table },
   { "autoboot",  Shell_bootloader_set_default },
   { "imggo",     Shell_bootloader_go_image },
   { "loadbin",   Shell_bootloader_tftp_client},
   { "atbtmo",    Shell_bootloader_set_timeout},
   { "reset",     Shell_bootloader_reset},

#endif
    { "?",         Shell_command_list },
    { NULL,        NULL }
};

/*TASK*-----------------------------------------------------------------
*
* Function Name  : Shell_bootloader_list_image
* Returned Value : void
* Comments       :
*
*END------------------------------------------------------------------*/

int_32  Shell_bootloader_list_image(int_32 argc, char_ptr argv[] )
{ /* Body */
   boolean             print_usage, shorthelp = FALSE;
   int_32              return_code = SHELL_EXIT_SUCCESS;

   print_usage = Shell_check_help_request(argc, argv, &shorthelp );


   if (!print_usage)  {
      
     if (argc != 1) {
         printf("Error, invalid number of parameters\n");
         return_code = SHELL_EXIT_ERROR;
         print_usage=TRUE;
     }
      else { 
         _bootloader_list_image();
      }
   }

   if (print_usage)  {
      if (shorthelp)  {
         printf("%s\n", argv[0]);
      } else  {
         printf("Usage: %s ", argv[0]);
         printf("   <%s> to list image table\n",argv[0]);
      }
   }

} /* Endbody */

/*TASK*-----------------------------------------------------------------
*
* Function Name  : Shell_bootloader_del_image
* Returned Value : void
* Comments       :
*
*END------------------------------------------------------------------*/

int_32  Shell_bootloader_del_image(int_32 argc, char_ptr argv[] )
{ /* Body */
   boolean             print_usage, shorthelp = FALSE;
   int_32              return_code = SHELL_EXIT_SUCCESS;
   uint_32             index, block, result;
   
   print_usage = Shell_check_help_request(argc, argv, &shorthelp );
   
  
   if (!print_usage)  {
   
     if ((argc < 2) || (argc >= 3)) {     
      printf("Error, invalid number of parameters\n");
      return_code = SHELL_EXIT_ERROR;
      print_usage=TRUE;
     }
     else 
     {
      index = _io_atoi(argv[1]);
      _bootloader_del_image(index);
   }
   
   }
 if (print_usage)  {
      if (shorthelp)  {
         printf("%s <index> \n", argv[0]);
      } else  {
         printf("Usage: %s <index> \n", argv[0]);
         printf("  <index> = index of image to delete\n");
         
      }
 }
}

/*TASK*-----------------------------------------------------------------
*
* Function Name  : Shell_bootloader_store_image
* Returned Value : void
* Comments       :
*
*END------------------------------------------------------------------*/

int_32  Shell_bootloader_store_image(int_32 argc, char_ptr argv[] )
{ /* Body */
   boolean             print_usage, shorthelp = FALSE;
   int_32              return_code = SHELL_EXIT_SUCCESS;
   uint_32             addr, size, result;
   uchar               buffer[] = {1,2,3,4,5,6,7,8,9,0};
   
   print_usage = Shell_check_help_request(argc, argv, &shorthelp );
   
   
   if (!print_usage)  {
   
      if (argc!=2) {
     
      printf("Error, invalid number of parameters\n");
      return_code = SHELL_EXIT_ERROR;
      print_usage=TRUE;
        }
      else {
      addr = _io_atoi(argv[1]);
      size = _io_atoi(argv[2]);
      _bootloader_store_image(addr, size, buffer,(uchar_ptr)"default");
       }
   }
 if (print_usage)  {
      if (shorthelp)  {
         printf("%s <add> <size> \n", argv[0]);
      } else  {
         printf("Usage: %s <add> <size>\n", argv[0]);
         printf("  <add> =  addrees begin to store");
         printf("  <size>=  size image to store   ");
         
      }
    }
  
}
/*TASK*-----------------------------------------------------------------
*
* Function Name  : Shell_bootloader_go_image
* Returned Value : void
* Comments       :
*
*END------------------------------------------------------------------*/

int_32  Shell_bootloader_go_image(int_32 argc, char_ptr argv[] )
{ /* Body */
   boolean             print_usage, shorthelp = FALSE;
   int_32              return_code = SHELL_EXIT_SUCCESS;
   
   print_usage = Shell_check_help_request(argc, argv, &shorthelp );
   
  
   if (!print_usage)  {
   
      _autoboot_cmd = AUTOBOOT_DISABLE;
      _image_index = _io_atoi(argv[1]);
      if(_bootloader_check_image(FALSE,_image_index)) {
         printf("\nStarting application at image:%d\n",_image_index);
         _mqx_exit(0);
      }
      else {
         printf("\nError no image found !\n");
      }
      
   }
   
 if (print_usage)  {
      if (shorthelp)  {
         printf("%s [<index>] \n", argv[0]);
      } else  {
         printf("Usage: %s [<index>] \n", argv[0]);
         printf("   <index> = image index in memory table \n");
         
      }
 }
}


/*TASK*-----------------------------------------------------------------
*
* Function Name  : Shell_bootloader_del_table
* Returned Value : 
* Comments       :
*
*END------------------------------------------------------------------*/

int_32  Shell_bootloader_del_table(int_32 argc, char_ptr argv[] )
{ /* Body */
   boolean             print_usage, shorthelp = FALSE;
   int_32              return_code = SHELL_EXIT_SUCCESS;
   char_ptr            read_buffer;
   MQX_FILE_PTR        nandflash_hdl;
   IMAGE_INFO_PTR      image;
   
   print_usage = Shell_check_help_request(argc, argv, &shorthelp );
   
  
   if (!print_usage)  {
   
    if (argc !=1) {
     
      printf("Error, invalid number of parameters\n");
      return_code = SHELL_EXIT_ERROR;
      print_usage=TRUE;
        }
    else
    {
         if(IO_ERROR == _bootloader_del_table())
            printf ("Delete table error\n ");
          else  
             return MQX_OK; 
    }
     
    
   }
   
 if (print_usage)  {
      if (shorthelp)  {
         printf("%s \n", argv[0]);
      } else  {
         printf("Usage: %s ", argv[0]);
         printf("   <%s> Delete table in memory \n",argv[0]);
      }
 }

} 

/*TASK*-----------------------------------------------------------------
*
* Function Name  : Shell_bootloader_reset
* Returned Value : 
* Comments       :
*
*END------------------------------------------------------------------*/

int_32  Shell_bootloader_reset(int_32 argc, char_ptr argv[] )
{ /* Body */
   boolean             print_usage, shorthelp = FALSE;
   int_32              return_code = SHELL_EXIT_SUCCESS;
   char_ptr            read_buffer;
   MQX_FILE_PTR        nandflash_hdl;
   IMAGE_INFO_PTR      image;
   
   print_usage = Shell_check_help_request(argc, argv, &shorthelp );
   
  
   if (!print_usage)  {
   
    if (argc !=1) {
     
      printf("Error, invalid number of parameters\n");
      return_code = SHELL_EXIT_ERROR;
      print_usage=TRUE;
        }
    else
    {
         _autoboot_cmd = AUTOBOOT_RESET;
         _mqx_exit(0);
         return MQX_OK; 
    }
     
    
   }
   
 if (print_usage)  {
      if (shorthelp)  {
         printf("%s \n", argv[0]);
      } else  {
         printf("Usage: %s ", argv[0]);
         printf("   <%s> booloader reset  \n",argv[0]);
      }
 }

} 

/*TASK*-----------------------------------------------------------------
*
* Function Name  : Shell_bootloader_set_timeout
* Returned Value : 
* Comments       :
*
*END------------------------------------------------------------------*/

int_32  Shell_bootloader_set_timeout(int_32 argc, char_ptr argv[] )
{ /* Body */
   boolean             print_usage, shorthelp = FALSE;
   int_32              return_code = SHELL_EXIT_SUCCESS;
    
   int_32              index,timeout;
    
   print_usage = Shell_check_help_request(argc, argv, &shorthelp );
   
  
   if (!print_usage)  {
   
      if (argc != 3) {
         printf("Error, invalid number of parameters\n");
         return_code = SHELL_EXIT_ERROR;
         print_usage=TRUE;
        }
      else
      {
          index = _io_atoi( argv[1]);
          timeout = _io_atoi( argv[2]);
          if (MQX_OK ==_bootloader_set_timeout(index,timeout)){
            printf ("Set image %d autoboot timeout in %d seconds success\n",index,timeout);
          }
          else{
            printf ("Set default error\n ");
          }
           
      }
    }
 if (print_usage)  {
      if (shorthelp)  {
         printf("%s <index> <timeout>\n", argv[0]);
      } else  {
         printf("Usage: %s <index> <timeout> \n", argv[0]);
         printf("   <index>    = Image index to set autoboot timeout\n");
         printf("   <timeout>  = Timeout value in second\n");
      }
    
   }
  } /* Endbody */
  
/*TASK*-----------------------------------------------------------------
*
* Function Name  : Shell_bootloader_set_default
* Returned Value : 
* Comments       :
*
*END------------------------------------------------------------------*/

int_32  Shell_bootloader_set_default(int_32 argc, char_ptr argv[] )
{ /* Body */
   boolean             print_usage, shorthelp = FALSE;
   int_32              return_code = SHELL_EXIT_SUCCESS;
    
   int_8               index;
    
   print_usage = Shell_check_help_request(argc, argv, &shorthelp );
   
  
   if (!print_usage)  {
   
      if (argc != 2) {
         printf("Error, invalid number of parameters\n");
         return_code = SHELL_EXIT_ERROR;
         print_usage=TRUE;
        }
      else
      {
          index = _io_atoi( argv[1]);
          if (MQX_OK ==_bootloader_set_default(index)){
            printf ("Set image %d as default boot image success\n",index);
          }
          else{
            printf ("Set default error\n ");
          }
           
      }
    }
 if (print_usage)  {
      if (shorthelp)  {
         printf("%s [<index>]", argv[0]);
      } else  {
         printf("Usage: %s ", argv[0]);
         printf("   <%s> Image index to boot\n",argv[0]);
      }
    
   }
  } /* Endbody */

#pragma section code_type ".image_data"
__declspec(section ".image_data")  extern uchar_ptr _image_data; 

/*FUNCTION*-------------------------------------------------------------
*
*  Function Name :  ChartoHex
*  Returned Value:  
*  Comments  :  convert a character to hex
*  Usage:  
*
*END*-----------------------------------------------------------------*/
uchar ChartoHex(uchar c) { 
 if (c>='0' && c<='9') return c-'0'; 
 if (c>='A' && c<='F') return c-'A'+10; 
 if (c>='a' && c<='f') return c-'a'+10; 
 return c=0;        /* not Hex digit  */
} 

/*FUNCTION*-------------------------------------------------------------
*
*  Function Name :  StrtoHex
*  Returned Value:  
*  Comments  :  convert a String to Hexa
*  Usage:  
*
*END*-----------------------------------------------------------------*/
uint_32 StrtoHex(char_ptr hex) 
{ 
 uint_32 hexa_value=0;
 uint_8 n=0,i;
 char_ptr buff = NULL ;
 
strcpy(buff,hex);
while(*(hex++) !=0) {
  n++;
 }
for(i=0;i<n;i++){
  hexa_value += ChartoHex(buff[i])*pow(16,n-1-i); 
  }
return hexa_value;
 } 
     
/*FUNCTION*-------------------------------------------------------------
*
*  Function Name :  Shell_TFTP_client
*  Returned Value:  none
*  Comments  :  SHELL utility to TFTP to or from a host
*  Usage:  tftp host get source [destination] [mode] 
*
*END*-----------------------------------------------------------------*/

int_32  Shell_bootloader_tftp_client(int_32 argc, char_ptr argv[] )
{
   _ip_address          hostaddr;
   char                 hostname[MAX_HOSTNAMESIZE];
   char_ptr             file_ptr;
   uint_32              tftp_handle, buffer_size,byte_number=0,bytes=0;
   uchar_ptr            buffer_ptr;
   TFTP_DATA_STRUCT     tftp_data;
   MQX_FILE_PTR         fd;
   int_32               error;
   boolean              print_usage, shorthelp = FALSE;
   int_32               return_code = SHELL_EXIT_SUCCESS;   
   int_32               i=0,address;
   print_usage = Shell_check_help_request(argc, argv, &shorthelp );

   if (!print_usage)  {
   
      if ((argc >= 3) && (argc <= 5))  {
         RTCS_resolve_ip_address( argv[1], &hostaddr, hostname, MAX_HOSTNAMESIZE ); 

         if (!hostaddr)  {
            printf("Unable to resolve host.\n");
            return_code = SHELL_EXIT_ERROR;
         } else  {
            tftp_data.SERVER   = hostaddr;
            tftp_data.FILENAME = argv[2];
            tftp_data.FILEMODE = argv[2];
            if (argc > 3)  {
               file_ptr = argv[3];
               if (argc > 4) {
                  tftp_data.FILEMODE = argv[4];
               } else {
              tftp_data.FILEMODE = argv[2];
               }
            } else {
               file_ptr = argv[2];
            }
              address = StrtoHex(argv[3]);      
             _image_data[0] = 0x00;
               printf("\nDownloading file %s from TFTP server: %s [%ld.%ld.%ld.%ld]\n",
               tftp_data.FILENAME,hostname, IPBYTES(hostaddr));
               tftp_handle = (*FT_TFTP->OPEN)( (pointer) &tftp_data );
               if ( tftp_handle != RTCS_OK )  {
                  printf("\nError opening file %s\n",tftp_data.FILENAME);
                  return_code = SHELL_EXIT_ERROR;
               } else  {
                  while (! (*FT_TFTP->EOFT)())  {
                
                    while(1) {
                      buffer_ptr = (*FT_TFTP->READ)( &buffer_size );
                     if (buffer_ptr != NULL)  {
                       for(i=0;i<(buffer_size);i++)
                       {
                        _image_data[i+byte_number]=buffer_ptr[i];
                        
                       }
                        byte_number += buffer_size;
                        if(byte_number&0x1000)
                        printf("#");
                     
                     } else {
                     
                     switch (buffer_size) {
                         case (RTCSERR_TFTP_ERROR + 1):
                            printf("\nFile %s not found\n", tftp_data.FILENAME);
                            break;
                         case (RTCSERR_TFTP_ERROR + 2):
                            printf("\nAccess violation\n");
                            break;
                         case (RTCSERR_TFTP_ERROR + 3):
                            printf("\nDisk full or allocation exceeded\n");
                            break;
                         case (RTCSERR_TFTP_ERROR + 4):
                            printf("\nIllegal TFTP operation\n");
                            break;
                         case (RTCSERR_TFTP_ERROR + 5):
                            printf("\nUnknown transfer ID\n");
                            break;
                         case (RTCSERR_TFTP_ERROR + 6):
                            printf("\nFile already exists\n");
                            break;
                         case (RTCSERR_TFTP_ERROR + 7):
                            printf("\nNo such user\n");
                            break;
                         default:
                            if(byte_number !=0) 
                               {
                                 printf("\nTransfer 0x%x byte success",byte_number);  
                                 if(MQX_OK == _bootloader_store_image(address, byte_number, _image_data,(uchar_ptr)tftp_data.FILEMODE)) {
                                    printf("\nWrite image to table Success\n");
                                    _bootloader_list_image();
                                 }
                                 else {
                                    printf("\nWrite image to table Fail\n");
                                 }
                                 break; 
                               }
                            else 
                            printf("\nError reading file %s\n", tftp_data.FILENAME);
                         } /* Endswitch */
                     break; 
                     }  
                          
                  }
                    
                  }
                
                error = (*FT_TFTP->CLOSE)();
              
               }
            tftp_handle = (*FT_TFTP->OPEN)( (pointer) &tftp_data );
            if ( tftp_handle != RTCS_OK )  {
               printf("\nError opening file %s\n",tftp_data.FILENAME);
               return_code = SHELL_EXIT_ERROR;
            } 
            error = (*FT_TFTP->CLOSE)();
         }
      } else  {
         printf("Error, %s invoked with incorrect number of arguments\n", argv[0]);
         print_usage = TRUE;
      }
   }
   
   if (print_usage)  {
      if (shorthelp)  {
         printf("%s <host> <source> <add> [<name>]\n", argv[0]);
      } else  {
         printf("Usage: %s <host> <source> <add> [<name>]\n", argv[0]);
         printf("   <host>    = TFTP server address or name\n");
         printf("   <source>  = Source file name\n");
         printf("   <add>     = Start address (Rom address in Linker file) \n");
         printf("   [<name>]  = Name of image will be stored in table \n");
      }
   }
   return return_code;
} /* Endbody */
 
/* EOF */