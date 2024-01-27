#include <string>

class NetworkMessage {
    enum class Type {
        IDLE,
        IDLE_ACK,
        JOIN,
        JOIN_ACK,
        LEAVE,
    };

  public:
    /**
     * @brief Constructor
     */
    NetworkMessage();

    /**
     * @brief Constructor
     */
    NetworkMessage(const std::string &info, Type type);

    /**
     * @brief Get message info
     */
    std::string getInfo() const;

    /**
     * @brief Get message type
     */
    Type getType() const;

  private:
    std::string m_info;
    Type m_type;
};