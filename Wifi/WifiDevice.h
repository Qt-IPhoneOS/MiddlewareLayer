#ifndef WIFIDEVICE_H
#define WIFIDEVICE_H

#include <string>
#include <Feature/CommonType.h>

class WifiDevice {
public:
    enum class DeviceProperty {
        Name,
        Password,
        LowDataMode,
        LimitIP,
        SpeedMode,
        DeviceType,
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

    struct IPConfigInfo {
        IPConfigInfo()
        {
        }

        IP mIPConfig {IP::Automatic};
        std::string mIPAddress {""};
        std::string mSubnetMask {""};
        std::string mRouter {""};
    };

    struct PairedDeviceInfo
    {
        PairedDeviceInfo(std::string name, std::string address, bool privateAddr, IP ipConfig, DNS dnsConfig, Proxy proxyConfig)
        {
            mName = name;
            mAddress = address;
            mPrivateAddress = privateAddr;
            mIPConfig = ipConfig;
            mDNSConfig = dnsConfig;
            mProxyConfig = proxyConfig;
        }

        inline PairedDeviceInfo()
        {
        }

        std::string mName {""};
        std::string mAddress {""};
        bool mPrivateAddress {false};
        IP mIPConfig {IP::Automatic};
        DNS mDNSConfig {DNS::Automatic};
        Proxy mProxyConfig {Proxy::Automatic};
    };

    WifiDevice(const PairedDeviceInfo& info);
    ~WifiDevice();

    void setData(const DeviceProperty&, const CommonType&);

    inline std::string getPassword() const { return mPassword; }
    inline bool getLowDataMode() const { return mLowDataMode; }
    inline bool getLimitIP() const { return mLimitIP; }
    inline SpeedMode getSpeedMode() const { return mSpeedMode; }
    inline DeviceType getDeviceType() const { return mDeviceType; }
    inline State getState() const { return mState; }
    inline PairedDeviceInfo getPairedDeviceInfo() const { return mPairedDeviceInfo; }
    inline IPConfigInfo getIPConfigInfo() const { return mIPConfigInfo; }

private:
    PairedDeviceInfo mPairedDeviceInfo;
    IPConfigInfo mIPConfigInfo;
    std::string mPassword;
    bool mLowDataMode, mLimitIP;
    SpeedMode mSpeedMode;
    DeviceType mDeviceType;
    State mState;
};

#endif // WIFIDEVICE_H
