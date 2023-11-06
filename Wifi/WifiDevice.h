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

    struct PairedDeviceInfo
    {
        PairedDeviceInfo(std::string name, std::string address, bool privateAddr)
        {
            mName = name;
            mAddress = address;
            mPrivateAddress = privateAddr;
        }

        inline PairedDeviceInfo()
        {
        }

        std::string mName {""};
        std::string mAddress {""};
        bool mPrivateAddress {false};
    };

    WifiDevice(const PairedDeviceInfo& info);
    ~WifiDevice();

    void setData(const DeviceProperty&, const CommonType&);

    inline std::string getPassword() const { return mPassword; }
    inline SpeedMode getSpeedMode() const { return mSpeedMode; }
    inline DeviceType getDeviceType() const { return mDeviceType; }
    inline State getState() const { return mState; }
    inline PairedDeviceInfo getPairedDeviceInfo() const { return mPairedDeviceInfo; }

private:
    PairedDeviceInfo mPairedDeviceInfo;
    std::string mPassword;
    SpeedMode mSpeedMode;
    DeviceType mDeviceType;
    State mState;
};

#endif // WIFIDEVICE_H
