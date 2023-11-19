#include "SettingAdapter.h"
#include "SettingAdapterConnect.cpp"

SettingAdapter::SettingAdapter() 
{
    printf("\nConstructor Adapter");
    mSettingAdapterConnect = new SettingAdapterConnect(*this);
}

SettingAdapter::~SettingAdapter() {

}

SettingAdapter& SettingAdapter::getInstance() {
    static SettingAdapter instance;
    return instance;
}

bool SettingAdapter::doConnect() {
    printf("\ninit do connect 222222222");
    if (mSettingAdapterConnect->mSysProxy == nullptr) {
        return false;
    }
    mSettingAdapterConnect->mSysProxy->connectService();
    return true;
}

bool SettingAdapter::doDisconnect() {
    if (mSettingAdapterConnect->mSysProxy == nullptr)
        return false;
    mSettingAdapterConnect->mSysProxy->disconnectService();
    return true;
}

void SettingAdapter::setAirplaneMode(const middlewarelayer::AirplaneMode& newAirplaneMode) {
    printf("\n----> THAIVD ---- setAirplaneMode in dapter");
    mSettingAdapterConnect->mSysProxy->setAirplaneMode(static_cast<AirplaneModeEnums>(newAirplaneMode));
}
