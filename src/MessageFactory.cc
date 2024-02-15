#include "MessageFactory.hh"

Message* MessageFactory::createMessage(Message::Type type)
{
    switch (type)
    {
        case Message::Type::JOIN:
        case Message::Type::ACCEPT:
        case Message::Type::LEAVE:
        case Message::Type::DISCOVER_REQUEST:
        case Message::Type::KEEP_ALIVE:
            return new Message(type);
        case Message::Type::DISCOVER_RESPONSE:
        case Message::Type::DATA_TRANSFER:
        case Message::Type::HEART_BEAT:
            return new DataMessage(type);
        default:
            return nullptr;
    }
}