#include "PhoneBookAdapter.h"
#include "PhoneBookConnect.cpp"

PhoneBookAdapter::PhoneBookAdapter()
    : mConnect(new PhoneBookConnect(*this))
{

}

PhoneBookAdapter::~PhoneBookAdapter() {

}

PhoneBookAdapter& PhoneBookAdapter::getInstance() {
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

