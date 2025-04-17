#include "./../c++_wrapper/wrapper.h"
#include "./../classes_methods/classes_methods.h"
#include "./../utils/utils.h"
#include "./../lib_c/lib_c.h"


#include <stdlib.h>
#include <stdio.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

int main() {
    if (sdk_init()) {
        perror("SDK initialization failed\n");
        exit(999);
    }
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


    sleep(1);


    int iso_writable = -1;
    unsigned int iso_current = 0;
    unsigned int *iso_array = NULL;
    unsigned int iso_array_len = 0;
	long int iso_get_result = get_iso_array(device_handle_handle, &iso_writable, &iso_current, iso_array, &iso_array_len);
    printf("iso_writable: %d\niso_current: %d\niso_array_len: %d\n", iso_writable, iso_current, iso_array_len);
    if(iso_get_result) {
        printf("Failed to get iso array\n");
        printf("error: %ld\n", iso_get_result);
        exit(EXIT_FAILURE);
    }


    for(unsigned int i = 0; i < iso_array_len; i++) {
        printf("%d)iso:%d\n", i + 1, iso_array[i]);
    }














    sdk_camera_object_info_release(camera_info);
    if (sdk_release()) {
        perror("SDK release failed\n");
        exit(EXIT_FAILURE);
    }
}

