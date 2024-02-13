#include "MessageFactory.hh"

std::unique_ptr<Message> MessageFactory::createMessage(Type type)
{
    switch (type)
    {
    case Type::JOIN:
        return std::make_unique<JoinMessage>();
    case Type::ACCEPT:
        return std::make_unique<JoinResponseMessage>();
    case Type::LEAVE:
        return std::make_unique<LeaveMessage>();
    case Type::DISCOVER_REQUEST:
        return std::make_unique<LeaveResponseMessage>();
    case Type::DISCOVER_RESPONSE:
        return std::make_unique<PingMessage>();
    case Type::KEEP_ALIVE:
        return std::make_unique<PongMessage>();
    case Type::DATA_TRANSFER:
        return std::make_unique<DataMessage>();
    case Type::HEART_BEAT:
        return std::make_unique<DataResponseMessage>();
    default:
        return nullptr;
    }
}