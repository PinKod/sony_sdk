#include "./../c++_wrapper/wrapper.h"
#include "./../classes_methods/classes_methods.h"
#include "./../utils/utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

//#define _POSIX_C_SOURCE 199309L
#include <time.h>



void timed_loop(void* device_handle_handle) {
    // volatile int* flag = 1;
    int c = 0;
    while(c++ < 100) {
        sdk_change_saving_destination_to_host_pc(device_handle_handle);
        char* path = just_get_live_view(device_handle_handle);
        printf("Original path: %s\n", path);

        /* New code for renaming file */
        char new_path[1024];  // Buffer for new path
        
        // Find last directory separator (works for both Unix and Windows)
        char* last_slash = strrchr(path, '/');
        char* last_backslash = strrchr(path, '\\');
        char* separator = (last_backslash > last_slash) ? last_backslash : last_slash;

        if (separator) {
            // If path contains directory, preserve it and replace filename
            size_t dir_length = separator - path + 1;
            snprintf(new_path, sizeof(new_path), "%.*slive_image.JPG", (int)dir_length, path);
        } else {
            // If no directory, use new filename directly
            strncpy(new_path, "live_image.JPG", sizeof(new_path));
        }

        // Perform the rename operation
        if (rename(path, new_path) != 0) {
            fprintf(stderr, "Error renaming file: %s\n", strerror(errno));
        } else {
            printf("Renamed to: %s\n", new_path);
        }

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
