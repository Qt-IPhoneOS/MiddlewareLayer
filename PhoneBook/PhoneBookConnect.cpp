#include <PhoneBook/PhoneBookServiceProxy.h>
#include <PhoneBook/PhoneBookServiceEvent.h>
#include <PhoneBook/PhoneBookAdapter.h>

class PhoneBookConnect {
public:
    PhoneBookConnect(PhoneBookAdapter& instance);
    ~PhoneBookConnect();

    PhoneBookServiceProxy* mProxy {nullptr};
    PhoneBookServiceEvent* mEvent {nullptr};
    PhoneBookAdapter& mAdaper;
};


PhoneBookConnect::PhoneBookConnect(PhoneBookAdapter& instance)
    : mProxy(PhoneBookServiceProxy::instance())
    , mEvent(PhoneBookServiceEvent::instance())
    , mAdaper(instance)
{
    if (mProxy == nullptr)
        throw std::runtime_error("Create WifiService backend is failed");
}

PhoneBookConnect::~PhoneBookConnect()
{

}
