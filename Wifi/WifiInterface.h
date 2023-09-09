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

    std::string mName, mPassword, mAddress, mIPAddress, mSubnet, mRouter;
    bool mPrivateAddr, mLowDataMode, mLimitIP;
    SpeedMode mSpeedMode;
    IP mIP;
    DeviceType mDeviceType;
    DNS mDNS;
    Proxy mProxy;
    State mState;

    WifiDevice(std::string name, std::string addr, DeviceType type = DeviceType::Unknown, SpeedMode speedMode = SpeedMode::Strong, bool privateAddr = true, IP ip = IP::Automatic,
               DNS dns = DNS::Automatic, Proxy proxy = Proxy::Automatic, std::string password = "", bool lowDataMode = true, bool limitIP = false,
               std::string ipAddr = "", std::string subnetMask = "", std::string router = "") {
        mName = name;
        mAddress = addr;
        mSpeedMode = speedMode;
        mDeviceType = type;
        mPrivateAddr = privateAddr;
        mIP = ip;
        mDNS = dns;
        mProxy = proxy;
        mPassword = password;
        mLowDataMode = lowDataMode;
        mLimitIP = limitIP;
        mIPAddress = ipAddr;
        mSubnet = subnetMask;
        mRouter = router;
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

    signal::Signal<void(const WifiDevice::SpeedMode&)> onWifiSpeedModeChanged;
    signal::Signal<void(const WifiDevice::State&, const WifiDevice::State&)> onDeviceStateChanged;
    signal::Signal<void(std::vector<WifiDevice*>)> onPairedDeviceChanged;
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
