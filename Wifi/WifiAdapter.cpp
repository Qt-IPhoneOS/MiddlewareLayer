#include "WifiAdapter.h"
#include "WifiAdapterConnect.cpp"

WifiAdapter::WifiAdapter()
{
    mConnect = new WifiAdapterConnect(*this);
}

WifiAdapter::~WifiAdapter()
{
    delete mConnect;
}

WifiAdapter *WifiAdapter::instance()
{
    static WifiAdapter* ins = new WifiAdapter();
    return ins;
}

bool WifiAdapter::doConnect()
{
    if (mConnect->mProxy == nullptr)
        return false;

    mConnect->mProxy->connectService();
    return true;
}

void WifiAdapter::setEnableWifi(const bool& enable)
{
    if (mConnect->mProxy == nullptr)
        return;

    mConnect->mProxy->setEnableWifi(enable);
}

void WifiAdapter::connectDevice(const std::string &address)
{
    if (mConnect->mProxy == nullptr)
        return;

    mConnect->mProxy->connectDevice(address);
}

bool WifiAdapter::getEnableWifi()
{
    if (mConnect->mProxy == nullptr)
        return false;

    return mConnect->mProxy->getEnableWifi().get();
}

void WifiAdapter::startDiscovery()
{
    if (mConnect->mProxy == nullptr)
        return;

    return mConnect->mProxy->startDiscovery();
}

WifiDevice *WifiAdapter::getDevice(const std::string &address)
{
    std::unordered_map<std::string, WifiDevice*>::iterator it = mDeviceTable.find(address);
    if (it != mDeviceTable.end())
    {
        return it->second;
    }

    return nullptr;
}

bool WifiAdapter::doDisconnect()
{
    if (mConnect->mProxy == nullptr)
        return false;

    mConnect->mProxy->disconnectService();
    return true;
}

std::vector<WifiDevice*> WifiAdapter::getDevices() const
{
    return {};
}

std::vector<WifiDevice*> WifiAdapter::getUnpairedDevices() const
{
    return {};
}

std::vector<WifiDevice*> WifiAdapter::getPairedDevice() const
{
    return {};
}

WifiDevice* WifiAdapter::getConnectedDevice() const
{
    return nullptr;
}
