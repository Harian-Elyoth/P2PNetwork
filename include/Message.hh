#ifndef MESSAGE_HH
#define MESSAGE_HH

#include <string>
#include <string.h>
#include <netinet/in.h>
#include <time.h>

#include "MessageBuilder.hh"

class Message {

  public:


    static constexpr size_t s_max_size = 1024;
    /**
     * @brief Constructor
     */
    Message();

    /**
     * @brief Destructor
     */
    ~Message();

    /**
     * @brief Copy Constructor
     */
    Message(const Message &other);

    /**
     * @brief Serialize the message
     */
    virtual size_t serialize(char* buffer) const = 0;

    /**
     * @brief Deserialize the message
     */
    virtual void deserialize(const char* buffer) = 0;

    friend class MessageBuilder;

protected:
    
    timespec m_timestamp;
    sockaddr_in m_from;
    socklen_t m_from_len;
    sockaddr_in m_to;
    socklen_t m_to_len;

    /*

    JOIN: NA
    ACCEPT: data = map:<id, std::pair(ip, port)>
    DISCOVER_REQUEST: NA
    DISCOVER_RESPONSE: data = map:<id, std::pair(ip, port)>
    DATA_TRANSFER: data = <data>
    KEEP_ALIVE: NA
    HEART_BEAT: NA
    LEAVE: NA


    */
};

#endif // MESSAGE_HH
