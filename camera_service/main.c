    
#define  BUFF_SIZE_IMAGE_INFO 1048576  //  1024 * 1024

void* device_handle_handle=NULL;


int get_live_veiw_to_file(void* device_handle_handle, char* filename) {

    static unsigned char image_buff[BUFF_SIZE_IMAGE_INFO];

    void* image_info_handle = sdk_construct_image_info();
    long int info_result = sdk_get_live_view_image_info(device_handle_handle, image_info_handle);
    if(info_result) {
        fprintf(stderr, "GetLiveView FAILED 1      err:%ld\n", info_result);
        return -1;
    }

    CrInt32u buffer_size = sdk_get_buffer_size_image_info(image_info_handle);
    if(buffer_size < 1) {
        fprintf(stderr, "GetLiveView FAILED 2      size:%d\n", buffer_size);
        return -2;
    }


    void* image_data_block_handle = sdk_construct_image_data_block();
    if(!image_data_block_handle) {
        fprintf(stderr, "GetLiveView FAILED 3      allocation failed\n");
        return NULL;
    }


    fprintf(stderr, "BUFF_SIZE_IMAGE_INFO = 1048576 <> %d = buffer_size\n", buffer_size);
    if(buffer_size > BUFF_SIZE_IMAGE_INFO) {
        perror("not enougth buffer for image\n");
    }


    memset(image_buff, 0, BUFF_SIZE_IMAGE_INFO);
    sdk_set_size_image_data_block(image_data_block_handle, buffer_size);
    sdk_set_data_image_data_block(image_data_block_handle, image_buff);

    
    long int live_view_result = sdk_get_live_view_image(device_handle_handle, image_data_block_handle);
    if(live_view_result) {
        if(live_view_result == 131095) {
            fprintf(stderr, "GetLiveView FAILED 4      Warning. GetLiveView Frame NotUpdate\n");
        }
        else if(live_view_result == 33539) {
            fprintf(stderr, "GetLiveView FAILED 4      Warning. GetLiveView Memory insufficient\n");
        }
        else {
            fprintf(stderr, "GetLiveView FAILED 4      allocation failed\n");
        }

        sdk_destruct_image_data_block(image_data_block_handle);
        return NULL;
    }


    if(sdk_get_size_image_data_block(image_data_block_handle) == 0) {
        fprintf(stderr, "GetLiveView FAILED 5      image size: 0\n");
        sdk_destruct_image_data_block(image_data_block_handle);
        return NULL;
    }



    size_t path_max_size = 256;
    struct timeval tv;
    struct tm tm_info;
    char time_str[80];
    char filename[128];
    char cwd[path_max_size];
    char full_path[path_max_size * 2];
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("getcwd() error");
        exit(EXIT_FAILURE);
    }


    
    FILE* file = fopen(filename, "wb");
    if(file == NULL) {
        fprintf(stderr, "GetLiveView FAILED 6      can't open file:%s\n", full_path);
        sdk_destruct_image_data_block(image_data_block_handle);
        return NULL;
    }
    
    fwrite(sdk_get_image_data_image_data_block(image_data_block_handle), 1, buffer_size, file);
    fclose(file);

    sdk_destruct_image_data_block(image_data_block_handle);

    return buffer_size;
}



proc_liveview()
{ 
       if get_live_veiw_to_file(device_handle_handle, tmplvFile)>0
       {

           if (rename(tmplvFile, lvFile) != 0) 
           {
               fprintf(stderr, "Error file rename:%s\n", tmplvFile);
           }

       }
    
}

proc_dump_lists()
{
   get_opts_to_file(OPT_ID_ISO,listISOFile);
   get_opts_to_file(OPT_ID_WB,listWBFile);
}



int main(int argc, char ** argv)
{
  device_handle_handle=init_sdk__get_device_handle_handle();

  sleep(1);

  printf("Init complete\n");

  while(1)
  {
    proc_liveview();
    proc_dump_lists();
    proc_dump_opts();
    proc_set_opts();
    usleep(10000);
  }


  close_camera(&ptp_usb, &params, dev);
}
