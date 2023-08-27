#ifndef WIFIINTERFACE_H
#define WIFIINTERFACE_H

#include <Common/AbstractInterface.h>
#include <shared_mutex>
#include <unordered_map>
#include "Signal.h"

struct WifiDevice {
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

    State getState() const
    {
        return mState;
    }

    enum class WifiSpeedMode {
        Off = 0,
        Weakness,
        Weak,
        Medium,
        Strong
    };

    State mState;
    DeviceType mDeviceType;
    std::string mAddress;
    std::string mName;

    WifiDevice(const std::string& addr, const std::string& name)
        : mState(State::UnknownState), mDeviceType(DeviceType::Unknown), mAddress(addr), mName(name)
    {
    }
};

class WifiIFConnect;
class WifiAdapter;
class WifiDevice;
class WifiInterface final : public AbstractInterface {
    friend class WifiIFConnect;
    friend class WifiAdapter;
    friend class WifiDevice;
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
    static WifiInterface* instance();
    ~WifiInterface();

    WifiAdapter& getAdapter()
    {
        return (*mAdapter);
    }

    bool doConnect() override;
    bool doDisconnect() override;

protected:
    WifiInterface();
    WifiInterface(const WifiInterface& ) = delete;
    WifiInterface& operator=(const WifiInterface& ) = delete;

    std::shared_mutex mMutex;
    WifiIFConnect* mWifiConnect {nullptr};
    WifiAdapter* mAdapter {nullptr};
};

class WifiAdapter {
    friend class WifiInterface;
    friend class WifiIFConnect;
public:
    std::vector<WifiDevice*> getDevices() const;
    std::vector<WifiDevice*> getUnpairedDevices() const;
    std::vector<WifiDevice*> getPairedDevice() const;
    WifiDevice* getConnectedDevice() const;

    signal::Signal<void(const WifiDevice::WifiSpeedMode&)> onWifiSpeedModeChanged;
    signal::Signal<void(const WifiDevice::State&, const WifiDevice::State&)> onDeviceStateChanged;
    signal::Signal<void(WifiDevice*)> onPairedDeviceChanged;
    signal::Signal<void(WifiDevice*)> onConnectedDeviceChanged;

protected:
    WifiAdapter(WifiInterface& interface);
    WifiAdapter(const WifiAdapter&) = delete;
    WifiAdapter& operator=(const WifiAdapter&) = delete;

    WifiInterface& mWifiIF;
    mutable WifiInterface::MutexWrapper mMutex;

    std::string mDeviceName {""};
    std::unordered_map<std::string, WifiDevice*> mDeviceTable;
};

#endif // WIFIINTERFACE_H
