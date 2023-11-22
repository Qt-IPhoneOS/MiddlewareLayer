#ifndef SETTINGADAPTER_H
#define SETTINGADAPTER_H

#include <Common/AbstractInterface.h>
#include <Feature/Signal.h>
#include <shared_mutex>
#include "SystemSettingServices/SystemSettingProxy.h"

class SystemSettingAdapter final : public AbstractInterface {
public:
    static SystemSettingAdapter& getInstance();
    ~SystemSettingAdapter();

    enum class AirplaneModeEnums {
        Inactive,
        Active
    };

    bool doConnect() override;
    bool doDisconnect() override;

public:
    bool setNewAirplaneMode(const AirplaneModeEnums&);
    void updateHandleDataAirplaneMode(const AirplaneModeTypes&);

public:
    signal::Signal<void(const AirplaneModeEnums&)> notifyUpdateAirplaneMode;

private:
    SystemSettingProxy& mSysProxy;
    SystemSettingEvent& mSysEvent;
    AirplaneModeEnums mAirplaneMode = AirplaneModeEnums::Inactive;


private: // singleton
    SystemSettingAdapter();
};

#endif //SETTINGADAPTER_H