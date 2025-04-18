#ifndef LIB_C_C
#define LIB_C_C

//#define ISO_CODE 260U
// #define ISO_CODE 261U
// #define ISO_VALUE_TYPE 8195U

// #define FOCUS_MODE_CODE 265U
// #define FOCUS_MODE_TYPE 8194U

// #define APERTURE_CODE 256U
// #define APERTURE_TYPE 8194U

// #define WHITE_BALANCE_CODE 264U
// #define WHITE_BALANCE_TYPE 8194U

// #define JPEG_QUALITY_CODE 263U
// #define JPEG_QUALITY_TYPE 8194U

// #define FILE_TYPE_CODE 262U
// #define FILE_TYPE_TYPE 8194U

// #define EXSPOSURE_CORRECTION_CODE 257U
// #define EXSPOSURE_CORRECTION_TYPE 8194U

// #define SHUTTER_SPEED_CODE 259U
// #define SHUTTER_SPEED_TYPE 8195U

void* init_sdk__get_device_handle_handle();

char* get_live_veiw(void* device_handle_handle);

unsigned int* get_iso_array(void* device_handle_handle, int* iso_writable, unsigned int* iso_current, unsigned int* iso_array_len, long int* iso_get_result);

unsigned int* get_property_array(long property_code, void* device_handle_handle, int* abstract_writable, unsigned int* abstract_current, unsigned int* abstract_array_len, long int* abstract_get_result);
int           get_current_value_property(long property_code, void* device_handle_handle, unsigned int* abstract_current);
long          set_value_property(long property_code, void* device_handle_handle, unsigned int value, unsigned int value_type);

// get current value, set value

char* new_tmp_file(const char* prefix);

int get_live_veiw_to_file(void* device_handle_handle, char* filename);

#endif // LIB_C_C