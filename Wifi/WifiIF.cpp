#include "WifiIF.h"
#include <Wifi/WifiServiceAdapter.h>
#include <QDebug>

/**
 * WifiIFPrivate
*/
class WifiIFPrivate {
public:
    WifiIFPrivate(WifiIF& interface);
    ~WifiIFPrivate();

    WifiIF& m_wifiIF;
    WifiServiceAdapter* mWifiServiceAdapter {nullptr};

    void connectEvent();
    void disconnectEvent();

    void responseLocalIPAddress(const std::string& address);
    void responseWifiSpeedMode(const Wifi_SpeedMode& speedMode);
};

WifiIFPrivate::WifiIFPrivate(WifiIF &interface) : m_wifiIF(interface), mWifiServiceAdapter(WifiServiceAdapter::instance())
{
    mWifiServiceAdapter->connectEvent.reqCallbackFunc(std::bind(&WifiIFPrivate::connectEvent, this));
    mWifiServiceAdapter->disconnectEvent.reqCallbackFunc(std::bind(&WifiIFPrivate::disconnectEvent, this));
}

WifiIFPrivate::~WifiIFPrivate()
{

}

void WifiIFPrivate::connectEvent()
{
    mWifiServiceAdapter->onGetLocalIPAddress.reqCallbackFunc(std::bind(&WifiIFPrivate::responseLocalIPAddress, this, std::placeholders::_1));
    mWifiServiceAdapter->onGetWifiSpeedMode.reqCallbackFunc(std::bind(&WifiIFPrivate::responseWifiSpeedMode, this, std::placeholders::_1));
}

void WifiIFPrivate::disconnectEvent()
{
    mWifiServiceAdapter->connectEvent.unReqCallbackFunc();
    mWifiServiceAdapter->disconnectEvent.unReqCallbackFunc();
    mWifiServiceAdapter->onGetLocalIPAddress.unReqCallbackFunc();
    mWifiServiceAdapter->onGetWifiSpeedMode.unReqCallbackFunc();
}

void WifiIFPrivate::responseLocalIPAddress(const std::string& address)
{
    qWarning() << __FUNCTION__ << " address: " << address;
    {
        std::unique_lock<std::shared_mutex> lock(m_wifiIF.m_mutex);
        m_wifiIF.m_IPAddress = address;
    }
    m_wifiIF.onIPAddressChanged(address);
}

void WifiIFPrivate::responseWifiSpeedMode(const Wifi_SpeedMode& speedMode)
{
    qWarning() << __FUNCTION__ << " speedMode: " << (int)speedMode;
    {
        std::unique_lock<std::shared_mutex> lock(m_wifiIF.m_mutex);
        m_wifiIF.m_speedMode = static_cast<WifiIF::Wifi_SpeedMode>(speedMode);
    }
    m_wifiIF.onWifiSpeedModeChanged(static_cast<WifiIF::Wifi_SpeedMode>(speedMode));
}


/**
 * WifiIF
*/
WifiIF::WifiIF()
{
    m_privWifi = new WifiIFPrivate(*this);
    m_wifiServiceProxy = WifiServiceProxy::instance();

    if (m_wifiServiceProxy == nullptr)
        throw std::runtime_error("Create WifiService backend is failed");
}

WifiIF::~WifiIF()
{
    delete m_privWifi;
}

WifiIF *WifiIF::instance()
{
    static WifiIF* ins = new WifiIF();
    return ins;
}

bool WifiIF::doConnect()
{
    m_wifiServiceProxy->connectService();
    return true;
}

bool WifiIF::doDisconnect()
{
    m_wifiServiceProxy->disconnectService();
    return true;
}
