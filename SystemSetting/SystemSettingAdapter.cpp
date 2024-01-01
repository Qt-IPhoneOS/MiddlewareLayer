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

void SystemSettingAdapter::setIsAllowOthersToJoin(const bool &status)
{
    mSysConnect->mSysProxy.setAllowOthersToJoinNetwork(static_cast<service::AllowOthersToJoinTypes>(status));
}

void SystemSettingAdapter::setIsMaximizeCompatibility(const bool &status)
{
    mSysConnect->mSysProxy.setMaximizeCompatibility(static_cast<service::MaximizeCompatibilityTypes>(status));
}

