#ifndef P2P_NODE_HH
#define P2P_NODE_HH

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

    uint16_t m_port;
    std::thread m_listenThread;
    int64_t m_listenSocket;

    std::thread m_msgHandlerThread;
    std::queue<NetworkMessage> m_msgQueue;
    std::mutex m_msgQueueMutex;

    bool m_isRunning;

    static void listenThreadFunc(void *p_arg);
    static void msgHandlerThreadFunc(void *p_arg);

  
    bool createSocket();
    bool bindSocket();

    void handleMsg(NetworkMessage p_msg);
    void sendMsg(NetworkMessage p_msg);
    void sendMsg(NetworkMessage p_msg, const std::string &p_ip,
                 const std::string &p_port);
};

#endif // P2P_NODE_HH
