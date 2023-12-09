#include "PhoneBookAdapter.h"
#include "PhoneBookAdapterConnect.cpp"

PhoneBookAdapter::PhoneBookAdapter()
    : mConnect(new PhoneBookAdapterConnect(*this))
{

}

PhoneBookAdapter::~PhoneBookAdapter() {

}

PhoneBookAdapter& PhoneBookAdapter::instance() {
    static PhoneBookAdapter instance;
    return instance;
}

bool PhoneBookAdapter::doConnect() {
    if (mConnect->mProxy == nullptr)
        return false;

    mConnect->mProxy->connectService();
    return true;
}

bool PhoneBookAdapter::doDisconnect() {
    if (mConnect->mProxy == nullptr)
        return false;

    mConnect->mProxy->disconnectService();
    return true;
}

