#include <PhoneBook/PhoneBookProxy.h>
#include <PhoneBook/PhoneBookEvent.h>
#include <PhoneBook/PhoneBookAdapter.h>

class PhoneBookConnect {
public:
    PhoneBookConnect(PhoneBookAdapter& instance);
    ~PhoneBookConnect();

    PhoneBookProxy& mProxy;
    PhoneBookEvent& mEvent;
    PhoneBookAdapter& mAdaper;
};


PhoneBookConnect::PhoneBookConnect(PhoneBookAdapter& instance)
    : mProxy(PhoneBookProxy::getInstance())
    , mEvent(PhoneBookEvent::getInstance())
    , mAdaper(instance)
{
}

PhoneBookConnect::~PhoneBookConnect() {

}
