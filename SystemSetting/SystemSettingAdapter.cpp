#include "SystemSettingAdapter.h"
#include <SystemSetting/SystemSettingProxy.h>
SystemSettingAdapter::SystemSettingAdapter()
    : mSysConnect(new SystemSettingConnect())
{

}

SystemSettingAdapter::~SystemSettingAdapter() {

}

SystemSettingAdapter& SystemSettingAdapter::getInstance() {
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

bool SystemSettingAdapter::setNewAirplaneMode(const AirplaneModeEnums& newAirplaneMode) {
    mSysConnect->mSysProxy.setAirplaneMode(static_cast<AirplaneModeTypes>(newAirplaneMode));
}

