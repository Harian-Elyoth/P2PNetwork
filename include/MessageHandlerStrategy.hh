#include "Message.hh"

class MessageHandlerStrategy {

public:

    virtual void handleMessage(Message* message) = 0;
    virtual ~MessageHandlerStrategy() = default;

};