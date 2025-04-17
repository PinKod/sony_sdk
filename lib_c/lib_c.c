#include "lib_c.h"

#include "./../c++_wrapper/wrapper.h"
#include "./../classes_methods/classes_methods.h"
#include "./../c++_wrapper/CrTypes.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <limits.h>

char* get_live_veiw(void* device_handle_handle) {
    void* image_info_handle = sdk_construct_image_info();
    long int info_result = sdk_get_live_view_image_info(device_handle_handle, image_info_handle);
    if(info_result) {
        fprintf(stderr, "GetLiveView FAILED 1      err:%ld\n", info_result);
        return NULL;
    }


    CrInt32u buffer_size = sdk_get_buffer_size_image_info(image_info_handle);
    if(buffer_size < 1) {
        fprintf(stderr, "GetLiveView FAILED 2      size:%d\n", buffer_size);
        return NULL;
    }


    void* image_data_block_handle = sdk_construct_image_data_block();
    if(!image_data_block_handle) {
        fprintf(stderr, "GetLiveView FAILED 3      allocation failed\n");
        return NULL;
    }


    #define  BUFF_SIZE_IMAGE_INFO 1048576  //  1024 * 1024
    static unsigned char image_buff[BUFF_SIZE_IMAGE_INFO];
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


    gettimeofday(&tv, NULL);
    localtime_r(&tv.tv_sec, &tm_info);
    strftime(time_str, sizeof(time_str), "%Y_%m_%d_%H_%M_%S", &tm_info);
    int milliseconds = tv.tv_usec / 1000;
    snprintf(filename, sizeof(filename), 
             "LiveVeiw_%s____%03d.JPG", 
             time_str, milliseconds);
    snprintf(full_path, sizeof(full_path), 
             "%s/%s", cwd, filename);
    

    
    FILE* file = fopen(full_path, "wb");
    if(file == NULL) {
        fprintf(stderr, "GetLiveView FAILED 6      can't open file:%s\n", full_path);
        sdk_destruct_image_data_block(image_data_block_handle);
        return NULL;
    }
    
    fwrite(sdk_get_image_data_image_data_block(image_data_block_handle), 1, buffer_size, file);
    fclose(file);

    
    fprintf(stdout, "GetLiveView SUCCESS\n");
    sdk_destruct_image_data_block(image_data_block_handle);

    char* return_path = malloc(sizeof(char) * strlen(full_path) + 1);
    strcpy(return_path, full_path);
    return return_path;
}




//will allocate memory for iso_array
long int get_iso_array(void* device_handle_handle, int* iso_writable, unsigned int* iso_current, unsigned int* iso_array, unsigned int* iso_array_len) {
    long nprop = 0;
    void* iso_device_property_handle = NULL;
    long codes = 260U;
    long int get_prop_result = sdk_get_select_device_properties(device_handle_handle, 1, &codes, &iso_device_property_handle, &nprop);
    if(get_prop_result) {
        fprintf(stderr, "Get_iso_array FAILED 1      err:%ld\n", get_prop_result);
        return get_prop_result;
    }
    printf("iso_device_property_handle: %p\n", iso_device_property_handle);
    


    unsigned long size = sdk_get_value_size_device_property(iso_device_property_handle);
    int number_values = 0;
    number_values = size / sizeof(unsigned int);
    *iso_writable = sdk_is_set_enable_device_property(iso_device_property_handle);
    *iso_current = sdk_get_current_value_device_property(iso_device_property_handle);
    if(number_values <= 0) {
        printf("value size: %ld\n", size);
        return -1;
    }

    iso_array = malloc(sizeof(unsigned int) * number_values);
    if(!iso_array) {
        return -2;
    }

    *iso_array_len = number_values;
    unsigned int const* source = (unsigned int const*)sdk_get_values_device_property(iso_device_property_handle);
    for(int i = 0; i < number_values; ++i, ++source) {
        memcpy(&iso_array[i], source, sizeof(unsigned int));
    }

    return 0;
}