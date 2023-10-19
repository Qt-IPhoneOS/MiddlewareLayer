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
    mConnect->mProxy->connectService();
    return true;
}

void WifiAdapter::setEnableWifi(const bool& enable)
{
    mConnect->mProxy->setEnableWifi(enable);
}

bool WifiAdapter::getEnableWifi()
{
    return mConnect->mProxy->getEnableWifi().get();
}

bool WifiAdapter::doDisconnect()
{
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
