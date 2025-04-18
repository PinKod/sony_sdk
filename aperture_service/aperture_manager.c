#include "./../c++_wrapper/wrapper.h"
#include "./../classes_methods/classes_methods.h"
#include "./../lib_c/lib_c.h"
#include "./../utils/utils.h"

#include <stdio.h>
#include <stdlib.h>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int main() {
    void*        device_handle_handle = init_sdk__get_device_handle_handle();
    int          aperture_writable = -1;
    unsigned int aperture_current = 0;
    unsigned int aperture_array_len = 0;
    long int     aperture_get_result = 0;
    // unsigned int *aperture_array = get_aperture_array(device_handle_handle, &aperture_writable, &aperture_current, &aperture_array_len, &aperture_get_result);
    unsigned int* aperture_array = get_property_array(APERTURE_CODE, device_handle_handle, &aperture_writable, &aperture_current, &aperture_array_len, &aperture_get_result);
    printf("aperture_writable: %d\naperture_current: %d\naperture_array_len: %d\n", aperture_writable, aperture_current, aperture_array_len);
    if (aperture_get_result) {
        printf("Failed to get aperture array\n");
        printf("error: %ld\n", aperture_get_result);
        exit(EXIT_FAILURE);
    }
    for (unsigned int i = 0; i < aperture_array_len; i++) {
        printf("%2.0d)aperture:%d\n", i + 1, aperture_array[i]);
    }

    unsigned int current_aperture = 0;
    if (get_current_value_property(APERTURE_CODE, device_handle_handle, &current_aperture) == 0) {
        printf("current aperture value: %d\n", current_aperture);
    } else {
        printf("get current value property error\n");
    }

    for (unsigned int i = 0; i < aperture_array_len; i++) {
        sleep(1);
        printf("%2.d)set aperture: %d\n", i + 1, aperture_array[i]);
        set_value_property(APERTURE_CODE, device_handle_handle, aperture_array[i], APERTURE_TYPE);
    }

    if (sdk_release()) {
        perror("SDK release failed\n");
        exit(EXIT_FAILURE);
    }
}
