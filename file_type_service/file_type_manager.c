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
    int file_type_writable = -1;
    unsigned int file_type_current = 0;
    unsigned int file_type_array_len = 0;
    long int file_type_get_result = 0;
    // unsigned int *file_type_array = get_file_type_array(device_handle_handle, &file_type_writable, &file_type_current, &file_type_array_len, &file_type_get_result);
    unsigned int *file_type_array = get_property_array(FILE_TYPE_CODE, device_handle_handle, &file_type_writable, &file_type_current, &file_type_array_len, &file_type_get_result);
    printf("file_type_writable: %d\nfile_type_current: %d\nfile_type_array_len: %d\n", file_type_writable, file_type_current, file_type_array_len);
    if(file_type_get_result) {
        printf("Failed to get file_type array\n");
        printf("error: %ld\n", file_type_get_result);
        exit(EXIT_FAILURE);
    }
    for(unsigned int i = 0; i < file_type_array_len; i++) {
        printf("%2.0d)file_type:%d\n", i + 1, file_type_array[i]);
    }

    unsigned int current_file_type = 0;
    if(get_current_value_property(FILE_TYPE_CODE, device_handle_handle, &current_file_type) == 0) {
        printf("current file_type value: %d\n", current_file_type);
    }
    else {
        printf("get current value property error\n");
    }

    for(unsigned int i = 0; i < file_type_array_len; i++) {
        sleep(1);
        printf("%2.d)set file_type: %d\n", i + 1, file_type_array[i]);
        set_value_property(FILE_TYPE_CODE, device_handle_handle, file_type_array[i], FILE_TYPE_TYPE);
    }


    



















    if (sdk_release()) {
        perror("SDK release failed\n");
        exit(EXIT_FAILURE);
    }
}

