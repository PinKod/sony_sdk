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
#include <sys/time.h>
#include <limits.h>

#define BUFF_SIZE_IMAGE_INFO 1048576 //  1024 * 1024

void* device_handle_handle = NULL;

void proc_liveview() {
    if (get_live_veiw_to_file(device_handle_handle, tmplvFile) > 0) {
        if (rename(tmplvFile, lvFile) != 0) {
            fprintf(stderr, "Error file rename:%s\n", tmplvFile);
        }
    }
}

void write_lists_to_file(unsigned int code, int table_count, char* file_name, void* table_codes, char** table_list, size_t TYPE_SIZE) {
    FILE* file = fopen(TEMPORARY_FILE, "w");
    if (!file) {
        perror("err 0\n");
        return;
    }


    int           writable = -1;
    unsigned int  current = 0;
    unsigned int  array_len = 0;
    long int      get_result = 0;
    unsigned char* array = get_property_array(code, device_handle_handle, &writable, &current, &array_len, &get_result, TYPE_SIZE);
    if (get_result) {
        fclose(file);
        rename(TEMPORARY_FILE, file_name);
        perror("err 1\n");
        printf("code: %d\n", code);
        return;
    }
    if(!writable) {
        fclose(file);
        rename(TEMPORARY_FILE, file_name);
        return;
    }

    unsigned char* table_codes_bytes = table_codes;
    for (unsigned int i = 0; i < array_len; i++, array += TYPE_SIZE) {
        unsigned int array_i = 0;
        memcpy(&array_i, array, TYPE_SIZE);
        unsigned char* table_codes_bytes_j = table_codes_bytes;
        for(int j = 0; j < table_count; j++, table_codes_bytes_j += TYPE_SIZE) {
            unsigned int table_j = 0;
            memcpy(&table_j, table_codes_bytes_j, TYPE_SIZE);
            if(array_i == table_j) {
                fprintf(file, "%s\n", table_list[j]);
                //fprintf(stdout, "%s\n", table_list[j]);
                break;
            }
        }
    }
    fclose(file);
    rename(TEMPORARY_FILE, file_name);
}


void write_current_setting_to_file(unsigned int code, unsigned int value_type, int table_count, char* file_name, void* table_codes, char** table_list, size_t TYPE_SIZE) {
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
    

    if(!table_codes) {
        fprintf(file, "%d\n", current_value);
        fclose(file);
        rename(TEMPORARY_FILE, file_name);
        return;
    }


    unsigned char* table_codes_bytes = table_codes;
    for(int i = 0; i < table_count; i++, table_codes_bytes += TYPE_SIZE) {
        unsigned int table_i = 0;
        memcpy(&table_i, table_codes_bytes, TYPE_SIZE);
        if(current_value == table_i) {
            fprintf(file, "%s\n", table_list[i]);
            break;
        }
    }
    fclose(file);
    rename(TEMPORARY_FILE, file_name);
}


void new_setting_from_file(unsigned int code, unsigned int value_type, int table_count, char* file_name, void* table_codes, char** table_list, size_t TYPE_SIZE) {
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
        fprintf(stderr, "no setting: %s\n", new_setting);
        return;
    }
    

    if(code == FOCUS_POSITION_SETTING_CODE) {
        int new_val_addition = atoi(new_setting);
        unsigned int current_focus_val = 0; 
        if (get_current_value_property(FOCUS_POSITION_SETTING_CODE, device_handle_handle, &current_focus_val) == 0) {
            unsigned int new_val = current_focus_val + new_val_addition;
            if(new_val <= USHRT_MAX) {
                set_value_property(FOCUS_POSITION_SETTING_CODE, device_handle_handle, new_val, FOCUS_MODE_VALUE_TYPE);
            }
        }
        return;
    }

    
    int           writable = -1;
    unsigned int  current = 0;
    unsigned int  array_len = 0;
    long int      get_result = 0;
    unsigned char* array = get_property_array(code, device_handle_handle, &writable, &current, &array_len, &get_result, TYPE_SIZE);
    if (get_result) {
        printf("Failed to get array for: %d\n", code);
        printf("error: %ld\n", get_result);
        return;
    }
    

    int flag = 0;
    unsigned int new_setting_unsigned = 0;
    unsigned char* table_codes_bytes = table_codes;
    table_codes_bytes += TYPE_SIZE * new_setting_i;
    unsigned int new_setting_val = 0;
    memcpy(&new_setting_val, table_codes_bytes, TYPE_SIZE);

    for (unsigned int i = 0; i < array_len; i++, array += TYPE_SIZE) {
        unsigned int array_i = 0;
        memcpy(&array_i, array, TYPE_SIZE);
        if(array_i == new_setting_val) {
            flag = 1;
            new_setting_unsigned = array_i;
            break;
        }
    }
    if (flag == 0) {
        printf("Invalid: %s\n", new_setting);
        return;
    }
    
    printf("new setting: %d\n", new_setting_unsigned);

    long set_res = set_value_property(code, device_handle_handle, new_setting_unsigned, value_type);
    if (set_res) {
        printf("error");
    }
    
    
}



void proc_dump_lists() {
    // clang-format off
    write_lists_to_file(FOCUS_MODE_CODE,                 FOCUS_MODE_TABLE_COUNT,                 LIST_FOCUS_MODE_FILE,                 FOCUS_MODE_TABLE_API_CODES,                      FOCUS_MODE_TABLE_API_LIST,                      sizeof(FOCUS_MODE_TYPE));
    write_lists_to_file(SHOOT_MODE_CODE,                 SHOOT_MODE_TABLE_COUNT,                 LIST_SHOOT_MODE_FILE,                 SHOOT_MODE_TABLE_API_CODES,                      SHOOT_MODE_TABLE_API_LIST,                      sizeof(SHOOT_MODE_TYPE));
    write_lists_to_file(APERTURE_CODE,                   APERTURE_TABLE_COUNT,                   LIST_APERTURE_FILE,                   APERTURE_TABLE_API_CODES,                        APERTURE_TABLE_API_LIST,                        sizeof(APERTURE_TYPE));
    write_lists_to_file(SHUTTER_SPEED_CODE,              SHUTTER_SPEED_TABLE_COUNT,              LIST_SHUTTER_SPEED_FILE,              SHUTTER_SPEED_TABLE_API_CODES,                   SHUTTER_SPEED_TABLE_API_LIST,                   sizeof(SHUTTER_SPEED_TYPE));
    write_lists_to_file(ISO_CODE,                        ISO_TABLE_COUNT,                        LIST_ISO_FILE,                        ISO_TABLE_API_CODES,                             ISO_TABLE_API_LIST,                             sizeof(ISO_TYPE));
    write_lists_to_file(EXPOSURE_BIAS_COMPENSATION_CODE, EXPOSURE_BIAS_COMPENSATION_TABLE_COUNT, LIST_EXPOSURE_BIAS_COMPENSATION_FILE, EXPOSURE_BIAS_COMPENSATION_TYPE_TABLE_API_CODES, EXPOSURE_BIAS_COMPENSATION_TYPE_TABLE_API_LIST, sizeof(EXPOSURE_BIAS_COMPENSATION_TYPE));
    write_lists_to_file(WHITE_BALANCE_CODE,              WHITE_BALANCE_TABLE_COUNT,              LIST_WHITE_BALANCE_FILE,              WHITE_BALANCE_TABLE_API_CODES,                   WHITE_BALANCE_TABLE_API_LIST,                   sizeof(WHITE_BALANCE_TYPE));
    write_lists_to_file(JPEG_QUALITY_CODE,               JPEG_QUALITY_TABLE_COUNT,               LIST_JPEG_QUALITY_FILE,               JPEG_QUALITY_TABLE_API_CODES,                    JPEG_QUALITY_TABLE_API_LIST,                    sizeof(JPEG_QUALITY_TYPE));
    write_lists_to_file(LIVE_VEIW_QUALITY_CODE,          LIVE_VEIW_QUALITY_TABLE_COUNT,          LIST_LIVE_VEIW_QUALITY_FILE,          LIVE_VEIW_QUALITY_TABLE_API_CODES,               LIVE_VEIW_QUALITY_TABLE_API_LIST,               sizeof(LIVE_VEIW_QUALITY_TYPE));
    write_lists_to_file(FOCUS_POSITION_SETTING_CODE,     FOCUS_POSITION_SETTING_TABLE_COUNT,     LIST_FOCUS_POSITION_SETTING_FILE,     FOCUS_MODE_TABLE_API_CODES,                      FOCUS_MODE_TABLE_API_LIST,                      sizeof(FOCUS_POSITION_SETTING_VALUE_TYPE));
    // clang-format on
}

void proc_dump_current_settings() {
    // clang-format off
    write_current_setting_to_file(FOCUS_MODE_CODE,                 FOCUS_MODE_VALUE_TYPE,                 FOCUS_MODE_TABLE_COUNT,                 NFO_FOCUS_MODE_FILE,                 FOCUS_MODE_TABLE_API_CODES,                      FOCUS_MODE_TABLE_API_LIST,                      sizeof(FOCUS_MODE_TYPE));
    write_current_setting_to_file(SHOOT_MODE_CODE,                 SHOOT_MODE_VALUE_TYPE,                 SHOOT_MODE_TABLE_COUNT,                 NFO_SHOOT_MODE_FILE,                 SHOOT_MODE_TABLE_API_CODES,                      SHOOT_MODE_TABLE_API_LIST,                      sizeof(SHOOT_MODE_TYPE));
    write_current_setting_to_file(APERTURE_CODE,                   APERTURE_VALUE_TYPE,                   APERTURE_TABLE_COUNT,                   NFO_APERTURE_FILE,                   APERTURE_TABLE_API_CODES,                        APERTURE_TABLE_API_LIST,                        sizeof(APERTURE_TYPE));
    write_current_setting_to_file(SHUTTER_SPEED_CODE,              SHUTTER_SPEED_VALUE_TYPE,              SHUTTER_SPEED_TABLE_COUNT,              NFO_SHUTTER_SPEED_FILE,              SHUTTER_SPEED_TABLE_API_CODES,                   SHUTTER_SPEED_TABLE_API_LIST,                   sizeof(SHUTTER_SPEED_TYPE));
    write_current_setting_to_file(ISO_CODE,                        ISO_VALUE_TYPE,                        ISO_TABLE_COUNT,                        NFO_ISO_FILE,                        ISO_TABLE_API_CODES,                             ISO_TABLE_API_LIST,                             sizeof(ISO_TYPE));
    write_current_setting_to_file(EXPOSURE_BIAS_COMPENSATION_CODE, EXPOSURE_BIAS_COMPENSATION_VALUE_TYPE, EXPOSURE_BIAS_COMPENSATION_TABLE_COUNT, NFO_EXPOSURE_BIAS_COMPENSATION_FILE, EXPOSURE_BIAS_COMPENSATION_TYPE_TABLE_API_CODES, EXPOSURE_BIAS_COMPENSATION_TYPE_TABLE_API_LIST, sizeof(EXPOSURE_BIAS_COMPENSATION_TYPE));
    write_current_setting_to_file(WHITE_BALANCE_CODE,              WHITE_BALANCE_VALUE_TYPE,              WHITE_BALANCE_TABLE_COUNT,              NFO_WHITE_BALANCE_FILE,              WHITE_BALANCE_TABLE_API_CODES,                   WHITE_BALANCE_TABLE_API_LIST,                   sizeof(WHITE_BALANCE_TYPE));
    write_current_setting_to_file(JPEG_QUALITY_CODE,               JPEG_QUALITY_VALUE_TYPE,               JPEG_QUALITY_TABLE_COUNT,               NFO_JPEG_QUALITY_FILE,               JPEG_QUALITY_TABLE_API_CODES,                    JPEG_QUALITY_TABLE_API_LIST,                    sizeof(JPEG_QUALITY_TYPE));
    write_current_setting_to_file(REMAIN_PHOTOS_CODE,              REMAIN_PHOTOS_VALUE_TYPE,              0,                                      NFO_REMAIN_PHOTOS_FILE,              NULL,                                            NULL,                                           sizeof(REMAIN_PHOTOS_TYPE));
    write_current_setting_to_file(LIVE_VEIW_QUALITY_CODE,          LIVE_VEIW_QUALITY_VALUE_TYPE,          LIVE_VEIW_QUALITY_TABLE_COUNT,          NFO_LIVE_VEIW_QUALITY_FILE,          LIVE_VEIW_QUALITY_TABLE_API_CODES,               LIVE_VEIW_QUALITY_TABLE_API_LIST,               sizeof(LIVE_VEIW_QUALITY_TYPE));
    write_current_setting_to_file(ZOOM_SCALE_CODE,                 ZOOM_SCALE_VALUE_TYPE,                 0,                                      NFO_ZOOM_SCALE_FILE,                 NULL,                                            NULL,                                           sizeof(ZOOM_SCALE_TYPE));
    write_current_setting_to_file(FOCUS_POSITION_SETTING_CODE,     FOCUS_POSITION_SETTING_VALUE_TYPE,     0,                                      NFO_FOCUS_POSITION_SETTING_FILE,     NULL,                                            NULL,                                           sizeof(FOCUS_POSITION_SETTING_TYPE));
    // clang-format on
}

void proc_set_setting() {
    // clang-format off
    new_setting_from_file(FOCUS_MODE_CODE,                 FOCUS_MODE_VALUE_TYPE,                 FOCUS_MODE_TABLE_COUNT,                 SET_FOCUS_MODE_FILE,                 FOCUS_MODE_TABLE_API_CODES,                      FOCUS_MODE_TABLE_API_LIST,                      sizeof(FOCUS_MODE_TYPE));
    new_setting_from_file(SHOOT_MODE_CODE,                 SHOOT_MODE_VALUE_TYPE,                 SHOOT_MODE_TABLE_COUNT,                 SET_SHOOT_MODE_FILE,                 SHOOT_MODE_TABLE_API_CODES,                      SHOOT_MODE_TABLE_API_LIST,                      sizeof(SHOOT_MODE_TYPE));
    new_setting_from_file(APERTURE_CODE,                   APERTURE_VALUE_TYPE,                   APERTURE_TABLE_COUNT,                   SET_APERTURE_FILE,                   APERTURE_TABLE_API_CODES,                        APERTURE_TABLE_API_LIST,                        sizeof(APERTURE_TYPE));
    new_setting_from_file(SHUTTER_SPEED_CODE,              SHUTTER_SPEED_VALUE_TYPE,              SHUTTER_SPEED_TABLE_COUNT,              SET_SHUTTER_SPEED_FILE,              SHUTTER_SPEED_TABLE_API_CODES,                   SHUTTER_SPEED_TABLE_API_LIST,                   sizeof(SHUTTER_SPEED_TYPE));
    new_setting_from_file(ISO_CODE,                        ISO_VALUE_TYPE,                        ISO_TABLE_COUNT,                        SET_ISO_FILE,                        ISO_TABLE_API_CODES,                             ISO_TABLE_API_LIST,                             sizeof(ISO_TYPE));
    new_setting_from_file(EXPOSURE_BIAS_COMPENSATION_CODE, EXPOSURE_BIAS_COMPENSATION_VALUE_TYPE, EXPOSURE_BIAS_COMPENSATION_TABLE_COUNT, SET_EXPOSURE_BIAS_COMPENSATION_FILE, EXPOSURE_BIAS_COMPENSATION_TYPE_TABLE_API_CODES, EXPOSURE_BIAS_COMPENSATION_TYPE_TABLE_API_LIST, sizeof(EXPOSURE_BIAS_COMPENSATION_TYPE));
    new_setting_from_file(WHITE_BALANCE_CODE,              WHITE_BALANCE_VALUE_TYPE,              WHITE_BALANCE_TABLE_COUNT,              SET_WHITE_BALANCE_FILE,              WHITE_BALANCE_TABLE_API_CODES,                   WHITE_BALANCE_TABLE_API_LIST,                   sizeof(WHITE_BALANCE_TYPE));
    new_setting_from_file(JPEG_QUALITY_CODE,               JPEG_QUALITY_VALUE_TYPE,               JPEG_QUALITY_TABLE_COUNT,               SET_JPEG_QUALITY_FILE,               JPEG_QUALITY_TABLE_API_CODES,                    JPEG_QUALITY_TABLE_API_LIST,                    sizeof(JPEG_QUALITY_TYPE));
    new_setting_from_file(LIVE_VEIW_QUALITY_CODE,          LIVE_VEIW_QUALITY_VALUE_TYPE,          LIVE_VEIW_QUALITY_TABLE_COUNT,          SET_LIVE_VEIW_QUALITY_FILE,          LIVE_VEIW_QUALITY_TABLE_API_CODES,               LIVE_VEIW_QUALITY_TABLE_API_LIST,               sizeof(LIVE_VEIW_QUALITY_TYPE));
    // clang-format on
}

long mtime() {
  struct timeval t;

  gettimeofday(&t, NULL);
  long mt = (long)t.tv_sec * 1000 + t.tv_usec / 1000;
  return mt;
}

int main(int argc, char** argv) {
    device_handle_handle = init_sdk__get_device_handle_handle();

    sleep(1);

    printf("Init complete\n");

    int i = 0;
    while (i++ < 150000) {
        proc_liveview();
        proc_dump_lists();
        proc_dump_current_settings();
        proc_set_setting();


        usleep(10000);
    }
    
    sdk_release();
}
