#include "SIMAdapter.h"
#include "SIMConnect.cpp"

using namespace midlayer;

SIMAdapter::SIMAdapter()
    : mConnect(new SIMConnect(*this))
{

}

SIMAdapter::~SIMAdapter() {

}

SIMAdapter& SIMAdapter::instance() {
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


void SIMAdapter::setIsAllowOthersToJoin(const bool &status) {
    mConnect->mProxy->setAllowOthersToJoinNetwork(static_cast<service::AllowOthersToJoinTypes>(status));
}

void SIMAdapter::setIsMaximizeCompatibility(const bool &status) {
    mConnect->mProxy->setMaximizeCompatibility(static_cast<service::MaximizeCompatibilityTypes>(status));
}

void SIMAdapter::setIsCellularDataStatus(const bool& status) {
    mConnect->mProxy->setCellularStatus(static_cast<service::CellularStatusTypes>(status));
}
