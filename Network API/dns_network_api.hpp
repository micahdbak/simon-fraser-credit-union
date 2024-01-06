#define DNS_NETWORK_API

#include <iostream>
#include <cstring>
#include <string>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>


namespace dns {

std::string network_custom(std::string custom_network_message) {
    //Create a UDP socket
    int clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (clientSocket == -1) {
        std::cerr << "Error creating socket" << std::endl;
        return "Error: Could Not Make A Socket To Contact Server With";
    }

    //Set up server address
    struct sockaddr_in serverAddress;
    std::memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("204.83.169.199"); //Server's IP address
    serverAddress.sin_port = htons(25542); //Server's Port

    //Send a message to the server
    sendto(clientSocket, custom_network_message.c_str(), custom_network_message.length(), 0,
           (struct sockaddr*)&serverAddress, sizeof(serverAddress));

    char buffer[1024];

    //Receive the response from the server
    ssize_t receivedBytes = recvfrom(clientSocket, buffer, sizeof(buffer), 0, nullptr, nullptr);
    if (receivedBytes == -1) {
        std::cerr << "Error receiving data." << std::endl;
        close(clientSocket);
        return "Error: No Responce From Server.";
    }

    //Process received data
    buffer[receivedBytes] = '\0';

    //Close the socket
    close(clientSocket);
    return buffer;
}

//Check how many unread packets are stored in the server
std::string network_check(std::string network_id) {
    return network_custom("check\n"+network_id);
}

//recived oldest unchecked packet
std::string network_request(std::string network_id) {
    return network_custom("request\n"+network_id);
}

//Used to check if the Server is Online
std::string network_status() {
    return network_custom("status");
}

//request server time (mainly for client & server to calibrate timezone differneces)
std::string network_time() {
    return network_custom("time");
}

}
