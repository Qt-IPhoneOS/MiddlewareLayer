#include "WifiInterface.h"

WifiAdapter::WifiAdapter(WifiInterface &interface):mWifiIF(interface), mMutex(mWifiIF.mMutex)
{
}

std::vector<WifiDevice*> WifiAdapter::getDevices() const
{

}

std::vector<WifiDevice*> WifiAdapter::getUnpairedDevices() const
{

}

std::vector<WifiDevice*> WifiAdapter::getPairedDevice() const
{

}

WifiDevice* WifiAdapter::getConnectedDevice() const
{
    for (std::unordered_map<std::string, WifiDevice*>::iterator it = mWifiIF.mAdapter->mDeviceTable.begin(); it != mWifiIF.mAdapter->mDeviceTable.end(); ++it)
    {
        if (it->second->mDeviceType == WifiDevice::DeviceType::Connected)
        {
            return it->second;
        }
    }
}

