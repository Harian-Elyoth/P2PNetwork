#include "DataMessage.hh"


DataMessage::DataMessage()
{}

/**
 * @brief Constructor
 */
DataMessage::DataMessage(Type p_type)
{
    m_type = p_type;
}

/**
 * @brief Destructor
 */
DataMessage::~DataMessage()
{}

/**
 * @brief Copy Constructor
 */
DataMessage::DataMessage(const DataMessage &other) : Message(other) {
    // TODO: Implement this
    (void)other;
}

/**
 * @brief Move constructor
 */
DataMessage::DataMessage(DataMessage &&other) {
    // TODO: Implement this
    (void)other;
}

/**
 * @brief Serialize the message
 */
size_t DataMessage::serialize(char* buffer) const {
    // TODO: Implement this
    (void)buffer;
    return 0;
}

/**
 * @brief Deserialize the message
 */
void DataMessage::deserialize(const char* buffer) {
    // TODO: Implement this
    (void)buffer;
}


