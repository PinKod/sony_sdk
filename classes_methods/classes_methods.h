#ifndef CLASSES_METHODS_H
#define CLASSES_METHODS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "./../c++_wrapper/CrTypes.h"

//wrapper for class ICrCameraObjectInfo
int sdk_enum_camera_object_get_count(void* enum_camera_object_handle);
void* sdk_enum_camera_object_get_camera_object_info(void* enum_camera_object_handle, int index);
void sdk_enum_camera_object_release(void* enum_camera_object_handle);
//wrapper for class ICrCameraObjectInfo


//wrapper for class ICrCameraObjectInfo
void sdk_camera_object_info_release(void* camera_object_info_handle);
char* sdk_camera_object_info_get_name(void* camera_object_info_handle);
int sdk_camera_object_info_get_name_size(void* camera_object_info_handle);
char* sdk_camera_object_info_get_model(void* camera_object_info_handle);
int sdk_camera_object_info_get_model_size(void* camera_object_info_handle);
int sdk_camera_object_info_get_usb_pid(void* camera_object_info_handle);
char* sdk_camera_object_info_get_id(void* camera_object_info_handle);
int sdk_camera_object_info_get_id_size(void* camera_object_info_handle);
int sdk_camera_object_info_get_id_type(void* camera_object_info_handle);
int sdk_camera_object_info_get_connection_status(void* camera_object_info_handle);
char* sdk_camera_object_info_get_connection_type_name(void* camera_object_info_handle);
char* sdk_camera_object_info_get_adaptor_name(void* camera_object_info_handle);
char* sdk_camera_object_info_get_guid(void* camera_object_info_handle);
char* sdk_camera_object_info_get_pairing_necessity(void* camera_object_info_handle);
int sdk_camera_object_info_get_authentification_state(void* camera_object_info_handle);
int sdk_camera_object_info_get_ssh_support(void* camera_object_info_handle);
//wrapper for class ICrCameraObjectInfo


//wrapper for class SCRSDK_API CrDeviceProperty
void* sdk_construct_device_property();
int sdk_is_get_enable_device_property(void* device_property_handle);
int sdk_is_set_enable_device_property(void* device_property_handle);
void sdk_set_code_device_property(void* device_property_handle, long int code);
long int sdk_get_code_device_property(void* device_property_handle);
void sdk_set_value_type_device_property(void* device_property_handle, long int type);
long int sdk_get_value_type_device_property(void* device_property_handle);
void sdk_set_property_enable_flag_device_property(void* device_property_handle, int flag);
int sdk_get_property_enable_flag_device_property(void* device_property_handle);
void sdk_set_property_variable_flag_device_property(void* device_property_handle, int flag);
int sdk_get_property_variable_flag_device_property(void* device_property_handle);
void sdk_set_current_value_device_property(void* device_property_handle, unsigned long long value);
unsigned long long sdk_get_current_value_device_property(void* device_property_handle);
void sdk_set_current_str_device_property(void* device_property_handle, unsigned short* str);
unsigned short* sdk_get_current_str_device_property(void* device_property_handle);
void sdk_set_value_size_device_property(void* device_property_handle, unsigned long size);
unsigned long sdk_get_value_size_device_property(void* device_property_handle);
void sdk_set_values_device_property(void* device_property_handle, unsigned char* values);
unsigned char* sdk_get_values_device_property(void* device_property_handle);
void sdk_set_set_value_size_device_property(void* device_property_handle, unsigned long size);
unsigned long sdk_get_set_value_size_device_property(void* device_property_handle);
void sdk_set_set_values_device_property(void* device_property_handle, unsigned char* values);
unsigned char* sdk_get_set_values_device_property(void* device_property_handle);
//wrapper for class SCRSDK_API CrDeviceProperty


//wrapper for class SCRSDK_API CrImageDataBlock
void* sdk_construct_image_data_block();
void sdk_destruct_image_data_block(void* image_data_block_handle);
unsigned long sdk_get_frame_no_image_data_block(void* image_data_block_handle);
void sdk_set_size_image_data_block(void* image_data_block_handle, CrInt32u size);
unsigned long sdk_get_size_image_data_block(void* image_data_block_handle);
void sdk_set_data_image_data_block(void* image_data_block_handle, unsigned char* data);
unsigned char* sdk_get_image_data_image_data_block(void* image_data_block_handle);
CrInt32u sdk_get_image_size_image_data_block(void* image_data_block_handle);
unsigned long sdk_get_time_code_image_data_block(void* image_data_block_handle);
//wrapper for class SCRSDK_API CrImageDataBlock



//wrapper for class SCRSDK_API CrImageInfo
void* sdk_construct_image_info();
void sdk_destruct_image_info(void* image_info_handle);
CrInt32u sdk_get_buffer_size_image_info(void* image_info_handle);
//wrapper for class SCRSDK_API CrImageInfo



//wrapper for class SCRSDK_API CrOSDImageMetaInfo
void* sdk_construct_osd_image_meta_info();
void sdk_destruct_osd_image_meta_info(void* meta_info_handle);
void sdk_set_is_lv_pos_exist(void* meta_info_handle, int value);
int sdk_get_is_lv_pos_exist(void* meta_info_handle);
void sdk_set_osd_width(void* meta_info_handle, unsigned long value);
unsigned long sdk_get_osd_width(void* meta_info_handle);
void sdk_set_osd_height(void* meta_info_handle, unsigned long value);
unsigned long sdk_get_osd_height(void* meta_info_handle);
void sdk_set_lv_pos_x(void* meta_info_handle, unsigned long value);
unsigned long sdk_get_lv_pos_x(void* meta_info_handle);
void sdk_set_lv_pos_y(void* meta_info_handle, unsigned long value);
unsigned long sdk_get_lv_pos_y(void* meta_info_handle);
void sdk_set_lv_width(void* meta_info_handle, unsigned long value);
unsigned long sdk_get_lv_width(void* meta_info_handle);
void sdk_set_lv_height(void* meta_info_handle, unsigned long value);
unsigned long sdk_get_lv_height(void* meta_info_handle);
void sdk_set_degree(void* meta_info_handle, unsigned long value);
unsigned long sdk_get_degree(void* meta_info_handle);
//wrapper for class SCRSDK_API CrOSDImageMetaInfo



//wrapper for class SCRSDK_API CrOSDImageDataBlock
void* sdk_construct_osd_image_data_block();
void sdk_destruct_osd_image_data_block(void* image_data_block_handle);
unsigned long sdk_get_frame_no_osd(void* image_data_block_handle);
unsigned long sdk_get_image_size_osd(void* image_data_block_handle);
unsigned char* sdk_get_image_data_osd(void* image_data_block_handle);
void sdk_set_image_data_osd(void* image_data_block_handle, unsigned char* data);
void* sdk_get_meta_info_osd(void* image_data_block_handle);
//wrapper for class SCRSDK_API CrOSDImageDataBlock



#ifdef __cplusplus
}
#endif












#endif //CLASSES_METHODS_H
