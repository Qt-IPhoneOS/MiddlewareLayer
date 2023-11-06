#include "WifiDevice.h"
#include <QDebug>

WifiDevice::WifiDevice(const PairedDeviceInfo& info) {
    mPairedDeviceInfo = std::move(info);
}

WifiDevice::~WifiDevice()
{
}

void WifiDevice::setData(const DeviceProperty& property, const CommonType& value)
{
    switch(property) {
    case DeviceProperty::Password:
        mPassword = value.value<std::string>();
        return;
    case DeviceProperty::LowDataMode:
        mLowDataMode = value.value<bool>();
        return;
    case DeviceProperty::LimitIP:
        mLimitIP = value.value<bool>();
        return;
    case DeviceProperty::SpeedMode:
        mSpeedMode = value.value<SpeedMode>();
        return;
    case DeviceProperty::DeviceType:
        mDeviceType = value.value<DeviceType>();
        return;
    case DeviceProperty::State:
        mState = value.value<State>();
        return;
    default:
        return;
    }
}
