#include <SystemSetting/SystemSettingProxy.h>
#include <SystemSetting/SystemSettingEvent.h>
#include <SystemSetting/SystemSettingAdapter.h>

class SystemSettingConnect {
public:
    SystemSettingConnect(SystemSettingAdapter& instance);
    ~SystemSettingConnect();

    void updateHandleDataAirplaneMode(const service::AirplaneModeTypes&);

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
