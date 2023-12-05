#include <SystemSetting/SystemSettingProxy.h>
#include <SystemSetting/SystemSettingEvent.h>
#include <SystemSetting/SystemSettingAdapter.h>

class SystemSettingConnect {
public:
    SystemSettingConnect(SystemSettingAdapter& instance);
    ~SystemSettingConnect();

    void updateHandleDataAirplaneMode(const AirplaneModeTypes&);

    SystemSettingProxy& mSysProxy;
    SystemSettingEvent& mSysEvent;
    SystemSettingAdapter& mSysAdap;
};


SystemSettingConnect::SystemSettingConnect(SystemSettingAdapter& instance)
    : mSysProxy(SystemSettingProxy::instance())
    , mSysEvent(SystemSettingEvent::instance())
    , mSysAdap(instance)
{
    mSysEvent.notifyUpdateAirplaneMode.reqCallbackFunc(std::bind(&SystemSettingConnect::updateHandleDataAirplaneMode, this, std::placeholders::_1));
}

SystemSettingConnect::~SystemSettingConnect() {

}

void SystemSettingConnect::updateHandleDataAirplaneMode(const AirplaneModeTypes& airplaneMode) {
    if (airplaneMode == AirplaneModeTypes::Active) {
        mSysAdap.notifyUpdateAirplaneMode(SystemSettingAdapter::AirplaneModeEnums::Active);
    } else {
        mSysAdap.notifyUpdateAirplaneMode(SystemSettingAdapter::AirplaneModeEnums::Inactive);
    }
}
