#include <SIM/SIMProxy.h>
#include <SIM/SIMEvent.h>
#include <SIM/SIMAdapter.h>

class SIMConnect {
public:
    SIMConnect(SIMAdapter& instance);
    ~SIMConnect();

    SIMProxy& mProxy;
    SIMEvent& mEvent;
    SIMAdapter& mAdaper;
};


SIMConnect::SIMConnect(SIMAdapter& instance)
    : mProxy(SIMProxy::instance())
    , mEvent(SIMEvent::instance())
    , mAdaper(instance)
{
}

SIMConnect::~SIMConnect() {

}
