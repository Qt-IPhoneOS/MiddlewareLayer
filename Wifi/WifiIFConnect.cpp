#include "WifiInterface.h"
#include <Wifi/WifiServiceEvent.h>
#include <Wifi/WifiServiceProxy.h>
#include <QDebug>

class WifiIFConnect {
public:
    WifiIFConnect(WifiInterface& interface);
    ~WifiIFConnect();

    WifiInterface& mWifiIF;
    WifiServiceEvent* mWifiServiceEvent {nullptr};
    WifiServiceProxy* mWifiServiceProxy {nullptr};

    void connectEvent();
    void disconnectEvent();

    void notifyWifiSpeedMode(const WifiSpeedMode& );
    void notifyUpdatePairedDevices(const std::vector<WifiPairedDeviceInfo>& );
    void notifyUpdateConnectedDevice(const WifiDeviceInfo& );
};

WifiIFConnect::WifiIFConnect(WifiInterface &interface) : mWifiIF(interface), mWifiServiceEvent(WifiServiceEvent::instance()), mWifiServiceProxy(WifiServiceProxy::instance())
{
    if (mWifiServiceProxy == nullptr)
        throw std::runtime_error("Create WifiService backend is failed");

    mWifiServiceEvent->connectEvent.reqCallbackFunc(std::bind(&WifiIFConnect::connectEvent, this));
    mWifiServiceEvent->disconnectEvent.reqCallbackFunc(std::bind(&WifiIFConnect::disconnectEvent, this));
}

WifiIFConnect::~WifiIFConnect()
{
}

void WifiIFConnect::connectEvent()
{
    mWifiServiceEvent->notifyWifiSpeedMode.reqCallbackFunc(std::bind(&WifiIFConnect::notifyWifiSpeedMode, this, std::placeholders::_1));
    mWifiServiceEvent->notifyUpdatePairedDevices.reqCallbackFunc(std::bind(&WifiIFConnect::notifyUpdatePairedDevices, this, std::placeholders::_1));
    mWifiServiceEvent->notifyUpdateConnectedDevice.reqCallbackFunc(std::bind(&WifiIFConnect::notifyUpdateConnectedDevice, this, std::placeholders::_1));
}

void WifiIFConnect::disconnectEvent()
{
    mWifiServiceEvent->connectEvent.unReqCallbackFunc();
    mWifiServiceEvent->disconnectEvent.unReqCallbackFunc();
    mWifiServiceEvent->notifyWifiSpeedMode.unReqCallbackFunc();
    mWifiServiceEvent->notifyUpdatePairedDevices.unReqCallbackFunc();
    mWifiServiceEvent->notifyUpdateConnectedDevice.unReqCallbackFunc();
}

void WifiIFConnect::notifyUpdatePairedDevices(const std::vector<WifiPairedDeviceInfo>& pairedDevices)
{
    qWarning() << "notifyUpdatePairedDevices size: " << pairedDevices.size();
    {
        bool changeFlg = false;
        for (size_t i = 0; i < pairedDevices.size(); i++)
        {
            {
                std::unique_lock<std::shared_mutex> lock(mWifiIF.mMutex);
                const WifiPairedDeviceInfo& devInfo = pairedDevices[i];
                qWarning() << devInfo.mWifiAddress;

                std::unordered_map<std::string, WifiDevice*>::iterator it = mWifiIF.mAdapter->mDeviceTable.find(devInfo.mWifiAddress);
                if (it != mWifiIF.mAdapter->mDeviceTable.end())
                {
                    if (it->second->mDeviceType == WifiDevice::DeviceType::Paired)
                        continue;

                    it->second->mDeviceType = WifiDevice::DeviceType::Paired;
                    changeFlg = true;
                }
                WifiDevice* device = new WifiDevice(devInfo.mWifiAddress, devInfo.mName);
                device->mDeviceType = WifiDevice::DeviceType::Paired;
                changeFlg = true;

                mWifiIF.mAdapter->mDeviceTable.emplace(devInfo.mWifiAddress, device);
            }
        }

        if (changeFlg)
        {
            for (std::unordered_map<std::string, WifiDevice*>::iterator it = mWifiIF.mAdapter->mDeviceTable.begin(); it != mWifiIF.mAdapter->mDeviceTable.end(); ++it)
            {
                if (it->second->mDeviceType == WifiDevice::DeviceType::Paired)
                {
                    mWifiIF.mAdapter->onPairedDeviceChanged(it->second);
                }
            }
        }
    }
}

void WifiIFConnect::notifyUpdateConnectedDevice(const WifiDeviceInfo& connectedDevice)
{
    qWarning() << __FUNCTION__ << " connectedDevice: " << connectedDevice.mWifiAddress;
    std::unordered_map<std::string, WifiDevice*>::iterator it = mWifiIF.mAdapter->mDeviceTable.find(connectedDevice.mWifiAddress);
    if (it != mWifiIF.mAdapter->mDeviceTable.end())
    {
        if (it->second->mDeviceType != WifiDevice::DeviceType::Connected)
        {
            it->second->mDeviceType = WifiDevice::DeviceType::Connected;
            mWifiIF.mAdapter->onConnectedDeviceChanged(it->second);
            return;
        }
    }

    WifiDevice* device = new WifiDevice(connectedDevice.mWifiAddress, connectedDevice.mName);
    device->mDeviceType = WifiDevice::DeviceType::Connected;
    mWifiIF.mAdapter->onConnectedDeviceChanged(device);
    mWifiIF.mAdapter->mDeviceTable.emplace(connectedDevice.mWifiAddress, device);
}

void WifiIFConnect::notifyWifiSpeedMode(const WifiSpeedMode& speedMode)
{
    mWifiIF.mAdapter->onWifiSpeedModeChanged(static_cast<WifiDevice::WifiSpeedMode>(speedMode));
}
