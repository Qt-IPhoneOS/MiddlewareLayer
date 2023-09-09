#include "AbstractInterface.h"
#include <QDebug>

AbstractInterface::AbstractInterface() : mState(AbstractState::State_Disconnected)
{
}

AbstractInterface::~AbstractInterface()
{
}

bool AbstractInterface::connect()
{
    std::unique_lock<std::shared_mutex> lock(mMutex);
    if (mState != AbstractState::State_Disconnected)
    {
        return false;
    }
    mState = AbstractState::State_WaitConnected;
    doConnect();
    return true;
}

bool AbstractInterface::disconnect()
{
    std::unique_lock<std::shared_mutex> lock(mMutex);
    if (mState == AbstractState::State_Disconnected)
    {
        return false;
    }
    mState = AbstractState::State_Disconnected;
    doDisconnect();
    return true;
}

bool AbstractInterface::doConnect()
{
    return true;
}

bool AbstractInterface::doDisconnect()
{
    return true;
}

void AbstractInterface::doConnectedEvent()
{
    if (mState != AbstractState::State_WaitConnected)
        return;

    mState = AbstractState::State_Ready;
}

void AbstractInterface::doDisconnectedEvent()
{
    if (mState != AbstractState::State_WaitConnected) {
        mState = AbstractState::State_WaitConnected;
        return;
    }

    if (mState == AbstractState::State_WaitConnected)
    {
        doDisconnect();
    }
}
