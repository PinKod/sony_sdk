#include "./wrapper.h"

#include "./CameraRemote_SDK.h"
#include "./CrError.h"
#include "./CrTypes.h"
#include "./callback.hpp"

#include <stdio.h>
// #include <iostream>
// #include <filesystem>
// #include <chrono>
// #include <ctime>
// #include <iomanip>
// #include <sstream>
// #include <string>


long int sdk_init() {
    auto init_success = SCRSDK::Init();
    if (!init_success) {
        fprintf(stderr, "Failed to initialize Remote SDK. Terminating.\n");
        SCRSDK::Release();
        return 1;
    }
    return 0;
}

long int sdk_release() {
    auto release_success = SCRSDK::Release();
    if (!release_success) {
        fprintf(stderr, "Failed to release Remote SDK. Terminating.\n");
        return 1;
    }
    return 0;
}

long int sdk_enum_camera_object(void** enum_camera_object_handle) {
    SCRSDK::ICrEnumCameraObjectInfo* camera_list = nullptr;
    auto res = SCRSDK::EnumCameraObjects(&camera_list);
    printf("res:%d\n", res);
    printf("list:%p\n", (void*)camera_list);
    *enum_camera_object_handle = camera_list;
    return res;
}

//ICrCameraObjectInfo* CreateCameraObjectInfo(CrChar* name, CrChar *model, CrInt16 usbPid, CrInt32u idType, CrInt32u idSize, CrInt8u* id, CrChar *connectTypeName, CrChar *adaptorName, CrChar *pairingNecessity, CrInt32u sshSupport = 0);
void* sdk_create_camera_object_info(char* name, char *model, int usbPid, int idType, long int idSize, unsigned char* id, char *connectTypeName, char *adaptorName, char *pairingNecessity) {
    return (void*) SCRSDK::CreateCameraObjectInfo(name, model, usbPid, idType, idSize, id, connectTypeName, adaptorName, pairingNecessity);
}

//CrError CreateCameraObjectInfoUSBConnection(ICrCameraObjectInfo** pCameraObjectInfo, CrCameraDeviceModelList model, CrInt8u* usbSerialNumber);
long int sdk_create_camera_object_usb_connection(void** camera_object_info_handle, int model, unsigned short int* usb_serial_number) {
    return (long int) SCRSDK::CreateCameraObjectInfoUSBConnection((SCRSDK::ICrCameraObjectInfo**)camera_object_info_handle, (SCRSDK::CrCameraDeviceModelList)model, (CrInt8u*)usb_serial_number);
}

//CrError CreateCameraObjectInfoEthernetConnection(ICrCameraObjectInfo** pCameraObjectInfo, CrCameraDeviceModelList model, CrInt32u ipAddress, CrInt8u* macAddress, CrInt32u sshSupport = 0);
long int sdk_create_camera_object_ethernet_connection(void** camera_object_info_handle, unsigned short int* usb_serial_number) {
    return -1;
}

//CrError EditSDKInfo(CrInt16u infotype);
long int sdk_edit_sdk_info(int infotype) {
    return (long int) SCRSDK::EditSDKInfo((CrInt16u)infotype);
}

//CrError GetFingerprint(/*in*/ ICrCameraObjectInfo* pCameraObjectInfo, /*out*/ char* fingerprint, /*out*/ CrInt32u* fingerprintSize);
long int sdk_get_fingerprint(void* camera_object_info_handle, char* fingerprint, long int* fingerprint_size) {
    return (long int) SCRSDK::GetFingerprint((SCRSDK::ICrCameraObjectInfo*)camera_object_info_handle, fingerprint, (CrInt32u*)fingerprint_size);
}

//CrError Connect(/*in*/ ICrCameraObjectInfo* pCameraObjectInfo, /*in*/  IDeviceCallback* callback, /*out*/ CrDeviceHandle* deviceHandle, /*in*/ CrSdkControlMode openMode = CrSdkControlMode_Remote, /*in*/ CrReconnectingSet reconnect = CrReconnecting_ON, const char* userId = 0, const char* userPassword = 0, const char* fingerprint = 0, CrInt32u fingerprintSize = 0);
long int sdk_connect(void* camera_object_info_handle, void* device_callback_handle, void* device_handle_handle) {
    return (long int) SCRSDK::Connect((SCRSDK::ICrCameraObjectInfo*)camera_object_info_handle, new SCRSDK::IDeviceCallback(), (SCRSDK::CrDeviceHandle*)device_handle_handle);
}

//CrError Disconnect(/*in*/ CrDeviceHandle deviceHandle);
long int sdk_disconnect(void* device_handle_handle) {
    return (long int) SCRSDK::Disconnect((SCRSDK::CrDeviceHandle)device_handle_handle);
}

//CrError ReleaseDevice(/*in*/ CrDeviceHandle deviceHandle);
long int sdk_release_device(void* device_handle_handle) {
    return (long int) SCRSDK::ReleaseDevice((SCRSDK::CrDeviceHandle)device_handle_handle);
}

//CrError GetDeviceProperties(/*in*/ CrDeviceHandle deviceHandle, /*out*/CrDeviceProperty** properties, /*out*/ CrInt32* numOfProperties);
long int sdk_get_device_properties(void* device_handle_handle, void** device_property_handle, long int* number_of_properties) {
    return (long int) SCRSDK::GetDeviceProperties(reinterpret_cast<SCRSDK::CrDeviceHandle>(device_handle_handle), (SCRSDK::CrDeviceProperty**)(device_property_handle), reinterpret_cast<CrInt32*>(number_of_properties));
}

//CrError GetSelectDeviceProperties(/*in*/ CrDeviceHandle deviceHandle, /*in*/ CrInt32u numOfCodes, /*in*/ CrInt32u* codes, /*out*/CrDeviceProperty** properties, /*out*/ CrInt32* numOfProperties);
long int sdk_get_select_device_properties(void* device_handle_handle, long int number_of_codes, long int* codes, void** device_property_handle, long int* number_of_properties) {
    return (long int) SCRSDK::GetSelectDeviceProperties( reinterpret_cast<SCRSDK::CrDeviceHandle>(device_handle_handle), (CrInt32u)number_of_codes, (CrInt32u*)codes, (SCRSDK::CrDeviceProperty**)device_property_handle, (CrInt32*)number_of_properties);
}

//CrError ReleaseDeviceProperties(/*in*/ CrDeviceHandle deviceHandle, /*in*/CrDeviceProperty* properties);
long int sdk_release_device_properties(void* device_handle_handle, void* device_property_handle) {
    return (long int) SCRSDK::ReleaseDeviceProperties((SCRSDK::CrDeviceHandle)device_handle_handle, (SCRSDK::CrDeviceProperty*)device_property_handle);
}

//CrError SetDeviceProperty(/*in*/ CrDeviceHandle deviceHandle, /*in*/CrDeviceProperty* pProperty);
long int sdk_set_device_property(void* device_handle_handle, void* device_property_handle) {
    return (long int) SCRSDK::SetDeviceProperty((SCRSDK::CrDeviceHandle)device_handle_handle, (SCRSDK::CrDeviceProperty*)device_property_handle);
}

//CrError SendCommand(/*in*/ CrDeviceHandle deviceHandle, /*in*/ CrInt32u commandId, /*in*/CrCommandParam commandParam);
long int sdk_send_command(void* device_handle_handle, long int command_id, long int command_param) {
    return (long int) SCRSDK::SendCommand((SCRSDK::CrDeviceHandle)device_handle_handle, (CrInt32u)command_id, (SCRSDK::CrCommandParam)command_param);
}

//CrError GetLiveViewImage(/*in*/ CrDeviceHandle deviceHandle, /*in*/CrImageDataBlock*imageData);
long int sdk_get_live_view_image(void* device_handle_handle, void* image_data_block_handle) {
    return (long int) SCRSDK::GetLiveViewImage(reinterpret_cast<SCRSDK::CrDeviceHandle>(device_handle_handle), (SCRSDK::CrImageDataBlock*)image_data_block_handle);
}

//CrError GetLiveViewImageInfo(/*in*/ CrDeviceHandle deviceHandle, /*out*/ CrImageInfo* info);
long int sdk_get_live_view_image_info(void* device_handle_handle, void* image_info_handle) {
    return (long int) SCRSDK::GetLiveViewImageInfo(reinterpret_cast<SCRSDK::CrDeviceHandle>(device_handle_handle), reinterpret_cast<SCRSDK::CrImageInfo*>(image_info_handle));
}

//CrError GetLiveViewProperties(/*in*/ CrDeviceHandle deviceHandle, /*out*/CrLiveViewProperty** properties, /*out*/ CrInt32* numOfProperties);
long int sdk_get_live_view_properties(void* device_handle_handle, void** deummy_data, long long int* dummy_int) {
    return (long int) SCRSDK::GetLiveViewProperties(reinterpret_cast<SCRSDK::CrDeviceHandle>(device_handle_handle), reinterpret_cast<SCRSDK::CrLiveViewProperty**>(deummy_data), reinterpret_cast<CrInt32*>(dummy_int));
}

//CrError GetSelectLiveViewProperties(/*in*/ CrDeviceHandle deviceHandle, /*in*/ CrInt32u numOfCodes, /*in*/ CrInt32u* codes, /*out*/CrLiveViewProperty** properties, /*out*/ CrInt32* numOfProperties);
long int sdk_get_select_live_view_properties(void* device_handle_handle, long int number_of_codes, long int* codes, void** deummy_data, long int* number_of_properties) {
    return (long int) SCRSDK::GetSelectLiveViewProperties((SCRSDK::CrDeviceHandle)device_handle_handle, (CrInt32u)number_of_codes, (CrInt32u*)codes, (SCRSDK::CrLiveViewProperty**)deummy_data, (CrInt32*)number_of_properties);
}

//CrError ReleaseLiveViewProperties(/*in*/ CrDeviceHandle deviceHandle, /*in*/CrLiveViewProperty* properties);
void sdk_release_live_view_properties(void* device_handle_handle, void* deummy_data) {
    SCRSDK::ReleaseLiveViewProperties((SCRSDK::CrDeviceHandle)device_handle_handle, (SCRSDK::CrLiveViewProperty*)deummy_data);
}

//CrError GetDeviceSetting(/*in*/ CrDeviceHandle deviceHandle, /*in*/ CrInt32u key, /*out*/ CrInt32u* value);
long int sdk_get_device_setting(void* device_handle_handle, long int key, long int* value) {
    return (long int) SCRSDK::GetDeviceSetting((SCRSDK::CrDeviceHandle)device_handle_handle, (CrInt32u)key, (CrInt32u*)value);
}

//CrError SetDeviceSetting(/*in*/ CrDeviceHandle deviceHandle, /*in*/ CrInt32u key, /*out*/ CrInt32u value);
long int sdk_set_device_setting(void* device_handle_handle, long int key, long int value) {
    return (long int) SCRSDK::SetDeviceSetting((SCRSDK::CrDeviceHandle)device_handle_handle, (CrInt32u)key, (CrInt32u)value);
}

//CrError SetSaveInfo(/*in*/ CrDeviceHandle deviceHandle, /*in*/ CrChar *path, CrChar* prefix, CrInt32 no);
long int sdk_set_save_info(void* device_handle_handle, char* path, char* prefix, long int no) {
    return (long int) SCRSDK::SetSaveInfo((SCRSDK::CrDeviceHandle)device_handle_handle, path, prefix, (CrInt32)no);
}

//CrInt32u GetSDKVersion();
long int sdk_get_sdk_version() {
    return (long int) SCRSDK::GetSDKVersion();
}

//CrInt32u GetSDKSerial();
long int sdk_get_sdk_serial() {
    return (long int) SCRSDK::GetSDKSerial();
}

//CrError GetDateFolderList(/*in*/ CrDeviceHandle deviceHandle, /*out*/ CrMtpFolderInfo** folders, /*out*/ CrInt32u* numOfFolders);
long int sdk_get_date_folder_list(void* device_handle_handle, void** folder_info_handle, long int* number_of_folders) {
    return (long int) SCRSDK::GetDateFolderList((SCRSDK::CrDeviceHandle)device_handle_handle, (SCRSDK::CrMtpFolderInfo**)folder_info_handle, (CrInt32u*)number_of_folders);
}

//CrError GetContentsHandleList(/*in*/ CrDeviceHandle deviceHandle, /*in*/CrFolderHandle folderHandle, /*out*/ CrContentHandle** contentsHandles, /*out*/ CrInt32u* numOfContents);
long int sdk_get_contents_handle_list(void* device_handle_handle, void* folder_handle, void** contents_handle, long int* number_of_contents) {
    return (long int) SCRSDK::GetContentsHandleList((SCRSDK::CrDeviceHandle)device_handle_handle, *(SCRSDK::CrFolderHandle*)folder_handle, (SCRSDK::CrContentHandle**)contents_handle, (CrInt32u*)number_of_contents);
}   

//CrError GetContentsDetailInfo(/*in*/ CrDeviceHandle deviceHandle, /*in*/CrContentHandle contentHandle, /*out*/ CrMtpContentsInfo* contentsInfo);
long int sdk_get_contents_detail_info(void* device_handle_handle, void* content_handle, void** contents_info_handle) {
    return (long int) SCRSDK::GetContentsDetailInfo((SCRSDK::CrDeviceHandle)device_handle_handle, *(SCRSDK::CrContentHandle*)content_handle, (SCRSDK::CrMtpContentsInfo*)contents_info_handle);
}

//CrError ReleaseDateFolderList(/*in*/ CrDeviceHandle deviceHandle, /*in*/ CrMtpFolderInfo* folders);
long int sdk_release_date_folder_list(void* device_handle_handle, void* folder_info_handle) {
    return (long int) SCRSDK::ReleaseDateFolderList((SCRSDK::CrDeviceHandle)device_handle_handle, (SCRSDK::CrMtpFolderInfo*)folder_info_handle);
}

//CrError ReleaseContentsHandleList(/*in*/ CrDeviceHandle deviceHandle, /*in*/ CrContentHandle* contentsHandles);
long int sdk_release_contents_handle_list(void* device_handle_handle, void* contents_handle) {
    return (long int) SCRSDK::ReleaseContentsHandleList((SCRSDK::CrDeviceHandle)device_handle_handle, (SCRSDK::CrContentHandle*)contents_handle);
}

//CrError PullContentsFile(/*in*/ CrDeviceHandle deviceHandle, /*in*/ CrContentHandle contentHandle, /*in*/ CrPropertyStillImageTransSize size = CrPropertyStillImageTransSize_Original, /*in*/ CrChar* path = 0, /*in*/ CrChar* fileName = 0);
long int sdk_pull_contents_file(void* device_handle_handle, void* content_handle, long int size, char* path, char* file_name) {
    return (long int) SCRSDK::PullContentsFile((SCRSDK::CrDeviceHandle)device_handle_handle, *(SCRSDK::CrContentHandle*)content_handle, (SCRSDK::CrPropertyStillImageTransSize)size, path, file_name);
}

//CrError GetContentsThumbnailImage(/*in*/ CrDeviceHandle deviceHandle, /*in*/ CrContentHandle contentHandle, /*out*/ CrImageDataBlock* imageData, /*out*/ CrFileType* fileType);
long int sdk_get_contents_thumbnail_image(void* device_handle_handle, void* content_handle, void* image_data_block_handle, long int* file_type) {
    return (long int) SCRSDK::GetContentsThumbnailImage((SCRSDK::CrDeviceHandle)device_handle_handle, *(SCRSDK::CrContentHandle*)content_handle, (SCRSDK::CrImageDataBlock*)image_data_block_handle, (SCRSDK::CrFileType*)file_type);
}

//CrError DownloadSettingFile(/*in*/ CrDeviceHandle deviceHandle, /*in*/CrDownloadSettingFileType type, CrChar* filePath = 0, CrChar* fileName = 0, const char* password = 0);
long int sdk_download_setting_file(void* device_handle_handle, long int type, char* file_path, char* file_name, const char* password) {
    return (long int) SCRSDK::DownloadSettingFile((SCRSDK::CrDeviceHandle)device_handle_handle, (SCRSDK::CrDownloadSettingFileType)type, file_path, file_name, password);
}

//CrError UploadSettingFile(/*in*/ CrDeviceHandle deviceHandle, /*in*/CrUploadSettingFileType type, CrChar* fileName, const char* password = 0);
long int sdk_upload_setting_file(void* device_handle_handle, long int type, char* file_name, const char* password) {
    return (long int) SCRSDK::UploadSettingFile((SCRSDK::CrDeviceHandle)device_handle_handle, (SCRSDK::CrUploadSettingFileType)type, file_name, password);
}

//CrError RequestDisplayStringList(/*in*/ CrDeviceHandle deviceHandle, /*in*/CrDisplayStringType type);
long int sdk_request_display_string_list(void* device_handle_handle, long int type) {
    return (long int) SCRSDK::RequestDisplayStringList((SCRSDK::CrDeviceHandle)device_handle_handle, (SCRSDK::CrDisplayStringType)type);
}

//CrError GetDisplayStringTypes(/*in*/ CrDeviceHandle deviceHandle, /*out*/CrDisplayStringType** types, /*out*/ CrInt32u* numOfTypes);
long int sdk_get_display_string_types(void* device_handle_handle, void** display_string_type_handle, long int* number_of_types) {
    return (long int) SCRSDK::GetDisplayStringTypes((SCRSDK::CrDeviceHandle)device_handle_handle, (SCRSDK::CrDisplayStringType**)display_string_type_handle, (CrInt32u*)number_of_types);
}

//CrError GetDisplayStringList(/*in*/ CrDeviceHandle deviceHandle, /*in*/CrDisplayStringType type,/*out*/ CrDisplayStringListInfo** list, /*out*/ CrInt32u* numOfList);
long int sdk_get_display_string_list(void* device_handle_handle, long int type, void** display_string_list_info_handle, long int* number_of_list) {
    return (long int) SCRSDK::GetDisplayStringList((SCRSDK::CrDeviceHandle)device_handle_handle, (SCRSDK::CrDisplayStringType)type, (SCRSDK::CrDisplayStringListInfo**)display_string_list_info_handle, (CrInt32u*)number_of_list);
}

//CrError ReleaseDisplayStringTypes(/*in*/ CrDeviceHandle deviceHandle, CrDisplayStringType* types);
long int sdk_release_display_string_types(void* device_handle_handle, void* display_string_type_handle) {
    return (long int) SCRSDK::ReleaseDisplayStringTypes((SCRSDK::CrDeviceHandle)device_handle_handle, (SCRSDK::CrDisplayStringType*)display_string_type_handle);
}

//CrError ReleaseDisplayStringList(/*in*/ CrDeviceHandle deviceHandle,CrDisplayStringListInfo* list);
long int sdk_release_display_string_list(void* device_handle_handle, void* display_string_list_info_handle) {
    return (long int) SCRSDK::ReleaseDisplayStringList((SCRSDK::CrDeviceHandle)device_handle_handle, (SCRSDK::CrDisplayStringListInfo*)display_string_list_info_handle);
}

//CrError GetMediaProfile(/*in*/ CrDeviceHandle deviceHandle, CrMediaProfile slot, /*out*/ CrMediaProfileInfo** mediaProfile, CrInt32u* numOfProfile);
long int sdk_get_media_profile(void* device_handle_handle, long int slot, void** media_profile_handle, long int* number_of_profile) {
    return (long int) SCRSDK::GetMediaProfile((SCRSDK::CrDeviceHandle)device_handle_handle, (SCRSDK::CrMediaProfile)slot, (SCRSDK::CrMediaProfileInfo**)media_profile_handle, (CrInt32u*)number_of_profile);
}

//CrError ReleaseMediaProfile(/*in*/ CrDeviceHandle deviceHandle, CrMediaProfileInfo * mediaProfile);
long int sdk_release_media_profile(void* device_handle_handle, void* media_profile_handle) {
    return (long int) SCRSDK::ReleaseMediaProfile((SCRSDK::CrDeviceHandle)device_handle_handle, (SCRSDK::CrMediaProfileInfo*)media_profile_handle);
}

//CrError RequestLensInformation(/*in*/ CrDeviceHandle deviceHandle);
long int sdk_request_lens_information(void* device_handle_handle) {
    return (long int) SCRSDK::RequestLensInformation((SCRSDK::CrDeviceHandle)device_handle_handle);
}

//CrError GetLensInformation(/*in*/ CrDeviceHandle deviceHandle, /*out*/ CrLensInformation** list, /*out*/ CrInt32u* numOfList);
long int sdk_get_lens_information(void* device_handle_handle, void** lens_information_handle, long int* number_of_list) {
    return (long int) SCRSDK::GetLensInformation((SCRSDK::CrDeviceHandle)device_handle_handle, (SCRSDK::CrLensInformation**)lens_information_handle, (CrInt32u*)number_of_list);
}

//CrError ReleaseLensInformation(/*in*/ CrDeviceHandle deviceHandle, CrLensInformation* list);
long int sdk_release_lens_information(void* device_handle_handle, void* lens_information_handle) {
    return (long int) SCRSDK::ReleaseLensInformation((SCRSDK::CrDeviceHandle)device_handle_handle, (SCRSDK::CrLensInformation*)lens_information_handle);
}

//CrError ImportLUTFile(/*in*/ CrDeviceHandle deviceHandle, CrChar* fileName, CrBaseLookNumber baseLookNumber);
long int sdk_import_lut_file(void* device_handle_handle, char* file_name, long int base_look_number) {
    return (long int) SCRSDK::ImportLUTFile((SCRSDK::CrDeviceHandle)device_handle_handle, file_name, (SCRSDK::CrBaseLookNumber)base_look_number);
}

//CrError RequestFTPServerSettingList(/*in*/ CrDeviceHandle deviceHandle);
long int sdk_request_ftp_server_setting_list(void* device_handle_handle) {
    return (long int) SCRSDK::RequestFTPServerSettingList((SCRSDK::CrDeviceHandle)device_handle_handle);
}

//CrError GetFTPServerSettingList(/*in*/ CrDeviceHandle deviceHandle, /*out*/ CrFTPServerSetting** list, /*out*/ CrInt32u* numOfList);
long int sdk_get_ftp_server_setting_list(void* device_handle_handle, void** ftp_server_setting_handle, long int* number_of_list) {
    return (long int) SCRSDK::GetFTPServerSettingList((SCRSDK::CrDeviceHandle)device_handle_handle, (SCRSDK::CrFTPServerSetting**)ftp_server_setting_handle, (CrInt32u*)number_of_list);
}

//CrError ReleaseFTPServerSettingList(/*in*/ CrDeviceHandle deviceHandle, CrFTPServerSetting* list);
long int sdk_release_ftp_server_setting_list(void* device_handle_handle, void* ftp_server_setting_handle) {
    return (long int) SCRSDK::ReleaseFTPServerSettingList((SCRSDK::CrDeviceHandle)device_handle_handle, (SCRSDK::CrFTPServerSetting*)ftp_server_setting_handle);
}

//CrError SetFTPServerSetting(/*in*/ CrDeviceHandle deviceHandle, CrFTPServerSetting* setting);
long int sdk_set_ftp_server_setting(void* device_handle_handle, void* ftp_server_setting_handle) {
    return (long int) SCRSDK::SetFTPServerSetting((SCRSDK::CrDeviceHandle)device_handle_handle, (SCRSDK::CrFTPServerSetting*)ftp_server_setting_handle);
}

//CrError RequestFTPJobList(/*in*/ CrDeviceHandle deviceHandle);
long int sdk_request_ftp_job_list(void* device_handle_handle) {
    return (long int) SCRSDK::RequestFTPJobList((SCRSDK::CrDeviceHandle)device_handle_handle);
}

//CrError GetFTPJobList(/*in*/ CrDeviceHandle deviceHandle, /*out*/ CrFTPJobInfo ** list, /*out*/ CrInt32u* numOfList);
long int sdk_get_ftp_job_list(void* device_handle_handle, void** ftp_job_info_handle, long int* number_of_list) {
    return (long int) SCRSDK::GetFTPJobList((SCRSDK::CrDeviceHandle)device_handle_handle, (SCRSDK::CrFTPJobInfo**)ftp_job_info_handle, (CrInt32u*)number_of_list);
}

//CrError ReleaseFTPJobList(/*in*/ CrDeviceHandle deviceHandle, CrFTPJobInfo* list);
long int sdk_release_ftp_job_list(void* device_handle_handle, void* ftp_job_info_handle) {
    return (long int) SCRSDK::ReleaseFTPJobList((SCRSDK::CrDeviceHandle)device_handle_handle, (SCRSDK::CrFTPJobInfo*)ftp_job_info_handle);
}

//CrError ControlFTPJobList(/*in*/ CrDeviceHandle deviceHandle, /*in*/ CrFTPJobControlType control, /*in*/ void* jobList, /*in*/ CrInt32u numOfList, /*in*/ CrFTPJobDeleteType deleteType = CrFTPJobDeleteType_Individual);
long int sdk_control_ftp_job_list(void* device_handle_handle, long int control, void* job_list, long int number_of_list, long int delete_type) {
    return (long int) SCRSDK::ControlFTPJobList((SCRSDK::CrDeviceHandle)device_handle_handle, (SCRSDK::CrFTPJobControlType)control, (void*)job_list, (CrInt32u)number_of_list, (SCRSDK::CrFTPJobDeleteType)delete_type);
}

//CrError GetCRSDKOperationResultsSupported(/*in*/ CrDeviceHandle deviceHandle, CrOperationResultSupportedInfo** opeResSupportInfo, /*out*/ CrInt32u* numOfInfo);
long int sdk_get_crsdk_operation_results_supported(void* device_handle_handle, void** operation_result_supported_info_handle, long int* number_of_info) {
    return (long int) SCRSDK::GetCRSDKOperationResultsSupported((SCRSDK::CrDeviceHandle)device_handle_handle, (SCRSDK::CrOperationResultSupportedInfo**)operation_result_supported_info_handle, (CrInt32u*)number_of_info);
}

//CrError ReleaseCRSDKOperationResultsSupported(/*in*/ CrDeviceHandle deviceHandle, CrOperationResultSupportedInfo* opeResSupportInfo);
long int sdk_release_crsdk_operation_results_supported(void* device_handle_handle, void* operation_result_supported_info_handle) {
    return (long int) SCRSDK::ReleaseCRSDKOperationResultsSupported((SCRSDK::CrDeviceHandle)device_handle_handle, (SCRSDK::CrOperationResultSupportedInfo*)operation_result_supported_info_handle);
}

//CrError SetMonitoringDeliverySetting(/*in*/ CrDeviceHandle deviceHandle, /*in*/ CrMonitoringDeliverySetting* deliverySetting, /*in*/CrInt32u numOfSetting);
long int sdk_set_monitoring_delivery_setting(void* device_handle_handle, void* delivery_setting_handle, long int number_of_setting) {
    return (long int) SCRSDK::SetMonitoringDeliverySetting((SCRSDK::CrDeviceHandle)device_handle_handle, (SCRSDK::CrMonitoringDeliverySetting*)delivery_setting_handle, (CrInt32u)number_of_setting);
}

//CrError GetMonitoringDeliverySetting(/*in*/ CrDeviceHandle deviceHandle, /*out*/ CrMonitoringDeliverySetting** deliverySetting, /*out*/ CrInt32u* numOfSetting);
long int sdk_get_monitoring_delivery_setting(void* device_handle_handle, void** delivery_setting_handle, long int* number_of_setting) {
    return (long int) SCRSDK::GetMonitoringDeliverySetting((SCRSDK::CrDeviceHandle)device_handle_handle, (SCRSDK::CrMonitoringDeliverySetting**)delivery_setting_handle, (CrInt32u*)number_of_setting);
}

//CrError ReleaseMonitoringDeliverySetting(/*in*/ CrDeviceHandle deviceHandle, CrMonitoringDeliverySetting* deliverySetting);
long int sdk_release_monitoring_delivery_setting(void* device_handle_handle, void* delivery_setting_handle) {
    return (long int) SCRSDK::ReleaseMonitoringDeliverySetting((SCRSDK::CrDeviceHandle)device_handle_handle, (SCRSDK::CrMonitoringDeliverySetting*)delivery_setting_handle);
}

//CrError ControlMonitoring(/*in*/ CrDeviceHandle deviceHandle, /*in*/ CrMonitoringOperation operationMode);
long int sdk_control_monitoring(void* device_handle_handle, long int operation_mode) {
    return (long int) SCRSDK::ControlMonitoring((SCRSDK::CrDeviceHandle)device_handle_handle, (SCRSDK::CrMonitoringOperation)operation_mode);
}

//CrError RequestZoomAndFocusPreset(/*in*/ CrDeviceHandle deviceHandle);
long int sdk_request_zoom_and_focus_preset(void* device_handle_handle) {
    return (long int) SCRSDK::RequestZoomAndFocusPreset((SCRSDK::CrDeviceHandle)device_handle_handle);
}

//CrError GetZoomAndFocusPreset(/*in*/ CrDeviceHandle deviceHandle, /*out*/ CrZoomAndFocusPresetInfo** list, /*out*/ CrInt32u* numOfList);
long int sdk_get_zoom_and_focus_preset(void* device_handle_handle, void** zoom_and_focus_preset_info_handle, long int* number_of_list) {
    return (long int) SCRSDK::GetZoomAndFocusPreset((SCRSDK::CrDeviceHandle)device_handle_handle, (SCRSDK::CrZoomAndFocusPresetInfo**)zoom_and_focus_preset_info_handle, (CrInt32u*)number_of_list);
}

//CrError ReleaseZoomAndFocusPreset(/*in*/ CrDeviceHandle deviceHandle, CrZoomAndFocusPresetInfo* list);
long int sdk_release_zoom_and_focus_preset(void* device_handle_handle, void* zoom_and_focus_preset_info_handle) {
    return (long int) SCRSDK::ReleaseZoomAndFocusPreset((SCRSDK::CrDeviceHandle)device_handle_handle, (SCRSDK::CrZoomAndFocusPresetInfo*)zoom_and_focus_preset_info_handle);
}

//CrError RequestFTPTransferResult(/*in*/ CrDeviceHandle deviceHandle, /*in*/ CrSlotNumber slotNumber);
long int sdk_request_ftp_transfer_result(void* device_handle_handle, long int slot_number) {
    return (long int) SCRSDK::RequestFTPTransferResult((SCRSDK::CrDeviceHandle)device_handle_handle, (SCRSDK::CrSlotNumber)slot_number);
}

//CrError GetOSDImage(/*in*/ CrDeviceHandle deviceHandle, /*out*/ CrOSDImageDataBlock* imageData);
long int sdk_get_osd_image(void* device_handle_handle, void* image_data_block_handle) {
    return (long int) SCRSDK::GetOSDImage((SCRSDK::CrDeviceHandle)device_handle_handle, (SCRSDK::CrOSDImageDataBlock*)image_data_block_handle);
}

//CrError GetRemoteTransferCapturedDateList(/*in*/ CrDeviceHandle deviceHandle, /*in*/ CrSlotNumber slotNumber, /* out */ CrCaptureDate** captureDateList, /* out */ CrInt32u* nums);
long int sdk_get_remote_transfer_captured_date_list(void* device_handle_handle, long int slot_number, void** capture_date_handle, long int* number_of_dates) {
    return (long int) SCRSDK::GetRemoteTransferCapturedDateList((SCRSDK::CrDeviceHandle)device_handle_handle, (SCRSDK::CrSlotNumber)slot_number, (SCRSDK::CrCaptureDate**)capture_date_handle, (CrInt32u*)number_of_dates);
}

//CrError GetRemoteTransferContentsInfoList(/*in*/ CrDeviceHandle deviceHandle, /*in*/ CrSlotNumber slotNumber, /*in*/ CrGetContentsInfoListType type, /* in */ CrCaptureDate* captureDate, /* in */ CrInt32u maxNums,  /* out */ CrContentsInfo** contentsInfoList, /* out */ CrInt32u* nums);
long int sdk_get_remote_transfer_contents_info_list(void* device_handle_handle, long int slot_number, long int type, void* capture_date_handle, long int max_nums, void** contents_info_handle, long int* number_of_contents) {
    return (long int) SCRSDK::GetRemoteTransferContentsInfoList((SCRSDK::CrDeviceHandle)device_handle_handle, (SCRSDK::CrSlotNumber)slot_number, (SCRSDK::CrGetContentsInfoListType)type, (SCRSDK::CrCaptureDate*)capture_date_handle, (CrInt32u)max_nums, (SCRSDK::CrContentsInfo**)contents_info_handle, (CrInt32u*)number_of_contents);
}

//CrError GetRemoteTransferContentsData(CrDeviceHandle deviceHandle, /*in*/ CrSlotNumber slotNumber, /*in*/ CrInt32u contentsId, /*in*/ CrInt32u fileId, /*in*/ CrInt32u divisionSize);
long int sdk_get_remote_transfer_contents_data(void* device_handle_handle, long int slot_number, long int contents_id, long int file_id, long int division_size) {
    return (long int) SCRSDK::GetRemoteTransferContentsData((SCRSDK::CrDeviceHandle)device_handle_handle, (SCRSDK::CrSlotNumber)slot_number, (CrInt32u)contents_id, (CrInt32u)file_id, (CrInt32u)division_size);
}

//CrError GetRemoteTransferContentsDataFile(CrDeviceHandle deviceHandle, /*in*/ CrSlotNumber slotNumber, /*in*/ CrInt32u contentsId, /*in*/ CrInt32u fileId, /*in*/ CrInt32u divisionSize, /*in*/ CrChar* path, /*in*/ CrChar* fileName);
long int sdk_get_remote_transfer_contents_data_file(void* device_handle_handle, long int slot_number, long int contents_id, long int file_id, long int division_size, char* path, char* file_name) {
    return (long int) SCRSDK::GetRemoteTransferContentsDataFile((SCRSDK::CrDeviceHandle)device_handle_handle, (SCRSDK::CrSlotNumber)slot_number, (CrInt32u)contents_id, (CrInt32u)file_id, (CrInt32u)division_size, path, file_name);
}

//CrError ControlGetRemoteTransferContentsDataFile(CrDeviceHandle deviceHandle, /*in*/ CrGetContentsDataControlType type);
long int sdk_control_get_remote_transfer_contents_data_file(void* device_handle_handle, long int type) {
    return (long int) SCRSDK::ControlGetRemoteTransferContentsDataFile((SCRSDK::CrDeviceHandle)device_handle_handle, (SCRSDK::CrGetContentsDataControlType)type);
}

//CrError GetRemoteTransferContentsCompressedData(CrDeviceHandle deviceHandle, /*in*/ CrSlotNumber slotNumber, /*in*/ CrInt32u contentsId, /*in*/ CrInt32u fileId, /*in*/ CrGetContentsCompressedDataType type);
long int sdk_get_remote_transfer_contents_compressed_data(void* device_handle_handle, long int slot_number, long int contents_id, long int file_id, long int type) {
    return (long int) SCRSDK::GetRemoteTransferContentsCompressedData((SCRSDK::CrDeviceHandle)device_handle_handle, (SCRSDK::CrSlotNumber)slot_number, (CrInt32u)contents_id, (CrInt32u)file_id, (SCRSDK::CrGetContentsCompressedDataType)type);
}

//CrError GetRemoteTransferContentsCompressedDataFile(CrDeviceHandle deviceHandle, /*in*/ CrSlotNumber slotNumber, /*in*/ CrInt32u contentsId, /*in*/ CrInt32u fileId, /*in*/ CrGetContentsCompressedDataType type, /*in*/ CrChar* path, /*in*/ CrChar* fileName);
long int sdk_get_remote_transfer_contents_compressed_data_file(void* device_handle_handle, long int slot_number, long int contents_id, long int file_id, long int type, char* path, char* file_name) {
    return (long int) SCRSDK::GetRemoteTransferContentsCompressedDataFile((SCRSDK::CrDeviceHandle)device_handle_handle, (SCRSDK::CrSlotNumber)slot_number, (CrInt32u)contents_id, (CrInt32u)file_id, (SCRSDK::CrGetContentsCompressedDataType)type, path, file_name);
}

//CrError ReleaseRemoteTransferCapturedDateList(/*in*/ CrDeviceHandle deviceHandle, /*in*/ CrCaptureDate* dateList);
long int sdk_release_remote_transfer_captured_date_list(void* device_handle_handle, void* capture_date_handle) {
    return (long int) SCRSDK::ReleaseRemoteTransferCapturedDateList((SCRSDK::CrDeviceHandle)device_handle_handle, (SCRSDK::CrCaptureDate*)capture_date_handle);
}

//CrError ReleaseRemoteTransferContentsInfoList(/*in*/ CrDeviceHandle deviceHandle, /*in*/ CrContentsInfo* contentsInfoList);
long int sdk_release_remote_transfer_contents_info_list(void* device_handle_handle, void* contents_info_handle) {
    return (long int) SCRSDK::ReleaseRemoteTransferContentsInfoList((SCRSDK::CrDeviceHandle)device_handle_handle, (SCRSDK::CrContentsInfo*)contents_info_handle);
}

//CrError SetMoviePlaybackSetting(/*in*/ CrDeviceHandle deviceHandle, /*in*/ CrMoviePlaybackSetting* setting, /*in*/CrInt32u numOfSetting);
long int sdk_set_movie_playback_setting(void* device_handle_handle, void* setting_handle, long int number_of_setting) {
    return (long int) SCRSDK::SetMoviePlaybackSetting((SCRSDK::CrDeviceHandle)device_handle_handle, (SCRSDK::CrMoviePlaybackSetting*)setting_handle, (CrInt32u)number_of_setting);
}

//CrError GetMoviePlaybackSetting(/*in*/ CrDeviceHandle deviceHandle, /*in*/ CrMoviePlaybackSetting** setting, /*in*/CrInt32u* numOfSetting);
long int sdk_get_movie_playback_setting(void* device_handle_handle, void** setting_handle, long int* number_of_setting) {
    return (long int) SCRSDK::GetMoviePlaybackSetting((SCRSDK::CrDeviceHandle)device_handle_handle, (SCRSDK::CrMoviePlaybackSetting**)setting_handle, (CrInt32u*)number_of_setting);
}

//CrError ReleaseMoviePlaybackSetting(/*in*/ CrDeviceHandle deviceHandle, CrMoviePlaybackSetting* setting);
long int sdk_release_movie_playback_setting(void* device_handle_handle, void* setting_handle) {
    return (long int) SCRSDK::ReleaseMoviePlaybackSetting((SCRSDK::CrDeviceHandle)device_handle_handle, (SCRSDK::CrMoviePlaybackSetting*)setting_handle);
}

//CrError ControlMoviePlayback(/*in*/ CrDeviceHandle deviceHandle, /*in*/ CrMoviePlaybackControlType operationMode, /*in*/ CrInt32u seekPosition = 0);
long int sdk_control_movie_playback(void* device_handle_handle, long int operation_mode, long int seek_position) {
    return (long int) SCRSDK::ControlMoviePlayback((SCRSDK::CrDeviceHandle)device_handle_handle, (SCRSDK::CrMoviePlaybackControlType)operation_mode, (CrInt32u)seek_position);
}

//CrError RequestMoviePlaybackStatus(/*in*/ CrDeviceHandle deviceHandle);
long int sdk_request_movie_playback_status(void* device_handle_handle) {
    return (long int) SCRSDK::RequestMoviePlaybackStatus((SCRSDK::CrDeviceHandle)device_handle_handle);
}

//CrError GetMoviePlaybackStatus(/*in*/ CrDeviceHandle deviceHandle, /*out*/ CrMoviePlaybackStatus* playbackStatus);
long int sdk_get_movie_playback_status(void* device_handle_handle, void** playback_status_handle) {
    return (long int) SCRSDK::GetMoviePlaybackStatus((SCRSDK::CrDeviceHandle)device_handle_handle, (SCRSDK::CrMoviePlaybackStatus*)playback_status_handle);
}

//CrError PrecheckFirmwareUpdate(/*in*/ CrDeviceHandle deviceHandle, /*in*/ CrInt64u fwFileSize);
long int sdk_precheck_firmware_update(void* device_handle_handle, long long int fw_file_size) {
    return (long int) SCRSDK::PrecheckFirmwareUpdate((SCRSDK::CrDeviceHandle)device_handle_handle, (CrInt64u)fw_file_size);
}

//CrError UploadPartialFile(/*in*/ CrDeviceHandle deviceHandle, /*in*/ CrUploadPartialDataType type, /*in*/ CrChar * filePath);
long int sdk_upload_partial_file(void* device_handle_handle, long int type, char* file_path) {
    return (long int) SCRSDK::UploadPartialFile((SCRSDK::CrDeviceHandle)device_handle_handle, (SCRSDK::CrUploadPartialDataType)type, file_path);
}

//CrError CancelFirmwareUpload(/*in*/ CrDeviceHandle deviceHandle);
long int sdk_cancel_firmware_upload(void* device_handle_handle) {
    return (long int) SCRSDK::CancelFirmwareUpload((SCRSDK::CrDeviceHandle)device_handle_handle);
}

//CrError RequestFirmwareUpdaterInfo(/*in*/ CrDeviceHandle deviceHandle);
long int sdk_request_firmware_updater_info(void* device_handle_handle) {
    return (long int) SCRSDK::RequestFirmwareUpdaterInfo((SCRSDK::CrDeviceHandle)device_handle_handle);
}

//CrError StartFirmwareUpdate(/*in*/ CrDeviceHandle deviceHandle);
long int sdk_start_firmware_update(void* device_handle_handle) {
    return (long int) SCRSDK::StartFirmwareUpdate((SCRSDK::CrDeviceHandle)device_handle_handle);
}
