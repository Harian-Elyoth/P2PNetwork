#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "Message.hh"

int main() {
    // Create a UDP socket
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        std::cerr << "Failed to create socket" << std::endl;
        return 1;
    }

    // Set up the server address
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(55660);
    if (inet_pton(AF_INET, "127.0.0.1", &(serverAddr.sin_addr)) <= 0) {
        std::cerr << "Invalid address" << std::endl;
        return 1;
    }

    // Create a message
    Message message("", Message::CommandType::JOIN);
    size_t messageSize = sizeof(message);
    char* messagePtr[Message::s_max_size];
    message.serialize((char*)messagePtr);
    // Send the message
    ssize_t numBytesSent = sendto(sockfd, (void*)messagePtr, messageSize, 0,
                                  (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if (numBytesSent < 0) {
        std::cerr << "Failed to send message" << std::endl;
        return 1;
    }

    std::cout << "Message sent successfully" << std::endl;

    // Close the socket
    close(sockfd);

    return 0;
}