#include "WifiAdapter.h"
#include "WifiAdapterConnect.cpp"

#define CheckNull(Ptr) if (Ptr == nullptr)

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
    CheckNull(mConnect->mProxy)
        return;

    mConnect->mProxy->setEnableWifi(enable);
}

void WifiAdapter::connectDevice(const std::string &address)
{
    CheckNull(mConnect->mProxy)
        return;

    mConnect->mProxy->connectDevice(address);
}

bool WifiAdapter::getEnableWifi()
{
    CheckNull(mConnect->mProxy)
        return false;

    return mConnect->mProxy->getEnableWifi().get();
}

bool WifiAdapter::doDisconnect()
{
    CheckNull(mConnect->mProxy)
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
