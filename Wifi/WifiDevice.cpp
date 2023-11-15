#include "WifiDevice.h"
#include <QDebug>

WifiDevice::WifiDevice()
{
}

WifiDevice::WifiDevice(const DeviceInfo& info) {
    mDeviceInfo = std::move(info);
}

WifiDevice::WifiDevice(std::string name, std::string address, bool privateAddr, std::string password, bool autoConnect)
{
    mDeviceInfo.mName = name;
    mDeviceInfo.mAddress = address;
    mDeviceInfo.mPrivateAddress = privateAddr;
    mPassword = password;
    mAutoConnect = autoConnect;
}

WifiDevice::~WifiDevice()
{
}

void WifiDevice::setValue(const DeviceProperty& property, const CommonType& value)
{
    switch(property) {
    case DeviceProperty::Password:
        mPassword = value.value<std::string>();
        return;
    case DeviceProperty::AutoConnect:
        mAutoConnect = value.value<bool>();
        return;
    case DeviceProperty::SpeedMode:
        mSpeedMode = value.value<SpeedMode>();
        return;
    case DeviceProperty::State:
        mState = value.value<State>();
        return;
    default:
        return;
    }
}
