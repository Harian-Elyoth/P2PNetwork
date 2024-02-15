#ifndef P2P_NODE_HH
#define P2P_NODE_HH

#include <mutex>
#include <queue>
#include <string>
#include <thread>

#include "Message.hh"
#include "MessageFactory.hh"
#include "MessageHandlerStrategy.hh"

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

    bool m_isRunning;

    uint16_t m_port;
    int64_t m_listenSocket;
    
    std::thread m_listenThread;
    std::thread m_msgHandlerThread;
    std::queue<Message*> m_msgQueue;
    std::mutex m_msgQueueMutex;

    bool m_isEntryPoint;
    const uint16_t m_bootstrapServerPort;
    const std::string m_bootstrapServerIp;

    static void listenThreadFunc(void *p_arg);
    static void msgHandlerThreadFunc(void *p_arg);

    bool createSocket();
    bool bindSocket();


    void sendMsg(Message* p_msg);
    void sendMsg(Message p_msg, const std::string &p_ip,
                 const std::string &p_port);

    MessageHandlerStrategy* m_msgHandlerStrategy;
};

#endif // P2P_NODE_HH
