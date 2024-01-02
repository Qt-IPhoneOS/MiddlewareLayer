#ifndef SIMADAPTER_H
#define SIMADAPTER_H

#include <Common/AbstractInterface.h>
#include <Feature/Signal.h>
#include <shared_mutex>

namespace midlayer {

class SIMConnect;
class SIMAdapter final : public AbstractInterface {
    friend class SIMConnect;
public:
    static SIMAdapter& instance();
    ~SIMAdapter();

    enum class ID_CALLBACK {
        Cellular_Data,
        Allow_Others_To_Join,
        Personal_Hotspot,
        Maximize_Compaxibility,
        None
    };

    uicommon::Signal<void(ID_CALLBACK, const int&)> notifyUpdateDataSIMService;

    void setIsAllowOthersToJoin(const bool & status);
    void setIsMaximizeCompatibility(const bool& status);
    void setIsCellularDataStatus(const bool& status);

    bool doConnect() override;
    bool doDisconnect() override;

private:
    SIMConnect* mConnect;

private: // singleton
    SIMAdapter();
};

}

#endif // SIMADAPTER_H
