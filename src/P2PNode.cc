#include "P2PNode.hh"
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define BOOTSTRAP_SERVER_IP "127.0.0.1"
#define BOOTSTRAP_SERVER_PORT 55660

P2PNode::P2PNode()
    :   m_isRunning(false),
        m_port(55660),
        m_listenSocket(-1), 
        m_listenThread(),
        m_msgHandlerThread(), 
        m_msgQueue(), 
        m_msgQueueMutex(), 
        m_isEntryPoint(false),
        m_bootstrapServerPort(BOOTSTRAP_SERVER_PORT), 
        m_bootstrapServerIp(BOOTSTRAP_SERVER_IP)
{
    // TODO
}

P2PNode::~P2PNode() {
    // TODO
}

void P2PNode::init() {
    // TODO
}

void P2PNode::start() {
    // Initialize the thread function
    m_isRunning = true;
    m_listenThread = std::thread(listenThreadFunc, this);
    m_msgHandlerThread = std::thread(msgHandlerThreadFunc, this);

    // Send JOIN message in a broadcast way
    Message* joinMessage = MessageFactory::createMessage(Message::Type::JOIN);

    sendMsg(joinMessage);

    m_listenThread.join();
    m_msgHandlerThread.join();
}

void P2PNode::stop() {
    // TODO
}

void P2PNode::release() {
    // TODO
}
void P2PNode::msgHandlerThreadFunc(void *p_arg) {
    P2PNode *l_node = static_cast<P2PNode *>(p_arg);
    while(l_node->m_isRunning)
    {
        std::lock_guard<std::mutex> lock(l_node->m_msgQueueMutex);
        if (!l_node->m_msgQueue.empty()) {
            Message *l_msg = l_node->m_msgQueue.front();
            l_node->m_msgHandlerStrategy->handleMessage(l_msg);
            delete l_msg;
            l_node->m_msgQueue.pop();
        }
    }
}  


void P2PNode::listenThreadFunc(void *p_arg) {
    P2PNode *l_node = static_cast<P2PNode *>(p_arg);
    if (!l_node->createSocket()) {
        std::cerr << "Failed to create socket" << std::endl;
        exit(EXIT_FAILURE);
    }
    if (!l_node->bindSocket()) {
        std::cerr << "Failed to bind socket" << std::endl;
        exit(EXIT_FAILURE);
    }
    while(l_node->m_isRunning)
    {   
        constexpr size_t l_max_size = sizeof(Message) + DataMessage::s_max_msg_size;
        char buffer[l_max_size];
        sockaddr l_incoming_addr;
        socklen_t l_incoming_addr_len = sizeof(l_incoming_addr); // Initialize the length

        // Read the message
        ssize_t l_bytes_received = recvfrom(l_node->m_listenSocket, buffer, l_max_size, 0, &l_incoming_addr, &l_incoming_addr_len);
        
        if (l_bytes_received == -1) 
        {
            // Handle error, for example:
            perror("recvfrom failed");
            return; // or throw an exception
        }

        // Check that we received enough bytes to form a Message object
        if ((l_bytes_received == sizeof(Message)) || (l_bytes_received == sizeof(Message) + DataMessage::s_max_msg_size)) 
        {
            std::cerr << "Received message was too short to be a Message object\n";
            return; // or throw an exception
        } 

        Message::Type l_recv_msg_type = Message::checkType(buffer);

        Message* l_msg = MessageFactory::createMessage(l_recv_msg_type);
        l_msg->deserialize(buffer);

        // Use std::lock_guard for exception safety
        std::lock_guard<std::mutex> lock(l_node->m_msgQueueMutex);
        l_node->m_msgQueue.push(l_msg);
        // Mutex is automatically unlocked here
    }

}


void P2PNode::sendMsg(Message* msg) {
    // TODO
}

void sendMsg(const std::string &msg, const std::string &ip,
             const std::string &port) {
    // TODO
}

bool P2PNode::createSocket() {
    m_listenSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (m_listenSocket == -1) {
        std::cerr << "Error creating server socket\n";
        return false;
    }
    return true;
}
bool P2PNode::bindSocket() {
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(m_port);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    int reuse = 1;
    if (setsockopt(m_listenSocket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1) {
        std::cerr << "Error setting socket option\n";
        close(m_listenSocket);
        return false;
    }

    if (bind(m_listenSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "Error binding server socket\n";
        close(m_listenSocket);
        return false;
    }
    return true;
}
