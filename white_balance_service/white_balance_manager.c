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
    int          white_balance_writable = -1;
    unsigned int white_balance_current = 0;
    unsigned int white_balance_array_len = 0;
    long int     white_balance_get_result = 0;
    // unsigned int *white_balance_array = get_white_balance_array(device_handle_handle, &white_balance_writable, &white_balance_current, &white_balance_array_len, &white_balance_get_result);
    unsigned int* white_balance_array = get_property_array(WHITE_BALANCE_CODE, device_handle_handle, &white_balance_writable, &white_balance_current, &white_balance_array_len, &white_balance_get_result);
    printf("white_balance_writable: %d\nwhite_balance_current: %d\nwhite_balance_array_len: %d\n", white_balance_writable, white_balance_current, white_balance_array_len);
    if (white_balance_get_result) {
        printf("Failed to get white_balance array\n");
        printf("error: %ld\n", white_balance_get_result);
        exit(EXIT_FAILURE);
    }
    for (unsigned int i = 0; i < white_balance_array_len; i++) {
        printf("%2.0d)white_balance:%d\n", i + 1, white_balance_array[i]);
    }

    unsigned int current_white_balance = 0;
    if (get_current_value_property(WHITE_BALANCE_CODE, device_handle_handle, &current_white_balance) == 0) {
        printf("current white_balance value: %d\n", current_white_balance);
    } else {
        printf("get current value property error\n");
    }

    for (unsigned int i = 0; i < white_balance_array_len; i++) {
        sleep(1);
        printf("%2.d)set white_balance: %d\n", i + 1, white_balance_array[i]);
        set_value_property(WHITE_BALANCE_CODE, device_handle_handle, white_balance_array[i], WHITE_BALANCE_TYPE);
    }

    if (sdk_release()) {
        perror("SDK release failed\n");
        exit(EXIT_FAILURE);
    }
}
