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
    void updateConnectedDevice(const WifiDeviceInfo& );
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
                const WifiPairedDeviceInfo& devInfo = pairedDevices[i];

                std::unordered_map<std::string, WifiDevice*>::iterator it = mAdapter.mDeviceTable.find(devInfo.mWifiAddress);
                if (it != mAdapter.mDeviceTable.end())
                {
                    if (it->second->getDeviceType() == WifiDevice::DeviceType::Paired)
                        continue;

                    it->second->setData(WifiDevice::DeviceProperty::DeviceType, WifiDevice::DeviceType::Paired);
                    changeFlg = true;
                }
                else
                {
                    WifiDevice* device = new WifiDevice(devInfo.mName, devInfo.mWifiAddress);
                    device->setData(WifiDevice::DeviceProperty::DeviceType, WifiDevice::DeviceType::Paired);
                    changeFlg = true;
                    mAdapter.mDeviceTable.emplace(devInfo.mWifiAddress, device);
                }
            }
        }

        if (changeFlg)
        {
            std::vector<WifiDevice*> temp;
            for (std::unordered_map<std::string, WifiDevice*>::iterator it = mAdapter.mDeviceTable.begin(); it != mAdapter.mDeviceTable.end(); ++it)
            {
                if (it->second->getDeviceType() == WifiDevice::DeviceType::Paired)
                {
                    temp.push_back(it->second);
                }
            }
            if (temp.size())
                mAdapter.onPairedDeviceChanged(temp);
        }
    }
}

void WifiAdapterConnect::updateConnectedDevice(const WifiDeviceInfo& connectedDevice)
{
    std::unordered_map<std::string, WifiDevice*>::iterator it = mAdapter.mDeviceTable.find(connectedDevice.mWifiAddress);
    if (it != mAdapter.mDeviceTable.end())
    {
        if (it->second->getDeviceType() != WifiDevice::DeviceType::Connected)
        {
            it->second->setData(WifiDevice::DeviceProperty::DeviceType, WifiDevice::DeviceType::Connected);
            mAdapter.onConnectedDeviceChanged(it->second);
            return;
        }
    }

    WifiDevice* device = new WifiDevice(connectedDevice.mName, connectedDevice.mWifiAddress);
    device->setData(WifiDevice::DeviceProperty::DeviceType, WifiDevice::DeviceType::Connected);
    mAdapter.mDeviceTable.emplace(connectedDevice.mWifiAddress, device);
}

void WifiAdapterConnect::updateWifiEnable(const bool &enable)
{
    std::shared_lock<std::shared_mutex> lock(mAdapter.mMutex);
    mAdapter.onWifiEnableChanged(enable);
}
