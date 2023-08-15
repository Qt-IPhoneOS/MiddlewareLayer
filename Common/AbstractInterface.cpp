#include "AbstractInterface.h"
#include <QDebug>

AbstractInterface::AbstractInterface() : m_state(AbstractState::State_Disconnected)
{
}

AbstractInterface::~AbstractInterface()
{
}

bool AbstractInterface::connect()
{
    std::unique_lock<std::shared_mutex> lock(m_mutex);
    if (m_state != AbstractState::State_Disconnected)
    {
        return false;
    }
    m_state = AbstractState::State_WaitConnected;
    doConnect();
    return true;
}

bool AbstractInterface::disconnect()
{
    std::unique_lock<std::shared_mutex> lock(m_mutex);
    if (m_state == AbstractState::State_Disconnected)
    {
        return false;
    }
    m_state = AbstractState::State_Disconnected;
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
    if (m_state != AbstractState::State_WaitConnected)
        return;

    m_state = AbstractState::State_Ready;
}

void AbstractInterface::doDisconnectedEvent()
{
    if (m_state != AbstractState::State_WaitConnected) {
        m_state = AbstractState::State_WaitConnected;
        return;
    }

    if (m_state == AbstractState::State_WaitConnected)
    {
        doDisconnect();
    }
}
