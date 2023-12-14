#include <PhoneBook/PhoneBookServiceProxy.h>
#include <PhoneBook/PhoneBookServiceEvent.h>
#include <PhoneBook/PhoneBookAdapter.h>
#include <QDebug>

namespace midlayer {

class PhoneBookAdapterConnect {
public:
    PhoneBookAdapterConnect(PhoneBookAdapter& instance);
    ~PhoneBookAdapterConnect();

    service::PhoneBookServiceProxy* mProxy {nullptr};
    service::PhoneBookServiceEvent* mEvent {nullptr};
    PhoneBookAdapter& mAdaper;

    void onServiceConnected();
    void onServiceDisconnected();

    void onQueryContact(const std::list<service::PhoneContactInfo>& list);
    void onQueryHistory(const std::list<service::PhoneHistoryInfo>& list);
};


PhoneBookAdapterConnect::PhoneBookAdapterConnect(PhoneBookAdapter& instance)
    : mProxy(service::PhoneBookServiceProxy::instance())
    , mEvent(service::PhoneBookServiceEvent::instance())
    , mAdaper(instance)
{
    if (mProxy == nullptr)
        throw std::runtime_error("Create WifiService backend is failed");

    mEvent->notifyConnectedEvent.reqCallbackFunc(std::bind(&PhoneBookAdapterConnect::onServiceConnected, this));
    mEvent->notifyDisconnectedEvent.reqCallbackFunc(std::bind(&PhoneBookAdapterConnect::onServiceDisconnected, this));
}

PhoneBookAdapterConnect::~PhoneBookAdapterConnect()
{
}

void PhoneBookAdapterConnect::onServiceConnected()
{
    mEvent->notifyQueryContact.reqCallbackFunc(std::bind(&PhoneBookAdapterConnect::onQueryContact, this, std::placeholders::_1));
    mEvent->notifyQueryHistory.reqCallbackFunc(std::bind(&PhoneBookAdapterConnect::onQueryHistory, this, std::placeholders::_1));

    if (mProxy == nullptr)
        return;

    mProxy->queryPhoneBook(service::PhoneBookDataType::Contact);
    mProxy->queryPhoneBook(service::PhoneBookDataType::History);
}

void PhoneBookAdapterConnect::onServiceDisconnected()
{
    mEvent->notifyConnectedEvent.unReqCallbackFunc();
    mEvent->notifyDisconnectedEvent.unReqCallbackFunc();
    mEvent->notifyQueryContact.unReqCallbackFunc();
    mEvent->notifyQueryHistory.unReqCallbackFunc();

}

void PhoneBookAdapterConnect::onQueryContact(const std::list<service::PhoneContactInfo> &list)
{
    std::list<ContactInfo> contacts;
    for (auto item = list.begin(); item != list.end(); ++item)
    {
        ContactInfo contact;
        contact.id = item->id;
        contact.firstName = item->firstName;
        contact.lastName = item->lastName;
        contact.formatName = item->formatName;
        contact.phoneNumber = item->phoneNumber;
        contact.photo = item->photo;
        contact.isFav = item->isFav;

        contacts.emplace_back(contact);
    }

    if (contacts.size() > 0)
    {
        mAdaper.onContactListChanged(contacts);
    }
}

void PhoneBookAdapterConnect::onQueryHistory(const std::list<service::PhoneHistoryInfo> &list)
{
    std::list<HistoryInfo> histories;
    for (auto item = list.begin(); item != list.end(); ++item)
    {
        HistoryInfo history;
        history.id = item->id;
        history.formatName = item->formatName;
        history.phoneNumber = item->phoneNumber;
        history.time = item->time;
        history.callingType = static_cast<int>(item->callingType);

        histories.emplace_back(history);
    }

    if (histories.size() > 0)
    {
        mAdaper.onHistoryListChanged(histories);
    }
}

}
