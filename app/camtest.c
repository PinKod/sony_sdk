#include "./../c++_wrapper/wrapper.h"
#include "./../classes_methods/classes_methods.h"
#include "./../utils/utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 

//#define _POSIX_C_SOURCE 199309L
#include <time.h>

#define INTERVAL_NS 33333333  // 33.333333 milliseconds

void timed_loop(void* device_handle_handle) {

    for(int i = 0; i < 120; i++) {  // Or use a while(1) loop
        void* image_data_block_handle = just_get_live_view(device_handle_handle);

    }
}

int main() {
    if (sdk_init()) 
    {
        perror("SDK initialization failed\n");
        exit(1);
    }

    void* enum_handle = NULL;
    long int enum_result = sdk_enum_camera_object(&enum_handle);
    if (!enum_result) 
    {
        perror("Failed to enumerate cameras\n");
        sdk_release();
        exit(2);
    }

    int camera_count = sdk_enum_camera_object_get_count(enum_handle);
    printf("Detected cameras: %d\n", camera_count);
    if (camera_count==0)
    {
        perror("Failed to enumerate cameras\n");
        sdk_release();
        exit(3);
    }

    if (camera_count>0)
        printf("Few cameras detected! Using first one.\n");


    void* camera_info = sdk_enum_camera_object_get_camera_object_info(enum_handle, 1);
    if (!camera_info) {
        printf("Failed to get info for camera\n");
    }

        // Get and print name information
    int name_size = sdk_camera_object_info_get_name_size(camera_info);
    char* name = sdk_camera_object_info_get_name(camera_info);
    printf("Name: %s (Size: %d)\n", name ? name : "N/A", name_size);

        // Get and print model information
    int model_size = sdk_camera_object_info_get_model_size(camera_info);
    char* model = sdk_camera_object_info_get_model(camera_info);
    printf("Model: %s (Size: %d)\n", model ? model : "N/A", model_size);

        // Get USB PID
    int usb_pid = sdk_camera_object_info_get_usb_pid(camera_info);
    printf("USB PID: 0x%04X\n", usb_pid);

        // Get ID information
    int id_type = sdk_camera_object_info_get_id_type(camera_info);
    char* camera_id = sdk_camera_object_info_get_id(camera_info);
    printf("ID: %s Type: %d\n", camera_id ? camera_id : "N/A", id_type);

        // Connection information
    int conn_status = sdk_camera_object_info_get_connection_status(camera_info);
    char* conn_type = sdk_camera_object_info_get_connection_type_name(camera_info);
    printf("Connection Status: %d, Type: %s\n", conn_status, conn_type ? conn_type : "N/A");

        // Additional information
    char* adaptor = sdk_camera_object_info_get_adaptor_name(camera_info);
    char* guid = sdk_camera_object_info_get_guid(camera_info);
    char* pairing = sdk_camera_object_info_get_pairing_necessity(camera_info);
    printf("Adaptor: %s\n", adaptor ? adaptor : "N/A");
    printf("GUID: %s\n", guid ? guid : "N/A");
    printf("Pairing Necessity: %s\n", pairing ? pairing : "N/A");

        // Authentication and SSH
    int auth_state = sdk_camera_object_info_get_authentification_state(camera_info);
    int ssh_support = sdk_camera_object_info_get_ssh_support(camera_info);
    printf("Authentication State: %d\n", auth_state);
    printf("SSH Support: %d\n", ssh_support);
        
    void* device_handle_handle = NULL;
    long long int connect_result = sdk_connect(camera_info, NULL, &device_handle_handle);
    printf("Connection result:%lld      device_handle_handle:%p     device:%lld\n", connect_result, device_handle_handle, *(long long*)device_handle_handle);
    sdk_camera_device_set_save_info(device_handle_handle);
        
    int dummy_int  = 0;
    void* dummy_data = NULL;
    int live_view_properties_result = sdk_get_live_view_properties(device_handle_handle, &dummy_data, &dummy_int); 
    printf("live_view_properties_result:%d      ptr:%p\n", live_view_properties_result, dummy_data);
    sdk_release_live_view_properties(device_handle_handle, dummy_data);
        
        // void* image_info = sdk_construct_image_info();
        // int get_image_info_result = sdk_get_live_view_image_info(device_handle_handle, image_info);
        // printf("get image info result:%d        ptr:%p\n", get_image_info_result, image_info);
        
        // void* image_data_block_handle = sdk_construct_image_data_block();
        // printf("image_data_block_handle ptr:%p\n", image_data_block_handle);
        // // unsigned long  time = sdk_get_time_code_image_data_block(image_data_block_handle);
        // // printf("time before:%lld\n", time);


        // #define  buff_size_image_info 1048576
        // static unsigned char image_buffer[buff_size_image_info]= {0};
        // memset(image_buffer, '0', sizeof(unsigned char) * buff_size_image_info);
        // //printf("buffer:'%s'\n", image_buffer);
        // printf("buffer len:%d\n", strlen(image_buffer)); 

        // sdk_set_size_image_data_block(image_data_block_handle, buff_size_image_info);
        // sdk_set_data_image_data_block(image_data_block_handle, image_buffer);
        
        // printf("size_image_data:%lld    ptr data image:%p\n", 
        //     sdk_get_size_image_data_block(image_data_block_handle),
        //     sdk_get_image_data_image_data_block(image_data_block_handle)
        // );
        
        // for(int i = 0; i < 15; i++) {
        //     sleep(2);
        //     long int view_rsult = sdk_get_live_view_image(device_handle_handle, image_data_block_handle);
        //     // printf("veiw result:%ld\n", view_rsult);    
        //     printf("image chars:%s\n", image_buffer);
        //     sdk_save_image(image_data_block_handle);
        // }
    timed_loop(device_handle_handle);



    sdk_camera_object_info_release(camera_info);
    
    if (sdk_release()) {
        perror("SDK release failed\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}
