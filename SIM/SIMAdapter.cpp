#include "SIMAdapter.h"
#include "SIMConnect.cpp"

SIMAdapter::SIMAdapter()
    : mConnect(new SIMConnect(*this))
{

}

SIMAdapter::~SIMAdapter() {

}

SIMAdapter& SIMAdapter::getInstance() {
    static SIMAdapter instance;
    return instance;
}

bool SIMAdapter::doConnect() {
    if (mConnect->mProxy == nullptr)
        return false;

    mConnect->mProxy->connectService();
    return true;
}

bool SIMAdapter::doDisconnect() {
    if (mConnect->mProxy == nullptr)
        return false;

    mConnect->mProxy->disconnectService();
    return true;
}

