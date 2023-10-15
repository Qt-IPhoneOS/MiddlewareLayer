#ifndef WIFIDEVICE_H
#define WIFIDEVICE_H

#include <string>
#include <FeatureClass/CommonType.h>

class WifiDevice {
public:
    enum class DeviceProperty {
        Name,
        Password,
        Address,
        IPAddress,
        Subnet,
        Router,
        PrivateAddress,
        LowDataMode,
        LimitIP,
        SpeedMode,
        IP,
        DeviceType,
        DNS,
        Proxy,
        State
    };

    enum class State {
        UnknownState,
        UnpairedState,
        WaitingAuthenState,
        AuthenFailState,
        AuthenSuccessState,
        PairedState,
        PairingState,
        PairingFailState,
        ConnectedState
    };

    enum class DeviceType {
        Unknown,
        Connected,
        Paired,
        Unpaired
    };

    enum class SpeedMode {
        Weak,
        Medium,
        Strong
    };

    enum class IP {
        Automatic,
        Manual,
        BootP
    };

    enum class DNS {
        Automatic,
        Manual
    };

    enum class Proxy {
        Off,
        Manual,
        Automatic
    };

    WifiDevice(std::string name, std::string addr);
    ~WifiDevice();

    void setData(const DeviceProperty&, const CommonType&);
    CommonType getData(const DeviceProperty&);

private:
    std::string mName, mPassword, mAddress, mIPAddress, mSubnet, mRouter;
    bool mPrivateAddr, mLowDataMode, mLimitIP;
    SpeedMode mSpeedMode;
    IP mIP;
    DeviceType mDeviceType;
    DNS mDNS;
    Proxy mProxy;
    State mState;
};

#endif // WIFIDEVICE_H
