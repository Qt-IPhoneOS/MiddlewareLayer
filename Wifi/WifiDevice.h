#ifndef WIFIDEVICE_H
#define WIFIDEVICE_H

#include <string>
#include <CommonType.h>

namespace midlayer {

class WifiDevice {
public:
    enum class DeviceProperty {
        Password,
        AutoConnect,
        SpeedMode,
        DeviceType
    };

    enum class SpeedMode {
        Weak,
        Medium,
        Strong
    };

    enum class DeviceType {
        Unknown,
        Unpaired,
        Pairing,
        Paired,
        Authenticating,
        Connected
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

    void setValue(const DeviceProperty&, const uicommon::CommonType&);

    inline DeviceInfo getDeviceInfo() const { return mDeviceInfo; }
    inline std::string getPassword() const { return mPassword; }
    inline bool getAutoConnect() const { return mAutoConnect; }
    inline SpeedMode getSpeedMode() const { return mSpeedMode; }
    inline DeviceType getDeviceType() const { return mType; }

private:
    DeviceInfo mDeviceInfo;
    std::string mPassword {""};
    bool mAutoConnect {false};
    SpeedMode mSpeedMode {SpeedMode::Weak};
    DeviceType mType {DeviceType::Unknown};

};

}

#endif // WIFIDEVICE_H
