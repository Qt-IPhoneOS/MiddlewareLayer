#ifndef PHONEBOOKADAPTER_H
#define PHONEBOOKADAPTER_H

#include <Common/AbstractInterface.h>
#include <Feature/Signal.h>
#include <shared_mutex>

class PhoneBookConnect;
class PhoneBookAdapter final : public AbstractInterface {
    friend class PhoneBookConnect;
public:
    static PhoneBookAdapter& getInstance();
    ~PhoneBookAdapter();

    bool doConnect() override;
    bool doDisconnect() override;

private:
    PhoneBookConnect* mConnect;

private: // singleton
    PhoneBookAdapter();
};

#endif // PHONEBOOKADAPTER_H
