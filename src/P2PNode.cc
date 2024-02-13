#include "P2PNode.hh"
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
P2PNode::P2PNode()
    : m_isRunning(false), m_port(55660), m_listenSocket(-1), m_listenThread(),
      m_msgHandlerThread(), m_msgQueue(), m_msgQueueMutex()
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
    NetworkMessage joinMessage;


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
            NetworkMessage l_msg = l_node->m_msgQueue.front();
            l_node->m_msgQueue.pop();
            l_node->handleMsg(l_msg);
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
        char buffer [Message::s_max_size];
        sockaddr l_incoming_addr;
        socklen_t l_incoming_addr_len = sizeof(l_incoming_addr); // Initialize the length

        ssize_t l_bytes_received = recvfrom(l_node->m_listenSocket, buffer, Message::s_max_size, 0, &l_incoming_addr, &l_incoming_addr_len);

        if (l_bytes_received == -1) {
            // Handle error, for example:
            perror("recvfrom failed");
            return; // or throw an exception
        }

        // Check that we received enough bytes to form a Message object
        if (bytes_received < sizeof(Message)) {
            std::cerr << "Received message was too short to be a Message object\n";
            return; // or throw an exception
        } 
        Message l_m;
        l_m.deserialize(buffer);
        NetworkMessage l_msg(l_m, l_incoming_addr, l_incoming_addr_len);

        // Use std::lock_guard for exception safety
        std::lock_guard<std::mutex> lock(l_node->m_msgQueueMutex);
        l_node->m_msgQueue.push(l_msg);
        // Mutex is automatically unlocked here
    }

}

void P2PNode::handleMsg(NetworkMessage p_msg) {
    
}

void P2PNode::sendMsg(NetworkMessage msg) {
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
