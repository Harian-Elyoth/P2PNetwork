#include "P2PNode.hh"
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
P2PNode::P2PNode() {
    // TODO
}

P2PNode::~P2PNode() {
    // TODO
}

void P2PNode::init() {
    // TODO
}

void P2PNode::start() {
    // Initialize the threadfunc
    m_listenThread = std::thread(listenThreadFunc, this);
}

void P2PNode::stop() {
    // TODO
}

void P2PNode::release() {
    // TODO
}

void P2PNode::listenThreadFunc(void *arg) {
    P2PNode *node = static_cast<P2PNode *>(arg);
    if (!node->createSocket()) {
        std::cerr << "Failed to create socket" << std::endl;
        exit(EXIT_FAILURE);
    }
    if (!node->bindSocket()) {
        std::cerr << "Failed to bind socket" << std::endl;
        exit(EXIT_FAILURE);
    }
    if (!node->listenToNodes()) {
        std::cerr << "Failed to listen" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void P2PNode::handleMsg(NetworkMessage msg) {
    // TODO
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

    if (bind(m_listenSocket, (struct sockaddr *)&serverAddr,
             sizeof(serverAddr)) == -1) {
        std::cerr << "Error binding server socket\n";
        close(m_listenSocket);
        return false;
    }
    return true;
}
bool P2PNode::listenToNodes() {
    if (listen(m_listenSocket, MAX_SIMULTANEOUS_CONNECTIONS) == -1) {
        std::cerr << "Error listening for clients\n";
        close(m_listenSocket);
        std::exit(EXIT_FAILURE);
    }
    std::cout << "Node listening on port " << m_port << std::endl;
    return true;
}
