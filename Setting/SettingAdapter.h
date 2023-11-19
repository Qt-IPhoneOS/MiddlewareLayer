#ifndef SETTINGADAPTER_H
#define SETTINGADAPTER_H

#include <Common/AbstractInterface.h>
#include <Feature/Signal.h>
#include <shared_mutex>
#include "SettingEnums/SettingEnums.h"

class SettingAdapterConnect;
class SettingAdapter final : public AbstractInterface {
    friend class SettingAdapterConnect;
public:
    static SettingAdapter& getInstance();
    ~SettingAdapter();

    bool doConnect() override;
    bool doDisconnect() override;

    void setAirplaneMode(const middlewarelayer::AirplaneMode&);

    signal::Signal<void(const middlewarelayer::AirplaneMode&)> onAirplaneModeChanged;

private:
    SettingAdapterConnect* mSettingAdapterConnect;
    middlewarelayer::AirplaneMode mAirplaneMode = middlewarelayer::AirplaneMode::Inactivve;
private: // singleton
    SettingAdapter();
};

#endif //SETTINGADAPTER_H