#include "./classes_methods.h"

#include "./../c++_wrapper/CameraRemote_SDK.h"
#include "./../c++_wrapper/CrImageDataBlock.h"
#include "./../c++_wrapper/CrError.h"
#include "./../c++_wrapper/CrTypes.h"
#include "./../c++_wrapper/callback.hpp"

#include <stdio.h>
#include <iostream>
#include <filesystem>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>

namespace fs = std::filesystem;


//wrapper for class ICrCameraObjectInfo
int sdk_enum_camera_object_get_count(void* enum_camera_object_handle) {
    SCRSDK::ICrEnumCameraObjectInfo* camera_list = reinterpret_cast<SCRSDK::ICrEnumCameraObjectInfo*>(enum_camera_object_handle);
    return camera_list ? static_cast<int>(camera_list->GetCount()) : -1;
}

void* sdk_enum_camera_object_get_camera_object_info(void* enum_camera_object_handle, int index) {
    return reinterpret_cast<void*>(const_cast<SCRSDK::ICrCameraObjectInfo*>(static_cast<SCRSDK::ICrEnumCameraObjectInfo*>(enum_camera_object_handle)->GetCameraObjectInfo(index)));
}

void sdk_enum_camera_object_release(void* enum_camera_object_handle) {
    reinterpret_cast<SCRSDK::ICrEnumCameraObjectInfo*>(enum_camera_object_handle)->Release();
}
//wrapper for class ICrCameraObjectInfo






//wrapper for class ICrCameraObjectInfo
void sdk_camera_object_info_release(void* camera_object_info_handle) {
    reinterpret_cast<SCRSDK::ICrCameraObjectInfo*>(camera_object_info_handle)->Release();
}

char* sdk_camera_object_info_get_name(void* camera_object_info_handle) {
    return reinterpret_cast<char*>(reinterpret_cast<SCRSDK::ICrCameraObjectInfo*>(camera_object_info_handle)->GetName());
}

int sdk_camera_object_info_get_name_size(void* camera_object_info_handle) {
    return reinterpret_cast<unsigned int>(reinterpret_cast<SCRSDK::ICrCameraObjectInfo*>(camera_object_info_handle)->GetNameSize());
}

char* sdk_camera_object_info_get_model(void* camera_object_info_handle) {
    return reinterpret_cast<char*>(reinterpret_cast<SCRSDK::ICrCameraObjectInfo*>(camera_object_info_handle)->GetModel());
}

int sdk_camera_object_info_get_model_size(void* camera_object_info_handle){
    return reinterpret_cast<unsigned int>(reinterpret_cast<SCRSDK::ICrCameraObjectInfo*>(camera_object_info_handle)->GetModelSize());
}

int sdk_camera_object_info_get_usb_pid(void* camera_object_info_handle) {
    return reinterpret_cast<short int>(reinterpret_cast<SCRSDK::ICrCameraObjectInfo*>(camera_object_info_handle)->GetUsbPid());
}

char* sdk_camera_object_info_get_id(void* camera_object_info_handle) {
    return reinterpret_cast<char*>(reinterpret_cast<SCRSDK::ICrCameraObjectInfo*>(camera_object_info_handle)->GetId());
}

int sdk_camera_object_info_get_id_size(void* camera_object_info_handle) {
    return reinterpret_cast<unsigned int>(reinterpret_cast<SCRSDK::ICrCameraObjectInfo*>(camera_object_info_handle)->GetIdSize());
}

int sdk_camera_object_info_get_id_type(void* camera_object_info_handle) {
    return reinterpret_cast<unsigned int>(reinterpret_cast<SCRSDK::ICrCameraObjectInfo*>(camera_object_info_handle)->GetIdType());
}

int sdk_camera_object_info_get_connection_status(void* camera_object_info_handle) {
    return reinterpret_cast<unsigned int>(reinterpret_cast<SCRSDK::ICrCameraObjectInfo*>(camera_object_info_handle)->GetConnectionStatus());
}

char* sdk_camera_object_info_get_connection_type_name(void* camera_object_info_handle){
    return reinterpret_cast<char*>(reinterpret_cast<SCRSDK::ICrCameraObjectInfo*>(camera_object_info_handle)->GetConnectionTypeName());
}

char* sdk_camera_object_info_get_adaptor_name(void* camera_object_info_handle) {
    return reinterpret_cast<char*>(reinterpret_cast<SCRSDK::ICrCameraObjectInfo*>(camera_object_info_handle)->GetAdaptorName());
}

char* sdk_camera_object_info_get_guid(void* camera_object_info_handle) {
    return reinterpret_cast<char*>(reinterpret_cast<SCRSDK::ICrCameraObjectInfo*>(camera_object_info_handle)->GetGuid());
}

char* sdk_camera_object_info_get_pairing_necessity(void* camera_object_info_handle) {
    return reinterpret_cast<char*>(reinterpret_cast<SCRSDK::ICrCameraObjectInfo*>(camera_object_info_handle)->GetPairingNecessity());
}

int sdk_camera_object_info_get_authentification_state(void* camera_object_info_handle) {
    return reinterpret_cast<unsigned short int>(reinterpret_cast<SCRSDK::ICrCameraObjectInfo*>(camera_object_info_handle)->GetAuthenticationState());
}

int sdk_camera_object_info_get_ssh_support(void* camera_object_info_handle) {
    return reinterpret_cast<unsigned int>(reinterpret_cast<SCRSDK::ICrCameraObjectInfo*>(camera_object_info_handle)->GetSSHsupport());
}
//wrapper for class ICrCameraObjectInfo







//wrapper for class SCRSDK_API CrDeviceProperty
void* sdk_construct_device_property() {
    return reinterpret_cast<void*>(new SCRSDK::CrDeviceProperty());
}

int sdk_is_get_enable_device_property(void* device_property_handle) {
    return reinterpret_cast<SCRSDK::CrDeviceProperty*>(device_property_handle)->IsGetEnableCurrentValue() == true ? 0 : 1;
}

int sdk_is_set_enable_device_property(void* device_property_handle) {
    return reinterpret_cast<SCRSDK::CrDeviceProperty*>(device_property_handle)->IsSetEnableCurrentValue() == true ? 0 : 1;
}

void sdk_set_code_device_property(void* device_property_handle, long int code) {
    reinterpret_cast<SCRSDK::CrDeviceProperty*>(device_property_handle)->SetCode(static_cast<CrInt32u>(code));
}

long int sdk_get_code_device_property(void* device_property_handle) {
    return static_cast<long int>(reinterpret_cast<SCRSDK::CrDeviceProperty*>(device_property_handle)->GetCode());
}

void sdk_set_value_type_device_property(void* device_property_handle, long int type) {
    reinterpret_cast<SCRSDK::CrDeviceProperty*>(device_property_handle)->SetValueType(static_cast<SCRSDK::CrDataType>(type));
}

long int sdk_get_value_type_device_property(void* device_property_handle) {
    return static_cast<long int>(reinterpret_cast<SCRSDK::CrDeviceProperty*>(device_property_handle)->GetValueType());
}

void sdk_set_property_enable_flag_device_property(void* device_property_handle, int flag) {
    reinterpret_cast<SCRSDK::CrDeviceProperty*>(device_property_handle)->SetPropertyEnableFlag(static_cast<SCRSDK::CrPropertyEnableFlag>(flag));
}

int sdk_get_property_enable_flag_device_property(void* device_property_handle) {
    return static_cast<int>(reinterpret_cast<SCRSDK::CrDeviceProperty*>(device_property_handle)->GetPropertyEnableFlag());
}

void sdk_set_property_variable_flag_device_property(void* device_property_handle, int flag) {
    reinterpret_cast<SCRSDK::CrDeviceProperty*>(device_property_handle)->SetPropertyVariableFlag(static_cast<SCRSDK::CrPropertyVariableFlag>(flag));
}

int sdk_get_property_variable_flag_device_property(void* device_property_handle) {
    return static_cast<int>(reinterpret_cast<SCRSDK::CrDeviceProperty*>(device_property_handle)->GetPropertyVariableFlag());
}

void sdk_set_current_value_device_property(void* device_property_handle, unsigned long long value) {
    reinterpret_cast<SCRSDK::CrDeviceProperty*>(device_property_handle)->SetCurrentValue(static_cast<CrInt64u>(value));
}

unsigned long long sdk_get_current_value_device_property(void* device_property_handle) {
    return static_cast<unsigned long long>(
        reinterpret_cast<SCRSDK::CrDeviceProperty*>(device_property_handle)->GetCurrentValue()
    );
}

void sdk_set_current_str_device_property(void* device_property_handle, unsigned short* str) {
    reinterpret_cast<SCRSDK::CrDeviceProperty*>(device_property_handle)->SetCurrentStr(str);
}

unsigned short* sdk_get_current_str_device_property(void* device_property_handle) {
    return reinterpret_cast<SCRSDK::CrDeviceProperty*>(device_property_handle)->GetCurrentStr();
}

void sdk_set_value_size_device_property(void* device_property_handle, unsigned long size) {
    reinterpret_cast<SCRSDK::CrDeviceProperty*>(device_property_handle)->SetValueSize(static_cast<CrInt32u>(size));
}

unsigned long sdk_get_value_size_device_property(void* device_property_handle) {
    return static_cast<unsigned long>(
        reinterpret_cast<SCRSDK::CrDeviceProperty*>(device_property_handle)->GetValueSize()
    );
}

void sdk_set_values_device_property(void* device_property_handle, unsigned char* values) {
    reinterpret_cast<SCRSDK::CrDeviceProperty*>(device_property_handle)->SetValues(values);
}

unsigned char* sdk_get_values_device_property(void* device_property_handle) {
    return reinterpret_cast<SCRSDK::CrDeviceProperty*>(device_property_handle)->GetValues();
}

void sdk_set_set_value_size_device_property(void* device_property_handle, unsigned long size) {
    reinterpret_cast<SCRSDK::CrDeviceProperty*>(device_property_handle)->SetSetValueSize(static_cast<CrInt32u>(size));
}

unsigned long sdk_get_set_value_size_device_property(void* device_property_handle) {
    return static_cast<unsigned long>(
        reinterpret_cast<SCRSDK::CrDeviceProperty*>(device_property_handle)->GetSetValueSize()
    );
}

void sdk_set_set_values_device_property(void* device_property_handle, unsigned char* values) {
    reinterpret_cast<SCRSDK::CrDeviceProperty*>(device_property_handle)->SetSetValues(values);
}

unsigned char* sdk_get_set_values_device_property(void* device_property_handle) {
    return reinterpret_cast<SCRSDK::CrDeviceProperty*>(device_property_handle)->GetSetValues();
}
//wrapper for class SCRSDK_API CrDeviceProperty







//wrapper for class SCRSDK_API CrImageDataBlock
void* sdk_construct_image_data_block() {
    return static_cast<void*>(new SCRSDK::CrImageDataBlock());
}

void sdk_destruct_image_data_block(void* image_data_block_handle) {
    delete reinterpret_cast<SCRSDK::CrImageDataBlock*>(image_data_block_handle);
}

unsigned long sdk_get_frame_no_image_data_block(void* image_data_block_handle) {
    return static_cast<unsigned long>(
        reinterpret_cast<SCRSDK::CrImageDataBlock*>(image_data_block_handle)->GetFrameNo()
    );
}

void sdk_set_size_image_data_block(void* image_data_block_handle, CrInt32u size) {
    reinterpret_cast<SCRSDK::CrImageDataBlock*>(image_data_block_handle)->SetSize(
        static_cast<CrInt32u>(size)
    );
}

unsigned long sdk_get_size_image_data_block(void* image_data_block_handle) {
    return static_cast<unsigned long>(
        reinterpret_cast<SCRSDK::CrImageDataBlock*>(image_data_block_handle)->GetSize()
    );
}

void sdk_set_data_image_data_block(void* image_data_block_handle, unsigned char* data) {
    static_cast<SCRSDK::CrImageDataBlock*>(image_data_block_handle)->SetData(
        reinterpret_cast<CrInt8u*>(data)
    );
}

unsigned char* sdk_get_image_data_image_data_block(void* image_data_block_handle) {
    return reinterpret_cast<unsigned char*>(
        reinterpret_cast<SCRSDK::CrImageDataBlock*>(image_data_block_handle)->GetImageData()
    );
}

CrInt32u sdk_get_image_size_image_data_block(void* image_data_block_handle) {
    return static_cast<unsigned long>(
        reinterpret_cast<SCRSDK::CrImageDataBlock*>(image_data_block_handle)->GetImageSize()
    );
}

unsigned long sdk_get_time_code_image_data_block(void* image_data_block_handle) {
    return static_cast<unsigned long>(
        reinterpret_cast<SCRSDK::CrImageDataBlock*>(image_data_block_handle)->GetTimeCode()
    );
}
//wrapper for class SCRSDK_API CrImageDataBlock






//wrapper for class SCRSDK_API CrImageInfo
void* sdk_construct_image_info() {
    return reinterpret_cast<void*>(new SCRSDK::CrImageInfo());
}

void sdk_destruct_image_info(void* image_info_handle) {
    delete reinterpret_cast<SCRSDK::CrImageInfo*>(image_info_handle);
}

CrInt32u sdk_get_buffer_size_image_info(void* image_info_handle) {
    SCRSDK::CrImageInfo inf = *((SCRSDK::CrImageInfo*)image_info_handle);
    return inf.GetBufferSize();
}
//wrapper for class SCRSDK_API CrImageInfo






//wrapper for class SCRSDK_API CrOSDImageMetaInfo
void* sdk_construct_osd_image_meta_info() {
    return reinterpret_cast<void*>(new SCRSDK::CrOSDImageMetaInfo());
}

void sdk_destruct_osd_image_meta_info(void* meta_info_handle) {
    delete reinterpret_cast<SCRSDK::CrOSDImageMetaInfo*>(meta_info_handle);
}

void sdk_set_is_lv_pos_exist(void* meta_info_handle, int value) {
    auto* meta = reinterpret_cast<SCRSDK::CrOSDImageMetaInfo*>(meta_info_handle);
    meta->isLvPosExist = static_cast<SCRSDK::CrIsLvPosExist>(value);
}

int sdk_get_is_lv_pos_exist(void* meta_info_handle) {
    auto* meta = reinterpret_cast<SCRSDK::CrOSDImageMetaInfo*>(meta_info_handle);
    return static_cast<int>(meta->isLvPosExist);
}

void sdk_set_osd_width(void* h, unsigned long v) {
    auto* m = reinterpret_cast<SCRSDK::CrOSDImageMetaInfo*>(h);
    m->osdWidth = static_cast<CrInt32u>(v);
}

unsigned long sdk_get_osd_width(void* h) {
    return reinterpret_cast<SCRSDK::CrOSDImageMetaInfo*>(h)->osdWidth;
}

void sdk_set_osd_height(void* h, unsigned long v) {
    auto* m = reinterpret_cast<SCRSDK::CrOSDImageMetaInfo*>(h);
    m->osdHeight = static_cast<CrInt32u>(v);
}

unsigned long sdk_get_osd_height(void* h) {
    return reinterpret_cast<SCRSDK::CrOSDImageMetaInfo*>(h)->osdHeight;
}

void sdk_set_lv_pos_x(void* h, unsigned long v) {
    auto* m = reinterpret_cast<SCRSDK::CrOSDImageMetaInfo*>(h);
    m->lvPosX = static_cast<CrInt32u>(v);
}

unsigned long sdk_get_lv_pos_x(void* h) {
    return reinterpret_cast<SCRSDK::CrOSDImageMetaInfo*>(h)->lvPosX;
}

void sdk_set_lv_pos_y(void* h, unsigned long v) {
    auto* m = reinterpret_cast<SCRSDK::CrOSDImageMetaInfo*>(h);
    m->lvPosY = static_cast<CrInt32u>(v);
}

unsigned long sdk_get_lv_pos_y(void* h) {
    return reinterpret_cast<SCRSDK::CrOSDImageMetaInfo*>(h)->lvPosY;
}

void sdk_set_lv_width(void* h, unsigned long v) {
    auto* m = reinterpret_cast<SCRSDK::CrOSDImageMetaInfo*>(h);
    m->lvWidth = static_cast<CrInt32u>(v);
}

unsigned long sdk_get_lv_width(void* h) {
    return reinterpret_cast<SCRSDK::CrOSDImageMetaInfo*>(h)->lvWidth;
}

void sdk_set_lv_height(void* h, unsigned long v) {
    auto* m = reinterpret_cast<SCRSDK::CrOSDImageMetaInfo*>(h);
    m->lvHeight = static_cast<CrInt32u>(v);
}

unsigned long sdk_get_lv_height(void* h) {
    return reinterpret_cast<SCRSDK::CrOSDImageMetaInfo*>(h)->lvHeight;
}

void sdk_set_degree(void* h, unsigned long v) {
    auto* m = reinterpret_cast<SCRSDK::CrOSDImageMetaInfo*>(h);
    m->degree = static_cast<CrInt32u>(v);
}

unsigned long sdk_get_degree(void* h) {
    return reinterpret_cast<SCRSDK::CrOSDImageMetaInfo*>(h)->degree;
}   
//wrapper for class SCRSDK_API CrOSDImageMetaInfo





//wrapper for class SCRSDK_API CrOSDImageDataBlock
void* sdk_construct_osd_image_data_block() {
    return reinterpret_cast<void*>(new SCRSDK::CrOSDImageDataBlock());
}

void sdk_destruct_osd_image_data_block(void* h) {
    delete reinterpret_cast<SCRSDK::CrOSDImageDataBlock*>(h);
}

unsigned long sdk_get_frame_no_osd(void* h) {
    return reinterpret_cast<SCRSDK::CrOSDImageDataBlock*>(h)->GetFrameNo();
}

unsigned long sdk_get_image_size_osd(void* h) {
    return reinterpret_cast<SCRSDK::CrOSDImageDataBlock*>(h)->GetImageSize();
}

unsigned char* sdk_get_image_data_osd(void* h) {
    return reinterpret_cast<SCRSDK::CrOSDImageDataBlock*>(h)->GetImageData();
}

void sdk_set_image_data_osd(void* h, unsigned char* data) {
    reinterpret_cast<SCRSDK::CrOSDImageDataBlock*>(h)->SetData(data);
}

void* sdk_get_meta_info_osd(void* h) {
    SCRSDK::CrOSDImageMetaInfo block = reinterpret_cast<SCRSDK::CrOSDImageDataBlock*>(h)->GetMetaInfo();
    SCRSDK::CrOSDImageMetaInfo* meta = new SCRSDK::CrOSDImageMetaInfo();
    meta->isLvPosExist = block.isLvPosExist;
    meta->osdWidth = block.osdWidth;
    meta->osdHeight = block.osdHeight;
    meta->lvPosX = block.lvPosX;
    meta->lvPosY = block.lvPosY;
    meta->lvWidth = block.lvWidth;
    meta->lvHeight = block.lvHeight;
    meta->degree = block.degree;
    return (void*)meta;
}
//wrapper for class SCRSDK_API CrOSDImageDataBlock


