#include "WifiDevice.h"

WifiDevice::WifiDevice(std::string name, std::string addr, DeviceType type, SpeedMode speedMode, bool privateAddr, IP ip,
           DNS dns, Proxy proxy, std::string password, bool lowDataMode, bool limitIP,
           std::string ipAddr, std::string subnetMask, std::string router) {
    mName = name;
    mAddress = addr;
    mSpeedMode = speedMode;
    mDeviceType = type;
    mPrivateAddr = privateAddr;
    mIP = ip;
    mDNS = dns;
    mProxy = proxy;
    mPassword = password;
    mLowDataMode = lowDataMode;
    mLimitIP = limitIP;
    mIPAddress = ipAddr;
    mSubnet = subnetMask;
    mRouter = router;
}

WifiDevice::~WifiDevice()
{
}
