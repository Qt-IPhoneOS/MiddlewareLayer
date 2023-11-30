#ifndef SIMADAPTER_H
#define SIMADAPTER_H

#include <Common/AbstractInterface.h>
#include <Feature/Signal.h>
#include <shared_mutex>

class SIMConnect;
class SIMAdapter final : public AbstractInterface {
    friend class SIMConnect;
public:
    static SIMAdapter& getInstance();
    ~SIMAdapter();

    bool doConnect() override;
    bool doDisconnect() override;

private:
    SIMConnect* mConnect;

private: // singleton
    SIMAdapter();
};

#endif // SIMADAPTER_H
