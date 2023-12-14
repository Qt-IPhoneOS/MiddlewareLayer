#include <SIM/SIMServiceProxy.h>
#include <SIM/SIMServiceEvent.h>
#include <SIM/SIMAdapter.h>

namespace midlayer {

class SIMConnect {
public:
    SIMConnect(SIMAdapter& instance);
    ~SIMConnect();

    service::SIMServiceProxy* mProxy {nullptr};
    service::SIMServiceEvent* mEvent {nullptr};
    SIMAdapter& mAdaper;
};


SIMConnect::SIMConnect(SIMAdapter& instance)
    : mProxy(service::SIMServiceProxy::instance())
    , mEvent(service::SIMServiceEvent::instance())
    , mAdaper(instance)
{
}

SIMConnect::~SIMConnect() {

}

}
