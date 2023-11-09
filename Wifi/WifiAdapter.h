#ifndef WIFIADAPTER_H
#define WIFIADAPTER_H

#include <Common/AbstractInterface.h>
#include <shared_mutex>
#include <unordered_map>
#include <Feature/Signal.h>
#include <Feature/CommonType.h>
#include <Feature/StackingTask.h>
#include "WifiDevice.h"

class WifiAdapterConnect;
class WifiAdapter final : public AbstractInterface {
    friend class WifiAdapterConnect;
public:
    static WifiAdapter* instance();
    ~WifiAdapter();

    bool doConnect() override;
    bool doDisconnect() override;

    std::vector<WifiDevice*> getDevices() const;
    std::vector<WifiDevice*> getUnpairedDevices() const;
    std::vector<WifiDevice*> getPairedDevice() const;
    WifiDevice* getConnectedDevice() const;

    // API Request
    void setEnableWifi(const bool&);
    void connectDevice(const std::string& address);
    bool getEnableWifi();

    // Method
    WifiDevice* getDevice(const std::string& address);

    signal::Signal<void(const bool&)> onWifiEnableChanged;
    signal::Signal<void(const std::string&, const WifiDevice::State&, const WifiDevice::State&)> onDeviceStateChanged;
    signal::Signal<void(std::vector<WifiDevice*>)> onPairedDeviceChanged;
    signal::Signal<void(WifiDevice*)> onConnectedDeviceChanged;

protected:
    WifiAdapter();
    WifiAdapter(const WifiAdapter& ) = delete;
    WifiAdapter& operator=(const WifiAdapter& ) = delete;

    std::shared_mutex mMutex;
    WifiAdapterConnect* mConnect {nullptr};
    std::string mDeviceName {""};
    std::unordered_map<std::string, WifiDevice*> mDeviceTable;
};

#endif // WIFIADAPTER_H
