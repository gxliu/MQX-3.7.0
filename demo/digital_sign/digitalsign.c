/**HEADER********************************************************************
* 
* Copyright (c) 2008-2010 Freescale Semiconductor;
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
* $FileName: digitalsign.c$
* $Version : 3.7.5.1$
* $Date    : Apr-7-2011$
*
* Comments:
*
*   
*
*END************************************************************************/

#include <mqx.h>
#include <bsp.h>
#include <rtcs.h>
#include <mfs.h>
#include <ftpc.h> 
#include <ftpd.h>
#include <httpd.h>
#include <tfs.h>

#include "digitalsign.h"
#include "cgi.h"



#if ! BSPCFG_ENABLE_IO_SUBSYSTEM
#error This application requires BSPCFG_ENABLE_IO_SUBSYSTEM defined non-zero in user_config.h. Please recompile BSP with this option.
#endif


#ifndef BSP_DEFAULT_IO_CHANNEL_DEFINED
#error This application requires BSP_DEFAULT_IO_CHANNEL to be not NULL. Please set corresponding BSPCFG_ENABLE_TTYx to non-zero in user_config.h and recompile BSP with this option.
#endif


#ifndef MQX_DEVICE
#define MQX_DEVICE BSP_DEFAULT_IO_CHANNEL
#endif

#define MAIN    1
#define DISPLAY 2

#define SCREEN_WIDTH   1024
#define SCREEN_HEIGHT  768
#define SCREEN_REFRESH 60

#define MAX_PICTURES 16
#define THUMB_SIZE   120   // max x/y in pixels

typedef struct {
   char                     Display_Name[PATHNAME_SIZE];
   char                     Image_Name[PATHNAME_SIZE];
   char                     Thumb_Name[PATHNAME_SIZE];
   DISPLAY_PIXEL_BUFFER_PTR pf_pb_ptr;
   DISPLAY_PIXEL_BUFFER_PTR th_pb_ptr;
   DISPLAY_VIEW_STRUCT_PTR  pf_view_ptr;
   DISPLAY_VIEW_STRUCT_PTR  th_view_ptr;
} PICTURE_STRUCT, * PICTURE_STRUCT_PTR;


PICTURE_STRUCT Pictures[MAX_PICTURES] = {0};
uint_32        Num_pictures=0;
MQX_FILE_PTR output_port = NULL;
uchar_ptr display_name,image_name,thumb_name;
uint_32 delay_time = 6;
DISPLAY_CONTEXT_STRUCT_PTR gdc_ptr = NULL;
LWSEM_STRUCT   sem;

MQX_FILE_PTR mfs_ptr=NULL;

#define RAM_DISK_SIZE   0x01000000
static uchar            ram_disk[RAM_DISK_SIZE];
#define RAM_DISK_BASE   &ram_disk[0]


void main_task(uint_32);
void display_task(uint_32);
extern const TFS_DIR_ENTRY tfs_data[];

/*
** MQX initialization information
*/

const TASK_TEMPLATE_STRUCT  MQX_template_list[] = 
{
   /* Task Index,   Function,      Stack,  Priority,   Name,      Attributes,          Param, Time Slice */
    { MAIN,         main_task,     5000,   9,          "Main",    MQX_AUTO_START_TASK, 0,     0 },
    { DISPLAY,      display_task,  5000,   8,          "Display", 0,                   0,     0 },
    { 0 }
};

const HTTPD_ROOT_DIR_STRUCT root_dir[] = {
    { "", "tfs:" },
    { "images", "a:" },
    { 0, 0 }
};
   
   
// ftp root dir
char FTPd_rootdir[] = {"a:\\"}; 

//ftp commands
const FTPd_COMMAND_STRUCT FTPd_commands[] = {
   { "abor", FTPd_unimplemented },
   { "acct", FTPd_unimplemented },
   { "cdup", FTPd_cdup },        
   { "cwd",  FTPd_cd   },        
   { "feat", FTPd_feat },       
   { "help", FTPd_help },       
   { "dele", FTPd_dele },       
   { "list", FTPd_list },       
   { "mkd",  FTPd_mkdir},       
   { "noop", FTPd_noop },
   { "nlst", FTPd_nlst },       
   { "opts", FTPd_opts },
   { "pass", FTPd_pass },
   { "pasv", FTPd_pasv },
   { "port", FTPd_port },
   { "pwd",  FTPd_pwd  },       
   { "quit", FTPd_quit },
   { "rnfr", FTPd_rnfr },
   { "rnto", FTPd_rnto },
   { "retr", FTPd_retr },
   { "stor", FTPd_stor },
   { "rmd",  FTPd_rmdir},       
   { "site", FTPd_site },
   { "size", FTPd_size },
   { "syst", FTPd_syst },
   { "type", FTPd_type },
   { "user", FTPd_user },
   { "xcwd", FTPd_cd    },        
   { "xmkd", FTPd_mkdir },       
   { "xpwd", FTPd_pwd   },       
   { "xrmd", FTPd_rmdir },       
   { NULL,   NULL } 
};



/**-----------------------------------------------------
* 
* Name         : Ram_disk_start
* Comments     :
*    
*
*END*-----------------------------------------------------*/
static uint_32 Ram_disk_start(void)
{
   MQX_FILE_PTR               dev_handle1;

   int_32                     error_code;
   _mqx_uint                  mqx_status;

   /* Install device */
   mqx_status = _io_mem_install("mfs_ramdisk:", (uchar_ptr)RAM_DISK_BASE, (_file_size)RAM_DISK_SIZE);
   if ( mqx_status != MQX_OK ) 
   {
      printf("\nError installing memory device (0x%x)", mqx_status);
      return mqx_status;
   }

   /* Open the device which MFS will be installed on */
   dev_handle1 = fopen("mfs_ramdisk:", 0);
   if ( dev_handle1 == NULL ) 
   {
      printf("\nUnable to open Ramdisk device");
      return IO_ERROR;
   }

   /* Install MFS  */
   mqx_status = _io_mfs_install(dev_handle1, "a:", (_file_size)0);
   if (mqx_status != MFS_NO_ERROR) 
   {
      printf("\nError initializing a:");
      return mqx_status;
   } 
   else 
   {
      printf("\nInitialized Ram Disk to a:\\");
   }

   /* Open the filesystem and detect, if format is required */
   mfs_ptr = fopen("a:", NULL);
   if (mfs_ptr==NULL) {
      return IO_ERROR;
   }
   
   error_code = ferror(mfs_ptr);
   if ((error_code != MFS_NO_ERROR) && (error_code != MFS_NOT_A_DOS_DISK))
   {
      printf("\nError while opening a:\\ (%s)", MFS_Error_text((uint_32)(uint_32)error_code));
      return error_code;
   }
   
   if (error_code == MFS_NOT_A_DOS_DISK) 
   {
      printf("\nNOT A DOS DISK! You must format to continue.");
      printf("\nPerforming Default Formatting...\n");
      error_code = MFS_Default_Format(mfs_ptr);
   }
   
   return error_code;
} 

/**-----------------------------------------------------
* 
* Name         : SyncTime
* Comments     :
*    
*
*END*-----------------------------------------------------*/
boolean SyncTime(void)
{
   boolean res = FALSE;
   TIME_STRUCT time;
   DATE_STRUCT date;

#ifdef SNTP_SERVER
   _ip_address  ipaddr;
   char tries = 0;
   
   printf("\nGetting time from time server...\n");
   
   /* Try three times to get time */
   while(tries++<3) {
      if (RTCS_resolve_ip_address(SNTP_SERVER,&ipaddr,NULL,0)) {
         /* Contact SNTP server and update time */
         res = SNTP_oneshot(ipaddr,1000)==RTCS_OK;
         if (res) {
            break;
         }
      }         
      _time_delay(1000);
   }
#endif
   
   /* Get current time */
   _time_get(&time);
   _time_to_date(&time,&date);
   printf("\nCurrent Time: %02d/%02d/%02d %02d:%02d:%02d\n",
      date.YEAR,date.MONTH,date.DAY,date.HOUR,date.MINUTE,date.SECOND);
   return res;
}


/*TASK*-----------------------------------------------------------------
*
* Function Name  : main_task
* Returned Value : void
* Comments       :
*
*END------------------------------------------------------------------*/

void main_task(uint_32 temp) 
{
   int_32              error;
   _enet_handle        ehandle;
   _rtcs_if_handle     ihandle;
   _enet_address       address;
   HTTPD_STRUCT        *server;
   extern const HTTPD_CGI_LINK_STRUCT cgi_lnk_tbl[];
   HTTPD_PARAMS_STRUCT *params;


   _lwsem_create(&sem,1);

   error = RTCS_create();

   ENET_get_mac_address(BSP_DEFAULT_ENET_DEVICE, ENET_IPADDR, address);
   error = ENET_initialize(BSP_DEFAULT_ENET_DEVICE, address, 0, &ehandle);
   error = RTCS_if_add(ehandle, RTCS_IF_ENET, &ihandle);
   error = RTCS_if_bind(ihandle, ENET_IPADDR, ENET_IPMASK);
   
   #ifdef GATE_IPADDR
      RTCS_gate_add(GATE_IPADDR, INADDR_ANY, INADDR_ANY);
   #endif

   #ifdef DNS_IPADDR
      LWDNS_server_ipaddr=DNS_IPADDR;
   #endif

   error = _io_tfs_install("tfs:", tfs_data);

   Ram_disk_start();

   _task_create (0, DISPLAY, 0);

   SyncTime();
   
   FTPd_init("FTP_server", 7, 3000 );

   /*If root directory is not specified, use root from first valid filesystem */
   if(FTPd_rootdir[0] == '\0')
   {
      _io_get_fs_name(_io_get_first_valid_fs(), FTPd_rootdir, sizeof(FTPd_rootdir));
      FTPd_rootdir[strlen(FTPd_rootdir)] = '\\';
      FTPd_rootdir[strlen(FTPd_rootdir)+1] = '\0';
   }

   printf("\nPreparing http server...\n");

   params = httpd_default_params(NULL);
   if (params) {
      params->root_dir = (HTTPD_ROOT_DIR_STRUCT*)root_dir;
      params->index_page = "\\index.html";

      server = httpd_init(params);
   }

   HTTPD_SET_PARAM_CGI_TBL(server, (HTTPD_CGI_LINK_STRUCT*)cgi_lnk_tbl);

   printf("\nRunning http server...\n");

#if HTTPDCFG_POLL_MODE
   while (1) {
        httpd_server_poll(server, 1);
   }
#else
   httpd_server_run(server);
   _task_block();
#endif
}



/**-----------------------------------------------------
* 
* Name         : add_picture
* Comments     :
*    
*
*END*-----------------------------------------------------*/

void add_picture(char * filename, boolean mfs)
{
   PICTURE_STRUCT_PTR   next_ptr;
   char                 pathname[PATHNAME_SIZE];
   char                 fileroot[PATHNAME_SIZE];
   MFS_FILE_ATTR_PARAM  attr;
   uchar                attribute;
   int_32               error;
   
   if (mfs) {
      strcpy(pathname,"a:/");
   } else {
       strcpy(pathname,"tfs:/");
       // tfs preceeds filename with /, we don't want that
       filename++;
   }
   strcat(pathname,filename);

   if (mfs) {
      // Get the file attributes: 
      attribute = 0;
      attr.PATHNAME = pathname;
      attr.ATTRIBUTE_PTR = &attribute;  
      error = ioctl(mfs_ptr, IO_IOCTL_GET_FILE_ATTR,(uint_32_ptr) &attr);
      if (error || (attribute & MFS_ATTR_READ_ONLY)) {
         return;
      }              
   }
  
   next_ptr = &Pictures[Num_pictures];

   next_ptr->pf_pb_ptr = display_create_pixel_buffer_from_bitmap(pathname);
   if (next_ptr->pf_pb_ptr) {
      if ((next_ptr->pf_pb_ptr->X <= SCREEN_WIDTH) && (next_ptr->pf_pb_ptr->Y <= SCREEN_HEIGHT)) {
          next_ptr->pf_view_ptr = display_create_view(gdc_ptr,next_ptr->pf_pb_ptr);
          if (next_ptr->pf_view_ptr) {
             display_flip_view(next_ptr->pf_view_ptr,FALSE,TRUE);
             display_center_view(next_ptr->pf_view_ptr);
             strcpy(next_ptr->Display_Name, filename );
             if (mfs) {
                strcpy(next_ptr->Image_Name, "images/" );
                strcat(next_ptr->Image_Name, filename );
             } else {
                strcpy(next_ptr->Image_Name, filename );
             }
             Num_pictures++;
                    
             printf("\nAdded %s\n",pathname);

             if (mfs) {
             // mark file as  processed.
                attribute |= MFS_ATTR_READ_ONLY;
                error = ioctl(mfs_ptr, IO_IOCTL_SET_FILE_ATTR,(uint_32_ptr) &attr);
             }
             
             // create thumbnail                        
             next_ptr->th_pb_ptr = display_create_thumbnail(next_ptr->pf_pb_ptr,THUMB_SIZE); 
             if (next_ptr->th_pb_ptr) {
                next_ptr->th_view_ptr = display_create_view(gdc_ptr,next_ptr->th_pb_ptr);
                
                strcpy(fileroot,filename);
                fileroot[strlen(fileroot)-4] = 0;
                
                strcpy(pathname,"a:/");
                strcat(pathname,fileroot);
                strcat(pathname,"_th.BMP");
                display_create_bitmap_from_pixel_buffer(next_ptr->th_pb_ptr, pathname);

                strcpy(next_ptr->Thumb_Name, "images/" );
                strcat(next_ptr->Thumb_Name, fileroot );
                strcat(next_ptr->Thumb_Name,"_th.BMP");
                
                // mark file as  processed.
                attribute = 0;
                attr.PATHNAME = pathname;
                attr.ATTRIBUTE_PTR = &attribute;  
                error = ioctl(mfs_ptr, IO_IOCTL_GET_FILE_ATTR,(uint_32_ptr) &attr);
                attribute |= MFS_ATTR_READ_ONLY;
                error = ioctl(mfs_ptr, IO_IOCTL_SET_FILE_ATTR,(uint_32_ptr) &attr);
             }
          } else {
             display_destroy_pixel_buffer(next_ptr->pf_pb_ptr);
          }
      } else {
         display_destroy_pixel_buffer(next_ptr->pf_pb_ptr);
      }
   }
}



/*TASK*-----------------------------------------------------------------
*
* Function Name  : display_task
* Returned Value : void
* Comments       :
*
*END------------------------------------------------------------------*/
void display_task(uint_32 temp) 
{
   uint_32              result;
   char                 buffer[256];
   uint_32              i;
   TIME_STRUCT          time;
   DATE_STRUCT          date;
   int_32               len;
   char_ptr             path_ptr, mode_ptr;
   pointer              dir_ptr;
   char_ptr             myptr;
 
   
   printf("\nPicture Frame Demo started\n\r");

   sprintf (buffer, "%dx%dx%d", SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_REFRESH);
   gdc_ptr = display_initialize(buffer);
 
   /*Read TFS and prepare images to display*/
   for (i=0;i<MAX_PICTURES && tfs_data[i].NAME; i++ ) {
      if (strcasecmp(&tfs_data[i].NAME[strlen(tfs_data[i].NAME)-4],".bmp")==0) {
         add_picture(tfs_data[i].NAME,FALSE);
      }
   }

   while (1) {
      if (Num_pictures<MAX_PICTURES) {
         /*Read ramdisk for new images*/
         
         path_ptr  ="*.bmp";  //find .bmp files
         mode_ptr = "f*";
                
         dir_ptr = _io_mfs_dir_open(mfs_ptr, path_ptr, mode_ptr );
      
         if (dir_ptr == NULL)  {
            printf("\nDirectory not found.\n");
         } else {
           
            //read file names from the directory until there are none left
            while ((_io_is_fs_valid(mfs_ptr)) && (len = _io_mfs_dir_read(dir_ptr, buffer, sizeof(buffer))) > 0) {
                        
               //trim spaces off the end of the file name (removes \n and \r)
               for (myptr = buffer + strlen(buffer) - 1; (myptr >= buffer) && isspace(*myptr); --myptr); {
                  myptr[1] = '\00';
               }   
                  
               add_picture(buffer,TRUE);
            } 
            _io_mfs_dir_close(dir_ptr);
         }
      }
      
      /*Display pictures */
      for (i=0;i<Num_pictures;i++) {
         _time_get(&time);
         _time_to_date(&time,&date);
         printf("\n %02d:%02d:%02d  Now showing %s\n",date.HOUR,date.MINUTE,date.SECOND ,Pictures[i].Display_Name );
         display_show_view(Pictures[i].pf_view_ptr, DIU_PLANE_1);

         _lwsem_wait(&sem);
         display_name = (uchar_ptr) &Pictures[i].Display_Name[0];
         image_name   = (uchar_ptr) &Pictures[i].Image_Name[0];
         thumb_name   = (uchar_ptr) &Pictures[i].Thumb_Name[0];
         _lwsem_post(&sem);
        
         _time_delay(delay_time*1000);
      }
   }   
}

   
/* EOF */
