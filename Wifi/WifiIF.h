#ifndef WIFIIF_H
#define WIFIIF_H

#include <Common/AbstractInterface.h>
#include <shared_mutex>
#include "Signal.h"

class WifiIFPrivate;
class WifiIF final : public AbstractInterface {
    friend class WifiIFPrivate;
    friend class WifiAdapter;
protected:
    class MutexWrapper {
    public:
        MutexWrapper(std::shared_mutex& mutex):mMutex(mutex)
        {}

        MutexWrapper(const MutexWrapper& other):mMutex(other.mMutex)
        {}

        void lock()
        {
            mMutex.lock();
        }

        void unlock()
        {
            mMutex.unlock();
        }

        void lock_shared()
        {
            mMutex.lock_shared();
        }

        bool try_lock_shared()
        {
            return mMutex.try_lock_shared();
        }

        void unlock_shared()
        {
            mMutex.unlock_shared();
        }

    private:
        std::shared_mutex& mMutex;
    };

public:
    static WifiIF* instance();
    ~WifiIF();

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

protected:
    WifiIF();
    WifiIF(const WifiIF& ) = delete;
    WifiIF& operator=(const WifiIF& ) = delete;

    WifiIFPrivate* mWifiPriv {nullptr};

    std::shared_mutex mMutex;
    std::string mIPAddress {""};
    Wifi_SpeedMode mSpeedMode {Wifi_SpeedMode::OFF};
};


class WifiAdapter {
    friend class WifiIF;
    friend class WifiIFPrivate;
public:
protected:
    WifiAdapter(WifiIF& interface);
    WifiAdapter(const WifiAdapter&) = delete;
    WifiAdapter& operator=(const WifiAdapter&) = delete;

    WifiIF& mWifiIF;

    mutable WifiIF::MutexWrapper mMutex;
};

#endif // WIFIIF_H
