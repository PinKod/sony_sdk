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
    // struct timespec next;
    // clock_gettime(CLOCK_MONOTONIC, &next);  // Get initial time

    for(int i = 0; i < 120; i++) {  // Or use a while(1) loop
        // Execute the target function
        void* image_data_block_handle = just_get_live_view(device_handle_handle);

        // Calculate next target time
        // next.tv_nsec += INTERVAL_NS;
        // if (next.tv_nsec >= 1000000000) {
        //     next.tv_nsec -= 1000000000;
        //     next.tv_sec += 1;
        // }

        // // Sleep until the next target time
        // struct timespec now;
        // clock_gettime(CLOCK_MONOTONIC, &now);
        
        // struct timespec sleep_time = {
        //     .tv_sec = next.tv_sec - now.tv_sec,
        //     .tv_nsec = next.tv_nsec - now.tv_nsec
        // };

        // // Handle underflow
        // if (sleep_time.tv_nsec < 0) {
        //     sleep_time.tv_sec -= 1;
        //     sleep_time.tv_nsec += 1000000000;
        // }

        // // Sleep only if needed
        // if (sleep_time.tv_sec > 0 || sleep_time.tv_nsec > 0) {
        //     nanosleep(&sleep_time, NULL);
        // }
    }
}

int main() {
    if (sdk_init()) {
        perror("SDK initialization failed\n");
        exit(999);
    }

    void* enum_handle = NULL;
    long int enum_result = sdk_enum_camera_object(&enum_handle);
    if (enum_result) {
        perror("Failed to enumerate cameras\n");
        sdk_release();
        exit(EXIT_FAILURE);
    }

    int camera_count = sdk_enum_camera_object_get_count(enum_handle);
    printf("Detected cameras: %d\n", camera_count);

    for (int i = 0; i < camera_count; i++) {
        printf("\n=== Camera %d ===\n", i+1);

        void* camera_info = sdk_enum_camera_object_get_camera_object_info(enum_handle, i);
        if (!camera_info) {
            printf("Failed to get info for camera %d\n", i+1);
            continue;
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
        int id_size = sdk_camera_object_info_get_id_size(camera_info);
        int id_type = sdk_camera_object_info_get_id_type(camera_info);
        char* camera_id = sdk_camera_object_info_get_id(camera_info);
        printf("ID: %s (Size: %d, Type: %d)\n", camera_id ? camera_id : "N/A", id_size, id_type);

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
        
        // void* device_properties_handle = NULL;
        // long int number_of_properties = 0;
        // int properties_result = sdk_get_device_properties(device_handle_handle, &device_properties_handle, &number_of_properties);
        // printf("get properties result:%lld\ndevice_properties_handle:%p      number of properties:%ld\n", properties_result, device_properties_handle, number_of_properties);


        // // void* new_device_property = sdk_construct_device_property();
        // // printf("new_device_property ptr:%p\n", new_device_property);

        // int dummy_int  = 0;
        // void* dummy_data = NULL;
        // int live_view_properties_result = sdk_get_live_view_properties(device_handle_handle, &dummy_data, &dummy_int); 
        // printf("live_view_properties_result:%d      ptr:%p\n", live_view_properties_result, dummy_data);
        // sdk_release_live_view_properties(device_handle_handle, dummy_data);
        
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

        printf("focus test\n");

        long int number_of_properties = -1;
        void* device_property_handle = NULL;
        long int prop_res = sdk_get_device_properties(device_handle_handle, &device_property_handle, &number_of_properties);
        printf("prop res:%ld        device_property_handle:%p\n", prop_res, device_property_handle);
        if(device_property_handle) {
            printf("focus:%lld\n", get_device_property_focus(device_handle_handle));
        }




        // // !!!                                                !!!
        // // !!!                                                !!!
        // // loop for taking liveView image(a lot)30 fps(not fixed)
        // // !!!                                                !!!
        // // !!!                                                !!!
        // sleep(2);
        // for(int i = 0; i < 1; i++) {

        //     timed_loop(device_handle_handle);
        // }



        // printf("save dst res: %d\n", sdk_change_saving_destination_to_camera(device_handle_handle));
        // for(int i = 0; i < 1; i++) {
        //     //usleep(499999);
        //     //get time in millisnods ad puts it to char buffer
        //     char path[100];
        //     struct timespec ts;
        //     clock_gettime(CLOCK_REALTIME, &ts);
        //     struct tm* tm_info = localtime(&ts.tv_sec);
        //     strftime(path, sizeof(path), "%Y_%m_%d_%H_%M_%S_", tm_info);
        //     snprintf(path + strlen(path), sizeof(path) - strlen(path), "_%ld", ts.tv_nsec / 1000);
        //     printf("path:'%s'\n", path); 
        //     sdk_capture_image(device_handle_handle, path);
        // }





        sdk_camera_object_info_release(camera_info);
        printf("====================\n");

        
    }

    // Test USB connection creation
    // int usb_conn_result = sdk_create_camera_object_usb_connection();
    // printf("\nUSB Connection Creation Result: %d (%s)\n", 
    //        usb_conn_result, 
    //        usb_conn_result ? "Failed" : "Success");

    // Cleanup
    //sdk_enum_camera_object_release(enum_handle);
    
    if (sdk_release()) {
        perror("SDK release failed\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}
