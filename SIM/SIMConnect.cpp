#include <SIM/SIMServiceProxy.h>
#include <SIM/SIMServiceEvent.h>
#include <SIM/SIMAdapter.h>

namespace midlayer {

class SIMConnect {
public:
    SIMConnect(SIMAdapter& instance);
    ~SIMConnect();

    void updateHandleDataCellularStatus(const service::CellularStatusTypes&);
    void updateHandleDataAllowOthersJoin(const service::AllowOthersToJoinTypes&);
    void updateHandleDataMaximizeCompa(const service::MaximizeCompatibilityTypes&);

    service::SIMServiceProxy* mProxy {nullptr};
    service::SIMServiceEvent* mEvent {nullptr};
    SIMAdapter& mAdaper;
};


SIMConnect::SIMConnect(SIMAdapter& instance)
    : mProxy(service::SIMServiceProxy::instance())
    , mEvent(service::SIMServiceEvent::instance())
    , mAdaper(instance)
{
    mEvent->notifyUpdateCellularStatus.reqCallbackFunc(std::bind(&SIMConnect::updateHandleDataCellularStatus, this, std::placeholders::_1));
    mEvent->notifyUpdateAllowOthersToJoin.reqCallbackFunc(std::bind(&SIMConnect::updateHandleDataAllowOthersJoin, this, std::placeholders::_1));
    mEvent->notifyUpdateMaximizeCompatibility.reqCallbackFunc(std::bind(&SIMConnect::updateHandleDataMaximizeCompa, this, std::placeholders::_1));
}

SIMConnect::~SIMConnect() {

}

void SIMConnect::updateHandleDataCellularStatus(const service::CellularStatusTypes& newStatus) {
    if (newStatus == service::CellularStatusTypes::Active) {
        mAdaper.notifyUpdateDataSIMService(SIMAdapter::ID_CALLBACK::Cellular_Data, 1);
    } else {
        mAdaper.notifyUpdateDataSIMService(SIMAdapter::ID_CALLBACK::Cellular_Data, 0);
    }
}
void SIMConnect::updateHandleDataAllowOthersJoin(const service::AllowOthersToJoinTypes& newStatus) {
    if (newStatus == service::AllowOthersToJoinTypes::Enable) {
        mAdaper.notifyUpdateDataSIMService(SIMAdapter::ID_CALLBACK::Allow_Others_To_Join, 1);
    } else {
        mAdaper.notifyUpdateDataSIMService(SIMAdapter::ID_CALLBACK::Allow_Others_To_Join, 0);
    }
}
void SIMConnect::updateHandleDataMaximizeCompa(const service::MaximizeCompatibilityTypes& newStatus) {
    if (newStatus == service::MaximizeCompatibilityTypes::Inactive) {
        mAdaper.notifyUpdateDataSIMService(SIMAdapter::ID_CALLBACK::Maximize_Compaxibility, 0);
    } else {
        mAdaper.notifyUpdateDataSIMService(SIMAdapter::ID_CALLBACK::Maximize_Compaxibility, 1);
    }
}

}
