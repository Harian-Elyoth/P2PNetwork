#ifndef MESSAGE_BUILDER_HH
#define MESSAGE_BUILDER_HH

#include "Message.hh"
#include <memory>

class MessageBuilder
{
public:
    MessageBuilder();
    ~MessageBuilder();
    MessageBuilder& addTimestamp(time_t p_timestamp);
    MessageBuilder& setFrom(const sockaddr& p_from, const socklen_t& p_from_len);
    MessageBuilder& setTo(const sockaddr& p_to, const socklen_t& p_to_len);
    std::unique_ptr<Message> build();

private:
    std::unique_ptr<Message> m_msg;
};

#endif // MESSAGE_BUILDER_HH
