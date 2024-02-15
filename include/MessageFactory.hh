#ifndef MESSAGE_FACTORY_HH
#define MESSAGE_FACTORY_HH

#include "Message.hh"
#include "DataMessage.hh"
#include <memory>

class MessageFactory
{

public:
    static Message* createMessage(Message::Type type);
};

#endif // MESSAGE_FACTORY_HH
