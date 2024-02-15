#ifndef MESSAGE_HH
#define MESSAGE_HH

#include <string>
#include <string.h>
#include <netinet/in.h>
#include <time.h>

class Message {

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

    /**
     * @brief Constructor
     */
    Message();

    /**
     * @brief Destructor
     */
    virtual ~Message();

    /**
     * @brief Constructor
     */
    Message(Type type);

    /**
     * @brief Copy Constructor
     */
    Message(const Message &other);

    /**
     * @brief Serialize the message
     */
    virtual size_t serialize(char* buffer) const;

    /**
     * @brief Deserialize the message
     */
    virtual void deserialize(const char* buffer);

    /**
     * @brief Get the type of the message
     */
    Type getType() const;

    static Type checkType(const char* buffer);

protected:
    
    Type m_type;
    timespec m_timestamp;
    sockaddr_in m_from;
    socklen_t m_from_len;
    sockaddr_in m_to;
    socklen_t m_to_len;

};

#endif // MESSAGE_HH
