#include "NetworkMessage.hh"

NetworkMessage::NetworkMessage() { m_type = Type::IDLE; }

NetworkMessage::NetworkMessage(const std::string &info, Type type) {
    m_info = info;
    m_type = type;
}

std::string NetworkMessage::getInfo() const { return m_info; }

NetworkMessage::Type NetworkMessage::getType() const { return m_type; }