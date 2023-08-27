#include "WifiInterface.h"
#include "WifiIFConnect.cpp"

WifiInterface::WifiInterface()
{
    mWifiConnect = new WifiIFConnect(*this);
    mAdapter = new WifiAdapter(*this);
}

WifiInterface::~WifiInterface()
{
    delete mWifiConnect;
    delete mAdapter;
}

WifiInterface *WifiInterface::instance()
{
    static WifiInterface* ins = new WifiInterface();
    return ins;
}

bool WifiInterface::doConnect()
{
    mWifiConnect->mWifiServiceProxy->connectService();
    return true;
}

bool WifiInterface::doDisconnect()
{
    mWifiConnect->mWifiServiceProxy->disconnectService();
    return true;
}
