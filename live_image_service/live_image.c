#include "./../c++_wrapper/wrapper.h"
#include "./../classes_methods/classes_methods.h"
#include "./../utils/utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 

//#define _POSIX_C_SOURCE 199309L
#include <time.h>



void timed_loop(void* device_handle_handle) {
    // volatile int* flag = 1;
    int c = 0;
    while(c++ < 100) {
        sdk_change_saving_destination_to_host_pc(device_handle_handle);
        char* path = just_get_live_view(device_handle_handle);
        printf("path: %s\n", path);
        sdk_change_saving_destination_to_camera(device_handle_handle);
    }
}

int main() {
    if (sdk_init()) {
        perror("SDK initialization failed\n");
        exit(999);
    }
    sleep(4);
    void* enum_handle = NULL;
    long int enum_result = sdk_enum_camera_object(&enum_handle);
    if (enum_result) {
        perror("Failed to enumerate cameras\n");
        printf("error: %ld\n", enum_result);
        exit(EXIT_FAILURE);
    }

    void* camera_info = sdk_enum_camera_object_get_camera_object_info(enum_handle, 0);
    if (!camera_info) {
        printf("Failed to get info for camera\n");
        sdk_release();
        exit(EXIT_FAILURE);
    }

    void* device_handle_handle = NULL;
    long int connect_result = sdk_connect(camera_info, NULL, &device_handle_handle);
    if(connect_result) {
        perror("Failed to connect to camera\n");
        printf("error: %ld\n", connect_result);
        exit(EXIT_FAILURE);
    }

    sleep(2);
    timed_loop(device_handle_handle);


    sdk_camera_object_info_release(camera_info);
    if (sdk_release()) {
        perror("SDK release failed\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}
