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
    int          exsposure_correction_writable = -1;
    unsigned int exsposure_correction_current = 0;
    unsigned int exsposure_correction_array_len = 0;
    long int     exsposure_correction_get_result = 0;
    // unsigned int *exsposure_correction_array = get_exsposure_correction_array(device_handle_handle, &exsposure_correction_writable, &exsposure_correction_current, &exsposure_correction_array_len, &exsposure_correction_get_result);
    unsigned int* exsposure_correction_array = get_property_array(EXSPOSURE_CORRECTION_CODE, device_handle_handle, &exsposure_correction_writable, &exsposure_correction_current, &exsposure_correction_array_len, &exsposure_correction_get_result);
    printf("exsposure_correction_writable: %d\nexsposure_correction_current: %d\nexsposure_correction_array_len: %d\n", exsposure_correction_writable, exsposure_correction_current, exsposure_correction_array_len);
    if (exsposure_correction_get_result) {
        printf("Failed to get exsposure_correction array\n");
        printf("error: %ld\n", exsposure_correction_get_result);
        exit(EXIT_FAILURE);
    }
    for (unsigned int i = 0; i < exsposure_correction_array_len; i++) {
        printf("%2.0d)exsposure_correction:%d\n", i + 1, exsposure_correction_array[i]);
    }

    unsigned int current_exsposure_correction = 0;
    if (get_current_value_property(EXSPOSURE_CORRECTION_CODE, device_handle_handle, &current_exsposure_correction) == 0) {
        printf("current exsposure_correction value: %d\n", current_exsposure_correction);
    } else {
        printf("get current value property error\n");
    }

    for (unsigned int i = 0; i < exsposure_correction_array_len; i++) {
        sleep(1);
        printf("%2.d)set exsposure_correction: %d\n", i + 1, exsposure_correction_array[i]);
        set_value_property(EXSPOSURE_CORRECTION_CODE, device_handle_handle, exsposure_correction_array[i], EXSPOSURE_CORRECTION_TYPE);
    }

    if (sdk_release()) {
        perror("SDK release failed\n");
        exit(EXIT_FAILURE);
    }
}
