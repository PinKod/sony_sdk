#include "./../c++_wrapper/wrapper.h"
#include "./../classes_methods/classes_methods.h"
#include "./../lib_c/lib_c.h"
#include "./../utils/utils.h"
#include "./../camera_service/sony_properties.h"

#include <stdio.h>
#include <stdlib.h>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <limits.h>

int main() {
    void*        device_handle_handle = init_sdk__get_device_handle_handle();
    int          shutter_speed_writable = -1;
    unsigned int shutter_speed_current = 0;
    unsigned int shutter_speed_array_len = 0;
    long int     shutter_speed_get_result = 0;
    // unsigned int *shutter_speed_array = get_shutter_speed_array(device_handle_handle, &shutter_speed_writable, &shutter_speed_current, &shutter_speed_array_len, &shutter_speed_get_result);
    FOCUS_MODE_TYPE* shutter_speed_array = get_property_array(FOCUS_POSITION_SETTING_CODE, device_handle_handle, &shutter_speed_writable, &shutter_speed_current, &shutter_speed_array_len, &shutter_speed_get_result, sizeof(FOCUS_MODE_TYPE));
    printf("shutter_speed_writable: %d\nshutter_speed_current: %d\nshutter_speed_array_len: %d\n", shutter_speed_writable, shutter_speed_current, shutter_speed_array_len);
    if (shutter_speed_get_result) {
        printf("Failed to get shutter_speed array\n");
        printf("error: %ld\n", shutter_speed_get_result);
        exit(EXIT_FAILURE);
    }
    for (unsigned int i = 0; i < shutter_speed_array_len; i++) {
        printf("%2.0d)shutter_speed:%d\n", i + 1, shutter_speed_array[i]);
    }

    unsigned int current_shutter_speed = 0;
    if (get_current_value_property(FOCUS_POSITION_SETTING_CODE, device_handle_handle, &current_shutter_speed) == 0) {
        printf("current shutter_speed value: %d\n", current_shutter_speed);
    } else {
        printf("get current value property error\n");
    }

    for (unsigned int i = 0; i < shutter_speed_array_len; i++) {
        sleep(1);
        printf("%2.d)set shutter_speed: %d\n", i + 1, shutter_speed_array[i]);
        set_value_property(FOCUS_POSITION_SETTING_CODE, device_handle_handle, shutter_speed_array[i], FOCUS_MODE_VALUE_TYPE);
    }

    FOCUS_MODE_TYPE val = 0;
    unsigned int i = 0;
    while(val < USHRT_MAX - 2184) {
        printf("%2.d)focus: %d\n", i + 1, val);
        set_value_property(FOCUS_POSITION_SETTING_CODE, device_handle_handle, val, FOCUS_MODE_VALUE_TYPE);
        sleep(1);
        unsigned int cur_val = 0;
        if (get_current_value_property(FOCUS_POSITION_SETTING_CODE, device_handle_handle, &cur_val) == 0) {
            printf("   current focus val: %d\n", cur_val);
        }
        i += 1;
        val += 2184;
    }

    if (sdk_release()) {
        perror("SDK release failed\n");
        exit(EXIT_FAILURE);
    }
}
