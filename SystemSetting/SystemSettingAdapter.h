#ifndef SETTINGADAPTER_H
#define SETTINGADAPTER_H

#include <Common/AbstractInterface.h>
#include <Feature/Signal.h>
#include <shared_mutex>
#include "Common/Enums.h"
#include <QVariant>

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

    bool getIsPersonalHotspot() const;
    void setIsPersonalHotspot(const bool);

    bool getIsAllowJoinNetwork() const;
    void setNewIsAllowJoinNetwork(const bool);

    bool getIsPersonalHotspotActive() const;
    void setIsPersonalHotspotActive(const bool);

    uicommon::Signal<void(const AirplaneModeEnums&)> notifyUpdateAirplaneMode;
    uicommon::Signal<void(const ID_STATE_CALLBACK, const QVariant)> notifyUpdateInfoSystemSetting;

private:
    SystemSettingConnect* mSysConnect;
    AirplaneModeEnums mAirplaneMode = AirplaneModeEnums::Inactive;
    bool mIsPersonalHotspotActive {false};

private: // singleton
    SystemSettingAdapter();
};

}

#endif //SETTINGADAPTER_H
