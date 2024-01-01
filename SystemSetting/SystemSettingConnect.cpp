#include <SystemSetting/SystemSettingProxy.h>
#include <SystemSetting/SystemSettingEvent.h>
#include <SystemSetting/SystemSettingAdapter.h>

namespace midlayer {

class SystemSettingConnect {
public:
    SystemSettingConnect(SystemSettingAdapter& instance);
    ~SystemSettingConnect();

    void updateHandleDataAirplaneMode(const service::AirplaneModeTypes&);
    void updateHandleDataCellularStatus(const service::CellularStatusTypes&);
    void updateHandleDataAllowOthersJoin(const service::AllowOthersToJoinTypes&);
    void updateHandleDataMaximizeCompa(const service::MaximizeCompatibilityTypes&);

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
    mSysEvent.notifyUpdateCellularStatus.reqCallbackFunc(std::bind(&SystemSettingConnect::updateHandleDataCellularStatus, this, std::placeholders::_1));
    mSysEvent.notifyUpdateAllowOthersToJoin.reqCallbackFunc(std::bind(&SystemSettingConnect::updateHandleDataAllowOthersJoin, this, std::placeholders::_1));
    mSysEvent.notifyUpdateMaximizeCompatibility.reqCallbackFunc(std::bind(&SystemSettingConnect::updateHandleDataMaximizeCompa, this, std::placeholders::_1));
}

SystemSettingConnect::~SystemSettingConnect() {

}

void SystemSettingConnect::updateHandleDataAirplaneMode(const service::AirplaneModeTypes& airplaneMode) {
    if (airplaneMode == service::AirplaneModeTypes::Active) {
        mSysAdap.notifyUpdateDataSystemSeting(SystemSettingAdapter::ID_CALLBACK::Airplane_Mode, 1);
    } else {
        mSysAdap.notifyUpdateDataSystemSeting(SystemSettingAdapter::ID_CALLBACK::Airplane_Mode, 0);
    }
}

void SystemSettingConnect::updateHandleDataCellularStatus(const service::CellularStatusTypes& newStatus) {
    if (newStatus == service::CellularStatusTypes::Active) {
        mSysAdap.notifyUpdateDataSystemSeting(SystemSettingAdapter::ID_CALLBACK::Cellular_Network, 1);
    } else {
        mSysAdap.notifyUpdateDataSystemSeting(SystemSettingAdapter::ID_CALLBACK::Cellular_Network, 0);
    }
}
void SystemSettingConnect::updateHandleDataAllowOthersJoin(const service::AllowOthersToJoinTypes& newStatus) {
    if (newStatus == service::AllowOthersToJoinTypes::Enable) {
        mSysAdap.notifyUpdateDataSystemSeting(SystemSettingAdapter::ID_CALLBACK::Allow_Others_To_Join, 1);
    } else {
        mSysAdap.notifyUpdateDataSystemSeting(SystemSettingAdapter::ID_CALLBACK::Allow_Others_To_Join, 0);
    }
}
void SystemSettingConnect::updateHandleDataMaximizeCompa(const service::MaximizeCompatibilityTypes& newStatus) {
    if (newStatus == service::MaximizeCompatibilityTypes::Inactive) {
        mSysAdap.notifyUpdateDataSystemSeting(SystemSettingAdapter::ID_CALLBACK::Maximize_Compaxibility, 0);
    } else {
        mSysAdap.notifyUpdateDataSystemSeting(SystemSettingAdapter::ID_CALLBACK::Maximize_Compaxibility, 1);
    }
}

}
