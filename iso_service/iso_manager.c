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
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>




#define FILE_LIST "iso.list"
#define FILE_NFO "iso.nfo"
#define FILE_SET "iso.set"



void check_file_set(void* device_handle_handle) {
    FILE* file = fopen(FILE_SET, "r");
    if(!file) return;

    unsigned int new_iso = 0;
    int res = fscanf(file, "%u", &new_iso);
    if(res != 1) {
        return;
    }
    fclose(file);

    int iso_writable = -1;
    unsigned int iso_current = 0;
    unsigned int iso_array_len = 0;
    long int iso_get_result = 0;
    unsigned int *iso_array = get_property_array(ISO_CODE, device_handle_handle, &iso_writable, &iso_current, &iso_array_len, &iso_get_result);
    if(iso_get_result) {
        printf("Failed to get iso array\n");
        printf("error: %ld\n", iso_get_result);
        fclose(file);
        return;
    }

    int flag = 0;
    for(unsigned int i = 0; i < iso_array_len; i++) {
        if(iso_array[i] == new_iso) {
            flag = 1;
        }
    }
    if(flag == 0) {
        printf("Invalid iso number: %d\n", new_iso);
        fclose(file);
    }

    long set_res = set_value_property(ISO_CODE, device_handle_handle, new_iso, ISO_VALUE_TYPE);
    if(set_res) {
        printf("error ocured, didt set new iso value\n");
    }
}   

void update_file_nfo(void* device_handle_handle) {
    char* tmp_file = new_tmp_file(FILE_NFO);
    if(!tmp_file) return;
    
    
    FILE* file = NULL;
    file = fopen(tmp_file, "w");
    if(!file) {
        free(tmp_file);
        return;
    }


    unsigned int iso_current = 0;
    int res = get_current_value_property(ISO_CODE, device_handle_handle, &iso_current);
    if(res) {
        fprintf(stderr, "failed update current iso\n");
        remove(tmp_file);
        free(tmp_file);
        return;
    }

    fclose(file);
    if (rename(tmp_file, FILE_NFO) != 0) {
        perror("Failed to rename file");
        remove(tmp_file);
    }


    free(tmp_file);
}

void update_file_list(void* device_handle_handle) {
    char* tmp_file = new_tmp_file(FILE_LIST);
    if(!tmp_file) return;
    
    
    FILE* file = NULL;
    file = fopen(tmp_file, "w");
    if(!file) {
        free(tmp_file);
        return;
    }
    

    int iso_writable = -1;
    unsigned int iso_current = 0;
    unsigned int iso_array_len = 0;
    long int iso_get_result = 0;
    unsigned int *iso_array = get_property_array(ISO_CODE, device_handle_handle, &iso_writable, &iso_current, &iso_array_len, &iso_get_result);
    if(iso_get_result) {
        printf("Failed to get iso array\n");
        printf("error: %ld\n", iso_get_result);
        remove(tmp_file);
        free(tmp_file);
        return;
    }


    for(unsigned int i = 0; i < iso_array_len; i++) {
        fprintf(file, "%d\n", iso_array[i]);
    }
    fclose(file);

    
    if (rename(tmp_file, FILE_LIST) != 0) {
        perror("Failed to rename file");
        remove(tmp_file);
    }

    free(tmp_file);
}


void update_iso(void* device_handle_handle) {
    for(int i = 0; i < 30; i++) {
        sleep(1);
        update_file_list(device_handle_handle);
        update_file_nfo(device_handle_handle);
        check_file_set(device_handle_handle);
    }
}


int main() {
    void* device_handle_handle = init_sdk__get_device_handle_handle();
    
    
    
    // int iso_writable = -1;
    // unsigned int iso_current = 0;
    // unsigned int iso_array_len = 0;
    // long int iso_get_result = 0;
    // // unsigned int *iso_array = get_iso_array(device_handle_handle, &iso_writable, &iso_current, &iso_array_len, &iso_get_result);
    // unsigned int *iso_array = get_property_array(ISO_CODE, device_handle_handle, &iso_writable, &iso_current, &iso_array_len, &iso_get_result);
    // printf("iso_writable: %d\niso_current: %d\niso_array_len: %d\n", iso_writable, iso_current, iso_array_len);
    // if(iso_get_result) {
    //     printf("Failed to get iso array\n");
    //     printf("error: %ld\n", iso_get_result);
    //     exit(EXIT_FAILURE);
    // }
    // for(unsigned int i = 0; i < iso_array_len; i++) {
    //     printf("%2.0d)iso:%d\n", i + 1, iso_array[i]);
    // }

    // unsigned int current_iso = 0;
    // if(get_current_value_property(ISO_CODE, device_handle_handle, &current_iso) == 0) {
    //     printf("current iso value: %d\n", current_iso);
    // }
    // else {
    //     printf("get current value property error\n");
    // }

    // for(unsigned int i = 0; i < iso_array_len; i++) {
    //     sleep(1);
    //     printf("%2.d)set iso: %d\n", i + 1, iso_array[i]);
    //     set_value_property(ISO_CODE, device_handle_handle, iso_array[i], ISO_VALUE_TYPE);
    // }


    update_iso(device_handle_handle);



















    if (sdk_release()) {
        perror("SDK release failed\n");
        exit(EXIT_FAILURE);
    }
}

