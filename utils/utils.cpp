#include "./utils.h"

#include "./../c++_wrapper/CameraRemote_SDK.h"
#include "./../c++_wrapper/CrError.h"
#include "./../c++_wrapper/CrTypes.h"
#include "./../c++_wrapper/callback.hpp"

#include <string.h> 
#include <filesystem>
#include <fstream>
#include <iostream>
#include <thread>
#include <unistd.h>
#include <cstring>
#include <string>
#include <codecvt>


namespace fs = std::filesystem;
using namespace std;


void sdk_camera_device_set_save_info(void* device_handle_handle) {
    constexpr int ImageSaveAutoStartNo = -1;
    std::__cxx11::basic_string<char>  path = fs::current_path().native();

    #ifdef Werror
    #define Werror=write-strings
    auto save_status = SCRSDK::SetSaveInfo(*reinterpret_cast<SCRSDK::CrDeviceHandle*>(device_handle_handle)
        , const_cast<char*>(path.data()), "", ImageSaveAutoStartNo);
    #undef Werror=write-strings
    #endif
}


void sdk_camera_device_set_iso(void* device_handle_handle, long long int iso, void* camera_object_info_handle) {
    SCRSDK::CrDeviceProperty prop;  
    prop.SetCode(SCRSDK::CrDevicePropertyCode::CrDeviceProperty_IsoSensitivity);
    prop.SetCurrentValue(iso);
    prop.SetValueType(SCRSDK::CrDataType::CrDataType_UInt32Array);

    SCRSDK::SetDeviceProperty(*reinterpret_cast<SCRSDK::CrDeviceHandle*>(device_handle_handle), &prop);
}


void sdk_save_image(void* image_data_block_handle) {
    auto path = fs::current_path();
    path.append("LiveView000000.JPG");
    std::cout << path << '\n';

    std::ofstream file(path, std::ios::out | std::ios::binary);
    if (!file.bad())
    {
        file.write(
            (char*)reinterpret_cast<SCRSDK::CrImageDataBlock*>(image_data_block_handle)->GetImageData(), 
            reinterpret_cast<SCRSDK::CrImageDataBlock*>(image_data_block_handle)->GetImageSize());
            file.close();
    }
}


void sdk_set_device_propery_time(void* device_handle_handle, void* device_property_handle) {
        SCRSDK::CrDeviceHandle m_device_handle = reinterpret_cast<SCRSDK::CrDeviceHandle>(device_handle_handle);
    SCRSDK::CrDeviceProperty prop;
    prop.SetCode(SCRSDK::CrDevicePropertyCode::CrDeviceProperty_StillImageStoreDestination);
    prop.SetCurrentValue(SCRSDK::CrStillImageStoreDestination_MemoryCard);
    prop.SetValueType(SCRSDK::CrDataType_UInt16Array);
    SCRSDK::SetDeviceProperty(m_device_handle, &prop);
}


void sdk_capture_image(void* device_handle_handle, char* meta_info) {
    SCRSDK::CrDeviceHandle m_device_handle = reinterpret_cast<SCRSDK::CrDeviceHandle>(device_handle_handle);
    std::string prefix;
    prefix.append("__");
    prefix.append(meta_info);
    #ifdef Werror
    #define Werror=write-strings
    char* ptr_prefix = const_cast<char*>(prefix.c_str());
    std::cout << "save path res1: " << SCRSDK::SetSaveInfo(m_device_handle, "C:\\Image", ptr_prefix, 163) << '\n';
    #undef Werror=write-strings
    #endif
    // usleep(499999);
    std::cout << "Capture image...\n";
    std::cout << "Shutter down\n";
    std::cout << "cap1: " << SCRSDK::SendCommand(m_device_handle, SCRSDK::CrCommandId::CrCommandId_Release, SCRSDK::CrCommandParam_Down) << '\n';

    // Wait, then send shutter up
    std::this_thread::sleep_for(35ms);
    std::cout << "Shutter up\n";
    std::cout << "cap2: " << SCRSDK::SendCommand(m_device_handle, SCRSDK::CrCommandId::CrCommandId_Release, SCRSDK::CrCommandParam_Up) << '\n';
}


int sdk_change_saving_destination_to_camera(void* device_handle_handle) {
    SCRSDK::CrDeviceHandle m_device_handle = reinterpret_cast<SCRSDK::CrDeviceHandle>(device_handle_handle);
    SCRSDK::CrDeviceProperty prop;
    prop.SetCode(SCRSDK::CrDevicePropertyCode::CrDeviceProperty_StillImageStoreDestination);
    prop.SetCurrentValue(SCRSDK::CrStillImageStoreDestination_MemoryCard);
    prop.SetValueType(SCRSDK::CrDataType_UInt16Array);
    return (int)SCRSDK::SetDeviceProperty(m_device_handle, &prop);
}

int sdk_change_saving_destination_to_host_pc(void* device_handle_handle) {
    SCRSDK::CrDeviceHandle m_device_handle = reinterpret_cast<SCRSDK::CrDeviceHandle>(device_handle_handle);
    SCRSDK::CrDeviceProperty prop;
    prop.SetCode(SCRSDK::CrDevicePropertyCode::CrDeviceProperty_StillImageStoreDestination);
    // prop.SetCurrentValue(SCRSDK::CrStillImageStoreDestination_MemoryCard);
    prop.SetCode(SCRSDK::CrStillImageStoreDestination_HostPC);
    prop.SetValueType(SCRSDK::CrDataType_UInt16Array);
    return (int)SCRSDK::SetDeviceProperty(m_device_handle, &prop);
}


char* just_get_live_view(void* device_handle_handle) {
    SCRSDK::CrDeviceHandle m_device_handle = reinterpret_cast<SCRSDK::CrDeviceHandle>(device_handle_handle);
    long signed int tmp = 123;
    printf("xe:%ld\n" , *(long signed int*)((void*)&tmp));
    // SCRSDK::CrDeviceHandle m_device_handle = *reinterpret_cast<SCRSDK::CrDeviceHandle*>(device_handle_handle);
    std::cout <<"device: " << m_device_handle << "      "<< device_handle_handle <<  '\n';
    CrInt32 num = 0;
    SCRSDK::CrLiveViewProperty* property = nullptr;
    auto err = SCRSDK::GetLiveViewProperties(m_device_handle, &property, &num);
    if (CR_FAILED(err)) {
        std::cout << "GetLiveView FAILED 1      err:" << err << '\n';
        return nullptr;
    }
    SCRSDK::ReleaseLiveViewProperties(m_device_handle, property);

    SCRSDK::CrImageInfo inf;
    err = SCRSDK::GetLiveViewImageInfo(m_device_handle, &inf);
    if (CR_FAILED(err)) {
        std::cout << "GetLiveView FAILED 2      err:" << err << '\n';
        return nullptr;
    }

    CrInt32u bufSize = inf.GetBufferSize();
    if (bufSize < 1)
    {
        std::cout << "GetLiveView FAILED 3\n";
        return nullptr;
    }

    SCRSDK::CrImageDataBlock* image_data = nullptr;
    // CrInt8u* image_buff = nullptr;

    image_data = new SCRSDK::CrImageDataBlock();
    if (!image_data)
    {
        // FAILED
        std::cout << "GetLiveView FAILED (new CrImageDataBlock class)\n";
        return nullptr;
    }
    // image_buff = new CrInt8u[bufSize];
    #define  BUFF_SIZE_IMAGE_INFO 1048576  //  1024 * 1024
    static unsigned char image_buff[BUFF_SIZE_IMAGE_INFO];
    memset(image_buff, 0, BUFF_SIZE_IMAGE_INFO);
    image_data->SetSize(bufSize);
    image_data->SetData(image_buff);

    // Get the LiveViewImage
    err = SCRSDK::GetLiveViewImage(m_device_handle, image_data);
    if (CR_FAILED(err))
    {
        // FAILED
        if (err == SCRSDK::CrWarning_Frame_NotUpdated) {
            std::cout << "Warning. GetLiveView Frame NotUpdate\n";
        }
        else if (err == SCRSDK::CrError_Memory_Insufficient) {
            std::cout << "Warning. GetLiveView Memory insufficient\n";
        }
        // delete[] image_buff; // Release
        delete image_data; // Release
        return nullptr;
    }

    if (0 == image_data->GetSize()) {
        // FAILED
        std::cout << "GetLiveView FAILED Image size=0\n";
        // delete[] image_buff; // Release
        delete image_data; // Release
        return nullptr;
    }


    auto path = fs::current_path();

    path.append("LiveView");
    
    std::string path_str;
    
    // Get current time with milliseconds
auto now = std::chrono::system_clock::now();
auto now_time_t = std::chrono::system_clock::to_time_t(now);
std::tm now_tm = *std::localtime(&now_time_t);
auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(
    now.time_since_epoch()
) % 1000;
    
// Format time into a string (YYYYMMDD_HHMMSSmmm)
std::stringstream time_stream;
time_stream << std::put_time(&now_tm, "%Y_%m_%d_%H_%M_%S")
            << std::setfill('0') << std::setw(3) << "____" << milliseconds.count();

    path_str.append(time_stream.str());
    path_str.append(".JPG");
    path.append(path_str);

    std::cout << path << '\n';
    std::cout << "meta info time: " << image_data->GetTimeCode() << '\n';
    std::ofstream file(path, std::ios::out | std::ios::binary);
    if (!file.bad())
    {
        file.write((char*)image_data->GetImageData(), image_data->GetImageSize());
        file.close();
    }
    std::cout << "GetLiveView SUCCESS\n";
    return (char*) path.c_str(); //return image data block
}


long long get_device_property_focus(void* device_properties_handle) {
    SCRSDK::CrDeviceHandle device_m = reinterpret_cast<SCRSDK::CrDeviceHandle>(device_properties_handle);
    std::int32_t nprop = 0;
    SCRSDK::CrDeviceProperty* prop_list = nullptr;
    CrInt32u getCode = SCRSDK::CrDevicePropertyCode::CrDeviceProperty_FocusPositionCurrentValue;
    auto status = SCRSDK::GetSelectDeviceProperties(device_m, 1, &getCode, &prop_list, &nprop);
    if(status) {
        std::cout << "focus err: " << status << '\n';
        return -1;
    }
    return prop_list[0].GetCurrentValue();
}

