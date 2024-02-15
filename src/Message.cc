#include "Message.hh"
#include <iostream>

Message::Message() : m_type(Type::UNKNOWN) {}

Message::Message(Type type) : m_type(type) {}

Message::~Message() {}

Message::Message(const Message &other) {
    m_type = other.m_type;
    m_timestamp = other.m_timestamp;
    m_from = other.m_from;
    m_from_len = other.m_from_len;
    m_to = other.m_to;
    m_to_len = other.m_to_len;
}

size_t Message::serialize(char* buffer) const
{
    if (buffer == nullptr) {
        std::cerr << "Buffer is null" << std::endl;
        return 0;
    }
    size_t total_size = sizeof(m_type) \
        + sizeof(m_timestamp) \
        + sizeof(m_from) \
        + sizeof(m_from_len) \
        + sizeof(m_to) \
        + sizeof(m_to_len);

    char* CurrentPos = buffer;
    memcpy(CurrentPos, &m_type, sizeof(m_type));
    CurrentPos += sizeof(m_type);
    memcpy(CurrentPos, &m_timestamp, sizeof(m_timestamp));
    CurrentPos += sizeof(m_timestamp);
    memcpy(CurrentPos, &m_from, sizeof(m_from));
    CurrentPos += sizeof(m_from);
    memcpy(CurrentPos, &m_from_len, sizeof(m_from_len));
    CurrentPos += sizeof(m_from_len);
    memcpy(CurrentPos, &m_to, sizeof(m_to));
    CurrentPos += sizeof(m_to);
    memcpy(CurrentPos, &m_to_len, sizeof(m_to_len));
    CurrentPos += sizeof(m_to_len);
    return total_size;
}

void Message::deserialize(const char* buffer)
{
    if (buffer == nullptr) {
        std::cerr << "Buffer is null" << std::endl;
        return;
    }
    char* CurrentPos = const_cast<char*>(buffer);
    memcpy(&m_type, CurrentPos, sizeof(m_type));
    CurrentPos += sizeof(m_type);
    memcpy(&m_timestamp, CurrentPos, sizeof(m_timestamp));
    CurrentPos += sizeof(m_timestamp);
    memcpy(&m_from, CurrentPos, sizeof(m_from));
    CurrentPos += sizeof(m_from);
    memcpy(&m_from_len, CurrentPos, sizeof(m_from_len));
    CurrentPos += sizeof(m_from_len);
    memcpy(&m_to, CurrentPos, sizeof(m_to));
    CurrentPos += sizeof(m_to);
    memcpy(&m_to_len, CurrentPos, sizeof(m_to_len));
    CurrentPos += sizeof(m_to_len);

}

Message::Type Message::getType() const { return m_type; }

Message::Type Message::checkType(const char* buffer) {
    if (buffer == nullptr) {
        std::cerr << "Buffer is null" << std::endl;
        return Type::UNKNOWN;
    }
    char* CurrentPos = const_cast<char*>(buffer);
    Type l_type;
    memcpy(&l_type, CurrentPos, sizeof(l_type));
    return l_type;
}
