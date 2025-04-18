#include "lib_c.h"

#include "./../c++_wrapper/CrTypes.h"
#include "./../c++_wrapper/wrapper.h"
#include "./../classes_methods/classes_methods.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

char* get_live_veiw(void* device_handle_handle) {
    void*    image_info_handle = sdk_construct_image_info();
    long int info_result = sdk_get_live_view_image_info(device_handle_handle, image_info_handle);
    if (info_result) {
        fprintf(stderr, "GetLiveView FAILED 1      err:%ld\n", info_result);
        return NULL;
    }

    CrInt32u buffer_size = sdk_get_buffer_size_image_info(image_info_handle);
    if (buffer_size < 1) {
        fprintf(stderr, "GetLiveView FAILED 2      size:%d\n", buffer_size);
        return NULL;
    }

    void* image_data_block_handle = sdk_construct_image_data_block();
    if (!image_data_block_handle) {
        fprintf(stderr, "GetLiveView FAILED 3      allocation failed\n");
        return NULL;
    }

#define BUFF_SIZE_IMAGE_INFO 1048576 //  1024 * 1024
    static unsigned char image_buff[BUFF_SIZE_IMAGE_INFO];
    fprintf(stderr, "BUFF_SIZE_IMAGE_INFO = 1048576 <> %d = buffer_size\n", buffer_size);
    if (buffer_size > BUFF_SIZE_IMAGE_INFO) {
        perror("not enougth buffer for image\n");
    }

    memset(image_buff, 0, BUFF_SIZE_IMAGE_INFO);
    sdk_set_size_image_data_block(image_data_block_handle, buffer_size);
    sdk_set_data_image_data_block(image_data_block_handle, image_buff);

    long int live_view_result = sdk_get_live_view_image(device_handle_handle, image_data_block_handle);
    if (live_view_result) {
        if (live_view_result == 131095) {
            fprintf(stderr, "GetLiveView FAILED 4      Warning. GetLiveView Frame NotUpdate\n");
        } else if (live_view_result == 33539) {
            fprintf(stderr, "GetLiveView FAILED 4      Warning. GetLiveView Memory insufficient\n");
        } else {
            fprintf(stderr, "GetLiveView FAILED 4      allocation failed\n");
        }

        sdk_destruct_image_data_block(image_data_block_handle);
        return NULL;
    }

    if (sdk_get_size_image_data_block(image_data_block_handle) == 0) {
        fprintf(stderr, "GetLiveView FAILED 5      image size: 0\n");
        sdk_destruct_image_data_block(image_data_block_handle);
        return NULL;
    }

    size_t         path_max_size = 256;
    struct timeval tv;
    struct tm      tm_info;
    char           time_str[80];
    char           filename[128];
    char           cwd[path_max_size];
    char           full_path[path_max_size * 2];
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("getcwd() error");
        exit(EXIT_FAILURE);
    }

    gettimeofday(&tv, NULL);
    localtime_r(&tv.tv_sec, &tm_info);
    strftime(time_str, sizeof(time_str), "%Y_%m_%d_%H_%M_%S", &tm_info);
    int milliseconds = tv.tv_usec / 1000;
    snprintf(filename, sizeof(filename),
             "LiveVeiw_%s____%03d.JPG",
             time_str, milliseconds);
    snprintf(full_path, sizeof(full_path),
             "%s/%s", cwd, filename);

    FILE* file = fopen(full_path, "wb");
    if (file == NULL) {
        fprintf(stderr, "GetLiveView FAILED 6      can't open file:%s\n", full_path);
        sdk_destruct_image_data_block(image_data_block_handle);
        return NULL;
    }

    fwrite(sdk_get_image_data_image_data_block(image_data_block_handle), 1, buffer_size, file);
    fclose(file);

    fprintf(stdout, "GetLiveView SUCCESS\n");
    sdk_destruct_image_data_block(image_data_block_handle);

    char* return_path = malloc(sizeof(char) * strlen(full_path) + 1);
    strcpy(return_path, full_path);
    return return_path;
}

// will allocate memory for iso_array
unsigned int* get_iso_array(void* device_handle_handle, int* iso_writable, unsigned int* iso_current, unsigned int* iso_array_len, long int* iso_get_result) {
    long     nprop = 0;
    void*    iso_device_property_handle = NULL;
    long     codes = 260U;
    long int get_prop_result = sdk_get_select_device_properties(device_handle_handle, 1, &codes, &iso_device_property_handle, &nprop);
    if (get_prop_result) {
        fprintf(stderr, "Get_iso_array FAILED 1      err:%ld\n", get_prop_result);
        *iso_get_result = get_prop_result;
        return NULL;
    }
    printf("iso_device_property_handle: %p\n", iso_device_property_handle);

    unsigned long size = sdk_get_value_size_device_property(iso_device_property_handle);
    int           number_values = 0;
    number_values = size / sizeof(unsigned int);
    *iso_writable = sdk_is_set_enable_device_property(iso_device_property_handle);
    *iso_current = sdk_get_current_value_device_property(iso_device_property_handle);
    if (number_values <= 0) {
        printf("value size: %ld\n", size);
        *iso_get_result = -1;
        return NULL;
    }

    unsigned int* iso_array_tmp = malloc(sizeof(unsigned int) * number_values);
    if (!iso_array_tmp) {
        *iso_get_result = -2;
        return NULL;
    }

    *iso_array_len = number_values;
    unsigned int const* source = (unsigned int const*)sdk_get_values_device_property(iso_device_property_handle);
    for (int i = 0; i < number_values; ++i, ++source) {
        // printf("%d\n", *source);
        memcpy(&iso_array_tmp[i], source, sizeof(unsigned int));
    }

    return iso_array_tmp;
}

unsigned int* get_property_array(long property_code, void* device_handle_handle, int* abstract_writable, unsigned int* abstract_current, unsigned int* abstract_array_len, long int* abstract_get_result) {
    long     nprop = 0;
    void*    abstract_device_property_handle = NULL;
    long int get_prop_result = sdk_get_select_device_properties(device_handle_handle, 1, &property_code, &abstract_device_property_handle, &nprop);
    if (get_prop_result) {
        fprintf(stderr, "Get_abstract_array FAILED 1      err:%ld\n", get_prop_result);
        *abstract_get_result = get_prop_result;
        return NULL;
    }
    //printf("abstract_device_property_handle: %p\n", abstract_device_property_handle);

    unsigned long size = sdk_get_value_size_device_property(abstract_device_property_handle);
    int           number_values = 0;
    number_values = size / sizeof(unsigned int);
    *abstract_writable = sdk_is_set_enable_device_property(abstract_device_property_handle);
    *abstract_current = sdk_get_current_value_device_property(abstract_device_property_handle);
    if (number_values <= 0) {
        printf("value size: %ld\n", size);
        *abstract_get_result = -1;
        return NULL;
    }

    unsigned int* abstract_array_tmp = malloc(sizeof(unsigned int) * number_values);
    if (!abstract_array_tmp) {
        *abstract_get_result = -2;
        return NULL;
    }

    *abstract_array_len = number_values;
    unsigned int const* source = (unsigned int const*)sdk_get_values_device_property(abstract_device_property_handle);
    for (int i = 0; i < number_values; ++i, ++source) {
        // printf("%d\n", *source);
        memcpy(&abstract_array_tmp[i], source, sizeof(unsigned int));
    }

    return abstract_array_tmp;
}

int get_current_value_property(long property_code, void* device_handle_handle, unsigned int* abstract_current) {
    long     nprop = 0;
    void*    abstract_device_property_handle = NULL;
    long int get_prop_result = sdk_get_select_device_properties(device_handle_handle, 1, &property_code, &abstract_device_property_handle, &nprop);
    if (get_prop_result) {
        fprintf(stderr, "Get_abstract_array FAILED 1      err:%ld\n", get_prop_result);
        return -1;
    }
    //printf("abstract_device_property_handle: %p\n", abstract_device_property_handle);

    *abstract_current = sdk_get_current_value_device_property(abstract_device_property_handle);
    return 0;
}

long set_value_property(long property_code, void* device_handle_handle, unsigned int value, unsigned int value_type) {
    long     nprop = 0;
    void*    abstract_device_property_handle = NULL;
    long int get_prop_result = sdk_get_select_device_properties(device_handle_handle, 1, &property_code, &abstract_device_property_handle, &nprop);
    if (get_prop_result) {
        fprintf(stderr, "Set value FAILED -1      check enable failed: err:%ld\n", get_prop_result);
        return -3;
    }

    if (sdk_is_set_enable_device_property(abstract_device_property_handle) == 1) {
        fprintf(stderr, "Set value FAILED 0      not enable\n");
        return -2;
    }

    void* prop = sdk_construct_device_property();
    if (!prop) {
        fprintf(stderr, "Set value FAILED 1      allocation failed\n");
        return -1;
    }

    sdk_set_code_device_property(prop, property_code);
    sdk_set_current_value_device_property(prop, value);
    sdk_set_value_type_device_property(prop, value_type);
    long set_property_result = sdk_set_device_property(device_handle_handle, prop);
    if (set_property_result) {
        fprintf(stderr, "Set value FAILED 2      err:%ld\n", set_property_result);
        return set_property_result;
    }
    return 0;
}

void* init_sdk__get_device_handle_handle() {
    if (sdk_init()) {
        perror("SDK initialization failed\n");
        exit(999);
    }
    void*    enum_handle = NULL;
    long int enum_result = sdk_enum_camera_object(&enum_handle);
    if (enum_result) {
        perror("Failed to enumerate cameras\n");
        printf("error: %ld\n", enum_result);
        exit(EXIT_FAILURE);
    }

    void* camera_info = sdk_enum_camera_object_get_camera_object_info(enum_handle, 0);
    if (!camera_info) {
        printf("Failed to get info for camera\n");
        sdk_release();
        exit(EXIT_FAILURE);
    }

    void*    device_handle_handle = NULL;
    long int connect_result = sdk_connect(camera_info, NULL, &device_handle_handle);
    if (connect_result) {
        perror("Failed to connect to camera\n");
        printf("error: %ld\n", connect_result);
        exit(EXIT_FAILURE);
    }



    sleep(1);

    set_value_property(377U, device_handle_handle, 2U, 8193U);



    return device_handle_handle;
}

char* new_tmp_file(const char* prefix) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    long long milliseconds = (long long)tv.tv_sec * 1000LL + tv.tv_usec / 1000;

    size_t prefix_len = strlen(prefix);
    size_t filename_len = prefix_len + 2 + 20 + 1; // "__" + 20 digits + null terminator
    char*  filename = (char*)malloc(filename_len);
    if (filename == NULL) {
        return NULL;
    }

    int written = snprintf(filename, filename_len, "%s__%lld", prefix, milliseconds);
    if (written < 0 || (size_t)written >= filename_len) {
        free(filename);
        return NULL;
    }

    FILE* fp = fopen(filename, "w");
    if (fp == NULL) {
        free(filename);
        return NULL;
    }
    fclose(fp);

    return filename;
}

int get_live_veiw_to_file(void* device_handle_handle, char* filename) {

    static unsigned char image_buff[BUFF_SIZE_IMAGE_INFO];
    memset(image_buff, 0, BUFF_SIZE_IMAGE_INFO);

    void*    image_info_handle = sdk_construct_image_info();
    long int info_result = sdk_get_live_view_image_info(device_handle_handle, image_info_handle);
    if (info_result) {
        fprintf(stderr, "GetLiveView FAILED 1      err:%ld\n", info_result);
        return -1;
    }

    CrInt32u buffer_size = sdk_get_buffer_size_image_info(image_info_handle);
    if (buffer_size < 1) {
        fprintf(stderr, "GetLiveView FAILED 2      size:%d\n", buffer_size);
        sdk_destruct_image_info(image_info_handle);
        return -2;
    }

    void* image_data_block_handle = sdk_construct_image_data_block();
    if (!image_data_block_handle) {
        fprintf(stderr, "GetLiveView FAILED 3      allocation failed\n");
        sdk_destruct_image_info(image_info_handle);
        return -3;
    }

    //fprintf(stderr, "BUFF_SIZE_IMAGE_INFO = 1048576 <> %d = buffer_size\n", buffer_size);
    if (buffer_size > BUFF_SIZE_IMAGE_INFO) {
        perror("not enougth buffer for image\n");
        sdk_destruct_image_info(image_info_handle);
        sdk_destruct_image_data_block(image_data_block_handle);
        return -4;
    }

    sdk_set_size_image_data_block(image_data_block_handle, buffer_size);
    sdk_set_data_image_data_block(image_data_block_handle, image_buff);

#define CrWarning_Frame_NotUpdated  131095
#define CrError_Memory_Insufficient 33539

    long int live_view_result = sdk_get_live_view_image(device_handle_handle, image_data_block_handle);
    if (live_view_result) {
        if (live_view_result == CrWarning_Frame_NotUpdated) {
            fprintf(stderr, "GetLiveView FAILED 4      Warning. GetLiveView Frame NotUpdate\n");
        } else if (live_view_result == CrError_Memory_Insufficient) {
            fprintf(stderr, "GetLiveView FAILED 4      Warning. GetLiveView Memory insufficient\n");
        } else {
            fprintf(stderr, "GetLiveView FAILED 4      allocation failed\n");
        }

        sdk_destruct_image_data_block(image_data_block_handle);
        return -5;
    }

    if (sdk_get_size_image_data_block(image_data_block_handle) == 0) {
        fprintf(stderr, "GetLiveView FAILED 5      image size: 0\n");
        sdk_destruct_image_info(image_info_handle);
        sdk_destruct_image_data_block(image_data_block_handle);
        return -6;
    }

    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        fprintf(stderr, "GetLiveView FAILED 6      can't open file:%s\n", filename);
        sdk_destruct_image_info(image_info_handle);
        sdk_destruct_image_data_block(image_data_block_handle);
        return -7;
    }

    fwrite(sdk_get_image_data_image_data_block(image_data_block_handle), 1, buffer_size, file);
    fclose(file);
    sdk_destruct_image_info(image_info_handle);
    sdk_destruct_image_data_block(image_data_block_handle);

    return buffer_size;
}