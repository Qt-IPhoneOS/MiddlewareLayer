#ifndef WIFIDEVICE_H
#define WIFIDEVICE_H

#include <string>
#include <Feature/CommonType.h>

class WifiDevice {
public:
    enum class DeviceProperty {
        Password,
        AutoConnect,
        SpeedMode,
        State
    };

    enum class State {
        UnknownState,
        UnpairedState,
        PairingState,
        PairingFailState,
        PairedState,
        WaitingAuthenState,
        AuthenFailState,
        AuthenSuccessState,
        ConnectedState
    };

    enum class SpeedMode {
        Weak,
        Medium,
        Strong
    };

    struct DeviceInfo
    {
        DeviceInfo(std::string name, std::string address, bool privateAddr)
        {
            mName = name;
            mAddress = address;
            mPrivateAddress = privateAddr;
        }

        inline DeviceInfo()
        {
        }

        std::string mName {""};
        std::string mAddress {""};
        bool mPrivateAddress {false};
    };

    WifiDevice();
    WifiDevice(const DeviceInfo& info);
    WifiDevice(std::string name, std::string address, bool privateAddr, std::string password, bool autoConnect);
    ~WifiDevice();

    void setData(const DeviceProperty&, const CommonType&);

    inline DeviceInfo getDeviceInfo() const { return mDeviceInfo; }
    inline std::string getPassword() const { return mPassword; }
    inline bool getAutoConnect() const { return mAutoConnect; }
    inline SpeedMode getSpeedMode() const { return mSpeedMode; }
    inline State getState() const { return mState; }

private:
    DeviceInfo mDeviceInfo;
    std::string mPassword {""};
    bool mAutoConnect {false};
    SpeedMode mSpeedMode {SpeedMode::Weak};
    State mState {State::UnknownState};
};

#endif // WIFIDEVICE_H
