#include "WifiIF.h"

WifiAdapter::WifiAdapter(WifiIF &interface):mWifiIF(interface), mMutex(mWifiIF.m_mutex)
{
}
