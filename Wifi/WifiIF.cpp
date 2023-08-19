#include "WifiIF.h"
#include <Wifi/WifiServiceEvent.h>
#include <Wifi/WifiServiceProxy.h>
#include <QDebug>

/**
 * WifiIFPrivate
*/
class WifiIFPrivate {
public:
    WifiIFPrivate(WifiIF& interface);
    ~WifiIFPrivate();

    WifiIF& mWifiIF;
    WifiServiceEvent* mWifiServiceEvent {nullptr};
    WifiServiceProxy* mWifiServiceProxy {nullptr};

    void connectEvent();
    void disconnectEvent();

    void responseLocalIPAddress(const std::string& address);
    void responseWifiSpeedMode(const WifiSpeedMode& speedMode);
};

WifiIFPrivate::WifiIFPrivate(WifiIF &interface) : mWifiIF(interface), mWifiServiceEvent(WifiServiceEvent::instance()), mWifiServiceProxy(WifiServiceProxy::instance())
{
    mWifiServiceEvent->connectEvent.reqCallbackFunc(std::bind(&WifiIFPrivate::connectEvent, this));
    mWifiServiceEvent->disconnectEvent.reqCallbackFunc(std::bind(&WifiIFPrivate::disconnectEvent, this));
}

WifiIFPrivate::~WifiIFPrivate()
{

}

void WifiIFPrivate::connectEvent()
{
    mWifiServiceEvent->onGetLocalIPAddress.reqCallbackFunc(std::bind(&WifiIFPrivate::responseLocalIPAddress, this, std::placeholders::_1));
    mWifiServiceEvent->onGetWifiSpeedMode.reqCallbackFunc(std::bind(&WifiIFPrivate::responseWifiSpeedMode, this, std::placeholders::_1));
}

void WifiIFPrivate::disconnectEvent()
{
    mWifiServiceEvent->connectEvent.unReqCallbackFunc();
    mWifiServiceEvent->disconnectEvent.unReqCallbackFunc();
    mWifiServiceEvent->onGetLocalIPAddress.unReqCallbackFunc();
    mWifiServiceEvent->onGetWifiSpeedMode.unReqCallbackFunc();
}

void WifiIFPrivate::responseLocalIPAddress(const std::string& address)
{
    qWarning() << __FUNCTION__ << " address: " << address;
    {
        std::unique_lock<std::shared_mutex> lock(mWifiIF.mMutex);
        mWifiIF.mIPAddress = address;
    }
    mWifiIF.onIPAddressChanged(address);
}

void WifiIFPrivate::responseWifiSpeedMode(const WifiSpeedMode& speedMode)
{
    qWarning() << __FUNCTION__ << " speedMode: " << (int)speedMode;
    {
        std::unique_lock<std::shared_mutex> lock(mWifiIF.mMutex);
        mWifiIF.mSpeedMode = static_cast<WifiIF::WifiSpeedMode>(speedMode);
    }
    mWifiIF.onWifiSpeedModeChanged(static_cast<WifiIF::WifiSpeedMode>(speedMode));
}


/**
 * WifiIF
*/
WifiIF::WifiIF()
{
    mWifiPriv = new WifiIFPrivate(*this);
    mWifiPriv->mWifiServiceProxy = WifiServiceProxy::instance();

    if (mWifiPriv->mWifiServiceProxy == nullptr)
        throw std::runtime_error("Create WifiService backend is failed");
}

WifiIF::~WifiIF()
{
    delete mWifiPriv;
}

WifiIF *WifiIF::instance()
{
    static WifiIF* ins = new WifiIF();
    return ins;
}

bool WifiIF::doConnect()
{
    mWifiPriv->mWifiServiceProxy->connectService();
    return true;
}

bool WifiIF::doDisconnect()
{
    mWifiPriv->mWifiServiceProxy->disconnectService();
    return true;
}
