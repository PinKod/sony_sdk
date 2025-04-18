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

#define FOCUS_MODE_CODE 265U
#define FOCUS_MODE_TYPE 8194U

int main() {
    void*        device_handle_handle = init_sdk__get_device_handle_handle();
    int          focus_mode_writable = -1;
    unsigned int focus_mode_current = 0;
    unsigned int focus_mode_array_len = 0;
    long int     focus_mode_get_result = 0;
    // unsigned int *focus_mode_array = get_focus_mode_array(device_handle_handle, &focus_mode_writable, &focus_mode_current, &focus_mode_array_len, &focus_mode_get_result);
    unsigned int* focus_mode_array = get_property_array(FOCUS_MODE_CODE, device_handle_handle, &focus_mode_writable, &focus_mode_current, &focus_mode_array_len, &focus_mode_get_result);
    printf("focus_mode_writable: %d\nfocus_mode_current: %d\nfocus_mode_array_len: %d\n", focus_mode_writable, focus_mode_current, focus_mode_array_len);
    if (focus_mode_get_result) {
        printf("Failed to get focus_mode array\n");
        printf("error: %ld\n", focus_mode_get_result);
        exit(EXIT_FAILURE);
    }
    for (unsigned int i = 0; i < focus_mode_array_len; i++) {
        printf("%2.0d)focus_mode:%d\n", i + 1, focus_mode_array[i]);
    }

    unsigned int current_focus_mode = 0;
    if (get_current_value_property(FOCUS_MODE_CODE, device_handle_handle, &current_focus_mode) == 0) {
        printf("current focus_mode value: %d\n", current_focus_mode);
    } else {
        printf("get current value property error\n");
    }

    for (unsigned int i = 0; i < focus_mode_array_len; i++) {
        sleep(1);
        printf("%2.d)set focus_mode: %d\n", i + 1, focus_mode_array[i]);
        set_value_property(FOCUS_MODE_CODE, device_handle_handle, focus_mode_array[i], FOCUS_MODE_TYPE);
    }

    printf("manual setting focus mode\n");
    unsigned int FOCUS_MODE_TABLE_API_CODES[] = {
        2,
        4,
        3,
        6,
        1,
    };
    for (unsigned int i = 0; i < 5; i++) {
        sleep(1);
        printf("err:%ld\n", set_value_property(FOCUS_MODE_CODE, device_handle_handle, FOCUS_MODE_TABLE_API_CODES[i], FOCUS_MODE_TYPE));
    }

    if (sdk_release()) {
        perror("SDK release failed\n");
        exit(EXIT_FAILURE);
    }
}
