#include "SettingAdapter.h"
#include <SystemSetting/SystemSettingEvent.h>
#include <SystemSetting/SystemSettingProxy.h>

class SettingAdapterConnect {
    friend class SettingAdapter;
public:
    SettingAdapterConnect(SettingAdapter& _settingAdap);
    ~SettingAdapterConnect();

    SettingAdapter& mSettingAdap;
    SystemSettingProxy* mSysProxy {nullptr};
    SystemSettingEvent* mSysEvent {nullptr};

    void connectEvent();
    void disconnectEvent();

    void updateAirplaneMode(const AirplaneModeEnums&);
};

SettingAdapterConnect::SettingAdapterConnect(SettingAdapter& _settingAdap)
    : mSettingAdap(_settingAdap)
    , mSysProxy(&SystemSettingProxy::getInstance())
    , mSysEvent(&SystemSettingEvent::getInstance())
{
    if (mSysProxy == nullptr) {
        throw std::runtime_error("Create System Settin is failed");
    }
    mSysEvent->connectEvent.reqCallbackFunc(std::bind(&SettingAdapterConnect::connectEvent, this));
    mSysEvent->connectEvent.reqCallbackFunc(std::bind(&SettingAdapterConnect::disconnectEvent, this));
}

SettingAdapterConnect::~SettingAdapterConnect() {

}

void SettingAdapterConnect::connectEvent() {
    mSysEvent->notifyAirplaneMode.reqCallbackFunc(std::bind(&SettingAdapterConnect::updateAirplaneMode, this, std::placeholders::_1));
}

void SettingAdapterConnect::disconnectEvent() {
    mSysEvent->connectEvent.unReqCallbackFunc();
    mSysEvent->disconnectEvent.unReqCallbackFunc();
}


void SettingAdapterConnect::updateAirplaneMode(const AirplaneModeEnums&  _newAirplaneMode) {
    printf("\nHerreee CB wrapper in modelllllllllll");
    mSettingAdap.setAirplaneMode(static_cast<middlewarelayer::AirplaneMode>(_newAirplaneMode));
    mSettingAdap.onAirplaneModeChanged(mSettingAdap.mAirplaneMode);
}