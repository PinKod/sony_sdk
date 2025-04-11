#ifndef CALLBACK_HPP
#define CALLBACK_HPP

#include "IDeviceCallback.h"

class callback : public SCRSDK::IDeviceCallback {
    public:
        virtual void OnConnected(SCRSDK::DeviceConnectionVersioin version) override{}
        virtual void OnDisconnected(CrInt32u error) override{}
        virtual void OnPropertyChanged() override{}
        virtual void OnLvPropertyChanged() override{}
        virtual void OnCompleteDownload(CrChar* filename, CrInt32u type) override{}
        virtual void OnWarning(CrInt32u warning) override{}
        virtual void OnWarningExt(CrInt32u warning, CrInt32 param1, CrInt32 param2, CrInt32 param3) override{}
        virtual void OnError(CrInt32u error) override{}
        virtual void OnPropertyChangedCodes(CrInt32u num, CrInt32u* codes) override{}
        virtual void OnLvPropertyChangedCodes(CrInt32u num, CrInt32u* codes) override{}
        virtual void OnNotifyContentsTransfer(CrInt32u notify, SCRSDK::CrContentHandle contentHandle, CrChar* filename) override{}
        virtual void OnNotifyFTPTransferResult(CrInt32u notify, CrInt32u numOfSuccess, CrInt32u numOfFail) override{}
        virtual void OnNotifyRemoteTransferResult(CrInt32u notify, CrInt32u per, CrChar* filename) override{}
        virtual void OnNotifyRemoteTransferResult(CrInt32u notify, CrInt32u per, CrInt8u* data, CrInt64u size) override{}
        virtual void OnNotifyRemoteTransferContentsListChanged(CrInt32u notify, CrInt32u slotNumber, CrInt32u addSize) override{}
        virtual void OnReceivePlaybackTimeCode(CrInt32u timeCode) override{}
        virtual void OnReceivePlaybackData(CrInt8u mediaType, CrInt32 dataSize, CrInt8u* data, CrInt64 pts, CrInt64 dts, CrInt32 param1, CrInt32 param2) override{}
        virtual void OnNotifyRemoteFirmwareUpdateResult(CrInt32u notify, const void* param) override{}
};












#endif //CALLBACK_HPP