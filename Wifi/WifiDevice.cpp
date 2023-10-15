#include "WifiDevice.h"
#include <QDebug>

WifiDevice::WifiDevice(std::string name, std::string addr) {
    mName = name;
    mAddress = addr;
}

WifiDevice::~WifiDevice()
{
}

void WifiDevice::setData(const DeviceProperty& property, const CommonType& value)
{
    switch(property) {
    case DeviceProperty::Name:
        mName = value.value<std::string>();
        return;
    case DeviceProperty::Password:
        mPassword = value.value<std::string>();
        return;
    case DeviceProperty::Address:
        mAddress = value.value<std::string>();
        return;
    case DeviceProperty::IPAddress:
        mIPAddress = value.value<std::string>();
        return;
    case DeviceProperty::Subnet:
        mSubnet = value.value<std::string>();
        return;
    case DeviceProperty::Router:
        mRouter = value.value<std::string>();
        return;
    case DeviceProperty::PrivateAddress:
        mPrivateAddr = value.value<bool>();
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
    case DeviceProperty::IP:
        mIP = value.value<IP>();
        return;
    case DeviceProperty::DeviceType:
        mDeviceType = value.value<DeviceType>();
        return;
    case DeviceProperty::DNS:
        mDNS = value.value<DNS>();
        return;
    case DeviceProperty::Proxy:
        mProxy = value.value<Proxy>();
        return;
    case DeviceProperty::State:
        mState = value.value<State>();
        return;
    default:
        return;
    }
}
