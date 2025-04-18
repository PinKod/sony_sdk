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
    void* device_handle_handle = init_sdk__get_device_handle_handle();
    int jpeg_quality_writable = -1;
    unsigned int jpeg_quality_current = 0;
    unsigned int jpeg_quality_array_len = 0;
    long int jpeg_quality_get_result = 0;
    // unsigned int *jpeg_quality_array = get_jpeg_quality_array(device_handle_handle, &jpeg_quality_writable, &jpeg_quality_current, &jpeg_quality_array_len, &jpeg_quality_get_result);
    unsigned int *jpeg_quality_array = get_property_array(JPEG_QUALITY_CODE, device_handle_handle, &jpeg_quality_writable, &jpeg_quality_current, &jpeg_quality_array_len, &jpeg_quality_get_result);
    printf("jpeg_quality_writable: %d\njpeg_quality_current: %d\njpeg_quality_array_len: %d\n", jpeg_quality_writable, jpeg_quality_current, jpeg_quality_array_len);
    if(jpeg_quality_get_result) {
        printf("Failed to get jpeg_quality array\n");
        printf("error: %ld\n", jpeg_quality_get_result);
        exit(EXIT_FAILURE);
    }
    for(unsigned int i = 0; i < jpeg_quality_array_len; i++) {
        printf("%2.0d)jpeg_quality:%d\n", i + 1, jpeg_quality_array[i]);
    }

    unsigned int current_jpeg_quality = 0;
    if(get_current_value_property(JPEG_QUALITY_CODE, device_handle_handle, &current_jpeg_quality) == 0) {
        printf("current jpeg_quality value: %d\n", current_jpeg_quality);
    }
    else {
        printf("get current value property error\n");
    }

    for(unsigned int i = 0; i < jpeg_quality_array_len; i++) {
        sleep(1);
        printf("%2.d)set jpeg_quality: %d\n", i + 1, jpeg_quality_array[i]);
        set_value_property(JPEG_QUALITY_CODE, device_handle_handle, jpeg_quality_array[i], JPEG_QUALITY_TYPE);
    }


    



















    if (sdk_release()) {
        perror("SDK release failed\n");
        exit(EXIT_FAILURE);
    }
}

