#include <SystemSetting/SystemSettingProxy.h>
#include <SystemSetting/SystemSettingEvent.h>
//#include <SystemSetting/SystemSettingAdapter.h>

class SystemSettingConnect {
public:
    SystemSettingConnect();
    ~SystemSettingConnect();

    void updateHandleDataAirplaneMode(const AirplaneModeTypes&);

    SystemSettingProxy& mSysProxy;
    SystemSettingEvent& mSysEvent;
//    SystemSettingAdapter& mSysAdap;
};


SystemSettingConnect::SystemSettingConnect()
    : mSysProxy(SystemSettingProxy::getInstance())
    , mSysEvent(SystemSettingEvent::getInstance())
//    , mSysAdap(SystemSettingAdapter::getInstance())
{
    mSysEvent.notifyUpdateAirplaneMode.reqCallbackFunc(std::bind(&SystemSettingConnect::updateHandleDataAirplaneMode, this, std::placeholders::_1));
}

SystemSettingConnect::~SystemSettingConnect() {

}

void SystemSettingConnect::updateHandleDataAirplaneMode(const AirplaneModeTypes& airplaneMode) {
    if (airplaneMode == AirplaneModeTypes::Active) {
//        mSysAdap.notifyUpdateAirplaneMode(SystemSettingAdapter::AirplaneModeEnums::Active);
    } else {
//        mSysAdap.notifyUpdateAirplaneMode(SystemSettingAdapter::AirplaneModeEnums::Inactive);
    }
}
