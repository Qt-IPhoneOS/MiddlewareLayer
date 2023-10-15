#include "WifiDevice.h"
#include <QDebug>

WifiDevice::WifiDevice(std::string name, std::string addr) {
    mName = name;
    mAddress = addr;
}

WifiDevice::~WifiDevice()
{
}

//inline std::string getName() const { return mName; }
//inline std::string getPassword() const { return mPassword; }
//inline std::string getAddress() const { return mAddress; }
//inline std::string getIPAddress() const { return mIPAddress; }
//inline std::string getSubnet() const { return mSubnet; }
//inline std::string getRouter() const { return mRouter; }
//inline bool getPrivateAddress() const { return mPrivateAddr; }
//inline bool getLowDataMode() const { return mLowDataMode; }
//inline bool getLimitIP() const { return mLimitIP; }
//inline SpeedMode getSpeedMode() const { return mSpeedMode; }
//inline IP getIP() const { return mIP; }
//inline DeviceType getDeviceType() const { return mDeviceType; }
//inline DNS getDNS() const { return mDNS; }
//inline Proxy getProxy() const { return mProxy; }
//inline State getState() const { return mState; }

void WifiDevice::setData(const DeviceProperty& property, const CommonType& value)
{
    qWarning() << "AAAA: " << value.value<std::string>();
    switch(property) {
    case DeviceProperty::Name:
        mName = value.value<std::string>();
        return;
    case DeviceProperty::Password:
        break;
    case DeviceProperty::Address:
        break;
    case DeviceProperty::IPAddress:
        break;
    case DeviceProperty::Subnet:
        break;
    case DeviceProperty::Router:
        break;
    case DeviceProperty::PrivateAddress:
        break;
    case DeviceProperty::LowDataMode:
        break;
    case DeviceProperty::LimitIP:
        break;
    case DeviceProperty::SpeedMode:
        break;
    case DeviceProperty::IP:
        break;
    case DeviceProperty::DeviceType:
        break;
    case DeviceProperty::DNS:
        break;
    case DeviceProperty::Proxy:
        break;
    case DeviceProperty::State:
        break;
    default:
        break;
    }
}

CommonType WifiDevice::getData(const DeviceProperty&)
{

}
