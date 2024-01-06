//WARNING UNTESTED

#define DNS_NETWORK_API

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winsock2.h>

#define BUFFER_SIZE 1024

char* dns_network_custom(const char* custom_network_message) {
    //Initialize Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        perror("WSAStartup failed");
        return "Error: Could Not Initialize Winsock";
    }

    //Create a UDP socket
    SOCKET clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        perror("Error creating socket");
        WSACleanup();
        return "Error: Could Not Make A Socket To Contact Server With";
    }

    //Set up server address
    struct sockaddr_in serverAddress;
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("204.83.169.199"); //Server's IP address
    serverAddress.sin_port = htons(25542); //Server's Port

    //Send a message to the server
    sendto(clientSocket, custom_network_message, strlen(custom_network_message), 0,
           (struct sockaddr*)&serverAddress, sizeof(serverAddress));

    char* buffer = (char*)malloc(BUFFER_SIZE);

    //Receive the response from the server
    int serverAddrLen = sizeof(serverAddress);
    ssize_t receivedBytes = recvfrom(clientSocket, buffer, BUFFER_SIZE, 0,
                                     (struct sockaddr*)&serverAddress, &serverAddrLen);
    if (receivedBytes == -1) {
        perror("Error receiving data.");
        closesocket(clientSocket);
        free(buffer);
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

char* dns_network_check(const char* network_id) {
    char custom_message[BUFFER_SIZE];
    snprintf(custom_message, sizeof(custom_message), "check\n%s", network_id);
    return dns_network_custom(custom_message);
}

char* dns_network_request(const char* network_id) {
    char custom_message[BUFFER_SIZE];
    snprintf(custom_message, sizeof(custom_message), "request\n%s", network_id);
    return dns_network_custom(custom_message);
}

char* dns_network_status() {
    return dns_network_custom("status");
}

char* dns_network_time() {
    return dns_network_custom("time");
}
