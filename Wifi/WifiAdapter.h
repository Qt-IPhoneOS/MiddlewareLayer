#ifndef WIFIADAPTER_H
#define WIFIADAPTER_H

#include <Common/AbstractInterface.h>
#include <shared_mutex>
#include <Signal.h>
#include <unordered_map>
#include <CommonType.h>
#include <StackingTask.h>
#include "WifiDevice.h"

class WifiAdapterConnect;
class WifiAdapter final : public AbstractInterface {
    friend class WifiAdapterConnect;
public:
    static WifiAdapter* instance();
    ~WifiAdapter();

    enum class State {
        UnknownState,
        UnpairedState,
        CheckingSSIDState,
        CheckedSSIDFailState,
        CheckedSSIDSuccessState,
        PairedState,
        WaitingAuthenState,
        AuthenFailState,
        AuthenSuccessState
    };

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
    void startDiscovery();

    // Method
    WifiDevice* getDevice(const std::string& address);

    signal::Signal<void(const bool&)> onWifiEnableChanged;
    signal::Signal<void(const std::string&, const State&, const State&)> onDeviceStateChanged;
    signal::Signal<void(std::vector<WifiDevice*>)> onPairedDeviceListChanged;
    signal::Signal<void(WifiDevice*)> onConnectedDeviceChanged;
    signal::Signal<void(WifiDevice*)> onAddDiscoveryDevice;
    signal::Signal<void(const std::string&)> onRemoveDiscoveryDevice;

protected:
    WifiAdapter();
    WifiAdapter(const WifiAdapter& ) = delete;
    WifiAdapter& operator=(const WifiAdapter& ) = delete;

    std::shared_mutex mMutex;
    WifiAdapterConnect* mConnect {nullptr};
    std::string mDeviceName {""};
    State mAuthenState {State::UnknownState};
    std::string mConnectingAddr {""};
    std::unordered_map<std::string, WifiDevice*> mDeviceTable;
};

#endif // WIFIADAPTER_H
