#ifndef JOIN_MESSAGE_HH
#define JOIN_MESSAGE_HH

#include "Message.hh"
#include <memory>

class JoinMessage : public Message
{
public:
    JoinMessage();
    virtual std::unique_ptr<Message> clone() const override;
    static std::unique_ptr<JoinMessage>
private:
    static std::unique_ptr<JoinMessage> s_prototype;
};

#endif // JOIN_MESSAGE_HH
