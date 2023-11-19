#ifndef ABSTRACTINTERFACE_H
#define ABSTRACTINTERFACE_H

#include <vector>
#include <shared_mutex>
#include <mutex>

class AbstractInterface {
public:
    AbstractInterface();
    ~AbstractInterface();

    enum class AbstractState {
        State_Disconnected,
        State_WaitConnected,
        State_Ready
    };

    virtual bool connect();
    virtual bool disconnect();
    virtual bool doConnect();
    virtual bool doDisconnect();
    virtual void doConnectedEvent();
    virtual void doDisconnectedEvent();

protected:
    AbstractState mState;
    std::shared_mutex mMutex;
};

#endif // ABSTRACTINTERFACE_H

