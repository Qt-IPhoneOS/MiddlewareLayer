#include "WifiAdapter.h"
#include <Wifi/WifiServiceEvent.h>
#include <Wifi/WifiServiceProxy.h>
#include <QDebug>

class WifiAdapterConnect {
    friend class WifiAdapter;
public:
    WifiAdapterConnect(WifiAdapter& interface);
    ~WifiAdapterConnect();

    WifiAdapter& mAdapter;
    WifiServiceEvent* mEvent {nullptr};
    WifiServiceProxy* mProxy {nullptr};

    void connectEvent();
    void disconnectEvent();

    void updateWifiEnable(const bool&);
    void updatePairedDevices(const std::vector<WifiPairedDeviceInfo>& );
    void updateConnectedDevice(const WifiPairedDeviceInfo& );
};

WifiAdapterConnect::WifiAdapterConnect(WifiAdapter &instance) : mAdapter(instance), mEvent(WifiServiceEvent::instance()), mProxy(WifiServiceProxy::instance())
{
    if (mProxy == nullptr)
        throw std::runtime_error("Create WifiService backend is failed");

    mEvent->connectEvent.reqCallbackFunc(std::bind(&WifiAdapterConnect::connectEvent, this));
    mEvent->disconnectEvent.reqCallbackFunc(std::bind(&WifiAdapterConnect::disconnectEvent, this));
}

WifiAdapterConnect::~WifiAdapterConnect()
{
}

void WifiAdapterConnect::connectEvent()
{
    mEvent->notifyUpdatePairedDevices.reqCallbackFunc(std::bind(&WifiAdapterConnect::updatePairedDevices, this, std::placeholders::_1));
    mEvent->notifyUpdateConnectedDevice.reqCallbackFunc(std::bind(&WifiAdapterConnect::updateConnectedDevice, this, std::placeholders::_1));
    mEvent->notifyUpdateEnableWifi.reqCallbackFunc(std::bind(&WifiAdapterConnect::updateWifiEnable, this, std::placeholders::_1));
}

void WifiAdapterConnect::disconnectEvent()
{
    mEvent->connectEvent.unReqCallbackFunc();
    mEvent->disconnectEvent.unReqCallbackFunc();
    mEvent->notifyUpdatePairedDevices.unReqCallbackFunc();
    mEvent->notifyUpdateConnectedDevice.unReqCallbackFunc();
    mEvent->notifyUpdateEnableWifi.unReqCallbackFunc();
}

void WifiAdapterConnect::updatePairedDevices(const std::vector<WifiPairedDeviceInfo>& pairedDevices)
{
    {
        bool changeFlg = false;
        for (size_t i = 0; i < pairedDevices.size(); i++)
        {
            {
                std::unique_lock<std::shared_mutex> lock(mAdapter.mMutex);
                const WifiPairedDeviceInfo& pairedDevice = pairedDevices[i];
                std::unordered_map<std::string, WifiDevice*>::iterator it = mAdapter.mDeviceTable.find(pairedDevice.mDeviceInfo.mAddress);
                if (it != mAdapter.mDeviceTable.end())
                {
//                    if (it->second->getDeviceType() == WifiDevice::DeviceType::Paired)
//                        continue;

                    changeFlg = true;
                }
                else
                {
                    WifiDevice* device = new WifiDevice({pairedDevice.mDeviceInfo.mName, pairedDevice.mDeviceInfo.mAddress, static_cast<bool>(pairedDevice.mDeviceInfo.mPrivateAddr)});
                    changeFlg = true;
                    mAdapter.mDeviceTable.emplace(pairedDevice.mDeviceInfo.mAddress, device);
                }
            }
        }

        if (changeFlg)
        {
            std::vector<WifiDevice*> temp;
            for (std::unordered_map<std::string, WifiDevice*>::iterator it = mAdapter.mDeviceTable.begin(); it != mAdapter.mDeviceTable.end(); ++it)
            {
                temp.push_back(it->second);
//                if (it->second->getDeviceType() == WifiDevice::DeviceType::Paired)
//                {
//                }
            }
            if (temp.size())
                mAdapter.onPairedDeviceChanged(temp);
        }
    }
}

void WifiAdapterConnect::updateConnectedDevice(const WifiPairedDeviceInfo& connectedDevice)
{
    std::unordered_map<std::string, WifiDevice*>::iterator it = mAdapter.mDeviceTable.find(connectedDevice.mDeviceInfo.mAddress);
    if (it != mAdapter.mDeviceTable.end())
    {
//        if (it->second->getDeviceType() != WifiDevice::DeviceType::Connected)
//        {
//            mAdapter.onConnectedDeviceChanged(it->second);
//        }
        return;
    }

    WifiDevice* device = new WifiDevice({connectedDevice.mDeviceInfo.mName, connectedDevice.mDeviceInfo.mAddress, static_cast<bool>(connectedDevice.mDeviceInfo.mPrivateAddr)});
    mAdapter.mDeviceTable.emplace(connectedDevice.mDeviceInfo.mAddress, device);
    mAdapter.onConnectedDeviceChanged(device);
}

void WifiAdapterConnect::updateWifiEnable(const bool &enable)
{
    std::shared_lock<std::shared_mutex> lock(mAdapter.mMutex);
    mAdapter.onWifiEnableChanged(enable);
}
