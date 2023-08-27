#include "WifiInterface.h"

WifiAdapter::WifiAdapter(WifiInterface &interface):mWifiIF(interface), mMutex(mWifiIF.m_mutex)
{
}
