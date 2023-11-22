#include "SystemSettingAdapter.h"

SystemSettingAdapter::SystemSettingAdapter() 
    // : mSysProxy(SystemSettingProxy::getInstance())
    , mSysEvent(SystemSettingEvent::getInstance())
{
    mSysEvent.notifyUpdateAirplaneMode.reqCallbackFunc(std::bind(&SystemSettingAdapter::updateHandleDataAirplaneMode, this, std::placeholders::_1));
}

SystemSettingAdapter::~SystemSettingAdapter() {

}

SystemSettingAdapter& SystemSettingAdapter::getInstance() {
    static SystemSettingAdapter instance;
    return instance;
}

bool SystemSettingAdapter::doConnect() {
    mSysProxy.connectService();
}

bool SystemSettingAdapter::doDisconnect() {
    mSysProxy.disconnectService();
}

bool SystemSettingAdapter::setNewAirplaneMode(const AirplaneModeEnums& newAirplaneMode) {
    // mSysProxy.setAirplaneMode(static_cast<AirplaneModeTypes>(newAirplaneMode));
}


void SystemSettingAdapter::updateHandleDataAirplaneMode(const AirplaneModeTypes& airplaneMode) {
    
}