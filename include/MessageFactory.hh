#ifndef MESSAGE_FACTORY_HH
#define MESSAGE_FACTORY_HH

#include "Message.hh"

class MessageFactory
{
public:
    enum class Type {
        JOIN,
        ACCEPT,
        DISCOVER_REQUEST,
        DISCOVER_RESPONSE,
        DATA_TRANSFER,
        KEEP_ALIVE,
        HEART_BEAT,
        LEAVE,
        UNKNOWN,
        NB_TYPES
    };

    static std::unique_ptr<Message> createMessage(Type type);
};

#endif // MESSAGE_FACTORY_HH
