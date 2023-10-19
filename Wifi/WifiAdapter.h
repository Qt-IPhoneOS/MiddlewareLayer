#ifndef WIFIADAPTER_H
#define WIFIADAPTER_H

#include <Common/AbstractInterface.h>
#include <shared_mutex>
#include <unordered_map>
#include <FeatureClass/Signal.h>
#include <FeatureClass/CommonType.h>
#include "WifiDevice.h"

class WifiAdapterConnect;
class WifiAdapter final : public AbstractInterface {
    friend class WifiAdapterConnect;
public:
    static WifiAdapter* instance();
    ~WifiAdapter();

    bool doConnect() override;
    bool doDisconnect() override;

    signal::Signal<void(const bool&)> onWifiEnableChanged;
    signal::Signal<void(const WifiDevice::State&, const WifiDevice::State&)> onDeviceStateChanged;
    signal::Signal<void(std::vector<WifiDevice*>)> onPairedDeviceChanged;
    signal::Signal<void(WifiDevice*)> onConnectedDeviceChanged;

    std::vector<WifiDevice*> getDevices() const;
    std::vector<WifiDevice*> getUnpairedDevices() const;
    std::vector<WifiDevice*> getPairedDevice() const;
    WifiDevice* getConnectedDevice() const;

    // API Request
    void setEnableWifi(const bool&);

    bool getEnableWifi();

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
