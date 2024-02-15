#ifndef DATA_MESSAGE_HH
#define DATA_MESSAGE_HH

#include <string>
#include <string.h>
#include <netinet/in.h>
#include <time.h>
#include "Message.hh"

class DataMessage : public Message {

  public:

    static constexpr size_t s_max_msg_size = 1024;
    /**
     * @brief Constructor
     */
    DataMessage();

    /**
     * @brief Constructor
     */
    DataMessage(Type p_type);

    /**
     * @brief Destructor
     */
    ~DataMessage() override;

    /**
     * @brief Copy Constructor
     */
    DataMessage(const DataMessage &other);

    /**
     * @brief Move constructor
     */
    DataMessage(DataMessage &&other);

    /**
     * @brief Serialize the message
     */
    size_t serialize(char* buffer) const override;

    /**
     * @brief Deserialize the message
     */
    void deserialize(const char* buffer) override;


private:
    
    char m_buffer[s_max_msg_size];

};

#endif // MESSAGE_HH
