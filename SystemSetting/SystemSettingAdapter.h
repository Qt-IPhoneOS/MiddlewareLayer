#ifndef SETTINGADAPTER_H
#define SETTINGADAPTER_H

#include <Common/AbstractInterface.h>
#include <Feature/Signal.h>
#include <shared_mutex>
#include "SystemSettingConnect.cpp"
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
    AirplaneModeEnums getAirplaneMode() const;
    bool setNewAirplaneMode(const AirplaneModeEnums&);

    signal::Signal<void(const AirplaneModeEnums&)> notifyUpdateAirplaneMode;

private:
    SystemSettingConnect* mSysConnect;
    AirplaneModeEnums mAirplaneMode = AirplaneModeEnums::Inactive;

private: // singleton
    SystemSettingAdapter();
};

#endif //SETTINGADAPTER_H
