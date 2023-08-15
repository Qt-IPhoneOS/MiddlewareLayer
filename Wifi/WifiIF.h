#ifndef WIFIIF_H
#define WIFIIF_H

#include <Wifi/WifiServiceProxy.h>
#include <Common/AbstractInterface.h>
#include <shared_mutex>
#include "Signal.h"

class WifiIFPrivate;
class WifiIF final : public AbstractInterface {
    friend class WifiIFPrivate;
public:
    static WifiIF* instance();

    enum class Wifi_SpeedMode {
        OFF = 0,
        WEAKNESS,
        WEAK,
        MEDIUM,
        STRONG
    };

    bool doConnect() override;
    bool doDisconnect() override;

    signal::Signal<void(std::string)> onIPAddressChanged;
    signal::Signal<void(Wifi_SpeedMode)> onWifiSpeedModeChanged;

private:
    WifiIF();
    ~WifiIF();

    WifiIFPrivate* m_privWifi {nullptr};
    WifiServiceProxy* m_wifiServiceProxy {nullptr};

    std::shared_mutex m_mutex;
    std::string m_IPAddress {""};
    Wifi_SpeedMode m_speedMode {Wifi_SpeedMode::OFF};
};

#endif // WIFIIF_H
