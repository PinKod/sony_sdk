#ifndef UTILS_H
#define UTILS_H


#ifdef __cplusplus
extern "C" {
#endif

void sdk_camera_device_set_save_info(void* device_handle_handle);
void sdk_camera_device_set_iso(void* device_handle_handle, long long int iso, void* camera_object_info_handle);
void sdk_save_image(void* image_data_block_handle);
void sdk_set_device_propery_time(void* device_handle_handle, void* device_property_handle);
void sdk_capture_image(void* device_handle_handle, char* meta_info);
int sdk_change_saving_destination_to_camera(void* device_handle_handle);
int sdk_change_saving_destination_to_host_pc(void* device_handle_handle);


char* just_get_live_view(void* device_handle_handle);






long long get_device_property_focus(void* device_properties_handle);

#ifdef __cplusplus
}
#endif



#endif // UTILS_H