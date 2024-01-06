//WARNING UNTESTED

#define DNS_NETWORK_API

#include <iostream>
#include <cstring>
#include <string>
#include <winsock2.h>

namespace dns {

std::string network_custom(std::string custom_network_message) {
    //Initialize Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed" << std::endl;
        return "Error: Could Not Initialize Winsock";
    }

    //Create a UDP socket
    SOCKET clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Error creating socket" << std::endl;
        WSACleanup();
        return "Error: Could Not Make A Socket To Contact Server With";
    }

    //Set up server address
    struct sockaddr_in serverAddress;
    std::memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("204.83.169.199"); //Server's IP address
    serverAddress.sin_port = htons(25543); //Server's Port

    //Send a message to the server
    sendto(clientSocket, custom_network_message.c_str(), custom_network_message.length(), 0,
           (struct sockaddr*)&serverAddress, sizeof(serverAddress));

    char buffer[1024];

    //Receive the response from the server
    int clientAddrLen = sizeof(serverAddress);
    ssize_t receivedBytes = recvfrom(clientSocket, buffer, sizeof(buffer), 0,
                                     (struct sockaddr*)&serverAddress, &clientAddrLen);
    if (receivedBytes == -1) {
        std::cerr << "Error receiving data." << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return "Error: No Response From Server.";
    }

    //Process received data
    buffer[receivedBytes] = '\0';

    //Close the socket
    closesocket(clientSocket);
    WSACleanup();
    return buffer;
}

std::string network_check(std::string network_id) {
    return network_custom("check\n" + network_id);
}

std::string network_request(std::string network_id) {
    return network_custom("request\n" + network_id);
}

std::string network_status() {
    return network_custom("status");
}

std::string network_time() {
    return network_custom("time");
}

}
