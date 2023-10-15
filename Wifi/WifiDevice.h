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

    inline std::string getName() const { return mName; }
    inline std::string getPassword() const { return mPassword; }
    inline std::string getAddress() const { return mAddress; }
    inline std::string getIPAddress() const { return mIPAddress; }
    inline std::string getSubnet() const { return mSubnet; }
    inline std::string getRouter() const { return mRouter; }
    inline bool getPrivateAddress() const { return mPrivateAddr; }
    inline bool getLowDataMode() const { return mLowDataMode; }
    inline bool getLimitIP() const { return mLimitIP; }
    inline SpeedMode getSpeedMode() const { return mSpeedMode; }
    inline IP getIP() const { return mIP; }
    inline DeviceType getDeviceType() const { return mDeviceType; }
    inline DNS getDNS() const { return mDNS; }
    inline Proxy getProxy() const { return mProxy; }
    inline State getState() const { return mState; }

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
