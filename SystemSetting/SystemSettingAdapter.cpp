#include "SystemSettingAdapter.h"
#include "SystemSettingConnect.cpp"

using namespace midlayer;

SystemSettingAdapter::SystemSettingAdapter()
    : mSysConnect(new SystemSettingConnect(*this))
{

}

SystemSettingAdapter::~SystemSettingAdapter() {

}

SystemSettingAdapter& SystemSettingAdapter::instance() {
    static SystemSettingAdapter instance;
    return instance;
}

bool SystemSettingAdapter::doConnect() {

}

bool SystemSettingAdapter::doDisconnect() {

}

SystemSettingAdapter::AirplaneModeEnums SystemSettingAdapter::getAirplaneMode() const {
    return mAirplaneMode;
}

void SystemSettingAdapter::setNewAirplaneMode(const AirplaneModeEnums& newAirplaneMode) {
    mSysConnect->mSysProxy.setAirplaneMode(static_cast<service::AirplaneModeTypes>(newAirplaneMode));
}

bool SystemSettingAdapter::getIsPersonalHotspot() const
{

}

void SystemSettingAdapter::setIsPersonalHotspot(const bool newStatus)
{
    mSysConnect->mSysProxy.setIsPersonalHotspotActive(newStatus);
}

bool SystemSettingAdapter::getIsAllowJoinNetwork() const
{

}

void SystemSettingAdapter::setNewIsAllowJoinNetwork(const bool newStatus)
{

}

bool SystemSettingAdapter::getIsPersonalHotspotActive() const
{

}

void SystemSettingAdapter::setIsPersonalHotspotActive(const bool newStatus)
{
    mSysConnect->mSysProxy.setIsPersonalHotspotActive(newStatus);
}

