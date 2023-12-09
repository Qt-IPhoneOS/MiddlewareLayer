#ifndef PHONEBOOKADAPTER_H
#define PHONEBOOKADAPTER_H

#include <Common/AbstractInterface.h>
#include <Feature/Signal.h>
#include <shared_mutex>
#include <list>

struct ContactInfo {
    uint32_t id;
    std::string firstName;
    std::string lastName;
    std::string formatName;
    std::string phoneNumber;
    std::string photo;
    bool isFav;
};

struct HistoryInfo {
    uint32_t id;
    std::string formatName;
    std::string phoneNumber;
    std::string time;
    int callingType;
};

class PhoneBookAdapterConnect;
class PhoneBookAdapter final : public AbstractInterface {
    friend class PhoneBookAdapterConnect;
public:
    static PhoneBookAdapter& instance();
    ~PhoneBookAdapter();

    bool doConnect() override;
    bool doDisconnect() override;

    signal::Signal<void(const std::list<ContactInfo>&)> onContactListChanged;
    signal::Signal<void(const std::list<HistoryInfo>&)> onHistoryListChanged;

private:
    PhoneBookAdapterConnect* mConnect;

private: // singleton
    PhoneBookAdapter();
};

#endif // PHONEBOOKADAPTER_H
