#include "./../c++_wrapper/wrapper.h"
#include "./../lib_c/lib_c.h"
#include "./sony_properties.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define BUFF_SIZE_IMAGE_INFO 1048576 //  1024 * 1024

void* device_handle_handle = NULL;

void proc_liveview() {
    if (get_live_veiw_to_file(device_handle_handle, tmplvFile) > 0) {
        if (rename(tmplvFile, lvFile) != 0) {
            fprintf(stderr, "Error file rename:%s\n", tmplvFile);
        }
    }
}

void write_lists_to_file(unsigned int code, int table_count, char* file_name, unsigned int* table_codes, char** table_list) {
    FILE* file = fopen(TEMPORARY_FILE, "w");
    if (!file) {
        perror("err 0\n");
        return;
    }


    int           writable = -1;
    unsigned int  current = 0;
    unsigned int  array_len = 0;
    long int      get_result = 0;
    unsigned int* array = get_property_array(code, device_handle_handle, &writable, &current, &array_len, &get_result);
    if (get_result) {
        fclose(file);
        perror("err 1\n");
        printf("code: %d\n", code);
        return;
    }


    if(code == FOCUS_MODE_CODE) {   ///focus mode setting dont work properly
        for (unsigned int i = 0; i < array_len; i++) {
            fprintf(file, "%s\n", table_list[i]);
        }
    }
    

    for (unsigned int i = 0; i < array_len; i++) {
        unsigned int array_i = array[i];
        for (int j = 0; j < table_count; j++) {
            if (array_i == table_codes[j]) {
                fprintf(file, "%s\n", table_list[j]);
                break;
            }
        }
    }
    fclose(file);
    rename(TEMPORARY_FILE, file_name);
}

void proc_dump_lists() {
    // clang-format off
    write_lists_to_file(FOCUS_MODE_CODE, FOCUS_MODE_TABLE_COUNT, LIST_FOCUS_MODE_FILE, FOCUS_MODE_TABLE_API_CODES, FOCUS_MODE_TABLE_API_LIST);
    write_lists_to_file(SHOOT_MODE_CODE, SHOOT_MODE_TABLE_COUNT, LIST_SHOOT_MODE_FILE, SHOOT_MODE_TABLE_API_CODES, SHOOT_MODE_TABLE_API_LIST);
    write_lists_to_file(ISO_CODE,        ISO_TABLE_COUNT,        LIST_ISO_FILE,               ISO_TABLE_API_CODES,        ISO_TABLE_API_LIST);
    // clang-format on
}

void write_current_setting_to_file(unsigned int code, unsigned int value_type, int table_count, char* file_name, unsigned int* table_codes, char** table_list) {
    FILE* file = fopen(TEMPORARY_FILE, "w");
    if (!file) {
        perror("err 0\n");
        return;
    }
    
    unsigned int current_value;
    int err = get_current_value_property(code, device_handle_handle, &current_value);
    if(err) {
        fprintf(stderr, "code: %d, get current value err: %d\n", code, err);
        fclose(file);
        return;
    }


    for(int i = 0; i < table_count; i++) {
        if(table_codes[i] == current_value) {
            fprintf(file, "%s\n", table_list[i]);
            break;
        }
    }
    fclose(file);
    rename(TEMPORARY_FILE, file_name);
}

void proc_dump_current_settings() {
    // clang-format off
    write_current_setting_to_file(FOCUS_MODE_CODE, FOCUS_MODE_TYPE,       FOCUS_MODE_TABLE_COUNT, NFO_FOCUS_MODE_FILE, FOCUS_MODE_TABLE_API_CODES, FOCUS_MODE_TABLE_API_LIST);
    write_current_setting_to_file(SHOOT_MODE_CODE, SHOOT_MODE_VALUE_TYPE, SHOOT_MODE_TABLE_COUNT, NFO_SHOOT_MODE_FILE, SHOOT_MODE_TABLE_API_CODES, SHOOT_MODE_TABLE_API_LIST);
    write_current_setting_to_file(ISO_CODE,        ISO_VALUE_TYPE,        ISO_TABLE_COUNT,        NFO_ISO_FILE,               ISO_TABLE_API_CODES,        ISO_TABLE_API_LIST);
    // clang-format on
}

void new_setting_from_file(unsigned int code, unsigned int value_type, int table_count, char* file_name, unsigned int* table_codes, char** table_list) {
    FILE* file = fopen(file_name, "r");
    
    if(!file) {
        return;
    }

    char new_setting[128];
    int          res = fscanf(file, "%s", new_setting);
    fclose(file);
    printf("remove res: %d\n", remove(file_name));
    if (res != 1) {
        return;
    }


    int           writable = -1;
    unsigned int  current = 0;
    unsigned int  array_len = 0;
    long int      get_result = 0;
    unsigned int* array = get_property_array(code, device_handle_handle, &writable, &current, &array_len, &get_result);
    if (get_result) {
        printf("Failed to get array for: %d\n", code);
        printf("error: %ld\n", get_result);
        return;
    }

    int flag_0 = 0;
    int new_setting_i = -1;
    for(int i = 0; i < table_count; i++) {
        if(strcmp(new_setting, table_list[i]) == 0) {
            flag_0 = 1;
            new_setting_i = i;
            break;
        }
    }
    if(flag_0 == 0) {
        return;
    }


    int flag = 0;
    unsigned int new_setting_unsigned = 0;
    for (unsigned int i = 0; i < array_len; i++) {
        if (array[i] == table_codes[new_setting_i]) {
            flag = 1;
            new_setting_unsigned = array[i];
            break;
        }
    }
    if (flag == 0) {
        printf("Invalid: %s\n", new_setting);
        return;
    }


    long set_res = set_value_property(code, device_handle_handle, new_setting_unsigned, value_type);
    if (set_res) {
        printf("error");
    }

    
}

void proc_set_setting() {
    // clang-format off
    new_setting_from_file(FOCUS_MODE_CODE, FOCUS_MODE_TYPE,       FOCUS_MODE_TABLE_COUNT, SET_FOCUS_MODE_FILE, FOCUS_MODE_TABLE_API_CODES, FOCUS_MODE_TABLE_API_LIST);
    new_setting_from_file(SHOOT_MODE_CODE, SHOOT_MODE_VALUE_TYPE, SHOOT_MODE_TABLE_COUNT, SET_SHOOT_MODE_FILE, SHOOT_MODE_TABLE_API_CODES, SHOOT_MODE_TABLE_API_LIST);
    new_setting_from_file(ISO_CODE,        ISO_VALUE_TYPE,        ISO_TABLE_COUNT,        SET_ISO_FILE,               ISO_TABLE_API_CODES,        ISO_TABLE_API_LIST);
    // clang-format on
}

int main(int argc, char** argv) {
    device_handle_handle = init_sdk__get_device_handle_handle();

    sleep(1);

    printf("Init complete\n");

    int i = 0;
    while (i++ < 100000) {
        proc_liveview();
        proc_dump_lists();
        proc_dump_current_settings();
        proc_set_setting();
        usleep(100000);
    }

    sdk_release();
}
