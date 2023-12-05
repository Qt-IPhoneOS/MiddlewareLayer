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

    void onServiceConnected();
    void onServiceDisconnected();

    void notifyPairedDeviceList();

    void updateWifiEnable(const bool&);
    void updatePairedDeviceList();
    void updateConnectedDevice(const WifiDeviceInfo& );
    void updateAuthenStatus(const std::string&, const WifiAuthenDeviceStatus&);
    void removeDiscoveryDevice(const std::string&);
    void addDiscoveryDevice(const WifiDiscoveryDeviceInfo&);
};

WifiAdapterConnect::WifiAdapterConnect(WifiAdapter &instance) : mAdapter(instance), mEvent(WifiServiceEvent::instance()), mProxy(WifiServiceProxy::instance())
{
    if (mProxy == nullptr)
        throw std::runtime_error("Create WifiService backend is failed");

    mEvent->notifyConnectedEvent.reqCallbackFunc(std::bind(&WifiAdapterConnect::onServiceConnected, this));
    mEvent->notifyDisconnectedEvent.reqCallbackFunc(std::bind(&WifiAdapterConnect::onServiceDisconnected, this));
}

WifiAdapterConnect::~WifiAdapterConnect()
{
}

void WifiAdapterConnect::onServiceConnected()
{
    mEvent->notifyPairedDeviceListChanged.reqCallbackFunc(std::bind(&WifiAdapterConnect::updatePairedDeviceList, this));
    mEvent->notifyUpdateConnectedDevice.reqCallbackFunc(std::bind(&WifiAdapterConnect::updateConnectedDevice, this, std::placeholders::_1));
    mEvent->notifyUpdateEnableWifi.reqCallbackFunc(std::bind(&WifiAdapterConnect::updateWifiEnable, this, std::placeholders::_1));
    mEvent->notifyUpdateAuthenStatus.reqCallbackFunc(std::bind(&WifiAdapterConnect::updateAuthenStatus, this, std::placeholders::_1, std::placeholders::_2));
    mEvent->notifyAddDiscoveryDevice.reqCallbackFunc(std::bind(&WifiAdapterConnect::addDiscoveryDevice, this, std::placeholders::_1));
    mEvent->notifyRemoveDiscoveryDevice.reqCallbackFunc(std::bind(&WifiAdapterConnect::removeDiscoveryDevice, this, std::placeholders::_1));
}

void WifiAdapterConnect::onServiceDisconnected()
{
    mEvent->notifyConnectedEvent.unReqCallbackFunc();
    mEvent->notifyDisconnectedEvent.unReqCallbackFunc();
    mEvent->notifyPairedDeviceListChanged.unReqCallbackFunc();
    mEvent->notifyUpdateConnectedDevice.unReqCallbackFunc();
    mEvent->notifyUpdateEnableWifi.unReqCallbackFunc();
    mEvent->notifyUpdateAuthenStatus.unReqCallbackFunc();
    mEvent->notifyAddDiscoveryDevice.unReqCallbackFunc();
    mEvent->notifyRemoveDiscoveryDevice.unReqCallbackFunc();
}

void WifiAdapterConnect::notifyPairedDeviceList()
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
        mAdapter.onPairedDeviceListChanged(temp);
}

void WifiAdapterConnect::updatePairedDeviceList()
{
    for (auto item : mAdapter.mDeviceTable)
    {
        if (item.second->getDeviceType() == WifiDevice::DeviceType::Paired)
        {
            item.second->setValue(WifiDevice::DeviceProperty::DeviceType, WifiDevice::DeviceType::Unknown);
        }
    }

    {
        auto list = mProxy->getPairedDeviceList().get();
        std::unique_lock<std::shared_mutex> lock(mAdapter.mMutex);
        for (size_t i = 0; i < list.size(); i++)
        {
            {
                const WifiDeviceInfo& pairedDevice = list[i];
                std::unordered_map<std::string, WifiDevice*>::iterator it = mAdapter.mDeviceTable.find(pairedDevice.mDeviceInfo.mAddress);
                if (it != mAdapter.mDeviceTable.end())
                {
                    if (it->second->getDeviceType() == WifiDevice::DeviceType::Paired)
                        continue;

                    it->second->setValue(WifiDevice::DeviceProperty::DeviceType, WifiDevice::DeviceType::Paired);
                }
                else
                {
                    WifiDevice* device = new WifiDevice({pairedDevice.mDeviceInfo.mName, pairedDevice.mDeviceInfo.mAddress, static_cast<bool>(pairedDevice.mDeviceInfo.mPrivateAddr)});
                    device->setValue(WifiDevice::DeviceProperty::DeviceType, WifiDevice::DeviceType::Paired);
                    mAdapter.mDeviceTable.emplace(pairedDevice.mDeviceInfo.mAddress, device);
                }
            }
        }
    }

    notifyPairedDeviceList();
}

void WifiAdapterConnect::updateConnectedDevice(const WifiDeviceInfo& connectedDevice)
{
    std::unique_lock<std::shared_mutex> lock(mAdapter.mMutex);

    std::unordered_map<std::string, WifiDevice*>::iterator it = mAdapter.mDeviceTable.find(connectedDevice.mDeviceInfo.mAddress);
    mAdapter.mConnectingAddr = "";
    if (it != mAdapter.mDeviceTable.end())
    {
        if (it->second->getDeviceType() != WifiDevice::DeviceType::Connected)
        {
            it->second->setValue(WifiDevice::DeviceProperty::DeviceType, WifiDevice::DeviceType::Connected);
        }
        mAdapter.onConnectedDeviceChanged(it->second);
        return;
    }

    WifiDevice* device = new WifiDevice({connectedDevice.mDeviceInfo.mName, connectedDevice.mDeviceInfo.mAddress, static_cast<bool>(connectedDevice.mDeviceInfo.mPrivateAddr)});
    device->setValue(WifiDevice::DeviceProperty::DeviceType, WifiDevice::DeviceType::Connected);
    mAdapter.mDeviceTable.emplace(connectedDevice.mDeviceInfo.mAddress, device);
    mAdapter.onConnectedDeviceChanged(device);
}

void WifiAdapterConnect::updateWifiEnable(const bool &enable)
{
    std::unique_lock<std::shared_mutex> lock(mAdapter.mMutex);
    mAdapter.onWifiEnableChanged(enable);
}

void WifiAdapterConnect::updateAuthenStatus(const std::string& addr, const WifiAuthenDeviceStatus& status)
{
    std::unique_lock<std::shared_mutex> lock(mAdapter.mMutex);

    WifiDevice* device = mAdapter.getDevice(addr);
    if (device == nullptr)
        return;

    WifiAdapter::State oldState, newState;
    oldState = newState = mAdapter.mAuthenState;
    mAdapter.mConnectingAddr = addr;


    switch (status) {
    case WifiAuthenDeviceStatus::CheckingSSID: {
        if (mAdapter.mAuthenState == WifiAdapter::State::CheckingSSIDState || mAdapter.mAuthenState == WifiAdapter::State::UnpairedState) {
            newState = WifiAdapter::State::CheckingSSIDState;
            if (device->getDeviceType() == WifiDevice::DeviceType::Unpaired)
            {
                device->setValue(WifiDevice::DeviceProperty::DeviceType, WifiDevice::DeviceType::Pairing);
                mAdapter.onRemoveDiscoveryDevice(addr);
            }
        }
        break;
    }
    case WifiAuthenDeviceStatus::CheckedSSID: {
        if (mAdapter.mAuthenState == WifiAdapter::State::CheckingSSIDState)
            newState = WifiAdapter::State::CheckedSSIDSuccessState;
        break;
    }
    case WifiAuthenDeviceStatus::Authencating: {
        if (mAdapter.mAuthenState == WifiAdapter::State::WaitingAuthenState || mAdapter.mAuthenState == WifiAdapter::State::PairedState)
            newState = WifiAdapter::State::WaitingAuthenState;

        if (device->getDeviceType() == WifiDevice::DeviceType::Paired)
        {
            device->setValue(WifiDevice::DeviceProperty::DeviceType, WifiDevice::DeviceType::Authenticating);
            notifyPairedDeviceList();
        }
        break;
    }
    case WifiAuthenDeviceStatus::AuthenSuccess: {
        if (mAdapter.mAuthenState == WifiAdapter::State::WaitingAuthenState)
            newState = WifiAdapter::State::AuthenSuccessState;
        break;
    }
    case WifiAuthenDeviceStatus::Fail: {
        if (mAdapter.mAuthenState == WifiAdapter::State::WaitingAuthenState)
        {
            newState = WifiAdapter::State::AuthenFailState;
            if (device->getDeviceType() == WifiDevice::DeviceType::Authenticating)
            {
                device->setValue(WifiDevice::DeviceProperty::DeviceType, WifiDevice::DeviceType::Paired);
                notifyPairedDeviceList();
            }
        }
        else if (mAdapter.mAuthenState == WifiAdapter::State::CheckingSSIDState)
        {
            newState = WifiAdapter::State::CheckedSSIDFailState;
            if (device->getDeviceType() == WifiDevice::DeviceType::Pairing)
            {
                device->setValue(WifiDevice::DeviceProperty::DeviceType, WifiDevice::DeviceType::Unpaired);
                mAdapter.onAddDiscoveryDevice(device);
            }
        }
        WifiDevice* connectedDevice = mAdapter.getConnectedDevice();
        if (connectedDevice != nullptr)
        {
            mAdapter.onConnectedDeviceChanged(connectedDevice);
        }
        mAdapter.mConnectingAddr = "";
        break;
    }
    default:
        break;
    }

    if (oldState != newState)
    {
        mAdapter.onDeviceStateChanged(device->getDeviceInfo().mName, oldState, newState);
        mAdapter.mAuthenState = newState;
    }
}

void WifiAdapterConnect::removeDiscoveryDevice(const std::string &addr)
{
    std::unique_lock<std::shared_mutex> lock(mAdapter.mMutex);
    std::unordered_map<std::string, WifiDevice*>::iterator it = mAdapter.mDeviceTable.find(addr);
    if (it != mAdapter.mDeviceTable.end())
    {
        if (it->second->getDeviceType() == WifiDevice::DeviceType::Unpaired)
        {
            it->second->setValue(WifiDevice::DeviceProperty::DeviceType, WifiDevice::DeviceType::Unknown);
        }

        mAdapter.onRemoveDiscoveryDevice(addr);
    }
}

void WifiAdapterConnect::addDiscoveryDevice(const WifiDiscoveryDeviceInfo &device)
{
    std::unique_lock<std::shared_mutex> lock(mAdapter.mMutex);
    std::unordered_map<std::string, WifiDevice*>::iterator it = mAdapter.mDeviceTable.find(device.mAddress);
    if (it != mAdapter.mDeviceTable.end())
    {
        if (it->second->getDeviceType() != WifiDevice::DeviceType::Unpaired)
        {
            it->second->setValue(WifiDevice::DeviceProperty::DeviceType, WifiDevice::DeviceType::Unpaired);
        }
        return;
    }

    WifiDevice *newDev = new WifiDevice({device.mName, device.mAddress, static_cast<bool>(device.mPrivateAddr)});
    newDev->setValue(WifiDevice::DeviceProperty::DeviceType, WifiDevice::DeviceType::Unpaired);
    mAdapter.mDeviceTable.emplace(device.mAddress, newDev);

    mAdapter.onAddDiscoveryDevice(newDev);
}
