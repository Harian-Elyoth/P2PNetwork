#include "JoinMessage.hh"

std::unique_ptr<JoinMessage> JoinMessage::s_prototype = std::make_unique<JoinMessage>();


std::unique_ptr<Message> JoinMessage::clone() const
{
    return std::make_unique<JoinMessage>(*this);
}