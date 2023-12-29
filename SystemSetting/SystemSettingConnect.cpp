#include <SystemSetting/SystemSettingProxy.h>
#include <SystemSetting/SystemSettingEvent.h>
#include <SystemSetting/SystemSettingAdapter.h>

namespace midlayer {

class SystemSettingConnect {
public:
    SystemSettingConnect(SystemSettingAdapter& instance);
    ~SystemSettingConnect();

    void updateHandleDataAirplaneMode(const service::AirplaneModeTypes&);
    void updatePersonalHotspot(const service::PersonalHotspotTypes&);

    service::SystemSettingProxy& mSysProxy;
    service::SystemSettingEvent& mSysEvent;
    SystemSettingAdapter& mSysAdap;
};


SystemSettingConnect::SystemSettingConnect(SystemSettingAdapter& instance)
    : mSysProxy(service::SystemSettingProxy::instance())
    , mSysEvent(service::SystemSettingEvent::instance())
    , mSysAdap(instance)
{
    mSysEvent.notifyUpdateAirplaneMode.reqCallbackFunc(std::bind(&SystemSettingConnect::updateHandleDataAirplaneMode, this, std::placeholders::_1));
    mSysEvent.notifyPersonalHotspot.reqCallbackFunc(std::bind(&SystemSettingConnect::updatePersonalHotspot, this, std::placeholders::_1));
}

SystemSettingConnect::~SystemSettingConnect() {

}

void SystemSettingConnect::updateHandleDataAirplaneMode(const service::AirplaneModeTypes& airplaneMode) {
    if (airplaneMode == service::AirplaneModeTypes::Active) {
        mSysAdap.notifyUpdateAirplaneMode(SystemSettingAdapter::AirplaneModeEnums::Active);
    } else {
        mSysAdap.notifyUpdateAirplaneMode(SystemSettingAdapter::AirplaneModeEnums::Inactive);
    }
}

void SystemSettingConnect::updatePersonalHotspot(const service::PersonalHotspotTypes &personalHospot) {
    if (personalHospot == service::PersonalHotspotTypes::Active) mSysAdap.notifyUpdateInfoSystemSetting(ID_STATE_CALLBACK::PersonalHotspot, QVariant(1));
    else mSysAdap.notifyUpdateInfoSystemSetting(ID_STATE_CALLBACK::PersonalHotspot, QVariant(0));
}

}
