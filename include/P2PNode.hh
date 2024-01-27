#include "NetworkMessage.hh"
#include <mutex>
#include <queue>
#include <string>
#include <thread>

#define MAX_SIMULTANEOUS_CONNECTIONS 3

class P2PNode {

  public:
    P2PNode();

    ~P2PNode();

    void init();
    void start();
    void stop();
    void release();

  private:
    std::string m_ip;
    uint16_t m_port;
    std::thread m_listenThread;
    int64_t m_listenSocket;

    std::thread m_msgHandlerThread;
    std::queue<NetworkMessage> m_msgQueue;
    std::mutex m_msgQueueMutex;

    static void listenThreadFunc(void *arg);
    static void msgHandlerThreadFunc(void *arg);

    bool listenToNodes();
    bool createSocket();
    bool bindSocket();

    void handleMsg(NetworkMessage msg);
    void sendMsg(NetworkMessage msg);
    void sendMsg(NetworkMessage msg, const std::string &ip,
                 const std::string &port);
};