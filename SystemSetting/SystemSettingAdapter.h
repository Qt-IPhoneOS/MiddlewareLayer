#ifndef SETTINGADAPTER_H
#define SETTINGADAPTER_H

#include <Common/AbstractInterface.h>
#include <Feature/Signal.h>
#include <shared_mutex>

namespace midlayer {

class SystemSettingConnect;
class SystemSettingAdapter final : public AbstractInterface {
    friend class SystemSettingConnect;
public:
    static SystemSettingAdapter& instance();
    ~SystemSettingAdapter();

    enum class AirplaneModeEnums {
        Inactive,
        Active
    };

    bool doConnect() override;
    bool doDisconnect() override;

public:
    AirplaneModeEnums getAirplaneMode() const;
    void setNewAirplaneMode(const AirplaneModeEnums&);

    uicommon::Signal<void(const AirplaneModeEnums&)> notifyUpdateAirplaneMode;

private:
    SystemSettingConnect* mSysConnect;
    AirplaneModeEnums mAirplaneMode = AirplaneModeEnums::Inactive;

private: // singleton
    SystemSettingAdapter();
};

}

#endif //SETTINGADAPTER_H
